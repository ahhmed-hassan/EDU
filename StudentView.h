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
	void SubListCourses(std::vector<Course> const& courses);
	void Unregister(int course_id, User& student_id);
	void CourseChoices(Course*);
	void GradesReport();
	
	
};

