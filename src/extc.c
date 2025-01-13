#include <extc.h>

static bool g_Initialized = false;

EXTC_API_SRC(bool, extc_init){
#ifdef EXTC_WINDOWS
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
#endif
  g_Initialized = true;
  return true;
}

EXTC_API_SRC(void, extc_exit){
  if (!g_Initialized) return;
#ifdef EXTC_WINDOWS
  _CrtDumpMemoryLeaks();
#endif
  g_Initialized = false;
}

EXTC_API_SRC(void, extc_assert, String file, int32 line, bool expression, String format, ...){
  if (expression) return;

  va_list list;
  va_start(list, format);
  printf("\033[40m\033[31m[%s:%d] ", file, line);
  vprintf(format, list);
  printf("\033[0m\n");
  va_end(list);
  exit(EXIT_FAILURE);
}
