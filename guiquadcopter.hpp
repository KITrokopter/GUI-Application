#ifndef GUIQUADCOPTER_HPP
#define GUIQUADCOPTER_HPP

#include "guiobject.hpp"

class GUIQuadcopter : public GUIObject
{
public:
    GUIQuadcopter(const char* meshPath, std::vector<double> positionVector, std::vector<double> rotationMatrix, ISceneManager *sceneManager);
};

#endif // GUIQUADCOPTER_HPP
