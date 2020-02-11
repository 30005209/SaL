#pragma once
#include <random>

class Die
{
private:
	int size;

public:
	Die();
	~Die();

	void setSize(int);
	static int roll(void);
};

