#include<iostream>
#include<string>
#include<utility>
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
    int getID_list()
    {
        return ID_list;
    }
    int getType()
    {
        return Type;
    }

    void setCoords(int X, int Y)
    {
       posX = X;
       posY = Y;
    }
    int getposX()
    {
        return posX;
    }
    int getposY()
    {
        return posY;
    }
    
    ~Pixel()
    {
        /* std::cout <<"Destructor Pixel"<<std::endl; */
    }
    friend std::ostream& operator<<(std::ostream& os, const Pixel& px){
        os << "Type " << px.Type << " ID_list " << px.ID_list << "\n";
        return os;
    }
    Pixel(const std::string& Name_, int ID_, int ID_l, int Type_, int posX_, int posY_) : Name{Name_}, ID{ID_}, ID_list{ID_l}, Type{Type_}, posX{posX_}, posY{posY_}{
        /* std::cout<<"Constructor initializare Pixel"<<std::endl;
        std::cout<<"Created Pixel "<< Name <<" With ID "<< ID << " Type " << Type << " And Behaviour " << std::endl; */
    }
    Pixel(const Pixel& other): Name{other.Name}, ID{other.ID}, ID_list{other.ID_list}, Type{other.Type}, posX{other.posX}, posY{other.posY} {
        /* std::cout<<"Constructor copiere Pixel"<<std::endl; */
         //std::cout<<"Copied Pixel "<< Name <<" With ID "<< ID << " Type " << Type << " And Behaviour " << std::endl;
    }
    Pixel& operator=(const Pixel& other) {
        Name = other.Name;
        ID = other.ID;
        ID_list = other.ID_list;
        Type = other.Type;
        posX = other.posX;
        posY = other.posY;
        /* std::cout<<"Operator= copiere Pixel"<<std::endl; */
        return *this;
    }
}; 

 class World{

    private:
    std::vector<std::vector<Pixel>> box;
   
    int SizeX;
    int SizeY;
    bool has_Border;
    //int Gravity;
    public:
    void Create(int SizeX_, int SizeY_, bool hasBorder)
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
    World(int X_, int Y_, bool hasBorder) {
        Create(X_,Y_,hasBorder);
        }
    
    
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



    void drawBox()
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
    friend std::ostream& operator<<(std::ostream& os, const World& w)
    {
        os<<"Size World " << w.SizeX << " x " <<w.SizeY <<"\n";
        return os;
    }
        void SetPixel(Pixel& P, int posX, int posY)
    {   
    
        if(box[posY][posX].getID_list()==0)
        {
        box[posY][posX] = P;
        P.setCoords(posX,posY);
        }
    }
    
        void movePixel (Pixel& P)
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
    void drawPixel(sf::RenderWindow& window)
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
            
            
            

};




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
    //sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    World w1{10,10,1};
    
    std::cout<<w1;
    Pixel p1{"DUST",0,2,1,0,0};
    /* PixelBehaviour pb1{p1}; */
    bool isActive = 0;
    w1.drawBox();
    /* std::cout<<w1;      Pixel p1{"FIRST",1,2};
    Pixel p6{"SECOND",2,3};
     std::cout<<p1; 
    PixelBehaviour pb1{1,2,1};
     std::cout<<pb1; 
    Pixel p2{p1};
    Pixel p3 = p1;
    p2 = p3;
    Elem_Button e1{p1}; 
    std::cout<<e1; 
     std::cout<<"6-------------6"<<std::endl; */
    //w1.SetPixel(p1.getID(),0,0,p1.getType());
    //w1.getWorld();
    //w1.getWorld();
   // w1.SpawnPixel(TYPE,posX,posY,LOC);
   // w1.Update();
sf::RenderWindow window(sf::VideoMode(500, 500), "SFML window");
/* sf::Vector2<Pixel> box; */
// Limit the framerate to 60 frames per second (this step is optional)
window.setFramerateLimit(60);
// The main loop - ends as soon as the window is closed
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