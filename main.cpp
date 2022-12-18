#include<iostream>
#include<string>
#include<utility>
#include "Pixel.h"
#include "World.h"
#include<memory>
//#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<cmath>
#include<thread>
#ifdef __linux__
#include <X11/Xlib.h>
#endif
#include<stdexcept>


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

/* void func(Pixel* list, int conX, int conY, World &w1)

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
} */
class app_error : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class coords_error : public app_error {
    public:
        explicit coords_error() :
            app_error("out of bounds") {}
};

void coords(float conX_ , float conY_ ,int SizeX_, int SizeY_)
{
    if((conX_<0||conX_>=SizeX_) || (conY_<0||conY_>=SizeY_))
        throw coords_error();
}

int main()
{
    #ifdef __linux__
    XInitThreads();
    #endif
    int SizeX, SizeY;
    int full = 0;
    SizeX = 20; SizeY = 20;
    World w1{SizeX,SizeY,1};
    std::thread tr;
    
    std::cout<<w1;
    
    std::shared_ptr<Pixel> p0= std::make_shared<Pixel>("VOID",0,0,0,0);
    std::shared_ptr<Pixel> p1= std::make_shared<Powder>("DUST",2,1,0,0);
    std::shared_ptr<Pixel> p2= std::make_shared<Liquid>("WATR",3,2,0,0);
    std::shared_ptr<Pixel> p3= std::make_shared<Solid>("BRCK",4,3,0,0);
    std::shared_ptr<Pixel> p4= std::make_shared<Solid>("ICE",5,3,0,0);
    //Pixel* select = p1;
    std::vector<std::shared_ptr<Pixel>> list{p1,p2,p3,p4};
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
    
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineThickness(5);
    rect.setOutlineColor(sf::Color::White);
    rect.setSize(sf::Vector2f(15, 15));
    rect.setPosition(20,20);
     

window.draw(bg);
window.draw(rect);
while (window.isOpen())
{
   window.setTitle("ParticleSim++");
   window.setMouseCursorVisible(false);
   window.draw(rect);
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
    
       if (event.type == sf::Event::Closed)
           window.close();
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
                {
                    
                    tr = std::thread{[&]() 
	            {
	        
           
		        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
		        {
                    int error = 0;
		
                    {
                    try
                    {
                    coords(conX,conY,SizeX,SizeY);
                    } 
                    catch(std::runtime_error& err)
                        {
                            std::cout << err.what() << "\n";
                            pause = -1;
                            error = 1;
                        }
                   // if((conX>0&&conX<20) && (conY>0&&conY<20)) 

                        if(error != 1)
		                w1.SetPixel(list[i],conX,conY);
                    
                    }

		        }
                
		    }};
             tr.detach();
            }
           

                if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) 
                {
                    
                    tr = std::thread{[&]() 
	            {
	        
           
		        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) 
		        {
                    int error2 = 0;
		
                    {
                    try
                    {
                    coords(conX,conY,SizeX,SizeY);
                    } 
                    catch(std::runtime_error& err)
                        {
                            std::cout << err.what() << "\n";
                            pause = -1;
                            error2 = 1;
                        }                    
		
                    
                    if(error2!=1) 
		             w1.SetPixel(p0,conX,conY);
            

		        }
                
		    }}};
            
		    tr.detach();
            }
            switch(event.type) {
        case sf::Event::MouseButtonPressed:
            
     
            
            if(event.mouseButton.button == sf::Mouse::Middle) 
            {
                    if(i<3)
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

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                {
                    w1.moveWorld();
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
                {
                    full = full + 1;
                    switch(full)
                    {   
                        case 1:
                        window.setSize(sf::Vector2u(800,800));
                        break;
                        case 2:
                        window.setSize(sf::Vector2u(1000,1000));
                        break;
                        case 3:
                        window.setSize(sf::Vector2u(500,500));
                        full = 0;
                        break;
                    }
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
   if((conX>0&&conX<20) && (conY>0&&conY<20))
     {
            switch(i)
            {
            case 0: 
            rect.setOutlineColor(sf::Color(255,190,90,255));
            break;
            case 1: 
            rect.setOutlineColor(sf::Color(40,80,175,255));
            break;
            case 2: 
            rect.setOutlineColor(sf::Color(125,125,125,255));
            break;
            case 3:
            rect.setOutlineColor(sf::Color(200,245,240,255));
            break;
            default:
            break;
            }
                rect.setPosition(pos.x,pos.y);
                
     }
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
   window.draw(rect);
   window.display();
   
   std::cout<<"SELECTED: "<<list[i]<<std::endl;
   std::cout<<"PIXEL COUNT: "<<p0->getID()<<std::endl;
}
}

