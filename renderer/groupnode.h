#ifndef _GROUP_NODE_H_
#define _GROUP_NODE_H_

//#include "lodnode.h"
#include "switchnode.h"

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
//class NodeVisitor;
//class LayerNode, public LODNode
//{
//public:
//  virtual bool acceptTraversal ( NodeVisitor* pNodeVisitor ) { return (SwitchNode::acceptTraversal(pNodeVisitor) && LODNode::acceptTraversal(pNodeVisitor)); }
//public:
//  LayerNode () {_isLock = false; _isEnableEdit=true; }
//  void lock ( bool isLock ) { _isLock = isLock; }
//  void enableEdit ( bool isEnable ) { _isEnableEdit = isEnable; }
//private:
//  bool _isLock, _isEnableEdit;
//};

#endif

