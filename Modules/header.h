// Disabling the "pragma once" and switching to the regular header guards
// fixes the build.

// These modules files are not represented in the .xcproj so don't show up
// in the XCode editor. For some reason that makes the reproduction case
// stop working.

#pragma once

//#ifndef header_h
//#define header_h

#define MY_MACRO 5
typedef int my_int;

//#endif // header_h
