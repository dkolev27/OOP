#include <iostream>
#include<cstring>
#include "User.h"

User::User()
{
	username = nullptr;
	password = nullptr;
	isAdmin = false;
	isFound = false;
}

User::User(const char* username, const char* password, bool isAdmin)
{
	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);
	this->password = new char[strlen(password) + 1];
	strcpy(this->password, password);
	this->isAdmin = isAdmin;
}

User::User(const User& other)
{
	copy(other);
}

User& User::operator=(const User& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

User::~User()
{
	clear();
}

void User::setUsername(const char* username)
{
	if (this->username)
	{
		delete[] this->username;
	}
	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);
}

char* User::getUsername() const
{
	return username;
}

void User::setPassword(const char* password)
{
	if (this->password)
	{
		delete[] this->password;
	}
	this->password = new char[strlen(password) + 1];
	strcpy(this->password, password);
}

char* User::getPassword() const
{
	return password;
}

void User::setIsAdmin(bool isAdmin)
{
	this->isAdmin = isAdmin;
}

bool User::getIsAdmin() const
{
	return isAdmin;
}

bool User::getIsFound() const
{
	return isFound;
}

void User::print() const
{
	std::cout << username << " " << password << " " << isAdmin << std::endl;
}

void User::copy(const User& other)
{
	this->username = new char[strlen(other.username) + 1];
	strcpy(this->username, other.username);
	this->password = new char[strlen(other.password) + 1];
	strcpy(this->password, other.password);
	isAdmin = other.isAdmin;
	isFound = other.isFound;
}

void User::clear()
{
	delete[] username;
	username = nullptr;
	delete[] password;
	password = nullptr;
}

std::istream& operator>>(std::istream& in, User& user)
{
	const int MAX_LINE_LEN = 128;
	char line[MAX_LINE_LEN];
	char readUsername[MAX_LINE_LEN]; //Initializing buffer for reading
	char readPassword[MAX_LINE_LEN];
	bool readIsAdmin;
	user.isFound = 0;

	do //Skips empty lines in file
	{
		in.getline(readUsername, MAX_LINE_LEN); 
		in.getline(readPassword, MAX_LINE_LEN);
		in >> readIsAdmin;
		in.getline(line, MAX_LINE_LEN);
		user.isAdmin = readIsAdmin;
		if ((strcmp(readUsername, user.username) == 0) && (strcmp(readPassword, user.password) == 0))
		{
			user.isFound = 1;
			break;
		}
		if (in.eof())
		{
			break;
		}
	} while (strlen(line) == 0);

	if (user.isFound == 0)
	{
		std::cout << "Wrong username or password!" << std::endl;
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, User& user)
{
	out
		<< user.username << std::endl
		<< user.password << std::endl
		<< user.isAdmin << std::endl;
		
	return out;
}
