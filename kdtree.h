#ifndef _KDTREE_H_
#define _KDTREE_H_


class KdTree
{
  struct KdNode {
    KdNode ( int f, int s ) : first(f), second(s) {}
    int first, second;
    BBox bb;
  };
public:
  template<class Vec, class Output>
  bool findobj ( Vec& s, Vec& e, Output out );
private:
  int addNode ( int f, int s ) { _nodes.push_back ( KdNode(f, s) ); return _nodes.size()-1; }
private:
  KdNode _root;
  vector<ObjectType> _objs;
  vector<KdNode> _nodes;
};

class BuildKdTree
{
public:
  typedef vec3<float> vec3f;
  template<class Input>
  BuildKdTree ( KdTree& _kdtree, Input begin, Input end );
private:
  void computeDivision(const BBox& bb );
  void divide ();

  KdTree& _kdtree;
  vector<int> _axisstack;
  vector<int> _objindices;
  vector<vec3f> _objcenters;
};

#endif
