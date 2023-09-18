#pragma once
#include "User.h"
#include "Course.h"
#include<map>
#include "Helpers.h"
#include<memory>
#include <functional>
#include <ranges>

using UserRef = std::reference_wrapper<User>;
using UserPtr = std::shared_ptr<User>;
//using UniqueUserPtr = std::unique_ptr<User>;
class UserManager
{
private:
	std::map<std::string, User> username_to_user{};
	UserRef current_user;
	int last_id{};
public:
	UserManager();
	UserManager(json const& jsonUsers);
	void Access_system();
	void Login(); 
	void Signup();
	void LoadDataBase(); 
	void UpdateDataBase(const User& user);
	void Unregister(int course_id, User& user);
	const User& GetCurrentUser() const;
	void register_in_course(std::string_view courseCode);
	std::string get_currentuser_username() const; 
	std::string get_currentuser_name() const; 
	UsernameAndName get_currentuser_usernameAndName() const;
	json get_json() const; 

	vector<std::string> GetCurrentUserCourses() const; 
	vector<std::string>const& get_students_names_enrolled_at_course(Course const& course) const;
	bool is_current_user_doctor() const; 
	//virtual void Display() = 0;
};

