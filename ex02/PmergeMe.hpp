#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <string>
# include <deque>
# include <list>
# include <cstdlib>
# include <cctype>
# include <cstring>
# include <algorithm>

class PmergeMe
{
private:
	int _len;
	int *_numbers;
	std::deque<int> _dmerge;
	std::list<int> _lmerge;
	PmergeMe(void);
	PmergeMe(PmergeMe const& src);
	PmergeMe& operator=(PmergeMe const& rhs);
public:
	PmergeMe(int len);
	~PmergeMe(void);
	bool initialisation(char **nbList);
	void dequeMerge(unsigned long begin);
	void listMerge();
};

#endif
