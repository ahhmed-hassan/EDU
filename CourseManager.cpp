#include "CourseManager.h"
void CourseManager::LoadDataBasee()
{
	return;
}

CourseManager::CourseManager(json const& courseManagerJson)
{
	for (const auto& courseJson : courseManagerJson)
	{
		Course tmpCourse(courseJson);
		std::string code(tmpCourse.get_code());
		courses_map.insert({ code,std::move(tmpCourse) });
	}
}

void CourseManager::SubmitSolution(int course_id, std::string_view solution)
{
	
}
//void CourseManager::remove_assignemnt_from_course(Assignment const& assignment)
//{
//	courses_map[assignment.get_courseId()].remove_assignment(assignment);
//}

void CourseManager::make_enum_based_action_on_course_assignment(Course const& course, CourseAssignment const& courseAssingment,Assignment const& assignment, std::string_view action_content, const AssignmentAction& actionType)
{
	courses_map[course.get_code()].make_enum_based_action_on_assignment(courseAssingment,assignment, action_content, actionType);
}

void CourseManager::add_course(std::string_view code, std::string_view courseName, std::string_view docName, std::string_view docUsername)
{
	Course newCourse(code, docUsername, docName, courseName);
	courses_map.insert({ (std::string)code, newCourse });
}

//void CourseManager::remove_assignment_from_course( Course const& course, Assignment const& assignment)
//{
//	courses_map[course.get_code()].remove_assignment(assignment);
//}

void CourseManager::add_new_student_usernameAndName_to_course(std::string_view courseCode,UsernameAndName const& studentUsernameAndName)
{
	//courses_map[(std::string)courseCode].add_empty_assignment_for_new_student(studentUsernameAndName);
	courses_map[(std::string)courseCode].add_new_student_ussername_and_name(studentUsernameAndName);
}

std::optional<std::string> CourseManager::get_course_overview(std::string_view courseCode) const
{
	std::optional<std::string> res{};
	auto it = courses_map.find(std::string(courseCode));
	if (it != courses_map.end())
		res = it->second.OverviewString();
	return res; 
}

void CourseManager::addAssignemntToCourse
(
	Course const& course, 
	std::string_view content,
	const int total_points
	/*std::string_view doc_name,*/
	/*std::vector<std::string> const& studentnamesAtThisCourse*/
)
{
	auto course_id = course.get_code();

	/*for (auto const& name : studentnamesAtThisCourse)
	{
		auto assignmentForThisStudent = Assignment(content, total_points, name);
		courses_map[course_id].addAssigment(std::move(assignmentForThisStudent));
	}*/
	courses_map[course_id].add_courseAssignment(content, total_points);
	
}
bool CourseManager::is_course_code_available(std::string_view courseCode) const
{
	std::string code = static_cast<std::string>(courseCode);
	return courses_map.find(code) != courses_map.end();
	//return std::find(courses_map.cbegin(), courses_map.cend(), code) != courses_map.cend();
}
json CourseManager::get_json() const
{
	json res{};
	for (const auto& [code, course] : courses_map)
	{
		res.push_back(course.get_json());
	}
	return res; 
}
//void CourseManager::RemoveStudent(int student_id, int course_id)
//{
//	courses_map[course_id]->RemoveStudent(student_id);
//}
 std::vector<Course> CourseManager::getUserCourses(User const& user) 
{
	std::vector<Course > res{};
	//static_assert(typeid(courses_map[1].name()=="Course *"))
	for ( const auto& id : user.get_courses())
		res.push_back(courses_map[id]);
	return res;
	
}