#pragma once
#include<iostream>
#include <string_view>
#include <sstream>
#include <optional>
#include "nlohman/json.hpp"
using json = nlohmann::json;
//class AssignmentId
//{
//private: 
//	std::string studentUsername{}; 
//	int courseId{};
//public: 
//	AssignmentId() = default; 
//	AssignmentId(std::string_view studentUsername, int courseId);
//	auto const operator<=>(const AssignmentId&) const = default;
//	int get_courseid() const;
//	std::string get_student_username() const; 
//};

struct UsernameAndName
{
	std::string username{};
	std::string name{};
	bool operator==(UsernameAndName const& another) const;
	bool operator==(std::string const& anotherUsername) const; 
	auto operator<=>(const UsernameAndName& another) const->std::weak_ordering
	{
		return username <=> another.username;
	}
	UsernameAndName(json const& usernameAndNameJson);
	UsernameAndName(std::string_view username = "", std::string_view name = "");
	nlohmann::json get_json() const;
};

class Assignment
{
private:
	int assignmentId{};
	std::string content{};
	std::string feedback{};
	std::string solution{};
	std::string answer{};
	std::string studentUsername {};
	std::string studentName{};
	std::optional<double> grade{};
	 int total{};
	
	int assignment_number{};
	bool submitted{};
	

public:
	Assignment(std::string_view content, int total, std::string_view studentUsername, std::string_view studentName);
	Assignment(std::string_view content, int total, UsernameAndName const& usernameAndName);
	Assignment(std::string_view content, int total);
	Assignment(json const& jsonAssignment);
	Assignment() = default;

	std::string get_student_username() const;
	/*int get_courseId() const;*/
	void set_id(const int id);//ToDo Make only the Course class can access this function. 
	void set_content(std::string_view content);
	std::string get_content() const;
	void set_grade(const int grade);
	void set_grade(std::string_view grade);
	std::optional<double> get_grade() const;
	int get_total() const;
	std::pair<double, int> get_relative_grade()const;
	void set_solution(std::string_view solution);
	void set_feedback(std::string_view feedback);
	std::string all_info_student_string() const;
	json get_json() const;
	bool is_submitted() const;
	
	auto operator<=>(const Assignment& another) const->std::strong_ordering
	{
		return std::tie(studentUsername, content) <=> std::tie(another.studentUsername, another.content);
	};
	bool operator==(const Assignment&) const;

	std::string student_string() const;

	std::string doctor_Overview() const;

	std::string doctor_detailed_view() const;
	bool is_graded() const;
};

