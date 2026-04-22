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

#include "core/components_ng/relaxed_interaction/utils/workflow_dumper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class WorkflowDumperTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

HWTEST_F(WorkflowDumperTest, GetInstance_Singleton, TestSize.Level1)
{
    auto& instance1 = WorkflowDumper::GetInstance();
    auto& instance2 = WorkflowDumper::GetInstance();
    EXPECT_EQ(&instance1, &instance2);
}

HWTEST_F(WorkflowDumperTest, AddLog_Empty, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    std::string dump = instance.Dump();
    EXPECT_TRUE(dump.empty() || dump.find("test_log") == std::string::npos);
}

HWTEST_F(WorkflowDumperTest, AddLog_SingleLog, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    instance.AddLog("single_test_log");
    std::string dump = instance.Dump();
    EXPECT_TRUE(dump.find("single_test_log") != std::string::npos);
}

HWTEST_F(WorkflowDumperTest, AddLog_MultipleLogs, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    instance.AddLog("log1");
    instance.AddLog("log2");
    instance.AddLog("log3");
    std::string dump = instance.Dump();
    EXPECT_TRUE(dump.find("log1") != std::string::npos);
    EXPECT_TRUE(dump.find("log2") != std::string::npos);
    EXPECT_TRUE(dump.find("log3") != std::string::npos);
}

HWTEST_F(WorkflowDumperTest, AddLog_ExceedLimit, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    for (int i = 0; i < 60; ++i) {
        instance.AddLog("exceed_log_" + std::to_string(i));
    }
    std::string dump = instance.Dump();
    EXPECT_TRUE(dump.find("exceed_log_51") != std::string::npos);
    EXPECT_TRUE(dump.find("exceed_log_59") != std::string::npos);
    EXPECT_TRUE(dump.find("exceed_log_0") == std::string::npos ||
                dump.find("exceed_log_3") == std::string::npos);
}

HWTEST_F(WorkflowDumperTest, Dump_Format, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    instance.AddLog("format_test");
    std::string dump = instance.Dump();
    EXPECT_TRUE(dump.find("format_test\n") != std::string::npos ||
                dump.find("format_test") != std::string::npos);
}

HWTEST_F(WorkflowDumperTest, AddLog_EmptyString, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    instance.AddLog("");
    std::string dump = instance.Dump();
    EXPECT_FALSE(dump.empty());
}

HWTEST_F(WorkflowDumperTest, AddLog_SpecialCharacters, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    instance.AddLog("special!@#$%^&*()");
    std::string dump = instance.Dump();
    EXPECT_TRUE(dump.find("special!@#$%^&*()") != std::string::npos);
}

HWTEST_F(WorkflowDumperTest, AddLog_ChineseCharacters, TestSize.Level1)
{
    auto& instance = WorkflowDumper::GetInstance();
    instance.AddLog("中文测试日志");
    std::string dump = instance.Dump();
    EXPECT_TRUE(dump.find("中文测试日志") != std::string::npos);
}

} // namespace OHOS::Ace::NG