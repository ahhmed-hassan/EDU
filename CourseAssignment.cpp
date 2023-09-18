#include "CourseAssignment.h"

CourseAssignment::CourseAssignment
(std::string_view content,
	const int totalPoints, 
	std::vector<std::string> const& studentNames):content(content), totalPoints(totalPoints)
{
	for(const auto& studentName:studentNames)
	{
		Assignment assignmentForStudent(content, totalPoints, studentName);
		assignments.emplace_back(assignmentForStudent);
	}
}

void CourseAssignment::add_student_entry(std::string_view studentName)
{
	if (assignments.empty())
		return;
	assignments.emplace_back(content, totalPoints, studentName);
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

bool CourseAssignment::operator==(const CourseAssignment& another) const
{
	return content == content;
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