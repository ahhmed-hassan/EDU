#pragma once
#include<iostream>
#include<vector>
#include <string_view>
#include "nlohman/json.hpp"
using json = nlohmann::json;
class User
{
protected:
	
	bool is_doctor{};
	std::string username{};
	std::string password{};
	std::string name{};
	std::vector<std::string> coursesCodes{};
public:
	User();
	User(json const& jsonUser);

	void set_username(std::string_view x);

	void set_password(std::string_view x);

	void set_name(std::string_view x);

	
	void set_doctor();

	std::string const& get_username()const;

	std::string to_string() const; 

	void read_user(std::string_view str /*, int id*/);

	bool operator==( User const& user);

	bool is_my_password(std::string_view pass); 

	const bool isDoctor()const;

	const std::vector<std::string>& get_courses()const;

	bool is_enrolled_at_course(std::string_view courseId) const;

	void unregister_from_course(std::string_view courseCode);

	void register_in_course(std::string_view courseCode);

	std::string get_name() const;

	json get_json() const;

	
};

