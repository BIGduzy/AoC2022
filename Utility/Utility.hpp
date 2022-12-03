#ifndef AOC2022_UTILITY
#define AOC2022_UTILITY

#include <fstream>

namespace Utility {
  namespace Literals {
    auto operator""_file(const char* path, [[maybe_unused]] size_t size) -> std::fstream {
      return std::fstream{path};
    };

    constexpr std::size_t operator""_uz(unsigned long long int number) {
      return number;
    }
  } // namespace Literals
  void Test(){};
} // namespace Utility

#endif
