#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <iomanip>

const double PI = 3.14159;

/***********************************************************************
* Declaration/Definition of the base-class Shape *
***********************************************************************/
class Shape {
public:
    // constructors and destructor
    Shape(){};
    virtual ~Shape(){};
    // Accessors; you should decide which should be virtual or pure virtual.
    virtual double CalculateArea() const=0;
    virtual double CalculatePerimeter() const=0;
    virtual int NumberCorners() const=0;

//private:
    // member variables;

};


/***********************************************************************
* Declaration/Definition of the child-classes *
***********************************************************************/
class Rectangle:public Shape
{
public:    
    Rectangle(double height,double width):Shape()
    {
        h=height;
        w=width;
    }
    virtual ~Rectangle()
    {
        std::cout << "A Rectangle has been destroyed.\n";
    }
    double CalculateArea() const
    {
        return h*w;
    }
    double CalculatePerimeter() const
    {
        return 2*(h+w);
    }
    int NumberCorners() const
    {
        return 4;
    }

private:
    double h;
    double w;

};

class Square:public Shape
{
public:    
    Square(double length):Shape()
    {
        l=length;
    }
    virtual ~Square()
    {
        std::cout << "A Square has been destroyed.\n";
    }
    double CalculateArea() const{
        return l*l;
    }
    double CalculatePerimeter() const{
        return 4*l;
    }
    int NumberCorners() const{
        return 4;
    }

private:
    double l;

}; // ...
class Triangle:public Shape
{
public:    
    Triangle(double height,double width):Shape()
    {
        h=height;
        w=width;
    }
    virtual ~Triangle()
    {
        std::cout << "A Triangle has been destroyed.\n";
    }
    double CalculateArea() const{
        return h*w/2;
    }
    double CalculatePerimeter() const{
        return h+w+sqrt(h*h+w*w);
    }
    int NumberCorners() const{
        return 3;
    }

private:
    double h;
    double w;

}; // ...
class Circle:public Shape
{
public:    
    Circle(double radius):Shape()
    {
        r=radius;
    }
    virtual ~Circle()
    {
        std::cout << "A Circle has been destroyed.\n";
    }
    double CalculateArea() const{
        return PI*r*r;
    }
    double CalculatePerimeter() const{
        return 2*PI*r;
    }
    int NumberCorners() const{
        return 0;
    }

private:
    double r;

}; // ...

/************************************************************************
* Main Function which is creating/reporting database (do not change!) *
************************************************************************/
int main() {
    //initialize an empty list of shapes
    std::list<Shape*> shapeDatabase;
    //interact with the user: ask the user to enter shapes one by one
    while (1) {
        //print instructions as to how to enter a shape
        std::cout << "Enter a type (Circle, Triangle, Square, or Rectangle) ";
        std::cout << "and one or two size parameters, ";
        std::cout << "separated with blank spaces:\n";
        double size1;
        double size2;
        //check which shape has been requested and store in the database
        std::string shapeType;
        std::cin >> shapeType;
        if (shapeType == std::string("Circle")) {
            std::cin >> size1;
            shapeDatabase.push_back( new Circle(size1) );
        }
        else if (shapeType == std::string("Triangle")) {
            std::cin >> size1 >> size2;
            shapeDatabase.push_back( new Triangle(size1,size2) );
        }
        else if (shapeType == std::string("Square")) {
            std::cin >> size1;
            shapeDatabase.push_back( new Square(size1) );
        }
        else if (shapeType == std::string("Rectangle")) { 
            std::cin >> size1 >> size2;
            shapeDatabase.push_back( new Rectangle(size1,size2) );
        }
        else {
            std::cout << "Unrecognized shape!!\n";
        }
        //check if the user wants to add more shapes
        std::cout << "Do you want to add more shapes? (Enter Y or N)\n";
        std::string answer;
        std::cin >> answer;
        if (answer != std::string("Y"))
            break;
    }
    //iterate through the list and output the area, perimeter,
    //and number of corners of each entered shape
    std::list<Shape *>::iterator it = shapeDatabase.begin();
    int shapeCounter = 0;
    while (it != shapeDatabase.end()) {   
        std::cout << "Properties of shape " << shapeCounter++ << ":\n";
        std::cout << "Area: " << std::setprecision(5) << (*it)->CalculateArea() << "\n";
        std::cout << "Perimeter: " << std::setprecision(5) << (*it)->CalculatePerimeter() << "\n";
        std::cout << "Corners: " << (*it)->NumberCorners() << "\n";
        std::cout << std::endl;
        it++;
    }

    it = shapeDatabase.begin();
    while (it != shapeDatabase.end()) {
        delete (*it);
        it = shapeDatabase.erase(it);
    }
    
    return 0;
}