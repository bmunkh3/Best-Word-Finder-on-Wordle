//  bestWordle.c
//  Author: Bill Munkh-Erdene
//  Date: 11/02/2022
//  Late Submission Essay: All of the code is my own, I didn't use any code from the posted program solution. To start off, my function that reads in the file and gets the size and my function that reads in a file and stores words is practically identical to the posted program solution since a template was already provided. Moving on, in the posted solution, the professors separated the process of reading in words from the files into the arrays into a separate function. I opted to have this process contained in my main function, only executed when menu option 1 or 2 is chosen by the user. I chose to do this because it was rather convenient and easier to go through the process of reading in the files. I opted to use a function that returns the integer value of the amount of words in each file, this was chosen for ease of use. In terms of what would be the better solution, either the posted solution or my solution could work and fulfill the purpose of retrieving the size of a file. The function that calculates the word comparison score in the posted solution and my solution is very similar, though the difference is in the parameters. I chose to pass down structs of the word arrays instead of passing down char types, this created more reiteration of a certain line of code that I would have to write when wanting to access the char words in my struct, or the int score. I think the posted program solution is the definitive choice due to the fact that it’s easier to understand, it makes the code less bloated and far more readable. Although my code was bloated, passing down structs into the function parameters definitely made it easier to work with in a single function. I was able to find the similarity between the answer words and guess words in my function, as well as attain the similarity score of a word. In the posted program solution, since the char types of the struct were passed, and not the struct itself, the function that gets the similarity score of words had to be split into two functions instead. Despite this difference, I still think the posted program’s solution is more intuitive, readable, and understandable than my own solution. As for the function that finds the second top words, I did not create a separate variable for the top scoring word, in hindsight, this definitely would have saved me a lot of time and made the code more understandable. Interestingly enough, I didn’t have the inclusion of DebugOn for checking my words in descending order / the top scoring words. I checked the similarity score of my words by having individual printf statements in several of my functions and my main function to make sure my outputs were exactly what I wanted.  I think in this case, since both my function and the professors’ posted program solution is similar to one another, I am unable to determine the definitive solution. However, I will say that for the next program, I will definitely use the posted program 3 solution as my template to begin working from.
//
//
//  Links to wordle dictionary words at:
//    https://www.reddit.com/r/wordle/comments/s4tcw8/a_note_on_wordles_word_list/
//


#include <stdio.h> //
#include <stdlib.h> // for exit( -1)
#include <string.h> // for string functions

// struct that stores the Wordle's words/score
struct Wordle {
  char word[6];
	int score;
};

typedef struct Wordle wordCountStruct;

// declaring variables to use them in any order
int compareFunction( const void * a, const void * b);
int readFileCountWords(char fileName[81]);
void readFileStoreWords(char fileName[81], wordCountStruct **array, int index);
void wordSimScore(wordCountStruct **wordArray, wordCountStruct *wordArrayA, int wordNumAnswers, int wordNumGuesses);
void wordSecondScore(wordCountStruct **wordSecondArray, wordCountStruct *wordSecondAnsArr, int wordNumAnswers, int wordNumGuesses);

//-----------------------------------------------------------------------------------------

// begin readFileCountWords(...) - Function reads in the file and gets the size of file
int readFileCountWords(char fileName[81]) {
        
      	int words = 0;
      	FILE *inFilePtr = fopen(fileName, "r"); // Connect logical name to filename
      
      	char inputString[81];
      
      	// Sanity check: ensure file open worked correctly
      	if (inFilePtr == NULL) {
              
          		printf("Error: could not open %s for reading\n", fileName);
          		exit(-1); // must include stdlib.h
          
      	}
      
      	// Read each word from file and print it.
      	while (fscanf(inFilePtr, "%s", inputString) != EOF) {
          		words++;
      	}
        
      	// Close the file
      	fclose(inFilePtr);
      	return words;
} // end readFileCountWords(...)

//-----------------------------------------------------------------------------------------

// begin readFileStoreWords(...) - Function reads in the file and stores the words into the allocated space in the array
void readFileStoreWords(char fileName[81], wordCountStruct **array, int index) {
        
      	FILE *inFilePtr = fopen(fileName, "r"); // Connect logical name to filename
      	char inputString[81];
      
      	// Sanity check: ensure file open worked correctly
      	if (inFilePtr == NULL) {
            		printf("Error: could not open %s for reading\n", fileName);
            		exit(-1); // must include stdlib.h
      	}
      
      	// Read each word from file and print it.
      	while (fscanf(inFilePtr, "%s", inputString) != EOF) {
            	  //print("%s", inputString);
            		strcpy((*array)[index++].word, inputString);
      		
      	}
      	// Close the file
      	fclose(inFilePtr);
} // end readFileStoreWords(...)

//-----------------------------------------------------------------------------------------

// begin wordSimScore(...) - Function to determine similarity between given guessed words and given answer words
void wordSimScore(wordCountStruct **wordArray, wordCountStruct *wordArrayA, int wordNumAnswers, int wordNumGuesses) {
      char blank[6];  // temp variable to store original array words
      char letter[6];  // temp variable to store original array answer words
      
    	for (int i = 0; i < wordNumAnswers + wordNumGuesses; i++) {
            (*wordArray)[i].score = 0;
        
        		for (int j = 0; j < wordNumAnswers; j++) {
        
            			strcpy(blank, (*wordArray)[i].word);
            			strcpy(letter, wordArrayA[j].word);

                  // 3 points for correct word and correct position
                  for (int k = 0; k < 5; k++) {
                    
                        if(blank[k] == letter[k]) {

                              // adding to score
                              (*wordArray)[i].score += 3;
                              // blanking out already visited letters
                              blank[k] = '=';
                              letter[k] = '-';
                          
                        }
                  }
                  // 1 point for correct word but wrong position
                  for (int x = 0; x < 5; x++) {
                    
                        for (int y = 0; y < 5; y++) {
                      
                              if (blank[x] == letter[y]) {
                                    // adding to score   
                                    (*wordArray)[i].score += 1;
                                    // blanking out already visited letters
                                    blank[x] = '=';
                                    letter[y] = '-';
                                    
                              }
                        }
                  }
    		    }
    	}
} //end wordSimScore(...)

//-----------------------------------------------------------------------------------------

// begin wordSecondScore(...) - Function that finds the second top results
void wordSecondScore(wordCountStruct **wordSecondArray, wordCountStruct *wordSecondAnsArr, int wordNumAnswers, int wordNumGuesses) {
        char topSecondWordTemp[6];  // temp variable to store original array words
        char topSecondAnswerTemp[6];  // temp variable to store original array answer words
      
        wordSimScore(wordSecondArray, wordSecondAnsArr, wordNumAnswers, wordNumGuesses);
        qsort(*wordSecondArray, (wordNumGuesses + wordNumAnswers), sizeof(wordCountStruct), compareFunction);
  
      // Allocating space for copy of best second words
        wordCountStruct *wordArray = (wordCountStruct *)malloc(sizeof (wordCountStruct) * (wordNumAnswers + wordNumGuesses));

      // Allocating space for copy of best second answer words
        wordCountStruct *wordAnswersArray = (wordCountStruct *)malloc(sizeof (wordCountStruct) * (wordNumAnswers));
    
    
        for (int a = 0; (*wordSecondArray)[a].score == (*wordSecondArray)[0].score; a++) {
            printf("%s %d\n", (*wordSecondArray)[a].word, (*wordSecondArray)[a].score);

          
            for (int i = 0; i < wordNumAnswers; i++) {
                // creating temp copies of the original arrays
                strcpy(topSecondWordTemp, (*wordSecondArray)[a].word);
                strcpy(topSecondAnswerTemp, wordSecondAnsArr[i].word);
              
                // for loop to check each letter in array
                for (int j = 0; j < 5; j++) {
                      if (topSecondWordTemp[j] == topSecondAnswerTemp[j]) {
                            topSecondWordTemp[j] = '-';
                            topSecondAnswerTemp[j] = '+';
                      }
                }
              
                // for loop to check each letter in the answers array
                for (int x = 0; x < 5; x++) {
                      for (int y = 0; y < 5; y++) {
                            if (topSecondWordTemp[x] == topSecondAnswerTemp[y]) {
                                  topSecondWordTemp[x] = '-';
                                  topSecondAnswerTemp[y] = '+';
                            }
                      }
                }
              
              strcpy(wordAnswersArray[i].word, topSecondAnswerTemp);
            }
        
            for (int i = 0; i < wordNumAnswers + wordNumGuesses; i++) {
                  strcpy(wordArray[i].word, (*wordSecondArray)[i].word);

                  //printf("    %s %d\n", wordArray[i].word, wordArray[i].score);
            
            }
        
            wordSimScore(&wordArray, wordAnswersArray, wordNumAnswers, wordNumGuesses);
            qsort(wordArray, (wordNumGuesses + wordNumAnswers), sizeof(wordCountStruct), compareFunction);
        
            for (int i = 0; wordArray[i].score == wordArray[0].score; i++) {
              printf("    %s %d\n", wordArray[i].word, wordArray[i].score);
            }
        }

        // Freeing up used memory
        free(wordArray);
        free(wordAnswersArray);
} // end wordSecondScore(...)


//-----------------------------------------------------------------------------------------

// begin compareFunction(...)
int compareFunction( const void * a, const void * b) {
        // Before using parameters we have cast them into the actual type they are in our program
        // and then extract the numerical value used in comparison
        int firstScore = ((wordCountStruct *) a)->score;
        int secondScore = ((wordCountStruct *) b)->score;
    
        // If scores are different, then that's all we need for our comparison.
        if (firstScore != secondScore) {
            // We reverse the values, so the result is in descending vs. the otherwise ascending order
            // return firstScore - secondScore;   // ascending order
            return secondScore - firstScore;      // descending order
        }
        else {
            // Scores are equal, so check words themselves, to put them in alphabetical order
    	  // Hint: return the value of strcmp( parameter a word,  parameter b word)
            return strcmp( ((wordCountStruct *) a) -> word, ((wordCountStruct *) b) -> word);
        }
} //end compareFunction(..)

// -----------------------------------------------------------------------------------------

// begin main()
int main() {
      	char answersFileName[81]; // = "answersTiny.txt"; // Stores the answers file name
      	char guessesFileName[81]; // = "guessesTiny.txt"; // Stores the guesses file name
      
      	// Set default file names to open
      	strcpy(answersFileName, "answersTiny.txt");
      	strcpy(guessesFileName, "guessesTiny.txt");
  
      	printf("Default file names are %s and %s\n", answersFileName, guessesFileName);
      
      	// Display menu, to allow partial credit for different program components
      	int menuOption = 0;
      	do {
          		printf("\n");
          		printf("Menu Options:\n");
          		printf("  1. Display best first words only\n");
          		printf("  2. Display best first and best second words\n");
          		printf("  3. Change answers and guesses filenames\n");
          		printf("  4. Exit\n");
          		printf("Your choice: ");
          		scanf("%d", &menuOption);
          
          		// Handle menu option 3 to exit the program
          		if (menuOption == 4) {
              			exit(1); // Exit the program  
          		}
          		else if (menuOption == 3) {
              			// Change file names.  Menu will then be redisplayed.
              			printf("Enter new answers and guesses filenames: ");
              			scanf("%s %s", answersFileName, guessesFileName);
              }
          
              // Handle menu option 1 to display best first words only
          		if (menuOption == 1) {  
                    // Getting size of both text files
                    int wordNumAnswers = readFileCountWords(answersFileName);
                    int wordNumGuesses = readFileCountWords(guessesFileName);
                
                    printf("%s has %d words\n", answersFileName, wordNumAnswers);
                    printf("%s has %d words\n\n", guessesFileName, wordNumGuesses);
                
                    // Allocating space for answers separately for comparison
                    wordCountStruct *wordAnswersArray = (wordCountStruct *)malloc(sizeof(wordCountStruct) * wordNumAnswers);
                    // Allocating space for answers and guesses combined
                    wordCountStruct *wordArray = (wordCountStruct *)malloc(sizeof(wordCountStruct) * (wordNumGuesses + wordNumAnswers));
                
                    // Filling in the struct wordArray and wordAnswersArray with their respective files
                    readFileStoreWords(answersFileName, &wordAnswersArray, 0);
                    readFileStoreWords(answersFileName, &wordArray, 0);
                    readFileStoreWords(guessesFileName, &wordArray, wordNumAnswers);
                      
                    // Getting the similarity score between the answer words and guess words
                    wordSimScore(&wordArray, wordAnswersArray, wordNumAnswers, wordNumGuesses);
                    qsort(wordArray, (wordNumGuesses + wordNumAnswers), sizeof(wordCountStruct), compareFunction);

                    //printf("All words in descending order by score:\n");
                    /*
                    for (int i = 0; i < wordNumAnswers + wordNumGuesses; i++) {
                          printf("%s %d\n", wordArray[i].word, wordArray[i].score);
                    }
                    */

                      printf("Words and scores for top first words:\n");
                
                    for (int i = 0; wordArray[i].score == wordArray[0].score ; i++) {
                          printf("%s %d\n", wordArray[i].word, wordArray[i].score);
                    } 

                    // Freeing up used memory
                    free(wordArray);
                    free(wordAnswersArray);

          		}

              // Handle menu option 2 to display the best first and second words
              if (menuOption == 2) {
                    // Getting size of both text files
                    int wordNumAnswers = readFileCountWords(answersFileName);
                    int wordNumGuesses = readFileCountWords(guessesFileName);
                
                    printf("%s has %d words\n", answersFileName, wordNumAnswers);
                    printf("%s has %d words\n\n", guessesFileName, wordNumGuesses);
                
                    // Allocating space for answers separately for comparison
                    wordCountStruct *wordSecondAnswersArray = (wordCountStruct *)malloc(sizeof(wordCountStruct) * wordNumAnswers);
                    // Allocating space for answers and guesses combined
                    wordCountStruct *wordSecondArray = (wordCountStruct *)malloc(sizeof(wordCountStruct) * (wordNumGuesses + wordNumAnswers));
                
                    // Filling in the struct wordArray and wordAnswersArray with their respective files
                    readFileStoreWords(answersFileName, &wordSecondAnswersArray, 0);
                    readFileStoreWords(answersFileName, &wordSecondArray, 0);
                    readFileStoreWords(guessesFileName, &wordSecondArray, wordNumAnswers);

                    printf("Words and scores for top first words and second words:\n");

                    // Getting the similarity score between the answer words and guess words
                    wordSecondScore(&wordSecondArray, wordSecondAnswersArray, wordNumAnswers, wordNumGuesses);
                    qsort(wordSecondArray, (wordNumGuesses + wordNumAnswers), sizeof(wordCountStruct), compareFunction);
                
                    /*
                    for (int i = 0; wordSecondArray[i].score == wordSecondArray[0].score; i++) {
                      printf("    %s %d\n", wordSecondArray[i].word, wordSecondArray[i].score);
                    } */

                    // Freeing up used memory
                    free(wordSecondArray);
                    free(wordSecondAnswersArray);
                    
              }

          
        } while (menuOption == 3);


      	printf("Done\n");
      	return 0;
} // end main()
