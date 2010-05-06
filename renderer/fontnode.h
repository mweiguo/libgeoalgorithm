#ifndef _FONTNODE_H_
#define _FONTNODE_H_

#include "sgnode.h"

#include <string>
using namespace std;

class FontNode : public SGNode
{
public:
    FontNode ( const string& family="Courier New", int pointSize=12, bool isItalic=false ) : 
      _family(family), _pointSize(pointSize), _isItalic(isItalic)
      {
      }
      FontNode ( const FontNode& rhs ) : SGNode(rhs)
      {
          _family     = rhs._family;
          _pointSize  = rhs._pointSize;
          _isItalic   = rhs._isItalic;
          _color      = rhs._color;
      }
      // set font interface
      void setFont ( const string& family="Courier New", int pointSize=12, bool isItalic=false );
      void family ( const string& f ) { _family = f; }
      const string& family () { return _family; }
      void size ( float psize ) { _pointSize = psize; }
      float size () { return _pointSize; }
      void italic ( bool isItalic ) { _isItalic = isItalic; }
      bool italic () { return _isItalic; }
      // set color
      void color ( const string& color );
      const string& color () { return _color; }
private:
    string _family;
    float _pointSize;
    bool _isItalic;
    string _color;
};

//typedef NodeMgr<FontNode>        FontNodeMgr;

#endif
