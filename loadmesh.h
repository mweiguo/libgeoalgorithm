#ifndef _LOADMESH_H_
#define _LOADMESH_H_

#include <xml_xerceshelper.h>
#include "kdtree.h"
class SGNode;

template<class OptiPolicy>
class LoadMesh 
{
public:
	LoadMesh ( const char* fileName, SGNode* node, const OptiPolicy& opt );
private:
	void traverseNode ( XERCES_CPP_NAMESPACE::DOMElement* pnode, SGNode* data );
	void getShapeGenParas (int index, int& s1, int& s2, int& s3, int& s4, int& s5, int& s6, int level0Cnt, int level1Cnt, int level2Cnt, int level3Cnt, int level4Cnt, int level5Cnt );
private:
	SGNode* _root;
	OptiPolicy _opt;
};

class KdTreeOptimization
{
public:
	KdTreeOptimization ( KdTree<DrawableNode*>& kdtree );
	void addOptimizeNode ( DrawableNode* node );
	void optimize ();
private:
	KdTree<DrawableNode*>& _kdtree;
	BBox _bb;
};

class NoOptimize
{
public:
	void addOptimizeNode ( DrawableNode* node );
	void optimize ();
};

#include "loadmesh.cpp"

#endif

