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

unsigned char* Parser::readInitialState()
{
	std::string line;

	// Get Size of "Taquin"
	std::getline(_ifs, line);
	std::stringstream  lineSize(line);
	lineSize >> _size;

	if (_size == 0)
	{
		std::cerr << "Bad \"Taquin\" file : Couldn't get size" << std::endl;
		return 0;
	}
	if (_size > 15)
	{
		std::cerr << "Bad \"Taquin\" file : Size is greater than 15, can't process" << std::endl;
		return 0;
	}
	unsigned char* base = new unsigned char[(_size * _size) + 1];
	base[_size * _size] = 0;
	int k = 0;
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
			int current;
			is >> current;
			base[k] = current;
			y++;
			k++;
		}
		if (y != _size)
		{
			std::cerr << "Bad \"Taquin\" file : Bad width" << std::endl;
			return 0;
		}
		x++;
	}
	if (!this->validateState(base))
		return 0;

	for (int i = 0; i < _size * _size; i++)
		if (base[i] == 0)
			base[i] = 255;
	return base;
}

bool Parser::validateState(unsigned char* base)
{
	bool err = false;

	// Create an element list
	std::list<unsigned char> elements;

	for (int i = 0 ; i <= (_size * _size) ; i++)
			elements.push_back(base[i]);

	// Check if first is the good number
	elements.sort();

	if (*(elements.begin()) != 0)
		err = true;

	// Check if last is the good number
	elements.reverse();

	if (*(elements.begin()) != (_size * _size) - 1)
		err = true;

	// Check if there's no doubled values
	elements.unique();

	if (elements.size() != (unsigned int)(_size * _size))
		err = true;

	if (err)
	{
		std::cerr << "Error in given numbers" << std::endl;
		return false;
	}
	return true;
}

unsigned char* Parser::getInitialState()
{
	return _state;
}


unsigned char Parser::getSize()
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
