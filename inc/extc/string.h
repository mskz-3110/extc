#ifndef __EXTC_STRING_H__
#define __EXTC_STRING_H__
#include <extc/api.h>

EXTC_STRUCT_BEGIN
  char* Chars;
  int32 Length;
  int32 __AllocatedSize;
EXTC_STRUCT_END(ExtcString)

EXTC_API_BEGIN
  EXTC_API_INC(const char*, extc_string_empty)
  EXTC_API_INC(const char*, extc_string_guard, const char* value)
  EXTC_API_INC(bool, extc_string_equals, const char* value1, const char* value2)
  EXTC_API_INC(bool, extc_string_starts_with, const char* targetValue, const char* checkValue)
  EXTC_API_INC(bool, extc_string_ends_with, const char* targetValue, const char* checkValue)
  EXTC_API_INC(int64, extc_string_to_int64, const char* value)
  EXTC_API_INC(double, extc_string_to_double, const char* value)
  EXTC_API_INC(ExtcString*, extc_string_escape_encode, const char* value, int32 length)
  EXTC_API_INC(ExtcString*, extc_string_escape_decode, const char* value, int32 length)
  EXTC_API_INC(ExtcString*, extc_string_yaml_line_split_key, const char* yamlLine)
  EXTC_API_INC(ExtcString*, extc_string_yaml_line_split_value, const char* yamlLine)

  EXTC_API_INC(ExtcString*, extc_string_new)
  EXTC_API_INC(void, extc_string_delete, ExtcString* string)
  EXTC_API_INC(const char*, extc_string_get_chars, ExtcString* string)
  EXTC_API_INC(int32, extc_string_get_length, ExtcString* string)
  EXTC_API_INC(void, extc_string_clear, ExtcString* string)
  EXTC_API_INC(void, extc_string_add_int32, ExtcString* string, const char* format, int32 value)
  EXTC_API_INC(void, extc_string_add_int64, ExtcString* string, const char* format, int64 value)
  EXTC_API_INC(void, extc_string_add_float, ExtcString* string, const char* format, float value)
  EXTC_API_INC(void, extc_string_add_double, ExtcString* string, const char* format, double value)
  EXTC_API_INC(void, extc_string_add_string, ExtcString* string, const char* format, const char* value)
  EXTC_API_INC(void, extc_string_add_string_repeat, ExtcString* string, const char* value, int32 repeatCount)
  EXTC_API_INC(void, extc_string_vprintf, ExtcString* string, const char* format, va_list list)
  EXTC_API_INC(void, extc_string_printf, ExtcString* string, const char* format, ...)
EXTC_API_END
#endif
