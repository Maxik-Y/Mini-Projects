Input: the path to the text file to be checked, and the path to a custom dictionary file.
This program implements a fast spell checker. It loads a list of words (a dictionary) into a hash 
table for rapid lookup, then reads the specified text file word by word, checking whether each word 
exists in the dictionary. It outputs all misspelled words, along with final statistics for the check.