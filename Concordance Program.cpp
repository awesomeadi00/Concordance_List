/*----------------------------------------------------------------------------------------*/
/* Name: Aditya Pandhare, Student Number: N17706593 */
/* Date: November 11, 2021. */
/* Program: Assignment 3 - Concordance of Text File.cpp */
/* Description: This program reads text from a text file and generates a Concordance List. */
/*----------------------------------------------------------------------------------------*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include<cstring>

using namespace std;

void readFile(string filename);
void removeNonAlpha(string wordarray[], int size);
void lowerCase(string wordarray[], int size);
void sortString(string wordarray[], int size);
void searchString(string wordarray[], int size);
void printConcordance(string final_array[], int final_size, int word_freq[], int size2);

int main() {
    
    string filename;
    cout << "Welcome to the Concordance Reader!" << endl;
    cout << "What is the name of the file you would like to input: " << endl;
    cin >> filename;
    
    readFile(filename); //Sends the filename input to the readFile function to generate an ifstream.

    return(0);
}

//This function reads in every word from the text file and puts it into an array of strings.
void readFile(string filename) {
    
    ifstream infile; //creates ifstream to read in data from the file inputted by the user.
    infile.open(filename, ios:: in);
    if(infile.fail()) {
        cout << "Error: The file could not opened." << endl;
        exit(1);
    }
    
    int size(0); //size of the array or the number of words in the text file.
    string word;
    string *arrayptr = new string[size]; //pointer called arrayptr points to a string array block in the heap with the size as 'size'
       
       for(int i=0; !infile.eof(); i++) { //While it's not the end of the file, read a word and store it into the array and increment the size by 1 hence a new block in the heap is allocated for the next word.
           infile >> word;
           arrayptr[i] = word;
           size++;
       }
       
       string wordarray[size]; //This transfers the array pointer to a static array so we can delete the pointer and pass the static to the other functions so it's easier to work with.
       
       for(int i=0; i<size; i++) {
           wordarray[i] = arrayptr[i];
       }
       
    delete[] arrayptr; //dealloacted memory that the pointer is pointing to.
    removeNonAlpha(wordarray, size); //Calls the remove non alphabetical characters function by passing the array and its size.
    
    infile.close();
    
}

//This function will remove every non-alphabetical character in the array of strings.
void removeNonAlpha(string wordarray[], int size) {
    
    double wordlength;
    string temp = "";
    
    //array[i] of a string accesses the word, array[i][j] accesses the letter of that word.
    //This loop takes a word, finds its wordlength, then cycles through every character of that word to see if it's a non-alphabetical character. If it is, it puts it in an empty string. Once it cycles through every letter in the word, it assigns that string to the array once again and empties the string again for the next word.
    for(int i=0; i<size; i++) {
        wordlength = wordarray[i].size(); //This assigns wordlength the exact number of letters of a string in the array.
        
        for(int j=0; j < wordlength; j++){ //This checks if the character read is between ASCII values A-Z and a-z
            if((wordarray[i][j] >= 'A' && wordarray[i][j] <= 'Z') || (wordarray[i][j] >= 'a' && wordarray[i][j] <= 'z')) {
                temp = temp + wordarray[i][j]; //If it is between those values, it will put it into the empty string.
            }
        }
        wordarray[i] = temp; //Once the loop for the entire word is completed, it will assign this string to the array once again.
        temp = ""; //The temp string is emptied out again for the next word.
    }
    
    lowerCase(wordarray, size); //Calls the lowercase function by passing this processed array and its size.
}

//This function will convert all uppercase alphabetical characters to a lowercased alphabetical character.
void lowerCase(string wordarray[], int size) {
    
    double wordlength;
    string temp = "";
    
    //Similar process to the previous function. This loop takes a word, finds its wordlength, then cycles through every character of that word to see if is an uppercase. If it is, it will convert it to a lowercase.
    for(int i=0; i<size; i++) {
        wordlength = wordarray[i].size();//This assigns wordlength the exact number of letters of a string in the array.
        
        for(int j=0; j < wordlength; j++){
            if(isupper(wordarray[i][j]) == true) { //If the character is an Uppercase, it will lowercase it.
                wordarray[i][j] = tolower(wordarray[i][j]);
            }
        }
    }

    sortString(wordarray, size); //Calls the sorting function by passing this processed array and its size.
}

//This function will sort the array of strings in alphabetical order. Since the ASCII values at this point should be between a-z or (97-122), alphabetical order would mean to arrange the string in ascending order.
void sortString(string wordarray[], int size) {
    
    string temp;
  
    //This loop selects a word from the array and then cycles through the entire array, if the ASCII value of that word if greater than the next word, it will swap them as it needs to be in ascending order, otherwise it will continue looking throughout the entire.
    for (int i=0; i<size; i++) {
        for (int j=i+1; j < size; j++) {
            if(wordarray[i] > wordarray[j]) {
                temp = wordarray[i]; //These three lines execute the swap between the word and the next word.
                wordarray[i] = wordarray[j];
                wordarray[j] = temp;
            }
        }
    }

    searchString(wordarray, size); //Calls the searching function by passing this processed array and its size.
}

//This function calculates the frequency of occurrences of each word in the string array of the text file that the user inputted.
void searchString(string wordarray[], int size) {
    
    int final_size(0); //This is the final size of the string array
    int frequency(0); //This is a variable to find the frequency of occurrence for each word.
    
    int *word_freqptr = new int[final_size]; //pointer word_freqptr points to an integer array block in the heap with the size as 'final_size'
    string *final_arrayptr = new string[final_size]; //pointer final_arrayptr points to a string array block in the heap with the size as 'final_size'
  
    final_arrayptr[0] = wordarray[0]; //Assigns the first element of wordarray to final_arrayptr
    
    //Then it cycles through the entire array, if that word is the same as the one in final_arrayptr then it will continue as we don't want repeated words. If it is not, it will put it in final_arrayptr and increment it so another word can go into the next element.
    for(int i=1; i<size; i++) {
        
        if(wordarray[i] == final_arrayptr[final_size]) {
            continue;
        }
        
        if(wordarray[i] != final_arrayptr[final_size]) {
            final_size++;
            final_arrayptr[final_size] = wordarray[i];
        }
    }
    final_size++; //To solidify the size of final_size.
    
    string final_array[final_size];
    
    for(int i=0; i<final_size; i++) { //This transfers the final_array pointer to a static array so we can delete the pointer and pass the static to the other functions so it's easier to work with.
        final_array[i] = final_arrayptr[i];
    }
        
    //This loops takes a word from final_array, then cycles through the previous wordarray and calculates the frequency of occurence. If the word matches, it increases the frequency. Otherwise it continues.
    for(int i=0; i < final_size; i++) {
        for(int j=0; j < size; j++) {
            if(final_arrayptr[i] == wordarray[j]) {
                frequency++;
            }
            else
                continue;
        }
        word_freqptr[i] = frequency; //Then once the loop is done, it assigns the calculated frequency to the word_freqptr array. This array will contain all the frequency of occurences of each word.
        frequency = 0; //Refreshes frequency to 0 for the next word.
    }
    
    int word_freq[final_size];
    
    for(int i=0; i<final_size; i++) { //This transfers the word_freq pointer to a static array so we can delete the pointer and pass the static to the other functions so it's easier to work with.
        word_freq[i] = word_freqptr[i];
    }
    
    delete[] final_arrayptr; //deallocated memory that both of these pointers are pointing to.
    delete[] word_freqptr;
    
    printConcordance(final_array, final_size, word_freq, final_size);  //Calls the printing function by passing both of these new arrays and their sizes.
}
     
//This function simply prints out the string array containing the words and the integer array containing the frequencies on the output screen and writes them on an output file called "Concordance.txt"
void printConcordance(string final_array[], int final_size, int word_freq[], int size2) {

    ofstream outfile; //created ofstream to write concordance list on an output file.
    outfile.open("Concordance.txt", ios::out);
    
    if(outfile.fail()) {
        cout << "Error: Could not create the file." << endl;
        exit(1);
    }
    
    cout << "\n";
    cout << "Your concordance list has been successfully created on: Concordance.txt in your directory." << endl;
    
    outfile << "Concordance of your Input File: " << endl;
    outfile << "\n";
    outfile << setw(15) << left << "Words" << setw(15) << left << "Frequency" << endl;
    
    cout << "Concordance of your Input File: " << endl;
    cout << "\n";
    cout << setw(15) << left << "Words" << setw(15) << left << "Frequency" << endl;
    
    //Prints out and writes on output file the string array containing words and integer rarray containing the frequencies in a tabular format.
    for(int i=0; i< final_size; i++) {
        outfile << setw(15) << left << final_array[i] << setw(15) << left << word_freq[i] << endl;
        cout << setw(15) << left << final_array[i] << setw(15) << left << word_freq[i] << endl;
    }
    outfile.close();
}
