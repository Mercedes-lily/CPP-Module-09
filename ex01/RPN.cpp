#include <stack>
#include <iostream>
#include <string>
#include <cstring>

int createstack(std::stack<int> &stck, char* equation)
{
	int numbers = 0;
	int len = 0;
	while(equation[len])
		len++;
	for(int i = len -1; i>= 0; i--)
	{
		if(equation[i] >= '0' && equation[i] <= '9')
		{
			stck.push(equation[i] - 48);
			numbers++;
		}
		else if(equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/')
			stck.push(equation[i]);
		else if(equation[i] == ' ')
			continue;
		else
		{
			std::cout << equation[i] << " is an invalid value" << std::endl;
			return(1);
		}
	}
	if(equation[0] < '0' || equation[0] > '9')
	{
		std::cout << "Must begin with a number" << std::endl;
		return(1);
	}
	else if(equation[len -1] >= '0' && equation[len - 1] <= '9')
	{
		std::cout << "Must finish with an operator" << std::endl;
		return(1);
	}
	else if(numbers != (stck.size() / 2) + 1)
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
	else if(op == '/' && second != 0)
		result = first / second;
	else if(op == '/' && second == 0)
	{
		std::cout << "Impossible to divide by 0" << std::endl;
		return(1);
	}
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

int RPN(char *equation)
{
	std::stack<int> stck;

	if(createstack(stck, equation) == 1)
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
	if(argc == 3)
	{
		std::cout << "Enter only 1 equation" << std::endl;
		return(1);
	}
	if(RPN(argv[1]) == 1)
		return(1);
	return(0);
}