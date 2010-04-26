#include "qviewport.h"

#include <QResizeEvent>
#include <QPaintEvent>

#include "interface.h"

QViewport::QViewport( const char* title )
{
    _x = _y = 0;
    _viewport = viewport_create ( title );
    _camid = camera_create ( "camera" );
    viewport_attachcamera ( _viewport, _camid );
    setWindowTitle ( title );
}

void QViewport::resizeEvent ( QResizeEvent* event )
{
    viewport_geometry ( _viewport, _x, _y, event->size().width(), event->size().height() );
}

void QViewport::paintEvent ( QPaintEvent* event )
{
    QPainter painter(this);    
    viewport_update ( _viewport, painter );
}
