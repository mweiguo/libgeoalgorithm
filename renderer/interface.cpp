#include "interface.h"
#include "nodemgr.h"
#include "nodes.h"
#include "vec3.h"
// camera management

int camera_create ()
{
    return CameraMgr::getInst().addNode ();
}

void camera_delete ( int id )
{
    CameraMgr::getInst().erase ( id );
}

void camera_translate ( int id, float tx, float ty, float tz )
{
    CameraOrtho* cam = CameraMgr::getInst()[id];
    if ( cam )
	cam->translate ( vec3f(tx, ty, tz) );
}

void camera_scale ( int id, float scale )
{
    CameraOrtho* cam = CameraMgr::getInst()[id];
    if ( cam )
	cam->zoom  ( scale );
}

void camera_reset ( int id )
{
    CameraOrtho* cam = CameraMgr::getInst()[id];
    if ( cam )
	cam->reset ();
}

int viewport_create ( const char* name )
{
    int id = ViewportMgr::getInst().addNode ();
    viewport_name ( id, name );
    return id;
}

void viewport_delete ( int id )
{
    ViewportMgr::getInst().erase ( id );
}

void viewport_geometry ( int id, int x, int y, int w, int h )
{
    Viewport* p = ViewportMgr::getInst()[id];
    if ( p )
    {
	p->position ( x, y );
	p->size ( w, h );
    }
}

void viewport_attachcamera ( int id, int camid )
{
    Viewport* p = ViewportMgr::getInst()[id];
    if ( p )
	p->attachcamera ( camid );
}

void viewport_name ( int id, const char* nm )
{
    Viewport* p = ViewportMgr::getInst()[id];
    if ( p )
	p->name ( nm );
}

void viewport_update ( int id )
{
    Viewport* p = ViewportMgr::getInst()[id];
    if ( p )
	p->update ();
}

void add_child ( int parent, int child )
{
    NodesVector& nv = NodesVector::getInst();
    nv[parent]->addChild ( nv[child] );
}

void remove_child ( int parent, int child )
{
    NodesVector& nv = NodesVector::getInst();
    nv[parent]->removeChild ( nv[child] );
}

void delete_node ( int id )
{
//     LayerNodeMgr::iterator pp = LayerNodeMgr::getInst().find ( id );
//     if ( pp != LayerNodeMgr::getInst().end() )
//     {
// 	LayerNode* node = pp->second;
// 	// remove relations
//         node->setParentNode ( NULL );
// 	LayerNodeMgr::getInst().erase ( id );
//     }
}

// layer
int layer_create ()
{
    return LayerNodeMgr::getInst().addNode ();
}

void layer_delete ( int id )
{
    LayerNodeMgr::iterator pp = LayerNodeMgr::getInst().find ( id );
    if ( pp != LayerNodeMgr::getInst().end() )
    {
	LayerNode* node = pp->second;
	// remove relations
        node->setParentNode ( NULL );
	LayerNodeMgr::getInst().erase ( id );
    }
}

void layer_name ( int id, const char* nm )
{
    LayerNodeMgr::iterator pp = LayerNodeMgr::getInst().find ( id );
    if ( pp != LayerNodeMgr::getInst().end() )
        pp->second->name ( nm );
}

void layer_visible ( int id, bool isVisible )
{
    LayerNodeMgr& mgr = LayerNodeMgr::getInst();
    LayerNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->second->setVisible ( isVisible );
}

// lod
int lod_create ( )
{
    return LODNodeMgr::getInst().addNode ();
}

void lod_delete ( int id )
{
    LODNodeMgr::iterator pp = LODNodeMgr::getInst().find ( id );
    if ( pp != LODNodeMgr::getInst().end() )
    {
	LODNode* node = pp->second;
	// remove relations
        node->setParentNode ( NULL );
	LODNodeMgr::getInst().erase ( id );
    }
}

void lod_delimiters ( int id, const char* delims )
{
    LODNodeMgr& mgr = LODNodeMgr::getInst();
    LODNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->second->setdelimiters ( delims );
}

// array
int array_create ( )
{
    return ArrayNodeMgr::getInst().addNode ();
}

void array_delete ( int id )
{
}

void array_props ( int id )
{
//   ArrayNodeMgr& mgr = ArrayNodeMgr::getInst();
//   ArrayNodeMgr::iterator pp = mgr.find ( id );
//   if ( pp != mgr.end() )
//     pp->setdelimiters ( nm );
}

// rectangle
int rectangle_create ( )
{
    return RectanglefMgr::getInst().addNode ();
}

void rectangle_delete ( int id )
{
}

void rectangle_props ( int id, float x, float y, float w, float h )
{
    RectanglefMgr& mgr = RectanglefMgr::getInst();
    RectanglefMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->second->setRect ( x, y, w, h );
}

// transform
int transform_create ( )
{
    return TransformNodeMgr::getInst().addNode ();
}

void transform_delete ( int id )
{
}

void transform_translate ( int id, float tx, float ty, float tz )
{
    TransformNodeMgr& mgr = TransformNodeMgr::getInst();
    TransformNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->second->setTranslate ( tx, ty, tz );
}

void transform_scale ( int id, float sx, float sy, float sz )
{
    TransformNodeMgr& mgr = TransformNodeMgr::getInst();
    TransformNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->second->setTranslate ( sx, sy, sz );
}

// pickablegroup
int pickablegroup_create ( )
{
    return PickableGroupMgr::getInst().addNode ();
}

void pickablegroup_delete ( int id )
{
}

void pickablegroup_props ( int id )
{
}

// switchnode
int switchnode_create ( )
{
    return SwitchNodeMgr::getInst().addNode ();
}

void switchnode_delete ( int id )
{
}

void switchnode_props ( int id, bool isVisible )
{
    SwitchNodeMgr& mgr = SwitchNodeMgr::getInst();
    SwitchNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->second->setVisible ( isVisible );
}

// groupnode
int groupnode_create ( )
{
    return GroupNodeMgr::getInst().addNode ();
}

void groupnode_delete ( int id )
{
}

void groupnode_props ( int id, const char* nm )
{
    GroupNodeMgr& mgr = GroupNodeMgr::getInst();
    GroupNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->second->name ( nm );
}

// root
//   |-transform
//        |- mesh
int mesh_load ( const char* file )
{
    // load mesh
    // create transform node
    // return transform node's id
    return 0;
}

void mesh_unload (int id)
{
}

void mesh_translate ( int id, float tx, float ty, float tz )
{
    // get transform node
    transform_translate ( id, tx, ty, tz );
}

void mesh_scale ( int id, float scale )
{
    transform_scale ( id, scale, scale, scale );
}

