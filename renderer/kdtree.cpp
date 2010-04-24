#include <algorithm>

using namespace std;

//template<class ObjectType>
//int BuildKdTree<ObjectType>::targetnumperleaf = 16;
//
//template<class ObjectType>
//int BuildKdTree<ObjectType>::maxlevel = 16;

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
inline BuildKdTree<ObjectType>::BuildKdTree ( KdTree<ObjectType>& kdtree, /*BBox& bb,*/ const BuildKdTreeOption& opt ) 
: _kdtree(kdtree)
{
#ifdef _USESTATISTIC_
	_buildStartClock = clock();
#endif
	BBox bb;
	for ( int i=0; i<kdtree.size(); i++ )
		bb = bb.unionbox ( kdtree[i]->getBBox() );

	computeDivision (bb, opt);

	generate_n ( back_inserter(_objindices), _kdtree.size(), Incr() );
	_kdtree._nodes.reserve (_kdtree.size()*5);

	transform ( _kdtree.begin(), _kdtree.end(), back_inserter(_objcenters), getBBCenter<ObjectType>() );

	int root = _kdtree.addNode ( -1, _kdtree.size() );

	divide (opt/*, bb*/);

	// set kdtree's objs in sorted order
	vector<ObjectType> objs;
	objs.reserve( _kdtree.size());
	for ( int i=0; i<_objindices.size(); i++ ) {
		objs.push_back ( _kdtree[_objindices[i]] );
	}
	_kdtree.swap ( objs );

#ifdef _USESTATISTIC_
	_buildFinishedClock = clock();
#endif
	//_kdtree.dump ( root, 0 );
}

template<class ObjectType>
template<class InputIterator>
inline BuildKdTree<ObjectType>::BuildKdTree ( KdTree<ObjectType>& kdtree, 
									  InputIterator begin, 
									  InputIterator end, 
									  /*BBox& bb,*/ const BuildKdTreeOption& opt ) 
									  : _kdtree(kdtree)
{
#ifdef _USESTATISTIC_
	_buildStartClock = clock();
#endif
	BBox bb;
	for ( int i=0; i<kdtree.size(); i++ )
		bb = bb.unionbox ( kdtree[i]->getBBox() );

	computeDivision (bb,opt);

	_kdtree.assign ( begin, end );
	_kdtree._nodes.reserve (_kdtree.size()*5);
	generate_n ( back_inserter(_objindices), _kdtree.size(), Incr() );

	transform ( _kdtree.begin(), _kdtree.end(), back_inserter(_objcenters), getBBCenter<ObjectType>() );

	int root = _kdtree.addNode ( -1, _kdtree.size() );

	divide (opt/*, bb*/);


	// set kdtree's objs in sorted order
	vector<ObjectType> objs;
	objs.reserve( _kdtree.size());
	for ( int i=0; i<_objindices.size(); i++ ) {
		objs.push_back ( _kdtree[_objindices[i]] );
	}
	_kdtree.swap ( objs );

#ifdef _USESTATISTIC_
	_buildFinishedClock = clock();
#endif
	//_kdtree.dump ( root, 0 );
}

template<class ObjectType>
inline void BuildKdTree<ObjectType>::computeDivision(const BBox& bb, const BuildKdTreeOption& opt )
{
#ifdef _DEBUG_OUTPUT_
	//LOG_DEBUG ( "begin computeDivision ... " );
#endif
	vec3f dimension;
	dimension = bb.max() - bb.min();

	int level = 0;
	while ( level < opt.maxlevel ) {
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

		//LOG_DEBUG ( "level=%d\taxis=%d\tdimension=(%f, %f, %f)", level, axis, dimension[0], dimension[1], dimension[2] );

		dimension[axis] /= 2.0f;
		++level;
	}

#ifdef _DEBUG_OUTPUT_
	//LOG_DEBUG ( "ok" );
#endif
}

//[istart, iend)
template<class ObjectType>
inline BBox BuildKdTree<ObjectType>::getBBox ( int istart, int iend )
{
	if ( (iend-istart)<1 )
		return BBox();

	BBox box = _kdtree[_objindices[istart]]->getBBox();
	for ( int i=istart+1; i<iend; i++ )
		box = box.unionbox ( _kdtree[_objindices[i]]->getBBox() );
	return box;
}

template <class Vec>
class IndexComp
{
public:
	IndexComp (vector<Vec>& vecs, int axis) : _vecs(vecs), _axis(axis) {}
	bool operator() ( int idx1, int idx2 ) {
		return (_vecs[idx1][_axis] < _vecs[idx2][_axis]);
	}
private:
	vector<Vec>& _vecs;
	int _axis;
};

//#include "time.h"
////[istart, iend)
//template<class ObjectType>
//void BuildKdTree<ObjectType>::sortindices ( int istart, int iend, int axis )
//{
//      IndexComp<vec3f> comp(_objcenters, axis);
//      std::sort ( _objindices.begin()+istart, _objindices.begin()+iend, comp );
//      //int clo = clock();
//      //qDebug ( "_ISORT_MAX=%d, sort %d clock, %f (ms)", _ISORT_MAX, clock() - clo,  (1000.0*(clock() - clo))/CLOCKS_PER_SEC );
//      //IndexVecSort<vec3f> sort(_objindices, _objcenters, axis);
//      //sort.sort ( istart, iend );
//      //std::sort ( istart, iend, IndexLesser(_objindices, _objcenters, axis) );
//
//      //for ( int i=istart; i<iend; i++ ) {
//      //      float t = _objcenters[_objindices[i]][axis];
//      //      for ( int j=i; j<iend; j++ ) {
//      //              float t1 = _objcenters[_objindices[j]][axis];
//      //              if ( t1 < t )
//      //                      swap ( _objindices[i], _objindices[j] );
//      //      }
//      //}
//}

//// [istart, iend)
//template<class ObjectType>
//int BuildKdTree<ObjectType>::getmidindex ( int istart, int iend, float mid, int axis )
//{
//      int len = 0;
//      for ( int i=istart; i<iend; i++, len++ ) {
//              if ( _objcenters[_objindices[i]][axis] > mid )
//                      break;
//      }
//      return istart + len - 1;
//}

template<class ObjectType>
inline void BuildKdTree<ObjectType>::divide ( const BuildKdTreeOption& opt, /*BBox& bb, */int nodeidx, int level )
{

	//while (1) 
	//{
	// if ( target number in this node < target number per leaf ) will stop divide 
	typename KdTree<ObjectType>::KdNode& node = _kdtree.getNode(nodeidx);
	int istart = -node.first-1;
	int iend   = istart + node.second;

	// set node.bb
	node.bb = getBBox ( istart, iend );

	if ( node.second <= opt.targetnumperleaf || level >= opt.maxlevel )
		return;

	int axis = _axisstack[level];

	// sort the indices from node.first to node.first + node.second
	IndexComp<vec3f> comp(_objcenters, axis);
	std::sort ( _objindices.begin()+istart, _objindices.begin()+iend, comp );
	//sortindices ( istart, iend, axis );

	// calculate left and right node's indices range
	//float mid = bb.center()[axis];
	//int imid = getmidindex ( istart, iend, mid, axis );
	int imid = istart + (iend - istart) / 2;
	//LOG_DEBUG ("\tistart=%d, iend=%d, mid=%f, axis=%d, imid=%d, left=%d, right=%d", istart, iend, mid, axis, imid, -istart-1, imid-istart );
#ifdef _DEBUG_OUTPUT1_
	stringstream ss, ss0;
	//for ( int i=0; i<_objindices.size(); i++ )
	//  ss << _objindices[i] << " ";
	for ( int i=0; i<level; i++ )
		ss0 << "  ";
	//qDebug ("%slevel=%d, istart=%d, iend=%d, imid=%d, axis=%d, indices=[%s]", ss0.str().c_str(), level, istart, iend, imid, axis, ss.str().c_str() );
	qDebug ("%slevel=%d, istart=%d, iend=%d, imid=%d, elementnum=%d, axis=%d", ss0.str().c_str(), level, istart, iend, imid, iend-istart, axis );
#endif
	node.first = _kdtree.addNode ( -istart-1, imid-istart );
	node.second = _kdtree.addNode( -imid-1, iend-imid );

	//  // use this condition to ensure stack depth bound = log(N)
	//  if ( (imid-istart) >= (iend-imid) ) 
	//  {
	//          float temp = bb.min()[axis];
	//          bb.min()[axis] = mid;
	//          divide ( opt, bb, node.second, level+1 );
	//          bb.min()[axis] = temp;

	//          nodeidx = node.first;
	//          level++;
	//  }
	//  else
	//  {
	//          float temp = bb.max()[axis];
	//          bb.max()[axis] = mid;
	//          divide ( opt, bb, node.first, level+1 );
	//          bb.max()[axis] = temp;

	//          nodeidx = node.second;
	//          level++;
	//  }
	//}
	//float temp = bb.max()[axis];
	//bb.max()[axis] = mid;
	divide ( opt, /*bb, */node.first, level+1 );
	//bb.max()[axis] = temp;

	// //LOG_DEBUG ("****istart=%d, iend=%d, mid=%f, axis=%d, imid=%d, left=%d, right=%d", istart, iend, mid, axis, imid, -imid-1, iend-imid );
	//temp = bb.min()[axis];
	//bb.min()[axis] = mid;
	divide ( opt, /*bb, */node.second, level+1 );
	//bb.min()[axis] = temp;
}

template<class ObjectType>
inline KdTree<ObjectType>::KdTree ()
{
#ifdef _USESTATISTIC_
	_bbcompcnt = 0;
#endif
}

template<class ObjectType>
inline BBox KdTree<ObjectType>::getBBox()
{
	if ( _nodes.empty() )
		return BBox();
	return _nodes.front().bb;
}

template<class ObjectType>
template<class Output >
inline bool KdTree<ObjectType>::intersect ( const BBox& box, Output out, int nodeidx )
{
#ifdef _USESTATISTIC_
	if ( nodeidx == 0 )
	{
		_selectedCount = _bbcompcnt = 0;
		_buildStartClock = clock();
	}
#endif 
	if ( nodeidx >= _nodes.size() || nodeidx < 0 )
	{
#ifdef _USESTATISTIC_
		if ( nodeidx == 0 )
			_buildFinishedClock = clock();
#endif
		return false;
	}

	KdNode& node = _nodes[nodeidx];

#ifdef _USESTATISTIC_
	_bbcompcnt++;
#endif 
	if ( !box.isIntersect ( node.bb ) ) 
	{
#ifdef _USESTATISTIC_
		if ( nodeidx == 0 )
			_buildFinishedClock = clock();
#endif
		return false;
	}

	if ( node.first >= 0 ) {  // if node is not leaf
		intersect ( box, out, node.first);
		intersect ( box, out, node.second );
	} else {  // if node is leaf 
		if ( node.second > 0 ) {
			int istart = -node.first-1;
			int iend = istart + node.second;
			for ( int i=istart; i!=iend; i++ ) {
				//BBox& bb = _objs[i]->getBBox();

#ifdef _USESTATISTIC_
				_bbcompcnt++;
#endif 

				if ( !box.isIntersect ( (*this)[i]->getBBox() ) )
					continue;

				*out++ = (*this)[i];
#ifdef _USESTATISTIC_
				_selectedCount++;
#endif 
			}
		}
	}

#ifdef _USESTATISTIC_
	if ( nodeidx == 0 )
		_buildFinishedClock = clock();
#endif 
	return true;
}


template<class ObjectType>
inline BuildKdTree<ObjectType>::~BuildKdTree () 
{
}

#ifdef _USESTATISTIC_
template<class ObjectType>
inline string KdTree<ObjectType>::memstatistic ()
{
	int nums = size();
	int objs = size() * sizeof(ObjectType);
	int heapalloc = size() * sizeof(Rectanglef);
	int nodes = _nodes.size() * sizeof(KdNode);
	double unit = 1000000.0;
	stringstream ss;
	ss << ">> statistic of KdTree" << endl;
	ss << "     nums = " << nums / unit << " (M)"  << endl;
	ss << "     objs = " << objs / unit << " (M)" << endl;
	ss << "     heapalloc = " << heapalloc / unit << " (M)"  << endl;
	ss << "     nodes = " << nodes / unit << " (M)"  << endl;
	ss << "==========================================" << endl;
	ss << "   total memory used = " << (objs+nodes+heapalloc)/unit << " (M)" << endl;
	return ss.str();
}

template<class ObjectType>
inline string KdTree<ObjectType>::intersectstatistic ()
{
	stringstream ss;
	ss << ">> statistic of KdTree" << endl;
	ss << "     bb compare times = " << _bbcompcnt  << endl;
	ss << "     time ellapse = " << (_buildFinishedClock - _buildStartClock)/(1.0*CLOCKS_PER_SEC) << " (s)" << endl;
	ss << "     number of selected items  = " << _selectedCount << endl;
	ss << "     select rate  = " << _selectedCount/(1.0*size()) << endl;
	return ss.str();
}

template<class ObjectType>
inline void KdTree<ObjectType>::dump ( int nodeIdx, int level  ) 
{
	KdNode& node = _nodes[nodeIdx];
	stringstream ss, ss0;
	for ( int i=0; i<level; i++ )
		ss0 << "  ";
	ss << ss0.str() << "DUMP kdtree:  level=" << level << "\tnodeidx=" << nodeIdx << "\tleft=" << node.first << "\tright=" << 
		node.second << "\tbbox={"<<node.bb.min().x()<<","<<node.bb.min().y()<<", "<<node.bb.max().x()<<","<<node.bb.max().y()<<"}";
	qDebug ( ss.str().c_str() );
	//LOG_INFO ( "DUMP kdtree:  level=%d\tleft=%d\tright=%d", level, node.first, node.second );
	if ( node.second == 0 )
		return;
	if ( node.first >=0 ) {
		dump ( node.first, level+1 );
		dump ( node.second, level+1 );
	}
	if ( level == 0 )
	{
		qDebug ( "size of object's container = %d", _objs.size() * 4 );
		qDebug ( "size of objects            = %d", _objs.size() * sizeof (*_objs[0]) );
		qDebug ( "size of nodes container    = %d", sizeof(_nodes) );
		qDebug ( "size of nodes              = %d", _nodes.size() * sizeof(_nodes[0]) );
	}
}

#endif
