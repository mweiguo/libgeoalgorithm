#ifndef _LAYER_NODE_H_
#define _LAYER_NODE_H_

#include "lodnode.h"
#include "switchnode.h"

class NodeVisitor;
class LayerNode : public SwitchNode, public LODNode
{
public:
  virtual bool acceptTraversal ( NodeVisitor* pNodeVisitor ) { return (SwitchNode::acceptTraversal(pNodeVisitor) && LODNode::acceptTraversal(pNodeVisitor)); }
public:
  LayerNode () {_isLock = false; _isEnableEdit=true; }
  void lock ( bool isLock ) { _isLock = isLock; }
  void enableEdit ( bool isEnable ) { _isEnableEdit = isEnable; }
private:
  bool _isLock, _isEnableEdit;
};

#endif
