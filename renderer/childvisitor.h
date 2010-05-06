#ifndef _CHILDVISITOR_H_
#define _CHILDVISITOR_H_

#include "nodevisitor.h"
#include "pickablegroup.h"
#include "kdtreenode.h"
#include "meshnode.h"

class ChildVisitor : public NodeVisitor
{
public:
    virtual void apply ( SGNode& node );
    virtual void apply ( LayerNode& node );
    virtual void apply ( Rectanglef& node );
    virtual void apply ( TransformNode& node );
    virtual void apply ( ArrayNode& node );
    virtual void apply ( LODNode& node );
    virtual void apply ( PickableGroup& node );
    virtual void apply ( KdTreeNode& node );
    virtual void apply ( MeshNode& node );
    virtual void apply ( FontNode& node );
    virtual void apply ( TextNode& node );
    virtual void apply ( GroupNode& node );
    virtual void apply ( SwitchNode& node );
};


inline void ChildVisitor::apply ( SGNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

inline void ChildVisitor::apply ( LayerNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

inline void ChildVisitor::apply ( Rectanglef& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

inline void ChildVisitor::apply ( TransformNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

inline void ChildVisitor::apply ( ArrayNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

inline void ChildVisitor::apply ( LODNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

inline void ChildVisitor::apply ( PickableGroup& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

inline void ChildVisitor::apply ( KdTreeNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

inline void ChildVisitor::apply ( MeshNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

inline void ChildVisitor::apply ( FontNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

inline void ChildVisitor::apply ( TextNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

inline void ChildVisitor::apply ( GroupNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

inline void ChildVisitor::apply ( SwitchNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

#endif // _CHILDVISITOR_H_
