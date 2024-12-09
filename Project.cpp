#include <iostream>
#include "SFML/Graphics.hpp"
int main()
{
    
    sf::RenderWindow window(sf::VideoMode(800, 800), "Test");
    sf::Event e;
    std::cout << "Hello World!\n";

    while (window.isOpen())
    {
        while (window.pollEvent(e)) 
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }
    
    


}
