#include "tclapi.h"
#include "interface.h"

int tcl_camera_create ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try 
    {
	if ( objc != 2 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_camera_create cameraname" );
	    return TCL_ERROR;
	}

	int len;
	const char* camname = Tcl_GetStringFromObj ( objv[1], &len);
	camera_create ( camname );
	return TCL_OK;
    } catch ( std::exception& e ) {
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_camera_delete ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

int tcl_camera_translate ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try 
    {
	if ( objc != 5 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_camera_translate id tx ty tz" );
	    return TCL_ERROR;
	}

	int id;
	double tx, ty, tz;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetDoubleFromObj ( interp, objv[2], &tx );
	Tcl_GetDoubleFromObj ( interp, objv[3], &ty );
	Tcl_GetDoubleFromObj ( interp, objv[4], &tz );
 
	camera_translate ( id, tx, ty, tz );
	return TCL_OK;
    } catch ( std::exception& e ) {
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_camera_scale ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_camera_scale id scale" );
	    return TCL_ERROR;
	}

	int id;
	double scale;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetDoubleFromObj ( interp, objv[2], &scale );
 
	camera_scale ( id, scale );
	return TCL_OK;
    } catch ( std::exception& e ) {
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_camera_reset ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 2 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_camera_reset id" );
	    return TCL_ERROR;
	}

	int id;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
 
	camera_reset ( id );
	return TCL_OK;
    } catch ( std::exception& e ) {
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_camera_name ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 2 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_camera_name id name" );
	    return TCL_ERROR;
	}

	int id, len;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	const char* camname = Tcl_GetStringFromObj ( objv[2], &len );
 
	camera_name ( id, camname );
	return TCL_OK;
    } catch ( std::exception& e ) {
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}


// viewport management
int tcl_viewport_create ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 2 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_viewport_create name" );
	    return TCL_ERROR;
	}

	int len;
	const char* vpname = Tcl_GetStringFromObj ( objv[1], &len );
 
	int id;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	id = viewport_create ( vpname );

	Tcl_Obj* rstobj = Tcl_NewIntObj(id);
	Tcl_SetObjResult ( interp, rstobj );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_viewport_delete ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

int tcl_viewport_geometry ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 6 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_viewport_geometry id x y w h" );
	    return TCL_ERROR;
	}

	int id;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	double x, y, w, h;
	Tcl_GetDoubleFromObj ( interp, objv[2], &x );
	Tcl_GetDoubleFromObj ( interp, objv[3], &y );
	Tcl_GetDoubleFromObj ( interp, objv[4], &w );
	Tcl_GetDoubleFromObj ( interp, objv[5], &h );

	viewport_geometry ( id, x, y, w, h );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_viewport_attachcamera ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_viewport_attachcamera id camid" );
	    return TCL_ERROR;
	}

	int id, camid;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetIntFromObj ( interp, objv[2], &camid ); 

	viewport_attachcamera ( id, camid );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_viewport_name ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_viewport_name id name" );
	    return TCL_ERROR;
	}

	int id, len;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	const char* name = Tcl_GetStringFromObj ( objv[2], &len);
	viewport_name ( id, name );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

// local mesh load, treat mesh as a single object
int tcl_mesh_load ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 2 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_mesh_load file" );
	    return TCL_ERROR;
	}

	int len;
	const char* file = Tcl_GetStringFromObj ( objv[1], &len );
	int id = mesh_load ( file );
	Tcl_Obj* rstobj = Tcl_NewIntObj(id);
	Tcl_SetObjResult ( interp, rstobj );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_mesh_save ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_mesh_save file meshid" );
	    return TCL_ERROR;
	}

	int len, id;
	const char* file = Tcl_GetStringFromObj ( objv[1], &len );
	Tcl_GetIntFromObj ( interp, objv[2], &id );
	mesh_save ( file, id );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_mesh_unload (ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 2 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_mesh_unload meshid" );
	    return TCL_ERROR;
	}

	int id;
	Tcl_GetIntFromObj ( interp, objv[1], &id );
	mesh_unload ( id );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_mesh_translate ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

int tcl_mesh_scale ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}


// remote mesh load, C/S architecture, client should maintian node structure
int tcl_add_child ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_add_child parent child" );
	    return TCL_ERROR;
	}

	int parent, child;
	Tcl_GetIntFromObj ( interp, objv[1], &parent );
	Tcl_GetIntFromObj ( interp, objv[1], &child );
	add_child ( parent, child );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_remove_child ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_remove_child parent child" );
	    return TCL_ERROR;
	}

	int parent, child;
	Tcl_GetIntFromObj ( interp, objv[1], &parent );
	Tcl_GetIntFromObj ( interp, objv[1], &child );
	remove_child ( parent, child );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}


// mesh
int tcl_mesh_create ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 1 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_mesh_create" );
	    return TCL_ERROR;
	}

	int id = mesh_create ();
	Tcl_Obj* rstobj = Tcl_NewIntObj(id);
	Tcl_SetObjResult ( interp, rstobj );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_mesh_delete ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

// layer
int tcl_layer_create ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 2 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_layer_create name" );
	    return TCL_ERROR;
	}

	int len;
	const char* name = Tcl_GetStringFromObj ( objv[1], &len );
	int id = layer_create ( name );
	Tcl_Obj* rstobj = Tcl_NewIntObj(id);
	Tcl_SetObjResult ( interp, rstobj );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_layer_delete ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

int tcl_layer_name ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_layer_name id name" );
	    return TCL_ERROR;
	}

	int id, len;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	const char* name = Tcl_GetStringFromObj ( objv[2], &len );
	layer_name ( id, name );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_layer_visible ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_layer_name id isvisible" );
	    return TCL_ERROR;
	}

	int id, isvisible;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetBooleanFromObj ( interp, objv[1], &isvisible ); 
	layer_visible ( id, isvisible );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}


// lod
int tcl_lod_create ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 1 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_lod_create" ); 
	    return TCL_ERROR;
	}

	int id = lod_create ();
	Tcl_Obj* rstobj = Tcl_NewIntObj(id);
	Tcl_SetObjResult ( interp, rstobj );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_lod_delete ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

int tcl_lod_delimiters ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_lod_delimiters id delims" ); 
	    return TCL_ERROR;
	}

	int id, len;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	const char* delims = Tcl_GetStringFromObj ( objv[2], &len );
	lod_delimiters ( id, delims );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}


// kdtree
int tcl_kdtree_create ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 1 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_kdtree_create" ); 
	    return TCL_ERROR;
	}

	int id = kdtree_create ();
	Tcl_Obj* rstobj = Tcl_NewIntObj(id);
	Tcl_SetObjResult ( interp, rstobj );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_kdtree_delete ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

// array
int tcl_array_create ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 1 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_array_create" ); 
	    return TCL_ERROR;
	}

	int id = array_create ();
	Tcl_Obj* rstobj = Tcl_NewIntObj(id);
	Tcl_SetObjResult ( interp, rstobj );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_array_delete ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

int tcl_array_rowcnt ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_array_rowcnt id cnt" ); 
	    return TCL_ERROR;
	}

	int id, cnt;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetIntFromObj ( interp, objv[2], &cnt ); 
	array_rowcnt ( id, cnt );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_array_columncnt ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_array_columncnt id cnt" ); 
	    return TCL_ERROR;
	}

	int id, cnt;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetIntFromObj ( interp, objv[2], &cnt ); 
	array_columncnt ( id, cnt );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_array_hlevelcnt ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 4 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_array_hlevelcnt id level cnt" ); 
	    return TCL_ERROR;
	}

	int id, level, cnt;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetIntFromObj ( interp, objv[2], &level ); 
	Tcl_GetIntFromObj ( interp, objv[3], &cnt ); 
	array_hlevelcnt ( id, level, cnt );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_array_vlevelcnt ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 4 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_array_vlevelcnt id level cnt" ); 
	    return TCL_ERROR;
	}

	int id, level, cnt;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetIntFromObj ( interp, objv[2], &level ); 
	Tcl_GetIntFromObj ( interp, objv[3], &cnt ); 
	array_vlevelcnt ( id, level, cnt );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_array_marginx ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 4 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_array_marginx id level space" ); 
	    return TCL_ERROR;
	}

	int id, level;
	double space;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetIntFromObj ( interp, objv[2], &level ); 
	Tcl_GetDoubleFromObj ( interp, objv[3], &space ); 
	array_marginx ( id, level, space );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}


int tcl_array_marginy ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 4 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_array_marginy id level space" ); 
	    return TCL_ERROR;
	}

	int id, level;
	double space;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetIntFromObj ( interp, objv[2], &level ); 
	Tcl_GetDoubleFromObj ( interp, objv[3], &space ); 
	array_marginy ( id, level, space );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}


// rectangle
int tcl_rectangle_create ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 1 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_rectangle_create" ); 
	    return TCL_ERROR;
	}

	int id = rectangle_create ();
	Tcl_Obj* rstobj = Tcl_NewIntObj(id);
	Tcl_SetObjResult ( interp, rstobj );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_rectangle_delete ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

int tcl_rectangle_size ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 4 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_rectangle_size id w h" ); 
	    return TCL_ERROR;
	}

	int id;
	double w, h;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetDoubleFromObj ( interp, objv[3], &w ); 
	Tcl_GetDoubleFromObj ( interp, objv[3], &h ); 
	rectangle_size ( id, w, h );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}


// transform
int tcl_transform_create ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 1 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_transform_create" ); 
	    return TCL_ERROR;
	}

	int id = transform_create ();
	Tcl_Obj* rstobj = Tcl_NewIntObj(id);
	Tcl_SetObjResult ( interp, rstobj );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_transform_delete ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

int tcl_transform_translate ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 5 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_transform_translate id tx ty tz" ); 
	    return TCL_ERROR;
	}

	int id;
	double x, y, z;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetDoubleFromObj ( interp, objv[3], &x ); 
	Tcl_GetDoubleFromObj ( interp, objv[3], &y ); 
	Tcl_GetDoubleFromObj ( interp, objv[3], &z ); 
	transform_translate ( id, x, y, z );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_transform_scale ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 5 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_transform_scale id sx sy sz" ); 
	    return TCL_ERROR;
	}

	int id;
	double x, y, z;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetDoubleFromObj ( interp, objv[3], &x ); 
	Tcl_GetDoubleFromObj ( interp, objv[3], &y ); 
	Tcl_GetDoubleFromObj ( interp, objv[3], &z ); 
	transform_scale ( id, x, y, z );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

// pickablegroup
int tcl_pickablegroup_create ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 1 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_pickablegroup_create" ); 
	    return TCL_ERROR;
	}

	int id = pickablegroup_create ();
	Tcl_Obj* rstobj = Tcl_NewIntObj(id);
	Tcl_SetObjResult ( interp, rstobj );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_pickablegroup_delete ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

int tcl_pickablegroup_name ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_pickablegroup_name id name" ); 
	    return TCL_ERROR;
	}

	int id, len;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	const char* name = Tcl_GetStringFromObj ( objv[2], &len);
	pickablegroup_name ( id, name );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}


// switchnode
int tcl_switchnode_create ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 1 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_switchnode_create" ); 
	    return TCL_ERROR;
	}

	int id = switchnode_create ();
	Tcl_Obj* rstobj = Tcl_NewIntObj(id);
	Tcl_SetObjResult ( interp, rstobj );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_switchnode_delete ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

int tcl_switchnode_props ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_switchnode_props id isvisible" ); 
	    return TCL_ERROR;
	}

	int id, isvisible;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetBooleanFromObj ( interp, objv[1], &isvisible ); 
	switchnode_props ( id, isvisible );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}


// groupnode
int tcl_groupnode_create ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 1 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_groupnode_create" ); 
	    return TCL_ERROR;
	}

	int id = groupnode_create ();
	Tcl_Obj* rstobj = Tcl_NewIntObj(id);
	Tcl_SetObjResult ( interp, rstobj );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_groupnode_delete ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

int tcl_groupnode_props ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_groupnode_props id name" ); 
	    return TCL_ERROR;
	}

	int id, len;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	const char* name = Tcl_GetStringFromObj ( objv[2], &len);
	groupnode_props ( id, name );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}


// text
int tcl_text_create ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 1 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_text_create" ); 
	    return TCL_ERROR;
	}

	int id = text_create ();
	Tcl_Obj* rstobj = Tcl_NewIntObj(id);
	Tcl_SetObjResult ( interp, rstobj );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_text_delete ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

int tcl_text_string ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_text_string id name" ); 
	    return TCL_ERROR;
	}

	int id, len;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	const char* name = Tcl_GetStringFromObj ( objv[2], &len);
	text_string ( id, name );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_text_font ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_text_font id fontid" ); 
	    return TCL_ERROR;
	}

	int id, fontid;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetIntFromObj ( interp, objv[2], &fontid ); 
	text_font ( id, fontid );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_text_anchor ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_text_anchor id anchor" ); 
	    return TCL_ERROR;
	}

	int id, anchor;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetIntFromObj ( interp, objv[2], &anchor ); 
	text_font ( id, anchor );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_text_justify ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_text_justify id justify" ); 
	    return TCL_ERROR;
	}

	int id, justify;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetIntFromObj ( interp, objv[2], &justify ); 
	text_font ( id, justify );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}


// font
int tcl_font_create ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try
    {
	if ( objc != 1 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_font_create" ); 
	    return TCL_ERROR;
	}

	int id = font_create ();
	Tcl_Obj* rstobj = Tcl_NewIntObj(id);
	Tcl_SetObjResult ( interp, rstobj );
	return TCL_OK;
    } catch ( std::exception& e ) {
//	Tcl_NewStringObj ( (const char*)(e.what()), e.what().size() );
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_font_delete ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    return TCL_OK;
}

int tcl_font_family ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try 
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_font_family id family" );
	    return TCL_ERROR;
	}

	int id, len;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	const char* family = Tcl_GetStringFromObj ( objv[2], &len);
	font_family ( id, family );
	return TCL_OK;
    } catch ( std::exception& e ) {
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

int tcl_font_size ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try 
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_font_size id size" );
	    return TCL_ERROR;
	}

	int id;
	double size;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetDoubleFromObj ( interp, objv[1], &size ); 
	font_size ( id, size );
	return TCL_OK;
    } catch ( std::exception& e ) {
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

/*PLAIN = 1, BOLD = 2, ITALIC = 3, BOLDITALIC = 4*/
int tcl_font_style ( ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[] )
{
    try 
    {
	if ( objc != 3 ) {
	    Tcl_WrongNumArgs ( interp, 0, objv, "tcl_font_style id style" );
	    return TCL_ERROR;
	}

	int id, style;
	Tcl_GetIntFromObj ( interp, objv[1], &id ); 
	Tcl_GetIntFromObj ( interp, objv[1], &style ); 
	font_style ( id, style );
	return TCL_OK;
    } catch ( std::exception& e ) {
	Tcl_SetResult ( interp, (char*)e.what(), TCL_VOLATILE );
	return TCL_ERROR;
    }
}

void createcommands ( Tcl_Interp* interp )
{
//    Tcl_CreateObjCommand ( interp, "rotate_gobo_ccwc", rotate_gobo_ccw, 0, 0 );
//    Tcl_CreateObjCommand ( interp, "add_fixture",         tcl_add_fixture             , 0, 0 );
    Tcl_CreateObjCommand ( interp, "camera_create",       tcl_camera_create           , 0, 0 );
    Tcl_CreateObjCommand ( interp, "camera_delete",       tcl_camera_delete           , 0, 0 );
    Tcl_CreateObjCommand ( interp, "camera_translate",   tcl_camera_translate         , 0, 0 );
    Tcl_CreateObjCommand ( interp, "camera_scale",        tcl_camera_scale            , 0, 0 );
    Tcl_CreateObjCommand ( interp, "camera_reset",        tcl_camera_reset            , 0, 0 );
    Tcl_CreateObjCommand ( interp, "camera_name",         tcl_camera_name             , 0, 0 );
    Tcl_CreateObjCommand ( interp, "viewport_create",    tcl_viewport_create          , 0, 0 );
    Tcl_CreateObjCommand ( interp, "viewport_delete",    tcl_viewport_delete          , 0, 0 );
    Tcl_CreateObjCommand ( interp, "viewport_geometr",   tcl_viewport_geometry        , 0, 0 );
    Tcl_CreateObjCommand ( interp, "viewport_attachcamera",tcl_viewport_attachcamera  , 0, 0 );
    Tcl_CreateObjCommand ( interp, "viewport_name",       tcl_viewport_name           , 0, 0 );
    Tcl_CreateObjCommand ( interp, "mesh_load",           tcl_mesh_load               , 0, 0 );
    Tcl_CreateObjCommand ( interp, "mesh_save",           tcl_mesh_save               , 0, 0 );
    Tcl_CreateObjCommand ( interp, "mesh_unload",         tcl_mesh_unload             , 0, 0 );
    Tcl_CreateObjCommand ( interp, "mesh_translate",     tcl_mesh_translate           , 0, 0 );
    Tcl_CreateObjCommand ( interp, "mesh_scale",          tcl_mesh_scale              , 0, 0 );
    Tcl_CreateObjCommand ( interp, "add_child",           tcl_add_child               , 0, 0 );
    Tcl_CreateObjCommand ( interp, "remove_child",        tcl_remove_child            , 0, 0 );
    Tcl_CreateObjCommand ( interp, "mesh_create",         tcl_mesh_create             , 0, 0 );
    Tcl_CreateObjCommand ( interp, "mesh_delete",         tcl_mesh_delete             , 0, 0 );
    Tcl_CreateObjCommand ( interp, "layer_create",        tcl_layer_create            , 0, 0 );
    Tcl_CreateObjCommand ( interp, "layer_delete",        tcl_layer_delete            , 0, 0 );
    Tcl_CreateObjCommand ( interp, "layer_name",          tcl_layer_name              , 0, 0 );
    Tcl_CreateObjCommand ( interp, "layer_visible",       tcl_layer_visible           , 0, 0 );
    Tcl_CreateObjCommand ( interp, "lod_create",          tcl_lod_create              , 0, 0 );
    Tcl_CreateObjCommand ( interp, "lod_delete",          tcl_lod_delete              , 0, 0 );
    Tcl_CreateObjCommand ( interp, "lod_delimiters",     tcl_lod_delimiters           , 0, 0 );
    Tcl_CreateObjCommand ( interp, "kdtree_create",       tcl_kdtree_create           , 0, 0 );
    Tcl_CreateObjCommand ( interp, "kdtree_delete",       tcl_kdtree_delete           , 0, 0 );
    Tcl_CreateObjCommand ( interp, "array_create",        tcl_array_create            , 0, 0 );
    Tcl_CreateObjCommand ( interp, "array_delete",        tcl_array_delete            , 0, 0 );
    Tcl_CreateObjCommand ( interp, "array_rowcnt",        tcl_array_rowcnt            , 0, 0 );
    Tcl_CreateObjCommand ( interp, "array_columncnt",    tcl_array_columncnt          , 0, 0 );
    Tcl_CreateObjCommand ( interp, "array_hlevelcnt",    tcl_array_hlevelcnt          , 0, 0 );
    Tcl_CreateObjCommand ( interp, "array_vlevelcnt",    tcl_array_vlevelcnt          , 0, 0 );
    Tcl_CreateObjCommand ( interp, "array_marginx",       tcl_array_marginx           , 0, 0 );
    Tcl_CreateObjCommand ( interp, "array_marginy",       tcl_array_marginy           , 0, 0 );
    Tcl_CreateObjCommand ( interp, "rectangle_create",   tcl_rectangle_create         , 0, 0 );
    Tcl_CreateObjCommand ( interp, "rectangle_delete",   tcl_rectangle_delete         , 0, 0 );
    Tcl_CreateObjCommand ( interp, "rectangle_size",     tcl_rectangle_size           , 0, 0 );
    Tcl_CreateObjCommand ( interp, "transform_create",   tcl_transform_create         , 0, 0 );
    Tcl_CreateObjCommand ( interp, "transform_delete",   tcl_transform_delete         , 0, 0 );
    Tcl_CreateObjCommand ( interp, "transform_translate",  tcl_transform_translate    , 0, 0 );
    Tcl_CreateObjCommand ( interp, "transform_scale",             tcl_transform_scale , 0, 0 );
    Tcl_CreateObjCommand ( interp, "pickablegroup_create", tcl_pickablegroup_create   , 0, 0 );
    Tcl_CreateObjCommand ( interp, "pickablegroup_delete", tcl_pickablegroup_delete   , 0, 0 );
    Tcl_CreateObjCommand ( interp, "pickablegroup_name",   tcl_pickablegroup_name     , 0, 0 );
    Tcl_CreateObjCommand ( interp, "switchnode_create",    tcl_switchnode_create      , 0, 0 );
    Tcl_CreateObjCommand ( interp, "switchnode_delete",    tcl_switchnode_delete      , 0, 0 );
    Tcl_CreateObjCommand ( interp, "switchnode_props",     tcl_switchnode_props       , 0, 0 );
    Tcl_CreateObjCommand ( interp, "groupnode_create",     tcl_groupnode_create       , 0, 0 );
    Tcl_CreateObjCommand ( interp, "groupnode_delete",     tcl_groupnode_delete       , 0, 0 );
    Tcl_CreateObjCommand ( interp, "groupnode_props",             tcl_groupnode_props , 0, 0 );
    Tcl_CreateObjCommand ( interp, "text_create",         tcl_text_create             , 0, 0 );
    Tcl_CreateObjCommand ( interp, "text_delete",         tcl_text_delete             , 0, 0 );
    Tcl_CreateObjCommand ( interp, "text_string",         tcl_text_string             , 0, 0 );
    Tcl_CreateObjCommand ( interp, "text_font",           tcl_text_font               , 0, 0 );
    Tcl_CreateObjCommand ( interp, "text_anchor",         tcl_text_anchor             , 0, 0 );
    Tcl_CreateObjCommand ( interp, "text_justify",        tcl_text_justify            , 0, 0 );
    Tcl_CreateObjCommand ( interp, "font_create",         tcl_font_create             , 0, 0 );
    Tcl_CreateObjCommand ( interp, "font_delete",         tcl_font_delete             , 0, 0 );
    Tcl_CreateObjCommand ( interp, "font_family",         tcl_font_family             , 0, 0 );
    Tcl_CreateObjCommand ( interp, "font_size",           tcl_font_size               , 0, 0 );
    Tcl_CreateObjCommand ( interp, "font_style",           tcl_font_style             , 0, 0 );               
}
