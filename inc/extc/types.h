#ifndef __EXTC_TYPES_H__
#define __EXTC_TYPES_H__
#if defined(_WIN32) || defined(_WIN64)
  #include <windows.h>
  #define _CRTDBG_MAP_ALLOC
  #include <crtdbg.h>
  #define EXTC_WINDOWS
#endif

#define EXTC_TYPEDEC_BEGIN(_type) typedef _type {
#define EXTC_TYPEDEC_END(_name) } _name;
#define EXTC_STRUCT_BEGIN EXTC_TYPEDEC_BEGIN(struct)
#define EXTC_STRUCT_END(_name) EXTC_TYPEDEC_END(_name)
#define EXTC_UNION_BEGIN EXTC_TYPEDEC_BEGIN(union)
#define EXTC_UNION_END(_name) EXTC_TYPEDEC_END(_name)
#define EXTC_ENUM_BEGIN EXTC_TYPEDEC_BEGIN(enum)
#define EXTC_ENUM_END(_name) EXTC_TYPEDEC_END(_name)
#define EXTC_CALLBACK(_return_type, _name, ...) typedef _return_type (*_name)(__VA_ARGS__);

#ifndef null
  #define null NULL
#endif

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>

#ifndef int8
  #define int8 int8_t
#endif
#ifndef uint8
  #define uint8 uint8_t
#endif
#ifndef int16
  #define int16 int16_t
#endif
#ifndef uint16
  #define uint16 uint16_t
#endif
#ifndef int32
  #define int32 int32_t
#endif
#ifndef uint32
  #define uint32 uint32_t
#endif
#ifndef int64
  #define int64 int64_t
#endif
#ifndef uint64
  #define uint64 uint64_t
#endif
#endif
