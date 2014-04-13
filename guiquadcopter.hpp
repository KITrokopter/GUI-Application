#ifndef GUIQUADCOPTER_HPP
#define GUIQUADCOPTER_HPP

#include "guiobject.hpp"

/**
 * Displays a quadcopter in the 3D view.
 *
 * @author Sebastian Schmidt
 */
class GUIQuadcopter : public GUIObject {
public:
	GUIQuadcopter(ISceneNode *parent, std::vector<double> positionVector, std::vector<double> rotationMatrix,
	              ISceneManager *sceneManager);
	GUIQuadcopter(ISceneNode *parent, vector3df positionVector, ISceneManager *sceneManager);

protected:
	void createMesh(ISceneManager *sceneManager);
};

#endif // GUIQUADCOPTER_HPP
