#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define APPLICATION_EXPORT __declspec(dllexport)
#else
  #define APPLICATION_EXPORT
#endif

APPLICATION_EXPORT void application();
APPLICATION_EXPORT void application_print_vector(const std::vector<std::string> &strings);
