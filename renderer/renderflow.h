#ifndef _RENDERFLOW_H_
#define _RENDERFLOW_H_

#include <string>
#include <map>
#include <algorithm>

#include "scenemgr.h"
#include "renderlist.h"
#include "cameraortho.h"
#include "viewport.h"
#include "mat4.h"
#include "renderfunctor.h"
#include "kdtree.h"

using namespace std;
class Loding : public map<int,vector<SpatialObjectMgr*> >
{
public:
    static Loding& getInst() 
    {
        static Loding inst;
        return inst;
    }
    void operator() ( int camid, float v ) 
    {
        if ( find ( camid ) == end() )
            (*this)[camid] = vector<SpatialObjectMgr*>();

        (*this)[camid].clear();

        for ( SceneMgr::iterator pp=SceneMgr::getInst().begin(); 
              pp!=SceneMgr::getInst().end(); ++pp ) {
            if ( (*pp)->isVisible () && !(*pp)->empty() ) {
                (*this)[camid].push_back ( (*pp)->lod()->selectPresentation (v) );
            }
        }
    }
private:
    Loding () {}
};

class Culling : public map<int, RenderList*>
{
public:
    typedef RenderListMgr::iterator iterator;
    static Culling& getInst() 
    {
        static Culling inst;
        return inst;
    }
    void operator() ( int camid, const BBox& box, vector<SpatialObjectMgr*>& soms/*Spatial object mgrs*/ ) 
    {
        static Rectanglef rect;
        typedef vector<SpatialObjectMgr*> SpatialObjectMgrs;
        RenderListMgr::iterator pp = find ( camid );
        RenderList* renderlist=0;
        if ( pp == end() )
            (*this)[camid] = renderlist = new RenderList();
        else
            renderlist = (*pp).second;
        renderlist->reset();

        for ( SpatialObjectMgrs::iterator pp=soms.begin(); pp!=soms.end(); ++pp )
        {
            (*pp)->intersect ( box, back_inserter(*renderlist) );
#ifdef _USESTATISTIC_
            qDebug ( "the culling volumn min=(%f,%f,%f), max=(%f,%f,%f)", 
                     box.min().x(), box.min().y(), box.min().z(),
                     box.max().x(), box.max().y(), box.max().z() );
            qDebug ( "%s", (*pp)->intersectstatistic ().c_str() );
#endif
            // insert bbox
            CameraOrtho* cam = CameraMgr::getInst()[camid];
            if ( cam )
            {
                BBox box = cam->viewvolume();
                rect.setRect ( box.min().x(), box.min().y(), 
                               box.max().x() - box.min().x(),
                               box.max().y() - box.min().y() );
                renderlist->push_back ( &rect );
            }
        }
    }
//     RenderListMgr::iterator findRenderList ( int camid ) { return _renderlistmgr.find ( camid ); }
//     iterator begin() { return _renderlistmgr.begin(); }
//     iterator end() { return _renderlistmgr.end(); }
private:
    Culling () {}
//     RenderListMgr _renderlistmgr;
};

class Rendering
{
public:
    Rendering ( const RenderList& renderlist, RenderOption& opt ) {
        for ( RenderList::const_iterator pp=renderlist.begin(); pp!=renderlist.end(); ++pp ) {
            QtRenderFunctor func ( &opt );
            (*pp)->accept ( func );
        }
    }
};

class RenderFlow
{
public:
    RenderFlow (RenderOption& opt) {
        // loding
        Loding& loding = Loding::getInst();
        CameraMgr& cammgr = CameraMgr::getInst();
        ViewportMgr& vpmgr = ViewportMgr::getInst();
        for ( CameraMgr::iterator pp=cammgr.begin(); pp!=cammgr.end(); ++pp ) {
            CameraOrtho* cam = pp->second;
            if ( cam && cam->dirty() ) {
                loding ( pp->first, cam->mvmatrix().sx() );
            }
        }

        // culling
        Culling& culling = Culling::getInst();
        for ( Loding::iterator pp=loding.begin(); pp!=loding.end(); ++pp ) {
            CameraOrtho* cam =cammgr[pp->first];
            if ( cam && cam->dirty() ) {
                culling ( pp->first, cam->viewvolume(), pp->second );
                cam->dirty( false );
            }
        }

        // rendering
        for ( ViewportMgr::iterator pp0=vpmgr.begin(); pp0!=vpmgr.end(); ++pp0 ) {
            Viewport& viewport = *pp0->second;
            //if ( viewport.dirty() ) {
            int camid = viewport.cameraid();
            CameraOrtho* cam = viewport.camera();
            if ( cam )
            {
                Culling::iterator pp = culling.find ( camid );
                if ( pp != culling.end() ) {
                    mat4f old = opt.matrix;
                    opt.matrix = viewport.vpmatrix() * cam->mvmatrix();
                    Rendering ( *(pp->second), opt );
                    opt.matrix = old;
                }
                //viewport.dirty( false );
            }
        }
    }
};

class RenderPass
{
    static const int END               = 0;
    static const int CAMERACHECKING    = 1;
    static const int VIEWPORTCHECKING  = 2;
    static const int LODING            = 3;
    static const int CULLING           = 4;
    static const int RENDERING         = 5;
public:
    RenderPass ( viewport& vp, RenderOption& opt )
    {
        CameraOrtho* cam = vp.camera();
        int camid = vp.cameraid();

        int state = CAMERACHECKING;
        while ( state != END )
        {
            switch ( state )
            {
            case CAMERACHECKING:
                if ( cam->dirty() )
                    state = LODING;
                else
                    state = VIEWPORTCHECKING;
                break;
            case VIEWPORTCHECKING:
                if ( vp.dirty() )
                    state = RENDERING;
                else
                    state = END;
                break;
            case LODING:
                Loding::getInst()( camid, cam->mvmatrix().sx() );
                state = CULLING;
                break;
            case CULLING:
                Culling::getInst()( camid, cam->viewvolume(), Loding::getInst()[camdid] );
                cam->dirty( false );
                state = RENDERING;
                break;
            case RENDERING:
                opt.matrix = viewport.vpmatrix() * cam->mvmatrix();
                Rendering ( *(Culling::getInst()[camid]), opt );
                opt.matrix = old;
                state = END;
                break;
            }
        }
    }
}

#endif
