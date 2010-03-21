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
  vec3 ( value_type x1=0, value_type y1=0, value_type z1=0 ) { _v[0] = x1; _v[1] = y1; _v[2] = z1; }
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
  void xyz( ValueType v0, ValueType v1, ValueType v2 ) { _v[0] = v0; _v[1] = v1; _v[2] = v2; }
  void xzy( ValueType v0, ValueType v1, ValueType v2 ) { _v[0] = v0; _v[2] = v1; _v[1] = v2; }
  void yxz( ValueType v0, ValueType v1, ValueType v2 ) { _v[1] = v0; _v[0] = v1; _v[2] = v2; }
  void yzx( ValueType v0, ValueType v1, ValueType v2 ) { _v[1] = v0; _v[2] = v1; _v[0] = v2; }
  void zxy( ValueType v0, ValueType v1, ValueType v2 ) { _v[2] = v0; _v[0] = v1; _v[1] = v2; }
  void zyx( ValueType v0, ValueType v1, ValueType v2 ) { _v[2] = v0; _v[1] = v1; _v[0] = v2; }
  void xz( ValueType v0, ValueType v1 )   { _v[0] = v0; _v[2] = v1; }
  void yz( ValueType v0, ValueType v1 )   { _v[1] = v0; _v[2] = v1; }
  void zx( ValueType v0, ValueType v1 )   { _v[2] = v0; _v[0] = v1; }
  void zy( ValueType v0, ValueType v1 )   { _v[2] = v0; _v[1] = v1; }
  void x( value_type v )         { _v[0] = v; }
  void y( value_type v )         { _v[1] = v; }
  void z( value_type v )         { _v[2] = v; }
public:
  value_type mod ();
  vec3 operator = ( const_reference rhs );
  vec3 operator + ( const_reference rhs );
  vec3 operator - ( const_reference rhs );
  vec3 operator / ( double rhs );
  value_type& operator[] (int idx)       { return _v[idx]; }
  value_type operator[] (int idx) const  { return _v[idx]; }
  vec3 cross ( const_reference rhs );
  vec3 min ( const_reference rhs );
  vec3 max ( const_reference rhs );
public:
  value_type _v[3];
};

// vec3
template < class ValueType >
inline ValueType vec3<ValueType>::mod ()
{ 
  return sqrt((double)(x() * x() + y() * y()) ); 
}

template < class ValueType >
inline vec3<ValueType> vec3<ValueType>::operator = ( const vec3<ValueType>& rhs )
{ 
  xyz ( rhs.x(), rhs.y(), rhs.z() );
  return *this;
}

template < class ValueType >
inline vec3<ValueType> vec3<ValueType>::operator + ( const vec3<ValueType>& rhs )
{ 
  return vec3<ValueType> ( x() + rhs.x(),  y() + rhs.y(), z() + rhs.z() ); 
}

template < class ValueType >
inline vec3<ValueType> vec3<ValueType>::operator - ( const vec3<ValueType>& rhs )
{ 
  return vec3<ValueType> ( x() - rhs.x(),  y() - rhs.y(), z() - rhs.z() ); 
}

template < class ValueType >
inline vec3<ValueType> vec3<ValueType>::operator / ( double rhs )
{ 
  return vec3<ValueType> ( x() / rhs,  y() / rhs, z() / rhs ); 
}

template < class ValueType >
inline vec3<ValueType> vec3<ValueType>::cross ( const vec3<ValueType>& rhs )
{
  return vec3<ValueType> ( y() * rhs.z() - rhs.y() * z(), 
		z() * rhs.x() - x() * rhs.z(),
		x() * rhs.y() - rhs.x() * y() );
} 

template < class ValueType >
inline vec3<ValueType> vec3<ValueType>::min ( const vec3<ValueType>& rhs )
{
  return vec3<ValueType> ( x() < rhs.x() ? x() : rhs.x(),
			   y() < rhs.y() ? y() : rhs.y(),
			   z() < rhs.z() ? z() : rhs.z() );
} 

template < class ValueType >
inline vec3<ValueType> vec3<ValueType>::max ( const vec3<ValueType>& rhs )
{
  return vec3<ValueType> ( x() > rhs.x() ? x() : rhs.x(),
			   y() > rhs.y() ? y() : rhs.y(),
			   z() > rhs.z() ? z() : rhs.z() );
} 

#endif
