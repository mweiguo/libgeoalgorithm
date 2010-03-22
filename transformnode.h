#ifndef _TRANSFORM_NODE_H_
#define _TRANSFORM_NODE_H_

#include "switchnode.h"
#include "mat3.h"

class TransformNode : public virtual SwitchNode
{
public:
  TransformNode () { _mat.normal(); }
  void setTranslate ( float dx, float dy, float dz ) { _mat.dx ( dx ); _mat.dy(dy); }
  void setScale ( float sx, float sy, float sz ) { _mat.sx(sx); _mat.sy(sy); }
  mat3<float> getMatrix () { return _mat; }
private:
  mat3<float> _mat;
};

#endif
