#ifndef _LOADNODE_H_
#define _LOADNODE_H_

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
class LoadNode
{
public:
    LoadNode ( const char* fileName/*, SGNode* node , const OptiPolicy& opt  */);
    MeshNode* root () { return _root; }
private:
    void traverseNode ( XERCES_CPP_NAMESPACE::DOMElement* pnode, SGNode* data );
    void getShapeGenParas (int index, int& s1, int& s2, int& s3, int& s4, int& s5, int& s6, int level0Cnt, int level1Cnt, int level2Cnt, int level3Cnt, int level4Cnt, int level5Cnt );
private:
    MeshNode* _root;
};


inline LoadNode::LoadNode ( const char* fileName/*, SGNode* node , const OptiPolicy& opt */ )// : _opt(opt)
{
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
    _root = new MeshNode ();
    traverseNode ( root, _root );
    qDebug ( "traverseNode TAKE %d clock, %f (s)", clock() - clo,  (1.0*(clock() - clo))/CLOCKS_PER_SEC );
}

inline void LoadNode::traverseNode ( XERCES_CPP_NAMESPACE::DOMElement* pnode, SGNode* parent )
{
    typedef vector<XERCES_CPP_NAMESPACE::DOMElement*> DOMElements;
    
    DOMElements tagLayers = XercesHelper::getChildElementsByTagName ( pnode, "layer" );
    for ( DOMElements::iterator pp=tagLayers.begin(); pp!=tagLayers.end(); ++pp ) {
        DOMElement* tagLayer  = static_cast<DOMElement*>(*pp);
        LayerNode* layer = new LayerNode();

        if ( XercesHelper::hasAttribute ( tagLayer, "isVisible" ) ) {
            string tmp = (char*)XercesHelper::getAttribute ( tagLayer, "isVisible" );
            if ( tmp == "1" ) layer->setVisible ( true );
            else if ( tmp == "0" ) layer->setVisible ( false );
        }
        if ( XercesHelper::hasAttribute ( tagLayer, "name" ) )
            layer->name ( (char*)XercesHelper::getAttribute ( tagLayer, "name" ) );
 
        parent->addChild ( layer );
        traverseNode ( tagLayer, layer );
    }

    DOMElements tagPickables = XercesHelper::getChildElementsByTagName ( pnode, "pickablegroup" );
    for ( DOMElements::iterator pp=tagPickables.begin(); pp!=tagPickables.end(); ++pp ) {
        DOMElement* tagPickable  = static_cast<DOMElement*>(*pp);
        PickableGroup* pick = new PickableGroup();

        if ( XercesHelper::hasAttribute ( tagPickable, "name" ) )
            pick->name ( (char*)XercesHelper::getAttribute ( tagPickable, "name" ) );

        parent->addChild ( pick );
        traverseNode ( tagPickable, pick );
    }

    DOMElements tagLods = XercesHelper::getChildElementsByTagName ( pnode, "lod" );
    for ( DOMElements::iterator pp=tagLods.begin(); pp!=tagLods.end(); ++pp ) {
        DOMElement* tagLod  = static_cast<DOMElement*>(*pp);
        LODNode* lod = new LODNode();

        // setting up layer node's properties
        if ( XercesHelper::hasAttribute ( tagLod, "range" ) )
            lod->setdelimiters ( (char*)XercesHelper::getAttribute ( tagLod, "range" ) );

        parent->addChild ( lod );
        traverseNode ( tagLod, lod );
    }

    DOMElements tagKdTrees = XercesHelper::getChildElementsByTagName ( pnode, "kdtree" );
    for ( DOMElements::iterator pp=tagKdTrees.begin(); pp!=tagKdTrees.end(); ++pp ) {
        DOMElement* tagKdTree  = static_cast<DOMElement*>(*pp);
        KdTreeNode* kdtreenode = new KdTreeNode();
        parent->addChild ( kdtreenode );
        traverseNode ( tagKdTree, kdtreenode );
    }

    DOMElements tagTransforms = XercesHelper::getChildElementsByTagName ( pnode, "transform" );
    for ( DOMElements::iterator pp=tagTransforms.begin(); pp!=tagTransforms.end(); ++pp ) {
        DOMElement* tagTransform  = static_cast<DOMElement*>(*pp);
        TransformNode* trans = new TransformNode();

        // setting up layer node's properties
        if ( XercesHelper::hasAttribute ( tagTransform, "translate" ) )
            trans->setTranslate ( (char*)XercesHelper::getAttribute ( tagTransform, "translate" ) );

        if ( XercesHelper::hasAttribute ( tagTransform, "scale" ) )
            trans->setScale ( (char*)XercesHelper::getAttribute ( tagTransform, "scale" ) );

        parent->addChild ( trans );
        traverseNode ( tagTransform, trans );
    }

    DOMElements tagArrays = XercesHelper::getChildElementsByTagName ( pnode, "array" );
    for ( DOMElements::iterator pp=tagArrays.begin(); pp!=tagArrays.end(); ++pp ) {
        DOMElement* tagArray = static_cast<DOMElement*>( *pp );
        ArrayNode* arraynode = new ArrayNode();

        if ( XercesHelper::hasAttribute ( tagArray, "cnty" ) ) arraynode->setRowCnt ( atoi((char*)XercesHelper::getAttribute( tagArray, "cnty" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "cntx" ) ) arraynode->setColumnCnt ( atoi((char*)XercesHelper::getAttribute( tagArray, "cntx" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level0hcnt" ) ) arraynode->setHLevels ( 0, atoi((char*)XercesHelper::getAttribute( tagArray, "level0hcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level1hcnt" ) ) arraynode->setHLevels ( 1, atoi((char*)XercesHelper::getAttribute( tagArray, "level1hcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level2hcnt" ) ) arraynode->setHLevels ( 2, atoi((char*)XercesHelper::getAttribute( tagArray, "level2hcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level3hcnt" ) ) arraynode->setHLevels ( 3, atoi((char*)XercesHelper::getAttribute( tagArray, "level3hcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level4hcnt" ) ) arraynode->setHLevels ( 4, atoi((char*)XercesHelper::getAttribute( tagArray, "level4hcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level5hcnt" ) ) arraynode->setHLevels ( 5, atoi((char*)XercesHelper::getAttribute( tagArray, "level5hcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level0vcnt" ) ) arraynode->setVLevels ( 0, atoi((char*)XercesHelper::getAttribute( tagArray, "level0vcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level1vcnt" ) ) arraynode->setVLevels ( 1, atoi((char*)XercesHelper::getAttribute( tagArray, "level1vcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level2vcnt" ) ) arraynode->setVLevels ( 2, atoi((char*)XercesHelper::getAttribute( tagArray, "level2vcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level3vcnt" ) ) arraynode->setVLevels ( 3, atoi((char*)XercesHelper::getAttribute( tagArray, "level3vcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level4vcnt" ) ) arraynode->setVLevels ( 4, atoi((char*)XercesHelper::getAttribute( tagArray, "level4vcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "level5vcnt" ) ) arraynode->setVLevels ( 5, atoi((char*)XercesHelper::getAttribute( tagArray, "level5vcnt" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacex1" ) ) arraynode->setMarginX ( 0, atof((char*)XercesHelper::getAttribute( tagArray, "spacex1" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacex2" ) ) arraynode->setMarginX ( 1, atof((char*)XercesHelper::getAttribute( tagArray, "spacex2" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacex3" ) ) arraynode->setMarginX ( 2, atof((char*)XercesHelper::getAttribute( tagArray, "spacex3" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacex4" ) ) arraynode->setMarginX ( 3, atof((char*)XercesHelper::getAttribute( tagArray, "spacex4" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacex5" ) ) arraynode->setMarginX ( 4, atof((char*)XercesHelper::getAttribute( tagArray, "spacex5" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacex6" ) ) arraynode->setMarginX ( 5, atof((char*)XercesHelper::getAttribute( tagArray, "spacex6" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacey1" ) ) arraynode->setMarginY ( 0, atof((char*)XercesHelper::getAttribute( tagArray, "spacey1" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacey2" ) ) arraynode->setMarginY ( 1, atof((char*)XercesHelper::getAttribute( tagArray, "spacey2" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacey3" ) ) arraynode->setMarginY ( 2, atof((char*)XercesHelper::getAttribute( tagArray, "spacey3" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacey4" ) ) arraynode->setMarginY ( 3, atof((char*)XercesHelper::getAttribute( tagArray, "spacey4" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacey5" ) ) arraynode->setMarginY ( 4, atof((char*)XercesHelper::getAttribute( tagArray, "spacey5" )) );
        if ( XercesHelper::hasAttribute ( tagArray, "spacey6" ) ) arraynode->setMarginY ( 5, atof((char*)XercesHelper::getAttribute( tagArray, "spacey6" )) );

        parent->addChild ( arraynode );
        traverseNode ( tagArray, arraynode );
    }

    DOMElements tagRects = XercesHelper::getChildElementsByTagName ( pnode, "rect" );
    for ( DOMElements::iterator pp=tagRects.begin(); pp!=tagRects.end(); ++pp ) {
        DOMElement* tagRect  = static_cast<DOMElement*>(*pp);
        Rectanglef* rect = new Rectanglef();
        //Rectanglef* rect = new Rectanglef();
        //_temp.push_back ( rect );

        // setting up layer node's properties
        float w = 1.f, h = 1.f;
        if ( XercesHelper::hasAttribute ( tagRect, "width" ) ) 
            w = atof((char*)XercesHelper::getAttribute( tagRect, "width" ));
        if ( XercesHelper::hasAttribute ( tagRect, "height" ) ) 
            h = atof((char*)XercesHelper::getAttribute( tagRect, "height" ));
        rect->size ( w, h );

        parent->addChild ( rect );
        traverseNode ( tagRect, rect );
    }
}

inline void LoadNode::getShapeGenParas (int index, int& s1, int& s2, int& s3, int& s4, int& s5, int& s6, int level0Cnt, int level1Cnt, int level2Cnt, int level3Cnt, int level4Cnt, int level5Cnt )
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

