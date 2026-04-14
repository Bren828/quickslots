/*
*
*
*
*   ---------------------------------------------------
*
*	Creater - @Bren828 					
*									14 April 2026
*
*   Version: 1.1
*
*   ---------------------------------------------------
*
*
*	https://github.com/Bren828/quickSlots
*
*
*
*/

#if defined _quickslots_included 
	#endinput
#endif
#define _quickslots_included


#if !defined QS_MAX_SLOTS
    #define QS_MAX_SLOTS 8
#endif


#if !defined QS_POSITION_X
    #define QS_POSITION_X 321.0
#endif

#if !defined QS_POSITION_Y
    #define QS_POSITION_Y 400.0
#endif

#if !defined QS_INDENT_X
    #define QS_INDENT_X 32.0
#endif


#if !defined QS_COLOR_BACKGROUND
    #define QS_COLOR_BACKGROUND 0x00000077
#endif

#if !defined QS_COLOR_FOREGROUND
    #define QS_COLOR_FOREGROUND 0x32323288
#endif

#if !defined QS_COLOR_SELECTED
    #define QS_COLOR_SELECTED 0x626262AA
#endif

#if !defined QS_TEXT_COLOR_VALUE
    #define QS_TEXT_COLOR_VALUE 0xFFFFFFFF
#endif



enum E_QUICK_SLOTS {
    bool:qs_IsVisible,
    qs_SelectedSlot,

    qs_ModelID[QS_MAX_SLOTS], 
    Float:qs_RotX[QS_MAX_SLOTS], 
    Float:qs_RotY[QS_MAX_SLOTS], 
    Float:qs_RotZ[QS_MAX_SLOTS], 
    Float:qs_Zoom[QS_MAX_SLOTS],
    qs_ItemCount[QS_MAX_SLOTS],
    qs_Extra[QS_MAX_SLOTS],

    PlayerText:qs_TD_Background[QS_MAX_SLOTS],
    PlayerText:qs_TD_Item[QS_MAX_SLOTS],
    PlayerText:qs_TD_CountText[QS_MAX_SLOTS]
}
static quickSlots[MAX_PLAYERS][E_QUICK_SLOTS];
static const NULL_quickslots[E_QUICK_SLOTS];



stock ShowQuickSlots(playerid) {

    if(IsQuickSlotsVisible(playerid)) {
        return 0;
    }

    quickSlots[playerid][qs_IsVisible] = true;

    new Float:PosX = QS_POSITION_X - ((QS_INDENT_X * QS_MAX_SLOTS) * 50) / 100, // get center
        string[11];

    for(new slot; slot < QS_MAX_SLOTS; slot ++) {

        quickSlots[playerid][qs_TD_Background][slot] = PlayerText:INVALID_TEXT_DRAW;
        quickSlots[playerid][qs_TD_Item][slot] = PlayerText:INVALID_TEXT_DRAW;
        quickSlots[playerid][qs_TD_CountText][slot] = PlayerText:INVALID_TEXT_DRAW;


        #if QS_COLOR_BACKGROUND != 0x00000000
            quickSlots[playerid][qs_TD_Background][slot] = CreatePlayerTextDraw(playerid, PosX + 1.4, QS_POSITION_Y + 1.6, "_");
            PlayerTextDrawLetterSize(playerid, quickSlots[playerid][qs_TD_Background][slot], 0.0, 3.5);
            PlayerTextDrawUseBox(playerid, quickSlots[playerid][qs_TD_Background][slot], 1);
            PlayerTextDrawTextSize(playerid, quickSlots[playerid][qs_TD_Background][slot], PosX + 28.4, 0.0);
            PlayerTextDrawBoxColor(playerid, quickSlots[playerid][qs_TD_Background][slot], QS_COLOR_BACKGROUND);
            PlayerTextDrawShow(playerid, quickSlots[playerid][qs_TD_Background][slot]);
        #endif


		quickSlots[playerid][qs_TD_Item][slot] = CreatePlayerTextDraw(playerid, PosX + 0.5, QS_POSITION_Y + 0.5, "_");
        PlayerTextDrawBackgroundColor(playerid, quickSlots[playerid][qs_TD_Item][slot], 
            (quickSlots[playerid][qs_SelectedSlot] == slot) ? (QS_COLOR_SELECTED) : (QS_COLOR_FOREGROUND) );
        
        PlayerTextDrawFont(playerid, quickSlots[playerid][qs_TD_Item][slot], 5);
		PlayerTextDrawLetterSize(playerid, quickSlots[playerid][qs_TD_Item][slot], 0.5000, 1.0000);
		PlayerTextDrawColor(playerid, quickSlots[playerid][qs_TD_Item][slot], 0xFFFFFFFF);
		PlayerTextDrawUseBox(playerid, quickSlots[playerid][qs_TD_Item][slot], 1);
		PlayerTextDrawBoxColor(playerid, quickSlots[playerid][qs_TD_Item][slot], 0x00000000);
		PlayerTextDrawTextSize(playerid, quickSlots[playerid][qs_TD_Item][slot], 28.7000, 33.8997);
        PlayerTextDrawSetPreviewModel(playerid, quickSlots[playerid][qs_TD_Item][slot], 
            (quickSlots[playerid][qs_ModelID][slot] == 0) ? (18691) : (quickSlots[playerid][qs_ModelID][slot]));
        
        if(quickSlots[playerid][qs_ModelID][slot] == 0) {
            PlayerTextDrawSetPreviewRot(playerid, quickSlots[playerid][qs_TD_Item][slot], 0.0, 0.0, 0.0, 0.0);
        }
        else {
            PlayerTextDrawSetPreviewRot(playerid, quickSlots[playerid][qs_TD_Item][slot], 
                quickSlots[playerid][qs_RotX][slot], 
                quickSlots[playerid][qs_RotY][slot], 
                quickSlots[playerid][qs_RotZ][slot], 
                quickSlots[playerid][qs_Zoom][slot]);
        }
        PlayerTextDrawSetSelectable(playerid, quickSlots[playerid][qs_TD_Item][slot], true);
		PlayerTextDrawShow(playerid, quickSlots[playerid][qs_TD_Item][slot]);


        if(quickSlots[playerid][qs_ItemCount][slot] != 0) {
            format(string, sizeof(string), "%d", quickSlots[playerid][qs_ItemCount][slot]);
        }
        else {
            string = "_";
        }
        
        quickSlots[playerid][qs_TD_CountText][slot] = CreatePlayerTextDraw(playerid, PosX + 27.0, QS_POSITION_Y + 26.0, string);
        PlayerTextDrawAlignment(playerid, quickSlots[playerid][qs_TD_CountText][slot], 3);
        PlayerTextDrawBackgroundColor(playerid, quickSlots[playerid][qs_TD_CountText][slot], 0x000000FF);
        PlayerTextDrawFont(playerid, quickSlots[playerid][qs_TD_CountText][slot], 2);
        PlayerTextDrawLetterSize(playerid, quickSlots[playerid][qs_TD_CountText][slot], 0.1400, 0.6499);
        PlayerTextDrawColor(playerid, quickSlots[playerid][qs_TD_CountText][slot], QS_TEXT_COLOR_VALUE);
        PlayerTextDrawSetProportional(playerid, quickSlots[playerid][qs_TD_CountText][slot], 1);
        PlayerTextDrawSetShadow(playerid, quickSlots[playerid][qs_TD_CountText][slot], 0);
        PlayerTextDrawShow(playerid, quickSlots[playerid][qs_TD_CountText][slot]);

        PosX += QS_INDENT_X;	
    }

    return 1;
}


stock HideQuickSlots(playerid) {

    if(!IsQuickSlotsVisible(playerid)) {
        return 0;
    }
    quickSlots[playerid][qs_IsVisible] = false;

    for(new slot; slot < QS_MAX_SLOTS; slot ++) {

        if(quickSlots[playerid][qs_TD_Background][slot] != PlayerText:INVALID_TEXT_DRAW) {
            PlayerTextDrawDestroy(playerid, quickSlots[playerid][qs_TD_Background][slot]);
            quickSlots[playerid][qs_TD_Background][slot] = PlayerText:INVALID_TEXT_DRAW;
        }

        if(quickSlots[playerid][qs_TD_Item][slot] != PlayerText:INVALID_TEXT_DRAW) {
            PlayerTextDrawDestroy(playerid, quickSlots[playerid][qs_TD_Item][slot]);
            quickSlots[playerid][qs_TD_Item][slot] = PlayerText:INVALID_TEXT_DRAW;
        }

        if(quickSlots[playerid][qs_TD_CountText][slot] != PlayerText:INVALID_TEXT_DRAW) {
            PlayerTextDrawDestroy(playerid, quickSlots[playerid][qs_TD_CountText][slot]);
            quickSlots[playerid][qs_TD_CountText][slot] = PlayerText:INVALID_TEXT_DRAW;
        }
    }
    return 1;
}


stock IsQuickSlotsVisible(playerid) {
    return quickSlots[playerid][qs_IsVisible];
}


stock SetQuickSlotModel(playerid, slot, modelid, Float:rotX = 0.0, Float:rotY = 0.0, Float:rotZ = 0.0, Float:zoom = 1.0, itemCount = 0) {

    if(slot < 0 || slot >= QS_MAX_SLOTS) {
        return 0;
    }

    quickSlots[playerid][qs_ModelID][slot] = modelid;
    quickSlots[playerid][qs_RotX][slot] = (modelid != 0) ? (rotX) : (0.0);
    quickSlots[playerid][qs_RotY][slot] = (modelid != 0) ? (rotY) : (0.0);
    quickSlots[playerid][qs_RotZ][slot] = (modelid != 0) ? (rotZ) : (0.0);
    quickSlots[playerid][qs_Zoom][slot] = (modelid != 0) ? (zoom) : (0.0);
    quickSlots[playerid][qs_ItemCount][slot] = itemCount;

    if(IsQuickSlotsVisible(playerid)) {

        PlayerTextDrawSetPreviewModel(playerid, quickSlots[playerid][qs_TD_Item][slot], (modelid != 0) ? (modelid) : (18691));
        PlayerTextDrawSetPreviewRot(playerid, quickSlots[playerid][qs_TD_Item][slot], 
            quickSlots[playerid][qs_RotX][slot], 
            quickSlots[playerid][qs_RotY][slot], 
            quickSlots[playerid][qs_RotZ][slot], 
            quickSlots[playerid][qs_Zoom][slot]);

        PlayerTextDrawShow(playerid, quickSlots[playerid][qs_TD_Item][slot]);

        new string[11] = "_";
        if(itemCount != 0) {
            format(string, sizeof(string), "%d", itemCount);
        }
        PlayerTextDrawSetString(playerid, quickSlots[playerid][qs_TD_CountText][slot], string);
    }

    return 1;
}


stock GetQuickSlotModel(playerid, slot, &modelid, &Float:rotX = 0.0, &Float:rotY = 0.0, &Float:rotZ = 0.0, &Float:zoom = 0.0, &itemCount = 0) {

    if(slot < 0 || slot >= QS_MAX_SLOTS) {
        return 0;
    }

    modelid = quickSlots[playerid][qs_ModelID][slot];
    rotX = quickSlots[playerid][qs_RotX][slot];
    rotY = quickSlots[playerid][qs_RotY][slot];
    rotZ = quickSlots[playerid][qs_RotZ][slot];
    zoom = quickSlots[playerid][qs_Zoom][slot];
    itemCount = quickSlots[playerid][qs_ItemCount][slot];

    return 1;
}


stock SetQuickSlotItemCount(playerid, slot, itemCount) {

    if(slot < 0 || slot >= QS_MAX_SLOTS) {
        return 0;
    }

    quickSlots[playerid][qs_ItemCount][slot] = itemCount;

    if(IsQuickSlotsVisible(playerid)) {
        new string[11] = "_";

        if(itemCount != 0) {
            format(string, sizeof(string), "%d", itemCount);
        }
        PlayerTextDrawSetString(playerid, quickSlots[playerid][qs_TD_CountText][slot], string);
    }

    return 1;
}


stock GetQuickSlotItemCount(playerid, slot) {

    if(slot < 0 || slot >= QS_MAX_SLOTS) {
        return 0;
    }

    return quickSlots[playerid][qs_ItemCount][slot];
}


stock SetQuickSlotExtraValue(playerid, slot, value) {

    if(slot < 0 || slot >= QS_MAX_SLOTS) {
        return 0;
    }

    quickSlots[playerid][qs_Extra][slot] = value;
    return 1;
}


stock GetQuickSlotExtraValue(playerid, slot) {

    if(slot < 0 || slot >= QS_MAX_SLOTS) {
        return 0;
    }

    return quickSlots[playerid][qs_Extra][slot];
}


stock SetQuickSlotSelected(playerid, slot) {

    if(slot < 0 || slot >= QS_MAX_SLOTS) {
        return 0;
    }

    if(quickSlots[playerid][qs_SelectedSlot] == slot) {
        return 0;
    }

    if(IsQuickSlotsVisible(playerid)) {
        PlayerTextDrawBackgroundColor(playerid, quickSlots[playerid][qs_TD_Item][quickSlots[playerid][qs_SelectedSlot]], QS_COLOR_FOREGROUND);
        PlayerTextDrawShow(playerid, quickSlots[playerid][qs_TD_Item][quickSlots[playerid][qs_SelectedSlot]]);
        
        PlayerTextDrawBackgroundColor(playerid, quickSlots[playerid][qs_TD_Item][slot], QS_COLOR_SELECTED);
        PlayerTextDrawShow(playerid, quickSlots[playerid][qs_TD_Item][slot]);
    }

    quickSlots[playerid][qs_SelectedSlot] = slot;
    return 1;
}


stock GetQuickSlotSelected(playerid) {
    return quickSlots[playerid][qs_SelectedSlot];
}



#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerConnect(playerid)
#else
	public OnPlayerConnect(playerid)
#endif
{
    quickSlots[playerid] = NULL_quickslots;

	#if !defined _inc_y_hooks && !defined _INC_y_hooks && defined OnPlayerConnect_QS
        return OnPlayerConnect_QS(playerid);
    #else 
        return 1;
    #endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect OnPlayerConnect_QS

	#if defined OnPlayerConnect_QS
		forward OnPlayerConnect_QS(playerid);
	#endif
#endif



#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
#else
	public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
#endif
{
    if(IsQuickSlotsVisible(playerid)) {

        for(new slot; slot < QS_MAX_SLOTS; slot ++) {

            if(playertextid != quickSlots[playerid][qs_TD_Item][slot]) {
                continue;
            }

            #if defined OnPlayerClickQuickSlot
                OnPlayerClickQuickSlot(playerid, 
                    slot, 
                    quickSlots[playerid][qs_ModelID][slot], 
                    quickSlots[playerid][qs_ItemCount][slot], 
                    quickSlots[playerid][qs_Extra][slot]);
            #endif
            return 1;
        }
    }

    #if !defined _inc_y_hooks && !defined _INC_y_hooks && defined OnPlayerClickPlayerTextDraw_QS
        return OnPlayerClickPlayerTextDraw_QS(playerid, playertextid);
    #else 
        return 1;
    #endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerClickPlayerTextDra
		#undef OnPlayerClickPlayerTextDraw
	#else
		#define _ALS_OnPlayerClickPlayerTextDra
	#endif
	#define OnPlayerClickPlayerTextDraw OnPlayerClickPlayerTextDraw_QS

	#if defined OnPlayerClickPlayerTextDraw_QS
		forward OnPlayerClickPlayerTextDraw_QS(playerid, PlayerText:playertextid);
	#endif
#endif