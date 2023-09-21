#pragma once
class User;

#include "CourseAssignment.h"
#include "User.h"
#include<vector>
#include<iostream>
#include<memory>
#include <string_view>
#include <sstream>
#include <ranges>
#include <map>

//The Course doesn't need to know about his students. 
// Cause the students and doctors knows, in whick course they are. 
using UserPtr=std::shared_ptr < User >  ;
using AssignmentPtr = std::unique_ptr<Assignment>;
using std::string_view;


class Course
{

	
public:
	Course(std::string_view code,string_view courseName, UsernameAndName const& docUsernameAndName);
	Course(json const& jsonCourse);
	Course() = default;

	//getters
	std::vector <std::string> get_assignments_contents() const;

	size_t get_courseAssignments_number() const;

	std::vector<Assignment> const& get_assignments(const int courseAssignmentPos) const;

	std::vector<CourseAssignment> const& get_course_assignments()const;

	std::string const get_code() const;

	std::vector<Assignment> get_user_assignments(std::string_view studentUsername) const; 

	json get_json() const; 

	int get_total_points_of_courseAssignments() const;

	double get_scored_points_by_student(std::string_view studentUsername) const;

	size_t get_number_of_student_submitted_assignments(std::string_view studentUsername) const;

	std::string get_grade_report_string(std::string_view studentUsername) const; 

	//operators
	bool operator==(const Course& another) const; 

	//strings
	std::string overview_string() const;
	std::string all_info_student_string(std::string_view studentName) const;
	std::string doc_and_assignment_string(std::string_view studentUsername) const;
	

	//adding, removing and modification
	void make_enum_based_action_on_assignment(
		const Assignment& assignment,
		std::string_view actionContent,
		AssignmentAction const& actionType);

	void add_courseAssignment(std::string_view content, const int totalPoints);

	void add_new_student_ussername_and_name(UsernameAndName const& usernameAndName);
	
	void remove_student(std::string const& studentUsername);
	

private:
	std::string code{};
	std::string doctorUsername {};
	std::string name{};
	std::string doc_name{};
	std::vector<UsernameAndName> usernameAndNames{};
	std::vector<CourseAssignment> courseAssignments{};

};

