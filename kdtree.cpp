#include "kdtree.h"
#include <algorithm>
using namespace std;

template<class ObjectType, class InputIterator>
int BuildKdTree<ObjectType,InputIterator>::targetnumperleaf = 16;
template<class ObjectType, class InputIterator>
int BuildKdTree<ObjectType,InputIterator>::maxlevel = 16;

template<class ObjType>
BBox getBBox ( ObjType& obj )
{
  return obj.bbox();
}

class Incr
{
public:
  Incr () : seed(0) {}
  int operator ()() { return seed++; }
private:
  int seed;
};

template<class ObjectType, class InputIterator>
BuildKdTree<ObjectType,InputIterator>::BuildKdTree ( 
	    KdTree<ObjectType>& kdtree, 
	    InputIterator begin, 
	    InputIterator end, 
	    const BBox& bb ) 
  : _kdtree(kdtree)
{
  computeDivision (bb);

  _kdtree._objs.assign ( begin, end );
  generate_n ( back_inserter(_objindices), _kdtree._objs.size(), Incr() );
  transform ( begin, end, back_inserter(_objcenters), getBBox );

  divide ();
}

template<class ObjectType, class InputIterator>
void BuildKdTree<ObjectType,InputIterator>::computeDivision(const BBox& bb )
{
  vec3f dimension;
  dimension = bb.max() - bb.min();
  
  int level = 0;
  while ( level < maxlevel ) {
    int axis;
    // get axis
    // 0 == divide x
    // 1 == divide y
    // 2 == divide z
    if (dimension[0]>=dimension[1]) {
	if (dimension[0]>=dimension[2]) axis = 0;
	else axis = 2;
    } else if (dimension[1]>=dimension[2]) axis = 1;
    else axis = 2;

    dimension[axis] /= 2.0f;

    _axisstack.push_back ( axis );
  }
}

//[istart, iend)
template<class ObjectType, class InputIterator>
BBox BuildKdTree<ObjectType,InputIterator>::getBBox ( int istart, int iend )
{
  BBox box;
  for ( int i=istart; i!=iend; i++ )
    box.unionbox ( _kdtree._objs[_objindices[i]].getBBox() );
  return box;
}

//[istart, iend)
template<class ObjectType, class InputIterator>
void BuildKdTree<ObjectType,InputIterator>::sortindices ( int istart, int iend, int axis )
{
  for ( int i=istart; i<=iend; i++ ) {
    float t = _objcenters[_objindices[i]][axis];
    for ( int j=i; j<=iend; j++ ) {
      float t1 = _objcenters[_objindices[j]][axis];
      if ( t1 < t )
	swap ( _objindices[i], _objindices[j] );
    }
  }
}

// 
template<class ObjectType, class InputIterator>
int BuildKdTree<ObjectType,InputIterator>::getmidindex ( int istart, int iend, float mid, int axis )
{
  int len = 0;
  for ( int i=istart; i<=iend; i++, len++ ) {
    if ( _objcenters[_objindices[i]][axis] > mid )
      return istart + len;
  }
}

template<class ObjectType, class InputIterator>
void BuildKdTree<ObjectType,InputIterator>::divide ( int nodeidx, int level )
{
  // if ( target number in this node < target number per leaf ) will stop divide 
  typename KdTree<ObjectType>::KdNode& node = _kdtree._nodes[_objindices[nodeidx]];
  if ( node.second < targetnumperleaf ){
    // set node.bb
    node.bb = getBBox ( node.first, node.first+node.second );
    return;
  }

  int axis = _axisstack[level];
  
  int istart = -node.first;
  int iend   = istart + node.second;
  // sort the indices from node.first to node.first + node.second
  sortindices ( istart, iend, axis );

  // calculate left and right node's indices range
  float mid = ((node.bb.max()+node.bb.min())/2)[axis];
  int imid = getmidindex ( istart, iend, mid, axis );
  node.left = _kdtree.addnode ( -istart, imid-istart );
  divide ( node.left, level+1 );

  node.right = _kdtree.addnode( -imid, iend-imid );
  divide ( node.right, level+1 );
}

template<class ObjectType>
template<class Vec, class Output >
bool KdTree<ObjectType>::intersect ( int nodeidx, Vec& s, Vec& e, Output out )
{
  KdNode& node = _nodes[nodeidx];

  Vec min = s.min ( e );
  Vec max = s.max ( e );
  if ( max < _root.bb.min() || min > _root.bb.max() ) return false;

  if ( node.first >= 0 ) {  // if node is not leaf
    intersect ( node.first, s, e, out );
    if ( node.second > 0 )
      findobj ( node.second, s, e, out );
  } else {  // if node is leaf 
    int istart = -node.first;
    int iend = -node.first + node.second;
    for ( int i=istart; i!=iend; i++ ) {
      *out++ = _objs[i];
    }
  }
  
}
