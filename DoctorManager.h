#pragma once
#include "Doctor.h"
#include <map>
using DoctorPtr = std::unique_ptr<Doctor>;
//#include <string>
class DoctorManager
{
private:
	std::map<std::string, DoctorPtr> username_to_doctor{};
	Doctor current_doc {}; 

};