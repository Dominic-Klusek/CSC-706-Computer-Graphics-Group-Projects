// File: ...Appendix/canvas.h

    // Protect against multiple #include's
#ifndef Canvas_FLAG_
#define Canvas_FLAG_

//Appendix 3. Some useful Classes and Utility Routines.
//This appendix defines some basic types and algorithms
//that may prove useful as you develop graphics applications
//as described throughout the book. The basic types are
//developed through classes which can be used at will.

//Some of the classes are fully developed here. Others have
//a number of methods declared but not defined: It is up to
//the student to flesh these out. Some classes are given here
//in very skeletal form, to suggest what might be developed
//in an actual application.

//In most classes a relaxed approach to encapsulation is
//taken: most data fields are declared public rather than
//private, as a matter of brevity and to avoid the need to
//define a large number of accessor and mutator functions.

//Another excellent source of classes and utilities may be
//found in the Graphics Gems series, whose on-line repository
//is http://www.acm.org/tog/GraphicsGems/index.html.


//Classes for 2D graphics.
// definition of simple support classes:
#include <string>
#include <iostream>
#include <fstream>
#include <strstream>
using namespace std;

//#include <windows.h> //change if using xWindows
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include<GL/glut.h>
//#include <GL/freeglut.h>


//<<<<<<<<<<<<<<<<<<<<<<< GLintPoint >>>>>>>>>>>>>>>>>>>>
class GLintPoint {
public:
  GLint x, y;
  GLintPoint(void){ x = y = 0; }
  GLintPoint(const int xx, const int yy){ x = xx; y = yy; }
  GLintPoint(GLintPoint& p){ x = p.x; y = p.y; }
  GLintPoint operator= (GLintPoint p) {
    x = p.x;  y = p.y;  return *this;  // return a copy of this object
  }
  void set(const int xx, const int yy){ x = xx; y = yy; }
};


//@@@@@@@@@@@@@@@@@@ IntPoint class @@@@@@@@@@@@@@@@
class IntPoint{ // for 2D points with integer coordinates
public:
    int x,y;
    void set(int dx, int dy){x = dx; y = dy;}
    void set(IntPoint& p){ x = p.x; y = p.y;}
    IntPoint(int xx, int yy){x = xx; y = yy;}
    IntPoint(){ x = y = 0;}
};


//@@@@@@@@@@@@@@@@@@ Point2 class @@@@@@@@@@@@@@@@
class Point2{ // for 2D points with real coordinates
public:
    float x, y;
    void set(float dx, float dy){x = dx; y = dy;}
    void set(Point2& p){ x = p.x; y = p.y;}
    Point2(float xx, float yy){x = xx; y = yy;}
    Point2(){x = y = 0;}
    float getX(void) { return x; }
    float getY(void) { return y; }
    float distanceTo (const Point2 P) {
       return sqrt((x - P.x)*(x - P.x) + (y - P.y)*(y - P.y));
    }
};


//<<<<<<<<<<<<<<<<<<<< Canvas class >>>>>>>>>>>
// a global Canvas object (described in Chapter 3) knows how
// to draw lines in world coordinates and to perform turtlegraphics
class Canvas {

 private:
    Point2 CP;  // current position in world
    float CD;   // current direction in degrees

 public:
    float windowAspect;
    Canvas(int width, int height, char* title)
    {
        // See Hill, Figure 3.27
        // Distributed code has no string to point to
        char* argv[1];       //dummy list for glutInit
        char dummyString[8];
        argv[0] = dummyString;
        int numArgs = 1;  //dummy value for glutInit

        // cout << "creating canvas ...\n";

        glutInit(&numArgs, argv);
		//glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(width, height);
        glutInitWindowPosition(100, 100);
        glutCreateWindow(title);
        setBackgroundColor(1.0, 1.0, 1.0);
        setColor(0.0, 0.0, 0.0);
        CP.x = CP.y = 0.0;
        windowAspect = 1.0;
    }
    void setWindow(float l, float r, float b, float t)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho((GLdouble)l, (GLdouble)r, (GLdouble)b, (GLdouble)t, -1, 1);
        if(t == b) return;
        windowAspect = (r - l)/(t - b);
    }
    void setViewport(int x, int y, int width, int height)
        {glViewport((GLint)x, (GLint)y, (GLint)(width), (GLint)(height));}
    float getWindowAspect(void) { return windowAspect;}
    Point2 getCP(void) { return CP; }
    void lineTo(float x, float y)
    {
        glBegin(GL_LINES);
        glVertex2f((GLfloat)CP.x, (GLfloat)CP.y);
        CP.x = x; CP.y = y;
        glVertex2f((GLfloat)CP.x, (GLfloat)CP.y);
        glEnd();
		glutSwapBuffers();
		//glFlush();
    }
	void drawPolygon(Point2* vertices, int vertexNumber)
	{
		int i = 0;
		if(vertices == NULL || vertexNumber == 0)
			;
		else
		{
			glBegin(GL_POLYGON);
				for(i = 0; i < vertexNumber; i++)
				{
					CP.x = vertices[i].x;
					CP.y = vertices[i].y;
                    glVertex2f((GLfloat)CP.x, (GLfloat)CP.y);
				}
			glEnd();
		}
		glutSwapBuffers();
			
	}
    void moveTo(float x, float y){ CP.x = x; CP.y = y; }
    void turn(float ang)   { CD += ang; }
    void turnLeft(void)    { turn(90.0); }
    void turnRight(void)   { turn(-90.0); }
    void turnTo(float ang) { CD = ang; }
    void forward(float dist, int vis) {
        #define RadPerDeg 0.017453393 //radians per degree
        float x = CP.x + dist * cos(RadPerDeg * CD);
        float y = CP.y + dist * sin(RadPerDeg * CD);
        if(vis) lineTo(x, y);
        else moveTo(x, y);
        CP.x = x; CP.y = y;
    }
    void forward(int dist, int vis) { forward((float)dist, vis); }
	void forward(float dist, int vis, int mode, Point2 *vertices, int vertexNumber)
	{
		if (mode == 0)
			forward(dist,vis);
		else if(mode == 1) //Go forward but draw a polygon!
		{
			#define RadPerDeg 0.017453393 //radians per degree
			float x = CP.x + dist * cos(RadPerDeg * CD);
			float y = CP.y + dist * sin(RadPerDeg * CD);
			if(vis) drawPolygon(vertices, vertexNumber);
			CP.x = x; CP.y = y;
		}

	}
    void initCT() { // initialize the CT (model view matrix)
        glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    }
    void rotate2D(double angle) {
        glMatrixMode(GL_MODELVIEW); glRotated(angle, 0.0, 0.0, 1.0);
    }
    void translate2D(double dx, double dy) {
        glMatrixMode(GL_MODELVIEW); glTranslated(dx, dy, 0.0);
    }
    void scale2D(double sx, double sy) {
        glMatrixMode(GL_MODELVIEW); glScaled(sx, sy, 1.0);
    }
    void scale2D(double s) { scale2D(s, s); }
    void pushCT(void) {
        glMatrixMode(GL_MODELVIEW); glPushMatrix();
    }
    void popCT(void) {
        glMatrixMode(GL_MODELVIEW); glPopMatrix();
    }


    // Member functions added by George Corliss for Figure 3.26:
    void clearScreen(void) {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void setBackgroundColor(GLclampf red, GLclampf green, GLclampf blue) {
        glClearColor(red, green, blue, 0.0);
    }
    void setColor(GLfloat red, GLfloat green, GLfloat blue) {
        glColor3f(red, green, blue);
    }

};


//<<<<<<<<<<<<<<<<<<<<<< PolyLine >>>>>>>>>>>>>>>>>>>>>>>>>
class PolyLine{ // a polyline is a num plus an array of points
public:
    int num;
    Point2 pt[80]; //may need larger arrays in some circumstances
    PolyLine(){num = 0;}
};


// @@@@@@@@@@@@@@@@@@@@@@@@ IntRect class @@@@@@@@@@@@@@@@@@@@
class IntRect{ // a rectangle with integer border values
public:
  int left, top, right, bott;
  IntRect(){left = top = right = bott = 0;}
  IntRect(int l, int t, int r, int b)
  {left = l; top = t; right = r; bott = b;}
  void set(int l, int t, int r, int b)
  {left = l; top = t; right = r; bott = b;}
  void set(IntRect& r)
  {left = r.left; top = r.top; right = r.right; bott = r.bott;}
  void draw (Canvas cvs) {
     cvs.moveTo(left,  top );
     cvs.lineTo(right, top );
     cvs.lineTo(right, bott);
     cvs.lineTo(left,  bott);
     cvs.lineTo(left,  top );
  }
};


// @@@@@@@@@@@@@@@@@@@@@@@@ RealRect class @@@@@@@@@@@@@@@@@@@@
class RealRect{ // a rectangle with integer border values
public:
  float left, top, right, bott;
  RealRect(){left = top = right = bott = 0;}
  RealRect(float l, float t, float r, float b)
  {left = l; top = t; right = r; bott = b;}
  void set(float l, float t, float r, float b)
  {left = l; top = t; right = r; bott = b;}
  void set(RealRect& r)
  {left = r.left; top = r.top; right = r.right; bott = r.bott;}
  void draw (Canvas cvs) {
     cvs.moveTo(left,  top );
     cvs.lineTo(right, top );
     cvs.lineTo(right, bott);
     cvs.lineTo(left,  bott);
     cvs.lineTo(left,  top );
  }
};



// @@@@@@@@@@@@@@@@@@@@@@@@ ngon class @@@@@@@@@@@@@@@@@@@@
class ngon { // a rectangle with integer border values
public:
  int n;
  float cx, cy, radius, rotAngle;
  ngon(void){
     n  = 0;
     cx = cy = radius = rotAngle = 0;
  }
  ngon(int nn, float ccx, float ccy, float rradius, float rrotAngle){
     if (nn < 3) { n = 3; }
     else { n = nn; }
     cx = ccx; cy = ccy; radius = rradius; rotAngle = rrotAngle;
  }
  void set (int nn, float ccx, float ccy, float rradius, float rrotAngle)
  {
     if (nn < 3) { n = 3; }
     else { n = nn; }
     cx = ccx; cy = ccy; radius = rradius; rotAngle = rrotAngle;
  }
  void set(ngon& r) {
     n = r.n; cx = r.cx; cy = r.cy;
     radius = r.radius; rotAngle = r.rotAngle;
  }
  void draw (Canvas cvs) {
      double angle = rotAngle * 3.14159265 / 180;  // initial angle
      double angleInc = 2 * 3.14159265 /n;         //angle increment
//      cvs.moveTo(radius + cx, cy);  // Hill's code.  GC mod:
      cvs.moveTo(radius * cos(angle) + cx,
                 radius * sin(angle) + cy);
      for(int k = 0; k < n; k++)                   // repeat n times
      {
         angle += angleInc;
         cvs.lineTo(radius * cos(angle) + cx,
                    radius * sin(angle) + cy);
      }
  }
};


//@@@@@@@@@@@@@@@@@@ Vector2 class @@@@@@@@@@@@@@@@
class Vector2{
public:
    float x,y;
    void set(float dx, float dy){ x = dx; y = dy; }
    void set(Vector2& v){ x = v.x; y = v.y;}
    void setDiff(Point2& a, Point2& b)//set to difference a - b
    {x = a.x - b.x; y = a.y - b.y;}
    void normalize()//adjust this vector to unit length
    {       double sizeSq = x * x + y * y;
        if(sizeSq < 0.0000001)
        {
            cerr << "\nnormalize() sees vector (0,0)!";
            return; // does nothing to zero vectors;
        }
        float scaleFactor = 1.0/(float)sqrt(sizeSq);
        x *= scaleFactor; y *= scaleFactor;
    }
    Vector2(float xx, float yy){x = xx; y = yy; }
    Vector2(Vector2& v){x = v.x; y = v.y; }
    Vector2(){x = y = 0;} //default constructor
    float dot(Vector2 b) // return this dotted with b
    {return x * b.x + y * b.y;}
    void perp() // perp this vector
    {float tmp = x; x = -y; y = tmp;}
    float perpDot(Vector2& v) // return perp of this dotted with v
    {return x *v.x - y * v.y;}
};


//3D Classes for Graphics

//@@@@@@@@@@@@@@@@@@ Point3 class @@@@@@@@@@@@@@@@
class Point3{
public:
    float x, y, z;
    void set(float dx, float dy, float dz){x = dx; y = dy; z = dz;}
    void set(const Point3& p){x = p.x; y = p.y; z = p.z;}
    Point3(float xx,     float yy, float zz){x = xx; y = yy; z = zz;}
    Point3(){x = y = z = 0;}
    Point3(int dx, int dy, int dz){x = dx; y = dy; z = dz;}
    void build4tuple(float v[])
    {// load 4-tuple with this color: v[3] = 1 for homogeneous
        v[0] = x; v[1] = y; v[2] = z; v[3] = 1.0f;
    }
};


//@@@@@@@@@@@@@@@@@@ Vector3 class @@@@@@@@@@@@@@@@
class Vector3{
public:
    float x, y, z;
    void set(float dx, float dy, float dz){ x = dx; y = dy; z = dz;}
    void set(const Vector3& v){ x = v.x; y = v.y; z = v.z;}
    void flip(){x = -x; y = -y; z = -z;}  // reverse this vector
    void setDiff(const Point3& a, const Point3& b)    // set to difference a - b
    { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;}
    void normalize()      //adjust this vector to unit length
    {
        double sizeSq = x * x + y * y + z * z;
        if(sizeSq < 0.0000001) {
            cerr << "\nnormalize() sees vector (0,0,0)!";
            return; // does nothing to zero vectors;
        }
        float scaleFactor = 1.0/(float)sqrt(sizeSq);
        x *= scaleFactor; y *= scaleFactor; z *= scaleFactor;
    }
    Vector3(float xx, float yy, float zz){x = xx; y = yy; z = zz;}
    Vector3(int xx, int yy, int zz){x = xx; y = yy; z = zz;}
    Vector3(Vector3& v){x = v.x; y = v.y; z = v.z;}
    Vector3(){x = y = z = 0;}  //default constructor
    Vector3 cross(Vector3 b)   //return this cross b
    {
       Vector3 c(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
       return c;
    }
    float dot(Vector3 b) // return this dotted with b
    {return x * b.x + y * b.y + z * b.z;}
};


// @@@@@@@@@@@@@@@@@@@@@ Color3 class @@@@@@@@@@@@@@@@
class Color3 { // holds an red, green, blue 3-tuple
public:
    float red, green, blue;
    Color3(){red = green = blue = 0;}
    Color3(float r, float g, float b){red = r; green = g; blue = b;}
    Color3(Color3& c){red = c.red; green = c.green; blue = c.blue;}
    void set(float r, float g, float b){red = r; green = g; blue = b;}
    void set(Color3& c)
      {red = c.red; green = c.green; blue = c.blue;}
    void add(float r, float g, float b)
      {red += r; green += g; blue += b;}
    void add(Color3& src, Color3& refl)
    { // add the product of source color and reflection coefficient
        red   += src.red   * refl.red;
        green += src.green * refl.green;
        blue  += src.blue  * refl.blue;
    }
    void add(Color3& colr)
    { // add colr to this color
     red += colr.red ; green += colr.green; blue += colr.blue;}
    void build4tuple(float v[])
    {// load 4-tuple with this color: v[3] = 1 for homogeneous
        v[0] = red; v[1] = green; v[2] = blue; v[3] = 1.0f;
    }
};


//@@@@@@@@@@@@@@@@@@@@ light class @@@@@@@@@@@@@@@@@@@
class Light{ // for a linked list of light sources color and position
public:
    Point3 pos;
    Color3 color;
    Light* next;
    void setPosition(Point3 p){pos.set(p);}
    void setColor(Color3 c){color.set(c);}
    Light(){next = NULL;}
};


#endif Canvas_FLAG_
