#include<iostream>
#include<string>
#include<utility>
//#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

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

//weight doesn't matter for static solids (is 0?)
//type dictates how pixels move
//density affects how pixels layer (e.g a liquid/powder pixel with density of 2 will go under a liquid/powder pixel with density of 1)
//temp_init is the initial temperature of the pixel upon spawn (celsius)
class PixelBehaviour {
    private:
    int type;
    float weight;
    int vx, vy;
    int temp;
    int gravity;

    public:
    //PixelBehaviour(int type_, int weight_, int temp_, int gravity_) : type{type_}, weight{weight_}, temp{temp_}, gravity{gravity_}
    PixelBehaviour(int type_, float weight_, int temp_) : type{type_}, weight{weight_}, temp{temp_}
    {
        std::cout<<"Constructor Initializare PixelBehaviour"<<std::endl;
        //std::cout<<"Type "<<type<<std::endl;
    }
    friend std::ostream& operator<<(std::ostream& os, const PixelBehaviour& pxb)
    {
        os<<"Type PB " << pxb.type <<"\n";
        return os;
    }
    void SetPixel() {}
    void MovePixel() {}
    void TransformPixel() {}


};
class Pixel {
    private:
    std::string Name;
    int ID;
    int Type;
    float Weight;
    int Density;
    int Temp_init;
    int colour; //change to sfml colour 
    bool Can_burn;
    bool Can_melt;
    bool Can_ignite;
    PixelBehaviour PB{this->Type, this->Weight, this->Temp_init};
    public:
    // to add PixelBehaviour to Pixel constructor
    Pixel(std::string Name_, int ID_, int Type_) : Name{Name_}, ID{ID_}, Type{Type_}{
        std::cout<<"Constructor initializare Pixel"<<std::endl;
        //std::cout<<"Created Pixel "<< Name <<" With ID "<< ID << " Type " << Type << " And Behaviour " << std::endl;
    }
    Pixel(const Pixel& other): Name{other.Name}, ID{other.ID}, Type{other.Type} {
        std::cout<<"Constructor copiere Pixel"<<std::endl;
         //std::cout<<"Copied Pixel "<< Name <<" With ID "<< ID << " Type " << Type << " And Behaviour " << std::endl;
    }
    Pixel& operator=(const Pixel& other) {
        Name = other.Name;
        ID = other.ID;
        Type = other.Type;
        std::cout<<"Operator= copiere Pixel"<<std::endl;
        return *this;
    }
    /* int getID()

    {
        return ID;
    }
    int getType()
    {
        return Type;
    } */
    ~Pixel()
    {
        std::cout <<"Destructor Pixel"<<std::endl;
    }
    friend std::ostream& operator<<(std::ostream& os, const Pixel& px){
        os << "Type " << px.Type << " ID " << px.ID << "\n";
        return os;
    }
}; 

 class World{

    private:
    std::vector<std::vector<Pixel>> box;
    int SizeX;
    int SizeY;
    bool has_Border;
    int Gravity;

    void Create(int SizeX, int SizeY)
    {  
        //std::cout<<"Create World "<<SizeX <<" x "<<SizeY<<std::endl; 
        this->SizeX=SizeX;
        this->SizeY=SizeY;
        /*for(int i = 0; i<SizeY; i++){
            std::vector<Pixel> v1;

            for(int j = 0; j<SizeX; j++)
            {
                v1.push_back(0);
            }
            this->box.push_back(v1); 
        } */
    }
    public:
    World(int X_, int Y_) {
        std::cout<<"Constructor initializare World"<<std::endl; Create(X_,Y_);
        }
/*     void getWorld()
    {
        
                std::cout<<"------------------------"<<std::endl;
        for(int i = 0; i<box.size(); i++)
        {
            for(int j = 0; j< box[i].size(); j++)
            {
               std::cout<<box[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        
                std::cout<<"------------------------"<<std::endl;
    }
    void SetPixel(int ID, int posX, int posY, int Type)
    {   
       
        box[posY][posX] = Type;
        if(Type!=4 && Type!=0)
        {   
            //IMPROVE EDGE DETECTION
            
            getWorld();
            if(posY<=SizeY-1){
            MovePixel(ID, posX, posY, Type);
            }
           
            
            
        }
         
    }
/*     void MovePixel(int ID, int posX, int posY, int Type)
    {

        if(Type==1) //POWDER
        {
            // ADD posX and formula with VX
            if(posY<SizeY-1){
            posY = posY + 1;  //ADD vy formula
        
            
            SetPixel(ID, posX, posY-1, 0);
            SetPixel(ID, posX, posY, Type);
            }
            else
            if(posY==SizeY-1)
            {        
            SetPixel(ID, posX, posY, Type);
            }
            
            
        }
    }    */
    friend std::ostream& operator<<(std::ostream& os, const World& w)
    {
        os<<"Size World " << w.SizeX << " x " <<w.SizeY <<"\n";
        return os;
    }
};

// buttons for elements
class Elem_Button{
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
        std::cout<<"Constructor initializare Elem_Button"<<std::endl;
    }
    friend std::ostream& operator<<(std::ostream& os, const Elem_Button& elem_b)
    {
        os<<"Type elem " << elem_b.content <<"\n";
        return os;
    }
    void onLeftClick() {} // Set LMB to spawn selected box' pixel
    void onRightClick() {}// Set RMB to spawn selected box' pixel
    void onMiddleClick() {}// Set MMB to spawn selected box' pixel

};



int main()
{
    //sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    World w1{5,5};
    std::cout<<w1;
    Pixel p1{"FIRST",1,2};
    std::cout<<p1;
    PixelBehaviour pb1{1,2,1};
    std::cout<<pb1;
    Pixel p2{p1};
    Pixel p3 = p1;
    p2 = p3;
    Elem_Button e1{p1};
    std::cout<<e1;
    std::cout<<"6-------------6"<<std::endl;
    //w1.SetPixel(p1.getID(),0,0,p1.getType());
    //w1.getWorld();
    //w1.getWorld();
   // w1.SpawnPixel(TYPE,posX,posY,LOC);
   // w1.Update();
    return 0;
// Create the main window

    // Load a sprite to displ 
    // Start the game loop
  /* while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        window.display();
    }
    return EXIT_SUCCESS; */
    
}