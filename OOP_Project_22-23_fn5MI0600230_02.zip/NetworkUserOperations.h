#pragma once
#include <fstream>
#include "NetworkUser.h"
#include "Vector.hpp"

class NetworkUserOperations {

private:
	friend class TopicOperations;
	friend class SocialNetwork;
	friend class PostOperations;

	Vector<NetworkUser> users;
	NetworkUser* logged;

	static unsigned counter;

public:
	bool userExists(const String&, const String&) const;

	bool signup();
	bool login();
	void logout();

	unsigned getUserIndex() const;

	void whoami();

	bool alreadyUpVoted(unsigned id)const;
	bool alreadyDownVoted(unsigned id) const;
};

