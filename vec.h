#pragma once
#include <cmath>

template < class ValueType >
class vec2
{
public:
  typedef ValueType value_type;
  typedef const vector2d const_type;
public:
  // constructor
  vec2 ( value_type* v ) { _x = v[0]; _y = v[1]; }
  vec2 ( value_type x1, value_type y1 ) : _x(x1), _y(y1) {}
  // getter & setter
  vec2 xx() { return vec2(_x,_x); }
  vec2 xy() { return *this; }
  vec2 yx() { return vec2(_y,_x); }
  vec2 yy() { return vec2(_y,_y); }
  value_type x() { return _x; }
  value_type y() { return _y; }

  void x( value_type v ) { _x = v; }
  void y( value_type v ) { _y = v; }
  void xy( vec2 v ) { _x = v._x; _y = v._y; }
  void yx( vec2 v ) { _x = v._y; _y = v._x; }
public:
  value_type mod () { return sqrt(_x*_x + _y*_y); }
  vector2d operator - ( vector2d::const_type rhs ) { return vector2d ( x - rhs.x,  y - rhs.y ); }
protected:
  value_type _x, _y;
};

template < class ValueType >
class vec3 : public vec2
{
public:
  typedef ValueType value_type;
  typedef const vector2d const_type;
public:
  // constructor
  vec3 ( value_type* v ) : vec2( v ) { _z = v[2]; }
  vec3 ( value_type x1, value_type y1, value_type z1 ) : vec2(x1, y1), _z:(z1) {}
  // getter & setter
  vec3 xxx()             { return vec3(_x, _x, _x); }
  vec3 xxy()             { return vec3(_x, _x, _y); }
  vec3 xxz()             { return vec3(_x, _x, _z); }
  vec3 xyx()             { return vec3(_x, _y, _x); }
  vec3 xyy()             { return vec3(_x, _y, _y); }
  vec3 xyz()             { return vec3(_x, _y, _z); }
  vec3 xzx()             { return vec3(_x, _z, _x); }
  vec3 xzy()             { return vec3(_x, _z, _y); }
  vec3 xzz()             { return vec3(_x, _z, _z); }
  vec2 xz()              { return vec2(_x, _z); }
  vec2 yz()              { return vec2(_y, _z); }
  vec2 zx()              { return vec2(_z, _x); }
  vec2 zy()              { return vec2(_z, _y); }
  vec2 zz()              { return vec2(_z, _z); }
  value_type z()         { return _z; }
  void xyz( vec3 v )     { _x = v._x; _y = v._y; _z = v._z; }
  void xzy( vec3 v )     { _x = v._x; _y = v._z; _z = v._y; }
  void yxz( vec3 v )     { _x = v._y; _y = v._x; _z = v._z; }
  void yzx( vec3 v )     { _x = v._y; _y = v._z; _z = v._x; }
  void zxy( vec3 v )     { _x = v._z; _y = v._x; _z = v._y; }
  void zyx( vec3 v )     { _x = v._x; _y = v._y; _z = v._x; }
  void xz( vec2 v )      { _x = v._x; _y = v._z; }
  void yz( vec2 v )      { _x = v._y; _y = v._z; }
  void zx( vec2 v )      { _x = v._z; _y = v._x; }
  void zy( vec2 v )      { _x = v._z; _y = v._y; }
  void z( value_type v ) { _z = v; }
public:
  value_type mod () { return sqrt(x*x + y*y); }
  vector2d operator - ( vector2d::const_type rhs ) { return vector2d ( x - rhs.x,  y - rhs.y ); }
public:
  value_type _z;
};
