#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include <bbox.h>

template < class T >
class Rectangle
{
public:
    Rectangle ( T x=0, T y=0, T w=0, T h=0 ) { setRect(x,y,w,h); }
    Rectangle ( const Rectangle& rhs )
    { 
        setRect ( rhs._x, rhs._y, rhs._w, rhs._h );
    }
    void setRect ( T x, T y, T w, T h ) {
        _x = x;
        _y = y;
        _w = w;
        _h = h;
    }
    inline T x() const { return _x; }
    inline T y() const { return _y; }
    inline T w() const { return _w; }
    inline T h() const { return _h; }
    inline void w( T v ) { _w = v; }
    inline void h( T v ) { _h = v; }
    inline vec2<T> lb() const { return vec2<T>(_x, _y); }
    inline vec2<T> rt() const { return vec2<T>(_x+_w, _y+_h); }
    inline void dimention( T w, T h ) { _w=w; _h=h; }
    inline vec2<T> dimention() const { return vec2<T>(_w, _h); }
    ~Rectangle () {}
    BBox boundingbox () {
        BBox bb;
        bb.init ( vec3f(_x, _y, 0) );
        bb.expandby ( vec3f(_x+_w, _y+_h, 0) );
        return bb;
    }
    void setUserData ( void* data ) { _userData = data; }
    void* getUserData () { return _userData; }
private:
    T _x, _y, _w, _h;
    void* _userData;
};

typedef Rectangle<float>  Rectanglef;
typedef Rectangle<double> Rectangled;
typedef Rectangle<int>    Rectanglei;
typedef Rectangle<short>  Rectangles;


#endif
