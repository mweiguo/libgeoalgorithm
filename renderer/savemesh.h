#ifndef _SAVEMESH_H_
#define _SAVEMESH_H_

#include <sstream>
#include <fstream>
using namespace std;

class SaveMesh : public NodeVisitor
{
public:
	SaveMesh( const string& filename, SGNode* node );
	virtual void apply ( SGNode& node );
	virtual void apply ( LayerNode& node );
	virtual void apply ( Rectanglef& node );
	virtual void apply ( TransformNode& node );
	virtual void apply ( ArrayNode& node );
	virtual void apply ( LODNode& node );
    virtual void apply ( PickableGroup& node );
    virtual void apply ( KdTreeNode& node );
    virtual void apply ( MeshNode& node );
private:
	stringstream _xmlContent;
};

inline SaveMesh::SaveMesh( const string& filename, SGNode* node )
{
	_xmlContent.str("");
	_xmlContent << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
	node->accept ( *this );
	ofstream out;
	out.open ( filename.c_str() );
	out << _xmlContent.str();
	out.close();
}

inline void SaveMesh::apply ( SGNode& node )
{
	_xmlContent << "<chiptemplate>";
	for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
		(*pp)->accept ( *this );
	_xmlContent << "</chiptemplate>";
}

inline void SaveMesh::apply ( LayerNode& node )
{
	_xmlContent << "<layer name='" << node.name() << "' isVisible='" << (node.isVisible() ? 1 : 0) << "'>";
	for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
		(*pp)->accept ( *this );
	_xmlContent << "</layer>";
}

inline void SaveMesh::apply ( Rectanglef& node )
{
	_xmlContent << "<rect width='" << node.w() << "' height='" << node.h() << "'>";
	for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
		(*pp)->accept ( *this );
	_xmlContent << "</rect>";
}

inline void SaveMesh::apply ( TransformNode& node )
{
	stringstream ts, ss;
	mat4f& tm = node.getMatrix();
	ts << tm.dx() << ' ' << tm.dy() << ' ' << tm.dz();
	mat4f& sm = node.getMatrix();
	ss << sm.sx() << ' ' << sm.sy() << ' ' << sm.sz();

	_xmlContent << "<transform translate='" << ts.str() << "' scale='" << ss.str() << "'>";
	for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
		(*pp)->accept ( *this );
	_xmlContent << "</transform>";
}

inline void SaveMesh::apply ( ArrayNode& node )
{
	stringstream ss;
	for ( int i=0; i<6; i++ )
	{
		int levelcnt = node.getHLevels (i);
		if ( levelcnt != 0 )
			ss << "level" << i << "hcnt='" << levelcnt << "' ";
		levelcnt = node.getVLevels (i);
		if ( levelcnt != 0 )
			ss << "level" << i << "vcnt='" << levelcnt << "' ";
		float space = node.getMarginX (i);
		if ( space != 0 )
			ss << "spacex" << i+1 << "='" << space << "' ";
		space = node.getMarginY (i);
		if ( space != 0 )
			ss << "spacey" << i+1 << "='" << space << "' ";
	}
	ss << "cntx='" << node.getColumnCnt() << "' cnty='" << node.getRowCnt() << "'";

	_xmlContent << "<array " << ss.str() << ">";
	for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
		(*pp)->accept ( *this );
	_xmlContent << "</array>";
}

inline void SaveMesh::apply ( LODNode& node )
{
	stringstream ss;
	for ( LODNode::diterator pp=node.dbegin(); pp!=node.dend(); ++pp )
		ss << (*pp) << " ";
	if ( ss.str() == "" )
		_xmlContent << "<lod>";
	else
		_xmlContent << "<lod range='" << ss.str() << "'>";

	for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
		(*pp)->accept ( *this );
	_xmlContent << "</lod>";
}

inline void SaveMesh::apply ( PickableGroup& node )
{
	_xmlContent << "<pickablegroup name='" << node.name() << "'>";
	for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
		(*pp)->accept ( *this );
	_xmlContent << "</pickablegroup>";
}

inline void SaveMesh::apply ( KdTreeNode& node )
{
	_xmlContent << "<kdtree>" ;
	for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
		(*pp)->accept ( *this );
	_xmlContent << "</kdtree>";
}

inline void SaveMesh::apply ( MeshNode& node )
{
	_xmlContent << "<mesh>";
	for ( SGNode::iterator pp=node.begin(); pp!=node.end(); ++pp )
		(*pp)->accept ( *this );
	_xmlContent << "</mesh>";
}

#endif

