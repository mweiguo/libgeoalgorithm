#ifndef _VEC4_H_
#define _VEC4_H_

#include "vec2.h"
#include "vec3.h"

template < class ValueType >
class vec4
{
public:
    typedef ValueType value_type;
    typedef vec4<ValueType> self;
    typedef vec4<ValueType>& reference;
    typedef const vec4<ValueType>& const_reference;
public:
    // constructor
    vec4 ( const vec2<ValueType>& v0, const vec2<ValueType>& v1=vec2<ValueType>(0,1)) { _v[0]=v0[0]; _v[1]=v0[1]; _v[2]=v1[0]; _v[3]=v1[1]; }
    vec4 ( const vec3<ValueType>& v3, ValueType v=1 ) { _v[0]=v3[0]; _v[1]=v3[1]; _v[2]=v3[2]; _v[3] = v; }
    vec4 ( value_type* v ) { _v[0] = v[0]; _v[1] = v[1]; _v[2] = v[2]; _v[3] = v[3]; }
    vec4 ( value_type x1=0, value_type y1=0, value_type z1=0, value_type w1=1 ) { _v[0] = x1; _v[1] = y1; _v[2] = z1; _v[3] = w1; }
    // getter & setter
    vec4 xyzw() const              { return vec4(_v[0], _v[1], _v[2], _v[3]); }
    vec3<ValueType> xxx() const    { return vec3<ValueType>(_v[0], _v[0], _v[0]); }
    vec3<ValueType> xxy() const    { return vec3<ValueType>(_v[0], _v[0], _v[1]); }
    vec3<ValueType> xxz() const    { return vec3<ValueType>(_v[0], _v[0], _v[2]); }
    vec3<ValueType> xyx() const    { return vec3<ValueType>(_v[0], _v[1], _v[0]); }
    vec3<ValueType> xyy() const    { return vec3<ValueType>(_v[0], _v[1], _v[1]); }
    vec3<ValueType> xyz() const    { return vec3<ValueType>(_v[0], _v[1], _v[2]); }
    vec3<ValueType> xzx() const    { return vec3<ValueType>(_v[0], _v[2], _v[0]); }
    vec3<ValueType> xzy() const    { return vec3<ValueType>(_v[0], _v[2], _v[1]); }
    vec3<ValueType> xzz() const    { return vec3<ValueType>(_v[0], _v[2], _v[2]); }
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
    value_type w() const           { return _v[3]; }
    void xyzw( ValueType v0, ValueType v1, ValueType v2, ValueType v3 ) { _v[0] = v0; _v[1] = v1; _v[2] = v2; _v[3] = v3; }
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
    void w( value_type v )         { _v[3] = v; }
public:
    value_type mod ();
    reference operator = ( const_reference rhs );
    vec4 operator + ( const_reference rhs );
    vec4 operator - ( const_reference rhs ) const;
    vec4 operator / ( double rhs );
    value_type& operator[] (int idx)       { return _v[idx]; }
    value_type operator[] (int idx) const  { return _v[idx]; }
public:
    value_type _v[4];
};

// vec3
template < class ValueType >
inline ValueType vec4<ValueType>::mod ()
{ 
    double x = x() / w();
    double y = y() / w();
    double z = z() / w();
    return sqrt( x*x + y*y + z*z ); 
}



template < class ValueType >
inline typename vec4<ValueType>::reference vec4<ValueType>::operator = ( const_reference rhs )
{ 
    xyzw ( rhs.x(), rhs.y(), rhs.z(), rhs.w() );
    return *this;
}

template < class ValueType >
inline typename vec4<ValueType>::self vec4<ValueType>::operator + ( const_reference rhs )
{ 
    return vec3<ValueType> ( x() + rhs.x(),  y() + rhs.y(), z() + rhs.z(), w() + rhs.w() ); 
}

template < class ValueType >
inline typename vec4<ValueType>::self vec4<ValueType>::operator - ( const_reference rhs ) const
{ 
    return self ( x() - rhs.x(),  y() - rhs.y(), z() - rhs.z(), w() - rhs.w() ); 
}

template < class ValueType >
inline typename vec4<ValueType>::self vec4<ValueType>::operator / ( double rhs )
{ 
    return self ( x()/rhs,  y()/rhs, z()/rhs, w()/rhs ); 
}

typedef vec4<float>  vec4f;
typedef vec4<int>    vec4i;
typedef vec4<double> vec4d;

#endif
