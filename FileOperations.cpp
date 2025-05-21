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


void load_student_grades_from_csv(const string& csvFile) {
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
    for (const auto& student_id_and_grades : csvGrades) {
        const string& student_id = student_id_and_grades.first;
        const auto& grades_map = student_id_and_grades.second;

        if (students.count(student_id)) {
            Student& student = students[student_id];

            for (const auto& courseGrades : grades_map) {
                const string& courseCode = courseGrades.first;
                int grade = courseGrades.second;

                student.setGrade(courseCode, grade);
                student.addCompletedCourse(courseCode);
            }
        }
    }
}


void save_students_grades_to_csv(
    const std::string& filename) {
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
}
