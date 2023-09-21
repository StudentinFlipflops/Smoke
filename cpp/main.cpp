#include <iostream>
#include <SFML/Graphics.hpp>
#include "smoke.h"
#include <vector>

int main()
{
    srand (static_cast <unsigned> (time(0)));

    constexpr int32_t window_width  = 1800;
    constexpr int32_t window_height = 1920;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    sf::RenderWindow window(sf::VideoMode(window_width,window_height,32), "Smoke" , sf::Style::Default , settings)  ; 
    
    const int32_t frame_rate = 60;
    window.setFramerateLimit(frame_rate);

    sf::Vector2f pos = {200.f, 200.f};
    float xpos = 0 ;
    float ypos = 0 ;

    std::vector<Smoke> smoke; 
    sf::Clock   clock; 
//    Smoke       Smoke( 400, pos);



    while (window.isOpen())
    {
        clock.restart();
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            } 
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                xpos = float(sf::Mouse::getPosition().x);
                ypos = float(sf::Mouse::getPosition().y);
                pos = {xpos, ypos};
                //std::cout << pos.x <<  "   "<< pos.y  << "|||"  << sf::Mouse::getPosition().x<< "   "  << sf::Mouse::getPosition().y << "\n";
                smoke.push_back(Smoke(1000, pos )); /*(sf::Vector2f)(sf::Mouse::getPosition())));*/
            }
        }
        
        for(int i = 0 ; i < static_cast<int>(smoke.size())  ; i++ ) smoke[i].update(1.0f/60 );       
        window.clear();
        for(int i = 0 ; i < static_cast<int>(smoke.size())  ; i++ ) smoke[i].render(window);
        window.display();
        
        
    }
    


}