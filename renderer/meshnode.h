#ifndef _MESHNODE_H_
#define _MESHNODE_H_

#include "nodemgr.h"

class MeshNode : public SGNode
{
public:
    MeshNode() {}
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~MeshNode () {}
};

typedef NodeMgr<MeshNode>      MeshNodeMgr;
#endif
