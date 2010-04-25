#ifndef _QVIEWPORT_H_
#define _QVIEWPORT_H_

#include <QWidget>

class QViewport : public QWidget
{
public:
    QViewport( const char* title );
protected:
    void resizeEvent ( QResizeEvent* event );
private:
    int _viewport;
    int _x, _y;
};

#endif
