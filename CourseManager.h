#pragma once
#include "Course.h"
#include <map>
#include <vector>
using CoursePtr = std::shared_ptr<Course>;


class CourseManager
{
private: 
	std::map<std::string, Course> courses_map{};//course code to course
public:
	 void LoadDataBasee();
	 /*inline*/ std::vector<Course> getUserCourses(User const& user)  ;
	 void SubmitSolution(int, std::string_view);
	 void RemoveStudent(int student_id, int course_id);

	// void remove_assignemnt_from_course(Assignment const& assignment);

	 void make_enum_based_action_on_course_assignment(
		 Course const& course,
		 CourseAssignment const& courseAssingment,
		 Assignment const& assignment, 
		 std::string_view action_content, 
		 const AssignmentAction& actionType
	 );

	 std::string get_detailed_string_for_course();

	 void remove_assignment_from_course(Course const& course, Assignment const& assignment);

	 void add_course_assignments_for_new_student(std::string_view courseCode, std::string_view studentName);

	 std::optional<std::string> get_course_overview(std::string_view courseCode) const;

	 void addAssignemntToCourse
	 (
		 Course const& course,
		 std::string_view content,
		 const int total_points,
		 std::string_view doc_name,
		 std::vector<std::string> const& studentnamesAtThisCourse
	 );

};

