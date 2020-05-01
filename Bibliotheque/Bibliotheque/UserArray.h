#pragma once
#include "User.h"
class UserArray
{
public:
	UserArray();
	UserArray(const UserArray& other);
	UserArray& operator=(const UserArray& other);
	~UserArray();

	void addUser(const User& user);
	void openFile(const char* filepath);
	void saveFile(const char* filepath);

	void print() const;

private:
	User** arr;
	int currentSize;
	int currentCount;

	void copy(const UserArray& other);
	void clear();
	void init();
};
