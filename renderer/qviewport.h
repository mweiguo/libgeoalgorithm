#ifndef _QVIEWPORT_H_
#define _QVIEWPORT_H_

#include <QWidget>

class QViewport : public QWidget
{
public:
    QViewport( const char* title );
protected:
    virtual void resizeEvent ( QResizeEvent* event );
    virtual void paintEvent ( QPaintEvent* event );
private:
    int _viewport, _camid;
    int _x, _y;
};

#endif
