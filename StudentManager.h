#pragma once
#include "Student.h"
#include "CourseManager.h"
#include <map>
using StudentPtr = std::unique_ptr<Student>;

class StudentManager
{
private:
	Student current_student{};
	std::map<std::string, StudentPtr> username_to_student{};
	std::unique_ptr<CourseManager> course_manager{};
};

