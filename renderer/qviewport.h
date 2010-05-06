#ifndef _QVIEWPORT_H_
#define _QVIEWPORT_H_

#include <QWidget>
#include <QResizeEvent>
#include <QPaintEvent>

#include <list>

#include "interface.h"
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
	_viewports.push_back ( id );
    }
    void remove_viewport ( int id )
    {
	_viewports.remove ( id );
    }
protected:
    //    virtual void resizeEvent ( QResizeEvent* event )
    virtual void paintEvent ( QPaintEvent* event )
    {
	QPainter painter(this);    
	list<int>::iterator pp, end=_viewports.end();
	for ( pp=_viewports.begin(); pp!=end; ++pp )
	    viewport_update ( *pp, painter );
    }

private:
    QViewport( const char* title )
    {
	_x = _y = 0;
	setWindowTitle ( title );
    }

    list<int> _viewports;
    int _x, _y;
//    int _viewport, _camid;
};

#endif
