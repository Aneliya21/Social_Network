#include "String.h"

String::String(size_t capacity) {
	_length = capacity - 1;
	_data = new char[capacity];
}

String operator+(const String& lhs, const String& rhs) {
	String result(lhs._length + rhs._length + 1);

	result[0] = '\0';
	strcat(result._data, lhs._data);
	strcat(result._data, rhs._data);

	return result;
}

String& String::operator+=(const String& other) {
	char* result = new char[(_length += other._length) + 1];
	result[0] = '\0';
	strcat(result, _data);
	strcat(result, other._data);

	delete[] _data;
	_data = result;

	return *this;
}

String::String() : String(1) {
	_data[0] = '\0';
}

String::String(const char* data) : String(strlen(data) + 1) {
	strcpy(_data, data);
}

String::String(const String& other) {
	copyFrom(other);
}

String& String::operator=(const String& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

void String::free() {
	delete[] _data;
	_data = nullptr;
}

String::~String() {
	free();
}

size_t String::length() const {
	return _length;
}

void String::copyFrom(const String& other) {
	_length = other._length;
	_data = new char[_length + 1];
	strcpy(_data, other._data);
}

void String::move(String&& other) {
	_data = other._data;
	other._data = nullptr;
	_length = other._length;
}

String::String(String&& other) noexcept {
	move(std::move(other));
}

String& String::operator=(String&& other) noexcept {
	if (this != &other) {
		free();
		move(std::move(other));
	}
	return *this;
}

char& String::operator[](size_t index) {
	return _data[index];
}

char String::operator[](size_t index) const {
	return _data[index];
}

String String::substr(size_t begin, size_t howMany) const {
	if (begin + howMany > _length)
		throw std::length_error("Error, Substr out of range");


	String res(howMany + 1);
	for (int i = 0; i < howMany; i++)
		res._data[i] = _data[begin + i];
	res[howMany] = '\0';
	return res;
}

const char* String::c_str() const {
	return _data;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
	return os << str.c_str();
}

std::istream& operator>>(std::istream& is, String& str) {
	char buff[1024];
	is >> buff;

	delete[] str._data;
	str._length = strlen(buff);
	str._data = new char[str._length + 1];
	strcpy(str._data, buff);
	return is;
}

bool operator<(const String& lhs, const String& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}
bool operator<=(const String& lhs, const String& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
bool operator>=(const String& lhs, const String& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}
bool operator>(const String& lhs, const String& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}
bool operator==(const String& lhs, const String& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator!=(const String& lhs, const String& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}
