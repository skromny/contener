#pragma once
class __declspec(dllexport) Shape {
private:

public:
	Shape() {
	}
	virtual ~Shape() {
	};
	double  x, y;
	void    move(double dx, double dy);
	virtual double area(void) = 0;
	virtual double perimeter(void) = 0;
};

class __declspec(dllexport) Circle : public Shape {
private:
	double radius;
public:
	Circle(double r) : radius(r) { };
	virtual double area(void);
	virtual double perimeter(void);
};

class __declspec(dllexport) Square : public Shape {
private:
	double width;
public:
	Square(double w) : width(w) { };
	virtual double area(void);
	virtual double perimeter(void);
};

