#ifndef _QVIEWPORT_H_
#define _QVIEWPORT_H_

#include <QWidget>
#include <list>
using namespace std;

class QViewport : public QWidget
{
public:
    static QViewport& getInst()
    {
	static QViewport inst("viewport");
	return inst;
    }
    void add_viewport ( int id );
    void remove_viewport ( int id );
protected:
    virtual void resizeEvent ( QResizeEvent* event );
    virtual void paintEvent ( QPaintEvent* event );
private:
    QViewport( const char* title );
    list<int> _viewports;
    int _x, _y;
//    int _viewport, _camid;
};

#endif
