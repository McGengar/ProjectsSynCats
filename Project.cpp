#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>

using namespace std;

const int SCREEN_HEIGHT = 768;
const int SCREEN_WIDTH = 1024;

class DrawableObject {
public:
    void Draw();
    const char* texture_path;
};

class Cat : DrawableObject {
public:
    int number_of_states;
    int current_state;
    void OnUpdate();
};

class VarCat : Cat {
public:
    const char* texture_path = "resources/varcat_2";
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SynCats");
    string message = "Hello World";
    string display = "";
    int index = 0;
    //std::cout << "Hello World!\n";

    sf::Clock clock;
    sf::Time time;
    float DeltaTime;

    window.setKeyRepeatEnabled(false);

    while (window.isOpen())
    {
        sf::Event event;
        time = clock.getElapsedTime();
        DeltaTime = time.asSeconds();
        while(window.pollEvent(event)) 
        {

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Return:
                    display += message[index];
                    index++;
                    system("cls");
                    cout << display;
                    break;
                }
            }
            
        }
        clock.restart();

        window.display();
    }
    
}
