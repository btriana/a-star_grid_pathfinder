/******************************************************************************/
/*!
\file   GridPathfinder.h
\author Blake Triana
\brief
  Finds the shortest path between an origin and a destination on a grid
  using A* pathfinding.
*/
/******************************************************************************/

#pragma once
#include <list>
#include "TerrainNode.h"
#include "TerrainGrid.h"

class GridPathfinder
{
public:
  GridPathfinder(const int rows, const int columns);
  ~GridPathfinder(void) {}
  
  void SetObstacle(const int x, const int y);
  void FindShortestPath(TerrainNode &origin, TerrainNode &destination);
  const TerrainGrid &GetGrid(void) { return grid_; } 

private:
  TerrainNode *get_smallest_open_f(void);
  void visit_node(TerrainNode &node);
  void update_parents(TerrainNode &node);
  
  float calculate_f_value(const TerrainNode &node);
  float calculate_g_value(const TerrainNode &destination, 
    const TerrainNode &source);
  float calculate_h_value(const TerrainNode &node);
  
  void add_node_children(TerrainNode &parent);
  bool is_valid_child(const int x, const int y);
  void add_child(TerrainNode &parent, TerrainNode &child);

  void mark_shortest_path(void);

  enum
  {
    STRAIGHT_DISTANCE = 10,
    DIAGONAL_DISTANCE = 14
  };

  TerrainGrid grid_;
  std::list<TerrainNode *> openList_, closedList_;
  TerrainNode *origin_, *destination_;
};

