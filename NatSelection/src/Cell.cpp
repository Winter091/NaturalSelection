#include "Cell.h"

Cell::Cell()
	:object()
{
}

void Cell::SetObject(Objects object)
{
	this->object = object;
}

void Cell::RemoveObject()
{
	this->object = Objects::NONE;
}

Objects Cell::GetObject()
{
	return this->object;
}
