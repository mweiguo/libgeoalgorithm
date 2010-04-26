// camera management
int camera_create ( const char* name );
void camera_delete ( int id );
void camera_translate ( int id, float tx, float ty, float tz );
void camera_scale ( int id, float scale );
void camera_reset ( int id );
void camera_name ( int id, const char* name );
// viewport management
int viewport_create ( const char* name );
void viewport_delete ( int id );
void viewport_geometry ( int id, int x, int y, int w, int h );
void viewport_attachcamera ( int id, int camid );
void viewport_name ( int id, const char* name );
class QPainter;
void viewport_update ( int id, QPainter& painter );
// build interfaces
void add_child ( int parent, int child );
void remove_child ( int preant, int child );
// layer
int layer_create ( const char* name );
void layer_delete ( int id );
void layer_name ( int id, const char* name );
void layer_visible ( int id, bool isVisible );
// lod
int lod_create ( );
void lod_delete ( int id );
void lod_delimiters ( int id, const char* delims );
// array
int array_create ( );
void array_delete ( int id );
void array_props ( int id );
// rectangle
int rectangle_create ( );
void rectangle_delete ( int id );
void rectangle_props ( int id, float x, float y, float w, float h );
// transform
int transform_create ();
void transform_delete ( int id );
void transform_translate ( int id, float tx, float ty, float tz );
void transform_scale ( int id, float sx, float sy, float sz );
// pickablegroup
int pickablegroup_create ( );
void pickablegroup_delete ( int id );
void pickablegroup_props ( int id );
// switchnode
int switchnode_create ( );
void switchnode_delete ( int id );
void switchnode_props ( int id, bool isVisible );
// groupnode
int groupnode_create ( );
void groupnode_delete ( int id );
void groupnode_props ( int id, const char* name );
// io
int mesh_load ( const char* file );
void mesh_unload (int id);
void mesh_translate ( int id, float tx, float ty, float tz );
void mesh_scale ( int id, float scale );



/// temporary implementation
#include "nodemgr.h"
#include "nodes.h"
#include "vec3.h"
#include "renderfunctor.h"
#include "renderflow.h"
// camera management

inline int camera_create ( const char* name )
{
    return CameraMgr::getInst().addNode ();
}

inline void camera_delete ( int id )
{
    CameraMgr::getInst().erase ( id );
}

inline void camera_translate ( int id, float tx, float ty, float tz )
{
    CameraOrtho* cam = CameraMgr::getInst()[id];
    if ( cam )
	cam->translate ( vec3f(tx, ty, tz) );
}

inline void camera_scale ( int id, float scale )
{
    CameraOrtho* cam = CameraMgr::getInst()[id];
    if ( cam )
	cam->zoom  ( scale );
}

inline void camera_reset ( int id )
{
    CameraOrtho* cam = CameraMgr::getInst()[id];
    if ( cam )
        cam->reset ();
}

inline void camera_name ( int id, const char* nm )
{
    CameraOrtho* cam = CameraMgr::getInst()[id];
    if ( cam )
        cam->name ( nm );
}

inline int viewport_create ( const char* name )
{
    int id = ViewportMgr::getInst().addNode ();
    viewport_name ( id, name );
    return id;
}

inline void viewport_delete ( int id )
{
    ViewportMgr::getInst().erase ( id );
}

inline void viewport_geometry ( int id, int x, int y, int w, int h )
{
    Viewport* p = ViewportMgr::getInst()[id];
    if ( p )
    {
	p->position ( x, y );
	p->size ( w, h );
    }
}

inline void viewport_attachcamera ( int id, int camid )
{
    Viewport* p = ViewportMgr::getInst()[id];
    if ( p )
	p->attachcamera ( camid );
}

inline void viewport_name ( int id, const char* nm )
{
    Viewport* p = ViewportMgr::getInst()[id];
    if ( p )
	p->name ( nm );
}

inline void viewport_update ( int id, QPainter& painter )
{
    Viewport* p = ViewportMgr::getInst()[id];   
    if ( p )
    {
        RenderOption opt;
        opt.painter = &painter;
        RenderFlow renderflow ( *p, opt );
        p->update ();
    }
}

inline void add_child ( int parent, int child )
{
    NodesVector& nv = NodesVector::getInst();
    nv[parent]->addChild ( nv[child] );
}

inline void remove_child ( int parent, int child )
{
    NodesVector& nv = NodesVector::getInst();
    nv[parent]->removeChild ( nv[child] );
}

inline void delete_node ( int id )
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
inline int layer_create ( const char* name )
{
    int id = LayerNodeMgr::getInst().addNode ();
    layer_name ( id, name );
    return id;
}

inline void layer_delete ( int id )
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

inline void layer_name ( int id, const char* nm )
{
    LayerNodeMgr::iterator pp = LayerNodeMgr::getInst().find ( id );
    if ( pp != LayerNodeMgr::getInst().end() )
        pp->second->name ( nm );
}

inline void layer_visible ( int id, bool isVisible )
{
    LayerNodeMgr& mgr = LayerNodeMgr::getInst();
    LayerNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->second->setVisible ( isVisible );
}

// lod
inline int lod_create ( )
{
    return LODNodeMgr::getInst().addNode ();
}

inline void lod_delete ( int id )
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

inline void lod_delimiters ( int id, const char* delims )
{
    LODNodeMgr& mgr = LODNodeMgr::getInst();
    LODNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->second->setdelimiters ( delims );
}

// array
inline int array_create ( )
{
    return ArrayNodeMgr::getInst().addNode ();
}

inline void array_delete ( int id )
{
}

inline void array_props ( int id )
{
//   ArrayNodeMgr& mgr = ArrayNodeMgr::getInst();
//   ArrayNodeMgr::iterator pp = mgr.find ( id );
//   if ( pp != mgr.end() )
//     pp->setdelimiters ( nm );
}

// rectangle
inline int rectangle_create ( )
{
    return RectanglefMgr::getInst().addNode ();
}

inline void rectangle_delete ( int id )
{
}

inline void rectangle_props ( int id, float x, float y, float w, float h )
{
    RectanglefMgr& mgr = RectanglefMgr::getInst();
    RectanglefMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->second->setRect ( x, y, w, h );
}

// transform
inline int transform_create ( )
{
    return TransformNodeMgr::getInst().addNode ();
}

inline void transform_delete ( int id )
{
}

inline void transform_translate ( int id, float tx, float ty, float tz )
{
    TransformNodeMgr& mgr = TransformNodeMgr::getInst();
    TransformNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->second->setTranslate ( tx, ty, tz );
}

inline void transform_scale ( int id, float sx, float sy, float sz )
{
    TransformNodeMgr& mgr = TransformNodeMgr::getInst();
    TransformNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->second->setTranslate ( sx, sy, sz );
}

// pickablegroup
inline int pickablegroup_create ( )
{
    return PickableGroupMgr::getInst().addNode ();
}

inline void pickablegroup_delete ( int id )
{
}

inline void pickablegroup_props ( int id )
{
}

// switchnode
inline int switchnode_create ( )
{
    return SwitchNodeMgr::getInst().addNode ();
}

inline void switchnode_delete ( int id )
{
}

inline void switchnode_props ( int id, bool isVisible )
{
    SwitchNodeMgr& mgr = SwitchNodeMgr::getInst();
    SwitchNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->second->setVisible ( isVisible );
}

// groupnode
inline int groupnode_create ( )
{
    return GroupNodeMgr::getInst().addNode ();
}

inline void groupnode_delete ( int id )
{
}

inline void groupnode_props ( int id, const char* nm )
{
    GroupNodeMgr& mgr = GroupNodeMgr::getInst();
    GroupNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->second->name ( nm );
}

// root
//   |-transform
//        |- mesh
inline int mesh_load ( const char* file )
{
    // load mesh
    // create transform node
    // return transform node's id
    return 0;
}

inline void mesh_unload (int id)
{
}

inline void mesh_translate ( int id, float tx, float ty, float tz )
{
    // get transform node
    transform_translate ( id, tx, ty, tz );
}

inline void mesh_scale ( int id, float scale )
{
    transform_scale ( id, scale, scale, scale );
}

