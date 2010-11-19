#ifndef		_PARSER_H_
#define		_PARSER_H_

#include <string>
#include <fstream>
#include <map>

class Parser
{

private:
	std::ifstream	_ifs;
	int				_size;

public:
	Parser(std::string const &);
	~Parser(void);
	int** getInitialState();
	bool validateState(int ** base);
	int getSize();
	bool hasSolution(int **base);
};

#endif