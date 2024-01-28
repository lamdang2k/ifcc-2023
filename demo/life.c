int main()
{
    int gameState[50000];
    int oldGameState[50000];
    /* Max 100 x 100 */
    int rows = 40;
    int columns = 160;
    int gameStateSize = rows * columns;

    int ITERATION_MAX = 10000;
    int CLEAR_SCREEN = 0;
    int DELAY_FRAME = 80000000;

    int index = 0;
    /* Initializing array on 0*/
    while (index < gameStateSize)
    {
        gameState[index] = 0;
        oldGameState[index] = 0;
        index = index + 1;
    }

    /* First motif */
    oldGameState[columns / 2 + columns * (rows / 2 - 1)] = 1;

    oldGameState[columns / 2 - 1 + columns * (rows / 2)] = 1;
    oldGameState[columns / 2 + columns * (rows / 2)] = 1;
    oldGameState[columns / 2 + 1 + columns * (rows / 2)] = 1;

    oldGameState[columns / 2 + columns * (rows / 2 + 1)] = 1;

    
    /* Second motif */
    oldGameState[columns / 4 + columns * (rows / 3 - 1)] = 1;

    oldGameState[columns / 4 - 1 + columns * (rows / 3)] = 1;
    oldGameState[columns / 4 + columns * (rows / 3)] = 1;
    oldGameState[columns / 4 + 1 + columns * (rows / 3)] = 1;

    oldGameState[columns / 4 + columns * (rows / 3 + 1)] = 1;


    /* Third motif */
    oldGameState[columns / 4 + columns * (2*rows / 3 - 1)] = 1;

    oldGameState[columns / 4 - 1 + columns * (2*rows / 3)] = 1;
    oldGameState[columns / 4 + columns * (2*rows / 3)] = 1;
    oldGameState[columns / 4 + 1 + columns * (2*rows / 3)] = 1;

    oldGameState[columns / 4 + columns * (2*rows / 3 + 1)] = 1;


    /* Forth motif */
    oldGameState[3*columns / 4 + columns * (rows / 3 - 1)] = 1;

    oldGameState[3*columns / 4 - 1 + columns * (rows / 3)] = 1;
    oldGameState[3*columns / 4 + columns * (rows / 3)] = 1;
    oldGameState[3*columns / 4 + 1 + columns * (rows / 3)] = 1;

    oldGameState[3*columns / 4 + columns * (rows / 3 + 1)] = 1;


    /* Fifth motif */
    oldGameState[3*columns / 4 + columns * (2*rows / 3 - 1)] = 1;

    oldGameState[3*columns / 4 - 1 + columns * (2*rows / 3)] = 1;
    oldGameState[3*columns / 4 + columns * (2*rows / 3)] = 1;
    oldGameState[3*columns / 4 + 1 + columns * (2*rows / 3)] = 1;

    oldGameState[3*columns / 4 + columns * (2*rows / 3 + 1)] = 1;


    /* Planeur */
    oldGameState[3*columns / 5 -1  + columns * (2*rows / 6)] = 1;
    oldGameState[3*columns / 5 -2  + columns * (2*rows / 6)] = 1;
    oldGameState[3*columns / 5 -3  + columns * (2*rows / 6)] = 1;

    oldGameState[3*columns / 5 -3 + columns * (2*rows / 6 -1)] = 1;
    oldGameState[3*columns / 5 -2 + columns * (2*rows / 6 -2)] = 1;

    /* Planeur 2 */
    oldGameState[2*columns / 5 +1  + columns * (2*rows / 6)] = 1;
    oldGameState[2*columns / 5 +2  + columns * (2*rows / 6)] = 1;
    oldGameState[2*columns / 5 +3  + columns * (2*rows / 6)] = 1;

    oldGameState[2*columns / 5 +3 + columns * (2*rows / 6 -1)] = 1;
    oldGameState[2*columns / 5 +2 + columns * (2*rows / 6 -2)] = 1;

    /* Planeur 3 */
    oldGameState[2*columns / 5 +1  + columns * (3*rows / 6)] = 1;
    oldGameState[2*columns / 5 +2  + columns * (3*rows / 6)] = 1;
    oldGameState[2*columns / 5 +3  + columns * (3*rows / 6)] = 1;

    oldGameState[2*columns / 5 +2 + columns * (3*rows / 6 +1)] = 1;
    oldGameState[2*columns / 5 +1 + columns * (3*rows / 6 +2)] = 1;

    int countLivingNeighbours = 0;
    int iteration = 0;
    while (iteration < ITERATION_MAX)
    {
        /* Clear Screen */
        index = 0;
        while (index < CLEAR_SCREEN)
        {
            putchar(10);
            index = index + 1;
        }

        /* Print Game State */
        index = 0;
        while (index < gameStateSize)
        {
            /* Neutre */
            if (oldGameState[index] == 0)
            {
                putchar(' ');
            }
            /* En vie */
            else if (oldGameState[index] == 1)
            {
                putchar('@');
            }

            index = index + 1;
            if ((index % columns) == 0)
            {
                putchar(10); /* New line */
            }
        }

        index = 0;
        /* Calculate new state */
        while (index < gameStateSize)
        {
            int i = index / columns;
            int j = index % columns;

            int neighboursVector[8];

            neighboursVector[0] = j + 1 + (i - 1) * columns;
            neighboursVector[1] = j + 1 + (i)*columns;
            neighboursVector[2] = j + 1 + (i + 1) * columns;

            neighboursVector[3] = j + (i - 1) * columns;
            neighboursVector[4] = j + (i + 1) * columns;

            neighboursVector[5] = j - 1 + (i - 1) * columns;
            neighboursVector[6] = j - 1 + (i)*columns;
            neighboursVector[7] = j - 1 + (i + 1) * columns;

            int neightboursVectorIterator = 0;
            countLivingNeighbours = 0;
            while (neightboursVectorIterator < 8)
            {
                if (neighboursVector[neightboursVectorIterator] < gameStateSize)
                {
                    if (neighboursVector[neightboursVectorIterator] >= 0)
                    {
                        if(oldGameState[neighboursVector[neightboursVectorIterator]] == 1)
                        {
                            countLivingNeighbours = countLivingNeighbours + 1;
                        }
                    }
                }
                neightboursVectorIterator = neightboursVectorIterator + 1;
            }

            /* Nee */
            if (countLivingNeighbours == 3)
            {
                if (oldGameState[j + i * columns] == 0)
                {
                    gameState[j + i * columns] = 1;
                }
            }

            /* Reste en vie */
            if (countLivingNeighbours == 2)
            {
                if (oldGameState[j + i * columns] == 1)
                {
                    gameState[j + i * columns] = 1;
                }
            }

            if (countLivingNeighbours == 3)
            {
                if (oldGameState[j + i * columns] == 1)
                {
                    gameState[j + i * columns] = 1;
                }
            }

            /* Mort */
            if (countLivingNeighbours < 2)
            {
                if (oldGameState[j + i * columns] == 1)
                {
                    gameState[j + i * columns] = 0;
                }
            }

            if (countLivingNeighbours > 3)
            {
                if (oldGameState[j + i * columns] == 1)
                {
                    gameState[j + i * columns] = 0;
                }
            }
            index = index + 1;
        }

        /* pass the gameState into oldGameState*/
        index = 0;
        while (index < gameStateSize)
        {
            oldGameState[index] = gameState[index];
            index = index + 1;
        }

        /* Delay*/
        index = 0;
        while (index < DELAY_FRAME)
        {
            index = index + 1;
        }
        iteration = iteration + 1;
    }

    return countLivingNeighbours;
}

/* TODO: Solve error
            if((countLivingNeighbours == 3 ) & gameState[i+j*columns] <= 0)
            {
                gameState[i+j*columns] = 1;
            }

             if (countLivingNeighbours < 2)
            {
                if (gameState[i + j * columns] == 1)
                {
                    gameState[i + j * columns] = -1;
                }
            }
            else if (countLivingNeighbours > 3)
            {
                if (gameState[i + j * columns] == 1)
                {
                    gameState[i + j * columns] = -1;
                }
            }
*/
