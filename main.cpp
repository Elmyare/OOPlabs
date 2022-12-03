#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf; using namespace std;

class IMovable
{
protected:
	bool right;
	float x, y;

	void move_() {
		if (right) {
			x += 2;
			if (x > 1280) {
				x -= 2;
				right = false;
			}
		}
		else {
			x -= 2;
			if (x < 0) {
				x += 2;
				right = true;
			}
		}
	}
};

class tPoint : public IMovable
{
public:
	tPoint() {
		const float radius = 3.0f;
		CircleShape point(radius);
		point.setFillColor(Color::Blue);
		point.setPosition(10, 20);
	}

	tPoint(int x, int y, Color color) {
		point.setRadius(3);
		point.setFillColor(color);
		point.setPosition(x, y);
		this->x = x;
		this->y = y;
	}

	CircleShape get_shape() {
		return point;
	}

	void move() {
		move_();
		point.setPosition(this->x, this->y);
	}

	Vector2f get_pos() {
		return point.getPosition();
	}

	void set_color(Color color) {
		point.setFillColor(color);
	}
	void set_pos(int x, int y) {
		point.setPosition(x, y);
	}

	void set_radius(int r) {
		point.setRadius(r);
	}
	float get_radius() {
		point.getRadius();
	}

private:
	CircleShape point;
};


class Line : public IMovable {
public:
	Line(int x = 50, int y = 50, Color color = Color::Red) {
		line = RectangleShape(Vector2f(100, 5));
		line.setOrigin(50, 2.5f);
		line.setFillColor(color);
		line.setPosition(x, y);
		this->x = x;
		this->y = y;
	}

	RectangleShape get_line() {
		return line;
	}

	void move() {
		move_();
		line.rotate(1);
		line.setPosition(this->x, this->y);
	}

	Vector2f get_pos() {
		return line.getPosition();
	}

	void set_color(Color color) {
		line.setFillColor(color);
	}

	void set_pos(Vector2f vec) {
		line.setPosition(vec);
	}

private:
	RectangleShape line;
};


class Circle : public IMovable
{
public:
	Circle() {
		circle = CircleShape(50, 3);
		circle.setOrigin(50, 50);
		circle.setFillColor(Color::Blue);
		circle.setPosition(10, 20);
	}

	Circle(int x, int y, Color color) {
		circle.setRadius(50);
		circle.setOrigin(50, 50);
		circle.setFillColor(color);
		circle.setPosition(x, y);
		this->x = x;
		this->y = y;
	}

	CircleShape get_shape() {
		return circle;
	}

	void move() {
		move_();
		circle.rotate(1);
		circle.setPosition(this->x, this->y);
	}
	Vector2f get_pos() {
		return circle.getPosition();
	}

	void set_color(Color color) {
		circle.setFillColor(color);
	}
	void set_pos(int x, int y) {
		circle.setPosition(x, y);
	}
private:
	CircleShape circle;
};


class Triangle : public IMovable
{

public:
	Triangle() {
		triangle = CircleShape(50, 3);
		triangle.setFillColor(Color::Blue);
		triangle.setPosition(600, 400);
		triangle.setOrigin(50, 50);
	}

	Triangle(int x, int y, Color color) {
		triangle.setRadius(50);
		triangle.setPointCount(3);
		triangle.setFillColor(color);
		triangle.setPosition(x, y);
		triangle.setOrigin(50, 50);
		this->x = x;
		this->y = y;
	}

	CircleShape get_shape() {
		return triangle;
	}

	void move() {
		move_();
		triangle.rotate(1);
		triangle.setPosition(this->x, this->y);
	}

	Vector2f get_pos() {
		return triangle.getPosition();
	}

	void set_color(Color color) {
		triangle.setFillColor(color);
	}
	void set_pos(int x, int y) {
		triangle.setPosition(x, y);
	}
private:
	CircleShape triangle;
};


class Rectangle : public IMovable {
public:
	Rectangle() {
		line = RectangleShape(Vector2f(100, 60));
		line.setFillColor(Color::Blue);
		line.setPosition(30, 50);
		line.setOrigin(50, 30);

	}


	Rectangle(int x, int y, Color color) {

		line = RectangleShape(Vector2f(100, 60));
		line.setFillColor(color);
		line.setPosition(x, y);
		line.setOrigin(50, 30);
		this->x = x;
		this->y = y;
	}

	RectangleShape get_line() {
		return line;
	}


	Vector2f get_pos() {
		return line.getPosition();
	}

	void move() {
		move_();
		line.rotate(1);
		line.setPosition(this->x, this->y);
	}

	void set_color(Color color) {
		line.setFillColor(color);
	}

	void set_pos(Vector2f vec) {
		line.setPosition(vec);
	}

private:
	RectangleShape line;
};


class Romb : public IMovable
{

public:
	Romb() {
		romb = CircleShape(50, 4);
		romb.setFillColor(Color::Blue);
		romb.setPosition(300, 400);
		romb.setOrigin(50, 50);

	}

	Romb(int x, int y, Color color) {
		romb.setRadius(50);
		romb.setPointCount(4);
		romb.setFillColor(color);
		romb.setPosition(x, y);
		romb.setOrigin(50, 50);
		this->x = x;
		this->y = y;
	}

	CircleShape get_shape() {
		return romb;
	}

	void move() {
		move_();
		romb.rotate(1);
		romb.setPosition(this->x, this->y);
	}

	Vector2f get_pos() {
		return romb.getPosition();
	}

	void set_color(Color color) {
		romb.setFillColor(color);
	}
	void set_pos(int x, int y) {
		romb.setPosition(x, y);
	}
private:
	CircleShape romb;
};


class Ellipse : public IMovable
{
public:

	Ellipse() {
		ellipse = CircleShape(25, 3);
		ellipse.setFillColor(Color::Blue);
		ellipse.setPosition(10, 20);
		ellipse.setOrigin(25, 25);

	}

	Ellipse(int x, int y, Color color) {
		ellipse.setRadius(25);
		ellipse.setFillColor(color);
		ellipse.setPosition(x, y);
		ellipse.scale(1.7f, 1.4f);
		ellipse.setOrigin(25, 25);
		this->x = x;
		this->y = y;
	}

	CircleShape get_shape() {
		return ellipse;
	}

	void move() {
		move_();
		ellipse.rotate(1);
		ellipse.setPosition(this->x, this->y);
	}

	Vector2f get_pos() {
		return ellipse.getPosition();
	}

	void set_color(Color color) {
		ellipse.setFillColor(color);
	}
	void set_pos(int x, int y) {
		ellipse.setPosition(x, y);
	}
private:
	CircleShape ellipse;


};


int main()
{
	ContextSettings settings;

	settings.antialiasingLevel = 8;


	RenderWindow window(VideoMode(1280, 720), ".", Style::Default, settings);
	window.setFramerateLimit(100);


	tPoint pt1(50, 50, Color::Blue);
	Line pt2(150, 150, Color::Red);
	Circle pt3(250, 250, Color::Green);
	Triangle pt4(350, 350, Color::Blue);
	Rectangle pt5(450, 450, Color::White);
	Romb pt6(550, 550, Color::Yellow);
	Ellipse pt7(650, 650, Color::Black);
	bool right = true;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

		pt1.move();
		pt2.move();
		pt3.move();
		pt4.move();
		pt5.move();
		pt6.move();
		pt7.move();




		window.clear(Color(40, 40, 40));
		window.draw(pt1.get_shape());
		window.draw(pt2.get_line());
		window.draw(pt3.get_shape());
		window.draw(pt4.get_shape());
		window.draw(pt5.get_line());
		window.draw(pt6.get_shape());
		window.draw(pt7.get_shape());



		window.display();


	}
}
