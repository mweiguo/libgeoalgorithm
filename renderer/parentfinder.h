#ifndef _PARENT_FINDER_H_
#define _PARENT_FINDER_H_

#include "parentvisitor.h"
struct FalseType { enum { value = false }; };
struct TrueType { enum { value = true }; };

template <typename T1, typename T2>
struct IsSame
{
    typedef FalseType Result;
};

template <typename T>
struct IsSame<T,T>
{
    typedef TrueType Result;
};

template < class T >
class ParentFinder : public ParentVisitor
{
public:
    ParentFinder() : _target(0) {}
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
    T* operator () ( SGNode* p ) 
    {
        SGNode* parent = p->getParentNode();
        if ( parent )
            parent->accept ( *this );
        return _target;
    }
private:
    T* _target;
};

template < class T >
void ParentFinder<T>::apply ( LayerNode& node )
{
    if ( false == IsSame<T, LayerNode>::Result::value ) {
	ParentVisitor::apply ( node );
    } else 
        _target = dynamic_cast<T*>(&node);
}

template < class T >
void ParentFinder<T>::apply ( Rectanglef& node )
{
    if ( false == IsSame<T, Rectanglef>::Result::value ) {
	ParentVisitor::apply ( node );
    } else 
        _target = dynamic_cast<T*>(&node);
}

template < class T >
void ParentFinder<T>::apply ( TransformNode& node )
{
    if ( false == IsSame<T, TransformNode>::Result::value ) {
	ParentVisitor::apply ( node );
    } else 
        _target = dynamic_cast<T*>(&node);
}

template < class T >
void ParentFinder<T>::apply ( ArrayNode& node )
{
    if ( false == IsSame<T, ArrayNode>::Result::value ) {
	ParentVisitor::apply ( node );
    } else 
        _target = dynamic_cast<T*>(&node);
}

template < class T >
void ParentFinder<T>::apply ( LODNode& node )
{
    if ( false == IsSame<T, LODNode>::Result::value ) {
	ParentVisitor::apply ( node );
    } else 
        _target = dynamic_cast<T*>(&node);
}

template < class T >
void ParentFinder<T>::apply ( PickableGroup& node )
{
    if ( false == IsSame<T, PickableGroup>::Result::value ) {
	ParentVisitor::apply ( node );
    } else 
        _target = dynamic_cast<T*>(&node);
}

template < class T >
void ParentFinder<T>::apply ( KdTreeNode& node )
{
    if ( false == IsSame<T, KdTreeNode>::Result::value ) {
	ParentVisitor::apply ( node );
    } else 
        _target = dynamic_cast<T*>(&node);
}

template < class T >
void ParentFinder<T>::apply ( MeshNode& node )
{
    if ( false == IsSame<T, KdTreeNode>::Result::value ) {
	ParentVisitor::apply ( node );
    } else 
        _target = dynamic_cast<T*>(&node);
}

template < class T >
void ParentFinder<T>::apply ( FontNode& node )
{
    if ( false == IsSame<T, KdTreeNode>::Result::value ) {
	ParentVisitor::apply ( node );
    } else 
        _target = dynamic_cast<T*>(&node);
}

template < class T >
void ParentFinder<T>::apply ( TextNode& node )
{
    if ( false == IsSame<T, KdTreeNode>::Result::value ) {
	ParentVisitor::apply ( node );
    } else 
        _target = dynamic_cast<T*>(&node);
}

#endif  // _PARENT_FINDER_H_
