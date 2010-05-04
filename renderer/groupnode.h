#ifndef _GROUP_NODE_H_
#define _GROUP_NODE_H_

#include "switchnode.h"
#include "nodemgr.h"

class GroupNode : public SwitchNode
{
public:
    GroupNode( const string& name="" ) : _groupname(name) {}
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~GroupNode () {}
    void name ( const string& name ) { _groupname=name; }
    string name () { return _groupname; }
private:
    string _groupname;
};

//typedef NodeMgr<GroupNode>      GroupNodeMgr;
#endif

