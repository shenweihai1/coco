//
// Created by Yi Lu on 7/22/18.
//

#ifndef SCAR_WORKER_H
#define SCAR_WORKER_H

#include "core/Transaction.h"
#include <atomic>

namespace scar {

template <class Workload> class Worker {
public:
  using WorkloadType = Workload;
  using DatabaseType = typename Workload::DatabaseType;
  using ProtocolType = typename DatabaseType::ProtocolType;
  using ContextType = typename DatabaseType::ContextType;
  using RandomType = typename DatabaseType::RandomType;

  Worker(DatabaseType &db, ContextType &context, std::atomic<uint64_t> &epoch,
         std::atomic<bool> &stopFlag)
      : db(db), context(context), stopFlag(stopFlag), protocol(epoch),
        workload(db, context, random, protocol) {}

  void start() {

    int cnt = 0;

    while (!stopFlag.load()) {
      std::unique_ptr<Transaction<DatabaseType>> p = workload.nextTransaction();
      p->execute();
      if (++cnt == 10) {
        break;
      }
    }
  }

private:
  DatabaseType &db;
  ContextType &context;
  std::atomic<bool> &stopFlag;
  RandomType random;
  ProtocolType protocol;
  WorkloadType workload;
};

} // namespace scar

#endif // SCAR_WORKER_H
