#include "World.h"

void World::Create(int SizeX_, int SizeY_, bool hasBorder)
    {  
        //std::cout<<"Create World "<<SizeX <<" x "<<SizeY<<std::endl; 
        this->SizeX=SizeX_;
        this->SizeY=SizeY_;
        this->has_Border = hasBorder;
        int ID = -1;
        for(int i = 0; i<SizeY; i++){
            std::vector<Pixel> v1;

            for(int j = 0; j<SizeX; j++)
            {
                if(hasBorder==1)
                {
        
                //std::cout<<"test1";
                if(i==0||i==SizeY-1)
                v1.push_back({"WALL",ID,1,4,j,i});
                else
                    if(j==0||j==SizeX-1)
                    v1.push_back({"WALL",ID,1,4,j,i});
                        else
                        v1.push_back({"VOID",ID,0,0,j,i});
                }
                else
                v1.push_back({"VOID",ID,0,0,j,i});
                
            }
            box.push_back(v1); 
        } 
    }

World::World(int X_, int Y_, bool hasBorder) 
        
        {
        World::Create(X_,Y_,hasBorder);
        }


void World::drawBox()
   
    {

        
                std::cout<<"------------------------"<<std::endl;
        for(int i = 0; i<SizeY; i++)
        {
            for(int j = 0; j<SizeX; j++)
            {
               std::cout<<box[i][j].getID_list()<<" ";
            }
            std::cout<<std::endl;
        }
        
                std::cout<<"------------------------"<<std::endl;
    }
/*     std::vector<std::vector<Pixel>> getBox()
    {
        return box;
    } */
    /* int getGravity()
    {
        return Gravity;
    }
     int getSizeX()
    {
        return SizeX;
    }
    int getSizeY()
    {
        return SizeY;
    } */

   std::ostream& operator<<(std::ostream& os, const World& w)
    {
        os<<"Size World " << w.SizeX << " x " <<w.SizeY <<"\n";
        return os;
    }
        void World::SetPixel(Pixel& P, int posX, int posY)
    {   
    
        if(box[posY][posX].getID_list()==0)
        {
        box[posY][posX] = P;
        P.setCoords(posX,posY);
        }
    }
    
        void World::movePixel (Pixel& P)
        {
            //std::cout<<"test GetPos"<< P.getposX() << P.getposY() << std::endl;
            int posX = P.getposX();
            int posY = P.getposY();
            if(P.getType()==1)
            {
                //std::cout<<"getType success"<< posX << posY << std::endl;
                if(box[posY][posX].getID_list() == 2&&box[posY+1][posX].getID_list() == 0)
                {
                    //std::cout<<"checkBox success"<<std::endl;
                    if(box[posY-1][posX].getType() == 4)
                    box[posY][posX] = {"VOID",-1,0,0,posX,posY};
                    else
                    box[posY][posX] = box[posY-1][posX];
                    posY = posY+1;
                    box[posY][posX] = P;
                    P.setCoords(posX,posY);
                }
                else
                    if(box[posY+1][posX].getID_list() != 0&&box[posY+1][posX].getID_list() != 1)
                    {
                        
                        if(box[posY+1][posX+1].getID_list() == 0)
                        {
                        if(box[posY-1][posX].getType() == 4)
                        box[posY][posX] = {"VOID",-1,0,0,posX,posY};
                        else
                        box[posY][posX] = box[posY-1][posX];
                        box[posY+1][posX+1] = P;
                        P.setCoords(posX+1,posY+1);
                        }
                        else if(box[posY+1][posX+1].getID_list() == 2 && box[posY+1][posX-1].getID_list() == 0)
                        {
                        if(box[posY-1][posX].getType() == 4)
                        box[posY][posX] = {"VOID",-1,0,0,posX,posY};
                            else
                            box[posY][posX] = box[posY-1][posX];
                        box[posY+1][posX-1] = P;
                        P.setCoords(posX-1,posY+1);
                        }
                    }
            }

        }

    void World::drawPixel(sf::RenderWindow& window)
    {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(50, 50));
        sf::Vector2f pos(0,0);
         for(int i = 0; i<SizeY; i++)
        {
            for(int j = 0; j<SizeX; j++)
            {
                pos.x = j*50;
                pos.y = i*50;
                if(box[i][j].getID_list()==0)
                {
                
                rect.setFillColor(sf::Color::Black);
                rect.setPosition(pos);
                window.draw(rect);
                }
                if(box[i][j].getID_list()==1)
                {
                rect.setFillColor(sf::Color::White);
                rect.setPosition(pos);
                window.draw(rect);
                }
                if(box[i][j].getID_list()==2)
                {
                rect.setFillColor(sf::Color::Yellow);
                rect.setPosition(pos);
                window.draw(rect);
                }
            }
            std::cout<<std::endl;
        }
    }
            
            
            
