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
    NodesVector() {}
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
	T* pp = NULL;
	(*this)[id] = pp = new T();
	NodesVector::getInst().push_back ( pp );
	return id;
    }
private:
    NodeMgr () {}
};

#endif
