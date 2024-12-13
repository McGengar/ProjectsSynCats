#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>

using namespace std;

const int SCREEN_HEIGHT = 768;
const int SCREEN_WIDTH = 1024;

class DrawableObject{
public:
    const char* texture_path;
    int pos_x;
    int pos_y;
    sf::Texture texture;
    sf::Sprite sprite;
};

class Cat : public DrawableObject {
public:
    int number_of_states;
    int current_state;
    void OnUpdate();
};

class VarCat : public Cat{
public:
    const char* texture_path = "resources/varcat_2.bmp";
    VarCat() {
        pos_x = 0;
        pos_y = 0;
        texture.loadFromFile(texture_path);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(128, 128);
    }
    VarCat(int _pos_x, int _pos_y){
        pos_x = _pos_x;
        pos_y = _pos_y;
        texture.loadFromFile(texture_path);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(128, 128);
    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SynCats");

    sf::Clock clock;
    sf::Time time;
    float DeltaTime;

    sf::Texture var_texture;
    var_texture.loadFromFile("resources/varcat_2.bmp");
    sf::Sprite var_sprite;
    var_sprite.setTexture(var_texture);
    var_sprite.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    var_sprite.setOrigin(128, 128);
    
    VarCat cats[3] = { VarCat(100,100),VarCat(200,200),VarCat(300,300)};


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
                    break;
                }
            }
            
        }
        window.draw(var_sprite);

        for (int i = 0; i < 3;i++) {
            window.draw(cats[i].sprite);
        }
        
        window.display();
        window.clear();
    }
    
}
