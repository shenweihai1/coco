//
// Created by Yi Lu on 7/22/18.
//

#include "benchmark/ycsb/Database.h"
#include "benchmark/ycsb/Transaction.h"
#include "core/Partitioner.h"
#include "protocol/Silo/Silo.h"
#include <gtest/gtest.h>

TEST(TestYCSBTransaction, TestBasic) {

  using MetaDataType = std::atomic<uint64_t>;
  using DatabaseType = scar::ycsb::Database<MetaDataType>;
  using RWKeyType = scar::SiloRWKey;

  DatabaseType db;
  scar::ycsb::Context context;
  scar::ycsb::Random random;

  scar::HashPartitioner partitioner(0, 1);

  std::atomic<uint64_t> epoch;
  scar::Silo<decltype(db)> silo(db, epoch, partitioner);

  scar::ycsb::ReadModifyWrite<RWKeyType, DatabaseType> t(db, context, random);
  EXPECT_EQ(true, true);
}
