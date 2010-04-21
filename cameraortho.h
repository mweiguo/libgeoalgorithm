#ifndef _CAMERAORTHO_H_
#define _CAMERAORTHO_H_

#include "mat4.h"
#include "vec4.h"
#include "bbox.h"

class CameraOrtho
{
public:
    CameraOrtho (const string& name);
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
    scale = 1.0/scale;
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
	//_mvmatrix.dx( _mvmatrix.dx() + offset.x() );
 //   _mvmatrix.dy( _mvmatrix.dy() + offset.y() );
 //   _mvmatrix.dz( _mvmatrix.dz() + offset.z() );

 //   _inversemvmatrix.dx( _inversemvmatrix.dx() - offset.x() );
 //   _inversemvmatrix.dy( _inversemvmatrix.dy() - offset.y() );
 //   _inversemvmatrix.dz( _inversemvmatrix.dz() - offset.z() );
    if ( offset != vec3f(0,0,0) )
        dirty ( true );
}

class CameraMgr
{
 public:
    typedef map<string, CameraOrtho*>::iterator iterator;
    typedef map<string, CameraOrtho*>::const_iterator const_iterator;
    static CameraMgr& getInst() {
        static CameraMgr inst;
        return inst;
    }
    CameraOrtho* addCamera ( const string& name ) {
        CameraOrtho* pp = NULL;
        if ( _cameras.find ( name ) == _cameras.end() )
            _cameras[name] = pp = new CameraOrtho(name);
        return pp;
    }
    iterator begin() { return _cameras.begin(); }
    iterator end() { return _cameras.end(); }
    CameraOrtho* operator[] (const string& cameraname) {
        iterator pp = _cameras.find ( cameraname );
        if ( pp == _cameras.end() )
            return NULL;
        return pp->second;
    }
    CameraOrtho* operator[] (const string& cameraname) const {
        const_iterator pp = _cameras.find ( cameraname );
        if ( pp == _cameras.end() )
            return NULL;
        return pp->second;
    }
    CameraOrtho* getDefaultCamera () const {
		return _defcam;
	}

 private:
    CameraMgr() {
        _defcam = addCamera ( "camera0" );
    }
 private:
    map<string, CameraOrtho*> _cameras;
	CameraOrtho* _defcam;
};

#endif
