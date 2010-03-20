#include "vec3.h"
#include "mat.h"
#include "unittest_vec.h"
//#include "alg_unittest.h"
#include <iostream>
#include <tinylog.h>

using namespace std;


int main ()
{
  try {
    vec3Test v3test ( 1, 2, 0);
    //    algTest algtest;  
  } catch ( exception& e ) {
    LOG_INFO ( "%s", e.what() );
  }
  LOG_INFO ( "all unit test passed" );
  
  //   // float t[] = {2,2};
  //   vec2<float> v1(0, 22);
  //   vec2<float> v2(22, 0);
  //   vec2<float> v(v1-v2);
  //   v.normal();
  //   v.mod ( 2 );
  //   v *= 4;
  //   mat2<float> m = mat2<float>::rotate_matrix( -90 );
  //   v = m * v;
  
  //   mat2<float> ms = mat2<float>::scale_matrix( 0.5, 0.5 );
  //   v = ms * v;

  //   cout << "x=" << v.x() << ", y=" << v.y() << endl;
  //   cout << "mod=" << v.mod() << endl;
  return 0;
}
