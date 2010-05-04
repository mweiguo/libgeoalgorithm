#ifndef _INTERFACE_H
#define _INTERFACE_H
#include "qviewport.h"
// camera management
int camera_create ( const char* name );
void camera_translate ( int id, float tx, float ty, float tz );
void camera_scale ( int id, float scale );
void camera_reset ( int id );
void camera_name ( int id, const char* name );
// viewport management
int viewport_create ( const char* name );
void viewport_geometry ( int id, int x, int y, int w, int h );
void viewport_attachcamera ( int id, int camid );
void viewport_name ( int id, const char* name );
void viewport_dirty ( int id );
class QPainter;
void viewport_update ( int id, QPainter& painter );
// window
void viewport_add ( int id );
void viewport_delete ( int id );
void update ( int id );
// local mesh load, treat mesh as a single object
int mesh_load ( const char* file );
void mesh_save ( const char* file, int meshid );
void mesh_unload (int id);
void mesh_translate ( int id, float tx, float ty, float tz );
void mesh_scale ( int id, float scale );
// remote mesh load, C/S architecture, client should maintian node structure
void add_child ( int parent, int child );
void remove_child ( int preant, int child );
void node_delete ( int id );
// mesh
int mesh_create ();
// layer
int layer_create ( const char* name );
void layer_name ( int id, const char* name );
void layer_visible ( int id, bool isVisible );
// lod
int lod_create ();
void lod_delimiters ( int id, const char* delims );
// kdtree
int kdtree_create ();
// array
int array_create ();
void array_rowcnt ( int id, int cnt );
void array_columncnt ( int id, int cnt );
void array_hlevelcnt ( int id, int level, int cnt );
void array_vlevelcnt ( int id, int level, int cnt );
void array_marginx ( int id, int level, float space );
void array_marginy ( int id, int level, float space );
// rectangle
int rectangle_create ();
void rectangle_size ( int id, float w, float h );
// transform
int transform_create ();
void transform_translate ( int id, float tx, float ty, float tz );
void transform_translate ( int id, const char* str );
void transform_scale ( int id, float sx, float sy, float sz );
void transform_scale ( int id, const char* str );
// pickablegroup
int pickablegroup_create ();
void pickablegroup_name ( int id, const char* name );
// switchnode
int switchnode_create ();
void switchnode_props ( int id, bool isVisible );
// groupnode
int groupnode_create ();
void groupnode_props ( int id, const char* name );
// text
int text_create ();
void text_string ( int id, const char* str );
void text_font ( int id, int fontid );
//  1     2     3
//  4     5     6
//  7     8     9
void text_anchor ( int id, int anchor );
//  1     2     3
//  4     5     6
//  7     8     9
void text_justify ( int id, int justify );
// font
int font_create ();
void font_family ( int id, const char* f );
void font_size ( int id, float size );
/*PLAIN = 1, BOLD = 2, ITALIC = 3, BOLDITALIC = 4*/
void font_style ( int id, int style );
//void font_color ( int id, const char* color );
/// temporary implementation
#include "nodemgr.h"
#include "nodes.h"
#include "vec3.h"
#include "renderfunctor.h"
#include "renderflow.h"
#include "savemesh.h"
//#include "loadmesh.h"
// camera management

inline int camera_create ( const char* name )
{
    // new camera
    // add it to manager
    return NodeMgr::getInst().addNode<CameraOrtho> ();
}

inline void camera_translate ( int id, float tx, float ty, float tz )
{
    CameraOrtho* cam = NodeMgr::getInst().getNodePtr<CameraOrtho> (id);
    if ( cam )
	cam->translate ( vec3f(tx, ty, tz) );
}

inline void camera_scale ( int id, float scale )
{
    CameraOrtho* cam = NodeMgr::getInst().getNodePtr<CameraOrtho> (id);
    if ( cam )
	cam->zoom  ( scale );
}

inline void camera_reset ( int id )
{
    CameraOrtho* cam = NodeMgr::getInst().getNodePtr<CameraOrtho> (id);
    if ( cam )
        cam->reset ();
}

inline void camera_name ( int id, const char* nm )
{
    CameraOrtho* cam = NodeMgr::getInst().getNodePtr<CameraOrtho> (id);
    if ( cam )
        cam->name ( nm );
}

inline int viewport_create ( const char* name )
{
    int id = NodeMgr::getInst().addNode<Viewport> ();
    viewport_name ( id, name );
    return id;
}

inline void viewport_geometry ( int id, int x, int y, int w, int h )
{
    Viewport* p = NodeMgr::getInst().getNodePtr<Viewport> (id);
    if ( p )
    {
        p->position ( x, y );
        p->size ( w, h );
    }
}

inline void viewport_attachcamera ( int id, int camid )
{
    Viewport* p = NodeMgr::getInst().getNodePtr<Viewport> (id);
    if ( p )
	p->attachcamera ( camid );
}

inline void viewport_name ( int id, const char* nm )
{
    Viewport* p = NodeMgr::getInst().getNodePtr<Viewport> (id);
    if ( p )
	p->name ( nm );
}

inline void viewport_update ( int id, QPainter& painter )
{
    Viewport* p = NodeMgr::getInst().getNodePtr<Viewport> (id);
    if ( p )
    {
        RenderOption opt;
        opt.painter = &painter;
        RenderFlow renderflow ( *p, opt );
        p->update ();
    }
}

inline void viewport_dirty ( int id )
{
    Viewport* p = NodeMgr::getInst().getNodePtr<Viewport> (id);
    if ( p )
	p->dirty ( true );
}

inline void viewport_add ( int id )
{
    QViewport::getInst().add_viewport( id );
}

inline void viewport_delete ( int id )
{
    QViewport::getInst().remove_viewport( id );
}

inline void update ( int id )
{
    viewport_dirty ( id );
    QViewport::getInst().update();
}

inline void add_child ( int parent, int child )
{
    NodeMgr& nv = NodeMgr::getInst();
    NodeMgr::iterator pp1 = nv.find ( parent );
    NodeMgr::iterator pp2 = nv.find ( child );
    if ( pp1!=nv.end() && pp2!=nv.end() )
	pp1->second->addChild ( pp2->second );
}

inline void remove_child ( int parent, int child )
{
    NodeMgr& nv = NodeMgr::getInst();
    NodeMgr::iterator pp1 = nv.find ( parent );
    NodeMgr::iterator pp2 = nv.find ( child );
    if ( pp1!=nv.end() && pp2!=nv.end() )
	pp1->second->removeChild ( pp2->second );
}

inline void node_delete ( int id )
{
    NodeMgr::iterator pp = NodeMgr::getInst().find(id);
    if ( pp != NodeMgr::getInst().end() )
    {
        SGNode* node = pp->second;
        node->removeAllChild ();
        node->setParentNode ( NULL );
        delete node;
        NodeMgr::getInst().erase ( id );
    }
}

// mesh
inline int mesh_create ()
{
    return NodeMgr::getInst().addNode<MeshNode> ();
}

// layer
inline int layer_create ( const char* name )
{
    int id = NodeMgr::getInst().addNode<LayerNode> ();
    layer_name ( id, name );
    return id;
}

inline void layer_name ( int id, const char* nm )
{
    LayerNode* layer = NodeMgr::getInst().getNodePtr<LayerNode> ( id );
    if ( layer )
        layer->name ( nm );
}

inline void layer_visible ( int id, bool isVisible )
{
    LayerNode* layer = NodeMgr::getInst().getNodePtr<LayerNode> ( id );
    if ( layer )
        layer->setVisible ( isVisible );
}

// lod
inline int lod_create ()
{
    return NodeMgr::getInst().addNode<LODNode> ();
}

inline void lod_delimiters ( int id, const char* delims )
{
    LODNode* lod = NodeMgr::getInst().getNodePtr<LODNode> ( id );
    if ( lod )
        lod->setdelimiters ( delims );
}

// kdtree
inline int kdtree_create ()
{
    return NodeMgr::getInst().addNode<KdTreeNode> ();
}

// array
inline int array_create ()
{
    return NodeMgr::getInst().addNode<ArrayNode> ();
}

inline void array_rowcnt ( int id, int cnt )
{
    ArrayNode* parray = NodeMgr::getInst().getNodePtr<ArrayNode>(id);
    if ( parray )
        parray->setRowCnt ( cnt );
}

inline void array_columncnt ( int id, int cnt )
{
    ArrayNode* parray = NodeMgr::getInst().getNodePtr<ArrayNode>(id);
    if ( parray )
        parray->setColumnCnt ( cnt );
}

inline void array_hlevelcnt ( int id, int level, int cnt )
{
    ArrayNode* parray = NodeMgr::getInst().getNodePtr<ArrayNode>(id);
    if ( parray )
        parray->setHLevels ( level, cnt );
}

inline void array_vlevelcnt ( int id, int level, int cnt )
{
    ArrayNode* parray = NodeMgr::getInst().getNodePtr<ArrayNode>(id);
    if ( parray )
        parray->setVLevels ( level, cnt );
}

inline void array_marginx ( int id, int level, float space )
{
    ArrayNode* parray = NodeMgr::getInst().getNodePtr<ArrayNode>(id);
    if ( parray )
        parray->setMarginX ( level, space );
}

inline void array_marginy ( int id, int level, float space )
{
    ArrayNode* parray = NodeMgr::getInst().getNodePtr<ArrayNode>(id);
    if ( parray )
        parray->setMarginY ( level, space );
}

// rectangle
inline int rectangle_create ()
{
    return NodeMgr::getInst().addNode<Rectanglef> ();
}

inline void rectangle_size ( int id, float width, float height )
{
    Rectanglef* rect = NodeMgr::getInst().getNodePtr<Rectanglef>(id);
    if ( rect )
    {
        rect->w ( width );
        rect->h ( height );
    }
}

// transform
inline int transform_create ()
{
    return NodeMgr::getInst().addNode<TransformNode> ();
}

inline void transform_translate ( int id, float tx, float ty, float tz )
{
    TransformNode* node = NodeMgr::getInst().getNodePtr<TransformNode> (id);
    if ( node )
        node->setTranslate ( tx, ty, tz );
}

inline void transform_translate ( int id, const char* str )
{
    TransformNode* node = NodeMgr::getInst().getNodePtr<TransformNode> (id);
    if ( node )
        node->setTranslate ( str );
}

inline void transform_scale ( int id, float sx, float sy, float sz )
{
    TransformNode* node = NodeMgr::getInst().getNodePtr<TransformNode> (id);
    if ( node )
        node->setScale ( sx, sy, sz );
}
inline void transform_scale ( int id, const char* str )
{
    TransformNode* node = NodeMgr::getInst().getNodePtr<TransformNode> (id);
    if ( node )
        node->setScale ( str );
}

// pickablegroup
inline int pickablegroup_create ()
{
    return NodeMgr::getInst().addNode<PickableGroup> ();
}

inline void pickablegroup_name ( int id, const char* nm )
{
    PickableGroup* pick = NodeMgr::getInst().getNodePtr<PickableGroup> (id);
    if ( pick )
        pick->name ( nm );
}

// switchnode
inline int switchnode_create ()
{
    return NodeMgr::getInst().addNode<SwitchNode> ();
}

inline void switchnode_props ( int id, bool isVisible )
{
    SwitchNode* node = NodeMgr::getInst().getNodePtr<SwitchNode> (id);
    if ( node )
        node->setVisible ( isVisible );
}

// groupnode
inline int groupnode_create ()
{
    return NodeMgr::getInst().addNode<GroupNode> ();
}

inline void groupnode_props ( int id, const char* nm )
{
    GroupNode* node = NodeMgr::getInst().getNodePtr<GroupNode> (id);
    if ( node )
        node->name ( nm );
}

inline int text_create ()
{
    return NodeMgr::getInst().addNode<TextNode> ();
}

inline void text_string ( int id, const char* str )
{
    TextNode* node = NodeMgr::getInst().getNodePtr<TextNode> (id);
    if ( node )
        node->text ( str );
}

inline void text_font ( int id, int fontid )
{
    TextNode* node = NodeMgr::getInst().getNodePtr<TextNode> (id);
    if ( node )
    {
	FontNode* fnode = NodeMgr::getInst().getNodePtr<FontNode> (id);
	if ( fnode )
        {
            node->fontnode ( fnode );
        }
    }
}

//  1     2     3
//  4     5     6
//  7     8     9
inline void text_anchor ( int id, int anchor )
{
    TextNode* node = NodeMgr::getInst().getNodePtr<TextNode> (id);
    if ( node )
    {
        switch ( anchor )
        {
        case 1:
            node->setAnchor ( TextNode::AnchorLEFT & TextNode::AnchorTOP );
            break;
        case 2:
            node->setAnchor ( TextNode::AnchorTOP );
            break;
        case 3:
            node->setAnchor ( TextNode::AnchorRIGHT & TextNode::AnchorTOP );
            break;
        case 4:
            node->setAnchor ( TextNode::AnchorLEFT );
            break;
        case 5:
            node->setAnchor ( TextNode::AnchorCENTER );
            break;
        case 6:
            node->setAnchor ( TextNode::AnchorRIGHT );
            break;
        case 7:
            node->setAnchor ( TextNode::AnchorLEFT & TextNode::AnchorBOTTOM );
            break;
        case 8:
            node->setAnchor ( TextNode::AnchorBOTTOM );
            break;
        case 9:
            node->setAnchor ( TextNode::AnchorRIGHT & TextNode::AnchorBOTTOM );
            break;
        }
    }
}

//  1     2     3
//  4     5     6
//  7     8     9
inline void text_justify ( int id, int justify )
{
    TextNode* node = NodeMgr::getInst().getNodePtr<TextNode> (id);
    if ( node )
    {
        switch ( justify )
        {
        case 1:
            node->setAlignFlag ( TextNode::AlignLeft & TextNode::AlignTop );
            break;
        case 2:
            node->setAlignFlag ( TextNode::AlignTop );
            break;
        case 3:
            node->setAlignFlag ( TextNode::AlignRight & TextNode::AlignTop );
            break;
        case 4:
            node->setAlignFlag ( TextNode::AlignLeft );
            break;
        case 5:
            node->setAlignFlag ( TextNode::AlignCenter );
            break;
        case 6:
            node->setAlignFlag ( TextNode::AlignRight );
            break;
        case 7:
            node->setAlignFlag ( TextNode::AlignLeft & TextNode::AlignBottom );
            break;
        case 8:
            node->setAlignFlag ( TextNode::AlignBottom );
            break;
        case 9:
            node->setAlignFlag ( TextNode::AlignRight & TextNode::AlignBottom );
            break;
        }
    }
}

// font
inline int font_create ()
{
    return NodeMgr::getInst().addNode<FontNode> ();
}

inline void font_family ( int id, const char* f )
{
    FontNode* node = NodeMgr::getInst().getNodePtr<FontNode> (id);
    if ( node )
        node->family ( f );
}

inline void font_size ( int id, float sz )
{
    FontNode* node = NodeMgr::getInst().getNodePtr<FontNode> (id);
    if ( node )
        node->size ( sz );
}

/*PLAIN = 1, BOLD = 2, ITALIC = 3, BOLDITALIC = 4*/
inline void font_style ( int id, int style )
{
    /* FontNode* node = NodeMgr::getInst().getNodePtr<FontNode> (id); */
    /* if ( node ) */
}


// root
//   |-transform
//        |- mesh
inline int mesh_load ( const char* file )
{
    // load mesh
/*     LoadMesh loadmesh ( file ); */
/*     return loadmesh.root(); */
    return 0;
}

inline void mesh_save ( const char* file, int meshid )
{
    MeshNode* node = NodeMgr::getInst().getNodePtr<MeshNode>(meshid);
    if ( node )
        SaveMesh saver ( file, node );
}

inline void mesh_unload (int meshid)
{
/*     MeshNode* node = NodeMgr::getInst().getNodePtr<MeshNode>(meshid); */
/*     if ( node ) */
/*         UnloadMesh unloadmesh ( node ); */
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

#endif
