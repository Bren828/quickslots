# quickslots
Quickslots for samp inventory

![Crosshair](https://raw.githubusercontent.com/Bren828/quickslots/main/preview.gif)

## Reference
* [Installation](https://github.com/Bren828/quickslots#installation)
* [Example](https://github.com/Bren828/quickslots#example)
* [Callbacks](https://github.com/Bren828/quickslots#example)
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
    //Выдадим предметы в слоты 0, 2, 6

    SetQuickSlotModel(playerid, 0, 19577, 300.00, 0.00, 0.00, 0.62); // Персик
    SetQuickSlotModel(playerid, 2, 2702, -153.00, -40.00, 261.00, 0.82); // Пицца пепперони
    SetQuickSlotModel(playerid, 6, 1546, -20.00, 0.00, 44.00, 0.97); // Sprunk
   
    SetQuickSlotValue(playerid, 0, 10); // Выдадим первому слоту количество из 10 персиков
    return 1;
}


public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CTRL_BACK) // кнопка H - Выбираем нужный слот. Листаем вправо .
    {
        if(IsPlayerShowQuickSlots(playerid)) SetQuickSlotSelected(playerid, GetQuickSlotSelected(playerid)+1);

        return 1;
    }
    else if(newkeys & KEY_YES) // кнопка Y - Выбираем нужный слот. Листаем влево.
    {
        if(IsPlayerShowQuickSlots(playerid)) SetQuickSlotSelected(playerid, GetQuickSlotSelected(playerid)-1);

        return 1;
    }
    else if(newkeys & KEY_NO) // кнопка N - Скрыть показать слоты
    {
        if(!IsPlayerShowQuickSlots(playerid)) ShowQuickSlots(playerid);
        else HideQuickSlots(playerid);
        return 1;
    }
    else if(newkeys & KEY_WALK) // кнопка L-ALT - Взаимодействие с слотом 
    {
        if(IsPlayerShowQuickSlots(playerid)) // проверка что показаны слоты
        {
            new slot = GetQuickSlotSelected(playerid), // Получаем номер выбранного слота 
                modelid;

            GetQuickSlotModel(playerid, slot, modelid); // Получаем модель выбранного слота 
            if(modelid == 0) return 1; // если 0 то не идем дальше

            switch(modelid)
            {
                case 1546:
                {
                    SetQuickSlotModel(playerid, slot, 0);
                    SendClientMessage(playerid, -1, "Вы выпили sprunk.");
                    return 1;
                }
                case 2702:
                {
                    SetQuickSlotModel(playerid, slot, 0);
                    SendClientMessage(playerid, -1, "Вы съели пиццу пепперони.");
                    return 1;
                }
                case 19577:// пример использование с количеством 
                {
                    new value = GetQuickSlotValue(playerid, slot);// Получаем количество предмета в слоте
                    if(value >= 2) // Если больше 2, то отнимаем один
                    {
                        SetQuickSlotValue(playerid, slot, value-1);
                    }
                    else SetQuickSlotModel(playerid, slot, 0); // Если остался один, то удаляем предмет их слота

                    SendClientMessage(playerid, -1, "Вы съели персик.");
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
#define QS_TD_FON_COLOR_BACK 0x00000077
#define QS_TD_FON_COLOR_MAIN 0x32323288
#define QS_TD_FON_COLOR_SELECTED 0x626262AA
#define QS_TD_COLOR_VALUE 0xFFFFFFFF
```
