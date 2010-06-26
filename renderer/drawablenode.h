#ifndef _DRAWABLE_NODE_H_
#define _DRAWABLE_NODE_H_

#include "sgnode.h"
#include "bbox.h"

class DrawableNode : public SGNode
{
    //public:
    //  virtual bool acceptTraversal ( NodeVisitor* pNodeVisitor );
    //  virtual void updateRenderList ( RenderItemContainer& output );
    //  virtual void render (QPainter& painter) = 0;
public:
    DrawableNode();
    DrawableNode( const DrawableNode& rhs );
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~DrawableNode () {}

    //void setColor ( unsigned int color );
    //unsigned int getColor ();
    //virtual bool getLayerColor ( unsigned int& color );
protected:
    bool _bRender;
    //int _color;
};

#endif
