Design Doc for HW6


## wordle game.c:



#### Score Guess:
- a boolean function that returns true if the guess word is exactly equal to the secret word
- returns false if else
- it goes through each letter of the guess word and compares them to the letters of the secret word
- if the letter of the guess word is both the same letter and in the same place as the secret word, then return a 'g' into result
- if the letter of the guess word is a letter that is within the secret word, just not in the same place, then return a 'y' into result
- (you can check for this by either making a helper function or doing something that would the same as "if guess[i] in secret" in python)
- else if the letter in guess isn't in secret then return a 'x' to result

#### Valid Guess:
- a boolean function that returns true if the guess is one of the strings in the vocabulary
- returns false otherwise
- go through all of vocabulary and use strcmp or strncmp to compare and check if the guess word actually shows up in the big list of allowed vocab words
- if it does then return true, and if it didn't then return false

#### Load Vocabulary:
- char ** function that returns an array of strings
- make sure to use fopen() to open the file
- use strdup or strndup to make copies of each word from the file and make sure to save those copies into the array of words
- this function will parse through all of vocabulary.txt and check to see how many words there are (save it in *num-words)
- allocate starting memory with calloc or malloc and then start filling it in with the vocab words
- make sure that you have it set up so that it reallocates when it needs to depending on how many words are needed/are left using realloc
- make sure to close the file with fclose()

#### Free Vocabulary:
- This should free things in reverse order of load vocabulary
- Have a for loop that goes through vocabulary and frees each individual word of the vocab in the array
- Free the actual pointer to vocabulary (you only need to do this once even if you realloc more than once)

## hw6.c



#### Make Sure All the Memory is Freed:
- This should just be making sure that free vocabulary works when it's getting called at the end of hw6.c
