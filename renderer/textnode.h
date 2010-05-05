#ifndef _TEXTNODE_H_
#define _TEXTNODE_H_

#include "drawablenode.h"
#include <string>
#include <QFont>
#include <QFontMetricsF>

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
    TextNode () : _fontnode(0) {}
    TextNode ( const string& content ) : _content(content), _fontnode(0) {}
    TextNode ( const TextNode& rhs ) : DrawableNode ( rhs )
    {
	_content      = _content;
	_anchor       = _anchor;
	_alignFlag    = _alignFlag;
	_fontnode     = _fontnode;
	_anchorPoint  = _anchorPoint;
    }
    void text ( const string& content )
    {
        _content = content; 
        // update bbox
        if ( _fontnode )
        {
            QFont font ( _fontnode->family().c_str(), _fontnode->size(), QFont::Normal, _fontnode->italic() );
            QFontMetricsF m ( font );
            QSizeF sz = m.size ( Qt::TextWordWrap, content.c_str() );
            _bb.init ( vec3f(0, 0, 0) );
            _bb.expandby ( vec3f(sz.width(), sz.height(), 0) );
        }
    }
    const string& text () { return _content; }

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

    // set align
    void setAlignFlag ( short alignFlag ) { _alignFlag = alignFlag; }
    short alignFlag () { return _alignFlag; }

    // bounding box display control
    //void showBoundingBox ( bool isShow );
    FontNode* fontnode() { return _fontnode; }
    void fontnode( FontNode* p ) { _fontnode = p; }

    void anchorPoint ( float x, float y, float z ) { _anchorPoint.xyz(x,y,z); }
    const vec3f& anchorPoint () { return _anchorPoint; }
    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~TextNode () {}
private:
    string _content;
    short _anchor;
    short _alignFlag;
    FontNode* _fontnode;
    vec3f _anchorPoint;
};

//typedef NodeMgr<TextNode>        TextNodeMgr;
#endif
