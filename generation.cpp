#include "head.h"
#include <ctime>
#include <stdlib.h>


void Table::place_word_ver(Word word, Point start){

	starts_ver.push_back(start);
	int end_row = start.i + word.size();
	for (int i = start.i; i < end_row; i++) {
		table[i][start.j] = word.word[i-start.i];
		hidden_table[i][start.j] = 'o';
	}
	number_of_words++;
	

	words_ver.push_back(word);
	
	answers.push_back({ number_of_words, word,start,true });
	

}

void Table::place_word_hor(Word word, Point start) {

	starts_hor.push_back(start);
	int end_col = start.j + word.size();
	for (int j = start.j; j < end_col; j++) {
		table[start.i][j] = word.word[j - start.j];
		hidden_table[start.i][j] = 'o';
	}
	number_of_words++;
	
	words_hor.push_back(word);
	answers.push_back({ number_of_words, word,start,false });
	

}

//picks random words out of general dictionary
void random_words(vector<Word>& all_words, vector<Word>& rand_words) {

	if (S >= all_words.size()) {
		rand_words = all_words;
		return;
	}
	srand(time(NULL));

	int n = all_words.size();
	if (n > N) {
		n = N;		//preventing overflow
	}
	int q{};
	bool taken[N]{};
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < 5; j++) {

			q = rand() % n;
			
			if (taken[q]) {
				continue;
			}
			else {
				taken[q] = true;
				rand_words.push_back(all_words[q]);
				break;
			}

		}
	}
	int i{};
	while (rand_words.size() < S||i>=all_words.size()) {
		
		if (!taken[i]) {
			taken[i] = true;
			rand_words.push_back(all_words[i]);
		}

		i++;
	}

}

void create_crossword(vector<Word> word_list, Table* table) {
	
	vector<Word> second_order;
	(*table).place_word_hor(word_list[0], {M / 2, (M - word_list[0].size()) / 2 });

	bool dir = true; //dir - direction. if true - vertical, else - horizontal

	for (int i = 1; i < word_list.size(); i++) {
		if (!(*table).try_to_fit(word_list[i], dir)) {
			second_order.push_back(word_list[i]);
		}
		dir = !dir;
	}

	//trying to put those words, that didn't fit at the first time
	for (int i = 1; i < second_order.size(); i++) {
		(*table).try_to_fit(word_list[i], dir);
		dir = !dir;
	}
	
	//making all numeration-markers visible on the hidden table
	for (int i = 0; i < (*table).number_of_words; i++)
	{
		if (i > 8) {
			char a = 'A' + i - 9;
			(*table).hidden_table[(*table).answers[i].start.i][(*table).answers[i].start.j] = a;
		}
		else
		{
			(*table).hidden_table[(*table).answers[i].start.i][(*table).answers[i].start.j] = i + 49;
		}
	}
	

}

//checks if the word will fit at given point and direction
bool Table::check_fitting(Point p, Word w, bool dir) {
	
	//preventing out of bonds
	if (p.i <= 0 || p.j <= 0) {
		return false;
	}
	int s = w.size();//putting size of the word in variable so it won't be calculated anew every iteration of the loop

	//if letter before or after first or last letter of the  word is already taken, then this is not suitable
	//it is so for more clear generation
	if (table[p.i - 1][p.j] != 0 || table[p.i + s][p.j] != 0) {
		return false;
	}
	if (table[p.i][p.j - 1] != 0 || table[p.i][p.j + s] != 0) {
		return false;
	}


	if (dir) {
		//preventing out of bonds
		if (p.i + s >= M) {
			return false;
		}
		
		for (int i = 0; i < s; i++)
		{
			if (!(table[p.i + i][p.j] == 0)) {
				if(!(table[p.i + i][p.j] == w.word[i])){
					return false;
				}
			}
		}

		return true;

	}
	else {
		//preventing out of bonds
		if (p.j + s >= M) {
			return false;
		}
		for (int j = 0; j < s; j++)
		{
			if (!(table[p.i][p.j + j] == 0)) {

				if (!(table[p.i][p.j + j] == w.word[j])) {
					return false;
				}

			}
		}

		return true;

	}

}


//looks for a letter from a word that is already on the board
bool Table::try_vert(Word word) {

	int s = word.size();//putting size of the word in variable so it won't be calculated anew every iteration of the loop

	for (int i = 0; i < s; i++)
	{
		for (int k =0; k<words_hor.size();k++)
		{
			Word word_tab = words_hor[k];
			int s_tab = word_tab.size();
			for (int j = 0; j < s_tab; j++)
			{
				if (word_tab.word[j] == word.word[i]) {
					if (check_fitting({(starts_hor[k].i)-i,(starts_hor[k].j)+j},word,true)) {
						place_word_ver(word, { starts_hor[k].i - i , starts_hor[k].j + j});
						return true;
						
					} 
				}
			}
		}
	}
	return false;
	

}

bool Table::try_hor(Word word) {

	int s = word.size();//putting size of the word in variable so it won't be calculated anew every iteration of the loop

	for (int j = 0; j < s; j++)
	{
		for (int k = 0; k < words_ver.size(); k++)
		{
			Word word_tab = words_ver[k];
			int s_tab = word_tab.size();
			for (int i = 0; i < s_tab; i++)
			{
				if (word_tab.word[i] == word.word[j]) {
					if (check_fitting({ (starts_ver[k].i) + i,(starts_ver[k].j) - j }, word, false)) {
						place_word_hor(word, { starts_ver[k].i + i , starts_ver[k].j - j });
						return true;

					}
				}
			}
		}
	}
	return false;


}

//first tries to fit the word with a preferred orientation, if fails - then with another
bool Table::try_to_fit(Word word, bool dir) {

	if (dir) {
		if (try_vert(word)) {//if true, then it already has been placed on the table
			return true;
		}
		else {
			if (try_hor(word)) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		if (try_hor(word)) {
			return true;
		}
		else {
			if (try_vert(word)) {
				return true;
			}
			else {
				return false;
			}
		}

	}

}
