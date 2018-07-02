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
class WorldMap;


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

	int getMaxY();
	int getMinY();
	WorldMap getAsMap();
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

class WorldMap {
private:
	bool** map;
	int height;
	int width;
public:
	WorldMap() = delete;
	WorldMap(bool** map, int height, int width);
	//~WorldMap();

	void show();
	std::string getHoles();
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

int World::getMaxY()
{
	return std::max_element(platforms.begin(), platforms.end(),
		/*needed & ?*/[&](Platform p1, Platform p2) {return p1.getYPos() < p2.getYPos(); })
		->getYPos();
}

int World::getMinY()
{
	return std::min_element(platforms.begin(), platforms.end(),
		[&](Platform p1, Platform p2) {return p1.getYPos() < p2.getYPos(); })
		->getYPos();
}

WorldMap World::getAsMap() 
{
	int maxY = getMaxY();
	int minY = getMinY();
	int height = maxY - minY + 1;
	int width = skyRight - skyLeft;

	//creating array
	bool** map = new bool*[height];
	for (int i = 0; i < height; i++)
		map[i] = new bool[width];

	//initializing array with 0
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			map[i][j] = false;

	//putting platforms into it
	for (int i = 0; i < numPlatforms; i++)
	{
		int left = platforms[i].getLeft();
		int right = platforms[i].getRight();

		int y = -platforms[i].getYPos() + maxY;
		for (int j = left; j < right; j++)
			map[y][j] = true;
	}
	return WorldMap(map,height,width);
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

//WorldMap implementation

WorldMap::WorldMap(bool** map, int height, int width)
{
	this->height = height;
	this->width = width;

	this->map = new bool*[height];

	for (int i = 0; i < height; i++)
	{
		this->map[i] = new bool[width];
		for (int j = 0; j < width; j++)
			this->map[i][j] = map[i][j];
	}
}

void WorldMap::show()
{
	//foreach?
	for (int i = 0; i < height; i++)
	{

		for (int j = 0; j < width; j++)
		{
			std::cout << (map[i][j] ? "x" : " ");
		}
		std::cout << std::endl;
	}
}

std::string WorldMap::getHoles()
{
	//TODO: most important	

	//for each column checking 

	int holesCounter = 0;
	int spaceCounter = 0;
	bool counted = false;
	int i;

	for (int j = 0; j < width; j++)
	{
		i = 0;
		while (i<height && !map[i][j])
		{
			i++;
		}
		if (i == height)
		{
			spaceCounter++;
			//check if keep going

			if (!counted)
			{
				counted = true;
				holesCounter++;
			}
		}
		
		else
		{
			if (counted)counted = false;
		}
	}
	std::stringstream ss;
	ss << holesCounter << " " << spaceCounter;
	return ss.str();
}

///WorldMap

//Additional

World handleInput();
World handleInput(std::string input);//for testing

///Addidional

int main()
{
	//todo read to vector
	int skyLeft = 0,
		skyRight = 8;
	int numPlatforms = 2;
	std::vector<Platform >platforms = 
	{ 
		{1,7,2},
		{1,8,0}
	};

	World world = World(skyLeft, skyRight, numPlatforms, platforms);
	
	WorldMap map = world.getAsMap();

	map.show();
	std::cout<<map.getHoles()<<std::endl;

	system("pause");
    return 0;
}


