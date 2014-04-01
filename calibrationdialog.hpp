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
    void tabChanged(int);

    void startCalibration();
    void takePicture();
    void calculateCalibration();
    void calculateCalibrationDone();

private:
    void setupTabs();
    void activateCamera(int cam, bool active);

    int prevTab = -1;

    Ui::CalibrationDialog *ui;
    kitrokopter::APICameraSystem *cameraSystem;
    QList<CameraModel*> cameraModels;

    // Watches the calibration calculation.
    QFutureWatcher<void> calculationWatcher;
};

#endif // CALIBRATIONDIALOG_HPP
