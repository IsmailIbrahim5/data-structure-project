#include "Course.h"

Course::Course() {
   this->code = "";
   this->name = "";
   this->instractor_name = "";
   this->syllabus = "";
   this->credit_hours = 0.0;
   this->semester = 1;
}

// Getters implementations
string Course::getCode() const { return code; }

string Course::getName() const { return name; }

string Course::getInstractorName() const { return instractor_name; }

string Course::getSyllabus() const { return syllabus; }

string Course::getSemester() const { return semester; }

float Course::getCreditHours() const { return credit_hours; }

const unordered_set<string> &Course::getPrerequisites() const {
   return prerequisites;
}

// Setters implementations
void Course::setCode(const string &code) { this->code = code; }

void Course::setName(const string &name) { this->name = name; }

void Course::setInstractorName(const string &name) {
   this->instractor_name = name;
}

void Course::setSyllabus(const string &syllabus) { this->syllabus = syllabus; }

void Course::setSemester(string semester) { this->semester = semester; }

void Course::setCreditHours(float hours) { this->credit_hours = hours; }

void Course::addPrerequisite(const string &code) { prerequisites.insert(code); }

bool Course::removePrerequisite(const string &code) {
   auto it = prerequisites.find(code);
   if (it != prerequisites.end()) {
      prerequisites.erase(it);
      return true;
   }
   return false;
}
