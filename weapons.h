//
// Created by Anthony Gatti on 2/3/23.
//

#ifndef SEM1FINAL_WEAPONS_H
#define SEM1FINAL_WEAPONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// base weapons class
class weapons {
protected:
	weapons* next; // Next in list
	string weaponType; // Type of weapon
	string name; // Name of weapon
	int serialNumber; // Serial number of weapon
	string fileString; // Weapon line in file
	string filename;
public:
	weapons* head; // Head of list
	weapons* tail; // Tail of list
	weapons () {next = NULL; serialNumber = 0; head = nullptr; tail = nullptr;}; // Weapons constructor
	void set_next (weapons* nxt) {next = nxt;} // Set next in list
	virtual void display() {}; // Display weapon
	void displayHeaderAll(); // Display header for all weapons
	virtual void displayHeader() {}; // Display header for single type of weapon
	weapons* get_next() {return next;} // Get next in list
	void addToList(weapons* weapon); // Add weapon to list
	string getWeaponType() {return weaponType;}; // Get the type of weapon
	int getSerialNumber() {return serialNumber;}; // Get the serial number of weapon
	bool deleteWeapon(const bool deleteOccured); // Delete a weapon from the list
	string getFileString() {return fileString;}; // Gets the weapons line in the file
	void updateFile(); // Updates the file is weapon deleted
	void readFile(); // Reads in the file of weapons and stores in list
	void displayAllWeapons(); // Displays all weapons in list
	void displaySingleWeapon(); // Displays single type of weapon in list
	string getFilename() {return filename;}; // Gets filename inputted
};

// derived tank class
class tank : public weapons {
private:
	int numCrew; // Number of crew for the tank
	int weight; // Weight of the tank
	int numRounds; // Number of rounds for the tank
public:
	tank(string w, string n, int s, int nc, int wt, int nr, string fs) { // Constructor
		this->weaponType = w;
		this->name = n;
		this->serialNumber = s;
		this->numCrew = nc;
		this->weight = wt;
		this->numRounds = nr;
		this->fileString = fs;
	};
	void display () { // Display tank
		cout.width(19); cout << left << weaponType;
		cout.width(12); cout << left << name;
		cout.width(6); cout << right << serialNumber;
		cout.width(15); cout << right << numCrew;
		cout.width(16); cout << right << weight;
		cout.width(15); cout << right << numRounds << endl;
	};
	void displayHeader(); // Display tank header
};

// derived armored class
class armored : public weapons {
private:
	int speed; // Speed of armored vehicle
public:
	armored(string w, string n, int s, int sp, string fs) { // Constructor
		this->weaponType = w;
		this->name = n;
		this->serialNumber = s;
		this->speed = sp;
		this->fileString = fs;
	}
	void display () { // Display armored vehicle
		cout.width(19); cout << left << weaponType;
		cout.width(8); cout << left << name;
		cout.width(10); cout << right << serialNumber;
		cout.width(16); cout << right << speed << endl;
	};
	void displayHeader(); // Display armored header
};

// derived missile class
class missile : public weapons {
private:
	int range; // Range of missile
	string support; // Support of the missile
public:
	missile(string w, string n, int s, int r, string supp, string fs) { // Constructor
		this->weaponType = w;
		this->name = n;
		this->serialNumber = s;
		this->range = r;
		this->support = supp;
		this->fileString = fs;
	}
	void display () { // Display missile
		cout.width(19); cout << left << weaponType;
		cout.width(13); cout << left << name;
		cout.width(6); cout << right << serialNumber;
		cout.width(15); cout << right << range;
		cout.width(21); cout << right << support << endl;
	}
	void displayHeader(); // Display missile header
};

#endif //SEM1FINAL_WEAPONS_H
