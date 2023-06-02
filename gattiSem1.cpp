/* Anthony Gatti
 * gattiSem1.cpp
 * Description: The armed forces in Ukraine need a way to
 * keep track of all the weapons and systems they have. These
 * types include tanks, armored vehicles, and missiles. These
 * are stored in an input file that will be read by the program to
 * display and update the file. This program uses a heterogeneous list.
 * Input: This program will give 5 choices of inputs, 1, 2, 3, 4, 5.
 * 1: Input a filename that contains the database of items.
 * Example input file:
 *  4
	tank	Challenger 2	153	4	75	50
	missile	Starstreak	9808	12	portable
	tank	M1 Abrams	224	4	67	55
	armored	Stryker		106	60
 * 2: No further input.
 * 3: Input type of weapon, tank, armored, or missile.
 * 4: Input serial number of weapon to delete.
 * 5: Quit the program and update the file.
 * Output:
 * 1: No output.
 * 2: Displays all the items pulled from the file.
 *  Weapon Type        Name           Serial Number    Item 1         Item 2         Item 3
	---------------------------------------------------------------------------------------
	tank               Challenger 2   153              4              75             50
	missile            Starstreak     9808             12             portable
	tank               M1 Abrams      224              4              67             55
	armored            Stryker        106              60
 * 3: Displays one type of weapon which was inputted.
 *  Weapon Type        Name           Serial Number    Num Crew       Weight         Num Rounds
	-------------------------------------------------------------------------------------------
	tank               Challenger 2   153              4              75             50
	tank               M1 Abrams      224              4              67             55
 * 4: No output.
 * 5: No output.
 */

#include "weapons.h"

int main() {
	int type = 0; // The option inputted, 1-5
	bool deleteOccured = false; // Bool to check if item has been deleted from list
	weapons weaponsList; // List of weapons

	// Keep formatting consistent
	cout.setf(ios::fixed, ios::floatfield);
	cout.setf(ios::showpoint);

	// While 5 has been inputted keep running program
	while (type != 5) {
		cout << "1 - read file" << endl;
		cout << "2 - display all items" << endl;
		cout << "3 - display one type" << endl;
		cout << "4 - delete on item" << endl;
		cout << "5 - quit" << endl;
		cin >> type;

		// Switch statement for different types of cases
		switch (type) {
			case 1: // Enter file and reads in all weapons and store in list
				weaponsList.readFile();
				break;
			case 2: // Displays all the weapons in the list
				weaponsList.displayAllWeapons();
				break;
			case 3: // Displays single type of weapon in list
				weaponsList.displaySingleWeapon();
				break;
			case 4: // Deletes weapon list
				deleteOccured = weaponsList.deleteWeapon(deleteOccured);
				break;
		}
	}

	if (deleteOccured) { // If an item has been deleted
		weaponsList.updateFile(); // Update file
	}

	return 0;
}
