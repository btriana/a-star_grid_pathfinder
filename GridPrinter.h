/******************************************************************************/
/*!
\file   GridPrinter.h
\author Blake Triana
\par    email: blake.triana\@gmail.com
\brief
  Used to print data about the GridPathfinder.
*/
/******************************************************************************/

#pragma once

#include "GridPathfinder.h"
#include <iostream>
#include <stdio.h>

void PrintNode(const int x, const int y, const TerrainGrid & grid);

void PrintTerrainGrid(const TerrainGrid &grid);

