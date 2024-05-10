#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>

void createCSVMap(std::fstream &csv, std::map<std::string, float> &csvData)
{
	char line[40];
	csv.getline(line, 40);
	std::string strline(line);
	if(strline.compare(date | value) != 0)
	{
		std::cout << "First line must be : date | value" << std::endl;
		return(1);
	}
	while(!csv.eof())
	{
		csv.getline(line, 19);
		if(line[4] != "-" || line[7] != "-" ||line[11] != "|" || line[10] != " " || line[12] != " ")
		{
			std::cout << "Wrong format : YYYY-MM-DD | value between 0 and 1000" << std::endl;
			return(1);
		}
		for(i = 0, i < 4, i++);
		{
			if (line[i] < '0' || line[i] > '9')
			{
			std::cout << "Wrong format : YYYY-MM-DD | value between 0 and 1000" << std::endl;
			return(1);
			}
		}
		for(i = 5, i < 7, i++);
		{
			if (line[i] < '0' || line[i] > '9')
			{
			std::cout << "Wrong format : YYYY-MM-DD | value between 0 and 1000" << std::endl;
			return(1);
			}
		}
		for(i = 8, i < 10, i++);
		{
			if (line[i] < '0' || line[i] > '9')
			{
			std::cout << "Wrong format : YYYY-MM-DD | value between 0 and 1000" << std::endl;
			return(1);
			}
		}
		// verifier chiffre ou . bitcoin.
		std::string strline(line);
		std::string date = strline.substr(0, 9);
		std::string ex_rate = strline.substr(11);
		double iex_rate = atof(ex_rate.c_str());
		csvData[date] = iex_rate;
	}
	//verifier la valeur des elements de csv
}

void createINPUTMap(std::fstream &input, std::map<std::string, float> &inputData)
{
	char line[];
	input.getline(line, 19);
	
	while(!input.eof())
	{
		input.getline(line, 19);

		std::string strline(line);
		std::string date = strline.substr(0, 9);
		std::string nbBitcoin = strline.substr(13);
		double inbBitcoin = atof(ex_rate.c_str());
		inputData[date] = intBitcoin;
	}
}

int check(int argc, char *file, std::fstream &input, std::fstream &csv)
{
	if(argc == 1)
	{
		std::cout << "1 file needed" << std::endl;
		return(1);
	}
	if(argc > 2)
	{
		std::cout << "Only 1 file is needed" << std::endl;
		return(1);
	}
	if (!input.is_open())
	{
		std::cout << "Impossible to open " << file << std::endl;
		return(1);
	}
	if (!csv.is_open())
	{
		std::cout << "Impossible to open " << "data.csv" << std::endl;
		input.close();
		return(1);
	}
	return(0);
}

int main(int argc, char **argv)
{
	std::fstream input(argv[1], std::fstream::in);
	std::fstream csv("data.csv", std::fstream::in);
	std::map<std::string, float> csvData;
	std::map<std::string, float> inputData;
	if(check(argc, argv[1], input, csv) == 1)
		return(1);
	createCSVMap(csv, csvData)
	csv.close();
	createINPUTMap(input, inputData);
	input.close();
}