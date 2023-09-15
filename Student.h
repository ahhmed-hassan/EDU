#pragma once
#include<iostream>
#include"Course.h"
class Course;
class Student: public User
{
private:
	/*std::string user_name{};
	std::string full_name{};
	std::string password{};
	std::vector<Course*>courses{};*/
public:
	void show_grades();
	void register_in_course();
	void unregister(std::string_view courseCode);
};

