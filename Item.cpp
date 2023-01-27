#include "Item.h"

Item::Item() 
{
    this->_name = NULL;
    this->_imgPath = NULL;
}

Item::~Item()
{
}

// Load img. The grid is the ssystem which decides where the item is going to be placed
void Item::Load(const char* imgPath, int gridX, int gridY, int Width, int Height)
{
    _imgPath = imgPath;
    Img::LoadImage(imgPath, _image);
    _last_position.x = _image.rect.x = (_image.rect.w * (gridX)) + Width;
    _last_position.y = _image.rect.y = (_image.rect.h * (gridY+1)) + Height;
}

void Item::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, _image.texture, NULL, &_image.rect);
}

bool Item::IsTouching(int x, int y)
{
    if (
        (_image.rect.x < x) && x < (_image.rect.x + _image.rect.w) &&
        (_image.rect.y < y) && y < (_image.rect.y + _image.rect.h)
        )
    {
        return true;
    }
    else
        return false;
}

bool Item::IsTouching(int x, int y, Img::Image* img)
{
    if (
        (_image.rect.x < x) && x < (_image.rect.x + _image.rect.w) &&
        (_image.rect.y < y) && y < (_image.rect.y + _image.rect.h)
        ) 
    {
        img->rect.x = _image.rect.x;
        img->rect.y = _image.rect.y;
        img->rect.w = _image.rect.w;
        img->rect.h = _image.rect.h;
        return true;
    }
    else
        return false;
}

bool Item::IsSelected() {
    return this->_selected;
}

bool Item::GetVisible()
{
    return _visible;
}

void Item::SetVisible(bool visible)
{
    _visible = visible;
}

const char* Item::GetName()
{
    return _name;
}

void Item::SetName(const char* name)
{
    _name = name;
}

bool Item::GetEquipped()
{
    return _equipped;
}

void Item::SetEquipped(bool equipped)
{
    _equipped = equipped;
}

const char* Item::GetImgPath()
{
    return _imgPath;
}

Img::Image* Item::GetImage()
{
    return &this->_image;
}

void Item::Equip(const char* path, int row, int x, int y)
{
    _last_position.x = _image.rect.x = x;
    _last_position.y = _image.rect.y = (_image.rect.h * (row)) + y;
}

void Item::SnapBack()
{
    _image.rect.x = _last_position.x;
    _image.rect.y = _last_position.y;
}
