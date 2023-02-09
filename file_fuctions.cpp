#include "head.h"
#include <fstream>

void library_read(vector<Word>& words_out,string path) {

	ifstream in_file(path);	
	

	if (in_file.good()) {

		Word temp;
		int i{};//counts words
		bool flag = false;//defines what line is this. true - definition; false - word
		bool failed_word = false;
		int delta = 'a' - 'A';//difference between codes of upper- and lowercase letters

		for (string line; getline(in_file, line);)//for each line of the file:
		{
			

			if (flag) {

				flag = !flag;//signalizes, that the next line will be with word

				if (failed_word) {//if the previous line was unexistant word, it's definition is ignored
					failed_word = false;
					continue;
				}
				
				temp.definicion = line;
				words_out.push_back(temp);
				i++;
				//prevention of overflow
				if (i > N-1) {
					cout << "Maximum amount of Words has been reached!" << endl;
					return;
				}
				
			}
			else
			{
				flag = !flag;//signalize, that the next line will be with definicion

				if (line.length() > M) {
					cout << "Invalid word: " << line << '\n';
					cout << "The word is too long. It must be shorter than "<<M+1 << endl;
					failed_word = true;
					continue;
				}

				for (int i = 0; i < line.length(); i++) {

					//checking if the word is acceptable
					if (line[i] < 'A' || line[i]>'z' || (line[i] > 'Z' && line[i] < 'a')) {

						cout << "Invalid word: " << line << '\n';
						cout << "Words must be written only with english letters, with no spaces and special characters." << endl;
						failed_word = true;
						continue;

					}
					//making all letters capital, so it would be easier to compare them
					if (line[i] > 'Z') {
						line[i] -= delta;
					}
				}

				temp.word = line;				
			}
			
		}
	}
	else {
		//if file cannot be opened or othervise unavailable:
		cout << "Sorry! There seem to be problem with our dictionary-file!" << endl;
		return;
	}

}