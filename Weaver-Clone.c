/*
 ============================================================================
 Name        : Weaver Clone
 Author      : Luke Hartzell
 Version     :2/23/2023
 Description : Text based Weaver Game
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

///*Functions*///==========================================================================

/*goes through the words.txt file and creates an array filled with all words that are the user-inputted length*/
int findWords(int wordLength, char*** wordList) {
	int numWords = 0;
  char **tempList = NULL;
  //int maxsize
  //malloc 100 spaces initially
  //set strlen = to an int and use that instead of calling it for the if statement
  
	char filename[] = "words.txt";
		FILE *filePtr  = fopen(filename, "r"); // "r" means we open the file for reading

		// Check that the file was able to be opened
		if(filePtr == NULL) {
			printf("Error: could not open %s for reading\n", filename);
			exit(-1);
		}

		// Read each word from file, and print them one by one
		char inputString[ 81]; 
		while(fscanf(filePtr, "%s", inputString) != EOF) {
			if(strlen(inputString) == wordLength) {
        numWords++;

        //dont need
    if (*wordList == NULL) {
                *wordList = malloc(sizeof(char*));
            } 
    else { //dont need
      //if(counter == maxsize)
      //maxsize *=2;
      tempList = realloc(*wordList, sizeof(char*) * numWords); // * maxSize
                if (tempList == NULL) {
                    printf("Error: failed to allocate memory for word list\n");
                    exit(-1);
                }
                *wordList = tempList;
            }

            (*wordList)[numWords - 1] = malloc(sizeof(char) * (strlen(inputString) + 1));
            if ((*wordList)[numWords - 1] == NULL) {
                printf("Error: failed to allocate memory for word\n");
                exit(-1);
            }
            strcpy((*wordList)[numWords - 1], inputString);
        }
    }
  
		// Close the file
		fclose(filePtr);
  printf("Number of %d-letter words found: %d. \n\n", wordLength, numWords);


   for (int i = 0; i < numWords; i++) {   
   free((*wordList)[i]);
  
    }
  
    return numWords;
	
	}

/*asks user how many letters they want in the word, calls findWords()*/
 int askWordSize(int* wordLength) {
   int inputtedLength;
   int numWords;
   printf("How many letters do you want to have in the words? ");
   scanf("%d", &inputtedLength);
   *wordLength = inputtedLength;
   
   return 0;
 }

/*checks to make sure length of word is same as inputted length*/
bool checkLength(char *word, int length) {
  return strlen(word) == length;
}

/*checks if word is within the "dictionary" (list of words of orig inputted length)*/
bool inDictionary(char **dictionary, char *wordToCompare, int numWordsInDict) {
  for(int i = 0; i < numWordsInDict; i++) { 
//    printf("%s\n", dictionary[i]);
  //   printf("%s\n", wordToCompare);
    if(strcmp(dictionary[i], wordToCompare) == 0) {
      return true;
    }
  }
  return false;
}


/*overarching function to check input for problems (both for initial words and the inputted word during the game); returns false if a word does
not match the correct length or if it is not a valid dictionary word*/
bool startAndEnd(char **startWord, char**endWord, int numWords, char** listOfWords, int wordLength){
  *startWord = malloc(sizeof(char*));
  *endWord = malloc(sizeof(char*));

  printf("Enter starting and ending words, or 'r' for either for a random word: ");

  scanf("%s %s", *startWord, *endWord);

    //chooses a random start word from the list of x letter words if r is entered as first string
  if(strcmp(*startWord, "r") == 0){
      int r;
        r = rand() % (numWords);
        *startWord = listOfWords[r]; 
  }
  
  //chooses a random end word from the list of x letter words if r is entered as second string
  if(strcmp(*endWord, "r") == 0){
      int r;
        r = rand() % (numWords); 
        *endWord = listOfWords[r]; 
  }

  //sets first word of input to starter word after checking its validity (length and in dictionary)
   if (strcmp(*startWord, "r") != 0){
    if (!(checkLength(*startWord, wordLength))) {
      printf("Your word, '%s', is not a %d-letter word. Try again.\n\n", *startWord, wordLength);
      free(*startWord);
      free(*endWord);
    return false;
    }
     else if(!(inDictionary(listOfWords, *startWord, numWords))) {
       printf("Your word, '%s', is not a valid dictionary word. Try again.\n\n", *startWord);
        free(*startWord);
        free(*endWord);
    return false;
     }
  }

  //sets second word of input to end word after checking its validity (length and in dictionary)
  if (strcmp(*endWord, "r") != 0){
    if (!(checkLength(*endWord, wordLength))) {
      printf("Your word, '%s', is not a %d-letter word. Try again.\n", *endWord, wordLength);
       free(*startWord);
       free(*endWord);
    return false;
    }
     else if(!(inDictionary(listOfWords, *endWord, numWords))) {
       printf("Your word, '%s', is not a valid dictionary word. Try again.\n", *endWord);
        free(*startWord);
        free(*endWord);
    return false;
     }
  }

  
   printf("Your starting word is: %s.\n", *startWord);
  printf("Your ending word is: %s.\n\n", *endWord);
  return true;
}


/*checks the amount of characters different between two words*/
int numDifferences(char *string1, char *string2, int numLetters){
  int differences = 0;
  for(int i = 0; i < numLetters; i++) {
  if(string1[i] != string2[i]) {
  differences++;
   }
  }
  return differences;
}

/*checks if a word inputted during the game is of right length, in dictionary, and exactly one change*/
int checkGameInput(char* checkedWord, int numLetters, char* previousWord, char **wordList, int numWords){

  if(strcmp(checkedWord, "q") == 0){
    //exit(0);
    //return false; //FIX THISSSSS 
    return -1;
    
    }
  
  else if(!(checkLength(checkedWord, numLetters))) {
   printf("Your word, '%s', is not a %d-letter word. Try again.\n", checkedWord, numLetters);
    return 0;
  } 
    
  else if(!(inDictionary(wordList, checkedWord, numWords))){
   printf("Your word, '%s', is not a valid dictionary word. Try again.\n", checkedWord);
    return 0;
  }

//if not exactly one difference
  else if(!(numDifferences(checkedWord, previousWord, numLetters) == 1)) {
   printf("Your word, '%s', is not exactly 1 character different. Try again.\n", checkedWord);
    return 0;
  }
  
return 1;
}


/*if passes validity checks, the inputted word assigned to be the word used in the next step of the game*/
char *nextWord(char* previousWord, char* endWord, int stepCounter, int numLetters, char **wordList, int numWords){
  int validWord = 0;
  char *tempWord = malloc(sizeof(char*));

  while(validWord == 0){
  printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", stepCounter, previousWord, endWord);
  scanf("%s", tempWord);
    validWord = checkGameInput(tempWord, numLetters, previousWord, wordList, numWords);
    if(validWord == -1){
    return "q";
   }
    }
  
  return tempWord;
}


/*portion of the program where the user plays the game*/
int game(char* startWord, char* endWord, int *stepCounter, int numLetters, char** wordList, int numWords) {
  char *previousWord = startWord; //will be the first comparison word
  
    printf("On each move enter a word of the same length that is at most 1 character different and is also in the dictionary.\n");
  printf("You may also type in 'q' to quit guessing.\n\n");

  //while your word is not the goal word
  while(strcmp(previousWord, endWord) != 0) {
     (*stepCounter)++;
    //this will only assign previous word if it passes all the checks, since nextWord() checks for validity
    previousWord = nextWord(previousWord, endWord, *stepCounter, numLetters, wordList, numWords);
    if(previousWord == "q"){
      *stepCounter = 0; //resets step counter for if the user wants to play again
      return 0;
   }
  }
  

  //after the goal word has been reached
  if(strcmp(previousWord, endWord) == 0){
  printf("Congratulations! You changed ‘%s’ into ‘%s” in %d moves.\n", startWord, endWord, *stepCounter);
    }
    *stepCounter = 0; //resets step counter for if the user wants to play again
    return 0;
}
// //=======================================================================================
int main() {
  
  int wordLength;
  char **wordList = NULL;
  char *firstWord = NULL;
  char *endWord = NULL;
  int numWordsInDictionary;
  int stepCounter = 0;
  int menuOption = 0;


  printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");
	printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
	printf("Enjoy!\n\n");

  
 askWordSize(&wordLength);  
  numWordsInDictionary = findWords(wordLength, &wordList);
  /*while the inputted start or end word is not valid, run the function asking for starting and end words, will stop once start and end word are both valid)*/
while (!(startAndEnd(&firstWord, &endWord, numWordsInDictionary, wordList, wordLength))); 


 game(firstWord, endWord, &stepCounter, wordLength, wordList, numWordsInDictionary);

/*choices at the end of program to play again, change number of letters in the word, and exit the program*/
while(menuOption != 3){
  	printf("\nEnter: \t1 to play again,\n");
    printf("\t\t2 to change the number of letters in the words and then play again, or\n");
    printf("\t\t3 to exit the program.\n");
    printf("Your choice --> ");
  scanf(" %d", &menuOption);

  switch(menuOption) {
    case 1:
      free(firstWord);
      free(endWord);
      while (!(startAndEnd(&firstWord, &endWord, numWordsInDictionary, wordList, wordLength)));
      game(firstWord, endWord, &stepCounter, wordLength, wordList, numWordsInDictionary);
    break;
    
    case 2:
      free(wordList);
      free(firstWord);
      free(endWord);
      askWordSize(&wordLength);  
    numWordsInDictionary = findWords(wordLength, &wordList);
    /*while the inputted start or end word is not valid*/
    while (!(startAndEnd(&firstWord, &endWord, numWordsInDictionary,         wordList, wordLength))); 
    game(firstWord, endWord, &stepCounter, wordLength, wordList, numWordsInDictionary);
    break;

    case 3:
      free(firstWord);
      free(endWord);
      free(wordList);
      printf("\nThanks for playing!\n");
      printf("Exiting...");
      return 0;
      break;

    default:
      printf("Invalid menu option. Retry. \n");
      continue;      
  }
}

free(firstWord);
free(endWord);
free(wordList);
}



