#include "Course.h"
#include <assert.h>


Course::Course(std::string_view code, std::string_view docUsername, string_view docName, string_view name):
code(code),doctorUsername(docUsername),doc_name(docName),name(name)
{
}

Course::Course(json const& jsonCourse):
code(jsonCourse["code"]),
doctorUsername(jsonCourse["docUsername"]),
doc_name(jsonCourse["docName"]),
name(jsonCourse["courseName"])
{
	auto jsonCoursesAssignments = jsonCourse["CourseAssignments"];
	std::vector<CourseAssignment>tempCourseAssignments{};
	
	for (const auto& jsonCourseAssi : jsonCoursesAssignments)
		tempCourseAssignments.emplace_back(CourseAssignment(jsonCourseAssi));
	courseAssignments = std::move(tempCourseAssignments);
}

std::string Course::StudentDetailedString(std::string_view studentUsername) const
{
	std::ostringstream res{};
	res << "Course " << name << " With Code " << code<<
		" taught by Doctor " << doc_name << " has " <<
		courseAssignments.size() + 1 << " Assignments:\n";

	int i{ 1 };

	for (const auto& assignment : get_user_assignments(studentUsername))
		res << "Assignment " << i++ <<" "<< assignment.StudentString() << '\n';

	return std::move(res.str());
}

std::string Course::OverviewString() const
{
	std::string res{}; 
	res += "Course "; 
	res += name; 
	res += " -Code: "; 
	res += code;
	return std::move(res);
}


std::vector<std::string> Course::get_assignments_contents() const
{
	auto AssignmentContents = courseAssignments | std::views::transform([](const CourseAssignment& courseAss) {return courseAss.get_content(); });
	return std::vector<std::string>(AssignmentContents.begin(), AssignmentContents.end());
}

std::vector<Assignment> const& Course::get_assignments(const int courseAssignmentPos) const
{
	return courseAssignments[courseAssignmentPos].get_assignments();
}

std::vector<CourseAssignment> const& Course::get_course_assignments() const
{
	return courseAssignments;
}

//int Course::GetId() const
//{
//	return id;
//}

std::string const Course::get_code() const
{
	return code;
}

void Course::add_courseAssignment(std::string_view content, const int totalPoints)//, std::vector<std::string> studentnamesAtThisCourse)
{
	courseAssignments.emplace_back(CourseAssignment(content, totalPoints, usernameAndNames));
}

//void Course::addAssigment( Assignment&& assign)
//{
//	assignments.push_back(assign);
//	//Every assignment has it's position in the vector as an ID. 
//	assignments.back().set_id((int)assignments.size() - 1);
//}

void Course::add_new_student_ussername_and_name(UsernameAndName const& usernameAndName)
{
	usernameAndNames.push_back(usernameAndName);
	if (courseAssignments.empty())
		return;

	for (auto& courseAssignment : courseAssignments)
		courseAssignment.add_student_entry(usernameAndName);
}

//void Course::add_empty_assignment_for_new_student(std::string_view studentName)
//{
//	if (courseAssignments.empty())
//		return;
//
//	for (auto& courseAssi : courseAssignments | std::views::all)
//		courseAssi.add_student_entry(studentName);
//
//}

std::vector<Assignment> Course::get_user_assignments(std::string_view studentUsername) const
{
	auto studentAssignments= courseAssignments | std::views::all |
		std::views::transform([&](const CourseAssignment& courseAssignment) {return courseAssignment.get_student_assigment(studentUsername); });
	return std::vector<Assignment>(studentAssignments.begin(), studentAssignments.end());
}

json Course::get_json() const
{
	json res{};
	res["code"] = code;
	res["docUsername"] = doctorUsername;
	res["docName"] = doc_name;
	res["courseName"] = name;

	json courseAssignmentArray;
	for (const auto& courseAss : courseAssignments)
		courseAssignmentArray.push_back(courseAss.get_json());

	res["CourseAssignments"] = courseAssignmentArray;
	return res;
}



void Course::make_enum_based_action_on_assignment(CourseAssignment const& courseAssingment,const Assignment& assignment, std::string_view actionContent, AssignmentAction const& actionType)
{

	auto courseAssignmentIterator = std::ranges::find(courseAssignments, courseAssingment);
	courseAssignmentIterator->make_enum_based_action_on_assignment(assignment, actionContent, actionType);
	
}

bool Course::operator==(const Course& another) const
{
	return code == another.code;
}

//void Course::remove_assignment(const Assignment& assignment)
//{
//	auto const assignmentIterator=std::find(assignments.begin(), assignments.end(), assignment);
//	//auto assPos = assignmentIterator - assignments.begin();
//	//auto it = assignmentIterator + assignments.begin();
//	assignments.erase(assignmentIterator);
//
//}

//void Course::RemoveStudent(int student_id)
//{
//	auto it = std::ranges::find(students_ids, student_id);
//	assert(it != students_ids.end(), "Student Not Fund");
//	students_ids.erase(it);
//	return;
//}

//void Course::SetSolution(string_view sol)
//{
//	conte
//}