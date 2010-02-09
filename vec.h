#pragma once
#include <cmath>

template < class ValueType >
class vec2
{
public:
  typedef vec2<ValueType> self;
  typedef vec2<ValueType>& reference;
  typedef ValueType value_type;
  typedef const vec2 const_reference;
public:
  // constructor
  vec2 ( value_type* v ) { _x = v[0]; _y = v[1]; }
  vec2 ( value_type x1, value_type y1 ) : _x(x1), _y(y1) {}
  // getter & setter
  vec2 xx() const { return vec2(_x,_x); }
  vec2 xy() const { return *this; }
  vec2 yx() const { return vec2(_y,_x); }
  vec2 yy() const { return vec2(_y,_y); }
  value_type x() const { return _x; }
  value_type y() const { return _y; }

  void x( value_type v ) { _x = v; }
  void y( value_type v ) { _y = v; }
  void xy( vec2 v ) { _x = v._x; _y = v._y; }
  void yx( vec2 v ) { _x = v._y; _y = v._x; }
public:
  reference normal ();
  self mod ( value_type length );
  value_type mod ();
  self operator - ( const_reference rhs );
  reference operator *= ( value_type rhs );
protected:
  value_type _x, _y;
};


template < class ValueType >
class vec3 : public vec2<ValueType>
{
public:
  typedef ValueType value_type;
  typedef const vec3 const_type;
public:
  // constructor
  vec3 ( value_type* v ) : vec2<ValueType>( v ) { _z = v[2]; }
  vec3 ( value_type x1, value_type y1, value_type z1 ) : vec2<ValueType>(x1, y1), _z(z1) {}
  // getter & setter
  vec3 xxx()             { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_x, vec2<ValueType>::_x); }
  vec3 xxy()             { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_x, vec2<ValueType>::_y); }
  vec3 xxz()             { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_x, vec2<ValueType>::_z); }
  vec3 xyx()             { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_y, vec2<ValueType>::_x); }
  vec3 xyy()             { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_y, vec2<ValueType>::_y); }
  vec3 xyz()             { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_y, vec2<ValueType>::_z); }
  vec3 xzx()             { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_z, vec2<ValueType>::_x); }
  vec3 xzy()             { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_z, vec2<ValueType>::_y); }
  vec3 xzz()             { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_z, vec2<ValueType>::_z); }
  vec2<ValueType> xz()   { return vec2<ValueType>(vec2<ValueType>::_x, vec2<ValueType>::_z); }
  vec2<ValueType> yz()   { return vec2<ValueType>(vec2<ValueType>::_y, vec2<ValueType>::_z); }
  vec2<ValueType> zx()   { return vec2<ValueType>(vec2<ValueType>::_z, vec2<ValueType>::_x); }
  vec2<ValueType> zy()   { return vec2<ValueType>(vec2<ValueType>::_z, vec2<ValueType>::_y); }
  vec2<ValueType> zz()   { return vec2<ValueType>(vec2<ValueType>::_z, vec2<ValueType>::_z); }
  value_type z()         { return vec2<ValueType>::_z; }
  void xyz( vec3 v )     { vec2<ValueType>::_x = v._x; vec2<ValueType>::_y = v._y; vec2<ValueType>::_z = v._z; }
  void xzy( vec3 v )     { vec2<ValueType>::_x = v._x; vec2<ValueType>::_y = v._z; vec2<ValueType>::_z = v._y; }
  void yxz( vec3 v )     { vec2<ValueType>::_x = v._y; vec2<ValueType>::_y = v._x; vec2<ValueType>::_z = v._z; }
  void yzx( vec3 v )     { vec2<ValueType>::_x = v._y; vec2<ValueType>::_y = v._z; vec2<ValueType>::_z = v._x; }
  void zxy( vec3 v )     { vec2<ValueType>::_x = v._z; vec2<ValueType>::_y = v._x; vec2<ValueType>::_z = v._y; }
  void zyx( vec3 v )     { vec2<ValueType>::_x = v._x; vec2<ValueType>::_y = v._y; vec2<ValueType>::_z = v._x; }
  void xz( vec2<ValueType> v )      { vec2<ValueType>::_x = v._x; vec2<ValueType>::_y = v._z; }
  void yz( vec2<ValueType> v )      { vec2<ValueType>::_x = v._y; vec2<ValueType>::_y = v._z; }
  void zx( vec2<ValueType> v )      { vec2<ValueType>::_x = v._z; vec2<ValueType>::_y = v._x; }
  void zy( vec2<ValueType> v )      { vec2<ValueType>::_x = v._z; vec2<ValueType>::_y = v._y; }
  void z( value_type v ) { vec2<ValueType>::_z = v; }
public:
  value_type mod ()
  { 
    return sqrt(vec2<ValueType>::_x * vec2<ValueType>::_x + vec2<ValueType>::_y * vec2<ValueType>::_y); 
  }
  vec3 operator - ( const_type rhs )
  { 
    return vec3<ValueType> ( vec2<ValueType>::_x - rhs.x,  vec2<ValueType>::_y - rhs.y, vec2<ValueType>::_z - rhs.z ); 
  }
public:
  value_type _z;
};


// vec2
template < class ValueType >
inline typename vec2<ValueType>::reference vec2<ValueType>::normal () 
{ 
  typename vec2<ValueType>::value_type m = mod (); 
  _x /= m; 
  _y /= m; 
  return *this;
}

template < class ValueType >
inline vec2<ValueType> vec2<ValueType>::mod ( ValueType length ) 
{ 
  normal();
  *this *= length;
  return *this;
}

template < class ValueType >
inline ValueType vec2<ValueType>::mod ()
{
  return sqrt(_x*_x + _y*_y); 
}

template < class ValueType >
inline vec2<ValueType> vec2<ValueType>::operator - ( typename vec2<ValueType>::const_reference rhs )
{
  return vec2 ( _x - rhs._x,  _y - rhs._y ); 
}

template < class ValueType >
inline typename vec2<ValueType>::reference vec2<ValueType>::operator *= ( ValueType rhs )
{
  _x *= rhs;
  _y *= rhs;
  return *this;
}


// vec3
