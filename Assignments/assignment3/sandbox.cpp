/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
#include "class.h"
#include <iostream>
void sandbox() {
  // STUDENT TODO: Construct an instance of your class!
  Date birthday(2006, 6, 17);
  Student student = Student("Zhao Xinrui", 19, birthday);

  std::string stu_name = student.get_name();
  std::cout << "Student name: " << stu_name << std::endl;

  Date stu_birthday = student.get_birthday();
  std::cout << "Student birthday: " << stu_birthday.year << "-" << stu_birthday.month << "-" << stu_birthday.day << std::endl;

  int stu_age = student.get_age();
  std::cout << "Student age: " << stu_age << std::endl;

  Course course("Data Structure", 4, 94);
  student.update_course(course);

  int stu_credits = student.get_credits();
  float stu_gpa = student.get_gpa();
  std::cout << "Student credits: " << stu_credits << std::endl;
  std::cout << "Student gpa: " << stu_gpa << std::endl;

  student.set_age(20);

}