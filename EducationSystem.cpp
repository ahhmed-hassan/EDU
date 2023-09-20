#include "EducationSystem.h"
EducationSystem::EducationSystem() :
	user_manager(std::make_shared<UserManager>()),
	course_manager(std::make_shared<CourseManager>()) {}

void EducationSystem::LoadDataBase()
{
	user_manager->load_database();
	//course_manager->load_database();
	//course_manager->LoadDataBasee();
}
void EducationSystem::init_view(bool isDoctor)
{

	if (isDoctor)
	{
		view.emplace<2>(DoctorView{ course_manager,user_manager });
	}
	else
	{
		view.emplace<1>( StudentView{ course_manager,user_manager });
	}
	
}

void EducationSystem::Run()
{
	
	while(user_manager->Access_system())

	{
		init_view(user_manager->is_current_user_doctor());

		std::visit(var_visitor(), view);
	}

	
}
