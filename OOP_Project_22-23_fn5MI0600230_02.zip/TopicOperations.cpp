#include "TopicOperations.h"

TopicOperations::TopicOperations(NetworkUserOperations& _userOp) {
	userOp = &_userOp;
}

namespace {
	//Sources: https://github.com/Angeld55/Introduction_to_programming_FMI/blob/main/Sem.%2008/searchInText.cpp

	bool isPrefix(const char* pattern, const char* text)
	{
		while (*text != '\0' && *pattern != '\0')
		{
			if (*text != *pattern)
				return false;
			text++;
			pattern++;
		}
		return *pattern == '\0';
	}
	bool searchInText(const char* text, const char* pattern)
	{
		size_t textLen = strlen(text);
		size_t patternLen = strlen(pattern);
		while (patternLen <= textLen)
		{
			if (isPrefix(pattern, text))
				return true;
			text++;
			textLen--;
		}
		return false;
	}
}
void TopicOperations::search(const String& name) const {
		for (unsigned i = 0; i < topics.getSize(); i++) {
			if (searchInText(topics[i].name.c_str(), name.c_str())) {
				std::cout << "    Topic: " << std::endl;
				std::cout << "    - " << topics[i].name << TOPIC_ID << topics[i].id << CLOSE_BRACK << std::endl;
			}
		}
}

void TopicOperations::create() {
		Topic topic;
		std::cin >> topic;

		topic.setId(userOp->counter++);
		topic.setCreator(*userOp->logged);
		topic.creatorIndex = userOp->getUserIndex();

		topics.pushBack(topic);
}

void TopicOperations::open(const String& name) {
		for (unsigned i = 0; i < topics.getSize(); i++) {
			if (searchInText(topics[i].name.c_str(), name.c_str())) {
				std::cout << OPENED_TOPIC << topics[i].name << std::endl;
				openedT = &topics[i];
				break;
			}
		}
}
void TopicOperations::open(unsigned id) {
		for (unsigned i = 0; i < topics.getSize(); i++) {

			if (topics[i].id == id) {
				std::cout << OPENED_TOPIC << topics[i].name << std::endl;
				openedT = &topics[i];
				break;
			}
		}
}

void TopicOperations::quit() {
	std::cout << "Topic successfully closed! " << std::endl;
	openedT = nullptr;
}

unsigned TopicOperations::getTopicIndex(unsigned ind) {
	for (unsigned i = 0; i < topics.getSize(); i++) {
		if (topics[i].id == ind) {
			return i;
		}
	}
	return -1;
}
void TopicOperations::about(unsigned id) {
	std::cout << topics[getTopicIndex(id)];
}

bool TopicOperations::checkIfTopicIdExists(unsigned id) const {
	for (unsigned i = 0; i < topics.getSize(); i++) {
		if (topics[i].id == id) {
			return true;
		}
	}
	return false;
}
bool TopicOperations::checkIfTopicNameExists(const String& name) const {
	for (unsigned i = 0; i < topics.getSize(); i++) {
		if (topics[i].name == name) {
			return true;
		}
	}
	return false;
}