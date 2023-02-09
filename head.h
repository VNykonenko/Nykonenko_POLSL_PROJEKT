#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int N = 250;//max number of words in dictionary
const int S = 5; //max number of words in puzzle. not recommended higher than 70
const int M = 20;//size of a table


struct Point
{
	int i{};
	int j{};
};


struct Word
{
	string word;

	string definicion;

	int size() {
		return word.length();
	}
};

struct Answer
{
	int number;
	Word correct_word;
	Point start;
	bool direction;//dir - direction. if true - vertical, else - horizontal
};

struct Table
{
	char table[M+1][M+1]{};
	vector<Word>words_hor;//used for creation of crossword
	vector<Word> words_ver;
	char hidden_table[M+1][M+1]{};//is outputted for user

	vector<Answer> answers;//used later in the game

	int number_of_words{};

	vector<Point> starts_hor;//used for creation of crossword
	vector<Point> starts_ver;

	void place_word_hor(Word word, Point start);
	void place_word_ver(Word word, Point start);


	//dir - direction. if true - vertical, else - horizontal
	bool check_fitting(Point p, Word w, bool dir);

	bool try_vert(Word word);
	bool try_hor(Word word);

	bool try_to_fit(Word word, bool dir);

	void print_ful() {

		for (int i = 0; i < M; i++) {

			for (int j = 0; j < M; j++) {
				if (table[i][j] == 0) {
					cout << '#';
				}
				else {
					cout << table[i][j];
				}


			}
			cout << '\n';
		}
		cout << endl;
	}

	void print_hidden() {

		for (int i = 0; i < M; i++) {

			for (int j = 0; j < M; j++) {
				if (hidden_table[i][j] != 0) {					
					cout << hidden_table[i][j];
				}
					else
					{
						cout << "\033[27;30m#\033[0m"; //"invisible" hashes
					}
				}


			
			cout << '\n';
		}
		cout << endl;
	}

};


//origin: file_functions.cpp reads words from txt file
void library_read( vector<Word>& words_out,string path = "Words and defs.txt");

//origin: sorting.cpp sorts words in decreasing order
void sort_by_len_des(vector<Word>& words);

//picks random words from a vector
void random_words(vector<Word>& all_words, vector<Word>& rand_words);

//creates initial puzzle
void create_crossword(vector<Word> word_list, Table* table);

//controlls interaction with user
void fun(Table* table);