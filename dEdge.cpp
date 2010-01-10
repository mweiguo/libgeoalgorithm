#include "Delaunay.h"
#include <tinylog.h>

bool dEdge::add_owner( int id )
{
  if ( mTris[0] && mTris[1] )
    return false;

  if ( mTris[0]==0 )
    mTris[0] = id;
  else
    mTris[1] = id;
  return true;
}

bool dEdge::remove_owner( int tri )
{
  if ( mTris[0]==tri )
    mTris[0]=0;
  else if ( mTris[1]==tri )
    mTris[1]=0;
  else
    return false;
  return true;
}

dEdge::dEdge( int id1, int id2, int id ) : mID (id)
{
  mPnts[0] = id1;
  mPnts[1] = id2;
  mTris[0] = mTris[1] = 0;
}
