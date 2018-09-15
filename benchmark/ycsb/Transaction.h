//
// Created by Yi Lu on 7/22/18.
//

#pragma once

#include "glog/logging.h"

#include "benchmark/ycsb/Database.h"
#include "benchmark/ycsb/Query.h"
#include "benchmark/ycsb/Schema.h"
#include "benchmark/ycsb/Storage.h"
#include "core/Defs.h"
#include "core/Partitioner.h"
#include "core/Table.h"

namespace scar {
namespace ycsb {

template <class Transaction> class ReadModifyWrite : public Transaction {

public:
  using MetaDataType = typename Transaction::MetaDataType;
  using DatabaseType = Database<MetaDataType>;
  using ContextType = typename DatabaseType::ContextType;
  using RandomType = typename DatabaseType::RandomType;
  using TableType = ITable<MetaDataType>;
  using StorageType = Storage;

  ReadModifyWrite(std::size_t coordinator_id, std::size_t partition_id,
                  DatabaseType &db, const ContextType &context,
                  RandomType &random, Partitioner &partitioner,
                  Storage &storage)
      : Transaction(coordinator_id, partition_id, partitioner), db(db),
        context(context), random(random), storage(storage),
        query(makeYCSBQuery<YCSB_FIELD_SIZE>()(context, partition_id, random)) {
  }

  virtual ~ReadModifyWrite() override = default;

  TransactionResult execute() override {

    RandomType random;

    DCHECK(context.keysPerTransaction == YCSB_FIELD_SIZE);

    int ycsbTableID = ycsb::tableID;

    for (auto i = 0; i < YCSB_FIELD_SIZE; i++) {
      auto key = query.Y_KEY[i];
      storage.ycsb_keys[i].Y_KEY = key;
      this->search_for_update(ycsbTableID, context.getPartitionID(key),
                              storage.ycsb_keys[i], storage.ycsb_values[i]);
    }

    if (this->process_requests()) {
      return TransactionResult::ABORT;
    }

    for (auto i = 0; i < YCSB_FIELD_SIZE; i++) {
      auto key = query.Y_KEY[i];
      if (query.UPDATE[i]) {
        storage.ycsb_values[i].Y_F01.assign(
            random.a_string(YCSB_FIELD_SIZE, YCSB_FIELD_SIZE));
        storage.ycsb_values[i].Y_F02.assign(
            random.a_string(YCSB_FIELD_SIZE, YCSB_FIELD_SIZE));
        storage.ycsb_values[i].Y_F03.assign(
            random.a_string(YCSB_FIELD_SIZE, YCSB_FIELD_SIZE));
        storage.ycsb_values[i].Y_F04.assign(
            random.a_string(YCSB_FIELD_SIZE, YCSB_FIELD_SIZE));
        storage.ycsb_values[i].Y_F05.assign(
            random.a_string(YCSB_FIELD_SIZE, YCSB_FIELD_SIZE));
        storage.ycsb_values[i].Y_F06.assign(
            random.a_string(YCSB_FIELD_SIZE, YCSB_FIELD_SIZE));
        storage.ycsb_values[i].Y_F07.assign(
            random.a_string(YCSB_FIELD_SIZE, YCSB_FIELD_SIZE));
        storage.ycsb_values[i].Y_F08.assign(
            random.a_string(YCSB_FIELD_SIZE, YCSB_FIELD_SIZE));
        storage.ycsb_values[i].Y_F09.assign(
            random.a_string(YCSB_FIELD_SIZE, YCSB_FIELD_SIZE));
        storage.ycsb_values[i].Y_F10.assign(
            random.a_string(YCSB_FIELD_SIZE, YCSB_FIELD_SIZE));

        this->update(ycsbTableID, context.getPartitionID(key),
                     storage.ycsb_keys[i], storage.ycsb_values[i]);
      }
    }
    return TransactionResult::READY_TO_COMMIT;
  }

private:
  DatabaseType &db;
  const ContextType &context;
  RandomType &random;
  Storage &storage;
  YCSBQuery<YCSB_FIELD_SIZE> query;
};
} // namespace ycsb

} // namespace scar
