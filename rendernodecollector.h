#ifndef _RENDERNODE_COLLECTOR_
#define _RENDERNODE_COLLECTOR_

#include "nodevisitor.h"
#include "rectitem.h"
#include "transformnode.h"
#include "arraynode.h"
#include "mat4.h"
#include "vec2.h"
#include "vec4.h"

#include <vector>
#include <string>
#include <sstream>
using namespace std;

template<class Output>
class RenderNodeCollector : public NodeVisitor
{
public:
    typedef vector<DrawableNode*>::iterator iterator;
    typedef vector<DrawableNode*>::const_iterator const_iterator;
    RenderNodeCollector(Output& output) : _result(output) {}
    virtual void apply ( Rectanglef& node );
    virtual void apply ( TransformNode& node );
    virtual void apply ( ArrayNode& node );
private:
    Output& _result;
    mat4f _curmat;
};

template<class Output>
void RenderNodeCollector<Output>::apply ( Rectanglef& node )
{
    vec2f v = (_curmat * vec4f (0,0,0,1)).xy();
    *_result++ = new Rectanglef(v.x(), v.y(), node.w(), node.h() );
    
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
}

template<class Output>
void RenderNodeCollector<Output>::apply ( TransformNode& node )
{
    const mat4f& m = node.getMatrix(), oldmat = _curmat;
    _curmat = m * _curmat;
    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
        (*pp)->accept ( *this );
    _curmat = oldmat;
}

template<class Output>
void RenderNodeCollector<Output>::apply ( ArrayNode& node )
{
    //_result.reserve ( node.rowCnt() * node.columnCnt() * 8);
    for ( int j=0; j<node.rowCnt(); j++ ) {
        float y = node.getVOffset ( j );
        for ( int k=0; k<node.columnCnt(); k++ ) {
            float x = node.getHOffset ( k );
            // generate new matrix & use this matrix
            mat4f m = mat4f::translate_matrix ( x, y, 0 ), oldmat = _curmat;
            _curmat = m * _curmat;
            for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
                (*pp)->accept ( *this );
            _curmat = oldmat;
        }
    }
}

#endif
