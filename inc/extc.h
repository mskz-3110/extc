#ifndef __EXTC_H__
#define __EXTC_H__
#include <extc/string.h>

EXTC_API_BEGIN
  EXTC_API_INC(bool, extc_init)
  EXTC_API_INC(void, extc_exit)

  #define EXTC_ASSERT(_expression, _format, ...) extc_assert(__FILE__, __LINE__, _expression, _format, ## __VA_ARGS__)
  EXTC_API_INC(void, extc_assert, const char* file, int32 line, bool expression, const char* format, ...)
EXTC_API_END
#endif
