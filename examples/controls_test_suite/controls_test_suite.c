/*******************************************************************************************
*
*   raygui - controls test suite
*
*   TEST CONTROLS:
*       - GuiDropdownBox()
*       - GuiValueBox()
*       - GuiSpinner()
*       - GuiTextBox()
*       - GuiTextBoxMulti()
*       - GuiListView()
*
*   DEPENDENCIES:
*       raylib 2.1  - Windowing/input management and drawing.
*       raygui 2.0  - Immediate-mode GUI controls.
*
*   COMPILATION (Windows - MinGW):
*       gcc -o $(NAME_PART).exe $(FILE_NAME) -I../../src -lraylib -lopengl32 -lgdi32 -std=c99
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2018 raylib technologies (@raylibtech)
*
**********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "../../src/raygui.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 690;
    int screenHeight = 540;

    InitWindow(screenWidth, screenHeight, "raygui - controls test suite");

    // GUI controls initialization
    //----------------------------------------------------------------------------------
    int dropdownBox000Active = 0;
    bool dropDown000EditMode = false;
    
    int dropdownBox001Active = 0;
    bool dropDown001EditMode = false;    
    
    int spinner001Value = 0;
    bool spinnerEditMode = false;
    
    int valueBox002Value = 0;
    bool valueBoxEditMode = false;
    
    char textBoxText[64] = "Text box";
    bool textBoxEditMode = false;
    
    int listViewScrollIndex = 0;
    int listViewActive = -1;
    bool listViewEditMode = false;
    
    int listViewExScrollIndex = 0;
    int listViewExActive = -1;
    int listViewExFocus = -1;
    const char *listViewExList[8] = { "This", "is", "a", "list view", "with", "disable", "elements", "amazing!" };
    int listViewExElementsEnable[8] = {1, 0, 1, 1, 0, 0, 1};
    bool listViewExEditMode = false;
    
    char multiTextBoxText[141] = "Multi text box";    
    bool multiTextBoxEditMode = false;
    Color colorPickerValue = RED;
    
    int sliderValue = 50;
    int sliderBarValue = 60;
    float progressValue = 0.4f;
    
    bool forceSquaredChecked = false;
    
    int comboBoxActive = 1;
    
    int toggleGroupActive = 0;
    
    Vector2 viewScroll = { 0, 0 };
    //----------------------------------------------------------------------------------
    
    // Custom GUI font loading
    //Font font = LoadFontEx("fonts/rainyhearts16.ttf", 12, 0, 0);
    //GuiFont(font);

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
 
            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            if (dropDown000EditMode || dropDown001EditMode) GuiLock();
            //GuiDisable();
            
            // First GUI column
            forceSquaredChecked = GuiCheckBox((Rectangle){ 25, 108, 15, 15 }, "Force Square", forceSquaredChecked);
            if (GuiSpinner((Rectangle){ 25, 135, 125, 30 }, &spinner001Value, 0, 100, spinnerEditMode)) spinnerEditMode = !spinnerEditMode;
            if (GuiValueBox((Rectangle){ 25, 175, 125, 30 }, &valueBox002Value, 0, 100, valueBoxEditMode)) valueBoxEditMode = !valueBoxEditMode;
            if (GuiTextBox((Rectangle){ 25, 215, 125, 30 }, textBoxText, 64, textBoxEditMode)) textBoxEditMode = !textBoxEditMode;
            
            GuiTextAlign(GUI_TEXT_ALIGN_LEFT);
            if (GuiButton((Rectangle){ 25, 255, 125, 30 }, "#001#SAMPLE TEXT")) { };
            GuiTextAlign(GUI_TEXT_ALIGN_CENTER);
            
            GuiGroupBox((Rectangle){ 25, 310, 125, 150 }, "CONTROL STATES");
            GuiLock();
            GuiState(GUI_STATE_NORMAL); if (GuiButton((Rectangle){ 30, 320, 115, 30 }, "NORMAL")) { }
            GuiState(GUI_STATE_FOCUSED); if (GuiButton((Rectangle){ 30, 355, 115, 30 }, "FOCUSED")) { }
            GuiState(GUI_STATE_PRESSED); if (GuiButton((Rectangle){ 30, 390, 115, 30 }, "PRESSED")) { }
            GuiState(GUI_STATE_DISABLED); if (GuiButton((Rectangle){ 30, 425, 115, 30 }, "DISABLED")) { }
            GuiState(GUI_STATE_NORMAL);            
            GuiUnlock();
            
            comboBoxActive = GuiComboBox((Rectangle){ 25, 470, 125, 30 }, "ONE;TWO;THREE;FOUR", comboBoxActive);
            
            // NOTE: GuiDropdownBox must draw after any other control that can be covered on unfolding
            if (GuiDropdownBox((Rectangle){ 25, 65, 125, 30 }, "ONE;TWO;THREE;FOUR", &dropdownBox001Active, dropDown001EditMode)) dropDown001EditMode = !dropDown001EditMode;
            if (GuiDropdownBox((Rectangle){ 25, 25, 125, 30 }, "ONE;TWO;THREE", &dropdownBox000Active, dropDown000EditMode)) dropDown000EditMode = !dropDown000EditMode;
            
            // Second GUI column      
            if (GuiListView((Rectangle){ 165, 25, 140, 140 }, "Charmander;Bulbasaur;Squirtel;Pikachu;Eevee;Pidgey", &listViewActive, &listViewScrollIndex, listViewEditMode)) listViewEditMode = !listViewEditMode;
            if (GuiListViewEx((Rectangle){ 165, 180, 140, 200 }, listViewExList, 8, listViewExElementsEnable, &listViewExActive, &listViewExFocus, &listViewExScrollIndex, listViewExEditMode)) listViewExEditMode = !listViewExEditMode;
            if (listViewExFocus >= 0 && listViewExFocus < 8) DrawText(FormatText("FOCUS: %s", listViewExList[listViewExFocus]), 165, 390, 10, listViewExElementsEnable[listViewExFocus] ? LIME : MAROON);
            
            toggleGroupActive = GuiToggleGroup((Rectangle){ 165, 400, 140, 25 }, "ONE\nTWO\nTHREE\nFOUR", toggleGroupActive);
            
            // Third GUI column
            if (GuiTextBoxMulti((Rectangle){ 320, 25, 225, 140 }, multiTextBoxText, 141, multiTextBoxEditMode)) multiTextBoxEditMode = !multiTextBoxEditMode;
            colorPickerValue = GuiColorPicker((Rectangle){ 320, 185, 196, 192 }, colorPickerValue);
            
            sliderValue = GuiSlider((Rectangle){ 320, 400, 200, 20 }, NULL, sliderValue, -50, 100, true);
            sliderBarValue = GuiSliderBar((Rectangle){ 320, 430, 200, 20 }, NULL, sliderBarValue, 0, 100, true);
            progressValue = GuiProgressBar((Rectangle){ 320, 460, 200, 20 }, NULL, progressValue, 0, 1, true);
            
            Rectangle view = GuiScrollPanel((Rectangle){ 560, 25, 100, 160 }, (Rectangle){ 560, 25, 100, 400 }, &viewScroll);
            
            //GuiEnable();
            GuiUnlock();
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
