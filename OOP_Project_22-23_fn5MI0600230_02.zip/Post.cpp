#include "Post.h"


Post::Post() {} ////////////////////////

Post::Post(const String& name, const String& content):name(name), content(content) {}
Post::Post(const String& name, const String& content, const Vector<Comment>& comments, unsigned id) :
			name(name), content(content), comments(comments), id(id) {};

void Post::setName(const String& name) {
	this->name = name;
}
void Post::setContent(const String& content) {
	this->content = content;
}

const String& Post::getName() const {
	return name;
}
const String& Post::getContent() const {
	return content;
}
Vector<Comment> Post::getComments() const {
	return comments;
}
unsigned Post::getId() const {
	return id;
}

std::istream& operator>>(std::istream& is, Post& p) {
	std::cout << ENTER_POST_TITLE;
	is >> p.name;
	std::cout << std::endl;

	std::cout << ENTER_POST_CONTENT;
	is >> p.content;
	std::cout << std::endl;

	return is;
}
std::ostream& operator<<(std::ostream& os, const Post& p) {
	os << p.name;
	os << POST_ID << p.id << CLOSE_BRACK << std::endl;
	return os;
}