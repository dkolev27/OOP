#include <cstring>
#include "Card.h"

Card::Card()
{
	suit[0] = 0;
	rank[0] = 0;
	serialNumber = nullptr;
}

Card::Card(const char* suit, const char* rank, const char* serialNumber)
{
	strcpy(this->suit, suit);
	strcpy(this->rank, rank);
	this->serialNumber = new char[strlen(serialNumber) + 1];
	strcpy(this->serialNumber, serialNumber);	
}

Card::Card(const Card& other)
{
	copy(other);
}

Card& Card::operator=(const Card& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

Card::~Card()
{
	clear();
}

int Card::getPoints() const
{
	if (strcmp(rank, "2") == 0) return 2;
	if (strcmp(rank, "3") == 0) return 3;
	if (strcmp(rank, "4") == 0) return 4;
	if (strcmp(rank, "5") == 0) return 5;
	if (strcmp(rank, "6") == 0) return 6;
	if (strcmp(rank, "7") == 0) return 7;
	if (strcmp(rank, "8") == 0) return 8;
	if (strcmp(rank, "9") == 0) return 9;
	if (strcmp(rank, "10") == 0) return 10;
	if (strcmp(rank, "K") == 0) return 10;
	if (strcmp(rank, "J") == 0) return 10;
	if (strcmp(rank, "Q") == 0) return 10;
	if (strcmp(rank, "A") == 0) return 11;	
}

void Card::clear()
{
	delete[] serialNumber;
	serialNumber = nullptr;
}

void Card::copy(const Card& other)
{
	strcpy(this->suit, other.suit);
	strcpy(this->rank, other.rank);
	for (int i = 0; i < MAX_SIZE_SERIAL_NUMBER; i++)
	{
		this->serialNumber[i] = other.serialNumber[i];
	}
}

std::ostream& operator<<(std::ostream& out, Card& card)
{
	std::cout << card.suit << "(" << card.rank << ")";
	return out;
}
