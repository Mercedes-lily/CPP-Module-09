#include <stack>
#include <iostream>
#include <string>
#include <cstring>

int createstack(std::stack<int> &stck, char**rpneq)
{
	int numbers = 0;
	int len = 0;
	while(rpneq[len])
		len++;
	for(int i = len -1; i>= 0; i--)
	{
		if(rpneq[i][0] >= '0' && rpneq[i][0] <= '9')
		{
			stck.push(rpneq[i][0] - 48);
			numbers++;
		}
		else if(rpneq[i][0] == '+' || rpneq[i][0] == '-' || rpneq[i][0] == '*' || rpneq[i][0] == '/')
			stck.push(rpneq[i][0]);
		else if(rpneq[i][0] == ' ')
			continue;
		else
		{
			std::cout << rpneq[i][0] << " is an invalid value" << std::endl;
			return(1);
		}
	}
	if(rpneq[0][0] <= '0' || rpneq[0][0] >= '9')
	{
		std::cout << "Must begin with a number" << std::endl;
		return(1);
	}
	else if(rpneq[len -1][0] >= '0' && rpneq[len - 1][0] <= '9')
	{
		std::cout << "Must finish with an operator" << std::endl;
		return(1);
	}
	else if(numbers != (len / 2) + 1)
	{
		std::cout << "Invalid equation" << std::endl;
		return(1);
	}
	return(0);
}

int executernp(std::stack<int> &stck)
{
	int first;
	int second;
	int result;
	int op;
	first = stck.top();
	stck.pop();
	if(first > 9)
	{
		std::cout << "Invalid equation" << std::endl;
		return(1);
	}
	second = stck.top();
	stck.pop();
	if(second > 9)
	{
		std::cout << "Invalid equation" << std::endl;
		return(1);
	}
	op = stck.top();
	if(op == '+')
		result = first + second;
	else if(op == '-')
		result = first - second;
	else if(op == '*')
		result = first * second;
	else if(op == '/')
		result = first / second;
	else 
	{
		std::cout << "Invalid equation" << std::endl;
		return(1);
	}
	stck.pop();
	while(!stck.empty())
	{
		first = result;
		second = stck.top();
		stck.pop();
		if(second > 9)
		{
			std::cout << "Invalid equation" << std::endl;
			return(1);
		}
		op = stck.top();
		if(op == '+')
			result = first + second;
		else if(op == '-')
			result = first - second;
		else if(op == '*')
			result = first * second;
		else if(op == '/')
			result = first / second;
		else 
		{
			std::cout << "Invalid equation" << std::endl;
			return(1);
		}
		stck.pop();
	}
	std::cout << "Result : " << result << std::endl;
	return(0);
}

int RPN(char **argv)
{
	std::stack<int> stck;
	if(createstack(stck, argv + 1) == 1)
		return(1);
	if(executernp(stck) == 1)
		return(1);
	return(0);
}

int main (int argc, char ** argv)
{
	if(argc == 1)
	{
		std::cout << "Enter an equation in reverse polish notation" << std::endl;
		return(1);
	}
	if(RPN(argv) == 1)
		return(1);
	return(0);
}