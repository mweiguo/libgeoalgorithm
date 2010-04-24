#ifndef _GROUP_NODE_H_
#define _GROUP_NODE_H_

#include "nodes.h"
#include <map>

template < class T >
class NodeMgr : public std::map<int, T*>
{
public:
  static NodeMgr<T>& getInst () 
  {
    static NodeMgr<T> inst;
    return inst;
  }
  T* addNode ( int id )
  {
    T* pp = NULL;
    if ( this->find ( id ) == end() )
      (*this)[id] = pp = new T();
    return pp;
  }
private:
  NodeMgr () {}
};

typedef NodeMgr<LayerNode>     	LayerNodeMgr;
typedef NodeMgr<LODNode>       	LODNodeMgr;
typedef NodeMgr<ArrayNode>     	ArrayNodeMgr;
typedef NodeMgr<Rectangled>    	RectangledMgr;
typedef NodeMgr<Rectanglef>    	RectanglefMgr;
typedef NodeMgr<Rectanglei>    	RectangleiMgr;
typedef NodeMgr<Rectangles>    	RectanglesMgr;
typedef NodeMgr<TransformNode>  TransformNodeMgr;
typedef NodeMgr<PickableGroup>  PickableGroupMgr;
typedef NodeMgr<SwitchNode>     SwitchNodeMgr;
typedef NodeMgr<GroupNode>      GroupNodeMgr;
typedef NodeMgr<Viewport>       ViewportMgr;
typedef NodeMgr<CameraOrtho>    CameraMgr;

#endif
