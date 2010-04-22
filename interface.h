// camera management
int create_camera ();
void delete_camera ( int id );
void camera_props ( int id, float scale, float tx, float ty, float tz )
// viewport management
int create_viewport ();
void delete_viewport ( int id );
void viewport_geometry ( int id, int x, int y, int w, int h );
void viewport_camera ( int id, int camid );
// io
int load_mesh ();
void unload_mesh (int id);
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
