#pragma once
#include "Topic.h"
#include "NetworkUserOperations.h"

class TopicOperations {

private:
	friend class PostOperations;
	friend class SocialNetwork;

	Vector<Topic> topics;
	Topic* openedT;

	NetworkUserOperations* userOp;

public:
	TopicOperations(NetworkUserOperations&);

	TopicOperations(const TopicOperations&) = delete;
	TopicOperations& operator=(const TopicOperations&) = delete;

	void search(const String&) const;

	void create();

	void open(const String&);
	void open(unsigned);

	void quit();

	unsigned getTopicIndex(unsigned);
	void about(unsigned);

	bool checkIfTopicIdExists(unsigned) const;
	bool checkIfTopicNameExists(const String&) const ;
};

