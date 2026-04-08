#include "class.h"

float Student::calculate_gpa(float score) const{
	return score / 25;
}

Student::Student() {
    name = "UNKNOWN";
    age = 0;
    credits = 0;
    gpa = 0.0;
    total_weighted = 0.0;
}

Student::Student(const std::string& stu_name, int stu_age, const Date& stu_birthday) {
    name = stu_name;
    age = stu_age;
    birthday = stu_birthday;
    gpa = 0.0;
    credits = 0;
    total_weighted = 0.0;
}

std::string Student::get_name() const {
	return name;
}

int Student::get_age() const {
	return age;
}

const Date& Student::get_birthday() const {
	return birthday;
}

int Student::get_credits() const {
	return credits;
}

float Student::get_gpa() const {
	return gpa;
}

const std::vector<Course>& Student::get_taken() const {
	return taken;
}

void Student::set_age(int new_age) {
    age = new_age;
}

void Student::update_course(const Course& new_course) {
    taken.push_back(new_course);
    credits += new_course.credits;
    float course_gpa = calculate_gpa(new_course.score);
    total_weighted += course_gpa * new_course.credits;
    if (credits != 0.0) {
        gpa = total_weighted / credits;
    }
}