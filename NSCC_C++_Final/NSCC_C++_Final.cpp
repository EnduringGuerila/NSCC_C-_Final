// NSCC_C++_Final.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct container {
	int treeNo[999];
	int species[999];
	float dbh[999];
	int totalHt[999];
	double totalVol[999];
};

int getTreeNo();
int getSpeciesCode();
float getDbh();
int getTotHt();
double calcTotVol(float dbh, int totalHt, int species);
void displayTreeData(container tre, int totalTrees);




int main()
{
	cout << "     *********************************************************************" << endl;
	cout << "     *                                                                   *" << endl;
	cout << "     *        This program 'logs' tree information for inventory         *" << endl;
	cout << "     *                                                                   *" << endl;
	cout << "     *********************************************************************" << endl << endl;

	container tre;
	int index = 0;

	tre.treeNo[index] = getTreeNo();

	while (tre.treeNo[index] != 999)
	{
		tre.species[index] = getSpeciesCode();

		tre.dbh[index] = getDbh();
		tre.totalHt[index] = getTotHt();
		tre.totalVol[index] = calcTotVol(tre.dbh[index], tre.totalHt[index], tre.species[index]);

		index++;
		cout << endl << endl;
		tre.treeNo[index] = getTreeNo();
	}

	displayTreeData(tre, index);


	system("pause");
	return 0;
}

// *******************************************************************************************************************************************************

int getTreeNo()
{
	int treeNo = 1000;
	do
	{
		cout << "Enter Tree Number: \n";
		treeNo = 1000;
		cin >> treeNo;
		if (treeNo > 999 || treeNo < 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\n\nError, incorrect input. (must be a whole number greater than 0 and less than 1000\n";
		}


	} while (treeNo > 999 || treeNo < 0);

	return treeNo;
}

// *******************************************************************************************************************************************************

int getSpeciesCode()
{
	int speciesCode;
	bool goodCode;
	//string Desc[6];

	do 
	{
		cout << "\n       (    11 = Balsam Fir, 12 = Black Spruce, 13 = Black Pine,    )\n       ( 21 = Trembling Ash, 22 = White Birch, 23 = Other Hardwoods )\nPlease enter the species code: \n";

		cin >> speciesCode;

		switch (speciesCode) {
		case 11: {
			speciesCode = 0;
			goodCode = true;
			break;
		}
		case 12: {
			speciesCode = 1;
			goodCode = true;
			break;
		}
		case 13: {
			speciesCode = 2;
			goodCode = true;
			break;
		}
		case 21: {
			speciesCode = 3;
			goodCode = true;
			break;
		}
		case 22: {
			speciesCode = 4;
			goodCode = true;
			break;
		}
		case 23: {
			speciesCode = 5;
			goodCode = true;
			break;
		}
		default: {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Species Code entered. \n\n";
			goodCode = false;
		}
		}
	} while (goodCode == false);

	return speciesCode;
}

// *******************************************************************************************************************************************************

float getDbh()
{
		cout << "\n";
	float dbh = 0;
	do
	{
		cout << "Enter tree diameter breast height (DBH) value: \n( 5 - 50.6   inches )\n";
		dbh = 0;
		cin >> dbh;
		if (dbh > 50.6 || dbh < 5) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\n\nError, incorrect input. \n(must be a whole number greater than 5 and less than 50.6\n\n";
		}


	} while (dbh > 50.6 || dbh < 5);

	return dbh;
}

// *******************************************************************************************************************************************************

int getTotHt()
{
	cout << "\n";
	int totHt = 0;
	bool badCode;

	do
	{
		cout << "Enter Tree Height value (the closest even integer): \n( 22 - 180  feet )\n";
		badCode = false;
		totHt = 0;
		cin >> totHt;
		
		if (totHt > 180 || totHt < 22) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nError, incorrect input. \n(must be a whole number greater than 2 and less than 180\n\n";
			badCode = true;
		}
		else if (totHt % 2 != 0) {
			cout << "\nError! Tree height must be entered as an even number.\n(22, 24, ...178, 180, etc)\n\n";
			badCode = true;
		}


	} while (badCode);

	return totHt;
}

// *******************************************************************************************************************************************************

double calcTotVol(float dbh, int totalHt, int species)
{
		cout << "\n";
	double totalVol = 0;
	float b0[6] = {1.3686, 0.000, 2.1892, 0.8528, 1.7478, 0.7668};
	float b1[6] = {.002182, .002468, .002052, .002251, .002142, .002164};


	totalVol = b0[species] + (b1[species] * dbh * dbh * totalHt);

	return totalVol;
}

// *******************************************************************************************************************************************************

void displayTreeData(container tre, int totalTrees)
{
	cout << "\n \n";  

	ofstream outFile;
	outFile.open("report.dat");
	string specDesc[6] = { "Balsam Fir", "Black Spruce", "Black Pine", "Trembling Ash", "White Birch", "Other Hardwoods" };
	int species[6] = { 11, 12, 13, 21, 22, 23 };
	double avgTotVol = 0;
	
	cout    << "TreeNo | Species |    Description  |  DBH | Tot Ht | Tot Vol" << endl;
	outFile << "TreeNo | Species |    Description  |  DBH | Tot Ht | Tot Vol" << endl;

	for (int counter = 0; counter < totalTrees; counter++) 
	{
		cout << fixed << setprecision(1)
			<< setw(6) << tre.treeNo[counter] << " |" 
			<< setw(8) << species[tre.species[counter]] << " |"
			<< setw(16) << specDesc[tre.species[counter]] << " |" 
			<< setw(5) << tre.dbh[counter]  << " |" 
			<< setw(6) << tre.totalHt[counter]  << "  |" 
			<< fixed << setprecision(3)
			<< setw(8) << tre.totalVol[counter];
		cout << endl;

		
		outFile << fixed << setprecision(1)
			<< setw(6) << tre.treeNo[counter] << " |" 
			<< setw(8) << species[tre.species[counter]] << " |"
			<< setw(16) << specDesc[tre.species[counter]] << " |" 
			<< setw(5) << tre.dbh[counter]  << " |" 
			<< setw(6) << tre.totalHt[counter]  << "  |" 
			<< fixed << setprecision(3)
			<< setw(8) << tre.totalVol[counter];
		outFile << endl;

		avgTotVol = (avgTotVol + static_cast<double>(tre.totalVol[counter])) / totalTrees;
	}

	cout    << "\n\nTotal trees entered: " << totalTrees << endl;
	cout    << "Average tree volume: " << avgTotVol << endl << endl;

	outFile << "\n\nTotal trees entered: " << totalTrees << endl;
	outFile << "Average tree volume: " << avgTotVol << endl << endl;

	outFile.close();
	return;
}