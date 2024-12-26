//LIBRARIES

#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>

using namespace std;

//SCREEN SIZE

const int SCREEN_HEIGHT = 768;
const int SCREEN_WIDTH = 1024;

//CLASSES

//Main class for all objects that are drawn on screen, all other classes derive from this class
class DrawableObject{
public:
    const char* texture_path;
    int pos_x;
    int pos_y;
    sf::Texture texture;
    sf::Sprite sprite;
};

//Classes for noninteractable objects
class Background : public DrawableObject {
public:
    Background() {
        texture_path = "resources/bg_tile.png";
        pos_x = 0;
        pos_y = 0;
        texture.loadFromFile(texture_path);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(0, 0);
    }
    Background(int _pos_x, int _pos_y) {
        texture_path = "resources/bg_tile.png";
        pos_x = _pos_x;
        pos_y = _pos_y;
        texture.loadFromFile(texture_path);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(0, 0);
    }
};

class Transiotion : public DrawableObject {
public:
    Transiotion() {
        texture_path = "resources/transition.png";
        pos_x = SCREEN_WIDTH/2;
        pos_y = SCREEN_HEIGHT/2;
        texture.loadFromFile(texture_path);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
};

//Class for selector, main tool for player to control, can target selectable objects
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
        sprite.setOrigin(128,128);
    }
};

//Parent class for all cat objects, main building blocks for levels, all "cat" classes derive from this class
class Cat : public DrawableObject {
public:
    int number_of_states;
    int current_state;
    const char* texture_path_state_0;
    const char* texture_path_state_1;
    const char* texture_path_state_2;
    void OnUpdate();
    
};

//Cat that changes when targetet by selector
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
        sprite.setOrigin(0,0);
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
        sprite.setOrigin(0,0);    
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

//Cat that automatically changes when any cat is updated, has 3 states
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
        sprite.setOrigin(0,0);
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
        sprite.setOrigin(0,0);
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

//Cat that automatically changes when any cat is updated, has 2 states
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
        sprite.setOrigin(0,0);
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
        sprite.setOrigin(0,0);
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

//Cat with constant state that cannot be modified
class ConstCat : public Cat {
public:
    ConstCat() {
        number_of_states = 3;
        current_state = 0;
        texture_path_state_0 = "resources/constcat_0.png";
        texture_path_state_1 = "resources/constcat_1.png";
        texture_path_state_2 = "resources/constcat_2.png";
        pos_x = 0;
        pos_y = 0;
        texture.loadFromFile(texture_path_state_0);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(0, 0);
    }
    ConstCat(int _pos_x, int _pos_y, int _state) {
        number_of_states = 3;
        current_state = _state;
        texture_path_state_0 = "resources/constcat_0.png";
        texture_path_state_1 = "resources/constcat_1.png";
        texture_path_state_2 = "resources/constcat_2.png";
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
        sprite.setOrigin(0, 0);
    }
};

//Main function of the game
int main()
{
    //Level Setup
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SynCats");
    sf::Clock clock;
    sf::Time time;
    sf::Clock clock_sin;
    sf::Time time_sin;
    float DeltaTime;
    float sin_time;
    int transition_state = -1;
    int level = 1;
    
    //Arrays for drawable objects in level
    Background background[] = {Background(0,0),Background(256,0),Background(512,0),Background(768,0),Background(0,256),Background(256,256),Background(512,256),Background(768,256),Background(0,512),Background(256,512),Background(512,512),Background(768,512) };
    VarCat var_cats[10] = { VarCat(128,128,0),VarCat(384,128,1),VarCat(640,128,2) };
    WhileCat while_cats[10] = { WhileCat(256,384,0) };
    BoolCat bool_cats[10] = { BoolCat(512,384,2) };
    Selector selector;
    Transiotion transition;

    VarCat var_cats2[10] = { VarCat(256,128,0),VarCat(512,128,2) };
    WhileCat while_cats2[10] = { WhileCat(384,384,1) };
    BoolCat bool_cats2[10] = {};

    selector.sprite.setPosition(var_cats[0].sprite.getPosition().x + 128, var_cats[0].sprite.getPosition().y + 128);
    window.setKeyRepeatEnabled(false);

    //GAME LOOP
    while (window.isOpen())
    {
        sf::Event event;
        time = clock.getElapsedTime();
        DeltaTime = time.asSeconds();
        time_sin = clock_sin.getElapsedTime();
        sin_time = time_sin.asSeconds();
        while (window.pollEvent(event))
        {

            //Handling Events

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            //Handling Inputs
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Right:
                    if (var_cats[selector.target + 1].pos_x != NULL) selector.target++;
                    break;
                case sf::Keyboard::Left:
                    if(selector.target>0) selector.target--;
                    break;
                //Updating targeted object with selector
                case sf::Keyboard::Return:
                    var_cats[selector.target].OnUpdate();
                    int state = var_cats[0].current_state;
                    bool winning_flag = true;
                    system("cls");
                    for (int i = 0; var_cats[i].pos_x!= NULL ;i++)
                    {
                        if (var_cats[i].current_state != state) winning_flag = false;
                        window.draw(var_cats[i].sprite);
                        cout << var_cats[i].current_state;
                    }
                    for (int i = 0; while_cats[i].pos_x != NULL;i++)
                    {
                        while_cats[i].OnUpdate();
                        if (while_cats[i].current_state != state) winning_flag = false;
                        window.draw(while_cats[i].sprite);
                        cout << while_cats[i].current_state;
                    }
                    for (int i = 0; bool_cats[i].pos_x != NULL;i++)
                    {
                        bool_cats[i].OnUpdate();
                        if (bool_cats[i].current_state != state) winning_flag = false;
                        window.draw(bool_cats[i].sprite);
                        cout << bool_cats[i].current_state;
                        cout <<endl<< DeltaTime;
                    }
                    //Win condition, when all cats share state
                    if (winning_flag) {
                        transition_state = 1;
                    }
                    break;
                }
                //Moving Selector
                selector.sprite.setPosition(var_cats[selector.target].sprite.getPosition().x+128, var_cats[selector.target].sprite.getPosition().y+128);
            }

        }
        //Drawing all objects, starting from background to front
        for (int i = 0; i < sizeof(background) / sizeof(background[0]);i++)
        {
            window.draw(background[i].sprite);
        }

        for (int i = 0; var_cats[i].pos_x != NULL;i++)
        {
            window.draw(var_cats[i].sprite);
        }
        for (int i = 0; while_cats[i].pos_x != NULL;i++)
        {
            window.draw(while_cats[i].sprite);
        }
        for (int i = 0; bool_cats[i].pos_x != NULL;i++)
        {
            window.draw(bool_cats[i].sprite);
        }
        selector.sprite.setScale(sin(sin_time * 4) * 0.1 + 1, sin(sin_time * 4) * 0.1 + 1);
        window.draw(selector.sprite);

        //Level transition
        switch (transition_state)
        {
        case 1:
            transition.sprite.setScale(transition.sprite.getScale().x - 25 * DeltaTime, transition.sprite.getScale().y - 25 * DeltaTime);
            if (transition.sprite.getScale().x <= 1.5) 
            {
                transition_state = -1;
                level++;
                switch (level)
                {
                case 2:
                    for (int i = 0; i<10;i++)
                    {
                        var_cats[i] = var_cats2[i];
                    }
                    for (int i = 0; i < 10;i++)
                    {
                        while_cats[i] = while_cats2[i];
                    }
                    for (int i = 0; i < 10;i++)
                    {
                        bool_cats[i] = bool_cats2[i];
                    }
                    break;
                default:
                    break;
                }
                

                selector.target = 0;
                selector.sprite.setPosition(var_cats[selector.target].sprite.getPosition().x - 1208, var_cats[selector.target].sprite.getPosition().y - 1208);

            }
            break;
        case -1:
            transition.sprite.setScale(transition.sprite.getScale().x + 25* DeltaTime, transition.sprite.getScale().y + 25 * DeltaTime);
            if (transition.sprite.getScale().x >= 40) transition_state = 0;
            break;
        default:
            break;
        }
        
        window.draw(transition.sprite);

        //Rendering
        clock.restart();
        window.display();
        window.clear();
    }
}
