#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Structure to store course information
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// Function prototypes
void loadDataStructure(map<string, Course> &courses, const string &filename);
void printCourseList(const map<string, Course> &courses);
void printCourseInfo(const map<string, Course> &courses, const string &courseNumber);

int main() {
    map<string, Course> courses;
    int choice;
    string filename;

    cout << "Welcome to the course planner." << endl;

    do {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "\nWhat would you like to do? ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the file name: ";
                cin >> filename;
                loadDataStructure(courses, filename);
                break;
            case 2:
                printCourseList(courses);
                break;
            case 3: {
                string courseNumber;
                cout << "What course do you want to know about? ";
                cin >> courseNumber;
                printCourseInfo(courses, courseNumber);
                break;
            }
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                break;
            default:
                cout << choice << " is not a valid option." << endl;
        }
    } while (choice != 9);

    return 0;
}

// Function to load data structure from a file
void loadDataStructure(map<string, Course> &courses, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, name, prerequisite;
        getline(ss, courseNumber, ',');
        getline(ss, name, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.name = name;

        while (getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        courses[courseNumber] = course;
    }

    file.close();
    cout << "Data loaded successfully!" << endl;
}

// Function to print the course list in alphanumeric order
void printCourseList(const map<string, Course> &courses) {
    cout << "\nHere is a sample schedule:" << endl;
    for (const auto &pair : courses) {
        cout << pair.second.courseNumber << ", " << pair.second.name << endl;
    }
}

// Function to print course information
void printCourseInfo(const map<string, Course> &courses, const string &courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        cout << it->second.courseNumber << ", " << it->second.name << endl;
        cout << "Prerequisites: ";
        for (const auto &prerequisite : it->second.prerequisites) {
            cout << prerequisite << " ";
        }
        cout << endl;
    } else {
        cout << "Course not found." << endl;
    }
}
