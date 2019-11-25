#pragma once

#include <string>

class Cell
{
private:
	std::string object;

public:
	Cell();

	void SetObject(std::string object);
	void RemoveObject();
	const std::string& GetObject();
};