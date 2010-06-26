#include "qviewport.h"

#include <QResizeEvent>
#include <QPaintEvent>

#include "interface.h"

QViewport::QViewport( const char* title )
{
    _x = _y = 0;
    setWindowTitle ( title );
}

void QViewport::add_viewport ( int id )
{
    _viewports.push_back ( id );
}

void QViewport::remove_viewport ( int id )
{
    _viewports.remove ( id );
}

void QViewport::resizeEvent ( QResizeEvent* event )
{
    viewport_geometry ( _viewport, _x, _y, event->size().width(), event->size().height() );
}

void QViewport::paintEvent ( QPaintEvent* event )
{
    QPainter painter(this);    
    list<int>::iterator pp, end=_viewports.end();
    for ( pp=_viewports.begin(); pp!=end; ++pp )
        viewport_update ( *pp, painter );
}
