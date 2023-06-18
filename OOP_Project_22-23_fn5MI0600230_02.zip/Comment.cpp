#include "Comment.h"

Comment::Comment() :user(), content("") {};

Comment::Comment(const NetworkUser& user, const String& content) : user(&user), content(content) {};

Comment::Comment(const NetworkUser& user, const String& content, unsigned id, Vector<Comment> replies) :
	user(&user), content(content), id(id), replies(replies) {};

unsigned Comment::getId() const {
	return id;
}

std::istream& operator>>(std::istream& is, Comment& comment) {
	is >> comment.content;
	return is;
}
std::ostream& operator<<(std::ostream& os, const Comment& comment) {
	os << comment.content << " {id:" << comment.id << "}, Likes: " << comment.countUpV << ", Dislikes: " << comment.countDownV;
	return os;
}