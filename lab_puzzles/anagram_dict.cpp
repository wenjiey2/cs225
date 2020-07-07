/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream words(filename);
    if(words.is_open()){
      string word;
      while (getline(words, word)){
        string sorted = word;
        sort(sorted.begin(), sorted.end());
        dict[sorted].push_back(word);
      }
    }

}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for(string word : words){
      string sorted = word;
      sort(sorted.begin(), sorted.end());
      dict[sorted].push_back(word);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string sorted = word;
    sort(sorted.begin(), sorted.end());
    std::map<string, std::vector<std::string>>::const_iterator lookup = dict.find(sorted);
    if(lookup != dict.end()){
      return lookup->second;
    }
    return vector<string>();

}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> all;
    for(const std::pair<string, std::vector<std::string>> &d: dict){
      const vector<string>& anagrams = d.second;
        if(anagrams.size() >= 2){
          all.push_back(anagrams);
        }
    }
    return all;
}
