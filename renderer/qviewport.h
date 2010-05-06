#ifndef _QVIEWPORT_H_
#define _QVIEWPORT_H_

#include <QWidget>
#include <QResizeEvent>
#include <QPaintEvent>
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
	}
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
