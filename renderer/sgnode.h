#ifndef _SGNODE_H_
#define _SGNODE_H_

#include <list>
#include <iterator>
#include <algorithm>
//#include "quickvector.h"
#include "nodevisitor.h"
using namespace std;

//class NodeVisitor;
//class DrawableNode;
class SGNode : public list<SGNode*>
{
public:
    //typedef list<SGNode*>::iterator iterator;
    //typedef list<SGNode*>::const_iterator const_iterator;

    SGNode() {_parent=NULL; }
    // nodes relation operations
    void addChild ( SGNode* pNode ) { 
        pNode->_setParent ( this );
        _addChild ( pNode );
    }
    void removeChild ( SGNode* pNode ) {
        if ( find ( begin(), end(), pNode ) != end() ) {
            pNode->_setParent ( NULL );
            _removeChild ( pNode );
        }
    }
    void removeAllChild ()
    {
        for ( iterator pp=begin(); pp!=end(); ++pp )
            (*pp)->_setParent(NULL);
        clear();
    }
    SGNode* getParentNode () { return _parent; }
    void setParentNode (SGNode* node) {
        if ( node ) {
            _parent->_removeChild (this);
            node->addChild ( this );
        } else {
            _parent->_removeChild (this);
            _setParent ( node );
        }
    }
    //// iteration
    //bool empty () { return _children.empty(); }
    //iterator begin() { return _children.begin(); }
    //iterator end() { return _children.end(); }
    //const_iterator begin() const { return _children.begin(); }
    //const_iterator end() const { return _children.end(); }

    // other operations
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~SGNode () {}
    //public:
    //  virtual void updateRenderList ( RenderItemContainer& output ) {}
    //  virtual bool acceptTraversal ( NodeVisitor* pNodeVisitor ) { return true; }
private:
    void _removeChild ( SGNode* p ) { remove (p); }
    void _addChild ( SGNode* p ) { push_back (p); }
    // void _removeParent ( SGNode* p ) { _parent.removeChild (p); }
    void _setParent ( SGNode* p ) { _parent=p; }
private:
    SGNode* _parent;
    //list<SGNode*> _children;
};

#endif
