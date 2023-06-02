#include "weapons.h"

/*
 * Pre: No input
 * Post: Displays header for all items
 * Description: Displays the header for case 2 where all items are displayed
 */
void weapons :: displayHeaderAll() {
	cout << endl;
	cout.width(10); cout << left << "Weapon Type";
	cout.width(12); cout << right << "Name";
	cout.width(24); cout << right << "Serial Number";
	cout.width(10); cout << right << "Item 1";
	cout.width(15); cout << right << "Item 2";
	cout.width(15); cout << right << "Item 3" << endl;
	cout << string(87, '-') << endl;
}

/*
 * Pre: No input
 * Post: Displays header for tank weapon type
 * Description: Displays the header for case 3 where the weapon type is tank
 */
void tank :: displayHeader() {
	cout << endl;
	cout.width(10); cout << left << "Weapon Type";
	cout.width(12); cout << right << "Name";
	cout.width(24); cout << right << "Serial Number";
	cout.width(12); cout << right << "Num Crew";
	cout.width(13); cout << right << "Weight";
	cout.width(19); cout << right << "Num Rounds" << endl;
	cout << string(91, '-') << endl;
}

/*
 * Pre: No input
 * Post: Displays header for armored weapon type
 * Description: Displays the header for case 3 where the weapon type is armored
 */
void armored :: displayHeader() {
	cout << endl;
	cout.width(10); cout << left << "Weapon Type";
	cout.width(12); cout << right << "Name";
	cout.width(24); cout << right << "Serial Number";
	cout.width(9); cout << right << "Speed" << endl;
	cout << string(56, '-') << endl;
}

/*
 * Pre: No input
 * Post: Displays header for missile weapon type
 * Description: Displays the header for case 3 where the weapon type is missile
 */
void missile :: displayHeader() {
	cout << endl;
	cout.width(10); cout << left << "Weapon Type";
	cout.width(12); cout << right << "Name";
	cout.width(24); cout << right << "Serial Number";
	cout.width(9); cout << right << "Range";
	cout.width(17); cout << right << "Support" << endl;
	cout << string(87, '-') << endl;
}

/*
 * Pre: Takes in a weapon
 * Post: Adds that weapon to the list
 * Description: Adds weapon to the list of weapons
 */
void weapons :: addToList(weapons* weapon) {
	if (this->head == nullptr) { // If head is empty
		this->head = weapon; // Set head equal to weapon
	} else {
		this->tail->set_next(weapon); // Add weapon to list
	}
	this->tail = weapon;
}

/*
 * Pre: Takes in a serial number
 * Post: Deletes the weapon from the list if a matching serial number is found
 * Description: Deletes the weapon from list of weapons based on the serial number
 */
bool weapons :: deleteWeapon(const bool deleteOccured) {
	struct weapons *temp = head, *prev; // Temporary list
	int serialInput; // Serial number input

	cout << "Enter weapon serial number -> ";
	cin >> serialInput; // Input serial number

	// If weapon in list matches delete it
	if (temp != nullptr && temp->getSerialNumber() == serialInput) {
		if (temp->get_next() == this->head->get_next()) { // If first in list
			this->head = this->head->get_next(); // Delete
		} else {
			this->head->set_next(temp->next); // Delete
		}
		free(temp);
		return true;
	}
	// Find the weapon to be deleted
	while (temp != nullptr && temp->getSerialNumber() != serialInput) {
		prev = temp;
		temp = temp->next;
	}

	// If the weapon is not present
	if (temp == nullptr) {
		return deleteOccured;
	}

	// Remove the node
	prev->next = temp->next;

	free(temp);
	return true;
}

/*
 * Pre: No inputs
 * Post: Updates the file if an item has been deleted
 * Description: Updates the file inputted if any
 * weapons have been deleted from the list
 */
void weapons :: updateFile() {
	ofstream outfile; // output file stream
	weapons* ptr; // Ptr for linked list of weapons
	int numberOfWeapons = 0; // The number of weapons read in list

	outfile.open(this->getFilename()); // Opens file

	ptr = this->head; // Sets pointer to start of list

	// Goes through list and counts number of weapons
	while (ptr){                // go through the linked list
		numberOfWeapons++;      // adds 1 to number of weapons
		ptr=ptr->get_next();     // go to next item on list
	}

	outfile << numberOfWeapons << "\n"; // Writes to file number of weapons

	ptr = this->head; // Sets pointer to start of list

	// Goes through list and writes to file each line
	while (ptr){                // go through the linked list
		outfile << ptr->getFileString() << "\n";
		ptr=ptr->get_next();     // go to next item on list
	}

	outfile.close(); // Closes file
}

/*
 * Pre: Takes in an input filestream
 * Post: Stores all the weapons in the file inside a linked list of weapons
 * Description: Reads in a file of weapons and stores them in a
 * heterogeneous linked list of weapons where head is the head of the list
 */
void weapons ::readFile() {
	int numberOfWeapons; // Number of weapons read from file
	string weaponType; // Weapon type in file
	string read; // Line read without weapon type
	string currentItem; // Current item in line
	string fileStringS; // Line read from file used to store in weapon
	string filename; // Filename inputted
	ifstream infile; // file stream for inputted file
	int j; // Iterator for current item

	head = nullptr; // Reset head

	cout << "Enter file name -> ";
	cin >> filename; // Enter file name
	infile.open(filename); // Open filestream
	if (infile.is_open()) { // If file exists
		infile >> numberOfWeapons; // Get number of weapons

		// For each weapon
		for (int i = 0; i < numberOfWeapons; i++) {
			j = 0; // Reset to 0

			infile >> weaponType; // Get type of weapon

			if (weaponType == "tank") { // If weapon is a tank
				string items[5]; // Store items in line

				if (getline(infile, read)) { // If line exists
					fileStringS = weaponType + read; // Store line of file
					istringstream iss(read);

					// Store items from line in array
					while (getline(iss, currentItem, '\t')) {
						if (currentItem.find_first_not_of(' ') != string::npos) { // Don't add space
							// There's a non-space.
							items[j] = currentItem;
							j++;
						}
					}
				}

				// Create new tank object
				tank *newTank = new tank("tank", items[0], stoi(items[1]), stoi(items[2]), stoi(items[3]), stoi(items[4]),
										 fileStringS);
				this->addToList(newTank); // Add tank to list
			} else if (weaponType == "armored") { // If weapon is armored
				string items[3]; // Store items in line

				if (getline(infile, read)) { // If line exists
					fileStringS = weaponType + read; // Store line of file
					istringstream iss(read);

					// Adds items to array
					while (getline(iss, currentItem, '\t')) {
						if (currentItem.find_first_not_of(' ') != string::npos) { // Don't add space
							// There's a non-space.
							items[j] = currentItem;
							j++;
						}
					}
				}

				// Create new armored object
				armored *newArmored = new armored("armored", items[0], stoi(items[1]), stoi(items[2]), fileStringS);
				this->addToList(newArmored); // Add armored to list
			} else if (weaponType == "missile") { // If weapon is a missile
				string items[4]; // Store items in line

				if (getline(infile, read)) { // If line exists
					fileStringS = weaponType + read; // Store line of file
					istringstream iss(read);

					// Add items to array
					while (getline(iss, currentItem, '\t')) {
						if (currentItem.find_first_not_of(' ') != string::npos) { // Don't add spaces
							// There's a non-space.
							items[j] = currentItem;
							j++;
						}
					}
				}

				// Create new missile object
				missile *newMissile = new missile("missile", items[0], stoi(items[1]), stoi(items[2]), items[3],
												  fileStringS);
				this->addToList(newMissile); // Add missile to list
			}

		}

		this->filename = filename; // Set filename
	} else { // If file doesn't exist
		cout << "file does not exist" << endl;
	}
	infile.close(); // Close file
}

/*
 * Pre: No input
 * Post: Displays all the weapons in the list
 * Description: Display function that displays an organized table
 * of the all the weapons in the list
 */
void weapons ::displayAllWeapons() {
	weapons* ptr; // Weapon pointer

	ptr = this->head; // Set to head
	ptr->displayHeaderAll(); // Display header

	while (ptr){                // go through the linked list
		ptr->display();          // use virtual function to display
		// appropriate object
		ptr=ptr->get_next();     // go to next item on list
	}
	cout << endl;
}

/*
 * Pre: Asks for a weapon type
 * Post: Displays all the weapons matching that type
 * Description: Display function that displays an organized table
 * of the single type of weapon the user inputted
 */
void weapons ::displaySingleWeapon() {
	string weaponTypeInput; // Weapon type inputted
	weapons* ptr; // Weapon pointer
	bool isHeaderDisp = false; // Check if header has been displayed

	cout << "Enter weapon type: tank, armored, or missile -> ";
	cin >> weaponTypeInput; // Input weapon type
	ptr = this->head; // Set pointer to head

	if (weaponTypeInput == "tank") { // If weapon is tank
		while (ptr){                // go through the linked list
			if (ptr->getWeaponType() == "tank") {
				if (!isHeaderDisp) { // Check if header has been displayed
					ptr->displayHeader();
					isHeaderDisp = true;
				}
				ptr->display();          // use virtual function to display
			}
			// appropriate object
			ptr=ptr->get_next();     // go to next item on list
		}
	}
	else if (weaponTypeInput == "armored") { // If armored
		while (ptr){                // go through the linked list
			if (ptr->getWeaponType() == "armored") { // If armored
				if (!isHeaderDisp) { // Check if header has been displayed
					ptr->displayHeader();
					isHeaderDisp = true;
				}
				ptr->display();          // use virtual function to display
			}
			// appropriate object
			ptr=ptr->get_next();     // go to next item on list
		}
	}
	else if (weaponTypeInput == "missile") { // If missile
		while (ptr){                // go through the linked list
			if (ptr->getWeaponType() == "missile") { // If missile
				if (!isHeaderDisp) {
					ptr->displayHeader();
					isHeaderDisp = true;
				}
				ptr->display();          // use virtual function to display
			}
			// appropriate object
			ptr=ptr->get_next();     // go to next item on list
		}
	}

	cout << endl;
}


