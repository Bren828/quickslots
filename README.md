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
CMD:test(playerid)
{
    //Set items in slots 0, 2, 6

    SetQuickSlotModel(playerid, 0, 19577, 300.00, 0.00, 0.00, 0.62); // Peach
    SetQuickSlotModel(playerid, 2, 2702, -153.00, -40.00, 261.00, 0.82); // Pepperoni pizza
    SetQuickSlotModel(playerid, 6, 1546, -20.00, 0.00, 44.00, 0.97); // Sprunk
   
    SetQuickSlotValue(playerid, 0, 10); // We will give the first slot the number of 10 peaches
    return 1;
}


public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CTRL_BACK) // button H - Select the desired slot.  Scroll to the right.
    {
        if(IsPlayerShowQuickSlots(playerid)) SetQuickSlotSelected(playerid, GetQuickSlotSelected(playerid)+1);

        return 1;
    }
    else if(newkeys & KEY_YES) // button Y - Select the desired slot.  Let's scroll left.
    {
        if(IsPlayerShowQuickSlots(playerid)) SetQuickSlotSelected(playerid, GetQuickSlotSelected(playerid)-1);

        return 1;
    }
    else if(newkeys & KEY_NO) // button N - Hide show slots
    {
        if(!IsPlayerShowQuickSlots(playerid)) ShowQuickSlots(playerid);
        else HideQuickSlots(playerid);
        return 1;
    }
    else if(newkeys & KEY_WALK) // L-ALT button - Interaction with the slot
    {
        if(IsPlayerShowQuickSlots(playerid)) // Check for slot show
        {
            new slot = GetQuickSlotSelected(playerid), // Get the number of the selected slot
                modelid;

            GetQuickSlotModel(playerid, slot, modelid); // Get the model of the selected slot
            if(modelid == 0) return 1;

            switch(modelid)
            {
                case 1546:
                {
                    SetQuickSlotModel(playerid, slot, 0);
                    SendClientMessage(playerid, -1, "You drank sprunk.");
                    return 1;
                }
                case 2702:
                {
                    SetQuickSlotModel(playerid, slot, 0);
                    SendClientMessage(playerid, -1, "You ate pepperoni pizza.");
                    return 1;
                }
                case 19577:// Example use with quantity
                {
                    new value = GetQuickSlotValue(playerid, slot);// Get the quantity in the slot
                    if(value >= 2) // If more than 2, then we subtract one
                    {
                        SetQuickSlotValue(playerid, slot, value-1);
                    }
                    else SetQuickSlotModel(playerid, slot, 0); // If there is only one left, then remove the item from the slot

                    SendClientMessage(playerid, -1, "You ate a peach.");
                    return 1;
                }
            }
        }
        return 1;
    }
    return 1;
}
```

## Callbacks

#### public OnPlayerQuickSlotSelected(playerid, slot, modelid, value, extra_value)
> Called when the cursor clicks
> * `playerid` - The ID of the player
> * `slot` - Slot number
> * `modelid` - Object model
> * `value` - Value
> * `extra_value` - Extra value

## Functions

#### ShowQuickSlots(playerid)
> Show QuickSlots
> * `playerid` - The ID of the player

#### HideQuickSlots(playerid)
> Hide QuickSlots
> * `playerid` - The ID of the player

#### IsPlayerShowQuickSlots(playerid)
> Get status QuickSlots
> * `playerid` - The ID of the player
> * Returns the status (show/hide)

#### SetQuickSlotSelected(playerid, slot)
> Set selected slot
> * `playerid` - The ID of the player
> * `slot` - Slot number

#### GetQuickSlotSelected(playerid)
> Get selected slot
> * `playerid` - The ID of the player
> * Returns the slot number

#### SetQuickSlotModel(playerid, slot, modelid, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0, Float:fZoom = 1.0, value = 0)
> Set Model
> * `playerid` - The ID of the player
> * `slot` - Slot number
> * `modelid` - Object model
> * `Float:fRotX` - The X rotation value.
> * `Float:fRotY` - The Y rotation value.
> * `Float:fRotZ` - The Z rotation value.
> * `Float:fZoom` - The zoom value
> * `value` - Value

#### GetQuickSlotModel(playerid, slot, &modelid, &Float:fRotX = 0.0, &Float:fRotY = 0.0, &Float:fRotZ = 0.0, &Float:fZoom = 0.0, &value = 0)
> Get Model
> * `playerid` - The ID of the player
> * `slot` - Slot number
> * `&modelid` - Object model
> * `&Float:fRotX` - The X rotation value.
> * `&Float:fRotY` - The Y rotation value.
> * `&Float:fRotZ` - The Z rotation value.
> * `&Float:fZoom` - The zoom value
> * `&value` - Value

#### SetQuickSlotValue(playerid, slot, value)
> Set value
> * `playerid` - The ID of the player
> * `slot` - Slot number
> * `value` - Value

#### GetQuickSlotValue(playerid, slot)
> Get value
> * `playerid` - The ID of the player
> * Returns the value

#### SetQuickSlotExtraValue(playerid, slot, value)
> Set extra value
> * `playerid` - The ID of the player
> * `slot` - Slot number
> * `value` - Value

#### GetQuickSlotExtraValue(playerid)
> Get extra value
> * `playerid` - The ID of the player
> * Returns the value


## Definition
```pawn
#define QS_MAX_SLOTS 8

// position
#define QS_TD_POSITION_X 321.0
#define QS_TD_POSITION_Y 400.0
#define QS_TD_INDENT_X 32.0

// color
#define QS_TD_FON_COLOR_BACK 0x00000077 // value '0x00000000' disables TextDraw
#define QS_TD_FON_COLOR_MAIN 0x32323288
#define QS_TD_FON_COLOR_SELECTED 0x626262AA
#define QS_TD_COLOR_VALUE 0xFFFFFFFF
```
