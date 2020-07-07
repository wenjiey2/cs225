/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream words(word_list_fname);
    if(words.is_open()){
      string word;
      while(getline(words, word)){
        if(word.length() == 5){
          const string& homophone1 = word.substr(1);
          const string& homophone2 = word.substr(0, 1) + word.substr(2);
          if(d.homophones(word, homophone1) && d.homophones(word, homophone2)){
            ret.push_back({ word, homophone1, homophone2 });
          }
        }
      }
    }
    return ret;
}
