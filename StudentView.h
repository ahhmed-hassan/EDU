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
	void list_courses();
	void view_courses(); 
	void register_in_course();
	void log_out();
	//At this point I already know the courses belongs to the same user
	void sublist_courses();
	void unregister(Course const& course);
	void course_choices(Course const& course);
	void assignment_subList(const Course& course, const Assignment& assignment);
	void show_assignments_in_course(Course const& course);
	void grades_report();
	
	
};

