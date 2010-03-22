#ifndef _SWITCH_NODE_H_
#define _SWITCH_NODE_H_

#include "sgnode.h"

class NodeVisitor;
class SwitchNode : public virtual SGNode
{
public:
  virtual bool acceptTraversal ( NodeVisitor* pNodeVisitor );
public:
  SwitchNode () {_isVisible = true;}
  bool isVisible() { return _isVisible; }
  void setVisible(bool isVisible) { _isVisible = isVisible; }
private:
  bool _isVisible;
};

#endif
