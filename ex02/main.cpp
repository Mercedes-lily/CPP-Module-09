#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	PmergeMe merge(argc -1);

	if(argc == 1)
	{
		std::cout << "Value to sort are needed" << std::endl;
		return (1);
	}
	if (merge.initialisation(argv +1) == 1)
		return(1);
	merge.dequeMerge(0);
	merge.listMerge();
}