#include "kdtree.h"

template<class ObjType>
BBox getBBox ( ObjType& obj )
{
  return obj.bbox();
}

void BuildKdTree::BuildKdTree ( KdTree& kdtree, Input begin, Input end, const BBox& bb ) 
  : _kdtree(kdtree)
{
  computeDivision (bb);

  _kdtree._objs.assign ( begin, end );
  _objindices.assign ( 0, _kdtree._objs.size() );
  std::transform ( begin, end, back_inserter(_objcenters), getBBox );

  divide ();
}

void BuildKdTree::computeDivision(const BBox& bb )
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

void BuildKdTree::divide ( int nodeidx, int level )
{
  // if ( target number in this node < target number per leaf ) will stop divide 
  // max level checking
  KdNode& node = _nodes[_objindices[nodeidx]];
  if ( level > maxlevel || node.second < targetnumperleaf ){
    // set node.bb
    return;
  }

  int axis = _axisstack[level];
  
  // sort the indices from node.first to node.first + node.second
  int istart = -node.first;
  int iend   = istart + node.second;
  for ( int i=istart; i<=iend; i++ ) {
    float t = _centers[_objindices[i]][axis]
    for ( int j=i; j<=iend; j++ ) {
      float t1 = _centers[_objindices[j]][axis]
      if ( t1 < t )
	swap ( _objindices[i], _objindices[j] );
    }
  }

  // calculate left and right node's indices range
  float mid = ((node.bb.max()+node.bb.min())/2)[axis];
  int len = 0;
  for ( i=istart; i<=iend; i++; len++ ) {
    float t = _centers[_objindices[i]][axis];
    if ( t>mid )
      break;
  }
  // -istart, len
  // -(istart+len), iend-istart-len
  node.left = _kdtree.addnode ( -istart, len );
  node.right = _kdtree.addnode( -(istart+len), iend-istart-len );
}

template<class Vec, class Output >
bool KdTree::findobj ( Vec& s, Vec& e, Output out )
{
  Vec min = min ( s, e );
  Vec max = max ( s, e );
  if ( min < _root.bb.min() || max > _root.bb.max() ) return false;
  
}

template<class Vec, class Output >
bool KdTree::findobj ( Vec& s, Vec& e, KdNode& node, Output out )
{
  Vec min = min ( s, e );
  Vec max = max ( s, e );
  if ( min < node.bb.min() || max > node.bb.max() ) return false;

  if ( node.first >= 0 ) {  // if node is not leaf
    findobj ( s, e, node.first, out );
    if ( node.second > 0 )
      findobj ( s, e, node.second, out );
  } else {  // if node is leaf 
    
  }
}
