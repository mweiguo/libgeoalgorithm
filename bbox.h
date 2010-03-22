#ifndef _BBOX_H
#define _BBOX_H

#include "vec3.h"
#include "algorithm"
#include <tinylog.h>

class BBox
{
public:
  // constructor
  BBox () {}
  BBox ( const BBox& rhs ) { _min=rhs.min(); _max=rhs.max(); }
  BBox ( vec3f& min, vec3f& max ) : _min(min), _max(max) {}
  // min/max
  const vec3f& min() const { return _min; }
  const vec3f& max() const { return _max; }
  vec3f& min() { return _min; }
  vec3f& max() { return _max; }
  void init ( const vec3f& v ) { _min = v; _max=v; }
  // other operations
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
  void dump () {
#ifdef _DEBUG_OUTPUT_
    LOG_DEBUG ( "min=(%f,%f,%f)\tmax=(%f,%f,%f)", _min.x(), _min.y(), _min.z(), _max.x(), _max.y(), _max.z() );
#endif
  }
private:
  vec3f _min, _max;
};



#endif
