#include <SFML/Graphics.hpp>;
#include <iostream>;
#include <stdio.h>;
#include <cstdlib>;
#include <ctime>;
#include <cmath>;
#include "tFigures.h";

using namespace sf;
using namespace std;

int main()
{
    srand(time(0));
    int WinHeight = 600, WinWide = 800;
    const int figures_amount = 5;
    RenderWindow window(VideoMode(WinWide, WinHeight), "Figures");

    tFigure *figures[7][figures_amount];
    for (int i = 0; i < figures_amount; i++) {
        figures[0][i] = new tPoint(10);
        figures[1][i] = new tLineSegment(250, 123, 234, 111);
        figures[2][i] = new tReactangle();
        figures[3][i] = new tTriangle();
        figures[4][i] = new tRhombus();
        figures[5][i] = new tEllips();
        figures[6][i] = new tRing();
    }

    float DELTA_TIME = 0.75f / 60.0f;
    window.setFramerateLimit(1.0f / DELTA_TIME);
    for (int i = 0; i < figures_amount; i++) {
        figures[0][i]->init_spawn_coords(WinWide, WinHeight);
        figures[1][i]->init_spawn_coords(WinWide, WinHeight);
        figures[2][i]->init_spawn_coords(WinWide, WinHeight);
        figures[3][i]->init_spawn_coords(WinWide, WinHeight);
        figures[4][i]->init_spawn_coords(WinWide, WinHeight);
        figures[5][i]->init_spawn_coords(WinWide, WinHeight);
        figures[6][i]->init_spawn_coords(WinWide, WinHeight);
    }

    int movement_type = 0;

    while (window.isOpen()) {

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == 26) { // Press '0' on keyboard
                    movement_type = 0;
                }
                else if (event.key.code == 27) {
                    movement_type = 1;
                }
                else {
                    window.close();
                }
            }
        }

        window.clear(Color::Black);
           for (int i = 0; i < figures_amount; i++) {
            figures[0][i]->Move(movement_type);
            figures[0][i]->Draw(window);

            figures[1][i]->Move(movement_type);
            figures[1][i]->Draw(window);

            figures[2][i]->Move(movement_type);
            figures[2][i]->Draw(window);

            figures[3][i]->Move(movement_type);
            figures[3][i]->Draw(window);

            figures[4][i]->Move(movement_type);
            figures[4][i]->Draw(window);

            figures[5][i]->Move(movement_type);
            figures[5][i]->Draw(window);

            figures[6][i]->Move(movement_type);
            figures[6][i]->Draw(window);
        }
        window.display();
    }
}


