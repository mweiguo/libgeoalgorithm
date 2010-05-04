#ifndef _PARENT_VISITOR_H_
#define _PARENT_VISITOR_H_

class ParentVisitor : public NodeVisitor
{
public:
    virtual void apply ( SGNode& node );
    virtual void apply ( LayerNode& node );
    virtual void apply ( Rectanglef& node );
    virtual void apply ( TransformNode& node );
    virtual void apply ( ArrayNode& node );
    virtual void apply ( LODNode& node );
    virtual void apply ( PickableGroup& node );
    virtual void apply ( KdTreeNode& node );
    virtual void apply ( MeshNode& node );
    virtual void apply ( FontNode& node );
    virtual void apply ( TextNode& node );
};


inline void ParentVisitor::apply ( SGNode& node )
{
    SGNode* parent = node.getParentNode();
    if ( parent )
	parent->accept ( *this );
}

inline void ParentVisitor::apply ( LayerNode& node )
{
    SGNode* parent = node.getParentNode();
    if ( parent )
	parent->accept ( *this );
}

inline void ParentVisitor::apply ( Rectanglef& node )
{
    SGNode* parent = node.getParentNode();
    if ( parent )
	parent->accept ( *this );
}

inline void ParentVisitor::apply ( TransformNode& node )
{
    SGNode* parent = node.getParentNode();
    if ( parent )
	parent->accept ( *this );
}

inline void ParentVisitor::apply ( ArrayNode& node )
{
    SGNode* parent = node.getParentNode();
    if ( parent )
	parent->accept ( *this );
}

inline void ParentVisitor::apply ( LODNode& node )
{
    SGNode* parent = node.getParentNode();
    if ( parent )
	parent->accept ( *this );
}

inline void ParentVisitor::apply ( PickableGroup& node )
{
    SGNode* parent = node.getParentNode();
    if ( parent )
	parent->accept ( *this );
}

inline void ParentVisitor::apply ( KdTreeNode& node )
{
    SGNode* parent = node.getParentNode();
    if ( parent )
	parent->accept ( *this );
}

inline void ParentVisitor::apply ( MeshNode& node )
{
    SGNode* parent = node.getParentNode();
    if ( parent )
	parent->accept ( *this );
}

inline void ParentVisitor::apply ( FontNode& node )
{
    SGNode* parent = node.getParentNode();
    if ( parent )
	parent->accept ( *this );
}

inline void ParentVisitor::apply ( TextNode& node )
{
    SGNode* parent = node.getParentNode();
    if ( parent )
	parent->accept ( *this );
}

#endif //_PARENT_VISITOR_H_
