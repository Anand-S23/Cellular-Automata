#include <SDL.h>
#include <stdio.h>
#include <stdint.h>

#include "cellular_automata.h"
#include "game_of_life.cpp"

global bool Running = true; 
global Game_State Game;

internal Window_Dimension GetWindowDimension(SDL_Window *window)
{
    Window_Dimension dimension;
    SDL_GetWindowSize(window, &dimension.width, &dimension.height); 
    return dimension; 
}

internal void RenderCell(SDL_Renderer *renderer, int i, Mode mode)
{
    int x = (i % (MAP_WIDTH / CELL_WIDTH)) * CELL_WIDTH;
    int y = (i / (MAP_WIDTH / CELL_WIDTH)) * CELL_WIDTH;

    if (mode == EDITOR)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); 
    }
    else 
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    }

    SDL_Rect rect = {x, y, CELL_WIDTH, CELL_HEIGHT};
    SDL_RenderDrawRect(renderer, &rect); 
    SDL_RenderFillRect(renderer, &rect); 
}

internal void RenderGrid(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); 
    for (int i = 0; i < (MAP_WIDTH / CELL_WIDTH) + 1; ++i)
    {
        SDL_RenderDrawLine(renderer,
                           i * CELL_WIDTH, 0,
                           i * CELL_WIDTH, MAP_HEIGHT);
        SDL_RenderDrawLine(renderer,
                           0,         i * CELL_HEIGHT,
                           MAP_WIDTH, i * CELL_HEIGHT);
    }
}

internal void RenderGame(SDL_Renderer *renderer, Game_State *game)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderClear(renderer); 

    switch(game->mode)
    {
        case EDITOR: 
        {
            RenderGrid(renderer); 

            for (int i = 0; i < BOARD_SIZE; ++i)
            {
                if (game->board[i] == 1)
                {
                    RenderCell(renderer, i, EDITOR); 
                }
            }
        } break; 

        case PLAYER: 
        {
            RenderGrid(renderer); 

            for (int i = 0; i < BOARD_SIZE; ++i)
            {
                if (game->board[i] == 1)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
                    RenderCell(renderer, i, PLAYER); 
                }
            }

            GameOfLife(game);
        } break; 

        case MENU: 
        {
        } break; 

        default:
            break; 
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(64);
}

internal void SetCell(Game_State *game, float mouseX, float mouseY, int state)
{
    int x = ((int)mouseX - (int)mouseX % CELL_WIDTH) / CELL_WIDTH; 
    int y = ((int)mouseY - (int)mouseY % CELL_HEIGHT) / CELL_HEIGHT; 
    int pos = y * (MAP_WIDTH / CELL_WIDTH) + x; 
    game->board[pos] = state;
}

internal int GetCell(Game_State *game, float mouseX, float mouseY)
{
    int x = ((int)mouseX - (int)mouseX % CELL_WIDTH) / CELL_WIDTH; 
    int y = ((int)mouseY - (int)mouseY % CELL_HEIGHT) / CELL_HEIGHT; 
    int pos = y * (MAP_WIDTH / CELL_WIDTH) + x; 
    game->board[pos] = game->board[pos] == 0 ? 1 : 0;

    return game->board[pos]; 
}

internal void HandleEvent(SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_QUIT:
        {
            Running = false;
        } break;

        case SDL_KEYUP:
        {
            if (event->key.repeat == 0)
            {
                if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
                {
                    if (Game.mode != MENU)
                    {
                        Game.mode = Game.mode == EDITOR ? PLAYER : EDITOR; 
                    }
                }
                
                else if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    Game.mode = Game.mode == MENU ? EDITOR : MENU; 
                }

                else if (event->key.keysym.scancode == SDL_SCANCODE_C)
                {
                    if (Game.mode == EDITOR)
                    {
                        for (int i = 0; i < BOARD_SIZE; ++i)
                        {
                            Game.board[i] = 0; 
                        }
                    }
                }
            }
        } break;

        case SDL_MOUSEBUTTONDOWN:
        {
            if (Game.mode == EDITOR)
            {
                Game.mouseDown = true; 
                Game.setState = GetCell(&Game, event->button.x, event->button.y);
            }
        } break; 

        case SDL_MOUSEBUTTONUP: 
        {
            if (Game.mode == EDITOR)
            {
                Game.mouseDown = false;
            }
        } break;

        case SDL_MOUSEMOTION: 
        {
            if (Game.mode == EDITOR && Game.mouseDown)
            {
                SetCell(&Game, event->button.x, event->button.y, Game.setState);
            }
        }
    }
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL_Init failed: %s", SDL_GetError());
    }

    SDL_Window *window = SDL_CreateWindow("Cellular Automata", 
                              SDL_WINDOWPOS_UNDEFINED, 
                              SDL_WINDOWPOS_UNDEFINED, 
                              1281, 721, 0);

    if (window)
    {
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (renderer)
        {
            while (Running)
            {
                SDL_Event event; 
                while (SDL_PollEvent(&event))
                {
                    HandleEvent(&event);
                }

                Window_Dimension dimension = GetWindowDimension(window);
                RenderGame(renderer, &Game); 
            }
        }
        else 
        {
            // TODO: Logging
        }
    }
    else
    {
        // TODO: Logging 
    }

    SDL_Quit();
    return 0; 
}