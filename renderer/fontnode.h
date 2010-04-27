#ifndef _FONTNODE_H_
#define _FONTNODE_H_

#include "sgnode.h"

#include <string>
using namespace std;

class FontNode : public SGNode
{
public:
    // set font interface
    void setFont ( const string& _family="Courier New", int pointSize=12, bool isItalic=false );
    void family ( const string& _family );
    const string& family () { return _family; }
    void size ( int psize ) { _pointSize = psize; }
    int size () { return _pointSize; }
    void italic ( bool isItalic ) { _isItalic = isItalic; }
    bool italic () { return _isItalic; }
    // set color
    void color ( const string& color );
    const string& color () { return _color; }
private:
    string _family;
    int _pointSize;
    bool _isItalic;
    string _color;
};

#endif
