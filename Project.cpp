﻿//Made by Marcin Węgrzyn

//SynCat is a logical puzzle game about synchronizing cats.
//The game consists of many levels, each containg sets of cats, 
//and each cat is an object with 2 or 3 states
//You can tell the state of the cat from how many eyes of theirs are open
//There are many cats with different quirks, each specific to that one cat. 
//For the most part, you can only impact one cat at the time, 
//but others will follow, so you have to be careful becouse changing state of one cat
//can drastically change state of all cats.

//LIBRARIES
//SynCats uses iostream for console debugging, and SFML as general media library
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

using namespace std;

//SCREEN SIZE

const int SCREEN_HEIGHT = 768;
const int SCREEN_WIDTH = 1024;

//CLASSES

//Main class for all objects that are drawn on screen, all other classes derive from this class
//Each drawable object posses texture, which is later drawn as a sprite, and also position coordinats
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

class Transition : public DrawableObject {
public:
    Transition() {
        texture_path = "resources/transition.png";
        pos_x = SCREEN_WIDTH/2;
        pos_y = SCREEN_HEIGHT/2;
        texture.loadFromFile(texture_path);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
};

class Title : public DrawableObject {
public:
    Title() {
        texture_path = "resources/title_screen.png";
        pos_x = SCREEN_WIDTH / 2;
        pos_y = SCREEN_HEIGHT / 2;
        texture.loadFromFile(texture_path);
        sprite.setTexture(texture);
        sprite.setPosition(pos_x, pos_y);
        sprite.setOrigin(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
};

class Start : public DrawableObject {
public:
    Start() {
        texture_path = "resources/start.png";
        pos_x = SCREEN_WIDTH / 2;
        pos_y = SCREEN_HEIGHT / 2;
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
//All cats have states, each with different texture and OnUpdate function, that describes what happens when that cat is updated
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
    //Level Setup, initializing window, clock/time objects to control animations, and other variables needed for levels
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SynCats");
    sf::Clock clock;
    sf::Time time;
    sf::Clock clock_sin;
    sf::Time time_sin;
    float DeltaTime;
    float sin_time;
    int transition_state = -1;
    int level = 0;

    //Setup for all sounds used in the game
    sf::SoundBuffer theme_buffer;
    sf::Sound theme;
    sf::SoundBuffer meow_buffer;
    sf::Sound meow;
    sf::SoundBuffer selector_buffer;
    sf::Sound selector_sound;

    theme_buffer.loadFromFile("resources/syncats_theme.wav");
    theme.setBuffer(theme_buffer);
    theme.setLoop(true);
    theme.setVolume(2);
    theme.play();

    meow_buffer.loadFromFile("resources/moew_sound_effect.wav");
    meow.setBuffer(meow_buffer);
    meow.setLoop(false);
    meow.setVolume(10);

    selector_buffer.loadFromFile("resources/selector_sound_effect.wav");
    selector_sound.setBuffer(selector_buffer);
    selector_sound.setLoop(false);
    selector_sound.setVolume(10);
    
    
    
    //Arrays for drawable objects in level, each level can be described as set of these arrays
    Background background[] = {Background(0,0),Background(256,0),Background(512,0),Background(768,0),Background(0,256),Background(256,256),Background(512,256),Background(768,256),Background(0,512),Background(256,512),Background(512,512),Background(768,512) };
    VarCat var_cats[10] = {};
    WhileCat while_cats[10] = {};
    BoolCat bool_cats[10] = {};
    ConstCat const_cats[10] = {};
    Selector selector;
    Transition transition;
    Title title;
    Start start;

    //All Levels described as arrays

    VarCat var_cats1[10] = {VarCat(256,256,0),VarCat(512,256,2)};
    WhileCat while_cats1[10] = {};
    BoolCat bool_cats1[10] = {};
    ConstCat const_cats1[10] = {};

    VarCat var_cats2[10] = { VarCat(256,128,0),VarCat(512,128,2) };
    WhileCat while_cats2[10] = {};
    BoolCat bool_cats2[10] = {};
    ConstCat const_cats2[10] = {ConstCat(384,384,1)};

    VarCat var_cats3[10] = { VarCat(256,128,0),VarCat(512,128,2) };
    WhileCat while_cats3[10] = {WhileCat(384,384,1) };
    BoolCat bool_cats3[10] = {};
    ConstCat const_cats3[10] = {};

    VarCat var_cats4[10] = { VarCat(384,128,2) };
    WhileCat while_cats4[10] = {  };
    BoolCat bool_cats4[10] = {BoolCat(384,384,0) };
    ConstCat const_cats4[10] = {  };

    VarCat var_cats5[10] = { VarCat(256,128,0),VarCat(512,128,2) };
    WhileCat while_cats5[10] = { WhileCat(256,384,1) };
    BoolCat bool_cats5[10] = {  };
    ConstCat const_cats5[10] = { ConstCat(512,384,1) };

    VarCat var_cats6[10] = { VarCat(128,128,0),VarCat(384,128,1),VarCat(640,128,2) };
    WhileCat while_cats6[10] = { WhileCat(256,384,0) };
    BoolCat bool_cats6[10] = { BoolCat(512,384,2) };
    ConstCat const_cats6[10] = {};

    VarCat var_cats7[10] = {  };
    WhileCat while_cats7[10] = {};
    BoolCat bool_cats7[10] = {  };
    ConstCat const_cats7[10] = {  };


    //Selectors position is set outsude of window at first, so it isnt visible in the title screen
    selector.sprite.setPosition(-128, -128);
    //This makes so you cannot hold a key to move to next object, you have to click each time
    window.setKeyRepeatEnabled(false);

    //GAME LOOP
    //A game loop is a loop that from now on controls our game, each loop is one frame rendered
    //All things that happen constantly, or in response to input must be contained here
    while (window.isOpen())
    {
        //Initializing Event object that will operate all events that happen, but mostly input events
        sf::Event event;

        //DeltaTime is a concept that describes how much time has passed since last frame
        //We use it for animations and elements that we want to happen in certain time in real life
        //For example, if we want object to move 100units to the right in 1 second, we need to
        //add to this objects position 100 units multipled by DeltaTime, so it will take exactly 1 second
        time = clock.getElapsedTime();
        DeltaTime = time.asSeconds();
        //sin_time is for situations simlar to DeltaTime, however this time doesnt reset at the end of loop
        //so it can be used for continous situations, like sin function, hence the name
        time_sin = clock_sin.getElapsedTime();
        sin_time = time_sin.asSeconds();
        //Loop that pools all events, but like mention earlier, mustly input events
        while (window.pollEvent(event))
        {
            //Handling Events
            switch (event.type)
            {
            //Closing window when X button is pressed
            case sf::Event::Closed:
                window.close();
                break;
            //Handling Inputs
            //Here we handle all key presses, like moving slector with keys and updating cats
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Right:
                    if (var_cats[selector.target + 1].pos_x != NULL) selector.target++;
                    selector.sprite.setPosition(var_cats[selector.target].sprite.getPosition().x + 128, var_cats[selector.target].sprite.getPosition().y + 128);
                    break;
                case sf::Keyboard::Left:
                    if(selector.target>0) selector.target--;
                    selector.sprite.setPosition(var_cats[selector.target].sprite.getPosition().x + 128, var_cats[selector.target].sprite.getPosition().y + 128);
                    break;
                //Updating targeted object with selector
                case sf::Keyboard::Return:
                    if (transition_state == 0) {
                        
                        var_cats[selector.target].OnUpdate();
                        int state = var_cats[0].current_state;
                        bool winning_flag = true;
                        system("cls");
                        for (int i = 0; var_cats[i].pos_x != NULL;i++)
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
                        }
                        for (int i = 0; const_cats[i].pos_x != NULL;i++)
                        {
                            if (const_cats[i].current_state != state) winning_flag = false;
                            window.draw(const_cats[i].sprite);
                            cout << const_cats[i].current_state;
                        }
                        //Win condition, when all cats share state
                        if (winning_flag) {
                            transition_state = 1;
                            meow.play();
                        }
                        else {
                            selector_sound.play();
                        }
                        break;
                    }
                }
                
            }

        }
        
        //Level transition
        //Here is handled both animation of level transition, as well as loading next level
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
                case 1:
                    for (int i = 0; i < 10;i++)
                    {
                        var_cats[i] = var_cats1[i];
                        while_cats[i] = while_cats1[i];
                        bool_cats[i] = bool_cats1[i];
                        const_cats[i] = const_cats1[i];
                    }
                    break;
                case 2:
                    for (int i = 0; i<10;i++)
                    {
                        var_cats[i] = var_cats2[i];
                        while_cats[i] = while_cats2[i];
                        bool_cats[i] = bool_cats2[i];
                        const_cats[i] = const_cats2[i];
                    }
                    break;
                case 3:
                    for (int i = 0; i < 10;i++)
                    {
                        var_cats[i] = var_cats3[i];
                        while_cats[i] = while_cats3[i];
                        bool_cats[i] = bool_cats3[i];
                        const_cats[i] = const_cats3[i];
                    }
                    break;
                case 4:
                    for (int i = 0; i < 10;i++)
                    {
                        var_cats[i] = var_cats4[i];
                        while_cats[i] = while_cats4[i];
                        bool_cats[i] = bool_cats4[i];
                        const_cats[i] = const_cats4[i];
                    }
                    break;
                case 5:
                    for (int i = 0; i < 10;i++)
                    {
                        var_cats[i] = var_cats5[i];
                        while_cats[i] = while_cats5[i];
                        bool_cats[i] = bool_cats5[i];
                        const_cats[i] = const_cats5[i];
                    }
                    break;
                case 6:
                    for (int i = 0; i < 10;i++)
                    {
                        var_cats[i] = var_cats6[i];
                        while_cats[i] = while_cats6[i];
                        bool_cats[i] = bool_cats6[i];
                        const_cats[i] = const_cats6[i];
                    }
                    break;
                case 7:
                    //After level 6, game goes back to the menu
                    for (int i = 0; i < 10;i++)
                    {
                        var_cats[i] = var_cats7[i];
                        while_cats[i] = while_cats7[i];
                        bool_cats[i] = bool_cats7[i];
                        const_cats[i] = const_cats7[i];
                    }
                    
                    selector.sprite.setPosition(-128, -128);
                    level = 0;

                    break;
                default:
                    break;
                }
                
                //Each time selector returns to first VarCat, only selectable cat
                
                selector.target = 0;
                if (level > 0)selector.sprite.setPosition(var_cats[selector.target].sprite.getPosition().x + 128, var_cats[selector.target].sprite.getPosition().y + 128);

            }
            break;
        case -1:
            transition.sprite.setScale(transition.sprite.getScale().x + 25* DeltaTime, transition.sprite.getScale().y + 25 * DeltaTime);
            if (transition.sprite.getScale().x >= 40) transition_state = 0;
            break;
        default:
            break;
        }

        //Drawing all objects, starting from background to front
        for (int i = 0; i < sizeof(background) / sizeof(background[0]);i++)
        {
            window.draw(background[i].sprite);
        }
        //Drawing title and start message only at the start of the game
        if (level == 0) {
            start.sprite.setScale(sin(sin_time * 4) * 0.05 + 1, sin(sin_time * 4) * 0.05 + 1);
            window.draw(title.sprite);
            window.draw(start.sprite);
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
        for (int i = 0; const_cats[i].pos_x != NULL;i++)
        {
            window.draw(const_cats[i].sprite);
        }

        selector.sprite.setScale(sin(sin_time * 4) * 0.1 + 1, sin(sin_time * 4) * 0.1 + 1);
        window.draw(selector.sprite);

        window.draw(transition.sprite);

        //Rendering and restarting clock for DeltaTime purposes
        clock.restart();
        window.display();
        window.clear();
    }
}
