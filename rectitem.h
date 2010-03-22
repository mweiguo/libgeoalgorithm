#ifndef __RECT_H__
#define __RECT_H__

#include "drawablenode.h"

class ARectItem : public DrawableNode
{
public:
  virtual bool acceptTraversal ( NodeVisitor* pNodeVisitor );
  virtual void render (QPainter& painter);
public:
  ARectItem ( float x=0, float y=0, float w=0, float h=0 ) : _x(x), _y(y), _w(w), _h(h) {
    getBBox().init ( vec3f(x, y, 0) );
    getBBox().expandby ( vec3f(x+w, y+h, 0) );
  }
  void setRect ( float x, float y, float w, float h );
private:
  float _x, _y, _w, _h;
};

void ARectItem::setRect ( float x, float y, float w, float h )
{
  _x = x;
  _y = y;
  _w = w;
  _h = h;
  getBBox().init ( vec3f(x, y, 0) );
  getBBox().expandby ( vec3f(x+w, y+h, 0) );
}

void ARectItem::render (QPainter& painter)
{
  // painter.drawRect ( _x, _y, _w, _h );
}

bool ARectItem::acceptTraversal ( NodeVisitor* pNodeVisitor )
{
  // Rect<int> rc = pNodeVisitor->ClipRect();
  // return (rc.contain (_x, _y) && rc.contain (_x+_w, _y+_h));
  return true;
  //pNodeVisitor->cull ( Rect<int>(_x, _y, _w, _h) );
  //left() < pNodeVisitor->right() && left() > pNodeVisitor->left();
  //right() < pNodeVisitor->right() && right() > pNodeVisitor->left();
  //top() < pNodeVisitor->top() && top() > pNodeVisitor->bottom();
  //bottom() < pNodeVisitor->top() && bottom() > pNodeVisitor->bottom();
  //return true;
}

#endif
