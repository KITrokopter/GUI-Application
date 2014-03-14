#ifndef SINGLECALIBRATIONWIDGET_HPP
#define SINGLECALIBRATIONWIDGET_HPP

#include <QWidget>
#include <QPixmap>

namespace Ui {
class SingleCalibrationWidget;
}

class CameraModel;

class SingleCalibrationWidget : public QWidget
{
    Q_OBJECT

public:
    SingleCalibrationWidget(QWidget *parent, CameraModel *model);
    ~SingleCalibrationWidget();

private slots:
    void setSourceImageType();
    void setCorrectedImageType();

    void calibrate();
    void deleteCalibration();

private:
    Ui::SingleCalibrationWidget *ui;

    CameraModel *model;
};

#endif // SINGLECALIBRATIONWIDGET_HPP
