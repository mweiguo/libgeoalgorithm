void nodes_reserve ( int count );
// camera management
int camera_create ( const char* name );
void camera_delete ( int id );
void camera_translate ( int id, float tx, float ty, float tz );
void camera_zoom ( int id, float scale );
void camera_reset ( int id );
// viewport management
int viewport_create ( const char* name );
void viewport_delete ( int id );
void viewport_geometry ( int id, int x, int y, int w, int h );
void viewport_attachcamera ( int id, int camid );
void viewport_name ( int id, const char* name );
void viewport_update ( int id );
// io
int mesh_load ( const char* file );
void mesh_unload (int id);
void mesh_translate ( int id, float tx, float ty, float tz );
void mesh_scale ( int id, float scale );
// build interfaces
void add_child ( int parent, int child );
void remove_child ( int preant, int child );
// layer
int layer_create ( );
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
