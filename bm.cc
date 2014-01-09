#include <cassert>

#include "benchmark/benchmark.h"
#include "cache.h"

void BM_Put(benchmark::State& state) {
  Cache<int, int> c(state.range_x());

  while (state.KeepRunning()) {
    for (int i = 0; i < state.range_y(); ++i) {
      c.Put(i, i);
    }
  }
  state.SetItemsProcessed(int64_t(state.iterations())*state.range_y());
}
BENCHMARK(BM_Put)->RangePair(1, 1<<10, 1, 1<<12);

void BM_Get(benchmark::State& state) {
  Cache<int, int> c(state.range_x());
  state.PauseTiming();
  for (int i = 0; i < state.range_y(); ++i) {
    c.Put(i, i);
  }
  state.ResumeTiming();

  int avoid_strip = 0;
  while (state.KeepRunning()) {
    for (int i = 0; i < state.range_y(); ++i) {
      int v;
      if (c.Get(i, &v)) {
        avoid_strip &= v;
      }
    }
  }
  assert(avoid_strip == 0);
  state.SetItemsProcessed(int64_t(state.iterations())*state.range_y());
}
BENCHMARK(BM_Get)->RangePair(1, 1<<10, 1, 1<<12);

int main(int argc, const char* argv[]) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  return 0;
}
