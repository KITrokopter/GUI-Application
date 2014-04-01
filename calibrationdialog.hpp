#ifndef CALIBRATIONDIALOG_HPP
#define CALIBRATIONDIALOG_HPP

#include <QDialog>
#include <QFutureWatcher>

namespace Ui {
class CalibrationDialog;
}

class CameraModel;

namespace kitrokopter {
class APICameraSystem;
}

class CalibrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalibrationDialog(QWidget *parent, kitrokopter::APICameraSystem *camsys);
    ~CalibrationDialog();

private slots:
    void startCalibration();
    void takePicture();
    void calculateCalibration();
    void calculateCalibrationDone();

private:
    void setupTabs();

    Ui::CalibrationDialog *ui;
    kitrokopter::APICameraSystem *cameraSystem;
    QList<CameraModel*> cameraModels;

    // Watches the calibration calculation.
    QFutureWatcher<void> calculationWatcher;
};

#endif // CALIBRATIONDIALOG_HPP
