#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "drawablenode.h"
#include "vec2.h"
#include "nodemgr.h"

template < class T >
class Rectangle : public DrawableNode
{
public:
    Rectangle ( T x=0, T y=0, T w=0, T h=0 ) { setRect(x,y,w,h); }
    void setRect ( T x, T y, T w, T h ) {
        _x = x;
        _y = y;
        _w = w;
        _h = h;
        _bb.init ( vec3f(x, y, 0 ) );
        _bb.expandby ( vec3f(x+w, y+h, 0 ) );
    }
    inline T x() const { return _x; }
    inline T y() const { return _y; }
    inline T w() const { return _w; }
    inline T h() const { return _h; }
    inline void w( T v ) { _w = v; }
    inline void h( T v ) { _h = v; }
    inline vec2<T> lb() const { return vec2<T>(_x, _y); }
    inline vec2<T> rt() const { return vec2<T>(_x+_w, _y+_h); }
    inline void size( T w, T h ) { _w=w; _h=h; }
    inline vec2<T> size() const { return vec2<T>(_w, _h); }
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    ~Rectangle () {}
private:
    T _x, _y, _w, _h;
};

typedef Rectangle<double>  Rectangled;
typedef Rectangle<float>   Rectanglef;
typedef Rectangle<int>     Rectanglei;
typedef Rectangle<short>   Rectangles;

/* typedef NodeMgr<Rectangled>     RectangledMgr; */
/* typedef NodeMgr<Rectanglef>     RectanglefMgr; */
/* typedef NodeMgr<Rectanglei>     RectangleiMgr; */
/* typedef NodeMgr<Rectangles>     RectanglesMgr; */
#endif
