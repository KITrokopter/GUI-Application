#ifndef CALIBRATIONDIALOG_HPP
#define CALIBRATIONDIALOG_HPP

#include <QDialog>

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

private:
    void setupTabs();

    Ui::CalibrationDialog *ui;
    kitrokopter::APICameraSystem *cameraSystem;
    QList<CameraModel*> cameraModels;
};

#endif // CALIBRATIONDIALOG_HPP
