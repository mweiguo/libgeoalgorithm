#include "switchnode.h"
#include "nodevisitor.h"

bool SwitchNode::acceptTraversal ( NodeVisitor* pNodeVisitor )
{
  return _isVisible;
}
