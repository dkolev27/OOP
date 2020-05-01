#include "Deck.h"

Deck::Deck() : Deck(52, "Default")
{}

Deck::Deck(int newCurrentCapacity) : Deck(newCurrentCapacity, "Default")
{}

Deck::Deck(int currentCapacity, const char* serialDeckNumber)
{
	maximumCapacity = currentCapacity;
	this->currentCapacity = currentCapacity;
	sequenceOfCards = new Card * [maximumCapacity];
	this->serialDeckNumber = new char[strlen(serialDeckNumber) + 1];
	strcpy(this->serialDeckNumber, serialDeckNumber);

	const char* arrayOfRanks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	const char* arrayOfSuits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	for (int i = 0; i < currentCapacity; i++)
	{
		char number[MAX_SIZE_SERIAL_NUMBER];
		strcpy(number, serialDeckNumber);
		int idxOfNum = strlen(serialDeckNumber);
		int num = i + 1;
		while (num > 0)
		{
			number[idxOfNum] = '0' + num%10;
			num /= 10;
			idxOfNum++;
		}
		number[idxOfNum] = '\0';

		Card* card = new Card(arrayOfSuits[i%4], arrayOfRanks[(i/4)%13], number);
		std::cout << *card << std::endl;
		sequenceOfCards[i] = card;
	}
}

Deck& Deck::operator=(const Deck& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

Deck::~Deck()
{
	clear();
}

Card* Deck::pop()
{
	if (currentCapacity == 0)
	{
		return nullptr;
	}
	else
	{
		return sequenceOfCards[--currentCapacity];
	}
}

float Deck::getProbability(int playerPoints)
{
	if (playerPoints < 10)
	{
		return 0;
	}
	int validCardsCounter = 0;
	for (int i = 0; i < currentCapacity; i++)
	{
		if (strcmp(sequenceOfCards[i]->getRank(), "A") == 0)
		{
			if (playerPoints == 10 || playerPoints == 20)
			{
				validCardsCounter++;
			}
		}
		else if (sequenceOfCards[i]->getPoints() + playerPoints == 21)
		{
			validCardsCounter++;
		}
	}
	return (float)validCardsCounter / currentCapacity;
}

int Deck::suit_count(const char* suit) const
{
	int suitCounter = 0;
	for (int i = 0; i < currentCapacity; i++)
	{
		if (strcmp(sequenceOfCards[i]->getSuit(), suit) == 0)
		{
			suitCounter++;
		}
	}
	return suitCounter;
}

int Deck::rank_count(const char* rank) const
{
	int rankCounter = 0;
	for (int i = 0; i < currentCapacity; i++)
	{
		if (strcmp(sequenceOfCards[i]->getSuit(), rank) == 0)
		{
			rankCounter++;
		}
	}
	return rankCounter;
}

void Deck::copy(const Deck& other)
{
	this->maximumCapacity = other.maximumCapacity;
	this->currentCapacity = other.currentCapacity;
	sequenceOfCards = new Card * [other.maximumCapacity];
	this->serialDeckNumber = new char[strlen(other.serialDeckNumber) + 1];
	strcpy(this->serialDeckNumber, other.serialDeckNumber);
}

void Deck::clear()
{
	for (int i = 0; i < currentCapacity; i++)
	{
		//delete sequenceOfCards[i];
	}
 	delete[] sequenceOfCards;
	sequenceOfCards = nullptr;
	delete[] serialDeckNumber;
	serialDeckNumber = nullptr;
}
