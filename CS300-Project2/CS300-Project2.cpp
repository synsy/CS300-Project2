// CS300-Project2.cpp 
// Christopher O'Dell
// CS300 - Southern New Hampshire University
// Project 2
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

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

	vector<Node*> nodes;
	unsigned int tableSize = DEFAULT_SIZE;
	unsigned int hash(string key);

public:
	HashTable();
	HashTable(unsigned int size);
	virtual ~HashTable();
	void Insert(Course course);
	void PrintAll();
	void PrintCourse(string courseNumber);
};

/**
 * Default constructor
 */
HashTable::HashTable() {
	// Initialize the structures used to hold courses
	// Initalize node structure by resizing tableSize
	nodes.resize(tableSize, nullptr);
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
	nodes.resize(tableSize, nullptr);
}

/**
 * Destructor
 */
HashTable::~HashTable() {
	// Iterate through each index in the hash table
	for (unsigned int i = 0; i < tableSize; ++i) {
		Node* node = nodes[i];

		// Traverse the linked list and delete each node
		while (node) {
			Node* temp = node;
			node = node->next;
			delete temp;
		}
	}
	// Clear the vector to remove all entries
	nodes.clear();
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
unsigned int HashTable::hash(string key) {
	// Logic to calculate a hash value
	unsigned int hashValue = 0;
	for (char ch : key) {
		hashValue = (hashValue * 31) + ch;
	}
	return (tableSize > 0) ? (hashValue % tableSize) : 0; // Prevent divide by zero
}

/**
 * Insert a course into the hash table
 */
void HashTable::Insert(Course course) {
	unsigned int key = hash(course.courseNumber);
	Node* newNode = new Node(course, key);

	if (nodes[key] == nullptr) {
		nodes[key] = newNode;
		return;  // Directly return after inserting to avoid further checks
	}

	Node* temp = nodes[key];

	// Check for duplicate before adding
	while (temp->next) {  // Iterate until reaching the last node
		if (temp->course.courseNumber == course.courseNumber) {
			delete newNode;  // Avoid memory leak
			return;  // Duplicate course, do not insert
		}
		temp = temp->next;
	}

	// Insert new node at the end of the linked list
	if (temp->course.courseNumber == course.courseNumber) {
		delete newNode;  // Prevent duplicate at the last node check
		return;
	}
	temp->next = newNode;
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
	// Traverse the hash table and print each course
	for (auto node : nodes) {
		while (node) {
			cout << node->course.courseNumber << ", " << node->course.courseName << endl;
			node = node->next;
		}
	}
}

/**
* Print a specific course
*/
void HashTable::PrintCourse(string courseNumber) {
	// Calculate the hash value of the course number
	unsigned int key = hash(courseNumber);
	Node* node = nodes[key];
	// Traverse the linked list at the hash index
	while (node) {
		if (node->course.courseNumber == courseNumber) {
			cout << node->course.courseNumber << ", " << node->course.courseName << endl;
			// Print prerequisites if they exist
			if (!node->course.coursePrerequisites.empty()) {
				cout << "Prerequisites: ";
				for (const string& prereq : node->course.coursePrerequisites) {
					cout << prereq << " ";
				}
				cout << endl;
			}
			else {
				cout << "No prerequisites" << endl;
			}
			return;
		}
		node = node->next;
	}
	cout << "Course not found" << endl;
}

void LoadCoursesFromFile(string fileName, HashTable& table) {
	// Open the file
	ifstream file(fileName);
	if (!file) {
		cerr << "Error opening file: " << fileName << endl;
		perror("Error Details");
		return;
	}
	if (!file.is_open()) {
		cout << "Error opening file." << endl;
		return;
	}

	// Read the file line by line
	string line; 
	while (getline(file, line)) {
		stringstream ss(line);
		string courseNumber, courseName, prereq;
		vector<string> prerequisites;

		getline(ss, courseNumber, ',');
		getline(ss, courseName, ',');

		// Split the prerequisites into a vector
		while (getline(ss, prereq, ',')) {
			prerequisites.push_back(prereq);
		}
		// Create a new course and insert it into the hash table
		Course course = { courseNumber, courseName, prerequisites };
		table.Insert(course);
	}

	file.close();
	cout << "Courses loaded successfully." << endl;
}

int main()
{
	HashTable table;
	string courseNumber;

	cout << "Welcome to the Course Planner!" << endl;

    int choice = 0;
    while (choice != 9)
    {
        cout << "1. Load Data Structure." << endl;
		cout << "2. Print Course List." << endl;
		cout << "3. Print Course." << endl;
		cout << "9. Exit" << endl;
		cout << "Enter your choice: ";

		// Input validation loop
		while (!(cin >> choice)) {
			cout << "Invalid input. Please enter a number: ";
			cin.clear();  // Clear error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
		}

		switch (choice)
		{
		case 1:
			LoadCoursesFromFile("CourseInfo.csv", table);
			break;
		case 2:
			table.PrintAll();
			break;
		case 3:
			cout << "What course do you want to know about? ";
			cin >> courseNumber;
			table.PrintCourse(courseNumber);
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
