


/*  Example 1

    The first option is full control using buttons via the OnPlayerKeyStateChange public

    H key - Select the desired slot. Scroll to the right.
    Y key - Select the desired slot. Scroll to the left.
    The N key is to Hide show slots.
    L-ALT key - Interaction with the selected slot.

*/


public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CTRL_BACK) // H button - Select the desired slot. Scroll to the right .
    {
        if(IsPlayerShowQuickSlots(playerid)) SetQuickSlotSelected(playerid, GetQuickSlotSelected(playerid)+1);

        return 1;
    }
    else if(newkeys & KEY_YES) //Y button - Select the desired slot. Scroll to the left.
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
        if(IsPlayerShowQuickSlots(playerid)) // checking that slots are shown
        {
            new slot = GetQuickSlotSelected(playerid), // We get the number of the selected slot
                modelid;

            GetQuickSlotModel(playerid, slot, modelid); // We get the model of the selected slot
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
                    SendClientMessage(playerid, -1, "Did you eat pepperoni pizza.");
                    return 1;
                }
                case 19577:// example usage with quantity
                {
                    new value = GetQuickSlotValue(playerid, slot);// We get the number of items in the slot
                    if(value >= 2) //If more than 2, then we subtract one
                    {
                        SetQuickSlotValue(playerid, slot, value-1);
                    }
                    else SetQuickSlotModel(playerid, slot, 0); // If there is one left, then we delete the item of their slot

                    SendClientMessage(playerid, -1, "Have you eaten a peach.");
                    return 1;
                }
            }
        }
        return 1;
    }
    return 1;
}




/*  Example 2

    The second option is to select using the cursor.

    N key - Hide show slots
    H key - Show cursor

*/ 

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CTRL_BACK) //H button - Hide show slots
    {
        if(!IsPlayerShowQuickSlots(playerid)) ShowQuickSlots(playerid);
        else HideQuickSlots(playerid);
        return 1;
    }
    else if(newkeys & KEY_NO) // button N - Show the cursor
    {
        if(IsPlayerShowQuickSlots(playerid)) 
        {
            SelectTextDraw(playerid, -1);
            return 1;
        }
        return 1;
    }
    return 1;
}

forward OnPlayerQuickSlotSelected(playerid, slot, modelid, value, extra_value); 
public OnPlayerQuickSlotSelected(playerid, slot, modelid, value, extra_value) // Called when the cursor clicks on the slot
{
    SetQuickSlotSelected(playerid, slot); // Select the desired slot.

    if(modelid == 0) return 1; 
    switch(modelid)
    {
        case 1546:
        {
            SetQuickSlotModel(playerid, slot, 0);
            SendClientMessage(playerid, -1, "You drank sprunk");
            return 1;
        }
        case 2702:
        {
            SetQuickSlotModel(playerid, slot, 0);
            SendClientMessage(playerid, -1, "Did you eat pepperoni pizza.");
            return 1;
        }
        case 19577:// example usage with quantity
        {
            if(value >= 2) // If more than 2, then we subtract one
            {
                SetQuickSlotValue(playerid, slot, value-1);
            }
            else SetQuickSlotModel(playerid, slot, 0); // If there is one left, then we delete the item of their slot

            SendClientMessage(playerid, -1, "Have you eaten a peach.");
            return 1;
        }
    }

    return 1;
}


/*  Example 3

    The third option is similar to the second, only using the selected slot using the Y button

    H key - Hide show slots.
    The N key is to show the cursor.
    The Y key is the interaction with the selected slot.

*/

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CTRL_BACK) // H button - Hide show slots
    {
        if(!IsPlayerShowQuickSlots(playerid)) ShowQuickSlots(playerid);
        else HideQuickSlots(playerid);
        return 1;
    }
    else if(newkeys & KEY_NO) // button N - Show the cursor
    {
        if(IsPlayerShowQuickSlots(playerid)) 
        {
            SelectTextDraw(playerid, -1);
            return 1;
        }
        return 1;
    }
    else if(newkeys & KEY_YES) //Y button - Interaction with the slot
    {
        if(IsPlayerShowQuickSlots(playerid)) // checking that slots are shown
        {
            new slot = GetQuickSlotSelected(playerid), // We get the number of the selected slot
                modelid;

            GetQuickSlotModel(playerid, slot, modelid); // We get the model of the selected slot
            if(modelid == 0) return 1; //if 0 then we do not go further

            switch(modelid)
            {
                case 1546:
                {
                    SetQuickSlotModel(playerid, slot, 0);
                    SendClientMessage(playerid, -1, "You drank sprunk");
                    return 1;
                }
                case 2702:
                {
                    SetQuickSlotModel(playerid, slot, 0);
                    SendClientMessage(playerid, -1, "Did you eat pepperoni pizza.");
                    return 1;
                }
                case 19577:// example usage with quantity
                {
                    new value = GetQuickSlotValue(playerid, slot);// We get the number of items in the slot
                    if(value >= 2) // If more than 2, then we subtract one
                    {
                        SetQuickSlotValue(playerid, slot, value-1);
                    }
                    else SetQuickSlotModel(playerid, slot, 0); // If there is one left, then we delete the item of their slot

                    SendClientMessage(playerid, -1, "Have you eaten a peach.");
                    return 1;
                }
            }
        }
        return 1;
    }
    return 1;
}

forward OnPlayerQuickSlotSelected(playerid, slot, modelid, value, extra_value);
public OnPlayerQuickSlotSelected(playerid, slot, modelid, value, extra_value) // Called when the cursor clicks on the slot
{
    SetQuickSlotSelected(playerid, slot); // Select the desired slot.
    return 1;
}