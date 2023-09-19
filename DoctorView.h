#pragma once
//To Do: Replace int choice with enum class
#include "CourseManager.h"
#include "UserManager.h"
#include <assert.h>
using CourseManagerPtr = std::shared_ptr<CourseManager>;
using UserManagerPtr = std::shared_ptr<UserManager>;
class DoctorView
{
private:
	CourseManagerPtr courses{};
	UserManagerPtr users{};
	
public:
	DoctorView(const DoctorView&)=default ; 
	//void operator=(const DoctorView&)=default;
	DoctorView(DoctorView&&) = default;
	DoctorView( CourseManagerPtr cManger,  UserManagerPtr uManger);
	void Display(); 
	void list_courses();
	void add_courses();
	void view_courses();
	void show_assignments(Course const& course);
	void add_assignment(Course course);
	//This function need to always ask the course abouth the information first, 
	//cause it can happen that assignments for this course were updated before we don't know
	void course_assignment_subList_from_course(Course const& course, CourseAssignment const& courseAssingment);
	void assignment_sublist(Course const & course, Assignment const& assignment);
	void log_out();
};

