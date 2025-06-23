/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#ifndef ASSERT_CAPI_H
#define ASSERT_CAPI_H

#include <benchmark/benchmark.h>

template <typename T1, typename T2>
void AssertEqual(const T1 &t1, const T2 &t2, const char* printInfo, benchmark::State& state)
{
    if (t1 != t2) {
        state.SkipWithError(printInfo);
    }
}

template <typename T1, typename T2>
void AssertUnequal(const T1 &t1, const T2 &t2, const char* printInfo, benchmark::State& state)
{
    if (t1 == t2) {
        state.SkipWithError(printInfo);
    }
}

template <typename T>
void AssertFalse(const T &t, const char* printInfo, benchmark::State& state)
{
    if (t) {
        state.SkipWithError(printInfo);
    }
}

template <typename T>
void AssertTrue(const T &t, const char* printInfo, benchmark::State& state)
{
    if (!t) {
        state.SkipWithError(printInfo);
    }
}

template <typename T1, typename T2>
void AssertLessThan(const T1 &t1, const T2 &t2, const char* printInfo, benchmark::State& state)
{
    if (t1 >= t2) {
        state.SkipWithError(printInfo);
    }
}

template <typename T1, typename T2>
void AssertLessThanOrEqual(const T1 &t1, const T2 &t2, const char* printInfo, benchmark::State& state)
{
    if (t1 > t2) {
        state.SkipWithError(printInfo);
    }
}

template <typename T1, typename T2>
void AssertGreaterThan(const T1 &t1, const T2 &t2, const char* printInfo, benchmark::State& state)
{
    if (t1 <= t2) {
        state.SkipWithError(printInfo);
    }
}

template <typename T1, typename T2>
void AssertGreaterThanOrEqual(const T1 &t1, const T2 &t2, const char* printInfo, benchmark::State& state)
{
    if (t1 < t2) {
        state.SkipWithError(printInfo);
    }
}

void AssertStringEqual(const char* str1, const char* str2, const char* printInfo, benchmark::State& state)
{
    if (strcmp(str1, str2) != 0) {
        state.SkipWithError(printInfo);
    }
}
#endif