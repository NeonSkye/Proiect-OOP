#include<iostream>
#include<string>
#include<utility>
#include "Pixel.h"
#include "World.h"
//#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<cmath>

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
/*PIXEL IDS (so far)
0. NOTHING
1. WALL
2. DUST*/

//weight doesn't matter for static solids (is 0?)
//type dictates how pixels move
//density affects how pixels layer (e.g a liquid/powder pixel with density of 2 will go under a liquid/powder pixel with density of 1)
//temp_init is the initial temperature of the pixel upon spawn (celsius)

//TO DO: FIGURE OUT HOW TO TRANSLATE MATRIX TO GRAPHICS
//SIMULATION ENGINE AFTER


 

// buttons for elements
/* class Elem_Button{
    private:
    std::string name;
    int ID;
    int type;
    int colour; //change to sfml colour
    int sel_colour; //change to sfml colour; selected box' colour, changes on whether clicked with LMB, RMB or MMB
    int wid, len;
    Pixel content;

    public:
    Elem_Button(const Pixel& content_) : content{content_} {
        //this->content.ID=content_.getID();
        //this->content.type=content_getType();
        // std::cout<<"Constructor initializare Elem_Button"<<std::endl; 
    }
    friend std::ostream& operator<<(std::ostream& os, const Elem_Button& elem_b)
    {
        os<<"Type elem " << elem_b.content <<"\n";
        return os;
    }
    void onLeftClick() {} // Set LMB to spawn selected box' pixel
    void onRightClick() {}// Set RMB to spawn selected box' pixel
    void onMiddleClick() {}// Set MMB to spawn selected box' pixel

}; */

/* class Simulation {
   private:
     int vx, vy;
    int temp;
    int gravity;
    Pixel pixel;
    std::vector<std::vector<Pixel>> box; 
 
    public:
    //PixelBehaviour(int type_, int weight_, int temp_, int gravity_) : type{type_}, weight{weight_}, temp{temp_}, gravity{gravity_}

  PixelBehaviour(Pixel P_) : pixel{P_}{}
    friend std::ostream& operator<<(std::ostream& os, const PixelBehaviour& pxb)
    {
        os<<"Type PB " << pxb.pixel << "\n";
        return os;
    }
    void TransformPixel() {}
}; */



int main()
{
    World w1{10,10,1};
    
    std::cout<<w1;
    Pixel p1{"DUST",0,2,1,0,0};
    bool isActive = 0;
    w1.drawBox();
sf::RenderWindow window(sf::VideoMode(500, 500), "SFML window");
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
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {w1.drawBox();}
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
            {
                sf::RectangleShape rect;
                w1.SetPixel(p1,conX,conY);
                rectangle.setPosition(pos2);
                rect.setSize(sf::Vector2f(50, 50));
                rect.setPosition(pos2);
                rect.move(10,1);
                w1.drawBox();
                window.draw(rect);
            }
            if(event.mouseButton.button == sf::Mouse::Middle) {std::cout << "m\n";}
            if(event.mouseButton.button == sf::Mouse::Right) 
            {
                w1.movePixel(p1);
                w1.drawBox();
                //
                /* bg.setPosition(0,0);
                isActive = 1;
                window.draw(rectangle); */
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::XButton2)) {rectangle.setPosition(pos2);}
            break;
        default:
        break;
        }
    }


   // Activate the window for OpenGL rendering

// draw it

if(isActive == 1) 
{
    rectangle.move(0,1);
    window.draw(bg);
    window.draw(rectangle);
    w1.drawPixel(window);
}

        //std::cout<<conX<<" "<<conY<<std::endl;
       // std::cout<<pos.x<<" "<<pos.y<<std::endl;
   w1.movePixel(p1);
   w1.drawBox();
   w1.drawPixel(window);
   //window.draw(rectangle);
   window.display();
}
}