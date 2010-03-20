#ifndef _VEC3_H_
#define _VEC3_H_

#include "vec2.h"

template < class ValueType >
class vec3
{
public:
  typedef ValueType value_type;
  typedef const vec3& const_reference;
public:
  // constructor
  vec3 ( const vec2<ValueType> v2 ) { _v[0]=v2[0]; _v[1]=v2[1]; _v[2]=0; }
  vec3 ( value_type* v ) { _v[0] = v[0]; _v[1] = v[1]; _v[2] = v[2]; }
  vec3 ( value_type x1, value_type y1, value_type z1 ) { _v[0] = x1; _v[1] = y1; _v[2] = z1; }
  // getter & setter
  vec3 xxx() const               { return vec3(_v[0], _v[0], _v[0]); }
  vec3 xxy() const               { return vec3(_v[0], _v[0], _v[1]); }
  vec3 xxz() const               { return vec3(_v[0], _v[0], _v[2]); }
  vec3 xyx() const               { return vec3(_v[0], _v[1], _v[0]); }
  vec3 xyy() const               { return vec3(_v[0], _v[1], _v[1]); }
  vec3 xyz() const               { return vec3(_v[0], _v[1], _v[2]); }
  vec3 xzx() const               { return vec3(_v[0], _v[2], _v[0]); }
  vec3 xzy() const               { return vec3(_v[0], _v[2], _v[1]); }
  vec3 xzz() const               { return vec3(_v[0], _v[2], _v[2]); }
  vec2<ValueType> xx() const     { return vec2<ValueType>(_v[0], _v[0]); }
  vec2<ValueType> xy() const     { return vec2<ValueType>(_v[0], _v[1]); }
  vec2<ValueType> xz() const     { return vec2<ValueType>(_v[0], _v[2]); }
  vec2<ValueType> yx() const     { return vec2<ValueType>(_v[1], _v[0]); }
  vec2<ValueType> yy() const     { return vec2<ValueType>(_v[1], _v[1]); }
  vec2<ValueType> yz() const     { return vec2<ValueType>(_v[1], _v[2]); }
  vec2<ValueType> zx() const     { return vec2<ValueType>(_v[2], _v[0]); }
  vec2<ValueType> zy() const     { return vec2<ValueType>(_v[2], _v[1]); }
  vec2<ValueType> zz() const     { return vec2<ValueType>(_v[2], _v[2]); }
  value_type x() const           { return _v[0]; }
  value_type y() const           { return _v[1]; }
  value_type z() const           { return _v[2]; }
  void xyz( vec3 v )             { _v[0] = v[0]; _v[1] = v[1]; _v[2] = v[2]; }
  void xzy( vec3 v )             { _v[0] = v[0]; _v[1] = v[2]; _v[2] = v[1]; }
  void yxz( vec3 v )             { _v[0] = v[1]; _v[1] = v[0]; _v[2] = v[2]; }
  void yzx( vec3 v )             { _v[0] = v[1]; _v[1] = v[2]; _v[2] = v[0]; }
  void zxy( vec3 v )             { _v[0] = v[2]; _v[1] = v[0]; _v[2] = v[1]; }
  void zyx( vec3 v )             { _v[0] = v[2]; _v[1] = v[1]; _v[2] = v[0]; }
  void xz( vec2<ValueType> v )   { _v[0] = v[0]; _v[2] = v[2]; }
  void yz( vec2<ValueType> v )   { _v[1] = v[1]; _v[2] = v[2]; }
  void zx( vec2<ValueType> v )   { _v[2] = v[2]; _v[0] = v[0]; }
  void zy( vec2<ValueType> v )   { _v[2] = v[2]; _v[1] = v[1]; }
  void x( value_type v )         { _v[0] = v; }
  void y( value_type v )         { _v[1] = v; }
  void z( value_type v )         { _v[2] = v; }
public:
  value_type mod ();
  vec3 operator - ( const_reference rhs );
  value_type& operator[] (int idx)       { return _v[idx]; }
  value_type operator[] (int idx) const  { return _v[idx]; }
  vec3 cross ( const_reference rhs );
public:
  value_type _v[3];
};

// vec3
template < class ValueType >
inline ValueType vec3<ValueType>::mod ()
{ 
  typedef vec2<ValueType> vec2t;
  return sqrt((double)(x() * x() + y() * y()) ); 
}

template < class ValueType >
inline vec3<ValueType> vec3<ValueType>::operator - ( const vec3<ValueType>& rhs )
{ 
  typedef vec2<ValueType> vec2t;
  return vec3<ValueType> ( x() - rhs.x(),  y() - rhs.y(), z() - rhs.z() ); 
}

template < class ValueType >
inline vec3<ValueType> vec3<ValueType>::cross ( const vec3<ValueType>& rhs )
{
  typedef vec2<ValueType> vec2t;
  return vec3<ValueType> ( y() * rhs.z() - rhs.y() * z(), 
		z() * rhs.x() - x() * rhs.z(),
		x() * rhs.y() - rhs.x() * y() );
} 

#endif
