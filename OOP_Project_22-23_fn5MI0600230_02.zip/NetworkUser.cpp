#include "NetworkUser.h"

NetworkUser::NetworkUser() :fName(""), lName(""), pass(""), id(0), points(0) {};

NetworkUser::NetworkUser(const String& fName, const String& lName, const String& pass, unsigned id, unsigned points) :
						fName(fName), lName(lName), pass(pass), id(id), points(points) {};

std::istream& operator>>(std::istream& is, NetworkUser& us) {
	std::cout << ENTER_FIRST_NAME;
	is >> us.fName;

	std::cout << std::endl;
	std::cout << ENTER_LAST_NAME;
	is >> us.lName;

	std::cout << std::endl;
	std::cout << ENTER_PASS;
	is >> us.pass;

	return is;
}
std::ostream& operator<<(std::ostream& os, const NetworkUser& us) {
	os << FIRST_NAME << us.fName << std::endl;
	os << LAST_NAME << us.lName << std::endl;
	os << POINTS << us.points << std::endl;
	return os;
}