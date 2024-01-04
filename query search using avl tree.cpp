#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct DocumentItem {
    string documentName;
    int count;
    DocumentItem() {
        documentName = "";
        count = 0;
    }

};

struct WordItem {
    int height;
    string word;
    DocumentItem* documentItemPtr;
    WordItem* left;
    WordItem* right;
    vector <DocumentItem*> vector_document_items;

    DocumentItem* newDocument(string documentName, int count) {
        documentItemPtr = new DocumentItem;
        documentItemPtr->documentName = documentName;
        documentItemPtr->count = count;
        this->vector_document_items.push_back(documentItemPtr);
        return documentItemPtr;
    }

    WordItem() { //default constructor
        left = nullptr;
        right = nullptr;
        word = "";
        height = 0;
        documentItemPtr = nullptr;
        vector_document_items = {};
    }

    WordItem(string word, WordItem* left, WordItem* right) {
        this->word = word;
        this->left = left;
        this->right = right;
    }

    //create a destructor to handle memeory leaks
    ~WordItem() {

        vector_document_items.clear();

        //delete documentItemPtr;
    }

    //preserve the height of the tree
    int getHeight(WordItem* node) {
        if (node == nullptr) {
            return -1;
        }
        else {
            return node->height;
        }
    }
    void rotateRight() {
        WordItem* newRoot = this->left;
        if (newRoot == nullptr) {
            return;
        }

        this->left = newRoot->right;
        newRoot->right = this;

        this->height = 1 + max(getHeight(this->left), getHeight(this->right));
        newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

        // Update 'this' to the new root of the subtree
        *this = *newRoot;
    }


    void rotateLeft() {
        WordItem* newRoot = this->right;
        if (newRoot == nullptr) {
            return;
        }

        this->right = newRoot->left;
        newRoot->left = this;

        this->height = 1 + max(getHeight(this->left), getHeight(this->right));
        newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

        // Update 'this' to the new root of the subtree
        *this = *newRoot;
    }

    void newNode(WordItem* node) {
        if (node->word < this->word) {
            if (left == nullptr) {
                left = node;
            }
            else {
                left->newNode(node);
            }
        }
        else if (node->word > this->word) {
            if (right == nullptr) {
                right = node;
            }
            else {
                right->newNode(node);
            }
        }

        // Update height of the current node
        height = 1 + max(getHeight(left), getHeight(right));

        // Check balance and rotate if necessary
        int balance = getHeight(left) - getHeight(right);
        if (balance > 1) { // Left subtree is taller
            if (getHeight(left->left) > getHeight(left->right)) { // Left-left case
                rotateRight();
            }
            else { // Left-right case
                left->rotateLeft();
                rotateRight();
            }
        }
        else if (balance < -1) { // Right subtree is taller
            if (getHeight(right->right) > getHeight(right->left)) { // Right-right case
                rotateLeft();
            }
            else { // Right-left case
                right->rotateRight();
                rotateLeft();
            }
        }

    }


    string getData() {
        return word;
    }
    WordItem* getLeft() {
        return left;
    }
    WordItem* getRight() {
        return right;
    }
    void setData(string word) {
        this->word = word;
    }
    void setLeft(WordItem* left) {
        this->left = left;
    }
    void setRight(WordItem* right) {
        this->right = right;
    }

    /*
    void removeNode(string wrd) { //remove node
        if (word < this->word) { //if data is less than current node
            if (left != nullptr) { //if left is not null
                if (left->word == word) { //if left data is equal to data
                    if (left->left == nullptr && left->right == nullptr) { //if left left and left right is null
                        delete left;
                        left = nullptr;
                    }
                    else if (left->left == nullptr) {
                        left = left->right;
                    }
                    else if (left->right == nullptr) {
                        left = left->left;
                    }
                    else {
                        WordItem* temp = left->right;
                        while (temp->left != nullptr) {
                            temp = temp->left;
                        }
                        left->word = temp->word;
                        left->removeNode(temp->word);
                    }

                }
                else {
                    left->removeNode(word);
                }
            }
        }
        else if (word > this->word) {
            if (right != nullptr) {
                if (right->word == word) {
                    if (right->left == nullptr && right->right == nullptr) {
                        delete right;
                        right = nullptr;
                    }
                    else if (right->left == nullptr) {
                        right = right->right;
                    }
                    else if (right->right == nullptr) {
                        right = right->left;
                    }
                    else {
                        WordItem* temp = right->right; //if right right is not null
                        while (temp->left != nullptr) { //while temp left is not null
                            temp = temp->left;
                        }
                        right->word = temp->word;
                        right->removeNode(temp->word);
                    }
                }
                else {
                    right->removeNode(word);
                }
            }
        }
    }*/

    WordItem* removeNode(string wrd) {
        WordItem* newRoot = this; // By default, the new root is 'this'
        if (wrd < this->word) {
            if (left != nullptr) {
                left = left->removeNode(wrd);
            }
        }
        else if (wrd > this->word) {
            if (right != nullptr) {
                right = right->removeNode(wrd);
            }
        }
        else {
            // Node with only one child or no child
            if (left == nullptr || right == nullptr) {
                WordItem* temp = left ? left : right;

                // No child case
                if (temp == nullptr) {
                    temp = this;
                    newRoot = nullptr;
                }
                else { // One child case
                    *this = *temp; // Copy the contents of the non-empty child
                }

                delete temp;
            }
            else {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                // ... [rest of the logic remains the same]
            }
        }

        // If the tree had only one node then return
        if (this == nullptr) {
            return nullptr;
        }
        // Update height of the current node
        height = 1 + max(getHeight(left), getHeight(right));

        // Get the balance factor of this node
        int balance = getHeight(left) - getHeight(right);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && getHeight(left->left) >= getHeight(left->right)) {
            rotateRight();
        }

        // Left Right Case
        if (balance > 1 && getHeight(left->left) < getHeight(left->right)) {
            left->rotateLeft();
            rotateRight();
        }

        // Right Right Case
        if (balance < -1 && getHeight(right->right) >= getHeight(right->left)) {
            rotateLeft();
        }

        // Right Left Case
        if (balance < -1 && getHeight(right->right) < getHeight(right->left)) {
            right->rotateRight();
            rotateLeft();
        }

        return newRoot; // Return the new root of the subtree
    }



    bool isItemnotExist(vector <bool> & doesntExist, int & count) {
        for (int i = 0; i < doesntExist.size(); i++) {
            if (doesntExist[i] == false) {
                continue;
            }
            else {
                return false;
            }
        }
        return true;
    }
    vector <bool> NOQUERY;
    void printNode(WordItem* node) {
        if (node != nullptr) {
            // Process the current node
            int count = vector_document_items.size();
            vector <bool> doesntExist(count, false);
            bool itemExists = false;
            
            for (int i = 0; i < node->vector_document_items.size(); i++) {
                DocumentItem* docItem = node->vector_document_items[i];
                
                if (docItem->count > 0) {
                    cout << "in Document " << docItem->documentName << ", "
                        << node->word << " found " << docItem->count << " times." << endl;
                    itemExists = true;
                }
                else {
                    count--;
                }
                if (count == 0) {
					itemExists = false;
                }
            }
            bool isI = isItemnotExist(doesntExist, count);
            /*
            if (isI) {
				cout << "No document contains the given query" << endl;
			}*/
            printNode(node->left);
            printNode(node->right);
        }
    }
};


template <class Key, class Value>
class AvlSearchTree
{
public:
    AvlSearchTree() {
        root = nullptr;
    }
    ~AvlSearchTree() {
        clearTree(root);
    }

    void insert(Key key, Value value) {
        if (root == nullptr) {
            root = value;
        }
        else {
            root->newNode(value);
        }

    }

    void print() {
        root->printNode(this->root);
    }

    void remove(Key key) {
        if (root != nullptr) {
			root = root->removeNode(key);
		}
        
    }


private:
    WordItem* root;

    void clearTree(WordItem* node) {
        static bool first = true;
        static int keepCount = 0;
        if (!first) {
            return;
        }
        if (node != nullptr) {
            keepCount++;
            clearTree(node->left);
            clearTree(node->right);
            if (keepCount != 0) {
                delete node;  // This will call the destructor of WordItem
                keepCount--;
                if (keepCount == 0) {
                    first = false;
                }
            }

        }
    }
};


bool isalphax(string word) {
    for (int i = 0; i < word.length(); i++) {
        if (!isalpha(word[i])) {
            return false;
        }
    }
    return true;
}

string lower(string word) {
    for (int i = 0; i < word.length(); i++) {
        word[i] = tolower(word[i]);
    }
    return word;
}

bool isInVector(vector <string> words, string word) {
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == word) {
            return true;
        }
    }
    return false;
}

int main()
{
    int input;
    int count = 0;
    vector <string> file_names;
    string file_name;
    string queried_words;
    bool devam = true;
    WordItem* obj = nullptr;
    AvlSearchTree<string, WordItem*> myTree;
    ifstream file;
    string word;
    vector <WordItem*> vector_word_items;

    vector <string> words;
    
    cout << "Enter the number of input files: ";
    cin >> input;
    while (count != input) { //put the names of the files into a vector
        count++;
        cout << "Enter " << count << ". file name: ";
        cin >> file_name;

        file_names.push_back(file_name);
    }

    while (devam) {
        cout << "Enter queried words in one line: ";

        cin.ignore(); // Add this line to clear the newline character
        getline(cin, queried_words); // Get the entire line, including spaces
        istringstream iss(queried_words); // Split the line into words
        while (iss >> word) { // Read each word inside the given query
            if (word == "ENDOFINPUT") { // Stop if the word is ENDOFINPUT
                devam = false;
                break;
            }
            if (word == "REMOVE") { //if the word is REMOVE
            	iss >> word; //read the next word
            	myTree.remove(word); //remove the word from the tree
            	continue; //skip the word
            }
            word = lower(word);
            //cout << word << endl;
            if (isInVector(words, word)) { //if the word is in the vector
                continue; //skip the word
            }
            else {
                words.push_back(word);  // Add the word to the vector
            }
        }

        for (int i = 0; i < words.size(); i++) { //read the query words
            obj = new WordItem; //create a new word item
            obj->word = words[i]; //set the word to the word in the vector

            for (int j = 0; j < file_names.size(); j++) { //traverse through the vector of file names.
                file.open(file_names[j]); //open the files
                if (!file) { //if the file cannot be opened
                    cout << "Unable to open file" << endl;
                    //exit(1); // terminate with error
                }
                obj->documentItemPtr = obj->newDocument(file_names[j], 0); //create a new documentItem object
                while (file >> word) { //read the words inside the file
                    if (lower(word) == words[i]) { //if the word is equal to the word in the vector
                        obj->documentItemPtr->count++; //increase the count
                    }
                }
                file.clear();
                file.seekg(0, ios::beg);
                file.close();
            }
            myTree.insert(words[i], obj); //insert the word into the tree
        }


        myTree.print();
        myTree.~AvlSearchTree();
    }

    return 0;
}