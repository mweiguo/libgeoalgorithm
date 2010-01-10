#include "Delaunay.h"
#include <stdexcept>
#include <stdlib.h>

#include "../alg/alg.hpp"
//-------------------------------------------------------------------------------------------------------------
dTriangle::dTriangle ( int e1, int e2, int e3, int id ) : mID (id)
{
  rebuild ( e1, e2, e3 );
}

//-------------------------------------------------------------------------------------------------------------
void dTriangle::rebuild ( int id1, int id2, int id3)
{
  // anti clockwise
  dPoint *p0[2], *p1[2], *p2[2];
  dBManager::get_edgepnts ( id1, &p0[0], &p0[1] );
  dBManager::get_edgepnts ( id2, &p1[0], &p1[1] );
  dBManager::get_edgepnts ( id3, &p2[0], &p2[1] );

  if ( p0[1]==p1[1] ){
    id2 = -id2;
    dPoint* tmp = p1[0];
    p1[0] = p1[1];
    p1[1] = tmp;
  }else if ( p0[0]==p1[0] ){
    id1 = -id1;
    dPoint* tmp = p0[0];
    p0[0] = p0[1];
    p0[1] = tmp;
  }else if ( p0[0]==p1[1] ){
    id1 = -id1;
    id2 = -id2;
    dPoint* tmp = p1[0];
    p1[0] = p1[1];
    p1[1] = tmp;
    tmp = p0[0];
    p0[0] = p0[1];
    p0[1] = tmp;
  }else if ( p0[1]==p1[0] );
  else
    throw std::invalid_argument ("the edges are not adjacency");

  if ( p1[1]==p2[1] ){
    id3 = -id3;
    dPoint* tmp = p2[0];
    p2[0] = p2[1];
    p2[1] = tmp;
  }else if ( p1[1]==p2[0] );
  else
    throw std::invalid_argument ("the edges are not adjacency");

  // anti-clock
  if ( clockwise( p0[0]->coord, p0[1]->coord, p1[1]->coord)){
    id1 *= -1;
    int tmp = id2;
    id2 = -id3;
    id3 = -tmp;
  }
  // edge
  mEdges[0] = id1;
  mEdges[1] = id2;
  mEdges[2] = id3;

  // build linkage topology
  // generate edge's owner
  dEdge *edge[] = {&dBManager::mEdges[abs(id1)], &dBManager::mEdges[abs(id2)], &dBManager::mEdges[abs(id3)]};
  edge[0]->add_owner( mID );
  edge[1]->add_owner( mID );
  edge[2]->add_owner( mID );
  // generate point's 
  dPoint *pp1, *pp2;
  dBManager::get_edgepnts ( id1, &pp1, &pp2 );
  mPnts[0] = pp1->mID;
  mPnts[1] = pp2->mID;
  dBManager::get_edgepnts ( id2, &pp1, &pp2 );
  mPnts[2] = pp2->mID;
  // generate tri's neighbour
  for ( int i=0; i<3; i++ ){
    if ( mID==edge[i]->mTris[0] )
      mTris[i] = edge[i]->mTris[1];
    else if ( mID==edge[i]->mTris[1] )
      mTris[i] = edge[i]->mTris[0];
  }
}
//-------------------------------------------------------------------------------------------------------------
void dTriangle::rebuild_neighbour ()
{
  dEdge *edge[] = {&dBManager::mEdges[abs(mEdges[0])], &dBManager::mEdges[abs(mEdges[1])], &dBManager::mEdges[abs(mEdges[2])]};
  for ( int i=0; i<3; i++ ){
    if ( mID==edge[i]->mTris[0] )
      mTris[i] = edge[i]->mTris[1];
    else if ( mID==edge[i]->mTris[1] )
      mTris[i] = edge[i]->mTris[0];
  }
}
//-------------------------------------------------------------------------------------------------------------
int dTriangle::share_edge( int id )
{
  if ( id==mTris[0] )
    return mEdges[0];
  else if ( id==mTris[1] )
    return mEdges[1];
  else if ( id==mTris[2] )
    return mEdges[2];
  return 0;
}

//-------------------------------------------------------------------------------------------------------------
int dTriangle::oppedge_pnt ( int id )
{
  if ( id==mPnts[0] )
    return mEdges[1];
  else if ( id==mPnts[1] )
    return mEdges[2];
  else if ( id==mPnts[2] )
    return mEdges[0];

  throw std::invalid_argument ( "the point is not on the triangle" );
}
//-------------------------------------------------------------------------------------------------------------
int dTriangle::oppnt_edge ( int id )
{
  id = id < 0 ? -id : id;
  if ( id==abs(mEdges[0]) )
    return mPnts[2];
  else if ( id==abs(mEdges[1]) )
    return mPnts[0];
  else if ( id==abs(mEdges[2]) )
    return mPnts[1];

  throw std::invalid_argument ( "the edge is not on the triangle" );
}
//-------------------------------------------------------------------------------------------------------------
int dTriangle::oppnt_pnt ( int id )
{
  int edge = oppedge_pnt(id);
  int tri = opptri_pnt(id);
  if ( tri )
    return dBManager::mTris[tri].oppnt_edge ( edge );
  return 0;
}
//-------------------------------------------------------------------------------------------------------------
void dTriangle::oppnts_pnt ( int p1, int& p2, int& p3 )
{
  int edge = oppedge_pnt ( p1 );
  if ( edge>0 ){
    p2 = dBManager::mEdges[edge].mPnts[0];
    p3 = dBManager::mEdges[edge].mPnts[1];
  }else{
    p2 = dBManager::mEdges[-edge].mPnts[1];
    p3 = dBManager::mEdges[-edge].mPnts[0];
  }
}
//-------------------------------------------------------------------------------------------------------------
int dTriangle::opptri_pnt ( int id )
{
  if ( id==mPnts[0] )
    return opptri_edge ( mEdges[1] );
  else if ( id==mPnts[1] )
    return opptri_edge ( mEdges[2] );
  else if ( id==mPnts[2] )
    return opptri_edge ( mEdges[0] );

  throw std::invalid_argument ( "the point is not in triangle" );
}
//-------------------------------------------------------------------------------------------------------------
int dTriangle::opptri_edge ( int id )
{
  dEdge& edge = dBManager::mEdges[abs(id)];
	
  if ( mID==abs(edge.mTris[0]) )
    return edge.mTris[1];
  else if ( mID==abs(edge.mTris[1]) )
    return edge.mTris[0];
  else// if ( edge.mTris[0]!=0 && edge.mTris[1]!=0 )
    throw std::invalid_argument ( "the edge is not on this triangle" );
}
//-------------------------------------------------------------------------------------------------------------
