//Source: https://github.com/Angeld55/Object-oriented_programming_FMI/blob/master/Week%2009/MyString%20(with%20move)/MyString.cpp
#pragma once
#include <iostream>
#pragma warning (disable: 4996)

class String {

private:
	char* _data;
	size_t _length;

public:
	String();
	String(const char* data);
	String(const String& other);
	String& operator=(const String& other);
	~String();

	String(String&& other) noexcept;
	String& operator=(String&& other) noexcept;

	size_t length() const;
	String& operator+=(const String& other);

	String substr(size_t begin, size_t howMany) const;

	char& operator[](size_t index);
	char operator[](size_t index) const;

	const char* c_str() const;

	friend String operator+(const String& lhs, const String& rhs);
	friend std::istream& operator>>(std::istream&, String& str);

private:
	void copyFrom(const String& data);
	void move(String&& other);
	void free();

	explicit String(size_t capacity);
};

std::ostream& operator<<(std::ostream& os, const String& str);

bool operator<(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);

