/*******************************
 * Lab 3: exercise 1            *
 * Frequency table of words     *
 *******************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>   //std::pair
#include <fstream>
#include <cassert>
#include <algorithm>
#include <cctype> // tolower


// A function to test the output of the program
void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
          const std::string& file_name, int n);

bool compare(const std::pair<std::string, int>& x, std::pair<std::string, int>& y) {
    if (x.second != y.second) {
        //sort numerically
        return x.second < y.second;
    }
    else {
        //sort alphabetically
        return x.first > y.first;
    }
}
/***************************
 * Main function           *
 **************************/

int main() {  
    std::cout << "Text file: ";
	std::string file_name;
	std::cin >> file_name;
	std::ifstream in_File{"../code/" + file_name};  // modify path, if needed

	if (!in_File) {
		std::cout << "Could not open input file!!\n";
		return 0;
	}

    std::map<std::string, int> table;
    int counter{0};  // to count total number of words read from the input file

    //ADD CODE to build table
    std::string word;
    while (in_File >> word) { //reading word by word from the file and store it in word
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        //move all special carachters to the back of the string
        auto it = std::remove_if(std::begin(word), std::end(word), [](char c)
            {return c == '.' || c == ',' || c == '!' || c == '?' || c == ':' ||
            c == '/' || c == '"' || c == '(' || c == ')' || c == ';'; });
        //erase them
        word.erase(it, word.end());

        counter++;
        table[word]++;
        
        //table.emplace(word, 0); //adds the word to table if it does not already exist

        //if (table.contains(word)) { //checking if the word already exists
        //    table[word]++;          //if so, the wordcounter increases
        //}
        //counter++;
    }

    std::vector<std::pair<std::string, int>> freq;

    //ADD CODE to build vector freq
    std::copy(table.begin(), table.end(), std::back_inserter(freq));
    std::sort(freq.rbegin(), freq.rend(), compare);

    //print
   /* for (std::pair pair : table) {
        std::cout << pair.first << " " << pair.second << "\n";
    }
    for (auto it = table.begin(); it != table.end(); it++) {
        std::cout << it->first << " " << it->second << "\n";
    }*/
    /* ************** Testing **************** */

    test(table, freq, file_name, counter);
}


/*******************************
 * Test implementation         *
 * Do not modify               *
 *******************************/

void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
          const std::string& file_name, int n) {

    std::ifstream file{"../code/out_" + file_name}; //modify path, if needed

    // Test if stream is in good state
    assert(bool(file) == true);

    std::map<std::string, int> result1;
    std::string word;
    int counter{0};
    int total{0};

    // load expected frequency table sorted alphabetically
    while (file >> word >> counter && counter > 0) {
        result1[word] = counter;
        total += counter;
    }

    /*
     * uppgift1_kort: 69 words
     * uppgift1.txt: 1063 words
     */

    assert(total == n);    // test if total number of words is correct
    assert(t == result1);  // test if map/table contents are correct

    std::vector<std::pair<std::string, int>> result2;

    // load expected frequency table sorted by frequence
    while (file >> word >> counter) {
        result2.push_back(std::pair{word, counter});
    }
    assert(v == result2);  // test if vector contents are correct

    std::cout << "\nPassed all tests successfully!!\n";
}
