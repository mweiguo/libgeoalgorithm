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

#endif
