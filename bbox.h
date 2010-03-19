#ifndef _BBOX_H
#define _BBOX_H

class BBox
{
public:
  typedef vec3<float> vec3f;
  BBox () {}
  BBox ( vec3f& min, vec3f& max ) : _min(min), _max(max) {}
  vec3f& min() const { return _min; }
  vec3f& max() const { return _max; }
  void min ( vec3f& v ) { _min = v; }
  void max ( vec3f& v ) { _max = v; }
  vec3f center ();
  void expandby ( vec3f& pnt );
private:
  vec3f _min, _max;
};

#endif
