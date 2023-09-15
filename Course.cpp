#include "Course.h"
#include <assert.h>


Course::Course(std::string_view code, std::string_view docUsername, string_view docName, string_view name):
code(code),doctorUsername(docUsername),doc_name(docName),name(name)
{
}

std::string Course::StudentDetailedString() const
{
	std::ostringstream res{};
	res << "Course " << name << " With Code " << code<<
		" taught by Doctor " << doc_name << " has " <<
		assignments.size() + 1 << " Assignments:\n";

	int i{ 1 };

	for (const auto& assignment : assignments)
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

std::vector<Assignment> const& Course::get_assignments() const
{
	return assignments;
}

//int Course::GetId() const
//{
//	return id;
//}

std::string const Course::get_code() const
{
	return code;
}

void Course::addAssigment( Assignment&& assign)
{
	assignments.push_back(assign);
	//Every assignment has it's position in the vector as an ID. 
	assignments.back().set_id((int)assignments.size() - 1);
}

void Course::add_empty_assignment_for_student(std::string_view studentName)
{
	if (assignments.empty())
		return;
	auto exampleAsssignment = assignments[0];
	Assignment ass(exampleAsssignment.get_content(), exampleAsssignment.get_total());
	addAssigment(std::move(ass));

}



void Course::make_enum_based_action_on_assignment(const Assignment& assignment, std::string_view actionContent, AssignmentAction const& actionType)
{
	auto myAssignmentIterator = std::find( assignments.begin(),assignments.end(), assignment);
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

void Course::remove_assignment(const Assignment& assignment)
{
	auto const assignmentIterator=std::find(assignments.begin(), assignments.end(), assignment);
	//auto assPos = assignmentIterator - assignments.begin();
	//auto it = assignmentIterator + assignments.begin();
	assignments.erase(assignmentIterator);

}

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