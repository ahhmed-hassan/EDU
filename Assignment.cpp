#include "Assignment.h"
using std::endl;


//AssignmentId::AssignmentId(std::string_view studentUsername, int courseId): studentUsername(studentUsername), courseId(courseId)
//{
//}
//
//int AssignmentId::get_courseid() const
//{
//	return courseId;
//}
//
//std::string AssignmentId::get_student_username() const
//{
//	return studentUsername;
//}

//auto Assignment::operator<=>(const Assignment& another) const -> std::strong_ordering
//{
//	return assignmentId <=> another.assignmentId;
//}


bool Assignment::operator==(const Assignment& another) const
{
	return std::tie(student_user_name,content) == std::tie(another.student_user_name,another.content);
}

std::string Assignment::StudentString() const
{
	std::ostringstream res{};
	
	//res << "Assignment " << assignment_number;
	if (!submitted)
		res << " NOT" ;
	res << " Submitted--";

	if (grade.has_value())
		res << "NA";
	else
		res << grade.value();
	res << "/" << total;

	return (res.str());

}

std::string Assignment::doctor_Overview() const
{
	std::ostringstream res{};
	res << "Student : " << studentName << " has ";
	if (not submitted)
		res << "not ";
	res << "submitted";
	res << "and has the grade ";

	if (grade.has_value())
		res << grade.value();
	else
		res << "NA";

	return res.str();
}

std::string Assignment::doctor_detailed_view() const
{
	std::ostringstream res{};
	res << "Your Feedback is " << Feedback<<"\n";
	res << "Student Solution: " << solution << endl;
	return res.str(); 
}

bool Assignment::is_graded() const
{
	return grade.has_value();
}



void Assignment::set_id(const int id)
{
	this->assignmentId = id;
}

Assignment::Assignment
(std::string_view content,
	int total,
	std::string_view studentUsername,
	std::string_view studentName
	
)
	:content(content), total(total), studentName(studentName), student_user_name(studentUsername)
{
	
}

Assignment::Assignment(std::string_view content, int total, UsernameAndName const& usernameAndName):
Assignment(content, total, usernameAndName.username,usernameAndName.name)
{
}

Assignment::Assignment(std::string_view content, int total):content(content),total(total)
{
}

Assignment::Assignment(json const& jsonAssignment) :
	studentName(jsonAssignment["studentName"]),
	student_user_name(jsonAssignment["studentUsername"]),
	content(jsonAssignment["content"]),
	submitted(jsonAssignment["isSubmitted"]),
	Feedback(jsonAssignment["feedback"]),
	solution(jsonAssignment["solution"]),
	total(jsonAssignment["total"])
{
	grade = jsonAssignment["grade"].is_null() ? 
		std::nullopt : 
		std::optional<double>(jsonAssignment["grade"].get<double>());
}



std::string Assignment::get_student_username() const
{
	return student_user_name;
}



void Assignment::set_content(std::string_view content)
{
	this->content = content;
}

std::string Assignment::get_content() const
{
	return content;
}

void Assignment::set_grade(const int grade)
{
	this->grade = grade;
}

void Assignment::set_grade(std::string_view grade)
{
	return set_grade(std::stoi(static_cast<std::string>(grade)));
}

std::optional<double> Assignment::get_grade() const
{
	return grade;
}

int Assignment::get_total() const
{
	return total;
}

std::pair<double, int> Assignment::get_relative_grade() const
{
	return std::pair<double, int>(grade.value_or(0),total);
}

void Assignment::set_solution(std::string_view solution)
{
	this->solution = solution;
}

void Assignment::set_feedback(std::string_view feedback)
{
	this->Feedback = feedback;
}

std::string Assignment::all_info_student_string() const
{
	std::ostringstream res{};
	res << "content: " << content << '\n';
	if (!submitted)
		res << " NOT";
	res << " Submitted--";
	if (!solution.empty())
		res << "Your Solution is: "<<solution<<"\n";
	if (!Feedback.empty())
		res << "Feedback is: " << Feedback << "\n";

	res << "degree is: ";
	if (grade.has_value())
		res << "NA";
	else
		res << grade.value();
	res << "/" << total<<"\n";
	
	return (res.str());
}

json Assignment::get_json() const
{
	json res{};
	res["studentName"] = studentName;
	res["studentUsername"] = student_user_name;
	res["content"] = content;
	res["isSubmitted"] = submitted;
	res["feedback"] = Feedback;
	res["solution"] = solution;
	res["total"] = total;
	if (grade.has_value())
		res["grade"] = grade.value();
	else
		res["grade"] = nullptr;
	return res;
}

bool Assignment::is_submitted() const
{
	return submitted;
}

bool UsernameAndName::operator==(UsernameAndName const& another) const
{
	return username==another.username;
}

bool UsernameAndName::operator==(std::string_view anotherUsername) const
{
	return username == anotherUsername;
}
