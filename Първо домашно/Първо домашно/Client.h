#pragma once
class Client
{
public:
	Client();
	Client(const Client& other);
	Client& operator=(const Client& other);
	~Client();

	//Setters
	void setClientName(char* newClient);
	void setClientPassword(char* newPassword);

	//Getters
	const char* getClientName() const;
	const char* getClientPassword() const;


private:
	char* clientName;
	char* clientPassword;

	//Helpers
	void copy(const Client& other);
	void clear();
};

