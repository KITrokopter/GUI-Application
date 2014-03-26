#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace kitrokopter {
class API;
}

class CalibrationDialog;
class Gamepad;
class Gui3D;
class QIrrlichtWidget;
class QuadcopterDebugDialog;
class QuadcopterModel;
class QuadcopterTrackedFilter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent, kitrokopter::API *api);
    void initializeIrrlicht();
    ~MainWindow();

public slots:
    // Buttons
    void launch();
    void deleteCalibration();
    void loadFormation();
    void scanForQuadcopters();
    void shutdownEverything();

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

    // Irrlicht
    QIrrlichtWidget *irrlichtWidget;
    Gui3D *gui3d;

};

#endif // MAINWINDOW_HPP
