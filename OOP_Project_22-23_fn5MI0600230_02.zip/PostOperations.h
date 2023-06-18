#pragma once
#include "Post.h"
#include "TopicOperations.h"
#include "Queue.hpp"


class PostOperations {

private:
	Post* openedP;
	TopicOperations* topicOp;
	NetworkUserOperations* userOp;

public:
	PostOperations(TopicOperations&, NetworkUserOperations&);

	PostOperations(const PostOperations&) = delete;
	PostOperations& operator=(const PostOperations&) = delete;

	friend class SocialNetwork;
	friend class TopicOperations;

	void list() const;
	void post();

	void p_open(const String&);
	void p_open(unsigned);

	void comment();

	void printComment(const Comment& comment, int indentLevel);
	void comments();

	bool searchComment_AndUpVote(unsigned id, Comment& toSearch);
	void upvote(unsigned);
	bool searchComment_AndDownVote(unsigned id, Comment& toSearch);
	void downvote(unsigned);

	bool searchComment(unsigned id, Comment& toSearch, const Comment& _reply);
	void reply(unsigned);

	void p_close();
};

