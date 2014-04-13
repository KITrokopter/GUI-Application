#ifndef QIRRLICHTWIDGET_H
#define QIRRLICHTWIDGET_H

#include <QtCore/QDebug>
#include <QWidget>
#include <QtGui/QShowEvent>
#include <QtGui/QPaintEngine>
#include <QtGui/QResizeEvent>
#include <QtGui/QPaintEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>

#include <irrlicht/irrlicht.h>

#include "imouselistener.hpp"

#if linux
#include <X11/Xlib.h>
#include <QGuiApplication>
#include <xcb/xcb.h>
#endif

/**
 * Irrlicht Engine Widget.
 *
 * This class can be used to display a Irrlicht 3D Engine powered scene in your
 * Qt application.
 *
 * @author jcfalcone (http://irrlicht.sourceforge.net/forum/viewtopic.php?f=1&t=48694)
 * @author Sebastian Schmidt
 */
class QIrrlichtWidget : public QWidget {
	Q_OBJECT

private:
	irr::IrrlichtDevice * m_IrrDevice;
	irr::video::E_DRIVER_TYPE m_DriverType;
	irr::video::SColor m_ClearColor;
	bool mousePressed;
	int mouseX;
	int mouseY;
	IMouseListener *mouseListener;

#if linux
	// X11 specific code to disable autorepeat
	void setAutoRepeatKeys(bool mode);

#endif

protected:
	virtual QPaintEngine* paintEngine() const;
	virtual void resizeEvent(QResizeEvent *event);
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

#if linux
	virtual void focusInEvent(QFocusEvent *event);
	virtual void focusOutEvent(QFocusEvent *event);

#endif

public:
	/** Constructor for the Widget. At least you have to specify the
	 * parent. Per default OpenGL is used
	 *    for the rendering.
	 */
	QIrrlichtWidget(QWidget *parent, irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL);
	virtual ~QIrrlichtWidget();

	/** Retrieve the Irrlicht Device.
	 *    @return The Irrlicht Device used in this Widget
	 */
	irr::IrrlichtDevice* getIrrlichtDevice();

	/** Retrieve the Scene Manager
	 *    @return The Scene Manager used in this Widget
	 */
	irr::scene::ISceneManager* getSceneManager();

	/** Sets the Color used to clear the screen (Background color).
	 * Default is a dark gray (0.2 0.2 0.2).
	 *    @param color Color (RGB)
	 */
	void setClearColor(const irr::video::SColorf &color);

	/** Set the aspect ratio of the active camera. Per default this is
	 * set to window width / window height every time the widget is resized.
	 *    @param aspect Aspect Ratio to set
	 */
	void setAspectRatio(irr::f32 aspect = -1.0f);

	/** Initializes the Irrlicht subsystem. You have to call this after
	 * the widget has been created.
	 */
	void initialize();

	void setMouseListener(IMouseListener *listener);

signals:
	/** Is emitted whenever the user presses a mouse button. */
	void mousePress(QMouseEvent *event);

	/** Is emitted whenever the user releases a mouse button. */
	void mouseRelease(QMouseEvent *event);

	/** Is emitted whenever the user moves the mouse. Mouse Tracking is
	 * active per default, call setMouseTracking(bool) to disable this. */
	void mouseMove(QMouseEvent *event);

	/**Is emitted whenever the user pressed a Key. */
	void keyPress(QKeyEvent *event);

	/** Is emitted whenever the user releases a Key. */
	void keyRelease(QKeyEvent *event);
};

#endif // QIRRLICHTWIDGET_H
