#include "Parser.h"
#include <sstream>
#include <iostream>
#include <list>

Parser::Parser(std::string const & file) : _ifs(file.c_str()), _size(0), 	_state(0)
{
	_file = file;
	if ((_state = readInitialState()))
	{
		std::cout << "Good \"Taquin\" File of " << _size << std::endl;
	}
}

int** Parser::readInitialState()
{
	std::string line;

	// Get Size of "Taquin"
	std::getline(_ifs, line);
	std::stringstream  lineSize(line);
	lineSize >> _size;

	if (_size == 0)
	{
		std::cerr << "Bad \"Taquin\" file" << std::endl;
		return 0;
	}
	int** base = new int*[_size];
	for (int i = 0 ; i < _size ; i++)
		base[i] = new int[_size];

	int x = 0;
	int y;


	while(std::getline(_ifs,line))
	{
		y = 0;
		std::string cell;
		std::stringstream  lineStream(line);

		while (std::getline(lineStream, cell, ' '))
		{
			std::istringstream is(cell);
			is >> base[x][y++];
		}

		if (y != _size)
		{
			std::cerr << "Bad \"Taquin\" file" << std::endl;
			return 0;
		}

		x++;
	}
	if (!this->validateState(base))
		return 0;
	return base;
}

bool Parser::validateState(int ** base)
{
	bool err = false;

	// Create an element list
	std::list<int> elements;

	for (int i = 0 ; i < _size ; i++)
		for (int j = 0 ; j < _size ; j++)
			elements.push_back(base[i][j]);

	// Check if first is the good number
	elements.sort();

	if (*(elements.begin()) != 0)
		err = true;

	// Check if last is the good number
	elements.reverse();

	if (*(elements.begin()) != (_size * _size) - 1)
		err = true;

	std::cout << err << std::endl;
	// Check if there's no doubled values
	elements.unique();

	if (elements.size() != (_size * _size))
		err = true;

	if (err)
	{
		std::cerr << "Error in given numbers" << std::endl;
		return false;
	}
	return true;
}

int** Parser::getInitialState()
{
	return _state;
}


int Parser::getSize()
{
	return _size;
}

void Parser::getSolution(std::list<std::string *> & solution)
{
	
	
	std::cout << "ouvre :" << std::string(_file + ".solution").c_str() << std::endl;
	std::ifstream ifs(std::string(_file + ".solution").c_str());

	std::string *line = new std::string();
	std::getline(ifs,*line);
	std::cout << line << std::endl;
	while(std::getline(ifs,*line))
	{
		std::cout << *line << std::endl;
		solution.push_back(line);
		line = new std::string();
	}
	ifs.close();
}

Parser::~Parser(void)
{
}
