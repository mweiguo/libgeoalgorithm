#ifndef _UNITTEST_KDTREE_H_
#define _UNITTEST_KDTREE_H_

class kdtreeTest
{
  kdtreeTest() {
    KdTree kdtree;
    BuildKdTree build ( kdtree, boxes.begin(), boxes.end() );
  }
};


#endif
