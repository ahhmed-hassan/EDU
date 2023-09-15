#include "CourseManager.h"
void CourseManager::LoadDataBasee()
{
	return;
}

void CourseManager::SubmitSolution(int course_id, std::string_view solution)
{
	
}
//void CourseManager::remove_assignemnt_from_course(Assignment const& assignment)
//{
//	courses_map[assignment.get_courseId()].remove_assignment(assignment);
//}

void CourseManager::make_enum_based_action_on_course_assignment(Course const& course,Assignment const& assignment, std::string_view action_content, const AssignmentAction& actionType)
{
	courses_map[course.get_code()].make_enum_based_action_on_assignment(assignment, action_content, actionType);
}

void CourseManager::remove_assignment_from_course( Course const& course, Assignment const& assignment)
{
	courses_map[course.get_code()].remove_assignment(assignment);
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
	const int total_points,
	std::string_view doc_name,
	std::vector<std::string> const& studentnamesAtThisCourse
)
{
	auto course_id = course.get_code();

	for (auto const& name : studentnamesAtThisCourse)
	{
		auto assignmentForThisStudent = Assignment(content, total_points, name);
		courses_map[course_id].addAssigment(std::move(assignmentForThisStudent));
	}
	
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