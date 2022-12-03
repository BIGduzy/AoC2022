#ifndef AOC2022_DAY1
#define AOC2022_DAY1

#include "Utility/Utility.hpp"

#include <algorithm>
#include <limits>
#include <numeric>
#include <optional>
#include <vector>


namespace Day1 {
  using namespace Utility::Literals;
  namespace Impl {
    auto ReadDataFromFile() -> std::optional<std::vector<size_t>> {
      auto inputStream{"Day1/input.txt"_file};
      if (!inputStream.is_open()) {
        return std::nullopt; // TODO: Use ResultType lib
      }

      auto calories{0_uz};
      auto caloryCounter{0_uz};
      std::vector<size_t> elves{};
      while (inputStream >> calories) {
        caloryCounter += calories;

        // Elves are separated by two newline characters
        if (inputStream.get() == '\n' && inputStream.peek() == '\n') {
          elves.emplace_back(caloryCounter);
          caloryCounter = 0;
        }
      }

      return elves;
    }
  } // namespace Impl
  auto CalculateTotalNCalories(size_t numberOfElves) -> std::optional<size_t> {
    auto result{Impl::ReadDataFromFile()};
    if (result.has_value() && numberOfElves < std::numeric_limits<int>::max()) {
      auto& elves = result.value();
      std::sort(std::begin(elves), std::end(elves), std::greater<size_t>{});
      return std::accumulate(
          std::begin(elves),
          std::next(std::begin(elves), static_cast<int>(numberOfElves)),
          0_uz);
    }
    return std::nullopt;
  }

  auto CalculateCalories() -> std::optional<size_t> {
    return CalculateTotalNCalories(1);
  }
} // namespace Day1

#endif