#ifndef _RENDERLIST_H_
#define _RENDERLIST_H_

#include <quickvector.h>

class DrawableNode;
typedef quickvector<DrawableNode*> RenderList;
typedef map<string, RenderList*> RenderListMgr;

#endif
