#ifndef LIB_HPP_
#define LIB_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <list>

class Point {
protected:
    sf::Shape* figure;
    int dx;
    int dy;
    inline void basic_init() {
        dx = rand() % 5;
        dy = rand() % 5;
        figure->setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        int x = rand() % 500;
        int y = rand() % 500;
        figure->setPosition(x, y);
    };

public:
    Point() {
        figure = new sf::CircleShape(1);
        basic_init();
        figure->setOrigin(0.5, 0.5);
    };

    ~Point() { delete figure; };

    virtual void moveObject() {
        if (figure->getPosition().y <= 0 || figure->getPosition().y => 500) {
            dy *= -1;
        };
        if (figure->getPosition().x <= 0 || figure->getPosition().x => 500) {
            dx *= -1;
        };
        figure->setPosition(figure->getPosition().x + dx,
            figure->getPosition().y + dy);
    };

    void virtual rotateObject(float speed) { figure->rotate(speed); };

    sf::Drawable* getDrawable() { return figure; };
};

class Line : public Point {
private:

    int length = rand() % 50 + 15;

public:

    Line() {

        figure = new sf::RectangleShape(sf::Vector2f(1, length));
        basic_init();
        figure->setOrigin(0.5, length / 2);

    };

    Line(int lenght) {

        this->length = lenght;
        figure = new sf::RectangleShape(sf::Vector2f(1, length));
        basic_init();
        figure->setOrigin(0.5, length / 2);
  
    }

    void moveObject() {
        if (figure->getPosition().y < length / 2 || figure->getPosition().y > 500 - length / 2) {
            dy *= -1;
        };
        if (figure->getPosition().x < length / 2 || figure->getPosition().x > 500 - length / 2) {
            dx *= -1;
        };
        figure->setPosition(figure->getPosition().x + dx,
            figure->getPosition().y + dy);
    };

    void rotateObject(float speed) { figure->rotate(speed); };
};

class Circle : public Point {
private:
    int radius = rand() % 5 + 50;
public:

    Circle() {
        figure = new sf::CircleShape(radius);
        basic_init();
        figure->setOrigin(radius, radius);
    };

    Circle(int radius) {
        this->radius = radius;
        figure = new sf::CircleShape(radius);
        basic_init();
        figure->setOrigin(radius, radius);
    };

    void moveObject() {
        if (figure->getPosition().y < radius || figure->getPosition().y > 500 - radius) {
            dy *= -1;
        };
        if (figure->getPosition().x < radius || figure->getPosition().x > 500 - radius) {
            dx *= -1;
        };
        figure->setPosition(figure->getPosition().x + dx,
            figure->getPosition().y + dy);
    };

    void rotateObject(float speed) { figure->rotate(speed); };

    int getRadius() {
        return radius;
    }
};

class Rectangle : public Point {
private:

    int length = rand() % 100;
    int width = rand() % 100;

public:

    Rectangle() {

        figure = new sf::RectangleShape(sf::Vector2f(length, width));
        basic_init();
        figure->setOrigin(length / 2, width / 2);

    };

    Rectangle(int length, int width = 40) {

        this->length = length;
        this->width = width;
        figure = new sf::RectangleShape(sf::Vector2f(length, width));
        basic_init();
        figure->setOrigin(length / 2, width / 2);

    };

    void moveObject() {

        if (figure->getPosition().y < width / 2 || figure->getPosition().y > 500 - width / 2) {
            dy *= -1;
        };
        if (figure->getPosition().x < length / 2 || figure->getPosition().x > 500 - length / 2) {
            dx *= -1;
        };
        figure->setPosition(figure->getPosition().x + dx,
            figure->getPosition().y + dy);

    };

    void rotateObject(float speed) { figure->rotate(speed); };
};

class Triangle : public Point {
private:

    int length = rand() % 100;

public:

    Triangle() {

        figure = new sf::CircleShape(length, 3);
        basic_init();
        figure->setOrigin(length, length);

    };

    Triangle(int length) {

        this->length = length;
        figure = new sf::CircleShape(length, 3);
        basic_init();
        figure->setOrigin(length, length);

    };

    void moveObject() {

        if (figure->getPosition().y < length / 2 || figure->getPosition().y > 500 - length / 2) {
            dy *= -1;
        };
        if (figure->getPosition().x < length / 2 || figure->getPosition().x > 500 - length / 2) {
            dx *= -1;
        };
        figure->setPosition(figure->getPosition().x + dx,
            figure->getPosition().y + dy);

    };

    void rotateObject(float speed) { figure->rotate(speed); };
};

class Ellipse : public Circle {
private:

    int radius = getRadius();

public:

    Ellipse() {

        ((sf::CircleShape*)figure)->setRadius(radius);
        figure->setScale(2, 1);

    };

    Ellipse(int radius, int scale = 2) {

        this->radius = radius;
        ((sf::CircleShape*)figure)->setRadius(radius);
        figure->setScale(scale, 1);

    };

    void moveObject() {

        if (figure->getPosition().y < radius / 2 || figure->getPosition().y > 500 - radius / 2) {
            dy *= -1;
        };
        if (figure->getPosition().x < radius || figure->getPosition().x > 500 - radius) {
            dx *= -1;
        };
        figure->setPosition(figure->getPosition().x + dx,
            figure->getPosition().y + dy);

    };

    void rotateObject(float speed) { figure->rotate(speed); };
};

class Rhombus : public Point {
private:

    int a = rand() % 200 + 25;
    int b = rand() % 200 + 25;

public:

    Rhombus() {

        figure = new sf::ConvexShape();
        ((sf::ConvexShape*)figure)->setPointCount(4);
        figure->setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        sf::Vector2f centerPosition(rand() % 500, rand() % 500);

        ((sf::ConvexShape*)figure)
            ->setPoint(
                0, sf::Vector2f(centerPosition.x - (int)a / 2, centerPosition.y));
        ((sf::ConvexShape*)figure)
            ->setPoint(1, sf::Vector2f(centerPosition.x, centerPosition.y + b / 2));
        ((sf::ConvexShape*)figure)
            ->setPoint(
                2, sf::Vector2f(centerPosition.x + (int)a / 2, centerPosition.y));
        ((sf::ConvexShape*)figure)
            ->setPoint(
                3, sf::Vector2f(centerPosition.x, centerPosition.y - (int)b / 2));

        figure->setOrigin(centerPosition.x, centerPosition.y);
        figure->setPosition(centerPosition);
    };

    Rhombus(int a, int b = 100) {

        this->a = a;
        this->b = b;
        figure = new sf::ConvexShape();
        ((sf::ConvexShape*)figure)->setPointCount(4);
        figure->setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        sf::Vector2f centerPosition(rand() % 500, rand() % 500);

        ((sf::ConvexShape*)figure)
            ->setPoint(
                0, sf::Vector2f(centerPosition.x - (int)a / 2, centerPosition.y));
        ((sf::ConvexShape*)figure)
            ->setPoint(1, sf::Vector2f(centerPosition.x, centerPosition.y + b / 2));
        ((sf::ConvexShape*)figure)
            ->setPoint(
                2, sf::Vector2f(centerPosition.x + (int)a / 2, centerPosition.y));
        ((sf::ConvexShape*)figure)
            ->setPoint(
                3, sf::Vector2f(centerPosition.x, centerPosition.y - (int)b / 2));

        figure->setOrigin(centerPosition.x, centerPosition.y);
        figure->setPosition(centerPosition);
    };

    void moveObject() {

        if (figure->getPosition().y < b / 2 || figure->getPosition().y > 500 - b / 2) {
            dy *= -1;
        };
        if (figure->getPosition().x < b / 2 || figure->getPosition().x > 500 - b / 2) {
            dx *= -1;
        };
        figure->setPosition(figure->getPosition().x + dx,
            figure->getPosition().y + dy);

    };

    void rotateObject(float speed) { figure->rotate(speed); };
};

#endif  // LIB_HPP_