#include "FileOperations.h"
#include "Student.h"
#include "Admin.h"
#include "Course.h"

unordered_map<string, Course> courses;
unordered_map<string, Student> students;
unordered_map<string, Admin> admins;

// File operations for students
void load_students_from_file(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Failed to open " << filename << endl;
        return;
    }

    json data;
    in >> data;
    in.close();

    if (!data.contains("students"))
        return;

    for (const auto& item : data["students"]) {
        Student s;
        s.setId(item["id"]);
        s.setName(item["name"]);
        s.setPassword(item["password"]);

        // Handle completed courses
        unordered_set<string> completed = item["completed_courses"].get<unordered_set<string>>();
        for (const auto& course : completed) {
            s.addCompletedCourse(course);
        }

        // Handle registered courses
        unordered_set<string> registered = item["registered_courses"].get<unordered_set<string>>();
        for (const auto& course : registered) {
            s.addRegisteredCourse(course);
        }

        // Handle grades
        unordered_map<string, int> grades = item["grades"].get<unordered_map<string, int>>();
        for (const auto& grade : grades) {
            s.setGrade(grade.first, grade.second);
        }

        students[s.getId()] = s;
    }
}

void save_students_to_file(const string& filename) {
    json data;

    // Load existing data (so we don't overwrite other sections)
    ifstream in(filename);
    if (in.is_open()) {
        in >> data;
        in.close();
    }

    data["students"] = json::array();

    for (const auto& student_pair : students) {
        const Student& student = student_pair.second;
        json student_json = {
            {"id", student.getId()},
            {"name", student.getName()},
            {"password", student.getPassword()},
            {"completed_courses", student.getCompletedCourses()},
            {"registered_courses", student.getRegisteredCourses()},
            {"grades", student.getGrades()}
        };
        data["students"].push_back(student_json);
    }

    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Failed to write to " << filename << endl;
        return;
    }

    out << data.dump(4); // pretty print
    out.close();
}

// File operations for admins
void load_admins_from_file(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Failed to open " << filename << endl;
        return;
    }

    json data;
    in >> data;
    in.close();

    if (!data.contains("admins"))
        return;

    for (const auto& item : data["admins"]) {
        Admin a;
        a.setUsername(item["username"]);
        a.setPassword(item["password"]);
        admins[a.getUsername()] = a;
    }
}

void save_admins_to_file(const string& filename) {
    json data;

    // Preserve existing data
    ifstream in(filename);
    if (in.is_open()) {
        in >> data;
        in.close();
    }

    data["admins"] = json::array();

    for (const auto& admin_pair : admins) {
        const Admin& admin = admin_pair.second;
        json admin_json = {
            {"username", admin.getUsername()},
            {"password", admin.getPassword()}
        };
        data["admins"].push_back(admin_json);
    }

    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Failed to write to " << filename << endl;
        return;
    }

    out << data.dump(4);
    out.close();
}

// File operations for courses
void loadCoursesFromFile(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Failed to open " << filename << endl;
        return;
    }

    json data;
    in >> data;
    in.close();

    if (!data.contains("courses"))
        return;

    for (const auto& course_json : data["courses"]) {
        Course c;
        c.setCode(course_json["code"]);
        c.setName(course_json["name"]);
        c.setInstractorName(course_json["instractor_name"]);
        c.setSyllabus(course_json["syllabus"]);
        c.setSemester(course_json["semester"]);
        c.setCreditHours(course_json["credit_hours"]);

        for (const auto& prereq : course_json["prerequisites"]) {
            c.addPrerequisite(prereq);
        }

        courses[c.getCode()] = c;
    }
}

void saveCourseToFile(const string& filename) {
    json data;

    // Preserve existing data
    ifstream in(filename);
    if (in.is_open()) {
        in >> data;
        in.close();
    }

    data["courses"] = json::array();

    for (const auto& course_pair : courses) {
        const Course& course = course_pair.second;
        json course_json = {
            {"code", course.getCode()},
            {"name", course.getName()},
            {"instractor_name", course.getInstractorName()},
            {"syllabus", course.getSyllabus()},
            {"semester", course.getSemester()},
            {"credit_hours", course.getCreditHours()},
            {"prerequisites", course.getPrerequisites()}
        };
        data["courses"].push_back(course_json);
    }

    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Failed to write to " << filename << endl;
        return;
    }

    out << data.dump(4);
    out.close();
}