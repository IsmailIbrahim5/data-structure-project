#include "Student.h"
#include "Course.h"

Student::Student() {
   this->semester = 1;
   this->termCreditHours = 18;
}

Student::Student(string id, string name, string password) {
   this->semester = 1;
   this->termCreditHours = 18;
   this->id = id;
   this->name = name;
   this->password = password;
}

// Getters implementation
int Student::getSemester() const { return semester; }

int Student::getTermCreditHours() const { return termCreditHours; }

string Student::getId() const { return id; }

string Student::getName() const { return name; }

string Student::getPassword() const { return password; }

const unordered_set<string> &Student::getCompletedCourses() const {
   return completedCourses;
}

const unordered_set<string> &Student::getRegisteredCourses() const {
   return registeredCourses;
}

const unordered_map<string, int> &Student::getGrades() const { return grades; }

// Setters implementation
void Student::setSemester(int semester) { this->semester = semester; }

void Student::setTermCreditHours(int hours) { this->termCreditHours = hours; }

void Student::setId(const string &id) { this->id = id; }

void Student::setName(const string &name) { this->name = name; }

void Student::setPassword(const string &password) { this->password = password; }

// Collection modification methods
void Student::addCompletedCourse(const string &code) {
   completedCourses.insert(code);
}

bool Student::removeCompletedCourse(const string &code) {
   return completedCourses.erase(code) > 0;
}

void Student::addRegisteredCourse(const string &code) {
   registeredCourses.insert(code);
}

bool Student::removeRegisteredCourse(const string &code) {
   return registeredCourses.erase(code) > 0;
}

void Student::setGrade(const string &course, int grade) {
   grades[course] = grade;
}

bool Student::removeGrade(const string &course) {
   return grades.erase(course) > 0;
}

void Student::studentMenu() {
   cout << "Hello, " << this->getName() << "\n";
   cout << "Your Courses:\n";
   for (const auto &course : getRegisteredCourses()) {
      cout << course << "  ";
   }
   cout << "\n";

   int choice = -1;
   cout
       << "1. Search for Courses\n2. Register Course\n3. View Grades\n4. Check "
          "Prerequisites\n5. Generate Report\n0. Logout\n";
   cout << "Enter your choice: ";
   cin >> choice;
   string code;

   switch (choice) {
   case 1:
      viewCourses();
      break;
   case 2:
      cin >> code;
      RegisterForCourse(code);
      break;
   case 3:
      viewGrades();
      break;
   case 4:
      showPrerequisites();
      break;
   case 5:
      generateReports();
      break;
   case 0:
      mainMenu();
      break;
   default:
      break;
   }
}

void Student::signUpStudent() {
   string id, name, password;
   cout << "enter Student ID: ";
   cin >> id;
   if (students.find(id) != students.end()) {
      cout << "Student already exists.\n";
      return;
   }
   cout << "enter Student Name: ";
   cin.ignore();
   getline(cin, name);
   cout << "enter Student Password: ";
   cin >> password;
   Student student(id, name, password);
   students[id] = student;
   cout << "SignUp successfully\n";
   student.studentMenu();
}

void Student::loginStudent() {
   string id, password;
   int input = 0;
   while (input < 3) {
      cout << "enter Student ID: ";
      cin >> id;
      cout << "enter Student password: ";
      password = "";
      char ch;
      while ((ch = _getch()) != '\n') {
         if (ch == 127 || ch == '\b') {
            if (!password.empty()) {
               password.pop_back();
               cout << "\b \b";
            }
         } else {
            password += ch;
            cout << '*';
         }
         cout.flush();
      }
      cout << endl;
      if (students.find(id) == students.end()) {
         cout << "the Student doesn't exist.\n";
         return;
      } else {
         auto it = students.find(id);
         if (it->second.getPassword() != password) {
            cout << "wrong Password \n";
            input++;
            if (input == 3) {
               cout << "your tried three wrong Passwords\n";
               return;
            }
            continue;
         } else {
            cout << "Login Student successfully\n";
            it->second.studentMenu();
            return;
         }
      }
   }
}

void Student::goBack() {
   cout << "Enter anything to back\n";
   char choice;
   cin >> choice;
   if (choice)
      this->studentMenu();
}

void Student::viewCourses() {
   cout << "Availabe Courses Are:" << endl;
   for (auto it = courses.begin(); it != courses.end(); it++) {
      cout << "Code: " << it->second.getCode() << "\t"
           << "name: " << it->second.getName() << endl;
      cout << "Instractor_Name: " << it->second.getInstractorName() << "\t"
           << "Credit Hours: " << it->second.getCreditHours() << endl;
   }
   goBack();
}

void Student::searchCourse(string code) {
   if (courses.find(code) != courses.end()) {
      cout << "Code: " << courses[code].getCode() << endl;
      cout << "Name: " << courses[code].getName() << endl;
      cout << "Instructor: " << courses[code].getInstractorName() << endl;
      cout << "Credit Hours: " << courses[code].getCreditHours() << endl;
   } else {
      cout << "Course not found!" << endl;
   }
}

void Student::RegisterForCourse(string code) {
   if (getRegisteredCourses().find(code) != getRegisteredCourses().end()) {
      cout << "You are already registered in this course!" << endl;
      return;
   }

   if (courses.find(code) == courses.end()) {
      cout << "Course not found!" << endl;
      return;
   }

   bool checkprerequisites = checkPrerequisites(code);
   if (checkprerequisites &&
       this->getTermCreditHours() >= courses[code].getCreditHours()) {
      this->addRegisteredCourse(code);
      this->setTermCreditHours(this->getTermCreditHours() -
                               courses[code].getCreditHours());
      cout << "Successfully registered for course: " << courses[code].getName()
           << endl;
   } else {
      cout << "You can't be registered to this course. You either have to "
              "complete "
              "prerequisites first or don't have enough credit hours remaining!"
           << endl;
   }
   goBack();
}

bool Student::checkPrerequisites(string code) {
   int completedCoursesSize = this->getCompletedCourses().size();
   int prerequisitesSize = courses[code].getPrerequisites().size();

   if (prerequisitesSize == 0)
      return true;
   else {
      if (completedCoursesSize == 0)
         return false;
      else {
         if (prerequisitesSize > completedCoursesSize)
            return false;
         else {
            const auto &prerequisites = courses[code].getPrerequisites();
            const auto &completedCourses = this->getCompletedCourses();

            for (const auto &prereq : prerequisites) {
               if (completedCourses.find(prereq) == completedCourses.end())
                  return false;
            }
            return true;
         }
      }
   }
}

void Student::viewGrades() {
   cout << "Your Grades:\n";
   for (const auto &grade_pair : getGrades()) {
      const string &courseCode = grade_pair.first;
      int grade = grade_pair.second;

      if (courses.find(courseCode) != courses.end()) {
         auto &course = courses[courseCode];
         cout << course.getName() << " -> (Grade: " << grade
              << ") (Semester: " << course.getSemester() << ")\n";
      } else {
         cout << courseCode << " -> (Grade: " << grade
              << ") (Course details not available)\n";
      }
   }
   goBack();
}

double Student::grade_to_gpa_point(int grade) {
   if (grade >= 93)
      return 4.0;
   if (grade >= 89)
      return 3.7;
   if (grade >= 84)
      return 3.3;
   if (grade >= 80)
      return 3.0;
   if (grade >= 76)
      return 2.7;
   if (grade >= 73)
      return 2.3;
   if (grade >= 70)
      return 2.0;
   if (grade >= 67)
      return 1.7;
   if (grade >= 64)
      return 1.3;
   if (grade >= 60)
      return 1.0;
   return 0.0;
}

double Student::calculate_gpa() {
   const auto &grades = this->getGrades();
   if (grades.empty())
      return 0.0;

   double total_weighted_points = 0.0;
   double total_credits = 0.0;

   for (const auto &grade_pair : grades) {
      const string &courseCode = grade_pair.first;
      int grade = grade_pair.second;

      auto it = courses.find(courseCode);
      if (it == courses.end())
         continue;

      double credit = it->second.getCreditHours();
      double gpa_point = grade_to_gpa_point(grade);
      total_weighted_points += gpa_point * credit;
      total_credits += credit;
   }

   return (total_credits == 0) ? 0.0 : (total_weighted_points / total_credits);
}

void Student::generateReports() {
   cout << "Name: " << getName() << "\n";
   cout << "ID: " << getId() << "\n";

   cout << "Courses taken: \n";
   for (const auto &courseCode : getCompletedCourses()) {
      if (getGrades().find(courseCode) != getGrades().end() &&
          courses.find(courseCode) != courses.end()) {
         cout << courseCode << ": " << getGrades().at(courseCode)
              << " (Semester: " << courses[courseCode].getSemester() << ")\n";
      }
   }
   cout << "GPA: " << calculate_gpa() << "\n";
   goBack();
}

void Student::showPrerequisites() {
   cout << "|\tCourse\t||\tPrerequisites\t|\n";
   for (const auto &course_pair : courses) {
      const Course &course = course_pair.second;
      cout << "| " << course.getName() << " ||";
      for (const auto &prereq : course.getPrerequisites())
         cout << " " << prereq;
      cout << "\n";
   }
   goBack();
}

void Student::showPrerequisitesForOneCourse(string code) {
   if (courses.find(code) != courses.end()) {
      cout << "Prerequisites for " << courses[code].getName() << ":\n";
      for (const auto &prereq : courses[code].getPrerequisites()) {
         cout << prereq << endl;
      }
   } else {
      cout << "Course not found!" << endl;
   }
}
