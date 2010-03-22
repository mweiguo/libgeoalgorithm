#ifndef _SGNODE_H_
#define _SGNODE_H_

#include <list>
#include <iterator>
#include "quickvector.h"

using namespace std;

class NodeVisitor;
class DrawableNode;
class SGNode
{
public:
  typedef list<SGNode*>::iterator Iterator;
  typedef quickvector<DrawableNode*> RenderItemContainer;
public:
	SGNode() {_parent=NULL; }
  void addChild ( SGNode* pNode ) { pNode->_parent = this; _children.push_back ( pNode ); }
  SGNode* getParentNode () { return _parent; }
  Iterator begin() { return _children.begin(); }
  Iterator end() { return _children.end(); }
public:
  virtual void updateRenderList ( RenderItemContainer& output ) {}
  virtual bool acceptTraversal ( NodeVisitor* pNodeVisitor ) { return true; }
private:
  SGNode* _parent;
  list<SGNode*> _children;
};

#endif
