#ifndef _CAMERAORTHO_H_
#define _CAMERAORTHO_H_

#include "mat4.h"
#include "vec4.h"
#include "bbox.h"
#include "nodemgr.h"

class CameraOrtho : public SGNode
{
public:
    CameraOrtho (const string& name="default");
    const string& name() const { return _name; }
    void name(const string& n) { _name = n; }
    bool dirty() { return _dirty; }
    void dirty( bool v ) { _dirty = v; }
    
        
    // bbox in object-coord;
    BBox viewvolume () {
        BBox box;
        //box.init ( vec4f(-1, -1, -1, 1).xyz() );
        //box.expandby ( vec4f(1, 1, -2, 1 ).xyz() );
        box.init ( (_inversemvmatrix * vec4f(-1, -1, -1, 1)).xyz() );
        box.expandby ( (_inversemvmatrix * vec4f(1, 1, -2, 1 )).xyz() );
        return box;
    }

    // behaviors
    void reset ();
    // these interface only modify model-view matrix and  do not support anisotropic scale
    void zoom ( float scale ); 
    void translate ( const vec3f& offset ); 

    mat4f& mvmatrix () { return _mvmatrix; }
    // return value in object-coord
    vec3f position () { return ( _inversemvmatrix * vec4f(0,0,0,0)).xyz(); };
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~CameraOrtho () {}

private:
    string _name;
    mat4f _mvmatrix;
    mat4f _inversemvmatrix;

    bool _dirty;
};

inline CameraOrtho::CameraOrtho (const string& name) : _name(name)
{
    dirty ( true );
}

inline void CameraOrtho::reset ()
{
    _mvmatrix.normalize();
    _inversemvmatrix.normalize();
    dirty ( true );
}

inline void CameraOrtho::zoom ( float scale )
{
    if ( scale < 0 )
        scale = -1/scale;
    if ( scale == 1 )
        return;
    mat4f smat = mat4f::scale_matrix ( scale, scale, scale );
    scale = 1.f/scale;
    mat4f invertsmat = mat4f::scale_matrix ( scale, scale, scale );

    _mvmatrix = smat * _mvmatrix;
    _inversemvmatrix = _inversemvmatrix * invertsmat;

    dirty ( true );
}

inline void CameraOrtho::translate ( const vec3f& offset )
{
    mat4f tmat = mat4f::translate_matrix ( offset.x(), offset.y(), offset.z() );
    mat4f inverttmat = mat4f::translate_matrix ( -offset.x(), -offset.y(), -offset.z() );

    _mvmatrix = tmat * _mvmatrix;
    _inversemvmatrix = _inversemvmatrix * inverttmat;
    if ( offset != vec3f(0,0,0) )
        dirty ( true );
}

typedef NodeMgr<CameraOrtho>      CameraMgr;
#endif
