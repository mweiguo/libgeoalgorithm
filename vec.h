#ifndef _VEC_H_
#define _VEC_H_

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
  template< class Vec >
  vec2 ( const Vec& v ) { _x = v.x(); _y = v.y(); }
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
  vec2 operator = ( const vec2& rhs );
  vec2 operator + ( const vec2& rhs );

protected:
  value_type _x, _y;
};

template < class ValueType >
class vec3 : public vec2<ValueType>
{
public:
  typedef ValueType value_type;
  typedef const vec3& const_reference;
public:
  // constructor
  vec3 ( const vec2<ValueType> v2 ) : vec2<ValueType>( v2 ) { _z = 0; }
  vec3 ( value_type* v ) : vec2<ValueType>( v ) { _z = v[2]; }
  vec3 ( value_type x1, value_type y1, value_type z1 ) : vec2<ValueType>(x1, y1), _z(z1) {}
  // getter & setter
  vec3 xxx() const               { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_x, vec2<ValueType>::_x); }
  vec3 xxy() const               { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_x, vec2<ValueType>::_y); }
  vec3 xxz() const               { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_x, vec2<ValueType>::_z); }
  vec3 xyx() const               { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_y, vec2<ValueType>::_x); }
  vec3 xyy() const               { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_y, vec2<ValueType>::_y); }
  vec3 xyz() const               { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_y, vec2<ValueType>::_z); }
  vec3 xzx() const               { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_z, vec2<ValueType>::_x); }
  vec3 xzy() const               { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_z, vec2<ValueType>::_y); }
  vec3 xzz() const               { return vec3(vec2<ValueType>::_x, vec2<ValueType>::_z, vec2<ValueType>::_z); }
  vec2<ValueType> xz() const     { return vec2<ValueType>(vec2<ValueType>::_x, vec2<ValueType>::_z); }
  vec2<ValueType> yz() const     { return vec2<ValueType>(vec2<ValueType>::_y, vec2<ValueType>::_z); }
  vec2<ValueType> zx() const     { return vec2<ValueType>(vec2<ValueType>::_z, vec2<ValueType>::_x); }
  vec2<ValueType> zy() const     { return vec2<ValueType>(vec2<ValueType>::_z, vec2<ValueType>::_y); }
  vec2<ValueType> zz() const     { return vec2<ValueType>(vec2<ValueType>::_z, vec2<ValueType>::_z); }
  value_type z() const           { return _z; }
  void xyz( vec3 v )             { vec2<ValueType>::_x = v._x; vec2<ValueType>::_y = v._y; vec2<ValueType>::_z = v._z; }
  void xzy( vec3 v )             { vec2<ValueType>::_x = v._x; vec2<ValueType>::_y = v._z; vec2<ValueType>::_z = v._y; }
  void yxz( vec3 v )             { vec2<ValueType>::_x = v._y; vec2<ValueType>::_y = v._x; vec2<ValueType>::_z = v._z; }
  void yzx( vec3 v )             { vec2<ValueType>::_x = v._y; vec2<ValueType>::_y = v._z; vec2<ValueType>::_z = v._x; }
  void zxy( vec3 v )             { vec2<ValueType>::_x = v._z; vec2<ValueType>::_y = v._x; vec2<ValueType>::_z = v._y; }
  void zyx( vec3 v )             { vec2<ValueType>::_x = v._x; vec2<ValueType>::_y = v._y; vec2<ValueType>::_z = v._x; }
  void xz( vec2<ValueType> v )   { vec2<ValueType>::_x = v._x; vec2<ValueType>::_y = v._z; }
  void yz( vec2<ValueType> v )   { vec2<ValueType>::_x = v._y; vec2<ValueType>::_y = v._z; }
  void zx( vec2<ValueType> v )   { vec2<ValueType>::_x = v._z; vec2<ValueType>::_y = v._x; }
  void zy( vec2<ValueType> v )   { vec2<ValueType>::_x = v._z; vec2<ValueType>::_y = v._y; }
  void z( value_type v )         { vec2<ValueType>::_z = v; }
public:
  value_type mod ();
  vec3 operator - ( const_reference rhs );
  vec3 cross ( const_reference rhs );
public:
  value_type _z;
};


// vec2
template < class ValueType >
inline typename vec2<ValueType>::reference vec2<ValueType>::normal () 
{ 
  typename vec2<ValueType>::value_type m = mod (); 
  if ( m != 0 )
  {
	  _x /= m; 
	  _y /= m; 
  }
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
  return sqrt((double)(_x*_x + _y*_y)); 
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

template < class ValueType >
inline vec2<ValueType> vec2<ValueType>::operator = ( const vec2<ValueType>& rhs )
{
	x ( rhs.x() );
	y ( rhs.y() );
	return *this;
}

template < class ValueType >
inline vec2<ValueType> vec2<ValueType>::operator + ( const vec2<ValueType>& rhs )
{
	x ( x() + rhs.x() );
	y ( y() + rhs.y() );
	return *this;
}

// vec3
template < class ValueType >
inline ValueType vec3<ValueType>::mod ()
{ 
  typedef vec2<ValueType> vec2t;
  return sqrt((double)(vec2t::x() * vec2t::x() + vec2t::y() * vec2t::y()) ); 
}

template < class ValueType >
inline vec3<ValueType> vec3<ValueType>::operator - ( const vec3<ValueType>& rhs )
{ 
  typedef vec2<ValueType> vec2t;
  return vec3<ValueType> ( vec2t::x() - rhs.x(),  vec2t::y() - rhs.y(), z() - rhs.z() ); 
}

template < class ValueType >
inline vec3<ValueType> vec3<ValueType>::cross ( const vec3<ValueType>& rhs )
{
  typedef vec2<ValueType> vec2t;
  return vec3<ValueType> ( vec2t::y() * rhs.z() - rhs.y() * z(), 
		z() * rhs.x() - vec2t::x() * rhs.z(),
		vec2t::x() * rhs.y() - rhs.x() * vec2t::y() );
} 
#endif
