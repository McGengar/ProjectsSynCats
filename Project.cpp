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

class Selector : public DrawableObject {
public:
    int target = 0;
    Selector() {
        texture_path = "resources/selector.png";
        pos_x = 100;
        pos_y = 100;
        texture.loadFromFile(texture_path);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(128, 128);
    }
};

class Cat : public DrawableObject {
public:
    int number_of_states;
    int current_state;
    const char* texture_path_state_0;
    const char* texture_path_state_1;
    const char* texture_path_state_2;
    void OnUpdate();
};

class VarCat : public Cat{
public:
    VarCat() {
        number_of_states = 3;
        current_state = 0;
        texture_path_state_0 = "resources/varcat_0.png";
        texture_path_state_1 = "resources/varcat_1.png";
        texture_path_state_2 = "resources/varcat_2.png";
        pos_x = 0;
        pos_y = 0;
        texture.loadFromFile(texture_path_state_0);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(128, 128);
    }
    VarCat(int _pos_x, int _pos_y, int _state){
        number_of_states = 3;
        current_state = _state;
        texture_path_state_0 = "resources/varcat_0.png";
        texture_path_state_1 = "resources/varcat_1.png";
        texture_path_state_2 = "resources/varcat_2.png";
        pos_x = _pos_x;
        pos_y = _pos_y;
        switch (current_state) {
            case 0:
                texture_path = texture_path_state_0;
                break;
            case 1:
                texture_path = texture_path_state_1;
                break;
            case 2:
                texture_path = texture_path_state_2;
                break;
        }
        texture.loadFromFile(texture_path);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(128, 128);    
    }
    void OnUpdate() {
        if (current_state < number_of_states - 1) current_state++;
        else current_state = 0;
        switch (current_state) {
        case 0:
            texture_path = texture_path_state_0;
            break;
        case 1:
            texture_path = texture_path_state_1;
            break;
        case 2:
            texture_path = texture_path_state_2;
            break;
        }
        texture.loadFromFile(texture_path);
        sprite.setTexture(texture);

    }
};

class WhileCat : public Cat {
public:
    WhileCat() {
        number_of_states = 3;
        current_state = 0;
        texture_path_state_0 = "resources/whilecat_0.png";
        texture_path_state_1 = "resources/whilecat_1.png";
        texture_path_state_2 = "resources/whilecat_2.png";
        pos_x = 0;
        pos_y = 0;
        texture.loadFromFile(texture_path_state_0);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(128, 128);
    }
    WhileCat(int _pos_x, int _pos_y, int _state) {
        number_of_states = 3;
        current_state = _state;
        texture_path_state_0 = "resources/whilecat_0.png";
        texture_path_state_1 = "resources/whilecat_1.png";
        texture_path_state_2 = "resources/whilecat_2.png";
        pos_x = _pos_x;
        pos_y = _pos_y;
        switch (current_state) {
        case 0:
            texture_path = texture_path_state_0;
            break;
        case 1:
            texture_path = texture_path_state_1;
            break;
        case 2:
            texture_path = texture_path_state_2;
            break;
        }
        texture.loadFromFile(texture_path);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(128, 128);
    }
    void OnUpdate() {
        if (current_state < number_of_states - 1) current_state++;
        else current_state = 0;
        switch (current_state) {
        case 0:
            texture_path = texture_path_state_0;
            break;
        case 1:
            texture_path = texture_path_state_1;
            break;
        case 2:
            texture_path = texture_path_state_2;
            break;
        }
        texture.loadFromFile(texture_path);
        sprite.setTexture(texture);

    }
};

class BoolCat : public Cat {
public:
    BoolCat() {
        number_of_states = 2;
        current_state = 0;
        texture_path_state_0 = "resources/boolcat_0.png";
        texture_path_state_2 = "resources/boolcat_2.png";
        pos_x = 0;
        pos_y = 0;
        texture.loadFromFile(texture_path_state_0);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(128, 128);
    }
    BoolCat(int _pos_x, int _pos_y, int _state) {
        number_of_states = 3;
        current_state = _state;
        texture_path_state_0 = "resources/boolcat_0.png";
        texture_path_state_2 = "resources/boolcat_2.png";
        pos_x = _pos_x;
        pos_y = _pos_y;
        switch (current_state) {
        case 0:
            texture_path = texture_path_state_0;
            break;
        case 2:
            texture_path = texture_path_state_2;
            break;
        }
        texture.loadFromFile(texture_path);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(128, 128);
    }
    void OnUpdate() {
        if (current_state < number_of_states-1) current_state+=2;
        else current_state = 0;
        switch (current_state) {
        case 0:
            texture_path = texture_path_state_0;
            break;
        case 2:
            texture_path = texture_path_state_2;
            break;
        }
        texture.loadFromFile(texture_path);
        sprite.setTexture(texture);

    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SynCats");

    sf::Clock clock;
    sf::Time time;
    float DeltaTime;


    VarCat var_cats[] = { VarCat(300,150,0),VarCat(700,150,1)};
    WhileCat while_cats[] = { WhileCat(300,550,2) };
    BoolCat bool_cats[] = { BoolCat(700,550,0) };
    Selector selector;
    selector.sprite.setPosition(var_cats[0].sprite.getPosition());

    window.setKeyRepeatEnabled(false);

    while (window.isOpen())
    {
        sf::Event event;
        time = clock.getElapsedTime();
        DeltaTime = time.asSeconds();
        while (window.pollEvent(event))
        {

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Right:
                    if (selector.target < (sizeof(var_cats) / sizeof(var_cats[0]))-1) selector.target++;
                    break;
                case sf::Keyboard::Left:
                    if(selector.target>0) selector.target--;
                    break;
                case sf::Keyboard::Return:
                    var_cats[selector.target].OnUpdate();
                    system("cls");
                    for (int i = 0; i < sizeof(var_cats) / sizeof(var_cats[0]);i++)
                    {
                        window.draw(var_cats[i].sprite);
                        cout << var_cats[i].current_state;
                    }
                    for (int i = 0; i < sizeof(while_cats) / sizeof(while_cats[0]);i++)
                    {
                        while_cats[i].OnUpdate();
                        window.draw(while_cats[i].sprite);
                        cout << while_cats[i].current_state;
                    }
                    for (int i = 0; i < sizeof(bool_cats) / sizeof(bool_cats[0]);i++)
                    {
                        bool_cats[i].OnUpdate();
                        window.draw(bool_cats[i].sprite);
                        cout << bool_cats[i].current_state;
                    }
                    break;
                }

                selector.sprite.setPosition(var_cats[selector.target].sprite.getPosition());
            }

        }
        
        selector.sprite.setScale(sin(DeltaTime * 4) * 0.1 + 1, sin(DeltaTime * 4) * 0.1 + 1);
        for (int i = 0; i < sizeof(var_cats) / sizeof(var_cats[0]);i++)
        {
            window.draw(var_cats[i].sprite);
        }
        for (int i = 0; i < sizeof(while_cats) / sizeof(while_cats[0]);i++)
        {
            window.draw(while_cats[i].sprite);
        }
        for (int i = 0; i < sizeof(bool_cats) / sizeof(bool_cats[0]);i++)
        {
            window.draw(bool_cats[i].sprite);
        }

        window.draw(selector.sprite);

        window.display();
        window.clear();
    }
}
