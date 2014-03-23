#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "quadcoptermodel.hpp"
#include "quadcopterdebugdialog.hpp"
#include "quadcoptertrackedfilter.hpp"

#include "calibrationdialog.hpp"

namespace Ui {
class MainWindow;
}

namespace kitrokopter {
class API;
}

class Gamepad;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent, kitrokopter::API *api);
    ~MainWindow();

public slots:
    // Quadcopter dialogs
    void openQuadcopterDebugDialog();
    void openQuadcopterDetailDialog(const QModelIndex &index);

    // Camera calibration dialogs
    void openCalibrationDialog();

    // Gamepad debugging
    void openGamepadDebugDialog();

    // About dialog
    void openAboutDialog();

private:
    void initGamepad();

    Ui::MainWindow *ui;

    kitrokopter::API *api;

    // Gamepad input
    Gamepad *gamepad;

    // Quadcopter handling
    QuadcopterModel *quadcopterModel;
    QuadcopterDebugDialog *quadcopterDebugDialog;
    QuadcopterTrackedFilter *trackedFilter, *untrackedFilter;

    // Calibration
    CalibrationDialog *calibrationDialog;

};

#endif // MAINWINDOW_HPP
