#ifndef _LAYER_NODE_H_
#define _LAYER_NODE_H_

#include "groupnode.h"
#include "lodnode.h"

class LayerNode : public GroupNode
{
public:
    LayerNode ( const string& name="default" ) :GroupNode(name) {}
    //    LODNode* lod() { return dynamic_cast<LODNode*>(*begin()); }
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~LayerNode () {}
};

#endif
//public:
//  virtual bool acceptTraversal ( NodeVisitor* nodevisitor ) { return isInLevelRange(nodevisitor->currentLevel()); }
//isInLevelRange ( short l ) { return (l>=_dispLowLevel && l<=_dispHiLevel); }
