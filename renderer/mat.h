#ifndef _MAT2_H_
#define _MAT2_H_

#define _USE_MATH_DEFINES
#include <math.h>
template < class ValueType >
class mat2
{
public:
  typedef mat2 self;
  typedef const mat2& const_reference;

  mat2 ( ValueType a00, ValueType a01, ValueType a10, ValueType a11 ) {
    m[0][0] = a00;
    m[0][1] = a01;
    m[1][0] = a10;
    m[1][1] = a11;
  }
  mat2 operator* ( const_reference rhs );

  template < class Vec >
  Vec operator * ( const Vec& rhs ) const
  {
    typename Vec::value_type t  = m[0][0]*rhs.x() + m[0][1]*rhs.y();
    typename Vec::value_type t1 = m[1][0]*rhs.x() + m[1][1]*rhs.y();
    return Vec ( t, t1 );
  }

  static mat2 rotate_matrix ( float angle );
  static mat2 scale_matrix ( ValueType sx, ValueType sy );
private:
  ValueType m[2][2];
};

template < class ValueType >
mat2<ValueType> mat2<ValueType>::rotate_matrix ( float angle )
{
  
  float alpha = angle * M_PI / 180;
  return mat2<ValueType> ( cos(alpha), -sin(alpha),
			   sin(alpha), cos(alpha) );
}

template < class ValueType >
mat2<ValueType> mat2<ValueType>::scale_matrix ( ValueType sx, ValueType sy )
{
  return mat2<ValueType> ( sx, 0, 0, sy );
}

template < class ValueType >
inline mat2<ValueType> mat2<ValueType>::operator* ( const_reference rhs )
{
  return mat2<ValueType> ( m[0][0]*rhs.m[0][0] + m[0][1]*rhs.m[1][0],
			   m[0][0]*rhs.m[0][1] + m[0][1]*rhs.m[1][1],
			   m[1][0]*rhs.m[0][1] + m[1][1]*rhs.m[1][1],
			   m[1][0]*rhs.m[0][1] + m[1][1]*rhs.m[1][1] );		    
}

// template < class ValueType, class Vec >
// inline Vec mat2<ValueType>::operator * ( const Vec& rhs ) const
// {
//   typename Vec::value_type t  = m[0][0]*rhs.x() + m[0][1]*rhs.y();
//   typename Vec::value_type t1 = m[1][0]*rhs.x() + m[1][1]*rhs.y();
//   return Vec ( t, t1 );

// }
#endif
