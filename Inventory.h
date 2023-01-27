#pragma once
#include "Weapon.h"
#include <vector>

/*
* 
* @BackPack CLASS
* 
*	Handles every aspect of each item that holds.
*	Can also create new Items.
* 
*	Currently can only hold Weapons.
* 
*/

class BackPack
{
public:

	BackPack(int, int);
	BackPack(int, int, int, int);
	~BackPack();

	void AddWeapon(const char*, const char*, WeaponType type);
	void ArrangeWeapons();
	void ArrangeInventory();

	Item CreateItem(int type); // On development

	void ClickWeapon(int, int);
	void ClickHold(int, int);
	void ClickRelease(int, int);

	void RenderItems(SDL_Renderer*, int, int);
	void WeaponRight();
	void WeaponLeft();
	int weaponRows, weaponColumns;
private:

	// Item ptr vector type: Holds every item in this backpack.
	std::vector<Item*> _items;

	// Item ptr vector type: Current holded weapons.
	std::vector<Item*> _inventory;

	// Item ptr type: Item currently selecte while holding mouse button or one time click
	Item* _selectedItem;

	// Image type: Static image used for the overlay texture.
	Img::Image _overlay;

	// vector type: X and Y coordinates used to store mouse position.
	Img::vector _pivot;

	/* int type : 
		weaponSlotSize; MAX WEAPONES WE CAN HAVE PER SLOT
		page; Current page
		weaponIndex; Where we are in grid
		numberItem; how many we have in backpack
		sizeInventory; who many we have in inventory
		mouseX, mouseY; coordinates of the mouse
	*/
	int _weaponSlotSize, _page, _weaponIndex, _numberItems, _sizeInventory , mouseX, mouseY;

	/* bool type :
		clicked; if something has been clicked
		holding; if holding an item
	*/
	bool _clicked = false, _holding = false;
};

