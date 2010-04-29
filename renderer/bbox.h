#ifndef _BBOX_H
#define _BBOX_H

#include "vec3.h"
#include "algorithm"
#include <sstream>
//#include <tinylog.h>

class BBox
{
public:
    // constructor
    BBox () {}
    BBox ( const BBox& rhs ) { _min=rhs.min(); _max=rhs.max(); }
    BBox ( const vec3f& min, const vec3f& max ) : _min(min), _max(max) {}
    // min/max
    const vec3f& min() const { return _min; }
    const vec3f& max() const { return _max; }
    vec3f& min() { return _min; }
    vec3f& max() { return _max; }
    void init ( const vec3f& v ) { _min = v; _max=v; }
    // other operations
    vec3f center () const { return ( _min + _max ) / 2; }
    void expandby ( const vec3f& pnt ) {
        _min = _min.min ( pnt );
        _max = _max.max ( pnt );
    }
    BBox unionbox ( const BBox& rhs ) const {
        BBox t = *this;
        t.expandby ( rhs.min() );
        t.expandby ( rhs.max() );
        return t;
    }
    bool isIntersect ( const BBox& rhs ) const {
        if ( max().x() < rhs.min().x() || max().y() < rhs.min().y() ||
             min().x() > rhs.max().x() || min().y() > rhs.max().y() )
            return false;
        return true;
    }
    string dump () {
        stringstream ss;
        ss << "min=("<<_min.x()<<"," << _min.y() << "," << _min.z() << ")\tmax=(" << _max.x() << "," << _max.y() << "," << _max.z() << ")";
        return ss.str();
        //LOG_DEBUG ( "min=(%f,%f,%f)\tmax=(%f,%f,%f)", _min.x(), _min.y(), _min.z(), _max.x(), _max.y(), _max.z() );
    }
private:
    vec3f _min, _max;
};



#endif
