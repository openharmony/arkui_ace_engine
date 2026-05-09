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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#define protected public


#include "base/log/dump_log.h"

#include "base/log/dump_log.h"
#include "core/accessibility/hidumper/accessibility_hidumper.h"

#include "core/components_ng/base/frame_node.h"


using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
} // namespace

class AccessibilityHidumperTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AccessibilityHidumperTest::SetUpTestCase()
{
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityHidumperTest::TearDownTestCase()
{
}

/**
 * @tc.name: AccessibilityDfxTest003
 * @tc.desc: DumpProcessInjectActionParameters
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest003, TestSize.Level1)
{
    std::vector<std::string> params = {"-inspector", "--inject-action", "999", "--NotifyChildAction", "5"};
    int64_t nodeId = 0;
    int32_t resultVal = 0;
    InjectActionType actionType{};

    bool ret = AccessibilityHidumper::DumpProcessInjectActionParameters(
        params, nodeId, resultVal, actionType);

    // suppose to parse inject-action normal
    EXPECT_TRUE(ret);
    EXPECT_EQ(nodeId, 999);
    EXPECT_EQ(resultVal, 5);
    EXPECT_EQ(actionType, InjectActionType::NOTIFY_CHILD_ACTION);
}

/**
 * @tc.name: AccessibilityDfxTest004
 * @tc.desc: DumpProcessInjectActionParameters
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest004, TestSize.Level1)
{
    std::vector<std::string> params = {"-inspector", "--NotifyChildAction"};
    int64_t nodeId = 0;
    int32_t resultVal = 0;
    InjectActionType actionType{};

    // suppose to parse inject-action fail
    bool ret = AccessibilityHidumper::DumpProcessInjectActionParameters(
        params, nodeId, resultVal, actionType);

    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AccessibilityDfxTest005
 * @tc.desc: DumpProcessInjectActionParameters
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest005, TestSize.Level1)
{
    std::vector<std::string> params = {};
    int64_t nodeId = 0;
    int32_t resultVal = 0;
    InjectActionType actionType{};

    // suppose to parse inject-action fail
    bool ret = AccessibilityHidumper::DumpProcessInjectActionParameters(
        params, nodeId, resultVal, actionType);

    EXPECT_FALSE(ret);
}


/**
 * @tc.name: AccessibilityDfxTest006
 * @tc.desc: DumpProcessInjectActionParameters
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest006, TestSize.Level1)
{
    std::vector<std::string> params = {"-inspector", "--inject-action"};
    int64_t nodeId = 0;
    int32_t resultVal = 0;
    InjectActionType actionType{};

    // suppose to parse inject-action fail
    bool ret = AccessibilityHidumper::DumpProcessInjectActionParameters(
        params, nodeId, resultVal, actionType);

    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DumpProcessExecuteActionParameters001
 * @tc.desc: Test DumpProcessExecuteActionParameters with valid params and no key-value pairs
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, DumpProcessExecuteActionParameters001, TestSize.Level1)
{
    std::vector<std::string> params = {"-inspector", "--execute-action", "100", "16"};
    ExecuteActionArgument argument;

    bool ret = AccessibilityHidumper::DumpProcessExecuteActionParameters(params, argument);

    EXPECT_TRUE(ret);
    EXPECT_EQ(argument.elementId, 100);
    EXPECT_EQ(argument.actionType, 16);
    EXPECT_TRUE(argument.actionArguments.empty());
}

/**
 * @tc.name: DumpProcessExecuteActionParameters002
 * @tc.desc: Test DumpProcessExecuteActionParameters with valid params and key-value pairs
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, DumpProcessExecuteActionParameters002, TestSize.Level1)
{
    std::vector<std::string> params =
        {"-inspector", "--execute-action", "200", "32", "key0", "value0", "key1", "value1"};
    ExecuteActionArgument argument;

    bool ret = AccessibilityHidumper::DumpProcessExecuteActionParameters(params, argument);

    EXPECT_TRUE(ret);
    EXPECT_EQ(argument.elementId, 200);
    EXPECT_EQ(argument.actionType, 32);
    EXPECT_EQ(argument.actionArguments.size(), 2u);
    EXPECT_EQ(argument.actionArguments["key0"], "value0");
    EXPECT_EQ(argument.actionArguments["key1"], "value1");
}

/**
 * @tc.name: DumpProcessExecuteActionParameters003
 * @tc.desc: Test DumpProcessExecuteActionParameters with missing actionType
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, DumpProcessExecuteActionParameters003, TestSize.Level1)
{
    std::vector<std::string> params = {"-inspector", "--execute-action", "100"};
    ExecuteActionArgument argument;

    bool ret = AccessibilityHidumper::DumpProcessExecuteActionParameters(params, argument);

    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DumpProcessExecuteActionParameters004
 * @tc.desc: Test DumpProcessExecuteActionParameters with only --execute-action
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, DumpProcessExecuteActionParameters004, TestSize.Level1)
{
    std::vector<std::string> params = {"-inspector", "--execute-action"};
    ExecuteActionArgument argument;

    bool ret = AccessibilityHidumper::DumpProcessExecuteActionParameters(params, argument);

    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DumpProcessExecuteActionParameters005
 * @tc.desc: Test DumpProcessExecuteActionParameters with no --execute-action flag
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, DumpProcessExecuteActionParameters005, TestSize.Level1)
{
    std::vector<std::string> params = {"-inspector", "100", "16"};
    ExecuteActionArgument argument;

    bool ret = AccessibilityHidumper::DumpProcessExecuteActionParameters(params, argument);

    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DumpProcessExecuteActionParameters006
 * @tc.desc: Test DumpProcessExecuteActionParameters with empty params
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, DumpProcessExecuteActionParameters006, TestSize.Level1)
{
    std::vector<std::string> params = {};
    ExecuteActionArgument argument;

    bool ret = AccessibilityHidumper::DumpProcessExecuteActionParameters(params, argument);

    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DumpProcessExecuteActionParameters007
 * @tc.desc: Test DumpProcessExecuteActionParameters with key but missing value
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, DumpProcessExecuteActionParameters007, TestSize.Level1)
{
    std::vector<std::string> params = {"-inspector", "--execute-action", "100", "16", "key0"};
    ExecuteActionArgument argument;

    bool ret = AccessibilityHidumper::DumpProcessExecuteActionParameters(params, argument);

    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DumpProcessExecuteActionParameters008
 * @tc.desc: Test DumpProcessExecuteActionParameters with single key-value pair
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, DumpProcessExecuteActionParameters008, TestSize.Level1)
{
    std::vector<std::string> params = {"-inspector", "--execute-action", "300", "64", "testKey", "testValue"};
    ExecuteActionArgument argument;

    bool ret = AccessibilityHidumper::DumpProcessExecuteActionParameters(params, argument);

    EXPECT_TRUE(ret);
    EXPECT_EQ(argument.elementId, 300);
    EXPECT_EQ(argument.actionType, 64);
    EXPECT_EQ(argument.actionArguments.size(), 1u);
    EXPECT_EQ(argument.actionArguments["testKey"], "testValue");
}

/**
 * @tc.name: AccessibilityDfxTest007
 * @tc.desc: DumpProcessCustomActionParameters with valid params and --list
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest007, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "100", "--list"};
    int64_t nodeId = 0;
    std::string actionName;
    bool listActions = false;

    bool ret = AccessibilityHidumper::DumpProcessCustomActionParameters(
        params, nodeId, actionName, listActions);

    EXPECT_TRUE(ret);
    EXPECT_EQ(nodeId, 100);
    EXPECT_TRUE(listActions);
    EXPECT_TRUE(actionName.empty());
}

/**
 * @tc.name: AccessibilityDfxTest008
 * @tc.desc: DumpProcessCustomActionParameters with empty params
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest008, TestSize.Level1)
{
    std::vector<std::string> params;
    int64_t nodeId = 0;
    std::string actionName;
    bool listActions = false;

    bool ret = AccessibilityHidumper::DumpProcessCustomActionParameters(
        params, nodeId, actionName, listActions);

    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AccessibilityDfxTest009
 * @tc.desc: DumpProcessCustomActionParameters without node id
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest009, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test"};
    int64_t nodeId = 0;
    std::string actionName;
    bool listActions = false;

    bool ret = AccessibilityHidumper::DumpProcessCustomActionParameters(
        params, nodeId, actionName, listActions);

    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AccessibilityDfxTest010
 * @tc.desc: DumpProcessCustomActionParameters without --custom-action-test flag
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest010, TestSize.Level1)
{
    std::vector<std::string> params = {"-inspector", "100", "--list"};
    int64_t nodeId = 0;
    std::string actionName;
    bool listActions = false;

    bool ret = AccessibilityHidumper::DumpProcessCustomActionParameters(
        params, nodeId, actionName, listActions);

    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AccessibilityDfxTest011
 * @tc.desc: DumpProcessCustomActionParameters with node id only (no --list, no action name)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest011, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "200"};
    int64_t nodeId = 0;
    std::string actionName;
    bool listActions = false;

    bool ret = AccessibilityHidumper::DumpProcessCustomActionParameters(
        params, nodeId, actionName, listActions);

    EXPECT_TRUE(ret);
    EXPECT_EQ(nodeId, 200);
    EXPECT_FALSE(listActions);
    EXPECT_TRUE(actionName.empty());
}

/**
 * @tc.name: AccessibilityDfxTest012
 * @tc.desc: DumpProcessCustomActionParameters with CustomActionTest inject action
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest012, TestSize.Level1)
{
    std::vector<std::string> params = {"--inject-action", "500", "--CustomActionTest", "3"};
    int64_t nodeId = 0;
    int32_t resultVal = 0;
    InjectActionType actionType{};

    bool ret = AccessibilityHidumper::DumpProcessInjectActionParameters(
        params, nodeId, resultVal, actionType);

    EXPECT_TRUE(ret);
    EXPECT_EQ(nodeId, 500);
    EXPECT_EQ(resultVal, 3);
    EXPECT_EQ(actionType, InjectActionType::CUSTOM_ACTION_TEST);
}

/**
 * @tc.name: AccessibilityDfxTest013
 * @tc.desc: DumpProcessCustomActionParameters with large node id
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest013, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "9999999999", "--list"};
    int64_t nodeId = 0;
    std::string actionName;
    bool listActions = false;

    bool ret = AccessibilityHidumper::DumpProcessCustomActionParameters(
        params, nodeId, actionName, listActions);

    EXPECT_TRUE(ret);
    EXPECT_EQ(nodeId, 9999999999L);
    EXPECT_TRUE(listActions);
}
} // namespace OHOS::Ace::NG