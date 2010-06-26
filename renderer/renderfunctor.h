#ifndef _QTRENDER_FUNCTOR_H_
#define _QTRENDER_FUNCTOR_H_

#include <QPainter>

#include "rectitem.h"
#include "fontnode.h"
#include "textnode.h"
#include "mat4.h"
#include "vec2.h"
#include "vec4.h"
#include "linenode.h"

struct RenderOption
{
    BBox bb;
    QPainter* painter;
    //mat4f* mvmatrix;
    // matrix = viewpmapping * model-view
    mat4f matrix;
    float scale;
    RenderOption() : painter(0) {}
};

class QtRenderFunctor : public NodeVisitor
{
public:
    QtRenderFunctor ( RenderOption* opt ) : _opt(opt) {}
    virtual void apply ( RectangleNodef& rect );
    virtual void apply ( TextNode& text );
    virtual void apply ( LineNodef& /*node*/ );
    //virtual void apply ( FontNode& font );
private:
    RenderOption* _opt;
};

inline void QtRenderFunctor::apply ( RectangleNodef& rect )
{
    //vec2f lb = (_opt->matrix * vec4f(rect.lb())).xy();
    //vec2f rt = (_opt->matrix * vec4f(rect.rt())).xy();
    vec2f lb = vec2f(rect.lb());
    vec2f rt = vec2f(rect.rt());
    GColor color = rect.getBorderColor();  
    QPen pen ( QColor(color.r(),color.g(),color.b(),color.a()) );

    color = rect.getFillColor();  
    QBrush brush ( QColor(color.r(),color.g(),color.b(),color.a()) );

    QPen oldpen = _opt->painter->pen();
    QBrush oldbrush = _opt->painter->brush();

    _opt->painter->setPen ( pen );
    _opt->painter->setBrush ( brush );

    _opt->painter->drawRect ( lb.x(), lb.y(), rt.x()-lb.x(), rt.y()-lb.y() );
    //_opt->painter->fillRect ( lb.x(), lb.y(), rt.x()-lb.x(), rt.y()-lb.y(), QColor (color>>24, (color&0x00FF0000)>>16, (color&0x0000FF00)>>8, color&0x000000FF) );

    _opt->painter->setPen ( oldpen );
    _opt->painter->setBrush ( oldbrush );

    for ( SGNode::iterator pp=rect.begin(); pp!=rect.end(); ++pp )
        (*pp)->accept ( *this );
}

//inline void QtRenderFunctor::apply ( FontNode& node )
//{
//    QPen pen ( node.color().c_str() );
//    QFont font ( node.family().c_str(), node.size(), QFont::Normal, node.italic() );
//    const QFont oldfont = _opt->painter->font();
//    const QPen oldpen = _opt->painter->pen();
//
//    _opt->painter->setFont ( font );
//    _opt->painter->setPen(pen);
//
//    for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
//        (*pp)->accept ( *this );
//
//    _opt->painter->setPen ( oldpen );
//    _opt->painter->setFont ( oldfont );
//}

inline void QtRenderFunctor::apply ( TextNode& text )
{
    QMatrix m;
    m.reset();
    m.scale ( 1, -1 );
    QMatrix oldm = _opt->painter->matrix();
    QMatrix newm = m * oldm;
    _opt->painter->setWorldMatrix ( newm );

    FontNode* fontnode = text.fontnode();
    //QPen pen ( fontnode->color().c_str() );
    QFont font ( fontnode->family().c_str(), fontnode->size(), QFont::Normal, fontnode->italic() );
    const QFont oldfont = _opt->painter->font();
    const QPen oldpen = _opt->painter->pen();
    _opt->painter->setFont ( font );
    //_opt->painter->setPen(pen);

    BBox b = text.getBBox ();
    //vec2f lb = (_opt->matrix * vec4f(b.min())).xy();
    //vec2f rt = (_opt->matrix * vec4f(b.max())).xy();
    //vec2f lb = vec2f(b.min());
    //vec2f rt = vec2f(b.max());
    
    QRectF rc( b.min().x(), -b.min().y(), b.dimension().w(), b.dimension().h() );
    //QRectF rc( lb.x(), lb.y(), 200, 100 );
    _opt->painter->drawRect ( rc.toRect() );
    _opt->painter->drawText ( rc, Qt::TextWordWrap | Qt::TextDontClip | Qt::AlignCenter, text.text().c_str() );
//    _opt->painter->drawText ( QPointF(lb.x(), lb.y()), text.text().c_str() );
    _opt->painter->setWorldMatrix ( oldm );

    for ( SGNode::iterator pp=text.begin(); pp!=text.end(); ++pp )
        (*pp)->accept ( *this );

    //_opt->painter->setPen ( oldpen );
    //_opt->painter->setFont ( oldfont );

    /* FontNode* fontnode = text.fontnode(); */
    /* QPen pen ( fontnode->color().c_str() ); */
    /* QFont font ( fontnode->family().c_str(), fontnode->size(), QFont::Normal, fontnode->italic() ); */
    /* const QFont oldfont = _opt->painter->font(); */
    /* const QPen oldpen = _opt->painter->pen(); */

    /* _opt->painter->setFont ( font ); */
    /* _opt->painter->setPen(pen); */

    /* //// now get the bounding box */
    /* //QRectF b ( 0, 0, width, height ); */
    /* QFontMetricsF m( _opt->painter->font() ); */
    /* QSizeF sz = m.size ( Qt::TextWordWrap, text.text().c_str() ); */
    /* QRectF b ( text.anchorPoint().x(), text.anchorPoint().y(), sz.width(), sz.height () ); */
    /* //////////////////////////////// */
    /* // end calculate bounding rect ///// */
    /* //////////////////////////////// */

    /* if ( text.isAnchorHCenter () ) */
    /*     b.translate ( -b.width()/2, 0 ); */
    /* else if ( text.isAnchorRight () ) */
    /*     b.translate ( -b.width(), 0 ); */

    /* if ( text.isAnchorVCenter () ) */
    /*     b.translate ( 0, b.height() / 2 ); */
    /* else if ( text.isAnchorTop () ) */
    /*     b.translate ( 0, b.height() ); */

    /* _opt->painter->drawText ( b, text.alignFlag() | Qt::TextWordWrap | Qt::TextDontClip, text.text().c_str() ); */

    /* // if ( _showBoundingBox ) */
    /* // 	painter->drawRect ( b ); */

    /* for ( SGNode::iterator pp=text.begin(); pp!=text.end(); ++pp ) */
    /*     (*pp)->accept ( *this ); */

    /* _opt->painter->setPen ( oldpen ); */
    /* _opt->painter->setFont ( oldfont ); */
}

inline void QtRenderFunctor::apply ( LineNodef& line )
{
    vec2f p1 = (_opt->matrix * vec4f(line.point1())).xy();
    vec2f p2 = (_opt->matrix * vec4f(line.point2())).xy();
    GColor color = line.getLineColor();
    
    //int r = color>>24;
    //int g = (color&0x00FF0000)>>16;
    //int b = (color&0x0000FF00)>>8;
    //int a = color&0x000000FF;
    const QPen& oldpen = _opt->painter->pen();
    _opt->painter->setPen ( QPen(QColor (color.r(),color.g(),color.b(),color.a())));
    _opt->painter->drawLine ( p1.x(), p1.y(), p2.x(), p2.y() );
    _opt->painter->setPen ( oldpen );

    for ( SGNode::iterator pp=line.begin(); pp!=line.end(); ++pp )
        (*pp)->accept ( *this );
}

#endif
