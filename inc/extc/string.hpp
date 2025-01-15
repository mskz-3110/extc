#ifndef __EXTC_STRING_HPP__
#define __EXTC_STRING_HPP__
#include <extc/string.h>

namespace extc {
  class String {
    public:
      static const char* Empty(){return extc_string_empty();}
      static const char* Guard(const char* value){return extc_string_guard(value);}
      static bool Equals(const char* value1, const char* value2){return extc_string_equals(value1, value2);}
      static bool StartsWith(const char* targetValue, const char* checkValue){return extc_string_starts_with(targetValue, checkValue);}
      static bool EndsWith(const char* targetValue, const char* checkValue){return extc_string_ends_with(targetValue, checkValue);}
      static int64 ToInt64(const char* value){return extc_string_to_int64(value);}
      static double ToDouble(const char* value){return extc_string_to_double(value);}
      static String* EscapeEncode(const char* value, int32 length){return new String(extc_string_escape_encode(value, length));}
      static String* EscapeDecode(const char* value, int32 length){return new String(extc_string_escape_decode(value, length));}
      static String* YamlLineSplitKey(const char* yamlLine){return new String(extc_string_yaml_line_split_key(yamlLine));}
      static String* YamlLineSplitValue(const char* yamlLine){return new String(extc_string_yaml_line_split_value(yamlLine));}

    private:
      ExtcString* m_String;

    public:
      String(){
        m_String = extc_string_new(); 
      }

      String(ExtcString* string){
        m_String = string;
      }

      ~String(){
        extc_string_delete(m_String);
      }

      const char* GetChars(){return extc_string_get_chars(m_String);}
      int32 GetLength(){return extc_string_get_length(m_String);}

      void Clear(){extc_string_clear(m_String);}

      void AddInt32(const char* format, int32 value){extc_string_add_int32(m_String, format, value);}
      void AddInt64(const char* format, int64 value){extc_string_add_int64(m_String, format, value);}
      void AddFloat(const char* format, float value){extc_string_add_float(m_String, format, value);}
      void AddDouble(const char* format, double value){extc_string_add_double(m_String, format, value);}
      void AddString(const char* format, const char* value){extc_string_add_string(m_String, format, value);}
      void AddStringRepeat(const char* value, int32 repeatCount){extc_string_add_string_repeat(m_String, value, repeatCount);}

      void VPrintf(const char* format, va_list list){extc_string_vprintf(m_String, format, list);}
      void Printf(const char* format, ...){
        va_list list;
        va_start(list, format);
        extc_string_vprintf(m_String, format, list);
        va_end(list);
      }
  };
}
#endif
