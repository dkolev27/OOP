#include <iostream>
#include <fstream>
#include "UserArray.h"

UserArray::UserArray()
{}

UserArray::UserArray(const UserArray& other)
{
	copy(other);
}

UserArray& UserArray::operator=(const UserArray& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

UserArray::~UserArray()
{
	clear();
}

void UserArray::addUser(const User& user)
{
	users.push_back(new User(user));
}

void UserArray::openFile(const string& filepath)
{
	std::ifstream file(filepath);
	if (file)
	{
		clear();
		while (!file.eof())
		{
			User user;
			file >> user;
			if (user.getUsername().size() == 0) 
			{
				break;
			}
			addUser(user);
		}

		file.close();
	}
}

void UserArray::saveFile(const string& filepath)
{
	std::ofstream file(filepath);
	if (file)
	{
		for (size_t i = 0; i < users.size(); i++)
		{
			file << *users[i];
		}

		file.close();
	}
}

void UserArray::print() const
{
	for (size_t i = 0; i < users.size(); i++)
	{
		std::cout << *users[i];
	}
}

void UserArray::copy(const UserArray& other)
{
	for (size_t i = 0; i < users.size(); i++)
	{
		users.push_back(new User(*other.users[i]));
	}
}

void UserArray::clear()
{
	for (size_t i = 0; i < users.size(); i++)
	{
		delete users[i];
	}
	users.clear();
}