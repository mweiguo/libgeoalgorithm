#ifndef _LAYER_NODE_H_
#define _LAYER_NODE_H_

#include "groupnode.h"
#include "nodemgr.h"
#include "lodnode.h"

class LayerNode : public GroupNode
{
public:
    LayerNode ( const string& name="default" ) :GroupNode(name) {}
    //LODNode* lod() { return dynamic_cast<LODNode*>(*begin()); }
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~LayerNode () {}
};

//class LayerNodeMgr : public std::map<int, LayerNode*>
//{
//public:
//    static LayerNodeMgr& getInst () 
//    {
//        static LayerNodeMgr inst;
//        return inst;
//    }
//    int addNode ()
//    {
//        int id = NodesVector::getInst().size();
//        T* pp = NULL;
//        (*this)[id] = pp = new LayerNode();
//        NodesVector::getInst().push_back ( pp );
//        SceneMgr::getInst().push_back ( pp );
//        return id;
//    }
//    void erase ( int key )
//    {
//        iterator pp = find ( key );
//        if ( pp != end() )
//        {
//            SceneMgr::getInst().erase ( pp->second );
//            std::map<int, LayerNode*>::erase ( key );
//        }
//    }
//private:
//    LayerNodeMgr () {}
//};
typedef NodeMgr<LayerNode>      LayerNodeMgr;

#endif
