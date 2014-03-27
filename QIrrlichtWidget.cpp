#include "QIrrlichtWidget.hpp"

// ####################################################################
// PRIVATE MEMBERS
// ####################################################################

#if linux
void QIrrlichtWidget::setAutoRepeatKeys( bool mode )
{
    qDebug() << "QIrrlichtWidget::setAutoRepeatKeys";

    XKeyboardControl control;
    control.auto_repeat_mode = ( mode ? 1 : 0 ); // Set mode to 1 for autorepeat, 0 to disable
    control.key = -1; // We want to change the behaviour for all keys

    QList<QScreen *> screens = QGuiApplication::screens();
    QXcbScreen *xcbscreen = static_cast<QXcbScreen *>(screens.at(0)->handle());
    Display *display = static_cast<Display *>(xcbscreen->connection()->xlib_display());

    XChangeKeyboardControl( display, KBAutoRepeatMode, &control );
}
#endif

// ####################################################################
// PROTECTED MEMBERS
// ####################################################################

QPaintEngine * QIrrlichtWidget::paintEngine() const
{
    qDebug() << "QIrrlichtWidget::paintEngine";

    return 0;
}

void QIrrlichtWidget::resizeEvent( QResizeEvent *event )
{    
    qDebug() << "QIrrlichtWidget::resizeEvent";

    if( m_IrrDevice == 0 )
        return;

    int newWidth = event->size().width();
    int newHeight = event->size().height();

    m_IrrDevice->getVideoDriver()->OnResize( irr::core::dimension2d<irr::u32>( newWidth, newHeight ));
    setAspectRatio();
}

void QIrrlichtWidget::paintEvent( QPaintEvent *event )
{
    qDebug() << "QIrrlichtWidget::paintEvent";

    if( m_IrrDevice == 0 )
        return;

    // Draw everything (Scene and GUI)
    m_IrrDevice->getVideoDriver()->beginScene( true, true, m_ClearColor );
    m_IrrDevice->getSceneManager()->drawAll();
    m_IrrDevice->getSceneManager()->getGUIEnvironment()->drawAll();
    m_IrrDevice->getVideoDriver()->endScene();
}

void QIrrlichtWidget::mousePressEvent( QMouseEvent *event )
{
    mouseX = event->x();
    mouseY = event->y();
    mousePressed = true;

    emit( mousePress( event ));
}

void QIrrlichtWidget::mouseReleaseEvent( QMouseEvent *event )
{
    mouseListener->mouseDragged(event->x() - mouseX, event->y() - mouseY);
    mouseX = event->x();
    mouseY = event->y();
    mousePressed = false;

    emit( mouseRelease( event ));
}

void QIrrlichtWidget::mouseMoveEvent( QMouseEvent *event )
{
    if (mousePressed) {
        mouseListener->mouseDragged(event->x() - mouseX, event->y() - mouseY);
        mouseX = event->x();
        mouseY = event->y();
    }

    emit( mouseMove( event ));
}

void QIrrlichtWidget::keyPressEvent( QKeyEvent * event )
{
    emit( keyPress( event ));
}

void QIrrlichtWidget::keyReleaseEvent( QKeyEvent *event )
{
    emit( keyRelease( event ));
}

void QIrrlichtWidget::wheelEvent(QWheelEvent *event)
{
    mouseListener->zoom(event->angleDelta().y());
}

#if linux
void QIrrlichtWidget::focusInEvent( QFocusEvent *event )
{
    setAutoRepeatKeys( false );
}

void QIrrlichtWidget::focusOutEvent( QFocusEvent *event )
{
    setAutoRepeatKeys( true );
}
#endif

// ####################################################################
// PUBLIC MEMBERS
// ####################################################################

QIrrlichtWidget::QIrrlichtWidget( QWidget *parent, irr::video::E_DRIVER_TYPE driverType ) : QWidget( parent )
{
    qDebug() << "QIrrlichtWidget::ctor()";

    setAttribute( Qt::WA_PaintOnScreen, true );
    setAttribute( Qt::WA_OpaquePaintEvent, true );
    setMouseTracking( true );
    setFocusPolicy( Qt::ClickFocus );
    setFocus( Qt::OtherFocusReason );

    m_IrrDevice = 0;
    m_DriverType = driverType;

    setClearColor( irr::video::SColorf( 0.2f, 0.2f, 0.2f ));

    mousePressed = false;
    mouseListener = 0;
}

QIrrlichtWidget::~QIrrlichtWidget()
{
    qDebug() << "QIrrlichtWidget::dtor()";

    if( m_IrrDevice != 0 )
        m_IrrDevice->drop();
}

irr::IrrlichtDevice * QIrrlichtWidget::getIrrlichtDevice()
{
    qDebug() << "QIrrlichtWidget::getIrrlichtDevice()";

    if( m_IrrDevice != 0 )
        return m_IrrDevice;

    throw( "Irrlicht device has not been initialized");
}

irr::scene::ISceneManager * QIrrlichtWidget::getSceneManager()
{
    qDebug() << "QIrrlichtWidget::getSceneManager";

    if( m_IrrDevice != 0 )
        return m_IrrDevice->getSceneManager();

    throw( "Irrlicht device has not been initialized" );
}

void QIrrlichtWidget::setClearColor( const irr::video::SColorf &color )
{
    m_ClearColor = color.toSColor();
}

void QIrrlichtWidget::setAspectRatio( irr::f32 aspect )
{
    qDebug() << "QIrrlichtWidget::setAspectRatio";

    if( m_IrrDevice == 0 )
        return;

    irr::f32 newAspectRatio;
    if( aspect < 0 ) // Automatic
    {
        irr::core::dimension2d<irr::u32> screenSize = m_IrrDevice->getVideoDriver()->getScreenSize();
        newAspectRatio = ( irr::f32 ) screenSize.Width / ( irr::f32 ) screenSize.Height;
    }
    else
        newAspectRatio = aspect;

    // Set Aspect for active Camera
    irr::scene::ISceneManager *mgr = getSceneManager();
    mgr->getActiveCamera()->setAspectRatio( newAspectRatio );
}

void QIrrlichtWidget::initialize()
{
    qDebug() << "QIrrlichtWidget::init";

    if( m_IrrDevice != 0 )
        return;

    // Create the Irrlicht device if this is the first time we are being shown
    irr::SIrrlichtCreationParameters createParams;
    createParams.DriverType = m_DriverType;
    createParams.WindowSize = irr::core::dimension2d<irr::u32>( size().width(), size().height() );
    createParams.EventReceiver = 0;
    createParams.Stencilbuffer = true;
    createParams.IgnoreInput = true;

    // Window ID for creating the native rendering context
    createParams.WindowId = ( void * ) winId();

    qDebug() << "   render size           = " << createParams.WindowSize.Width << " x " << createParams.WindowSize.Height;
    qDebug() << "   native window ID      = " << /*( irr::u32 )*/ createParams.WindowId;

    if(( m_IrrDevice = irr::createDeviceEx( createParams )) == 0 )
        throw( "failed to create Irrlicht device" );
}

void QIrrlichtWidget::setMouseListener(IMouseListener *listener)
{
    mouseListener = listener;
}
