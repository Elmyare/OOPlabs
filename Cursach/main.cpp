#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

#define N 5
using namespace std;
using namespace sf;

bool is_in(int x, int b1, int b2);

class Square {
    protected:
        RectangleShape shape;

    public:
    Square() {
        shape = RectangleShape(Vector2f(50.0f, 50.0f));
        shape.setPosition(Vector2f(0, 0));
        shape.setFillColor(Color(50, 50, 50));
    }
    Square(int x, int y, int height = 50, int width = 100, Color color = Color(100, 100, 100)) {
        shape = RectangleShape(Vector2f(width, height));
        shape.setPosition(Vector2f(x, y));
        shape.setFillColor(color);
    }

    void set_position(int x, int y) {
        shape.setPosition(Vector2f(x, y));
    }

    void set_color(Color color) { shape.setFillColor(color); }

    RectangleShape get_shape() { return shape; }
};

class Cell: public Square {
    public:

        Cell() : Square() {
            mine = ' ';
            showed = false;
            amount = 0;
        }

        Cell(int x, int y, int size, Color color, Font &font): Square(x, y, size, size, color), color{color} {
            mine = ' ';
            showed = false;
            amount = 0;
            texton.setFillColor(color);
            texton.setCharacterSize(size);
            texton.setFont(font);
            texton.setPosition(Vector2f(x+size/4, y-size/10));
            texton.setFillColor(color);
            texton.setString(" ");
        }

        void set_mine() {
            mine = '*';
        }

        bool is_mine() {
            bool result = false;
            if (mine == '*') result = true;
            return result;
        }

        void set_amount(int amounts) {
            amount = amounts;
            string s = to_string(amount);
            texton.setString(s);
        }

        int get_amount() {
            return amount;
        }

        void show() {
            showed = true;
            if (mine == '*') {
                shape.setFillColor(Color(45, 5, 5));
                texton.setString("*");
            } else {
                shape.setFillColor(Color(5, 5, 45));
            }
        }

        bool is_show() {
            return showed;
        }

        void write_amount(RenderWindow &window) { //
            window.draw(texton);
        }
    private:
        Text texton;
        char mine;
        bool showed;
        int amount;
        Color color;
};

void field_generate(Cell ****field, int height, int width, Font &farial);
void mines_spawn(Cell ****field, int x, int y, int height, int width, int *all_mines);
void mines_recursion(Cell ****field, int x, int y, int height, int width, int direction);

class Textbox {
    public:

        Textbox() { }

        Textbox(int size, Color color, bool sel) {
            textbox.setCharacterSize(size);
            textbox.setFillColor(color);
            isSelected = sel;
            if (sel) {
                textbox.setString("_");
            } else {
                textbox.setString("");
            }
        }
    
        void setFont(Font &font) {
            textbox.setFont(font);
        }

        void setPosition(Vector2f pos) {
            textbox.setPosition(pos);
        }

        void setLimit(bool toF, int lim) {
            hasLimit = toF;
            limit = lim;
        }

        void setSelected(bool sel) {
            isSelected = sel;
            if (!sel) {
                string t = text.str();
                string newT = "";
                for (long unsigned int i = 0; i < t.length(); i++) {
                    newT += t[i];
                }
                textbox.setString(newT);
            } else {
                textbox.setString(text.str()+"_");
            }
        }

        Text getTextbox() {
            return textbox;
        }
        string getText() {
            return text.str();
        }

        void drawTo(RenderWindow &window) {
            window.draw(textbox);
        }

        void typedOn(Event input) {
            if(isSelected) {
                int charTyped = input.text.unicode;
                if (charTyped < 128) {
                    if (hasLimit) {
                        if(text.str().length() <= limit) {
                            inputLogic(charTyped);
                        } else if (text.str().length() > limit && charTyped == DELETE_KEY) {
                            deleteLastChar();
                        }
                    } else {
                        inputLogic(charTyped);
                    }
                }
            }
        }
    private:

        Text textbox;
        ostringstream text;
        bool isSelected = false;
        bool hasLimit = false;
        long unsigned int limit;
    
    void inputLogic(int charTyped) {
        if(charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
            text << static_cast<char>(charTyped);
        } else if (charTyped == DELETE_KEY) {
            if (text.str().length() > 0) {
                deleteLastChar();
            }
        }
        textbox.setString(text.str()+"_");
    }

    void deleteLastChar() {
        string t = text.str();
        string newT = "";
        for (long unsigned int i = 0; i < t.length() - 1; i++) {
            newT += t[i];
        }
        text.str("");
        text << newT;

        textbox.setString(text.str());
    }
};

int main() {

    srand(time(nullptr));
    RenderWindow window(VideoMode(800, 600), "Lab work №3", Style::Default);
    window.setFramerateLimit(180);
    window.setKeyRepeatEnabled(true);
    Vector2i mousePoz;
    bool init = true;
    bool first_click = true;
    Font arial;
    arial.loadFromFile("arial.ttf");
    Textbox textbox1(30, Color::Black, true);
    Textbox textbox2(30, Color::Black, false);

    Text start("Enter height and width (from 5 to 15)", arial);
    start.setFillColor(Color::Black);
    start.setCharacterSize(40);
    start.setPosition({50, 0});

    Text gameover("Game over", arial);
    gameover.setFillColor(Color::Black);
    gameover.setCharacterSize(40);
    gameover.setPosition({50, 0});

    Text winn("You win!", arial);
    winn.setFillColor(Color::Black);
    winn.setCharacterSize(40);
    winn.setPosition({50, 0});

    textbox1.setFont(arial);
    textbox1.setPosition({50, 80});
    textbox2.setFont(arial);
    textbox2.setPosition({50, 150});

    Square border1(50, 80, 40, 200, Color(120, 120, 120));
    Square border2(50, 150, 40, 200, Color(120, 120, 120));
    Square startButton(50, 220, 40, 90, Color(120, 120, 120));
    Text onstartbutton("Start", arial);
    onstartbutton.setFillColor(Color::Black);
    onstartbutton.setCharacterSize(30);
    onstartbutton.setPosition({60, 220});

    Cell ***cells;
    int size_y = 0;
    int size_x = 0;
    int all_mines = 1;
    int all_showed = 0;
    bool is_game_over = false;
    while (window.isOpen()) {
        mousePoz = Mouse::getPosition(window);
        Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::TextEntered:
                    textbox1.typedOn(event);
                    textbox2.typedOn(event);
                    break;
                default:
                    break;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (border1.get_shape().getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                textbox1.setSelected(true);
            } else {
                textbox1.setSelected(false);
            }
            if (border2.get_shape().getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                textbox2.setSelected(true);
            } else {
                textbox2.setSelected(false);
            }
            all_showed = 0;
            if (startButton.get_shape().getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                if(sscanf(textbox1.getText().c_str(), "%d", &size_y) == 1 && sscanf(textbox2.getText().c_str(), "%d", &size_x) == 1) {
                    init = false; //text1 - y, text2 - x
                    field_generate(&cells, size_y, size_x, arial);
                }
            } else if (!init) for (int i = 0; i < size_y; i++)
                for (int j = 0; j < size_x; j++) {
                    if (cells[i][j]->is_show()) all_showed++;
                    if (cells[i][j]->get_shape().getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                        cells[i][j]->show();
                        if (first_click) {
                            first_click = false;
                            //cout << j << i << size_y << size_x;
                            mines_spawn(&cells, j, i, size_y, size_x, &all_mines);
                        }
                        if (cells[i][j]->get_amount() == 0) mines_recursion(&cells, j, i, size_y, size_x, 0);
                        if (cells[i][j]->is_mine()) is_game_over = true;
                    }
                }
        }
        window.clear(Color(255, 255, 255));
        if (is_game_over) {
            window.draw(gameover);
        } else if (size_x*size_y-all_showed == all_mines) {
            window.draw(winn);
        } else if (init) {
            window.draw(start);
            window.draw(startButton.get_shape());
            window.draw(onstartbutton);
            window.draw(border1.get_shape());
            window.draw(border2.get_shape());
            textbox1.drawTo(window);
            textbox2.drawTo(window);
            window.draw(start);
        } else {
            for (int i = 0; i < size_y; i++)
                for (int j = 0; j < size_x; j++) {
                    window.draw(cells[i][j]->get_shape());
                    //usleep(1000);
                    cells[i][j]->write_amount(window); //window
                }
        }
        

        
        window.display();
    }
    return 0;
}

// void reset_game(Cell cells**) {

// }

void mines_spawn(Cell ****field, int x, int y, int height, int width, int *all_mines) {
    (*all_mines) = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (rand()%4 == 0 && (x != j && y != i)) {
                (*field)[i][j]->set_mine();
                (*all_mines)++;
            }
        }
    }
    int am;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            am = 0;
            for (int dy = -1; dy <= 1; dy++)
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx == 0 && dy == 0) continue;
                    if (is_in(i+dy, 0, height) && is_in(j+dx, 0, width) && (*field)[i+dy][j+dx]->is_mine()) am++;
                }
            (*field)[i][j]->set_amount(am);
        }
    }
}

void mines_recursion(Cell ****field, int x, int y, int height, int width, int direction) { // 0-all  1-not up  2-not down  3-not left  4-not right
        if (is_in(x, 0, width) && is_in(y-1, 0, height) && direction != 1)
            if (!((*field)[y-1][x]->is_mine()) && !((*field)[y-1][x]->is_show())) {
                (*field)[y-1][x]->show();
                if ((*field)[y-1][x]->get_amount() == 0) {
                    mines_recursion(field, x, y-1, height, width, 2);
                }
            }
        if (is_in(x, 0, width) && is_in(y+1, 0, height) && direction != 2)
            if (!((*field)[y+1][x]->is_mine()) && !((*field)[y+1][x]->is_show())) {
                (*field)[y+1][x]->show();
                if ((*field)[y+1][x]->get_amount() == 0) {
                    mines_recursion(field, x, y+1, height, width, 1);
                }
            }
        if (is_in(x-1, 0, width) && is_in(y, 0, height) && direction != 3)
            if (!((*field)[y][x-1]->is_mine()) && !((*field)[y][x-1]->is_show())) {
                (*field)[y][x-1]->show();
                if ((*field)[y][x-1]->get_amount() == 0) {
                    mines_recursion(field, x-1, y, height, width, 4);
                }
            }
        if (is_in(x+1, 0, width) && is_in(y, 0, height) && direction != 4)
            if (!((*field)[y][x+1]->is_mine()) && !((*field)[y][x+1]->is_show())) {
                (*field)[y][x+1]->show();
                if ((*field)[y][x+1]->get_amount() == 0) {
                    mines_recursion(field, x+1, y, height, width, 3);
                }
            }
}

void field_generate(Cell ****field, int height, int width, Font &farial) {
    int min_of_sizes = (800/(width+5) < 600/(height+5)) ? 800/(width+5) : 600/(height+5);
    int x_space = 0;
    int y_space = 0;

    (*field) = new Cell**[height];
    for (int i = 0; i < height; i++) (*field)[i] = new Cell*[width];

    if (800/(width+5) < 600/(height+5)) {
        min_of_sizes = 800/(width+5);
    } else {
        min_of_sizes = 600/(height+5);
    }
    y_space = (600-((min_of_sizes+5)*height-5))/2;
    x_space = (800-((min_of_sizes+5)*width-5))/2;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            (*field)[i][j] = new Cell(x_space+j*(min_of_sizes+5)+5, y_space+i*(min_of_sizes+5)+5, min_of_sizes, Color(120, 120, 120), farial);
            //field[i][j]->set_position(x_space+i*(min_of_sizes+5)+5, y_space+j*(min_of_sizes+5)+5); //800 600
            //field[i][j]->
        }
    }
}

bool is_in(int x, int b1, int b2) {
    bool result = false;
    if (b1 <= x && x < b2) result = true;
    return result;
}