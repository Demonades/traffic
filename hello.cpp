#include <bits/stdc++.h>
using namespace std;


int currentDay = 17;
int currentMonth = 5;
int currentYear = 2020;
int exitHandler = 1;

const int maxNumOfCars = 3;
const int maxNumOfFines = 10;
int numberOfDrivers = 0;

void carUserMenuPrompt();
void fineMenuPrompt();
void mainMenuPrompt();

struct date
{
	int day;
	int month;
	int year;
	bool isPaid = false;
};

struct fine
{
	float value;
	char street[100];
	date issueDate;

};

struct car
{
	char plateNumber[100];
	char model[100];
	int numberOfFines = 0;
	fine listOfFines[maxNumOfFines];
	int productionYear;
};

struct person
{
	char license[100];
	char firstName[100];
	char lastName[100];
	date birthdate;
	int numOfCars = 0;
	car listOfCars[maxNumOfCars];
};

person driverDatabase[100];


bool nameValidation(char *driverName)
{
	for(int i = 0; i < 100; i++)
	{
		if(driverName[i] == '\0')
		{
			break;
		}
		if(driverName[i] == ' ')
		{
			continue;
		}
		if(!isalpha(driverName[i]))
		{
			return false;
		}
		driverName[i] = toupper(driverName[i]);
	}
	return true;
}


 void ClearScreen()
 {
    cout << string( 100, '\n' );
 }
//////////////////////////////////////////FINES///////////////////////////////////////
void addFine()
{
	fine newFine;

	cout << "Please enter the speed of the car: ";
	float carSpeed;
	cin >> carSpeed;

	cout << "Please enter the maximum allowed speed of the road: ";
	float allowedCarSpeed;
	cin >> allowedCarSpeed;
	if(carSpeed <= allowedCarSpeed)
	{
		cout << "Invalid fine, the car is not in violation of speeding!\n";
		return;
	}

	newFine.value = 2 * (carSpeed - allowedCarSpeed);


	cout << "Please enter the street name: ";
	cin >> newFine.street;

	cout << "Please enter the date of today:\n";
	date Date;
	cout << "Day: ";
	cin >> Date.day;
	cout << "Month: ";
	cin >> Date.month;
	cout << "Year: ";
	cin >> Date.year;

	newFine.issueDate = Date;

	cout << "Please enter the car's license number: ";

	char plateNumber[100];
	cin >> plateNumber;
	bool isPlateNumberRegistered = false;

	for(int i = 0; i < numberOfDrivers; i++)
	{
		for(int j = 0; j < driverDatabase[i].numOfCars; j++)
		{
			if(strcmp(driverDatabase[i].listOfCars[j].plateNumber, plateNumber) == 0)
			{
				isPlateNumberRegistered = true;
				int numberOfCarFines = driverDatabase[i].listOfCars[j].numberOfFines;
				driverDatabase[i].listOfCars[j].listOfFines[numberOfCarFines] = newFine;
				driverDatabase[i].listOfCars[j].numberOfFines++;
				break;
			}
		}			
	}

	if(!isPlateNumberRegistered)
	{

		cout << "Plate number is not registered on the system, please try again!\n";
	}
}

void payCarFines()
{
	cout << "Please enter the car's license number: ";

	char plateNumber[100];
	cin >> plateNumber;
	bool isPlateNumberRegistered = false;
	float totalCarFines = 0;

	for(int i = 0; i < numberOfDrivers; i++)
	{
		for(int j = 0; j < driverDatabase[i].numOfCars; j++)
		{
			if(strcmp(driverDatabase[i].listOfCars[j].plateNumber, plateNumber) == 0)
			{
				int numberOfCarFines = driverDatabase[i].listOfCars[j].numberOfFines;
				driverDatabase[i].listOfCars[j].numberOfFines = 0;
				for(int f = 0; f < numberOfCarFines; f++)
				{
					totalCarFines += driverDatabase[i].listOfCars[j].listOfFines[f].value;
				}
				break;
			}
		}			
	}

	if(!isPlateNumberRegistered)
	{

		cout << "Plate number is not registered on the system, please try again!\n";
	}
	cout << "Total paid =  " << totalCarFines << "\n";
}

void showActiveFines()
{
	char driverFirstName[100];
	char driverLastName[100];
	cout << "Please enter the name of the driver:\n";
	cout << "First: ";
	cin >> driverFirstName;
	cout << "Last: ";
	cin >> driverLastName;
	bool isDriverRegistered = false;
	bool doesDriverHaveActiveFines = false;
	int driverIndex = 0;

	if(nameValidation(driverFirstName) == false)
	{
		cout << "NAME IS NOT VALID!\n";
		return;
	}
	if(nameValidation(driverLastName) == false)
	{
		cout << "NAME IS NOT VALID!\n";
		return;
	}

	for(int i = 0; i < numberOfDrivers; i++)
	{
		if(strcmp(driverDatabase[i].firstName, driverFirstName) == 0 && strcmp(driverDatabase[i].lastName, driverLastName) == 0)
		{
			isDriverRegistered = true;
			driverIndex = i;
			break;
		}
	}

	if(!isDriverRegistered)
	{
		cout << "Driver is not registered on the system, please try again!\n";
		return; 
	}

	cout << "Date | Street name | Value\n";
	for(int i = 0; i < driverDatabase[driverIndex].numOfCars; i++)
	{
		int numberOfCarFines = driverDatabase[driverIndex].listOfCars[i].numberOfFines;
		for(int f = 0; f < numberOfCarFines; f++)
		{
			cout << driverDatabase[driverIndex].listOfCars[i].listOfFines[f].issueDate.day << "/";
			cout << driverDatabase[driverIndex].listOfCars[i].listOfFines[f].issueDate.month << "/";
			cout << driverDatabase[driverIndex].listOfCars[i].listOfFines[f].issueDate.year << ;
			cout << " | " << driverDatabase[driverIndex].listOfCars[i].listOfFines[f].street;
			cout << " | " << driverDatabase[driverIndex].listOfCars[i].listOfFines[f].value;
			cout << "\n";
		}
	}
	cout << "\n\n";
	return;
}			

//////////////////////////////////////////SEARCH///////////////////////////////////////
void searchByPlateNumber()
{
	char plateNumber[100];
	cout << "Please enter the plate number of the car you wish to find:";
	cin >> plateNumber;
	bool isPlateNumberRegistered = false;

	for(int i = 0; i < numberOfDrivers; i++)
	{
		for(int j = 0; j < driverDatabase[i].numOfCars; j++)
		{
			if(strcmp(driverDatabase[i].listOfCars[j].plateNumber, plateNumber) == 0)
			{
				isPlateNumberRegistered = true;
				cout << "Name of driver: " << driverDatabase[i].firstName << " " << driverDatabase[i].lastName << "\n";
				cout << driverDatabase[i].listOfCars[j].plateNumber << " | ";
				cout << driverDatabase[i].listOfCars[j].model << " | ";
				cout << driverDatabase[i].listOfCars[j].productionYear << " | ";
				cout << driverDatabase[i].listOfCars[j].numberOfFines << "\n";
				break;
			}
		}			
	}

	if(!isPlateNumberRegistered)
	{
		cout << "Plate number is not registered on the system, please try again!\n";
	}
	return;
}

void searchByOwner()
{
	char driverFirstName[100];
	char driverLastName[100];
	cout << "Please enter the name of car owner:\n";
	cout << "First: ";
	cin >> driverFirstName;
	cout << "Last: ";
	cin >> driverLastName;
	bool isDriverRegistered = false;
	int driverIndex = 0;


	if(nameValidation(driverFirstName) == false)
	{
		cout << "NAME IS NOT VALID!\n";
		return;
	}
	if(nameValidation(driverLastName) == false)
	{
		cout << "NAME IS NOT VALID!\n";
		return;
	}


	for(int i = 0; i < numberOfDrivers; i++)
	{
		if(strcmp(driverDatabase[i].firstName, driverFirstName) == 0 && strcmp(driverDatabase[i].lastName, driverLastName) == 0)
		{
			isDriverRegistered = true;
			driverIndex = i;
			break;
		}
	}

	if(!isDriverRegistered)
	{
		cout << "Driver is not registered on the system, please try again!\n";
		return; 
	}

	int ownedCars = driverDatabase[driverIndex].numOfCars;
	if(ownedCars == 0)
	{
		cout << "Driver does not have a car registered under their name, please try again!\n";
		return;
	}
	cout << "Plate Number | Model | Year of production | Number of fines\n";
	for (int i = 0; i < ownedCars; i++)
	{
		cout << driverDatabase[driverIndex].listOfCars[i].plateNumber << " | ";
		cout << driverDatabase[driverIndex].listOfCars[i].model << " | ";
		cout << driverDatabase[driverIndex].listOfCars[i].productionYear << " | ";
		cout << driverDatabase[driverIndex].listOfCars[i].numberOfFines << "\n";
		cout << "\n--------------------------------------------------------\n";
	}
	return;
}

//////////////////////////////////////////REGISTERATION///////////////////////////////////////
void registerCar()
{
	int driverIndex = 0;
	cout << "To register a car, please fill in the data below:\n" << endl;
	char driverFirstName[100];
	char driverLastName[100];
	cout << "First name of driver: ";
	cin >> driverFirstName;
	cout << "Last name: ";
	cin >> driverLastName;

	if(nameValidation(driverFirstName) == false)
	{
		cout << "NAME IS NOT VALID!\n";
		return;
	}
	if(nameValidation(driverLastName) == false)
	{
		cout << "NAME IS NOT VALID!\n";
		return;
	}


	bool isDriverRegistered = false;
	for(int i = 0; i < numberOfDrivers; i++)
	{
		if(strcmp(driverDatabase[i].firstName, driverFirstName) == 0 && strcmp(driverDatabase[i].lastName, driverLastName) == 0)
		{
			isDriverRegistered = true;
			driverIndex = i;
			break;
		}
	}
	if(!isDriverRegistered)
	{
		cout << "Driver is not registered on the system, please try again!\n";
		return; 
	}
	int ownedCars = driverDatabase[driverIndex].numOfCars;
	if(ownedCars > maxNumOfCars)
	{
		cout << "Driver exceeds the limit of the maximum possible number of owned cars, please try again!\n";
		return;
	}
	//////////////////////////////////////////////////////////////////////
	car newCar;
	cout << "Plate number: ";
	cin >> newCar.plateNumber;
	cout << "Model: ";
	cin >> newCar.model;
	cout << "Year of production: ";
	cin >> newCar.productionYear;
	if(newCar.productionYear > currentYear)
	{
		cout << "Invalid year of production, please try again!\n";
		return;
	}
	driverDatabase[driverIndex].listOfCars[ownedCars] = newCar;
	driverDatabase[driverIndex].numOfCars++;
	return;
}


void registerDriver()
{
	ClearScreen();
	cout << "To register a driver, please fill in the data below:\n";
	person driver;
	cout << "First name: ";
	cin >> driver.firstName;
	cout << "Last name: ";
	cin >> driver.lastName;
	//VALIDATION THAT NAME IS PROPER AND DOES NOT EXIST ON SYSTEM
	if(nameValidation(driver.firstName) == false)
	{
		cout << "NAME IS NOT VALID!\n";
		return;
	}
	if(nameValidation(driver.lastName) == false)
	{
		cout << "NAME IS NOT VALID!\n";
		return;
	}


	for(int i = 0; i < numberOfDrivers; i++)
	{
		if(strcmp(driver.firstName, driverDatabase[i].firstName) == 0 && strcmp(driver.lastName, driverDatabase[i].lastName) == 0)
		{
			cout << "NAME ALREADY EXISTS ON DATABASE!\n";
			return;
		}		
	}
	////////////////////////////////////////////////////////

	cout << "License number: ";
	cin >> driver.license;
	//VALIDATION THAT LICENSE DOES NOT EXIST ON SYSTEM
	for(int i = 0; i < numberOfDrivers; i++)
	{
		if(strcmp(driver.license, driverDatabase[i].license) == 0)
		{
			cout << "LICENSE ALREADY EXISTS ON DATABASE!\n";
			return;
		}
	}

	date driverDOB;
	cout << "Please enter the driver's date of birth:\n";
	cout << "Day: ";
	cin >> driverDOB.day;
	cout << "Month (in numbers): ";
	cin >> driverDOB.month;
	cout << "Year: ";
	cin >> driverDOB.year;
	//VALIDATION THAT DRIVER IS OLDER THAN 18 years
	int ageInDays = driverDOB.year * 365;
	ageInDays += driverDOB.month * 30;
	ageInDays += driverDOB.day;
	if(ageInDays < 18 * 365)
	{
		cout << driver.firstName << " " << driver.lastName << " is too young to get a driver's license.\n";
		return;
	}
	driver.birthdate = driverDOB;
	driverDatabase[numberOfDrivers] = driver;
	numberOfDrivers++;
	return;
}

/////////////////////////////////////////////MENUS////////////////////////////////////////////
void carSearchMenuPrompt()
{
	int userAction;	
	cout << "--------------------------------------------------------\n";
	cout << "Car Search\n";
	cout << "--------------------------------------------------------\n";
	cout << "How would you like to find the car?\n";
	cout << "[1] By car owner name\n";
	cout << "[2] By plate number\n";
	cout << "[3] Go back to previous menu\n";
	cout << "[0] Exit program\n";
	cout << "Your choice: ";
	cin >> userAction;
	switch(userAction)
	{
		case 1:
			searchByOwner();
			break;
		case 2:
			searchByPlateNumber();
			break;
		case 3:
			carUserMenuPrompt();
			break;
		case 0:
			exitHandler = 0;
			break;
		default:
			cout << "Invalid choice, please try again!\n\n\n";
			carSearchMenuPrompt();
			break;
	}
}
void carUserMenuPrompt()
{
	int userAction;
	cout << "--------------------------------------------------------\n";
	cout << "User and Car management system:\n";
	cout << "--------------------------------------------------------\n";
	cout << "What would you like to do today?\n";
	cout << "[1] Search for a car\n";
	cout << "[2] Register a car\n";
	cout << "[3] Register a driver\n";
	cout << "[4] Go back to previous menu\n";
	cout << "[0] Exit program\n";
	cout << "Your choice: ";
	cin >> userAction;
	switch(userAction)
	{
		case 1:
			carSearchMenuPrompt();
			break;
		case 2:
			registerCar();
			break;
		case 3:
			registerDriver();
			break;
		case 4:
			mainMenuPrompt();
			break;
		case 0:
			exitHandler = 0;
			break;
		default:
			cout << "Invalid choice, please try again!\n\n\n";
			carUserMenuPrompt();
			break;
	}
}

void fineMenuPrompt()
{
	int userAction;
	cout << "--------------------------------------------------------\n";
	cout << "Fine management system:\n";
	cout << "--------------------------------------------------------\n";
	cout << "What would you like to do today?\n";
	cout << "[1] Add a fine\n";
	cout << "[2] Pay fines for a car\n";
	cout << "[3] Show all fines for a driver\n";
	cout << "[4] Go back to previous menu\n";
	cout << "[0] Exit program\n";
	cout << "Your choice: ";
	cin >> userAction;
	switch(userAction)
	{
		case 1:
			addFine();
			break;
		case 2:
			payCarFines();
			break;
		case 3:
			showActiveFines();
			break;
		case 4:
			mainMenuPrompt();
			break;
		case 0:
			exitHandler = 0;
			break;
		default:
			cout << "Invalid choice, please try again!\n\n\n";
			fineMenuPrompt();
			break;
	}
}

void mainMenuPrompt()
{
	int userAction;
	cout << "--------------------------------------------------------\n";
	cout << "Hello, welcome to the traffic control management system!\n";
	cout << "--------------------------------------------------------\n";
	cout << "What would you like to do today?\n";
	cout << "[1] User & car management system\n";
	cout << "[2] Fine management system\n";
	cout << "[0] Exit\n";
	cout << "Your choice: ";
	cin >> userAction;
	switch(userAction)
	{
		case 0:
		exitHandler = 0;
			break;
		case 1:
			carUserMenuPrompt();
			break;
		case 2:
			fineMenuPrompt();
			break;
		default:
			cout << "Invalid choice, please try again!\n\n\n";
			mainMenuPrompt();
			break;
	}

	//EXIT PROGRAM FROM ANY MENU HANDLER
	if(exitHandler != 0)
	{
		mainMenuPrompt();
	}
	else
	{
		cout << "Thank you for using the traffic control management system!\n";
		return;
	}
}

int main ()
{
	mainMenuPrompt();
}