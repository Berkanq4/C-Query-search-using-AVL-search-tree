CS300 – Fall 2023-2024 - Sabancı University
Homework #2 – Search Engine
Due November 24 Friday at 22:00
Brief Description
In this homework, you will write a search engine. The search engines in real life, search
hundreds of millions web pages to see if they have the words that you have typed, and they can
do this for thousands of users at a given time. In order to do these searches really fast, search
engines such as Google do a lot of what we call preprocessing of the pages they search; that is,
they transform the contents of a web page (which for the purposes of this homework, we will
assume to consist of only strings) into a structure that can be searched very fast.
In this homework, you are going to preprocess the documents provided to you. For each unique
word, you will insert a node into your AVL Search Tree. Of course you will also keep track of the
details such as the document name which the word appears in and the number of times the
word appears in each document. So, you need to implement a templated AVL Search Tree first.
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
Program Flow
You need to get the number of documents that you need to preprocess first. Then, after getting
the names of all documents from the console, you need to preprocess all the text in the
documents. Only the alphabetical characters are considered, and the unique words need to be
case insensitive (for example; “izmir” and “Izmir” are the same). The rest (such as digits or
punctuation characters) will be ignored. For each unique word appearing in the text, you need
to insert a new node into the tree. If the node is already there, you need to update the node
with the information about this document. For example; you have preprocessed the “a.txt”
document first and there is only one “the” word in this document. You need to insert “the”
word into the AVL Search Tree. Then, while preprocessing the “b.txt” document, “the” word
appears 4 times. So, you need to add this information ({“b.txt”, 4}) into the existing node in your
BST and the node of “the” word becomes {{“a.txt”, 1}, {“b.txt”, 4}}.
After you preprocess all the documents, you need to get a query from the console which
consists of a line of strings (HINT: You may use getline(cin, line)). This line might consist of more
than one word. Then, you need to output the document names in which all words in the query
appear, including the number of times that each word appears in that document.
Hint
struct DocumentItem {
string documentName;
int count;
};
struct WordItem {
string word;
// List of DocumentItem’s. In order to keep the documents
//you can again use the BST that you are going to
implement.
};
template <class Key, class Value>
class AVLSearchTree
{
…
};
and then when you create a AVL Search Tree object it looks like this:
AVLSearchTree<string, WordItem *> myTree;
Sample Runs
The example text files that we will use in the sample runs are as follows:
a.txt
Sabanci sabanci cs CS FENS Engineering Computer
b.txt
Homeworks are so fun. WoW, What a story!!!
Sabanci is so cool. I love 2 CS CS CS CS
Sample Run
Enter number of input files: 2
Enter 1. file name: a.txt
Enter 2. file name: b.txt
Enter queried words in one line: Sabanci
in Document a.txt, sabanci found 2 times.
in Document b.txt, sabanci found 1 times.
Enter queried words in one line: cs sabanci
in Document a.txt, cs found 2 times, sabanci found 2 times.
in Document b.txt, cs found 4 times, sabanci found 1 times.
Enter queried words in one line: sabanci fens
in Document a.txt, sabanci found 2 times, fens found 1 times.
Enter queried words in one line: fun computer Engineer
No document contains the given query
Enter queried words in one line: REMOVE sabanci
sabanci has been REMOVED
Enter queried words in one line: Sabanci
No document contains the given query
Enter queried words in one line: ENDOFINPUT
