#ifndef GLOBALCALIBRATIONWIDGET_HPP
#define GLOBALCALIBRATIONWIDGET_HPP

#include <QWidget>
#include <QList>
#include <QLabel>

#include "cameramodel.hpp"

namespace Ui {
class GlobalCalibrationWidget;
}

class GlobalCalibrationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalCalibrationWidget(QWidget *parent, QList<CameraModel*> cameras);
    ~GlobalCalibrationWidget();

private slots:
    void calibrate();

    void updateImage1(const QPixmap &img);
    void updateImage2(const QPixmap &img);
    void updateImage3(const QPixmap &img);
    void updateImage4(const QPixmap &img);
    void updateImage(QLabel *label, const QPixmap &img);

private:
    Ui::GlobalCalibrationWidget *ui;

    QList<CameraModel*> cameras;
};

#endif // GLOBALCALIBRATIONWIDGET_HPP
