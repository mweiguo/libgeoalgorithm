#ifndef _VOLUMEPICKER_H_
#define _VOLUMEPICKER_H_

#include "nodevisitor.h"
#include "kdtreenode.h"

template <class Output>
class VolumePicker : public NodeVisitor
{
public:
    VolumePicker ( const BBox& box, int camid/*this is for lod filter*/, Output output ) : _bbox(box), _output(output), _camid(camid) {}
    virtual void apply ( SGNode& node );
    virtual void apply ( LayerNode& node );
    virtual void apply ( Rectanglef& node );
    virtual void apply ( TransformNode& node );
    virtual void apply ( ArrayNode& node );
    virtual void apply ( LODNode& node );
    virtual void apply ( PickableGroup& node );
    virtual void apply ( KdTreeNode& node );
    void operator () ( SGNode& node ) { node.accept ( *this ); }
private:
    BBox _bbox;
    Output _output;
    int _camid;
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
    CameraMgr& cameramgr = CameraMgr::getInst();
    CameraMgr::iterator pp = cameramgr.find ( _camid );
    if ( pp == cameramgr.end() )
        return;

    CameraOrtho* cam = pp->second;
    SGNode* sgnode = node.selectPresentation ( cam->mvmatrix().sx() );
    if ( sgnode )
    {
        for ( SGNode::iterator pp=sgnode->begin(); pp!=sgnode->end(); ++pp )
            (*pp)->accept ( *this );
    }
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
