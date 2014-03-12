#ifndef SINGLECALIBRATIONWIDGET_HPP
#define SINGLECALIBRATIONWIDGET_HPP

#include <QWidget>

namespace Ui {
class SingleCalibrationWidget;
}

class SingleCalibrationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleCalibrationWidget(QWidget *parent = 0);
    ~SingleCalibrationWidget();

private:
    Ui::SingleCalibrationWidget *ui;
};

#endif // SINGLECALIBRATIONWIDGET_HPP
