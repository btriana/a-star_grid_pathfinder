/******************************************************************************/
/*!
\file   GridPrinter.cpp
\author Blake Triana
\par    email: blake.triana\@gmail.com
\brief  
  GridPrinter implementation.
*/
/******************************************************************************/

#include "GridPrinter.h"

void PrintTerrainGrid(const TerrainGrid &grid)
{
  // Iterate and print the array like a 2D grid
  for (unsigned i = 0; i < grid.rows_; ++i)
  {
    for (unsigned j = 0; j < grid.columns_; ++j)
    {
      TerrainNode *currentNode = grid[j][i];
      std::cout << "[" << static_cast<char>(currentNode->data_) << "] ";
    }

    std::cout << std::endl << std::endl;
  }
}

void PrintNode(const int x, const int y, const TerrainGrid & grid)
{
  printf("[%i, %i] = x(%i) y(%i)\n", x, y, grid[x][y]->x_, grid[x][y]->y_);
}
