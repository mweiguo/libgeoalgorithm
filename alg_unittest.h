#ifndef _ALG_UNITTEST_H_
#define _ALG_UNITTEST_H_

#include "alg.hpp"
#include "indexiter.h"
#include <stdexcept>
#include <iostream>
using namespace std;

class algTest
{
public:
  algTest() 
  {
    //is_leftside_test();
    get_visiblepoints_test ();
  }
  void is_leftside_test ()
  {
    typedef vec2<float> vec2f;
    if ( is_leftside ( vec2f(1,0), vec2f(0,0), vec2f(1,1) ) )
      throw logic_error ("is_leftside_test failed");
    if ( !is_leftside ( vec2f(1,0), vec2f(1,1), vec2f(0,0) ) )
      throw logic_error ("is_leftside_test failed");
    if ( is_leftside ( vec2f(0.5,0.5), vec2f(0,0), vec2f(1,1) ) )
      throw logic_error ("is_leftside_test failed");
  }
  void get_visiblepoints_test ()
  {
    typedef vec2<float> vec2f;
    typedef vec3<float> vec3f;
    typedef IndexIterator<vec3f> idxiter;
    vector<vec3f> points;
    points.push_back ( vec3f(0, 0, 0) );
    points.push_back ( vec3f(1, 0, 0) );
    points.push_back ( vec3f(1, 1, 0) );
    points.push_back ( vec3f(0, 1, 0) );
    
    idxiter begin( &points, 0 );
    idxiter end( &points, points.size() );

    {
      vector<idxiter> out;
      get_visiblepoints ( vec2f(0.5, -1), begin, end, back_inserter(out) );
      if ( out.size() != 2 || out[0].index() != 0 || out[1].index() != 1 )
	throw logic_error ("is_leftside_test failed 0");
    }

    {
      vector<idxiter> out;
      get_visiblepoints ( vec2f(1.5, -1), begin, end, back_inserter(out) );
      if ( out.size() != 3 || out[0].index() != 0 || out[1].index() != 1 || out[2].index() != 2 )
	throw logic_error ("is_leftside_test failed 1");
    }

    {
      vector<idxiter> out;
      get_visiblepoints ( vec2f(1.5, .5), begin, end, back_inserter(out) );
      if ( out.size() != 2 || out[0].index() != 1 || out[1].index() != 2 )
	throw logic_error ("is_leftside_test failed 2");
    }

    {
      vector<idxiter> out;
      get_visiblepoints ( vec2f(1.5, 1.5), begin, end, back_inserter(out) );
      if ( out.size() != 3 || out[0].index() != 1 || out[1].index() != 2 || out[2].index() != 3 )
	throw logic_error ("is_leftside_test failed 3");
    }

    {
      vector<idxiter> out;
      get_visiblepoints ( vec2f(.5, 1.5), begin, end, back_inserter(out) );
      if ( out.size() != 2 || out[0].index() != 2 || out[1].index() != 3)
	throw logic_error ("is_leftside_test failed 4");
    }

    {
      vector<idxiter> out;
      get_visiblepoints ( vec2f(-.5, 1.5), begin, end, back_inserter(out) );
      if ( out.size() != 3 || out[0].index() != 2 || out[1].index() != 3 || out[2].index() != 0) {
	throw logic_error ("is_leftside_test failed 5");
      }
    }

    {
      vector<idxiter> out;
      get_visiblepoints ( vec2f(-.5, .5), begin, end, back_inserter(out) );
      if ( out.size() != 2 || out[0].index() != 3 || out[1].index() != 0 )
	throw logic_error ("is_leftside_test failed 6");
    }
    
    {
      vector<idxiter> out;
      get_visiblepoints ( vec2f(-.5, -.5), begin, end, back_inserter(out) );
      if ( out.size() != 3 || out[0].index() != 3 || out[1].index() != 0 || out[2].index() != 1 ) {
	cout << "out.size=" << out.size() << ", out[0]=" << out[0].index() << ", out[1]=" << out[1].index()
	      << ", out[2]=" << out[2].index() << ", out[3]=" << out[3].index() << endl;
	throw logic_error ("is_leftside_test failed 7");
      }
    }

  }
};

#endif
