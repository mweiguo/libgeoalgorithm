#include <algorithm>
#include <tinylog.h>
using namespace std;

template<class ObjectType>
int BuildKdTree<ObjectType>::targetnumperleaf = 16;

template<class ObjectType>
int BuildKdTree<ObjectType>::maxlevel = 16;

// #include "drawablenode.h"
template<class ObjType>
struct getBBCenter
{
  vec3f operator() (ObjType node )
  {
    return node->getBBox().center();
  }
};

class Incr
{
public:
  Incr () : seed(0) {}
  int operator ()() { return seed++; }
private:
  int seed;
};

template<class ObjectType>
BuildKdTree<ObjectType>::BuildKdTree ( KdTree<ObjectType>& kdtree, const BBox& bb ) 
  : _kdtree(kdtree)
{
  computeDivision (bb);

#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "begin settting up _objindices ... " );
#endif
  generate_n ( back_inserter(_objindices), _kdtree._objs.size(), Incr() );
#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "ok" );
#endif

#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "begin setting up _objcenters ... " );
#endif
  transform ( _kdtree._objs.begin(), _kdtree._objs.end(), back_inserter(_objcenters), getBBCenter<ObjectType>() );
#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "ok" );
#endif

  int root = _kdtree.addNode ( -1, _kdtree._objs.size() );

#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "begin divide ... " );
#endif
  divide ();
#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "ok" );
#endif


  // set kdtree's objs in sorted order
#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "begin sort the primitive's order ... " );
#endif
  vector<ObjectType> objs ( _kdtree._objs.size() );
  for ( int i=0; i<_objindices.size(); i++ )
    objs[i] = _kdtree._objs[_objindices[i]];
  _kdtree._objs.swap ( objs );
#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "ok" );
#endif

  _kdtree.dump ( root, 0 );
}

template<class ObjectType>
template<class InputIterator>
BuildKdTree<ObjectType>::BuildKdTree ( KdTree<ObjectType>& kdtree, 
				       InputIterator begin, 
				       InputIterator end, 
				       const BBox& bb ) 
  : _kdtree(kdtree)
{
  computeDivision (bb);

#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "begin settting up _objindices ... " );
#endif
  _kdtree._objs.assign ( begin, end );
  generate_n ( back_inserter(_objindices), _kdtree._objs.size(), Incr() );
#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "ok" );
#endif

#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "begin setting up _objcenters ... " );
#endif
  transform ( _kdtree._objs.begin(), _kdtree._objs.end(), back_inserter(_objcenters), getBBCenter<ObjectType>() );
#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "ok" );
#endif

  int root = _kdtree.addNode ( -1, _kdtree._objs.size() );

#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "begin divide ... " );
#endif
  divide ();
#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "ok" );
#endif

#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "begin sort primitive's order ... " );
#endif
  // set kdtree's objs in sorted order
  vector<ObjectType> objs ( _kdtree._objs.size() );
  for ( int i=0; i<_objindices.size(); i++ )
    objs[i] = _kdtree._objs[_objindices[i]];
  _kdtree._objs.swap ( objs );
#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "ok" );
#endif

  _kdtree.dump ( root, 0 );
}

template<class ObjectType>
void BuildKdTree<ObjectType>::computeDivision(const BBox& bb )
{
#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "begin computeDivision ... " );
#endif
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


    _axisstack.push_back ( axis );

    LOG_DEBUG ( "level=%d\taxis=%d\tdimension=(%f, %f, %f)", level, axis, dimension[0], dimension[1], dimension[2] );

    dimension[axis] /= 2.0f;
    ++level;
  }

#ifdef _DEBUG_OUTPUT_
  LOG_DEBUG ( "ok" );
#endif
}

//[istart, iend)
template<class ObjectType>
BBox BuildKdTree<ObjectType>::getBBox ( int istart, int iend )
{
  BBox box;
  for ( int i=istart; i!=iend; i++ )
    box.unionbox ( _kdtree._objs[_objindices[i]]->getBBox() );
  return box;
}

//[istart, iend)
template<class ObjectType>
void BuildKdTree<ObjectType>::sortindices ( int istart, int iend, int axis )
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
template<class ObjectType>
int BuildKdTree<ObjectType>::getmidindex ( int istart, int iend, float mid, int axis )
{
  int len = 0;
  for ( int i=istart; i<=iend; i++, len++ ) {
    if ( _objcenters[_objindices[i]][axis] > mid )
      return istart + len;
  }
  return -1;
}

template<class ObjectType>
void BuildKdTree<ObjectType>::divide ( int nodeidx, int level )
{
  // if ( target number in this node < target number per leaf ) will stop divide 
  typename KdTree<ObjectType>::KdNode& node = _kdtree._nodes[_objindices[nodeidx]];
  //  LOG_DEBUG ("nodeidx=%d, node.first=%d, node.second=%d, level=%d, targetnumperleaf=%d, maxlevel=%d", nodeidx, node.first, node.second, level, targetnumperleaf, maxlevel );
  int istart = -node.first-1;
  int iend   = istart + node.second;

  if ( node.second < targetnumperleaf || level >= maxlevel ){
    // set node.bb
    node.bb = getBBox ( istart, iend );
    return;
  }

  int axis = _axisstack[level];
  
  // sort the indices from node.first to node.first + node.second
  sortindices ( istart, iend, axis );

  // calculate left and right node's indices range
  // float mid = ((node.bb.max()+node.bb.min())/2)[axis];
  float mid = node.bb.center()[axis];
  int imid = getmidindex ( istart, iend, mid, axis );
  LOG_DEBUG ("\tistart=%d, iend=%d, mid=%f, axis=%d, imid=%d", istart, iend, mid, axis, imid );
  node.first = _kdtree.addNode ( -istart-1, imid-istart );
  divide ( node.first, level+1 );

  LOG_DEBUG ("****istart=%d, iend=%d, mid=%f, axis=%d, imid=%d", istart, iend, mid, axis, imid );
  node.second = _kdtree.addNode( -imid-1, iend-imid );
  divide ( node.second, level+1 );
}


template<class ObjectType>
template<class Vec, class Output >
bool KdTree<ObjectType>::intersect ( const Vec& s, const Vec& e, Output out, int nodeidx )
{
  KdNode& node = _nodes[nodeidx];

  Vec min = s.min ( e );
  Vec max = s.max ( e );
  if ( max < node.bb.min() || min > node.bb.max() ) return false;

  if ( node.first >= 0 ) {  // if node is not leaf
    intersect ( s, e, out, node.first);
    intersect ( s, e, out, node.second );
  } else {  // if node is leaf 
    if ( node.second > 0 ) {
      int istart = -node.first-1;
      int iend = istart + node.second;
      for ( int i=istart; i!=iend; i++ ) {
	BBox& bb = _objs[i]->getBBox();
	if ( max < bb.min() || min > bb.max() ) 
	  continue;

	*out++ = _objs[i];
      }
    }
  }
  return true;
}

template<class ObjectType>
void KdTree<ObjectType>::dump ( int nodeIdx, int level  ) 
{
#ifdef _DEBUG_OUTPUT_
  KdNode& node = _nodes[nodeIdx];
  LOG_DEBUG ( "DUMP kdtree:  level=%d\tleft=%d\tright=%d", level, node.first, node.second );
  if ( node.second == 0 )
    return;
  if ( node.first >=0 ) {
    dump ( node.first, level+1 );
    dump ( node.second, level+1 );
  }
#endif
}
