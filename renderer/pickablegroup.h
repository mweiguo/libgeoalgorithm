#ifndef _PICKABLE_GROUP_H_
#define _PICKABLE_GROUP_H_

#include "groupnode.h"
#include "nodemgr.h"

class PickableGroup : public GroupNode
{
public:
    PickableGroup( const string& name="" ) : GroupNode(name) {}
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~PickableGroup () {}
};

//typedef NodeMgr<PickableGroup>  PickableGroupMgr;

#endif
