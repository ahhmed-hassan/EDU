#pragma once
#include "Course.h"
#include "Helpers.h"
#include <map>
#include <fstream>

#include <vector>
using CoursePtr = std::shared_ptr<Course>;


class CourseManager
{
private: 
	std::map<std::string, Course> courses_map{};//course code to course
	void load_database(std::string const& path = "courses.json");
public:
	
	 CourseManager(std::optional<nlohmann::json> courseManagerJson);
	 CourseManager(std::string const& path = "courses.json");
	// CourseManager() = default;
	 /*inline*/ std::vector<Course> getUserCourses(User const& user) const  ;
	 void SubmitSolution(int, std::string_view);
	 void remove_student(const Course& course, std::string const&  studentUsername);
	 std::vector<std::string>  get_user_courses_overview(const User& user) const;
	std::vector<std::string> get_all_courses_overview() const; 
	// void remove_assignemnt_from_course(Assignment const& assignment);



	 void make_enum_based_action_on_course_assignment(
		 Course const& course,
		
		 Assignment const& assignment,
		 std::string_view action_content,
		 const AssignmentAction& actionType
	 );

	 std::string get_detailed_string_for_course();

	 void add_course(
		 std::string_view code, std::string_view courseName,
		UsernameAndName const& docUsernameAndName);

	 void remove_assignment_from_course(Course const& course, Assignment const& assignment);

	 void add_new_student_usernameAndName_to_course(std::string_view courseCode, UsernameAndName const& studentUsernameAndName);

	 std::optional<std::string> get_course_overview(std::string_view courseCode) const;

	 void add_assignment_to_course
	 (
		 Course const& course,
		 std::string_view content,
		 const int total_points
		/* std::string_view doc_name,*/
		// std::vector<std::string> const& studentnamesAtThisCourse
	 );
	 std::pair<double,int> get_relative_grade_report_for_student(const User& student) const;
	 bool is_course_code_available(std::string_view courseCode)const;
	 void save_data_to_json(std::string const& path= "courses.json") const;
	 json get_json() const;

};

