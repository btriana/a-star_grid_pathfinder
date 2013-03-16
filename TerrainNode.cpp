/******************************************************************************/
/*!
\file   TerrainNode.cpp
\author Blake Triana
\par    email: blake.triana\@gmail.com
\brief  
  TerrainNode implementation.
*/
/******************************************************************************/

#include "TerrainNode.h"
#include <cmath>

TerrainNode::TerrainNode(const unsigned x, const unsigned y)
  : parent_(0),
  data_(ASD_Empty),
  x_(x),
  y_(y),
  fValue_(0.0f), 
  gValue_(0.0f),
  hValue_(0.0f)
{

}

TerrainNode::~TerrainNode(void)
{

}

bool TerrainNode::IsAdjacentToNode(const TerrainNode &rhs) const
{
  // Nodes are adjacent if they are within one unit of each other
  if ((abs(rhs.x_ - y_) <= 1))
    if ((abs(rhs.y_ - y_) <= 1))
      return true;

  return false;
}

bool TerrainNode::IsSideToSideWithNode(const TerrainNode &rhs) const
{
  // If the nodes share x or y-coordinates, they are directly side-to-side
  if (x_ == rhs.x_ || y_ == rhs.y_)
    return true;
  if (x_ == rhs.x_ || y_ == rhs.y_)
    return true;

  return false;
}

bool TerrainNode::IsDiagonalToNode(const TerrainNode &rhs) const
{
  // If the x or y-coordinates differ by a value of 1, then we know
  // the nodes are diagonal from each other.
  if ((x_ + 1) == rhs.x_ || (x_ - 1) == rhs.x_)
    if ((y_ + 1) == rhs.y_ || (y_ - 1) == rhs.y_)
      return true;

  return false;
}
