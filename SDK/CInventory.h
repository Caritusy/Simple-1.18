#pragma once
#include "CItem.h"
class C_Inventory {
};

class C_PlayerInventoryProxy {
private:
	char pad_0x0000[0x4];  //0x0000
public:
	int selectedHotbarSlot;  //0x0010
private:
	char pad_0x0014[0xAC];  //0x0014
public:
	C_Inventory* inventory;  //0x00B4
};
class CInventory
{
};

