//#include "FileOperations.h"
//
////FileOperations::FileOperations(SocialNetwork& _sN) {
////	sN = &_sN;
////}
//
//namespace {
//	String readStringFromFile(std::ifstream& ifs) {
//		int stringLength;
//		ifs.read((char*)&stringLength, sizeof(int));
//		char* str = new char[stringLength + 1];
//		ifs.read(str, stringLength);
//		str[stringLength] = '\0';
//
//		return str;
//	}
//}
//NetworkUser FileOperations::readN_U(std::ifstream& ifs) {
//	NetworkUser us;
//	us.fName = readStringFromFile(ifs);
//	us.lName = readStringFromFile(ifs);
//	us.pass = readStringFromFile(ifs);
//
//	unsigned id, points;
//	ifs.read((char*)&id, SIZE_OF_UNS);
//	ifs.read((char*)&points, SIZE_OF_UNS);
//	us.id = id;
//	us.points = points;
//	////////////////////////////////////voted?
//
//	return us;
//}
//Topic FileOperations::readT(std::ifstream& ifs) {
//	//using namespace _readStringFromFile;
//	Topic t;
//	t.name = readStringFromFile(ifs);
//
//	unsigned ind, id;
//	ifs.read((char*)&ind, SIZE_OF_UNS);
//	t.creatorIndex = ind;
//
//	t.content = readStringFromFile(ifs);
//
//	ifs.read((char*)&id, SIZE_OF_UNS);
//	t.id = id;
//
//	int p_count;
//	ifs.read((char*)&p_count, SIZE_OF_INT);
//
//	/*for (unsigned i = 0; i < p_count; i++) {
//		t.posts.pushBack(readP(ifs));
//	}*/
//
//	return t;
//}
//Comment FileOperations::readC(std::ifstream& ifs) {
//	Comment com;
//
//	unsigned ind, countUpV, countDownV, id;
//	ifs.read((char*)&ind, SIZE_OF_UNS);
//	//com.user = &users[ind];
//	com.creatorInd = ind;
//
//	ifs.read((char*)&countUpV, SIZE_OF_UNS);
//	com.countUpV = countUpV;
//
//	ifs.read((char*)&countDownV, SIZE_OF_UNS);
//	com.countDownV = countDownV;
//
//	ifs.read((char*)&id, SIZE_OF_UNS);
//	com.id = id;
//
//	int repCount;
//	ifs.read((char*)&repCount, SIZE_OF_INT);
//
//	for (unsigned i = 0; i < repCount; i++)
//		com.replies.pushBack(readC(ifs));
//	return com;
//}
//Post FileOperations::readP(std::ifstream& ifs) {
//	Post p;
//
//	p.name = readStringFromFile(ifs);
//	p.content = readStringFromFile(ifs);
//
//	unsigned counter, id;
//	static unsigned size = sizeof(unsigned);
//	ifs.read((char*)&counter, size);
//	p.p_counter = counter;
//
//	ifs.read((char*)&id, size);
//	p.id = id;
//
//	int p_count;
//	ifs.read((char*)&p_count, SIZE_OF_INT);
//
//	/*for (size_t i = 0; i < p_count; i++)
//		p.comments.pushBack(readC(ifs));*/
//
//	return p;
//}
//
//namespace {
//	void writeText(std::ofstream& ofs, const char* text) {
//
//		unsigned stringLength = strlen(text);
//		ofs.write((const char*)&stringLength, SIZE_OF_INT);
//		ofs.write(text, stringLength);
//	}
//}
//void FileOperations::writeN_U(std::ofstream& ofs, const NetworkUser& us) {
//
//	writeText(ofs, us.fName.c_str());
//	writeText(ofs, us.lName.c_str());
//	writeText(ofs, us.pass.c_str());
//
//	ofs.write((const char*)&us.id, SIZE_OF_UNS);
//	ofs.write((const char*)&us.points, SIZE_OF_UNS);
//	//ofs.write((const char*)&us.voted, sizeof(user.voted));
//}
//void FileOperations::writeT(std::ofstream& ofs, const Topic& topic) {
//
//	writeText(ofs, topic.name.c_str());
//
//	ofs.write((const char*)&topic.creatorIndex, SIZE_OF_UNS);
//
//	writeText(ofs, topic.content.c_str());
//
//	ofs.write((const char*)&topic.id, SIZE_OF_UNS);
//
//	int size = topic.posts.getSize();
//	ofs.write((const char*)&size, SIZE_OF_INT);
//
//	for (size_t i = 0; i < size; i++)
//		writeP(ofs, topic.posts[i]);
//}
//void FileOperations::writeC(std::ofstream& ofs, const Comment& comm) {
//
//	ofs.write((const char*)&comm.creatorInd, SIZE_OF_UNS);
//
//	writeText(ofs, comm.content.c_str());
//
//	ofs.write((const char*)&comm.countUpV, SIZE_OF_UNS);
//	ofs.write((const char*)&comm.countDownV, SIZE_OF_UNS);
//	ofs.write((const char*)&comm.id, SIZE_OF_UNS);
//
//	int size = comm.replies.getSize();
//	ofs.write((const char*)&size, SIZE_OF_INT);
//
//	for (unsigned i = 0; i < size; i++)
//		writeC(ofs, comm.replies[i]);
//}
//void FileOperations::writeP(std::ofstream& ofs, const Post& post) {
//
//	writeText(ofs, post.name.c_str());
//	writeText(ofs, post.content.c_str());
//
//	ofs.write((const char*)&post.p_counter, SIZE_OF_UNS);
//	ofs.write((const char*)&post.id, SIZE_OF_UNS);
//
//	int size = post.comments.getSize();
//	ofs.write((const char*)&size, SIZE_OF_INT);
//
//	/*for (unsigned i = 0; i < size; i++)
//		writeC(ofs, post.comments[i]);*/
//}