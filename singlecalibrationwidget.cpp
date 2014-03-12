#include "singlecalibrationwidget.hpp"
#include "ui_singlecalibrationwidget.h"

SingleCalibrationWidget::SingleCalibrationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleCalibrationWidget)
{
    ui->setupUi(this);
}

SingleCalibrationWidget::~SingleCalibrationWidget()
{
    delete ui;
}
