#include<iostream>
#include<string>
using namespace std;

//used the main template from the assignment document and referenced the example code
class GameCharacter
{
protected:
    double health;
    string name;
    int level;

public:
    //constructors
    GameCharacter();
    GameCharacter(double, string, int);

    //accessors
    double getHealth(){return health;}
    string getName(){return name;}
    int getLevel(){return level;}

    //mutators
    void setHealth(double newHealth){health = newHealth;}

    //perform attack function
    double virtual PerformUniqueAttack();

};

class Knight : public GameCharacter
{

public:
    //constructors
    Knight();
    Knight(string, double, int, string);

    //getters
    string getArmor(){return armorType;}

    //mutators
    void setArmor(string newArmor){armorType = newArmor;}

    //perform attack function
    double virtual PerformUniqueAttack();

private:
    string armorType;

};


class Mage : public GameCharacter
{

public:
    //constructor
    Mage();
    Mage(string, double, int, double);

    //getters
    double getMana(){return mana;}

    //setter
    void setMana(double newMana){mana = newMana;}

    //perform attack function
    double virtual PerformUniqueAttack();

private:
    double mana;

};

//used the main template from the assignment document
int main()
{
    GameCharacter* characters[4];
    characters[0] = new Knight("Arthur", 100.0, 10, "chest plate");
    characters[1] = new Mage("Merlin", 80.0, 12, 200.0);
    characters[2] = new Knight("Lancelot", 90.0, 8, "helmet");
    characters[3] = new Mage("Gandalf", 95.0, 15, 300.0);

    for (int i = 0; i < 4; i++) 
    {
        characters[i]->PerformUniqueAttack();
    }
    //delete all characters
    return 0;
}


GameCharacter::GameCharacter()
{
    health = 0.0;
    name = "";
    level = 0;
}

GameCharacter::GameCharacter(double setHealth, string setName, int setLevel)
{
    health = setHealth;
    name = setName;
    level = setLevel;
}

double GameCharacter::PerformUniqueAttack()
{
    cout<< name <<" is nothing but a mere mortal, there is no unique attack, you run and hide";

    return health;
}

Knight::Knight()
{
    health = 0.0;
    name = "";
    level = 0;
    armorType = "";
}

Knight::Knight(string setName, double setHealth, int setLevel, string setArmor)
{
    health = setHealth;
    name = setName;
    level = setLevel;
    armorType = setArmor;
}

double Knight::PerformUniqueAttack()
{
    cout<< name <<" performs a devastating sword slash in his "<< armorType <<", dealing "<<level<<" damage!"<<endl;

    return health;
}

Mage::Mage()
{
    health = 0.0;
    name = "";
    level = 0;
    mana = 0.0;
}

Mage::Mage(string setName, double setHealth, int setLevel, double setMana)
{
    health = setHealth;
    name = setName;
    level = setLevel;
    mana = setMana;
}

double Mage::PerformUniqueAttack()
{
    cout<< name << " the Mage casts a powerful fireball using "<<mana<<" mana, dealing "<<level<<" damage!"<<endl;

    return health;
}