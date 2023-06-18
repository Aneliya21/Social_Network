#include "NetworkUserOperations.h"

unsigned NetworkUserOperations::counter = 0;

bool NetworkUserOperations::userExists(const String& name, const String& pass) const {
	for (unsigned i = 0; i < users.getSize(); i++)
		if (users[i].fName == name && users[i].pass == pass) { return true; }
	return false;
}

bool NetworkUserOperations::signup() {
	NetworkUser user;
	std::cin >> user;
	user.id = counter++;
	if (!userExists(user.fName, user.pass)) {
		users.pushBack(user);
		std::cout << std::endl;
		std::cout << "YOU SUCCESSFULLY CREATED YOUR ACCOUNT! " << std::endl;
		std::cout << std::endl;
		std::cout << "< Now if you want to use it, please login. >" << std::endl;
		return true;
	}
	return false;
}
bool NetworkUserOperations::login() {
	String name, pass;
	std::cout << ENTER_FIRST_NAME;
	std::cin >> name;
	std::cout << std::endl;
	std::cout << ENTER_PASS;
	std::cin >> pass;

	if (userExists(name, pass)) {
		for (unsigned i = 0; i < users.getSize(); i++) {
			if (users[i].fName == name && users[i].pass == pass) {
				logged = &users[i];
				std::cout << std::endl;
				std::cout << "Welcome, " << users[i].fName << "!" << std::endl;
				return true;
			}
		}
	}
	std::cout << std::endl;
	std::cout << NOT_EXISTING_ACCOUNT;
	std::cout << std::endl;
	return false;
}
void NetworkUserOperations::logout() {
	logged = nullptr;
	std::cout << "You logged out! " << std::endl;;
}

unsigned NetworkUserOperations::getUserIndex() const {
	for (unsigned i = 0; i < users.getSize(); i++) {
		if (&users[i] == logged) {
			return i;
		}
	}
	return -1;
}
void NetworkUserOperations::whoami() {
	if (logged != nullptr) {
		std::cout << *(logged);
		return;
	}
	std::cout << WHOAMI_ERROR << std::endl;
}

bool NetworkUserOperations::alreadyUpVoted(unsigned id) const {
	for (unsigned i = 0; i < logged->upVoted.getSize(); i++) {
		if (logged->upVoted[i] == id) {
			return true;
		}
	}
	return false;
}

bool NetworkUserOperations::alreadyDownVoted(unsigned id) const {
	for (unsigned i = 0; i < logged->downVoted.getSize(); i++) {
		if (logged->downVoted[i] == id) {
			return true;
		}
	}
	return false;
}
