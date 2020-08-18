
#ifndef LOADOUT_H
#define LOADOUT_H
#include <windows.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
//#include <sql.h>
//#include <sqlext.h>
//#include <sqltypes.h>

using namespace std;

const int MAX = 6;
const int MAX_LOADOUTS = 50;
//const int minItemRating;
const int maxCost = 800;
const int minRating = 2400;
const int minDPS = 200;
const int minfRes = 190;
const int mineRes = 190;
const int mincRes = 190;
const int minchRes = 90;
const int maxfRes = 250;
const int maxeRes = 250;
const int maxcRes = 250;
const int maxchRes = 175;
const int minHp = 650;
const int minArmor = 2000;
const int minEs = 0;
const float fResWeight = 1.7;
const float eResWeight = 1.7;
const float cResWeight = 1.7;
const float chResWeight = 2.1;
const float hpWeight = 1;
const float armorWeight = .15;
const float esWeight = 0;
const float dpsWeight = 200;

class Item {
public:
	Item(string newName, string id, float newCost, int newRating);
	string getName();
	string getId();
	float getCost();
	int getRating();
	void setName(string newName);
	void setId(string newName);
	void setCost(float newCost);
	void setRating(int newRating);
protected:
	string name;
	string id;
	float cost;
	int rating;
};

class Weapon : public Item {
public:
	friend ofstream& operator << (ofstream& os, Weapon& weapon);
	Weapon(string name = "Unknown Weapon", string id = "", float cost = 0.0, int dmg = 0, double speed = 0.0, double dps = 0, int rating = 0);
	int getDamage();
	double getSpeed();
	double getDPS();
	void setDamage(int& newDamage);
	void setSpeed(double& newSpeed);
	void calcRating();
	void calcDPS();
private:
	int damage;
	double speed;
	double DPS;
};

class Armor : public Item {
	friend ofstream& operator << (ofstream& os, Armor& armor);
public:
	Armor(string name = "Unknown Armor", string id = "", float cost = 0.0, int fres = 0, int eres = 0, int cres = 0, int chres = 0, int arm = 0, int health = 0, int shield = 0, int rating = 0);
	int getfRes();
	int geteRes();
	int getcRes();
	int getchRes();
	int getArmor();
	int getHp();
	int getEs();
	void setfRes(int& newFRES);
	void seteRes(int& newERES);
	void setcRes(int& newCRES);
	void setchRes(int& newCHRES);
	void setArmor(int& newArmor);
	void setHp(int& newHp);
	void setEs(int& newEs);
	void calcRating();
private:
	int fRes;
	int eRes;
	int cRes; //cold resistance
	int chRes;
	int armor;
	int hp;
	int es;
};

class Jewlry : public Item {
	friend ofstream& operator << (ofstream& os, Jewlry& jewl);
public:
	Jewlry(string name = "Unknown Jewlry", string id = "", float cost = 0.0, int fres = 0, int eres = 0, int cres = 0, int chres = 0, int arm = 0, int health = 0, int shield = 0, int rating = 0);
	int getfRes();
	int geteRes();
	int getcRes();
	int getchRes();
	int getArmor();
	int getHp();
	int getEs();
	void setfRes(int& newFRES);
	void seteRes(int& newERES);
	void setcRes(int& newCRES);
	void setchRes(int& newCHRES);
	void setArmor(int& newArmor);
	void setHp(int& newHealth);
	void setEs(int& newShield);
	void calcRating();
private:
	int fRes;
	int eRes;
	int cRes; //cold resistance
	int chRes;
	int armor;
	int hp;
	int es;
};

/*class weaponList{

};*/

class Loadout {
public:
	Loadout();
	void addWeapon(Weapon*& _weapon);
	void addHelmet(Armor*& _helmet);
	void addBoots(Armor*& _boots);
	void addGloves(Armor*& _gloves);
	void addChest(Armor*& _chest);
	void addRing1(Jewlry*& _ring1);
	void addRing2(Jewlry*& _ring2);
	void addBelt(Jewlry*& _belt);
	void addAmulet(Jewlry*& _amulet);
	void calcRating();
	void calcDPS();
	void calcStats();
	bool meetsMinimums();
	void printLoadout(ofstream& fout);
	int getItems();
	int getRating();
	int getfRes();
	int geteRes();
	int getcRes();
	int getchRes();
	int getArmor();
	int getHp();
	int getEs();
	int getCost();
	double getDPS();
private:
	Weapon* weapon;
	Armor* chest;
	Armor* gloves;
	Armor* boots;
	Armor* helmet;
	Jewlry* ring1;
	Jewlry* ring2;
	Jewlry* belt;
	Jewlry* amulet;
	int totalRating;
	int numItems;
	int rating;
	int cost;
	int fRes;
	int eRes;
	int cRes; //cold resistance
	int chRes;
	int armor;
	int hp;
	int es;
	double DPS;
};

class Pool {
	friend ofstream& operator << (ofstream& os, Pool& pool);
public:
	Pool();
	void readItems();
	template <class t>
	void addItem(Pool& pool, string type, int& l, t& tempItem);
	void printPool(ofstream& fout);
	void bestLoadouts(Loadout*& loadouts);
	int searchRingHash(unsigned long long hash);
	int searchTwiceHash(unsigned long long hash);
	unsigned long long getHash(string id, string id2);
	void getRepeatHash();
private:
	Weapon* weaponPool[MAX];
	Armor* helmetPool[MAX];
	Armor* glovesPool[MAX];
	Armor* bootsPool[MAX];
	Armor* chestPool[MAX];
	Jewlry* ring1Pool[MAX];
	Jewlry* ring2Pool[MAX];
	Jewlry* amuletPool[MAX];
	Jewlry* beltPool[MAX];
	vector<unsigned long long> ringHash;
	vector<unsigned long long> twiceHash;
};

void printLoadouts(Loadout loadouts[], ofstream& fout);

template <class t>
void Pool::addItem(Pool& pool, string type, int& l, t& tempItem)
{
	int m;
	if constexpr (is_same<t, Armor>())
	{
		if (type == "chest") {
			m = l;
			while (m > 0 && chestPool[m - 1]->getRating() < tempItem.getRating())
			{
				*chestPool[m] = *chestPool[m - 1];
				m--;
			}
			*chestPool[m] = tempItem;
		}
		else if (type == "gloves") {
			m = l;
			while (m > 0 && glovesPool[m - 1]->getRating() < tempItem.getRating())
			{
				*glovesPool[m] = *glovesPool[m - 1];
				m--;
			}
			*glovesPool[m] = tempItem;
		}
		else if (type == "boots") {
			m = l;
			while (m > 0 && bootsPool[m - 1]->getRating() < tempItem.getRating())
			{
				*bootsPool[m] = *bootsPool[m - 1];
				m--;
			}
			*bootsPool[m] = tempItem;
		}
		else if (type == "helmet") {
			m = l;
			while (m > 0 && helmetPool[m - 1]->getRating() < tempItem.getRating())
			{
				*helmetPool[m] = *helmetPool[m - 1];
				m--;
			}
			*helmetPool[m] = tempItem;
		}
	}
	else if constexpr (is_same<t, Jewlry>()) {
		if (type == "amulet") {
			m = l;
			while (m > 0 && amuletPool[m - 1]->getRating() < tempItem.getRating())
			{
				*amuletPool[m] = *amuletPool[m - 1];
				m--;
			}
			*amuletPool[m] = tempItem;
		}
		else if (type == "ring1") {
			m = l;
			while (m > 0 && ring1Pool[m - 1]->getRating() < tempItem.getRating())
			{
				*ring1Pool[m] = *ring1Pool[m - 1];
				m--;
			}
			*ring1Pool[m] = tempItem;
		}
		else if (type == "ring2") {
			m = l;
			while (m > 0 && ring2Pool[m - 1]->getRating() < tempItem.getRating())
			{
				*ring2Pool[m] = *ring2Pool[m - 1];
				m--;
			}
			*ring2Pool[m] = tempItem;
		}
		else if (type == "belt") {
			m = l;
			while (m > 0 && beltPool[m - 1]->getRating() < tempItem.getRating())
			{
				*beltPool[m] = *beltPool[m - 1];
				m--;
			}
			*beltPool[m] = tempItem;
		}
	}
}
#endif