#ifndef _QVIEWPORT_H_
#define _QVIEWPORT_H_

#include <QWidget>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <list>
#include "renderfunctor.h"
#include "renderflow.h"
#include "nodemgr.h"
//#include "interface.h"
using namespace std;

class QViewport : public QWidget
{
public:
    static QViewport& getInst()
    {
        static QViewport inst("viewport");
        return inst;
    }
    void add_viewport ( int id )
    {
        Viewport* p = NodeMgr::getInst().getNodePtr<Viewport>(id);
        if ( p )
            _viewports.push_back ( p );
    }
    void remove_viewport ( int id )
    {
        Viewport* p = NodeMgr::getInst().getNodePtr<Viewport>(id);
        if ( p )
            _viewports.remove ( p );
    }
    void QViewport::resizeEvent ( QResizeEvent* event )
    {
        list<Viewport*>::iterator pp, end=_viewports.end();
        for ( pp=_viewports.begin(); pp!=end; ++pp )
        {
            (*pp)->position ( _x, _y );
            (*pp)->size ( event->size().width(), event->size().height() );
        }
    }
    void dirty_all ()
    {
        list<Viewport*>::iterator pp, end=_viewports.end();
        for ( pp=_viewports.begin(); pp!=end; ++pp )
            (*pp)->dirty ( true );
    }

protected:
    //    virtual void resizeEvent ( QResizeEvent* event )
    virtual void paintEvent ( QPaintEvent* event )
    {
        QPainter painter(this);    
        list<Viewport*>::iterator pp, end=_viewports.end();
        for ( pp=_viewports.begin(); pp!=end; ++pp )
        {
            RenderOption opt;
            opt.painter = &painter;
            RenderFlow renderflow ( *(*pp), opt );
            (*pp)->update();
        }
    }

    virtual void mouseMoveEvent ( QMouseEvent * event  )
    {
        float viewportCoord[3], sceneCoord[3];
        viewportCoord[0] = event->x();
        viewportCoord[1] = event->y();
        viewportCoord[2] = 0;

        get_scenepos ( 2, viewportCoord, sceneCoord );
        qDebug ( "x=%f, y=%f, z=%f", sceneCoord[0], sceneCoord[1], sceneCoord[2] );
    }
private:
    QViewport( const char* title )
    {
        _x = _y = 0;
        setWindowTitle ( title );
    }

    list<Viewport*> _viewports;
    int _x, _y;
    //    int _viewport, _camid;
};

#endif
