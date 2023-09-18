#pragma once
#include "CourseManager.h"
#include "UserManager.h"
using CourseManagerPtr = std::shared_ptr<CourseManager>;
using UserManagerPtr = std::shared_ptr<UserManager>;
class StudentView
{
private:
	CourseManagerPtr courses;
	UserManagerPtr users;
public:
	//StudentView(const StudentView&) = delete;
	//void operator=(const StudentView&) = delete;
	StudentView(CourseManagerPtr cManger, UserManagerPtr uManger);
	StudentView(StudentView&&) noexcept;
	void Display();
	void ListCourses();
	void ViewCourses(); 
	void RegisterInCourse();
	//At this point I already know the courses belongs to the same user
	void SubListCourses();
	void Unregister(Course const& course);
	void CourseChoices(Course const& course);
	void assignment_subList(const Course& course, const Assignment& assignment);
	void show_assignments_in_course(Course const& course);
	void GradesReport();
	
	
};

