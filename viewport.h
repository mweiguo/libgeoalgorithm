#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include <string>
#include <vec2.h>
#include "cameraortho.h"
class Viewport
{
public:
  void attachcamera ( CameraOrtho* camera ) {_camera = camera;}
  CameraOrtho* camera() const { return _camera; }
  //RnederList& getRenderList ( const string& cameraname );
  bool dirty() { return _dirty; }
  void dirty( bool v ) { _dirty = v; }
  Viewport ( const string& name, int x=0, int y=0, int w=400, int h=300 ) : _name(name), _pos(x,y), _size(w,h) {
    _dirty = true;
    attachcamera ( CameraMgr::getInst().getDefaultCamera() );
    updateVPMatrix ();
  }
  void position ( int orgx, int orgy ) { _pos.x(orgx); _pos.y(orgy); }
  const vec2i& size() const { return _size; }
  void size ( int w, int h ) { _size.w(w); _size.h(h); dirty(true); updateVPMatrix(); }
  const mat4f& vpmatrix () const { return _vpmatrix; }
  void update () {
    CameraOrtho* cam = CameraMgr::getInst().getDefaultCamera();
    cam->dirty(true);
  }
private:
  void updateVPMatrix () {
    _vpmatrix.normalize();
    _vpmatrix.sx ( _size.w() / 2.f );
    _vpmatrix.sy ( _size.h() / -2.f );
    _vpmatrix.dx ( _size.w() / 2.f );
    _vpmatrix.dy ( _size.h() / 2.f );
  }
private:
  string _name;
  vec2i _size, _pos;
  CameraOrtho* _camera;
  bool _dirty;
  mat4f _vpmatrix;
};

class ViewportMgr
{
public:
  typedef map<int, Viewport*>::iterator iterator;
  //static const char* DefViewportName = "viewport0";
  static ViewportMgr& getInst()
  {
    static ViewportMgr inst;
    return inst;
  }

  Viewport* addViewport ( int id ) 
  { 
    Viewport* pp = NULL;
    if ( _viewports.find ( id ) == _viewports.end() )
      _viewports[id] = pp = new Viewport("default");
    return pp;
  }
  void erase ( int id )
  {
    _viewports.erase ( id );
  }
  iterator begin() { return _viewports.begin(); }
  iterator end() { return _viewports.end(); }
  Viewport* operator[] ( int id ) 
  { 
    iterator pp = _viewports.find ( id );
    if ( pp == _viewports.end() )
      return NULL;
    return pp->second;
  }
  //const Viewport& operator[] ( const string& vpname ) const { return *(_viewports[vpname]); }
private:
  ViewportMgr() {
    addViewport ( "viewport0" );
  }
private:
  map<int, Viewport*> _viewports;
};


#endif

