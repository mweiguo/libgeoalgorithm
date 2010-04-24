#ifndef _UNITTEST_KDTREE_H_
#define _UNITTEST_KDTREE_H_

#include <list>
#include <algorithm>
#include "bbox.h"
#include "rectitem.h"
#include "kdtree.h"
#include <tinylog.h>

using namespace std;

class kdtreeTest
{
public:
  kdtreeTest() {
    KdTree<ARectItem*> kdtree;
    ARectItem* item[5];
    BBox bb;
    LOG_INFO ( "begin setting up items" );
    item[0] = new ARectItem ( 0, 0, 2, 2 );
    bb = bb.unionbox ( item[0]->getBBox() );
    item[1] = new ARectItem ( 0, 0, 2, 2 );
    bb = bb.unionbox ( item[1]->getBBox() );
    item[2] = new ARectItem ( 0, 0, 2, 2 );
    bb = bb.unionbox ( item[2]->getBBox() );
    item[3] = new ARectItem ( 0, 0, 2, 2 );
    bb = bb.unionbox ( item[3]->getBBox() );
    item[4] = new ARectItem ( 0, 0, 2, 2 );
    bb = bb.unionbox ( item[4]->getBBox() );
    
    bb.dump();

    LOG_INFO ( "items setting up finished" );
    LOG_INFO ( "begin build kdtree" );
    BuildKdTree<ARectItem*>::targetnumperleaf = 1;
    BuildKdTree<ARectItem*> build ( kdtree, item, item+5, bb );
    LOG_INFO ( "kdtree built finished" );

    
    list<ARectItem*> items;
    LOG_INFO ( "begin test intersect interface of kdtree" );
    kdtree.intersect (vec3f(0,0,0), vec3f(1,3,0), back_inserter(items) );
    LOG_INFO ( "kdtree intersect finished" );
  }
};


#endif
