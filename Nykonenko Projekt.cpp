#include "head.h"

int main()
{
    char q;
    vector<Word>words;
    library_read(words);
    int n = words.size();

 


    vector<Word> for_puzzle;
    //creates a puzzle for the first time, and repeats it untill user demands it
    do {
      //  system("cls");

        random_words(words, for_puzzle);

        sort_by_len_des(for_puzzle);

        
        Table table;
        create_crossword(for_puzzle, &table);

        fun(&table);
        //this messendge shows after the "game" (function "fun") is exited. completed or interrupted
        cout << "Thank's for playing!\nWould you like to play another crossword? (y/n)";

        cin >> q;
    } while (q == 'y' || q == 'Y');
    cout << "Guess, that is a \"No\"." << endl;

    system("pause");
   
}
