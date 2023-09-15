#pragma once
#include<iostream>
#include<vector>
#include <string_view>
class User
{
protected:
	//int id{};
	bool is_doctor{};
	std::string username{};
	std::string password{};
	std::string name{};
	std::vector<std::string> coursesCodes{};
public:
	User();
	User(std::string line);

	void set_username(std::string_view x);

	void set_password(std::string_view x);

	void set_name(std::string_view x);

	//void set_id(int);
	void set_doctor();

	std::string const& get_username()const;

	std::string to_string() const; 

	void read_user(std::string_view str /*, int id*/);

	bool operator==( User const& user);

	bool is_my_password(std::string_view pass); 

	const bool isDoctor()const;

	const std::vector<std::string>& get_courses()const;

	bool is_enrolled_at_course(std::string_view courseId) const;

	void Unregister(int course_id);

	void register_in_course(std::string_view courseCode);

	std::string get_name() const;

	//int getId() const;
};

