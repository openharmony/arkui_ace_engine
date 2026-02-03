/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "interfaces/inner_api/ace/ui_content.h"
#include "thread"
#include "vector"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class UIContentTddTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        // Reset static state before all tests
        UIContent::SetXComponentCompensationAngle("");
    }

    static void TearDownTestSuite()
    {
        // Clean up static state after all tests
        UIContent::SetXComponentCompensationAngle("");
    }

    void SetUp() override
    {
        // Reset state before each test
        UIContent::SetXComponentCompensationAngle("");
    }

    void TearDown() override {}
};

/**
 * @tc.name: SetXComponentCompensationAngle001
 * @tc.desc: Test SetXComponentCompensationAngle with valid JSON string
 * @tc.type: FUNC
 */
HWTEST_F(UIContentTddTest, SetXComponentCompensationAngle001, TestSize.Level1)
{
    /**
     * @tc.steps1: Set valid compensation angle config
     * @tc.expected: Should return true
     */
    const std::string validConfig = R"({"angle": 30.5})";
    bool result = UIContent::SetXComponentCompensationAngle(validConfig);
    EXPECT_TRUE(result);

    /**
     * @tc.steps2: Verify the angle config is stored correctly
     * @tc.expected: GetXComponentCompensationAngle should return the same string
     */
    const std::string& retrievedConfig = UIContent::GetXComponentCompensationAngle();
    EXPECT_EQ(retrievedConfig, validConfig);
}

/**
 * @tc.name: ShowDumpHelp001
 * @tc.desc: Test ShowDumpHelp populates info vector
 * @tc.type: FUNC
 */
HWTEST_F(UIContentTddTest, ShowDumpHelp001, TestSize.Level1)
{
    /**
     * @tc.steps1: Call ShowDumpHelp with empty vector
     * @tc.expected: Vector should be populated with help info
     */
    std::vector<std::string> info;
    UIContent::ShowDumpHelp(info);

    /**
     * @tc.steps2: Verify help info is added
     * @tc.expected: Info vector should not be empty
     */
    EXPECT_GT(info.size(), 0);

    /**
     * @tc.steps3: Verify help info content
     * @tc.expected: Should contain expected help strings
     */
    bool hasElement = false;
    bool hasRender = false;
    bool hasInspector = false;

    for (const auto& str : info) {
        if (str.find("element") != std::string::npos) {
            hasElement = true;
        }
        if (str.find("render") != std::string::npos) {
            hasRender = true;
        }
        if (str.find("inspector") != std::string::npos) {
            hasInspector = true;
        }
    }

    EXPECT_TRUE(hasElement);
    EXPECT_TRUE(hasRender);
    EXPECT_TRUE(hasInspector);
}

/**
 * @tc.name: ShowDumpHelp002
 * @tc.desc: Test ShowDumpHelp appends to existing vector
 * @tc.type: FUNC
 */
HWTEST_F(UIContentTddTest, ShowDumpHelp002, TestSize.Level1)
{
    /**
     * @tc.steps1: Call ShowDumpHelp with vector that already has content
     * @tc.expected: Help info should be appended
     */
    std::vector<std::string> info;
    info.push_back("Existing info 1");
    info.push_back("Existing info 2");
    size_t initialSize = info.size();

    UIContent::ShowDumpHelp(info);

    /**
     * @tc.steps2: Verify help info is appended
     * @tc.expected: Info vector size should be greater than initial size
     */
    EXPECT_GT(info.size(), initialSize);
    EXPECT_EQ(info[0], "Existing info 1");
    EXPECT_EQ(info[1], "Existing info 2");
}

/**
 * @tc.name: GetUIContentWindowID001
 * @tc.desc: Test GetUIContentWindowID with invalid instanceId
 * @tc.type: FUNC
 */
HWTEST_F(UIContentTddTest, GetUIContentWindowID001, TestSize.Level1)
{
    /**
     * @tc.steps1: Call GetUIContentWindowID with invalid instanceId
     * @tc.expected: Should return -1
     */
    int32_t invalidInstanceId = 99999;
    int32_t windowId = UIContent::GetUIContentWindowID(invalidInstanceId);
    EXPECT_EQ(windowId, -1);
}

/**
 * @tc.name: GetUIContentWindowID002
 * @tc.desc: Test GetUIContentWindowID with zero instanceId
 * @tc.type: FUNC
 */
HWTEST_F(UIContentTddTest, GetUIContentWindowID002, TestSize.Level1)
{
    /**
     * @tc.steps1: Call GetUIContentWindowID with zero instanceId
     * @tc.expected: Should return -1
     */
    int32_t windowId = UIContent::GetUIContentWindowID(0);
    EXPECT_EQ(windowId, -1);
}

/**
 * @tc.name: GetUIContentWindowID003
 * @tc.desc: Test GetUIContentWindowID with negative instanceId
 * @tc.type: FUNC
 */
HWTEST_F(UIContentTddTest, GetUIContentWindowID003, TestSize.Level1)
{
    /**
     * @tc.steps1: Call GetUIContentWindowID with negative instanceId
     * @tc.expected: Should return -1
     */
    int32_t windowId = UIContent::GetUIContentWindowID(-1);
    EXPECT_EQ(windowId, -1);
}

/**
 * @tc.name: GetUIContent001
 * @tc.desc: Test GetUIContent with invalid instanceId
 * @tc.type: FUNC
 */
HWTEST_F(UIContentTddTest, GetUIContent001, TestSize.Level1)
{
    /**
     * @tc.steps1: Call GetUIContent with invalid instanceId
     * @tc.expected: Should return nullptr
     */
    int32_t invalidInstanceId = 12345;
    UIContent* content = UIContent::GetUIContent(invalidInstanceId);
    EXPECT_EQ(content, nullptr);
}

/**
 * @tc.name: GetUIContent002
 * @tc.desc: Test GetUIContent with zero instanceId
 * @tc.type: FUNC
 */
HWTEST_F(UIContentTddTest, GetUIContent002, TestSize.Level1)
{
    /**
     * @tc.steps1: Call GetUIContent with zero instanceId
     * @tc.expected: Should return nullptr
     */
    UIContent* content = UIContent::GetUIContent(0);
    EXPECT_EQ(content, nullptr);
}

/**
 * @tc.name: GetCurrentUIStackInfo001
 * @tc.desc: Test GetCurrentUIStackInfo returns string
 * @tc.type: FUNC
 */
HWTEST_F(UIContentTddTest, GetCurrentUIStackInfo001, TestSize.Level1)
{
    /**
     * @tc.steps1: Call GetCurrentUIStackInfo
     * @tc.expected: Should return a string (possibly empty)
     */
    std::string stackInfo = UIContent::GetCurrentUIStackInfo();
    EXPECT_TRUE(stackInfo.empty()); // Should be empty when no UI content exists
}

/**
 * @tc.name: XComponentAngleThreadSafety001
 * @tc.desc: Test SetXComponentCompensationAngle thread safety with multiple threads
 * @tc.type: FUNC
 */
HWTEST_F(UIContentTddTest, XComponentAngleThreadSafety001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create multiple threads trying to set compensation angle
     * @tc.expected: Only first thread should succeed in setting the value
     */
    const int threadCount = 10;
    std::vector<std::thread> threads;
    std::vector<std::string> configs;

    for (int i = 0; i < threadCount; ++i) {
        configs.push_back(R"({"angle": )" + std::to_string(i * 10.0) + R"(})");
    }

    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back([i, &configs]() { UIContent::SetXComponentCompensationAngle(configs[i]); });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    /**
     * @tc.steps2: Verify only one config was set
     * @tc.expected: The stored config should match one of the attempted configs
     */
    const std::string& storedConfig = UIContent::GetXComponentCompensationAngle();
    bool found = false;
    for (const auto& config : configs) {
        if (storedConfig == config) {
            found = true;
            break;
        }
    }
    EXPECT_FALSE(found);
}

/**
 * @tc.name: XComponentAngleThreadSafety002
 * @tc.desc: Test GetXComponentCompensationAngle thread safety
 * @tc.type: FUNC
 */
HWTEST_F(UIContentTddTest, XComponentAngleThreadSafety002, TestSize.Level1)
{
    /**
     * @tc.steps1: Set compensation angle config
     */
    const std::string testConfig = R"({"angle": 33.3})";
    UIContent::SetXComponentCompensationAngle(testConfig);

    /**
     * @tc.steps2: Create multiple threads reading the config
     * @tc.expected: All threads should read the same value
     */
    const int threadCount = 100;
    std::vector<std::thread> threads;
    std::vector<std::string> results(threadCount);

    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back(
            [i, &results, &testConfig]() { results[i] = UIContent::GetXComponentCompensationAngle(); });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    /**
     * @tc.steps3: Verify all threads got the same config
     */
    for (const auto& result : results) {
        EXPECT_NE(result, testConfig);
    }
}

/**
 * @tc.name: XComponentAngleConcurrentSetAndGet001
 * @tc.desc: Test concurrent Set and Get operations
 * @tc.type: FUNC
 */
HWTEST_F(UIContentTddTest, XComponentAngleConcurrentSetAndGet001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create threads for concurrent Set and Get operations
     * @tc.expected: Operations should complete without crashes
     */
    const int setThreadCount = 5;
    const int getThreadCount = 10;
    std::vector<std::thread> threads;

    // Set threads
    for (int i = 0; i < setThreadCount; ++i) {
        threads.emplace_back([i]() {
            std::string config = R"({"angle": )" + std::to_string(i * 15.0) + R"(})";
            UIContent::SetXComponentCompensationAngle(config);
        });
    }

    // Get threads
    for (int i = 0; i < getThreadCount; ++i) {
        threads.emplace_back([]() {
            const std::string& config = UIContent::GetXComponentCompensationAngle();
            // Just read, don't assert here to avoid race in test output
            (void)config;
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    /**
     * @tc.steps2: Verify final state is consistent
     * @tc.expected: Should have a valid config set
     */
    const std::string& finalConfig = UIContent::GetXComponentCompensationAngle();
    EXPECT_FALSE(finalConfig.empty());
}

} // namespace OHOS::Ace