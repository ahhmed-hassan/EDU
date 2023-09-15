#include "EducationSystem.h"
EducationSystem::EducationSystem() :
	user_manager(std::make_unique<UserManager>()),
	course_manager(std::make_unique<CourseManager>()) {}

void EducationSystem::LoadDataBase()
{
	user_manager->LoadDataBase();
	//course_manager->LoadDataBasee();
}
void EducationSystem::MakeView(bool isDoctor)
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

	MakeView(user_manager->GetCurrentUser().isDoctor());

	std::visit(var_visitor(), view);

	
}
