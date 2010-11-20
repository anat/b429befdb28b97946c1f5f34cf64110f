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
	int**			_state;
public:
	Parser(std::string const &);
	~Parser(void);
	int** getInitialState();
	bool validateState(int ** base);
	int getSize();
};

#endif