#pragma once
#include <string>
#include <vector>

struct Date {
    int year;
    int month;
    int day;

    Date(): year(0), month(0), day(0) {}
    Date(int y, int m, int d): year(y), month(m), day(d) {}
};

struct Course {
    std::string name;
    int credits;
    float score;

    Course(): name("UNKNOWN"), credits(0), score(0.0) {}
    Course(const std::string& n, int c, float s): name(n), credits(c), score(s) {}
};

class Student {
private:
    std::string name;
    int age;
    Date birthday;
    int credits;
    float gpa;
    double total_weighted;
    std::vector<Course> taken;

    float calculate_gpa(float score) const;
    
public:
    Student();
    /*用const修饰采取引用传递的stu_name和stu_birthday*/
    Student(const std::string& stu_name, int stu_age, const Date& stu_birthday);

    /*用const修饰采取引用传递的birthday和taken*/
    std::string get_name() const;
    const Date& get_birthday() const;
    const std::vector<Course>& get_taken() const;
    int get_age() const;
    int get_credits() const;
    float get_gpa() const;

    void set_age(int new_age);
    
    /*用const修饰采用引用传递的new_course*/
    void update_course(const Course& new_course);
};