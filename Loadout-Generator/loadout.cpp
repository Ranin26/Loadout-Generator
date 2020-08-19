#include "loadout.h"
#include "database.h"

Item::Item(string newName, string id, float newCost, int newRating)
{
	name = newName;
	cost = newCost;
	rating = newRating;
}

string Item::getName(){
	return name;
}
string Item::getId() {
	return id;
}
float Item::getCost(){
	return cost;
}
int Item::getRating(){
	return rating;
}

void Item::setName(string newName){
	name = newName;
}
void Item::setId(string newId)
{
	id = newId;
}
void Item::setCost(float newCost){
	cost = newCost;
}
void Item::setRating(int newRating){
	rating = newRating;
}

Weapon::Weapon(string name, string id, float cost, int dmg, double spd, double dps, int rating) : Item(name, id, cost, rating)
{
	damage = dmg;
	speed = spd;
	DPS = dps;
}

ofstream& operator << (ofstream& os, Weapon& weapon){
	os	<< weapon.getName() << "  " << "Chaos " << weapon.getCost() << "   Rating:" << weapon.getRating() << "\n"
		<< "\t" << "Damage: " << weapon.getDamage() << "   Attack Speed: " << weapon.getSpeed() << "   DPS: " << weapon.getDPS() << "\n\n";
	return os;
}

int Weapon::getDamage(){
	return damage;
}
double Weapon::getSpeed(){
	return speed;
}
double Weapon::getDPS(){
	return speed*damage;
}

void Weapon::setDamage(int &newDamage){
	damage = newDamage;
	calcDPS();
}
void Weapon::setSpeed(double &newSpeed){
	speed = newSpeed;
	calcDPS();
}

void Weapon::calcRating()
{
	rating = DPS * dpsWeight;
}

void Weapon::calcDPS()
{
	DPS = damage * speed;
}
//Armor

Armor::Armor(string name, string id, float cost, int fres, int eres, int cres, int chres, int arm, int health, int shield, int rating) : Item(name, id, cost, rating)
{
	fRes = fres;
	eRes = eres;
	cRes = cres;
	chRes = chres;
	armor = arm;
	hp = health;
	es = shield;
}
/*
Armor &Armor::operator =(Armor &_armor)
{
	this->armor = _armor.armor;
	this->hp = _armor.hp;
	this->fRes = _armor.fRes;
	this->eRes = _armor.eRes;
	this->chRes = _armor.chRes;
	this->cRes = _armor.cRes;
	this->cost = _armor.cost;
	this->es = _armor.es;
	this->name = _armor.name;
	this->rating = _armor.rating;
}*/

ofstream& operator << (ofstream& os, Armor& armor)
{
	os << armor.getName() << "  " << "Chaos " << armor.getCost() << "   Rating:" << armor.getRating() << "\n"
		<< "\t" << "Health: " << armor.getHp() << "   Armor: " << armor.getArmor() << "   Shield: " << armor.getEs() << "\n"
		<< "\t" << "Fire Res:" << armor.getfRes() << " | Elec Res:" << armor.geteRes() << " | Cold Res:" << armor.getcRes() << " | Chaos Res:" << armor.getchRes() << "\n\n";
	return  os;
}

int Armor::getfRes(){
	return fRes;
}
int Armor::geteRes(){
	return eRes;
}
int Armor::getcRes(){
	return cRes;
}
int Armor::getchRes(){
	return chRes;
}
int Armor::getArmor(){
	return armor;
}
int Armor::getHp(){
	return hp;
}
int Armor::getEs(){
	return es;
}

void Armor::setfRes(int &newFRES){
	fRes = newFRES;
}
void Armor::seteRes(int &newERES){
	eRes = newERES;
}
void Armor::setcRes(int &newCRES){
	cRes = newCRES;
}
void Armor::setchRes(int &newCHRES){
	chRes = newCHRES;
}
void Armor::setArmor(int &newArmor){
	armor = newArmor;
}
void Armor::setHp(int &newHp){
	hp = newHp;
}
void Armor::setEs(int &newEs){
	es = newEs;
}

void Armor::calcRating()
{
	rating = (eRes + fRes + cRes) * eResWeight + chRes * cResWeight + (armor * armorWeight) + hp + es;
}


Jewlry::Jewlry(string name, string id, float cost, int fres, int eres, int cres, int chres, int arm, int health, int shield, int rating) : Item(name, id, cost, rating)
{
	fRes = fres;
	eRes = eres;
	cRes = cres;
	chRes = chres;
	armor = arm;
	hp = health;
	es = shield;
}

ofstream& operator << (ofstream& os, Jewlry& jewl)
{
	os << jewl.getName() << "  " << "Chaos " << jewl.getCost() << "   Rating:" << jewl.getRating() << "\n"
		<< "\t" << "Health: " << jewl.getHp() << "   Armor: " << jewl.getArmor() << "   Shield: " << jewl.getEs() << "\n"
		<< "\t" << "Fire Res:" << jewl.getfRes() << " | Elec Res:" << jewl.geteRes() << " | Cold Res:" << jewl.getcRes() << " | Chaos Res:" << jewl.getchRes() << "\n\n";
	return os;
}

int Jewlry::getfRes(){
	return fRes;
}
int Jewlry::geteRes(){
	return eRes;
}
int Jewlry::getcRes(){
	return cRes;
}
int Jewlry::getchRes(){
	return chRes;
}
int Jewlry::getArmor(){
	return armor;
}
int Jewlry::getHp(){
	return hp;
}
int Jewlry::getEs(){
	return es;
}

void Jewlry::setfRes(int &newFRES){
	fRes = newFRES;
}
void Jewlry::seteRes(int &newERES){
	eRes = newERES;
}
void Jewlry::setcRes(int &newCRES){
	cRes = newCRES;
}
void Jewlry::setchRes(int &newCHRES){
	chRes = newCHRES;
}
void Jewlry::setArmor(int &newArmor){
	armor = newArmor;
}
void Jewlry::setHp(int &newHp){
	hp = newHp;
}
void Jewlry::setEs(int &newEs){
	es = newEs;
}

void Jewlry::calcRating()
{
	rating = (eRes + fRes + cRes) * eResWeight + chRes * chResWeight + (armor * armorWeight) + hp + es;
}

Loadout::Loadout() 
{
	totalRating = 0;
	numItems = 0;
	rating = 0;
	fRes = 0;
	eRes = 0;
	cRes = 0; //cold resistance
	chRes = 0;
	armor = 0;
	hp = 0;
	es = 0;
	DPS = 0.0;
	cost = 0;
	weapon = NULL;
	chest = NULL;
	gloves = NULL;
	helmet = NULL;
	boots = NULL;
	amulet = NULL;
	ring1 = NULL;
	ring2 = NULL;
	belt = NULL;
}
double Loadout::getDPS(){
	return DPS;
}
int Loadout::getItems(){
	return numItems;
}
int Loadout::getRating(){
	return totalRating;
}
int Loadout::getfRes() {
	return fRes;
}
int Loadout::geteRes() {
	return eRes;
}
int Loadout::getcRes() {
	return cRes;
}
int Loadout::getchRes() {
	return chRes;
}
int Loadout::getArmor() {
	return armor;
}
int Loadout::getHp() {
	return hp;
}
int Loadout::getEs() {
	return es;
}
int Loadout::getCost() {
	return cost;
}
void Loadout::addWeapon(Weapon *&_weapon){
	weapon = _weapon;
	weapon->calcDPS();
	weapon->calcRating();
}
void Loadout::addHelmet(Armor *&_helmet){
	helmet = _helmet;
	helmet->calcRating();
}
void Loadout::addBoots(Armor *&_boots){
	boots = _boots;
	boots->calcRating();
}
void Loadout::addGloves(Armor *&_gloves){
	gloves = _gloves;
	gloves->calcRating();
}
void Loadout::addChest(Armor *&_chest){
	chest = _chest;
	chest->calcRating();
}
void Loadout::addRing1(Jewlry *&_ring1){
	ring1 = _ring1;
	ring1->calcRating();
}
void Loadout::addRing2(Jewlry *&_ring2){
	ring2 = _ring2;
	ring2->calcRating();
}
void Loadout::addBelt(Jewlry *&_belt){
	belt = _belt;
	belt->calcRating();
}
void Loadout::addAmulet(Jewlry *&_amulet){
	amulet = _amulet;
	amulet->calcRating();
}
void Loadout::calcRating(){
	double res;
	//(eRes + fRes + cRes) * 1.5 + chRes * 2 + (armor * .5) + hp + es;
	totalRating = hp + es + DPS + (armor * ((armor + 5 * minArmor) / (6 * minArmor))) * armorWeight;

	fRes < maxfRes ? res = fRes : res = maxfRes;
	totalRating += res * res / maxfRes * fResWeight;

	eRes < maxeRes ? res = eRes : res = maxeRes;
	totalRating += res * res / maxeRes * eResWeight;

	cRes < maxcRes ? res = cRes : res = maxcRes;
	totalRating += res * res / maxcRes * cResWeight;

	chRes < maxchRes ? res = chRes : res = maxchRes;
	totalRating += res * (2 * maxchRes + res) * chResWeight /(3 * maxchRes);
}
void Loadout::calcDPS(){
	DPS = weapon->getDPS();
}
void Loadout::calcStats() {
	fRes = chest->getfRes() + helmet->getfRes() + boots->getfRes() + gloves->getfRes() + belt->getfRes() + amulet->getfRes() + ring1->getfRes() + ring2->getfRes();
	eRes = chest->geteRes() + helmet->geteRes() + boots->geteRes() + gloves->geteRes() + belt->geteRes() + amulet->geteRes() + ring1->geteRes() + ring2->geteRes();
	cRes = chest->getcRes() + helmet->getcRes() + boots->getcRes() + gloves->getcRes() + belt->getcRes() + amulet->getcRes() + ring1->getcRes() + ring2->getcRes();
	chRes = chest->getchRes() + helmet->getchRes() + boots->getchRes() + gloves->getchRes() + belt->getchRes() + amulet->getchRes() + ring1->getchRes() + ring2->getchRes();
	armor = chest->getArmor() + helmet->getArmor() + boots->getArmor() + gloves->getArmor() + belt->getArmor() + amulet->getArmor() + ring1->getArmor() + ring2->getArmor();
	hp = chest->getHp() + helmet->getHp() + boots->getHp() + gloves->getHp() + belt->getHp() + amulet->getHp() + ring1->getHp() + ring2->getHp();
	es = chest->getEs() + helmet->getEs() + boots->getEs() + gloves->getEs() + belt->getEs() + amulet->getEs() + ring1->getEs() + ring2->getEs();
	cost = chest->getCost() + helmet->getCost() + boots->getCost() + gloves->getCost() + belt->getCost() + amulet->getCost() + ring1->getCost() + ring2->getCost();
}
bool Loadout::meetsMinimums()
{
	//totalRating < minRating || 
	if (cost > maxCost || fRes < minfRes || eRes < mineRes || cRes < mincRes || chRes < minchRes || armor < minArmor || hp < minHp || es < minEs)
		return false;
	else
		return true;
}
void Loadout::printLoadout(ofstream& fout)
{
	if (weapon && helmet && chest && gloves && boots && amulet && belt && ring1 && ring2)
	{
		fout << "Rating: " << totalRating << "  Cost: " << cost << "   DPS: " << DPS
			<< "\n\tHp: " << hp << "   Armor: " << armor << "   Shield: " << es
			<< "\n\tFire Res: " << fRes << "  Cold Res: " << cRes << "  Elec Res: " << eRes << "  Chaos Res: " << chRes << "\n\t"
			<< "w: " << weapon->getName() << " | " << "h: " << helmet->getName() << " | " << "c: " << chest->getName() << " | "
			<< "g: " << gloves->getName() << " | " << "b: " << boots->getName() << " | " << "a: " << amulet->getName() << " | "
			<< "r1: " << ring1->getName() << " | " << "r2: " << ring2->getName() << " | " << "b: " << belt->getName() << "\n\n";
	}
}

Pool::Pool()
{
	for (int i = 0; i < MAX; i++)
	{
		weaponPool[i] = new Weapon;
		helmetPool[i] = new Armor;
		glovesPool[i] = new Armor;
		bootsPool[i] = new Armor;
		chestPool[i] = new Armor;
		ring1Pool[i] = new Jewlry;
		ring2Pool[i] = new Jewlry;
		amuletPool[i] = new Jewlry;
		beltPool[i] = new Jewlry;
	}
	ringHash.reserve(MAX * MAX);
	twiceHash.reserve((MAX * MAX+1)/2);
}

int Pool::searchRingHash(unsigned long long hash)
{
	for (int i = 0; i < ringHash.size(); i++)
	{
		if (ringHash[i] == hash)
		{
			//cout << hash << endl;
			return 1;
		}
	}
	ringHash.push_back(hash);
	return 0;
}

int Pool::searchTwiceHash(unsigned long long hash)
{
	for (int i = 0; i < ringHash.size(); i++)
	{
		if (ringHash[i] == hash)
		{
			//cout << hash << endl;
			return 1;
		}
	}
	return 0;
}

void Pool::getRepeatHash()
{
	int hash;
	for (int i = 0; i < MAX && ring1Pool[i]->getId() != ""; i++)
	{
		for (int j = 0; j < MAX && ring2Pool[j]->getId() != ""; j++)
		{
			hash = getHash(ring1Pool[i]->getId(), ring2Pool[j]->getId());
			if (searchRingHash(hash))
			{
				twiceHash.push_back(hash);
			} else {
				ringHash.push_back(hash);
			}
		}
	}
}
unsigned long long Pool::getHash(string id, string id2)
{
	int seed = 5, i;
	unsigned long long hash = 0, hash2 = 0;
	for (i = 0; i < id.length(); i++)
	{
		hash = (hash * seed) + id[i];
	}
	for (i = 0; i < id2.length(); i++)
	{
		hash2 = (hash2 * seed) + id2[i];
	}
	return hash + hash2;
}
/*
ofstream& operator << (ofstream& os, Pool& pool)
{
	int i;
	for (i = 0; i < MAX; i++)
		os << pool.weaponPool[i];
	os << "\n";
	for (i = 0; i < MAX; i++)
		os << pool.helmetPool[i];
	os << "\n";
	for (i = 0; i < MAX; i++)
		os << pool.glovesPool[i];
	os << "\n";
	for (i = 0; i < MAX; i++)
		os << pool.bootsPool[i];
	os << "\n";
	for (i = 0; i < MAX; i++)
		os << pool.chestPool[i];
	os << "\n";
	for (i = 0; i < MAX; i++)
		os << pool.ring1Pool[i];
	os << "\n";
	for (i = 0; i < MAX; i++)
		os << pool.ring2Pool[i];
	os << "\n";
	for (i = 0; i < MAX; i++)
		os << pool.amuletPool[i];
	os << "\n";
	for (i = 0; i < MAX; i++)
		os << pool.beltPool[i];
	os << "\n";
	return os;
}*/

void Pool::readItems()
{
	ifstream fin;
	fin.open("items.txt");

	if (!fin)
	{
		cerr << "Can't open file.";
		system("pause");
		exit(1);
	}

	string name;
	float cost;
	int damage, i;
	double speed;
	int fRes, cRes, eRes, chRes, hp, armor, es, j;
	Weapon tempWeapon;
	Armor tempChest;
	Armor tempGloves;
	Armor tempBoots;
	Armor tempHelmet;
	Jewlry tempRing1;
	Jewlry tempRing2;
	Jewlry tempBelt;
	Jewlry tempAmulet;

	MYSQL* conn;
	dbConnect(conn);

	const char* query = new char[512];
	stringstream ss;
	string str; 
	MYSQL_ROW row;
	MYSQL_RES* res;

	query = "Select * from weapons";

	if (mysql_query(conn, query))
	{
		cout << "Weapon Select failed \n";
		system("pause");
		exit(1);
	}
	else {
		i = 0;
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)) && i < MAX_LOADOUTS)
		{
			name = row[1];
			cost = stof(row[2]);
			damage = stoi(row[4]);
			speed = stod(row[5]);

			tempWeapon.setName(name);
			tempWeapon.setCost(cost);
			tempWeapon.setDamage(damage);
			tempWeapon.setSpeed(speed);
			tempWeapon.calcRating();
			
			j = i;
			while (j > 0 && weaponPool[j - 1]->getRating() < tempWeapon.getRating())
			{
				*weaponPool[j] = *weaponPool[j-1];
				j--;
			}
			*weaponPool[j]=tempWeapon;
			i++;
		}
		cout << "Weapon Read successful\n";
	}

	query = "Select * from helmets";

	if (mysql_query(conn, query))
	{
		cout << "Helmet Select failed \n";
		system("pause");
		exit(1);
	}
	else {
		i = 0;
		res = mysql_store_result(conn);
		while((row = mysql_fetch_row(res)) && i < MAX_LOADOUTS)
		{
			name = row[1];
			cost = stof(row[2]);
			fRes = stoi(row[4]);
			eRes = stod(row[5]);
			cRes = stod(row[6]);
			chRes = stod(row[7]);
			armor = stod(row[8]);
			hp = stod(row[9]);
			tempHelmet.setName(name);
			tempHelmet.setCost(cost);
			tempHelmet.setfRes(fRes);
			tempHelmet.seteRes(eRes);
			tempHelmet.setcRes(cRes);
			tempHelmet.setchRes(chRes);
			tempHelmet.setArmor(armor);
			tempHelmet.setHp(hp);
			tempHelmet.calcRating();
			j = i;
			while (j > 0 && helmetPool[j - 1]->getRating() < tempHelmet.getRating())
			{
				*helmetPool[j] = *helmetPool[j - 1];
				j--;
			}
			*helmetPool[j] = tempHelmet;
			i++;
		}
		cout << "Helmets Read successful\n";
	}

	query = "Select * from gloves";

	if (mysql_query(conn, query))
	{
		cout << "Gloves Insert failed \n";
		system("pause");
		exit(1);
	}
	else {
		i = 0;
		res = mysql_store_result(conn);
		while((row = mysql_fetch_row(res)) && i < MAX_LOADOUTS)
		{
			name = row[1];
			cost = stof(row[2]);
			fRes = stoi(row[4]);
			eRes = stod(row[5]);
			cRes = stod(row[6]);
			chRes = stod(row[7]);
			armor = stod(row[8]);
			hp = stod(row[9]);
			tempGloves.setName(name);
			tempGloves.setCost(cost);
			tempGloves.setfRes(fRes);
			tempGloves.seteRes(eRes);
			tempGloves.setcRes(cRes);
			tempGloves.setchRes(chRes);
			tempGloves.setArmor(armor);
			tempGloves.setHp(hp);
			tempGloves.calcRating();
			j = i;
			while (j > 0 && glovesPool[j - 1]->getRating() < tempGloves.getRating())
			{
				*glovesPool[j] = *glovesPool[j - 1];
				j--;
			}
			*glovesPool[j]=tempGloves;
			i++;
		}
		cout << "Gloves Read successful\n";
	}

	query = "Select * from boots";

	if (mysql_query(conn, query))
	{
		cout << "Boots Insert failed \n";
		system("pause");
		exit(1);
	}
	else {
		i = 0;
		res = mysql_store_result(conn);
		while((row = mysql_fetch_row(res)) && i < MAX_LOADOUTS)
		{
			name = row[1];
			cost = stof(row[2]);
			fRes = stoi(row[4]);
			eRes = stod(row[5]);
			cRes = stod(row[6]);
			chRes = stod(row[7]);
			armor = stod(row[8]);
			hp = stod(row[9]);
			tempBoots.setName(name);
			tempBoots.setCost(cost);
			tempBoots.setfRes(fRes);
			tempBoots.seteRes(eRes);
			tempBoots.setcRes(cRes);
			tempBoots.setchRes(chRes);
			tempBoots.setArmor(armor);
			tempBoots.setHp(hp);
			tempBoots.calcRating();
			j = i;
			while (j > 0 && bootsPool[j - 1]->getRating() < tempBoots.getRating())
			{
				*bootsPool[j] = *bootsPool[j-1];
				j--;
			}
			*bootsPool[j]=tempBoots;
			i++;
		}
		cout << "Boots Read successful\n";
	}

	query = "Select * from chests";

	if (mysql_query(conn, query))
	{
		cout << "Chest Insert failed \n";
		system("pause");
		exit(1);
	}
	else {
		i = 0;
		res = mysql_store_result(conn);
		while((row = mysql_fetch_row(res)) && i < MAX_LOADOUTS)
		{
			name = row[1];
			cost = stof(row[2]);
			fRes = stoi(row[4]);
			eRes = stod(row[5]);
			cRes = stod(row[6]);
			chRes = stod(row[7]);
			armor = stod(row[8]);
			hp = stod(row[9]);
			tempChest.setName(name);
			tempChest.setCost(cost);
			tempChest.setfRes(fRes);
			tempChest.seteRes(eRes);
			tempChest.setcRes(cRes);
			tempChest.setchRes(chRes);
			tempChest.setArmor(armor);
			tempChest.setHp(hp);
			tempChest.calcRating();
			j = i;
			while (j > 0 && chestPool[j - 1]->getRating() < tempChest.getRating())
			{
				*chestPool[j] = *chestPool[j-1];
				j--;
			}
			*chestPool[j]=tempChest;
			i++;
		}
		cout << "Chests Read successful\n";
	}

	query = "Select * from Lrings";

	if (mysql_query(conn, query))
	{
		cout << "Ring1 Insert failed \n";
		system("pause");
		exit(1);
	}
	else {
		i = 0;
		res = mysql_store_result(conn);
		while((row = mysql_fetch_row(res)) && i < MAX_LOADOUTS)
		{
			name = row[1];
			cost = stof(row[2]);
			fRes = stoi(row[4]);
			eRes = stod(row[5]);
			cRes = stod(row[6]);
			chRes = stod(row[7]);
			armor = stod(row[8]);
			hp = stod(row[9]);
			tempRing1.setName(name);
			tempRing1.setCost(cost);
			tempRing1.setfRes(fRes);
			tempRing1.seteRes(eRes);
			tempRing1.setcRes(cRes);
			tempRing1.setchRes(chRes);
			tempRing1.setArmor(armor);
			tempRing1.setHp(hp);
			tempRing1.calcRating();
			j = i;
			while (j > 0 && ring1Pool[j - 1]->getRating() < tempRing1.getRating())
			{
				*ring1Pool[j] = *ring1Pool[j-1];
				j--;
			}
			*ring1Pool[j]=tempRing1;
			i++;
		}
		cout << "Ring1s Read successful\n";
	}

	query = "Select * from Rrings";

	if (mysql_query(conn, query))
	{
		cout << "Ring2 Insert failed \n";
		system("pause");
		exit(1);
	}
	else {
		i = 0;
		res = mysql_store_result(conn);
		while((row = mysql_fetch_row(res)) && i < MAX_LOADOUTS)
		{
			name = row[1];
			cost = stof(row[2]);
			fRes = stoi(row[4]);
			eRes = stod(row[5]);
			cRes = stod(row[6]);
			chRes = stod(row[7]);
			armor = stod(row[8]);
			hp = stod(row[9]);
			tempRing2.setName(name);
			tempRing2.setCost(cost);
			tempRing2.setfRes(fRes);
			tempRing2.seteRes(eRes);
			tempRing2.setcRes(cRes);
			tempRing2.setchRes(chRes);
			tempRing2.setArmor(armor);
			tempRing2.setHp(hp);
			tempRing2.calcRating();
			j = i;
			while (j > 0 && ring2Pool[j - 1]->getRating() < tempRing2.getRating())
			{
				*ring2Pool[j] = *ring2Pool[j-1];
				j--;
			}
			*ring2Pool[j]=tempRing2;
			i++;
		}
		cout << "Ring2s Read successful\n";
	}

	query = "Select * from amulets";

	if (mysql_query(conn, query))
	{
		cout << "Amulet Insert failed \n";
		system("pause");
		exit(1);
	}
	else {
		i = 0;
		res = mysql_store_result(conn);
		while((row = mysql_fetch_row(res)) && i < MAX_LOADOUTS)
		{
			name = row[1];
			cost = stof(row[2]);
			fRes = stoi(row[4]);
			eRes = stod(row[5]);
			cRes = stod(row[6]);
			chRes = stod(row[7]);
			armor = stod(row[8]);
			hp = stod(row[9]);
			tempAmulet.setName(name);
			tempAmulet.setCost(cost);
			tempAmulet.setfRes(fRes);
			tempAmulet.seteRes(eRes);
			tempAmulet.setcRes(cRes);
			tempAmulet.setchRes(chRes);
			tempAmulet.setArmor(armor);
			tempAmulet.setHp(hp);
			tempAmulet.calcRating();
			j = i;
			while (j > 0 && amuletPool[j - 1]->getRating() < tempAmulet.getRating())
			{
				*amuletPool[j] = *amuletPool[j-1];
				j--;
			}
			*amuletPool[j]=tempAmulet;
			i++;
		}
		cout << "Amulets Read successful\n";
	}

	query = "Select * from belts";

	if (mysql_query(conn, query))
	{
		cout << "Belt Insert failed \n";
		system("pause");
		exit(1);
	}
	else {
		i = 0;
		res = mysql_store_result(conn);
		while((row = mysql_fetch_row(res)) && i < MAX_LOADOUTS)
		{
			name = row[1];
			cost = stof(row[2]);
			fRes = stoi(row[4]);
			eRes = stod(row[5]);
			cRes = stod(row[6]);
			chRes = stod(row[7]);
			armor = stod(row[8]);
			hp = stod(row[9]);
			tempBelt.setName(name);
			tempBelt.setCost(cost);
			tempBelt.setfRes(fRes);
			tempBelt.seteRes(eRes);
			tempBelt.setcRes(cRes);
			tempBelt.setchRes(chRes);
			tempBelt.setArmor(armor);
			tempBelt.setHp(hp);
			tempBelt.calcRating();
			j = i;
			while (j > 0 && beltPool[j - 1]->getRating() < tempBelt.getRating())
			{
				*beltPool[j] = *beltPool[j-1];
				j--;
			}
			*beltPool[j]=tempBelt;
			i++;
		}
		cout << "Belts Read successful\n";
	}
}



void Pool::printPool(ofstream& fout)
{
	int i;
	fout << "________________Weapons________________\n";
	for (i = 0; i < MAX && weaponPool[i] != NULL; i++) {
		fout << i << ".    ";
		fout << *weaponPool[i];
	}
	fout << "\n";

	fout << "________________Helmets________________\n";
	for (i = 0; i < MAX && helmetPool[i] != NULL; i++) {
		fout << i << ".    ";
		fout << *helmetPool[i];
	}
	fout << "\n";

	fout << "________________Gloves________________\n";
	for (i = 0; i < MAX && glovesPool[i] != NULL; i++) {
		fout << i << ".    ";
		fout << *glovesPool[i];
	}
	fout << "\n";

	fout << "________________Boots________________\n";
	for (i = 0; i < MAX && bootsPool[i] != NULL; i++) {
		fout << i << ".    ";
		fout << *bootsPool[i];
	}
	fout << "\n";

	fout << "________________Chests________________\n";
	for (i = 0; i < MAX && chestPool[i] != NULL; i++) {
		fout << i << ".    ";
		fout << *chestPool[i];
	}
	fout << "\n";

	fout << "________________Left Rings________________\n";
	for (i = 0; i < MAX && ring1Pool[i] != NULL; i++) {
		fout << i << ".    ";
		fout << *ring1Pool[i];
	}
	fout << "\n";

	fout << "________________Right Rings________________\n";
	for (i = 0; i < MAX && ring2Pool[i] != NULL; i++) {
		fout << i << ".    ";
		fout << *ring2Pool[i];
	}
	fout << "\n";

	fout << "________________Amulets________________\n";
	for (i = 0; i < MAX && amuletPool[i] != NULL; i++) {
		fout << i << ".    ";
		fout << *amuletPool[i];
	}
	fout << "\n";

	fout << "________________Belts________________\n";
	for (i = 0; i < MAX && beltPool[i] != NULL; i++) {
		fout << i << ".    ";
		fout << *beltPool[i];
	}
	fout << "\n";
}

void Pool::bestLoadouts(Loadout *&loadouts)
{
	Loadout tempLoadout;
	int count = 0,b,c,d,e,f,g,h,i,t, rating = 0;

	typedef chrono::high_resolution_clock::time_point Timer;
	#define CLOCK chrono::high_resolution_clock
	#define DURATION chrono::duration_cast<chrono::milliseconds>
	Timer start;
	Timer end;
	int dmg = 300;
	double spd = 1;
	weaponPool[0]->setCost(50);
	weaponPool[0]->setName("Shotgun");
	weaponPool[0]->setDamage(dmg);
	weaponPool[0]->setSpeed(spd);
	tempLoadout.addWeapon(weaponPool[0]);
	tempLoadout.calcDPS();
	//cout << chrono::high_resolution_clock::period::den << endl;
	const int MAXe = MAX;
	long long duration = 0;
	start = CLOCK::now();
	for (b = 0; b < MAXe && helmetPool[b]->getId() != ""; b++)
	{
		tempLoadout.addHelmet(helmetPool[b]);
		for (c = 0; c < MAXe && bootsPool[c]->getId() != ""; c++)
		{
			tempLoadout.addBoots(bootsPool[c]);
			for (d = 0; d < MAXe && glovesPool[d]->getId() != ""; d++)
			{
				tempLoadout.addGloves(glovesPool[d]);
				for (e = 0; e < MAXe && chestPool[e]->getId() != ""; e++)
				{
					tempLoadout.addChest(chestPool[e]);
					for (h = 0; h < MAXe && amuletPool[h]->getId() != ""; h++)
					{
						tempLoadout.addAmulet(amuletPool[h]);
						for (i = 0; i < MAXe && beltPool[i]->getId() != ""; i++)
						{
							tempLoadout.addBelt(beltPool[i]);
							for (f = 0; f < MAXe && ring1Pool[f]->getId() != ""; f++)
							{
								tempLoadout.addRing1(ring1Pool[f]);
								for (g = 0; g < MAXe && ring2Pool[g]->getId() != ""; g++)
								{
									if (ring2Pool[g]->getId() != ring1Pool[f]->getId()
										&& !searchRingHash(getHash(ring1Pool[f]->getId(), ring2Pool[g]->getId())) )
									{
										tempLoadout.addRing2(ring2Pool[g]);
										tempLoadout.calcStats();
										if (tempLoadout.meetsMinimums())
										{
											tempLoadout.calcRating(); 
											rating = tempLoadout.getRating();
											if (rating > minRating && rating > loadouts[MAX_LOADOUTS - 1].getRating())
											{
												t = count;
												while (t > 0 && loadouts[t - 1].getRating() < rating)
												{
													loadouts[t] = loadouts[t - 1];
													t--;
												}
												loadouts[t] = tempLoadout;/**/
												if (count < MAX_LOADOUTS - 1)	count++;
											}
										}
									}
								}
							}
							ringHash.clear();
							ringHash.reserve(MAX* MAX);
						}
					}
				}
			}
		}
	}
	end = CLOCK::now();
	cout << DURATION(end - start).count()/1000.0 << " seconds." << endl;
}

void printLoadouts(Loadout loadouts[], ofstream& fout)
{
	for (int i = 0; i < MAX_LOADOUTS && loadouts[i].getRating() > 0; i++)
	{
		fout << i+1 << ". ";
		loadouts[i].printLoadout(fout);
	}
}