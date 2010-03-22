#ifndef _KDTREE_H_
#define _KDTREE_H_

#include "bbox.h"
#include <vector>
using namespace std;


template<class ObjectType>
class BuildKdTree;
template<class ObjectType>
class KdTree
{
  struct KdNode {
    KdNode ( int f=0, int s=0 ) : first(f), second(s) {}
    int first, second;
    BBox bb;
  };
public:
  template<class Vec, class Output >
  bool intersect ( const Vec& s, const Vec& e, Output out, int nodeidx=0 );
  void addPrimitive (ObjectType obj) { _objs.push_back (obj); }
private:
  int addNode ( int f, int s ) { _nodes.push_back ( KdNode(f, s) ); return _nodes.size()-1; }
  void dump ( int nodeIdx, int level  );
private:
  // KdNode _root;
  vector<ObjectType> _objs;
  vector<KdNode> _nodes;
  friend class BuildKdTree<ObjectType>;
};

template<class ObjectType>
class BuildKdTree
{
public:
  static int targetnumperleaf;
  static int maxlevel;

  BuildKdTree ( KdTree<ObjectType>& _kdtree, const BBox& bb );
  template<class InputIterator>
  BuildKdTree ( KdTree<ObjectType>& _kdtree, InputIterator begin, InputIterator end, const BBox& bb );

private:
  void computeDivision(const BBox& bb );
  void divide ( int nodeidx=0, int level=0 );

  BBox getBBox ( int istart, int iend );
  void sortindices ( int istart, int iend, int axis );
  int getmidindex ( int istart, int iend, float mid, int axis );

  KdTree<ObjectType>& _kdtree;
  vector<int> _axisstack;
  vector<int> _objindices;
  vector<vec3f> _objcenters;
};


#include "kdtree.cpp"

#endif
