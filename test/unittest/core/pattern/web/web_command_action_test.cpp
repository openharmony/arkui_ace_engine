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
    EXPECT_EQ(WebCommandWrapper::ParseEventType("tap"), WebCommandEventType::EVENT_TYPE_TAP_GESTURE);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("scrollGesture"), WebCommandEventType::EVENT_TYPE_SCROLL_GESTURE);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("pinch"), WebCommandEventType::EVENT_TYPE_PINCH_GESTURE);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("longPress"), WebCommandEventType::EVENT_TYPE_LONG_PRESS);
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

// ===== Gesture Command Tests =====

/**
 * @tc.name: ParseEventType_GestureTypes_0100
 * @tc.desc: Test ParseEventType with gesture event types.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ParseEventType_GestureTypes_0100, TestSize.Level1)
{
    EXPECT_EQ(WebCommandWrapper::ParseEventType("tap"), WebCommandEventType::EVENT_TYPE_TAP_GESTURE);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("scrollGesture"), WebCommandEventType::EVENT_TYPE_SCROLL_GESTURE);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("pinch"), WebCommandEventType::EVENT_TYPE_PINCH_GESTURE);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("longPress"), WebCommandEventType::EVENT_TYPE_LONG_PRESS);
}

/**
 * @tc.name: ValidateTapParameters_Success_0100
 * @tc.desc: Test ValidateTapParameters with valid parameters.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ValidateTapParameters_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "x": 100.5,
        "y": 200.5,
        "duration": 100,
        "tapCount": 2
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    double outX, outY;
    int32_t outDuration, outTapCount;
    int result = WebCommandWrapper::ValidateTapParameters(comJson, outX, outY, outDuration, outTapCount);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_EQ(outX, 100.5);
    EXPECT_EQ(outY, 200.5);
    EXPECT_EQ(outDuration, 100);
    EXPECT_EQ(outTapCount, 2);
#endif
}

/**
 * @tc.name: ValidateTapParameters_MissingX_0100
 * @tc.desc: Test ValidateTapParameters with missing x parameter.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ValidateTapParameters_MissingX_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "y": 200.5
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    double outX, outY;
    int32_t outDuration, outTapCount;
    int result = WebCommandWrapper::ValidateTapParameters(comJson, outX, outY, outDuration, outTapCount);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_X));
#endif
}

/**
 * @tc.name: ValidateTapParameters_MissingY_0100
 * @tc.desc: Test ValidateTapParameters with missing y parameter.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ValidateTapParameters_MissingY_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "x": 100.5
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    double outX, outY;
    int32_t outDuration, outTapCount;
    int result = WebCommandWrapper::ValidateTapParameters(comJson, outX, outY, outDuration, outTapCount);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_Y));
#endif
}

/**
 * @tc.name: ValidateScrollGestureParameters_Success_0100
 * @tc.desc: Test ValidateScrollGestureParameters with valid parameters.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ValidateScrollGestureParameters_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "x": 100.5,
        "y": 200.5,
        "xDistance": 50.0,
        "yDistance": -100.0,
        "speed": 800
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    double outX, outY, outXDistance, outYDistance;
    int32_t outSpeed;
    int result = WebCommandWrapper::ValidateScrollGestureParameters(
        comJson, outX, outY, outXDistance, outYDistance, outSpeed);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_EQ(outX, 100.5);
    EXPECT_EQ(outY, 200.5);
    EXPECT_EQ(outXDistance, 50.0);
    EXPECT_EQ(outYDistance, -100.0);
    EXPECT_EQ(outSpeed, 800);
#endif
}

/**
 * @tc.name: ValidateScrollGestureParameters_MissingXDistance_0100
 * @tc.desc: Test ValidateScrollGestureParameters with missing xDistance.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ValidateScrollGestureParameters_MissingXDistance_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "x": 100.5,
        "y": 200.5,
        "yDistance": -100.0
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    double outX, outY, outXDistance, outYDistance;
    int32_t outSpeed;
    int result = WebCommandWrapper::ValidateScrollGestureParameters(
        comJson, outX, outY, outXDistance, outYDistance, outSpeed);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_DISTANCE));
#endif
}

/**
 * @tc.name: ValidatePinchParameters_Success_0100
 * @tc.desc: Test ValidatePinchParameters with valid parameters.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ValidatePinchParameters_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "x": 100.5,
        "y": 200.5,
        "scale": 1.5,
        "speed": 800
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    double outX, outY, outScaleFactor;
    int32_t outSpeed;
    int result = WebCommandWrapper::ValidatePinchParameters(comJson, outX, outY, outScaleFactor, outSpeed);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_EQ(outX, 100.5);
    EXPECT_EQ(outY, 200.5);
    EXPECT_EQ(outScaleFactor, 1.5);
    EXPECT_EQ(outSpeed, 800);
#endif
}

/**
 * @tc.name: ValidatePinchParameters_InvalidScale_0100
 * @tc.desc: Test ValidatePinchParameters with invalid scale (zero or negative).
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ValidatePinchParameters_InvalidScale_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "x": 100.5,
        "y": 200.5,
        "scale": 0,
        "speed": 800
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    double outX, outY, outScaleFactor;
    int32_t outSpeed;
    int result = WebCommandWrapper::ValidatePinchParameters(comJson, outX, outY, outScaleFactor, outSpeed);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_SCALE));
#endif
}

/**
 * @tc.name: ValidatePinchParameters_MissingScale_0100
 * @tc.desc: Test ValidatePinchParameters with missing scale.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ValidatePinchParameters_MissingScale_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "x": 100.5,
        "y": 200.5,
        "speed": 800
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    double outX, outY, outScaleFactor;
    int32_t outSpeed;
    int result = WebCommandWrapper::ValidatePinchParameters(comJson, outX, outY, outScaleFactor, outSpeed);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_SCALE));
#endif
}

/**
 * @tc.name: ValidateLongPressParameters_Success_0100
 * @tc.desc: Test ValidateLongPressParameters with valid parameters.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ValidateLongPressParameters_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "x": 100.5,
        "y": 200.5
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    double outX, outY;
    int result = WebCommandWrapper::ValidateLongPressParameters(comJson, outX, outY);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_EQ(outX, 100.5);
    EXPECT_EQ(outY, 200.5);
#endif
}

/**
 * @tc.name: ValidateLongPressParameters_MissingX_0100
 * @tc.desc: Test ValidateLongPressParameters with missing x parameter.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ValidateLongPressParameters_MissingX_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "y": 200.5
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    double outX, outY;
    int result = WebCommandWrapper::ValidateLongPressParameters(comJson, outX, outY);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_X));
#endif
}

/**
 * @tc.name: ValidateLongPressParameters_MissingY_0100
 * @tc.desc: Test ValidateLongPressParameters with missing y parameter.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ValidateLongPressParameters_MissingY_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "x": 100.5
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    double outX, outY;
    int result = WebCommandWrapper::ValidateLongPressParameters(comJson, outX, outY);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_Y));
#endif
}

/**
 * @tc.name: BuildGestureActionInfo_Tap_Success_0100
 * @tc.desc: Test BuildGestureActionInfo with tap event.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildGestureActionInfo_Tap_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "x": 100.5,
        "y": 200.5,
        "duration": 100,
        "tapCount": 2
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo> outActionInfo;
    int result = WebCommandWrapper::BuildGestureActionInfo(comJson, "tap", outActionInfo);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outActionInfo, nullptr);
    EXPECT_EQ(outActionInfo->GetEventType(), "tap");
    EXPECT_EQ(outActionInfo->GetX(), 100.5);
    EXPECT_EQ(outActionInfo->GetY(), 200.5);
    EXPECT_EQ(outActionInfo->GetDuration(), 100);
    EXPECT_EQ(outActionInfo->GetTapCount(), 2);
#endif
}

/**
 * @tc.name: BuildGestureActionInfo_ScrollGesture_Success_0100
 * @tc.desc: Test BuildGestureActionInfo with scrollGesture event.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildGestureActionInfo_ScrollGesture_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "x": 100.5,
        "y": 200.5,
        "xDistance": 50.0,
        "yDistance": -100.0,
        "speed": 800
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo> outActionInfo;
    int result = WebCommandWrapper::BuildGestureActionInfo(comJson, "scrollGesture", outActionInfo);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outActionInfo, nullptr);
    EXPECT_EQ(outActionInfo->GetEventType(), "scrollGesture");
    EXPECT_EQ(outActionInfo->GetX(), 100.5);
    EXPECT_EQ(outActionInfo->GetY(), 200.5);
    EXPECT_EQ(outActionInfo->GetDistanceX(), 50.0);
    EXPECT_EQ(outActionInfo->GetDistanceY(), -100.0);
    EXPECT_EQ(outActionInfo->GetSpeed(), 800);
#endif
}

/**
 * @tc.name: BuildGestureActionInfo_Pinch_Success_0100
 * @tc.desc: Test BuildGestureActionInfo with pinch event.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildGestureActionInfo_Pinch_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "x": 100.5,
        "y": 200.5,
        "scale": 1.5,
        "speed": 800
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo> outActionInfo;
    int result = WebCommandWrapper::BuildGestureActionInfo(comJson, "pinch", outActionInfo);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outActionInfo, nullptr);
    EXPECT_EQ(outActionInfo->GetEventType(), "pinch");
    EXPECT_EQ(outActionInfo->GetX(), 100.5);
    EXPECT_EQ(outActionInfo->GetY(), 200.5);
    EXPECT_EQ(outActionInfo->GetScale(), 1.5f);
    EXPECT_EQ(outActionInfo->GetSpeed(), 800);
#endif
}

/**
 * @tc.name: BuildGestureActionInfo_LongPress_Success_0100
 * @tc.desc: Test BuildGestureActionInfo with longPress event.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildGestureActionInfo_LongPress_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "x": 100.5,
        "y": 200.5
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo> outActionInfo;
    int result = WebCommandWrapper::BuildGestureActionInfo(comJson, "longPress", outActionInfo);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outActionInfo, nullptr);
    EXPECT_EQ(outActionInfo->GetEventType(), "longPress");
    EXPECT_EQ(outActionInfo->GetX(), 100.5);
    EXPECT_EQ(outActionInfo->GetY(), 200.5);
    EXPECT_EQ(outActionInfo->GetDuration(), 0);
#endif
}

/**
 * @tc.name: IsGestureCommandType_GestureTypes_0100
 * @tc.desc: Test IsGestureCommandType with gesture event types.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, IsGestureCommandType_GestureTypes_0100, TestSize.Level1)
{
    EXPECT_TRUE(WebCommandWrapper::IsGestureCommandType(WebCommandEventType::EVENT_TYPE_TAP_GESTURE));
    EXPECT_TRUE(WebCommandWrapper::IsGestureCommandType(WebCommandEventType::EVENT_TYPE_SCROLL_GESTURE));
    EXPECT_TRUE(WebCommandWrapper::IsGestureCommandType(WebCommandEventType::EVENT_TYPE_PINCH_GESTURE));
    EXPECT_TRUE(WebCommandWrapper::IsGestureCommandType(WebCommandEventType::EVENT_TYPE_LONG_PRESS));
    EXPECT_FALSE(WebCommandWrapper::IsGestureCommandType(WebCommandEventType::CLICK));
    EXPECT_FALSE(WebCommandWrapper::IsGestureCommandType(WebCommandEventType::SCROLL));
}

// ===== ParseEventType - Input Method Types =====

/**
 * @tc.name: ParseEventType_InputMethodTypes_0100
 * @tc.desc: Test ParseEventType with all input method event type strings.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ParseEventType_InputMethodTypes_0100, TestSize.Level1)
{
    EXPECT_EQ(WebCommandWrapper::ParseEventType("inputInsert"), WebCommandEventType::INPUT_INSERT);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("inputModify"), WebCommandEventType::INPUT_MODIFY);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("inputSelect"), WebCommandEventType::INPUT_SELECT);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("inputCut"), WebCommandEventType::INPUT_CUT);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("inputCopy"), WebCommandEventType::INPUT_COPY);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("inputFocus"), WebCommandEventType::INPUT_FOCUS);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("inputSetCursor"), WebCommandEventType::INPUT_SET_CURSOR);
}

/**
 * @tc.name: ParseEventType_InputMethodCaseSensitive_0100
 * @tc.desc: Test ParseEventType with incorrect case for input method types.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, ParseEventType_InputMethodCaseSensitive_0100, TestSize.Level1)
{
    EXPECT_EQ(WebCommandWrapper::ParseEventType("InputInsert"), WebCommandEventType::UNKNOWN);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("INPUTINSERT"), WebCommandEventType::UNKNOWN);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("inputinsert"), WebCommandEventType::UNKNOWN);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("InputModify"), WebCommandEventType::UNKNOWN);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("InputSelect"), WebCommandEventType::UNKNOWN);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("InputCut"), WebCommandEventType::UNKNOWN);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("InputCopy"), WebCommandEventType::UNKNOWN);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("InputFocus"), WebCommandEventType::UNKNOWN);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("InputSetCursor"), WebCommandEventType::UNKNOWN);
    EXPECT_EQ(WebCommandWrapper::ParseEventType("inputsetcursor"), WebCommandEventType::UNKNOWN);
}

// ===== BuildInputMethodAction - InputInsert Tests =====

/**
 * @tc.name: BuildInputMethodAction_InputInsert_Success_0100
 * @tc.desc: Test BuildInputMethodAction with valid inputInsert JSON.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputInsert_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputInsert",
        "content": "hello world",
        "index": 5
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputInsert", outCommandAction);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outCommandAction, nullptr);
    EXPECT_EQ(outCommandAction->GetEventType(), "inputInsert");
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputInsert_MissingContent_0100
 * @tc.desc: Test BuildInputMethodAction with inputInsert JSON missing content.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputInsert_MissingContent_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputInsert",
        "index": 5
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputInsert", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_CONTENT));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputInsert_InvalidContentType_0100
 * @tc.desc: Test BuildInputMethodAction with inputInsert JSON where content is not a string.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputInsert_InvalidContentType_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputInsert",
        "content": 123,
        "index": 5
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputInsert", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_CONTENT));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputInsert_ContentBoolean_0100
 * @tc.desc: Test BuildInputMethodAction with inputInsert JSON where content is boolean.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputInsert_ContentBoolean_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputInsert",
        "content": true,
        "index": 5
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputInsert", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_CONTENT));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputInsert_MissingIndex_0100
 * @tc.desc: Test BuildInputMethodAction with inputInsert JSON missing index.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputInsert_MissingIndex_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputInsert",
        "content": "hello"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputInsert", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputInsert_InvalidIndexString_0100
 * @tc.desc: Test BuildInputMethodAction with inputInsert JSON where index is a string.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputInsert_InvalidIndexString_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputInsert",
        "content": "hello",
        "index": "five"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputInsert", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputInsert_InvalidIndexDouble_0100
 * @tc.desc: Test BuildInputMethodAction with inputInsert JSON where index is a double.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputInsert_InvalidIndexDouble_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputInsert",
        "content": "hello",
        "index": 1.5
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputInsert", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputInsert_IndexBoolean_0100
 * @tc.desc: Test BuildInputMethodAction with inputInsert JSON where index is boolean.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputInsert_IndexBoolean_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputInsert",
        "content": "hello",
        "index": true
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputInsert", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputInsert_NegativeIndex_0100
 * @tc.desc: Test BuildInputMethodAction with inputInsert JSON where index is negative.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputInsert_NegativeIndex_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputInsert",
        "content": "hello",
        "index": -1
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputInsert", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputInsert_IndexZero_0100
 * @tc.desc: Test BuildInputMethodAction with inputInsert JSON where index is zero.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputInsert_IndexZero_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputInsert",
        "content": "test",
        "index": 0
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputInsert", outCommandAction);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outCommandAction, nullptr);
#endif
}

// ===== BuildInputMethodAction - InputModify Tests =====

/**
 * @tc.name: BuildInputMethodAction_InputModify_Success_0100
 * @tc.desc: Test BuildInputMethodAction with valid inputModify JSON.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputModify_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputModify",
        "content": "modified text"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputModify", outCommandAction);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outCommandAction, nullptr);
    EXPECT_EQ(outCommandAction->GetEventType(), "inputModify");
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputModify_MissingContent_0100
 * @tc.desc: Test BuildInputMethodAction with inputModify JSON missing content.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputModify_MissingContent_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputModify"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputModify", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_CONTENT));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputModify_InvalidContentType_0100
 * @tc.desc: Test BuildInputMethodAction with inputModify JSON where content is a number.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputModify_InvalidContentType_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputModify",
        "content": 42
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputModify", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_CONTENT));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputModify_ContentNull_0100
 * @tc.desc: Test BuildInputMethodAction with inputModify JSON where content is null.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputModify_ContentNull_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputModify",
        "content": null
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputModify", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_CONTENT));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputModify_ContentArray_0100
 * @tc.desc: Test BuildInputMethodAction with inputModify JSON where content is an array.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputModify_ContentArray_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputModify",
        "content": ["a", "b"]
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputModify", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_CONTENT));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputModify_ContentObject_0100
 * @tc.desc: Test BuildInputMethodAction with inputModify JSON where content is an object.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputModify_ContentObject_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputModify",
        "content": {"key": "value"}
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputModify", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_CONTENT));
#endif
}

// ===== BuildInputMethodAction - InputSelect Tests =====

/**
 * @tc.name: BuildInputMethodAction_InputSelect_Success_0100
 * @tc.desc: Test BuildInputMethodAction with valid inputSelect JSON.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSelect_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputSelect",
        "start_index": 0,
        "finish_index": 10
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputSelect", outCommandAction);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outCommandAction, nullptr);
    EXPECT_EQ(outCommandAction->GetEventType(), "inputSelect");
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputSelect_MissingStartIndex_0100
 * @tc.desc: Test BuildInputMethodAction with inputSelect JSON missing start_index.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSelect_MissingStartIndex_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputSelect",
        "finish_index": 10
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputSelect", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputSelect_MissingFinishIndex_0100
 * @tc.desc: Test BuildInputMethodAction with inputSelect JSON missing finish_index.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSelect_MissingFinishIndex_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputSelect",
        "start_index": 0
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputSelect", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputSelect_StartGreaterOrEqualFinish_0100
 * @tc.desc: Test BuildInputMethodAction with inputSelect where start_index >= finish_index.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSelect_StartGreaterOrEqualFinish_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr1 = R"({
        "event_type": "inputSelect",
        "start_index": 10,
        "finish_index": 5
    })";
    auto comJson1 = JsonUtil::ParseJsonString(jsonStr1);
    ASSERT_NE(comJson1, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson1, "inputSelect", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX_DURATION));

    const std::string jsonStr2 = R"({
        "event_type": "inputSelect",
        "start_index": 10,
        "finish_index": 10
    })";
    auto comJson2 = JsonUtil::ParseJsonString(jsonStr2);
    ASSERT_NE(comJson2, nullptr);
    result = WebCommandWrapper::BuildInputMethodAction(comJson2, "inputSelect", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX_DURATION));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputSelect_NegativeStartIndex_0100
 * @tc.desc: Test BuildInputMethodAction with inputSelect where start_index is negative.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSelect_NegativeStartIndex_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputSelect",
        "start_index": -1,
        "finish_index": 10
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputSelect", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputSelect_NegativeFinishIndex_0100
 * @tc.desc: Test BuildInputMethodAction with inputSelect where finish_index is negative.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSelect_NegativeFinishIndex_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputSelect",
        "start_index": 0,
        "finish_index": -5
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputSelect", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputSelect_InvalidStartIndexType_0100
 * @tc.desc: Test BuildInputMethodAction with inputSelect where start_index is a string.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSelect_InvalidStartIndexType_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputSelect",
        "start_index": "zero",
        "finish_index": 10
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputSelect", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputSelect_InvalidStartIndexType_0200
 * @tc.desc: Test BuildInputMethodAction with inputSelect where start_index is a double.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSelect_InvalidStartIndexType_0200, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputSelect",
        "start_index": 1.5,
        "finish_index": 10
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputSelect", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputSelect_InvalidFinishIndexType_0100
 * @tc.desc: Test BuildInputMethodAction with inputSelect where finish_index is a double.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSelect_InvalidFinishIndexType_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputSelect",
        "start_index": 1,
        "finish_index": 3.5
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputSelect", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputSelect_BothIndexesMissing_0100
 * @tc.desc: Test BuildInputMethodAction with inputSelect JSON missing both indexes.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSelect_BothIndexesMissing_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputSelect"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputSelect", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

// ===== BuildInputMethodAction - InputFocus Tests =====

/**
 * @tc.name: BuildInputMethodAction_InputFocus_Success_0100
 * @tc.desc: Test BuildInputMethodAction with valid inputFocus JSON.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputFocus_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputFocus",
        "XPath": "/html/body/input",
        "no_need_keyboard": 1
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputFocus", outCommandAction);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outCommandAction, nullptr);
    EXPECT_EQ(outCommandAction->GetEventType(), "inputFocus");
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputFocus_MissingNoNeedKeyboard_0100
 * @tc.desc: Test BuildInputMethodAction with inputFocus JSON missing no_need_keyboard.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputFocus_MissingNoNeedKeyboard_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputFocus",
        "XPath": "/html/body/input"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputFocus", outCommandAction);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outCommandAction, nullptr);
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputFocus_MissingXPath_0100
 * @tc.desc: Test BuildInputMethodAction with inputFocus JSON missing XPath.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputFocus_MissingXPath_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputFocus",
        "no_need_keyboard": 1
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputFocus", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_XPATH));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputFocus_InvalidNoNeedKeyboard_0100
 * @tc.desc: Test BuildInputMethodAction with inputFocus JSON where no_need_keyboard is invalid (2).
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputFocus_InvalidNoNeedKeyboard_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputFocus",
        "XPath": "/html/body/input",
        "no_need_keyboard": 2
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputFocus", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_NO_NEED_KEYBOARD));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputFocus_NoNeedKeyboardNegative_0100
 * @tc.desc: Test BuildInputMethodAction with inputFocus JSON where no_need_keyboard is negative.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputFocus_NoNeedKeyboardNegative_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputFocus",
        "XPath": "/html/body/input",
        "no_need_keyboard": -1
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputFocus", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_NO_NEED_KEYBOARD));
#endif
}

// ===== BuildInputMethodAction - InputSetCursor Tests =====

/**
 * @tc.name: BuildInputMethodAction_InputSetCursor_Success_0100
 * @tc.desc: Test BuildInputMethodAction with valid inputSetCursor JSON.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSetCursor_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputSetCursor",
        "index": 15
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputSetCursor", outCommandAction);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outCommandAction, nullptr);
    EXPECT_EQ(outCommandAction->GetEventType(), "inputSetCursor");
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputSetCursor_MissingIndex_0100
 * @tc.desc: Test BuildInputMethodAction with inputSetCursor JSON missing index.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSetCursor_MissingIndex_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputSetCursor"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputSetCursor", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputSetCursor_NegativeIndex_0100
 * @tc.desc: Test BuildInputMethodAction with inputSetCursor JSON where index is negative.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSetCursor_NegativeIndex_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputSetCursor",
        "index": -3
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputSetCursor", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputSetCursor_InvalidIndexType_0100
 * @tc.desc: Test BuildInputMethodAction with inputSetCursor JSON where index is a string.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSetCursor_InvalidIndexType_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputSetCursor",
        "index": "fifteen"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputSetCursor", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputSetCursor_InvalidIndexType_0200
 * @tc.desc: Test BuildInputMethodAction with inputSetCursor JSON where index is a double.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputSetCursor_InvalidIndexType_0200, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputSetCursor",
        "index": 1.5
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputSetCursor", outCommandAction);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_INDEX));
#endif
}

// ===== BuildInputMethodAction - InputCut/InputCopy (fallback path) =====

/**
 * @tc.name: BuildInputMethodAction_InputCut_Success_0100
 * @tc.desc: Test BuildInputMethodAction with inputCut JSON (falls through to default).
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputCut_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputCut",
        "XPath": "/html/body/input"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputCut", outCommandAction);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outCommandAction, nullptr);
    EXPECT_EQ(outCommandAction->GetEventType(), "inputCut");
#endif
}

/**
 * @tc.name: BuildInputMethodAction_InputCopy_Success_0100
 * @tc.desc: Test BuildInputMethodAction with inputCopy JSON (falls through to default).
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, BuildInputMethodAction_InputCopy_Success_0100, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string jsonStr = R"({
        "event_type": "inputCopy",
        "XPath": "/html/body/input"
    })";
    auto comJson = JsonUtil::ParseJsonString(jsonStr);
    ASSERT_NE(comJson, nullptr);
    std::shared_ptr<NWebCommandActionImpl> outCommandAction;
    int result = WebCommandWrapper::BuildInputMethodAction(comJson, "inputCopy", outCommandAction);
    EXPECT_EQ(result, WEB_COMMAND_BUILD_SUCCESS);
    EXPECT_NE(outCommandAction, nullptr);
    EXPECT_EQ(outCommandAction->GetEventType(), "inputCopy");
#endif
}

// ===== WebCommandResult enum value verification =====

/**
 * @tc.name: WebCommandResult_InputMethodErrorCodes_0100
 * @tc.desc: Verify the WebCommandResult error codes for input method.
 * @tc.type: FUNC
 */
HWTEST_F(WebCommandActionTest, WebCommandResult_InputMethodErrorCodes_0100, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int>(WebCommandResult::JSON_INVALID_CONTENT), 230);
    EXPECT_EQ(static_cast<int>(WebCommandResult::JSON_INVALID_INDEX), 231);
    EXPECT_EQ(static_cast<int>(WebCommandResult::JSON_INVALID_INDEX_DURATION), 232);
    EXPECT_EQ(static_cast<int>(WebCommandResult::JSON_INVALID_NO_NEED_KEYBOARD), 233);
}

} // namespace OHOS::Ace::NG
