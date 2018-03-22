#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <time.h>

#define MAX_BUFF_SIZE 255

std::vector<int> numberHolder;

std::vector<std::string> getTokens(std::string code, const std::string delim)
{
	code.erase(std::remove(code.begin(), code.end(), '\n'), code.end());

	std::string token;
	std::string numberToken;
	std::vector<std::string> tokens;

	std::size_t pos = 0;
	while ((pos = code.find(delim)) != std::string::npos)
	{
		token = code.substr(0, pos);

		std::size_t n = token.find_first_of("0123456789");
		if (n != std::string::npos)
		{
			std::size_t m = token.find_first_not_of("0123456789", n);
			numberToken = token.substr(n, m != std::string::npos ? m - n : m);
			tokens.push_back(numberToken);

			token = token.substr(0, n - 1);
			tokens.push_back(token);
		}
		else
		{
			tokens.push_back(token);
		}

		code.erase(0, pos + delim.length());
	}

	return tokens;
}

std::string parseFile(const char *dataPath)
{
	std::ifstream code_file(dataPath);
	std::stringstream buffer;

	if (code_file.is_open())
	{
		buffer << code_file.rdbuf();

		return buffer.str();
	}
	else
	{
		fprintf(stderr, "Cannot open the file\n");
	}
}

void makeComputation(const std::string operation)
{
	
}

void processCode(const std::string bufferCode)
{
	std::vector<std::string> tokens = getTokens(bufferCode, ";");

	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i] == "PUSH")
		{
			std::string number = tokens[i - 1];
			numberHolder.push_back(std::stoi(number));
		}

		if (tokens[i] == "ADD")
		{
			if (numberHolder.size() >= 2)
			{
				int result = numberHolder[numberHolder.size() - 1] + numberHolder[numberHolder.size() - 2];
				numberHolder.pop_back();
				numberHolder.pop_back();
				numberHolder.push_back(result);
			}
			else if (numberHolder.size() == 1)
			{
				int result = numberHolder[numberHolder.size() - 1];
				numberHolder.pop_back();
				numberHolder.push_back(result);
			}
			else
			{
				int result = 0;
				numberHolder.push_back(result);
			}
		}

		if (tokens[i] == "MUL")
		{
			if (numberHolder.size() >= 2)
			{
				int result = numberHolder[numberHolder.size() - 1] * numberHolder[numberHolder.size() - 2];
				numberHolder.pop_back();
				numberHolder.pop_back();
				numberHolder.push_back(result);
			}
			else if (numberHolder.size() <= 1)
			{
				int result = 0;
				numberHolder.pop_back();
				numberHolder.push_back(result);
			}
		}

		if (tokens[i] == "DIV")
		{
			if (numberHolder.size() >= 2)
			{
				int result = numberHolder[numberHolder.size() - 1] / numberHolder[numberHolder.size() - 2];
				numberHolder.pop_back();
				numberHolder.pop_back();
				numberHolder.push_back(result);
			}
			else if (numberHolder.size() <= 1)
			{
				int result = 0;
				numberHolder.pop_back();
				numberHolder.push_back(result);
			}
		}

		if (tokens[i] == "END")
		{
			return;
		}
	}
}

int main()
{
	std::size_t timeStart = clock();

	const std::string code = parseFile("SCRIPT.txt");

	processCode(code);

	for (int i = 0; i < numberHolder.size(); i++)
	{
		std::cout << numberHolder[i] << std::endl;
	}

	std::size_t timeEnd = clock();

	std::cout << "Time : -> " << (timeEnd - timeStart) << std::endl;

	system("pause");
	return 0;
}


