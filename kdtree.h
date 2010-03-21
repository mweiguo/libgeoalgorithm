#ifndef _KDTREE_H_
#define _KDTREE_H_

#include "bbox.h"
#include <vector>
using namespace std;

template<class ObjectType>
class KdTree
{
  struct KdNode {
    KdNode ( int f, int s ) : first(f), second(s) {}
    int first, second;
    BBox bb;
  };
public:
  template<class Vec, class Output >
  bool intersect ( int nodeidx, Vec& s, Vec& e, Output out );
private:
  int addNode ( int f, int s ) { _nodes.push_back ( KdNode(f, s) ); return _nodes.size()-1; }
private:
  KdNode _root;
  vector<ObjectType> _objs;
  vector<KdNode> _nodes;
  friend class BuildKdTree;
};

template<class ObjectType, class InputIterator>
class BuildKdTree
{
public:
  typedef vec3<float> vec3f;

  static int targetnumperleaf;
  static int maxlevel;

  BuildKdTree ( KdTree<ObjectType>& _kdtree, InputIterator begin, InputIterator end, const BBox& bb );

private:
  void computeDivision(const BBox& bb );
  void divide ( int nodeidx, int level );

  BBox getBBox ( int istart, int iend );
  void sortindices ( int istart, int iend, int axis );
  int getmidindex ( int istart, int iend, float mid, int axis );

  KdTree<ObjectType>& _kdtree;
  vector<int> _axisstack;
  vector<int> _objindices;
  vector<vec3f> _objcenters;
};

#endif
