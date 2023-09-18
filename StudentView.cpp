#include "StudentView.h"
StudentView::StudentView(CourseManagerPtr cManger, UserManagerPtr uManger):
	courses(cManger), users(uManger){}

StudentView::StudentView(StudentView&& another) noexcept
{
	courses=std::move(another.courses);
	users = std::move(another.users);
}

void StudentView::CourseChoices(Course* course)
{
	int choice = ShowReadMenu({ "Unregister from course","Submit Solution", "Back" });
	switch (choice)
	{
	case 1:

	default:
		break;
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
	courses->add_course_assignments_for_new_student(code, users->get_currentuser_usernameAndName());
	std::cout << "You are enrolled in the course";

}

void StudentView::SubListCourses()
{
	auto userCourses = courses->getUserCourses(users->GetCurrentUser());

	std::cout << "Choose the ith  [1" << userCourses.size()  << "] Course to view\n";
	int choice = ReadInt(1, (int)userCourses.size() );
	std::string courseDetailedString{};
	std::cout << userCourses[choice - 1].StudentDetailedString(users->get_currentuser_username()) << endl;


}

void StudentView::Unregister(int course_id, User& student)
{
	//users->Unregister(course_id, student);
	//courses->RemoveStudent(student.getId(), course_id);
}

void StudentView::ViewCourses()
{
	//std::cout<<"Choose the ith [1"<<
	std::cout << "My Courses List:\n";
	//users->
}
