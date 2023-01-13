#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstring>
#include <vector>
using namespace std;

//Function Prototypes
void removeNonAlpha(vector<string>& words, int size);
void lowerCase(vector<string>& words, int size);
void sortString(vector<string>& words, int size);
void searchString(vector<string> words, int size);
void printConcordance(vector<string> final_words, vector<int> word_freq, int final_size);

//===============================================================================================================
int main() {
    string filename;
    cout << "Welcome to the Concordance Reader!" << endl;
    cout << "What is the name of the file you would like to input: ";
    cin >> filename;

    //Creates ifstream to read in data from the file inputed by the user.
    ifstream infile;
    infile.open(filename, ios:: in);
    if(infile.fail()) {
        cout << "Error: The file could not opened." << endl;
        exit(1);
    }
    
    int size(0);
    string word;
    vector<string> words(size);

    //This simply checks if the file is empty, then it will not execute the program and simply terminate.
    if(infile.peek() == ifstream::traits_type::eof()) {
        cout << "File is empty!" << endl;
        exit(2);
    }
    
    //This will read a word and store it into the array and increment the size.
    for(int i=0; !infile.eof(); i++) {
        infile >> word;
        words.push_back(word);
        size++;
    }

    removeNonAlpha(words, size);    //Calls function to remove all non-alphabetical characters.
    lowerCase(words, size);         //Calls function to lowercase all alphabets in each word.
    sortString(words, size);        //Calls function to sort all words in alphabetical order.
    searchString(words, size);      //Calls function to calculates the frequency of occurrences for each word.
    
    infile.close();
    return(0);
}

//===============================================================================================================
//This function will remove every non-alphabetical character in the array of strings.
void removeNonAlpha(vector<string>& words, int size) {
    unsigned long wordlength;
    string word;
    string temp = "";
    
    for(int i=0; i<size; i++) {
        wordlength = words[i].size(); //wordlength = exact number of letters of a word.
        word = words[i];
        
        for(int j=0; j < wordlength; j++){ //This checks if the character read is between ASCII values A-Z and a-z
            if((word[j] >= 'A' and word[j] <= 'Z') or (word[j] >= 'a' and word[j] <= 'z')) {
                temp = temp + word[j]; //If it is between those values, it will put it into the empty string.
            }
        }
        
        words[i] = temp; //It will assign the word (without non-alpha) back into the vector index.
        temp = ""; //The temp string is emptied out again for the next word.
    }
}

//===============================================================================================================
//This function will convert all uppercase alphabetical characters to a lowercased alphabetical character.
void lowerCase(vector<string>& words, int size) {
    unsigned long wordlength;
    string word;
    
    for(int i=0; i<size; i++) {
        wordlength = words[i].size();
        word = words[i];
        
        for(int j=0; j < wordlength; j++){
            if(isupper(word[j]) == true) { //If the character is an Uppercase, it will lowercase it.
                word[j] = tolower(word[j]);
            }
        }
        
        words[i] = word; //takes the lowercased word and puts it back into the vector.
    }
}

//===============================================================================================================
//This function will sort the array of strings in alphabetical order. Since the ASCII values at this point should be between a-z or (97-122), alphabetical order would mean to arrange the string in ascending order.
void sortString(vector<string>& words, int size) {
    string temp;
  
    //Bubble Sort:
    for (int i=0; i<size; i++) {
        for (int j=i+1; j < size; j++) {
            if(words[i] > words[j]) { //If the word is greater than the one ahead, then swap
                temp = words[i];
                words[i] = words[j];
                words[j] = temp;
            }
        }
    }
}

//===============================================================================================================
//This function calculates the frequency of occurrences for each word in the text file
void searchString(vector<string> words, int size) {
    int final_size(0); //This is the final size of the final_words vector.
    vector<string> final_words(final_size); //This vector is the final vector for all the words (removes repeated words)
        
    final_words.push_back(words[0]); //Assigns the first element.
    
    //We go through every word, if it is found in the final vector, then it is ignored as we want to remove repeated words, else we will add it into the final vector.
    for(int i = 1; i < size; i++) {
        if(words[i] == final_words[final_size]) {
            continue;
        }
        
        if(words[i] != final_words[final_size]) {
            final_size++;
            final_words.push_back(words[i]);
        }
    }
    
    final_size++; //To solidify the size of final_size.
    
    
    int frequency(0); //This is a variable to find the frequency of occurrence for each word.
    vector<int> word_freq(final_size); //This vector contains all the frequencies of occurences for each word.
    
    //This loops takes a word from final_words, then cycles through the initial words vector and calculates the frequency of occurence. If the word matches, it increases the frequency. Otherwise it continues.
    for(int i=0; i < final_size; i++) {
        for(int j=0; j < size; j++) {
            if(final_words[i] == words[j]) {
                frequency++;
            }
            else
                continue;
        }
        
        word_freq[i] = frequency; //Once the loop is done, it assigns the calculated frequency to the vector.
        frequency = 0; //Refreshes frequency to 0 for the next word.
    }
    
    printConcordance(final_words, word_freq, final_size); //This will call the print function directly.
}
    
//===============================================================================================================
//This function prints out the concordance list on the output and also onto an output .txt file.
void printConcordance(vector<string> final_words, vector<int> word_freq, int final_size) {
    ofstream outfile; //created ofstream to write concordance list on an output file.
    outfile.open("Concordance.txt", ios::out);
    
    if(outfile.fail()) {
        cout << "Error: Could not create the file." << endl;
        exit(1);
    }
    
    cout << "\n";
    cout << "Your concordance list has been created on: Concordance.txt in your directory." << endl;
    
    outfile << "Concordance of your Input File: " << endl;
    outfile << "\n";
    outfile << setw(15) << left << "Words" << setw(15) << left << "Frequency" << endl;
    
    cout << "Concordance of your Input File: " << endl;
    cout << "\n";
    cout << setw(15) << left << "Words" << setw(15) << left << "Frequency" << endl;
    
    //Prints out and writes on output file the string array containing words and integer rarray containing the frequencies in a tabular format.
    for(int i=0; i< final_size; i++) {
        outfile << setw(15) << left << final_words[i] << setw(15) << left << word_freq[i] << endl;
        cout << setw(15) << left << final_words[i] << setw(15) << left << word_freq[i] << endl;
    }
    outfile.close();
}
