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
}

SingleCalibrationWidget::~SingleCalibrationWidget()
{
    delete ui;
}
