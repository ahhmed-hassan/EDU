#include "StudentView.h"
StudentView::StudentView(CourseManagerPtr cManger, UserManagerPtr uManger):
	courses(std::move(cManger)), users(std::move(uManger)){}

StudentView::StudentView(StudentView&& another) noexcept
{
	courses=std::move(another.courses);
	users = std::move(another.users);
}

void StudentView::course_choices(Course const& course)
{
	while (true)
	{
		int choice = show_read_menu({ "Unregister from course","Show Assignments", "Back" });
		switch (choice)
		{
		case 1:
			unregister(course);
			break;
		case 2:
			show_assignments_in_course(course);
			break;
		default:
			return;
		}
	}
}

void StudentView::assignment_subList(const Course& course,const Assignment& assignment)
{
	if (assignment.is_graded())
	{
		std::cout << "You cannot set a solution for a graded Assignment try another one\n"; return;
	}
	while(true)
	{
		std::cout << "Enter 1 to add a solution or 0 to go back\n";
		int choice = read_int(0, 1);
		if (!choice)
			return;
		std::cout << "Please Enter Your Solution\n";
		std::string solution;
		std::getline(std::cin, solution);
		courses->make_enum_based_action_on_course_assignment(course, assignment, solution, AssignmentAction::addSolution);
		std::cout << "You have added a new Solution!\n";

	}


}

void StudentView::show_assignments_in_course(Course const& course)
{
	auto studentAssignments = course.get_user_assignments(users->get_currentuser_username());
	int i{ 1 };
	while (true)
	{
		for (const auto ass : studentAssignments)
			std::cout << ass.all_info_student_string() << "\n";
		std::cout << "choose the ith assignments or 0 to cancel";
		int assignmentChoice = read_int(0, (int)studentAssignments.size()) - 1;
		if (assignmentChoice < 0)
			return;

		return assignment_subList(course, studentAssignments[assignmentChoice]);
	}
}

void StudentView::Display()
{
	int choice = show_read_menu(
		{ "Register In Course", "List My Courses", "View Course","Grades Report",
		"Log Out" }
	);
	while (true)
	{
		switch (choice)
		{
		case 1:
			register_in_course(); break;
		case 2:
			list_courses(); break;
		case 3:
			view_courses(); break;
		case 4:
			grades_report(); break;
		case 5:
			log_out();
			return;

		default:
			break;
		}
	}
	return;
}

void StudentView::grades_report()
{
	
	auto studentCourses = courses->getUserCourses(users->get_current_user());
	for (const auto& course : studentCourses)
	{
		std::cout << course.get_grade_report_string(users->get_currentuser_username())<<"\n";
	}

	
}

void StudentView::list_courses()
{
	std::vector<Course> const& user_courses= courses->getUserCourses(users->get_current_user()) ;
	auto coursesOverviews = user_courses
		| std::views::transform([](const Course& course) {return course.overview_string(); });

	int coursesChoice= show_read_menu(to_vector(coursesOverviews), "Your Courses Are",true,true)-1;
	if (coursesChoice == -1)
		return; 
	std::cout << user_courses[coursesChoice].all_info_student_string(users->get_currentuser_username()) << endl;
		
	/*std::cout << endl; 
	return sublist_courses();*/

}

void StudentView::register_in_course()
{
	std::cout << "Please Enter the code of the course in which you want to register\n"; std::string code{}; cin >> code;
	auto courseOverview = courses->get_course_overview(code);
	if (not courseOverview.has_value())
	{
		std::cout << "There is no course with this code\n"; return register_in_course();
	}
	std::cout << "Your chosen course\n" << courseOverview.value() << "\n"; 

	users->register_in_course(code);
	courses->add_new_student_usernameAndName_to_course(code, users->get_currentuser_usernameAndName());
	std::cout << "You are enrolled in the course";

}

void StudentView::log_out()
{
	users->save_data_to_json();
	courses->save_data_to_json();
}

void StudentView::sublist_courses()
{
	auto userCourses = courses->getUserCourses(users->get_current_user());

	std::cout << "Choose the ith  [1" << userCourses.size()  << "] Course to view\n";
	int choice = read_int(1, (int)userCourses.size() );
	std::string courseDetailedString{};
	std::cout << userCourses[choice - 1].all_info_student_string(users->get_currentuser_username()) << endl;


}

void StudentView::unregister(Course const& course)
{

	courses->remove_student(course, users->get_currentuser_username());
	users->unregister_student_from_course(users->get_current_user(), course.get_code());
}

void StudentView::view_courses()
{
	//std::cout<<"Choose the ith [1"<<
	
	auto userCourses = courses->getUserCourses(users->get_current_user());
	auto coursesOverviews = userCourses |
		std::views::transform([](const Course& course) {return course.overview_string(); });
	int coursesChoice = show_read_menu(to_vector(coursesOverviews), "Your Courses", true, true);
	/*int i = 0;
	for (const auto& course : userCourses)
		std::cout << ++i << " -)" << course.overview_string() << std::endl;
	std::cout << "choose the ith course or 0 to cancel\n";
	int courseChoice = read_int(0, (int)userCourses.size())-1;*/

	if (coursesChoice  ==-1)
		return; 
	std::cout << userCourses[coursesChoice].doc_and_assignment_string(users->get_currentuser_username());
	std::cout << "Choose the ith Assignment or 0 to cancel\n";

	int assignmentChoice = read_int(0, (int)userCourses[coursesChoice].get_courseAssignments_number())-1;
	if (assignmentChoice < 0)
		return;

	auto userAssignments = userCourses[coursesChoice].get_user_assignments(users->get_currentuser_username());
	auto chosenAssignment = userAssignments[assignmentChoice];

	//users->
}
