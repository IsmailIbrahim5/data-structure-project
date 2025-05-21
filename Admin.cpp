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