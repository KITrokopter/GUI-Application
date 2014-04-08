#include "guiobject.hpp"

#include <cmath>

#include <qdebug.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

GUIObject::GUIObject(ISceneNode *parent, std::vector<double> positionVector, std::vector<double> rotationMatrix, ISceneManager *sceneManager)
{
    qDebug() << "Constructing GUIObject";

    rotationFreeNode = sceneManager->addEmptySceneNode(parent);

    if (rotationFreeNode == 0) {
        qDebug() << "Could not create rotation free scene node";
    }

    node = sceneManager->addEmptySceneNode(rotationFreeNode);

    if (node == 0) {
        qDebug() << "Could not create scene node";
    }

    setRotationMatrix(rotationMatrix);
    setPositionVector(positionVector);

    qDebug() << "Constructed GUIObject";
}

GUIObject::GUIObject(ISceneNode *parent, vector3df positionVector, ISceneManager *sceneManager)
{
    qDebug() << "Constructing GUIObject";

    rotationFreeNode = sceneManager->addEmptySceneNode(parent);

    if (rotationFreeNode == 0) {
        qDebug() << "Could not create rotation free scene node";
    }

    node = sceneManager->addEmptySceneNode(rotationFreeNode);

    if (node == 0) {
        qDebug() << "Could not create scene node";
    }

    setPositionVector(positionVector);

    qDebug() << "Constructed GUIObject";
}

GUIObject::~GUIObject()
{
    // Node should not be dropped
}

/**
 * Calculates the euler angles from the rotation matrix and applies them to the node.
 *
 * @see https://en.wikipedia.org/wiki/Rotation_formalisms_in_three_dimensions#Conversion_formulae_between_formalisms
 * @param rotationMatrix The 3x3 rotation matrix.
 */
void GUIObject::setRotationMatrix(std::vector<double> rotationMatrix)
{
    node->setRotation(vector3df(atan2(rotationMatrix[6], rotationMatrix[7]),
                                acos(rotationMatrix[8]),
                                -atan2(rotationMatrix[2], rotationMatrix[5])));
}

void GUIObject::setEulerRotation(vector3df eulerAngles)
{
    node->setRotation(eulerAngles);
}

void GUIObject::setEulerRotation(std::vector<double> eulerAngles)
{
    setEulerRotation(vector3df(eulerAngles[0], eulerAngles[1], eulerAngles[2]));
}

void GUIObject::setEulerRotation(kitrokopter::Vector eulerAngles)
{
    vector3df toPass(3);
    toPass.X = eulerAngles.getX();
    toPass.Y = eulerAngles.getY();
    toPass.Z = eulerAngles.getZ();
    setEulerRotation(toPass);
}

void GUIObject::setPositionVector(vector3df positionVector)
{
    rotationFreeNode->setPosition(positionVector);
}

void GUIObject::setPositionVector(std::vector<double> positionVector)
{
    if (positionVector.size() != 3) {
        qDebug() << "Error: Vector size is " << positionVector.size() << " but should be 3!";
    }
    
    setPositionVector(vector3df(positionVector[0], positionVector[1], positionVector[2]));
}

void GUIObject::setPositionVector(kitrokopter::Vector positionVector)
{
    vector3df toPass;
    toPass.X = positionVector.getX();
    toPass.Y = positionVector.getY();
    toPass.Z = positionVector.getZ();
    setPositionVector(toPass);
}

ISceneNode* GUIObject::getSceneNode()
{
    return node;
}

ISceneNode* GUIObject::getRotationFreeSceneNode()
{
    return rotationFreeNode;
}

vector3df GUIObject::getPositionVector()
{
    return rotationFreeNode->getPosition();
}

void GUIObject::addShadowVolumeSceneNode(IShadowVolumeSceneNode *shadowVolumeSceneNode)
{
    shadowVolumes.push_back(shadowVolumeSceneNode);
}

void GUIObject::updateShadowVolumes()
{
    for (auto shadowVolume : shadowVolumes) {
        shadowVolume->updateShadowVolumes();
    }
}
