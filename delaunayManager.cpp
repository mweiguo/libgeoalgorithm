#include "Delaunay.h"
#include <gexception.h>
#include <stdexcept>
#include <tinylog.h>

int DelnyManager::SEED = 0;

int createDelaunay ()
{
  return DelnyManager::getInst().add ( new cDelaunay() );
}

void destroyDelaunay ( int id )
{
  DelnyManager::getInst().remove ( id );
}

#define TEST( x, ... )    int yy= 2;

int delnyAddPoint (int id, double x, double y)
{
  map<int, cDelaunay*>::iterator pp = DelnyManager::getInst().mgr.find( id );
  if ( pp == DelnyManager::getInst().mgr.end() )
    throw GException("delaunay %d dose not exists!",id);
    //    throw std::logic_error("delaunay %d dose not exists!" );
    

  return pp->second->add_point ( x, y );
}

int delnyAddPoint (int id, double* coord) {
  map<int, cDelaunay*>::iterator pp = DelnyManager::getInst().mgr.find( id );
  if ( pp == DelnyManager::getInst().mgr.end() )
    throw GException("delaunay %d dose not exists!", id);

  return pp->second->add_point ( coord );
}

void delnyBuild ( int id ) {
  map<int, cDelaunay*>::iterator pp = DelnyManager::getInst().mgr.find( id );
  if ( pp == DelnyManager::getInst().mgr.end() )
    throw GException("delaunay %d dose not exists!", id);

  LOG_DEBUG ("begin to build net");
  pp->second->build_net ();
}

void delnyIndexes(int id, int* out, int& cnt )
{
  map<int, cDelaunay*>::iterator pp = DelnyManager::getInst().mgr.find( id );
  if ( pp == DelnyManager::getInst().mgr.end() )
    throw GException("delaunay %d dose not exists!", id);

  cDelaunay* pDelny = pp->second;
  if ( NULL == pDelny )
    throw GException("delaunay %d is null object!", id);

  if ( out == 0 ){
    cnt = pDelny->tri_cnt() * 3;
    return;
  }

  cDelaunay::tri_iterator pp1, end=pDelny->end_tri();
  for ( pp1=pDelny->begin_tri(); pp1!=end; ++pp1 ) {
    *out++ = (*pp1).mPnts[0];
    *out++ = (*pp1).mPnts[1];
    *out++ = (*pp1).mPnts[2];
  }
}

void delnyCoords (int id, float* out, int& cnt)
{
  map<int, cDelaunay*>::iterator pp = DelnyManager::getInst().mgr.find( id );
  if ( pp == DelnyManager::getInst().mgr.end() )
    throw GException("delaunay %d dose not exists!", id);

  cDelaunay* pDelny = pp->second;
  if ( NULL == pDelny )
    throw GException("delaunay %d is null object!", id);

  if ( out == 0 ){
    cnt = pDelny->pnt_cnt() * 2;
    return;
  }

  cDelaunay::pnt_iterator pp1, end=pDelny->end_pnt();
  for ( pp1=pDelny->begin_pnt(); pp1!=end; ++pp1 ) {
    *out++ = (*pp1).x;
    *out++ = (*pp1).y;
  }
}

// void delnyRemovePoint ( int id, int pntid ) {
//   map<int, cDelaunay*>::iterator pp = DelnyManager::getInst().mgr.find( id );
//   if ( pp == DelnyManager::getInst().mgr.end() )
//     return;
//   pp->second->remove_point ( id );
// }

// int delnyChangePoint (int id, double x, double y, void* data=0 )
// {
//   map<int, cDelaunay*>::iterator pp = DelnyManager::getInst().mgr.find( id );
//   if ( pp == DelnyManager::getInst().mgr.end() )
//     return -1;
//   return pp->second->change_point ( x, y );
// }

// int delnyChangePoint (int id, double*, void* data=0 )
// {
//   map<int, cDelaunay*>::iterator pp = DelnyManager::getInst().mgr.find( id );
//   if ( pp == DelnyManager::getInst().mgr.end() )
//     return -1;
//   return pp->second->change_point ( coord );
// }

