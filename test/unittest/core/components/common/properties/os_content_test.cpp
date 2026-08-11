/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "os_content_test.h"

#include <array>
#include <atomic>
#include <thread>

#include "core/components/common/properties/os_content.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
namespace {
const char* TEST_SCENARIO = "TEST_SCENARIO";
const char* TEST_ACTION_STR = "TEST_ACTION_STR";
const char* TEST_JSON = "TEST_JSON";
} // namespace

HWTEST_F(OsContentTest, OsContentTest_CallSendAction001, TestSize.Level1)
{
    auto result = OsContent::CallSendAction(TEST_SCENARIO, TEST_ACTION_STR, TEST_JSON);
    EXPECT_EQ(result, OsContent::CallSendAction(TEST_SCENARIO, TEST_ACTION_STR, TEST_JSON));
}

/**
 * @tc.name: OsContentTest_CallSendAction002
 * @tc.desc: Verify concurrent calls return the same cached result.
 * @tc.type: FUNC
 */
HWTEST_F(OsContentTest, OsContentTest_CallSendAction002, TestSize.Level1)
{
    constexpr int32_t threadCount = 8;
    std::array<bool, threadCount> results {};
    std::array<std::thread, threadCount> threads;
    std::atomic<int32_t> readyCount { 0 };
    std::atomic<bool> start { false };
    for (int32_t index = 0; index < threadCount; index++) {
        threads[index] = std::thread([&results, &readyCount, &start, index]() {
            readyCount.fetch_add(1, std::memory_order_relaxed);
            while (!start.load(std::memory_order_acquire)) {}
            results[index] = OsContent::CallSendAction(TEST_SCENARIO, TEST_ACTION_STR, TEST_JSON);
        });
    }
    while (readyCount.load(std::memory_order_acquire) != threadCount) {}
    start.store(true, std::memory_order_release);
    for (auto& thread : threads) {
        thread.join();
    }
    for (const auto result : results) {
        EXPECT_EQ(result, results.front());
    }
}
} // namespace OHOS::Ace
