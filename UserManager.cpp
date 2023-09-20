#include "UserManager.h"
#include <assert.h>

UserManager::UserManager(std::string const& jsonPath):UserManager(parse_json_from_file(jsonPath))
{
}

UserManager::UserManager(std::optional<json> jsonUsers)
{
	if ( jsonUsers.has_value())
	{
		auto jsonUsersData = jsonUsers.value();
		for (const auto& jsonUser : jsonUsersData)
		{
			User tmpUser(jsonUser);
			auto username = tmpUser.get_username();
			username_to_user.insert({ username, std::move(tmpUser) });
		}
		isDataLoaded = true;
	}
}
void UserManager::load_database(std::string const& jsonPath)
{
	auto usersJson(parse_json_from_file(jsonPath));
	if (not usersJson.has_value())
		return; 
	auto usersJsonData = usersJson.value();
	for (const auto& jsonUser : usersJsonData)
	{
		User tmpUser(jsonUser);
		auto username = tmpUser.get_username();
		username_to_user.insert({ username, std::move(tmpUser) });
	}
}

bool UserManager::Access_system() {
	int choice = show_read_menu({ "Log In", "Sign up" ,"Shut Down"});
	switch (choice) {
	case 1:
	{Login(); return true; ; }
	case 2:
	{Signup(); return true; }
	case 3: 
	{ return false; }
	default:
		return false;
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

	current_user.read_user(x);

	
	username_to_user[get_currentuser_username()] = current_user;
	//UpdateDataBase(current_user);
}
void UserManager::UpdateDataBase(const User& user) {
	std::string line = user.to_string();
	WriteFileLines("users.txt", {line});
}

void UserManager::unregister_student_from_course(User const& student, std::string_view courseCode)
{
	assert(not student.isDoctor());
	username_to_user[student.get_username()].unregister_from_course(courseCode);

}

const User& UserManager:: get_current_user() const
{
	return username_to_user.at(current_user.get_username());
}

vector<std::string> UserManager::GetCurrentUserCourses() const
{
	return get_current_user().get_courses();
}

void UserManager::register_in_course(std::string_view courseCode)
{
	//assert(not is_current_user_doctor());
	username_to_user[get_currentuser_username()].register_in_course(courseCode);
}

std::string UserManager::get_currentuser_username() const
{
	return get_current_user().get_username();
}

std::string UserManager::get_currentuser_name() const
{
	return get_current_user().get_name(); 
}

UsernameAndName UserManager::get_currentuser_usernameAndName() const
{
	return UsernameAndName(get_currentuser_username(), get_currentuser_name());
}

json UserManager::get_json() const
{
	json res{};
	for (const auto& [userName, user] : username_to_user)
		res.push_back(user.get_json());
	return res; 

}

void UserManager::save_data_to_json(std::string const& path) const
{
	auto jsonData = get_json();
	std::ofstream output(path);
	if (not output.is_open())
		throw std::runtime_error("Cannot open the file " + path);
	output << jsonData.dump(4) << std::endl;
	output.close();
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
	return get_current_user().isDoctor();
}

