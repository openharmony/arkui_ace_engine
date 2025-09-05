/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _KOALA_PROFILER_
#define _KOALA_PROFILER_

#include <stdint.h>
#include <stdio.h>

#include <unordered_map>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

#include "interop-utils.h"

struct InteropProfilerRecord {
    int64_t time;
    int64_t count;
    InteropProfilerRecord(int64_t time, int64_t count) : time(time), count(count) {}
};

class InteropProfiler {
  private:
    std::unordered_map<std::string, InteropProfilerRecord> records;
    static InteropProfiler* _instance;
    InteropProfiler() {}

  public:
    static InteropProfiler* instance() {
        if (!_instance) _instance = new InteropProfiler();
        return _instance;
    }

    void record(const char* name, int64_t ns) {
        auto it = records.find(name);
        if (it == records.end()) {
            records.insert({name, InteropProfilerRecord(ns, 1)});
        } else {
            it->second.time += ns;
            it->second.count++;
        }
    }

    std::string report() {
        std::vector<std::pair<std::string, InteropProfilerRecord>> elems(records.begin(), records.end());
        std::sort(elems.begin(), elems.end(),
            [](const std::pair<std::string, InteropProfilerRecord>&a, const std::pair<std::string, InteropProfilerRecord>&b) {
                return b.second.time < a.second.time;
            });
        int64_t total = 0;
        std::for_each(elems.begin(), elems.end(), [&total](const std::pair<std::string, InteropProfilerRecord>&a) {
            total += a.second.time;
        });
        std::string result;
        std::for_each(elems.begin(), elems.end(), [total, &result](const std::pair<std::string, InteropProfilerRecord>&a) {
            auto ns = a.second.time;
            auto count = a.second.count;
            char buffer[1024];
            interop_snprintf(buffer, sizeof buffer, "for %s[%lld]: %.01f%% (%lld)\n", a.first.c_str(), (long long)count, (double)ns / total * 100.0, (long long)ns);
            result += buffer;
        });
        return result;
    }

    void reset() {
        records.clear();
    }
};


class InteropMethodCall {
  private:
    const char* name;
    std::chrono::steady_clock::time_point begin;
  public:
    InteropMethodCall(const char* name) : name(name) {
        begin = std::chrono::steady_clock::now();
    }
    ~InteropMethodCall() {
        auto end = std::chrono::steady_clock::now();
        int64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        InteropProfiler::instance()->record(name, ns);
    }
};

#endif // _KOALA_PROFILER_