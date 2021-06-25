#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;


int playgame(string phrase) {
	int misses = 0;
	int exposed = 0;

	string display = phrase;
	for (int i = 0; i < display.length(); i++) {
		display[i] = '*';
	}

	while (exposed < phrase.length() && misses < 10) {
		cout << "Miss: " << misses << ": ";
		cout << "Enter a letter in phrase ";
		cout << display << ":";
		char response;
		cin >> response;

		bool goodGuess = false;
		bool duplicate = false;
		for (int i = 0; i < phrase.length(); i++) {
			if (response == phrase[i]) {
				if (display[i] == phrase[i]) {
					cout << response << " is already in the phrase.\n";
					duplicate = true;
					break;
				}
				else {
					/* if(response == phrase[i]){
						 display[i] = toupper(phrase[i]);
						 exposed++;
						 goodGuess = true;}
					 else{
						 display[i] = phrase[i];
						 exposed++;
						 goodGuess = true;}*/
				}
			}
		}
		if (duplicate)
			continue;
		if (!goodGuess) {
			misses++;
			cout << response << " is not in the phrase.\n";
		}
	}
	if (exposed == phrase.length())
		cout << "Yes, the phrase was " << phrase << "." << endl;

	return misses;
}

int main() {
	srand(time(0));//seed for random generator
	int num = rand() % 4;

	if (num == 0) {
		cout << "You missed " << playgame("Back to Square One");
		cout << " times to guess the phrase Back to Square One." << endl;
	}
	if (num == 1) {
		cout << "You missed " << playgame("Easy As Pie");
		cout << " times to guess the phrase Easy As Pie." << endl;
	}
	if (num == 2) {
		cout << "You missed " << playgame("Elephant in the Room");
		cout << " times to guess the phrase Elephant in the Room." << endl;
	}
	if (num == 3) {
		cout << "You missed " << playgame("Fish Out Of Water");
		cout << " times to guess the phrase Fish Out Of Water." << endl;
	}
	if (num == 4) {
		cout << "You missed " << playgame("Needle In a Haystack");
		cout << " times to guess the phrase Needle In a Haystack." << endl;
	}

	return 0;
}
