#ifndef __EXTC_HPP__
#define __EXTC_HPP__
#include <extc.h>
#include <extc/string.hpp>
namespace extc {
  class Extc {
    public:
    static bool Init(){return extc_init();}
    static void Exit(){extc_exit();}
  };
}
#endif
