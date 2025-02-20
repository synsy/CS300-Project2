// CS300-Project2.cpp 
// Christopher O'Dell
// CS300 - Southern New Hampshire University
// Project 2
//

#include <iostream>
#include <vector>

using namespace std;

const unsigned int DEFAULT_SIZE = 50;

// Course Structure
struct Course
{
	string courseNumber;
	string courseName;
	vector<string> coursePrerequisites;
};

class HashTable {

private:
	struct Node {
		Course course;
		unsigned int key;
		Node* next;

		Node() {
			key = UINT_MAX;
			next = nullptr;
		}

		Node(Course aCourse) : Node() {
			course = aCourse;
		}

		Node(Course aCourse, unsigned int aKey) : Node(aCourse) {
			key = aKey;
		}
	};

	vector<Node> nodes;
	unsigned int tableSize = DEFAULT_SIZE;
	unsigned int hash(int key);

public:
	HashTable();
	HashTable(unsigned int size);
	virtual ~HashTable();
	void PrintAll();
	void PrintCourse(string courseNumber);
};

/**
 * Default constructor
 */
HashTable::HashTable() {
	// Initialize the structures used to hold courses
	// Initalize node structure by resizing tableSize
	nodes.resize(tableSize);
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
	// invoke local tableSize to size with this->
	this->tableSize = size;
	// resize nodes size
	nodes.resize(tableSize);
}

/**
 * Destructor
 */
HashTable::~HashTable() {
	// Logic to free storage when class is destroyed
	nodes.erase(nodes.begin());
	// erase nodes beginning
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
	// Logic to calculate a hash value
	// return key tableSize
	return key % tableSize;
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
	//FIXME: Implement this function
}

/**
* Print a specific course
*/
void HashTable::PrintCourse(string courseNumber) {
	//FIXME: Implement this function
}

int main()
{
	cout << "Welcome to the Course Planner!" << endl;

    int choice = 0;
    while (choice != 9)
    {
        cout << "1. Load Data Structure." << endl;
		cout << "2. Print Course List." << endl;
		cout << "3. Print Course." << endl;
		cout << "9. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "Load Course Data" << endl;
			break;
		case 2:
			cout << "Print Course List" << endl;
			break;
		case 3:
			cout << "Print Course" << endl;
			break;
		case 9:
			cout << "Thank you for using the course planner!" << endl;
			break;
		default:
			cout << choice << " is not a valid option." << endl;
			break;
		}
    }
}
