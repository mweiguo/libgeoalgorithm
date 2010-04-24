#include "agl_rectitem.h"
#include "layernode.h"

template<class OptiPolicy>
LoadMesh<OptiPolicy>::LoadMesh ( const char* fileName, SGNode* node, const OptiPolicy& opt ) : _opt(opt)
{
  int clo = clock();
  XercesParser parser;
  XERCES_CPP_NAMESPACE::DOMDocument* doc = parser.parseFile ( fileName, false);
  if(doc == NULL)	
    throw logic_error("Fail to load Shape Template");

  DOMElement* root = doc->getDocumentElement();
  if (root == NULL) 
    throw logic_error("invalid Shape Template file:");
  char* tagName = (char*)XercesHelper::getTagName (root);

  _root = new SGNode();
  traverseNode ( root, _root );
  LOG_INFO ( "loading file TAKE %d clock, %f (ms)",clock() - clo, (1000.0*(clock() - clo))/CLOCKS_PER_SEC );

  _opt.optimize ();
  //BuildKdTree buildkdtree ( *kdtree, _root.bbox() );
}

template<class OptiPolicy>
void LoadMesh<OptiPolicy>::traverseNode ( XERCES_CPP_NAMESPACE::DOMElement* pnode, SGNode* data )
{
  //static int rectCount = 0;
  if ( NULL == data )
    return;

  vector<XERCES_CPP_NAMESPACE::DOMElement*> tagLayers = XercesHelper::getChildElementsByTagName ( pnode, "layer" );
  for (int i = 0; i<tagLayers.size(); ++i)
    {
      DOMElement* tagLayer  = static_cast<DOMElement*>(tagLayers[i]);
      LayerNode* layer = new LayerNode();
      // setting up layer node's properties
      string tmp = (char*)XercesHelper::getAttribute ( tagLayer, "isVisible" );
      if ( tmp == "1" ) layer->setVisible ( true );
      else if ( tmp == "0" ) layer->setVisible ( false );
      tmp = (char*)XercesHelper::getAttribute ( tagLayer, "lodvalue" );
      layer->setLevel ( atoi(tmp.c_str()), atoi(tmp.c_str())+100 );

      data->addChild ( layer );
      traverseNode ( tagLayer, layer );
    }

  vector<XERCES_CPP_NAMESPACE::DOMElement*> tagRectSets = XercesHelper::getChildElementsByTagName ( pnode, "rects" );
  for ( int i=0; i<tagRectSets.size(); ++i )
    {
      DOMElement* tagRectSet = static_cast<DOMElement*>( tagRectSets[i] );

      int rowCnt    = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "cnty" ) );
      int columnCnt = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "cntx" ) );
      float orgx    = atof( (char*)XercesHelper::getAttribute ( tagRectSet, "orgx" ) );
      float orgy    = atof( (char*)XercesHelper::getAttribute ( tagRectSet, "orgy" ) );
      int levelHCnt[6], levelVCnt[6];
      levelHCnt[0]  = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "level0hcnt" ) );
      levelHCnt[1]  = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "level1hcnt" ) );
      levelHCnt[2]  = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "level2hcnt" ) );
      levelHCnt[3]  = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "level3hcnt" ) );
      levelHCnt[4]  = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "level4hcnt" ) );
      levelHCnt[5]  = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "level5hcnt" ) );
      levelVCnt[0]  = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "level0vcnt" ) );
      levelVCnt[1]  = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "level1vcnt" ) );
      levelVCnt[2]  = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "level2vcnt" ) );
      levelVCnt[3]  = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "level3vcnt" ) );
      levelVCnt[4]  = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "level4vcnt" ) );
      levelVCnt[5]  = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "level5vcnt" ) );
      float spacex[6], spacey[6];
      spacex[0]     = atof( (char*)XercesHelper::getAttribute ( tagRectSet, "spacex1" ) );
      spacex[1]     = atof( (char*)XercesHelper::getAttribute ( tagRectSet, "spacex2" ) );
      spacex[2]     = atof( (char*)XercesHelper::getAttribute ( tagRectSet, "spacex3" ) );
      spacex[3]     = atof( (char*)XercesHelper::getAttribute ( tagRectSet, "spacex4" ) );
      spacex[4]     = atof( (char*)XercesHelper::getAttribute ( tagRectSet, "spacex5" ) );
      spacex[5]     = atof( (char*)XercesHelper::getAttribute ( tagRectSet, "spacex6" ) );
      spacey[0]     = atof( (char*)XercesHelper::getAttribute ( tagRectSet, "spacey1" ) );
      spacey[1]     = atof( (char*)XercesHelper::getAttribute ( tagRectSet, "spacey2" ) );
      spacey[2]     = atof( (char*)XercesHelper::getAttribute ( tagRectSet, "spacey3" ) );
      spacey[3]     = atof( (char*)XercesHelper::getAttribute ( tagRectSet, "spacey4" ) );
      spacey[4]     = atof( (char*)XercesHelper::getAttribute ( tagRectSet, "spacey5" ) );
      spacey[5]     = atof( (char*)XercesHelper::getAttribute ( tagRectSet, "spacey6" ) );
      int width     = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "width" ) );
      int height    = atoi( (char*)XercesHelper::getAttribute ( tagRectSet, "height" ) );

      float x, y;
      int s1, s2, s3, s4, s5, s6;
      for ( int j=0; j<rowCnt; j++ )
	{
	  getShapeGenParas ( j, s1, s2, s3, s4, s5, s6, levelVCnt[0], levelVCnt[1], levelVCnt[2], levelVCnt[3], levelVCnt[4], levelVCnt[5] );
	  y = orgy + (j+1)*height + s1*spacey[0] + s2*spacey[1] + s3*spacey[2] + s4*spacey[3] + s5*spacey[4] + s6*spacey[5];
	  for ( int k=0; k<columnCnt; k++ )
	    {
	      getShapeGenParas ( k, s1, s2, s3, s4, s5, s6, levelHCnt[0], levelHCnt[1], levelHCnt[2], levelHCnt[3], levelHCnt[4], levelHCnt[5] );
	      x = orgx + (k+1)*height + s1*spacex[0] + s2*spacex[1] + s3*spacex[2] + s4*spacex[3] + s5*spacex[4] + s6*spacex[5];
	      ARectItem* rect = new ARectItem();
	      rect->setRect ( x, y, width, height );
	      data->addChild ( rect );

	      //_kdtree.addPrimitive ( rect );
	      _opt.addOptimizeNode ( rect );
	      //rectCount++;

	    }
	}

      //traverseNode ( tagRectSet, rects );
    }
}

template<class OptiPolicy>
void LoadMesh<OptiPolicy>::getShapeGenParas (int index, int& s1, int& s2, int& s3, int& s4, int& s5, int& s6, int level0Cnt, int level1Cnt, int level2Cnt, int level3Cnt, int level4Cnt, int level5Cnt )
{
  // init
  s1 = s2 = s3 = s4 = s5 = 0;

  if ( 0 == level1Cnt )
    {
      //s1 = index;
      return;
    }
  else
    s1 = index - index / level1Cnt;

  if ( 0 == level2Cnt )
    {
      //s2 = index / level1Cnt;
      return;
    }
  else
    s2 = index / level1Cnt - index / level2Cnt;

  if ( 0 == level3Cnt )
    {
      //s3 = index / level2Cnt;
      return;
    }
  else
    s3 = index / level2Cnt - index / level3Cnt;

  if ( 0 == level4Cnt )
    {
      //s4 = index / level3Cnt;
      return;
    }
  else
    s4 = index / level3Cnt - index / level4Cnt;

  if ( 0 == level5Cnt )
    {
      //s5 = index / level4Cnt;
      return;
    }
  else
    s5 = index / level4Cnt - index / level5Cnt;

  s6 = index / level5Cnt;
}

KdTreeOptimization::KdTreeOptimization ( KdTree<DrawableNode*>& kdtree ) : _kdtree(kdtree) 
{
}

void KdTreeOptimization::addOptimizeNode ( DrawableNode* node ) 
{ 
  _kdtree.addPrimitive ( node ); 
  _bb.unionbox ( node->getBBox() );
}

void KdTreeOptimization::optimize () 
{ 
  BuildKdTree<DrawableNode*> buildkdtree ( _kdtree, _bb ); 
}


void NoOptimize::addOptimizeNode ( DrawableNode* node )
{
}

void NoOptimize::optimize ()
{
}
