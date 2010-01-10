#include "alg.hpp"
#include <math.h>
#include <stdexcept>
//#include <ActiveDomain.h>
#include <vector>
//#include <ErrorTable.hpp>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>


const int ESUCCESS             = 0;
const int ENOMEMORY            = 1;
const int EARGU_INVALID        = 2;
const int EPLACEHOLDER         = 3;
const int EINTEGRITY           = 4;
const int ENOELEMENT           = 5;
const int EUNKNOWN             = 6;
const int EINCOMPLETE_TRIANGLE = 7;
const int E_ERROR              = 8;
const int E_NOTDEVIDE          = 9;

#ifndef M_PI
#define M_PI 3.1415926
#endif

bool HitTestDist2D (double x1, double y1, double x2, double y2, double x, double y)
{
    double a = sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
    double b = sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
    double c = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    a = a+b-c;
    return (fabs(a) < DIST_EXTEND);
}


double circle3pnt( double x1, double y1, double z1,
                   double x2, double y2, double z2,
                   double x3, double y3, double z3,
                   double& x, double& y, double& z )
{
    double a1 = x2-x1;  double b1 = y2-y1;  double c1 = z2-z1;
    double a2 = x3-x1;  double b2 = y3-y1;  double c2 = z3-z1;

    // normal vector, a*x + b*y + c*z = d(the normal formula)
    double a = b1*c2-b2*c1;
    double b = a2*c1-a1*c2;
    double c = a1*b2-a2*b1;
    double mo = sqrt ( a*a + b*b + c*c );
    a = a/mo;  b = b/mo;  c = c/mo;
    double d = -1*(a*x1 + b*y1 + c*z1);

    // middle parameter
    a1 *= 2;  b1 *= 2;  c1 *= 2;
    a2 *= 2;  b2 *= 2;  c2 *= 2;
    double d1 = x2*x2 + y2*y2 + z2*z2 - x1*x1 - y1*y1 - z1*z1;
    double d2 = x3*x3 + y3*y3 + z3*z3 - x1*x1 - y1*y1 - z1*z1;

    //  double D = a1*b2*c + a2*b*c1 + a*b1*c2 - a*b2*c1 - a2*b1*c - a1*b*c2;
    double D = a1*(b2*c-b*c2) + a2*(b*c1-b1*c) + a*(b1*c2-b2*c1);
    // x, y, z
    x = (d1*(b2*c-b*c2) + d2*(b*c1-b1*c) + d*(b1*c2-b2*c1))/D;
    y = (d*(a2*c1-a1*c2) + d1*(a*c2-a2*c) + d2*(a1*c-a*c1))/D;
    z = (d*(a1*b2-a2*b1) + d1*(a2*b-a*b2) + d2*(a*b1-a1*b))/D;

    // radius
    return sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y)+(z1-z)*(z1-z));
}

double circle3pnt( double x1, double y1, double x2, double y2, double x3, double y3, double& x, double& y )
{
  double a1 = 2*(x2-x1), b1=2*(y2-y1), c1=x2*x2+y2*y2-x1*x1-y1*y1;
  double a2 = 2*(x3-x2), b2=2*(y3-y2), c2=x3*x3+y3*y3-x2*x2-y2*y2;
  x = (b2*c1-b1*c2)/(a1*b2-a2*b1);
  y = (a2*c1-a1*c2)/(a2*b1-a1*b2);

  return sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y) );
}

double circle3pnt4dv( double *c1, double *c2, double* c3, double* c )
{
	return circle3pnt ( c1[0], c1[1], c2[0], c2[1], c3[0], c3[1], c[0], c[1] );
}

bool greater ( double f1, double f2 )
{
    if ( (f1-f2) > DIST_EXTEND )
        return true;
    return false;
}

bool equal ( double f1, double f2)
{
    if ( fabs(f1-f2) < DIST_EXTEND )
        return true;
    return false;
}


double area2d ( double c1[], double c2[], double c3[] )
{
  return fabs ((c1[1]+c2[1])*(c2[0]-c1[0])/2 + (c2[1]+c3[1])*(c3[0]-c2[0])/2 + (c1[1]+c3[1])*(c1[0]-c3[0])/2);
}


double area3d (  double coord1[], double coord2[], double coord3[] )
{
  if ( equal(coord1[0],coord2[0]) && equal(coord1[1],coord2[1]) && equal(coord1[2],coord2[2]) )
  	return 0;
  if ( equal(coord3[0],coord2[0]) && equal(coord3[1],coord2[1]) && equal(coord3[2],coord2[2]) )
  	return 0;
  if ( equal(coord1[0],coord3[0]) && equal(coord1[1],coord3[1]) && equal(coord1[2],coord3[2]) )
  	return 0;

  if ( collinear ( coord1, coord2, coord3 ) )
		return 0;
		
  double m[16]={0}, coord[9]={0};
  get_matrix ( coord1, coord2, coord3, m );

  point3d_transform ( coord1, m, coord );
  point3d_transform ( coord2, m, coord+3 );
  point3d_transform ( coord3, m, coord+6 );

  return fabs(coord[3]*coord[7])/2;
}

/*
 * @brief: code the parameter to a short number
 * @para:  i, j, k(the extent is between 0 and 32)
 * @return:if parameter exceed the extent, return -1
 *         if operation succeeded, return the coded number
 */
short IJK_555 ( int i, int j, int k )
{
    short rtn = 0;
    rtn = i;
    rtn <<= 5;
    rtn |= j;
    rtn <<= 5;
    rtn |= k;
    return rtn;
}

/*
 * @brief:  decode the parameter to three identifiers
 * @para:   i, j, k(the extent is between 0 and 32)
 * @para:   val(this short number will be decoded)
 * @return: if operation succeeded, return the decoded numbers
 *          every identifier place 5 bits, then this operation extract every identifier
 *          from the corresponding bits
 */
void IJK_555 ( short val, int& i, int& j, int& k )
{
    i = val & 0x7C00;
    i >>= 10;
    j = val & 0x03E0;
    j >>= 5;
    k = val & 0x001F;
}

uint64 IJ_3232 ( uint32 a, uint32 b )
{
  uint64 rtn=0;
  rtn |= a;
  rtn <<= 32;
  rtn |= b;
  return rtn;
}

void IJ_3232( uint64 val, uint32& a, uint32& b)
{
	a = (uint32)(val>>32);
	b = (uint32)val;
}



void gravity_coord ( double u, double v, double w, double* coord1, double* coord2, double* coord3, double* coord)
{
    double x = u*coord1[0] + v*coord2[0] + w*coord3[0];
    double y = u*coord1[1] + v*coord2[1] + w*coord3[1];
    double z = u*coord1[2] + v*coord2[2] + w*coord3[2];
    *coord++ = x;
    *coord++ = y;
    *coord = z;
}

void gravity_coord ( double* coord1, double* coord2, double* coord3, double* coord, double& u, double& v, double& w )
{
	double d = area3d ( coord1, coord2, coord3 );
	u = area3d ( coord, coord2, coord3 );
	v = area3d ( coord, coord1, coord2 );
	w = area3d ( coord, coord1, coord3 );
	u = u/d;
	v = v/d;
	w = w/d;
}

//////////////////////////////////////////////////////////////////////////
bool in_leftside( double x, double y, double x1, double y1, double x2, double y2 )
{
//   double sum = (y2+y1)*(x2-x1)/2;
//   sum += (y+y2)*(x-x2)/2;
//   sum += (y1+y)*(x1-x)/2;
  double sum = (y2+y1)*(x2-x1);
  sum += (y+y2)*(x-x2);
  sum += (y1+y)*(x1-x);
  if ( sum < 0 )
    return true;
  else
    return false;
}
bool in_leftside( double* coord, double *coord1, double* coord2 )
{
	return in_leftside( coord[0], coord[1], coord1[0], coord1[1], coord2[0], coord2[1] );
}

///////////////////////////////////////////////////////////////////////////
//inline 
//double determinant33 ( double m[] )
//{
//  return determinant33 ( m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8] );
//}
//
//inline
//double determinant33 ( double a1, double b1, double c1,
//		       double a2, double b2, double c2,
//		       double a3, double b3, double c3)
//{
//  return a1*b2*c3 + a2*b3*c1 + a3*b1*c2 - a3*b2*c1 - a2*b1*c3 - a1*b3*c2;
//}
//
//inline 
//double determinant44 ( double m[] )
//{
//  return determinant44 ( m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], 
//			 m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15] );
//}
//
//inline 
//double determinant44 ( double a1, double b1, double c1, double d1,
//		       double a2, double b2, double c2, double d2,
//		       double a3, double b3, double c3, double d3,
//		       double a4, double b4, double c4, double d4)
//{
//  return a1*b2*c3*d4 + a2*b3*c4*d1 + a3*b4*c1*d2 + a4*b1*c2*d3 - a4*b3*c2*d1 - a3*b2*c1*d4 - a2*b1*c4*d3 - a1*b4*c3*d2;
//}
//
//inline
//double daishu44 ( int RowNum, int ColNum, double** m )
//{
//  double mm[9]={0};
//  int idx = 0;
//  for ( int i=0; i<4; i++ ){
//    if ( i==RowNum )
//      continue;
//    for ( int j=0; j<4; j++ ){
//      if ( j==ColNum )
//	continue;
//      mm[idx++] = m[i][j];
//    }
//  }
//
//  return determinant33 ( mm );
//}
//
//inline
//void bansui44 ( double m[], double m1[] )
//{
//  double tm[16];
//  memcpy ( tm, m, sizeof(tm) );
//  int idx = 0;
//  for ( int i=0; i<4; i++ ){
//    for ( int j=0; j<4; j++ ){
//      m1[idx++] = daishu44 ( i, j, (double**)tm );
//    }
//  }
//}
//
//inline
//void matrix44_numul ( double val, double m[] )
//{
//  for ( int i=0; i<16; i++ )
//    m[i] *= val;
//}

//void reverse_matrix ( double m[], double m1[] )
//{
//  double val = determinant44 ( m );
//  val = 1/val;
//  bansui44 ( m, m );
//  matrix44_numul ( val, m );
//  memcpy ( m1, m, sizeof(m) );
//}

// inline
// void chuixin( double x1, double y1, double z1,
// 	      double x2, double y2, double z2,
// 	      double x3, double y3, double z3,
// 	      double &x, double &y, double &z ){
//   double A1, B1, C1, D1, A2, B2, C2, D2, A3, B3, C3, D3;
//   A1 = 2*(x2-x1);
//   B1 = 2*(y2-y1);
//   C1 = 2*(z2-z1);
//   D1 = x2*x2 + y2*y2 + z2*z2 - x1*x1 - y1*y1 - z1*z1 + d4 - d5;

//   double s = d4*d4 / d5*d5;
//   A2 = 2*((s+1)*x3-x1-x2*s);
//   B2 = 2*((s+1)*y3-y1-y2*s);
//   B2 = 2*((s+1)*z3-z1-y2*s);
//   D2 = (1+s)*(x3*x3+y3*y3+z3*z3-x1*x1-y1*y1-z1*z1 );

//   A3 = b1*c2-b2*c1;
//   B3 = a2*c1-a1*c2;
//   C3 = a1*b2-a2*b1;
//   s = sqrt ( a*a + b*b + c*c );
//   A3 = A3/s;  B3 = B3/s;  C3 = C3/s;
//   D3 = -1*(A3*x1 + B3*y1 + C3*z1);

//   s = determinant33 ( A1, B1, C1, A2, B2, C2, A3, B3, C3 );
//   x = determinant33 ( D1, B1, C1, D2, B2, C2, D3, B3, C3 );
//   y = determinant33 ( A1, D1, C1, A2, D2, C2, A3, D3, C3 );
//   y = determinant33 ( A1, B1, D1, A2, B2, D2, A3, B3, D3 );
//   x = x/s;
//   y = y/s;
//   z = z/s;
// }

//////////////////////////////////////////////////////////////// matrix operation begin   
double determinant ( double m[], int num )
{
  // parameter check
  if ( num<=0 )
	  throw std::invalid_argument ("row num is not invalid" );
  else if ( num==1 )
	  return m[0];
  else if ( num==2 )
	  return m[0]*m[3]-m[1]*m[2];
  else if ( num==3 )
	  return m[0]*m[4]*m[8]+m[1]*m[5]*m[6]+m[2]*m[3]*m[7] - m[2]*m[4]*m[6]-m[1]*m[3]*m[8]-m[0]*m[5]*m[7];

  double sum=0;
  for ( int i=0; i<num; i++ )
	  sum+=m[i]*daishu ( 0, i, m, num );
  
  return sum;
}

double daishu ( int RowNum, int ColNum, double* m, int num )
{
  double mm[256]={0};
  int idx = 0;
  for ( int i=0; i<num; i++ ){
    if ( i==RowNum )
      continue;
    for ( int j=0; j<num; j++ ){
      if ( j==ColNum )
	continue;
      mm[idx++] = m[i*num+j];
    }
  }

  if ( (RowNum+ColNum)%2==0 )
	return determinant ( mm, num-1 );
  else
    return -determinant ( mm, num-1 );
}

void bansui ( double m[], double m1[], int num )
{
  double tm[256]={0};
  memcpy ( tm, m, sizeof(double)*num*num );
  int idx = 0;
  for ( int i=0; i<num; i++ ){
    for ( int j=0; j<num; j++ ){
      m1[idx++] = daishu ( i, j, tm, num );
    }
  }
  matrix_transpose ( m1, num );
}

void matrix_numul ( double val, double m[], int num )
{
  for ( int i=0; i<num*num; i++ )
    m[i] *= val;
}

void matrix_mul ( double lmatrix[], int lrow, int lcol, double rmatrix[], int rrow, int rcol, double* m )
{
  if ( lcol!=rrow )
    throw std::invalid_argument ( "matrixs are not suitable for mul" );
  double lm[256]={0}, rm[356]={0};
  memcpy ( lm, lmatrix, sizeof(double)*lrow*lcol );
  memcpy ( rm, rmatrix, sizeof(double)*rrow*rcol );
  int idx=0;
  for ( int i=0; i<lrow; i++ ){
    for ( int j=0; j<rcol; j++ ){
      double sum=0;
      for ( int k=0; k<lcol; k++ ){
	sum+=lm[i*lcol+k]*rm[k*rcol+j];
      }
      m[idx++] = sum;
    }
  }
}

void reverse_matrix ( double m[], double m1[], int num )
{
  memcpy ( m1, m, sizeof(double)*num*num);
  double val = determinant ( m1, num );
  val = 1/val;
  bansui ( m1, m1, num );
  matrix_numul ( val, m1, num );
}

void matrix_transpose ( double m[], int num )
{
  double tmp;
  for ( int i=0; i<num; i++ ){
	  for ( int j=i+1; j<num; j++ ){
	    tmp = m[i*num+j];
		m[i*num+j] = m[j*num+i];
		m[j*num+i] = tmp;
	  }
  }
}

void point3d_transform ( double* coord, double* matrix, double* out )
{
  double tx=coord[0], ty=coord[1], tz=coord[2];
  out[0] = tx*matrix[0] + ty*matrix[4] + tz*matrix[8] + matrix[12];
  out[1] = tx*matrix[1] + ty*matrix[5] + tz*matrix[9] + matrix[13];
  out[2] = tx*matrix[2] + ty*matrix[6] + tz*matrix[10] + matrix[14];
}

void point3d_transform ( double x, double y, double z, double* matrix, double& ox, double& oy, double& oz)
{
  double tx=x, ty=y, tz=z;
  ox = tx*matrix[0] + ty*matrix[4] + tz*matrix[8] + matrix[12];
  oy = tx*matrix[1] + ty*matrix[5] + tz*matrix[9] + matrix[13];
  oz = tx*matrix[2] + ty*matrix[6] + tz*matrix[10] + matrix[14];
}

void get_matrixs ( double coord1[], double coord2[], double coord3[],
		   double offset[], double rotz[],
		   double roty[], double rotx[], 
		   double ext1[], double ext2[] )
{
  double d,cosx,sinx,siny,cosy,sinz,cosz;
  double c1[3]={0}, c2[3]={0}, c3[3]={0};
  int tt = sizeof(double)*16;
  memset ( offset, 0, tt );
  memset ( rotx, 0, tt );
  memset ( roty, 0, tt );
  memset ( rotz, 0, tt );
  memcpy ( c1, coord1, sizeof(c1) );
  memcpy ( c2, coord2, sizeof(c2) );
  memcpy ( c3, coord3, sizeof(c3) );

  //1.move offset
  offset[0]=offset[5]=offset[10]=offset[15]=1;
  offset[12]=-c1[0];
  offset[13]=-c1[1];
  offset[14]=-c1[2];
  point3d_transform ( c1, offset, c1 );
  point3d_transform ( c2, offset, c2 );
  point3d_transform ( c3, offset, c3 );
  
  //2.rotate z
  d= sqrt( c2[0]*c2[0] + c2[1]*c2[1] );
  cosz = -c2[0]/d;
  sinz = c2[1]/d;
  rotz[0]=rotz[5]=cosz;
  rotz[1]=sinz;
  rotz[4]=-sinz;
  rotz[10]=rotz[15]=1;
  point3d_transform ( c1, rotz, c1 );
  point3d_transform ( c2, rotz, c2 );
  point3d_transform ( c3, rotz, c3 );
  
  //rotate y
  d= sqrt( c2[0]*c2[0] + c2[2]*c2[2] );
  if( fabs(c2[0])==d )
    cosy = 1;
  else
    cosy = c2[0] / d;
  siny = c2[2] / d;
  roty[0] = roty[10] = cosy;
  roty[2] = -siny;
  roty[8] = siny;
  roty[5] = roty[15] = 1;
  point3d_transform ( c1, roty, c1 );
  point3d_transform ( c2, roty, c2 );
  point3d_transform ( c3, roty, c3 );
  
  //rotate x
  d = sqrt ( c3[1]*c3[1] + c3[2]*c3[2] );
  cosx= -c3[1] / d;
  sinx = c3[2] / d;
  rotx[0] = rotx[15] = 1;
  rotx[5] = rotx[10] = cosx;
  rotx[6] = sinx;
  rotx[9] = -sinx;
  point3d_transform ( c1, rotx, c1 );
  point3d_transform ( c2, rotx, c2 );
  point3d_transform ( c3, rotx, c3 );

  // confirm the x2 > 0 && y3 > 0
  memset ( ext1, 0, tt );
  if ( c2[0] < 0 ){
    // rotate by y-axis cos(180)
    cosy = -1;
    siny = 0;
    ext1[0] = ext1[10] = cosy;
    ext1[2] = -siny;
    ext1[8] = siny;
    ext1[5] = ext1[15] = 1;
	point3d_transform ( c1, ext1, c1 );
	point3d_transform ( c2, ext1, c2 );
	point3d_transform ( c3, ext1, c3 );
  }else
    ext1[0] = ext1[5] = ext1[10] = ext1[15] = 1;

  memset ( ext2, 0, tt );
  if ( c3[1] < 0 ){
    // rotate by x-axis 
    cosx = -1;
    sinx = 0;
    ext2[0] = ext2[15] = 1;
    ext2[5] = ext2[10] = cosx;
    ext2[6] = sinx;
    ext2[9] = -sinx;
	point3d_transform ( c1, ext2, c1 );
	point3d_transform ( c2, ext2, c2 );
	point3d_transform ( c3, ext2, c3 );
 }else
    ext2[0] = ext2[5] = ext2[10] = ext2[15] = 1;
}

void get_matrix( double coord1[], double coord2[], double coord3[],	 double matrix[] )
{
  double offset[16] = {0};
  double rotz[16] = {0};
  double roty[16] = {0};
  double rotx[16] = {0};
  double ext1[16];
  double ext2[16];

  get_matrixs ( coord1, coord2, coord3,	offset, rotz, roty, rotx, ext1, ext2 );
  memcpy ( matrix, offset, sizeof(offset) );
  matrix_mul ( matrix, 4, 4, rotz, 4, 4, matrix );
  matrix_mul ( matrix, 4, 4, roty, 4, 4, matrix );
  matrix_mul ( matrix, 4, 4, rotx, 4, 4, matrix );
  matrix_mul ( matrix, 4, 4, ext1, 4, 4, matrix );
  matrix_mul ( matrix, 4, 4, ext2, 4, 4, matrix );
}    

//////////////////////////////////////////////////////////////// matrix operation end

// intersection
int intersection_ltol2d ( double x1, double y1, double x2, double y2, 
			  double x3, double y3, double x4, double y4,
			  double &x, double &y )
{
  double A1, B1, C1, A2, B2, C2, D;

  if ( x1==x2 && y1!=y2 ){
    A1 = 1;    B1 = 0;    C1 = x1;
  }else if ( y1==y2 && x1!=x2 ){
    A1 = 0;    B1 = 1;    C1 = y1;
  }else if( x1!=x2 && y1!=y2 ){
    A1 = y2-y1;    B1 = x1-x2;    C1 = x1*y2 - x2*y1;
  }else{
    return EARGU_INVALID;
  }

  if ( x3==x4 && y3!=y4 ){
    A2 = 1;    B2 = 0;    C2 = x3;
  }else if ( y3==y4 ){
    A2 = 0;    B2 = 1;    C2 = y3;
  }else if( x3!=x4 && y3!=y4 ){
    A2 = y4-y3;    B2 = x3-x4;    C2 = x3*y4 - x4*y3;
  }else{
    return EARGU_INVALID;
  }

  D = A1*B2 - A2*B1;
  if ( D!=0 ){
    x = C1*B2 - C2*B1;
    y = A1*C2 - A2*C1;
    x /= D;
    y /= D;
  }else{
    if ( C1==C2 )//overlap
      return RELATION_OVERLAP;
    else
      return RELATION_NONE;
  }

  // check extent
  double minx, maxx, miny, maxy;
  minx = x1<x2 ? (maxx=x2,x1) : (maxx=x1,x2);
  miny = y1<y2 ? (maxy=y2,y1) : (maxy=y1,y2);
  if ( x<minx || x>maxx || y<miny || y>maxy )
    return RELATION_NONE;

  return RELATION_INTERSECTION;
}

double corner_angle ( double *c1, double* c0, double* c2 )
{
  // vector
  double a1 = c1[0]-c0[0], b1 = c1[1]-c0[1];
  double a2 = c2[0]-c0[0], b2 = c2[1]-c0[1];

  // vector mul
  double C = a2*b1-a1*b2;

  double ang = atan2 ( C, a1*a2+b1*b2 );
  if ( ang < 0 )
    return 2*M_PI+ang;
  return ang;
}

double corner_angle3d ( double* c1, double* c, double* c2 )
{
  double xa = c1[0]-c[0], ya = c1[1]-c[1], za = c1[2]-c[2];
  double xb = c2[0]-c[0], yb = c2[1]-c[1], zb = c2[2]-c[2];
  return (xa*xb+ya*yb+za*zb)/(sqrt(xa*xa+ya*ya+za*za)*sqrt(xb*xb+yb*yb+zb*zb));
}


bool same_direction ( double x1, double y1, double x2, double y2, 
					  double xx1, double yy1, double xx2, double yy2 )
{
	bool pos1 = in_leftside( xx1, yy1, x1, y1, x2, y2 );
	bool pos2 = in_leftside( x1, y1, xx1, yy1, xx2, yy2 );

	return pos1 ^ pos2;

}
int intersection_l2tri ( double* coordsLine, double* coordsTri, double* coordsOut )
{
  struct tmp{
    static bool get_para ( double* pp1, double *pp2, double *pp3, double *pp4, double* pp5, double& out )
    {
      double x = pp1[1]*pp2[2] - pp1[2]*pp2[1], y = pp1[2]*pp2[0] - pp1[0]*pp2[2], z = pp1[0]*pp2[1] - pp1[1]*pp2[0];
      double tmp = x*pp5[0] + y*pp5[1] + z*pp5[2];
      if ( tmp==0 )
	return false;      
      out =  (x*(pp3[0]-pp4[0]) + y*(pp3[1]-pp4[1]) + z*(pp3[2]-pp4[2]))/tmp;
      return true;
    }
    static bool get_uw ( double a1, double b1, double c1, double a2, double b2, double c2, double& u, double &w )
    {
      double d = a1*b2-a2*b1;
      if ( d==0 )
	return false;
      u = (c1*b2-c2*b1)/d;
      w = (a1*c2-a2*c1)/d;
      return true;
    }
  };

  double a[3] = { coordsTri[0], coordsTri[1], coordsTri[2] };
  double b[3] = { coordsTri[3]-coordsTri[0], coordsTri[4]-coordsTri[1], coordsTri[5]-coordsTri[2] };
  double c[3] = { coordsTri[6]-coordsTri[0], coordsTri[7]-coordsTri[1], coordsTri[8]-coordsTri[2] };
  double d[3] = { coordsLine[0], coordsLine[1], coordsLine[2] };
  double e[3] = { coordsLine[3]-coordsLine[0], coordsLine[4]-coordsLine[1], coordsLine[5]-coordsLine[2]};

  double t, u, w, u1, w1;
  if ( tmp::get_uw ( b[0], c[0], coordsLine[0]-coordsTri[0], b[1], c[1], coordsLine[1]-coordsTri[1], u1, w1 ) ){
    if ( (fabs(a[2]+u1*b[2]+w1*c[2]-coordsLine[2])<DIST_EXTEND) )
      if ( tmp::get_uw ( b[0], c[0], coordsLine[3]-coordsTri[0], b[1], c[1], coordsLine[4]-coordsTri[1], u, w ) ){
	if ( (fabs(a[2]+u*b[2]+w*c[2]-coordsLine[5])<DIST_EXTEND) ){
	  if ( (u1>=0 && u1<=1 && w1>=0 && w1<=1 && (1-u1-w1)>=0 && (1-u1-w1)<=1 ) && (u>=0 && u<=1 && w>=0 && w<=1  && (1-u-w)>=0 && (1-u-w)<=1 ) )
	    return RELATION_OVERLAP;
	  else if ( (u1>=0 && u1<=1 && w1>=0 && w1<=1 && (1-u1-w1)>=0 && (1-u1-w1)<=1 ) || (u>=0 && u<=1 && w>=0 && w<=1  && (1-u-w)>=0 && (1-u-w)<=1 ) )
	    return RELATION_PARTOVERLAP;
	}
      }
  }

  if ( false==tmp::get_para ( b, c, a, d, e, t ) )
    return RELATION_PARALLEL;

  // check extent
  if ( t<=1 && t>=0 ){
    tmp::get_para ( c, e, d, a, b, u );
    if ( u<=1 && u>=0 ){
      tmp::get_para ( b, e, d, a, c, w );
      if ( w<=1 && w>=0 ){
	coordsOut[0] = d[0]+t*e[0];
	coordsOut[1] = d[1]+t*e[1];
	coordsOut[2] = d[2]+t*e[2];
	return RELATION_INTERSECTION;
      }
    }
  }
  return RELATION_NONE;
}

int intersection_l2a ( double* coordsLine, double* coordsTri, double* coordsOut, int flag )
{
  struct tmp{
    static bool get_para ( double* pp1, double *pp2, double *pp3, double *pp4, double* pp5, double& out )
    {
      double x = pp1[1]*pp2[2] - pp1[2]*pp2[1], y = pp1[2]*pp2[0] - pp1[0]*pp2[2], z = pp1[0]*pp2[1] - pp1[1]*pp2[0];
      double tmp = x*pp5[0] + y*pp5[1] + z*pp5[2];
      if ( tmp==0 )
	return false;      
      out =  (x*(pp3[0]-pp4[0]) + y*(pp3[1]-pp4[1]) + z*(pp3[2]-pp4[2]))/tmp;
      return true;
    }
    static bool get_uw ( double a1, double b1, double c1, double a2, double b2, double c2, double& u, double &w )
    {
      double d = a1*b2-a2*b1;
      if ( d==0 )
	return false;
      u = (c1*b2-c2*b1)/d;
      w = (a1*c2-a2*c1)/d;
      return true;
    }
  };

  double a[3] = { coordsTri[0], coordsTri[1], coordsTri[2] };
  double b[3] = { coordsTri[3]-coordsTri[0], coordsTri[4]-coordsTri[1], coordsTri[5]-coordsTri[2] };
  double c[3] = { coordsTri[6]-coordsTri[0], coordsTri[7]-coordsTri[1], coordsTri[8]-coordsTri[2] };
  double d[3] = { coordsLine[0], coordsLine[1], coordsLine[2] };
  double e[3] = { coordsLine[3]-coordsLine[0], coordsLine[4]-coordsLine[1], coordsLine[5]-coordsLine[2]};

  double t, u, w, u1, w1;
  if ( tmp::get_uw ( b[0], c[0], coordsLine[0]-coordsTri[0], b[1], c[1], coordsLine[1]-coordsTri[1], u1, w1 ) ){
    if ( (fabs(a[2]+u1*b[2]+w1*c[2]-coordsLine[2])<DIST_EXTEND) )
      if ( tmp::get_uw ( b[0], c[0], coordsLine[3]-coordsTri[0], b[1], c[1], coordsLine[4]-coordsTri[1], u, w ) ){
	if ( (fabs(a[2]+u*b[2]+w*c[2]-coordsLine[5])<DIST_EXTEND) ){
	  if ( (u1>=0 && u1<=1 && w1>=0 && w1<=1 ) && (u>=0 && u<=1 && w>=0 && w<=1 ) )
	    return RELATION_OVERLAP;
	       else if ( (u1>=0 && u1<=1 && w1>=0 && w1<=1  ) || (u>=0 && u<=1 && w>=0 && w<=1 ) )
	    return RELATION_PARTOVERLAP;
	}
      }
  }

  if ( false==tmp::get_para ( b, c, a, d, e, t ) )
    return RELATION_PARALLEL;

  // check extent
  if ( !(flag & CONSTRAINT_LINE) || (t<=1 && t>=0) ){
    tmp::get_para ( c, e, d, a, b, u );
    if ( !(flag & CONSTRAINT_AREA) ||  (u<=1 && u>=0) ){
      tmp::get_para ( b, e, d, a, c, w );
      if ( !(flag & CONSTRAINT_AREA) || (w<=1 && w>=0) ){
	coordsOut[0] = d[0]+t*e[0];
	coordsOut[1] = d[1]+t*e[1];
	coordsOut[2] = d[2]+t*e[2];
	return RELATION_INTERSECTION;
      }
    }
  }
  return RELATION_NONE;
}

void cross_product ( double* a, double* b, double* n )
{
  n[0] = a[1]*b[2] - a[2]*b[1];
  n[1] = a[2]*b[0] - a[0]*b[2];
  n[2] = a[0]*b[1] - a[1]*b[0];
}

double dot_product ( double* a, double* b )
{
	return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

// f = A + uB + wC  ==> A*x + B*y + C*z = D
void get_genpara ( double* A, double* B, double* C, double* planePara )
{
	// nx*(x-x0) + ny*(y-y0) + nz*(z-z0 )=0;
	// ==> nx*x + ny*y + nz*z = nx*x0 + ny*y0 + nz*z0
	double n[3]={0};
	cross_product ( B, C, n );
	normalize( n, n);
	planePara[0] = n[0];
	planePara[1] = n[1];
	planePara[2] = n[2];
	planePara[3] = n[0]*A[0] + n[1]*A[1] + n[2]*A[2];
}


// A + w*B + v*C = D + t*E
// t = (B X C)
int intersection_l2apara ( double* coordsLine, double* A, double* B, double* C, double* coordsOut )
{
//	double A[3] = { coord[0], coord[1], coord[2] };
	//double B[3] = { coord[3]-coord[0], coord[4]-coord[1], coord[5]-coord[2] };
	//double C[3] = { coord[6]-coord[0], coord[7]-coord[1], coord[8]-coord[2] };
	//double D[3] = { coordsLine[0], coordsLine[1], coordsLine[2]};
	double E[3] = { coordsLine[3]-coordsLine[0], coordsLine[4]-coordsLine[1], coordsLine[5]-coordsLine[2] };
	double f[3]={0};
	cross_product ( B, C, f );
	double t = dot_product ( f, E );
	if ( fabs(t)<0.00001 ){
		double para[4];
		get_genpara ( A, B, C, para );
		para[0] = para[0]*coordsLine[0]+para[1]*coordsLine[1]+para[2]*coordsLine[2]-para[3];
		if ( fabs(para[0])<0.00001 )
		//if ( (para[0]*coordsLine[0]+para[1]*coordsLine[1]+para[2]*coordsLine[2]-para[3] )==0 )
			return RELATION_OVERLAP;
		return RELATION_PARALLEL;
	}

	double fa = dot_product ( f, A );
	double fd = dot_product ( f, coordsLine );
	double u = (fa-fd)/t;
	if ( fabs(u-1)<=0.00001 ){
		u = 1;
	}else if(  fabs(u)<=0.00001  ){
		u = 0;
	}

	//if ( coordsLine[0]==42355.019000000000 &&
	//	coordsLine[1]==40718.031999999999 &&
	//	coordsLine[2]==2.9300000000000002 &&
	//	coordsLine[3]==42305.307890455231 &&
	//	coordsLine[4]==40971.721323952355 &&
	//	coordsLine[5]==4.7222550781704289 
	//	)
	//	int aa=0;

	if ( (fabs(u)<0.00001 || u>0) && (fabs(u-1)<0.00001 || u<1 )){
		*coordsOut++ = coordsLine[0] + u*E[0];
		*coordsOut++ = coordsLine[1] + u*E[1];
		*coordsOut = coordsLine[2] + u*E[2];
		return RELATION_INTERSECTION;
	}
	return RELATION_NONE;
}


void generate_tricoords ( double* planePara, double* coord )
{
	do{
		coord[0] = rand()%10000;		coord[1] = rand()%10000;		coord[2] = rand()%10000;
		coord[3] = rand()%10000;		coord[4] = rand()%10000;		coord[5] = rand()%10000;
		coord[6] = rand()%10000;		coord[7] = rand()%10000;		coord[8] = rand()%10000;
		if ( planePara[2] ){
			coord[2] = (planePara[3] - planePara[0]*coord[0] - planePara[1]*coord[1] )/planePara[2];
			coord[5] = (planePara[3] - planePara[0]*coord[3] - planePara[1]*coord[4] )/planePara[2];
			coord[8] = (planePara[3] - planePara[0]*coord[6] - planePara[1]*coord[7] )/planePara[2];
		}else if ( planePara[0] ){
			coord[0] = (planePara[3] - planePara[2]*coord[2] - planePara[1]*coord[1] )/planePara[0];
			coord[3] = (planePara[3] - planePara[2]*coord[5] - planePara[1]*coord[4] )/planePara[0];
			coord[6] = (planePara[3] - planePara[2]*coord[8] - planePara[1]*coord[7] )/planePara[0];
		}else if ( planePara[1] ){
			coord[1] = (planePara[3] - planePara[0]*coord[0] - planePara[2]*coord[2] )/planePara[1];
			coord[4] = (planePara[3] - planePara[0]*coord[3] - planePara[2]*coord[5] )/planePara[1];
			coord[7] = (planePara[3] - planePara[0]*coord[6] - planePara[2]*coord[8] )/planePara[1];
		}else
			throw std::invalid_argument ( "plane para is invalid" );
	}while ( collinear ( coord, coord+3, coord+9 ) );
}

void get_planetricoords ( double* planePara, double* c1, double* c2, double* c3, double* out )
{
	generate_tricoords( planePara, out );
	out[0] = c1[0];	out[1] = c1[1];
	out[3] = c2[0];	out[4] = c2[1];
	out[6] = c3[0];	out[7] = c3[1];
	out[2] = (planePara[3] - planePara[0]*out[0] - planePara[1]*out[1] )/planePara[2];
	out[5] = (planePara[3] - planePara[0]*out[3] - planePara[1]*out[4] )/planePara[2];
	out[8] = (planePara[3] - planePara[0]*out[6] - planePara[1]*out[7] )/planePara[2];
}

// f = A + u*B + w*C
int intersection_tri2apara ( double* coordsTri, double* A, double* B, double* C, double* coordsOut, unsigned char& interFlag )
{
	interFlag = 0;
	double tCoordTri[12];
	memcpy ( tCoordTri, coordsTri, sizeof(double)*9 );
	tCoordTri[9] = coordsTri[0];
	tCoordTri[10] = coordsTri[1];
	tCoordTri[11] = coordsTri[2];
	//generate_tricoords ( planePara, coord );

	// calculate intersection point
	double interp[9]={0};
	double *pInter = interp;
	unsigned char flag=0;
	for ( int i=0; i<3; i++, pInter+=3 ){
		int code = intersection_l2apara ( tCoordTri+3*i, A, B, C, pInter );
		if ( RELATION_INTERSECTION==code )
			interFlag |= (1<<i);
		else if ( RELATION_OVERLAP==code || RELATION_PARTOVERLAP==code )
			flag |= (1<<i);
	}

	// remove overlap
	if ( flag!=1 && flag!=2 && flag!=4 && flag!=0 )
		return RELATION_OVERLAP;
	

	double planePara[4]={0};
	get_genpara ( A, B, C, planePara );
	// remove part nonintersection
	if ( 0==interFlag || flag==1 || flag==2 || flag==4 ){
		double ptSide;
		interFlag = flag;
		if ( flag == 1 )
			ptSide = planePara[0]*coordsTri[6] + planePara[1]*coordsTri[7] + planePara[2]*coordsTri[8] - planePara[3];
		else if ( flag ==2 )
			ptSide = planePara[0]*coordsTri[0] + planePara[1]*coordsTri[1] + planePara[2]*coordsTri[2] - planePara[3];
		else if ( flag ==4 )
			ptSide = planePara[0]*coordsTri[3] + planePara[1]*coordsTri[4] + planePara[2]*coordsTri[5] - planePara[3];
		else if ( interFlag==0 )
			ptSide = planePara[0]*coordsTri[3] + planePara[1]*coordsTri[4] + planePara[2]*coordsTri[5] - planePara[3];
		if ( ptSide<=0 )
			return RELATION_NEGTIVE_SIDE;
		else
			return RELATION_POSITIVE_SIDE;
	}

	// remove intersect with one point
	pInter = interp;
	switch( interFlag )
	{
		case 3:
			if ( equal(pInter[0],pInter[3]) && equal(pInter[1],pInter[4]) && equal(pInter[2],pInter[5]) ){
				if ( (equal(pInter[0],coordsTri[0]) && equal(pInter[1],coordsTri[1]) && equal(pInter[2],coordsTri[2]) ) || 
					(equal(pInter[0],coordsTri[3]) && equal(pInter[1],coordsTri[4]) && equal(pInter[2],coordsTri[5]) ) || 
					(equal(pInter[0],coordsTri[6]) && equal(pInter[1],coordsTri[7]) && equal(pInter[2],coordsTri[8]) ) ){
						if ( (planePara[0]*coordsTri[0] + planePara[1]*coordsTri[1] + planePara[2]*coordsTri[2] - planePara[3])<0 )
							return RELATION_NEGTIVE_SIDE;
						else
							return RELATION_POSITIVE_SIDE;
				}
			}
			break;
		case 5:
			if ( equal(pInter[0],pInter[6]) && equal(pInter[1],pInter[7]) && equal(pInter[2],pInter[8]) ){
				if ( (equal(pInter[0],coordsTri[0]) && equal(pInter[1],coordsTri[1]) && equal(pInter[2],coordsTri[2]) ) || 
					(equal(pInter[0],coordsTri[3]) && equal(pInter[1],coordsTri[4]) && equal(pInter[2],coordsTri[5]) ) || 
					(equal(pInter[0],coordsTri[6]) && equal(pInter[1],coordsTri[7]) && equal(pInter[2],coordsTri[8]) ) ){
						if ( (planePara[0]*coordsTri[3] + planePara[1]*coordsTri[4] + planePara[2]*coordsTri[5] - planePara[3])<0 )
							return RELATION_NEGTIVE_SIDE;
						else
							return RELATION_POSITIVE_SIDE;
				}
			}
			interp[3] = interp[6];
			interp[4] = interp[7];
			interp[5] = interp[8];
			break;
		case 6:
			if ( equal(pInter[3],pInter[6]) && equal(pInter[4],pInter[7]) && equal(pInter[5],pInter[8]) ){
				if ( (equal(pInter[3],coordsTri[0]) && equal(pInter[4],coordsTri[1]) && equal(pInter[5],coordsTri[2]) ) || 
					(equal(pInter[3],coordsTri[3]) && equal(pInter[4],coordsTri[4]) && equal(pInter[5],coordsTri[5]) ) || 
					(equal(pInter[3],coordsTri[6]) && equal(pInter[4],coordsTri[7]) && equal(pInter[5],coordsTri[8]) ) ){
						if ( (planePara[0]*coordsTri[3] + planePara[1]*coordsTri[4] + planePara[2]*coordsTri[5] - planePara[3])<0 )
							return RELATION_NEGTIVE_SIDE;
						else
							return RELATION_POSITIVE_SIDE;
				}
			}
			interp[0] = interp[3];
			interp[1] = interp[4];
			interp[2] = interp[5];
			interp[3] = interp[6];
			interp[4] = interp[7];
			interp[5] = interp[8];
			break;
		default:
			{
				if ( fabs(pInter[0]-pInter[3])<0.1 && fabs(pInter[1]-pInter[4])<0.1 && fabs(pInter[2]-pInter[5])<0.1 ){
					pInter += 6;
					interFlag = 2;
				}else if ( fabs(pInter[0]-pInter[6])<0.1 && fabs(pInter[1]-pInter[7])<0.1 && fabs(pInter[2]-pInter[8])<0.1 ){
					pInter += 3;
					interFlag = 1;
				}else if ( fabs(pInter[3]-pInter[6])<0.1 && fabs(pInter[4]-pInter[7])<0.1 && fabs(pInter[5]-pInter[8])<0.1 )
					interFlag = 4;
				else
					throw std::logic_error ("impossible");
				memcpy ( coordsOut, pInter, sizeof(double)*6 );
				return RELATION_INTERPOINT;
			}
			break;
	}

	memcpy ( coordsOut, interp, sizeof(double)*6 );
	return RELATION_INTERSECTION;
}
double distance2d ( double x1, double y1, double x2, double y2 )
{
  return sqrt ( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

double distance3d ( double x1, double y1, double z1, double x2, double y2, double z2 )
{
  return sqrt ( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2) );
}

double distance3dv ( double* c1, double *c2 )
{
  return sqrt ( (c1[0]-c2[0])*(c1[0]-c2[0]) + (c1[1]-c2[1])*(c1[1]-c2[1]) + (c1[2]-c2[2])*(c1[2]-c2[2]) );
}

double distance2dv ( double* c1, double *c2 )
{
  return sqrt ( (c1[0]-c2[0])*(c1[0]-c2[0]) + (c1[1]-c2[1])*(c1[1]-c2[1]) );
}

int intersection_l2l ( double* coordLine1, double* coordLine2, double* coordsOut )
{
  struct tmp{
    static bool get_t ( double a, double b, double& t )
    {
      if ( a==0 )
	return false;
      t = b/a;
      return true;
    }
    static int check_overlap ( double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz )
    {
      double t;
      if ( get_t ( bx-ax, cx-ax, t ) ){
	if ( (fabs(ay+(by-ay)*t - cy) < DIST_EXTEND) && (fabs(az+(bz-az)*t - cz) < DIST_EXTEND) ){
	  if ( t<=1 && t>=0 )
	    return RELATION_INSIDE;
	  else
	    return RELATION_EXTENDLINE;
	}else{
	  return RELATION_OUTSIDE;
	}
      }else if ( get_t ( by-ay, cy-ay, t ) ){
	if ( (fabs(ax - cx) < DIST_EXTEND) && (fabs(az+(bz-az)*t - cz) < DIST_EXTEND) ){
	  if ( t<=1 && t>=0 )
	    return RELATION_INSIDE;
	  else
	    return RELATION_EXTENDLINE;
	}else{
	  return RELATION_OUTSIDE;
	}
      }else if ( get_t ( bz-az, cz-az, t ) ){
	if ( (fabs(ax - cx) < DIST_EXTEND) && (fabs(ay - cy) < DIST_EXTEND ) ){
	  if ( t<=1 && t>=0 )
	    return RELATION_INSIDE;
	  else
	    return RELATION_EXTENDLINE;
	}else{
	  return RELATION_OUTSIDE;
	}
      }
      if ( cx==ax && cy==ay && cz==az )
	return RELATION_INSIDE;
      return RELATION_OUTSIDE;
    }
  };
  double ax = coordLine1[0], ay = coordLine1[1], az = coordLine1[2];
  double bx = coordLine1[3], by = coordLine1[4], bz = coordLine1[5];
  double cx = coordLine2[0], cy = coordLine2[1], cz = coordLine2[2];
  double dx = coordLine2[3], dy = coordLine2[4], dz = coordLine2[5];

// check overlap
  int b1 = tmp::check_overlap( ax, ay, az, bx, by, bz, cx, cy, cz );
  int b2 = tmp::check_overlap( ax, ay, az, bx, by, bz, dx, dy, dz );
  if ( (RELATION_INSIDE==b1 && RELATION_INSIDE==b2) ||
       (RELATION_EXTENDLINE==b1 && RELATION_EXTENDLINE==b2) )
    return RELATION_OVERLAP;
  else if ( (RELATION_INSIDE==b1 && RELATION_EXTENDLINE==b2) ||
	    (RELATION_INSIDE==b2 && RELATION_EXTENDLINE==b1) )
    //	    (RELATION_INSIDE==b2) && (RELATION_EXTENDLINE==b1) )
    return RELATION_PARTOVERLAP;

  double d = (by*dx-bx*dy);
  if ( d != 0 ){
    double s = (by*(ax-cx)+by*(cy-ay))/d;
    double t = (dx*(ay-cy)+by*(cx-ax))/(-d);
    if ( (az+bz*t - cz - dz*s)< DIST_EXTEND ){
      if ( s<=1 && s>=0 && t<=1 && t>=0 ){
	coordsOut[0] = ax + bx*t;
	coordsOut[1] = ay + by*t;
	coordsOut[2] = az + bz*t;
	return RELATION_INTERSECTION;
      }
    }
  }
  return RELATION_NONE;
}

void plane_genpara ( double* coord1, double* coord2, double* coord3, double& A, double& B, double& C, double& D )
{
  // A*x + B*y + C*z = D
  double x1 = coord1[0];
  double x2 = coord2[0]-x1;
  double x3 = coord3[0]-x1;
  double y1 = coord1[1];
  double y2 = coord2[1]-y1;
  double y3 = coord3[1]-y1;
  double z1 = coord1[2];
  double z2 = coord2[2]-z1;
  double z3 = coord3[2]-z1;
	
  A = y2*z3-y3*z2;
  B = x3*z2-x2*z3;
  C = x2*y3-x3*y2;
  if ( A==0 && B==0 && C==0 )
	  throw std::invalid_argument ("three point on a line");
  D = A*x1 + B*y1 + C*z1;
}

void unit_normal ( double* c1, double* c0, double* c2, float* unitNormal )
{
  double ax = c1[0] - c0[0];
  double ay = c1[1] - c0[1];
  double az = c1[2] - c0[2];
  double bx = c2[0] - c0[0];
  double by = c2[1] - c0[1];
  double bz = c2[2] - c0[2];

  double A = ay*bz - az*by;
  double B = az*bx - ax*bz;
  double C = ax*by - ay*bx;
  double D = sqrt ( A*A + B*B + C*C );

  if ( D==0 )
    throw std::invalid_argument ("three points on a line");

  unitNormal[0] = A/D;
  unitNormal[1] = B/D;
  unitNormal[2] = C/D;
}

double direction_angle4dv ( double* c1, double* c0, double* c2, float* unitNormal )
{
  double ax = c1[0] - c0[0];
  double ay = c1[1] - c0[1];
  double az = c1[2] - c0[2];
  double bx = c2[0] - c0[0];
  double by = c2[1] - c0[1];
  double bz = c2[2] - c0[2];

  double A = ay*bz - az*by;
  double B = az*bx - ax*bz;
  double C = ax*by - ay*bx;

  double D = sqrt ( A*A + B*B + C*C );
  double tmp = ax*bx + ay*by + az*bz;

  if ( D==0 ){
    if ( tmp > 0 )
      return 0;
    else
      return M_PI;
  }


  return atan2 (A*unitNormal[0] + B*unitNormal[1] + C*unitNormal[2], tmp );

  //if ( tmp==0 ){  // 90 or 270
  //  throw std::invalid_argument ("direction is error");
  //}

  //// get unit normal
  //A /= D;  B /= D;  C /= D;

  //if ( equal(fabs(A), fabs(unitNormal[0])) && 
  //     equal(fabs(B), fabs(unitNormal[1])) && 
  //     equal(fabs(C), fabs(unitNormal[2])) ){
  //  if ( equal(A, unitNormal[0]) && 
	 //equal(B, unitNormal[1]) && 
	 //equal(C, unitNormal[2]) ){
  //    // same direction
  //    return atan2 ( D, tmp );
  //  }else{
  //    // reverse
  //    return atan2 ( -D, tmp );
  //  }
  //}else{
  //  throw std::invalid_argument ("direction is error");
  //}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------
int collinear ( double* coord1, double* coord2, double* coord3 )
{
  // vector product
  //double ax = c2[0]-c1[0], ay = c2[1]-c1[1], az = c2[2]-c1[2];
  //double bx = c3[0]-c1[0], by = c3[1]-c1[1], bz = c3[2]-c1[2];
  //
  //if ( fabs(ay*bz-az*by)<0.0001 && fabs(az*bx-ax*bz)<0.0001 && fabs(ax*by-ay*bx)<0.0001 )
  //  return true;
  //return false;
	double c1[] = {coord1[0], coord1[1], coord1[2] }, c2[] = {coord2[0], coord2[1], coord2[2] }, c3[] = {coord3[0], coord3[1], coord3[2] };
	for ( int i=0; i<2; i++ ){
		double a[3] = { c2[0]-c1[0], c2[1]-c1[1], c2[2]-c1[2] }, u;
		if ( a[0] )
			u = (c3[0]-c1[0])/a[0];
		else if ( a[1] )
			u = (c3[1]-c1[1])/a[1];
		else if ( a[2] )
			u = (c3[2]-c1[2])/a[2];
		else{
			double tmp = c1[0];		c1[0] = c2[0];		c2[0] = c3[0];		c3[0] = tmp;
			tmp = c1[1];		c1[1] = c2[1];			c2[1] = c3[1];		c3[1] = tmp;
			tmp = c1[2];		c1[2] = c2[2];			c2[2] = c3[2];		c3[2] = tmp;
			continue;
		}

		if ( fabs(c1[0]+u*a[0]-c3[0])<0.0001 &&
			fabs(c1[1]+u*a[1]-c3[1])<0.0001 &&
			fabs(c1[2]+u*a[2]-c3[2])<0.0001 ){
				if ( u<0 )
					return COLLINEAR_LEFT;
				if ( u>1 )
					return COLLINEAR_RIGHT;
				if ( u==0 )
					return COLLINEAR_LEFTEND;
				if ( u==1 )
					return COLLINEAR_RIGHTEND;
				return COLLINEAR_MIDDLE;
		}
		return COLLINEAR_NONE;
	}
	throw std::invalid_argument ("three point is one point" );
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------
double mincos_intri ( double* c1, double* c2, double* c3 )
{
  double a[3] = { c1[0]-c2[0], c1[1]-c2[1], c1[2]-c2[2] };
  double b[3] = { c2[0]-c3[0], c2[1]-c3[1], c2[2]-c3[2] };
  double c[3] = { c3[0]-c1[0], c3[1]-c1[1], c3[2]-c1[2] };

  double A = sqrt( a[0]*a[0] + a[1]*a[1] + a[2]*a[2] );
  double B = sqrt( b[0]*b[0] + b[1]*b[1] + b[2]*b[2] );
  double C = sqrt( c[0]*c[0] + c[1]*c[1] + c[2]*c[2] );

  double AA = A*A, BB = B*B, CC = C*C;
  double min = (AA+BB-CC)/(2*A*B);
  double tmp = (BB+CC-AA)/(2*B*C);
  min = min<tmp ? min : tmp;
  tmp = (CC+AA-BB)/(2*C*A);
  min = min<tmp ? min : tmp;
  return min;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
bool clockwise ( double* c1, double* c2, double* c3)
{
	double rst = (c1[1]+c2[1])*(c2[0]-c1[0])+(c2[1]+c3[1])*(c3[0]-c2[0])+(c3[1]+c1[1])*(c1[0]-c3[0]);
	return rst>0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------
void trim_end ( char* pDest )
{
  char* end = pDest-1, *pp;
  for ( pp=pDest+strlen(pDest)-1; pp!=end; --pp ){
    if ( *pp > 255 || *pp<0 )
      continue;
    if ( isspace ( *pp ) )
      continue;
    *(pp+1) = 0;
    break;
  }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------
int get_sub ( const char *pSrc, char* pDest, char delimiter )
{
  const char *end = strchr ( pSrc, delimiter ), *pp;
  if ( end==NULL )
    end = pSrc + strlen ( pSrc )+1;
  for ( pp=pSrc; pp!=end; pp++ ){
	if (*pp < 0){
		pp ++;
		continue;
	}
	if ( (*pp == 0x20) || (*pp==0x0d) || (*pp==0x0a) || (*pp=='\t') )
		continue;
	memcpy ( pDest, pp, end-pp );
    *(pDest+(end-pp)) = 0;
    trim_end ( pDest );
    return end-pSrc;
  }
  return 0;
}	
//---------------------------------------------------------------------------------------------------------------------------------------------------------
void cross_product (double* c0, double* c1, double* c2, float* n)
{
  double ax = c1[0] - c0[0];
  double ay = c1[1] - c0[1];
  double az = c1[2] - c0[2];
  double bx = c2[0] - c0[0];
  double by = c2[1] - c0[1];
  double bz = c2[2] - c0[2];

  n[0] = ay*bz - az*by;
  n[1] = az*bx - ax*bz;
  n[2] = ax*by - ay*bx;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------
void normalize(double nx, double ny, double nz, float* nCoord)
{
	double d = sqrt( nx*nx+ny*ny+nz*nz );
	nCoord[0] = nx/d;
	nCoord[1] = ny/d;
	nCoord[2] = nz/d;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
void normalize(double* c, double* n)
{
	double d = sqrt( c[0]*c[0]+c[1]*c[1]+c[2]*c[2] );
	n[0] = c[0]/d;
	n[1] = c[1]/d;
	n[2] = c[2]/d;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------

