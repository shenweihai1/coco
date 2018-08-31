//
// Created by Yi Lu on 8/31/18.
//

#pragma once

enum class SiloMessage {
  READ_REQUEST,
  READ_RESPONSE,
  LOCK_REQUEST,
  LOCK_RESPONSE,
  READ_VALIDATION_REQUEST,
  READ_VALIDATION_RESPONSE,
  ABORT_REQUEST,
  WRITE_REQUEST,
  REPLICATION_REQUEST,
  REPLICATION_RESPONSE,
  NFIELDS
};
