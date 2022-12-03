#include "lib.hpp"
//#include "tFigures.h"

using namespace std;


int main() {
    srand(time(NULL));

    Point*** fig = new Point**[7];
    for (int i = 0; i < 7; i++) {
        fig[i] = new Point*[2];
    }
    fig[0][0] = new Point;
    fig[1][0] = new Line;
    fig[2][0] = new Circle;
    fig[3][0] = new Rectangle;
    fig[4][0] = new Triangle;
    fig[5][0] = new Ellipse;
    fig[6][0] = new Rhombus;
  

    fig[0][1] = new Point;
    fig[1][1] = new Line(40);
    fig[2][1] = new Circle(25);
    fig[3][1] = new Rectangle(80);
    fig[4][1] = new Triangle(25);
    fig[5][1] = new Ellipse(40);
    fig[6][1] = new Rhombus(50);

    sf::RenderWindow window(sf::VideoMode(500, 500), "First Window");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 2; j++) {
                (*fig[i][j]).rotateObject(5);
                (*fig[i][j]).moveObject();
                window.draw(*fig[i][j]->getDrawable());
            }
        }

        window.display();
    }
    return 0;
}