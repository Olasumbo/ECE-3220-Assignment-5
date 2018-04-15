//============================================================================
// Name        : Lab.cpp
// Author      : Ola
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>

using namespace std;
#define PI 3.1416

class BaseConic
{
	protected:
		double x;
		double y;

	public:
		// Notice the default values. They don't need to be 0
		BaseConic(double x0 = 0, double y0 = 0){x = x0; y = y0;}
		virtual ~BaseConic(){};
		void Move(double nx, double ny){x = nx; y = ny;}
		virtual double Area() = 0; // a pure virtual function ==> ABC
		virtual void display() = 0;
};

class Ellipse : public BaseConic
{
	private:
		double a; 	// semi-major axis
		double b; 	// semi-minor axis
		double angle; // orientation angle

	public:
		Ellipse(double x0, double y0, double a0, double b0, double an0);
		~Ellipse(){}
		virtual double Area() {return PI*a*b;}
		void Rotate(double nang){angle += nang;}
		virtual void display();
		void Resize(double x, double y);//o modify the radius or semi-major/minor axis values, respectively;
		void Display();
		void Vertices();
};

// Notice the default values. Those are used if no parameter is given when
// an object is created.
// Notice how the BaseConic constructor can be called. If other constructors where defined,
// those could be used instead.
Ellipse::Ellipse(double x0=1,double y0=0,double a0=0,double b0=0,double an0=0) : BaseConic(x0,y0) {
	// x and y are set in the BaseConic constuctor
	a = a0;
	b = b0;
	angle = an0;
}

void Ellipse:: Resize(double x, double y)
{
	a = x;
	b = y;
	cout << "New Area of Ellipse is" << Area() << endl;
}

void Ellipse::display()
{
	cout << "x = " << x << ", y = " << y << ", a = " << a << ", b = " << b
		 << ", angle = " << angle << ", Area = " << this->Area() << endl;
}

void Ellipse::Vertices()
{
	double vertexmajor;
	double vertexminor;
	if (a > b)
	{
		cout << a << " is the semi-major value" << endl;
		vertexmajor = (a/2);
		vertexmajor = (b + 2);
	}
	else
	{
		return;
	}
}

class Circle : public BaseConic
{
	private:
		double r; 	// radius

	public:
		virtual double Area() {return PI*r*r;}
		Circle(double x0=1,double y0=1,double r0=1) : BaseConic(x0,y0){r = r0;}
		virtual void display();
		void Resize(double Newr);//o modify the radius or semi-major/minor axis values, respectively;
		bool inside(double x_in, double y_in);
};

void Circle::display()
{
	cout << "x = " << x << ", y = " << y << ", r = " << r
		 << ", Area = " << this->Area() << endl;
}
bool Circle::inside( double x_in, double y_in )
{
	x_in -= x;
	y_in -= y;

	double distance = sqrt( x_in*x_in + y_in*y_in );

	if( distance < r )
	{
		return true;
	}
	else
	{
		return false;
	} // END if...else

}
void Circle::Resize(double Newr)
{
	r = Newr;
}

int main()
{
	//BaseConic b0;	// not possible to create an object of the ABC
	cout << "==========CIRCLE==========" << endl;
	Circle c0, c1(2,-1,5);
	c0.display();
	c1.display();

	c1.Move(-20,32);
	c1.display();
	cout << "Circle area: " << c1.Area() << endl;
	c1.Resize(54);
	c1.display();

	cout << endl << "==========ELLIPSE==========" << endl;
	Ellipse e0, e2(0.1,0.2,0.3,0.4,0.5);
	e2.display();
	e2.Move(10, 6);
	cout << "Ellipse area: " << e2.Area() << endl;
	e2.Resize(5, 4);
	e2.Rotate(45);
	e2.display();
	cout << "\n--------------------------------------------------------------\n" << endl;
	cout << "\n--------------------------------------------------------------\n" << endl;

	// You CAN use ABC pointers and references
	BaseConic *bptr2 = new Ellipse(1,1,2,3,0.5);
	bptr2->display();

	cout << "\n--------------------------------------------------------------\n" << endl;

	BaseConic *bptr4 = new Circle(-3,0,1.5);
	bptr4->display();

	delete bptr2;
	delete bptr4;
}
