#include<iostream>
#include<string>
#include<utility>
//#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>

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
    //sf::Color colour(0,0,0,255);
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
    Pixel(const std::string& Name_, int ID_l, int Type_) : Name{Name_}, ID_list{ID_l}, Type{Type_}{
        /* std::cout<<"Constructor initializare Pixel"<<std::endl;
        std::cout<<"Created Pixel "<< Name <<" With ID "<< ID << " Type " << Type << " And Behaviour " << std::endl; */
    }
    Pixel(const Pixel& other): Name{other.Name}, ID_list{other.ID_list}, Type{other.Type} {
        /* std::cout<<"Constructor copiere Pixel"<<std::endl; */
         //std::cout<<"Copied Pixel "<< Name <<" With ID "<< ID << " Type " << Type << " And Behaviour " << std::endl;
    }
    Pixel& operator=(const Pixel& other) {
        Name = other.Name;
        ID_list = other.ID_list;
        Type = other.Type;
        /* std::cout<<"Operator= copiere Pixel"<<std::endl; */
        return *this;
    }
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
}; 

 class World{

    private:
    std::vector<std::vector<Pixel>> box;
   
    int SizeX;
    int SizeY;
    bool has_Border;
    //int Gravity;
    public:
    void Create(int SizeX, int SizeY, bool hasBorder)
    {  
        //std::cout<<"Create World "<<SizeX <<" x "<<SizeY<<std::endl; 
        this->SizeX=SizeX;
        this->SizeY=SizeY;
        this->has_Border = hasBorder;

        for(int i = 0; i<SizeY; i++){
            std::vector<Pixel> v1;

            for(int j = 0; j<SizeX; j++)
            {
                if(hasBorder==1)
                {
        
                //std::cout<<"test1";
                if(i==0||i==SizeY-1)
                v1.push_back({"WALL",1,4});
                else
                    if(j==0||j==SizeX-1)
                    v1.push_back({"WALL",1,4});
                    else
                        v1.push_back({"VOID",0,0});
                        }
                        else
                            v1.push_back({"VOID",0,0});
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
    std::vector<std::vector<Pixel>> getBox()
    {
        return box;
    }
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
        box[posY][posX] = P;
        P.setCoords(posX,posY);

    }
    
        void movePixel (Pixel& P)
        {
            std::cout<<"test GetPos"<< P.getposX() << P.getposY() << std::endl;
            int posX = P.getposX();
            int posY = P.getposY();
            if(P.getType()==1)
            {
                std::cout<<"getType success"<< posX << posY << std::endl;
                if(box[posY][posX].getID_list() == 2)
                {
                    std::cout<<"checkBox success"<<std::endl;
                    box[posY+1][posX] = P;
                    box[posY][posX] = {"VOID",0,0};
                    P.setCoords(posX,posY+1);
                }
                else std::cout<<"checkBox failed"<<std::endl;


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
    World w1{5,5,1};
    std::cout<<w1;
    Pixel p1{"DUST",2,1};
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
sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
/* sf::Vector2<Pixel> box; */
// Limit the framerate to 60 frames per second (this step is optional)
window.setFramerateLimit(60);
// The main loop - ends as soon as the window is closed
sf::RectangleShape rectangle, bg;

    rectangle.setSize(sf::Vector2f(100, 50));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(5);
        rectangle.setPosition(10, 20);

            bg.setSize(sf::Vector2f(800,600));
            bg.setOutlineColor(sf::Color::Black);
            bg.setOutlineThickness(5);
            bg.setFillColor(sf::Color::Black);

window.draw(bg);
window.draw(rectangle);
while (window.isOpen())
{
   // Event processing
   window.draw(rectangle);
   sf::Event event;
   while (window.pollEvent(event))
   {
       // Request for closing the window
       if (event.type == sf::Event::Closed)
           window.close();
   }

   // Activate the window for OpenGL rendering
   window.setActive();
if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
{
    w1.SetPixel(p1,2,2);
    //w1.SetPixel(p1,2,2);
  
    

};
// draw it



if(isActive == 0) {

if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
{
     //w1.movePixel(p1,w1);
     rectangle.move(10,1);
     bg.setPosition(0,0);
     w1.movePixel(p1);
     //rectangle.setOutlineColor(sf::Color::Blue);
     isActive = 1;
     window.draw(rectangle);
}
}
else
{
    rectangle.move(0,1);
    window.draw(bg);
    window.draw(rectangle);
    
}


   w1.drawBox();
   //window.draw(rectangle);
   window.display();
}
    
}