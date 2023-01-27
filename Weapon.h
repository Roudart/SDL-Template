#pragma once
#include "Item.h"
enum WeaponType 
{
	AssaultRiffle,
	Pistol,
	RocketLauncher,
	Shotgun,
	SniperRiffle
};


class Weapon : public Item
{
public:
	Weapon(const char*, WeaponType);
	~Weapon();
private:
	WeaponType _type;
};
