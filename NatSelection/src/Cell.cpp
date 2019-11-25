#include "Cell.h"

Cell::Cell()
	:object()
{
}

void Cell::SetObject(std::string object)
{
	this->object = object;
}

void Cell::RemoveObject()
{
	this->object = "";
}

const std::string& Cell::GetObject()
{
	return this->object;
}
