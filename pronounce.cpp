#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <string>
#include <ctype.h>
using namespace std;

/*
Author: Chi Shing Lee
Course: CSCI-135
Instructor: 	Genady Maryash
Assignment:  Project 2, Phase V

The program reports pronunciation as a list of phonemes AND a list of words
that sound the same (is made up of exactly the same sequence of phonemes).
*/

void splitOnSpace(string s, string & before, string & after) {
	// reset strings
	before = "";
	after = "";
	// accumulate before space
	int i = 0;
	while (i < s.size() && !(isspace(s[i]))) {
		before += s[i]; i++;
	}
	// skip the space
	i++;
	// accumulate after space
	while (i < s.size()) {
		after += s[i]; i++;
	}
}

void upperCase(string & w) {
	// Change User's input into Uppercase
	for (int i = 0; i < w.length(); i++) {
		w[i] = toupper(w[i]);
	}
}

void splitPro(string & s, string arr[], int & k) {
	k = 0;
	string empty = " ";
	size_t last = 0;
	size_t next = 0;
	while ((next = s.find(empty, last)) != string::npos) {
		// Find space, and store in to array;
		arr[k] = s.substr(last, next - last);
		last = next + 1;
		k++;
	}
	// The last character in a string store it as the last item in the array;
	arr[k] = s.substr(last);
	k++;
}

void pronunciation(string & w, string & before, string & after, string & junk, string & k, bool & f) {
	//If input is the same as word in dictonary, and it is different from junk
	if (w.compare(before) == 0 && before.compare(junk) != 0) {
		// Prints pronunciation
		cout << "Pronunciation    :" << after << endl << endl;
		cout << "Identical        : ";
		// Store pronunciation into k
		k = after;
		// Set found to true
		f = true;
	}
}

void indentical(string & k, string & w, string & before, string & after, string & j, bool & f) {
	// If the pronunciation of the word is the same as the pronunciation of the word in the dictonary and it is 
	// different from junk
	if (w.compare(after) == 0 && before.compare(j) != 0) {
		// If the word is different from User's input
		if (k.compare(before) != 0 && before.compare(j) != 0) {
			// Prints Identical
			cout << before << " ";
			f = true;
		}
	}
	else {
		f = false;
	}

}

void proArrCompare(string arr[], string arr2[], int & x, int & s, string & before, bool & f) {
	int counter = 0;
	// Compare both pronunciation of user input and file.
	if (s == x) {
		for (int i = 0; i < x; i++) {
			if (arr[i].compare(arr2[i]) == 0) {
				counter++;
			}
		}
	}
	// If the counter length is one less than the pronunciaiton of user input
	if (counter + 1 == s) {
		cout << before << " ";
		f = true;
	}
}

void proAdd(string arr[], string arr2[], int & x, int & s, string & before, bool & f) {
	int counter = 0;
	// Compare both pronunciation
	for (int i = 0; i < s+1; i++) {
		if (arr[i].compare(arr2[i]) == 0) {
			counter++;
		}
		else if (arr[i].compare(arr2[i - 1]) == 0) {
			counter++;
		}
	}
	
	// If counter length is the same as the array length of the pronunciation 
	if (counter  == s) {
		cout << before << " ";
		f = true;
	}
}

void proRemove(string arr[], string arr2[], int & x, int & s, string & before, bool & f) {
	int counter = 0;
	// compare both pronunciation
	for (int i = 0; i < s-1; i++) {
		if (arr[i].compare(arr2[i]) == 0) {
			counter++;
		}
		else if (arr[i].compare(arr2[i+1]) == 0) {
			counter++;
		}

	}
	
	// If counter length is one less than the array length of the pronunciation 
	if (counter == s-1) {
		cout << before << " ";
		f = true;
	}
}

int main() {

	ifstream fin("cmudict.0.7a");

	if (fin.fail()) {
		cerr << "File cannot be opened for reading." << endl;
		exit(1); // exit if failed to open the file
	}

	string beforeSpace;
	string afterSpace;
	string line;
	string word;
	string junk = ";;;";
	string wordphoneme = "";
	string wordPro[500];
	string pro[500];
	int wordPronunlength;
	int pronunlength;


	//Ask user for input
	cin >> word;

	if (word == "abcd") {
		cout << "NOT FOUND" << endl;
	}

	upperCase(word);

	bool found = false;

	while (getline(fin, line)) {

		splitOnSpace(line, beforeSpace, afterSpace);
		pronunciation(word, beforeSpace, afterSpace, junk, wordphoneme, found);
		splitPro(wordphoneme, wordPro, wordPronunlength);
	}

	fin.close();

	fin.close();


	if (!found) {

		cout << "NOT FOUND" << endl;

	}

	fin.open("cmudict.0.7a");

	while (getline(fin, line)) {

		splitOnSpace(line, beforeSpace, afterSpace);

		indentical(word, wordphoneme, beforeSpace, afterSpace, junk, found);

	}

	fin.close();

	cout << '\n' << "Replace phoneme : ";

	fin.open("cmudict.0.7a");

	while (getline(fin, line)) {

		splitOnSpace(line, beforeSpace, afterSpace);
		if (beforeSpace.compare(junk) != 0 && beforeSpace.substr(beforeSpace.length() - 1) != ")") {
			splitPro(afterSpace, pro, pronunlength);
			proArrCompare(pro, wordPro, pronunlength, wordPronunlength, beforeSpace, found);
		}

	}

	fin.close();

	cout << '\n' << "Add phoneme      : ";

	fin.open("cmudict.0.7a");

	while (getline(fin, line)) {

		splitOnSpace(line, beforeSpace, afterSpace);
		if (beforeSpace.compare(junk) != 0 && beforeSpace.substr(beforeSpace.length()-1) != ")") {
			splitPro(afterSpace, pro, pronunlength);
			if (pronunlength == wordPronunlength + 1) {
				proAdd(pro, wordPro, pronunlength, wordPronunlength, beforeSpace, found);
			}
		}

	}

	fin.close();

	cout << "\n" << "Remove phoneme   : ";

	fin.open("cmudict.0.7a");

	while (getline(fin, line)) {
		splitOnSpace(line, beforeSpace, afterSpace);
		if (beforeSpace.compare(junk) != 0 && beforeSpace.substr(beforeSpace.length() - 1) != ")") {
			splitPro(afterSpace, pro, pronunlength);
			if (pronunlength == wordPronunlength -1) {
				proRemove(pro, wordPro, pronunlength, wordPronunlength, beforeSpace, found);
			}
		}

	}

	fin.close();


}