#pragma once 

#define global static
#define local_persist static 
#define internal static 

#define MAP_WIDTH 1280 
#define MAP_HEIGHT 720 
#define CELL_HEIGHT 10 
#define CELL_WIDTH 10
#define BOARD_SIZE (MAP_WIDTH / CELL_WIDTH) * (MAP_HEIGHT / CELL_HEIGHT)

enum Mode {
    EDITOR, 
    PLAYER, 
    MENU 
};

struct Game_State {
    Mode mode = EDITOR; 
    bool mouseDown = false; 
    int setState = 1; 
    int board[BOARD_SIZE] = {};  
}; 

struct Window_Dimension {
    int width; 
    int height; 
}; 
