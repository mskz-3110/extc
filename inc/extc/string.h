#ifndef __EXTC_STRING_H__
#define __EXTC_STRING_H__
#include <extc/api.h>

EXTC_STRUCT_BEGIN
  char* Chars;
  int32 Length;
  int32 __AllocatedSize;
EXTC_STRUCT_END(ExtcString)

EXTC_API_BEGIN
  EXTC_API_INC(String, extc_string_empty)
  EXTC_API_INC(String, extc_string_guard, String value)
  EXTC_API_INC(bool, extc_string_equals, String value1, String value2)
  EXTC_API_INC(bool, extc_string_starts_with, String targetValue, String checkValue)
  EXTC_API_INC(bool, extc_string_ends_with, String targetValue, String checkValue)
  EXTC_API_INC(int64, extc_string_to_int64, String value)
  EXTC_API_INC(double, extc_string_to_double, String value)

  EXTC_API_INC(ExtcString, extc_string_fixed, char* chars, int32 size)
  EXTC_API_INC(ExtcString*, extc_string_new)
  EXTC_API_INC(void, extc_string_delete, ExtcString* string)
  EXTC_API_INC(String, extc_string_get_chars, ExtcString* string)
  EXTC_API_INC(int32, extc_string_get_length, ExtcString* string)
  EXTC_API_INC(void, extc_string_clear, ExtcString* string)
  EXTC_API_INC(void, extc_string_add_int32, ExtcString* string, String format, int32 value)
  EXTC_API_INC(void, extc_string_add_int64, ExtcString* string, String format, int64 value)
  EXTC_API_INC(void, extc_string_add_float, ExtcString* string, String format, float value)
  EXTC_API_INC(void, extc_string_add_double, ExtcString* string, String format, double value)
  EXTC_API_INC(void, extc_string_add_string, ExtcString* string, String format, String value)
  EXTC_API_INC(void, extc_string_add_string_repeat, ExtcString* string, String value, int32 repeatCount)
  EXTC_API_INC(void, extc_string_vprintf, ExtcString* string, String format, va_list list)
  EXTC_API_INC(void, extc_string_printf, ExtcString* string, String format, ...)
  EXTC_API_INC(void, extc_string_escape_encode, ExtcString* string, String value, int32 length)
  EXTC_API_INC(void, extc_string_escape_decode, ExtcString* string, String value, int32 length)
  EXTC_API_INC(bool, extc_string_yaml_line_split, ExtcString* keyString, ExtcString* valueString, String line)
EXTC_API_END
#endif
