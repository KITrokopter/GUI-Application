#ifndef GUIOBJECT_HPP
#define GUIOBJECT_HPP

#include <irrlicht/irrlicht.h>
#include <vector>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class GUIObject
{
public:
    GUIObject(std::vector<double> positionVector, std::vector<double> rotationMatrix, ISceneManager *sceneManager);
    ~GUIObject();

    void setRotationMatrix(std::vector<double> rotationMatrix);
    void setPositionVector(std::vector<double> positionVector);

protected:
    ISceneNode* getSceneNode();

private:
    ISceneNode *node;
};

#endif // GUIOBJECT_HPP
