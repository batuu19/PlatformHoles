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
	//World(World& second) = delete;
	World(int skyLeft, int skyRight, int numPlatforms, std::vector<Platform> platforms);

	std::string getHoles();
};

class Platform {
private:
	int left, right;
	int yPos;
public:
	Platform() = delete;
	//Platform(Platform& second) = delete;
	Platform(int left, int right, int yPos);

	int getLeft();
	int getRight();

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
			//skip this platform
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

bool Platform::operator<(Platform& second)
{
	return this->left < second.left;
}
///Platform

//Additional
World handleInput();

//implementation
World handleInput()
{
	int skyLeft, skyRight, numPlatforms;
	std::vector <Platform> platforms;

	std::cin >> skyLeft >> skyRight >> numPlatforms;

	int left, right, y;
	for (int i = 0; i < numPlatforms - 1; i++)
	{
		std::cin >> left >> right >> y;
		platforms.push_back({ left,right,y });
	}

	return World(skyLeft, skyRight, numPlatforms, platforms);
}
///Addidional

int main()
{
	/*
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
	*/

	World world = handleInput();
	
	std::cout<<world.getHoles()<<std::endl;

	system("pause");
    return 0;
}


