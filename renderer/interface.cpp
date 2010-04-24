// camera management
static int seed = 0;

void nodes_reserve ( int count )
{
    gnodes.reserve ( count );
}

int create_camera ()
{
    CameraMgr::getInst().addNode ( seed );
    return seed++;
}

void delete_camera ( int id )
{
    CameraMgr::getInst().erase ( seed );
}

void camera_props ( int id, float scale, float tx, float ty, float tz )
{
    CameraOrtho* cam = CameraMgr::getInst()[id];
    if ( NULL == cam )
        return;
    cam->zoom  ( scale );
    cam->translate ( tx, ty, tz );
}

int create_viewport ()
{
    ViewportMgr::getInst().addNode ( seed );
    return seed++;
}

void delete_viewport ( int id )
{
    ViewportMgr::getInst().erase ( id );
}

void viewport_geometry ( int id, int x, int y, int w, int h )
{
    Viewport* p = ViewportMgr::getInst()[id];
    if ( NULL == p )
        return;
    p->position ( x, y );
    p->size ( w, h )
        }

void viewport_camera ( int id, int camid )
{
    CameraOrtho* cam = CameraMgr::getInst()[camid];
    Viewport* p = ViewportMgr::getInst()[id];
    if ( NULL == cam || NULL == p )
        return;

    p->attachcamera ( cam );
}

void viewport_name ( int id, const char* nm )
{
    Viewport* p = ViewportMgr::getInst()[id];
    if ( NULL == p )
        return;
    p->name ( name );
}

// root
//   |-transform
//        |- mesh
int mesh_load ( const char* file )
{
    // load mesh
    // create transform node
    // return transform node's id
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
    transform_scale ( id, scale );
}

void add_child ( int parent, int child )
{
    gnodes[parent].addChild ( &gnodes[child] );
}

void remove_child ( int preant, int child )
{
    gnodes[parent].removeChild ( &gnodes[child] );
}

// layer
int layer_create ()
{
    LayerNodeMgr::getInst().addNode ( seed );
    return seed++;
}

void layer_delete ( int id )
{
    // remove relations
    gnodes[id].setParentNode ( NULL );
    // delete layernode & it's children
}

void layer_name ( int id, const char* nm )
{
    LayerNodeMgr::iterator pp = LayerNodeMgr::getInst().find ( id );
    if ( pp != LayerNodeMgr::getInst().end() )
        pp->name ( nm );
}

void layer_visible ( int id, bool isVisible )
{
    LayerNodeMgr& mgr = LayerNodeMgr::getInst();
    LayerNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->setVisible ( isVisible );
}

// lod
int lod_create ( )
{
    LODNodeMgr::getInst().addNode ( seed );
    return seed++;
}

void lod_delete ( int id )
{
}

void lod_delimiters ( int id, const char* delims )
{
    LODNodeMgr& mgr = LODNodeMgr::getInst();
    LODNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->setdelimiters ( nm );
}

// array
int array_create ( )
{
    ArrayNodeMgr::getInst().addNode ( seed );
    return seed++;
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
    RectanglefMgr::getInst().addNode ( seed );
    return seed++;
}

void rectangle_delete ( int id )
{
}

void rectangle_props ( int id, float x, float y, float w, float h );
{
    RectanglefMgr& mgr = RectanglefMgr::getInst();
    RectanglefMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->setRect ( x, y, w, h );
}

// transform
int transform_create ( )
{
    TransformNodeMgr::getInst().addNode ( seed );
    return seed++;
}

void transform_delete ( int id )
{
}

void transform_translate ( int id, float tx, float ty, float tz )
{
    TransformNodeMgr& mgr = TransformNodeMgr::getInst();
    TransformNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->setTranslate ( tx, ty, tz );
}

void transform_scale ( int id, float sx, float sy, float sz )
{
    TransformNodeMgr& mgr = TransformNodeMgr::getInst();
    TransformNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->setTranslate ( sx, sy, sz );
}

// pickablegroup
int pickablegroup_create ( )
{
    PickableGroupMgr::getInst().addNode ( seed );
    return seed++;
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
    SwitchNodeMgr::getInst().addNode ( seed );
    return seed++;
}

void switchnode_delete ( int id )
{
}

void switchnode_props ( int id, bool isVisible )
{
    SwitchNodeMgr& mgr = SwitchNodeMgr::getInst();
    SwitchNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->setVisible ( isVisible );
}

// groupnode
int groupnode_create ( )
{
    GroupNodeMgr::getInst().addNode ( seed );
    return seed++;
}

void groupnode_delete ( int id )
{
}

void groupnode_props ( int id, const char* nm )
{
    GroupNodeMgr& mgr = GroupNodeMgr::getInst();
    GroupNodeMgr::iterator pp = mgr.find ( id );
    if ( pp != mgr.end() )
        pp->name ( nm );
}
