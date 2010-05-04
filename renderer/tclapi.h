#ifndef _TCLAPI_H_
#define _TCLAPI_H_

// marshalling all the api, it is a annoy work, is there any trick to avoid this?
#include <tcl.h>

int tcl_add_fixture ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_camera_create ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_camera_delete ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_camera_translate ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_camera_scale ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_camera_reset ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_camera_name ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// viewport management
int tcl_viewport_create ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_viewport_delete ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_viewport_geometry ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_viewport_attachcamera ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_viewport_name ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// local mesh load, treat mesh as a single object
int tcl_mesh_load ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_mesh_save ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_mesh_unload (ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_mesh_translate ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_mesh_scale ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// remote mesh load, C/S architecture, client should maintian node structure
int tcl_add_child ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_remove_child ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// mesh
int tcl_mesh_create ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_mesh_delete ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// layer
int tcl_layer_create ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_layer_delete ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_layer_name ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_layer_visible ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// lod
int tcl_lod_create ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_lod_delete ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_lod_delimiters ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// kdtree
int tcl_kdtree_create ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_kdtree_delete ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// array
int tcl_array_create ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_array_delete ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_array_rowcnt ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_array_columncnt ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_array_hlevelcnt ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_array_vlevelcnt ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_array_marginx ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_array_marginy ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// rectangle
int tcl_rectangle_create ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_rectangle_delete ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_rectangle_size ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// transform
int tcl_transform_create ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_transform_delete ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_transform_translate ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_transform_translate ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_transform_scale ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_transform_scale ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// pickablegroup
int tcl_pickablegroup_create ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_pickablegroup_delete ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_pickablegroup_name ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// switchnode
int tcl_switchnode_create ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_switchnode_delete ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_switchnode_props ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// groupnode
int tcl_groupnode_create ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_groupnode_delete ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_groupnode_props ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// text
int tcl_text_create ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_text_delete ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_text_string ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_text_font ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_text_anchor ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_text_justify ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

// font
int tcl_font_create ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_font_delete ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_font_family ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
int tcl_font_size ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );
/*PLAIN = 1, BOLD = 2, ITALIC = 3, BOLDITALIC = 4*/
int tcl_font_style ( ClientData clientData, Tcl_Interp* interp, int argc, Tcl_Obj* const argv[] );

void createcommands ( Tcl_Interp* interp );
#endif //_TCLAPI_H_
