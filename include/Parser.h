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
	unsigned char*	_state;
	std::string		_file;
public:
	Parser(std::string const &);
	~Parser(void);
	unsigned char* readInitialState();
	unsigned char* getInitialState();
	bool validateState(unsigned char* base);
	unsigned char getSize();
	void getSolution(std::list<std::string *> & solution);
};

#endif