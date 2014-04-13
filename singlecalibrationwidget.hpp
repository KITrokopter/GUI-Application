#ifndef SINGLECALIBRATIONWIDGET_HPP
#define SINGLECALIBRATIONWIDGET_HPP

#include <QWidget>
#include <QPixmap>

namespace Ui {
class SingleCalibrationWidget;
}

class CameraModel;

/**
 * Shows live video for a single camera.
 */
class SingleCalibrationWidget : public QWidget {
	Q_OBJECT

public:
	SingleCalibrationWidget(QWidget *parent, CameraModel *model);
	~SingleCalibrationWidget();

private:
	Ui::SingleCalibrationWidget *ui;

	CameraModel *model;
};

#endif // SINGLECALIBRATIONWIDGET_HPP
