#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

// Structure to store course information
struct Course {
    string name;
    double grade;
    int creditHours;
};

// Function to convert letter grade to grade points (4.0 scale)
double letterToGradePoint(string letterGrade) {
    if (letterGrade == "A" || letterGrade == "a") return 4.0;
    if (letterGrade == "A-" || letterGrade == "a-") return 3.7;
    if (letterGrade == "B+" || letterGrade == "b+") return 3.3;
    if (letterGrade == "B" || letterGrade == "b") return 3.0;
    if (letterGrade == "B-" || letterGrade == "b-") return 2.7;
    if (letterGrade == "C+" || letterGrade == "c+") return 2.3;
    if (letterGrade == "C" || letterGrade == "c") return 2.0;
    if (letterGrade == "C-" || letterGrade == "c-") return 1.7;
    if (letterGrade == "D+" || letterGrade == "d+") return 1.3;
    if (letterGrade == "D" || letterGrade == "d") return 1.0;
    if (letterGrade == "F" || letterGrade == "f") return 0.0;
    return -1; // Invalid grade
}

int main() {
    vector<Course> currentSemester;
    int numCourses;
    double totalGradePoints = 0;
    int totalCredits = 0;
    
    cout << "========================================" << endl;
    cout << "    GPA & CGPA Calculator" << endl;
    cout << "========================================" << endl << endl;
    
    // Input for current semester
    cout << "Enter the number of courses this semester: ";
    cin >> numCourses;
    
    if (numCourses <= 0) {
        cout << "Invalid number of courses!" << endl;
        return 1;
    }
    
    cout << endl;
    
    // Input course details
    for (int i = 0; i < numCourses; i++) {
        Course course;
        string gradeInput;
        
        cout << "Course " << (i + 1) << ":" << endl;
        cout << "  Enter course name: ";
        cin.ignore();
        getline(cin, course.name);
        
        cout << "  Enter grade (numeric 0-4 or letter A/B/C/D/F): ";
        cin >> gradeInput;
        
        // Check if input is numeric or letter grade
        if (isdigit(gradeInput[0]) || gradeInput[0] == '.') {
            course.grade = stod(gradeInput);
            if (course.grade < 0 || course.grade > 4) {
                cout << "  Invalid grade! Must be between 0 and 4." << endl;
                i--;
                continue;
            }
        } else {
            course.grade = letterToGradePoint(gradeInput);
            if (course.grade < 0) {
                cout << "  Invalid letter grade!" << endl;
                i--;
                continue;
            }
        }
        
        cout << "  Enter credit hours: ";
        cin >> course.creditHours;
        
        if (course.creditHours <= 0) {
            cout << "  Invalid credit hours!" << endl;
            i--;
            continue;
        }
        
        currentSemester.push_back(course);
        totalGradePoints += course.grade * course.creditHours;
        totalCredits += course.creditHours;
        cout << endl;
    }
    
    // Calculate semester GPA
    double semesterGPA = totalGradePoints / totalCredits;
    
    // Display current semester results
    cout << "========================================" << endl;
    cout << "    Current Semester Results" << endl;
    cout << "========================================" << endl;
    cout << left << setw(25) << "Course Name" 
         << setw(10) << "Grade" 
         << setw(10) << "Credits" << endl;
    cout << "----------------------------------------" << endl;
    
    for (const auto& course : currentSemester) {
        cout << left << setw(25) << course.name 
             << setw(10) << fixed << setprecision(2) << course.grade 
             << setw(10) << course.creditHours << endl;
    }
    
    cout << "----------------------------------------" << endl;
    cout << "Total Credits: " << totalCredits << endl;
    cout << "Semester GPA: " << fixed << setprecision(2) << semesterGPA << endl << endl;
    
    // CGPA Calculation
    cout << "========================================" << endl;
    cout << "Calculate Overall CGPA" << endl;
    cout << "========================================" << endl;
    
    char calculateCGPA;
    cout << "Do you want to calculate overall CGPA? (y/n): ";
    cin >> calculateCGPA;
    
    if (calculateCGPA == 'y' || calculateCGPA == 'Y') {
        double previousGPA;
        int previousCredits;
        
        cout << "Enter your previous CGPA (0 if first semester): ";
        cin >> previousGPA;
        
        cout << "Enter total credits completed before this semester: ";
        cin >> previousCredits;
        
        if (previousCredits < 0 || previousGPA < 0 || previousGPA > 4) {
            cout << "Invalid input!" << endl;
            return 1;
        }
        
        // Calculate CGPA
        double totalPreviousGradePoints = previousGPA * previousCredits;
        double overallGradePoints = totalPreviousGradePoints + totalGradePoints;
        int overallCredits = previousCredits + totalCredits;
        double cgpa = overallGradePoints / overallCredits;
        
        cout << endl;
        cout << "========================================" << endl;
        cout << "    Final Results" << endl;
        cout << "========================================" << endl;
        cout << "Previous CGPA: " << fixed << setprecision(2) << previousGPA << endl;
        cout << "Previous Credits: " << previousCredits << endl;
        cout << "Current Semester GPA: " << semesterGPA << endl;
        cout << "Current Semester Credits: " << totalCredits << endl;
        cout << "----------------------------------------" << endl;
        cout << "Overall CGPA: " << fixed << setprecision(2) << cgpa << endl;
        cout << "Total Credits Completed: " << overallCredits << endl;
        cout << "========================================" << endl;
    }
    
    return 0;
}