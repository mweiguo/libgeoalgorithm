#include "Delaunay.h"
#include <tinylog.h>

//------------------------------------------------------------------------------------------------------------------------
std::vector<dPoint> dBManager::mPoints;
std::vector<dEdge> dBManager::mEdges;
std::vector<dTriangle> dBManager::mTris;

//------------------------------------------------------------------------------------------------------------------------
int dBManager::add_point ( double x, double y )
{
  //   if ( mPoints.empty() )
  //     mPoints.push_back ( dPoint(0, 0, 0 ) );
  mPoints.push_back ( dPoint(x, y, mPoints.size() ) );
  return mPoints.back().mID;
}

//------------------------------------------------------------------------------------------------------------------------
int dBManager::add_point( double* c )
{
  //   if ( mPoints.empty() )
  //     mPoints.push_back ( dPoint(c, 0 ) );
  mPoints.push_back ( dPoint(c, mPoints.size() ) );
	
  return mPoints.back().mID;
}

//------------------------------------------------------------------------------------------------------------------------
int dBManager::add_edge ( int id1, int id2 )
{
//   if ( mEdges.empty() )
//     mEdges.push_back ( dEdge( 0, 0, 0 ) ); // place holder
  mEdges.push_back ( dEdge (id1, id2, mEdges.size()) );
  return mEdges.back().mID;
}
//------------------------------------------------------------------------------------------------------------------------
int dBManager::add_triangle ( int id1, int id2, int id3 )
{
//   if ( mTris.empty() )
//     mTris.push_back ( dTriangle( 0, 0, 0, 0 ) );  // place holder

  mTris.push_back ( dTriangle( id1, id2, id3, mTris.size() ) );

  dTriangle& tri = mTris.back();
  int id;
  if ( (id = tri.opptri_edge( id1 ))!=0 )
    mTris[id].rebuild_neighbour();
  if ( (id = tri.opptri_edge( id2 ))!=0 )
    mTris[id].rebuild_neighbour();
  if ( (id=tri.opptri_edge( id3))!=0 )
    mTris[id].rebuild_neighbour();

  return mTris.back().mID;
}

//------------------------------------------------------------------------------------------------------------------------
void dBManager::reset ()
{
  mPoints.clear();
  mEdges.clear();
  mTris.clear();
}
//------------------------------------------------------------------------------------------------------------------------
void dBManager::get_edgepnts ( int edge, dPoint** pp1, dPoint** pp2)
{
  if ( edge>0 ){	
    *pp1 = &mPoints[mEdges[edge].mPnts[0]];
    *pp2 = &mPoints[mEdges[edge].mPnts[1]];
  }else{
    *pp1 = &mPoints[mEdges[-edge].mPnts[1]];
    *pp2 = &mPoints[mEdges[-edge].mPnts[0]];
  }
}
////------------------------------------------------------------------------------------------------------------------------
//void display_points ( std::ostream& to, int id, std::string title )
//{
//	to.precision ( 10 );
//	to << title << std::endl;
//	dPoint& pnt = dBManager::mPoints[id];
//	to << pnt.x << ',' << pnt.y << std::endl;
//	if ( title=="circle" )
//		to << 5 << std::endl;
//}
////------------------------------------------------------------------------------------------------------------------------
//void display_points ( std::ostream& to, int *p, int cnt, std::string title )
//{
//	to.precision ( 10 );
//	to << title << std::endl;
//	for ( int i=1; i<cnt; i++ ){
//		dPoint& pnt = dBManager::mPoints[i];
//		to << pnt.x << ',' << pnt.y << std::endl;
//	}
//}
////------------------------------------------------------------------------------------------------------------------------
//void display_points ( std::ostream& to, std::list<int>& pnts, std::string title )
//{
//	to.precision ( 10 );
//	typedef std::list<int>::iterator ITER;
//	to << title << std::endl;
//	ITER end = pnts.end(), pp;
//	for ( pp=pnts.begin(); pp!=end; ++pp ){
//		dPoint& pnt = dBManager::mPoints[*pp];
//		to << pnt.x << ',' << pnt.y << std::endl;
//	}
//}
////------------------------------------------------------------------------------------------------------------------------
//void display_points ( std::ostream& to, std::vector<int>& pnts, std::string title )
//{
//	to.precision ( 10 );
//	typedef std::vector<int>::iterator ITER;
//	to << title << std::endl;
//	ITER end = pnts.end(), pp;
//	for ( pp=pnts.begin(); pp!=end; ++pp ){
//		dPoint& pnt = dBManager::mPoints[*pp];
//		to << pnt.x << ',' << pnt.y << std::endl;
//	}
//}
////------------------------------------------------------------------------------------------------------------------------
//void display_edges ( std::ostream& to, int id, std::string title )
//{
//	to.precision ( 10 );
//	to << title << std::endl;
//	dPoint *p1, *p2;
//	dBManager::get_edgepnts(id, &p1, &p2 );
//	to << p1->x << ',' << p1->y << std::endl;
//	to << p2->x << ',' << p2->y << std::endl << std::endl;
//}
////------------------------------------------------------------------------------------------------------------------------
//void display_edges ( std::ostream& to, int *p, int cnt, std::string title )
//{
//	to.precision ( 10 );
//	to << title << std::endl;
//	dPoint *p1, *p2;
//	for ( int i=1; i<cnt; i++ ){
//		dBManager::get_edgepnts(i, &p1, &p2 );
//		to << p1->x << ',' << p1->y << std::endl;
//		to << p2->x << ',' << p2->y << std::endl;
//	}
//	to << std::endl;
//}
////------------------------------------------------------------------------------------------------------------------------
//void display_edges ( std::ostream& to, std::list<int>& pnts, std::string title )
//{
//	to.precision ( 10 );
//	typedef std::list<int>::iterator ITER;
//	to << title << std::endl;
//	ITER end = pnts.end(), pp;
//	dPoint *p1, *p2;
//	for ( pp=pnts.begin(); pp!=end; ++pp ){
//		dBManager::get_edgepnts(*pp, &p1, &p2 );
//		to << p1->x << ',' << p1->y << std::endl;
//		to << p2->x << ',' << p2->y << std::endl;
//	}
//	to << std::endl;
//}
////------------------------------------------------------------------------------------------------------------------------
//void display_edges ( std::ostream& to, std::vector<int>& pnts, std::string title )
//{
//	to.precision ( 10 );
//	typedef std::vector<int>::iterator ITER;
//	to << title << std::endl;
//	ITER end = pnts.end(), pp;
//	dPoint *p1, *p2;
//	for ( pp=pnts.begin(); pp!=end; ++pp ){
//		dBManager::get_edgepnts(*pp, &p1, &p2 );
//		to << p1->x << ',' << p1->y << std::endl;
//		to << p2->x << ',' << p2->y << std::endl;
//	}
//	to << std::endl;
//}
////------------------------------------------------------------------------------------------------------------------------
//void display_tris ( std::ostream& to, int id, std::string title )
//{
//	to.precision ( 10 );
//	to << title << std::endl;
//	dPoint *p1, *p2;
//	dTriangle& tri = dBManager::mTris[id];
//	for ( int i=0; i<3; i++ ){
//		dBManager::get_edgepnts(tri.mEdges[i], &p1, &p2 );
//		to << p1->x << ',' << p1->y << std::endl;
//		to << p2->x << ',' << p2->y << std::endl;
//	}
//	to << std::endl;
//}
////------------------------------------------------------------------------------------------------------------------------
//void display_tris ( std::ostream& to, int *p, int cnt, std::string title )
//{
//	to.precision ( 10 );
//	dPoint *p1, *p2;
//	for ( int i=1; i<cnt; i++ ){
//		to << title << std::endl;
//		dTriangle& tri = dBManager::mTris[i];
//		for ( int j=0; j<3; j++ ){
//			dBManager::get_edgepnts(tri.mEdges[j], &p1, &p2 );
//			to << p1->x << ',' << p1->y << std::endl;
//			to << p2->x << ',' << p2->y << std::endl;
//		}
//		to << std::endl;
//	}
//}
////------------------------------------------------------------------------------------------------------------------------
//void display_tris ( std::ostream& to, std::list<int>& pnts, std::string title )
//{
//	to.precision ( 10 );
//	typedef std::list<int>::iterator ITER;
//	ITER end = pnts.end(), pp;
//	dPoint *p1, *p2;
//	for ( pp=pnts.begin(); pp!=end; ++pp ){
//		to << title << std::endl;
//		dTriangle& tri = dBManager::mTris[*pp];
//		for ( int j=0; j<3; j++ ){
//			dBManager::get_edgepnts(tri.mEdges[j], &p1, &p2 );
//			to << p1->x << ',' << p1->y << std::endl;
//			to << p2->x << ',' << p2->y << std::endl;
//		}
//		to << std::endl;
//	}
//}
////------------------------------------------------------------------------------------------------------------------------
//void display_tris ( std::ostream& to, std::vector<int>& pnts, std::string title )
//{
//	to.precision ( 10 );
//	typedef std::vector<int>::iterator ITER;
//	ITER end = pnts.end(), pp;
//	dPoint *p1, *p2;
//	for ( pp=pnts.begin(); pp!=end; ++pp ){
//		to << title << std::endl;
//		dTriangle& tri = dBManager::mTris[*pp];
//		for ( int j=0; j<3; j++ ){
//			dBManager::get_edgepnts(tri.mEdges[j], &p1, &p2 );
//			to << p1->x << ',' << p1->y << std::endl;
//			to << p2->x << ',' << p2->y << std::endl;
//		}
//		to << std::endl;
//	}
//}
////------------------------------------------------------------------------------------------------------------------------
//void display_tris ( std::ostream& to, std::vector<dTriangle>& tris, std::string title )
//{
//	to.precision ( 10 );
//	typedef std::vector<dTriangle>::iterator ITER;
//	ITER end = tris.end(), pp;
//	dPoint *p1, *p2;
//	for ( pp=tris.begin(); pp!=end; ++pp ){
//		to << title << std::endl;
//		for ( int j=0; j<3; j++ ){
//			dBManager::get_edgepnts((*pp).mEdges[j], &p1, &p2 );
//			to << p1->x << ',' << p1->y << std::endl;
//			to << p2->x << ',' << p2->y << std::endl;
//		}
//		to << std::endl;
//	}
//}
//------------------------------------------------------------------------------------------------------------------------
