#ifndef GLOBALCALIBRATIONWIDGET_HPP
#define GLOBALCALIBRATIONWIDGET_HPP

#include <QWidget>
#include <QList>
#include <QLabel>

namespace Ui {
class GlobalCalibrationWidget;
}

class CameraModel;

/**
 * The global calibration widget shows up to four camera live images.
 *
 * It is intended to be used as a tab page.
 *
 * @see CalibrationDialog
 */
class GlobalCalibrationWidget : public QWidget {
	Q_OBJECT

public:
	/**
	 * Constructs a widget for the given cameras.
	 *
	 * Only the first four (or less) cameras are used.
	 */
	explicit GlobalCalibrationWidget(QWidget *parent, QList<CameraModel*> cameras);
	~GlobalCalibrationWidget();

private slots:
	void updateImage1(const QPixmap &img);
	void updateImage2(const QPixmap &img);
	void updateImage3(const QPixmap &img);
	void updateImage4(const QPixmap &img);
	void updateImage(QLabel *label, const QPixmap &img);

private:
	Ui::GlobalCalibrationWidget *ui;

	QList<CameraModel*> cameras;
};

#endif // GLOBALCALIBRATIONWIDGET_HPP
