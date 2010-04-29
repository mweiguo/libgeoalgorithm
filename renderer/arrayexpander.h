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
#include <algorithm>
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
    virtual void apply ( TextNode& /*node*/ );
    void operator () ( ArrayNode& node )
    {
        vector<SGNode*> tmpChildren;
        copy ( node.begin(), node.end(), back_inserter(tmpChildren) );

        GroupNodeMgr::getInst().addNode ();
        GroupNode* group = GroupNodeMgr::getInst().lastNode ();
        _curparent->addChild ( group );
        _curparent = group;

        //_result.reserve ( node.rowCnt() * node.columnCnt() * 8);
        for ( int j=0; j<node.rowCnt(); j++ ) {
            float y = node.getVOffset ( j );
            for ( int k=0; k<node.columnCnt(); k++ ) {
                float x = node.getHOffset ( k );
                // generate new matrix & use this matrix
                TransformNodeMgr::getInst().addNode ();
                TransformNode* trans = TransformNodeMgr::getInst().lastNode ();
                trans->setTranslate ( x, y, 0 );
                _curparent->addChild ( trans );
                SGNode* oldparent = _curparent;
                _curparent = trans;

                for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
                    (*pp)->accept ( *this );

                _curparent = oldparent;
            }
        }

        for ( vector<SGNode*>::iterator pp=tmpChildren.begin(); pp!=tmpChildren.end(); ++pp )
            (*pp)->setParentNode ( NULL );
    }
    vector<KdTreeNode*>::iterator kdbegin() { return _kdtreenodes.begin(); }
    vector<KdTreeNode*>::iterator kdend() { return _kdtreenodes.end(); }
private:
    SGNode* _parent, * _curparent;
    vector<KdTreeNode*> _kdtreenodes;
};

inline void ArrayExpander::apply ( SGNode& node )
{
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

inline void ArrayExpander::apply ( LayerNode& node )
{
    LayerNodeMgr::getInst().addNode ( node );
    LayerNode* layer = LayerNodeMgr::getInst().lastNode();
    layer->clear();
    _curparent->addChild ( layer );

    SGNode* oldparent = _curparent;
    _curparent = layer;
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    _curparent = oldparent;
}

inline void ArrayExpander::apply ( Rectanglef& node )
{
    RectanglefMgr::getInst().addNode ( node );
    Rectanglef* rc = RectanglefMgr::getInst().lastNode ();
    rc->clear();
    _curparent->addChild ( rc );

    SGNode* oldparent = _curparent;
    _curparent = rc;
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    _curparent = oldparent;
}

inline void ArrayExpander::apply ( TransformNode& node )
{
    TransformNodeMgr::getInst().addNode ( node );
    TransformNode* trans = TransformNodeMgr::getInst().lastNode ();
    trans->clear();
    _curparent->addChild ( trans );

    SGNode* oldparent = _curparent;
    _curparent = trans;
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    _curparent = oldparent;
}

inline void ArrayExpander::apply ( ArrayNode& node )
{
    ArrayExpander expander( node.getParentNode() );
    expander( node );
}

inline void ArrayExpander::apply ( LODNode& node )
{
    LODNodeMgr::getInst().addNode ( node );
    LODNode* lod = LODNodeMgr::getInst().lastNode ();
    lod->clear();
    _curparent->addChild ( lod );

    SGNode* oldparent = _curparent;
    _curparent = lod;
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    _curparent = oldparent;
}

inline void ArrayExpander::apply ( PickableGroup& node )
{
    PickableGroupMgr::getInst().addNode ( node );
    PickableGroup* pick = PickableGroupMgr::getInst().lastNode ();
    pick->clear();
    _curparent->addChild ( pick );

    SGNode* oldparent = _curparent;
    _curparent = pick;
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    _curparent = oldparent;
}

inline void ArrayExpander::apply ( KdTreeNode& node )
{
    KdTreeNodeMgr::getInst().addNode ( node );
    KdTreeNode* kdtreenode = KdTreeNodeMgr::getInst().lastNode();
    kdtreenode->clear();
    _curparent->addChild ( kdtreenode );
    _kdtreenodes.push_back ( kdtreenode );

    SGNode* oldparent = _curparent;
    _curparent = kdtreenode;
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    _curparent = oldparent;
}

inline void ArrayExpander::apply ( TextNode& node )
{
    TextNodeMgr::getInst().addNode ( node );
    TextNode* textnode = TextNodeMgr::getInst().lastNode ();
    textnode->clear();
    _curparent->addChild ( textnode );

    SGNode* oldparent = _curparent;
    _curparent = textnode;
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    _curparent = oldparent;
}

#endif
