# BPlus Tree
This code implements a B-tree data structure for a dictionary. The B-tree is a self-balancing tree that allows efficient insertion, deletion, and search operations. 

The program begins by creating a B-tree structure with the specified number of children per node. It then reads word pairs from a file and inserts them into the B-tree. Each word pair consists of an English word and its corresponding translation in another language (in this case, Bangla). 

To insert a word pair, the code searches for the appropriate leaf node in the B-tree based on the English word's alphabetical order. If the leaf node is full, it splits into two leaf nodes to accommodate the new entry. The splitting process also updates the parent nodes accordingly.

Once the B-tree is constructed, the program allows the user to enter English words for translation. It performs a search operation to locate the leaf node containing the word, and then searches within the leaf node for the exact word. If found, it displays the corresponding Bangla translation; otherwise, it indicates that the word is not present in the dictionary.

The code utilizes various helper functions to create nodes, insert data, and search for leaf nodes. It also incorporates timing functionality to measure the execution time of each search operation.

Overall, this code demonstrates the implementation of a B-tree data structure for efficient dictionary operations, including insertion and search, making it suitable for managing large collections of words and their translations.
