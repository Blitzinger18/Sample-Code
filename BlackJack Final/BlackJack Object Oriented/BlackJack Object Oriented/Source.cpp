#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <limits>
#include <fstream>

using namespace std;

class game {
private:
	int value;
	string suit;
	bool isAce;
	bool isFace;

public:
	game();
	game(int, string, bool, bool);
	void displaycard();
	void displayPlayer();
	void displayDealer();
	int getValue();
	string getSuit();
	bool getisAce();
	bool getisFace();
	int getcardValue(int total);
};

int game::getValue() {
	return value;
}
string game::getSuit() {
	return suit;
}
bool game::getisAce() {
	return isAce;
}
bool game::getisFace() {
	return isFace;
}

game::game() {
	value = 0;
	suit = "Empty";
	isAce = false;
	isFace = false;
}

game::game(int v, string s, bool a, bool f) {
	this->value = v;
	this->suit = s;
	this->isAce = a;
	this->isFace = f;
}

void game::displayPlayer() {
	string cardTemp = std::to_string(value);
	if (value == 1) {
		cardTemp = "Ace";
	}
	else if (value == 11) {
		cardTemp = "Jack";
	}
	else if (value == 12) {
		cardTemp = "Queen";
	}
	else if (value == 13) {
		cardTemp = "King";
	}

	cout << "Player was dealt " << cardTemp << " of " << suit << endl;
}

void game::displayDealer() {
	string cardTemp = std::to_string(value);
	if (value == 1) {
		cardTemp = "Ace";
	}
	else if (value == 11) {
		cardTemp = "Jack";
	}
	else if (value == 12) {
		cardTemp = "Queen";
	}
	else if (value == 13) {
		cardTemp = "King";
	}

	cout << "Dealer was dealt " << cardTemp << " of " << suit << endl;
}

void game::displaycard() {
	string cardTemp = std::to_string(value);
	if (value == 1) {
		cardTemp = "Ace";
	}
	else if (value == 11) {
		cardTemp = "Jack";
	}
	else if (value == 12) {
		cardTemp = "Queen";
	}
	else if (value == 13) {
		cardTemp = "King";
	}

	cout << cardTemp << " of " << suit << endl;
}

int game::getcardValue(int total) {
	if (isAce) {
		if (total >= 11) {
			return 1;
		}
		return 11;
	}
	else if (isFace) {
		return 10;
	}
	return value;
}

void balance();
//void goto menu;


int main() {

	//system("CLS");

menu:
	system("CLS");

	cout << "xXx----BLACKJACK----xXx" << endl << endl;
	cout << "Enter 1 to Play." << endl;
	cout << "Enter 2 to see Current Balance." << endl;
	cout << "Enter 3 to see the rules." << endl;
	cout << "Enter 4 to Exit the game." << endl;
	cout << "Select an option: ";
	int entry;
	cin >> entry;

	//menu options by case
	switch (entry) {
	case 1:
		system("CLS");
		cout << "You have selected Play game." << endl << endl;
		cout << "Press ENTER to play." << endl;
		cin.get();
		cin.ignore();
		goto play;
		break;
	case 2:
		system("CLS");
		cout << "You have selected Current Balance." << endl << endl;
		balance();
		cout << "Press ENTER to go to menu." << endl;
		cin.get();
		cin.ignore();
		goto menu;
		break;
	case 3:
		system("CLS");
		cout << "The rules of BlackJack are as follows:" << endl;
		cout << "You are delt 2 cards and you have to choose hit or miss to try an beat the dealer's hand or make 21." << endl;
		cout << "If you choose to play double down, u get one additonal card and ur winnings are doubled." << endl;
		//cout << "If you choose to play split hand, your initial hand is split and two games are played with the same bet." << endl;
		cout << "The payout rate is 3:2 for a BlackJack, which is starting with a 21 hand." << endl;
		cout << "The payout rate is 2:1 for beating the delears hand." << endl << endl;
		cout << "Press ENTER to go to menu." << endl;
		cin.get();
		cin.ignore();
		goto menu;
		break;
	case 4:
		system("CLS");
		cout << "Thank you for playing BLACKJACK!" << endl << endl;
		cout << "Press ENTER to quit." << endl;
		cin.get();
		cin.ignore();
		exit(1);
		break;
	default:
		system("CLS");
		cout << "Invaild Input! Please select an Option." << endl << endl;
		goto menu;
		break;

	}


play:
	//load player balance
	float balance;
	ifstream myfile;
	myfile.open("money.txt");
	myfile >> balance;
	cout << "Current balance is: $" << balance << endl << endl;
	myfile.close();

	if (balance < 0) {
		cout << "No chips were found!" << endl << endl;
		goto chips;
	}

chips:
	ofstream outfile("money.txt");
	//checks current balance
	string choice;
	if (balance <= 0) {
		cout << "Would you like to add chips? Y/N: ";
		cin >> choice;
		while (choice != "y" && choice != "n" && choice != "N" && choice != "Y") {
			cout << "Wrong Input!: ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> choice;
		}
		if (choice == "Y" || choice == "y") {
			balance = 10;
			outfile << 10;
			outfile.close();
			cout << "10 chips were added to you account." << endl << endl;
			goto menu;
		}
		if (choice == "N" || choice == "n") {
			cout << "You need chips to play the game!" << endl << endl;
			goto menu;
		}
	}
	//users bet a certain amount of chips
	system("CLS");
	int bet = 0;
	do {

		cout << "How many chips would you like to bet? (min of 5): ";
		cin >> bet;
		cout << endl;

		if (bet < 5) {
			system("CLS");
			cout << "You need a min of 5 chips to play!" << endl;
			continue;
		}
		if (bet > balance) {
			system("CLS");
			cout << "Insufficient number if chips!" << endl;
			continue;
		}
		else {
			balance = balance - bet;
			cout << "Your new balance is: $" << balance << endl << endl;
			outfile << balance;
			outfile.close();
			break;
		}
	} while (true);

	vector<game *> playerHand;
	vector<game *> dealerHand;
	vector<game *> Deck;
	//vector<game *>::iterator y;

	//asign suits to the cards
	for (int suitnumber = 0; suitnumber <= 3; suitnumber++) {
		for (int cardnumber = 1; cardnumber <= 13; cardnumber++) {
			string suitTemp;
			bool isFacecardTemp = false;
			bool isAceTemp = false;
			if (suitnumber == 0) {
				suitTemp = "Clubs";
			}
			if (suitnumber == 1) {
				suitTemp = "Hearts";
			}
			if (suitnumber == 2) {
				suitTemp = "Spades";
			}
			if (suitnumber == 3) {
				suitTemp = "Diamonds";
			}

			if (cardnumber == 1) {
				isAceTemp = true;
			}
			if (cardnumber >= 11 && cardnumber <= 13) {
				isFacecardTemp = true;
			}
			Deck.push_back(
				new game(cardnumber, suitTemp, isAceTemp, isFacecardTemp));
		}
	}
	//randomize cards
	srand(unsigned(time(0)));
	random_shuffle(Deck.begin(), Deck.end());

	int playerTotal1 = 0;
	int playerTotal2 = 0;
	int playerTotal3 = 0;
	int dealerTotal = 0;
	int dealtcardIndex = 0;
	bool splitHand;
	string hit;
	string option;
	string option2;

	//players first hand
	playerTotal1 = playerTotal1 + Deck[dealtcardIndex]->getcardValue(playerTotal1);
	Deck[dealtcardIndex]->displayPlayer();
	dealtcardIndex++;

	playerTotal2 = playerTotal2 + Deck[dealtcardIndex]->getcardValue(playerTotal2);
	Deck[dealtcardIndex]->displayPlayer();
	playerTotal3 = playerTotal1 + playerTotal2;
	cout << "Player total: " << playerTotal3 << endl;
	dealtcardIndex++;

	//split game
	/*if (playerTotal3 < 22) {
		cout << "Would you like to play split hand? (Y/N)" << endl;
		cin >> option2;

		if (option2 == "Y" || option2 == "y") {
			bet = bet * 2;
			goto split1;
		}
		else {
			goto down;
		}
	}*/

	//BlackJack Auto Win
	if (playerTotal1 == 21 || playerTotal2 == 21 || playerTotal3 == 21) {
		cout << "You got a BlackJack! You win!" << endl;
		cout << "Your new balance is $" << bet * 2.5 << endl;
		balance = balance + bet * 2.5;
		outfile.open("Money.txt");
		outfile << balance;
		outfile.close();
		cout << "Press ENTER to go to menu." << endl;
		cin.get();
		cin.ignore();
		goto menu;
	}


	//double down
	cout << "Would you like to play double down? (Y/N)" << endl;
	cin >> option;

	if (option == "Y" || option == "y") {
		bet = bet * 2;
		goto down;
	}
	else {
		goto game;
	}

down:

	//choose whether or not to take another card

	while (playerTotal3 < 22 && (option == "Y" || option == "y")) {
		playerTotal3 =
			playerTotal3 + Deck[dealtcardIndex]->getcardValue(playerTotal3);
		Deck[dealtcardIndex]->displayPlayer();
		cout << "New Player total is: " << playerTotal3 << endl;
		dealtcardIndex++;
		goto win;
	}

	/*split1:
		//splits hands into seperate hands

		splitHand = true;

		//cout <<  << endl;

		playerTotal1 = playerTotal1 + Deck[dealtcardIndex]->getcardValue(playerTotal1);
		Deck[dealtcardIndex]->displayPlayer();
		cout << "New Player total: " << playerTotal1 << endl;
		dealtcardIndex++;

		cout << "Hit or stand (H/S): " << endl;
		cin >> hit;

		while (playerTotal1 < 22 && (hit == "h" || hit == "H")) {
			playerTotal1 =
				playerTotal1+ Deck[dealtcardIndex]->getcardValue(playerTotal1);
			Deck[dealtcardIndex]->displayPlayer();
			cout << "New Player total is: " << playerTotal1 << endl;
			if (playerTotal1 < 22) {
				cout << "Hit or stand (H/S): " << endl;
				cin >> hit;
			}
			dealtcardIndex++;
		}
		goto win;


	split2:

		splitHand = false;

		//cout << Deck[dealtcardIndex - 2] << endl;

		playerTotal2 = playerTotal2 + Deck[dealtcardIndex]->getcardValue(playerTotal2);
		Deck[dealtcardIndex]->displayPlayer();
		cout << "New Player total: " << playerTotal2 << endl << endl;
		dealtcardIndex++;

		cout << "Hit or stand (H/S): " << endl;
		cin >> hit;

		while (playerTotal2 < 22 && (hit == "h" || hit == "H")) {
			playerTotal2 =
				playerTotal2 + Deck[dealtcardIndex]->getcardValue(playerTotal2);
			Deck[dealtcardIndex]->displayPlayer();
			cout << "New Player total is: " << playerTotal2 << endl;
			if (playerTotal2 < 22) {
				cout << "Hit or stand (H/S): " << endl;
				cin >> hit;
			}
			dealtcardIndex++;
		}
		goto win;*/

game:
	cout << "Hit or stand (H/S): " << endl;
	cin >> hit;

	while (playerTotal3 < 22 && (hit == "h" || hit == "H")) {
		playerTotal3 =
			playerTotal3 + Deck[dealtcardIndex]->getcardValue(playerTotal3);
		Deck[dealtcardIndex]->displayPlayer();
		cout << "New Player total is: " << playerTotal3 << endl;
		if (playerTotal3 < 22) {
			cout << "Hit or stand (H/S): " << endl;
			cin >> hit;
		}
		dealtcardIndex++;
	}

win:
	//player lose condition
	//cout << "New Player score: " << playerTotal << endl;
	if (playerTotal1 > 21 || playerTotal2 > 21 || playerTotal3 > 21) {
		cout << "You busted! Dealer Wins!" << endl;

		/*if (splitHand) {
			goto split2;
		}*/

		cout << "Press ENTER to quit." << endl;
		cin.get();
		cin.ignore();
		goto menu;
		return 0;
	}

	//dealer's hand
	dealerTotal = dealerTotal + Deck[dealtcardIndex]->getcardValue(dealerTotal);
	Deck[dealtcardIndex]->displayDealer();
	dealtcardIndex++;
	dealerTotal = dealerTotal + Deck[dealtcardIndex]->getcardValue(dealerTotal);
	Deck[dealtcardIndex]->displayDealer();
	dealtcardIndex++;

	//dealer decides whether to take another card
	while (dealerTotal < 17 && dealerTotal < 21) {
		dealerTotal =
			dealerTotal + Deck[dealtcardIndex]->getcardValue(dealerTotal);
		Deck[dealtcardIndex]->displayDealer();
		dealtcardIndex++;
	}
	//player win condition
	cout << "Dealer total: " << dealerTotal << endl;
	if (dealerTotal > 21) {
		cout << "Dealer busted! You win!" << endl;
		cout << "Your new balance is $" << bet * 2 << endl;
		balance = balance + bet * 2;
		outfile.open("Money.txt");
		outfile << balance;
		outfile.close();

		/*if (splitHand) {
			goto split2;
		}*/

		cout << "Press ENTER to go to menu." << endl;
		cin.get();
		cin.ignore();
		goto menu;
	}
	//player win condition
	if (playerTotal1 >= dealerTotal || playerTotal2 >= dealerTotal || playerTotal3 >= dealerTotal) {
		cout << "Dealer chose to stand." << endl;
		cout << "You win!" << endl;
		cout << "Your new balance is $" << bet * 2 << endl;
		balance = balance + bet * 2.5;
		outfile.open("Money.txt");
		outfile << balance;
		outfile.close();

		/*if (splitHand) {
			goto split2;
		}*/

		cout << "Press ENTER to go to menu." << endl;
		cin.get();
		cin.ignore();
		goto menu;
	}
	//dealer win condition
	else {
		cout << "Dealer wins! You lose!" << endl;

		/*if (splitHand) {
			goto split2;
		}*/

		cout << "Press ENTER to go to menu." << endl;
		cin.get();
		cin.ignore();
		goto menu;
	}


	return 0;
}

void balance() {
	ifstream inFile;
	inFile.open("Money.txt");

	if (!inFile) {
		cout << "Unable to open file Money.txt";
		exit(1);   // call system to stop
	}

	string balance;
	while (inFile.good()) {
		getline(inFile, balance);
		if (balance[0] == '/')
			continue;
	}

	cout << "Your current balance is: $" << balance << endl << endl;

	inFile.close();
}