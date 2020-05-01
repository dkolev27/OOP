#include <iostream>
#include <cstring>
#include "Client.h"

Client::Client()
{
	clientName = nullptr;
	clientPassword = nullptr;
}

Client::Client(const Client& other)
{
	copy(other);
}

Client& Client::operator=(const Client& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

Client::~Client()
{
	clear();
}

void Client::setClientName(char* newClient)
{
	this->clientName = new char[strlen(newClient) + 1];
	strcpy(this->clientName, newClient);
}

void Client::setClientPassword(char* newPassword)
{
	this->clientPassword = new char[strlen(newPassword) + 1];
	strcpy(this->clientPassword, newPassword);
}

const char* Client::getClientName() const
{
	return clientName;
}

const char* Client::getClientPassword() const
{
	return clientPassword;
}

void Client::copy(const Client& other)
{
	this->clientName = new char[strlen(other.clientName) + 1];
	strcpy(this->clientName, other.clientName);
	this->clientPassword = new char[strlen(other.clientPassword) + 1];
	strcpy(this->clientPassword, other.clientPassword);
}

void Client::clear()
{
	delete[] clientName;
	clientName = nullptr;
	delete[] clientPassword;
	clientPassword = nullptr;
}
