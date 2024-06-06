#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cstdlib>
#include <cstring>

//TODO le programme n<exite pas s<il y a une ligne invalid in marque seulement le code d'erreur

float find_exchange_rate(std::map<int, float> &csvData, int total)
{
	if(csvData.find(total) != csvData.end())
		return(csvData.find(total)->second);
	else
	{
		for(int i = 1; i <= 10; i++)
		{
			if(csvData.find(total - i) != csvData.end())
				return(csvData.find(total - i)->second);
		}
		return(47115.93);
	}
	return(0);
}

void mapformonth(std::map<int, int> &month)
{
	//non-bissextile
	month[1] = 0;
	month[2] = 31;
	month[3] = 59;
	month[4] = 90;
	month[5] = 120;
	month[6] = 151;
	month[7] = 181;
	month[8] = 212;
	month[9] = 243;
	month[10] = 273;
	month[11] = 304;
	month[12] = 334;
	//bissextile
	month[21] = 0;
	month[22] = 31;
	month[23] = 60;
	month[24] = 91;
	month[25] = 121;
	month[26] = 152;
	month[27] = 182;
	month[28] = 213;
	month[29] = 244;
	month[30] = 274;
	month[31] = 305;
	month[32] = 335;
}

void fillmapcsv(char *line, std::map<int, float> &csvData, std::map<int, int> month)
{
	std::string strline(line);
	std::string YearStr = strline.substr(0,4);
	std::string MonthStr = strline.substr(5,2);
	std::string DateStr = strline.substr(8,2);
	std::string BitcoinStr = strline.substr(11);
	int YearInt = atoi(YearStr.c_str());
	int MonthInt = atoi(MonthStr.c_str());
	int DateInt = atoi(DateStr.c_str());
	float BitcoinInt = atof(BitcoinStr.c_str());
	int bissextile = 0;
	int nonbissextile = YearInt - 2009;
	int tmp = nonbissextile;
	int total = 0;
	while(tmp - 4 >= 0)
	{
		tmp -= 4;
		bissextile++;
		nonbissextile--;
	}
	total = (365 * nonbissextile) + (366 * bissextile);
	if (YearInt % 4 == 0)
		total += month[MonthInt + 20];
	else
		total += month[MonthInt];
	total += DateInt;
	csvData[total] = BitcoinInt;
}


void fillmapinput(char *line , std::map<int, float> csvData, std::map<int, int> month)
{
	std::string strline(line);
	std::string YearStr = strline.substr(0,4);
	std::string MonthStr = strline.substr(5,2);
	std::string DateStr = strline.substr(8,2);
	std::string BitcoinStr = strline.substr(13);
	int YearInt = atoi(YearStr.c_str());
	int MonthInt = atoi(MonthStr.c_str());
	int DateInt = atoi(DateStr.c_str());
	float BitcoinInt = atof(BitcoinStr.c_str());
	if (YearInt < 2009)
	{
		std::cout << "No value before 2009" << std::endl;
		return;
	}
	if (MonthInt < 1 || MonthInt > 12)
	{
		std::cout << "Month must be between 1 and 12" << std::endl;
		return;
	}
	if (MonthInt == 2)
	{
		if (YearInt % 4 == 0)
		{
			if (DateInt < 1 || DateInt > 29)
			{
				std::cout << "February must be between 1 and 29 for " << YearInt << std::endl;
				return;
			}
		}
		else
		{
			if (DateInt < 1 || DateInt > 28)
			{
				std::cout << "February must be between 1 and 28 for " << YearInt << std::endl;
				return;
			}
		}
	}
	else if(MonthInt == 4 || MonthInt == 6 || MonthInt == 9 || MonthInt == 11)
	{
		if (DateInt < 1 || DateInt > 30)
		{
			std::cout << "Wrong date" << std::endl;
			return;
		}
	}
	else
	{
		if (DateInt < 1 || DateInt > 31)
		{
			std::cout << "Wrong date" << std::endl;
			return;
		}
	}
	int bissextile = 0;
	int nonbissextile = YearInt - 2009;
	int tmp = nonbissextile;
	int total = 0;
	//change for the number
	float exchange_rate = 0;
	nonbissextile = YearInt - 2009;
	while(tmp - 4 >= 0)
	{
		tmp -= 4;
		bissextile++;
		nonbissextile--;
	}
	total = (365 * nonbissextile) + (366 * bissextile);
	if (YearInt % 4 == 0)
		total += month[MonthInt + 20];
	else
		total += month[MonthInt];
	total += DateInt;
	exchange_rate = find_exchange_rate(csvData, total);
	std::cout << YearInt << "-" << MonthStr << "-" << DateStr << "=>" << BitcoinInt << "=" << (exchange_rate * BitcoinInt) << std::endl;
}


int createInputMap(std::fstream &input, std::map<int, float> csvData, std::map<int, int> month)
{
	char line[40];
	input.getline(line, 40);
	std::string strline(line);
	if(strline.compare("date | value") != 0)
	{
		std::cout << "First line must be : date | value" << std::endl;
		return(1);
	}
	while(!input.eof())
	{
		input.getline(line, 40);
		if(input.eof() == 1)
			continue;
		if(line[0] == 0)
			continue;
		if(strlen(line) < 14)
		{
			std::cout << "Your entry id invalid: " << line << std::endl;
			continue;
		}
		if(line[4] != '-' || line[7] != '-' ||line[11] != '|' || line[10] != ' ' || line[12] != ' ')
		{
			std::cout << "Your entry is invalid : " << line << std::endl;
			continue;
		}
		for(int i = 0; i < 4; i++)
		{
			if (line[i] < '0' || line[i] > '9')
			{
				std::cout << "Invalid entry for the year : " << line[0] << line[1] << line[2] << line[3];
				std::cout << " in " << line  << std::endl;
				continue;
			}
		}
		for(int i = 5; i < 7; i++)
		{
			if (line[i] < '0' || line[i] > '9')
			{
				std::cout << "Inavalid entry for the month : " << line[5] << line[6] << std::endl;
				continue;
			}
		}
		for(int i = 8; i < 10; i++)
		{
			if (line[i] < '0' || line[i] > '9')
			{
				std::cout << "Inavalid entry for the day : " << line[8] << line[9] << std::endl;
				continue;
			}
		}
		int dot = 0;
		for(int i = 13; line[i]; i++)
		{
			if(line[i] == '.')
			{
				dot++;
				if(dot >= 2)
				{
					std::cout << "More than one dot in: " << line << std::endl;
					continue;
				}
			}
			else if (line[i] < '0' || line[i] > '9')
			{
				std::cout << "Invalid entry for the number of bit coin : " << line << std::endl;
				continue;
			}
		}
		fillmapinput(line, csvData, month);
	}
	return(0);
}

int createCSVMap(std::fstream &csv, std::map<int, float> &csvData, std::map<int, int> month)
{
	char line[40];
	csv.getline(line, 40);
	std::string strline(line);
	if(strline.compare("date,exchange_rate") != 0)
	{
		std::cout << "First line must be : date,exchange_rate" << std::endl;
		return(1);
	}
	while(!csv.eof())
	{
		csv.getline(line, 40);
		if(csv.eof() == 1)
			continue;
		if(line[4] != '-' || line[7] != '-' ||line[10] != ',')
		{
			std::cout << "Wrong format : YYYY-MM-DD,value" << std::endl;
			return(1);
		}
		for(int i = 0; i < 4; i++)
		{
			if (line[i] < '0' || line[i] > '9')
			{
				std::cout << "Wrong format : YYYY-MM-DD,value" << std::endl;
				return(1);
			}
		}
		for(int i = 5; i < 7; i++)
		{
			if (line[i] < '0' || line[i] > '9')
			{
				std::cout << "Wrong format : YYYY-MM-DD,value" << std::endl;
				return(1);
			}
		}
		for(int i = 8; i < 10; i++)
		{
			if (line[i] < '0' || line[i] > '9')
			{
				std::cout << "Wrong format : YYYY-MM-DD,value" << std::endl;
				return(1);
			}
		}
		int dot = 0;
		for(int i = 11; line[i]; i++)
		{
			if(line[i] == '.')
			{
				dot++;
				if(dot >= 2)
				{
					std::cout << "Wrong format : YYYY-MM-DD,value" << std::endl;
					return(1);
				}
			}
			else if (line[i] < '0' || line[i] > '9')
			{
				std::cout << "Wrong format : YYYY-MM-DD,value" << std::endl;
				return(1);
			}
		}
		fillmapcsv(line, csvData, month);
	}
	return(0);
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
	std::map<int, int> month;
	std::map<int, float> csvData;
	if(check(argc, argv[1], input, csv) == 1)
		return(1);
	mapformonth(month);
	if(createCSVMap(csv, csvData, month) == 1)
		return(1);
	createInputMap(input, csvData, month);
	csv.close();
	input.close();
}