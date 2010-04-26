#ifndef _VOLUMEPICKER_H_
#define _VOLUMEPICKER_H_

#include "nodevisitor.h"

template <class Output>
class VolumePicker : public NodeVisitor
{
public:
    VolumePicker ( const BBox& box, Output output ) : _bbox(box), _output(output) {}
    virtual void apply ( SGNode& /*node*/ );
    virtual void apply ( LayerNode& /*node*/ );
    virtual void apply ( Rectanglef& /*node*/ );
    virtual void apply ( TransformNode& /*node*/ );
    virtual void apply ( ArrayNode& /*node*/ );
    virtual void apply ( LODNode& /*node*/ );
    virtual void apply ( PickableGroup& /*node*/ );
    virtual void apply ( KdTreeNode& /*node*/ );
    void operator () ( GroupNode& groupnode ) { groupnode.accept ( *this ); }
private:
    Output _output;
    BBox _bbox;
};

template <class Output>
void VolumePicker<Output>::apply ( SGNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

template <class Output>
void VolumePicker<Output>::apply ( LayerNode& node )
{
    if ( node.isVisible () )
    {
        for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
            (*pp)->accept ( *this );
    }
}

template <class Output>
void VolumePicker<Output>::apply ( Rectanglef& node )
{
    if ( (node.x() >= _bbox.min().x()) && (node.x() <= _bbox.max().x()) &&
        (node.y() >= _bbox.min().y()) && (node.y() <= _bbox.max().y()) )
        *_output++ = &node;

    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

template <class Output>
void VolumePicker<Output>::apply ( TransformNode& node )
{
    if ( node.isVisible () )
    {
        for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
            (*pp)->accept ( *this );
    }
}

template <class Output>
void VolumePicker<Output>::apply ( ArrayNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

template <class Output>
void VolumePicker<Output>::apply ( LODNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

template <class Output>
void VolumePicker<Output>::apply ( PickableGroup& node )
{
    if ( node.isVisible () )
    {
        for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
            (*pp)->accept ( *this );
    }
}

template <class Output>
void VolumePicker<Output>::apply ( KdTreeNode& node )
{
    node.intersect ( _bbox, _output );
}

#endif // _VOLUMNPICKER_H_
