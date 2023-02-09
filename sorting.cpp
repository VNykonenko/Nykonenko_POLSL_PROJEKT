#include "head.h"

//bubble-sorting words from biggest to smallest
void sort_by_len_des(vector<Word>& words ) {

	Word temp{};
	int n = words.size();
	for (int i = 0; i < n; i++) {

		for (int j = 0; j < n - 1; j++) {

			for (int k = 0; k < n - j - 1; k++) {

				if (words[k].size() < words[k + 1].size()) {

					temp = words[k];
					words[k] = words[k + 1];
					words[k + 1] = temp;

				}

			}

		}

	}

}