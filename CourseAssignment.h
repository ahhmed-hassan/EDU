#pragma once
#include <string>
#include <vector>
#include<string_view>
#include <ranges>
#include <assert.h>
#include "Assignment.h"


enum class AssignmentAction
{
	addSolution,
	addFeedback,
	addDegree
};
//new Assignment within the course
class CourseAssignment
{
public:
	CourseAssignment(std::string_view content, const int totalPoints, std::vector<UsernameAndName>const& studentNames);
	CourseAssignment(json const& jsonCourseAssignment);

	//getters
	std::string const& get_content() const;
	std::vector<Assignment> const& get_assignments() const;
	std::vector<std::string> get_doctor_overview() const; 
	Assignment get_student_assigment(std::string_view studentName) const; 
	json get_json() const;
	int get_total()const;

	//operators
	auto operator<=>(const CourseAssignment& another) const->std::strong_ordering
	{
		return content <=> another.content;
	}
	bool operator== (const CourseAssignment& another) const;
	bool operator==(std::string_view anotherCOntent)const;


	//adding,removing and modification
	void add_student_entry(UsernameAndName const& usernameAndName);
	void make_enum_based_action_on_assignment(const Assignment& assignment, std::string_view actionContent, AssignmentAction const& actionType);
	void remove_student(std::string_view studentUsername);
	
	
private:
	std::string content{};
	int totalPoints{};
	std::vector<Assignment> assignments{};
};

