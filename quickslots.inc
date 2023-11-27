/*
*
*
*
*   ---------------------------------------------------
*
*	Creater - @Bren828 					
*									27 November 2023
*
*   Version: 1.0
*
*   ---------------------------------------------------
*
*
*	https://github.com/Bren828/quickslots
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


#if !defined QS_TD_POSITION_X
    #define QS_TD_POSITION_X 321.0
#endif

#if !defined QS_TD_POSITION_Y
    #define QS_TD_POSITION_Y 400.0
#endif

#if !defined QS_TD_INDENT_X
    #define QS_TD_INDENT_X 32.0
#endif


#if !defined QS_TD_FON_COLOR_BACK
    #define QS_TD_FON_COLOR_BACK 0x00000077
#endif

#if !defined QS_TD_FON_COLOR_MAIN
    #define QS_TD_FON_COLOR_MAIN 0x32323288
#endif

#if !defined QS_TD_FON_COLOR_SELECTED
    #define QS_TD_FON_COLOR_SELECTED 0x626262AA
#endif

#if !defined QS_TD_COLOR_VALUE
    #define QS_TD_COLOR_VALUE 0xFFFFFFFF
#endif



enum QUICKSLOTS_EN
{
    bool:qs_Show,
    qs_SelectedSlot,

    qs_Modelid[QS_MAX_SLOTS], 
    Float:qs_fRotX[QS_MAX_SLOTS], 
    Float:qs_fRotY[QS_MAX_SLOTS], 
    Float:qs_fRotZ[QS_MAX_SLOTS], 
    Float:qs_fZoom[QS_MAX_SLOTS],
    qs_Value[QS_MAX_SLOTS],
    qs_ExtraValue[QS_MAX_SLOTS],

    PlayerText:qs_TD_FonBack[QS_MAX_SLOTS],
    PlayerText:qs_TD_FonMain[QS_MAX_SLOTS],
    PlayerText:qs_TD_FonValue[QS_MAX_SLOTS]
}
static quickslots[MAX_PLAYERS][QUICKSLOTS_EN];
static const NULL_quickslots[QUICKSLOTS_EN];



stock ShowQuickSlots(playerid)
{
    if(quickslots[playerid][qs_Show] == true) return 0;
    quickslots[playerid][qs_Show] = true;

    new Float:PosX = QS_TD_POSITION_X - ((QS_TD_INDENT_X * QS_MAX_SLOTS) * 50)/100, // get center
        string[11];

    for(new slot; slot < QS_MAX_SLOTS; slot ++)
    {
        quickslots[playerid][qs_TD_FonBack][slot] = PlayerText:INVALID_TEXT_DRAW;
        quickslots[playerid][qs_TD_FonMain][slot] = PlayerText:INVALID_TEXT_DRAW;
        quickslots[playerid][qs_TD_FonValue][slot] = PlayerText:INVALID_TEXT_DRAW;

        #if QS_TD_FON_COLOR_BACK != 0x00000000
            quickslots[playerid][qs_TD_FonBack][slot] = CreatePlayerTextDraw(playerid, PosX+1.4, QS_TD_POSITION_Y+1.6, "_");
            PlayerTextDrawLetterSize(playerid, quickslots[playerid][qs_TD_FonBack][slot], 0.0, 3.5);
            PlayerTextDrawUseBox(playerid, quickslots[playerid][qs_TD_FonBack][slot], 1);
            PlayerTextDrawTextSize(playerid, quickslots[playerid][qs_TD_FonBack][slot], PosX+28.4, 0.0);
            PlayerTextDrawBoxColor(playerid, quickslots[playerid][qs_TD_FonBack][slot], QS_TD_FON_COLOR_BACK);
            PlayerTextDrawShow(playerid, quickslots[playerid][qs_TD_FonBack][slot]);
        #endif

		quickslots[playerid][qs_TD_FonMain][slot] = CreatePlayerTextDraw(playerid, PosX + 0.5, QS_TD_POSITION_Y + 0.5, "_");
        PlayerTextDrawBackgroundColor(playerid, quickslots[playerid][qs_TD_FonMain][slot], (quickslots[playerid][qs_SelectedSlot] == slot) ? (QS_TD_FON_COLOR_SELECTED):(QS_TD_FON_COLOR_MAIN) );
        PlayerTextDrawFont(playerid, quickslots[playerid][qs_TD_FonMain][slot], 5);
		PlayerTextDrawLetterSize(playerid, quickslots[playerid][qs_TD_FonMain][slot], 0.5000, 1.0000);
		PlayerTextDrawColor(playerid, quickslots[playerid][qs_TD_FonMain][slot], 0xFFFFFFFF);
		PlayerTextDrawUseBox(playerid, quickslots[playerid][qs_TD_FonMain][slot], 1);
		PlayerTextDrawBoxColor(playerid, quickslots[playerid][qs_TD_FonMain][slot], 0x00000000);
		PlayerTextDrawTextSize(playerid, quickslots[playerid][qs_TD_FonMain][slot], 28.7000, 33.8997);
        PlayerTextDrawSetPreviewModel(playerid, quickslots[playerid][qs_TD_FonMain][slot], (quickslots[playerid][qs_Modelid][slot] == 0) ? (18691):(quickslots[playerid][qs_Modelid][slot]));
        if(quickslots[playerid][qs_Modelid][slot] == 0) PlayerTextDrawSetPreviewRot(playerid, quickslots[playerid][qs_TD_FonMain][slot], 0.0, 0.0, 0.0, 0.0);
        else PlayerTextDrawSetPreviewRot(playerid, quickslots[playerid][qs_TD_FonMain][slot], quickslots[playerid][qs_fRotX][slot], quickslots[playerid][qs_fRotY][slot], quickslots[playerid][qs_fRotZ][slot], quickslots[playerid][qs_fZoom][slot]);
        PlayerTextDrawSetSelectable(playerid, quickslots[playerid][qs_TD_FonMain][slot], true);
		PlayerTextDrawShow(playerid, quickslots[playerid][qs_TD_FonMain][slot]);

        if(quickslots[playerid][qs_Value][slot] != 0) format(string, sizeof(string), "%d", quickslots[playerid][qs_Value][slot]);
        else string = "_";
        quickslots[playerid][qs_TD_FonValue][slot] = CreatePlayerTextDraw(playerid, PosX + 27.0, QS_TD_POSITION_Y + 26.0, string);
        PlayerTextDrawAlignment(playerid, quickslots[playerid][qs_TD_FonValue][slot], 3);
        PlayerTextDrawBackgroundColor(playerid, quickslots[playerid][qs_TD_FonValue][slot], 0x000000FF);
        PlayerTextDrawFont(playerid, quickslots[playerid][qs_TD_FonValue][slot], 2);
        PlayerTextDrawLetterSize(playerid, quickslots[playerid][qs_TD_FonValue][slot], 0.1400, 0.6499);
        PlayerTextDrawColor(playerid, quickslots[playerid][qs_TD_FonValue][slot], QS_TD_COLOR_VALUE);
        PlayerTextDrawSetProportional(playerid, quickslots[playerid][qs_TD_FonValue][slot], 1);
        PlayerTextDrawSetShadow(playerid, quickslots[playerid][qs_TD_FonValue][slot], 0);
        PlayerTextDrawShow(playerid, quickslots[playerid][qs_TD_FonValue][slot]);

        PosX += QS_TD_INDENT_X;	
    }

    return 1;
}


stock HideQuickSlots(playerid)
{
    if(quickslots[playerid][qs_Show] == false) return 0;
    quickslots[playerid][qs_Show] = false;

    for(new slot; slot < QS_MAX_SLOTS; slot ++)
    {
        if(quickslots[playerid][qs_TD_FonBack][slot] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, quickslots[playerid][qs_TD_FonBack][slot]);
        if(quickslots[playerid][qs_TD_FonMain][slot] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, quickslots[playerid][qs_TD_FonMain][slot]);
        if(quickslots[playerid][qs_TD_FonValue][slot] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, quickslots[playerid][qs_TD_FonValue][slot]);

        quickslots[playerid][qs_TD_FonBack][slot] = PlayerText:INVALID_TEXT_DRAW;
        quickslots[playerid][qs_TD_FonMain][slot] = PlayerText:INVALID_TEXT_DRAW;
        quickslots[playerid][qs_TD_FonValue][slot] = PlayerText:INVALID_TEXT_DRAW;
    }

    return 1;
}


stock IsPlayerShowQuickSlots(playerid)
{
    return quickslots[playerid][qs_Show];
}


stock SetQuickSlotModel(playerid, slot, modelid, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0, Float:fZoom = 1.0, value = 0)
{
    if(slot < 0 || slot >= QS_MAX_SLOTS) return 0;

    quickslots[playerid][qs_Modelid][slot] = modelid;
    quickslots[playerid][qs_fRotX][slot] = (modelid != 0) ? (fRotX) : (0.0);
    quickslots[playerid][qs_fRotY][slot] = (modelid != 0) ? (fRotY) : (0.0);
    quickslots[playerid][qs_fRotZ][slot] = (modelid != 0) ? (fRotZ) : (0.0);
    quickslots[playerid][qs_fZoom][slot] = (modelid != 0) ? (fZoom) : (0.0);
    quickslots[playerid][qs_Value][slot] = value;

    if(quickslots[playerid][qs_Show] == true) 
    {
        PlayerTextDrawSetPreviewModel(playerid, quickslots[playerid][qs_TD_FonMain][slot], (modelid != 0) ? (modelid):(18691));
        PlayerTextDrawSetPreviewRot(playerid, quickslots[playerid][qs_TD_FonMain][slot], quickslots[playerid][qs_fRotX][slot], quickslots[playerid][qs_fRotY][slot], quickslots[playerid][qs_fRotZ][slot], quickslots[playerid][qs_fZoom][slot]);
        PlayerTextDrawShow(playerid, quickslots[playerid][qs_TD_FonMain][slot]);

        new string[11] = "_";
        if(value != 0) format(string, sizeof(string), "%d", value);
        PlayerTextDrawSetString(playerid, quickslots[playerid][qs_TD_FonValue][slot], string);
    }

    return 1;
}


stock GetQuickSlotModel(playerid, slot, &modelid, &Float:fRotX = 0.0, &Float:fRotY = 0.0, &Float:fRotZ = 0.0, &Float:fZoom = 0.0, &value = 0)
{
    if(slot < 0 || slot >= QS_MAX_SLOTS) return 0;

    modelid = quickslots[playerid][qs_Modelid][slot];
    fRotX = quickslots[playerid][qs_fRotX][slot];
    fRotY = quickslots[playerid][qs_fRotY][slot];
    fRotZ = quickslots[playerid][qs_fRotZ][slot];
    fZoom = quickslots[playerid][qs_fZoom][slot];
    value = quickslots[playerid][qs_Value][slot];

    return 1;
}


stock SetQuickSlotValue(playerid, slot, value)
{
    if(slot < 0 || slot >= QS_MAX_SLOTS) return 0;

    quickslots[playerid][qs_Value][slot] = value;

    if(quickslots[playerid][qs_Show] == true) 
    {
        new string[11] = "_";
        if(value != 0) format(string, sizeof(string), "%d", value);
        PlayerTextDrawSetString(playerid, quickslots[playerid][qs_TD_FonValue][slot], string);
    }

    return 1;
}


stock GetQuickSlotValue(playerid, slot)
{
    if(slot < 0 || slot >= QS_MAX_SLOTS) return 0;

    return quickslots[playerid][qs_Value][slot];
}


stock SetQuickSlotExtraValue(playerid, slot, value)
{
    if(slot < 0 || slot >= QS_MAX_SLOTS) return 0;

    quickslots[playerid][qs_ExtraValue][slot] = value;
    return 1;
}


stock GetQuickSlotExtraValue(playerid)
{
    if(slot < 0 || slot >= QS_MAX_SLOTS) return 0;

    return quickslots[playerid][qs_ExtraValue][slot];
}


stock SetQuickSlotSelected(playerid, slot)
{
    if(slot < 0 || slot >= QS_MAX_SLOTS || quickslots[playerid][qs_SelectedSlot] == slot) return 0;

    if(quickslots[playerid][qs_Show] == true) 
    {
        PlayerTextDrawBackgroundColor(playerid, quickslots[playerid][qs_TD_FonMain][quickslots[playerid][qs_SelectedSlot]], QS_TD_FON_COLOR_MAIN);
        PlayerTextDrawShow(playerid, quickslots[playerid][qs_TD_FonMain][quickslots[playerid][qs_SelectedSlot]]);
        
        PlayerTextDrawBackgroundColor(playerid, quickslots[playerid][qs_TD_FonMain][slot], QS_TD_FON_COLOR_SELECTED);
        PlayerTextDrawShow(playerid, quickslots[playerid][qs_TD_FonMain][slot]);
    }

    quickslots[playerid][qs_SelectedSlot] = slot;
    return 1;
}


stock GetQuickSlotSelected(playerid)
{
    return quickslots[playerid][qs_SelectedSlot];
}



#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerConnect(playerid)
#else
	public OnPlayerConnect(playerid)
#endif
{
    quickslots[playerid] = NULL_quickslots;

	#if !defined _inc_y_hooks && !defined _INC_y_hooks && defined OnPlayerConnect_Quickslots
        OnPlayerConnect_Quickslots(playerid);
    #endif
    return 1;
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect OnPlayerConnect_Quickslots

	#if defined OnPlayerConnect_Quickslots
		forward OnPlayerConnect_Quickslots(playerid);
	#endif
#endif



#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
#else
	public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
#endif
{
    if(quickslots[playerid][qs_Show] == true) 
    {
        for(new slot; slot < QS_MAX_SLOTS; slot ++)
        {
            if(playertextid != quickslots[playerid][qs_TD_FonMain][slot]) continue;

            #if defined OnPlayerQuickSlotSelected
                OnPlayerQuickSlotSelected(playerid, slot, quickslots[playerid][qs_Modelid][slot], quickslots[playerid][qs_Value][slot], quickslots[playerid][qs_ExtraValue][slot]);
            #endif
            return 1;
        }
    }

    #if !defined _inc_y_hooks && !defined _INC_y_hooks && defined OnPlayerClickPlayerTextDraw_QS
        OnPlayerClickPlayerTextDraw_QS(playerid, playertextid);
    #endif
    return 1;
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