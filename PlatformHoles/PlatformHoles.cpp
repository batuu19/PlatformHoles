// PlatformHoles.cpp : Defines the entry point for the console application.
//


//#include <stdio.h>
//#include <tchar.h>

#include "stdafx.h"
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>

class Engine;
class World;
class Platform;


class World {
private:
	int skyLeft, skyRight;
	int numPlatforms;
	std::vector<Platform> platforms;
public:
	World() = delete;//??
	World(int skyLeft, int skyRight, int numPlatforms, std::vector<Platform> platforms);
	//~World();
	int getSkyLeft();
	int getSkyRight();
	int getNumPlatforms();
	Platform getPlatform(int index);

	std::string getHoles();
};

class Platform {
private:
	int left, right;
	int yPos;
public:
	Platform() = delete;//??
	Platform(int left, int right, int yPos);
	//~Platform();

	int getLeft();
	int getRight();
	int getYPos();

	bool operator<(Platform &second);
};

//World implementation
World::World(int skyLeft, int skyRight, int numPlatforms, std::vector<Platform> platforms)
{
	this->skyLeft = skyLeft;
	this->skyRight = skyRight;
	this->numPlatforms = numPlatforms;
	this->platforms = platforms;

	std::sort(this->platforms.begin(), this->platforms.end());
}

std::string World::getHoles()
{
	int holes = 0;
	int space = 0;

	int pos = skyLeft;

	for (int i = 0; i < numPlatforms; i++)
	{
		int left = platforms[i].getLeft();
		int right = platforms[i].getRight();
		if (left > pos)//there is hole __P  L___
		{
			holes++;
			space += left - pos;
		}

		while(right < pos)	//______P
							// ___R
		{
			//skip next(this?) platform
			i++;
			right = platforms[i].getRight();
		}

		pos = platforms[i].getRight();
	}
	//hole at end
	int right = platforms[numPlatforms - 1].getRight();
	if (right < skyRight)
	{
		holes++;
		space += skyRight - right;
	}


	std::stringstream ss;

	ss << holes << " " << space;

	return ss.str();
}

///World

//Platform implementation

Platform::Platform(int left, int right, int yPos)
{
	this->left = left;
	this->right = right;
	this->yPos = yPos;
}

int Platform::getLeft()
{
	return left;
}

int Platform::getRight()
{
	return right;
}

int Platform::getYPos()
{
	return yPos;
}

bool Platform::operator<(Platform& second)
{
	return this->left < second.left;
}
///Platform

//Additional

World handleInput();
World handleInput(std::string input);//for testing

///Addidional

int main()
{
	//todo read to vector
	int skyLeft = 0,
		skyRight = 25;
	int numPlatforms = 7;
	std::vector<Platform >platforms =
	{
		{0,7,0},
		{6,10,-2},
		{9, 12, 0},
		{13, 16, 0},
		{15, 18, -2},
		{21, 22, 0},
		{17, 19, -4},
	};

	World world = World(skyLeft, skyRight, numPlatforms, platforms);
	
	std::cout<<world.getHoles()<<std::endl;

	system("pause");
    return 0;
}


