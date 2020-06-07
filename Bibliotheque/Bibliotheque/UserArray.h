#pragma once
#include "User.h"
#include <string>
#include <vector>

using namespace std;

class UserArray
{
public:
	// Голяма четворка
	UserArray(const string& filepath);
	UserArray(const UserArray& other);
	UserArray& operator=(const UserArray& other);
	~UserArray();

	// Методи
	void addUser(const User& user);
	void openFile(const string& filepath);
	void saveFile() const;
	User* logInUser(const string& username, const string& password) const;
	User* getUser(const string& username) const;
	bool removeUser(const string& username);

	void print() const;

private:
	// Член данни
	vector<User*> users;
	string filepath;

	// Помощни функции
	void copy(const UserArray& other);
	void clear();
};
