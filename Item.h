#pragma once
#include "Manufacturer.h"

/*
* Item class
* Parent of all pickable items that can be stored in BackPack
* 
*/
class Item
{
public:

	Item();
	~Item();

	void Load(const char*, int, int, int, int);
	void Render(SDL_Renderer*);

	// Collition methods
	bool IsTouching(int, int, Img::Image*);
	bool IsTouching(int, int);

	// Return true if selected
	bool IsSelected();

	// Get set methods
	bool GetVisible();
	void SetVisible(bool);
	const char* GetName();
	void SetName(const char*);
	bool GetEquipped();
	void SetEquipped(bool);
	const char* GetImgPath();
	Img::Image* GetImage();

	// Moves between backpack to inventory
	void Equip(const char*, int, int, int);
	
	// Snap to last valid position
	void SnapBack();
private:

	// Get whole image
	Img::Image _image;

	// Last valid position
	Img::vector _last_position;
	
	// String with image path
	const char* _imgPath;

	/* bool type:
	*		selected; if the item is selected
	*		visible; if the item is rendered
	*		equipped; if the item is equiped on inventory
	*/
	bool _selected, _visible, _equipped = false;
protected:

	// Item's name
	const char* _name;
};

