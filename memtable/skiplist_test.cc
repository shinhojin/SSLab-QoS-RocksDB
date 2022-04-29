//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "memtable/skiplist.h"
#include <set>
#include "memory/arena.h"
#include "rocksdb/env.h"
#include "test_util/testharness.h"
#include "util/hash.h"
#include "util/random.h"

// Zipfian pattern generator from util directory - Signal.Jin
#include "util/zipf.h"
#include "util/latest-generator.h"

namespace ROCKSDB_NAMESPACE {

typedef uint64_t Key;

struct TestComparator {
  int operator()(const Key& a, const Key& b) const {
    if (a < b) {
      return -1;
    } else if (a > b) {
      return +1;
    } else {
      return 0;
    }
  }
};

class SkipTest : public testing::Test {};
/*
TEST_F(SkipTest, Empty) { // In here, Main step for Skiplist_test (Empty) - Signal.Jin
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);
  ASSERT_TRUE(!list.Contains(10));

  SkipList<Key, TestComparator>::Iterator iter(&list);
  ASSERT_TRUE(!iter.Valid());
  iter.SeekToFirst();
  ASSERT_TRUE(!iter.Valid());
  iter.Seek(100);
  ASSERT_TRUE(!iter.Valid());
  iter.SeekForPrev(100);
  ASSERT_TRUE(!iter.Valid());
  iter.SeekToLast();
  ASSERT_TRUE(!iter.Valid());
}
*/
/*
TEST_F(SkipTest, HJAllWork) { // Skiplist test for All Patterns - Signal.Jin
  const int N = 5000; // Write Count - Signal.Jin
  const int R = 2000; // Read Count - Signal.Jin
  Random rnd(1000);
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);
  init_zipf_generator(0, N);

  //FILE *fp_sk_test;
  
  //fp_sk_test = fopen("Xseq_test_skiplist.txt", "at");

  //struct timespec s_time, e_time;
  //double r_time, avg_time = 0;

  for (int i = 1; i < N; i++) {
    Key key = i;
    if (keys.insert(key).second) {
      list.Insert(key);
    }
  }

  for (int i = 1; i < R; i++) {
    //clock_gettime(CLOCK_MONOTONIC, &s_time);
    if (list.Contains(i)) { // Maybe estimate time in here - Signal.Jin
      ASSERT_EQ(keys.count(i), 1U);
    } else {
      ASSERT_EQ(keys.count(i), 0U);
    }
    //clock_gettime(CLOCK_MONOTONIC, &e_time);
    //r_time = (e_time.tv_sec - s_time.tv_sec) + (e_time.tv_nsec - s_time.tv_nsec)*0.001;
    //avg_time += r_time;
  }
  //fprintf(stdout, "Sequential True = %.2lf\n", avg_time/R);
  //avg_time = 0;

  for (int i = N + 1; i < N + R + 1; i++) { 
    //clock_gettime(CLOCK_MONOTONIC, &s_time);
    if (list.Contains(i)) { // Maybe estimate time in here - Signal.Jin
      ASSERT_EQ(keys.count(i), 1U);
    } else {
      ASSERT_EQ(keys.count(i), 0U);
    }
    //clock_gettime(CLOCK_MONOTONIC, &e_time);
    //r_time = (e_time.tv_sec - s_time.tv_sec) + (e_time.tv_nsec - s_time.tv_nsec)*0.001;
    //avg_time += r_time;
  }
  //fprintf(stdout, "Sequential False = %.2lf\n", avg_time/R);
  //avg_time = 0;

  for (int i = 0; i < R; i++) { 
    Key Ukey = rnd.Next() % N; // Generate Random Key - Signal.Jin
    //clock_gettime(CLOCK_MONOTONIC, &s_time);
    if (list.Contains(Ukey)) { // Maybe estimate time in here - Signal.Jin
      ASSERT_EQ(keys.count(Ukey), 1U);
    } else {
      ASSERT_EQ(keys.count(Ukey), 0U);
    }
    //clock_gettime(CLOCK_MONOTONIC, &e_time);
    //r_time = (e_time.tv_sec - s_time.tv_sec) + (e_time.tv_nsec - s_time.tv_nsec)*0.001;
    //avg_time += r_time;
  }
  //fprintf(stdout, "Uniform Random = %.2lf\n", avg_time/R); // Signal.Jin
  //avg_time = 0;

  for (int i = 0; i < R; i++) { 
    Key Zkey = nextValue() % N; // Zipfian Key Pattern - Signal.Jin
    //clock_gettime(CLOCK_MONOTONIC, &s_time);
    if (list.Contains(Zkey)) { // Maybe estimate time in here - Signal.Jin
      ASSERT_EQ(keys.count(Zkey), 1U);
    } else {
      ASSERT_EQ(keys.count(Zkey), 0U);
    }
    //clock_gettime(CLOCK_MONOTONIC, &e_time);
    //r_time = (e_time.tv_sec - s_time.tv_sec) + (e_time.tv_nsec - s_time.tv_nsec)*0.001;
    //avg_time += r_time;
  }
  //fprintf(stdout, "Zipfian Random = %.2lf\n", avg_time/R); // Signal.Jin 

}
*/

TEST_F(SkipTest, SeqInsertAndLookupX) { // Skiplist test for Sequential Pattern (Find nothing) - Signal.Jin
  const int N = 50000; // Write Count - Signal.Jin
  //const int R = 1000000; // Read Count - Signal.Jin
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  //FILE *fp_sk_test;
  //float *lat = (float *)malloc(sizeof(float)*R);
  //int j = 0;

  //fp_sk_test = fopen("Xseq_test_skiplist.txt", "at");
  //struct timespec s_time, e_time;
  //double r_time;

  for (int i = 1; i < N; i++) {
    Key key = i;
    if (keys.insert(key).second) {
      list.Insert(key);
    }
  }
/*
  for (int i = N + 1; i < N + R + 1; i++) { 
    clock_gettime(CLOCK_MONOTONIC, &s_time);
    if (list.Contains(i)) { // Maybe estimate time in here - Signal.Jin
      ASSERT_EQ(keys.count(i), 1U);
    } else {
      ASSERT_EQ(keys.count(i), 0U);
    }
    clock_gettime(CLOCK_MONOTONIC, &e_time);
    r_time = (e_time.tv_sec - s_time.tv_sec) + (e_time.tv_nsec - s_time.tv_nsec)*0.001;
    lat[j] = r_time;
    j++;
    //fprintf(fp_sk_test, "%.2f\n", r_time); // Signal.Jin
  }

  for (int i = 0; i < R; i++) {
    fprintf(fp_sk_test, "%.2f\n", lat[i]);
  }
  fclose(fp_sk_test);
  free(lat);*/
}

/*
TEST_F(SkipTest, SeqInsertAndLookupO) { // Skiplist test for Sequential Pattern (Find all keys) - Signal.Jin
  const int N = 50000; // Write Count - Signal.Jin
  const int R = 1000000; // Read Count - Signal.Jin
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  FILE *fp_sk_test;
  float *lat = (float *)malloc(sizeof(float)*R);
  
  fp_sk_test = fopen("Oseq_test_skiplist.txt", "at");

  struct timespec s_time, e_time;
  double r_time;

  for (int i = 1; i < N; i++) {
    Key key = i;
    if (keys.insert(key).second) {
      list.Insert(key);
    }
  }

  // Insert key sequential pattern in skiplist
  //int start_p = rand() % (N-R);
  int j = 0; int count = 0;
  for (int i = 0;; i++) {
    count++;
    if (count % N == 0) {
      i = 0;
      if (count == R) {
        break;
      }
    }
    clock_gettime(CLOCK_MONOTONIC, &s_time);
    if (list.Contains(i)) { // Maybe estimate time in here - Signal.Jin
      ASSERT_EQ(keys.count(i), 1U);
    } 
    else {
      ASSERT_EQ(keys.count(i), 0U);
    }
    clock_gettime(CLOCK_MONOTONIC, &e_time);
    r_time = (e_time.tv_sec - s_time.tv_sec) + (e_time.tv_nsec - s_time.tv_nsec)*0.001;
    lat[j] = r_time;
    j++;
    //fprintf(fp_sk_test, "%.2f\n", r_time); // Signal.Jin  
  }
  
  for (int i = 0; i < R; i++) {
    fprintf(fp_sk_test, "%.2f\n", lat[i]);
  }
  fclose(fp_sk_test);
  free(lat);
}
*/
/*
TEST_F(SkipTest, UniRandInsertAndLookup) { // Skiplist test for Random Pattern - Signal.Jin
  const int N = 50000; // Write Count - Signal.Jin
  const int R = 1000000; // Read Count - Signal.Jin
  Random rnd(1000);
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distr(0, N);

  FILE *fp_sk_test;
  
  float *lat = (float *)malloc(sizeof(float)*R);
  uint64_t *rnd_val = (uint64_t *)malloc(sizeof(uint64_t)*R);
  
  fp_sk_test = fopen("uni_rand_test_skiplist.txt", "at");

  struct timespec s_time, e_time;
  double r_time;

  for (int i = 1; i < N; i++) {
    Key key = i;
    if (keys.insert(key).second) {
      list.Insert(key);
    }
  }

  for(int i = 0; i < R; i++) {
    //rnd_val[i] = rnd.Next() % N;
    rnd_val[i] = distr(gen);
  } // Generate Random Key - Signal.Jin
  int j = 0;
  for (int i = 0; i < R; i++) { 
    Key Gkey = rnd_val[i];
    clock_gettime(CLOCK_MONOTONIC, &s_time);
    if (list.Contains(Gkey)) { // Maybe estimate time in here - Signal.Jin
      ASSERT_EQ(keys.count(Gkey), 1U);
    } else {
      ASSERT_EQ(keys.count(Gkey), 0U);
    }
    clock_gettime(CLOCK_MONOTONIC, &e_time);
    r_time = (e_time.tv_sec - s_time.tv_sec) + (e_time.tv_nsec - s_time.tv_nsec)*0.001;
    lat[j] = r_time;
    j++;
    //fprintf(fp_sk_test, "%.2f\n", r_time); // Signal.Jin 
  }

  for(int i = 0; i < R; i++) {
    fprintf(fp_sk_test, "%.2f\n", lat[i]);
  }
  fclose(fp_sk_test);
  free(lat);
  free(rnd_val);
}
*/
/*
TEST_F(SkipTest, ZipRandInsertAndLookup) { // Skiplist test for Random Pattern - Signal.Jin
  const int N = 50000; // Write Count - Signal.Jin
  const int R = 1000000; // Read Count - Signal.Jin
  Random rnd(1000);
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  // Init Zipfian Generator - Signal.Jin
  //init_latestgen(N);
  init_zipf_generator(0, N);

  FILE *fp_sk_test;
  
  float *lat = (float *)malloc(sizeof(float)*R);
  uint64_t *zipf_val = (uint64_t *)malloc(sizeof(uint64_t)*R);
  
  fp_sk_test = fopen("zipf_rand_test_skiplist.txt", "at");

  struct timespec s_time, e_time;
  double r_time;

  for (int i = 1; i < N; i++) {
    Key key = i;
    if (keys.insert(key).second) {
      list.Insert(key);
    }
  }

  for(int i = 0; i < R; i++) {
    zipf_val[i] = nextValue() % N;
  } // Zipfian Key Pattern - Signal.Jin
  int j = 0;
  for (int i = 0; i < R; i++) { 
    Key Zkey = zipf_val[i]; 
    clock_gettime(CLOCK_MONOTONIC, &s_time);
    if (list.Contains(Zkey)) { // Maybe estimate time in here - Signal.Jin
      ASSERT_EQ(keys.count(Zkey), 1U);
    } else {
      ASSERT_EQ(keys.count(Zkey), 0U);
    }
    clock_gettime(CLOCK_MONOTONIC, &e_time);
    r_time = (e_time.tv_sec - s_time.tv_sec) + (e_time.tv_nsec - s_time.tv_nsec)*0.001;
    lat[j] = r_time;
    j++;
    //fprintf(fp_sk_test, "%.2f\n", r_time); // Signal.Jin 
  }

  for(int i = 0; i < R; i++) {
    fprintf(fp_sk_test, "%.2f\n", lat[i]);
  }
  fclose(fp_sk_test);
  free(zipf_val);
  free(lat);
}
*/
}  // namespace ROCKSDB_NAMESPACE

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
