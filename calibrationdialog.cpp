#include "calibrationdialog.hpp"
#include "ui_calibrationdialog.h"

#include "singlecalibrationwidget.hpp"

CalibrationDialog::CalibrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrationDialog)
{
    ui->setupUi(this);

    SingleCalibrationWidget *widget = new SingleCalibrationWidget(this);
    ui->tabWidget->addTab(widget, "Camera 1");
}

CalibrationDialog::~CalibrationDialog()
{
    delete ui;
}
