#ifndef _NODELETER_H_
#define _NODELETER_H_

#include "nodevisitor.h"

class Nodeleter : public NodeVisitor
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
    void operator() ( SGNode* node )
    {
	node->accept ( *this );
    }
};

inline void Nodeleter::apply ( SGNode& node )
{
    for ( SGNode::const_iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

inline void Nodeleter::apply ( LayerNode& node )
{
    for ( SGNode::const_iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    delete &node;
}

inline void Nodeleter::apply ( PickableGroup& node )
{
    for ( SGNode::const_iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    delete &node;
}

inline void Nodeleter::apply ( Rectanglef& node )
{
    for ( SGNode::const_iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    delete &node;
}

inline void Nodeleter::apply ( TransformNode& node )
{
    for ( SGNode::const_iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    delete &node;
}

inline void Nodeleter::apply ( ArrayNode& node )
{
    for ( SGNode::const_iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    delete &node;
}

inline void Nodeleter::apply ( LODNode& node )
{
    for ( SGNode::const_iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    delete &node;
}

inline void Nodeleter::apply ( KdTreeNode& node )
{
    for ( SGNode::const_iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    delete &node;
}

inline void Nodeleter::apply ( MeshNode& node )
{
    for ( SGNode::const_iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    delete &node;
}

#endif
