#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>


class Square
{

public:

    sf::Vector2f    size                = {100.f , 100.f};
    sf::Vector2f    position_current    = {100.f , 100.f}; 
    sf::Vector2f    position_old        = {100.f , 100.f};
    float           rotation            = 1.f; 
    sf::Color       color               = sf::Color::White; 
    sf::Vector2f    acceleration        = {0.0f , -50.f};
    sf::Vector2f    distance            = {0.0f , 0.0f};

    Square() = default;
    Square(sf::Vector2f position , sf::Vector2f v )
        :position_current{position}
        ,distance{v}

        //,size{size_}
        //,rotation{rotation_}
    {}

    ~Square() = default;
    void setPosition(sf::Vector2f position)
    {
        position_current = position;
    }

    void setVelocity(sf::Vector2f v)
    {
        distance = v;
    }

    void update(float dt)
    {

        position_current = position_current + distance + acceleration*dt*dt;
    }



};




class Smoke
{
private:

std::default_random_engine generator;
std::normal_distribution<float> distributionY = std::normal_distribution<float>(0.0 , 20.0);
std::normal_distribution<float> distributionX = std::normal_distribution<float>(0.0 , 20.0);



std::vector<Square>     m_objects ;
sf::Vector2f            start_velocity      = {1.f , 0.f };
sf::Vector2f            start_position      = {500.f , 500.f};
int32_t                 m_amount_objects    =0;
float                   m_frame_dt          =0.0f;
float                   m_time              =0.0f; 
sf::Texture             texture; 

public:
    Smoke() = default;

    Smoke(int32_t amount , sf::Vector2f position)  
        :start_position{position}
        ,m_amount_objects{amount}
        
        {
            m_objects.reserve(amount);
            if(!texture.loadFromFile("./smoke.png" ,sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(280,280) ) ))
            {
                std::cout << "failed to load image" << std::endl;
                exit(1);
            }

        }
    

    void update(float dt)
    {

            if(static_cast<int32_t>(m_objects.size()) < m_amount_objects)
            {   
                for(int i = 0 ; i < 100 ; i++)
                {
                    start_velocity.y = distributionY(generator);
                    start_velocity.x = distributionX(generator);

                    float normal_velocity = sqrt(start_velocity.y*start_velocity.y +start_velocity.x*start_velocity.x);

                    start_position.y = start_position.y+10*start_velocity.y/normal_velocity;
                    start_position.x = start_position.x+10*start_velocity.x/normal_velocity;
                    m_objects.insert(m_objects.begin() , Square(start_position , start_velocity));
                }
            }



        for(long unsigned int i = 0 ; i< m_objects.size() ; i++)
        {
            m_objects[i].update(dt);   

            m_objects[i].distance.y = m_objects[i].distance.y * 0.90;
            m_objects[i].distance.x = m_objects[i].distance.x * 0.90;

            if(m_objects[i].color.a != 1 )m_objects[i].color.a-=2 ; 


        }
        m_time += dt;

         if(m_time >= 2.0f and m_objects.size() > 0)
        {   
            for (int i =0 ; i <5 ; i++)
            {
                m_objects.pop_back();
                m_amount_objects--;
            } 
        }
    }

    void render(sf::RenderWindow& render_target)
    {
        sf::RectangleShape rectangle(start_velocity);
        for(long unsigned int i = 0 ; i<m_objects.size() ; i++)
        {

            rectangle.setPosition(m_objects[i].position_current);
            rectangle.setSize(m_objects[i].size);
            rectangle.setFillColor(m_objects[i].color);
            rectangle.setRotation(m_objects[i].rotation);
            rectangle.setTexture(&texture);
            render_target.draw(rectangle);

        }

       
    }

};




