#ifndef _LAYER_NODE_H_
#define _LAYER_NODE_H_

#include "groupnode.h"
#include "nodemgr.h"

class LayerNode : public GroupNode
{
public:
    LayerNode ( const string& name="default" ) :GroupNode(name) {}
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~LayerNode () {}
};

typedef NodeMgr<LayerNode>      LayerNodeMgr;

#endif
