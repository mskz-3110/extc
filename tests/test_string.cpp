#include <extc.hpp>

#define STRING_ASSERT(_string, _check_chars) string_assert(__FILE__, __LINE__, _string, _check_chars)
void string_assert(const char* file, int32 line, extc::String* string, const char* checkChars){
  const char* chars = string->GetChars();
  int32 length = string->GetLength();
  extc_assert(file, line, length == (int32)strlen(checkChars) && extc::String::Equals(chars, checkChars), "length=%d chars='%s'", length, chars);
}

void test_int32(extc::String* string){
  string->Clear();
  string->AddInt32("%d:", -1);
  string->AddInt32("%d", 1);
  STRING_ASSERT(string, "-1:1");
}

void test_int64(extc::String* string){
  string->Clear();
  string->AddInt64("%lld:", -1);
  string->AddInt64("%lld", 1);
  STRING_ASSERT(string, "-1:1");
}

void test_float(extc::String* string){
  string->Clear();
  string->AddFloat("%.1f:", -1.5f);
  string->AddFloat("%.1f", 1.5f);
  STRING_ASSERT(string, "-1.5:1.5");
}

void test_double(extc::String* string){
  string->Clear();
  string->AddDouble("%.1f:", -1.5f);
  string->AddDouble("%.1f", 1.5f);
  STRING_ASSERT(string, "-1.5:1.5");
}

void test_string(extc::String* string){
  string->Clear();
  string->AddString("%s:", "abcde");
  string->AddString("%s", "あいうえお");
  STRING_ASSERT(string, "abcde:あいうえお");
  string->Clear();
  string->AddStringRepeat("ABC", 3);
  STRING_ASSERT(string, "ABCABCABC");
}

void test_escape(){
  extc::String* encodeString = extc::String::EscapeEncode("1\\2\'3\"4\t5\n6", 11);
  STRING_ASSERT(encodeString, "1\\\\2\\\'3\\\"4\\t5\\n6");
  extc::String* decodeString = extc::String::EscapeDecode(encodeString->GetChars(), encodeString->GetLength());
  STRING_ASSERT(decodeString, "1\\2\'3\"4\t5\n6");
  delete encodeString;
  delete decodeString;
}

#define YAML_LINE_ASSERT(_yaml_line, _check_key, _check_value) yaml_line_assert(__FILE__, __LINE__, _yaml_line, _check_key, _check_value)
void yaml_line_assert(const char* file, int32 line, const char* yamlLine, const char* checkKey, const char* checkValue){
  extc::String* keyString = extc::String::YamlLineSplitKey(yamlLine);
  extc_assert(file, line, keyString != null, "keyString is null");
  extc::String* valueString = extc::String::YamlLineSplitValue(yamlLine);
  extc_assert(file, line, valueString != null, "valueString is null");
  string_assert(file, line, keyString, checkKey);
  string_assert(file, line, valueString, checkValue);
  delete keyString;
  delete valueString;
}

void test_yaml_line(){
  YAML_LINE_ASSERT("Key: Value", "Key", "Value");
  YAML_LINE_ASSERT("Japanese: あいうえお", "Japanese", "あいうえお");
  YAML_LINE_ASSERT("Empty: ''", "Empty", "");
  YAML_LINE_ASSERT("Escape: 1\\\\2\\\'3\\\"4\\t5\\n6", "Escape", "1\\2\'3\"4\t5\n6");
}

int32 main(int32 argc, const char* argv[]){
  if (!extc::Extc::Init()) return EXIT_FAILURE;
  EXTC_ASSERT(extc::String::Equals(extc::String::Guard(null), ""), "guard error");
  EXTC_ASSERT(extc::String::Equals(extc::String::Guard("abc"), "abc"), "guard error");
  EXTC_ASSERT(extc::String::StartsWith("file.ext", ""), "starts with error");
  EXTC_ASSERT(!extc::String::StartsWith("", "file"), "starts with error");
  EXTC_ASSERT(extc::String::StartsWith("file.ext", "file"), "starts with error");
  EXTC_ASSERT(extc::String::StartsWith("file.ext", "file.ext"), "starts with error");
  EXTC_ASSERT(!extc::String::StartsWith("file.ext", "file.ext1"), "starts with error");
  EXTC_ASSERT(extc::String::EndsWith("file.ext", ""), "ends with error");
  EXTC_ASSERT(!extc::String::EndsWith("", ".ext"), "ends with error");
  EXTC_ASSERT(extc::String::EndsWith("file.ext", ".ext"), "ends with error");
  EXTC_ASSERT(extc::String::EndsWith("file.ext", "file.ext"), "ends with error");
  EXTC_ASSERT(!extc::String::EndsWith("file.ext", "file.ext1"), "ends with error");
  EXTC_ASSERT(extc::String::ToInt64("1") == 1, "to int64 error");
  EXTC_ASSERT(extc::String::ToInt64("-1") == -1, "to int64 error");
  EXTC_ASSERT(extc::String::ToDouble("1.5") == 1.5, "to double error");
  EXTC_ASSERT(extc::String::ToDouble("-1.5") == -1.5, "to double error");
  extc::String* string = new extc::String();
  EXTC_ASSERT(string != null, "string is null");
  STRING_ASSERT(string, "");
  test_int32(string);
  test_int64(string);
  test_float(string);
  test_double(string);
  test_string(string);
  delete string;
  test_escape();
  test_yaml_line();
  extc_string_delete(null);
  extc::Extc::Exit();
  return EXIT_SUCCESS;
}
