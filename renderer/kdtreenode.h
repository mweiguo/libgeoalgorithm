#ifndef _KDTREE_NODE_H_
#define _KDTREE_NODE_H_

#include "kdtree.h"
#include "nodemgr.h"

template < class T>
class KdTreeNodeT : public GroupNode
{
public:
    KdTreeNodeT () {}
    KdTreeNodeT ( const KdTreeNodeT& rhs ) : GroupNode (rhs)
    {
	_kdtree = rhs._kdtree;
    }
    template<class Output >
    bool intersect ( const BBox& box, Output out )
    {
        return _kdtree.intersect ( box, out );
    }
    void buildKdTree ()
    {
        _kdtree.reset ();
        RenderNodeCollector< back_insert_iterator<KdTree<T> > > collector( back_inserter(_kdtree) );
        collector ( *this );
        BuildSpatialObjectMgr build ( _kdtree );
    }
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~KdTreeNodeT () {}
private:
    KdTree<T> _kdtree;
};

typedef KdTreeNodeT<DrawableNode*> KdTreeNode;
//typedef NodeMgr<KdTreeNode>        KdTreeNodeMgr;

#endif // _KDTREE_NODE_H_
