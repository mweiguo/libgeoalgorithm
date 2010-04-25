#ifndef _SWITCH_NODE_H_
#define _SWITCH_NODE_H_

#include "sgnode.h"
#include "nodemgr.h"

class NodeVisitor;
class SwitchNode : public virtual SGNode
{
public:
    SwitchNode () {_isVisible = true;}
    bool isVisible() { return _isVisible; }
    void setVisible(bool isVisible) { _isVisible = isVisible; }
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~SwitchNode () {}
private:
    bool _isVisible;
};

typedef NodeMgr<SwitchNode>     SwitchNodeMgr;

#endif
