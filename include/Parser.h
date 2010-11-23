#ifndef		_PARSER_H_
#define		_PARSER_H_

#include <string>
#include <fstream>
#include <map>
#include <list>
class Parser
{

private:
	std::ifstream	_ifs;
	int				_size;
	int**			_state;
	std::string		_file;
public:
	Parser(std::string const &);
	~Parser(void);
	int** readInitialState();
	int** getInitialState();
	bool validateState(int ** base);
	int getSize();
	void getSolution(std::list<std::string *> & solution);
};

#endif