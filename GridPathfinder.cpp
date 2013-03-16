/******************************************************************************/
/*!
\file   GridPathfinder.cpp
\author Blake Triana
\brief  
  AStarPathfinder implementation.
*/
/******************************************************************************/

#include "GridPathfinder.h"
#include "GridPrinter.h"
#include <cmath>
#include <algorithm>

GridPathfinder::GridPathfinder(const int rows, const int columns) 
  : grid_(rows, columns), origin_(0), destination_(0)
{
}

void GridPathfinder::SetObstacle(const int x, const int y)
{
  if (grid_.AreValidCoordinates(x, y))
    grid_[x][y]->data_ = ASD_Obstacle;
  else
    printf("Unable to place obstacle at (%i, %i)\n", x, y);
}

void GridPathfinder::FindShortestPath(TerrainNode &origin, 
  TerrainNode &destination)
{
  if (grid_.AreCoordinatesAccessible(origin.x_, origin. y_))
  {
    grid_[origin.x_][origin.y_]->data_ = ASD_Origin;
    origin_ = grid_[origin.x_][origin.y_];
  }
  else
  {
    printf("Could not find path, origin is not accessible.\n");
    return;
  }

  if (grid_.AreCoordinatesAccessible(destination.x_, destination.y_))
  {
    grid_[destination.x_][destination.y_]->data_ = ASD_Destination;
    destination_ = grid_[destination.x_][destination.y_];
  }
  else
  {
    printf("Could not find path, destination is not accessible.\n");
    return;
  }  

  printf("Finding shortest path between (%i, %i) and (%i, %i)...\n", 
    origin_->x_, origin_->y_, destination_->x_, destination_->y_);

  // Start at origin
  openList_.push_back(origin_);
  
  while (!openList_.empty())
  {
    // Visit node with smallest 'F' value
    TerrainNode *nodeToVisit = get_smallest_open_f(); 

    visit_node(*nodeToVisit);

    // We found a path if we visit the destination
    if (nodeToVisit == destination_) 
      break;
  }

  mark_shortest_path();
}

TerrainNode *GridPathfinder::get_smallest_open_f(void)
{
  std::list<TerrainNode *>::iterator iter = openList_.begin();
  TerrainNode *lowestF = *(openList_.begin());

  // Walk the open list for the node with the smallest 'F' value
  while (iter != openList_.end())
  {
    TerrainNode *currentNode = *iter;

    if (currentNode->fValue_ < currentNode->fValue_)
      lowestF = currentNode;

    ++iter;
  }

  return lowestF;
}

void GridPathfinder::visit_node(TerrainNode &node)
{
  // Remove from the openList_, and to the closedList_
  openList_.remove(&node);
  closedList_.push_back(&node);

  // Update the parents for adjacent nodes on openList_
  update_parents(node);

  // Add new children to open list
  add_node_children(node);
}

void GridPathfinder::update_parents(TerrainNode &node)
{
  // Check all eight cardinal directions (NW, N, NE, E, SE, S, SW, W)
  for (int i = -1; i < 2; ++i)
  {
    for (int j = -1; j < 2; ++j)
    {
      // Don't make a node a child of itself
      if (j == 0 && i == 0) 
        continue;

      // Make sure this node is accessible on grid
      if (!grid_.AreCoordinatesAccessible(node.x_, node.y_))
        continue;

      // Make sure this node is on the openList_
      std::list<TerrainNode *>::iterator iter = std::find(openList_.begin(), 
        openList_.end(), grid_[node.x_][node.y_]);

      if (iter == openList_.end())
        continue;

      // If the path we're inspecting is shorter than the node's shortest path, 
      // the current node becomes the inspected node's parent
      float newGValue = node.gValue_ + calculate_g_value(node, (**iter));

      if (newGValue < (*iter)->gValue_)
      {
        (*iter)->parent_ = &node;
        (*iter)->gValue_ = static_cast<float>(newGValue);
      }
    }
  }
}

float GridPathfinder::calculate_f_value(const TerrainNode &node)
{
  return (node.gValue_ + node.hValue_);
}

float GridPathfinder::calculate_g_value(const TerrainNode &destination, 
  const TerrainNode &source)
{
  if (destination.IsSideToSideWithNode(source))
    return STRAIGHT_DISTANCE + source.gValue_;

  if (destination.IsDiagonalToNode(source))
    return DIAGONAL_DISTANCE + source.gValue_;

  // Return -1 if we were sent non-adjacent nodes
  return -1;
}

float GridPathfinder::calculate_h_value(const TerrainNode &node)
{
  // Compute h using the Chebyshev distance
  float hDiag = std::min(abs(node.x_ - static_cast<float>(destination_->x_)), 
    abs(node.y_ - static_cast<float>(destination_->y_)));

  float hStraight = abs(node.x_ - static_cast<float>(destination_->x_)) 
    + abs(node.y_ - static_cast<float>(destination_->y_));

  float hValue = (DIAGONAL_DISTANCE * hDiag) + 
    (STRAIGHT_DISTANCE * (hStraight - (2.0f * hDiag)));

  return hValue;
}

void GridPathfinder::add_node_children(TerrainNode &parent)
{
  // Check all eight cardinal directions (NW, N, NE, E, SE, S, SW, W)
  for (int i = -1; i < 2; ++i)
  {
    for (int j = -1; j < 2; ++j)
    {
      // Don't make a node a child of itself
      if (j == 0 && i == 0) 
        continue;

      if (is_valid_child((parent.x_ + j), (parent.y_ + i)))
        add_child(parent, *(grid_[parent.x_ + j][parent.y_ + i]));
    }
  }
}

bool GridPathfinder::is_valid_child(const int x, const int y)
{
  if (grid_.AreCoordinatesAccessible(x, y))
  {
    // Make sure this node is not on the openList_
    std::list<TerrainNode *>::iterator findIter =
      std::find(openList_.begin(), openList_.end(), grid_[x][y]);

    if (findIter != openList_.end())
      return false;

    // Make sure this node is not on the closedList_
    findIter = std::find(closedList_.begin(), closedList_.end(), grid_[x][y]);

    if (findIter != closedList_.end())
      return false;
  }
  else
  {
    return false;
  }

  return true;
}

void GridPathfinder::add_child(TerrainNode &parent, TerrainNode &child)
{
  openList_.push_back(&child);
  child.gValue_ = calculate_g_value(child, parent);
  child.hValue_ = calculate_h_value(child);
  child.fValue_ = calculate_f_value(child);
  child.parent_ = &parent;
}

void GridPathfinder::mark_shortest_path(void)
{
  TerrainNode *pathIter = destination_;
  bool pathFound = false;

  // Mark all of the empty locations on our path
  while (pathIter)
  {
    if (pathIter->data_ == ASD_Empty)
      pathIter->data_ = ASD_Path;    

    if (pathIter == origin_)
      pathFound = true;

    pathIter = pathIter->parent_;
  }

  if (pathFound)
    printf("Shortest path found.\n");
  else
    printf("Unable to find path.\n");
}
