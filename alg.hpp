#pragma once
#include <vector>
#include <list>

/*
 * @brief:  generate delaunay triangle net
 * @para:   begin, end are iterator in [begin, end) form
 * @return: InputIterator will be pushed into out parameter, in1a, int2a, in3a, in1b, int2b, int3b ...
 */
template < class InputIterator, class OutputIterator >
void build_delaunay ( InputIterator begin, InputIterator end, OutputIterator out );

template < class InputIterator, class OutputIterator >
void build_convexhull ( InputIterator begin, InputIterator end, OutputIterator out );

template < class InputIterator, class OutputIterator >
void merge_convexhull ( InputIterator begin, const T& pnt, OutputIterator out );

template< class InputIterator, class T, class OutputIterator >
void get_visiblepoints ( InputIterator begin, InputIterator end, const T& pnt, OutputIterator result );

/*
 * @brief:  sort
 * @para:   begin, end are iterator in [begin, end) form
 * @return: InputIterator will be pushed into out parameter, InputIterator1, InputIterator1, ...
 */
template < class InputIterator, class InputIterator2, class Compare, class OutputIterator >
void sortbydist ( InputIterator1 begin, InputIterator1 end, InputIterator2 dest, OutputIterator out, Compare comp );


#define DIST_EXTEND	0.01
// intersection flag
#define CONSTRAINT_NONE 0
#define CONSTRAINT_LINE 1
#define CONSTRAINT_AREA 2
#define CONSTRAINT_ALL  3
// collinear result
#define COLLINEAR_NONE      0
#define COLLINEAR_LEFT      1
#define COLLINEAR_RIGHT     2
#define COLLINEAR_MIDDLE    3
#define COLLINEAR_LEFTEND   4
#define COLLINEAR_RIGHTEND  5

// typedef unsigned __int32 uint32;
// typedef unsigned __int64 uint64;
typedef unsigned int uint32;
typedef unsigned long long uint64;

/*
 * @brief:  calculate circle using 3 point
 * @para:   x[1-3], y[1-3] are in parameter
 *          x and y are circle's center
 * @return: retrieve radius
 */
double circle3pnt( double x1, double y1, double x2, double y2, double x3, double y3, double& x, double& y );
double circle3pnt4dv( double *coord1, double *coord2, double* coord3, double* coord );
/*
 * @brief:  calculate the area of triangle which three point constructed(2d)
 * @return: retrieve area
 */
double area2d ( double coord1[], double coord2[], double coord3[] );
/*
 * @brief:  calculate the area of triangle which three point constructed(3d)
 * @return: retrieve area
 */
double area3d (  double coord1[], double coord2[], double coord3[] );

/*
 * @brief:  retrieve (x,y) is in (x1,y1), (x2,y2) 's left
 * @return: if in left, return true, otherwise return false
 */
bool in_leftside( double x, double y, double x1, double y1, double x2, double y2 );
bool in_leftside( double* , double*, double* );


/*
 * @brief:  calculate intersection point between two edges [ (x1,y1)-(x2,y2), 
 *          (x3,y3)-(x4,y4) ]
 * @return: (x,y) is that point, return value will show follow
 *          EARGU_INVALID
 *          RELATION_OVERLAP
 *          RELATION_NONE
 *          RELATION_INTERSECTION
 */
int intersection_ltol2d ( double x1, double y1, double x2, double y2, 
			  double x3, double y3, double x4, double y4,
			  double &x, double &y );

/*
 * @brief:  calculate corner angle between (x1,y1)-(x2,y2) and (x2,y2)-(x3,y3)
 * @return: return value is in [0,2PI)
 */
double corner_angle ( double* c1, double* c, double* c2 );

/*
 * @brief:  calculate corner angle between (x1,y1,z1)-(x2,y2,z2) and (x2,y2,z2)-(x3,y3,z3)
 * @return: return value : cosa
 */
double corner_angle3d ( double* c1, double* c, double* c2 );
/*
 * @brief:  return two edge has same direction ( angle < 90 )
 */
bool same_direction ( double x1, double y1, double x2, double y2, 
		      double xx1, double yy1, double xx2, double yy2 );

// graph object's topology
const int RELATION_OVERLAP      = 1000;
const int RELATION_NONE         = 1001;
const int RELATION_OUTSIDE      = 1002;
const int RELATION_INSIDE       = 1003;
const int RELATION_ADJACENCY    = 1004;
const int RELATION_PARTOVERLAP  = 1005;
const int RELATION_INTERSECTION = 1006;
const int RELATION_INCLUDE      = 1007;
const int RELATION_PARALLEL     = 1008;
const int RELATION_EXTENDLINE   = 1009;
const int RELATION_NEGTIVE_SIDE = 1010;
const int RELATION_POSITIVE_SIDE= 1011;
const int RELATION_INTERPOINT   = 1012;


//////////////////////////////////////////////////////////////// matrix operation begin   
double determinant ( double m[], int num );
double daishu ( int RowNum, int ColNum, double* m, int num );
void bansui ( double m[], double m1[], int num );
void matrix_numul ( double val, double m[], int num );
void matrix_mul ( double lm[], int lrow, int lcol, double rm[], int rrow, int rcol, double* m );
void reverse_matrix ( double m[], double m1[], int num );
void matrix_transpose ( double m[], int num );
void point3d_transform ( double* coord, double* m, double* out );
void point3d_transform ( double x, double y, double z, double* m, double& ox, double& oy, double& oz);
void get_matrixs ( double coord1[], double coord2[], double coord3[],
		   double offset[], double rotz[],
		   double roty[], double rotx[], 
		   double ext1[], double ext2[] );
void get_matrix( double coord1[], double coord2[], double coord3[], double matrix[] );
//////////////////////////////////////////////////////////////// matrix operation end

//iLink* min_path ( std::vector<iEdge*>& edges );
//bool TransformPlane ( std::list<iEdge*>& plines );
bool HitTestDist2D (double x1, double y1, double x2, double y2, double x, double y);
bool greater ( double, double  );
bool equal ( double, double );
void gravity_coord ( double u, double v, double w, double* coord1, double* coord2, double* coord3, double* coord);
void gravity_coord ( double* coord1, double* coord2, double* coord3, double* coord, double& u, double& v, double& w );
short IJK_555 ( int i, int j, int k );
void IJK_555 ( short val, int& i, int& j, int& k );


int intersection_l2tri ( double* coordsLine, double* coordsTri, double* coordsOut );
int intersection_l2a ( double* coordsLine, double* coordsRect, double* coordsOut, int flag=CONSTRAINT_ALL );
int intersection_tri2apara ( double* coordsTri, double* A, double* B, double* C, double* coordsOut, unsigned char& interFlag );
int intersection_l2l ( double* coordLine1, double* coordLine2, double* coordsOut );
int intersection_l2apara ( double* coordsLine, double* A, double* B, double* C, double* coordsOut );
double distance2d ( double x1, double y1, double x2, double y2 );
double distance3d ( double x1, double y1, double z1, double x2, double y2, double z2 );
double distance2dv ( double* coords1, double *coords2 );
double distance3dv ( double* c1, double *c2 );
void plane_genpara ( double* coord1, double* coord2, double* coord3, double& A, double& B, double& C, double& D );
double direction_angle4dv ( double* c1, double* c0, double* c2, float* unitNormal );
void unit_normal ( double* c1, double* c0, double* c2, float* unitNormal );
int collinear ( double* c1, double* c2, double* c3 );
double mincos_intri ( double* c1, double* c2, double* c3 );
bool clockwise ( double*, double*, double* );

void trim_end ( char* pDest );
int get_sub ( const char *pSrc, char* pDest, char delimiter );
void cross_product (double*, double*, double*, float* );
void cross_product ( double* a, double* b, double* n );
void normalize(double, double, double, float* );
void normalize(double*, double* );
void generate_tricoords ( double* planePara, double* coord );
void get_planetricoords ( double* planePara, double* c1, double* c2, double* c3, double* out );
void get_genpara ( double* A, double* B, double* C, double* planePara );
