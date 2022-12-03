#include "Day1/Day1.hpp"
#include "Day2/Day2.hpp"

#include <array>
#include <format>
#include <iostream>


int main() {
  std::cout << std::format(
      "Day 1: {}, {}\n",
      Day1::CalculateCalories().value_or(0),
      Day1::CalculateTotalNCalories(3).value_or(0));
  std::cout << std::format(
      "Day 2: {}, {}\n",
      Day2::CalculateTotalScore().value_or(0),
      Day2::CalculateStrategyScore().value_or(0));
}
