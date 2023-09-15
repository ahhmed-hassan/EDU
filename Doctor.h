#pragma once
#include"Course.h"
class Course;
class Doctor: public User
{
public: 
	Doctor(int, Course* c=nullptr);
	Doctor();
	int get_id();
	void set_course(Course*);
	void add_course();
	int get_course_id();
private:
	/*int id;
	std::string user_name{};
	std::string full_name{};
	std::string password{};
	Course* course{};*/
};

