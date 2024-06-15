#include <iostream>
#include <string>
#include <limits>
using namespace std;

#include "BSTree.h"

//Shows the user the options they have to create and modify their own BSTree. The user types in a number to access the corresponding function.
int PrintMenu();

//Prints the BSTree in three different orders.
//Preorder: Middle, Left, Right
//Inorder: Left, Middle, Right
//Postorder: Right, Left, Middle
void PrintOrders(BSTree tree); 

int main(){
    BSTree tree1; 
    string userString;
    int choice = PrintMenu();
    while (choice != 8){
        if (choice == 1){
            cout << "Enter string to insert: ";
            getline(cin, userString);
            tree1.insert(userString); 
            cout << endl;
        }
        else if (choice == 2){
            cout << "Enter string to remove: ";
            getline(cin, userString);
            tree1.remove(userString);
            cout << endl;
        }
        else if (choice == 3) {
            PrintOrders(tree1); 
        }
        else if (choice == 4) {
            cout << "Enter string to search for: ";
            getline(cin, userString);
            cout << endl;
            if (tree1.search(userString) == 0){
                cout << "Not Found" << endl;
            }
            else {
                cout << "Found" << endl; 
            }
        }
        else if (choice == 5) {
            cout << "Smallest: ";
            cout << tree1.smallest() << endl;
        }
        else if (choice == 6) {
            cout << "Largest: ";
            cout << tree1.largest() << endl; 
        }
        else if (choice == 7) {
            cout << "Enter string: " << endl;
            getline(cin, userString);
            cout << "Height of subtree rooted at " << userString << ": " << tree1.height(userString) << endl;
        }
        //cin.clear(); 
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choice = PrintMenu(); 
    }
    return 0; 
}

int PrintMenu(){
    int userChoice = 0;
    cout << endl;
    cout << "Enter menu choice: " << endl;
    cout << "1. Insert" << endl; 
    cout << "2. Remove" << endl;
    cout << "3. Print" << endl;
    cout << "4. Search" << endl; 
    cout << "5. Smallest" << endl;
    cout << "6. Largest" << endl;
    cout << "7. Height" << endl;
    cout << "8. Quit" << endl;
    cin >> userChoice; 
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return userChoice; 
}

void PrintOrders(BSTree tree){
    cout << "Preorder = ";
    tree.preOrder();
    cout << "Inorder = ";
    tree.inOrder();
    cout << "Postorder = ";
    tree.postOrder(); 
}