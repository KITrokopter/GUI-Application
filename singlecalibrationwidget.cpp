#include "singlecalibrationwidget.hpp"
#include "ui_singlecalibrationwidget.h"

#include <QMessageBox>

#include "cameramodel.hpp"

#include "APICamera.hpp"

SingleCalibrationWidget::SingleCalibrationWidget(QWidget *parent, CameraModel *model) :
    QWidget(parent),
    ui(new Ui::SingleCalibrationWidget),
    model(model)
{
    ui->setupUi(this);

    ui->image->setPixmap(model->image());
    connect(model, SIGNAL(imageChanged(QPixmap)), ui->image, SLOT(setPixmap(QPixmap)));

    connect(ui->showSourceRadio, SIGNAL(pressed()), this, SLOT(setSourceImageType()));
    connect(ui->showCorrectedRadio, SIGNAL(pressed()), this, SLOT(setCorrectedImageType()));

    connect(ui->calibrateButton, SIGNAL(clicked()), this, SLOT(calibrate()));
    connect(ui->deleteCalibrationButton, SIGNAL(clicked()), this, SLOT(deleteCalibration()));
}

SingleCalibrationWidget::~SingleCalibrationWidget()
{
    delete ui;
}

void SingleCalibrationWidget::setSourceImageType()
{
    model->setImageType(CameraModel::SourceImage);
}

void SingleCalibrationWidget::setCorrectedImageType()
{
    model->setImageType(CameraModel::CorrectedImage);
}
