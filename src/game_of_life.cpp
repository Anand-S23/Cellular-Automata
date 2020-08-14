int AliveNeighbours(int* board, int pos)
{
    int alive = 0;

    // Top Left Corner 
    if (pos == 0)
    {
        if (board[pos + 1])
        {
            alive++; 
        }

        if (board[pos + (MAP_WIDTH / CELL_WIDTH)])
        {
            alive++; 
        }

        if (board[pos + (MAP_WIDTH / CELL_WIDTH) + 1])
        {
            alive++; 
        }
    }

    // Top Right Corner
    else if (pos == (MAP_WIDTH / CELL_WIDTH) - 1) 
    {
        if (board[pos - 1])
        {
            alive++; 
        }

        if (board[pos + (MAP_WIDTH / CELL_WIDTH)])
        {
            alive++; 
        }

        if (board[pos + (MAP_WIDTH / CELL_WIDTH) - 1])
        {
            alive++; 
        }
    }

    // Bottom Left Corner
    else if (pos == BOARD_SIZE - MAP_WIDTH / CELL_HEIGHT)
    {
        if (board[pos + 1])
        {
            alive++; 
        }

        if (board[pos - (MAP_WIDTH / CELL_WIDTH)])
        {
            alive++; 
        }

        if (board[pos - (MAP_WIDTH / CELL_WIDTH) + 1])
        {
            alive++; 
        }
    }
    
    // Bottom Right Corner
    else if (pos == BOARD_SIZE - 1) 
    {
        if (board[pos - 1])
        {
            alive++; 
        }

        if (board[pos - (MAP_WIDTH / CELL_WIDTH)])
        {
            alive++; 
        }

        if (board[pos - (MAP_WIDTH / CELL_WIDTH) - 1])
        {
            alive++; 
        }
    }

    // Top 
    else if (pos / (MAP_WIDTH / CELL_WIDTH) == 0)
    {
        if (board[pos + (MAP_WIDTH / CELL_WIDTH) - 1])
        {
            alive++; 
        }

        if (board[pos + (MAP_WIDTH / CELL_WIDTH)])
        {
            alive++; 
        }

        if (board[pos + (MAP_WIDTH / CELL_WIDTH) + 1])
        {
            alive++; 
        }

        if (board[pos - 1])
        {
            alive++; 
        }

        if (board[pos + 1])
        {
            alive++; 
        }
    } 

    // Bottom 
    else if (pos / (MAP_WIDTH / CELL_WIDTH) == (MAP_HEIGHT / CELL_HEIGHT) - 1)
    {
        if (board[pos - (MAP_WIDTH / CELL_WIDTH) - 1])
        {
            alive++; 
        }

        if (board[pos - (MAP_WIDTH / CELL_WIDTH)])
        {
            alive++; 
        }

        if (board[pos - (MAP_WIDTH / CELL_WIDTH) + 1])
        {
            alive++; 
        }

        if (board[pos - 1])
        {
            alive++; 
        }

        if (board[pos + 1])
        {
            alive++; 
        }
    }

    // Left 
    else if (pos % (MAP_WIDTH / CELL_WIDTH) == 0)
    {
        if (board[pos - (MAP_WIDTH / CELL_WIDTH)])
        {
            alive++; 
        }

        if (board[pos + (MAP_WIDTH / CELL_WIDTH)])
        {
            alive++; 
        }

        if (board[pos - (MAP_WIDTH / CELL_WIDTH) + 1])
        {
            alive++; 
        }

        if (board[pos + (MAP_WIDTH / CELL_WIDTH) + 1])
        {
            alive++; 
        }

        if (board[pos + 1])
        {
            alive++; 
        }
    }

    // Right
    else if (pos % (MAP_WIDTH / CELL_WIDTH) == (MAP_WIDTH / CELL_WIDTH) - 1)
    {
        if (board[pos - (MAP_WIDTH / CELL_WIDTH)])
        {
            alive++; 
        }

        if (board[pos + (MAP_WIDTH / CELL_WIDTH)])
        {
            alive++; 
        }

        if (board[pos - (MAP_WIDTH / CELL_WIDTH) - 1])
        {
            alive++; 
        }

        if (board[pos + (MAP_WIDTH / CELL_WIDTH) - 1])
        {
            alive++; 
        }

        if (board[pos - 1])
        {
            alive++; 
        }
    }

    // Not an edge
    else
    {
        if (board[pos + (MAP_WIDTH / CELL_WIDTH) - 1])
        {
            alive++; 
        }

        if (board[pos + (MAP_WIDTH / CELL_WIDTH)])
        {
            alive++; 
        }

        if (board[pos + (MAP_WIDTH / CELL_WIDTH) + 1])
        {
            alive++; 
        }

        if (board[pos - 1])
        {
            alive++; 
        }

        if (board[pos + 1])
        {
            alive++; 
        }

        if (board[pos - (MAP_WIDTH / CELL_WIDTH) - 1])
        {
            alive++; 
        }

        if (board[pos - (MAP_WIDTH / CELL_WIDTH)])
        {
            alive++; 
        }

        if (board[pos - (MAP_WIDTH / CELL_WIDTH) + 1])
        {
            alive++; 
        }
    }

    return alive; 
}

void GameOfLife(Game_State *game)
{
    int board_copy[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        board_copy[i] = game->board[i]; 
    }

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        int neighbours = AliveNeighbours(board_copy, i);

        if (neighbours < 2 && board_copy[i] == 1)
        {
            game->board[i] = 0; 
        }

        else if (neighbours > 3 && board_copy[i] == 1)
        {
            game->board[i] = 0; 
        }

        else if (neighbours == 3 && board_copy[i] == 0)
        {
            game->board[i] = 1; 
        }
    }
}