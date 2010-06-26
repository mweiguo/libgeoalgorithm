#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "agef_global.h"
extern "C"
{

    /*********************************/
    /******** TCL COMMANDS REG *******/
    /*********************************/
    struct Tcl_Interp;
    void AGEF_EXPORT register_tclcmds ( Tcl_Interp* interp );

    /*********************************/
    /********** WINDOW INIT **********/
    /*********************************/
    void AGEF_EXPORT init_windowsystem ();

    /*********************************/
    /******* CAMERA MANAGEMENT *******/
    /*********************************/
    int AGEF_EXPORT camera_create ( const char* name );
    void AGEF_EXPORT camera_translate ( int id, float tx, float ty, float tz );
    void AGEF_EXPORT camera_scale ( int id, float scale );
    void AGEF_EXPORT camera_reset ( int id );
    void AGEF_EXPORT camera_name ( int id, const char* name );
    float AGEF_EXPORT find_view ( float* min, float* max, float percentOfView, int camid, int vpid );

    /*********************************/
    /****** VIEWPORT MANAGEMENT ******/
    /*********************************/
    int AGEF_EXPORT viewport_create ( const char* name );
    void AGEF_EXPORT viewport_geometry ( int id, int x, int y, int w, int h );
    void AGEF_EXPORT viewport_attachcamera ( int id, int camid );
    void AGEF_EXPORT viewport_name ( int id, const char* name );
    void AGEF_EXPORT viewport_dirty ( int id );
    class QPainter;
    void AGEF_EXPORT viewport_update ( int id, QPainter& painter );

    /*********************************/
    /************* WINDOW ************/
    /*********************************/
    void AGEF_EXPORT viewport_add ( int id );
    void AGEF_EXPORT viewport_delete ( int id );
    void AGEF_EXPORT sgwindow_update ( int id );

    /*********************************/
    /************** IO ***************/
    /*********************************/
    // local mesh load, treat mesh as a single object
    int AGEF_EXPORT mesh_load ( const char* file );
    void AGEF_EXPORT mesh_save ( const char* file, int meshid );
    void AGEF_EXPORT unload_node (int id);
    void AGEF_EXPORT mesh_translate ( int id, float tx, float ty, float tz );
    void AGEF_EXPORT mesh_scale ( int id, float scale );

    /*********************************/
    /*********** diagnose ************/
    /*********************************/
    void AGEF_EXPORT dump_node ( int id, const char* filename );

    /*********************************/
    /************ QUERY **************/
    /*********************************/
    void AGEF_EXPORT get_bbox ( int id, float* min, float* max );
    void AGEF_EXPORT get_scenepos ( int vpid, float* viewportCoord, float* sceneCoord );

    /*********************************/
    /************* PICK **************/
    /*********************************/
    // since the system use LOD, and in different level, objects in the scene
    // may be different, so here need parameter camid.
    // when function return. data store pick ids, returning result is the size of ids
    int AGEF_EXPORT pick ( float x, float y, float z, int camid, int* data );

    /*********************************/
    /********** build nodes **********/
    /*********************************/
    // remote mesh load, C/S architecture, client should maintain node structure
    void AGEF_EXPORT add_child ( int parent, int child );
    void AGEF_EXPORT remove_child ( int preant, int child );
    void AGEF_EXPORT node_delete ( int id );
    void AGEF_EXPORT set_userdata ( int id, void* data );
    void* get_userdata ( int id );
    void AGEF_EXPORT update_bbox ( int id );
    // color access
    void AGEF_EXPORT set_bordercolori ( int id, unsigned int color, bool isByGroup/*=true*/ );
    void AGEF_EXPORT set_fillcolori ( int id, unsigned int color, bool isByGroup );
    void AGEF_EXPORT set_fgcolori ( int id, unsigned int color );
    void AGEF_EXPORT set_bgcolori ( int id, unsigned int color );
    void AGEF_EXPORT set_bordercolors ( int id, const char* color, bool isByGroup );
    void AGEF_EXPORT set_fillcolors ( int id, const char* color, bool isByGroup );
    // mesh
    int AGEF_EXPORT mesh_create ();
    // layer
    int AGEF_EXPORT layer_create ( const char* name="" );
    void AGEF_EXPORT layer_name ( int id, const char* name );
    void AGEF_EXPORT layer_visible ( int id, bool isVisible );
    // lod
    int AGEF_EXPORT lod_create ();
    void AGEF_EXPORT lod_delimiters ( int id, const char* delims );
    // kdtree
    int AGEF_EXPORT kdtree_create ();
    void AGEF_EXPORT kdtree_build ( int id );
    // array
    int AGEF_EXPORT array_create ();
    void AGEF_EXPORT array_rowcnt ( int id, int cnt );
    void AGEF_EXPORT array_columncnt ( int id, int cnt );
    void AGEF_EXPORT array_hlevelcnt ( int id, int level, int cnt );
    void AGEF_EXPORT array_vlevelcnt ( int id, int level, int cnt );
    void AGEF_EXPORT array_marginx ( int id, int level, float space );
    void AGEF_EXPORT array_marginy ( int id, int level, float space );
    void AGEF_EXPORT expand_arraynode ( int id );
    // rectangle
    int AGEF_EXPORT rectangle_create ();
    void AGEF_EXPORT rectangle_size ( int id, float w, float h );
    // transform
    int AGEF_EXPORT transform_create ();
    void AGEF_EXPORT transform_translate3f ( int id, float tx, float ty, float tz );
    void AGEF_EXPORT transform_translates ( int id, const char* str );
    //void AGEF_EXPORT transform_scale ( int id, float sx, float sy, float sz );
    void AGEF_EXPORT transform_scale ( int id, const char* str );
    // pickablegroup
    int AGEF_EXPORT pickablegroup_create ();
    void AGEF_EXPORT pickablegroup_name ( int id, const char* name );
    // switchnode
    int AGEF_EXPORT switchnode_create ();
    void AGEF_EXPORT switchnode_visible ( int id, bool isVisible );
    // groupnode
    int AGEF_EXPORT groupnode_create ();
    void AGEF_EXPORT groupnode_name ( int id, const char* name );
    // text
    int AGEF_EXPORT text_create ( const char* str= "" );
    void AGEF_EXPORT text_string ( int id, const char* str );
    void AGEF_EXPORT text_font ( int id, int fontid );
    //  1     2     3
    //  4     5     6
    //  7     8     9
    void AGEF_EXPORT text_anchor ( int id, int anchor );
    //  1     2     3
    //  4     5     6
    //  7     8     9
    void AGEF_EXPORT text_justify ( int id, int justify );
    // font
    int AGEF_EXPORT font_create ();
    void AGEF_EXPORT font_family ( int id, const char* f );
    void AGEF_EXPORT font_size ( int id, float size );
    /*NORMAL = 1, ITALIC = 3, UNDERSTRIKE = 4*/
    void AGEF_EXPORT font_style ( int id, int style );
    void AGEF_EXPORT font_weight ( int id, int weight );
    //void font_color ( int id, const char* color );

    // line
    int AGEF_EXPORT line_create ();
    void AGEF_EXPORT line_points ( int id, float x1, float y1, float x2, float y2 );
    void AGEF_EXPORT line_point ( int id, float x, float y, bool isFirst );
}
#endif
