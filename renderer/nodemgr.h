#ifndef _NODEMGR_H_
#define _NODEMGR_H_

#include <map>
#include <vector>
#include "sgnode.h"
using namespace std;

// class NodesVector : public vector<SGNode*>
// {
// public:
//     static NodesVector& getInst()
//     {
//         static NodesVector inst;
//         return inst;
//     }
// private:
//     NodesVector() 
//     {
//         push_back ( new SGNode() ); 
//     }
// };
//
// template < class T >
// class NodeMgr : public std::map<int, T*>
// {
// public:
//     static NodeMgr<T>& getInst () 
//     {
//         static NodeMgr<T> inst;
//         return inst;
//     }
//     int addNode ()
//     {
//         int id = NodesVector::getInst().size();
//         (*this)[id] = _lastNode = new T();
//         NodesVector::getInst().push_back ( _lastNode );
//         return id;
//     }
//     int addNode ( const T& node )
//     {
//         int id = NodesVector::getInst().size();
//         (*this)[id] = _lastNode = new T(node);
//         NodesVector::getInst().push_back ( _lastNode );
//         return id;
//     }
//     T* lastNode () { return _lastNode; }
// private:
//     NodeMgr () {}
//     T* _lastNode;
// };
class SeedGenerator
{
public:
    static SeedGenerator& getInst ()
    {
        static SeedGenerator inst;
        return inst;
    }
    int seed() { return _seed++; }
private:
    SeedGenerator()
    {
        _seed = 0;
    }
    int _seed;

};

class NodeMgr : public std::map<int, SGNode*>
{
public:
    static NodeMgr& getInst ()
    {
        static NodeMgr inst;
        return inst;
    }

    template < class T >
    int addNode ()
    {
        int seed = SeedGenerator::getInst().seed();
        (*this)[seed] = _lastNode = new T();
        return seed;
    }

    template < class T >
    T* getNodePtr ( int id )
    {
        iterator pp=find ( id );
        if ( pp == end() )
            return NULL;
        T* p = dynamic_cast<T*>(pp->second);
        return p;
    }

    //template < class T >
    //int addNode ( const T& node )
    //{
    //    //        int id = NodesVector::getInst().size();
    //    (*this)[_seed] = _lastNode = new T(node);
    //    //        NodesVector::getInst().push_back ( _lastNode );
    //    return _seed++;
    //}
    //SGNode* lastNode () { return _lastNode; }
    SGNode* root() { return _root; }
private:
    NodeMgr () 
    {
        addNode<SGNode>();
        _root = (*this)[0];
    }
    SGNode* _lastNode, *_root;
};

#endif
