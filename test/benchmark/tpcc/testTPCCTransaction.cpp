//
// Created by Yi Lu on 7/22/18.
//

#include "benchmark/tpcc/Database.h"
#include "benchmark/tpcc/Operation.h"
#include "benchmark/tpcc/Transaction.h"
#include "core/Partitioner.h"
#include "protocol/Silo/Silo.h"
#include "protocol/Silo/SiloTransaction.h"
#include <gtest/gtest.h>

TEST(TestTPCCTransaction, TestBasic) {

  using MetaDataType = std::atomic<uint64_t>;
  using DatabaseType = scar::tpcc::Database<MetaDataType>;

  DatabaseType db;
  scar::tpcc::Context context;
  scar::tpcc::Random random;

  scar::HashPartitioner partitioner(0, 1);

  scar::tpcc::Storage storage;
  scar::tpcc::Operation operation;

  scar::Silo<decltype(db)> silo(db, partitioner);
  scar::tpcc::NewOrder<scar::SiloTransaction> t1(
      0, 0, db, context, random, partitioner, storage, operation);
  scar::tpcc::Payment<scar::SiloTransaction> t2(
      0, 0, db, context, random, partitioner, storage, operation);
  EXPECT_EQ(true, true);
}
