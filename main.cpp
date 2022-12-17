#include<iostream>
#include<string>
#include<utility>
#include "Pixel.h"
#include "World.h"
//#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<cmath>
#include<thread>

/*vx, vy affected by pixel weight*/

// To implement getting gravity of World

/* 
PIXEL TYPES
0. NOTHING
1. POWDER SOLID
2. LIQUID
3. GAS
4. STATIC SOLID
5. MOVING SOLID (MAYBE)
*/
/*PIXEL IDS_LIST (so far)
0. NOTHING
1. WALL
2. DUST
3. WATER*/

//weight doesn't matter for static solids (is 0?)
//type dictates how pixels move
//density affects how pixels layer (e.g a liquid/powder pixel with density of 2 will go under a liquid/powder pixel with density of 1)
//temp_init is the initial temperature of the pixel upon spawn (celsius)

//TO DO: FIGURE OUT HOW TO TRANSLATE MATRIX TO GRAPHICS
//SIMULATION ENGINE AFTER

void func(Pixel* list, int conX, int conY, World &w1)

{
    int i = 0;
    std::thread tr{[&]() 
            {
                while(sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
                {
                    i++;
                    if(i%4==0)
                    {
                     w1.SetPixel(list,conX,conY);
                     std::cout<<"test"<<std::endl;
                     
                     i = 0;
                    }
                }
            }};
   
    tr.detach();
}


int main()
{
    World w1{20,20,1 };
    
    
    std::cout<<w1;
    
    Pixel* p0= new Pixel {"VOID",0,0,0,0};
    Pixel* p1= new Powder {"DUST",2,1,0,0};
    Pixel* p2= new Liquid {"WATR",3,2,0,0};
    Pixel* p3= new Solid {"BRCK",4,3,0,0};
    //Pixel* select = p1;
    std::vector<Pixel*> list = {p1,p2,p3};
    int i = 0;
    int pause = 1;
    w1.drawBox();
sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML window");
window.setFramerateLimit(60);
sf::RectangleShape rectangle, bg;
        rectangle.setSize(sf::Vector2f(50, 50));
        

        bg.setSize(sf::Vector2f(500,500));
        bg.setOutlineColor(sf::Color::Black);
        bg.setOutlineThickness(5);
        bg.setFillColor(sf::Color::Black);

window.draw(bg);
while (window.isOpen())
{
   
    float conX, conY;
    window.setActive();
   // Event processing
   sf::Vector2i pos = sf::Mouse::getPosition(window);
   sf::Vector2f pos2(0,0);
   pos2.x = pos.x;
   pos2.y = pos.y;
   conX = floor(pos.x/50);
   conY = floor(pos.y/50);
   sf::Event event;
   
   while (window.pollEvent(event))
   {
    
       // Request for closing the window
       if (event.type == sf::Event::Closed)
           window.close();
            switch(event.type) {
        case sf::Event::MouseButtonPressed:
            
            
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
                {
                    func(list[i],conX,conY,w1);
                    
                }
            
            if(event.mouseButton.button == sf::Mouse::Middle) 
            {
                    if(i<2)
                    i = i+1;
                    else i = 0;
            }
           
            if(event.mouseButton.button == sf::Mouse::Right) 
            {
                w1.SetPixel(p0,conX,conY);
          
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::XButton2)) {rectangle.setPosition(pos2);}
            break;
        case sf::Event::KeyPressed:
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    pause = pause * -1;
                }
            break;

        default:
        break;

        }
    }


   // Activate the window for OpenGL rendering

// draw it

   // rectangle.move(0,1);
   // w1.moveWorld();
    window.draw(bg);
    window.draw(rectangle);
    w1.drawPixel(window);
        //std::cout<<conX<<" "<<conY<<std::endl;
       // std::cout<<pos.x<<" "<<pos.y<<std::endl;
    if(pause==1)
    w1.moveWorld();
   //w1.movePixel(p1);
   //w1.drawBox();
   //window.draw(rectangle);
   window.display();
   std::cout<<"SELECTED: "<<list[i]<<std::endl;
}
}
