#include "PostOperations.h"

PostOperations::PostOperations(TopicOperations& _topicOp, NetworkUserOperations& _userOp) {
	topicOp = &_topicOp;
	userOp = &_userOp;
}

void PostOperations::list() const {
	for (unsigned i = 0; i < topicOp->openedT->getPosts().getSize(); i++) {
		std::cout << "   Posts:" << std::endl;
		std::cout << "   >> " << topicOp->openedT->getPosts()[i];
	}
	
}
void PostOperations::post() {

		Post post;
		std::cin >> post;
		post.id = topicOp->openedT->p_counter++;
		topicOp->openedT->posts.pushBack(post);
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
void PostOperations::p_open(const String& name) {

	for (unsigned i = 0; i < topicOp->openedT->getPosts().getSize(); i++) {
		if (searchInText(topicOp->openedT->getPosts()[i].getName().c_str(), name.c_str())) {
			openedP = &(topicOp->openedT->getPosts()[i]);
			std::cout << P_OPEN << topicOp->openedT->getPosts()[i];
			return;
		}
	}
}
void PostOperations::p_open(unsigned id) {
	for (unsigned i = 0; i < topicOp->openedT->getPosts().getSize(); i++) {
		if (topicOp->openedT->getPosts()[i].getId() == id) {
			std::cout << P_OPEN << topicOp->openedT->getPosts()[i];
			openedP = &(topicOp->openedT->posts[i]);
			return;
		}
	}
}

void PostOperations::comment() {
	Comment comment;
	std::cout << COMMENT;
	std::cin >> comment;
	comment.id = openedP->p_counter;
	openedP->p_counter++;
	openedP->comments.pushBack(comment);
	userOp->logged->points++;
}

void PostOperations::printComment(const Comment& comment, int indentLevel) {
	for (int i = 0; i < indentLevel; i++)
		std::cout << "  ";
	
	std::cout << comment << std::endl << std::endl;

	unsigned size = comment.replies.getSize();

	for (unsigned i = 0; i < size; i++) 
		printComment(comment.replies[i], indentLevel + 1);	
}
void PostOperations::comments() {
	unsigned size = openedP->comments.getSize();
	for (unsigned i = 0; i < size; i++) {
		printComment(openedP->comments[i], 0);
	}
	return;
}

bool PostOperations::searchComment_AndUpVote(unsigned id, Comment& toSearch) {
	Queue<Comment*> queue;
	queue.push(&toSearch);

	while (!queue.isEmpty()) {
		Comment* current = queue.peek();
		queue.pop();

		if (current->id == id) {
			if (!userOp->alreadyUpVoted(id) && !userOp->alreadyDownVoted(id)) {
				current->countUpV++;
				userOp->logged->upVoted.pushBack(id);
			}
			else if (userOp->alreadyDownVoted(id)) {
				current->countDownV--;
				for (unsigned i = 0; i < userOp->logged->downVoted.getSize(); i++) {
					if (userOp->logged->downVoted[i] == id);
					userOp->logged->downVoted.popAt(i);
					break;
				}
				current->countUpV++;
				userOp->logged->upVoted.pushBack(id);
			}
			else if (userOp->alreadyUpVoted(id)) {
				current->countUpV--;
				for (unsigned i = 0; i < userOp->logged->upVoted.getSize(); i++) {
					if (userOp->logged->upVoted[i] == id);
					userOp->logged->upVoted.popAt(i);
					break;
				}
			}
			if (current->countUpV < 0) {
				current->countUpV = 0;
			}
			else if (current->countDownV < 0) {
				current->countDownV = 0;
			}

			return true;
		}
		for (size_t i = 0; i < current->replies.getSize(); ++i) {
			queue.push(&(current->replies[i]));
		}
	}
	return false;
}
bool PostOperations::searchComment_AndDownVote(unsigned id, Comment& toSearch) {
	Queue<Comment*> queue;
	queue.push(&toSearch);

	while (!queue.isEmpty()) {
		Comment* current = queue.peek();
		queue.pop();

		if (current->id == id) {
			if (!userOp->alreadyDownVoted(id) && !userOp->alreadyUpVoted(id)) {
				current->countDownV++;
				userOp->logged->downVoted.pushBack(id);
			}
			else if (userOp->alreadyUpVoted(id)) {
				current->countUpV--;
				for (unsigned i = 0; i < userOp->logged->upVoted.getSize(); i++) {
					if (userOp->logged->upVoted[i] == id);
					userOp->logged->upVoted.popAt(i);
					break;
				}
				current->countDownV++;
				userOp->logged->downVoted.pushBack(id);
			}
			else if (userOp->alreadyDownVoted(id)) {
				current->countDownV--;
				for (unsigned i = 0; i < userOp->logged->downVoted.getSize(); i++) {
					if (userOp->logged->downVoted[i] == id);
					userOp->logged->downVoted.popAt(i);
					break;
				}
			}

			if (current->countDownV < 0) {
				current->countDownV = 0;
			}
			else if (current->countUpV < 0) {
				current->countUpV = 0;
			}

			return true;
		}

		for (size_t i = 0; i < current->replies.getSize(); ++i) {
			queue.push(&(current->replies[i]));
		}
	}
	return false;
}

void PostOperations::upvote(unsigned id) {

		for (unsigned i = 0; i < openedP->comments.getSize(); i++) {
			if (id == openedP->comments[i].id) {
				if (!userOp->alreadyUpVoted(id) && !userOp->alreadyDownVoted(id)) {
					openedP->comments[i].countUpV++;
					userOp->logged->upVoted.pushBack(id);
				}
				else if (userOp->alreadyDownVoted(id)) {
					openedP->comments[i].countDownV--;
					for (unsigned i = 0; i < userOp->logged->downVoted.getSize(); i++) {
						if (userOp->logged->downVoted[i] == id);
						userOp->logged->downVoted.popAt(i);
						break;
					}
					openedP->comments[i].countUpV++;
					userOp->logged->upVoted.pushBack(id);
				}
				else if (userOp->alreadyUpVoted(id)) {
					openedP->comments[i].countUpV--;
					for (unsigned i = 0; i < userOp->logged->upVoted.getSize(); i++) {
						if (userOp->logged->upVoted[i] == id);
						userOp->logged->upVoted.popAt(i);
						break;
					}
				}
				
				if (openedP->comments[i].countUpV < 0 ) {
					openedP->comments[i].countUpV = 0;
				}
				else if (openedP->comments[i].countDownV < 0) {
					openedP->comments[i].countDownV = 0;
				}
			}
			else if(searchComment_AndUpVote(id, openedP->comments[i])){
				break;
			}
		}
}
void PostOperations::downvote(unsigned id) {

		for (unsigned i = 0; i < openedP->getComments().getSize(); i++) {
			if (id == openedP->comments[i].id) {

				if (!userOp->alreadyDownVoted(id) && !userOp->alreadyUpVoted(id)) {
					openedP->comments[i].countDownV++;
					userOp->logged->downVoted.pushBack(id);
				}
				else if (userOp->alreadyUpVoted(id)) {
					openedP->comments[i].countUpV--;
					for (unsigned i = 0; i < userOp->logged->upVoted.getSize(); i++) {
						if (userOp->logged->upVoted[i] == id);
						userOp->logged->upVoted.popAt(i);
						break;
					}
					openedP->comments[i].countDownV++;
					userOp->logged->downVoted.pushBack(id);
				}
				else if (userOp->alreadyDownVoted(id)) {
					openedP->comments[i].countDownV--;
					for (unsigned i = 0; i < userOp->logged->downVoted.getSize(); i++) {
						if (userOp->logged->downVoted[i] == id);
						userOp->logged->downVoted.popAt(i);
						break;
					}
				}
				if (openedP->comments[i].countDownV < 0) {
					openedP->comments[i].countDownV = 0;
				}
				else if (openedP->comments[i].countUpV < 0) {
					openedP->comments[i].countUpV = 0;
				}
			}
			else if (searchComment_AndDownVote(id, openedP->comments[i])) {
				break;
			}
		}
}

bool PostOperations::searchComment(unsigned id, Comment& toSearch, const Comment& _reply) {
	Queue<Comment*> queue;
	queue.push(&toSearch);

	while (!queue.isEmpty()) {
		Comment* current = queue.peek();
		queue.pop();

		if (current->id == id) {
			current->replies.pushBack(_reply);
			return true;
		}

		for (size_t i = 0; i < current->replies.getSize(); ++i) {
			queue.push(&(current->replies[i]));
		}
	}
	return false;
}

void PostOperations::reply(unsigned id) {

		Comment reply;
		std::cout << "Enter your reply: ";
		std::cin >> reply;

		reply.user = userOp->logged;
		reply.id = openedP->p_counter++;

		for (unsigned i = 0; i < openedP->comments.getSize(); i++) {
			if (openedP->comments[i].id == id) {
				openedP->comments[i].replies.pushBack(reply);
				break;
			}
			if (searchComment(id, openedP->comments[i], reply)) {
				break;
			}			
		}
}

void PostOperations::p_close() {
	std::cout << "Post successfully closed! " << std::endl;
	openedP = nullptr;
}
