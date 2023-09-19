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
		auto const& doctorCourses = courses->getUserCourses(users->GetCurrentUser());
		int i = 1;
		for (const auto& course : doctorCourses)
		{
			cout << i << "- " << course.OverviewString() << "\n";
		}
		std::cout << "choose course num or 0 to go back\n";
		int courseChoice = ReadInt(0, (int)doctorCourses.size()) - 1;

		if (courseChoice < 0)
			return;

		int choice2 = ShowReadMenu({ "Create Assignment", "Show Assignment","Back" });
		switch (choice2)
		{
		case 1:
			ShowAssigments(doctorCourses[courseChoice]);
			return ViewCourses();
		case 2:
			AddAssignment(doctorCourses[courseChoice]);
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
	//	const auto& assignments = course.get_assignments();
		auto courseAssignments = course.get_course_assignments();
		//auto assignmentContents = course.get_assignments_contents();
		int j = 0; 
		for (const auto& courseAssignment : courseAssignments)
			std::cout << ++j << "- Assignment has content: " << courseAssignment.get_content() << "\n";
	
		std::cout << "Choose the ith Assignment [1-" << courseAssignments.size() << "]\n";
		std::cout << "or 0 to go back";
		int choice = ReadInt(0, (int)courseAssignments.size() - 1) - 1;

		if (choice < 0)
			return;

		return course_assignment_subList_from_course(course, courseAssignments[choice]);
	}


}

void DoctorView::AddAssignment(Course course)
{
	assert(users->GetCurrentUser().isDoctor());
	std::string assigmentContent; 
	std::cout << "Please enter your new assigment\n";
	std::getline(std::cin, assigmentContent);
	std::cout << "What is the total points of this assigment?\n"; int points; cin >> points;

	
	courses->addAssignemntToCourse(course, assigmentContent, points);
	std::cout << "You have added a new Assignment!\n";
}

void DoctorView::course_assignment_subList_from_course(Course const& course, CourseAssignment const& courseAssingment)
{
	while (true)
	{
		//const auto& assignments = course.get_assignments();
		const auto assignments = courseAssingment.get_assignments();
		//const auto& assignmentss = course.get_assignments(choice);
		int count = 0;
		for (const auto& assignment : assignments)
			std::cout <<++count<<"- "<< assignment.doctor_Overview() << "\n";

		std::cout << "choose the ith assignment or 0 to cancel";
		int assignmentChoice = ReadInt(0, (int)assignments.size()) -1;
		if (assignmentChoice < 0)
			return;
		return assignment_sublist(course, assignments[assignmentChoice]);

		//std::cout << assignments[choice - 1].doctor_detailed_view()<<endl;
	
	}

}
void DoctorView::assignment_sublist(Course const& course, Assignment const& assignment)
{
	while (true)
	{
		int assignmentMenuChoice = ShowReadMenu({ "Add Feedback","Add Degree","Return" });
		std::string actionContent;

		switch (assignmentMenuChoice)
		{
		case 1:
		{
			std::cout << "Enter your Feedback: \n"; cin >> actionContent;
			courses->make_enum_based_action_on_course_assignment(course,assignment, actionContent, AssignmentAction::addFeedback);

			break;
		}
		case 2:
		{
			std::cout << "Enter your Degree: \n"; cin >> actionContent;
			courses->make_enum_based_action_on_course_assignment(course,assignment, actionContent, AssignmentAction::addDegree);

			break;
		}

		default:
			return;
		}
		//courses->make_enum_based_action_on_course_assignment(course, assignment, actionContent, AssignmentAction::addFeedback);

	}
}
void DoctorView:: AddCourses()
{
	assert(users->is_current_user_doctor());
	std::cout << "What is the course name?\n"; std::string courseName{}; std::cin >> courseName; 
	std::cout << "What is the course code?\n"; std::string courseCode{}; std::cin >> courseCode; 
	while (not courses->is_course_code_available(courseCode))
	{
		std::cout << "This code is already taken please chose another course code\n"; std::cin >> courseCode; 
	}
	std::string docUsername = users->get_currentuser_username();
	std::string docName = users->get_currentuser_name();
	courses->add_course(courseCode, courseName, docName, docUsername);
	std::cout << "You have added a new course ! \n"; 

}
//Userless comment