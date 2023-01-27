#define main SDL_main
#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "image.h"
#include "Item.h"
#include "Weapon.h"
#include "Inventory.h"


void GameLoop(SDL_Window* window);