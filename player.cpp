#include "head.h"

void fun(Table* table) {

	int guessed{};
	int n{};
	string inp{};
	bool solved[S]{};
	(*table).print_hidden();
	cout << "Definitions: \n";
	for (int i = 0; i < (*table).number_of_words; i++)
	{
		cout << (*table).answers[i].number <<": " << (*table).answers[i].correct_word.definicion << '\n';
	}

	cout << "Enter a number of a word you want to guess. Then, enter the word itself. Enter \"end\" if you want to exit" << endl;
	
	//until all words are guessed
	while (guessed<S)
	{
		
		do
		{	
			cout << "Enter a number: ";
			cin >> inp;
			//checking if number is inputed
			while ((inp.find_first_not_of("1234567890") != -1) || (stoi(inp) > (*table).number_of_words))
			{
				if (inp == "end") {
					
					return;
				}
				cout << "Sorry, that is incorrect! Please, write a Natural number, lesser than " << (*table).number_of_words + 1 << ": ";
				cin >> inp;
			}
			n = stoi(inp);
			n--;
			//checking if the chosen number has already been completed
			if (solved[n]) {
				cout << "You've already answered that one!\n";
			}
		} while (solved[n]);
		cout << "Enter a word:\n";
		cin >> inp;
		if (inp == "end") {
			return;
		}

		for (int i = 0; i < inp.size(); i++) {
			inp[i] = toupper(inp[i]);
		}
		
		//if correct - copies letters from full table to the hidden, thus "revealing them"
		if (inp == (*table).answers[n].correct_word.word) {
			if ((*table).answers[n].direction) {
				for (int i = 0; i < (*table).answers[n].correct_word.size(); i++)
				{
					(*table).hidden_table[(*table).answers[n].start.i + i][(*table).answers[n].start.j] = (*table).table[(*table).answers[n].start.i + i][(*table).answers[n].start.j];
				}
			}
			else {
				for (int j = 0; j < (*table).answers[n].correct_word.size(); j++)
				{
					(*table).hidden_table[(*table).answers[n].start.i][(*table).answers[n].start.j+j] = (*table).table[(*table).answers[n].start.i][(*table).answers[n].start.j+j];
				}
			}
			solved[n] = true;
			//clears and reoutputs the table with the word revealed
			system("cls");
			(*table).print_hidden();
			cout << "Definitions: \n";
			for (int i = 0; i < (*table).number_of_words; i++)
			{
				cout << (*table).answers[i].number << ": " << (*table).answers[i].correct_word.definicion << '\n';
			}

			cout << "Enter a number of a word you want to guess. Then, enter the word itself. Enter \"end\" if you want to exit" << endl;
			cout << "Correct! ";
			guessed++;

		}
		else
		{
			cout << "That's wrong! Try again!" << endl;
		}
	}
	cout << "Congratulations! You've solwed this puzzle!" << endl;

	return;

}