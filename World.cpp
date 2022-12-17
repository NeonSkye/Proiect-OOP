#include "World.h"

void World::Create(int SizeX_, int SizeY_, bool hasBorder)
    {  
        //std::cout<<"Create World "<<SizeX <<" x "<<SizeY<<std::endl; 
        this->SizeX=SizeX_;
        this->SizeY=SizeY_;
        this->has_Border = hasBorder;
        for(int i = 0; i<SizeY; i++){
            std::vector<Pixel*> v1;

            for(int j = 0; j<SizeX; j++)
            {
                if(hasBorder==1)
                {
        
                //std::cout<<"test1";
                if(i==0||i==SizeY-1)
                v1.push_back(new Pixel {"WALL",1,4,j,i});
                else
                    if(j==0||j==SizeX-1)
                    v1.push_back(new Pixel {"WALL",1,4,j,i});
                        else
                        v1.push_back(new Pixel {"VOID",0,0,j,i});
                }
                else
                v1.push_back(new Pixel {"VOID",0,0,j,i});
                
            }
            box.push_back(v1); 
        } 
    }

World::World(int X_, int Y_, bool hasBorder) 
        
        {
        Create(X_,Y_,hasBorder);
        }


void World::drawBox()
   
    {

        
                std::cout<<"------------------------"<<std::endl;
        for(int i = 0; i<SizeY; i++)
        {
            for(int j = 0; j<SizeX; j++)
            {
               std::cout<<box[i][j]->getID_list()<<" ";
            }
            std::cout<<std::endl;
        }
        
                std::cout<<"------------------------"<<std::endl;
    }
    Pixel* World::getBox(float conX, float conY)
    {
        return box[conY][conX];
    }


   std::ostream& operator<<(std::ostream& os, const World& w)
    {
        os<<"Size World " << w.SizeX << " x " <<w.SizeY <<"\n";
        return os;
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
                if(box[i][j]->getID_list()==0)
                {
                rect.setFillColor(sf::Color::Black);
                rect.setPosition(pos);
                window.draw(rect);
                }
                if(box[i][j]->getID_list()==1)
                {
                rect.setFillColor(sf::Color::White);
                rect.setPosition(pos);
                window.draw(rect);
                }
                if(box[i][j]->getID_list()==2)
                {
                rect.setFillColor(sf::Color(255,190,90,255));
                rect.setPosition(pos);
                window.draw(rect);
                }
                if(box[i][j]->getID_list()==3)
                {
                rect.setFillColor(sf::Color(40,80,175,255));
                rect.setPosition(pos);
                window.draw(rect);
                }
                if(box[i][j]->getID_list()==4)
                {
                rect.setFillColor(sf::Color(125,125,125,255));
                rect.setPosition(pos);
                window.draw(rect);
                }
            }
            std::cout<<std::endl;
        }
    }
            
        void World::SetPixel(Pixel* P, int posX, int posY)
    {   
    
        if(box[posY][posX]->getID_list()==0)
        {
        box[posY][posX] = P;
        P->setCoords(posX,posY);
        P->setID(1);
        //box[posY][posX]->setCoords(posX,posY);
        }
        if(P->getID_list()==0 && box[posY][posX]->getID_list()!=1)
        {
        box[posY][posX] = P;
        P->setCoords(posX,posY);
        P->setID(-1);
        } 
        
    }

    void World::moveWorld()
    {
        //Pixel aux{"VOID",0,0,0,0,0};
         for(int i = 1; i<SizeY-1; i++)
        {
            for(int j = 1; j<SizeX-1; j++)
            {   

                box[i][j]->setCoords(j,i);
                box[i][j]->movePixel(box);
                
                   
            }
        }
        
    }
    
    

            
            
