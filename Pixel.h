#ifndef PIXEL_H
#define PIXEL_H
#include<string>
#include<iostream>

class Pixel {
    private:
    std::string Name;
/*     sf::RectangleShape px;
    px.setSize(sf::Vector2f(10, 10)); */
    //sf::RectangleShape px;
    //sf::Color colour(0,0,0,255);
    int ID;
    int ID_list;
    
    int Type;
    int posX, posY;
    //int x, y;
    /*float Weight;
    int Density;
    int Temp_init;
    int colour; //change to sfml colour 
    bool Can_burn;
    bool Can_melt;
    bool Can_ignite; */
    //PixelBehaviour PB{this->Type, this->Weight, this->Temp_init};
    public:
    // to add PixelBehaviour to Pixel constructor
/*     int Color(int r, int g, int b, int a)
    {
        &colour.r=r;
        &colour.g=g;
        &colour.b=b;
        &colour.a=a;
    } */
    int getID_list();
    int getType();
    void setCoords(int X, int Y);
    int getposX();
    int getposY();
    
    ~Pixel()
    {
        /* std::cout <<"Destructor Pixel"<<std::endl; */
    }
    friend std::ostream& operator<<(std::ostream& os, const Pixel& px){
        os << "Type " << px.Type << " ID_list " << px.ID_list << "\n";
        return os;
    }
    Pixel(const std::string& Name_, int ID_, int ID_l, int Type_, int posX_, int posY_);
    Pixel(const Pixel& other);
    Pixel& operator=(const Pixel& other);
}; 


#endif