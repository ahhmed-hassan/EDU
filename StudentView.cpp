#include "StudentView.h"
const std::string dummy = "dummy";
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
			return;
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
	if(not assignment.get_solution().empty())
		std::cout << "your current solution: " << assignment.get_solution();
	if (assignment.is_graded())
	{
		std::cout << "You cannot set a solution for a graded Assignment try another one\n"; return;
	}
	while(true)
	{
		
		int choice = show_read_menu({"add a solution", "go back"});
		if (choice==2)
			return;
		std::cout << "Please Enter Your Solution\n";
		std::string solution;
		std::getline(std::cin, solution);
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
		
		auto assignmentsAllInfoStrings = studentAssignments |
			std::views::transform([](const Assignment& ass) {return ass.all_info_student_string(); });
		std::string_view header = "Your Assignments report", fallback = "You have no assignments";
		int assignmentChoice = show_read_menu(to_vector(assignmentsAllInfoStrings), header, fallback, true, true)-1;
		if (assignmentChoice == -1)
			return;

		return assignment_subList(course, studentAssignments[assignmentChoice]);
	}
}

void StudentView::Display()
{
	
	while (true)
	{
		int choice = show_read_menu(
			{ "Register In Course", "List My Courses", "View system Course","Grades Report",
			"Log Out" }
		);
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
	
	auto studentCourses = courses->get_user_courses(users->get_current_user());
	for (const auto& course : studentCourses)
	{
		std::cout << course.get_grade_report_string(users->get_currentuser_username())<<"\n";
	}

	
}

void StudentView::list_courses()
{
	std::vector<Course> const& user_courses= courses->get_user_courses(users->get_current_user()) ;
	auto coursesOverviews = user_courses
		| std::views::transform([](const Course& course) {return course.overview_string(); });

	std::string_view header = "Your courses are", backUp = "You have no courses yet";
	int coursesChoice= show_read_menu(to_vector(coursesOverviews),header, backUp,true,true)-1;
	if (coursesChoice == -1)
		return; 
	std::cout << user_courses[coursesChoice].doc_and_assignment_string(users->get_currentuser_username()) ;

	 course_choices(user_courses[coursesChoice]);
	return list_courses(); 
		
}

void StudentView::register_in_course()
{
	std::cout << "Please Enter the code of the course in which you want to register\n"; std::string code{}; cin >> code;
	auto courseOverview = courses->get_course_overview(code);
	while (not courseOverview.has_value() or users->get_current_user().is_enrolled_at_course(code))
	{
		if (not courseOverview.has_value())
			std::cout << "There is no course with this code please try again ";

		else
			std::cout << "you are already enrolled at this course please try again ";
					
		std::cout << "or enter "+ dummy+ " to cancel\n";
		std::cin >> code;
		if (code == dummy)
			return;
		courseOverview = courses->get_course_overview(code);
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



void StudentView::unregister(Course const& course)
{

	courses->remove_student(course, users->get_currentuser_username());
	users->unregister_student_from_course(users->get_current_user(), course.get_code());
	std::cout << "You have unregistered from the course!\n";
}

void StudentView::view_courses()
{
	std::string_view header = "System Courses", fallBack = "No Courses yet";
	show_read_menu(courses->get_all_courses_overview(), header, fallBack, false, false);
	//std::cout<<"Choose the ith [1"<<
	return;


}
