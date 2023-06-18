#pragma once
#include<fstream>
#include <iostream>
#include "NetworkUserOperations.h"
#include "Vector.hpp"
#include "TopicOperations.h"
#include "PostOperations.h"
#include "FileOperations.h"

class SocialNetwork {

private:

	NetworkUserOperations users;
	TopicOperations topics;
	PostOperations posts;

	bool checkIfLogged() const;
	bool checkIfOpenedT() const;
	bool checkIfOpenedP() const;

public:

	SocialNetwork();
	~SocialNetwork();

	void fileSerialization();
	void fileDeserialization();

	void run();

	NetworkUser readN_U(std::ifstream&);
	void writeN_U(std::ofstream&, const NetworkUser&);

	Topic readT(std::ifstream&);
	void writeT(std::ofstream&, const Topic&);

	Comment readC(std::ifstream&);
	void writeC(std::ofstream&, const Comment&);

	Post readP(std::ifstream&);
	void writeP(std::ofstream&, const Post&);

};
