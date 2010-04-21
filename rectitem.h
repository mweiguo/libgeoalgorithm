#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "drawablenode.h"
#include "vec2.h"

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
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
private:
    T _x, _y, _w, _h;
};

typedef Rectangle<double>  Rectangled;
typedef Rectangle<float>   Rectanglef;
typedef Rectangle<int>     Rectanglei;
typedef Rectangle<short>   Rectangles;
//class AGEF_EXPORT ARectangle : public DrawableNode
//{
//public:
//  virtual bool acceptTraversal ( NodeVisitor* pNodeVisitor );
//  virtual void render (QPainter& painter);
//public:
//  ARectangle ( float x=0, float y=0, float w=0, float h=0 ) : _x(x), _y(y), _w(w), _h(h) {
//    getBBox().init ( vec3f(x, y, 0) );
//    getBBox().expandby ( vec3f(x+w, y+h, 0) );
//  }
//  void setRect ( float x, float y, float w, float h );
//private:
//  float _x, _y, _w, _h;
//};

#endif
