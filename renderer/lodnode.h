#ifndef _LOD_NODE_H_
#define _LOD_NODE_H_

#include "sgnode.h"
#include "kdtree.h"
#include "rendernodecollector.h"
#include <vector>


class LODNode : public virtual SGNode
{
public:
	typedef vector<float>::iterator diterator;
	typedef vector<float>::const_iterator const_diterator;
    LODNode () {}
    // in proj mode, v is dist
    // in ortho mode, v is scale
    SpatialObjectMgr* selectPresentation ( float v ) 
    {
        typedef vector<float> DefLevel;
        DefLevel::iterator pp = upper_bound ( levelDelimiters.begin(), levelDelimiters.end(), v );
        return lodModels[ (pp - levelDelimiters.begin()) ];
    }
    void setdelimiters ( const string& str ) 
    {
        vector<string> tokens;
        vector<float> floattokens;
        istringstream iss(str);
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));
        for ( vector<string>::iterator pp=tokens.begin(); pp!=tokens.end(); ++pp )
            floattokens.push_back ( atof(pp->c_str()) );
        levelDelimiters.assign ( floattokens.begin(), floattokens.end() );
    }
    template < class Input >
    void assigndelimiters ( Input begin, Input end ) { levelDelimiters.assign ( begin, end); }
    void buildsom ();
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~LODNode () {}
	diterator dbegin() { return levelDelimiters.begin(); }
	diterator dend() { return levelDelimiters.end(); }
	const_diterator dbegin() const { return levelDelimiters.begin(); }
	const_diterator dend() const { return levelDelimiters.begin(); }
private:
    // in proj mode, levelDelimiters is dist array
    // in ortho mode, levelDelimiters is scale array
    vector<float> levelDelimiters;
    vector<SpatialObjectMgr*> lodModels;
};

#include <time.h>
// build spatial objects management
inline void LODNode::buildsom ()
{
    if ( lodModels.size() != (levelDelimiters.size()+1) ) {
        lodModels.reserve ( levelDelimiters.size()+1 );
        for ( int i=0; i<=levelDelimiters.size(); i++ )
            lodModels.push_back ( new SpatialObjectMgr() );
    }

    int i =0;
    for ( iterator pp=this->begin(); pp!=end(); ++pp, i++ )
        {
			lodModels[i]->reset();
#ifdef _USESTATISTIC_
            int clo = clock();
#endif          
            RenderNodeCollector< back_insert_iterator<SpatialObjectMgr> > collector(back_inserter(*lodModels[i]) );
            (*pp)->accept ( collector );
#ifdef _USESTATISTIC_
            qDebug ( "collect nodes TAKE %d clock, %f (s)", clock() - clo,  (1.0*(clock() - clo))/CLOCKS_PER_SEC );
            clo = clock();
#endif          
            BuildSpatialObjectMgr build ( *lodModels[i]/*, collector.begin(), collector.end()*/ );
#ifdef _USESTATISTIC_
            qDebug ( "%s", build.statistic().c_str() );
            qDebug ( "%s", lodModels[i]->memstatistic().c_str() );
#endif          
        }
}

#endif
