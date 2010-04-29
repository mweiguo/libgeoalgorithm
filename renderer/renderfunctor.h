#ifndef _QTRENDER_FUNCTOR_H_
#define _QTRENDER_FUNCTOR_H_

#include <QPainter>
#include "rectitem.h"
#include "fontnode.h"
#include "textnode.h"
#include "mat4.h"

struct RenderOption
{
    BBox bb;
    QPainter* painter;
    //mat4f* mvmatrix;
    // matrix = viewpmapping * model-view
    mat4f matrix;
    RenderOption() : painter(0) {}
};

class QtRenderFunctor : public NodeVisitor
{
public:
    QtRenderFunctor ( RenderOption* opt ) : _opt(opt) {}
    virtual void apply ( Rectanglef& rect );
    virtual void apply ( TextNode& text );
    //virtual void apply ( FontNode& font );
private:
    RenderOption* _opt;
};

inline void QtRenderFunctor::apply ( Rectanglef& rect )
{
    vec2f lb = (_opt->matrix * vec4f(rect.lb())).xy();
    vec2f rt = (_opt->matrix * vec4f(rect.rt())).xy();

    _opt->painter->drawRect ( lb.x(), lb.y(), rt.x()-lb.x(), rt.y()-lb.y() );

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
    FontNode* fontnode = text.fontnode();
    QPen pen ( fontnode->color().c_str() );
    QFont font ( fontnode->family().c_str(), fontnode->size(), QFont::Normal, fontnode->italic() );
    const QFont oldfont = _opt->painter->font();
    const QPen oldpen = _opt->painter->pen();

    _opt->painter->setFont ( font );
    _opt->painter->setPen(pen);

    ////////////////////////////////
    // calculate bounding rect /////
    ////////////////////////////////
    //QFontMetrics m( _opt->painter->font() );
    //// get lines in string
    //int lines  = count (text.text().begin(), text.text().end(), '\n') + 1;
    //// get height of all text
    //int height = lines * m.lineSpacing ();
    //// get longest width of each line text
    //int width=0;
    //if ( 1 == lines )
    //    width = m.boundingRect ( text.text().c_str() ).width();
    //else {
    //    string::const_iterator pp, end=text.text().end(), lastpp=text.text().begin();
    //    for ( pp=text.text().begin(); pp != end; ++pp ) {
    //        if ( *pp == '\n' )
    //        {
    //            string tmp ( lastpp, pp );
    //            QRect b = m.boundingRect ( tmp.c_str() );
    //            if ( width < b.width() )
    //                width = b.width();
    //            lastpp = pp;
    //        }
    //    }
    //    if ( pp == end ) {
    //        string tmp ( lastpp, end );
    //        QRect b = m.boundingRect ( tmp.c_str() );
    //        if ( width < b.width() )
    //            width = b.width();
    //    }
    //}

    //// now get the bounding box
    //QRectF b ( 0, 0, width, height );
    QFontMetricsF m( _opt->painter->font() );
    QSizeF sz = m.size ( Qt::TextWordWrap, text.text().c_str() );
    QRectF b ( text.anchorPoint().x(), text.anchorPoint().y(), sz.width(), sz.height () );
    ////////////////////////////////
    // end calculate bounding rect /////
    ////////////////////////////////

    if ( text.isAnchorHCenter () )
        b.translate ( -b.width()/2, 0 );
    else if ( text.isAnchorRight () )
        b.translate ( -b.width(), 0 );

    if ( text.isAnchorVCenter () )
        b.translate ( 0, b.height() / 2 );
    else if ( text.isAnchorTop () )
        b.translate ( 0, b.height() );

    _opt->painter->drawText ( b, text.alignFlag() | Qt::TextWordWrap | Qt::TextDontClip, text.text().c_str() );

    // if ( _showBoundingBox )
    // 	painter->drawRect ( b );

    for ( SGNode::iterator pp=text.begin(); pp!=text.end(); ++pp )
        (*pp)->accept ( *this );

    _opt->painter->setPen ( oldpen );
    _opt->painter->setFont ( oldfont );
}

#endif
