#ifndef RQT2_UTIL__VISIBILITY_CONTROL_H_
#define RQT2_UTIL__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define RQT2_UTIL_EXPORT __attribute__ ((dllexport))
    #define RQT2_UTIL_IMPORT __attribute__ ((dllimport))
  #else
    #define RQT2_UTIL_EXPORT __declspec(dllexport)
    #define RQT2_UTIL_IMPORT __declspec(dllimport)
  #endif
  #ifdef RQT2_UTIL_BUILDING_LIBRARY
    #define RQT2_UTIL_PUBLIC RQT2_UTIL_EXPORT
  #else
    #define RQT2_UTIL_PUBLIC RQT2_UTIL_IMPORT
  #endif
  #define RQT2_UTIL_PUBLIC_TYPE RQT2_UTIL_PUBLIC
  #define RQT2_UTIL_LOCAL
#else
  #define RQT2_UTIL_EXPORT __attribute__ ((visibility("default")))
  #define RQT2_UTIL_IMPORT
  #if __GNUC__ >= 4
    #define RQT2_UTIL_PUBLIC __attribute__ ((visibility("default")))
    #define RQT2_UTIL_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define RQT2_UTIL_PUBLIC
    #define RQT2_UTIL_LOCAL
  #endif
  #define RQT2_UTIL_PUBLIC_TYPE
#endif

#endif  // RQT2_UTIL__VISIBILITY_CONTROL_H_
