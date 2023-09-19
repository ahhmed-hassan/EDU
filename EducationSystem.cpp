#include "EducationSystem.h"
EducationSystem::EducationSystem() :
	user_manager(std::make_unique<UserManager>()),
	course_manager(std::make_unique<CourseManager>()) {}

void EducationSystem::LoadDataBase()
{
	user_manager->LoadDataBase();
	//course_manager->LoadDataBasee();
}
void EducationSystem::init_view(bool isDoctor)
{

	if (isDoctor)
	{
		view.emplace<2>(DoctorView{ std::move(course_manager),std::move(user_manager) });
	}
	else
	{
		view.emplace<1>( StudentView{ std::move(course_manager),std::move(user_manager) });
	}
	
}

void EducationSystem::Run()
{
	LoadDataBase();
	user_manager->Access_system();

	init_view(user_manager->is_current_user_doctor());

	std::visit(var_visitor(), view);

	
}
