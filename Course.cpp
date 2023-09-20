#include "Course.h"
#include <assert.h>


Course::Course(std::string_view code, string_view courseName, UsernameAndName const& docUsernameAndName) :
code(code),doctorUsername(docUsernameAndName.username),doc_name(docUsernameAndName.name),name(courseName)
{
}

Course::Course(json const& jsonCourse):
code(jsonCourse["code"]),
doctorUsername(jsonCourse["docUsername"]),
doc_name(jsonCourse["docName"]),
name(jsonCourse["courseName"])
{
	auto jsonCoursesAssignments = jsonCourse["courseAssignments"];
	std::vector<CourseAssignment>tempCourseAssignments{};
	
	for (const auto& jsonCourseAssi : jsonCoursesAssignments)
		tempCourseAssignments.emplace_back(CourseAssignment(jsonCourseAssi));
	courseAssignments = std::move(tempCourseAssignments);

	auto jsonUsernameAndNames = jsonCourse["usernameAndNames"];
	for (const auto& jsonUsernameandName : jsonUsernameAndNames)
		usernameAndNames.emplace_back(UsernameAndName(jsonUsernameandName));
}

std::string Course::doc_and_assignment_string(std::string_view studentUsername) const
{
	std::ostringstream res{};
	res << "Course " << name << " With Code " << code<<
		" taught by Doctor " << doc_name << " has " <<
		courseAssignments.size()  << " Assignments:\n";

	int i{ 1 };

	//for (const auto& assignment : get_user_assignments(studentUsername))
	//	res << "Assignment " << i++ <<" "<< assignment.StudentString() << '\n';

	return std::move(res.str());
}

std::string Course::overview_string() const
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

size_t Course::get_courseAssignments_number() const
{
	return courseAssignments.size();
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

std::string Course::all_info_student_string(std::string_view studentUsername) const
{
	std::ostringstream res{};
	res << doc_and_assignment_string(studentUsername);
	int i{ 1 };
	auto userAssins = get_user_assignments(studentUsername);
	for (const auto& assignment : userAssins)
		res << i++ << "- " << assignment.all_info_student_string()<<"\n";
	return res.str();
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

	json courseAssignmentArray, usernameAndNameArray;

	for (const auto& courseAss : courseAssignments)
		courseAssignmentArray.push_back(courseAss.get_json());
	res["courseAssignments"] = courseAssignmentArray;

	for (const auto& usernameAndName : usernameAndNames)
		usernameAndNameArray.push_back(usernameAndName.get_json());
	res["usernameAndNames"] = usernameAndNameArray;

	
	return res;
}

int Course::get_total_points_of_courseAssignments() const
{
	int res{};
	for (const auto& courseAssignment : courseAssignments)
		res += courseAssignment.get_total();
	return res;
}

double Course::get_scored_points_by_student(std::string_view studentUsername) const
{
	double res{ 0 };
	for (auto&& value :
		get_user_assignments(studentUsername) |
		std::views::transform([](const Assignment& assi) {return assi.get_grade().value_or(0); }))
	{
		res += value;
	}
	return res;
}

size_t Course::get_number_of_student_submitted_assignments(std::string_view studentUsername) const
{
	
	auto numSubmitted= get_user_assignments(studentUsername) |
		std::views::filter([](const Assignment& ass) {return ass.is_submitted(); });
	return std::distance(numSubmitted.begin(), numSubmitted.end());
}

std::string Course::get_grade_report_string(std::string_view studentUsername) const
{
	std::ostringstream res{};
	res << "For the Course: " << get_code() << " You have submitted " << get_number_of_student_submitted_assignments(studentUsername);
	res << "out of " << get_courseAssignments_number() << "assignments\n";
	res << "the currentGrade " << get_scored_points_by_student(studentUsername) << " out of " <<
		get_total_points_of_courseAssignments() << " Points\n";

	return res.str();
}





void Course::make_enum_based_action_on_assignment(const Assignment& assignment, std::string_view actionContent, AssignmentAction const& actionType)
{
	auto courseAssignmentIterator = std::find_if(courseAssignments.begin(), courseAssignments.end(), 
		[&](const CourseAssignment& searchedCourseAss) {return searchedCourseAss.get_content() == assignment.get_content(); });

	assert(courseAssignmentIterator != courseAssignments.end());
	courseAssignmentIterator->make_enum_based_action_on_assignment(assignment, actionContent, actionType);
}

void Course::remove_student(std::string const& studentUsername)
{
	for (auto& courseAssignment : courseAssignments)
		courseAssignment.remove_student(studentUsername);
	auto erasedStudents= std::erase(usernameAndNames, studentUsername);
	assert(erasedStudents > 0);
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



