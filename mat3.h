#ifndef _MAT3_H_
#define _MAT3_H_

#define _USE_MATH_DEFINES
#include <math.h>

template < class ValueType >
class mat3
{
public:
  typedef mat3 self;
  typedef const mat3& const_reference;

  mat3 ( ValueType a00, ValueType a01, ValueType a02, 
	 ValueType a10, ValueType a11, ValueType a12, 
	 ValueType a20, ValueType a21, ValueType a12 ) {
    m[0][0] = a00; m[0][1] = a01; m[0][2] = a02;
    m[1][0] = a10; m[1][1] = a11; m[1][2] = a12;
    m[2][0] = a20; m[2][1] = a21; m[2][2] = a22;
  }
  mat3 operator* ( const_reference rhs );

  template < class Vec >
  Vec operator * ( const Vec& rhs ) const
  {
    typename Vec::value_type t  = m[0][0]*rhs.x() + m[0][1]*rhs.y() + m[0][2]*rhs.z();
    typename Vec::value_type t1 = m[1][0]*rhs.x() + m[1][1]*rhs.y() + m[1][2]*rhs.z();
    typename Vec::value_type t2 = m[2][0]*rhs.x() + m[2][1]*rhs.y() + m[2][2]*rhs.z();
    return Vec ( t, t1, t2 );
  }

  
  static mat3 rotate_matrix ( float angle );
  static mat3 scale_matrix ( ValueType sx, ValueType sy );
private:
  ValueType m[3][3];
};

template < class ValueType >
mat3<ValueType> mat3<ValueType>::rotate_matrix ( float angle )
{
  
  float alpha = angle * M_PI / 180;
  return mat3<ValueType> ( cos(alpha), -sin(alpha), 0,
			   sin(alpha), cos(alpha), 0, 
			   0, 0, 1 );
}

template < class ValueType >
mat3<ValueType> mat3<ValueType>::scale_matrix ( ValueType sx, ValueType sy )
{
  return mat3<ValueType> ( sx, 0, 0, 0, sy, 0, 0, 0, 1 );
}

template < class ValueType >
inline mat3<ValueType> mat3<ValueType>::operator* ( const_reference rhs )
{
  return mat3<ValueType> ( m[0][0]*rhs.m[0][0] + m[0][1]*rhs.m[1][0] + m[0][2]*rhs.m[2][0], 
			   m[0][0]*rhs.m[0][1] + m[0][1]*rhs.m[1][1] + m[0][2]*rhs.m[2][1],
			   m[0][0]*rhs.m[0][2] + m[0][1]*rhs.m[1][2] + m[0][2]*rhs.m[2][2],
			   m[1][0]*rhs.m[0][0] + m[1][1]*rhs.m[1][0] + m[1][2]*rhs.m[2][0], 
			   m[1][0]*rhs.m[0][1] + m[1][1]*rhs.m[1][1] + m[1][1]*rhs.m[2][1],
			   m[1][0]*rhs.m[0][2] + m[1][1]*rhs.m[1][2] + m[1][1]*rhs.m[2][2],
			   m[2][0]*rhs.m[0][0] + m[2][1]*rhs.m[1][0] + m[2][2]*rhs.m[2][0], 
			   m[2][0]*rhs.m[0][1] + m[2][1]*rhs.m[1][1] + m[2][1]*rhs.m[2][1],
			   m[2][0]*rhs.m[0][2] + m[2][1]*rhs.m[1][2] + m[2][1]*rhs.m[2][2]
			   );		    
}

#endif
