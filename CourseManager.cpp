#include "CourseManager.h"
void CourseManager::load_database(std::string const& path)
{
	std::optional<nlohmann::json> courseManagerJson = parse_json_from_file(path);
	if (not courseManagerJson.has_value())
		return; 
	for (const auto& courseJson : courseManagerJson.value())
	{
		Course tmpCourse(courseJson);
		std::string code(tmpCourse.get_code());
		courses_map.insert({ code,std::move(tmpCourse) });
	}
	
}

CourseManager::CourseManager(std::optional<nlohmann::json> courseManagerJson)
{
	if( courseManagerJson.has_value())
	{
		auto jsonData = courseManagerJson.value();
		for (const auto& courseJson : jsonData)
		{
			Course tmpCourse(courseJson);
			std::string code(tmpCourse.get_code());
			courses_map.insert({ code,std::move(tmpCourse) });
		}
	}
}

CourseManager::CourseManager(std::string const& path):CourseManager(parse_json_from_file(path))
{
	
}


void CourseManager::remove_student(const Course& course, std::string const& studentUsername)
{
	courses_map[course.get_code()].remove_student(studentUsername);
}
std::vector<std::string> CourseManager::get_user_courses_overview(const User& user) const
{
	auto const userCourses = get_user_courses(user);
	auto overviews = userCourses | views::transform([](const Course& course) {return course.overview_string(); });
	return std::vector<std::string>{overviews.begin(), overviews.end()};
}
std::vector<std::string> CourseManager::get_all_courses_overview() const
{
	auto overviewsRange = courses_map | std::views::values |
		std::views::transform([](const Course& course) {return course.overview_string(); });
	return std::vector<std::string>(overviewsRange.begin(), overviewsRange.end());
}




void CourseManager::make_enum_based_action_on_course_assignment(Course const& course, Assignment const& assignment, std::string_view action_content, const AssignmentAction& actionType)
{
	courses_map[course.get_code()].make_enum_based_action_on_assignment(assignment, action_content, actionType);
}

void CourseManager::add_course(std::string_view code, std::string_view courseName, UsernameAndName const& docUsernameAndName)
{
	Course newCourse(code,courseName,docUsernameAndName);
	courses_map.insert({ (std::string)code, newCourse });
}



void CourseManager::add_new_student_usernameAndName_to_course(std::string_view courseCode,UsernameAndName const& studentUsernameAndName)
{
	
	courses_map[(std::string)courseCode].add_new_student_ussername_and_name(studentUsernameAndName);
}

std::optional<std::string> CourseManager::get_course_overview(std::string_view courseCode) const
{
	std::optional<std::string> res{};
	auto it = courses_map.find(std::string(courseCode));
	if (it != courses_map.end())
		res = it->second.overview_string();
	return res; 
}

void CourseManager::add_assignment_to_course
(
	Course const& course, 
	std::string_view content,
	const int total_points
)
{
	auto course_id = course.get_code();


	courses_map[course_id].add_courseAssignment(content, total_points);
	
}
std::pair<double, int> CourseManager::get_relative_grade_report_for_student(const User& student) const
{
	assert(not student.isDoctor());
	double scored{}; int total{};
	auto studentCourses = get_user_courses(student);
	for (const auto& course : studentCourses)
	{
		auto userAssignments=course.get_user_assignments(student.get_username());
		auto relativeGradeReportRange = userAssignments |
										std::views::transform([](const Assignment& ass) {return ass.get_relative_grade(); });
		for (const auto& [scoredInRange, totalInRange] : relativeGradeReportRange)
		{
			scored += scoredInRange; total += totalInRange;
		}
			
		
	}
	return { scored,total };
}
bool CourseManager::is_course_code_available(std::string_view courseCode) const
{
	std::string code = static_cast<std::string>(courseCode);
	return courses_map.find(code) == courses_map.end();
	
}
void CourseManager::save_data_to_json(std::string const& path) const
{
	auto jsonData = get_json(); 
	std::ofstream output(path); 
	if (not output.is_open())
		throw std::runtime_error("Cannot open the file " + path);
	
	try
	{
		output << jsonData.dump(4) << std::endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what()<<endl; 
	}
	output.close();
}
json  CourseManager::get_json() const
{
	json res{};
	for (const auto& [code, course] : courses_map)
	{
		res.push_back(course.get_json());
	}
	return res; 
}

 std::vector<Course> CourseManager::get_user_courses(User const& user) const
{
	std::vector<Course > res{};
	//static_assert(typeid(courses_map[1].name()=="Course *"))
	for ( const auto& id : user.get_courses())
		res.push_back(courses_map.at(id));
	return res;
	
}