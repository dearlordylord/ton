/*
 * Copyright (c) 2025-2026, TON CORE TECHNOLOGIES CO. L.L.C
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include "auto/tl/ton_api.h"
#include "td/utils/Status.h"
#include "td/utils/tl_parsers.h"

namespace ton::validator::consensus {

inline td::Status validate_broadcast_data(td::Slice data) {
  if (data.size() < 4) {
    return td::Status::Error("Broadcast data too small");
  }
  td::TlParser parser(data);
  auto magic = parser.fetch_int();
  if (magic != ton_api::consensus_block::ID && magic != ton_api::consensus_empty::ID) {
    return td::Status::Error("Unknown broadcast TL type");
  }
  return td::Status::OK();
}

}  // namespace ton::validator::consensus
