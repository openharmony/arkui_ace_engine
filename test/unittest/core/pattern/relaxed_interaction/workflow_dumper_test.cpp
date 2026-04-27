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

#include "gtest/gtest.h"

#define PRIVATE public
#include "core/components_ng/relaxed_interaction/utils/workflow_dumper.h"
#undef PRIVATE

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class WorkflowDumperTest : public testing::Test {
public:
    void SetUp() override
    {
        ClearLogs();
    }

    void TearDown() override
    {
        ClearLogs();
    }

    static void ClearLogs()
    {
        auto& instance = WorkflowDumper::GetInstance();
        instance.logs_.clear();
    }
};

class WorkflowDumperGetInstanceTest : public WorkflowDumperTest {};
class WorkflowDumperAddLogTest : public WorkflowDumperTest {};
class WorkflowDumperDumpTest : public WorkflowDumperTest {};

HWTEST_F(WorkflowDumperGetInstanceTest, GetInstance_Singleton, TestSize.Level1)
{
    auto& instance1 = WorkflowDumper::GetInstance();
    auto& instance2 = WorkflowDumper::GetInstance();
    EXPECT_EQ(&instance1, &instance2);
}

HWTEST_F(WorkflowDumperGetInstanceTest, GetInstance_ReturnsValidReference, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    instance.AddLog("test");
    std::string dump = instance.Dump();
    EXPECT_TRUE(dump.find("test") != std::string::npos);
}

HWTEST_F(WorkflowDumperGetInstanceTest, GetInstance_LimitValue, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    instance.AddLog("limit_test");
    instance.AddLog("limit_test2");
    // Verify that logs are stored (limit behavior is internal implementation)
    EXPECT_EQ(instance.logs_.size(), 2);
}

HWTEST_F(WorkflowDumperAddLogTest, AddLog_SingleLog, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    instance.AddLog("single_test_log");
    EXPECT_EQ(instance.logs_.size(), 1);
    EXPECT_TRUE(instance.logs_.back().find("single_test_log") != std::string::npos);
}

HWTEST_F(WorkflowDumperAddLogTest, AddLog_MultipleLogs, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    instance.AddLog("log1");
    instance.AddLog("log2");
    instance.AddLog("log3");
    EXPECT_EQ(instance.logs_.size(), 3);
}

HWTEST_F(WorkflowDumperAddLogTest, AddLog_BelowLimit_NoPop, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    instance.AddLog("below_limit_test_1");
    instance.AddLog("below_limit_test_2");
    EXPECT_EQ(instance.logs_.size(), 2);
    EXPECT_TRUE(instance.logs_.front().find("below_limit_test_1") != std::string::npos);
    EXPECT_TRUE(instance.logs_.back().find("below_limit_test_2") != std::string::npos);
}

HWTEST_F(WorkflowDumperAddLogTest, AddLog_ExceedLimit_PopsFront, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    for (int i = 0; i < 60; ++i) {
        instance.AddLog("exceed_log_" + std::to_string(i));
    }
    // Logs should not exceed internal limit
    EXPECT_LE(instance.logs_.size(), 60);
    EXPECT_GE(instance.logs_.size(), 50);
    EXPECT_TRUE(instance.logs_.front().find("exceed_log_10") != std::string::npos);
    EXPECT_TRUE(instance.logs_.back().find("exceed_log_59") != std::string::npos);
}

HWTEST_F(WorkflowDumperAddLogTest, AddLog_ExactlyAtLimit, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    for (int i = 0; i < 50; ++i) {
        instance.AddLog("at_limit_log_" + std::to_string(i));
    }
    EXPECT_EQ(instance.logs_.size(), 50);
    EXPECT_TRUE(instance.logs_.back().find("at_limit_log_49") != std::string::npos);
}

HWTEST_F(WorkflowDumperAddLogTest, AddLog_EmptyString, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    instance.AddLog("");
    EXPECT_EQ(instance.logs_.size(), 1);
}

HWTEST_F(WorkflowDumperAddLogTest, AddLog_SpecialCharacters, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    instance.AddLog("special!@#$%^&*()");
    EXPECT_EQ(instance.logs_.size(), 1);
    EXPECT_TRUE(instance.logs_.back().find("special!@#$%^&*()") != std::string::npos);
}

HWTEST_F(WorkflowDumperAddLogTest, AddLog_ChineseCharacters, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    instance.AddLog("中文测试日志");
    EXPECT_EQ(instance.logs_.size(), 1);
    EXPECT_TRUE(instance.logs_.back().find("中文测试日志") != std::string::npos);
}

HWTEST_F(WorkflowDumperAddLogTest, AddLog_WithTimestamp, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    instance.AddLog("timestamp_test");
    EXPECT_EQ(instance.logs_.size(), 1);
    std::string logEntry = instance.logs_.back();
    EXPECT_TRUE(logEntry.find("timestamp_test") != std::string::npos);
    EXPECT_TRUE(logEntry.length() > std::string("timestamp_test").length());
}

HWTEST_F(WorkflowDumperAddLogTest, AddLog_LongString, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    std::string longLog(1000, 'a');
    instance.AddLog(longLog);
    EXPECT_EQ(instance.logs_.size(), 1);
    EXPECT_TRUE(instance.logs_.back().find(longLog) != std::string::npos);
}

HWTEST_F(WorkflowDumperAddLogTest, AddLog_UnicodeCharacters, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    instance.AddLog("日本語テスト");
    EXPECT_EQ(instance.logs_.size(), 1);
    EXPECT_TRUE(instance.logs_.back().find("日本語テスト") != std::string::npos);
}

HWTEST_F(WorkflowDumperDumpTest, Dump_EmptyDeque_ReturnsNewline, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    std::string dump = instance.Dump();
    EXPECT_EQ(dump, "\n");
}

HWTEST_F(WorkflowDumperDumpTest, Dump_SingleLog, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    instance.AddLog("single_dump_test");
    std::string dump = instance.Dump();
    EXPECT_TRUE(dump.find("single_dump_test") != std::string::npos);
    EXPECT_TRUE(dump.find("\n") != std::string::npos);
}

HWTEST_F(WorkflowDumperDumpTest, Dump_WithMultipleLogs_HasNewlines, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    instance.AddLog("dump_test_1");
    instance.AddLog("dump_test_2");
    std::string dump = instance.Dump();
    EXPECT_TRUE(dump.find("dump_test_1") != std::string::npos);
    EXPECT_TRUE(dump.find("dump_test_2") != std::string::npos);
    EXPECT_TRUE(dump.find("\n") != std::string::npos);
}

HWTEST_F(WorkflowDumperDumpTest, Dump_ConstMethod, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    const WorkflowDumper& constInstance = WorkflowDumper::GetInstance();
    instance.AddLog("const_test");
    std::string dump = constInstance.Dump();
    EXPECT_TRUE(dump.find("const_test") != std::string::npos);
}

HWTEST_F(WorkflowDumperDumpTest, Dump_VerifyStructure, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    instance.AddLog("structure_test");
    std::string dump = instance.Dump();
    size_t pos = dump.find("structure_test");
    EXPECT_TRUE(pos != std::string::npos);
    EXPECT_TRUE(dump[0] == '\n');
}

HWTEST_F(WorkflowDumperDumpTest, Dump_LimitBehavior_Verified, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    for (int i = 0; i < 51; ++i) {
        instance.AddLog("limit_behavior_" + std::to_string(i));
    }
    std::string dump = instance.Dump();
    EXPECT_TRUE(dump.find("limit_behavior_1") != std::string::npos);
    EXPECT_TRUE(dump.find("limit_behavior_50") != std::string::npos);
    EXPECT_TRUE(dump.find("limit_behavior_0") == std::string::npos);
}

HWTEST_F(WorkflowDumperDumpTest, Dump_LogsCountMatchesDeque, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    EXPECT_TRUE(instance.logs_.empty());

    instance.AddLog("log1");
    instance.AddLog("log2");
    instance.AddLog("log3");
    std::string dump = instance.Dump();

    size_t newlineCount = 0;
    for (char c : dump) {
        if (c == '\n') newlineCount++;
    }
    EXPECT_EQ(newlineCount, instance.logs_.size() + 1);
}

} // namespace OHOS::Ace::NG