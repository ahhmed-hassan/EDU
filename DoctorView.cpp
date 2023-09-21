#include "DoctorView.h"

DoctorView::DoctorView(CourseManagerPtr cManger, UserManagerPtr uManger) :
	courses(cManger), users(uManger) {}

void DoctorView::Display() {
	while(true)
	{
		int choice{ show_read_menu({"List Courses", "Add Courses", "View Courses", "LogOut"}) };
		switch (choice)
		{
		case 1:
		{
			list_courses(); break;
		}
		case 2:
		{
			add_courses(); break;
		}
		case 3:
		{
			view_courses(); break;
		}
		case 4:
		{
			log_out(); return;
		}
		default:
			return;
		}
	}
}
void DoctorView:: log_out()
{
	users->save_data_to_json();
	courses->save_data_to_json();
}
void DoctorView:: list_courses()
{
	std::string_view header = "System Courses", fallBack = "No Courses yet";
	show_read_menu(courses->get_all_courses_overview(), header, fallBack, false, false);
}

void DoctorView:: view_courses()
{
	
	while(true)
	{
		//should it be put here or before the while loop?
		auto const& doctorCourses = courses->get_user_courses(users->get_current_user());
	
		auto doctorCoursesOverviews = doctorCourses |
			std::views::transform([](const Course& course) {return course.overview_string(); });
		
		std::string_view header = "Your Courses are: ", backUp = "You have no Courses";
		int courseChoice= show_read_menu(to_vector(doctorCoursesOverviews), header,backUp, true, true) - 1;
		/*int i = 1;
		for (const auto& course : doctorCourses)
		{
			cout << i << "- " << course.overview_string() << "\n";
		}
		std::cout << "choose course num or 0 to go back\n";
		int courseChoice = read_int(0, (int)doctorCourses.size()) - 1;*/

		if (courseChoice ==-1)
			return;

		int choice2 = show_read_menu({ "Create Assignment", "Show Assignment","Back" });
		switch (choice2)
		{
		case 1:
			add_assignment(doctorCourses[courseChoice]);
			break;
		case 2:
			show_assignments(doctorCourses[courseChoice]);
			break;
		default:
			return;
		}
	}


}
void DoctorView::show_assignments(Course const & course)
{
	while(true)
	{
	
		auto courseAssignments = course.get_course_assignments();
		auto courseAssignmentsContents = courseAssignments | 
			std::views::transform([](const CourseAssignment& ass) {return ass.get_content(); });

		std::string_view header = "Assignment contents of this course: ", backUp = "There's no Assignments for this course";
		int choice = show_read_menu(to_vector(courseAssignmentsContents), header, backUp, true, true)-1;

		if (choice ==-1)
			return;

		return course_assignment_subList_from_course(course, courseAssignments[choice]);
	}


}

void DoctorView::add_assignment(Course course)
{
	assert(users->is_current_user_doctor());
	std::string assigmentContent,dummy; int points;
	std::cout << "Please enter your new assigment\n";
	std::getline(std::cin, assigmentContent);
	std::getline(std::cin, assigmentContent);
	std::cout << "What is the total points of this assigment?\n";  cin >> points;

	
	courses->add_assignment_to_course(course, assigmentContent, points);
	std::cout << "You have added a new Assignment!\n";
}

void DoctorView::course_assignment_subList_from_course(Course const& course, CourseAssignment const& courseAssingment)
{
	while (true)
	{
		
		const auto assignments = courseAssingment.get_assignments();
		
		auto assignmentsDoctoroverviews = assignments |
			std::views::filter([](const Assignment& ass) {return ass.is_submitted(); }) |
			std::views::transform([](const Assignment& ass) {return ass.doctor_Overview(); });
			

		std::string_view title{"All Assignments overview fot this assignment: "}, backUp = "No submitted Assignments yet";
		int assignmentChoice = show_read_menu(to_vector(assignmentsDoctoroverviews), title, backUp, true, true)-1;

		if (assignmentChoice == -1)
			return; 

		return assignment_sublist(course, assignments[assignmentChoice]);

	
	}

}
void DoctorView::assignment_sublist(Course const& course, Assignment const& assignment)
{
	std::cout << assignment.doctor_detailed_view() << "\n";
	while (true)
	{
		
		int assignmentMenuChoice = show_read_menu({ "Add Feedback","Add Degree","Return" });
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
			while(std::stoi(actionContent)>assignment.get_total())
			{
				"Degree is bigger than the maximum possible points please try again\n"; std::cin >> actionContent;
			}
			courses->make_enum_based_action_on_course_assignment(course,assignment, actionContent, AssignmentAction::addDegree);

			break;
		}

		default:
			return;
		}
		

	}
}
void DoctorView:: add_courses()
{
	assert(users->is_current_user_doctor());
	std::cout << "What is the course name?\n"; std::string courseName{}; std::cin >> courseName; 
	std::cout << "What is the course code?\n"; std::string courseCode{}; std::cin >> courseCode; 
	while (not courses->is_course_code_available(courseCode))
	{
		std::cout << "This code is already taken please chose another course code\n"; std::cin >> courseCode; 
	}
	auto [docUsername,docName] = users->get_currentuser_usernameAndName();
	courses->add_course(courseCode, courseName,users->get_currentuser_usernameAndName());
	users->register_in_course(courseCode);
	std::cout << "You have added a new course ! \n"; 

}
//Userless comment