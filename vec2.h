#ifndef _VEC2_H_
#define _VEC2_H_

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
    vec2 ( const Vec& v ) { _v[0] = v.x(); _v[1] = v.y(); }
    vec2 ( value_type* v ) { _v[0] = v[0]; _v[1] = v[1]; }
    vec2 ( value_type x1=0, value_type y1=0 ) { _v[0] = x1; _v[1] = y1; }
    // getter & setter
    vec2 xx() const { return vec2(_v[0],_v[0]); }
    vec2 xy() const { return *this; }
    vec2 yx() const { return vec2(_v[1],_v[0]); }
    vec2 yy() const { return vec2(_v[1],_v[1]); }
    value_type x() const { return _v[0]; }
    value_type y() const { return _v[1]; }
    value_type w() const { return _v[0]; }
    value_type h() const { return _v[1]; }

    void x( value_type v ) { _v[0] = v; }
    void y( value_type v ) { _v[1] = v; }
    void w( value_type v ) { _v[0] = v; }
    void h( value_type v ) { _v[1] = v; }
    void xy( vec2 v ) { _v[0] = v.x(); _v[1] = v.y(); }
    void yx( vec2 v ) { _v[0] = v.y(); _v[1] = v.x(); }
public:
    reference normal ();
    self mod ( value_type length );
    value_type mod ();
    self operator - ( const_reference rhs );
    reference operator *= ( value_type rhs ); 
    vec2 operator = ( const vec2& rhs );
    vec2 operator + ( const vec2& rhs );
    value_type& operator[] (int idx)       { return _v[idx]; }
    value_type operator[] (int idx) const  { return _v[idx]; }

protected:
    value_type _v[2];
};


// vec2
template < class ValueType >
inline typename vec2<ValueType>::reference vec2<ValueType>::normal () 
{ 
    typename vec2<ValueType>::value_type m = mod (); 
    if ( m != 0 ) {
        _v[0] /= m; 
        _v[1] /= m; 
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
    return sqrt((double)(_v[0]*_v[0] + _v[1]*_v[1])); 
}

template < class ValueType >
inline vec2<ValueType> vec2<ValueType>::operator - ( typename vec2<ValueType>::const_reference rhs )
{
    return vec2 ( _v[0] - rhs._v[0],  _v[1] - rhs._v[1] ); 
}

template < class ValueType >
inline typename vec2<ValueType>::reference vec2<ValueType>::operator *= ( ValueType rhs )
{
    _v[0] *= rhs;
    _v[1] *= rhs;
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

typedef vec2<float> vec2f;
typedef vec2<double> vec2d;
typedef vec2<int> vec2i;
typedef vec2<short> vec2s;

#endif
