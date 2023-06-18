#include "Topic.h"

Topic::Topic() :name(""),  content("") {};

Topic::Topic(const String& name, const NetworkUser& creator, const String& content) : name(name), creator(&creator), content(content), id(0) {};

Topic::Topic(const String& name, const NetworkUser& creator, const String& content, Vector<Post> posts, unsigned id): 
				name(name), creator(&creator), content(content), posts(posts), id(id) {}

void Topic::setName(const String& name) {
	this->name = name;
}
void Topic::setCreator(const NetworkUser& creator) {
	this->creator = &creator;
}
void Topic::setContent(const String& content) {
	this->content = content;
}
void Topic::setId(unsigned id) {
	this->id = id;
}

const String& Topic:: getName()const {
	return name;
}
unsigned Topic::getId() const {
	return id;
}
Vector<Post> Topic::getPosts() {
	return posts;
}

std::istream& operator>>(std::istream& is, Topic& topic) {
	std::cout << ENTER_TOPIC_NAME;
	is >> topic.name;

	std::cout << std::endl;
	std::cout << ENTER_TOPIC_CONTENT;
	is >> topic.content;

	return is;
}
std::ostream& operator<<(std::ostream& os, const Topic& topic) {
	os << TOPIC_NAME << topic.name;
	os << std::endl;

	os << TOPIC_CREATOR;
	os << std::endl;
	os << *(topic.creator);
	os << std::endl;

	os << TOPIC_CONTENT << topic.content;
	os << std::endl;

	os << TOPIC_POSTS << topic.posts.getSize();
	os << std::endl;

	return os;
}

bool Topic::checkIfPostIdExists(unsigned id) const {
	for (unsigned i = 0; i < posts.getSize(); i++) {
		if (posts[i].getId() == id) {
			return true;
		}
	}
	return false;
}
bool Topic::checkIfPOstNameExists(const String& name) const {
	for (unsigned i = 0; i < posts.getSize(); i++) {
		if (posts[i].getName() == name) {
			return true;
		}
	}
	return false;
}