#ifndef _DRAWABLE_NODE_H_
#define _DRAWABLE_NODE_H_

#include "sgnode.h"
//#include "mat3.h"
#include "bbox.h"


class DrawableNode : public SGNode
{
//public:
//  virtual bool acceptTraversal ( NodeVisitor* pNodeVisitor );
//  virtual void updateRenderList ( RenderItemContainer& output );
//  virtual void render (QPainter& painter) = 0;
public:
	DrawableNode() : _bRender(true) {}
	const BBox& getBBox () const { return _bb; }
	virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~DrawableNode () {}
protected:
	BBox _bb;
	bool _bRender;
};

//
//
  //void render ( const RenderOptions& opt );
//
//  mat3<float> getMatrix () { return _matrix; }
//  void draw (QPainter& painter);
//  const BBox& getBBox () const { return _bb; }
//  BBox& getBBox () { return _bb; }
//protected:
//  void reCalcMatrix();
//  void beginRender(QPainter& painter);
//  void endRender(QPainter& painter);
//private:
//  BBox _bb;
//  mat3f _matrix, _oldMatrix;

#endif
