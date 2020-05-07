#pragma once
#include "User.h"
#include <string>
#include <vector>

using namespace std;

class UserArray
{
public:
	UserArray();
	UserArray(const UserArray& other);
	UserArray& operator=(const UserArray& other);
	~UserArray();

	void addUser(const User& user);
	void openFile(const string& filepath);
	void saveFile(const string& filepath);

	void print() const;

private:
	std::vector<User*> users;

	void copy(const UserArray& other);
	void clear();
};
