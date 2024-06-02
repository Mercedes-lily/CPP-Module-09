#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <string>
# include <deque>
# include <vector>
# include <cstdlib>
# include <cctype>
# include <cstring>
# include <algorithm>
#include <ctime>

class PmergeMe
{
private:
	int _len;
	int *_numbers;
	clock_t timestampDeque;
	clock_t timestampVector;
	std::deque<int> _dmerge;
	std::vector<int> _vmerge;
	PmergeMe(void);
	PmergeMe(PmergeMe const& src);
	PmergeMe& operator=(PmergeMe const& rhs);
public:
	PmergeMe(int len);
	~PmergeMe(void);
	bool initialisation(char **nbList);
	void dequeMerge();
	void pairCheckDequeMerge(unsigned long begin);
	int binarysearch(int left, int right, int nb, std::deque<int> &result);
	void vectorMerge();
	void pairCheckvectorMerge(unsigned long begin);
	int binarysearchvector(int left, int right, int nb, std::vector<int> &result);
	void printtime();
};

#endif
