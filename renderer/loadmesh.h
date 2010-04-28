#ifndef _LOADMESH_H_
#define _LOADMESH_H_

#include <xml_xerceshelper.h>
#include <algorithm>
#include <time.h>
#include "arraynode.h"
#include "transformnode.h"
#include "rectitem.h"
#include "scenemgr.h"
//#include "sombuilder.h"
#include "arrayexpander.h"
#include "parentfinder.h"

/* #include "kdtree.h" */
class SGNode;

// template<class OptiPolicy>
class LoadMesh 
{
public:
    LoadMesh ( const char* fileName/*, SGNode* node , const OptiPolicy& opt  */);
    int root () { return _root; }
private:
    void clearall ();
    void traverseNode ( XERCES_CPP_NAMESPACE::DOMElement* pnode, int data );
    void getShapeGenParas (int index, int& s1, int& s2, int& s3, int& s4, int& s5, int& s6, int level0Cnt, int level1Cnt, int level2Cnt, int level3Cnt, int level4Cnt, int level5Cnt );
private:
    int _root;
    vector<ArrayNode*> _arraynodes;  // only save top arraynode
    vector<KdTreeNode*> _kdtreenodes;  // only save top kdtreenode
};

inline void LoadMesh::clearall ()
{
    vector<SGNode*> tmp;
    copy ( NodesVector::getInst().begin()+1, NodesVector::getInst().end(), back_inserter(tmp) );
    NodesVector::getInst()[0]->removeAllChild ();
    NodesVector::getInst().erase ( NodesVector::getInst().begin()+1, NodesVector::getInst().end() );
    for ( vector<SGNode*>::iterator pp=tmp.begin(); pp!=tmp.end(); ++pp )
        delete *pp;
    
    LayerNodeMgr::getInst().clear();
    RectanglefMgr::getInst().clear();
    TransformNodeMgr::getInst().clear();
    ArrayNodeMgr::getInst().clear();
    LODNodeMgr::getInst().clear();
    PickableGroupMgr::getInst().clear();
    KdTreeNodeMgr::getInst().clear();
    MeshNodeMgr::getInst().clear();
    ViewportMgr::getInst().clear();
    CameraMgr::getInst().clear();
}

inline LoadMesh::LoadMesh ( const char* fileName/*, SGNode* node , const OptiPolicy& opt */ )// : _opt(opt)
{
    clearall ();
    int clo = clock();
    XercesParser parser;
    XERCES_CPP_NAMESPACE::DOMDocument* doc = parser.parseFile ( fileName, false);
    if(doc == NULL)     
        throw logic_error("Fail to load Shape Template");

    DOMElement* root = doc->getDocumentElement();
    if (root == NULL) 
        throw logic_error("invalid Shape Template file:");
    //char* tagName = (char*)XercesHelper::getTagName (root);
    qDebug ( "parseFile TAKE %d clock, %f (s)", clock() - clo,  (1.0*(clock() - clo))/CLOCKS_PER_SEC );

    clo = clock();
    _root = mesh_create ();
    add_child ( 0, _root );
    traverseNode ( root, _root );
    qDebug ( "traverseNode TAKE %d clock, %f (s)", clock() - clo,  (1.0*(clock() - clo))/CLOCKS_PER_SEC );

    // expand array node
    for ( vector<ArrayNode*>::iterator pp=_arraynodes.begin(); pp!=_arraynodes.end(); ++pp )
    {
        ArrayNode* node = *pp;
        SGNode* parent = node->getParentNode();
        node->setParentNode ( NULL );
        ArrayExpander expander ( parent );
        expander ( *(*pp) );
        copy ( expander.kdbegin(), expander.kdend(), back_inserter(_kdtreenodes) );
    }

    // if exists kdtree, build it
    for ( vector<KdTreeNode*>::iterator pp=_kdtreenodes.begin(); pp!=_kdtreenodes.end(); ++pp )
    {
        (*pp)->buildKdTree ();
    }

    //SomBuilder sombuilder;
    //_root->accept ( sombuilder );
}

inline void LoadMesh::traverseNode ( XERCES_CPP_NAMESPACE::DOMElement* pnode, int parent )
{
    typedef vector<XERCES_CPP_NAMESPACE::DOMElement*> DOMElements;
    
    DOMElements tagLayers = XercesHelper::getChildElementsByTagName ( pnode, "layer" );
    for ( DOMElements::iterator pp=tagLayers.begin(); pp!=tagLayers.end(); ++pp ) {
        DOMElement* tagLayer  = static_cast<DOMElement*>(*pp);
        int layerid = layer_create ("");

        if ( XercesHelper::hasAttribute ( tagLayer, "isVisible" ) ) {
            string tmp = (char*)XercesHelper::getAttribute ( tagLayer, "isVisible" );
            if ( tmp == "1" ) layer_visible ( layerid, true );
            else if ( tmp == "0" ) layer_visible( layerid, false );
        }
        if ( XercesHelper::hasAttribute ( tagLayer, "name" ) )
            layer_name ( layerid, (char*)XercesHelper::getAttribute ( tagLayer, "name" ) );
        add_child ( parent, layerid );
        traverseNode ( tagLayer, layerid );
    }

    DOMElements tagPickables = XercesHelper::getChildElementsByTagName ( pnode, "pickablegroup" );
    for ( DOMElements::iterator pp=tagPickables.begin(); pp!=tagPickables.end(); ++pp ) {
        DOMElement* tagPickable  = static_cast<DOMElement*>(*pp);
        int id = pickablegroup_create ();

        if ( XercesHelper::hasAttribute ( tagPickable, "name" ) )
            pickablegroup_name ( id, (char*)XercesHelper::getAttribute ( tagPickable, "name" ) );
        add_child ( parent, id );
        traverseNode ( tagPickable, id );
    }

    DOMElements tagLods = XercesHelper::getChildElementsByTagName ( pnode, "lod" );
    for ( DOMElements::iterator pp=tagLods.begin(); pp!=tagLods.end(); ++pp ) {
        DOMElement* tagLod  = static_cast<DOMElement*>(*pp);
        int id = lod_create ();

        // setting up layer node's properties
        if ( XercesHelper::hasAttribute ( tagLod, "range" ) )
            lod_delimiters ( id, (char*)XercesHelper::getAttribute ( tagLod, "range" ) );
        add_child ( parent, id );
        traverseNode ( tagLod, id );
    }

    DOMElements tagKdTrees = XercesHelper::getChildElementsByTagName ( pnode, "kdtree" );
    for ( DOMElements::iterator pp=tagKdTrees.begin(); pp!=tagKdTrees.end(); ++pp ) {
        DOMElement* tagKdTree  = static_cast<DOMElement*>(*pp);
        int id = kdtree_create();
	KdTreeNode* kdtreenode = KdTreeNodeMgr::getInst()[id];
	ParentFinder<KdTreeNode> finder;
	if ( NULL == finder ( kdtreenode ) )
	    _kdtreenodes.push_back ( kdtreenode );
	_kdtreenodes.push_back ( kdtreenode );
        add_child ( parent, id );
        traverseNode ( tagKdTree, id );
    }

    DOMElements tagTransforms = XercesHelper::getChildElementsByTagName ( pnode, "transform" );
    for ( DOMElements::iterator pp=tagTransforms.begin(); pp!=tagTransforms.end(); ++pp ) {
        DOMElement* tagTransform  = static_cast<DOMElement*>(*pp);
        int id = transform_create ();

        // setting up layer node's properties
        if ( XercesHelper::hasAttribute ( tagTransform, "translate" ) )
            transform_translate ( id, (char*)XercesHelper::getAttribute ( tagTransform, "translate" ) );

        if ( XercesHelper::hasAttribute ( tagTransform, "scale" ) )
            transform_scale ( id, (char*)XercesHelper::getAttribute ( tagTransform, "scale" ) );

        add_child ( parent, id );
        traverseNode ( tagTransform, id );
    }

    DOMElements tagArrays = XercesHelper::getChildElementsByTagName ( pnode, "array" );
    for ( DOMElements::iterator pp=tagArrays.begin(); pp!=tagArrays.end(); ++pp ) {
        DOMElement* tagArray = static_cast<DOMElement*>( *pp );
        int id = array_create();
	ArrayNode* arraynode = ArrayNodeMgr::getInst()[id];
	ParentFinder<KdTreeNode> finder;
	if ( NULL == finder ( arraynode ) )
	    _arraynodes.push_back ( arraynode );

        if ( XercesHelper::hasAttribute ( tagArray, "cnty" ) ) array_rowcnt ( id, atoi((char*)XercesHelper::getAttribute( tagArray, "cnty" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "cntx" ) ) array_columncnt ( id, atoi((char*)XercesHelper::getAttribute( tagArray, "cntx" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level0hcnt" ) ) array_hlevelcnt ( id, 0, atoi((char*)XercesHelper::getAttribute( tagArray, "level0hcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level1hcnt" ) ) array_hlevelcnt ( id, 1, atoi((char*)XercesHelper::getAttribute( tagArray, "level1hcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level2hcnt" ) ) array_hlevelcnt ( id, 2, atoi((char*)XercesHelper::getAttribute( tagArray, "level2hcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level3hcnt" ) ) array_hlevelcnt ( id, 3, atoi((char*)XercesHelper::getAttribute( tagArray, "level3hcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level4hcnt" ) ) array_hlevelcnt ( id, 4, atoi((char*)XercesHelper::getAttribute( tagArray, "level4hcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level5hcnt" ) ) array_hlevelcnt ( id, 5, atoi((char*)XercesHelper::getAttribute( tagArray, "level5hcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level0vcnt" ) ) array_vlevelcnt ( id, 0, atoi((char*)XercesHelper::getAttribute( tagArray, "level0vcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level1vcnt" ) ) array_vlevelcnt ( id, 1, atoi((char*)XercesHelper::getAttribute( tagArray, "level1vcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level2vcnt" ) ) array_vlevelcnt ( id, 2, atoi((char*)XercesHelper::getAttribute( tagArray, "level2vcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level3vcnt" ) ) array_vlevelcnt ( id, 3, atoi((char*)XercesHelper::getAttribute( tagArray, "level3vcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level4vcnt" ) ) array_vlevelcnt ( id, 4, atoi((char*)XercesHelper::getAttribute( tagArray, "level4vcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level5vcnt" ) ) array_vlevelcnt ( id, 5, atoi((char*)XercesHelper::getAttribute( tagArray, "level5vcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacex1" ) ) array_marginx ( id, 0, atof((char*)XercesHelper::getAttribute( tagArray, "spacex1" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacex2" ) ) array_marginx ( id, 1, atof((char*)XercesHelper::getAttribute( tagArray, "spacex2" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacex3" ) ) array_marginx ( id, 2, atof((char*)XercesHelper::getAttribute( tagArray, "spacex3" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacex4" ) ) array_marginx ( id, 3, atof((char*)XercesHelper::getAttribute( tagArray, "spacex4" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacex5" ) ) array_marginx ( id, 4, atof((char*)XercesHelper::getAttribute( tagArray, "spacex5" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacex6" ) ) array_marginx ( id, 5, atof((char*)XercesHelper::getAttribute( tagArray, "spacex6" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacey1" ) ) array_marginy ( id, 0, atof((char*)XercesHelper::getAttribute( tagArray, "spacey1" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacey2" ) ) array_marginy ( id, 1, atof((char*)XercesHelper::getAttribute( tagArray, "spacey2" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacey3" ) ) array_marginy ( id, 2, atof((char*)XercesHelper::getAttribute( tagArray, "spacey3" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacey4" ) ) array_marginy ( id, 3, atof((char*)XercesHelper::getAttribute( tagArray, "spacey4" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacey5" ) ) array_marginy ( id, 4, atof((char*)XercesHelper::getAttribute( tagArray, "spacey5" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacey6" ) ) array_marginy ( id, 5, atof((char*)XercesHelper::getAttribute( tagArray, "spacey6" )) );

        add_child ( parent, id );
        traverseNode ( tagArray, id );
    }

    DOMElements tagRects = XercesHelper::getChildElementsByTagName ( pnode, "rect" );
    for ( DOMElements::iterator pp=tagRects.begin(); pp!=tagRects.end(); ++pp ) {
        DOMElement* tagRect  = static_cast<DOMElement*>(*pp);
        int id = rectangle_create ();
        //Rectanglef* rect = new Rectanglef();
        //_temp.push_back ( rect );

        // setting up layer node's properties
        float w = 1.f, h = 1.f;
        if ( XercesHelper::hasAttribute ( tagRect, "width" ) ) 
            w = atof((char*)XercesHelper::getAttribute( tagRect, "width" ));
        if ( XercesHelper::hasAttribute ( tagRect, "height" ) ) 
            h = atof((char*)XercesHelper::getAttribute( tagRect, "height" ));
        rectangle_size ( id, w, h );

        add_child ( parent, id );
        traverseNode ( tagRect, id );
    }
}

inline void LoadMesh::getShapeGenParas (int index, int& s1, int& s2, int& s3, int& s4, int& s5, int& s6, int level0Cnt, int level1Cnt, int level2Cnt, int level3Cnt, int level4Cnt, int level5Cnt )
{
    // init
    s1 = s2 = s3 = s4 = s5 = 0;

    if ( 0 == level1Cnt ) {
        //s1 = index;
        return;
    }
    else
        s1 = index - index / level1Cnt;

    if ( 0 == level2Cnt ) {
        //s2 = index / level1Cnt;
        return;
    }
    else
        s2 = index / level1Cnt - index / level2Cnt;

    if ( 0 == level3Cnt ) {
        //s3 = index / level2Cnt;
        return;
    }
    else
        s3 = index / level2Cnt - index / level3Cnt;

    if ( 0 == level4Cnt ) {
        //s4 = index / level3Cnt;
        return;
    }
    else
        s4 = index / level3Cnt - index / level4Cnt;

    if ( 0 == level5Cnt ) {
        //s5 = index / level4Cnt;
        return;
    }
    else
        s5 = index / level4Cnt - index / level5Cnt;

    s6 = index / level5Cnt;
}

#endif

