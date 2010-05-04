#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include <string>
#include "vec2.h"
#include "cameraortho.h"
#include "nodemgr.h"

class Viewport : public SGNode
{
public:
    void attachcamera ( int camid ) {_camid = camid;}
    CameraOrtho* camera() const {
        return NodeMgr::getInst().getNodePtr<CameraOrtho>(_camid);
        //CameraMgr& mgr = CameraMgr::getInst();
        //CameraMgr::iterator pp = mgr.find (_camid);
        //if ( pp == mgr.end() )
        //    return NULL;
        //return pp->second;
    }
    int cameraid() const { return _camid; }
    //RnederList& getRenderList ( const string& cameraname );
    bool dirty() { return _dirty; }
    void dirty( bool v ) { _dirty = v; }
    Viewport ( const string& name="default", int x=0, int y=0, int w=400, int h=300 ) : 
    _name(name), _pos(x,y), _size(w,h) 
    {
        _dirty = true;
        //attachcamera ( CameraMgr::getInst().getDefaultCamera() );
        resetVPMatrix ();
    }
    void position ( int orgx, int orgy ) { _pos.x(orgx); _pos.y(orgy); }
    const vec2i& size() const { return _size; }
    void size ( int w, int h ) { _size.w(w); _size.h(h); dirty(true); resetVPMatrix(); }
    const mat4f& vpmatrix () const { return _vpmatrix; }
    void update () 
    {
        CameraOrtho* cam = camera();
        if ( cam )
            cam->dirty(true);
    }
    void name ( const string& nm ) { _name = nm; }
    const string& name () const { return _name; }
    string name () { return _name; }
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~Viewport () {}
private:
    // reset view port matrix
    void resetVPMatrix () 
    {
        _vpmatrix.normalize();
        _vpmatrix.sx ( _size.w() / 2.f );
        _vpmatrix.sy ( _size.h() / -2.f );
        _vpmatrix.dx ( _size.w() / 2.f );
        _vpmatrix.dy ( _size.h() / 2.f );
    }
private:
    string _name;
    vec2i _pos, _size;
    int _camid;
    bool _dirty;
    mat4f _vpmatrix;
};

//typedef NodeMgr<Viewport>       ViewportMgr;

#endif

