#pragma once
#include "DoctorView.h"
#include "StudentView.h"
#include "CourseManager.h"

#include <variant>


using VariantView = std::variant<std::monostate,StudentView, DoctorView>;
class EducationSystem
{
private:
	unique_ptr<UserManager> user_manager{};
	unique_ptr <CourseManager> course_manager{};
	VariantView view{};
	struct var_visitor
	{
		void operator() (std::monostate) { throw runtime_error("Accessing before Initializing"); }
		void operator() (DoctorView& doc) { doc.Display(); }
		void operator() (StudentView& doc) { doc.Display(); }
	};
	void LoadDataBase();
	void init_view(bool isDoctor);

public:
	EducationSystem();
	
	void Run();

	
};

