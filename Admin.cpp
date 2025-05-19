#include "Admin.h"
#include "Course.h"
#include "Student.h"

Admin::Admin() {}

Admin::Admin(string username,string name, string password) {
   this->username = username;
   this->name = name;
   this->password = password;
}

// Getters implementation
string Admin::getUsername() const { return username; }
string Admin::getName() const { return name; }

string Admin::getPassword() const { return password; }

// Setters implementation
void Admin::setUsername(const string &username) { this->username = username; }
void Admin::setName(const string &name) { this->name = name; }

void Admin::setPassword(const string &password) { this->password = password; }

string Admin::signUpAdmin(string username, string name, string password) {

   if (admins.find(username) != admins.end()) {
      return "Admin already exists.";
   }

   Admin admin(username,name ,password);
   admins[username] = admin;
   return "";
}

string Admin::loginAdmin(string username, string password) {
      if (admins.find(username) == admins.end()) {
         return "Admin doesn't exists.";
      } else {
         auto it = admins.find(username);
         if (it->second.getPassword() != password) {
            return "wrong Password ";
         } else {
            return "";
         }
   }
}

void Admin::addCourse(string code, string name, string instractor_name,
                      string syllabus, float credit_hours) {
   Course course;
   course.setCode(code);
   course.setCreditHours(credit_hours);
   course.setName(name);
   course.setInstractorName(instractor_name);
   course.setSyllabus(syllabus);

   if (courses.find(code) != courses.end()) {
      cout << "This course is already exist!" << endl;
      return;
   }
   courses.insert(make_pair(code, course));
   cout << "Course added successfully!" << endl;
}

void Admin::addPrerequisiteToCourse(const string &courseCode,
                                    const string &prerequisiteCode) {
   if (courses.find(courseCode) == courses.end()) {
      cout << "The course is not found!" << endl;
      return;
   }
   courses[courseCode].addPrerequisite(prerequisiteCode);
}

void Admin::removePrerequisiteFromCourse(const string &courseCode,
                                         const string &prerequisiteCode) {
   if (courses.find(courseCode) == courses.end()) {
      cout << "The course is not found!" << endl;
      return;
   }

   bool success = courses[courseCode].removePrerequisite(prerequisiteCode);
   if (!success) {
      cout << "This removePrerequisite function does not work!!!" << endl;
   } else {
      cout << "Prerequisite removed successfully!" << endl;
   }
}

void Admin::uploadGradesFromCsv(string &csvFile) {
   ifstream file(csvFile);
   if (!file.is_open()) {
      cout << "Failed to open file: " << csvFile << endl;
      return;
   }

   string line;
   vector<string> headers;
   unordered_map<string, unordered_map<string, int>> csvGrades;

   // Parse headers
   getline(file, line);
   stringstream headerStream(line);
   string col;
   while (getline(headerStream, col, ',')) {
      headers.push_back(col);
   }

   // Parse CSV data
   while (getline(file, line)) {
      stringstream ss(line);
      string cell;
      string student_id;
      unordered_map<string, int> grades;

      for (size_t i = 0; i < headers.size(); ++i) {
         getline(ss, cell, ',');
         if (i == 0)
            student_id = cell;
         else if (!cell.empty())
            grades[headers[i]] = stoi(cell);
      }
      csvGrades[student_id] = grades;
   }

   // Update students map
   for (const auto &student_id_and_grades : csvGrades) {
      const string &student_id = student_id_and_grades.first;
      const auto &grades_map = student_id_and_grades.second;

      if (students.count(student_id)) {
         Student &student = students[student_id];

         for (const auto &courseGrades : grades_map) {
            const string &courseCode = courseGrades.first;
            int grade = courseGrades.second;

            student.setGrade(courseCode, grade);
            student.addCompletedCourse(courseCode);
         }
      }
   }
   cout << "Grades updated from CSV.\n";
}

void Admin::setGradeToStudent(string id, string code, int grade)
{
    if (students.find(id) == students.end())
        return;// we should add worning statement here
    else
    {
        Student& student = students[id];
        if (courses.find(code) != courses.end() && student.isRegisteredCourse(code))
            student.setGrade(code, grade);
        else
            return;// we should add worning statement here
        if(student.getCourseGrade(code) >= 60)
            student.addCompletedCourse(code);
        bool check = student.removeRegisteredCourse(code);
        if (!check)
            cout << "Remove function doesn't work!" << endl;// for test you can delete it and make it worning 
        if (student.getRegisteredCourses().size() == 0)
        {
            double gpa = student.calculate_gpa();
            if (gpa >= 3)
                student.setTermCreditHours(21);
            else if (gpa >= 2)
                student.setTermCreditHours(18);
            else
                student.setTermCreditHours(15);
        }
    }
}
void Admin::save_students_grades_to_csv(
    const std::string& filename,
    const std::unordered_map<std::string, Student>& students) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }

    // 1. Collect all course codes that appear in any student's grades
    std::unordered_set<std::string> allCourses;
    for (const auto& [id, student] : students) {
        for (const auto& [course, _] : student.getGrades()) {
            allCourses.insert(course);
        }
    }

    // 2. Write header row: id,course1,course2,...
    out << "id";
    for (const auto& course : allCourses) {
        out << "," << course;
    }
    out << "\n";

    // 3. Write each student row
    for (const auto& [id, student] : students) {
        out << id;
        for (const auto& course : allCourses) {
            int checkIfGradeIsFounded = student.getCourseGrade(course);
            if (checkIfGradeIsFounded != -1) {
                out << "," << checkIfGradeIsFounded;
            }
            else {
                out << ","; // blank for missing grade
            }
        }
        out << "\n";
    }

    out.close();
    std::cout << "Student grades exported to " << filename << "\n";
}
