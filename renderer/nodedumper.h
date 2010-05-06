#ifndef _NODEDUMPER_H_
#define _NODEDUMPER_H_

#include "childvisitor.h"
#include <string>
#include <sstream>
using namespace std;

class NodeDumper : public ChildVisitor
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
    virtual void apply ( GroupNode& node );
    virtual void apply ( SwitchNode& node );
    void operator() ( SGNode* node )
    {
        _dump.str("");
        _ident = "";
        node->accept ( *this );
    }
    string dumpstring () { return _dump.str(); }
private:
    stringstream _dump;
    string _ident;
};

inline void NodeDumper::apply ( SGNode& node )
{
    stringstream ss;
    _ident.insert ( 0, "  " );
    _dump << _ident << "sgnode" << endl;
    ChildVisitor::apply ( node );
    _ident.erase ( 0, 2 );
}

inline void NodeDumper::apply ( LayerNode& node )
{
    stringstream ss;
    _ident.insert ( 0, "  " );
    _dump << _ident << "LayerNode: name=" << node.name() << endl;
    ChildVisitor::apply ( node );
    _ident.erase ( 0, 2 );
}

inline void NodeDumper::apply ( PickableGroup& node )
{
    stringstream ss;
    _ident.insert ( 0, "  " );
    _dump << _ident << "PickableGroup: name=" << node.name() << endl;
    ChildVisitor::apply ( node );
    _ident.erase ( 0, 2 );
}

inline void NodeDumper::apply ( Rectanglef& node )
{
    stringstream ss;
    _ident.insert ( 0, "  " );
    _dump << _ident << "Rectanglef: w=" << node.w() << " h=" << node.h() << endl;
    ChildVisitor::apply ( node );
    _ident.erase ( 0, 2 );
}

inline void NodeDumper::apply ( TransformNode& node )
{
    stringstream ss;
    _ident.insert ( 0, "  " );
    _dump << _ident << "TransformNode tx=" << node.getMatrix().dx() << 
        " ty=" << node.getMatrix().dy() <<
        " tz=" << node.getMatrix().dz() << endl;
    ChildVisitor::apply ( node );
    _ident.erase ( 0, 2 );
}

inline void NodeDumper::apply ( ArrayNode& node )
{
    stringstream ss;
    _ident.insert ( 0, "  " );
    _dump << _ident << "ArrayNode" << endl;
    ChildVisitor::apply ( node );
    _ident.erase ( 0, 2 );
}

inline void NodeDumper::apply ( LODNode& node )
{
    stringstream ss;
    _ident.insert ( 0, "  " );
    _dump << _ident << "LODNode" << endl;
    ChildVisitor::apply ( node );
    _ident.erase ( 0, 2 );
}

inline void NodeDumper::apply ( KdTreeNode& node )
{
    stringstream ss;
    _ident.insert ( 0, "  " );
    _dump << _ident << "KdTreeNode" << endl;
    ChildVisitor::apply ( node );
    _ident.erase ( 0, 2 );
}

inline void NodeDumper::apply ( MeshNode& node )
{
    stringstream ss;
    _ident.insert ( 0, "  " );
    _dump << _ident << "MeshNode" << endl;
    ChildVisitor::apply ( node );
    _ident.erase ( 0, 2 );
}

inline void NodeDumper::apply ( FontNode& node )
{
    stringstream ss;
    _ident.insert ( 0, "  " );
    _dump << _ident << "FontNode family=" << node.family() <<
        " pointsize=" << node.size() << endl;
    ChildVisitor::apply ( node );
    _ident.erase ( 0, 2 );
}

inline void NodeDumper::apply ( TextNode& node )
{
    stringstream ss;
    _ident.insert ( 0, "  " );
    _dump << _ident << "TextNode string=" << node.text() << endl;
    ChildVisitor::apply ( node );
    _ident.erase ( 0, 2 );
}

inline void NodeDumper::apply ( GroupNode& node )
{
    stringstream ss;
    _ident.insert ( 0, "  " );
    _dump << _ident << "GroupNode name=" << node.name() << endl;
    ChildVisitor::apply ( node );
    _ident.erase ( 0, 2 );
}

inline void NodeDumper::apply ( SwitchNode& node )
{
    stringstream ss;
    _ident.insert ( 0, "  " );
    _dump << _ident << "SwitchNode isVisible=" << node.isVisible() << endl;
    ChildVisitor::apply ( node );
    _ident.erase ( 0, 2 );
}

#endif
