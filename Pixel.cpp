#include"Pixel.h"

int Pixel::getID_list()
    {
    return ID_list;
    }

int Pixel::getType()
     {
        return Type;
    }

void Pixel::setCoords(int X, int Y)
    {
       posX = X;
       posY = Y;
    }

int Pixel::getposX()
    {
        return posX;
    }

int Pixel::getposY()
    {
        return posY;
    }

    Pixel::Pixel(const std::string& Name_, int ID_, int ID_l, int Type_, int posX_, int posY_) : Name{Name_}, ID{ID_}, ID_list{ID_l}, Type{Type_}, posX{posX_}, posY{posY_}{
        /* std::cout<<"Constructor initializare Pixel"<<std::endl;
        std::cout<<"Created Pixel "<< Name <<" With ID "<< ID << " Type " << Type << " And Behaviour " << std::endl; */
    }
    Pixel::Pixel(const Pixel& other): Name{other.Name}, ID{other.ID}, ID_list{other.ID_list}, Type{other.Type}, posX{other.posX}, posY{other.posY} {
        /* std::cout<<"Constructor copiere Pixel"<<std::endl; */
         //std::cout<<"Copied Pixel "<< Name <<" With ID "<< ID << " Type " << Type << " And Behaviour " << std::endl;
    }
    Pixel& Pixel::operator=(const Pixel& other) {
        Name = other.Name;
        ID = other.ID;
        ID_list = other.ID_list;
        Type = other.Type;
        posX = other.posX;
        posY = other.posY;
        /* std::cout<<"Operator= copiere Pixel"<<std::endl; */
        return *this;
    }