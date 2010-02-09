#ifndef __VEC_UNITTEST_H_
#define __VEC_UNITTEST_H_

#include "vec.h"
#include <stdexcept>

using namespace std;
class vec3Test : public vec3<float>
{
public:
  typedef vec3<float> vec3f;
  vec3Test (float x1, float y1, float z1) : vec3f(x1,y1,z1)
  {
    modTest ();
    subTest ();
    crossTest();
  }
  void modTest ()
  {
    if ( sqrt(x() * x() + y() * y() + z() * z()) != mod() )
      throw logic_error ( "modTest failed" );
  }
  void subTest ()
  {
    vec3f t ( _x+1, _y+1, _z+1 );
    vec3f t1 = t - *this;
    if ( t1.x() != 1 || t1.y() != 1 || t1.z() != 1 )
      throw logic_error ( "subTest failed" );
  }
  void crossTest()
  {
    vec3f t ( _x+1, _y+2, _z+3 );
    vec3f t1 = this->cross ( t );

    if ( t1.x() != y() * t.z() - z() * t.y() ||
	 t1.y() != z() * t.x() - x() * t.z() ||
	 t1.z() != x() * t.y() - y() * t.x() )
      throw logic_error ( "crossTest failed" );
  }
};

#endif
