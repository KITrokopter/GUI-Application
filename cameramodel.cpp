#include "cameramodel.hpp"

#include "APICamera.hpp"

#include <QMessageBox>
#include <QDebug>

CameraModel::CameraModel(QObject *parent, kitrokopter::APICamera *camera) :
    QObject(parent),
    m_camera(camera)
{
    /*
    bool result = m_image.load("C:/Source/KITrokopter/GUI-Application/image.jpg");
    if (!result)
        QMessageBox::critical(0, QString("Error"), QString("Image loading failed"));
    */
    camera->addCameraListener(this);
    camera->addImageListener(this);
}

kitrokopter::APICamera* CameraModel::camera()
{
    return m_camera;
}

void CameraModel::updateCameraValues(kitrokopter::APICameraUpdateEvent e)
{
    // TODO - is there anything to update here?
}

void CameraModel::imageReceived(cv::Mat image)
{
    m_image = QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888).rgbSwapped());
    qDebug() << "New image: " << image.cols << "x" << image.rows;
    qDebug() << "Image data: " << image.data[42];
    emit imageChanged(m_image);
}

const QPixmap& CameraModel::image()
{
    return m_image;
}

void CameraModel::setImageType(CameraImageType type)
{
    m_imageType = type;
}
