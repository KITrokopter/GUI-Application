#ifndef CAMERAMODEL_HPP
#define CAMERAMODEL_HPP

#include <QObject>
#include <QPixmap>

#include "APICameraListener.hpp"
#include "APIImageListener.hpp"

namespace kitrokopter {
class APICamera;
}

class CameraModel : public QObject, public kitrokopter::APICameraListener, public kitrokopter::APIImageListener {
	Q_OBJECT

	Q_PROPERTY(QPixmap image READ image)

public:
	explicit CameraModel(QObject *parent, kitrokopter::APICamera *camera);

	~CameraModel();

	kitrokopter::APICamera* camera();

	void updateCameraValues(kitrokopter::APICameraUpdateEvent e);
	void imageReceived(cv::Mat);

	const QPixmap& image();

	enum CameraImageType
	{
		SourceImage,
		CorrectedImage,
	};

signals:
	void imageChanged(const QPixmap&);

public slots:
	void setImageType(CameraImageType type);

private:
	QPixmap m_image;
	CameraImageType m_imageType;

	kitrokopter::APICamera *m_camera;
};

#endif // CAMERAMODEL_HPP
