#include "qviewport.h"

#include <QResizeEvent>

#include "interface.h"

QViewport::QViewport( const char* title )
{
    _x = _y = 0;
    _viewport = viewport_create ( title );
    setWindowTitle ( title );
}

void QViewport::resizeEvent ( QResizeEvent* event )
{
    viewport_geometry ( _viewport, _x, _y, event->size().width(), event->size().height() );
}
