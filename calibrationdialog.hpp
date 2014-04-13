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

/**
 * The calibration dialog helps with camera calibration.
 *
 * It consists of a live video stream of one or all cameras (selected via tabs)
 * and a control panel for performing the calibration.
 *
 * @see SingleCalibrationWidget
 * @see GlobalCalibrationWidget
 */
class CalibrationDialog : public QDialog {
	Q_OBJECT

public:
	/**
	 * Creates a calibration dialog for the given camera system.
	 */
	explicit CalibrationDialog(QWidget *parent, kitrokopter::APICameraSystem *camsys);
	~CalibrationDialog();

public slots:
	/**
	 * Creates the video stream tabs.
	 *
	 * This is separated from the constructor as cameras can be added at
	 * runtime.
	 */
	void setupTabs();

private slots:
	void tabChanged(int);

	void startCalibration();
	void takePicture();
	void takePictureDone();
	void calculateCalibration();
	void calculateCalibrationDone();

private:
	void activateCamera(int cam, bool active);

	int prevTab = -1;

	Ui::CalibrationDialog *ui;
	kitrokopter::APICameraSystem *cameraSystem;
	QList<CameraModel*> cameraModels;

	QList<QWidget*> tabPages;

	QMap<uint32_t, unsigned int> calibrationPictureCount;

	// Watches the takePicture call
	QFutureWatcher<std::map<uint32_t, bool> > takePicturesWatcher;
	// Watches the calibration calculation.
	QFutureWatcher<void> calculationWatcher;
};

#endif // CALIBRATIONDIALOG_HPP
