#include <iostream>
#include <fstream>
#include "UserArray.h"
UserArray::UserArray()
{
	init();
}

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
	if (currentCount == currentSize)
	{
		currentSize *= 2;
		User** newArr;
		newArr = new User*[currentSize];
		for (int i = 0; i < currentCount; i++)
		{	
			newArr[i] = arr[i];
		}
		delete[] arr;
		arr = newArr;
	}

	arr[currentCount] = new User(user);
	currentCount++;
}

void UserArray::openFile(const char* filepath)
{
	std::ifstream file(filepath);
	if (file)
	{
		clear();
		init();
		while (!file.eof())
		{
			User user;
			file >> user;
			if (user.getUsername() == nullptr) 
			{
				break;
			}
			addUser(user);
		}

		file.close();
	}
}

void UserArray::saveFile(const char* filepath)
{
	std::ofstream file(filepath);
	if (file)
	{
		for (int i = 0; i < currentCount; i++)
		{
			file << *arr[i];
		}

		file.close();
	}
}

void UserArray::print() const
{
	for (int i = 0; i < currentCount; i++)
	{
		std::cout << *arr[i];
	}
}

void UserArray::copy(const UserArray& other)
{
	currentSize = other.currentSize;
	currentCount = other.currentCount;
	arr = new User*[currentSize];
	for (int i = 0; i < currentCount; i++)
	{
		arr[i] = new User(*other.arr[i]);
	}
}

void UserArray::clear()
{
	for (int i = 0; i < currentCount; i++)
	{
		delete arr[i];
	}
	delete[] arr;
	arr = nullptr;
}

void UserArray::init()
{
	currentSize = 2;
	currentCount = 0;
	arr = new User*[currentSize];
}
