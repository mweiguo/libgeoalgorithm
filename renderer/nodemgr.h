#ifndef _NODEMGR_H_
#define _NODEMGR_H_

#include <map>
#include <vector>
#include "sgnode.h"
using namespace std;

class NodesVector : public vector<SGNode*>
{
public:
    static NodesVector& getInst()
    {
        static NodesVector inst;
        return inst;
    }
private:
    NodesVector() 
    {
        push_back ( new SGNode() ); 
    }
};


template < class T >
class NodeMgr : public std::map<int, T*>
{
public:
    static NodeMgr<T>& getInst () 
    {
        static NodeMgr<T> inst;
        return inst;
    }
    int addNode ()
    {
        int id = NodesVector::getInst().size();
        (*this)[id] = _lastNode = new T();
        NodesVector::getInst().push_back ( _lastNode );
        return id;
    }
    int addNode ( const T& node )
    {
        int id = NodesVector::getInst().size();
        (*this)[id] = _lastNode = new T(node);
        NodesVector::getInst().push_back ( _lastNode );
        return id;
    }
    T* lastNode () { return _lastNode; }
private:
    NodeMgr () {}
    T* _lastNode;
};

#endif
