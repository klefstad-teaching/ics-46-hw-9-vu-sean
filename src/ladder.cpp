#include "ladder.h"
#include <algorithm>

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " ('" << word1 << "' to '" << word2 << "')" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (str1 == str2) 
        return true;
    if (d != 1) return false;
    
    int len1 = str1.length();
    int len2 = str2.length();
    
    if (abs(len1 - len2) > 1) 
        return false;
    
    if (len1 == len2) {
        int diff_count = 0;
        for (int i = 0; i < len1; i++) {
            if (str1[i] != str2[i]) {
                diff_count++;
                if (diff_count > 1) 
                    return false;
            }
        }
        return diff_count == 1;
    }
    
    const string& shorter = (len1 < len2) ? str1 : str2;
    const string& longer = (len1 < len2) ? str2 : str1;
    
    int i = 0, j = 0;
    bool found_diff = false;
    
    while (i < shorter.length() && j < longer.length()) {
        if (shorter[i] != longer[j]) {
            if (found_diff) 
                return false;  
            found_diff = true;
            j++; 
        } else {
            i++;
            j++;
        }
    }
    
    return (i == shorter.length() && (j == longer.length() || j == longer.length() - 1));
}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1 == word2) 
        return true;

    int len1 = word1.length();
    int len2 = word2.length();
    
    if (abs(len1 - len2) > 1) 
        return false;
    
    if (len1 == len2) {
        int diff_count = 0;
        for (int i = 0; i < len1; i++) {
            if (word1[i] != word2[i]) {
                diff_count++;
                if (diff_count > 1) return false;
            }
        }
        return diff_count <= 1;
    }
    
    const string& shorter = (len1 < len2) ? word1 : word2;
    const string& longer = (len1 < len2) ? word2 : word1;
    
    int i = 0, j = 0;
    bool found_diff = false;
    
    while (i < shorter.length() && j < longer.length()) {
        if (shorter[i] != longer[j]) {
            if (found_diff) return false; 
            found_diff = true;
            j++; 
        } else {
            i++;
            j++;
        }
    }
    
    return (i == shorter.length() && (j == longer.length() || j == longer.length() - 1));
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    
    if (begin_word == end_word) {
        return {};
    }
    
    queue<vector<string>> ladder_queue;

    vector<string> initial_ladder = {begin_word};
    ladder_queue.push(initial_ladder);

    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) { //bfs
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        
        string last_word = current_ladder.back();
        
        if (last_word == end_word) {
            return current_ladder;
        }
        
        for (const string& word : word_list) {
            int len1 = last_word.length();
            int len2 = word.length();
            
            bool is_adj = false;
            
            if (abs(len1 - len2) <= 1) {
                if (len1 == len2) {
                    int diff_count = 0;
                    for (int i = 0; i < len1; i++) {
                        if (last_word[i] != word[i]) {
                            diff_count++;
                            if (diff_count > 1) break;
                        }
                    }
                    is_adj = (diff_count == 1);
                } else {
                    const string& shorter = (len1 < len2) ? last_word : word;
                    const string& longer = (len1 < len2) ? word : last_word;
                    
                    int i = 0, j = 0;
                    bool found_diff = false;
                    
                    while (i < shorter.length() && j < longer.length()) {
                        if (shorter[i] != longer[j]) {
                            if (found_diff) {
                                is_adj = false;
                                break;
                            }
                            found_diff = true;
                            j++;  
                        } else {
                            i++;
                            j++;
                        }
                    }

                    is_adj = (i == shorter.length() && (j == longer.length() || j == longer.length() - 1));
                }
            }
            
            if (is_adj && visited.find(word) == visited.end()) {
                visited.insert(word);

                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);
                
                if (word == end_word) {
                    return new_ladder;
                }

                ladder_queue.push(new_ladder);
            }
        }
    }
    
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in) {
        throw runtime_error("Cannot open dictionary file: " + file_name);
    }
    
    string word;
    while (in >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
    
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "Empty ladder" << endl;
        return;
    }
    
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " → ";
        }
    }
    cout << endl;
    cout << "Ladder length: " << ladder.size() << endl;
}

void verify_word_ladder() { //given
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    auto my_assert = [](bool e, const string& expr) {
        cout << expr << (e ? " passed" : " failed") << endl;
    };
    
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4, 
              "generate_word_ladder(\"cat\", \"dog\", word_list).size() == 4");
    
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6, 
              "generate_word_ladder(\"marty\", \"curls\", word_list).size() == 6");
    
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6, 
              "generate_word_ladder(\"code\", \"data\", word_list).size() == 6");
    
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6, 
              "generate_word_ladder(\"work\", \"play\", word_list).size() == 6");
    
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8, 
              "generate_word_ladder(\"sleep\", \"awake\", word_list).size() == 8");
    
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4, 
              "generate_word_ladder(\"car\", \"cheat\", word_list).size() == 4");
}