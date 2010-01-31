struct XY
{
   float x, y;
};

struct XYZ
{
   float x, y, z;
};

struct TriNodes
{
   int pnt1, pnt2, pnt3;
};

struct NeighTris
{
   int tri1, int tri2, int tri3;
};

struct Point2D
{
  XY coords;
  
  iterator getTriBegin();
  iterator getTriEnd();
};

struct Point3D
{
   XYZ coords;
};

struct Triangle
{
  TriNodes nodes;
  NeighTris tris;
};

vector<Point2D> PointTable;
vector<Triangle> TriangleTable;


template <class InputIterator, class OutputIteratorn >
void getNeighTris ( InputIterator begin, InputIterator end, OutputIterator out )
{
  while ( begin != end )
    *out++ = *begin++;
}

template <class OutputIteratorn >
void getNeighTris ( OutputIteratorn out );
