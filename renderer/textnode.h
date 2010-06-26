#ifndef _TEXTNODE_H_
#define _TEXTNODE_H_

#include "drawablenode.h"
#include "fontnode.h"
#include <string>
#include <fontmetric.h>
#include <vec4.h>
#include "fbcolor.h"
#include "parentfinder.h"

using namespace std;

class TextNode : public DrawableNode
{
public:
    enum AnchorFlag
    {
        AnchorLEFT    = 1,
        AnchorTOP     = 2,
        AnchorRIGHT   = 4,
        AnchorBOTTOM  = 8,
        AnchorHCENTER  = 16,
        AnchorVCENTER  = 32,
        AnchorCENTER  = AnchorHCENTER | AnchorVCENTER
    };
    enum AlignFlag
    {
        AlignLeft     = 0x1, 
        AlignRight    = 0x2,
        AlignHCenter  = 0x4,
        AlignJustify  = 0x8,
        AlignTop      = 0x20,
        AlignBottom   = 0x40,
        AlignVCenter  = 0x80,
        AlignCenter   = AlignHCenter | AlignVCenter
    };
    TextNode () { _fontnode = &FontNode::defaultNode(); }
    TextNode ( const string& content ) : _text(content) { _fontnode = &FontNode::defaultNode(); }
    TextNode ( const TextNode& rhs ) : DrawableNode ( rhs )
    {
        _text         = rhs._text;
        _anchor       = rhs._anchor;
        _alignFlag    = rhs._alignFlag;
        _fontnode     = rhs._fontnode;
    }

    virtual void updateBBox( const mat4f& mat=mat4f() )
    {
        if ( NULL == _fontnode )
            return;

        _bb.init ( vec3f(0.f, 0.f, 0.f) );
        _bb.expandby ( _dimension );

        if ( isAnchorHCenter () )
            _bb.translate ( vec3f(-_dimension.x()/2.f, 0.f, 0.f ) );
        else if ( isAnchorRight () )
            _bb.translate ( vec3f(-_dimension.x(), 0.f, 0.f) );

        if ( isAnchorVCenter () )
            _bb.translate ( vec3f(0, _dimension.y()/2.f, 0.f) );
        else if ( isAnchorTop () )
            _bb.translate ( vec3f(0, _dimension.y(), 0.f) );

        vec4f min = mat * vec4f ( _bb.min() );
        vec4f max = mat * vec4f ( _bb.max() );

        _bb.setminmax ( min.xyz(), max.xyz() );

        for ( iterator pp=begin(); pp!=end(); ++pp )
        {
            (*pp)->updateBBox();
            _bb = _bb.unionbox ( (*pp)->getBBox() );
        }
    }

    void text ( const string& content )
    {
        _text = content; 
        _dimension = FontMetric::getInst().getBBox ( *_fontnode, _text ).dimension();
    }
    const string& text () { return _text; }

    // anchor interface
    // anchor have 9 options
    //  1     2     3
    //  4     5     6
    //  7     8     9
    void setAnchor ( int anchorFlag ) { _anchor = anchorFlag; }
    bool isAnchorLeft () { return ( (AnchorLEFT & _anchor) != 0 ); }
    bool isAnchorHCenter () { return ( (AnchorHCENTER & _anchor) != 0 ); }
    bool isAnchorRight () { return ( (AnchorRIGHT & _anchor) != 0 ); }
    bool isAnchorTop () { return ( (AnchorTOP & _anchor) != 0 ); }
    bool isAnchorVCenter () { return ( (AnchorVCENTER & _anchor) != 0 ); }
    bool isAnchorBottom () { return ( (AnchorBOTTOM & _anchor) != 0 ); }
    short anchorValue ()
    {
        int value = 0;
        if ( isAnchorTop() )
        {
            if ( isAnchorLeft() )
                value = 1;
            else if ( isAnchorHCenter() )
                value = 2;
            else if ( isAnchorRight() )
                value = 3;
        }
        else if ( isAnchorVCenter() )
        {
            if ( isAnchorLeft() )
                value = 4;
            else if ( isAnchorHCenter() )
                value = 5;
            else if ( isAnchorRight() )
                value = 6;
        }
        else if ( isAnchorBottom() )
        {
            if ( isAnchorLeft() )
                value = 7;
            else if ( isAnchorHCenter() )
                value = 8;
            else if ( isAnchorRight() )
                value = 9;
        }
        return value;
    }
    void anchorValue ( short v )
    {
        switch ( v)
        {
        case 1:
            setAnchor ( AnchorLEFT | AnchorTOP );
            break;
        case 2:
            setAnchor ( AnchorHCENTER | AnchorTOP );
            break;
        case 3:
            setAnchor ( AnchorRIGHT | AnchorTOP );
            break;
        case 4:
            setAnchor ( AnchorLEFT | AnchorVCENTER );
            break;
        case 5:
            setAnchor ( AnchorHCENTER | AnchorVCENTER );
            break;
        case 6:
            setAnchor ( AnchorRIGHT | AnchorVCENTER );
            break;
        case 7:
            setAnchor ( AnchorLEFT | AnchorBOTTOM );
            break;
        case 8:
            setAnchor ( AnchorHCENTER | AnchorBOTTOM );
            break;
        case 9:
            setAnchor ( AnchorRIGHT | AnchorBOTTOM );
            break;

        }
    }



    // set align
    void setAlignFlag ( short alignFlag ) { _alignFlag = alignFlag; }
    short alignFlag () { return _alignFlag; }

    // bounding box display control
    //void showBoundingBox ( bool isShow );
    FontNode* fontnode() { return _fontnode; }
    void fontnode( FontNode* p ) { _fontnode = p; }

    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~TextNode () {}
    void useLayerColor ()
    {
        ParentFinder<LayerNode> finder ( this );
        if ( finder.target() )
            _color.useLayerFgColor(finder.target()); 
    }
    void setTextColor ( GColor color )
    {
        _color.setFgColor(color);
    }
    GColor getTextColor () { return _color.getFgColor(); }

private:
    string _text;
    short _anchor;
    short _alignFlag;
    FontNode* _fontnode;

    vec3f _dimension;
private:
    FgBgColorComponent _color;
};

//typedef NodeMgr<TextNode>        TextNodeMgr;
#endif
