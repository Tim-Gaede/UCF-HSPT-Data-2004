#include <iostream>
#include <cctype>
#include <fstream>

using namespace std;

//Determine whether a character is a vowel.
bool isVowel( char ch ) {
	ch = (char)toupper( ch );

	return ( 'A' == ch ) || ( 'E' == ch ) || ( 'I' == ch ) 
		|| ( 'O' == ch ) || ( 'U' == ch );
}

//Determine whether a character is a consonant.
bool isConsonant( char ch ) {
	ch = (char)toupper( ch );

	//A letter is a consonant if it is not a vowel nor is a 'y'.

	return isalpha( ch ) && ( ! ( ( 'A' == ch ) || ( 'E' == ch ) || ( 'I' == ch ) 
			|| ( 'O' == ch ) || ( 'U' == ch ) 
			|| ( 'Y' == ch ) ) );
}

//Determine the base value of a character based on the character and the
//character before that and the character after that).
int baseValue( char character, char prevCharacter, char nextCharacter ) {
	if( isdigit( character ) ) {
		return character - '0';
	} else if( isConsonant( character ) ) {
		return 10;
	} else if( isVowel( character ) ) {
		return 15;
	} else if( 'Y' == toupper( character ) ) {
		if( isConsonant( nextCharacter ) || isConsonant( prevCharacter ) ) {
			return 15;
		} else {
			return 10;
		}
	}
}
//Determine the value of a character based on the character and the character
//before that, and the character two characters before the character
//and the character after the character. 
//(Use a blank if the value of the first or last character is desired.)
int valueOfCharacter( char character, char prevCharacter, char prev2Character, char nextCharacter ) {
	//The base value of the character
	
	if( ( isalpha( character ) && isalpha( prevCharacter ) )
			|| ( isdigit( character ) && isdigit( prevCharacter ) ) ) {
		return baseValue( character, prevCharacter, nextCharacter ) + baseValue( prevCharacter, prev2Character, character );
	} else {
		return baseValue( character, prevCharacter, nextCharacter );
	}
}

#define MAX_STRING_LEN 40000

//Get the hashcode for a license plate.
char hashcodeString[MAX_STRING_LEN];

int getHashcode( char * licensePlate ) {
	//Current value of the hashcode.
	int hashcodeValue = 0;
	//The previous character -- the one before the character the algorithm 
	//is analyzing.
	char prevCharacter = ' ';
	//The character two characters before the character the algorithm is 
	//analyzing
	char prev2Character = ' ';
	//The character the algorith is analyzing.
	char character = ' ';
	//The next character -- the one after the character the algorithm is 
	//analyzing
	char nextCharacter = ' ';

	//Create a string that is a space followed by the licensePlate.
	hashcodeString[0] = ' ';
	strcpy( hashcodeString + 1, licensePlate );

	//Scan through the string BACKWARDS.
	for( int characterI = strlen( hashcodeString ) - 1;
			characterI >= 1;
			characterI-- ) {
		//Set the characters in the "window" the algorithm is 
		//analyzing.
		prev2Character = prevCharacter;
		prevCharacter = character;

		
		character = hashcodeString[characterI];
		nextCharacter = hashcodeString[characterI-1];
		
		hashcodeValue += valueOfCharacter( character, prevCharacter, prev2Character, nextCharacter );

	}
	return hashcodeValue;
}
//List of hashcodes found so far.
#define MAX_NUM_HASHCODES 40000
int numHashcodes;
int hashcodesList[MAX_NUM_HASHCODES];

//Add a hashcode to the list -- if it is not already there.
void addHashcode( int hashcode ) {
	//Index for the proper place in the list for the new hashcode.
	int hashcodeI = 0;
	//cout << hashcode << endl;
	while( hashcodeI < numHashcodes ) {
		if( hashcodesList[hashcodeI] == hashcode ) {
			//The hashcode has been found.
			return;
		}
		hashcodeI++;
	}
	//If the function gets here, the hashcode should be added.
	hashcodesList[numHashcodes] = hashcode;
	numHashcodes++;
}

//Initialize the program for a dataset.
void init() {
	numHashcodes = 0;
}


//String for the lisence plate read in.
char licensePlate[MAX_STRING_LEN];
int main() {
	//Input stream
	ifstream input( "lice.in" );

	//index of the current run;
	int curRunI = 1;

	//number of plates for the current run.
	int numPlates;

	input >> numPlates;
	while( 0 != numPlates ) {
		init();

		for( int plateI = 0; plateI < numPlates; plateI++ ) {
			input >> licensePlate;
//			cout << licensePlate << " = " << getHashcode( licensePlate ) << endl;
			addHashcode( getHashcode( licensePlate ) );
		}

		cout << "The lice in data set #" << curRunI << 
			" came from " << numHashcodes 
			<<" different head(s)." << endl;

		curRunI++;
		input >> numPlates;
	}
}
