#include "calibrationdialog.hpp"
#include "ui_calibrationdialog.h"

#include "APICameraSystem.hpp"

#include "cameramodel.hpp"
#include "globalcalibrationwidget.hpp"
#include "singlecalibrationwidget.hpp"

#include <QMessageBox>
#include <QtConcurrentRun>

CalibrationDialog::CalibrationDialog(QWidget *parent, kitrokopter::APICameraSystem *camsys) :
    QDialog(parent),
    ui(new Ui::CalibrationDialog),
    cameraSystem(camsys)
{
    ui->setupUi(this);

    // Connect the tab change signal before setting up the tabs to capture the change to the first tab.
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
    setupTabs();

    connect(ui->startCalibrationButton, SIGNAL(clicked()), this, SLOT(startCalibration()));
    connect(ui->takePictureButton, SIGNAL(clicked()), this, SLOT(takePicture()));
    connect(ui->calculateCalibrationButton, SIGNAL(clicked()), this, SLOT(calculateCalibration()));
    connect(&takePicturesWatcher, SIGNAL(finished()), this, SLOT(takePictureDone()));
    connect(&calculationWatcher, SIGNAL(finished()), this, SLOT(calculateCalibrationDone()));
}

CalibrationDialog::~CalibrationDialog()
{
    delete ui;
}

void CalibrationDialog::setupTabs()
{
    // Clear all tab pages.
    ui->tabWidget->clear();
    for (QWidget *widget : tabPages)
        delete widget;
    for (auto camera : cameraModels)
        delete camera;
    cameraModels.clear();

    // Create tabs for single cameras.
    for (int i = 0; i < cameraSystem->getCameraAmount(); ++i) {
        kitrokopter::APICamera *camera = cameraSystem->getCamera(i);
        CameraModel *model = new CameraModel(this, camera);
        cameraModels.append(model);
        SingleCalibrationWidget *widget = new SingleCalibrationWidget(this, model);
        ui->tabWidget->addTab(widget, QString("Camera &%1").arg(i));
    }

    // Create a tab showing all cameras.
    GlobalCalibrationWidget *global = new GlobalCalibrationWidget(this, cameraModels);
    ui->tabWidget->addTab(global, "&All");
}

void CalibrationDialog::activateCamera(int cam, bool active)
{
    auto camera = cameraSystem->getCamera(cam);
    if (camera) {
        camera->sendPictureSendingActivation(active);
    }
}

void CalibrationDialog::tabChanged(int tab)
{
    int camAmount = cameraSystem->getCameraAmount();
    // Stop receiving images from the camera on the previous tab.
    if (prevTab < camAmount) {
        activateCamera(tab, false);
    } else {
        for (int i = 0; i < camAmount; ++i) {
            activateCamera(i, false);
        }
    }
    // Receive images from the camera on the new tab, or all cameras.
    if (tab < camAmount) {
        activateCamera(tab, true);
    } else {
        for (int i = 0; i < camAmount; ++i) {
            activateCamera(i, true);
        }
    }
    // Save previous tab for the next switch.
    prevTab = tab;
}

void CalibrationDialog::startCalibration()
{
    // Get calibration parameters.
    int rowCount, columnCount, fieldWidth, fieldHeight;
    rowCount = ui->rowCountSpinBox->value();
    columnCount = ui->columnCountSpinBox->value();
    fieldWidth = ui->fieldWidthSpinBox->value();
    fieldHeight = ui->fieldHeightSpinBox->value();

    kitrokopter::CalibrationBoard board(rowCount, columnCount, (float)fieldWidth, (float)fieldHeight);
    bool result = cameraSystem->startCalibration(board);
    if (!result)
        QMessageBox::critical(this, "Calibration Error", "Could not start calibration.");
}

void CalibrationDialog::takePicture()
{
    ui->takePictureLabel->setText("Taking picture...");
    auto future = QtConcurrent::run(cameraSystem, &kitrokopter::APICameraSystem::takeCalibrationPictures);
    takePicturesWatcher.setFuture(future);
}

void CalibrationDialog::takePictureDone()
{
    std::map<uint32_t, bool> status;
    try {
        status = takePicturesWatcher.future().result();
    } catch (QUnhandledException &e) {
        ui->takePictureLabel->setText("No pictures taken due to error.");
        QMessageBox::critical(this, "Take Picture Error", "There was an error in the ROS call.");
        return;
    }
    QString statusText;
    for (auto& cs : status) {
        if (cs.second)
            calibrationPictureCount[cs.first]++;
        statusText.append(QString("Camera %1: %2 (%3)<br>")
                          .arg(cs.first)
                          .arg(cs.second ? QString::fromUtf8("<span style='color: green'>\u2713</span>") : QString::fromUtf8("<span style='color: red'>\u2717</span>"))
                          .arg(calibrationPictureCount[cs.first]));
    }
    ui->takePictureLabel->setText(statusText);
}

void CalibrationDialog::calculateCalibration()
{
    auto future = QtConcurrent::run(cameraSystem, &kitrokopter::APICameraSystem::calculateCalibration);
    calculationWatcher.setFuture(future);
    ui->calculateCalibrationLabel->setText("Calculating calibration.\nThis may take a while...");
}

void CalibrationDialog::calculateCalibrationDone()
{
    ui->calculateCalibrationLabel->setText("Calibration calculated.");
}
