#ifndef PIXEL_H
#define PIXEL_H
#include<string>
#include<vector>
#include<iostream>
#include<random>

class Pixel {
    private:
    std::string Name;
    static int ID;
    int ID_list;
    int Type;
    protected:
    int posX, posY;
    public:
    void setCoords(int X, int Y);
    int getID_list();
 /*    int getType(); */
    
  /*   int getposX();
    int getposY(); */
    static void setID(int N);
    static int getID();
    virtual void movePixel (std::vector<std::vector<Pixel*>>& box);
    
    
    friend std::ostream& operator<<(std::ostream& os, const Pixel* px){
        os << px->Name << " Type " << px->Type << " ID_list " << px->ID_list <<"\n";
        return os;
    }
    Pixel(const std::string& Name_, int ID_l, int Type_, int posX_, int posY_);
    Pixel(const Pixel& other);
    Pixel& operator=(const Pixel& other);
    ~Pixel() {}
}; 


class Powder : public Pixel {
    private:
    std::string Name;
    static int Type;
    using Pixel::Pixel;
    public:
    virtual void movePixel (std::vector<std::vector<Pixel*>>& box) override;
};

class Liquid : public Pixel {
    private:
    std::string Name;
    using Pixel::Pixel;

    public:
    virtual void movePixel (std::vector<std::vector<Pixel*>>& box) override;
};

class Solid : public Pixel {
    private:
    std::string Name;
    using Pixel::Pixel;
};

#endif