#ifndef _QVIEWPORT_H_
#define _QVIEWPORT_H_

class QViewport : QWidget
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
