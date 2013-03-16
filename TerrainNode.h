/******************************************************************************/
/*!
\file   TerrainNode.h
\author Blake Triana
\par    email: blake.triana\@gmail.com
\brief
  TerrainNode represents a single node in a terrain grid.
*/
/******************************************************************************/

#pragma once

enum TerrainData
{
  ASD_Origin = 'O',
  ASD_Destination = 'D',
  ASD_Empty = ' ',
  ASD_Path = '*',
  ASD_Obstacle = '#'
};

struct TerrainNode
{
public:
  TerrainNode(const unsigned x, const unsigned y);
  ~TerrainNode(void);
  bool IsAdjacentToNode(const TerrainNode &rhs) const;
  bool IsSideToSideWithNode(const TerrainNode &rhs) const;
  bool IsDiagonalToNode(const TerrainNode &rhs) const;

  TerrainData data_;
  float fValue_;
  float gValue_;
  float hValue_;
  TerrainNode *parent_;
  const int x_, y_;
};
