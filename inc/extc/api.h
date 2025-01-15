#ifndef __EXTC_API_H__
#define __EXTC_API_H__
#include <extc/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef EXTC_WINDOWS
  #define __EXTC_API_PREFIX __declspec(dllexport)
#else
  #define __EXTC_API_PREFIX
#endif
#define EXTC_API_SRC(_return_type, _name, ...) _return_type _name(__VA_ARGS__)
#define EXTC_API_INC(_return_type, _name, ...) __EXTC_API_PREFIX EXTC_API_SRC(_return_type, _name, ## __VA_ARGS__);

#ifdef __cplusplus
  #define EXTC_API_BEGIN extern "C" {
  #define EXTC_API_END   }
#else
  #define EXTC_API_BEGIN
  #define EXTC_API_END
#endif
#endif
