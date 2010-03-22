#ifndef _LOD_NODE_H_
#define _LOD_NODE_H_

#include "sgnode.h"
#include "nodevisitor.h"

class LODNode : public virtual SGNode
{
public:
  virtual bool acceptTraversal ( NodeVisitor* nodevisitor ) { return isInLevelRange(nodevisitor->currentLevel()); }
public:
  LODNode () {_dispLowLevel=0; _dispHiLevel=255;}
  void setLevel ( short low, short hi ) { _dispLowLevel = low; _dispHiLevel = hi; }
  bool isInLevelRange ( short l ) { return (l>=_dispLowLevel && l<=_dispHiLevel); }
private:
  short _dispLowLevel, _dispHiLevel;
};

#endif
