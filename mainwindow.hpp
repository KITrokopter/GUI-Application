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

/**
 * The main window of the KITrokopter GUI.
 */
class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	/**
	 * Constructs a main window with the given API.
	 */
	explicit MainWindow(QWidget *parent, kitrokopter::API *api);
	/**
	 * Initializes Irrlicht for the 3d view.
	 */
	void initializeIrrlicht();

	~MainWindow();

public slots:
	// Buttons
	void launch();
	void loadFormation();
	void scanForQuadcopters();
	void shutdownEverything();

	// Quadcopter dialogs
	void openQuadcopterDebugDialog();
	void openQuadcopterDetailDialog(const QModelIndex &index);

	// Setup
	void openCalibrationDialog();
	void startSystem();

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
