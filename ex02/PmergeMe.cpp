#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
}

PmergeMe::PmergeMe(int len) : _len(len)
{
	this->_numbers = new int[len];
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
		this->_vmerge = rhs._vmerge;
		this->_numbers = rhs._numbers;
		this->_len = rhs._len;
	}
	return *this;
}

PmergeMe::~PmergeMe(void)
{
	delete [] this->_numbers;
}

void PmergeMe::printtime()
{
	std::cout << "Time to process a range of " << this->_len << " elements with std::deque  : ";
	std::cout << (static_cast<float>(this->timestampDeque)/CLOCKS_PER_SEC * 1000) << "ms" << std::endl;
	std::cout << "Time to process a range of " << this->_len << " elements with std::vector : ";
	std::cout << (static_cast<float>(this->timestampVector)/CLOCKS_PER_SEC * 1000) << "ms" << std::endl;
}

bool PmergeMe::initialisation(char **nbvector)
{
	int test;
	for (int i = 0; i < this->_len; i++)
	{
		int j = 0;
		while(nbvector[i][j])
		{
			if(isdigit(nbvector[i][j]) == 0)
			{
				std::cout << nbvector[i] << " is invalid" << std::endl;
				return(1);
			}
			j++;
		}
		test = atol(nbvector[i]);
		if(test > 2147483647 || test < -2147483648)
		{
			std::cout << nbvector[i] << " is out of range" << std::endl;
			return(1);
		}
		this->_numbers[i] = atoi(nbvector[i]);
	}
	for (int i = 0; i < this->_len; i++)
	{
		this->_dmerge.push_back(this->_numbers[i]);
		this->_vmerge.push_back(this->_numbers[i]);
	}
	std::cout << "Before :  ";
	for(std::deque<int>::iterator it = this->_dmerge.begin(); it != this->_dmerge.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	return(0);
}

void PmergeMe::pairCheckDequeMerge(unsigned long begin)
{
	if (this->_dmerge.size() == 1)
		return;
	if (this->_dmerge.size() - begin < 2)
		return;
	if(this->_dmerge[begin] > this->_dmerge[begin + 1])
		std::swap(this->_dmerge[begin], this->_dmerge[begin + 1]);
	begin += 2;
	this->pairCheckDequeMerge(begin);
}

int PmergeMe::binarysearch(int left, int right, int nb, std::deque<int> &result)
{
	int mid = (left + right)/2;
	if(result[mid] == nb)
		return(mid);
	else if(left > right)
		return(left);
	else if(result[mid] > nb)
		return(binarysearch(left, mid -1 , nb, result));
	else if(result[mid] < nb)
		return(binarysearch(mid + 1, right , nb, result));
	return(-1);
}

void PmergeMe::dequeMerge()
{
	clock_t start = clock();
	std::deque<int> result;
	std::deque<int>::iterator it;
	int BiggerNumber = this->_dmerge.size();
	this->pairCheckDequeMerge(0);
	if(BiggerNumber > 1)
	{
		if(BiggerNumber % 2 == 0)
			BiggerNumber --;
		else
			BiggerNumber -= 2;
		for(int j = BiggerNumber; j >= 1; j -= 2)
		{
			for(it = result.begin(); it != result.end(); it++)
			{
				
				if (this->_dmerge[j] < *it)
				{
					result.insert(it, this->_dmerge[j]);
					this->_dmerge.erase (this->_dmerge.begin() + j);
					break;
				}
			}
			if (it == result.end())
			{
				result.push_back(this->_dmerge[j]);
				this->_dmerge.erase (this->_dmerge.begin() + j);
			}
		}
		it = this->_dmerge.begin();
		while(it != this->_dmerge.end())
		{
			int pos = binarysearch(0, result.size() -1, *it, result);
			result.insert(result.begin() + pos, *it);
			this->_dmerge.erase (this->_dmerge.begin());
			it = this->_dmerge.begin();
		}
	}
	else 
	{
		it = this->_dmerge.begin();
		result.insert(result.begin(), *it);
		this->_dmerge.erase (this->_dmerge.begin());
	}
	clock_t end = clock();

	this->timestampDeque = end - start;
}

void PmergeMe::pairCheckvectorMerge(unsigned long begin)
{
	if (this->_vmerge.size() == 1)
		return;
	if (this->_vmerge.size() - begin < 2)
		return;
	if(this->_vmerge[begin] > this->_vmerge[begin + 1])
		std::swap(this->_vmerge[begin], this->_vmerge[begin + 1]);
	begin += 2;
	this->pairCheckvectorMerge(begin);
}

int PmergeMe::binarysearchvector(int left, int right, int nb, std::vector<int> &result)
{
	int mid = (left + right)/2;
	if(result[mid] == nb)
		return(mid);
	else if(left > right)
		return(left);
	else if(result[mid] > nb)
		return(binarysearchvector(left, mid -1 , nb, result));
	else if(result[mid] < nb)
		return(binarysearchvector(mid + 1, right , nb, result));
	return(-1);
}

void PmergeMe::vectorMerge()
{
	clock_t start = clock();
	std::vector<int> result;
	std::vector<int>::iterator it;
	int BiggerNumber = this->_vmerge.size();
	this->pairCheckvectorMerge(0);
	if(BiggerNumber > 1)
	{
		if(BiggerNumber % 2 == 0)
			BiggerNumber --;
		else
			BiggerNumber -= 2;
		for(int j = BiggerNumber; j >= 1; j -= 2)
		{
			for(it = result.begin(); it != result.end(); it++)
			{
				
				if (this->_vmerge[j] < *it)
				{
					result.insert(it, this->_vmerge[j]);
					this->_vmerge.erase (this->_vmerge.begin() + j);
					break;
				}
			}
			if (it == result.end())
			{
				result.push_back(this->_vmerge[j]);
				this->_vmerge.erase (this->_vmerge.begin() + j);
			}
		}
		std::cout << "Vector big number :   " << std::endl;
		for(it = result.begin(); it != result.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		it = this->_vmerge.begin();

		while(it != this->_vmerge.end())
		{
			int pos = binarysearchvector(0, result.size() -1, *it, result);
			result.insert(result.begin() + pos, *it);
			this->_vmerge.erase (this->_vmerge.begin());
			it = this->_vmerge.begin();
		}
	}
		else 
	{
		it = this->_vmerge.begin();
		result.insert(result.begin(), *it);
		this->_vmerge.erase (this->_vmerge.begin());
	}
	clock_t end = clock();
	this->timestampVector = end - start;
	std::cout << "After :   ";
	for(it = result.begin(); it != result.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}
