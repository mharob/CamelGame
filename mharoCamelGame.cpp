/*
Author: Miquel Haro
Created: 28 April 2017
Class: ITSY 2441 - Object Oriented Programming
Instructor: Prof  Welch
Problem description: Create a script that greets the user and provides responses
based on the user's name, age, and lucky numbers.

Todo - Summary of Modifications:
04/28/2016 - Analysis and algorithm design
04/28/2016 - Code baseline - complete main() and all input validation functions
04/29/2016 - Simplification, Style, & Review
04/29/2016 - Testing
04/30/2016 - Testing & Screenshots

Lessons learned:
(1) Pointers are useful for mainipulating a large amount of variables between functions.
(2) Large programs are more easy to tackle when broken downn into modular pieces.
(3) Not only is it useful to break down a complex problem into solvable parts it helps to debug each part. 

https://github.com/mharob/CamelGame.git

*/


#include <iostream>// Needed cout, cin
#include <fstream>// Needed ofstream
#include <cstdlib>// needed srand()
#include <ctime>// Needed time()
using namespace std;


void seedRandom();
void instructions();
void menu();
void isValid(char* choicePtr);
void checkConditions(bool* ptrDone, int* ptrMilesTraveled, int* ptrThirst, int* ptrCamelTiredness, int* ptrDistNatives);
void drinkCanteen(int* ptrCanteen, int* ptrThirst);
void moderateSpeed(int* ptrMilesTraveled, int* ptrCanteen, int* ptrThirst, int* ptrCamelTiredness, int* ptrDistNatives);
void fullSpeed(int* ptrMilesTraveled, int* ptrCanteen, int* ptrThirst, int* ptrCamelTiredness, int* ptrDistNatives);
void stopRest(int* ptrCamelTiredness, int* ptrDistNatives);
void checkStatus(int* ptrMilesTraveled, int* ptrCanteen, int* ptrDistNatives);
void randNatives(int* nativesPtr);
void randCamelModerate(int* camelPtr);
void randCamelFull(int* camelPtr);
void randModerateSpeed(int* milesPtr, int* nativesPtr);
void randFullSpeed(int* milesPtr, int* nativesPtr);
void randOasis(int* ptrCanteen, int* ptrThirst, int* ptrCamelTiredness);


ofstream fout("results.txt"); // Needed to write data to results.txt


int main()
{
	seedRandom();
	instructions();
	menu();

    return 0;
}// end main()


//-------------------------------------
// Functions
//-------------------------------------

//============================================================
void seedRandom()
{
	unsigned seed;
	seed = time(0);
	srand(seed);

	return;
}// end seedRandom()
//============================================================


//============================================================
void instructions()
{
	cout << "Welcome to Camel!" << endl;
	cout << "You have stolen a camel to make your way across the great Mobi desert." << endl;
	cout << "The natives want their camel back and are chasing you down!";
	cout << " Survive your" << endl;
	cout << "desert trek and outrun the natives." << endl << endl;
	cout << "Choices A and E  do not count as movement thus will not advance time." << endl;
	cout << "Choices B-D count as movement commands and will advance time." << endl;

	fout << "Welcome to Camel!" << endl;
	fout << "You have stolen a camel to make your way across the great Mobi desert." << endl;
	fout << "The natives want their camel back and are chasing you down!";
	fout << " Survive your" << endl;
	fout << "desert trek and outrun the natives." << endl << endl;
	fout << "Choices A and E  do not count as movement thus will not advance time." << endl;
	fout << "Choices B-D count as movement commands and will advance time." << endl;

	return;
}// end instructions()
//============================================================


//============================================================
void menu()
{
	//Variable Initialization_Declaration
	int milesTraveled = 0;
	int thirst = 0;
	int camelTiredness = 0;
	int distNatives = -20;
	int canteen = 2;
	char playerChoice;
	bool done = false;

	//Pointer Initialization_Declaration
	int* milesTraveledPtr = &milesTraveled;
	int* thirstPtr = &thirst;
	int* camelTirednessPtr = &camelTiredness;
	int* distNativesPtr = &distNatives;
	int* canteenPtr = &canteen;
	char* choicePtr = &playerChoice;
	bool* donePtr = &done;

	//Menu do-while loop
	do
	{
		cout << "============================================================" << endl;
		cout << "A. Drink from your canteen." << endl;
		cout << "B. Ahead moderate speed." << endl;
		cout << "C. Ahead full speed." << endl;
		cout << "D. Stop and rest." << endl;
		cout << "E. Status check." << endl;
		cout << "Q. Quit." << endl;
		cout << "Your choice? ";

		fout << "============================================================" << endl;
		fout << "A. Drink from your canteen." << endl;
		fout << "B. Ahead moderate speed." << endl;
		fout << "C. Ahead full speed." << endl;
		fout << "D. Stop and rest." << endl;
		fout << "E. Status check." << endl;
		fout << "Q. Quit." << endl;
		fout << "Your choice? ";

		cin >> playerChoice;

		isValid(choicePtr);

		switch (playerChoice)
		{
		case 'A': drinkCanteen(canteenPtr, thirstPtr);
				break;
		case 'B': moderateSpeed(milesTraveledPtr, canteenPtr, thirstPtr, camelTirednessPtr, distNativesPtr);
				break;
		case 'C': fullSpeed(milesTraveledPtr, canteenPtr, thirstPtr, camelTirednessPtr, distNativesPtr);
				break;
		case 'D': stopRest(camelTirednessPtr, distNativesPtr);
				break;
		case 'E' : checkStatus(milesTraveledPtr, canteenPtr, distNativesPtr);
				break;
		case 'Q': done = true;
				break;
		}// end switch()

		checkConditions(donePtr, milesTraveledPtr, thirstPtr, camelTirednessPtr, distNativesPtr);

		cout << "============================================================" << endl << endl;
		fout << "============================================================" << endl << endl;

	} while (!done);

	cout << "Game results written to results.txt" << endl << endl;

	return;
}// end menu()
//============================================================


//============================================================
void isValid(char* choicePtr)
{
	bool isValid = false;
	*choicePtr = toupper(*choicePtr);

	do
	{
		switch (*choicePtr)
		{
		case 'A': isValid = true;
			break;
		case 'B': isValid = true;
			break;
		case 'C': isValid = true;
			break;
		case 'D': isValid = true;
			break;
		case 'E': isValid = true;
			break;
		case 'Q': isValid = true;
			break;
		default: cout << "You did not enter A, B, C, D, E, or Q." << endl;
			cout << "Your choice? ";
			fout << "You did not enter A, B, C, D, E, or Q." << endl;
			fout << "Your choice? ";
			cin >> *choicePtr;
			*choicePtr = toupper(*choicePtr);
			break;
		}// end switch()

	} while (!isValid);

	return;
}// end isValid();
//============================================================


//============================================================
void checkConditions(bool* ptrDone, int* ptrMilesTraveled, int* ptrThirst, int* ptrCamelTiredness, int* ptrDistNatives)
{
	if ((*ptrThirst > 4) && (*ptrThirst <= 6))
	{
		cout << "You are thirsty." << endl;
		fout << "You are thirsty." << endl;
	}// end if()
	else if (*ptrThirst > 6)
	{
		cout << "You died of thirst!" << endl;
		cout << "GAME OVER" << endl;

		fout << "You died of thirst!" << endl;
		fout << "GAME OVER" << endl;
		*ptrDone = true;
		return;
	}// end else if()

	if ((*ptrCamelTiredness >= 5) && (*ptrCamelTiredness <= 8))
	{
		cout << "Your camel is getting tired." << endl;
		fout << "Your camel is getting tired." << endl;
	}// end if()
	else if (*ptrCamelTiredness > 8)
	{
		cout << "Your camel is dead!" << endl;
		cout << "GAME OVER" << endl;

		fout << "Your camel is dead!" << endl;
		fout << "GAME OVER" << endl;
		*ptrDone = true;
		return;
	}// end else if()

	if ((*ptrDistNatives > -15) && (*ptrDistNatives < 0))
	{
		cout << "The natives are getting close!" << endl;
		fout << "The natives are getting close!" << endl;
	}// end if()
	else if (*ptrDistNatives >= 0)
	{
		cout << "The natives caught you!" << endl;
		cout << "GAME OVER" << endl;

		fout << "The natives caught you!" << endl;
		fout << "GAME OVER" << endl;
		*ptrDone = true;
		return;
	}// end else if()

	if (*ptrMilesTraveled >= 200)
	{
		cout << "You made it across the desert! You won!" << endl;
		fout << "You made it across the desert! You won!" << endl;
		*ptrDone = true;
		return;
	}// end if()

	return;
}// end checkConditions()
//============================================================


//============================================================
void drinkCanteen(int* ptrCanteen, int* ptrThirst)
{
	const int DRINK = 1; // Needed to subtract 1 from canteen.
	const int HYDRATED = 0; // Needed to reset thirst to 0.

	if (*ptrCanteen > 0)
	{
		*ptrCanteen = (*ptrCanteen - DRINK);
		*ptrThirst = HYDRATED;

		cout << "You sated your thirst." << endl;
		fout << "You sated your thirst." << endl;
	}// end if()
	else
	{
		cout << "Your canteen is empty." << endl;
		fout << "Your canteen is empty." << endl;
	}// Trailing else

	return;
}// end drinkCanteen()
//============================================================


//============================================================
void moderateSpeed(int* ptrMilesTraveled, int* ptrCanteen, int* ptrThirst, int* ptrCamelTiredness, int* ptrDistNatives)
{
	const int THIRSTY = 1; // Needed to add 1 to thirst counter. 

	randModerateSpeed(ptrMilesTraveled, ptrDistNatives);
	randCamelModerate(ptrCamelTiredness);
	randNatives(ptrDistNatives);

	*ptrThirst = (*ptrThirst + THIRSTY);

	randOasis(ptrCanteen, ptrThirst, ptrCamelTiredness);

	return;
}// end moderateSpeed()
//============================================================


//============================================================
void fullSpeed(int* ptrMilesTraveled, int* ptrCanteen, int* ptrThirst, int* ptrCamelTiredness, int* ptrDistNatives)
{
	const int THIRSTY = 1; // Needed to add 1 to thirst counter.

	randFullSpeed(ptrMilesTraveled, ptrDistNatives);
	randCamelFull(ptrCamelTiredness);
	randNatives(ptrDistNatives);

	*ptrThirst = (*ptrThirst + THIRSTY);

	randOasis(ptrCanteen, ptrThirst, ptrCamelTiredness);

	return;
}// end fullSpeed()
//============================================================


//============================================================
void stopRest(int* ptrCamelTiredness, int* ptrDistNatives)
{
	*ptrCamelTiredness = 0;
	cout << "You stop and rest." << endl;
	cout << "Your camel is happy." << endl;

	fout << "You stop and rest." << endl;
	fout << "Your camel is happy." << endl;

	randNatives(ptrDistNatives);

	return;
}// end stopRest()
//============================================================


//============================================================
void checkStatus(int* ptrMilesTraveled, int* ptrCanteen, int* ptrDistNatives)
{
	cout << "Miles traveled: " << *ptrMilesTraveled << endl;
	cout << "Drinks in canteen: " << *ptrCanteen << endl;
	cout << "The natives are " << abs(*ptrDistNatives) << " miles behind you." << endl;

	fout << "Miles traveled: " << *ptrMilesTraveled << endl;
	fout << "Drinks in canteen: " << *ptrCanteen << endl;
	fout << "The natives are " << abs(*ptrDistNatives) << " miles behind you." << endl;

	return;
}// end checkStatus()
//============================================================


//============================================================
void randNatives(int* nativesPtr)
{
	int nativesTraveled = (rand() % (14 - 7 + 1)) + 8;
	*nativesPtr = (*nativesPtr + nativesTraveled);

	return;
}// end randNatives()
//============================================================

//============================================================
void randCamelModerate(int* camelPtr)
{
	int camelTired = (rand() % (2 - 1 + 1)) + 1;
	*camelPtr = (*camelPtr + camelTired);

	return;
}// end randCamelModerate()
//============================================================


//============================================================
void randCamelFull(int* camelPtr)
{
	int camelTired = (rand() % (3 - 1 + 1)) + 1;
	*camelPtr = (*camelPtr + camelTired);

	return;
}// end randCamel()
//============================================================


//============================================================
void randModerateSpeed(int* milesPtr, int* nativesPtr)
{
	int playerTraveled = (rand() % (12 - 5 + 1)) + 5;
	*milesPtr = (*milesPtr + playerTraveled);
	*nativesPtr = (*nativesPtr - playerTraveled);

	cout << "You traveled " << playerTraveled << " miles." << endl;
	fout << "You traveled " << playerTraveled << " miles." << endl;

	return;
}// end randModerateSpeed()
//============================================================

//============================================================
void randFullSpeed(int* milesPtr, int* nativesPtr)
{
	int playerTraveled = (rand() % (18 - 10 + 1)) + 10;
	*milesPtr = (*milesPtr + playerTraveled);
	*nativesPtr = (*nativesPtr - playerTraveled);

	cout << "You traveled " << playerTraveled << " miles." << endl;
	fout << "You traveled " << playerTraveled << " miles." << endl;

	return;
}// end randFullSpeed()
//============================================================


//============================================================
void randOasis(int* ptrCanteen, int* ptrThirst, int* ptrCamelTiredness)
{
	const int HYDRATED = 0; // Needed to reset thirst.
	const int RESTED = 0; // Needed to reset camel's fatigue.
	const int FILLED = 2; // Needed to fill canteen.
	int oasisChance = (rand() % (20 - 1 + 1)) + 1;

	if (oasisChance == 10)
	{
		cout << "You found an oasis!" << endl;
		fout << "You found an oasis!" << endl;

		cout << "You drink and fill your canteen." << endl;
		cout << "Your thirst is sated." << endl;

		fout << "You drink and fill your canteen." << endl;
		fout << "Your thirst is sated." << endl;
		*ptrCanteen = FILLED;
		*ptrThirst = HYDRATED;

		cout << "You rest your camel." << endl;
		cout << "Your camel is happy." << endl;

		fout << "You rest your camel." << endl;
		fout << "Your camel is happy." << endl;
		*ptrCamelTiredness = RESTED;
	}// end if()

	return;
}// end randOasis()
//============================================================
