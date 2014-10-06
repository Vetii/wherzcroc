#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <sstream>

template<typename T> std::wstring toWString(const T& t) {
  std::wstringstream stringStream;
  stringStream << t;
  return stringStream.str();
}

#endif