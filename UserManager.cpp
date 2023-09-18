#include "UserManager.h"
#include <assert.h>
UserManager::UserManager():current_user(username_to_user["ahmed"]) {
	last_id = 0; 
}
void UserManager::LoadDataBase()
{

}

void UserManager::Access_system() {
	int choice = ShowReadMenu({ "Log In", "Sign up" ,"Shut Down"});
	switch (choice) {
	case 1:
	{Login(); break; }
	case 2:
	{Signup(); break; }
	case 3: 
	{ break; }
	default:
		break;
	}

}
void UserManager::Login() {
	while (true) {
		std::string x, y; 
		cout << "Enter username and password\n"; 
		std::cin >> x; cin >> y;
		if (not username_to_user.count(x) or not username_to_user[x].is_my_password(y)) {
			std::cout << "Invalid username oor password\n"; continue;
		}
		current_user = username_to_user[x]; break;
}
	
}
void UserManager::Signup() {

	string x{};

	cout << "Enter a username\n"; cin >> x;
	while (username_to_user.find(x) != username_to_user.end())
	{
		cout << "Already taken, Please try another username\n";
		cout << "Enter a username\n"; cin >> x;
	}

	current_user.get().read_user(x);

	//username_to_user[current_user.get_username()] = std::make_unique<User>(current_user);
	username_to_user[current_user.get().get_username()] = current_user;
	UpdateDataBase(current_user);
}
void UserManager::UpdateDataBase(const User& user) {
	std::string line = user.to_string();
	WriteFileLines("users.txt", {line});
}

const User& UserManager:: GetCurrentUser() const
{
	return current_user;
}

vector<std::string> UserManager::GetCurrentUserCourses() const
{
	return GetCurrentUser().get_courses();
}

void UserManager::register_in_course(std::string_view courseCode)
{
	assert(not current_user.get().isDoctor());
	current_user.get().register_in_course(courseCode);
}

std::string UserManager::get_current_user_username() const
{
	return GetCurrentUser().get_username();
}

std::string UserManager::get_current_username() const
{
	return GetCurrentUser().get_name(); 
}

json UserManager::get_json() const
{
	json res{};
	for (const auto& [userName, user] : username_to_user)
		res.push_back(user.get_json());
	return res; 

}

vector<std::string> const& UserManager::get_students_names_enrolled_at_course(Course const& course) const
{
	// TODO: insert return statement here
	auto courseCode = course.get_code(); 

	auto usersEnrolledAtCourse = username_to_user | views::values |
		views::filter([&courseCode](const User& user) {return user.isDoctor() and user.is_enrolled_at_course(courseCode); })
		| views::transform([](const User& user) {return user.get_name(); });

	return vector<std::string>(usersEnrolledAtCourse.begin(), usersEnrolledAtCourse.end());
}

bool UserManager::is_current_user_doctor() const
{
	return GetCurrentUser().isDoctor();
}

