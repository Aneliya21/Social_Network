#include "SocialNetwork.h"

SocialNetwork::SocialNetwork():topics(users), posts(topics,users) {
	fileDeserialization();
}

SocialNetwork::~SocialNetwork() {
	fileSerialization();
}
void SocialNetwork::fileSerialization() {
	std::ofstream ofs("Data.dat", std::ios::out | std::ios::binary);
	if (!ofs.is_open()) {
		std::cout << "Error!" << std::endl;
		return;
	}

	ofs.write((const char*)&users.counter, sizeof(users.counter));

	unsigned numUsers = users.users.getSize();
	ofs.write((const char*)&numUsers, SIZE_OF_UNS);
	for (unsigned i = 0; i < users.users.getSize(); i++) {
		const NetworkUser& user = users.users[i];
		writeN_U(ofs, user);
	}

	unsigned numTopics = topics.topics.getSize();
	ofs.write((const char*)&numTopics, SIZE_OF_UNS);
	for (unsigned i = 0; i < topics.topics.getSize(); i++) {
		const Topic& topic = topics.topics[i];
		writeT(ofs, topic);
	}

	ofs.close();
}
void SocialNetwork::fileDeserialization() {
	std::ifstream ifs("Data.dat", std::ios::in | std::ios::binary);
	if (!ifs.is_open()) {
		std::cout << "Error!" << std::endl;
		return;
	}

	ifs.read((char*)&users.counter, sizeof(users.counter));

	unsigned numUsers = 0;
	ifs.read((char*)&numUsers, SIZE_OF_UNS);
	for (unsigned i = 0; i < numUsers; i++) {
		NetworkUser user = readN_U(ifs);
		users.users.pushBack(user);
	}

	unsigned numTopics = 0;
	ifs.read((char*)&numTopics, SIZE_OF_UNS);
	for (unsigned i = 0; i < numTopics; i++) {
		Topic topic = readT(ifs);
		topics.topics.pushBack(topic);
	}
	ifs.close();
}

bool SocialNetwork::checkIfLogged() const {
	if (users.logged != nullptr) {
		return true;
	}
	return false;
}
bool SocialNetwork::checkIfOpenedT() const {
	if (topics.openedT != nullptr) {
		return true;
	}
	return false;
}
bool SocialNetwork::checkIfOpenedP() const {
	if (posts.openedP != nullptr) {
		return true;
	}
	return false;
}

void SocialNetwork::run() {

	String command;

	std::cout << "      --COMMANDS--" << std::endl;
	std::cout << "------------------------" << std::endl;
	std::cout << "|>--" << SIGNUP << "     |>--" << LOGIN << std::endl;
	std::cout << std::endl;
	std::cout << "|>--" << LOGOUT << "     |>--" << SEARCH<< std::endl;
	std::cout << std::endl;
	std::cout << "|>--" << CREATE << "     |>--" << OPEN << std::endl;
	std::cout << std::endl;
	std::cout << "|>--" << pOPEN << "     |>--" << LIST<< std::endl;
	std::cout << std::endl;
	std::cout << "|>--" << POST << "       |>--" << COMMENT_<< std::endl;
	std::cout << std::endl;
	std::cout << "|>--" << COMMENTS << "   |>--" << REPLY << std::endl;
	std::cout << std::endl;
	std::cout << "|>--" << UP_VOTE << "     |>--" << DOWN_VOTE << std::endl;
	std::cout << std::endl;
	std::cout << "|>--" << P_CLOSE << "    |>--" << QUIT << std::endl;
	std::cout << std::endl;
	std::cout << "|>--" << WHOAMI << "     |>--" << ABOUT << std::endl;
	std::cout << std::endl;
	std::cout << "|>--" << EXIT << std::endl;
	
	while (true) {
		std::cout << "------------------------" << std::endl;
		std::cout << std::endl;
		std::cout << "-->PLEASE ENTER COMMAND: ";
		std::cin >> command;
		std::cout << std::endl;

		if (command == EXIT) { break; }

		if (!checkIfLogged()) {         //if user is NOT logged in
			if (command == SIGNUP) {   
				users.signup(); 
				continue;
			}
			else if (command == LOGIN) { 
				users.login();
				continue;
			}
		}
		else {                          //if user is logged in
			if (command == LOGOUT) { 
				users.logout();
				continue;
			}
			else if (command == WHOAMI) { 
				users.whoami();
				continue;
			}
			if (!checkIfOpenedT()) {      //if the topic is NOT opened
				if (command == CREATE) { 
					topics.create();
					continue;
				}
				else if (command == OPEN) {
					std::cout << std::endl;
					std::cout << "    >>Select criteria: " << std::endl;
					std::cout << "       1] open by ID" << std::endl;
					std::cout << "       2] open by topic name" << std::endl;
					std::cout << std::endl;
					std::cout << "    >>Enter criteria ['id' or 'name]: ";
					String ans;
					std::cin >> ans;
					if (ans == "id" || ans =="ID") {
						unsigned id;
						std::cout << std::endl;
						std::cout << "    -->Enter ID: ";
						std::cin >> id;
						if (topics.checkIfTopicIdExists(id))
							topics.open(id);
						else {
							std::cout << std::endl;
							std::cout << "ID not found! " << std::endl << "Please try again! " << std::endl;
						}
					}
					else if (ans == "name") {
						String name;
						std::cout << "    -->Enter topic name: ";
						std::cin >> name;
						if(topics.checkIfTopicNameExists(name))
							topics.open(name);
						else {
							std::cout << std::endl;
							std::cout << "Topic not found!" << std::endl << "Please try again!" << std::endl;
						}
					}
					continue;
				}
				else if (command == ABOUT) {

					unsigned id;
					std::cout << "    -->Enter id: ";
					std::cin >> id;
					if (topics.checkIfTopicIdExists(id))
						topics.about(id);
					else {
						std::cout << std::endl;
						std::cout << "ID not found!" << std::endl << "-- - Please try againg!-- - " << std::endl;
					}
					continue;
				}
				else if (command == SEARCH) {
					String text;
					std::cout << "    -->Enter the topic you are searching for: ";
					std::cin >> text;
					std::cout << std::endl;
					topics.search(text);
					continue;
				}
			}
			else {                           //if the topic is opened
				if (command == SEARCH) {
					String text;
					std::cout << "    -->Enter the topic you are searching for: ";
					std::cin >> text;
					topics.search(text);
					continue;
				}
				if (command == QUIT) { 
					topics.quit();
					continue;
				}
				else if (command == ABOUT) {

					unsigned id;
					std::cout << "    -->Enter id: ";
					std::cin >> id;
					if (topics.checkIfTopicIdExists(id))
						topics.about(id);
					else {
						std::cout << std::endl;
						std::cout << "ID not found!" << std::endl << "--- Please try again!--- " << std::endl;
					}
					continue;
				}
				if (!checkIfOpenedP()) {    //if the post is NOT opened
					if (command == LIST) { 
						posts.list();
						continue;
					}
					else if (command == POST) { 
						posts.post();
						continue;
					}
					else if (command == pOPEN) {
						std::cout << "    Select criteria: " << std::endl;
						std::cout << "       1] p_open by id" << std::endl;
						std::cout << "       2] p_open by topic name" << std::endl;
						std::cout << "    --Enter criteria ('id' or 'name): ";
						String ans;
						std::cin >> ans;
						if (ans == "id") {
							unsigned id;
							std::cout << "    -->Enter post id: ";
							std::cin >> id;
							if (topics.openedT->checkIfPostIdExists(id))
								posts.p_open(id);
							else {
								std::cout << std::endl;
								std::cout << "ID not found!" << std::endl << "Please try again!" << std::endl;
							}
						}
						else if (ans == "name") {
							String name;
							std::cout << "    -->Enter post name: ";
							std::cin >> name;
							if (topics.openedT->checkIfPOstNameExists(name))
								posts.p_open(name);
							else {
								std::cout << std::endl;
								std::cout << "Post not found!" << std::endl << "--- Please try again!--- " << std::endl;
							}
						}
						continue;
					}
				}
				else {                            //if the post is opened
					if (command == COMMENT_) { 
						posts.comment();
						continue;
					}
					else if (command == COMMENTS) { 
						std::cout << "Comments: " << std::endl << std::endl;
						posts.comments();
						continue;
					}
					else if (command == REPLY) {
						unsigned id;
						std::cout << "    -->Enter the id of the comment you want to reply to: ";
						std::cin >> id;
						posts.reply(id);
						continue;
					}
					else if (command == UP_VOTE) {
						unsigned id;
						std::cout << "    -->Enter the id of the comment you want to upvote: ";
						std::cin >> id;
						posts.upvote(id);
						continue;
					}
					else if (command == DOWN_VOTE) {
						unsigned id;
						std::cout << "    -->Enter the id of the comment you want to downvote: ";
						std::cin >> id;
						posts.downvote(id);
						continue;
					}
					else if (command == P_CLOSE) { 
						posts.p_close();
						continue;
					}
				}
			}
		}
			std::cout << "    --INVALID COMMAND--    " << std::endl;  //if the command is NOT valid
			std::cout << std::endl;
			std::cout << "Try again! "<< std::endl;
	}
}


namespace {
	String readStringFromFile(std::ifstream& ifs) {
		int stringLength;
		ifs.read((char*)&stringLength, sizeof(int));
		char* str = new char[stringLength + 1];
		ifs.read(str, stringLength);
		str[stringLength] = '\0';

		return str;
	}
}
NetworkUser SocialNetwork::readN_U(std::ifstream& ifs) {
	NetworkUser us;
	us.fName = readStringFromFile(ifs);
	us.lName = readStringFromFile(ifs);
	us.pass = readStringFromFile(ifs);

	unsigned id, points;
	ifs.read((char*)&id, SIZE_OF_UNS);
	ifs.read((char*)&points, SIZE_OF_UNS);
	us.id = id;
	us.points = points;

	size_t upV_count;
	ifs.read((char*)&upV_count, sizeof(size_t));

	for (unsigned i = 0; i < upV_count; i++) {
		unsigned number;
		ifs.read((char*)&number, sizeof(unsigned));
		us.upVoted.pushBack(number);
	}

	size_t downV_count;
	ifs.read((char*)&downV_count, sizeof(size_t));

	for (unsigned i = 0; i < downV_count; i++) {
		unsigned number;
		ifs.read((char*)&number, sizeof(unsigned));
		us.downVoted.pushBack(number);
	}
	return us;
}
Topic SocialNetwork::readT(std::ifstream& ifs) {
	Topic t;
	t.name = readStringFromFile(ifs);

	unsigned ind, id;
	ifs.read((char*)&ind, SIZE_OF_UNS);
	t.creatorIndex = ind;

	t.creator = &users.users[ind];

	t.content = readStringFromFile(ifs);

	ifs.read((char*)&id, SIZE_OF_UNS);
	t.id = id;

	size_t p_count;
	ifs.read((char*)&p_count, sizeof(size_t));

	for (unsigned i = 0; i < p_count; i++) {
		t.posts.pushBack(readP(ifs));
	}

	return t;
}
Comment SocialNetwork::readC(std::ifstream& ifs) {
	Comment com;

	unsigned ind, countUpV, countDownV, id;
	ifs.read((char*)&ind, SIZE_OF_UNS);

	com.creatorInd = ind;

	com.content=readStringFromFile(ifs);

	ifs.read((char*)&countUpV, SIZE_OF_UNS);
	com.countUpV = countUpV;

	ifs.read((char*)&countDownV, SIZE_OF_UNS);
	com.countDownV = countDownV;

	ifs.read((char*)&id, SIZE_OF_UNS);
	com.id = id;

	size_t repCount;
	ifs.read((char*)&repCount, sizeof(repCount));

	for (unsigned i = 0; i < repCount; i++)
		com.replies.pushBack(readC(ifs));

	return com;
}
Post SocialNetwork::readP(std::ifstream& ifs) {
	Post p;

	p.name = readStringFromFile(ifs);
	p.content = readStringFromFile(ifs);

	unsigned counter, id;
	ifs.read((char*)&counter, SIZE_OF_UNS);
	p.p_counter = counter;

	ifs.read((char*)&id, SIZE_OF_UNS);
	p.id = id;

	size_t p_count;
	ifs.read((char*)&p_count, sizeof(size_t));

	for (size_t i = 0; i < p_count; i++)
		p.comments.pushBack(readC(ifs));

	return p;
}

namespace {
	void writeText(std::ofstream& ofs, const char* text) {

		unsigned stringLength = strlen(text);
		ofs.write((const char*)&stringLength, SIZE_OF_INT);
		ofs.write(text, stringLength);
	}
}
void SocialNetwork::writeN_U(std::ofstream& ofs, const NetworkUser& us) {

	writeText(ofs, us.fName.c_str());
	writeText(ofs, us.lName.c_str());
	writeText(ofs, us.pass.c_str());

	ofs.write((const char*)&us.id, SIZE_OF_UNS);
	ofs.write((const char*)&us.points, SIZE_OF_UNS);

	size_t size = us.upVoted.getSize();
	ofs.write((const char*)&size, sizeof(size_t));

	for (size_t i = 0; i < size; i++) {
		ofs.write((const char*)&us.upVoted[i], sizeof(size_t));
	}

	size = us.downVoted.getSize();
	ofs.write((const char*)&size, sizeof(size_t));

	for (size_t i = 0; i < size; i++) {
		ofs.write((const char*)&us.downVoted[i], sizeof(size_t));
	}

}
void SocialNetwork::writeT(std::ofstream& ofs, const Topic& topic) {

	writeText(ofs, topic.name.c_str());

	ofs.write((const char*)&topic.creatorIndex, SIZE_OF_UNS);

	writeText(ofs, topic.content.c_str());

	ofs.write((const char*)&topic.id, SIZE_OF_UNS);

	size_t size = topic.posts.getSize();
	ofs.write((const char*)&size, sizeof(size));

	for (size_t i = 0; i < size; i++)
		writeP(ofs, topic.posts[i]);
}
void SocialNetwork::writeC(std::ofstream& ofs, const Comment& comm) {

	ofs.write((const char*)&comm.creatorInd, SIZE_OF_UNS);

	writeText(ofs, comm.content.c_str());

	ofs.write((const char*)&comm.countUpV, SIZE_OF_UNS);
	ofs.write((const char*)&comm.countDownV, SIZE_OF_UNS);
	ofs.write((const char*)&comm.id, SIZE_OF_UNS);

	size_t size = comm.replies.getSize();
	ofs.write((const char*)&size, sizeof(size));

	for (unsigned i = 0; i < size; i++)
		writeC(ofs, comm.replies[i]);
}
void SocialNetwork::writeP(std::ofstream& ofs, const Post& post) {

	writeText(ofs, post.name.c_str());
	writeText(ofs, post.content.c_str());

	ofs.write((const char*)&post.p_counter, sizeof(post.p_counter));
	ofs.write((const char*)&post.id, sizeof(post.id));

	size_t size = post.comments.getSize();
	ofs.write((const char*)&size, sizeof(size));

	for (unsigned i = 0; i < size; i++)
		writeC(ofs, post.comments[i]);
}

