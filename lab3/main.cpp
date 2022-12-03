#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

using namespace std;
using namespace sf;

#define N 100

class tPoint {
public:
  tPoint() {
    shape = RectangleShape(Vector2f(3, 3));
    shape.setFillColor(Color::Black);
    shape.setPosition(Vector2f(rand() % 600, rand() % 600));
    direction = Vector2f(400, 0);
    direction.x = 0;
    direction.y = 0;
  }

  tPoint(int x, int y, Color color) {
    shape = RectangleShape(Vector2f(10, 1));
    shape.setFillColor(color);
    shape.setPosition(Vector2f(x, y));
    direction = Vector2f(400, 0);
    direction.x = 0;
    direction.y = 0;
  }

  RectangleShape get_shape() { return shape; }

  void move() { shape.move(direction.x, direction.y); }

  Vector2f get_pos() { return shape.getPosition(); }

  void set_color(Color color) { shape.setFillColor(color); }

  void set_pos(Vector2f vec) { shape.setPosition(vec); }

  Vector2f direction;

  void set_direction(double xdir, double ydir) {direction.x = xdir; direction.y = ydir;}

private:
  RectangleShape shape;
};

int main() {
  srand(time(nullptr));
  RenderWindow window(VideoMode(800, 600), "Lab work №3", Style::Default);
  window.setFramerateLimit(180);

  tPoint pt(400, 300, Color(140, 30, 230));
  tPoint arr[N];

  for (int i = 0; i < N; i++) {
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;
    arr[i].set_color(Color(r, g, b));
    arr[i].set_direction(rand()%7-3, rand()%7-3);
  }

  while (window.isOpen()) {
    Event ev;
    while (window.pollEvent(ev)) {
      if (ev.type == Event::Closed)
        window.close();
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape))
      window.close();

    window.clear(Color(0, 0, 0));

    for (int i = 0; i < N; i++) {
      if (arr[i].get_pos().x >= 800 || arr[i].get_pos().x <= 0) {
        arr[i].direction.x *= -1;
      }
      if (arr[i].get_pos().y >= 600 || arr[i].get_pos().y <= 0) {
        arr[i].direction.y *= -1;
      }

      arr[i].move();
      window.draw(arr[i].get_shape());
    }

    window.display();
  }
}