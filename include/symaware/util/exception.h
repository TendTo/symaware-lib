/**
 * @file exception.h
 * @author dlinear
 * @date 07 Aug 2023
 * @copyright 2023 dlinear
 * @brief Utilities that verify assumptions made by the program and aborts
 * the program if those assumptions are not true.
 *
 * If NDEBUG is defined, most of the macro do nothing and give no explanation.
 * It makes the program faster, but less useful for debugging.
 */
#pragma once

#include <stdexcept>

#ifdef NDEBUG

#include <utility>

#define SYMAWARE_ASSERT(condition, msg) ((void)0)
#define SYMAWARE_ASSERT_FMT(condition, msg, ...) ((void)0)
#define SYMAWARE_UNREACHABLE() std::unreachable()
#define SYMAWARE_RUNTIME_ERROR(msg) throw std::runtime_error(msg)
#define SYMAWARE_RUNTIME_ERROR_FMT(msg, ...) throw std::runtime_error(msg)
#define SYMAWARE_OUT_OF_RANGE_FMT(msg, ...) throw std::out_of_range(msg)
#define SYMAWARE_INVALID_ARGUMENT(argument, actual) throw std::runtime_error(argument)
#define SYMAWARE_INVALID_ARGUMENT_EXPECTED(argument, actual, expected) throw std::runtime_error(argument)

#else

#include <fmt/core.h>

#include <iostream>

#define SYMAWARE_ASSERT(condition, message)                                                                \
  do {                                                                                                     \
    if (!(condition)) {                                                                                    \
      fmt::println(stderr, "Assertion `{}` failed in {}:{}: {}", #condition, __FILE__, __LINE__, message); \
      std::terminate();                                                                                    \
    }                                                                                                      \
  } while (false)

#define SYMAWARE_ASSERT_FMT(condition, message, ...)                                          \
  do {                                                                                        \
    if (!(condition)) {                                                                       \
      fmt::println(stderr, "Assertion `{}` failed in {}:{}", #condition, __FILE__, __LINE__); \
      fmt::println(stderr, message, __VA_ARGS__);                                             \
      std::terminate();                                                                       \
    }                                                                                         \
  } while (false)

#define SYMAWARE_UNREACHABLE()                                                  \
  do {                                                                          \
    fmt::println(stderr, "{}:{} Should not be reachable.", __FILE__, __LINE__); \
    std::terminate();                                                           \
  } while (false)

#define SYMAWARE_RUNTIME_ERROR(msg) \
  do {                              \
    std::cerr << msg << std::endl;  \
    throw std::runtime_error(msg);  \
  } while (false)

#define SYMAWARE_RUNTIME_ERROR_FMT(msg, ...)                 \
  do {                                                       \
    fmt::println(stderr, msg, __VA_ARGS__);                  \
    throw std::runtime_error(fmt::format(msg, __VA_ARGS__)); \
  } while (false)

#define SYMAWARE_OUT_OF_RANGE_FMT(msg, ...)                 \
  do {                                                      \
    fmt::println(stderr, msg, __VA_ARGS__);                 \
    throw std::out_of_range(fmt::format(msg, __VA_ARGS__)); \
  } while (false)

#define SYMAWARE_INVALID_ARGUMENT(argument, actual) \
  throw std::invalid_argument(fmt::format("Invalid argument for {}: {}", argument, actual))

#define SYMAWARE_INVALID_ARGUMENT_EXPECTED(argument, actual, expected) \
  throw std::invalid_argument(                                         \
      fmt::format("Invalid argument for {}: received '{}', expected '{}'", argument, actual, expected))

#endif
