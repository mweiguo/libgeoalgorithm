#ifndef _MESHNODE_H_
#define _MESHNODE_H_

#include "nodemgr.h"

class MeshNode : public SGNode
{
public:
    MeshNode() {}
};

typedef NodeMgr<MeshNode>      MeshNodeMgr;
#endif
