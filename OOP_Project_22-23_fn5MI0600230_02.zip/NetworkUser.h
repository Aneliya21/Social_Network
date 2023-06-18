#pragma once
#include "String.h"
#include "Constants.h"
#include "Vector.hpp"

class NetworkUser {

private:
	friend class SocialNetwork;
	friend class NetworkUserOperations;
	friend class PostOperations;

	String fName;
	String lName;
	String pass;
	unsigned id;
	unsigned points;
	Vector<int> upVoted;
	Vector<int> downVoted;

public:
	NetworkUser();
	NetworkUser(const String&, const String&, const String&, unsigned, unsigned);

	friend std::istream& operator>>(std::istream&, NetworkUser&);
	friend std::ostream& operator<<(std::ostream&, const NetworkUser&);
};
std::istream& operator>>(std::istream&, NetworkUser&);
std::ostream& operator<<(std::ostream&, const NetworkUser&);