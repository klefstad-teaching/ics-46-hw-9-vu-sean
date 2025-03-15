#include "ladder.h"
#include <iostream>
#include <string>
#include <set>

int main() {
    set<string> word_list;
    string dictionary_file = "words.txt";
    
    try {
        load_words(word_list, dictionary_file);
    }
    catch (const exception& e) {
        cerr << "error: " << e.what() << endl;
        return 1;
    }
    
    string begin_word, end_word;
    
    cout << "Enter start word: ";
    cin >> begin_word;
    
    cout << "Enter end word: ";
    cin >> end_word;
    
    for (char& c : begin_word) c = tolower(c);
    for (char& c : end_word) c = tolower(c);
    
    if (begin_word == end_word) {
        error(begin_word, end_word, "Start and end words are same");
        return 1;
    }
    
    if (word_list.find(end_word) == word_list.end()) {
        error(begin_word, end_word, "End word is not in the dictionary");
        return 1;
    }

    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    
    if (ladder.empty()) {
        cout << "No ladder found from '" << begin_word << "' to '" << end_word << "'." << endl;
    } else {
        cout << "Found from '" << begin_word << "' to '" << end_word << "':" << endl;
        print_word_ladder(ladder);
    }
    
    return 0;
}