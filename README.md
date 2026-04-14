# quickslots
Quickslots for samp inventory

![Crosshair](https://raw.githubusercontent.com/Bren828/quickslots/main/preview.gif)

## Reference
* [Installation](https://github.com/Bren828/quickslots#installation)
* [Example](https://github.com/Bren828/quickslots#example)
* [Callbacks](https://github.com/Bren828/quickslots#callbacks)
* [Functions](https://github.com/Bren828/quickslots#functions)
* [Definition](https://github.com/Bren828/quickslots#definition)


## Installation

Include in your code and begin using the library:
```pawn
#include <quickslots>
```

## Example
```pawn
CMD:test(playerid) {

    //Set items in slots 0, 2, 6

    SetQuickSlotModel(playerid, 0, 19577, 300.00, 0.00, 0.00, 0.62); // Peach
    SetQuickSlotModel(playerid, 2, 2702, -153.00, -40.00, 261.00, 0.82); // Pepperoni pizza
    SetQuickSlotModel(playerid, 6, 1546, -20.00, 0.00, 44.00, 0.97); // Sprunk
   
    SetQuickSlotItemCount(playerid, 0, 10); // We will give the first slot the number of 10 peaches
	SetQuickSlotExtraValue(playerid, 0, 50); // Other values

	//printf("%d", GetQuickSlotItemCount(playerid, 0));
	//printf("%d", GetQuickSlotExtraValue(playerid, 0));

    return 1;
}

// Called when the textdraw is clicked.
forward OnPlayerClickQuickSlot(playerid, slot, modelid, itemCount, extraValue);
public OnPlayerClickQuickSlot(playerid, slot, modelid, itemCount, extraValue) {

	printf("Click > Slot: %d | modelid: %d | itemCount: %d | extraValue: %d", slot, modelid, itemCount, extraValue);

	return 1;
}


public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {

    if(newkeys & KEY_CTRL_BACK) { // button H - Select the desired slot.  Scroll to the right.
    
        if(IsQuickSlotsVisible(playerid)) {
			SetQuickSlotSelected(playerid, GetQuickSlotSelected(playerid) + 1);
		}
        return 1;
    }

    else if(newkeys & KEY_YES) { // button Y - Select the desired slot.  Let's scroll left.
    
        if(IsQuickSlotsVisible(playerid)) {
			SetQuickSlotSelected(playerid, GetQuickSlotSelected(playerid) - 1);
		}
        return 1;
    }

    else if(newkeys & KEY_NO) { // button N - Hide show slots
    
        if(!IsQuickSlotsVisible(playerid)) {
			ShowQuickSlots(playerid);
		}
		else {
			HideQuickSlots(playerid);
		}
		return 1;
    }

    else if(newkeys & KEY_WALK) { // L-ALT button - Interaction with the slot
    
        if(IsQuickSlotsVisible(playerid)) { // Check for slot show
        
            new slot = GetQuickSlotSelected(playerid), // Get the number of the selected slot
                modelid;

            GetQuickSlotModel(playerid, slot, modelid); // Get the model of the selected slot
            if(modelid == 0) {
				return 1;
			}

            switch(modelid) {

                case 1546: {
                    SetQuickSlotModel(playerid, slot, 0);
                    SendClientMessage(playerid, -1, "You drank sprunk.");
                    return 1;
                }

                case 2702: {
                    SetQuickSlotModel(playerid, slot, 0);
                    SendClientMessage(playerid, -1, "You ate pepperoni pizza.");
                    return 1;
                }

                case 19577: { // Example use with quantity
                
                    new itemCount = GetQuickSlotItemCount(playerid, slot);// Get the quantity in the slot

                    if(itemCount >= 2) { // If more than 2, then we subtract one
                        SetQuickSlotItemCount(playerid, slot, itemCount - 1);
                    }
                    else {
						SetQuickSlotModel(playerid, slot, 0); // If there is only one left, then remove the item from the slot
					}

                    SendClientMessage(playerid, -1, "You ate a peach.");
                    return 1;
                }
            }
        }
    }

    return 1;
}
```

## Callbacks

#### public OnPlayerClickQuickSlot(playerid, slot, modelid, itemCount, extraValue)
> Called when the textdraw is clicked.
> * `playerid` - The ID of the player
> * `slot` - Slot number
> * `modelid` - Object model
> * `itemCount` - Quantity
> * `extraValue` - Extra value

## Functions

#### ShowQuickSlots(playerid)
> Display the quick slots interface for a player
> * `playerid` - The ID of the player

#### HideQuickSlots(playerid)
> Hide the quick slots interface for a player
> * `playerid` - The ID of the player

#### IsQuickSlotsVisible(playerid)
> Checks whether the Quick Slots are visible to the player
> * `playerid` - The ID of the player
> * Returns 1 if visible, 0 if hidden

#### SetQuickSlotSelected(playerid, slot)
> Set the number of the selected slot
> * `playerid` - The ID of the player
> * `slot` - Slot number

#### GetQuickSlotSelected(playerid)
> Get the number of the currently selected slot
> * `playerid` - The ID of the player
> * Returns the slot number

#### SetQuickSlotModel(playerid, slot, modelid, Float:rotX = 0.0, Float:rotY = 0.0, Float:rotZ = 0.0, Float:zoom = 1.0, itemCount = 0)
> Set the slot model data
> * `playerid` - The ID of the player
> * `slot` - Slot number
> * `modelid` - Object model
> * `Float:rotX` - The X rotation value.
> * `Float:rotY` - The Y rotation value.
> * `Float:rotZ` - The Z rotation value.
> * `Float:zoom` - The zoom value
> * `itemCount` - Quantity

#### GetQuickSlotModel(playerid, slot, &modelid, &Float:rotX = 0.0, &Float:rotY = 0.0, &Float:rotZ = 0.0, &Float:zoom = 0.0, &itemCount = 0)
> Get the slot model data
> * `playerid` - The ID of the player
> * `slot` - Slot number
> * `&modelid` - Object model
> * `&Float:rotX` - The X rotation value.
> * `&Float:rotY` - The Y rotation value.
> * `&Float:rotZ` - The Z rotation value.
> * `&Float:zoom` - The zoom value
> * `&itemCount` - Quantity

#### SetQuickSlotItemCount(playerid, slot, itemCount)
> Set the number of items in the slot.
> * `playerid` - The ID of the player
> * `slot` - Slot number
> * `itemCount` - Number of items

#### GetQuickSlotItemCount(playerid, slot)
> Get the number of items in the slot.
> * `playerid` - The ID of the player
> * `slot` - Slot number
> * Returns the number of items

#### SetQuickSlotExtraValue(playerid, slot, value)
> Set extra value
> * `playerid` - The ID of the player
> * `slot` - Slot number
> * `value` - Value

#### GetQuickSlotExtraValue(playerid, slot)
> Get extra value
> * `playerid` - The ID of the player
> * `slot` - Slot number
> * Returns the value


## Definition
```pawn
#define QS_MAX_SLOTS 8

#define QS_POSITION_X 321.0
#define QS_POSITION_Y 400.0
#define QS_INDENT_X 32.0

#define QS_COLOR_BACKGROUND 0x00000077
#define QS_COLOR_FOREGROUND 0x32323288
#define QS_COLOR_SELECTED 0x626262AA
#define QS_TEXT_COLOR_VALUE 0xFFFFFFFF
```
