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
	return std::tie(studentUsername,content) == std::tie(another.studentUsername,another.content);
}

std::string Assignment::student_string() const
{
	std::ostringstream res{};

	if (!submitted)
		res << " NOT" ;
	res << " Submitted-- ";

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
	res << "submitted ";


	if (grade.has_value())
		res << "and has the grade "<<grade.value()<<" out of "<<total;
	else
		res << "Not graded yet";

	return res.str();
}

std::string Assignment::doctor_detailed_view() const
{
	std::ostringstream res{};
	if (feedback.empty())
		res << "You have not provided a feeback yet\n";
	else
		res << "Your Feedback is " << feedback << "\n";

	res << "Student Solution: " << solution << endl;
	return res.str(); 
}

bool Assignment::is_graded() const
{
	return grade.has_value();
}





Assignment::Assignment
(std::string_view content,
	int total,
	std::string_view studentUsername,
	std::string_view studentName
	
)
	:content(content), total(total), studentName(studentName), studentUsername(studentUsername)
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
	studentUsername(jsonAssignment["studentUsername"]),
	content(jsonAssignment["content"]),
	submitted(jsonAssignment["isSubmitted"]),
	feedback(jsonAssignment["feedback"]),
	solution(jsonAssignment["solution"]),
	total(jsonAssignment["total"])
{
	grade = jsonAssignment["grade"].is_null() ? 
		std::nullopt : 
		std::optional<double>(jsonAssignment["grade"].get<double>());
}



std::string Assignment::get_student_username() const
{
	return studentUsername;
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
	this->submitted = true;
}

std::string Assignment::get_solution() const
{
	return solution;
}

void Assignment::set_feedback(std::string_view feedback)
{
	this->feedback = feedback;
}

std::string Assignment::all_info_student_string() const
{
	std::ostringstream res{};
	res  << "content :"<<content << '\t';
	if (!submitted)
		res << " NOT";
	res << " Submitted--";
	if (!solution.empty())
		res << "Your Solution is: "<<solution<<"\t";
	if (!feedback.empty())
		res << "Feedback is: " << feedback << "\t";

	
	if (not grade.has_value())
		res << "Not Graded yet";
	else
		res << "degree is: "<< grade.value() << "/" << total << "\n";
	
	
	return (res.str());
}

json Assignment::get_json() const
{
	json res{};
	res["studentName"] = studentName;
	res["studentUsername"] = studentUsername;
	res["content"] = content;
	res["isSubmitted"] = submitted;
	res["feedback"] = feedback;
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

bool UsernameAndName::operator==(std::string const& anotherUsername) const
{
	return username == anotherUsername;
}

UsernameAndName::UsernameAndName(json const& usernameAndNameJson):
	UsernameAndName(usernameAndNameJson["username"],usernameAndNameJson["name"])
{

}

UsernameAndName::UsernameAndName(std::string_view username, std::string_view name):username(username), name(name)
{
}

nlohmann::json UsernameAndName::get_json() const
{
	 nlohmann::json res{};
	 res["username"] = username;
	 res["name"] = name;
	 return res; 
}
