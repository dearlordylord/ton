/*
 * Copyright (c) 2025-2026, TON CORE TECHNOLOGIES CO. L.L.C
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include "td/utils/buffer.h"
#include "validator/consensus/misbehavior.h"

namespace ton::validator::consensus::simplex {

class ConflictingVotes : public Misbehavior {
 public:
  static MisbehaviorRef create(td::BufferSlice vote1, td::BufferSlice vote2) {
    return td::make_ref<ConflictingVotes>(std::move(vote1), std::move(vote2));
  }

  ConflictingVotes(td::BufferSlice vote1, td::BufferSlice vote2) : vote1_(std::move(vote1)), vote2_(std::move(vote2)) {
  }

 private:
  td::BufferSlice vote1_;
  td::BufferSlice vote2_;
};

class ConflictingCandidateAndCertificate : public Misbehavior {
 public:
  static MisbehaviorRef create(td::BufferSlice candidate, td::BufferSlice certificate) {
    return td::make_ref<ConflictingCandidateAndCertificate>(std::move(candidate), std::move(certificate));
  }

  ConflictingCandidateAndCertificate(td::BufferSlice candidate, td::BufferSlice certificate)
      : candidate_(std::move(candidate)), certificate_(std::move(certificate)) {
  }

 private:
  td::BufferSlice candidate_;
  td::BufferSlice certificate_;
};

class InvalidCandidate : public Misbehavior {
 public:
  static MisbehaviorRef create(td::BufferSlice candidate) {
    return td::make_ref<InvalidCandidate>(std::move(candidate));
  }

  explicit InvalidCandidate(td::BufferSlice candidate) : candidate_(std::move(candidate)) {
  }

 private:
  td::BufferSlice candidate_;
};

class ConflictingCandidates : public Misbehavior {
 public:
  static MisbehaviorRef create(td::BufferSlice candidate1, td::BufferSlice candidate2) {
    return td::make_ref<ConflictingCandidates>(std::move(candidate1), std::move(candidate2));
  }

  ConflictingCandidates(td::BufferSlice candidate1, td::BufferSlice candidate2)
      : candidate1_(std::move(candidate1)), candidate2_(std::move(candidate2)) {
  }

 private:
  td::BufferSlice candidate1_;
  td::BufferSlice candidate2_;
};

}  // namespace ton::validator::consensus::simplex
