#include "Delaunay.h"
#include <alg.hpp>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <iostream>
#include <tinylog.h>

using namespace std;
////////////////////////////////////////////// implDelaunay /////////////
cDelaunay::cDelaunay()
{
	mPoints.reserve(100);
	mTris.reserve (100);
}

cDelaunay::~cDelaunay()
{
}

/*
* 1. create a point an set coordinate to it
* 2. save point
* 3. recalculate the border
*/
int cDelaunay::add_point ( double x, double y )
{
	return dBManager::add_point ( x, y );
}

int cDelaunay::add_point ( double* c )
{
	return dBManager::add_point ( c );
}

/*
* 1. initialize triangles
* 2. sort points relay on distance from the border center
* 3. create delaunay net
* 4. add every point to delaunay net
*/
bool cDelaunay::build_net ()
{
	//   time_t tm, tm1;
	//   time ( &tm );
	LOG_DEBUG ("begin sort distance");
	SortByDist();

	LOG_DEBUG ("begin generate delaunay");
	bool rtn = GenDelaunay();

	//   time ( &tm1 );
	//   std::cout << "generate delaunay ellepse " << tm1-tm << std::endl;
	return rtn;
}

void cDelaunay::reset()
{
	dBManager::reset();
}

/*
* @brief: sort mpTempPnts's element by distance from center point
* @remark: bubble sort
*/
// void cDelaunay::SortByDist()
// {
//   if ( mPoints.empty() )
//     return;

//   // get center point
//   double x = mPoints[0].x;
//   double y = mPoints[0].y;

//   double dist, min;
//   pnt_iterator pp1;

//   // bubble sort by dist from center point
//   for ( pnt_iterator pp=mPoints.begin(); pp!=mPoints.end(); ++pp ){
//     min = distance2d ( (*pp).x, (*pp).y, x, y );
//     pp1 = pp;
//     for ( ++pp1; pp1!=mPoints.end(); ++pp1 ){
//       dist = distance2d ( pp1->x, pp1->y, x, y );

//       if ( dist < min ){
// 	min = dist;
// 	dPoint temp = *pp;
// 	*pp = *pp1;
// 	*pp1 = temp;
//       }
//     }
//   }

//   // reset point id
//   for ( size_t i=0; i<mPoints.size(); i++ )
//     mPoints[i].mID = i;
// }

void cDelaunay::SortByDist()
{
	if ( mPoints.empty() )
		return;

	// initialize mvIndex
	mvIndex.resize ( mPoints.size(), 0 );
	generate ( mvIndex.begin(), mvIndex.end(), Incr() );
	vector<double> vdist ( mPoints.size() - 1 );

	// get center point
	double x = mPoints[0].x;
	double y = mPoints[0].y;

	// calculate dists
	pnt_iterator pp=mPoints.begin(), end=mPoints.end();
	for ( pnt_iterator pp0=++pp; pp!=end; ++pp )
		vdist[pp-pp0] = distance2d ( pp->x, pp->y, x, y );
		//vdist.push_back ( distance2d ( pp->x, pp->y, x, y ) );

	// sort
	for ( int i=0; i<vdist.size(); ++i ) {
		for ( int j=i; j<vdist.size(); ++j ) {
			if ( vdist[i] > vdist[j] ) {

				double td = vdist[i];
				vdist[i] = vdist[j];
				vdist[j] = td;

				int ti = mvIndex[i+1];
				mvIndex[i+1] = mvIndex[j+1];
				mvIndex[j+1] = ti;
			}
		}
	}

   //// reset point id
   //for ( size_t i=0; i<mPoints.size(); i++ )
   //  mPoints[i].mID = i;

}

/*
* @brief: generate delaunay triangle net from the sorted points
* @implicity para: [IN]mpTempPnts( the sorted points)
* @implicity para: [OUT]mTris(the triangle net)
* @remark: this operation will succeeded until mpTempPnts has more than 
*          three points
*/

bool cDelaunay::GenDelaunay()
{
	if ( mPoints.size() < 3 )
		return false;

	LOG_DEBUG ( "begin create first triangle ... " );
	// create first triangle and add it to triNet
	int id1 = add_edge ( mvIndex[0], mvIndex[1] );
	int id2 = add_edge ( mvIndex[1], mvIndex[2] );
	int id3 = add_edge ( mvIndex[2], mvIndex[0] );
	id1 = add_triangle ( id1, id2, id3 );

	// init outline
	mOutline.clear();
	mOutline.push_back ( mTris[id1].mEdges[0] );
	mOutline.push_back ( mTris[id1].mEdges[1] );
	mOutline.push_back ( mTris[id1].mEdges[2] );

	// add each point to generate trinet
	for ( size_t i=4; i<mvIndex.size(); i++ ) {
		merge_point ( mvIndex[i] );
	}

	LOG_DEBUG ( "finished merge point" );
	if ( mTris.size()==1 ){
		mTris.clear();	 
		return false;
	}

	return true;
}

bool cDelaunay::merge_point ( int pnt )
{
	// get visible points
	bool backwardFind = false;
	dPoint *p1, *p2;
	size_t tmpSize=0;
	std::list<int> visEdge;

	{
		std::list<int>::iterator pp, end=mOutline.end();

		for ( pp=mOutline.begin(); pp!=end; ++pp ){

			get_edgepnts ( *pp, &p1, &p2 );

			if ( !in_leftside( mPoints[pnt].coord, p1->coord, p2->coord )){

				if ( pp==mOutline.begin() )
					backwardFind = true;

				visEdge.push_back ( *pp );

			} else if ( !visEdge.empty() )
				break;
		}
	}

	tmpSize = visEdge.size();

	if ( backwardFind ){

		std::list<int>::reverse_iterator pp, end=mOutline.rend();

		for ( pp=mOutline.rbegin(); pp!=end; ++pp ){

			get_edgepnts ( *pp, &p1, &p2 );

			if ( !in_leftside ( point(pnt).coord, p1->coord, p2->coord )){

				visEdge.push_front ( *pp );

			}else{

				if ( tmpSize==visEdge.size() )

					backwardFind = false;

				break;

			}
		}
	}

	if ( visEdge.empty() )
		return false;

	// prepare edges
	std::vector<int> ids;
	std::list<int>::iterator pp, end=visEdge.end();

	get_edgepnts ( visEdge.front(), &p1, &p2 );
	ids.push_back ( add_edge ( p1->mID, pnt) );
	for ( pp=visEdge.begin(); pp!=end; ++pp ){
		get_edgepnts ( *pp, &p1, &p2 );
		ids.push_back ( add_edge ( pnt, p2->mID ));
	}

	// add triangle & optimize  
	int idx=0, id;
	for ( pp=visEdge.begin(); pp!=end; ++pp, idx++ ){
		id = add_triangle ( ids[idx], ids[idx+1], *pp );
		optimize ( id, pnt );
	}

	// rebuild outline
	pp = std::find ( mOutline.begin(), mOutline.end(), visEdge.front() );
	end = std::find ( mOutline.begin(), mOutline.end(), visEdge.back() );
	++end;
	if ( backwardFind ){

		mOutline.erase ( pp, mOutline.end() );
		mOutline.erase ( mOutline.begin(), end ); 
		mOutline.push_back( ids.front() );
		mOutline.push_front ( ids.back() );

	} else {

		mOutline.insert ( pp, ids.front() );
		mOutline.insert ( pp, ids.back() );
		mOutline.erase ( pp, end );

	}
	return true;
}

void cDelaunay::optimize( int tri, int pnt )
{
	int npnt[3];
	int ntri[3];
	ntri[0] = mTris[tri].opptri_pnt ( mTris[tri].mPnts[0] );
	npnt[0] = mTris[tri].oppnt_pnt ( mTris[tri].mPnts[0] );
	ntri[1] = mTris[tri].opptri_pnt ( mTris[tri].mPnts[1] );
	npnt[1] = mTris[tri].oppnt_pnt ( mTris[tri].mPnts[1] );
	ntri[2] = mTris[tri].opptri_pnt ( mTris[tri].mPnts[2] );
	npnt[2] = mTris[tri].oppnt_pnt ( mTris[tri].mPnts[2] );

	int p1, p2, tri1, idnew, e1[2], e2[2];
	double coord[3], r;

	for ( int i=0; i<3; i++ ){
		if ( 0==ntri[i] )
			continue;

		if ( pnt != mTris[ntri[i]].oppnt_pnt ( npnt[i]))
			continue;
		tri1 = mTris[ntri[i]].opptri_pnt ( npnt[i] );
		if ( 0==tri1 )
			continue;

		// test & change
		mTris[ntri[i]].oppnts_pnt ( npnt[i], p1, p2 );
		r = circle3pnt4dv ( mPoints[npnt[i]].coord, mPoints[p1].coord, mPoints[p2].coord, coord );
		if ( distance2dv ( coord, mPoints[pnt].coord ) < r ){
			idnew = mTris[ntri[i]].oppedge_pnt ( npnt[i] );
			dEdge& sedge = mEdges[abs(idnew)];
			sedge.mPnts[0] = npnt[i];
			sedge.mPnts[1] = pnt;
			e1[0] = mTris[ntri[i]].oppedge_pnt ( p1 );
			e1[1] = mTris[tri1].oppedge_pnt ( p1 );
			e2[0] = mTris[ntri[i]].oppedge_pnt ( p2 );
			e2[1] = mTris[tri1].oppedge_pnt ( p2 );

			// remove edge's old owner
			mEdges[abs(e1[0])].remove_owner ( ntri[i] );
			mEdges[abs(e1[1])].remove_owner ( tri1 );
			mEdges[abs(e2[0])].remove_owner ( ntri[i] );
			mEdges[abs(e2[1])].remove_owner ( tri1 );
			sedge.remove_owner ( ntri[i] );
			sedge.remove_owner ( tri1 );

			mTris[ntri[i]].rebuild ( idnew, e1[0], e1[1] );
			mTris[tri1].rebuild ( idnew, e2[0], e2[1] );
			if ( mTris[ntri[i]].mPnts[0]==pnt ||
				mTris[ntri[i]].mPnts[1]==pnt ||
				mTris[ntri[i]].mPnts[2]==pnt )
				optimize ( ntri[i], pnt );
			if ( mTris[tri1].mPnts[0]==pnt ||
				mTris[tri1].mPnts[1]==pnt ||
				mTris[tri1].mPnts[2]==pnt )
				optimize ( tri1, pnt );
		}
	}
}


