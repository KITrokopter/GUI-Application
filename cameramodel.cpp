#include "cameramodel.hpp"

#include <QMessageBox>

CameraModel::CameraModel(QObject *parent) :
    QObject(parent)
{
    /*
    bool result = m_image.load("C:/Source/KITrokopter/GUI-Application/image.jpg");
    if (!result)
        QMessageBox::critical(0, QString("Error"), QString("Image loading failed"));
    */
}

const QPixmap& CameraModel::image()
{
    return m_image;
}

void CameraModel::setImageType(CameraImageType type)
{
    m_imageType = type;
}
