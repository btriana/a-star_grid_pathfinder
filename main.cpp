/******************************************************************************/
/*!
\file   main.cpp
\author Blake Triana
\par    email: blake.triana\@gmail.com
\brief  
  main implementation.
*/
/******************************************************************************/

#include <iostream>
#include "GridPrinter.h"
#include "GridPathfinder.h"
#include "MemoryLeakDetector.h"

void Test1(void)
{
  // 4 x 4 straight-across
  printf("Test 1:");
  const int gridColumns = 4, gridRows = 4;
  GridPathfinder pathFinder(gridRows, gridColumns);
  TerrainNode origin(0, 0);
  TerrainNode destination(3, 3);

  printf("\n");
  pathFinder.FindShortestPath(origin, destination);
  PrintTerrainGrid(pathFinder.GetGrid());
  printf("\n");
}

void Test2(void)
{
  // 4 x 4 not straight-across
  printf("Test 2:");
  const int gridColumns = 10, gridRows = 10;
  GridPathfinder pathFinder(gridRows, gridColumns);
  TerrainNode origin(0, 0);
  TerrainNode destination(4, 7);

  printf("\n");
  pathFinder.FindShortestPath(origin, destination);
  PrintTerrainGrid(pathFinder.GetGrid());
  printf("\n");
}

void Test3(void)
{
  // Non-square grid
  printf("Test 3:");
  const int gridColumns = 4, gridRows = 1;
  GridPathfinder pathFinder(gridRows, gridColumns);
  TerrainNode origin(0, 0);
  TerrainNode destination(3, 0);

  printf("\n");
  pathFinder.FindShortestPath(origin, destination);
  PrintTerrainGrid(pathFinder.GetGrid());
  printf("\n");
}

void Test4(void)
{
  // Obstacles  
  printf("Test 4:");
  const int gridColumns = 5, gridRows = 5;
  GridPathfinder pathFinder(gridRows, gridColumns);
  TerrainNode origin(0, 0);
  TerrainNode destination(4, 4);

  pathFinder.SetObstacle(2, 1);
  pathFinder.SetObstacle(2, 2);
  pathFinder.SetObstacle(1, 2);

  printf("\n");
  pathFinder.FindShortestPath(origin, destination);
  PrintTerrainGrid(pathFinder.GetGrid());
  printf("\n");
}

void Test5(void)
{
  // Obstacles  
  printf("Test 5:");
  const int gridColumns = 10, gridRows = 10;
  GridPathfinder pathFinder(gridRows, gridColumns);
  TerrainNode origin(0, 0);
  TerrainNode destination(9, 9);
  
//   pathFinder.SetObstacle(2, 1);
//   pathFinder.SetObstacle(2, 2);
//   pathFinder.SetObstacle(1, 2);

  pathFinder.SetObstacle(5, 0);
  pathFinder.SetObstacle(5, 1);
  pathFinder.SetObstacle(5, 2);
  pathFinder.SetObstacle(5, 3);
  pathFinder.SetObstacle(5, 4);
  pathFinder.SetObstacle(5, 5);
  pathFinder.SetObstacle(4, 5);
  pathFinder.SetObstacle(3, 5);
  pathFinder.SetObstacle(2, 5);
  pathFinder.SetObstacle(1, 5);
  pathFinder.SetObstacle(0, 5);

  printf("\n");
  pathFinder.FindShortestPath(origin, destination);
   PrintTerrainGrid(pathFinder.GetGrid());
  printf("\n");
}

void Test6(void)
{
  // Obstacles  
  printf("Test 6:");
  const int gridColumns = 10, gridRows = 8;
  GridPathfinder pathFinder(gridRows, gridColumns);
  TerrainNode origin(1, 1);
  TerrainNode destination(9, 7);

  //   pathFinder.SetObstacle(2, 1);
  //   pathFinder.SetObstacle(2, 2);
  //   pathFinder.SetObstacle(1, 2);

  pathFinder.SetObstacle(0, 0);
  pathFinder.SetObstacle(1, 0);
  // pathFinder.SetObstacle(2, 0);
  pathFinder.SetObstacle(0, 2);
  pathFinder.SetObstacle(1, 2);
  pathFinder.SetObstacle(2, 2);
  pathFinder.SetObstacle(0, 1);
  pathFinder.SetObstacle(2, 1);

//   pathFinder.SetObstacle(5, 0);
//   pathFinder.SetObstacle(5, 1);
//   pathFinder.SetObstacle(5, 2);
//   pathFinder.SetObstacle(5, 3);
//   pathFinder.SetObstacle(5, 4);
//   pathFinder.SetObstacle(5, 5);
//   pathFinder.SetObstacle(4, 5);
//   pathFinder.SetObstacle(3, 5);
//   pathFinder.SetObstacle(2, 5);
//   pathFinder.SetObstacle(1, 5);
//   pathFinder.SetObstacle(0, 5);

  printf("\n");
  pathFinder.FindShortestPath(origin, destination);
  PrintTerrainGrid(pathFinder.GetGrid());
  printf("\n");
}

void ParameterizedTest(void)
{  
  int gridColumns, gridRows;
  std::cout << "Grid rows: ";
  std::cin >> gridRows;
  std::cout << "Grid columns: ";
  std::cin >> gridColumns;
  std::cout << std::endl;
  GridPathfinder pathFinder(gridRows, gridColumns);

  int originX, originY, destX, destY;
  std::cout << "Path origin X: ";
  std::cin >> originX;

  std::cout << "Path origin Y: ";
  std::cin >> originY;
  std::cout << std::endl;

  std::cout << "Path destination X: ";
  std::cin >> destX;

  std::cout << "Path destination Y: ";
  std::cin >> destY;
  std::cout << std::endl;

  TerrainNode origin(originX, originY);
  TerrainNode destination(destX, destY);
  pathFinder.FindShortestPath(origin, destination);
}


int main()
{
  GameEngine::MemoryLeakDetector::GetInstance();

  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();

  // ParameterizedTest();
  return 0;
}
