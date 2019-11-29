#pragma once

#include <string>
#include <chrono>
#include <iostream>

class Timer
{
public:

	std::chrono::steady_clock::time_point start;
	std::string name;

	Timer(std::string name)
	{
		start = std::chrono::high_resolution_clock::now();
		this->name = name;
	}

	~Timer()
	{
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		std::cout << name << " " << duration << '\n';
	}
};
