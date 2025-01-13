#include <extc.h>

#define STRING_ASSERT(_string, _check_chars) string_assert(__FILE__, __LINE__, _string, _check_chars)
void string_assert(String file, int32 line, ExtcString* string, String checkChars){
  String chars = extc_string_get_chars(string);
  int32 length = extc_string_get_length(string);
  extc_assert(file, line, length == (int32)strlen(checkChars) && extc_string_equals(chars, checkChars), "length=%d chars='%s'", length, chars);
}

void test_int32(ExtcString* string){
  extc_string_clear(string);
  extc_string_add_int32(string, "%d:", -1);
  extc_string_add_int32(string, "%d", 1);
  STRING_ASSERT(string, "-1:1");
}

void test_int64(ExtcString* string){
  extc_string_clear(string);
  extc_string_add_int64(string, "%lld:", -1);
  extc_string_add_int64(string, "%lld", 1);
  STRING_ASSERT(string, "-1:1");
}

void test_float(ExtcString* string){
  extc_string_clear(string);
  extc_string_add_float(string, "%.1f:", -1.5f);
  extc_string_add_float(string, "%.1f", 1.5f);
  STRING_ASSERT(string, "-1.5:1.5");
}

void test_double(ExtcString* string){
  extc_string_clear(string);
  extc_string_add_double(string, "%.1f:", -1.5f);
  extc_string_add_double(string, "%.1f", 1.5f);
  STRING_ASSERT(string, "-1.5:1.5");
}

void test_string(ExtcString* string){
  extc_string_clear(string);
  extc_string_add_string(string, "%s:", "abcde");
  extc_string_add_string(string, "%s", "あいうえお");
  STRING_ASSERT(string, "abcde:あいうえお");
  extc_string_clear(string);
  extc_string_add_string_repeat(string, "ABC", 3);
  STRING_ASSERT(string, "ABCABCABC");
}

void test_escape(){
  char encodeFixedString[32];
  ExtcString encodeString = extc_string_fixed(encodeFixedString, sizeof(encodeFixedString));
  char decodeFixedString[32];
  ExtcString decodeString = extc_string_fixed(decodeFixedString, sizeof(decodeFixedString));
  extc_string_escape_encode(&encodeString, "1\\2\'3\"4\t5\n6", 11);
  STRING_ASSERT(&encodeString, "1\\\\2\\\'3\\\"4\\t5\\n6");
  extc_string_escape_decode(&decodeString, extc_string_get_chars(&encodeString), extc_string_get_length(&encodeString));
  STRING_ASSERT(&decodeString, "1\\2\'3\"4\t5\n6");
}

#define YAML_LINE_ASSERT(_yaml_line, _check_key, _check_value) yaml_line_assert(__FILE__, __LINE__, _yaml_line, _check_key, _check_value)
void yaml_line_assert(String file, int32 line, String yamlLine, String checkKey, String checkValue){
  char keyFixedString[32];
  ExtcString keyString = extc_string_fixed(keyFixedString, sizeof(keyFixedString));
  char valueFixedString[32];
  ExtcString valueString = extc_string_fixed(valueFixedString, sizeof(valueFixedString));
  extc_assert(file, line, extc_string_yaml_line_split(&keyString, &valueString, "Key: Value"), "yaml line split error");
  string_assert(file, line, &keyString, "Key");
  string_assert(file, line, &valueString, "Value");
}

void test_yaml_line(){
  YAML_LINE_ASSERT("Key: Value", "Key", "Value");
  YAML_LINE_ASSERT("Japanese: あいうえお", "Japanese", "あいうえお");
  YAML_LINE_ASSERT("Empty: ''", "Empty", "");
  YAML_LINE_ASSERT("Escape: 1\\\\2\\\'3\\\"4\\t5\\n6", "Escape", "1\\2\'3\"4\t5\n6");
}

int32 main(int32 argc, String argv[]){
  if (!extc_init()) return EXIT_FAILURE;
  EXTC_ASSERT(extc_string_equals(extc_string_guard(null), ""), "guard error");
  EXTC_ASSERT(extc_string_equals(extc_string_guard("abc"), "abc"), "guard error");
  EXTC_ASSERT(extc_string_starts_with("file.ext", ""), "starts with error");
  EXTC_ASSERT(!extc_string_starts_with("", "file"), "starts with error");
  EXTC_ASSERT(extc_string_starts_with("file.ext", "file"), "starts with error");
  EXTC_ASSERT(extc_string_starts_with("file.ext", "file.ext"), "starts with error");
  EXTC_ASSERT(!extc_string_starts_with("file.ext", "file.ext1"), "starts with error");
  EXTC_ASSERT(extc_string_ends_with("file.ext", ""), "ends with error");
  EXTC_ASSERT(!extc_string_ends_with("", ".ext"), "ends with error");
  EXTC_ASSERT(extc_string_ends_with("file.ext", ".ext"), "ends with error");
  EXTC_ASSERT(extc_string_ends_with("file.ext", "file.ext"), "ends with error");
  EXTC_ASSERT(!extc_string_ends_with("file.ext", "file.ext1"), "ends with error");
  EXTC_ASSERT(extc_string_to_int64("1") == 1, "to int64 error");
  EXTC_ASSERT(extc_string_to_int64("-1") == -1, "to int64 error");
  EXTC_ASSERT(extc_string_to_double("1.5") == 1.5, "to double error");
  EXTC_ASSERT(extc_string_to_double("-1.5") == -1.5, "to double error");
  ExtcString* string = extc_string_new();
  EXTC_ASSERT(string != null, "string=%p", string);
  STRING_ASSERT(string, "");
  test_int32(string);
  test_int64(string);
  test_float(string);
  test_double(string);
  test_string(string);
  test_escape();
  test_yaml_line();
  extc_string_delete(string);
  extc_string_delete(null);
  extc_exit();
  return EXIT_SUCCESS;
}
