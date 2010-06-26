
#include "drawablenode.h"
#include "colortable.h"
#include "parentfinder.h"
#include "layernode.h"

DrawableNode::DrawableNode()
{
    _bRender = true;
}

DrawableNode::DrawableNode ( const DrawableNode& rhs ) : SGNode(rhs), _bRender(rhs._bRender)
{
}

//void DrawableNode::setColor ( unsigned int color )
//{
//    _color = ColorTable::getInst().addColor ( color );
//}
//
//unsigned int DrawableNode::getColor ()
//{
//    unsigned int color;
//    if ( getLayerColor ( color ) )
//        return color;
//    return ColorTable::getInst().getColor ( _color );
//}
//
//bool DrawableNode::getLayerColor ( unsigned int& color )
//{
//    //if ( ColorTable::getInst().isByGroup (_color) )
//    //{
//    //    ParentFinder<LayerNode> find;
//    //    LayerNode* player = find ( this );
//    //    if ( player )
//    //        return player->getColor();
//    //}
//    return false;
//}

