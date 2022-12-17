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
       this->posX = X;
       this->posY = Y;
    }

int Pixel::getposX()
    {
        return posX;
    }

int Pixel::getposY()
    {
        return posY;
    }
 void Pixel::setID(int N)
    {
        ID = ID+N;
    }
int Pixel::getID()
    {
    return ID;
    }
    void Pixel::movePixel(std::vector<std::vector<Pixel*>>& box)
        {
            box[posY][posX] = box[posY][posX];
        /*     
            
            
            int posX = this->posX;
            int posY = this->posY;
            Pixel *P = box[posY][posX];
            if(box[posY][posX]->getID_list() == 2&&box[posY+1][posX]->getID_list() == 0)
            {
                box[posY+1][posX] = P;
                box[posY][posX] = new Pixel {"VOID",-1,0,0,posX,posY};
                
                P->setCoords(posX,posY+1);

            }
             if(box[posY][posX]->getID_list() == 2&&box[posY+1][posX]->getID_list() != 1)
            {
                if(box[posY+1][posX+1]->getID_list()==0)
                {
                    box[posY+1][posX+1]=P;
                    box[posY][posX] = new  Pixel {"VOID",-1,0,0,posX,posY};
                     P->setCoords(posX+1,posY+1);
                    
                }
                else
                    if(box[posY+1][posX+1]->getID_list()!=0 && box[posY+1][posX-1]->getID_list() == 0)
                    {
                    box[posY+1][posX-1]=P;
                    box[posY][posX] =  new  Pixel {"VOID",-1,0,0,posX,posY};
                        P->setCoords(posX-1,posY+1);
                    }
                    
            } */
        
        } 

    Pixel::Pixel(const std::string& Name_, int ID_l, int Type_, int posX_, int posY_) : Name{Name_}, ID_list{ID_l}, Type{Type_}, posX{posX_}, posY{posY_}{
    }
    Pixel::Pixel(const Pixel& other): Name{other.Name}, ID_list{other.ID_list}, Type{other.Type}, posX{other.posX}, posY{other.posY} {}
    Pixel& Pixel::operator=(const Pixel& other) {
        Name = other.Name;
        ID_list = other.ID_list;
        Type = other.Type;
        posX = other.posX;
        posY = other.posY;
        return *this;
    }
    int Pixel::ID = 0;
    void Powder::setCoords(int X, int Y)
    {
       this->posX = X;
       this->posY = Y;
    }
     void Powder::movePixel(std::vector<std::vector<Pixel*>>& box)
        {
            
            int posX = this->posX;
            int posY = this->posY;
            Pixel *P = box[posY][posX];
            P->setCoords(posX,posY);
            if(box[posY][posX]->getID_list() == 2&&box[posY+1][posX]->getID_list() == 0)
            {
                box[posY+1][posX] = P;
                box[posY][posX] = new Pixel {"VOID",0,0,posX,posY};
                
                P->setCoords(posX,posY+1);

            }
            if(box[posY][posX]->getID_list() == 2&&box[posY+1][posX]->getID_list() == 3)
            {
                box[posY+1][posX] = P;
                box[posY][posX] = new Liquid {"WATR",3,2,posX,posY};
                
                P->setCoords(posX,posY+1);

            }
             if(box[posY][posX]->getID_list() == 2&&box[posY+1][posX]->getID_list() != 1)
            {
                if(box[posY+1][posX+1]->getID_list()==0)
                    {
                    box[posY+1][posX+1]=P;
                    box[posY][posX] = new  Pixel {"VOID",0,0,posX,posY};
                     P->setCoords(posX+1,posY+1);
                    }
                else
                    
                if(box[posY+1][posX+1]->getID_list()!=0 && box[posY+1][posX-1]->getID_list() == 0)
                    {
                    box[posY+1][posX-1]=P;
                    box[posY][posX] =  new  Pixel {"VOID",0,0,posX,posY};
                        P->setCoords(posX-1,posY+1);
                    }
                    
            }
            
        } 
    void Liquid::setCoords(int X, int Y)
    {
       this->posX = X;
       this->posY = Y;
    }
    void Liquid::movePixel(std::vector<std::vector<Pixel*>>& box) 
   
        { 
            int move = rand() % 2;
            int posX = this->posX;
            int posY = this->posY;
            Pixel *P = box[posY][posX];
            P->setCoords(posX,posY);
                if(box[posY][posX]->getID_list() == 3&&box[posY+1][posX]->getID_list() == 0)
            {
                box[posY+1][posX] = P;
                box[posY][posX] = new Pixel {"VOID",0,0,posX,posY};

                P->setCoords(posX,posY+1);
            }
                if(box[posY][posX]->getID_list() == 3&&box[posY+1][posX]->getID_list() != 0)
            {
                if(move==1)
                { 
                    if(box[posY][posX+1]->getID_list()==0)
                        {
                        box[posY][posX+1] = P;
                        box[posY][posX] = new Pixel {"VOID",0,0,posX,posY};
                        }
                    P->setCoords(posX+1,posY);
                }
                else
                {   
                    if(box[posY][posX-1]->getID_list()==0)
                        {
                        box[posY][posX-1] = P;
                        box[posY][posX] = new Pixel {"VOID",0,0,posX,posY};
                        }
                    P->setCoords(posX-1,posY);
                }
            }
           
            
        } 
        void Solid::setCoords(int X, int Y)
    {
       this->posX = X;
       this->posY = Y;
    }
   