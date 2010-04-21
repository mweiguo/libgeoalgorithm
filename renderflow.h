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
class Loding
{
public:
    typedef map<string,vector<SpatialObjectMgr*>>::iterator iterator;
    static Loding& getInst() 
    {
        static Loding inst;
        return inst;
    }
    void operator() ( const string& camname, float v ) 
    {
		if ( _scenemgr.find ( camname ) == _scenemgr.end() )
			_scenemgr[camname] = vector<SpatialObjectMgr*>();

		_scenemgr[camname].clear();

       for ( SceneMgr::iterator pp=SceneMgr::getInst().begin(); 
              pp!=SceneMgr::getInst().end(); ++pp ) {
            if ( (*pp)->isVisible () && !(*pp)->empty() ) {
                //if ( _scenemgr.find ( camname ) == _scenemgr.end() )
                //    _scenemgr[camname] = vector<SpatialObjectMgr*>();
				_scenemgr[camname].push_back ( (*pp)->lod()->selectPresentation (v) );
            }
        }

        //_scenemgr[camname] = LodMgr::getInst().selectPresentation ( dist );
    }
    iterator begin() { return _scenemgr.begin(); }
    iterator end() { return _scenemgr.end(); }
private:
    Loding () {}
    map<string,vector<SpatialObjectMgr*>> _scenemgr;
};

class Culling
{
public:
    typedef RenderListMgr::iterator iterator;
    static Culling& getInst() 
    {
        static Culling inst;
        return inst;
    }
    void operator() ( const string& camname, const BBox& box, vector<SpatialObjectMgr*>& soms/*Spatial object mgrs*/ ) 
    {
		static Rectanglef rect;
        typedef vector<SpatialObjectMgr*> SpatialObjectMgrs;
        RenderListMgr::iterator pp = _renderlistmgr.find ( camname );
        RenderList* renderlist=0;
        if ( pp == _renderlistmgr.end() )
            _renderlistmgr[camname] = renderlist = new RenderList();
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
			CameraOrtho* cam = CameraMgr::getInst()[camname];
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
    RenderListMgr::iterator findRenderList ( const string& cameraname ) { return _renderlistmgr.find ( cameraname ); }
    iterator begin() { return _renderlistmgr.begin(); }
    iterator end() { return _renderlistmgr.end(); }
private:
    RenderListMgr _renderlistmgr;
};

class Rendering
{
public:
    Rendering ( const RenderList& renderlist, RenderOption& opt ) {
        for ( RenderList::const_iterator pp=renderlist.begin(); 
              pp!=renderlist.end(); 
              ++pp ) {
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
        for ( CameraMgr::iterator pp=CameraMgr::getInst().begin(); 
              pp!=CameraMgr::getInst().end(); 
              ++pp ) {
            CameraOrtho& cam = *(pp->second);
            if ( cam.dirty() ) {
				loding ( cam.name(), cam.mvmatrix().sx() );
            }
        }

        // culling
		Culling& culling = Culling::getInst();
        for ( Loding::iterator pp=loding.begin(); 
              pp!=loding.end(); 
              ++pp ) {
            CameraOrtho* cam = CameraMgr::getInst()[pp->first];
            if ( cam && cam->dirty() ) {
                culling ( cam->name(), cam->viewvolume(), pp->second );
                cam->dirty( false );
            }
        }

        // rendering
        for ( ViewportMgr::iterator pp=ViewportMgr::getInst().begin();
              pp!=ViewportMgr::getInst().end();
              ++pp ) {
            Viewport& viewport = *pp->second;
            //if ( viewport.dirty() ) {
                CameraOrtho* cam = viewport.camera();
				if ( cam ) {
					Culling::iterator pp = culling.findRenderList(cam->name());
					if ( pp != culling.end() ) {
						mat4f old = opt.matrix;				
						opt.matrix = viewport.vpmatrix() * cam->mvmatrix();
						Rendering ( *(pp->second), opt );
						opt.matrix = old;
					}
					//viewport.dirty( false );
				}
				//}
        }
    }
};

#endif
