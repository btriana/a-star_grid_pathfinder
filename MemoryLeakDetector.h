/******************************************************************************/
/*!
\file   MemoryLeakDetector.h
\author Blake Triana
\par    email: blake.triana\@gmail.com
\brief
  Creates an object that checks for memory leaks on exit, in addition,
  automatically defines the debug version of new if a debugger is present.
*/
/******************************************************************************/

#pragma once
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// Enables the debug version of new() when a debugger is present
#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK new(_CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

namespace GameEngine
{
  class MemoryLeakDetector
  {
  public:
    static MemoryLeakDetector &GetInstance(void);
    
  private:
    MemoryLeakDetector(void);
    ~MemoryLeakDetector(void);
    MemoryLeakDetector(const MemoryLeakDetector &rhs);
    MemoryLeakDetector &operator=(const MemoryLeakDetector &rhs);
  };
}
