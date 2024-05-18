#include <stack>

void createstack(std::list<int> &stck, char*rpneq)
{
	//TODO changer pour prendre une string "5 3 +"
	for( int i = 0; rpneq[i]; i++)
	{
		int numbers = 0;
		if(rpneq[i] >= '0' && rpneq[i][0] <= '9')
		{
			lst.push(rpneq[i][0] - 48)
			numbers++;
		}
		else if(rpneq[i] == '+')
			lst.push('+')
		else if(rpneq[i] == '-')
			lst.push('-')
		else if(rpneq[i] == '/')
			lst.push('/')
		else if(rpneq[i] == '*')
			lst.push('*')
		else if(rpneq[i] == ' ')
			continue;
		else
			std::cout << "Invalid input" << std::endl;
		if(!(rpneq[0] >= '0' && rpneq[i][0] <= '9'))
			std::cout << "Invalid input" << std::endl;
		if(rnpeq[i + 1] == '\0' && rpneq[i] >= '0' && rpneq[i][0] <= '9')
			std::cout << "Invalid input" << std::endl;
		if(rnpeq[i + 1] == '\0' && numbers != (i / 2) + 1)
			std::cout << "Invalid input" << std::endl;
	}
}

void executernp(std::list<int> &stck)
{
	int nb1;
	int nb2;
	int operator;
	for( int i = 0; rpneq[i]; i++)
	{
		int numbers = 0;
		if(rpneq[i] >= '0' && rpneq[i][0] <= '9')
		{
			lst.push(rpneq[i][0] - 48)
			numbers++;
		}
		else if(rpneq[i] == '+')
			lst.push('+')
		else if(rpneq[i] == '-')
			lst.push('-')
		else if(rpneq[i] == '/')
			lst.push('/')
		else if(rpneq[i] == '*')
			lst.push('*')
		else if(rpneq[i] == ' ')
			continue;
		else
			std::cout << "Invalid input" << std::endl;
		if(!(rpneq[0] >= '0' && rpneq[i][0] <= '9'))
			std::cout << "Invalid input" << std::endl;
		if(rnpeq[i + 1] == '\0' && rpneq[i] >= '0' && rpneq[i][0] <= '9')
			std::cout << "Invalid input" << std::endl;
		if(rnpeq[i + 1] == '\0' && numbers != (i / 2) + 1)
			std::cout << "Invalid input" << std::endl;
	}

	
}

void RPN(char **argv)
{
	if(argc % 2 == 0)
		std::cout << "Invalid input" << std::endl;
	else
	{
		std::stack<int> stck;
		createlist(stck, argv[1]);
		executernp(stck);
	}
}

int main (int argc, char ** argv)
{
	if(argc == 1)
		std::cout << "Enter an equation in polish reverse notation" << std::endl;
	else
		RPN(argv);
}