/*
 * Copyright (c) 2025-2026, TON CORE TECHNOLOGIES CO. L.L.C
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "consensus/broadcast-validation.h"

#include "auto/tl/ton_api.h"
#include "td/utils/buffer.h"
#include "td/utils/logging.h"

using namespace ton;
using namespace ton::validator::consensus;

static void test_empty_data() {
  auto r = validate_broadcast_data(td::Slice());
  CHECK(r.is_error());
  LOG(INFO) << "test_empty_data: OK";
}

static void test_too_small() {
  char buf[3] = {1, 2, 3};
  auto r = validate_broadcast_data(td::Slice(buf, 3));
  CHECK(r.is_error());
  LOG(INFO) << "test_too_small: OK";
}

static void test_unknown_magic() {
  td::int32 magic = 0x12345678;
  auto r = validate_broadcast_data(td::Slice(reinterpret_cast<const char*>(&magic), 4));
  CHECK(r.is_error());
  LOG(INFO) << "test_unknown_magic: OK";
}

static void test_valid_block() {
  td::int32 magic = ton_api::consensus_block::ID;
  auto r = validate_broadcast_data(td::Slice(reinterpret_cast<const char*>(&magic), 4));
  CHECK(r.is_ok());
  LOG(INFO) << "test_valid_block: OK";
}

static void test_valid_empty() {
  td::int32 magic = ton_api::consensus_empty::ID;
  auto r = validate_broadcast_data(td::Slice(reinterpret_cast<const char*>(&magic), 4));
  CHECK(r.is_ok());
  LOG(INFO) << "test_valid_empty: OK";
}

static void test_exactly_4_bytes_garbage() {
  td::int32 magic = 0;
  auto r = validate_broadcast_data(td::Slice(reinterpret_cast<const char*>(&magic), 4));
  CHECK(r.is_error());
  LOG(INFO) << "test_exactly_4_bytes_garbage: OK";
}

int main() {
  test_empty_data();
  test_too_small();
  test_unknown_magic();
  test_valid_block();
  test_valid_empty();
  test_exactly_4_bytes_garbage();
  LOG(INFO) << "All broadcast validation tests passed";
  return 0;
}
