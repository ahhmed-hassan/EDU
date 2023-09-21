#pragma once
#include "Course.h"
#include "Helpers.h"
#include <map>
#include <fstream>

#include <vector>
using CoursePtr = std::shared_ptr<Course>;


class CourseManager
{
public:
	
	 CourseManager(std::optional<nlohmann::json> courseManagerJson);
	 CourseManager(std::string const& path = "courses.json");
	

	 //getters
	 std::vector<Course> get_user_courses(User const& user) const  ;
	 void remove_student(const Course& course, std::string const&  studentUsername);
	 std::vector<std::string>  get_user_courses_overview(const User& user) const;
	std::vector<std::string> get_all_courses_overview() const; 

	 std::pair<double,int> get_relative_grade_report_for_student(const User& student) const;

	 std::optional<std::string> get_course_overview(std::string_view courseCode) const;

	 bool is_course_code_available(std::string_view courseCode)const;
	 json get_json() const;


	 //adding, removing and modification
	 	 void make_enum_based_action_on_course_assignment
		 (
		 Course const& course,
		 Assignment const& assignment,
		 std::string_view action_content,
		 const AssignmentAction& actionType
		 );


	
	 void add_course(
		 std::string_view code, std::string_view courseName,
		UsernameAndName const& docUsernameAndName);

	
	 void add_new_student_usernameAndName_to_course(std::string_view courseCode, UsernameAndName const& studentUsernameAndName);


	 void add_assignment_to_course
	 (
		 Course const& course,
		 std::string_view content,
		 const int total_points
	 );
	 void save_data_to_json(std::string const& path= "courses.json") const;

private:
	std::map<std::string, Course> courses_map{};//course code to course
	void load_database(std::string const& path = "courses.json");

};

