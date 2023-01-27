#pragma once
#include "image.h"

class Manufacturer
{
public:
	Manufacturer(const char*);
	~Manufacturer();
private:
	Img::Image _img;
	const char* _name;
};

const Manufacturer Atlas("hola");
const Manufacturer Dahl("hola");
const Manufacturer Eridian("hola");
const Manufacturer Hyperion("hola");
const Manufacturer Jakobs("hola");