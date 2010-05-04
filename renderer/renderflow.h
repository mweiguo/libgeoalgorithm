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
#include "nodevisible.h"
#include "culling.h"
#include "nodemgr.h"

using namespace std;

class Rendering
{
public:
    Rendering ( RenderList& renderlist, RenderOption& opt ) {
        for ( RenderList::const_iterator pp=renderlist.begin(); pp!=renderlist.end(); ++pp ) {
            QtRenderFunctor func ( &opt );
            (*pp)->accept ( func );
        }

	// clean up renderlist
        for ( RenderList::const_iterator pp=renderlist.begin(); pp!=renderlist.end(); ++pp )
	    delete *pp;
	renderlist.reset ();
    }
};

//class RenderFlow
//{
//public:
//    RenderFlow (RenderOption& opt) {
//        // loding
//        Loding& loding = Loding::getInst();
//        CameraMgr& cammgr = CameraMgr::getInst();
//        ViewportMgr& vpmgr = ViewportMgr::getInst();
//        for ( CameraMgr::iterator pp=cammgr.begin(); pp!=cammgr.end(); ++pp ) {
//            CameraOrtho* cam = pp->second;
//            if ( cam && cam->dirty() ) {
//                loding ( pp->first, cam->mvmatrix().sx() );
//            }
//        }
//
//        // culling
//        Culling& culling = Culling::getInst();
//        for ( Loding::iterator pp=loding.begin(); pp!=loding.end(); ++pp ) {
//            CameraOrtho* cam =cammgr[pp->first];
//            if ( cam && cam->dirty() ) {
//                culling ( pp->first, cam->viewvolume(), pp->second );
//                cam->dirty( false );
//            }
//        }
//
//        // rendering
//        for ( ViewportMgr::iterator pp0=vpmgr.begin(); pp0!=vpmgr.end(); ++pp0 ) {
//            Viewport& viewport = *pp0->second;
//            //if ( viewport.dirty() ) {
//            int camid = viewport.cameraid();
//            CameraOrtho* cam = viewport.camera();
//            if ( cam )
//            {
//                Culling::iterator pp = culling.find ( camid );
//                if ( pp != culling.end() ) {
//                    mat4f old = opt.matrix;
//                    opt.matrix = viewport.vpmatrix() * cam->mvmatrix();
//                    Rendering ( *(pp->second), opt );
//                    opt.matrix = old;
//                }
//                //viewport.dirty( false );
//            }
//        }
//    }
//};

class RenderFlow
{
    static const int END               = 0;
    static const int CAMERACHECKING    = 1;
    static const int VIEWPORTCHECKING  = 2;
//    static const int LODING            = 3;
    static const int CULLING           = 4;
    static const int RENDERING         = 5;
public:
    RenderFlow ( Viewport& vp, RenderOption& opt )
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
                {
                    state = CULLING;
                    cam->dirty(false);
                }
                else
                    state = VIEWPORTCHECKING;
                break;
            case VIEWPORTCHECKING:
                if ( vp.dirty() )
                {
                    state = RENDERING;
                    vp.dirty(false);
                }
                else
                    state = END;
                break;
            case CULLING:
                Culling::getInst()( camid, cam->viewvolume(), NodeMgr::getInst().root() );
                cam->dirty( false );
                state = RENDERING;
                break;
            case RENDERING:
                {
                    mat4f old = opt.matrix;
                    opt.matrix = vp.vpmatrix() * cam->mvmatrix();
                    Rendering ( *(Culling::getInst()[camid]), opt );
                    opt.matrix = old;
                }
                state = END;
                break;
            }
        }
    }
};

#endif
