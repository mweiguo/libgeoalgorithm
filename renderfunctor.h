#ifndef _QTRENDER_FUNCTOR_H_
#define _QTRENDER_FUNCTOR_H_

#include <QPainter>
#include "rectitem.h"
#include "mat4.h"

struct RenderOption
{
	BBox bb;
	QPainter* painter;
	//mat4f* mvmatrix;
	// matrix = viewpmapping * model-view
	mat4f matrix;
};

class QtRenderFunctor : public NodeVisitor
{
public:
    QtRenderFunctor ( RenderOption* opt ) : _opt(opt) {}
    virtual void apply ( Rectanglef& rect );
private:
    RenderOption* _opt;
};

inline void QtRenderFunctor::apply ( Rectanglef& rect )
{
	vec2f lb = (_opt->matrix * vec4f(rect.lb())).xy();
	vec2f rt = (_opt->matrix * vec4f(rect.rt())).xy();

    _opt->painter->drawRect ( lb.x(), lb.y(), rt.x()-lb.x(), rt.y()-lb.y() );
    //_opt->painter->drawRect ( rect.x(), rect.y(), rect.w(), rect.h() );
}

#endif
