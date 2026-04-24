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

#include "test/unittest/core/pattern/web/mock_web_delegate.h"

#include "base/json/json_util.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_command_wrapper.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_ng/pattern/web/web_util.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace OHOS::Ace::NG {
namespace {
RefPtr<FrameNode> g_commandFrameNode = nullptr;
RefPtr<WebPattern> g_commandWebPattern = nullptr;
} // namespace

class WebCommandActionTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebCommandActionTest::SetUpTestCase()
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string src = "web_command_action_test";
    RefPtr<WebController> webController = AceType::MakeRefPtr<WebController>();
    EXPECT_NE(webController, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    g_commandFrameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId,
        [src, webController]() { return AceType::MakeRefPtr<WebPattern>(src, webController); });
    stack->Push(g_commandFrameNode);
    g_commandWebPattern = g_commandFrameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(g_commandWebPattern);
    g_commandWebPattern->SetWebSrc(src);
    g_commandWebPattern->SetWebController(webController);
#endif
}

void WebCommandActionTest::TearDownTestCase()
{
#ifdef OHOS_STANDARD_SYSTEM
    g_commandFrameNode = nullptr;
    g_commandWebPattern = nullptr;
#endif
}

void WebCommandActionTest::SetUp() {}
void WebCommandActionTest::TearDown() {}

// ===== WebCommandWrapper::ParseEventType Tests =====

/**
 * @tc.name: ParseEventType_ValidTypes_0100
 * @tc.desc: Test ParseEventType with all valid event type strings.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ParseEventType_ValidTypes_0100, TestSize.Level1)
{
    EXPECT_EQ(WebCommandWrapper::ParseEventType("click"), WebCommandEventType::CLICK);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("scroll"), WebCommandEventType::SCROLL);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("input-date"), WebCommandEventType::INPUT_DATE);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("input-datetime-local"), WebCommandEventType::INPUT_DATETIME_LOCAL);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("input-month"), WebCommandEventType::INPUT_MONTH);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("input-time"), WebCommandEventType::INPUT_TIME);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("input-week"), WebCommandEventType::INPUT_WEEK);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("select"), WebCommandEventType::SELECT);
}

/**
 * @tc.name: ParseEventType_InvalidTypes_0100
 * @tc.desc: Test ParseEventType with empty, unrecognized, and case-sensitive strings.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ParseEventType_InvalidTypes_0100, TestSize.Level1)
{
    EXPECT_EQ(WebCommandWrapper::ParseEventType(""), WebCommandEventType::UNKNOWN);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("invalid"), WebCommandEventType::UNKNOWN);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("CLICK"), WebCommandEventType::UNKNOWN);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("click "), WebCommandEventType::UNKNOWN);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("Select"), WebCommandEventType::UNKNOWN);
}

// ===== WebCommandWrapper::IsValidAlign Tests =====

/**
 * @tc.name: IsValidAlign_ValidValues_0100
 * @tc.desc: Test IsValidAlign with all valid align strings.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, IsValidAlign_ValidValues_0100, TestSize.Level1)
{
    EXPECT_TRUE(WebCommandWrapper::IsValidAlign("top"));
    EXPECT_TRUE(WebCommandWrapper::IsValidAlign("mid"));
    EXPECT_TRUE(WebCommandWrapper::IsValidAlign("bottom"));
}

/**
 * @tc.name: IsValidAlign_InvalidValues_0100
 * @tc.desc: Test IsValidAlign with invalid align strings.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, IsValidAlign_InvalidValues_0100, TestSize.Level1)
{
    EXPECT_FALSE(WebCommandWrapper::IsValidAlign("center"));
    EXPECT_FALSE(WebCommandWrapper::IsValidAlign(""));
    EXPECT_FALSE(WebCommandWrapper::IsValidAlign("Top"));
    EXPECT_FALSE(WebCommandWrapper::IsValidAlign("top "));
    EXPECT_FALSE(WebCommandWrapper::IsValidAlign("left"));
}

// ===== WebCommandWrapper::BuildClickScrollAction Tests =====

/**
 * @tc.name: BuildClickScrollAction_Click_Success_0100
 * @tc.desc: Test BuildClickScrollAction with valid click JSON.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildClickScrollAction_Click_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "click",
        "XPath": "/html/body/div"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildClickScrollAction(comJson, "click", outCommandAction);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outCommandAction, nullptr);
    EXPECT_EQ(outCommandAction->GetEventType(), "click");
    EXPECT_EQ(outCommandAction->GetXPath(), "/html/body/div");
#endif
}

/**
 * @tc.name: BuildClickScrollAction_Scroll_Success_0100
 * @tc.desc: Test BuildClickScrollAction with valid scroll JSON.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildClickScrollAction_Scroll_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "scroll",
        "duration": 500,
        "align": "mid",
        "offset": 100,
        "XPath": "/html/body"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildClickScrollAction(comJson, "scroll", outCommandAction);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outCommandAction, nullptr);
    EXPECT_EQ(outCommandAction->GetEventType(), "scroll");
    EXPECT_EQ(outCommandAction->GetDuration(), 500);
    EXPECT_EQ(outCommandAction->GetAlign(), "mid");
    EXPECT_EQ(outCommandAction->GetOffset(), 100);
#endif
}

/**
 * @tc.name: BuildClickScrollAction_Click_MissingXPath_0100
 * @tc.desc: Test BuildClickScrollAction with click JSON missing XPath.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildClickScrollAction_Click_MissingXPath_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "click"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildClickScrollAction(comJson, "click", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_XPATH));
#endif
}

/**
 * @tc.name: BuildClickScrollAction_Click_InvalidXPathType_0100
 * @tc.desc: Test BuildClickScrollAction with click JSON where XPath is a number.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildClickScrollAction_Click_InvalidXPathType_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "click",
        "XPath": 123
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildClickScrollAction(comJson, "click", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_XPATH));
#endif
}

/**
 * @tc.name: BuildClickScrollAction_Scroll_MissingDuration_0100
 * @tc.desc: Test BuildClickScrollAction with scroll JSON missing duration.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildClickScrollAction_Scroll_MissingDuration_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "scroll",
        "align": "top",
        "offset": 10,
        "XPath": "/html/body"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildClickScrollAction(comJson, "scroll", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_DURATION));
#endif
}

/**
 * @tc.name: BuildClickScrollAction_Scroll_InvalidAlign_0100
 * @tc.desc: Test BuildClickScrollAction with scroll JSON having invalid align value.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildClickScrollAction_Scroll_InvalidAlign_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "scroll",
        "duration": 100,
        "align": "center",
        "offset": 10,
        "XPath": "/html/body"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildClickScrollAction(comJson, "scroll", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_VALUE_ERROR_ALIGN));
#endif
}

/**
 * @tc.name: BuildClickScrollAction_Scroll_MissingOffset_0100
 * @tc.desc: Test BuildClickScrollAction with scroll JSON missing offset.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildClickScrollAction_Scroll_MissingOffset_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "scroll",
        "duration": 100,
        "align": "top",
        "XPath": "/html/body"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildClickScrollAction(comJson, "scroll", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_OFFSET));
#endif
}

// ===== WebCommandWrapper::BuildInputActionInfo Tests =====

/**
 * @tc.name: BuildInputActionInfo_Success_0100
 * @tc.desc: Test BuildInputActionInfo with valid xpath and value.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputActionInfo_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "xpath": "/html/body/input",
        "value": "2025-01-01"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo> outActionInfo;
    int result = WebCommandWrapper::BuildInputActionInfo(comJson, "input-date", outActionInfo);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outActionInfo, nullptr);
    EXPECT_EQ(outActionInfo->GetEventType(), "input-date");
    EXPECT_EQ(outActionInfo->GetInputValue(), "2025-01-01");
    EXPECT_EQ(outActionInfo->GetXPath(), "/html/body/input");
#endif
}

/**
 * @tc.name: BuildInputActionInfo_MissingXpath_0100
 * @tc.desc: Test BuildInputActionInfo with missing xpath.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputActionInfo_MissingXpath_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "value": "2025-01-01"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo> outActionInfo;
    int result = WebCommandWrapper::BuildInputActionInfo(comJson, "input-date", outActionInfo);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INPUT_XPATH));
#endif
}

/**
 * @tc.name: BuildInputActionInfo_EmptyXpath_0100
 * @tc.desc: Test BuildInputActionInfo with empty xpath string.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputActionInfo_EmptyXpath_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "xpath": "",
        "value": "2025-01-01"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo> outActionInfo;
    int result = WebCommandWrapper::BuildInputActionInfo(comJson, "input-date", outActionInfo);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INPUT_XPATH));
#endif
}

/**
 * @tc.name: BuildInputActionInfo_MissingValue_0100
 * @tc.desc: Test BuildInputActionInfo with missing value.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputActionInfo_MissingValue_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "xpath": "/html/body/input"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo> outActionInfo;
    int result = WebCommandWrapper::BuildInputActionInfo(comJson, "input-date", outActionInfo);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INPUT_VALUE));
#endif
}

/**
 * @tc.name: BuildInputActionInfo_EmptyValue_0100
 * @tc.desc: Test BuildInputActionInfo with empty value string.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputActionInfo_EmptyValue_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "xpath": "/html/body/input",
        "value": ""
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo> outActionInfo;
    int result = WebCommandWrapper::BuildInputActionInfo(comJson, "input-date", outActionInfo);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INPUT_VALUE));
#endif
}

// ===== WebCommandWrapper::BuildSelectActionInfo Tests =====

/**
 * @tc.name: BuildSelectActionInfo_SuccessWithValues_0100
 * @tc.desc: Test BuildSelectActionInfo with valid xpath and values array.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildSelectActionInfo_SuccessWithValues_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "xpath": "/html/body/select",
        "value": ["option1", "option2"]
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo> outActionInfo;
    int result = WebCommandWrapper::BuildSelectActionInfo(comJson, "select", outActionInfo);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outActionInfo, nullptr);
    EXPECT_EQ(outActionInfo->GetEventType(), "select");
    EXPECT_EQ(outActionInfo->GetXPath(), "/html/body/select");
    auto values = outActionInfo->GetOptionValues();
    EXPECT_EQ(values.size(), 2u);
    EXPECT_EQ(values[0], "option1");
    EXPECT_EQ(values[1], "option2");
#endif
}

/**
 * @tc.name: BuildSelectActionInfo_SuccessWithIndexes_0100
 * @tc.desc: Test BuildSelectActionInfo with valid xpath and indexes array.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildSelectActionInfo_SuccessWithIndexes_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "xpath": "/html/body/select",
        "index": [0, 2]
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo> outActionInfo;
    int result = WebCommandWrapper::BuildSelectActionInfo(comJson, "select", outActionInfo);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outActionInfo, nullptr);
    auto indexes = outActionInfo->GetOptionIndexes();
    EXPECT_EQ(indexes.size(), 2u);
    EXPECT_EQ(indexes[0], 0);
    EXPECT_EQ(indexes[1], 2);
#endif
}

/**
 * @tc.name: BuildSelectActionInfo_SuccessWithSingleValueArray_0100
 * @tc.desc: Test BuildSelectActionInfo with valid xpath and single-element value array.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildSelectActionInfo_SuccessWithSingleValueArray_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "xpath": "/html/body/select",
        "value": ["option1"]
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo> outActionInfo;
    int result = WebCommandWrapper::BuildSelectActionInfo(comJson, "select", outActionInfo);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outActionInfo, nullptr);
    auto values = outActionInfo->GetOptionValues();
    EXPECT_EQ(values.size(), 1u);
    EXPECT_EQ(values[0], "option1");
#endif
}

/**
 * @tc.name: BuildSelectActionInfo_MissingXpath_0100
 * @tc.desc: Test BuildSelectActionInfo with missing xpath.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildSelectActionInfo_MissingXpath_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "value": ["option1"]
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo> outActionInfo;
    int result = WebCommandWrapper::BuildSelectActionInfo(comJson, "select", outActionInfo);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_SELECT_XPATH));
#endif
}

/**
 * @tc.name: BuildSelectActionInfo_EmptyOptions_0100
 * @tc.desc: Test BuildSelectActionInfo with no values or indexes.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildSelectActionInfo_EmptyOptions_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "xpath": "/html/body/select"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo> outActionInfo;
    int result = WebCommandWrapper::BuildSelectActionInfo(comJson, "select", outActionInfo);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_SELECT_OPTIONS));
#endif
}

// ===== IsInputEventType Tests =====

/**
 * @tc.name: IsInputEventType_AllTypes_0100
 * @tc.desc: Test IsInputEventType with all event types.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, IsInputEventType_AllTypes_0100, TestSize.Level1)
{
    EXPECT_TRUE(IsInputEventType(WebCommandEventType::INPUT_DATE));
    EXPECT_TRUE(IsInputEventType(WebCommandEventType::INPUT_DATETIME_LOCAL));
    EXPECT_TRUE(IsInputEventType(WebCommandEventType::INPUT_MONTH));
    EXPECT_TRUE(IsInputEventType(WebCommandEventType::INPUT_TIME));
    EXPECT_TRUE(IsInputEventType(WebCommandEventType::INPUT_WEEK));
    EXPECT_FALSE(IsInputEventType(WebCommandEventType::CLICK));
    EXPECT_FALSE(IsInputEventType(WebCommandEventType::SCROLL));
    EXPECT_FALSE(IsInputEventType(WebCommandEventType::SELECT));
    EXPECT_FALSE(IsInputEventType(WebCommandEventType::UNKNOWN));
}

// ===== WebPattern::OnInjectionEvent supplementary tests (input/select paths) =====

/**
 * @tc.name: OnInjectionEvent_InputDate_ManagerNull_0100
 * @tc.desc: Test OnInjectionEvent with input-date when command action manager is null.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, OnInjectionEvent_InputDate_ManagerNull_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string command = R"({
        "event_type": "input-date",
        "xpath": "/html/body/input",
        "value": "2025-01-01"
    })";
    int result = g_commandWebPattern->OnInjectionEvent(command);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::FAILED));
#endif
}

/**
 * @tc.name: OnInjectionEvent_InputTime_MissingValue_0100
 * @tc.desc: Test OnInjectionEvent with input-time missing value.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, OnInjectionEvent_InputTime_MissingValue_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string command = R"({
        "event_type": "input-time",
        "xpath": "/html/body/input"
    })";
    int result = g_commandWebPattern->OnInjectionEvent(command);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INPUT_VALUE));
#endif
}

/**
 * @tc.name: OnInjectionEvent_Select_ManagerNull_0100
 * @tc.desc: Test OnInjectionEvent with select when command action manager is null.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, OnInjectionEvent_Select_ManagerNull_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string command = R"({
        "event_type": "select",
        "xpath": "/html/body/select",
        "value": ["option1", "option2"]
    })";
    int result = g_commandWebPattern->OnInjectionEvent(command);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::FAILED));
#endif
}

/**
 * @tc.name: OnInjectionEvent_Select_EmptyOptions_0100
 * @tc.desc: Test OnInjectionEvent with select command having no values or indexes.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, OnInjectionEvent_Select_EmptyOptions_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string command = R"({
        "event_type": "select",
        "xpath": "/html/body/select"
    })";
    int result = g_commandWebPattern->OnInjectionEvent(command);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_SELECT_OPTIONS));
#endif
}

} // namespace OHOS::Ace::NG
