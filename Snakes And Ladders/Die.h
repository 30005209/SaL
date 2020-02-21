#ifndef _Die
#define _Die
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
	static int roll(int);
};

#endif _Die