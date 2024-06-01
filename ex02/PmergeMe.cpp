#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
}

PmergeMe::PmergeMe(int len) : _len(len)
{
}

PmergeMe::PmergeMe(PmergeMe const& src)
{
	*this = src;
}

PmergeMe& PmergeMe::operator=(PmergeMe const& rhs)
{
	if (this != &rhs)
	{
		this->_dmerge = rhs._dmerge;
		this->_lmerge = rhs._lmerge;
		this->_numbers = rhs._numbers;
		this->_len = rhs._len;
	}
	return *this;
}

PmergeMe::~PmergeMe(void)
{
}

bool PmergeMe::initialisation(char **nblist)
{
	int test;
	for (int i = 0; i < this->_len; i++)
	{
		int j = 0;
		while(nblist[i][j])
		{
			if(isdigit(nblist[i][j]) == 0)
			{
				std::cout << nblist[i] << " is invalid" << std::endl;
				return(1);
			}
			j++;
		}
		test = atol(nblist[i]);
		if(test > 2147483647 || test < -2147483648)
		{
			std::cout << nblist[i] << " is out of range" << std::endl;
			return(1);
		}
		this->_numbers[i] = atoi(nblist[i]);
	}
	for (int i = 0; i < this->_len; i++)
	{
		this->_dmerge.push_back(this->_numbers[i]);
		this->_lmerge.push_back(this->_numbers[i]);
	}
	/*
	for (int i = 0; i < this->_len; i++)
		std::cout << " " << this->_numbers[i];
	std::cout << std::endl;
	for (int i = 0; i < this->_len; i++)
		std::cout << " " << this->_dmerge[i];
	std::cout << std::endl;
	for (std::list<int>::iterator i = _lmerge.begin(); i != _lmerge.end(); i++)
		std::cout << " " << *i;
	std::cout << std::endl;
	*/
	return(0);
}

void PmergeMe::dequeMerge(unsigned long begin)
{
	if (this->_dmerge.size() == 1)
		return;
	if (begin >= this->_dmerge.size())
		return;
	std::cout << this->_dmerge[begin] << std::endl;
	std::cout << this->_dmerge[begin + 1] << std::endl;
	if(this->_dmerge[begin] > this->_dmerge[begin + 1])
		std::swap(this->_dmerge[begin], this->_dmerge[begin + 1]);
	std::cout << this->_dmerge[begin ]<< std::endl;
	std::cout << this->_dmerge[begin + 1] << std::endl;
	begin += 2;
	this->dequeMerge(begin);

}

void PmergeMe::listMerge()
{}
