#include "DoctorView.h"

DoctorView::DoctorView(CourseManagerPtr cManger, UserManagerPtr uManger) :
	courses(cManger), users(uManger) {}

void DoctorView::Display() {
	while(true)
	{
		int choice{ ShowReadMenu({"List Courses", "Add Courses", "View Courses", "LogOut"}) };
		switch (choice)
		{
		case 1:
		{
			ListCourses(); break;
		}
		case 2:
		{
			AddCourses(); break;
		}
		case 3:
		{
			ViewCourses(); break;
		}
		case 4:
		{
			LogOut(); return;
		}
		default:
			return;
		}
	}
}
void DoctorView:: LogOut(){}
void DoctorView:: ListCourses(){}
void DoctorView:: ViewCourses()
{
	
	while(true)
	{
		//should it be put here or before the while loop?
		auto const& courses_objects = courses->getUserCourses(users->GetCurrentUser());
		int i = 1;
		for (const auto& course : courses_objects)
		{
			cout << i << "- " << course.OverviewString() << "\n";
		}
		std::cout << "choose course num or 0 to go back\n";
		int courseChoice = ReadInt(0, (int)courses_objects.size()) - 1;

		if (courseChoice < 0)
			return;

		int choice2 = ShowReadMenu({ "Create Assignment", "Show Assignment","Back" });
		switch (choice2)
		{
		case 1:
			ShowAssigments(courses_objects[courseChoice]);
			return ViewCourses();
		case 2:
			AddAssignment(courses_objects[courseChoice]);
			return ViewCourses();
		default:
			break;
		}
	}


}
void DoctorView::ShowAssigments(Course const & course)
{
	while(true)
	{
		const auto& assignments = course.get_assignments();
		int i = 0;
		for (const auto& assignemnt : assignments)
		{
			std::cout << ++i << "- " << assignemnt.doctor_Overview() << std::endl;
		}
		std::cout << "Choose the ith Assignment [1-" << assignments.size() << "]\n";
		std::cout << "or 0 to go back";
		int choice = ReadInt(0, (int)assignments.size() - 1) - 1;

		if (choice < 0)
			return;

		return assignment_subList_from_course(course, choice);
	}


}

void DoctorView::AddAssignment(Course course)
{
	assert(users->GetCurrentUser().isDoctor());
	std::string assigmentContent; 
	std::cout << "Please enter your new assigment\n";
	std::getline(std::cin, assigmentContent);
	std::cout << "What is the total points of this assigment?\n"; int points; cin >> points;

	auto studentnamesEnrolledAtThisCourse = users->get_students_names_enrolled_at_course(course);
	courses->addAssignemntToCourse(course, assigmentContent, points,users->GetCurrentUser().get_name(),studentnamesEnrolledAtThisCourse);
}

void DoctorView::assignment_subList_from_course(Course const& course, int choice)
{
	while (true)
	{
		const auto& assignments = course.get_assignments();
	
		std::cout << assignments[choice - 1].doctor_detailed_view()<<endl;
	
		int assignmentMenuChoice = ShowReadMenu({ "Add Feedback","Add Degree","Return" });
		std::string actionContent;
	
			switch (assignmentMenuChoice)
			{
			case 1:
			{
				std::cout << "Enter your Feedback: \n"; cin >> actionContent;

				break;
			}
			case 2:
			{
				std::cout << "Enter your Degree: \n"; cin >> actionContent;
				break;
			}

			default:
				return;
			}
			courses->make_enum_based_action_on_course_assignment(course,assignments[choice - 1], actionContent, AssignmentAction::addFeedback);
	}

}
void DoctorView:: AddCourses(){}
//Userless comment