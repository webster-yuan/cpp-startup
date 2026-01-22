//实现了对象创建和客户端代码的解耦
//根据传入的参数创建不同类型的图形对象。客户端代码通过调用 ShapeFactory::createShape() 方法来创建图形对象，
// 而不需要直接实例化 Circle 或 Rectangle 类。
//这样，在未来添加更多的图形类型时，只需要修改工厂类而不需要修改客户端代码，实现了对象创建和客户端代码的解耦。
#include<iostream>
using namespace std;
class Shape
{
public:
	virtual void draw() = 0;
};
class Circle : public Shape
{
public:
	void draw() override
	{
		cout << "draw a circle" << endl;
	}
};
class Rectangle:public Shape
{
public:
	void draw() override
	{
		cout << "draw a Rectangle" << endl;
	}
};
class ShapeFactory
{
public:
	static Shape* createShape(const std::string& shapeType)
	{
		if (shapeType == "Circle")
			return new Circle();
		else if (shapeType == "Rectangle")
			return new Rectangle();
		else
			return nullptr;
	}
};
int main()
{
	Shape* circle = ShapeFactory::createShape("Circle");
	circle->draw();
	Shape* rectangle = ShapeFactory::createShape("Rectangle");
	rectangle->draw();

	return 0;
}