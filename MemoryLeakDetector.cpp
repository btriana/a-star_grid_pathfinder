/******************************************************************************/
/*!
\file   MemoryLeakDetector.cpp
\author Blake Triana
\par    email: blake.triana\@gmail.com
\brief  
  MemoryLeakDetector implementation.
*/
/******************************************************************************/

#include "MemoryLeakDetector.h"
#include <windows.h>

namespace GameEngine
{
  MemoryLeakDetector &MemoryLeakDetector::GetInstance(void)
  {
    static MemoryLeakDetector obj;
    return obj;
  }
  MemoryLeakDetector::MemoryLeakDetector(void)
  {
  }

  MemoryLeakDetector::~MemoryLeakDetector(void)
  {
    if (_CrtDumpMemoryLeaks())
    {
      MessageBoxA(GetDesktopWindow(), 
        "Memory leaks were detected in your program!",
        "Memory Leak Warning", NULL);
    }
  }
}
