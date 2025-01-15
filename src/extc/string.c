#include <extc.h>

static const char* g_Empty = "";

static EXTC_API_SRC(int32, __string_get_allocated_size, ExtcString* string){
  return 0 <= string->__AllocatedSize ? string->__AllocatedSize : string->__AllocatedSize * -1;
}

static EXTC_API_SRC(const char*, __string_skip_space, const char* value){
  int32 length = (int32)strlen(value);
  for (int32 i = 0; i < length; ++i){
    if (value[i] != ' ') return value + i;
  }
  return value + length;
}

EXTC_API_SRC(const char*, extc_string_empty){
  return g_Empty;
}

EXTC_API_SRC(const char*, extc_string_guard, const char* value){
  return value != null ? value : g_Empty;
}

EXTC_API_SRC(bool, extc_string_equals, const char* value1, const char* value2){
  if ((value1 == null) || (value2 == null)) return (value1 == null) && (value2 == null);

  int32 length = (int32)strlen(value1);
  return length == (int32)strlen(value2) ? memcmp(value1, value2, length) == 0 : false;
}

EXTC_API_SRC(bool, extc_string_starts_with, const char* targetValue, const char* checkValue){
  if ((targetValue == null) || (checkValue == null)) return ((targetValue == null) && (checkValue == null));

  int32 targetLength = (int32)strlen(targetValue);
  int32 checkLength = (int32)strlen(checkValue);
  return checkLength <= targetLength ? memcmp(targetValue, checkValue, checkLength) == 0 : false;
}

EXTC_API_SRC(bool, extc_string_ends_with, const char* targetValue, const char* checkValue){
  if ((targetValue == null) || (checkValue == null)) return ((targetValue == null) && (checkValue == null));

  int32 length = (int32)strlen(checkValue);
  int32 index = (int32)strlen(targetValue) - length;
  return 0 <= index ? memcmp(&(targetValue[index]), checkValue, length) == 0 : false;
}

EXTC_API_SRC(int64, extc_string_to_int64, const char* value){
  return strtol(value, null, 0);
}

EXTC_API_SRC(double, extc_string_to_double, const char* value){
  return strtod(value, null);
}

EXTC_API_SRC(ExtcString*, extc_string_escape_encode, const char* value, int32 length){
  ExtcString* string = extc_string_new();
  if (string == null) return null;
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
  return string;
}

EXTC_API_SRC(ExtcString*, extc_string_escape_decode, const char* value, int32 length){
  ExtcString* string = extc_string_new();
  if (string == null) return null;
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
  return string;
}

EXTC_API_SRC(ExtcString*, extc_string_yaml_line_split_key, const char* yamlLine){
  const char* keyEndString = strchr(yamlLine, ':');
  if (keyEndString == null) return null;

  ExtcString* string = extc_string_new();
  if (string == null) return null;

  extc_string_printf(string, "%.*s", (int32)(keyEndString - yamlLine), yamlLine);
  return string;
}

EXTC_API_SRC(ExtcString*, extc_string_yaml_line_split_value, const char* yamlLine){
  const char* keyEndString = strchr(yamlLine, ':');
  if (keyEndString == null) return false;

  const char* valueEndString = yamlLine + strlen(yamlLine);
  keyEndString = __string_skip_space(keyEndString + 1);
  switch (keyEndString[0]){
    case '\'':
    case '\"':{
      ++keyEndString;
      --valueEndString;
    }break;
  }
  return extc_string_escape_decode(keyEndString, (int32)(valueEndString - keyEndString));
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

EXTC_API_SRC(const char*, extc_string_get_chars, ExtcString* string){
  return string->Chars;
}

EXTC_API_SRC(int32, extc_string_get_length, ExtcString* string){
  return string->Length;
}

EXTC_API_SRC(void, extc_string_clear, ExtcString* string){
  string->Chars[0] = '\0';
  string->Length = 0;
}

EXTC_API_SRC(void, extc_string_add_int32, ExtcString* string, const char* format, int32 value){
  extc_string_printf(string, format, value);
}

EXTC_API_SRC(void, extc_string_add_int64, ExtcString* string, const char* format, int64 value){
  extc_string_printf(string, format, value);
}

EXTC_API_SRC(void, extc_string_add_float, ExtcString* string, const char* format, float value){
  extc_string_printf(string, format, value);
}

EXTC_API_SRC(void, extc_string_add_double, ExtcString* string, const char* format, double value){
  extc_string_printf(string, format, value);
}

EXTC_API_SRC(void, extc_string_add_string, ExtcString* string, const char* format, const char* value){
  extc_string_printf(string, format, value);
}

EXTC_API_SRC(void, extc_string_add_string_repeat, ExtcString* string, const char* value, int32 repeatCount){
  for (int32 i = 0; i < repeatCount; ++i){
    extc_string_printf(string, "%s", value);
  }
}

EXTC_API_SRC(void, extc_string_vprintf, ExtcString* string, const char* format, va_list list){
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

EXTC_API_SRC(void, extc_string_printf, ExtcString* string, const char* format, ...){
  va_list list;
  va_start(list, format);
  extc_string_vprintf(string, format, list);
  va_end(list);
}
