#include "drawablenode.h"
#include "transformnode.h"
// #include <QPainter>
void DrawableNode::reCalcMatrix()
{
  SGNode *node = this;
  while ( (node = node->getParentNode ()) != NULL ) {
    TransformNode* p = dynamic_cast<TransformNode*>(node);
    if ( NULL == p )
      continue;
    _matrix = p->getMatrix() * _matrix;
  }
}

void DrawableNode::beginRender (QPainter& painter)
{
  // mat3<float> m = getMatrix();
  // _oldMatrix = painter.matrix();
  // painter.setMatrix (QMatrix(m.m00(),m.m01(),m.m10(),m.m11(),m.dx(),m.dy()));
}

void DrawableNode::endRender (QPainter& painter)
{
  // painter.setMatrix (_oldMatrix);
}

bool DrawableNode::acceptTraversal ( NodeVisitor* pNodeVisitor )
{
	// culling
	return true; 
}

void DrawableNode::updateRenderList ( RenderItemContainer& output )
{
  reCalcMatrix();
  output.push_back ( this );
}

void DrawableNode::draw (QPainter& painter)
{
	beginRender ( painter );
	render ( painter );
	endRender ( painter );
}
