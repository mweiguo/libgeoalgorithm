#ifndef _COORD_FLATER_H_
#define _COORD_FLATER_H_

#include "nodevisitor.h"
#include "rectitem.h"
#include "transformnode.h"
#include "arraynode.h"
#include "mat4.h"
#include "vec2.h"
#include "vec4.h"

#include <vector>
#include <string>
#include <sstream>
using namespace std;

class ArrayExpander : public NodeVisitor
{
public:
    ArrayExpander ( SGNode* parent ) : _parent(parent), _curparent(parent) { }
    virtual void apply ( SGNode& /*node*/ );
    virtual void apply ( LayerNode& /*node*/ );
    virtual void apply ( Rectanglef& /*node*/ );
    virtual void apply ( TransformNode& /*node*/ );
    virtual void apply ( ArrayNode& /*node*/ );
    virtual void apply ( LODNode& /*node*/ );
    virtual void apply ( PickableGroup& /*node*/ );
    virtual void apply ( KdTreeNode& /*node*/ );
    void operator () ( ArrayNode& node )
    {
	//_result.reserve ( node.rowCnt() * node.columnCnt() * 8);
	for ( int j=0; j<node.rowCnt(); j++ ) {
	    float y = node.getVOffset ( j );
	    for ( int k=0; k<node.columnCnt(); k++ ) {
		float x = node.getHOffset ( k );
		// generate new matrix & use this matrix
		mat4f m = mat4f::translate_matrix ( x, y, 0 ), oldmat = _curmat;
		_curmat = m * _curmat;
		for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
		    (*pp)->accept ( *this );
		_curmat = oldmat;
	    }
	}
    }
private:
    SGNode* _parent, * _curparent;
};

void ArrayExpander::apply ( SGNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

void ArrayExpander::apply ( LayerNode& node )
{
    LayerNode* layer = new LayerNode(node);
    _curparent.addChild ( layer );

    SGNode* oldparent = _curparent;
    _curparent = layer;
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    _curparent = oldparent;
}

void ArrayExpander::apply ( Rectanglef& node )
{
    Rectanglef* rc = new Rectanglef(node);
    _curparent.addChild ( rc );

    SGNode* oldparent = _curparent;
    _curparent = rc;
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    _curparent = oldparent;
}

void ArrayExpander::apply ( TransformNode& node )
{
    TransformNode* trans = new TransformNode(node);
    _curparent.addChild ( trans );

    SGNode* oldparent = _curparent;
    _curparent = trans;
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    _curparent = oldparent;
}

void ArrayExpander::apply ( ArrayNode& node )
{
    ArrayExpander expander( node->getParentNode() );
    expander( node );
}

void ArrayExpander::apply ( LODNode& node )
{
    LODNode* lod = new LODNode(node);
    _curparent.addChild ( lod );

    SGNode* oldparent = _curparent;
    _curparent = lod;
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    _curparent = oldparent;
}

void ArrayExpander::apply ( PickableGroup& node )
{
    PickableGroup* pick = new PickableGroup(node);
    _curparent.addChild ( pick );

    SGNode* oldparent = _curparent;
    _curparent = pick;
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    _curparent = oldparent;
}

void ArrayExpander::apply ( KdTreeNode& node )
{
    KdTreeNode* kdtree = new KdTreeNode(node);
    _curparent.addChild ( kdtree );

    SGNode* oldparent = _curparent;
    _curparent = kdtree;
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    _curparent = oldparent;
}
#endif
