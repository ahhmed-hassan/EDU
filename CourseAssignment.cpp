#include "CourseAssignment.h"

CourseAssignment::CourseAssignment
(std::string_view content,
	const int totalPoints, 
	std::vector<UsernameAndName> const& studentNames):content(content), totalPoints(totalPoints)
{
	for(const auto& studentName:studentNames)
	{
		Assignment assignmentForStudent(content, totalPoints, studentName);
		assignments.emplace_back(assignmentForStudent);
	}
}

CourseAssignment::CourseAssignment(json const& jsonCourseAssignment) :
	content(jsonCourseAssignment["content"]),
	totalPoints(jsonCourseAssignment["totalPoints"])
{
	auto jsonAssignments = jsonCourseAssignment["Assignments"];
	std::vector<Assignment> tempAssignments{}; 

	for (const auto& jsonAssignmet : jsonAssignments)
		tempAssignments.push_back(Assignment(jsonAssignmet));

	assignments = std::move(tempAssignments);
}

void CourseAssignment::add_student_entry(UsernameAndName const& usernameAndName)
{
	if (assignments.empty())
		return;
	assignments.emplace_back(content, totalPoints, usernameAndName);
}

std::string const& CourseAssignment::get_content() const
{
	return content;
}

std::vector<Assignment> const& CourseAssignment::get_assignments() const
{
	return assignments;
}

std::vector<std::string> CourseAssignment::get_doctor_overview() const
{
	std::vector<std::string>res{}; 
	for (const auto& assign : assignments)
		res.push_back(assign.doctor_detailed_view());
	return res; 
}

Assignment CourseAssignment::get_student_assigment(std::string_view studentUsername) const
{
	/*auto studentAssignments = assignments |
		std::views::filter([&](const Assignment& ass) {return ass.get_student_username() == studentUsername; });*/
	auto assignnmentIterator = std::ranges::find_if(assignments, [&](const Assignment& ass) {return ass.get_student_username() == studentUsername; });
	assert(assignnmentIterator != assignments.end());
	return *assignnmentIterator;
}

json CourseAssignment::get_json() const
{
	json res{  };
	res["content"] = content;
	res["totalPoints"] = totalPoints;
	json assignmentsArray;

	for (const auto& ass : assignments)
		assignmentsArray.push_back(ass.get_json());

	res["Assignments"] = assignmentsArray;
	return res;
}

bool CourseAssignment::operator==(const CourseAssignment& another) const
{
	return content == content;
}

bool CourseAssignment::operator==(std::string_view anotherCOntent) const
{
	return content == anotherCOntent;
}

void CourseAssignment::make_enum_based_action_on_assignment(const Assignment& assignment, std::string_view actionContent, AssignmentAction const& actionType)
{
	
	auto myAssignmentIterator = std::find(assignments.begin(), assignments.end(), assignment);
	auto pos = myAssignmentIterator - assignments.begin();
	auto& searchedAssignment = assignments[pos];
	switch (actionType)
	{
	case AssignmentAction::addFeedback:
		searchedAssignment.set_feedback(actionContent); break;
	case AssignmentAction::addSolution:
		searchedAssignment.set_solution(actionContent); break;
	case AssignmentAction::addDegree:
		searchedAssignment.set_grade(actionContent); break;
	default:
		break;
	}
}

int CourseAssignment::get_total() const
{
	return totalPoints;
}
