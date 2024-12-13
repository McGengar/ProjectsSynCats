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

class VarCat : Cat{
public:
    const char* texture_path = "resources/varcat_2.bmp";

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

    sf::Texture var_texture;
    var_texture.loadFromFile("resources/varcat_2.bmp");
    sf::Sprite var_sprite;
    var_sprite.setTexture(var_texture);
    var_sprite.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    var_sprite.setOrigin(128, 128);
    

    window.setKeyRepeatEnabled(false);

    while (window.isOpen())
    {
        sf::Event event;
        time = clock.getElapsedTime();
        DeltaTime = time.asSeconds();
        var_sprite.setScale(sin(DeltaTime*4)*0.1 + 1, sin(DeltaTime*4) * 0.1 + 1);
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
        window.draw(var_sprite);
        window.display();
        window.clear();
    }
    
}
