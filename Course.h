#pragma once
class User;

#include "Assignment.h"
#include "User.h"
#include<vector>
#include<iostream>
#include<memory>
#include <string_view>
#include <sstream>
#include <ranges>

//The Course doesn't need to know about his students. 
// Cause the students and doctors knows, in whick course they are. 
using UserPtr=std::shared_ptr < User >  ;
using AssignmentPtr = std::unique_ptr<Assignment>;
using std::string_view;

enum class AssignmentAction
{
	addSolution,
	addFeedback,
	addDegree
};
class Course
{
private:
	std::string code{};
	std::string doctorUsername {};
	std::string name{};
	string_view doc_name{};
	//std::vector<int>students_ids{};
	std::vector<Assignment>assignments{};
public:
	Course(std::string_view code, std::string_view docUsername, string_view docName, string_view name);
	Course() = default;
	std::string StudentDetailedString() const;
	std::string OverviewString() const;
	std::vector<Assignment> const& get_assignments()const;
	//int GetId()const;
	std::string const get_code() const;
	void addAssigment(Assignment&& assign);

	void add_empty_assignment_for_student(std::string_view studentName);



	void make_enum_based_action_on_assignment(const Assignment& assignment, std::string_view actionContent, AssignmentAction const& actionType);

	void remove_assignment(const Assignment& assignemnt);

	//void RemoveStudent(int student_id);
	//void SetSolution();

};

