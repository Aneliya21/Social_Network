#pragma once
#include "NetworkUser.h"
#include "Post.h"
#include "Vector.hpp"
#include "Constants.h"

class Topic {

public:
	friend class SocialNetwork;
	friend class TopicOperations;

	String name;
	const NetworkUser* creator = nullptr;
	unsigned creatorIndex = 0;
	String content;
	unsigned id ;
	Vector<Post> posts;
	unsigned p_counter;

public:
	Topic();
	Topic(const String&, const NetworkUser&, const String&);
	Topic(const String&, const NetworkUser&, const String&, Vector<Post>, unsigned);

	void setName(const String&);
	void setCreator(const NetworkUser&);
	void setContent(const String&);

	const String& getName()const;
	void setId(unsigned id);
	unsigned getId() const;
	
	Vector<Post> getPosts();

	friend std::istream& operator>>(std::istream&, Topic&);
	friend std::ostream& operator<<(std::ostream&, const Topic&);

	bool checkIfPostIdExists(unsigned) const;
	bool checkIfPOstNameExists(const String&) const;
};
std::istream& operator>>(std::istream&, Topic&);
std::ostream& operator<<(std::ostream&, const Topic&);
