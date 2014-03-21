#ifndef CAMERAMODEL_HPP
#define CAMERAMODEL_HPP

#include <QObject>
#include <QPixmap>


class CameraModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPixmap image READ image)

public:
    explicit CameraModel(QObject *parent = 0);

    const QPixmap& image();

    enum CameraImageType {
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
};

#endif // CAMERAMODEL_HPP
