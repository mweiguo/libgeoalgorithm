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
//#include "nodevisible.h"
#include "culling.h"
#include "nodemgr.h"

#include "nodedumper.h"

using namespace std;

class Rendering
{
public:
    Rendering ( RenderList& renderlist, RenderOption& opt ) 
    {
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
                //opt.matrix = cam->mvmatrix();
                //opt.scale = cam->mvmatrix().sx();
                opt.painter->setMatrix ( QMatrix( opt.matrix.m00(), opt.matrix.m10(), opt.matrix.m01(), opt.matrix.m11(), opt.matrix.dx(), opt.matrix.dy() ) );
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
