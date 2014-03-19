#include "calibrationdialog.hpp"
#include "ui_calibrationdialog.h"

#include "globalcalibrationwidget.hpp"
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

    QList<CameraModel*> list;
    list.append(model);
    GlobalCalibrationWidget *global = new GlobalCalibrationWidget(this, list);
    ui->tabWidget->addTab(global, "All");
}

CalibrationDialog::~CalibrationDialog()
{
    delete ui;
}
