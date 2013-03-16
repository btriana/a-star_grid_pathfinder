/******************************************************************************/
/*!
\file   TerrainGrid.h
\author Blake Triana
\par    email: blake.triana\@gmail.com
\brief
  TerrainGrid represents a 2D grid of TerrainNodes
*/
/******************************************************************************/

#pragma once
#include <vector>

struct TerrainNode;

class TerrainGrid
{
public:
  TerrainGrid(const unsigned rows, const unsigned columns);
  ~TerrainGrid(void);
  const std::vector<TerrainNode *>&operator[](unsigned index) const;
  bool AreValidCoordinates(const int x, const int y);
  bool AreCoordinatesAccessible(const int x, const int y);

  unsigned rows_, columns_;

private:
  std::vector<std::vector<TerrainNode *> > grid_;
};
