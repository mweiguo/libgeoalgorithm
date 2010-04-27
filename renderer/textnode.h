#ifndef _TEXTNODE_H_
#define _TEXTNODE_H_

#include "drawablenode.h"
#include <string>
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
    TextNode ();
    TextNode ( const string& content );

    void content ( const string& content );
    const string& content () { return _content; }

    // anchor interface
    // anchor have 9 options
    //  .     .     .
    //  .     .     .
    //  .     .     .
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

    virtual void accept ( NodeVisitor& pvisitor ) const { pvisitor.apply ( *this ); }
    virtual void accept ( NodeVisitor& pvisitor ) { pvisitor.apply ( *this ); }
    virtual ~TextNode () {}
private:
    string _content;
    short _anchor;
    short _alignFlag;
};

#endif
