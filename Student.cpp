#include "Student.h"
#include "CourseManager.h"
void Student::unregister(std::string_view courseCode)
{
	auto it = std::ranges::find(get_courses(), courseCode);
	if (it == get_courses().end())
		throw std::invalid_argument("There's no such a course");
	
}