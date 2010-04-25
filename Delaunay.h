#pragma once

#include <vector>
#include <list>
#include <map>
#include "indexiter.h"

using namespace std;

class TPoint
{
  TPoint ( double x, double y, int id );
  TPoint ( double* coord, int id );
  int getId ();
};

class TEdge
{
  TEdge ( int p1, int p2, int id );
  int getId ();
};

class TTriangle
{
  TTriangle ( int e1, int e2, int e3, int id);
  int share_edge( int tri );
  int oppedge_pnt ( int pnt );
  int oppnt_edge ( int edge );
  int oppnt_pnt ( int pnt );
  void oppnts_pnt ( int pnt, int& pnt1, int& pnt2);

  int opptri_pnt ( int pnt );
  int opptri_edge ( int edge );
};

//--------------------------------------------------

struct dPoint
{
  dPoint (double _x, double _y, int id ) : x(_x), y(_y), mID(id) { }
  dPoint (double* coord, int id ) : x(coord[0]), y(coord[1]), mID(id) { }

  int mID;
  union{
    struct
    {
      double x, y;
    };
    double coord[1];
  };
};

struct dEdge
{
  bool add_owner( int tri );
  bool remove_owner( int tri );
  dEdge( int, int, int id);
public:
  int mID;       
  int mPnts[2];
  int mTris[2];
};

struct dTriangle
{
  dTriangle ( int e1, int e2, int e3, int id);
  void rebuild ( int, int, int );
  void rebuild_neighbour ();
  int share_edge( int );
  int oppedge_pnt ( int );
  int oppnt_edge ( int );
  int oppnt_pnt ( int );
  void oppnts_pnt ( int, int&, int& );

  int opptri_pnt ( int );
  int opptri_edge ( int );
public:
  int mID;
  int mPnts[3];
  int mEdges[3];
  int mTris[3];
};

class dBManager
{
public:
  typedef IndexIterator<dPoint> point_iterator;
  typedef IndexIterator<dEdge> edge_iterator;
  typedef IndexIterator<dTriangle> triangle_iterator;

  static point_iterator point_begin() {
    return point_iterator ( &mPoints, 0 );
  }
  static point_iterator point_end() {
    return point_iterator ( &mPoints, mPoints.size() );
  }
  static edge_iterator edge_begin() {
    return edge_iterator ( &mEdges, 0 );
  }
  static edge_iterator edge_end() {
    return edge_iterator ( &mEdges, mEdges.size() );
  }
  static triangle_iterator triangle_begin() {
    return triangle_iterator ( &mTris, 0 );
  }
  static triangle_iterator triangle_end() {
    return triangle_iterator ( &mTris, mTris.size() );
  }
  static int add_point ( double, double );
  static int add_point ( double* );
  static int add_edge ( int, int );
  static int add_triangle ( int, int, int );
  static void reset ();

  static void get_edgepnts ( int, dPoint**, dPoint** );
  static dPoint& point( int id ){ return mPoints[id]; }
  static dEdge& edge( int id ){ return mEdges[id]; }
  static dTriangle& triangle( int id ){ return mTris[id]; }

  static std::vector<dPoint> mPoints;
  static std::vector<dEdge> mEdges;
  static std::vector<dTriangle> mTris;
};

class cDelaunay : private dBManager
{
public:
  typedef std::vector<dPoint>::iterator pnt_iterator;
  typedef std::vector<dEdge>::iterator edge_iterator;
  typedef std::vector<dTriangle>::iterator tri_iterator;

  cDelaunay();
  ~cDelaunay();
  // add discrete point then calculate the triangle net
  int add_point ( double, double );
  int add_point ( double* );
  bool build_net ();
  void reset();

  // get
  pnt_iterator begin_pnt(){ return mPoints.begin(); }
  pnt_iterator end_pnt(){return mPoints.end();}
  edge_iterator begin_edge(){return mEdges.begin(); }
  edge_iterator end_edge(){return mEdges.end(); }
  tri_iterator begin_tri(){return mTris.begin(); }
  tri_iterator end_tri(){return mTris.end(); }
  int tri_cnt(){return mTris.size(); }
  int pnt_cnt(){return mPoints.size(); }

  bool empty_pnt(){return mPoints.empty(); }
  bool empty_edge(){return mEdges.empty(); }
  bool empty_tri(){return mTris.empty(); }

protected:
  void SortByDist();
  bool GenDelaunay();
  bool merge_point ( int );
  void optimize ( int, int );
protected:
  // store vertex id
  vector<int> mvIndex;
  list<int> mOutline;
  struct Incr { int seed; Incr() : seed(0) {} int operator() () { return seed++; } };
};

class DelnyManager 
{
  DelnyManager(){}
public:
  static DelnyManager& getInst() {
    static DelnyManager _this;
    return _this;
  }

  ~DelnyManager () {
    map<int, cDelaunay*>::iterator pp, end;
    for ( pp=mgr.begin(); pp!=mgr.end(); ++pp )
      delete pp->second;
  }

  int add ( cDelaunay* p ) {
    mgr[DelnyManager::SEED] = p;
    return DelnyManager::SEED++;
  }

  void remove ( int id ) {
    mgr.erase ( id );
  }

public:
  static int SEED;
  map<int, cDelaunay*> mgr;
};

// interface 
int createDelaunay ();
void destroyDelaunay ( int id );
int delnyAddPoint (int id, double x, double y);
int delnyAddPoint (int id, double*);
void delnyBuild ( int id );

/*
  @id: delaunay id, created by 'createDelaunay' function
  @out: 'point index array' will be filled if 'out' is not null, the array size
  should get by invoke 'delnyIndexes(id, NULL, cnt );'
  @cnt: when 'out' is null, this parameter will be filled the size of 'coordinate index' 
  @description: get 'point index array' of the delaunay, specified by id.
  @note: 'point index array' in form of 'p1 p2 p3 p4 p5 p1 p2 p3 p4 ...', every three
  index will composed a triangle.
 */
void delnyIndexes(int id, int* out, int& cnt );

/*
  @id: delaunay id, created by 'createDelaunay' function
  @out: coordinate array will be filled if 'out' is not null, the array size
  should get by invoke 'delnyIndexes(id, NULL, cnt );'
  @cnt: when 'out' is null, this parameter will be filled the size of 'coordinate' 
  @description: get 'coordinate array' of the delaunay, specified by id.
  @note: 'coordinate array' in the form of 'x1 y1 x2 y2 x3 y3 x4 y4 ... xn yn'
 */
void delnyCoords (int id, float* out, int& cnt);

/* void delnyRemovePoint ( int id, int pntid ); */
/* int delnyChangePoint (int id, double x, double y, void* data=0 ); */
/* int delnyChangePoint (int id, double*, void* data=0 ); */
