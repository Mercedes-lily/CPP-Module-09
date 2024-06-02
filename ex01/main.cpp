#include <list>
#include <iostream>
#include <string>

void resetLst(int &Case, std::list<int> lst, std::list<int>::iterator it, int *first, int *second, int result)
{
	static int step = 0;
	lst.erase(it);
	lst.erase(it);
	if (step == 0)
		lst.erase(it);
	if (*it <= '9' && *it >= '0')
	{
		(*second) = result;
		(*first) = -1;
		(*Case) = 2;
	}
	else
	{
		(*second) = -1;
		(*first) = result;
		(*Case) = 1;
	}
	step++;
}

bool createlist(std::list<int> &lst, char *rpneq)
{
	//TODO changer pour prendre une string "5 3 +"
	unsigned long numbers = 0;
	for( int i = 0; rpneq[i]; i++)
	{
		if(rpneq[i] >= '0' && rpneq[i] <= '9')
		{
			lst.push_front(rpneq[i] - 48);
			numbers++;
		}
		else if(rpneq[i] == '+' || rpneq[i] == '-' || rpneq[i] == '*' || rpneq[i] == '/')
			lst.push_front(rpneq[i]);
		else if(rpneq[i] == ' ')
			continue;
		else
		{
			std::cout << rpneq[i] << ": is invalid" << std::endl;
			return(1);
		}
		if(!(rpneq[0] >= '0' && rpneq[0] <= '9'))
		{
			std::cout << "First entry must be an number" << std::endl;
			return(1);
		}
		if(rpneq[i + 1] == '\0' && (rpneq[i] >= '0' && rpneq[i] <= '9'))
		{
			std::cout << "Last entry can't be an number" << std::endl;
			return(1);
		}
		if(rpneq[i + 1] == '\0' && numbers < (lst.size() / 2) + 1)
		{
			std::cout << "Not enough number" << std::endl;
			return(1);
		}
		if(rpneq[i + 1] == '\0' && numbers > (lst.size() / 2) + 1)
		{
			std::cout << "Too many numbers" << std::endl;
			return(1);
		}
	}
	return(0);
}

int calculator(int first, int second, int symbole)
{
	switch(symbole)
	{
		case '+':
			return(first + second);
		case '-':
			return(first - second);
		case '*':
			return(first * second);
		case '/':
			return(first / second);
	}
	return(0)
}

void findNumbers(int Case, int *first, int *second, int *symbole, std::list<int>::iterator *it_supp)
{
	//pour la premiere loop apres on ne doit changer que un chiffre
	for(std::list<int>::iterator it = lst.begin(); it != lst.end(); it++)
	{
		std::list<int>::iterator it_symbole;
		if (*it <= '9' && *it >= '0')
			continue;
		else if (Case == 0)  //premier passage
		{
			it_symbole = it;
			(*it_supp) = it;
			(*symbole) = *it_symbole;
			it_symbole++;
			if (*it_symbole <= 9 && *it_symbole >= 0)
			{
				(*second) = *it_symbole;
				it_symbole++;
			}
			if (*it_symbole <= 9 && *it_symbole >= 0)
				(*first) = *it_symbole;
		}
		else if (Case == 1) //autre passage
		{
			it_symbole = it;
			(*it_supp) = it;
			(*symbole) = *it_symbole;
			it_symbole++;
			if (*it_symbole <= 9 && *it_symbole >= 0)
				(*second) = *it_symbole;
		}
		else if (Case == 2) //autre passage
		{
			it_symbole = it;
			(*it_supp) = it;
			(*symbole) = *it_symbole;
			it_symbole++;
			if (*it_symbole <= 9 && *it_symbole >= 0)
				(*first) = *it_symbole;
		}
	}
}

int executernp(std::list<int> &lst)
{
	int first = -1;
	int second = -1;
	int symbole = -1;
	int result;
	int Case = 0;
	while (!lst.empty())
	{
		std::list<int>::iterator it_supp;
		findNumbers(Case, &first, &second, &symbole, it_supp);
		result = calculator(first, second, symbole);
		resetLst(&Case, lst, it, first, second, result);
		symbole = -1;
	}
	return (result);
} 

bool RPN(char **argv)
{
	std::list<int> lst;
	if(createlist(lst, argv[1]) == 1)
		return(1);
	std::cout << executernp(lst) << std::endl;
	return(0);
}

int main (int argc, char ** argv)
{
	if(argc == 1)
		std::cout << "Enter an equation in polish reverse notation" << std::endl;
	else if(argc == 2)
	{
		if(RPN(argv) == 1)
			return(1);
	}
	else
		std::cout << "Enter only one equation" << std::endl;
}