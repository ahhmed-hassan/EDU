#include "User.h"
#include <sstream>
#include <assert.h>

User::User() = default;
User::User(json const& jsonUser):
	is_doctor(jsonUser["isDoctor"]),
	username(jsonUser["userName"]),
	name(jsonUser["name"]),
	password(jsonUser["password"])
	
{
	for (const auto& code : jsonUser["coursesCodes"])
		coursesCodes.push_back(code);
}
void User::set_username(std::string_view x) {
	username=x;
}

void User::set_password(std::string_view x) {
	password = x;
}

void User::set_name(std::string_view x) {
	name = x;
}

void User::set_doctor() {
	is_doctor = true;
}

std::string const& User::get_username()const {
	return username;
}

void User::read_user(std::string_view str) {
	set_username(std::string(str));
	std::string x;
	std::cout << "Enter a name: "; std::cin >> x; name = x;
	std::cout << "\nEnter a password: "; std::cin >> x; password = x;
	std::cout << "\n non zero for doctor: "; int i; std::cin >> i;
	if (i)
		set_doctor();
}

std::string User::to_string()const {
	std::ostringstream oss{};
	oss << username << "," << name << "," << password << "," << is_doctor;
	return oss.str();
}

bool User::is_my_password(std::string_view pass) {
	return password == pass;
}

bool User::operator==(const User& user) {
	return user.username == username;
	}


const bool User:: isDoctor() const
{
	return is_doctor;
}

const std::vector<std::string>& User::get_courses()const
{
	return coursesCodes;
}

bool User::is_enrolled_at_course(std::string_view courseCode) const
{
	return std::ranges::find(coursesCodes, courseCode) != std::end(coursesCodes);
}

void User::unregister_from_course(std::string_view courseCode)
{
	auto erasedCourses = std::erase_if(coursesCodes, [&](const std::string& code) {return code == courseCode; });
	assert(erasedCourses > 0);
}

void User::register_in_course(std::string_view courseCode)
{
	assert(std::ranges::find(coursesCodes,courseCode) == coursesCodes.end());
	coursesCodes.emplace_back(std::string(courseCode));
}

std::string User::get_name() const
{
	return name;
}

json User::get_json() const
{
	json res{};
	res["isDoctor"] = is_doctor;
	res["userName"] = username; 
	res["name"] = name; 
	res["coursesCodes"] = coursesCodes;
	res["password"] = password;
	return res; 
}
