#include <extc.h>

static String g_Empty = "";

static EXTC_API_SRC(int32, __string_get_allocated_size, ExtcString* string){
  return 0 <= string->__AllocatedSize ? string->__AllocatedSize : string->__AllocatedSize * -1;
}

static EXTC_API_SRC(bool, __string_is_fixed, ExtcString* string){
  return string->__AllocatedSize <= 0;
}

static EXTC_API_SRC(String, __string_if_null, String value, String value_if_null){
  return value == null ? value_if_null : value;
}

EXTC_API_SRC(String, extc_string_empty){
  return g_Empty;
}

EXTC_API_SRC(String, extc_string_guard, String value){
  return value != null ? value : g_Empty;
}

EXTC_API_SRC(bool, extc_string_equals, String value1, String value2){
  if ((value1 == null) || (value2 == null)) return (value1 == null) && (value2 == null);

  int32 length = (int32)strlen(value1);
  return length == (int32)strlen(value2) ? memcmp(value1, value2, length) == 0 : false;
}

EXTC_API_SRC(bool, extc_string_starts_with, String targetValue, String checkValue){
  if ((targetValue == null) || (checkValue == null)) return ((targetValue == null) && (checkValue == null));

  int32 targetLength = (int32)strlen(targetValue);
  int32 checkLength = (int32)strlen(checkValue);
  return checkLength <= targetLength ? memcmp(targetValue, checkValue, checkLength) == 0 : false;
}

EXTC_API_SRC(bool, extc_string_ends_with, String targetValue, String checkValue){
  if ((targetValue == null) || (checkValue == null)) return ((targetValue == null) && (checkValue == null));

  int32 length = (int32)strlen(checkValue);
  int32 index = (int32)strlen(targetValue) - length;
  return 0 <= index ? memcmp(&(targetValue[index]), checkValue, length) == 0 : false;
}

EXTC_API_SRC(int64, extc_string_to_int64, String value){
  return strtol(value, null, 0);
}

EXTC_API_SRC(double, extc_string_to_double, String value){
  return strtod(value, null);
}

EXTC_API_SRC(ExtcString, extc_string_fixed, char* chars, int32 size){
  ExtcString string;
  string.Chars = chars;
  string.__AllocatedSize = -size;
  extc_string_clear(&string);
  return string;
}

EXTC_API_SRC(ExtcString*, extc_string_new){
  ExtcString* string = malloc(sizeof(ExtcString));
  if (string == null) return null;

  string->__AllocatedSize = 4;
  string->Chars = malloc(string->__AllocatedSize);
  if (string->Chars == null){
    extc_string_delete(string);
    return null;
  }

  extc_string_clear(string);
  return string;
}

EXTC_API_SRC(void, extc_string_delete, ExtcString* string){
  if (string == null) return;
  if (string->Chars != null){
    free(string->Chars);
  }
  free(string);
}

EXTC_API_SRC(String, extc_string_get_chars, ExtcString* string){
  return string->Chars;
}

EXTC_API_SRC(int32, extc_string_get_length, ExtcString* string){
  return string->Length;
}

EXTC_API_SRC(void, extc_string_clear, ExtcString* string){
  string->Chars[0] = '\0';
  string->Length = 0;
}

EXTC_API_SRC(void, extc_string_add_int32, ExtcString* string, String format, int32 value){
  extc_string_printf(string, format, value);
}

EXTC_API_SRC(void, extc_string_add_int64, ExtcString* string, String format, int64 value){
  extc_string_printf(string, format, value);
}

EXTC_API_SRC(void, extc_string_add_float, ExtcString* string, String format, float value){
  extc_string_printf(string, format, value);
}

EXTC_API_SRC(void, extc_string_add_double, ExtcString* string, String format, double value){
  extc_string_printf(string, format, value);
}

EXTC_API_SRC(void, extc_string_add_string, ExtcString* string, String format, String value){
  extc_string_printf(string, format, value);
}

EXTC_API_SRC(void, extc_string_add_string_repeat, ExtcString* string, String value, int32 repeatCount){
  for (int32 i = 0; i < repeatCount; ++i){
    extc_string_printf(string, "%s", value);
  }
}

EXTC_API_SRC(void, extc_string_vprintf, ExtcString* string, String format, va_list list){
  va_list copiedList;
  va_copy(copiedList, list);
  int32 writableSize = __string_get_allocated_size(string) - string->Length;
  int32 length = vsnprintf(&(string->Chars[string->Length]), writableSize, format, list);
  do{
    if (length <= 0) break;
    if (length < writableSize){
      string->Length += length;
      break;
    }
    if (__string_is_fixed(string)){
      string->Length = (int32)strlen(string->Chars);
      break;
    }

    int32 needSize = string->Length + length + 1;
    int32 allocatedSize = string->__AllocatedSize * 2;
    while (allocatedSize < needSize) allocatedSize *= 2;
    char* allocatedChars = realloc(string->Chars, allocatedSize);
    if (allocatedChars == null) break;

    string->Chars = allocatedChars;
    string->__AllocatedSize = allocatedSize;
    length = vsnprintf(&(string->Chars[string->Length]), string->__AllocatedSize - string->Length, format, copiedList);
    if (0 < length) string->Length += length;
  }while (0);
  va_end(copiedList);
}

EXTC_API_SRC(void, extc_string_printf, ExtcString* string, String format, ...){
  va_list list;
  va_start(list, format);
  extc_string_vprintf(string, format, list);
  va_end(list);
}

EXTC_API_SRC(void, extc_string_escape_encode, ExtcString* string, String value, int32 length){
  for (int32 i = 0; i < length; ++i){
    switch (value[i]){
      case '\\':{extc_string_printf(string, "%s", "\\\\");}break;
      case '\'':{extc_string_printf(string, "%s", "\\\'");}break;
      case '\"':{extc_string_printf(string, "%s", "\\\"");}break;
      case '\t':{extc_string_printf(string, "%s", "\\t");}break;
      case '\n':{extc_string_printf(string, "%s", "\\n");}break;
      default: extc_string_printf(string, "%c", value[i]);
    }
  }
}

EXTC_API_SRC(void, extc_string_escape_decode, ExtcString* string, String value, int32 length){
  for (int32 i = 0; i < length; ++i){
    if (value[i] != '\\'){
      extc_string_printf(string, "%c", value[i]);
      continue;
    }

    ++i;
    switch (value[i]){
      case '\0':break;
      case '\\':{extc_string_printf(string, "%c", '\\');}break;
      case '\'':{extc_string_printf(string, "%c", '\'');}break;
      case '\"':{extc_string_printf(string, "%c", '\"');}break;
      case 't':{extc_string_printf(string, "%c", '\t');}break;
      case 'n':{extc_string_printf(string, "%c", '\n');}break;
      default: extc_string_printf(string, "%c", value[i]);
    }
  }
}

EXTC_API_SRC(bool, extc_string_yaml_line_split, ExtcString* keyString, ExtcString* valueString, String line){
  extc_string_clear(keyString);
  extc_string_clear(valueString);
  int32 keyLength = 0;
  String keyEndString = strchr(line, ':');
  if (keyEndString == null) return false;

  keyLength = (int32)(keyEndString - line);
  extc_string_printf(keyString, "%.*s", keyLength, line);
  String valueEndString = line + strlen(line);
  ++keyEndString;
  int32 count = (int32)(valueEndString - keyEndString);
  for (int32 i = 0; i < count; ++i){
    if (keyEndString[0] != ' ') break;

    ++keyEndString;
  }
  switch (keyEndString[0]){
    case '\'':
    case '\"':{
      ++keyEndString;
      --valueEndString;
    }break;
  }
  extc_string_escape_decode(valueString, keyEndString, (int32)(valueEndString - keyEndString));
  return true;
}
