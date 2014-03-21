#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "quadcoptermodel.hpp"
#include "quadcopterdebugdialog.hpp"
#include "quadcoptertrackedfilter.hpp"

#include "calibrationdialog.hpp"

#include "QIrrlichtWidget.hpp"
#include "gui3d.hpp"

namespace Ui {
class MainWindow;
}

class Gamepad;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void initializeIrrlicht();
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
