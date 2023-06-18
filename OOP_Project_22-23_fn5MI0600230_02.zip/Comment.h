#pragma once
#include "NetworkUser.h"
#include "Vector.hpp"
#include "Constants.h"

class Comment {

private:
	friend class SocialNetwork;
	friend class PostOperations;

	const NetworkUser* user;
	unsigned creatorInd;
	String content;
	unsigned id;
	Vector<Comment> replies;
	int countUpV;
	int countDownV;

public:
	Comment();
	Comment(const NetworkUser&, const String&);
	Comment(const NetworkUser&, const String&, unsigned, Vector<Comment>);

	unsigned getId() const;

	friend std::istream& operator>>(std::istream&, Comment&);
	friend std::ostream& operator<<(std::ostream&, const Comment&);
};
std::istream& operator>>(std::istream&, Comment&);
std::ostream& operator<<(std::ostream&, const Comment&);
