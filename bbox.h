#ifndef _BBOX_H
#define _BBOX_H

#include "vec3.h"
#include "algorithm"

class BBox
{
public:
  typedef vec3<float> vec3f;
  BBox () {}
  BBox ( const BBox& rhs ) { _min=rhs.min(); _max=rhs.max(); }
  BBox ( vec3f& min, vec3f& max ) : _min(min), _max(max) {}
  const vec3f& min() const { return _min; }
  const vec3f& max() const { return _max; }
  void min ( vec3f& v ) { _min = v; }
  void max ( vec3f& v ) { _max = v; }
  vec3f center () { return ( _min + _max ) / 2; }
  void expandby ( const vec3f& pnt ) {
    _min = _min.min ( pnt );
    _max = _max.max ( pnt );
  }
  BBox unionbox ( const BBox& rhs ) {
    BBox t = *this;
    t.expandby ( rhs.min() );
    t.expandby ( rhs.max() );
    return t;
  }
private:
  vec3f _min, _max;
};



#endif
