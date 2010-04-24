#ifndef _LODMGR_H_
#define _LODMGR_H_

#include <map>
#include <utility>

class KdTree;
class LodMgr
{
public:
    KdTree* selectPresentation ( float dist ) {
        map<pair<float, float>>,Kdtree*>::iterator pp, end=lodModels.end();
        for ( pp=lodModels.begin(); pp!=end; ++pp ) {
            if ( dist < pp->first.first || dist > pp->first.second )
                continue;
            return pp->second;
        }
        return NULL;
    }
    LodMgr& getInst() {
        static LodMgr inst;
        return inst;
    }
private:
    map<pair<float, float>>, KdTree*> lodModels;
};


#endif
