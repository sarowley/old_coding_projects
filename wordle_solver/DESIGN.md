Design Doc for HW7


## search-util.c:



#### Score Letter:
- This is an int function that takes in the parameters of the specific letter, the vocab array, and the number of words and returns how many words in the list contain that specific letter
- This function starts by looping through the vocabulary num-words times
- Within the loop check if the word has the specified letter
- If it does the add one to a counter that will be returned at the end of the function 
- (Make sure this function isn't double counting letters, so irate shows up instead of eerie)

#### Score Word:
- This is a int function that takes the specific word and the letter scores, and uses them to return the score of the word
- Loop through the letter scores 26 times keeping track of the individual letter score and making sure to add it to a tally that gets returned at the end
- (Make sure to check that a repeating letter isn't added to the score, ex) if 'e' shows up three times it's only adds to the score total once.)

#### Filter Vocabulary Gray:
- This is a size-t function that takes in the specific letter, the complete array of the vocabulary, and the total number of words, and returns the number of words that have been erased
- Loop through all the words in the vocabulary list and check to see if the specific letter is in any of the words
- If it is in the words then make sure to free the pointer related to the word and then set it to NULL
- Keep track of the number of words deleted with a counter and make sure to implement it up by one every time a word is free'd and set to NULL

#### Filter Vocabulary Yellow:
- This is a size-t function that takes in the letter, the position the letter is at, the array of the vocab words, and the total number of words, then returns the number of words that have been removed from the list
- Loop through all the words and check if the specific letter is at the specified position in the word
- If any of the words have the letter in that specific place, then free and set the word equal to NULL
- Then go through and check against all the remaining words if any of them don't contain the letter (regardless of position) and if they don't have the letter then free them and set them to NULL
- Keep a counter of and make sure to return the total number of words that have been free'd and deleted.

#### Filter Vocabulary Green:
- This is a size-t function that takes in the specified letter, the position of the letter in the word, the array of vocab words, and the total number of words left, and returns the number of words removed from the list
- Loop through all the words in the list and check if they don't have the specified letter in the specific place
- If the word doesn't have the letter in the specific place then free it and set it to NULL
- Keep a counter of and make sure to increment and return the total number of words that have been free'd and deleted.
