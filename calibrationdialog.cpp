#include "calibrationdialog.hpp"
#include "ui_calibrationdialog.h"

#include "APICameraSystem.hpp"

#include "cameramodel.hpp"
#include "globalcalibrationwidget.hpp"
#include "singlecalibrationwidget.hpp"

CalibrationDialog::CalibrationDialog(QWidget *parent, kitrokopter::APICameraSystem *camsys) :
    QDialog(parent),
    ui(new Ui::CalibrationDialog),
    cameraSystem(camsys)
{
    ui->setupUi(this);
    setupTabs();
}

CalibrationDialog::~CalibrationDialog()
{
    delete ui;
}

void CalibrationDialog::setupTabs()
{
    for (int i = 0; i < cameraSystem->getCameraAmount(); ++i) {
        kitrokopter::APICamera *camera = cameraSystem->getCamera(i);
        CameraModel *model = new CameraModel(this, camera);
        cameraModels.append(model);
        SingleCalibrationWidget *widget = new SingleCalibrationWidget(this, model);
        ui->tabWidget->addTab(widget, QString("Camera &%1").arg(i));
    }

    GlobalCalibrationWidget *global = new GlobalCalibrationWidget(this, cameraModels);
    ui->tabWidget->addTab(global, "&All");
}
