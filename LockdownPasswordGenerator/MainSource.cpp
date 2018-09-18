#include <iostream>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <Synchapi.h>
#include <stdexcept>
#include <limits>
#include <fstream>
#include <ctime>
#include <atlstr.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
/******************************************************************************************************/
/* GLOBAL VARIABLES */
const int numbersStart = 0, numbersEnd = 10;
const int lowercaseStart = 10, lowercaseEnd = 36;
const int allLettersStart = 10, allLettersEnd = 62;
const int allSymbolsStart = 0, allSymbolsEnd = 94;

char symbolArray[allSymbolsEnd];

string currentFiletype = ".txt";
/******************************************************************************************************/
void nullFunction() {
	/*

	This is a note-only function. Do not call this in regular code.
	Use the codes below in conjunction with console color changing functions to generate colors.

	const Color NORMAL  = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE;
	const Color WHITE   = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY;
	const Color RED     = FOREGROUND_RED|FOREGROUND_INTENSITY;
	const Color DKRED   = FOREGROUND_RED;
	const Color BLUE    = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY;
	const Color DKBLUE  = FOREGROUND_BLUE|FOREGROUND_GREEN;
	const Color GREEN   = FOREGROUND_GREEN|FOREGROUND_INTENSITY;
	const Color DKGREEN = FOREGROUND_GREEN;
	const Color YELLOW  = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY;
	const Color BROWN   = FOREGROUND_RED|FOREGROUND_GREEN;

	*/
}//end nullFunction
/******************************************************************************************************/
WORD GetConsoleTextAttribute(HANDLE hCon) {
	CONSOLE_SCREEN_BUFFER_INFO con_info;
	GetConsoleScreenBufferInfo(hCon, &con_info);
	return con_info.wAttributes;
}//end GetConsoleTextAttribute
/******************************************************************************************************/
void showError(string displayText) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << displayText;
	SetConsoleTextAttribute(hConsole, saved_colors);
}
/******************************************************************************************************/
void showMessage(string displayText) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << displayText;
	SetConsoleTextAttribute(hConsole, saved_colors);
}//end showMessage
/******************************************************************************************************/
void showData(string displayText) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << displayText;
	SetConsoleTextAttribute(hConsole, saved_colors);
}//end showData
/******************************************************************************************************/
void showLabel(string displayText) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << displayText;
	SetConsoleTextAttribute(hConsole, saved_colors);
}//end showLabel
/******************************************************************************************************/
void showPassword(string password) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | FOREGROUND_RED |
		FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << password;
	SetConsoleTextAttribute(hConsole, saved_colors);
}//end showPassword (strings)
/******************************************************************************************************/
void showPassword(char password) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | FOREGROUND_RED |
		FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << password;
	SetConsoleTextAttribute(hConsole, saved_colors);
}//end showPassword (chars)
/******************************************************************************************************/
void showKey(char key) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << key;
	SetConsoleTextAttribute(hConsole, saved_colors);
}//end showKey
/******************************************************************************************************/
string getTime() {
	string timeVar;
	time_t now = time(0);
	char buf[80];
	struct tm timeInfo;
	localtime_s(&timeInfo, &now);
	strftime(buf, sizeof(buf), "%d.%m.%Y@%H.%M.%S", &timeInfo);
	return buf;
}//end getTime
/******************************************************************************************************/
void executeFile(string filepathIn) {
	CString filepath = filepathIn.c_str();
	CString action = "open";
	ShellExecute(NULL, action, filepath, NULL, NULL, SW_SHOW);
}//end executeFile
/******************************************************************************************************/
void deleteFile(string filepathIn) {
	const char* filepath = filepathIn.c_str();
	remove(filepath);
}//end deleteFile
/******************************************************************************************************/
void writeKeysToFile(char* generatedKey, int numberOfKeys, int totalDigits) {
	string timeString = getTime();
	string path = "Lockdown_Generated_Keys_" + timeString + currentFiletype;
	ofstream generatedKeysFile(path);

	if (numberOfKeys == 1) 	generatedKeysFile << "Lockdown has generated " << numberOfKeys << " key:\n";
	else generatedKeysFile << "Lockdown has generated " << numberOfKeys << " keys:\n";

	for (int i = 0; i < numberOfKeys; i++) {
		generatedKeysFile << generatedKey[i];
	}
	generatedKeysFile << endl;

	generatedKeysFile.close();
	executeFile(path); Sleep(1000);
	deleteFile(path);
}//end writeKeysToFile
/******************************************************************************************************/
void writePasswordToFile(string generatedPassword, int length) {
	string timeString = getTime();
	string path = "Lockdown_Generated_Password_" + timeString + ".txt";
	ofstream generatedPasswordFile(path);

	generatedPasswordFile << "Copy this password for use. It will be lost on exit.\n";
	generatedPasswordFile << "Lockdown has generated the following password:\n";


	for (int i = 0; i < length; i++) {
		generatedPasswordFile << generatedPassword[i];
	}//end for

	cout << endl;

	generatedPasswordFile.close();
	executeFile(path); Sleep(1000);
	deleteFile(path);
}//end writePasswordToFile
/******************************************************************************************************/
void initializeEnvironment() {
	system("Color A");
	system("Title \"Lockdown\" Key/Password Generator");
	srand(time(NULL));
}//end initializeEnvironment
/******************************************************************************************************/
void clearScreen() {
	system("CLS");
}
/******************************************************************************************************/
void stop() {
	system("exit");
}
/******************************************************************************************************/
void pause() {
	system("pause");
}
/******************************************************************************************************/
void printHeader() {
	cout << "*******************************************************************************" << endl;
	cout << "*********************** LOCKDOWN KEY/PASSWORD GENERATOR ***********************" << endl;
	cout << "*******************************************************************************" << endl;
	cout << "**                                                                           **" << endl;
}//end printHeader
/******************************************************************************************************/
void initializeArrays() {
	//NUMBERS SUB-ARRAY: 0-9
	symbolArray[0] = '0'; 	symbolArray[1] = '1'; 	symbolArray[2] = '2';
	symbolArray[3] = '3'; 	symbolArray[4] = '4'; 	symbolArray[5] = '5';
	symbolArray[6] = '6'; 	symbolArray[7] = '7'; 	symbolArray[8] = '8';
	symbolArray[9] = '9';

	//LOWERCASE LETTERS SUBARRAY: 10-35
	symbolArray[10] = 'a'; 	symbolArray[11] = 'b'; 	symbolArray[12] = 'c';
	symbolArray[13] = 'd'; 	symbolArray[14] = 'e'; 	symbolArray[15] = 'f';
	symbolArray[16] = 'g'; 	symbolArray[17] = 'h'; 	symbolArray[18] = 'i';
	symbolArray[19] = 'j'; 	symbolArray[20] = 'k'; 	symbolArray[21] = 'l';
	symbolArray[22] = 'm'; 	symbolArray[23] = 'n'; 	symbolArray[24] = 'o';
	symbolArray[25] = 'p'; 	symbolArray[26] = 'q'; 	symbolArray[27] = 'r';
	symbolArray[28] = 's'; 	symbolArray[29] = 't'; 	symbolArray[30] = 'u';
	symbolArray[31] = 'v'; 	symbolArray[32] = 'w'; 	symbolArray[33] = 'x';
	symbolArray[34] = 'y'; 	symbolArray[35] = 'z';

	//UPPERCASE LETTERS SUBARRAY: 36-61
	symbolArray[36] = 'A'; 	symbolArray[37] = 'B'; 	symbolArray[38] = 'C';
	symbolArray[39] = 'D'; 	symbolArray[40] = 'E'; 	symbolArray[41] = 'F';
	symbolArray[42] = 'G'; 	symbolArray[43] = 'H'; 	symbolArray[44] = 'I';
	symbolArray[45] = 'J'; 	symbolArray[46] = 'K'; 	symbolArray[47] = 'L';
	symbolArray[48] = 'M'; 	symbolArray[49] = 'N'; 	symbolArray[50] = 'O';
	symbolArray[51] = 'P'; 	symbolArray[52] = 'Q'; 	symbolArray[53] = 'R';
	symbolArray[54] = 'S'; 	symbolArray[55] = 'T'; 	symbolArray[56] = 'U';
	symbolArray[57] = 'V'; 	symbolArray[58] = 'W'; 	symbolArray[59] = 'X';
	symbolArray[60] = 'Y'; 	symbolArray[61] = 'Z';

	//SPECIAL SYMBOLS SUBARRAY: 62-94
	symbolArray[62] = '`'; 	symbolArray[63] = '~'; 	symbolArray[64] = '!';
	symbolArray[65] = '@'; 	symbolArray[66] = '#'; 	symbolArray[67] = '$';
	symbolArray[68] = '%'; 	symbolArray[69] = '^'; 	symbolArray[70] = '&';
	symbolArray[71] = '('; 	symbolArray[72] = ')'; 	symbolArray[73] = '-';
	symbolArray[74] = '_'; 	symbolArray[75] = '='; 	symbolArray[76] = '+';
	symbolArray[77] = '['; 	symbolArray[78] = '{'; 	symbolArray[79] = ']';
	symbolArray[80] = '}'; 	symbolArray[81] = '\\'; symbolArray[82] = '|';
	symbolArray[83] = ';'; 	symbolArray[84] = ':'; 	symbolArray[85] = '\'';
	symbolArray[86] = '"'; 	symbolArray[87] = ','; 	symbolArray[88] = '<';
	symbolArray[89] = '.'; 	symbolArray[90] = '>'; 	symbolArray[91] = '/';
	symbolArray[92] = '*'; 	symbolArray[93] = '?'; 	symbolArray[94] = ' ';
}//end initalizeArrays
/******************************************************************************************************/
void generateNumbers() {
	int digitNum = -1;
	do {
		clearScreen();
		printHeader();
		cout << "**  NUMERIC PASSWORD GENERATOR                                               **" << endl;
		cout << "**                                                                           **" << endl;
		cout << "*******************************************************************************" << endl;
		showMessage("Enter number of digits to generate (4-32), or 0 to Cancel: "); cin >> digitNum;
	} while ((digitNum != 0) && (digitNum < 4) || (digitNum > 32));

	if (digitNum != 0) {
		char* generatedArray;
		generatedArray = new char[digitNum];
		for (int i = 0; i < digitNum; i++) {
			int randomNumber = (rand() % (numbersEnd)+numbersStart);
			generatedArray[i] = symbolArray[randomNumber];
		} //end for

		showMessage("Generated Password: ");
		for (int i = 0; i < digitNum; i++) {
			showPassword(generatedArray[i]);
		} //end for
		cout << endl;
		//writePasswordToFile(generatedArray, digitNum);    ENABLE THIS LATER
		pause();
	}//end if not 0
	else {
		showMessage("Cancelling...\n"); /*Sleep(2000); ENABLE THIS LATER*/
	}//end else
}//end generateNumbers
/******************************************************************************************************/
void generateLetters() {
	int digitNum = -1;
	bool isLowercaseOnly = false;
	bool validInput = false;
	char lowercaseOnlyChar;
	do {
		clearScreen();
		printHeader();
		cout << "**  ALPHABETIC PASSWORD GENERATOR                                            **" << endl;
		cout << "**                                                                           **" << endl;
		cout << "*******************************************************************************" << endl;

		do {
			showMessage("Generate lowercase-only password? (Y/N): "); cin >> lowercaseOnlyChar;
			if ((lowercaseOnlyChar == 'Y') || (lowercaseOnlyChar == 'y') || (lowercaseOnlyChar == 'n') || (lowercaseOnlyChar == 'N'))
				validInput = true;
			else validInput = false;
		} while (validInput == false);

		if ((lowercaseOnlyChar == 'Y') || (lowercaseOnlyChar == 'y')) isLowercaseOnly = true;
		else isLowercaseOnly = false;

		showMessage("Enter number of digits to generate (4-32), or 0 to Cancel: "); cin >> digitNum;
	} while ((digitNum != 0) && (digitNum < 4) || (digitNum > 32));

	if (digitNum != 0) {
		char* generatedArray;
		generatedArray = new char[digitNum];

		if (isLowercaseOnly) {
			for (int i = 0; i < digitNum; i++) {
				int randomNumber = (rand() % (lowercaseEnd - lowercaseStart) + lowercaseStart);
				generatedArray[i] = symbolArray[randomNumber];
			} //end for
		}//end if isLowerCaseOnly
		else {
			for (int i = 0; i < digitNum; i++) {
				int randomNumber = (rand() % (allLettersEnd - allLettersStart) + allLettersStart);
				generatedArray[i] = symbolArray[randomNumber];
			} //end for
		}//end if NOT isLowercaseOnly

		showMessage("Generated Password: ");
		for (int i = 0; i < digitNum; i++) {
			showPassword(generatedArray[i]);
		} //end for
		cout << endl;
		//writePasswordToFile(generatedArray, digitNum);    ENABLE THIS LATER
		pause();
	}//end if not 0
	else {
		showMessage("Cancelling...\n"); /*Sleep(2000); ENABLE THIS LATER*/
	}//end else
}//end generateLetters
/******************************************************************************************************/
void generateAlphanumeric() {
	int digitNum = -1;
	do {
		clearScreen();
		printHeader();
		cout << "**  ALPHANUMERIC PASSWORD GENERATOR                                          **" << endl;
		cout << "**                                                                           **" << endl;
		cout << "*******************************************************************************" << endl;
		showMessage("Enter number of digits to generate (4-32), or 0 to Cancel: "); cin >> digitNum;
	} while ((digitNum != 0) && (digitNum < 4) || (digitNum > 32));

	if (digitNum != 0) {
		char* generatedArray;
		generatedArray = new char[digitNum];
		for (int i = 0; i < digitNum; i++) {
			int randomNumber = (rand() % (allLettersEnd));
			generatedArray[i] = symbolArray[randomNumber];
		} //end for

		showMessage("Generated Password: ");
		for (int i = 0; i < digitNum; i++) {
			showPassword(generatedArray[i]);
		} //end for
		cout << endl;
		//writePasswordToFile(generatedArray, digitNum);    ENABLE THIS LATER
		pause();
	}//end if not 0
	else {
		showMessage("Cancelling...\n"); /*Sleep(2000); ENABLE THIS LATER*/
	}//end else
}//end generateAlphanumeric
/******************************************************************************************************/
void generateSymbols() {
	int digitNum = -1;
	do {
		clearScreen();
		printHeader();
		cout << "**  ALPHANUMERIC PASSWORD GENERATOR                                          **" << endl;
		cout << "**                                                                           **" << endl;
		cout << "*******************************************************************************" << endl;
		showMessage("Enter number of digits to generate (4-32), or 0 to Cancel: "); cin >> digitNum;
	} while ((digitNum != 0) && (digitNum < 4) || (digitNum > 32));

	if (digitNum != 0) {
		char* generatedArray;
		generatedArray = new char[digitNum];
		for (int i = 0; i < digitNum; i++) {
			int randomNumber = (rand() % (allSymbolsEnd));
			generatedArray[i] = symbolArray[randomNumber];
		} //end for

		showMessage("Generated Password: ");
		for (int i = 0; i < digitNum; i++) {
			showPassword(generatedArray[i]);
		} //end for
		cout << endl;
		//writePasswordToFile(generatedArray, digitNum);    ENABLE THIS LATER
		pause();
	}//end if not 0
	else {
		showMessage("Cancelling...\n"); /*Sleep(2000); ENABLE THIS LATER*/
	}//end else
}//end generateSymbols
/******************************************************************************************************/
void generateFromKeyword() {
	string keyword;
	int digitNum = -1;
	int diff = 0;
	int maxNumberOfDigits = 32;

	do {
		clearScreen();
		printHeader();
		cout << "**  KEYWORD-BASED PASSWORD GENERATOR                                         **" << endl;
		cout << "**                                                                           **" << endl;
		cout << "*******************************************************************************" << endl;
		showMessage("Enter keyword (Length 3-16): "); cin >> keyword;
	} while ((keyword.empty()) || (keyword.length() > 16) || (keyword.length() < 3));

	diff = maxNumberOfDigits - keyword.length();

	do {
		showMessage("Enter additional number of characters (1-"); showMessage(to_string(diff)); showMessage(") or 0 to Cancel: ");
		cin >> digitNum;
	} while ((digitNum != 0) && (digitNum < 1) || (digitNum > diff));

	if (digitNum != 0) {
		char* generatedArray = new char[digitNum];
		for (int i = 0; i < digitNum; i++) {
			int randomNumber = (rand() % (allSymbolsEnd));
			generatedArray[i] = symbolArray[randomNumber];
		} //end for

		string combinedPassString;
		int totalDigits = keyword.length() + digitNum;
		char* combinedPass = new char[totalDigits];
		showMessage("Generated Password: ");
		combinedPassString = keyword + generatedArray;
		
		//Copy from char* to string array to be able to print in file using writePasswordToFile()
		for (int i = 0; i < totalDigits; i++) {
			combinedPass[i] = combinedPassString[i];
		}//end copy String to Char*

		//Show each character indivudually using showPassword()
		for (int i = 0; i < totalDigits; i++) {
			showPassword(combinedPass[i]);
		}//end show string as chars pass

		cout << endl;
		writePasswordToFile(combinedPass, totalDigits);    //ENABLE THIS LATER
		pause();
	}//end if NOT 0
	else {
		showMessage("Cancelling...\n"); /*Sleep(2000); ENABLE THIS LATER*/
	}//end else

}//end generateFromKeyword
/******************************************************************************************************/
void generateKeys() {
	int keyNum = -1;
	do {
		clearScreen();
		printHeader();
		cout << "**  KEY GENERATOR                                                            **" << endl;
		cout << "**                                                                           **" << endl;
		cout << "*******************************************************************************" << endl;
		showMessage("      Keys will be generated in the form: XXXX-XXXX-XXXX-XXXX \n");
		showMessage("Enter number of keys to generate (1-10,000), or 0 to Cancel: "); cin >> keyNum;
	} while ((keyNum != 0) && (keyNum < 1) || (keyNum > 10000));

	char** allKeys = new char*[keyNum]; //store keys here

	if (keyNum != 0) {

		for (int j = 0; j < keyNum; j++) {
			int digitsPerBatch = 4; //could be changed by user in later upgrades
			int totalBatches = 4; // could be changed by user in later upgrades
			int separators = 3; //could be change by user in later upgrades
			int totalDigits = totalBatches*digitsPerBatch + separators;
			char* firstBatch = new char[digitsPerBatch];
			char* secondBatch = new char[digitsPerBatch];
			char* thirdBatch = new char[digitsPerBatch];
			char* fourthBatch = new char[digitsPerBatch]; //needs to be a linked list later for dynamic keys
			char separator = '-';

			char* combinedKey = new char[totalDigits+1]; //hardwired to be 19 for now


			for (int i = 0; i < digitsPerBatch; i++) {
				int randomNumber = (rand() % lowercaseEnd);
				firstBatch[i] = symbolArray[randomNumber];
			} //end first batch

			for (int i = 0; i < digitsPerBatch; i++) {
				int randomNumber = (rand() % lowercaseEnd);
				secondBatch[i] = symbolArray[randomNumber];
			} //end second batch

			for (int i = 0; i < digitsPerBatch; i++) {
				int randomNumber = (rand() % lowercaseEnd);
				thirdBatch[i] = symbolArray[randomNumber];
			} //end third batch

			for (int i = 0; i < digitsPerBatch; i++) {
				int randomNumber = (rand() % lowercaseEnd);
				fourthBatch[i] = symbolArray[randomNumber];
			} //end fourth batch

			combinedKey[4] = separator; //shift by 0 from a divisor
			combinedKey[9] = separator; //shift by 1 from a divisor
			combinedKey[14] = separator; //shift by 2 from a divisor
			//etc....
			//need to be dynamically found according to key configuration later

			for (int i = 0; i < digitsPerBatch; i++) {
				combinedKey[i] = firstBatch[i];
			}//copy first batch

			for (int i = 5; i < 9; i++) { //i has to be found dynamically later 
				combinedKey[i] = secondBatch[i - 5];
			}//copy second batch

			for (int i = 10; i < 14; i++) { //i has to be found dynamically later 
				combinedKey[i] = thirdBatch[i - 10];
			}//copy third batch

			for (int i = 15; i < 19; i++) { //i has to be found dynamically later 
				combinedKey[i] = fourthBatch[i - 15];
			}//copy fourth batch

			//Convert entire key to uppercase
			for (int i = 0; i < totalDigits; i++) {
				combinedKey[i] = toupper(combinedKey[i]);
			}//end for

			//Display the key
			for (int i = 0; i < totalDigits; i++) {
				showKey(combinedKey[i]);
			}//end for

			allKeys[j] = combinedKey;
			cout << endl;
			
			for (int x = 0; x < keyNum; x++) {
				writeKeysToFile(allKeys[x], keyNum, totalDigits); 
			}
		}//end if not 0
	}//end FOR (NUMBER OF KEYS)
	else {
		showMessage("Cancelling...\n");
	}//end else
	pause();
}//end generateKeys
/******************************************************************************************************/
string changeFiletype() {
	string filetype = currentFiletype;
	int choice = -1;
	do {
		clearScreen();
		printHeader();
		cout << "**  CURRENT DATA FILE TYPE: "; showData(currentFiletype); cout << "                                             **" << endl;
		cout << "**                                                                           **" << endl;
		cout << "**  Options:                                                                 **" << endl;
		cout << "**       1. Text File (.txt)                                                 **" << endl;
		cout << "**       2. Comma Delimited File (.csv)                                      **" << endl;
		cout << "**       0. Cancel                                                           **" << endl;
		cout << "**                                                                           **" << endl;
		cout << "*******************************************************************************" << endl;
		showMessage("Please select filetype (1-2 or 0 to Cancel): "); cin >> choice;

		if (choice == 0) {
			showMessage("Cancelling...\n"); /*Sleep(2000); ENABLE THIS LATER*/
		}
		else if (choice == 1) {
			filetype = ".txt";
			showMessage("Filetype set to Text File (.txt)\n");
			pause();
		}
		else if (choice == 2) {
			filetype = ".csv";
			showMessage("Filetype set to Comma Delimited File (.csv)\n");
			pause();
		}
		else {
			showError("Wrong choice provided. Pick an option from the menu above.\n");
			pause();
		}

	} while ((choice < 0) || (choice > 2));

	return filetype;
}
/******************************************************************************************************/
void displayInfo() {
	clearScreen();
	printHeader();
	cout << "**  APPLICATION INFORMATION                                                  **" << endl;
	cout << "**                                                                           **" << endl;
	cout << "*******************************************************************************" << endl;
	showData("Created by HF-November\n");
	showData("Version 0 Build 0 - Month Year\n");
	showData("------------------------------------------------------------------------------\n");
	showData("    This application was designed to generate random numeric, alphanumeric    \n");
	showData("  all-symbol and keyword-based passwords of different complexities. It has    \n");
	showData("  been exclusively programmed by HF-November and its source code is available \n");
	showData("  at: http://dev.hfnovember.com                                               \n");
	showData("------------------------------------------------------------------------------\n");
	showData("    Password Complexities:                                                    \n");
	showData(" NUMERIC PASSWORDS                   -- 10,000 Permutations / 4 Digits        \n");
	showData(" LOWERCASE ALPHABETIC PASSWORDS      -- 390,625 Permutations / 4 Digits       \n");
	showData(" ALPHABETIC PASSWORDS                -- 6,250,000 Permutations / 4 Digits     \n");
	showData(" ALL-SYMBOL PASSWORDS                -- 81,450,625 Permutations / 4 Digits    \n");
	showData("------------------------------------------------------------------------------\n");
	pause();
}//end displayInfo
/******************************************************************************************************/
void displayMenu() {
	int userInput = -1;
	do {
		clearScreen();
		printHeader();
		cout << "**-------------------- MENU ---------------------\\   "; showLabel("Created by HF-November"); cout << "  **" << endl;
		cout << "** 1. Generate Numeric Password                  |   "; showLabel("Version 0 Build 1"); cout << "       **" << endl;
		cout << "** 2. Generate Alphabetic Password               |   "; showLabel("04 Aug 2015"); cout << "             **" << endl;
		cout << "** 3. Generate Alphanumeric Password             |                           **" << endl;
		cout << "** 4. Generate All-Symbol Password               |                           **" << endl;
		cout << "** 5. Generate Keyword-based Password            |                           **" << endl;
		cout << "** 6. Generate Keys                              |                           **" << endl;
		cout << "** 7. Change default filetype (Current: "; showData(currentFiletype); cout << ")    |                           **" << endl;
		cout << "** 8. Display Application Info                   |                           **" << endl;
		cout << "** 0. Exit                                       |                           **" << endl;
		cout << "**-----------------------------------------------/                           **" << endl;
		cout << "**                                                                           **" << endl;
		cout << "*******************************************************************************" << endl;
		cout << endl;
		cout << "Choice (0-8): "; cin >> userInput;
		switch (userInput) {
		case 1: generateNumbers(); break;
		case 2: generateLetters(); break;
		case 3: generateAlphanumeric(); break;
		case 4: generateSymbols(); break;
		case 5: generateFromKeyword(); break;
		case 6: generateKeys(); break;
		case 7: currentFiletype = changeFiletype(); break;
		case 8: displayInfo(); break;
		case 0: showMessage("Exiting...\n"); /*Sleep(2000); ENABLE THIS LATER*/ clearScreen(); break;
		default: showError("Invalid User Option! Valid options range from 0 to 4.\n"); pause(); break;
		}//end switch
	} while (userInput != 0);
}//end displayMenu
/******************************************************************************************************/
int main() {
	clearScreen();
	showMessage("Initializing Program...\n");
	initializeEnvironment();
	initializeArrays();
	displayMenu();

	pause(); // ideally use stop(); but use this for debugging
}//end main
/******************************************************************************************************/