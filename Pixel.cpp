#include "Pixel.h"

int Pixel::getID_list()
{
    return ID_list;
}

/* int Pixel::getType()
     {
        return Type;
    }
 */
void Pixel::setCoords(int X, int Y)
{
    this->posX = X;
    this->posY = Y;
}

/* int Pixel::getposX()
    {
        return posX;
    }

int Pixel::getposY()
    {
        return posY;
    } */
void Pixel::setID(int N)
{
    ID = ID + N;
}
int Pixel::getID()
{
    return ID;
}
void Pixel::movePixel(std::vector<std::vector<std::shared_ptr<Pixel>>> &box)
{
    box[posY][posX]->getID_list();
}

Pixel::Pixel(const std::string &Name_, int ID_l, int Type_, int posX_, int posY_) : Name{Name_}, ID_list{ID_l}, Type{Type_}, posX{posX_}, posY{posY_}
{
}
Pixel::Pixel(const Pixel &other) : Name{other.Name}, ID_list{other.ID_list}, Type{other.Type}, posX{other.posX}, posY{other.posY} {}
Pixel &Pixel::operator=(const Pixel &other)
{
    Name = other.Name;
    ID_list = other.ID_list;
    Type = other.Type;
    posX = other.posX;
    posY = other.posY;
    return *this;
}
int Pixel::ID = 0;

void Powder::movePixel(std::vector<std::vector<std::shared_ptr<Pixel>>> &box)
{
    int move = rand() % 2;
    int posX_ = this->posX;
    int posY_ = this->posY;
    std::shared_ptr<Pixel> P = box[posY_][posX_];
    // P->setCoords(posX_,posY_);
    if (box[posY_][posX_]->getID_list() == 2 && box[posY_ + 1][posX_]->getID_list() == 0)
    {

        box[posY_ + 1][posX_] = P;
        box[posY_][posX_] = std::make_shared<Pixel>("VOID", 0, 0, posX_, posY_);

        P->setCoords(posX_, posY_ + 1);
    }
    if (box[posY_][posX_]->getID_list() == 2 && box[posY_ + 1][posX_]->getID_list() == 3)
    {
        box[posY_ + 1][posX_] = P;
        box[posY_][posX_] = std::make_shared<Liquid>("WATR", 3, 2, posX_, posY_);

        P->setCoords(posX_, posY_ + 1);
    }
    if (box[posY_][posX_]->getID_list() == 2 && box[posY_ + 1][posX_]->getID_list() != 1)
    {
        if (move == 1)
        {
            if (box[posY_ + 1][posX_ + 1]->getID_list() == 0)
            {
                box[posY_ + 1][posX_ + 1] = P;
                box[posY_][posX_] = std::make_shared<Pixel>("VOID", 0, 0, posX_, posY_);
                P->setCoords(posX_ + 1, posY_ + 1);
            }
        }
        else if (box[posY_ + 1][posX_ - 1]->getID_list() == 0)
        {
            box[posY_ + 1][posX_ - 1] = P;
            box[posY_][posX_] = std::make_shared<Pixel>("VOID", 0, 0, posX_, posY_);
            P->setCoords(posX_ + 1, posY_ - 1);
        }
    }
}

void Liquid::movePixel(std::vector<std::vector<std::shared_ptr<Pixel>>> &box)

{
    int move = rand() % 2;
    int posX_ = this->posX;
    int posY_ = this->posY;
    std::shared_ptr<Pixel> P = box[posY_][posX_];
    // P->setCoords(posX_,posY_);
    if (box[posY_ + 1][posX_]->getID_list() == 0)
    {
        box[posY_ + 1][posX_] = P;
        box[posY_][posX_] = std::make_shared<Pixel>("VOID", 0, 0, posX_, posY_);

        P->setCoords(posX_, posY_ + 1);
    }
    if (box[posY_][posX_]->getID_list() == 3 && box[posY_ + 1][posX_]->getID_list() != 0)
    {
        if (move == 1)
        {
            if (box[posY_][posX_ + 1]->getID_list() == 0)
            {

                box[posY_][posX_ + 1] = P;
                box[posY_][posX_] = std::make_shared<Pixel>("VOID", 0, 0, posX_, posY_);
            }
            P->setCoords(posX_ + 1, posY_);
        }
        else
        {
            if (box[posY_][posX_ - 1]->getID_list() == 0)
            {

                box[posY_][posX_ - 1] = P;
                box[posY_][posX_] = std::make_shared<Pixel>("VOID", 0, 0, posX_, posY_);
            }
            P->setCoords(posX_ - 1, posY_);
        }
    }
}

void Solid::transformPixel(std::shared_ptr<Pixel> &P, std::vector<std::vector<std::shared_ptr<Pixel>>> &box)
{
    int melt = rand() % 4;
    if (getID_list() == 5)
    {
        if (melt == 3)
        {
            box[this->posY][this->posX] = std::make_shared<Liquid>("WATR", 3, 2, this->posX, this->posY);
            P = std::make_shared<Liquid>("WATR", 3, 2, this->posX, this->posY);
        }
    }
}
