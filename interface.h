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
int load_mesh ( const char* file );
void unload_mesh (int id);

// build mesh interfaces
/* // mesh management */
/* int create_layer ( int parent ); */
/* void delete_layer ( int id ); */
/* void layer_props ( int id ); */
/* int create_array ( int parent ); */
/* void delete_array ( int id ); */
/* void array_props ( int id ); */
/* int create_rectangle ( int parent ); */
/* void delete_rectangle ( int id ); */
/* void rectangle_props ( int id ); */
/* int create_transform ( int parent ); */
/* void delete_transform ( int id ); */
/* void transform_props ( int id ); */
