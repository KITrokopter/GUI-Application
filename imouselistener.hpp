#ifndef IMOUSELISTENER_HPP
#define IMOUSELISTENER_HPP

class IMouseListener {
public:
	virtual void mouseDragged(int deltaX, int deltaY) = 0;
	virtual void zoom(int delta) = 0;
};

#endif // IMOUSELISTENER_HPP
