#include "StudentView.h"
StudentView::StudentView(CourseManagerPtr cManger, UserManagerPtr uManger):
	courses(cManger), users(uManger){}

StudentView::StudentView(StudentView&& another) noexcept
{
	courses=std::move(another.courses);
	users = std::move(another.users);
}

void StudentView::CourseChoices(Course const& course)
{
	int choice = ShowReadMenu({ "Unregister from course","Show Assignments", "Back" });
	switch (choice)
	{
	case 1:
		Unregister(course);
		break;

	default:
		break;
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
		int choice = ReadInt(0, 1);
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
		int assignmentChoice = ReadInt(0, (int)studentAssignments.size()) - 1;
		if (assignmentChoice < 0)
			return;

		return assignment_subList(course, studentAssignments[assignmentChoice]);
	}
}

void StudentView::Display()
{
	int choice = ShowReadMenu(
		{ "Register In Course", "List My Courses", "View Course","Grades Report",
		"Log Out" }
	);
	while (true)
	{
		switch (choice)
		{
		case 1:
			RegisterInCourse(); break;
		case 2:
			ListCourses(); break;
		case 3:
			ViewCourses(); break;
		case 4:
			GradesReport(); break;

		default:
			break;
		}
	}
	return;
}

void StudentView::GradesReport()
{
	
	auto studentCourses = courses->getUserCourses(users->GetCurrentUser());
	for (const auto& course : studentCourses)
	{
		std::cout << course.get_grade_report_string(users->get_currentuser_username())<<"\n";
	}

	
}

void StudentView::ListCourses()
{
	std::vector<Course> const& user_courses= courses->getUserCourses(users->GetCurrentUser()) ;
	std::cout << "My Courses:\n";
	int i = 0;
	for (auto course : user_courses)
		std::cout << ++i<<"- "<<course.OverviewString() << endl;
		
	std::cout << endl; 
	return SubListCourses();

}

void StudentView::RegisterInCourse()
{
	std::cout << "Please Enter the code of the course in which you want to register\n"; std::string code{}; cin >> code;
	auto courseOverview = courses->get_course_overview(code);
	if (not courseOverview.has_value())
	{
		std::cout << "There is no course with this code\n"; return RegisterInCourse();
	}
	std::cout << "Your chosen course\n" << courseOverview.value() << "\n"; 

	users->register_in_course(code);
	courses->add_new_student_usernameAndName_to_course(code, users->get_currentuser_usernameAndName());
	std::cout << "You are enrolled in the course";

}

void StudentView::SubListCourses()
{
	auto userCourses = courses->getUserCourses(users->GetCurrentUser());

	std::cout << "Choose the ith  [1" << userCourses.size()  << "] Course to view\n";
	int choice = ReadInt(1, (int)userCourses.size() );
	std::string courseDetailedString{};
	std::cout << userCourses[choice - 1].all_info_student_string(users->get_currentuser_username()) << endl;


}

void StudentView::Unregister(Course const& course)
{
	//users->Unregister(course_id, student);
	//courses->RemoveStudent(student.getId(), course_id);
}

void StudentView::ViewCourses()
{
	//std::cout<<"Choose the ith [1"<<
	std::cout << "Your Courses List:\n";
	auto userCourses = courses->getUserCourses(users->GetCurrentUser());
	int i = 0;
	for (const auto& course : userCourses)
		std::cout << ++i << " -)" << course.OverviewString() << std::endl;
	std::cout << "choose the ith course or 0 to cancel\n";
	int courseChoice = ReadInt(0, (int)userCourses.size())-1;
	if (courseChoice < 0)
		return; 
	std::cout << userCourses[courseChoice].doc_and_assignment_string(users->get_currentuser_username());
	std::cout << "Choose the ith Assignment or 0 to cancel\n";

	int assignmentChoice = ReadInt(0, (int)userCourses[courseChoice].get_courseAssignments_number())-1;
	if (assignmentChoice < 0)
		return;

	auto userAssignments = userCourses[courseChoice].get_user_assignments(users->get_currentuser_username());
	auto chosenAssignment = userAssignments[assignmentChoice];

	//users->
}
