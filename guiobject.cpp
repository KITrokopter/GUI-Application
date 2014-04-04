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

    node = sceneManager->addEmptySceneNode(parent);

    if (node == 0) {
        qDebug() << "Could not create scene node";
    } else {
        qDebug() << "Node has value " << node << ". There might be more than one cameras, so remember that it can have different values in the future";
    }

    setRotationMatrix(rotationMatrix);
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
    std::vector<double> toPass(3);
    toPass[0] = eulerAngles.getX();
    toPass[1] = eulerAngles.getY();
    toPass[2] = eulerAngles.getZ();
    setEulerRotation(toPass);
}

void GUIObject::setPositionVector(std::vector<double> positionVector)
{
    if (node == 0) {
        qDebug() << "Error: Node is 0!";
    } else {
        qDebug() << "Node is " << node << ". If this differs from what you've seen from the past, there is a memory corruption somewhere.";
    }
    
    if (positionVector.size() != 3) {
        qDebug() << "Error: Vector size is " << positionVector.size() << " but should be 3!";
    }
    
    node->setPosition(vector3df(positionVector[0], positionVector[1], positionVector[2]));
}

void GUIObject::setPositionVector(kitrokopter::Vector positionVector)
{
    std::vector<double> toPass(3);
    toPass[0] = positionVector.getX();
    toPass[1] = positionVector.getY();
    toPass[2] = positionVector.getZ();
    setPositionVector(toPass);
}

ISceneNode* GUIObject::getSceneNode()
{
    return node;
}
