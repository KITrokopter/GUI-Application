#include "calibrationdialog.hpp"
#include "ui_calibrationdialog.h"

#include "singlecalibrationwidget.hpp"
#include "cameramodel.hpp"

CalibrationDialog::CalibrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrationDialog)
{
    ui->setupUi(this);

    CameraModel *model = new CameraModel(this);
    SingleCalibrationWidget *widget = new SingleCalibrationWidget(this, model);
    ui->tabWidget->addTab(widget, "Camera 1");
}

CalibrationDialog::~CalibrationDialog()
{
    delete ui;
}
