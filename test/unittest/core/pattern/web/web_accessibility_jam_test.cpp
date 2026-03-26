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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#undef protected
#undef private

#include "adapter/ohos/osal/js_accessibility_manager.h"
#include "base/log/dump_log.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/accessibility/accessibility_manager.h"

using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
using Framework::WEB_ACC_INVALID;
using Framework::WEB_EXE_ACTION;
using Framework::WEB_GET_ACC;
using Framework::WEB_HOVER;
using Framework::WEB_NEXT;
using Framework::WEB_NODE;
using Framework::WEB_OFF_ACC;
using Framework::WEB_ON_ACC;
using Framework::WEB_PRE;
using Framework::WEB_SEND_EVENT;
using Framework::WEB_TREE;

namespace {
constexpr int64_t TEST_ELEMENT_ID_NEGATIVE = -1;
constexpr int64_t TEST_ELEMENT_ID_POSITIVE = 100;
constexpr int64_t TEST_ELEMENT_ID_LARGE = 0x100000000LL;
constexpr int32_t TEST_WINDOW_ID = 1;
constexpr int32_t TEST_INVALID_WINDOW_ID = 999;
const std::string WEB_SRC_TEST = "web_test";
} // namespace

class WebAccessibilityJamTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static RefPtr<WebPattern> CreateWebPattern();
    static RefPtr<WebPattern> webPattern_;
};

RefPtr<WebPattern> WebAccessibilityJamTest::webPattern_ = nullptr;

RefPtr<WebPattern> WebAccessibilityJamTest::CreateWebPattern()
{
    auto controller = AceType::MakeRefPtr<WebController>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, [&]() { return AceType::MakeRefPtr<WebPattern>(WEB_SRC_TEST, controller); });
    stack->Push(frameNode);
    return frameNode->GetPattern<WebPattern>();
}

void WebAccessibilityJamTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
    webPattern_ = CreateWebPattern();
}

void WebAccessibilityJamTest::TearDownTestCase()
{
    webPattern_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

// ==================== ConvertToSplitElementId ====================

/**
 * @tc.name: ConvertToSplitElementId001
 * @tc.desc: Test elementId <= 0 branch - returns elementId directly
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ConvertToSplitElementId001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    EXPECT_EQ(manager->ConvertToSplitElementId(TEST_ELEMENT_ID_NEGATIVE), TEST_ELEMENT_ID_NEGATIVE);
    EXPECT_EQ(manager->ConvertToSplitElementId(0), 0);
}

/**
 * @tc.name: ConvertToSplitElementId002
 * @tc.desc: Test elementId within WEB_MAX_ELEMENT_ID range - returns same value
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ConvertToSplitElementId002, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    EXPECT_EQ(manager->ConvertToSplitElementId(TEST_ELEMENT_ID_POSITIVE), TEST_ELEMENT_ID_POSITIVE);
}

// ==================== DumpElementInfosIfNeed ====================

/**
 * @tc.name: DumpElementInfosIfNeed001
 * @tc.desc: Test default case (invalidFun) - direction=-1, mode=-1, returns true
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, DumpElementInfosIfNeed001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    DumpInfoArgument argument;
    argument.webAccFun = "invalidFun";
    std::list<AccessibilityElementInfo> infos;
    EXPECT_TRUE(manager->DumpElementInfosIfNeed(argument, infos, nullptr, TEST_WINDOW_ID));
    EXPECT_TRUE(infos.empty());
}

/**
 * @tc.name: DumpElementInfosIfNeed002
 * @tc.desc: Test tree/node/pre/next with null pipeline - returns false
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, DumpElementInfosIfNeed002, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    DumpInfoArgument argument;
    argument.webAccId = TEST_ELEMENT_ID_POSITIVE;
    std::list<AccessibilityElementInfo> infos;

    argument.webAccFun = "tree";
    EXPECT_FALSE(manager->DumpElementInfosIfNeed(argument, infos, nullptr, TEST_INVALID_WINDOW_ID));
    argument.webAccFun = "node";
    EXPECT_FALSE(manager->DumpElementInfosIfNeed(argument, infos, nullptr, TEST_INVALID_WINDOW_ID));
    argument.webAccFun = "pre";
    EXPECT_FALSE(manager->DumpElementInfosIfNeed(argument, infos, nullptr, TEST_INVALID_WINDOW_ID));
    argument.webAccFun = "next";
    EXPECT_FALSE(manager->DumpElementInfosIfNeed(argument, infos, nullptr, TEST_INVALID_WINDOW_ID));
}

// ==================== ExecuteWebDump ====================

/**
 * @tc.name: ExecuteWebDump001
 * @tc.desc: Test null webPattern - CHECK_NULL_VOID early return
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebDump001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    DumpInfoArgument argument;
    argument.webAccFun = "getAcc";
    std::list<AccessibilityElementInfo> infos;
    manager->ExecuteWebDump(argument, infos, nullptr);
    SUCCEED();
}

/**
 * @tc.name: ExecuteWebDump002
 * @tc.desc: Test WEB_GET_ACC/WEB_ON_ACC/WEB_OFF_ACC branches with valid webPattern
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebDump002, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(webPattern_, nullptr);
    DumpInfoArgument argument;
    std::list<AccessibilityElementInfo> infos;

    argument.webAccFun = "getAcc";
    manager->ExecuteWebDump(argument, infos, webPattern_);
    argument.webAccFun = "onAcc";
    manager->ExecuteWebDump(argument, infos, webPattern_);
    argument.webAccFun = "offAcc";
    manager->ExecuteWebDump(argument, infos, webPattern_);
    SUCCEED();
}

/**
 * @tc.name: ExecuteWebDump003
 * @tc.desc: Test WEB_TREE/WEB_NODE/WEB_PRE/WEB_NEXT with empty infos
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebDump003, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(webPattern_, nullptr);
    DumpInfoArgument argument;
    std::list<AccessibilityElementInfo> infos;

    argument.webAccFun = "tree";
    manager->ExecuteWebDump(argument, infos, webPattern_);
    argument.webAccFun = "node";
    manager->ExecuteWebDump(argument, infos, webPattern_);
    argument.webAccFun = "pre";
    manager->ExecuteWebDump(argument, infos, webPattern_);
    argument.webAccFun = "next";
    manager->ExecuteWebDump(argument, infos, webPattern_);
    SUCCEED();
}

/**
 * @tc.name: ExecuteWebDump004
 * @tc.desc: Test WEB_TREE/WEB_NODE/WEB_PRE/WEB_NEXT with non-empty infos
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebDump004, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(webPattern_, nullptr);
    DumpInfoArgument argument;
    std::list<AccessibilityElementInfo> infos;
    infos.push_back(AccessibilityElementInfo());

    argument.webAccFun = "tree";
    manager->ExecuteWebDump(argument, infos, webPattern_);
    argument.webAccFun = "node";
    manager->ExecuteWebDump(argument, infos, webPattern_);
    SUCCEED();
}

/**
 * @tc.name: ExecuteWebDump005
 * @tc.desc: Test WEB_EXE_ACTION/WEB_SEND_EVENT/WEB_HOVER branches
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebDump005, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(webPattern_, nullptr);
    DumpInfoArgument argument;
    std::list<AccessibilityElementInfo> infos;

    argument.webAccFun = "exeAction";
    argument.action = 16;
    manager->ExecuteWebDump(argument, infos, webPattern_);

    argument.webAccFun = "sendEvent";
    argument.eventId = 1;
    manager->ExecuteWebDump(argument, infos, webPattern_);

    argument.webAccFun = "hover";
    argument.pointX = 100;
    argument.pointY = 200;
    manager->ExecuteWebDump(argument, infos, webPattern_);
    SUCCEED();
}

/**
 * @tc.name: ExecuteWebDump006
 * @tc.desc: Test default case - invalid webAccFun
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebDump006, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    DumpInfoArgument argument;
    argument.webAccFun = "invalidFun";
    std::list<AccessibilityElementInfo> infos;
    manager->ExecuteWebDump(argument, infos, nullptr);
    SUCCEED();
}

// ==================== ChooseWebDumpEvent ====================

/**
 * @tc.name: ChooseWebDumpEvent001
 * @tc.desc: Test callback not found - webPattern null, early return
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ChooseWebDumpEvent001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    DumpInfoArgument argument;
    argument.nodeId = TEST_ELEMENT_ID_POSITIVE;
    manager->ChooseWebDumpEvent(argument, TEST_WINDOW_ID);
    SUCCEED();
}

/**
 * @tc.name: ChooseWebDumpEvent002
 * @tc.desc: Test with negative/large nodeId
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ChooseWebDumpEvent002, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    DumpInfoArgument argument;
    argument.nodeId = TEST_ELEMENT_ID_NEGATIVE;
    manager->ChooseWebDumpEvent(argument, TEST_WINDOW_ID);
    argument.nodeId = TEST_ELEMENT_ID_LARGE;
    manager->ChooseWebDumpEvent(argument, TEST_WINDOW_ID);
    SUCCEED();
}

// ==================== DumpWebInfoParams ====================

/**
 * @tc.name: DumpWebInfoParams001
 * @tc.desc: Test valid params with -webAccId and -webAccFun
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, DumpWebInfoParams001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    std::vector<std::string> params = { "dump", "-webAccId", "100", "-webAccFun", "tree" };
    DumpInfoArgument argument;
    EXPECT_TRUE(manager->DumpWebInfoParams(params, argument));
    EXPECT_EQ(argument.webAccId, 100);
    EXPECT_EQ(argument.webAccFun, "tree");
    EXPECT_EQ(argument.mode, DumpMode::WEB_ACC_DUMP);
}

/**
 * @tc.name: DumpWebInfoParams002
 * @tc.desc: Test exeAction/sendEvent/hover with valid params
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, DumpWebInfoParams002, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    DumpInfoArgument argument;

    std::vector<std::string> params1 = { "dump", "-webAccFun", "exeAction", "16" };
    EXPECT_TRUE(manager->DumpWebInfoParams(params1, argument));
    EXPECT_EQ(argument.action, 16U);

    std::vector<std::string> params2 = { "dump", "-webAccFun", "sendEvent", "1" };
    EXPECT_TRUE(manager->DumpWebInfoParams(params2, argument));
    EXPECT_EQ(argument.eventId, 1U);

    std::vector<std::string> params3 = { "dump", "-webAccFun", "hover", "100", "200" };
    EXPECT_TRUE(manager->DumpWebInfoParams(params3, argument));
    EXPECT_EQ(argument.pointX, 100U);
    EXPECT_EQ(argument.pointY, 200U);
}

/**
 * @tc.name: DumpWebInfoParams003
 * @tc.desc: Test missing value cases - returns false
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, DumpWebInfoParams003, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    DumpInfoArgument argument;

    EXPECT_FALSE(manager->DumpWebInfoParams({ "dump", "-webAccId" }, argument));
    EXPECT_FALSE(manager->DumpWebInfoParams({ "dump", "-webAccFun" }, argument));
    EXPECT_FALSE(manager->DumpWebInfoParams({ "dump", "-webAccFun", "exeAction" }, argument));
    EXPECT_FALSE(manager->DumpWebInfoParams({ "dump", "-webAccFun", "sendEvent" }, argument));
    EXPECT_FALSE(manager->DumpWebInfoParams({ "dump", "-webAccFun", "hover" }, argument));
    EXPECT_FALSE(manager->DumpWebInfoParams({ "dump", "-webAccFun", "hover", "100" }, argument));
}

/**
 * @tc.name: DumpWebInfoParams004
 * @tc.desc: Test empty/valid edge cases - returns true
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, DumpWebInfoParams004, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    DumpInfoArgument argument;

    EXPECT_TRUE(manager->DumpWebInfoParams({ "dump" }, argument));
    EXPECT_TRUE(manager->DumpWebInfoParams({ "dump", "-webAccId", "-100", "-webAccFun", "tree" }, argument));
}

// ==================== ExecuteWebAccStateDump ====================

/**
 * @tc.name: ExecuteWebAccStateDump001
 * @tc.desc: Test null webPattern - early return
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebAccStateDump001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    manager->ExecuteWebAccStateDump(WEB_GET_ACC, nullptr);
    SUCCEED();
}

/**
 * @tc.name: ExecuteWebAccStateDump002
 * @tc.desc: Test WEB_GET_ACC/WEB_ON_ACC/WEB_OFF_ACC/default with valid webPattern
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebAccStateDump002, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(webPattern_, nullptr);

    manager->ExecuteWebAccStateDump(WEB_GET_ACC, webPattern_);
    manager->ExecuteWebAccStateDump(WEB_ON_ACC, webPattern_);
    manager->ExecuteWebAccStateDump(WEB_OFF_ACC, webPattern_);
    manager->ExecuteWebAccStateDump(WEB_ACC_INVALID, webPattern_); // default case
    SUCCEED();
}

// ==================== ExecuteWebInfoDump ====================

/**
 * @tc.name: ExecuteWebInfoDump001
 * @tc.desc: Test null webPattern - early return
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebInfoDump001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    std::list<AccessibilityElementInfo> infos;
    manager->ExecuteWebInfoDump(WEB_TREE, infos, nullptr);
    SUCCEED();
}

/**
 * @tc.name: ExecuteWebInfoDump002
 * @tc.desc: Test WEB_TREE with empty and non-empty infos
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebInfoDump002, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(webPattern_, nullptr);

    std::list<AccessibilityElementInfo> emptyInfos;
    manager->ExecuteWebInfoDump(WEB_TREE, emptyInfos, webPattern_); // empty infos branch

    std::list<AccessibilityElementInfo> infos;
    infos.push_back(AccessibilityElementInfo());
    manager->ExecuteWebInfoDump(WEB_TREE, infos, webPattern_); // non-empty infos branch
    SUCCEED();
}

/**
 * @tc.name: ExecuteWebInfoDump003
 * @tc.desc: Test WEB_NODE/WEB_PRE/WEB_NEXT/default branches
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebInfoDump003, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(webPattern_, nullptr);

    std::list<AccessibilityElementInfo> infos;
    infos.push_back(AccessibilityElementInfo());

    manager->ExecuteWebInfoDump(WEB_NODE, infos, webPattern_);
    manager->ExecuteWebInfoDump(WEB_PRE, infos, webPattern_);
    manager->ExecuteWebInfoDump(WEB_NEXT, infos, webPattern_);
    manager->ExecuteWebInfoDump(WEB_ACC_INVALID, infos, webPattern_); // default case
    SUCCEED();
}

// ==================== ExecuteWebActionDump ====================

/**
 * @tc.name: ExecuteWebActionDump001
 * @tc.desc: Test null webPattern - early return
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebActionDump001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    DumpInfoArgument argument;
    argument.action = 16;
    manager->ExecuteWebActionDump(WEB_EXE_ACTION, argument, 100, nullptr);
    SUCCEED();
}

/**
 * @tc.name: ExecuteWebActionDump002
 * @tc.desc: Test WEB_EXE_ACTION/WEB_SEND_EVENT/default with valid webPattern
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebActionDump002, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(webPattern_, nullptr);

    DumpInfoArgument argument;
    argument.action = 16;
    manager->ExecuteWebActionDump(WEB_EXE_ACTION, argument, 100, webPattern_);

    argument.eventId = 1;
    manager->ExecuteWebActionDump(WEB_SEND_EVENT, argument, 100, webPattern_);

    manager->ExecuteWebActionDump(WEB_ACC_INVALID, argument, 100, webPattern_); // default case
    SUCCEED();
}

/**
 * @tc.name: ExecuteWebActionDump003
 * @tc.desc: Test WEB_EXE_ACTION with different action types
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebActionDump003, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(webPattern_, nullptr);

    DumpInfoArgument argument;
    // Test ACTION_CLICK
    argument.action = 16;
    manager->ExecuteWebActionDump(WEB_EXE_ACTION, argument, TEST_ELEMENT_ID_POSITIVE, webPattern_);

    // Test ACTION_LONG_CLICK
    argument.action = 32;
    manager->ExecuteWebActionDump(WEB_EXE_ACTION, argument, TEST_ELEMENT_ID_POSITIVE, webPattern_);

    // Test ACTION_SCROLL_FORWARD
    argument.action = 4096;
    manager->ExecuteWebActionDump(WEB_EXE_ACTION, argument, TEST_ELEMENT_ID_POSITIVE, webPattern_);
    SUCCEED();
}

/**
 * @tc.name: ExecuteWebActionDump004
 * @tc.desc: Test WEB_SEND_EVENT with different event types
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebActionDump004, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(webPattern_, nullptr);

    DumpInfoArgument argument;
    argument.eventId = 0; // TYPE_VIEW_FOCUSED
    manager->ExecuteWebActionDump(WEB_SEND_EVENT, argument, TEST_ELEMENT_ID_POSITIVE, webPattern_);

    argument.eventId = 1; // TYPE_VIEW_TEXT_CHANGED
    manager->ExecuteWebActionDump(WEB_SEND_EVENT, argument, TEST_ELEMENT_ID_POSITIVE, webPattern_);

    argument.eventId = 2; // TYPE_VIEW_CLICKED
    manager->ExecuteWebActionDump(WEB_SEND_EVENT, argument, TEST_ELEMENT_ID_POSITIVE, webPattern_);
    SUCCEED();
}

// ==================== Extended Tests ====================

/**
 * @tc.name: ConvertToSplitElementId003
 * @tc.desc: Test boundary values around WEB_MAX_ELEMENT_ID
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ConvertToSplitElementId003, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);

    int64_t belowThreshold = 0xFFFFFFFFFELL;
    EXPECT_EQ(manager->ConvertToSplitElementId(belowThreshold), belowThreshold);

    int64_t eqThreshold = 0xFFFFFFFFFFLL;
    EXPECT_EQ(manager->ConvertToSplitElementId(eqThreshold), eqThreshold);

    int64_t atThreshold = 0x10000000000LL;
    EXPECT_NE(manager->ConvertToSplitElementId(atThreshold), atThreshold);
}

/**
 * @tc.name: DumpElementInfosIfNeed003
 * @tc.desc: Test getAcc/onAcc/offAcc - return true (default case)
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, DumpElementInfosIfNeed003, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    DumpInfoArgument argument;
    argument.webAccId = TEST_ELEMENT_ID_POSITIVE;
    std::list<AccessibilityElementInfo> infos;

    argument.webAccFun = "getAcc";
    EXPECT_TRUE(manager->DumpElementInfosIfNeed(argument, infos, nullptr, TEST_WINDOW_ID));

    argument.webAccFun = "onAcc";
    EXPECT_TRUE(manager->DumpElementInfosIfNeed(argument, infos, nullptr, TEST_WINDOW_ID));

    argument.webAccFun = "offAcc";
    EXPECT_TRUE(manager->DumpElementInfosIfNeed(argument, infos, nullptr, TEST_WINDOW_ID));
}

/**
 * @tc.name: DumpWebInfoParams005
 * @tc.desc: Test all valid webAccFun types
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, DumpWebInfoParams005, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    DumpInfoArgument argument;

    EXPECT_TRUE(manager->DumpWebInfoParams({ "dump", "-webAccFun", "getAcc" }, argument));
    EXPECT_TRUE(manager->DumpWebInfoParams({ "dump", "-webAccFun", "onAcc" }, argument));
    EXPECT_TRUE(manager->DumpWebInfoParams({ "dump", "-webAccFun", "offAcc" }, argument));
    EXPECT_TRUE(manager->DumpWebInfoParams({ "dump", "-webAccFun", "tree" }, argument));
    EXPECT_TRUE(manager->DumpWebInfoParams({ "dump", "-webAccFun", "node" }, argument));
    EXPECT_TRUE(manager->DumpWebInfoParams({ "dump", "-webAccFun", "pre" }, argument));
    EXPECT_TRUE(manager->DumpWebInfoParams({ "dump", "-webAccFun", "next" }, argument));
}

/**
 * @tc.name: ExecuteWebDump007
 * @tc.desc: Test with different elementId values
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ExecuteWebDump007, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(webPattern_, nullptr);
    DumpInfoArgument argument;
    std::list<AccessibilityElementInfo> infos;

    argument.webAccFun = "getAcc";
    argument.webAccId = TEST_ELEMENT_ID_NEGATIVE;
    manager->ExecuteWebDump(argument, infos, webPattern_);

    argument.webAccId = 0;
    manager->ExecuteWebDump(argument, infos, webPattern_);

    argument.webAccId = TEST_ELEMENT_ID_LARGE;
    manager->ExecuteWebDump(argument, infos, webPattern_);
    SUCCEED();
}

/**
 * @tc.name: ChooseWebDumpEvent003
 * @tc.desc: Test with boundary nodeId values
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityJamTest, ChooseWebDumpEvent003, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager, nullptr);

    DumpInfoArgument argument;
    argument.nodeId = 0;
    manager->ChooseWebDumpEvent(argument, TEST_WINDOW_ID);

    argument.nodeId = INT64_MAX;
    manager->ChooseWebDumpEvent(argument, TEST_WINDOW_ID);

    argument.nodeId = INT64_MIN;
    manager->ChooseWebDumpEvent(argument, TEST_WINDOW_ID);
    SUCCEED();
}
}
