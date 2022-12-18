#ifndef WORLD_H
#define WORLD_H
#include<iostream>
#include"Pixel.h"
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<memory>

class World{
    
    private:
    std::vector<std::vector<std::shared_ptr<Pixel>>> box;
   
    int SizeX;
    int SizeY;
    bool has_Border;
    //int Gravity;
    public:
    void Create(int SizeX_, int SizeY_, bool hasBorder);
    World(int X_, int Y_, bool hasBorder);
    
    
/*     void setBox(std::vector<std::vector<Pixel>> box_)
    {
        for(int i = 0; i<SizeY; i++){
            std::vector<Pixel> v1;

            for(int j = 0; j<SizeX; j++)
            {
                v1.push_back(box_[i][j]);
            }
            this->box.push_back(v1); 
        } 
    } */



    void drawBox();
 /*    Pixel* getBox(float conX, float conY); */
    friend std::ostream& operator<<(std::ostream& os, const World& w);
    void SetPixel(std::shared_ptr<Pixel> P, int posX, int posY);
    void moveWorld();
    
   void drawPixel(sf::RenderWindow& window);
            
            
            

};

#endif