#ifndef RPN_HPP
# define RPN_HPP
#include <list>
#include <iostream>
#include <string>

class Rpn
{
private:
	std::list<int> _lst;
	int _first;
	int _second;
	int _symbole;
	int _result;
	int _Case;
	int _step;
public:
	Rpn(void);
	Rpn(Rpn const& src);
	~Rpn(void);
	Rpn& operator=(Rpn const& rhs);
	void Rpn::resetLst(std::list<int>::iterator it);
	bool Rpn::createlist(char *rpneq);
	int calculator();
	void findNumbers(std::list<int>::iterator *it_supp);
	int executernp(std::list<int> &lst)
};

#endif