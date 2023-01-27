#include "Inventory.h"
#include <iostream>

BackPack::BackPack(int width, int height)
{
	this->_pivot.x = width;
	this->_pivot.y = height;
	this->weaponColumns = 2;
	this->weaponRows = 4;
	this->_weaponIndex = 0;
	this->_weaponSlotSize = 8;
	this->_page = 0;
	this->_page = 0;
	this->_sizeInventory = 0;
	this->_numberItems = 0;
	this->mouseX = 0;
	this->mouseY = 0;
	this->_selectedItem = NULL;
}

BackPack::BackPack(int width, int height, int rows, int columns)
{
	this->_pivot.x = width;
	this->_pivot.y = height;
	this->weaponColumns = columns;
	this->weaponRows = rows;
	this->_weaponIndex = 0;
	this->_weaponSlotSize = 8;
	this->_page = 0;
	this->_sizeInventory = 0;
	this->_numberItems = 0;
	this->mouseX = 0;
	this->mouseY = 0;
	this->_selectedItem = NULL;
}

BackPack::~BackPack()
{
	for (Item* item : _items){ delete item; }
	for (Item* item : _inventory){ delete item; }
}

// Add a weapon to the backpack
void BackPack::AddWeapon(const char* name, const char* path, WeaponType type)
{
	Weapon *aux = new Weapon(name, type);
	_items.push_back(aux);
	int column = _weaponIndex / 2;
	int row = _weaponIndex % 2;
	aux->Load(path, row, column, _pivot.x, _pivot.y);
	if (_weaponIndex < _weaponSlotSize - 1) { _weaponIndex++; }
	else { _weaponIndex = 0; }
	_numberItems++;
}

// Rearenge weapons how the need to look and be
void BackPack::ArrangeWeapons() 
{
	int count = 0;
	for (Item* item : _items)
	{
		int column = count / 2;
		int row = count % 2;
		item->Load(item->GetImgPath(), row, column, _pivot.x, _pivot.y);
		if (count > 0) { item->SetVisible(false); }
		else { item->SetVisible(true); }
		if (count < _weaponSlotSize - 1) { count++; }
		else { count=  0; }
	}
}

// Rearenge inventory how the need to look and be
void BackPack::ArrangeInventory() 
{
	int count = 0;
	for (Item* item : _inventory) 
	{
		item->Equip("assets/walk1.png", count, 200, 200);
		count++;
	}
}

// On development
Item BackPack::CreateItem(int type)
{
	return Item();
}

// One time click. Turn on overlay to select item
void BackPack::ClickWeapon(int x, int y) 
{
	Img::LoadImage("assets/overlayWeapon.png", _overlay);
	for (Item* item : _items)
	{
		if (item->IsTouching(x, y, &_overlay)) {
			_clicked = true;
			return;
		}
	}
	for (Item* item : _inventory)
	{
		if (item->IsTouching(x, y, &_overlay)) {
			_clicked = true;
			return;
		}
	}
	_clicked = false;
}

// While holding mouse buton, grab an item and move it
void BackPack::ClickHold(int x, int y)
{
	mouseX = x;
	mouseY = y;
	if (!_holding) {
		for (Item* item : _items)
		{
			if (item->IsTouching(x, y) && item->GetVisible()) {
				_selectedItem = item;
				_holding = true;
				return;
			}
		}		
		for (Item* item : _inventory)
		{
			if (item->IsTouching(x, y) && item->GetVisible()) {
				_selectedItem = item;
				_holding = true;
				return;
			}
		}
	}
	_holding = false;
}

// Release mouse buton and drop item. If valid position, will change store
void BackPack::ClickRelease(int x, int y) 
{
	if (_selectedItem == NULL) return;
	_holding = false;
	if (
			// Toca inventario
			(_selectedItem->GetImage()->rect.x > 200 && _selectedItem->GetImage()->rect.x < 500) &&
			(_selectedItem->GetImage()->rect.y > 200 && _selectedItem->GetImage()->rect.y < 600)
		) 
	{
		if (!_selectedItem->GetEquipped())
		{
			_inventory.push_back(_selectedItem);
			int i = 0;
			for (Item* item : _items) {
				if (_selectedItem == item) {
					_items.erase(_items.begin() + i);
					break;
				}
				i++;
				//else return;
			}
			_selectedItem->Equip("assets/walk1.png", _sizeInventory, 200, 200);
			_selectedItem->SetEquipped(true);
			_sizeInventory++;
			ArrangeWeapons();
			ArrangeInventory();
			return;
		}
		else {
			_selectedItem->SnapBack();
		}
	}
	if (
		// Toca mochila
		(_selectedItem->GetImage()->rect.x > 1350 && _selectedItem->GetImage()->rect.x < 1750) &&
		(_selectedItem->GetImage()->rect.y > 300 && _selectedItem->GetImage()->rect.y < 800)
		) 
	{
		if (_selectedItem->GetEquipped())
		{
			_items.push_back(_selectedItem);
			int i = 0;
			for (Item* item : _inventory) {
				if (_selectedItem == item) {
					_inventory.erase(_inventory.begin() + i);
					break;
				} 
				i++;
				//else return;
			}
			_selectedItem->SetEquipped(false);
			_sizeInventory--;
			ArrangeWeapons();
			ArrangeInventory();
			return;
		}
		else {
			_selectedItem->SnapBack();
		}
	}
	else {
		_selectedItem->SnapBack();
	}

	
}

// Render all items in backpack
void BackPack::RenderItems(SDL_Renderer* renderer, int x, int y)
{
	int i = 0;
	int begin = _weaponSlotSize * _page;
	int end = 7 * (_page + 1);
	for (Item* item : _items) 
	{ 
		if (i >= begin && i <= end) {
			item->Render(renderer); 
			item->SetVisible(true);
		} else item->SetVisible(false);
		i++; 
	}
	i = 0;
	for (Item* item : _inventory) 
	{ 
			item->Render(renderer); 
			item->SetVisible(true);
		i++; 
	}
	if (_clicked && !_holding) SDL_RenderCopy(renderer, _overlay.texture, NULL, &_overlay.rect);
	if (_holding)
	{
		std::cout << "Holding: " << mouseX << "\t" << mouseY << std::endl;
		_selectedItem->GetImage()->rect.x = x - (_selectedItem->GetImage()->rect.w / 2);
		_selectedItem->GetImage()->rect.y = y - (_selectedItem->GetImage()->rect.h / 2);
	}
}

// Backpack Pagination
void BackPack::WeaponRight() 
{
	_clicked = false;
	if (_page < 2)this->_page++; else this->_page = 0;
}
void BackPack::WeaponLeft() 
{
	_clicked = false;
	if (_page > 0)this->_page--; else this->_page = 2;
}