#include "globalcalibrationwidget.hpp"
#include "ui_globalcalibrationwidget.h"

GlobalCalibrationWidget::GlobalCalibrationWidget(QWidget *parent, QList<CameraModel*> cameras) :
    QWidget(parent),
    ui(new Ui::GlobalCalibrationWidget),
    cameras(cameras)
{
    ui->setupUi(this);

    connect(ui->takePictureButton, SLOT(click()), this, SLOT(calibrate()));

    int size = cameras.size();
    if (size > 4) size = 4;
    switch (size) {
    case 4:
        connect(cameras[3], SIGNAL(imageChanged(QPixmap)), this, SLOT(updateImage4(QPixmap)));
    case 3:
        connect(cameras[2], SIGNAL(imageChanged(QPixmap)), this, SLOT(updateImage3(QPixmap)));
    case 2:
        connect(cameras[1], SIGNAL(imageChanged(QPixmap)), this, SLOT(updateImage2(QPixmap)));
    case 1:
        connect(cameras[0], SIGNAL(imageChanged(QPixmap)), this, SLOT(updateImage1(QPixmap)));
    }

}

GlobalCalibrationWidget::~GlobalCalibrationWidget()
{
    delete ui;
}

void GlobalCalibrationWidget::calibrate()
{
    // TODO: Do API call.
}

void GlobalCalibrationWidget::updateImage(QLabel *label, const QPixmap &img)
{
    label->setPixmap(img);
}

void GlobalCalibrationWidget::updateImage1(const QPixmap &img)
{
    updateImage(ui->image1, img);
}

void GlobalCalibrationWidget::updateImage2(const QPixmap &img)
{
    updateImage(ui->image2, img);
}

void GlobalCalibrationWidget::updateImage3(const QPixmap &img)
{
    updateImage(ui->image3, img);
}

void GlobalCalibrationWidget::updateImage4(const QPixmap &img)
{
    updateImage(ui->image4, img);
}
