#ifndef _NODEVISITOR_NODE_H_
#define _NODEVISITOR_NODE_H_


class SGNode;

template < class T >
class Rectangle;
typedef Rectangle<float> Rectanglef;
class TransformNode;
class ArrayNode;
class LODNode;
class LayerNode;
class PickableGroup;

class NodeVisitor 
{
public:
    NodeVisitor(){}
    virtual void apply ( const SGNode& /*node*/ ) {}
    virtual void apply ( const LayerNode& /*node*/ ) {}
    virtual void apply ( const Rectanglef& /*node*/ ) {}
    virtual void apply ( const TransformNode& /*node*/ ) {}
    virtual void apply ( const ArrayNode& /*node*/ ) {}
    virtual void apply ( const LODNode& /*node*/ ) {}
    virtual void apply ( SGNode& /*node*/ ) {}
    virtual void apply ( LayerNode& /*node*/ ) {}
    virtual void apply ( Rectanglef& /*node*/ ) {}
    virtual void apply ( TransformNode& /*node*/ ) {}
    virtual void apply ( ArrayNode& /*node*/ ) {}
    virtual void apply ( LODNode& /*node*/ ) {}
    virtual void apply ( PickableGroup& /*node*/ ) {}
};


//
//#include "quickvector.h"
//
//using namespace std;
//
//template <class T>
//class Rect
//{
//public:
//      Rect( T x, T y, T w, T h ) : _x(x), _y(y), _w(w), _h(h) {}
//      T left()   { return _x; }
//      T right()  { return _x+_w; }
//      T top()    { return _y; }
//      T bottom() { return _y + _w; }
//      T width()  { return _w; }
//      T height() { return _h; }
//      template <class T1>
//      bool contain ( T1 x, T1 y ) {   return ( x>_x && x<_x+_w && y>_y && y<_y+_h ); }
//private:
//      T _x, _y, _w, _h;
//};
//
//class DrawableNode;
//class SGNode;
//class NodeVisitor 
//{
//protected:
//  NodeVisitor();
//public:
//  typedef quickvector<DrawableNode*>::iterator iterator;
//  static NodeVisitor& getInst();
//  void traverse ( SGNode* pNode );
//  int currentLevel () { return _currDispLevel; }
//  void genRenderList ( SGNode* pNode );
//
//  iterator begin() { return _renderList.begin(); }
//  iterator end() { return _renderList.end(); }
//
//  Rect<int> ClipRect() { return Rect<int>(_x, _y, _width, _height); };
//private:
//  int _currDispLevel;
//  int _x, _y, _width, _height;
//  //list<DrawableNode*>* _renderList;
//  quickvector<DrawableNode*> _renderList;
//};
//
//
//

#endif
