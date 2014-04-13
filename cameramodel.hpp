#ifndef CAMERAMODEL_HPP
#define CAMERAMODEL_HPP

#include <QObject>
#include <QPixmap>

#include "APICameraListener.hpp"
#include "APIImageListener.hpp"

namespace kitrokopter {
class APICamera;
}

/**
 * The CameraModel adapts the API's camera listeners for Qt signal/slot usage.
 */
class CameraModel : public QObject, public kitrokopter::APICameraListener, public kitrokopter::APIImageListener {
	Q_OBJECT

	Q_PROPERTY(QPixmap image READ image)

public:
	/**
	 * Constructs a camera model for the given camera.
	 */
	explicit CameraModel(QObject *parent, kitrokopter::APICamera *camera);

	~CameraModel();

	/**
	 * Returns the camera given to the constructor.
	 */
	kitrokopter::APICamera* camera();

	void updateCameraValues(kitrokopter::APICameraUpdateEvent e);
	void imageReceived(cv::Mat);

	/**
	 * Returns the last image this camera received.
	 */
	const QPixmap& image();

	// Currently unused.
	enum CameraImageType
	{
		SourceImage,
		CorrectedImage,
	};

signals:
	/**
	 * Signals that an image was received from the camera.
	 */
	void imageChanged(const QPixmap&);

public slots:
	// Currently unused.
	void setImageType(CameraImageType type);

private:
	QPixmap m_image;
	CameraImageType m_imageType;

	kitrokopter::APICamera *m_camera;
};

#endif // CAMERAMODEL_HPP
