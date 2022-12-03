#ifndef AOC2022_DAY2
#define AOC2022_DAY2

#include "Utility/Utility.hpp"

#include <format>
#include <fstream>
#include <iostream>
#include <numeric>
#include <optional>
#include <unordered_map>
#include <vector>


namespace Day2 {
  using namespace Utility::Literals;
  namespace Impl {
    enum class Move_e { ROCK = 0, PAPER, SCISSORS };
    enum class Strategy_e { LOSE = 0, DRAW, WIN };
    using Turn = std::pair<Move_e, Move_e>;
    using Strategy = std::pair<Move_e, Strategy_e>;


    const std::unordered_map<Move_e, Move_e> WINNING_MOVES{
        {Move_e::ROCK, Move_e::SCISSORS},
        {Move_e::PAPER, Move_e::ROCK},
        {Move_e::SCISSORS, Move_e::PAPER},
    };
    const std::unordered_map<Move_e, Move_e> LOSING_MOVES{
        {Move_e::ROCK, Move_e::PAPER},
        {Move_e::PAPER, Move_e::SCISSORS},
        {Move_e::SCISSORS, Move_e::ROCK},
    };

    std::istream& operator>>(std::istream& stream, Move_e& move) {
      char nextChar{};
      stream >> nextChar;

      if (nextChar == 'A' || nextChar == 'X') {
        move = Move_e::ROCK;
      } else if (nextChar == 'B' || nextChar == 'Y') {
        move = Move_e::PAPER;
      } else if (nextChar == 'C' || nextChar == 'Z') {
        move = Move_e::SCISSORS;
      }

      return stream;
    }
    std::istream& operator>>(std::istream& stream, Strategy_e& move) {
      char nextChar{};
      stream >> nextChar;

      if (nextChar == 'X') {
        move = Strategy_e::LOSE;
      } else if (nextChar == 'Y') {
        move = Strategy_e::DRAW;
      } else if (nextChar == 'Z') {
        move = Strategy_e::WIN;
      }

      return stream;
    }

    template<typename T1, typename T2>
    std::istream& operator>>(std::istream& stream, std::pair<T1, T2>& pair) {
      stream >> pair.first;
      stream >> std::skipws;
      stream >> pair.second;
      return stream;
    }

    [[nodiscard]] auto CalculateRoundScore(const Turn& turn) -> size_t {
      const std::unordered_map<Move_e, size_t> moveScores{
          {Move_e::ROCK, 1_uz},
          {Move_e::PAPER, 2_uz},
          {Move_e::SCISSORS, 3_uz},
      };

      const auto& [opponent, you]{turn};
      const auto moveScore{moveScores.at(you)};
      const auto outcomeScore{[](const auto& turn) {
        const auto& [opponent, you]{turn};
        constexpr auto winningScore{6_uz};
        constexpr auto drawScore{3_uz};
        constexpr auto lostScore{0_uz};

        if (WINNING_MOVES.at(you) == opponent) {
          return winningScore;
        }

        return (you == opponent) ? drawScore : lostScore;
      }(turn)};

      return moveScore + outcomeScore;
    }

    [[nodiscard]] auto CalculateStrategyRoundScore(const Strategy& turn) -> size_t {
      constexpr auto implementStrategy{[](const auto& turn) {
        const auto& [opponentMove, strategy]{turn};

        switch (strategy) {
          case Strategy_e::LOSE: {
            return WINNING_MOVES.at(opponentMove);
          }
          case Strategy_e::DRAW: {
            return opponentMove;
          }
          case Strategy_e::WIN: {
            return LOSING_MOVES.at(opponentMove);
          }
        }
      }};

      const auto& [opponentMove, strategy]{turn};
      return CalculateRoundScore({opponentMove, implementStrategy(turn)});
    }

    template<typename StrategyType>
    [[nodiscard]] auto ReadDataFromFile() -> std::optional<std::vector<StrategyType>> {
      auto inputStream{"Day2/input.txt"_file};
      if (!inputStream.is_open()) {
        return std::nullopt; // TODO: Use ResultType lib
      }

      StrategyType turn{};
      std::vector<StrategyType> turns;
      while (inputStream >> turn) {
        turns.emplace_back(turn);
      }

      return turns;
    }
  } // namespace Impl

  [[nodiscard]] auto CalculateTotalScore() -> std::optional<size_t> {
    auto result{Impl::ReadDataFromFile<Impl::Turn>()};

    if (result.has_value()) {
      const auto& moves{result.value()};
      return std::transform_reduce(
          std::begin(moves),
          std::end(moves),
          0_uz,
          std::plus{},
          Impl::CalculateRoundScore);
    }

    return std::nullopt;
  }

  [[nodiscard]] auto CalculateStrategyScore() -> std::optional<size_t> {
    auto result{Impl::ReadDataFromFile<Impl::Strategy>()};

    if (result.has_value()) {
      const auto& moves{result.value()};
      return std::transform_reduce(
          std::begin(moves),
          std::end(moves),
          0_uz,
          std::plus{},
          Impl::CalculateStrategyRoundScore);
    }

    return std::nullopt;
  }
} // namespace Day2

#endif
