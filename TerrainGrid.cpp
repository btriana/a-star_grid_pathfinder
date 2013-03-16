/******************************************************************************/
/*!
\file   TerrainGrid.cpp
\author Blake Triana
\par    email: blake.triana\@gmail.com
\brief  
  TerrainGrid implementation.
*/
/******************************************************************************/

#include "TerrainGrid.h"
#include "TerrainNode.h"

TerrainGrid::TerrainGrid(const unsigned rows, const unsigned columns)
  : rows_(rows), columns_(columns)
{
  grid_.resize(columns_, std::vector<TerrainNode *>(rows_, 0));

  // Create the grid of terrain nodes
  for (unsigned i = 0; i < rows_; ++i)
  {
    for (unsigned j = 0; j < columns_; ++j)
    {
      grid_[j][i] = new TerrainNode(j, i);
    }
  }
}

TerrainGrid::~TerrainGrid(void)
{
  // Deallocate all of the terrain nodes
  for (unsigned i = 0; i < rows_; ++i)
  {
    for (unsigned j = 0; j < columns_; ++j)
    {
      delete grid_[j][i];
    }
  }
}

const std::vector<TerrainNode *>& TerrainGrid::operator[](unsigned index) const
{
  return grid_[index];
}

bool TerrainGrid::AreValidCoordinates(const int x, const  int y)
{
  if (x >= 0 && x < static_cast<int>(columns_))
    if (y >= 0 && y < static_cast<int>(rows_))
      return true;

  return false;
}

bool TerrainGrid::AreCoordinatesAccessible(const int x, const int y)
{
  if (AreValidCoordinates(x, y))
  {
    TerrainNode *node = grid_[x][y];

    // The Node is accessible if nothing occupies it
    if (node ->data_ != ASD_Obstacle)
      return true;
  }

  return false;
}
