/**
 * @file test_exception.cpp
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Main
 */
#include <gtest/gtest.h>

#include <stdexcept>

#include "symaware/util/exception.h"

TEST(TestException, AssertFail) { EXPECT_DEATH(SYMAWARE_ASSERT(false, "Message"), "Assertion `false` failed"); }

TEST(TestException, AssertFailReport) { EXPECT_DEATH(SYMAWARE_ASSERT(1 + 1 == 3, "Message"), "Message"); }

TEST(TestException, AssertSuccess) { EXPECT_NO_THROW(SYMAWARE_ASSERT(true, "Message")); }

TEST(TestException, Unreachable) { EXPECT_DEATH(SYMAWARE_UNREACHABLE(), "Should not be reachable"); }

TEST(TestException, RuntimeError) { EXPECT_THROW(SYMAWARE_RUNTIME_ERROR("Message"), std::runtime_error); }

TEST(TestLogging, RuntimeErrorFmt) {
  EXPECT_THROW(SYMAWARE_RUNTIME_ERROR_FMT("Message: {}", "format"), std::runtime_error);
}
