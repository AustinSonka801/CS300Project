    #include <iostream>
    #include <fstream>
    #include "CSVparser.hpp"
    using namespace std;
    
    struct Course {
        string courseNum;
        string courseName;
        vector<string> preReqs;
        Course() {}
    };
    struct Node {
        Course course;
        Node* left;
        Node* right;
        Node() {
            left = nullptr;
            right = nullptr;
        }
        Node(Course aCourse) : Node() {
            this->course = aCourse;
} };
    
    class CourseBST {
    private:
        Node* root;
        void addNode(Node* node, Course course);
        void printSampleSchedule(Node* node);
        void printCourseInformation(Node* node, string courseNum);
    public:
        CourseBST();
        virtual ~CourseBST();
        void DeleteRecursive(Node* node);
        void Insert(Course course);
        int NumPrerequisiteCourses(Course course);
        void PrintSampleSchedule();
        void PrintCourseInformation(string courseNum);
};
    
    CourseBST::CourseBST() {
        root = nullptr;
    }
    /*
     Deconstruct the Binary Search
     */
    CourseBST::~CourseBST() {
        DeleteRecursive(root);
}
    
    void CourseBST::DeleteRecursive(Node* node) {
        if (node) {
            DeleteRecursive(node->left);
            DeleteRecursive(node->right);
            delete node;
} }
    
    void CourseBST::Insert(Course course) {
        //root not initialized
        if (root == nullptr)
            //initialize current info
            root = new Node(course);

}
} }
int CourseBST::NumPrerequisiteCourses(Course course) {
    int count = 0;
    for (unsigned int i = 0; i < course.preReqs.size(); i++) {
        if (course.preReqs.at(i).length() > 0)
count++;
}
    return count;
}
void CourseBST::PrintSampleSchedule() {
    this->printSampleSchedule(root);
}
void CourseBST::PrintCourseInformation(string courseNum) {
    this->printCourseInformation(root, courseNum);
}
void CourseBST::addNode(Node* node, Course course) {
    // less than
    if (node->course.courseNum.compare(course.courseNum) > 0) {
        if (node->left == nullptr)
            node->left = new Node(course);
        else
            this->addNode(node->left, course);
    }
    // Current courseNum is equal or greater
    else {
        if (node->right == nullptr)
            node->right = new Node(course);
        else
    Recursively prints the loaded courses IN ORDER
     */
    void CourseBST::printSampleSchedule(Node* node) {
        if (node != nullptr) {
            printSampleSchedule(node->left);
            cout << node->course.courseNum << ", " << node->course.courseName << endl;
            printSampleSchedule(node->right);
}
return; }
    void CourseBST::printCourseInformation(Node* curr, string courseNum) {
        // Traverse BST
        while (curr != nullptr) {
            if (curr->course.courseNum.compare(courseNum) == 0) {
                // Display course
                cout << endl << curr->course.courseNum << ", " << curr-
    >course.courseName << endl;
                unsigned int size = NumPrerequisiteCourses(curr->course);
                cout << "Prerequisite(s): ";
                // display each prereq
                unsigned int i = 0;
                for (i = 0; i < size; i++) {
                    cout << curr->course.preReqs.at(i);
                    if (i != size - 1)
cout << ", ";
                }
                // If no prereq
                if (i == 0)
                    cout << "No prerequisites required.";
                cout << endl;
return; }
            // smaller so traverse left
            else if (courseNum.compare(curr->course.courseNum) < 0)
                curr = curr->left;
            // larger so traverse right
            else
                curr = curr->right;
        }
        //inform
    user
        cout << "Course " << courseNum << " not found." << endl;
}
    
//Load Courses
bool loadCourses(string csvPath, CourseBST* coursesBST) {
    // Open course file
    try {
        ifstream courseFile(csvPath);
        if (courseFile.is_open()) {
            while (!courseFile.eof()) {
from str less
vector<string> courseInfo;
string courseData;
getline(courseFile, courseData);
while (courseData.length() > 0) {
    // Get substring
    unsigned int comma = courseData.find(',');
    if (comma < 100) {  // Any data field is allowed 99
        courseInfo.push_back(courseData.substr(0, comma));
        courseData.erase(0, comma + 1);
    }
    // Add last course
    else {
courseData.length()));
courseInfo.push_back(courseData.substr(0,
                            courseData = "";
                        }
}
                    // Load
                    Course course;
                    course.courseNum = courseInfo[0];
                    course.courseName = courseInfo[1];
                    for (unsigned int i = 2; i < courseInfo.size(); i++) {
                        course.preReqs.push_back(courseInfo[i]);
}
                    coursesBST->Insert(course);
                }
                courseFile.close();
                return true;
            }
        }
        catch (csv::Error& e) {
            cerr << e.what() << endl;
        }
        return false;
    }

int main(int argc, char* argv[]) {
    // Process argument
    string csvPath, courseId;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    case 3:
        csvPath = argv[1];
        courseId = argv[2];
        break;
    default:
        csvPath = "";
break; }
    // welcome 
    CourseBST* coursesBST = nullptr;
    cout << "\nWelcome to the course planner!\n" << endl;
    // Make a string
invalid data
    string choice = "0";
    int userChoice = choice[0] - '0';
    //if not 9 or exit
    while (userChoice != 9) {
cout << "
cout << "
cout << "
cout << "
cout << "\nWhat would you like to do? ";
cin >> choice;
1. Load Data Structure" << endl;
2. Print Course List" << endl;
3. Print Course" << endl;
9. Exit" << endl;
            // Check if user choice is a double digit
            if (choice.length() == 1)
                userChoice = choice[0] - '0';
            else
                userChoice = 0;
            bool success = 1;
            // Handle users choice from menu
            switch (userChoice) {
                // Instant BST
case 1:
                if (coursesBST == nullptr)
                    coursesBST = new CourseBST();
                if (csvPath.length() == 0) {

        cout << "Enter the file name that contains the course data: ";
        cin >> csvPath;
    }
    success = loadCourses(csvPath, coursesBST);
    if (success)
        cout << "Courses have been loaded.\n" << endl;
    else
        cout << "File not found.\n" << endl;
    csvPath = "";
break;
    // Validate that BST exists
case 2:
    if (coursesBST != nullptr && success) {
        cout << "Here is a sample schedule:\n" << endl;
        coursesBST->PrintSampleSchedule();
        cout << endl;
} else
        cout << "Load courses first - option 1\n" << endl;
    break;
    // Validate that BST exists
case 3:
    if (coursesBST != nullptr && success) {
        if (courseId.length() == 0) {
                    cout << "What course do you want to know about? ";
                    cin >> courseId;
                    for (auto& userChoice : courseId) userChoice =
toupper(userChoice);
                }
                    coursesBST->PrintCourseInformation(courseId);
                    cout << endl;
                }
                else
                    cout << "Load courses first - option 1\n" << endl;
                courseId = "";
                break;
                // User entered invalid data or exited the program
            default:
                if (userChoice != 9)
                    cout << choice << " is not a valid option\n" << endl;
break; }
        }
        cout << "\nThank you for using the course planner!" << endl;
return 0; }

