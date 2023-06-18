#pragma once
#include "String.h"
#include "Vector.hpp"
#include "Comment.h"
#include "Constants.h"

class Post {

private:
	friend class SocialNetwork;
	friend class PostOperations;

	String name;
	String content;
	unsigned id = 0;
	Vector<Comment> comments;
	unsigned p_counter = 0;

public:
	Post();
	Post(const String&, const String&);
	Post(const String&, const String&, const Vector<Comment>&, unsigned);

	void setName(const String&);
	void setContent(const String&);

	const String& getName() const;
	const String& getContent() const;
	Vector<Comment> getComments() const;
	unsigned getId() const;

	friend std::istream& operator>>(std::istream&, Post&);
	friend std::ostream& operator<<(std::ostream&, const Post&);
};
std::istream& operator>>(std::istream&, Post&);
std::ostream& operator<<(std::ostream&, const Post&);
