/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <gmock/gmock.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/web/mock_web_delegate.h"

#include "base/memory/ace_type.h"

#define private public
#include "core/common/ai/image_analyzer_manager.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_ng/property/safe_area_insets.h"
#undef private

#include "core/common/udmf/unified_data.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class UnifiedDataMock : public Ace::UnifiedData {
public:
    int64_t GetSize() override
    {
        return 0;
    }
};

class MockNWebAccessibilityNodeInfo : public NWeb::NWebAccessibilityNodeInfo {
public:
    MOCK_METHOD(std::string, GetHint, (), (override));
    MOCK_METHOD(std::string, GetError, (), (override));
    MOCK_METHOD(int32_t, GetRectX, (), (override));
    MOCK_METHOD(int32_t, GetRectY, (), (override));
    MOCK_METHOD(void, SetPageId, (int32_t), (override));
    MOCK_METHOD(int32_t, GetPageId, (), (override));
    MOCK_METHOD(std::vector<uint32_t>, GetActions, (), (override));
    MOCK_METHOD(std::string, GetContent, (), (override));
    MOCK_METHOD(std::vector<int64_t>, GetChildIds, (), (override));
    MOCK_METHOD(void, SetParentId, (int64_t), (override));
    MOCK_METHOD(int64_t, GetParentId, (), (override));
    MOCK_METHOD(bool, GetIsHeading, (), (override));
    MOCK_METHOD(bool, GetIsChecked, (), (override));
    MOCK_METHOD(bool, GetIsEnabled, (), (override));
    MOCK_METHOD(bool, GetIsFocused, (), (override));
    MOCK_METHOD(int32_t, GetRectWidth, (), (override));
    MOCK_METHOD(int32_t, GetRectHeight, (), (override));
    MOCK_METHOD(bool, GetIsVisible, (), (override));
    MOCK_METHOD(bool, GetIsHinting, (), (override));
    MOCK_METHOD(bool, GetIsEditable, (), (override));
    MOCK_METHOD(bool, GetIsSelected, (), (override));
    MOCK_METHOD(size_t, GetItemCounts, (), (override));
    MOCK_METHOD(int32_t, GetLiveRegion, (), (override));
    MOCK_METHOD(bool, GetIsPassword, (), (override));
    MOCK_METHOD(bool, GetIsCheckable, (), (override));
    MOCK_METHOD(bool, GetIsClickable, (), (override));
    MOCK_METHOD(bool, GetIsFocusable, (), (override));
    MOCK_METHOD(bool, GetIsScrollable, (), (override));
    MOCK_METHOD(bool, GetIsDeletable, (), (override));
    MOCK_METHOD(int64_t, GetAccessibilityId, (), (override));
    MOCK_METHOD(bool, GetIsPopupSupported, (), (override));
    MOCK_METHOD(bool, GetIsContentInvalid, (), (override));
    MOCK_METHOD(int32_t, GetSelectionEnd, (), (override));
    MOCK_METHOD(int32_t, GetSelectionStart, (), (override));
    MOCK_METHOD(float, GetRangeInfoMin, (), (override));
    MOCK_METHOD(float, GetRangeInfoMax, (), (override));
    MOCK_METHOD(float, GetRangeInfoCurrent, (), (override));
    MOCK_METHOD(int32_t, GetInputType, (), (override));
    MOCK_METHOD(std::string, GetComponentType, (), (override));
    MOCK_METHOD(std::string, GetDescriptionInfo, (), (override));
    MOCK_METHOD(int32_t, GetGridRows, (), (override));
    MOCK_METHOD(int32_t, GetGridItemRow, (), (override));
    MOCK_METHOD(int32_t, GetGridColumns, (), (override));
    MOCK_METHOD(int32_t, GetGridItemColumn, (), (override));
    MOCK_METHOD(int32_t, GetGridItemRowSpan, (), (override));
    MOCK_METHOD(int32_t, GetGridSelectedMode, (), (override));
    MOCK_METHOD(int32_t, GetGridItemColumnSpan, (), (override));
    MOCK_METHOD(bool, GetIsAccessibilityFocus, (), (override));
    MOCK_METHOD(bool, GetIsPluralLineSupported, (), (override));
    MOCK_METHOD(bool, GetIsAccessibilityGroup, (), (override));
    MOCK_METHOD(std::string, GetAccessibilityLevel, (), (override));
    MOCK_METHOD(std::string, GetAccessibilityDescription, (), (override));
    MOCK_METHOD(std::string, GetAccessibilityText, (), (override));
};

class WebPatternTouchTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternTouchTestNg::SetUpTestCase() {}
void WebPatternTouchTestNg::TearDownTestCase() {}
void WebPatternTouchTestNg::SetUp() {}
void WebPatternTouchTestNg::TearDown()
{
    OHOS::Ace::SetReturnStatus("");
    OHOS::Ace::SetComponentType("");
}

/**
 * @tc.name: CheckSafeAreaIsExpand_001
 * @tc.desc: CheckSafeAreaIsExpand.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, CheckSafeAreaIsExpand_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto ret = webPattern->CheckSafeAreaIsExpand();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: CheckSafeAreaIsExpand_002
 * @tc.desc: CheckSafeAreaIsExpand.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, CheckSafeAreaIsExpand_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty();
    SafeAreaExpandOpts opts { .type = SAFE_AREA_TYPE_CUTOUT, .edges = SAFE_AREA_EDGE_TOP | SAFE_AREA_EDGE_BOTTOM };
    layoutProperty->UpdateSafeAreaExpandOpts(opts);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto ret = webPattern->CheckSafeAreaIsExpand();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: CheckSafeAreaIsExpand_003
 * @tc.desc: CheckSafeAreaIsExpand.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, CheckSafeAreaIsExpand_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty();
    SafeAreaExpandOpts opts { .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_TOP | SAFE_AREA_EDGE_BOTTOM };
    layoutProperty->UpdateSafeAreaExpandOpts(opts);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto ret = webPattern->CheckSafeAreaIsExpand();
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: CheckSafeAreaIsExpand_004
 * @tc.desc: CheckSafeAreaIsExpand.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, CheckSafeAreaIsExpand_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty();
    SafeAreaExpandOpts opts { .type = SAFE_AREA_TYPE_KEYBOARD, .edges = SAFE_AREA_EDGE_TOP | SAFE_AREA_EDGE_BOTTOM };
    layoutProperty->UpdateSafeAreaExpandOpts(opts);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto ret = webPattern->CheckSafeAreaIsExpand();
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: CheckSafeAreaKeyBoard_001
 * @tc.desc: CheckSafeAreaKeyBoard.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, CheckSafeAreaKeyBoard_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto ret = webPattern->CheckSafeAreaKeyBoard();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: CheckSafeAreaKeyBoard_002
 * @tc.desc: CheckSafeAreaKeyBoard.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, CheckSafeAreaKeyBoard_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty();
    SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_KEYBOARD, .edges = SAFE_AREA_EDGE_BOTTOM };
    layoutProperty->UpdateSafeAreaExpandOpts(opts);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto ret = webPattern->CheckSafeAreaKeyBoard();
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: CheckSafeAreaKeyBoard_003
 * @tc.desc: CheckSafeAreaKeyBoard.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, CheckSafeAreaKeyBoard_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty();
    SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_KEYBOARD, .edges = SAFE_AREA_EDGE_TOP };
    layoutProperty->UpdateSafeAreaExpandOpts(opts);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto ret = webPattern->CheckSafeAreaKeyBoard();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: CheckSafeAreaKeyBoard_004
 * @tc.desc: CheckSafeAreaKeyBoard.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, CheckSafeAreaKeyBoard_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty();
    SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_BOTTOM };
    layoutProperty->UpdateSafeAreaExpandOpts(opts);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto ret = webPattern->CheckSafeAreaKeyBoard();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: GetWordSelection_001
 * @tc.desc: GetWordSelection.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, GetWordSelection_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    std::string text = "test";
    int8_t offset = 5;
    auto ret = webPattern->GetWordSelection(text, offset);
    std::vector<int8_t> expectedResult = { -1, -1 };
    EXPECT_EQ(ret, expectedResult);
#endif
}

/**
 * @tc.name: Backward_001
 * @tc.desc: Backward.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, Backward_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    auto ret = webpattern.Backward();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: Backward_002
 * @tc.desc: Backward.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, Backward_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto ret = webPattern->Backward();
    EXPECT_EQ(ret, false);
    ret = webPattern->Backward();
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: SuggestionSelected_001
 * @tc.desc: SuggestionSelected.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, SuggestionSelected_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    int32_t index = 1;
    webpattern.SuggestionSelected(index);
    EXPECT_EQ(webpattern.isShowAutofillPopup_, false);
#endif
}

/**
 * @tc.name: SuggestionSelected_002
 * @tc.desc: SuggestionSelected.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, SuggestionSelected_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    int32_t index = 1;
    webPattern->SuggestionSelected(index);
    EXPECT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: OnShowAutofillPopup_001
 * @tc.desc: OnShowAutofillPopup
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, OnShowAutofillPopup_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    MockPipelineContext::SetUp();
    std::vector<std::string> menu_items;
    webPattern->OnShowAutofillPopup(0, 0, menu_items);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: OnShowAutofillPopupV2_001
 * @tc.desc: OnShowAutofillPopupV2
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, OnShowAutofillPopupV2_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    MockPipelineContext::SetUp();
    std::vector<std::string> menu_items;
    webPattern->OnShowAutofillPopupV2(0, 0, 10, 10, menu_items);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: OnHideAutofillPopup_001
 * @tc.desc: OnHideAutofillPopup.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, OnHideAutofillPopup_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    MockPipelineContext::SetUp();
    webPattern->isShowAutofillPopup_ = false;
    webPattern->OnHideAutofillPopup();
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: OnHideAutofillPopup_002
 * @tc.desc: OnHideAutofillPopup.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, OnHideAutofillPopup_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    webPattern->isShowAutofillPopup_ = true;
    webPattern->OnHideAutofillPopup();
#endif
}

/**
 * @tc.name: CloseKeyboard_001
 * @tc.desc: CloseKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, CloseKeyboard_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    webPattern->CloseKeyboard();
#endif
}

/**
 * @tc.name: GetWebInfoType_001
 * @tc.desc: GetWebInfoType.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, GetWebInfoType_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    OHOS::Ace::SetReturnStatus("8");
    auto ret = webPattern->GetWebInfoType();
    EXPECT_EQ(ret, WebInfoType::TYPE_2IN1);

    OHOS::Ace::SetReturnStatus("4");
    ret = webPattern->GetWebInfoType();
    EXPECT_EQ(ret, WebInfoType::TYPE_TABLET);

    OHOS::Ace::SetReturnStatus("2");
    ret = webPattern->GetWebInfoType();
    EXPECT_EQ(ret, WebInfoType::TYPE_MOBILE);

    OHOS::Ace::SetReturnStatus("1");
    ret = webPattern->GetWebInfoType();
    EXPECT_EQ(ret, WebInfoType::TYPE_MOBILE);
#endif
}

/**
 * @tc.name: GetWebInfoType_002
 * @tc.desc: GetWebInfoType.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, GetWebInfoType_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    auto expectedType = OHOS::Ace::NG::WebInfoType::TYPE_UNKNOWN;
    auto result = webpattern.GetWebInfoType();
    EXPECT_EQ(result, expectedType);
#endif
}

/**
 * @tc.name: JsonNodePutDefaultValue_001
 * @tc.desc: JsonNodePutDefaultValue.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, JsonNodePutDefaultValue_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    std::unique_ptr<OHOS::Ace::JsonValue> jsonNode = nullptr;
    auto key = WebPattern::WebAccessibilityType::SEL_END;
    bool value = false;
    webPattern->JsonNodePutDefaultValue(jsonNode, key, value);
#endif
}

/**
 * @tc.name: JsonNodePutDefaultValue_002
 * @tc.desc: JsonNodePutDefaultValue.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, JsonNodePutDefaultValue_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    std::unique_ptr<OHOS::Ace::JsonValue> jsonNode = std::make_unique<OHOS::Ace::JsonValue>();
    auto key = WebPattern::WebAccessibilityType::SEL_END;
    bool value = true;
    webPattern->JsonNodePutDefaultValue(jsonNode, key, value);
#endif
}

/**
 * @tc.name: JsonNodePutDefaultValue_003
 * @tc.desc: JsonNodePutDefaultValue.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, JsonNodePutDefaultValue_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    std::unique_ptr<OHOS::Ace::JsonValue> jsonNode = nullptr;
    auto key = WebPattern::WebAccessibilityType::SEL_END;
    std::string value1 = "";
    webPattern->JsonNodePutDefaultValue(jsonNode, key, value1);
#endif
}

/**
 * @tc.name: JsonNodePutDefaultValue_004
 * @tc.desc: JsonNodePutDefaultValue.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, JsonNodePutDefaultValue_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    std::unique_ptr<OHOS::Ace::JsonValue> jsonNode = std::make_unique<OHOS::Ace::JsonValue>();
    auto key = WebPattern::WebAccessibilityType::SEL_END;
    std::string value = "test";
    webPattern->JsonNodePutDefaultValue(jsonNode, key, value);
#endif
}

/**
 * @tc.name: JsonNodePutDefaultValue_005
 * @tc.desc: JsonNodePutDefaultValue.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, JsonNodePutDefaultValue_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    auto jsonNode = std::make_unique<OHOS::Ace::JsonValue>();
    auto key = WebPattern::WebAccessibilityType::SEL_END;
    int32_t value = 1;
    int32_t defaultValue = 0;
    webPattern->JsonNodePutDefaultValue(jsonNode, key, value, defaultValue);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: JsonNodePutDefaultValue_006
 * @tc.desc: JsonNodePutDefaultValue.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, JsonNodePutDefaultValue_006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    std::unique_ptr<OHOS::Ace::JsonValue> jsonNode = std::make_unique<OHOS::Ace::JsonValue>();
    auto key = WebPattern::WebAccessibilityType::SEL_END;
    int32_t value = 1;
    int32_t defaultValue = 1;
    webPattern->JsonNodePutDefaultValue(jsonNode, key, value, defaultValue);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: EnumTypeToString_001
 * @tc.desc: EnumTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, EnumTypeToString_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto type = WebPattern::WebAccessibilityType::SEL_END;
    auto result = webPattern->EnumTypeToString(type);
    std::string expected = std::to_string(static_cast<int>(WebPattern::WebAccessibilityType::SEL_END));
    EXPECT_EQ(result, expected);
#endif
}

/**
 * @tc.name: VectorIntToString_001
 * @tc.desc: VectorIntToString.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, VectorIntToString_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    std::vector<int64_t> vec1 = { 1, 2, 3 };
    std::string result = webPattern->VectorIntToString(std::move(vec1));
    std::string expected = "1 2 3";
    EXPECT_EQ(result, expected);
#endif
}

/**
 * @tc.name: VectorIntToString_002
 * @tc.desc: VectorIntToString.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, VectorIntToString_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    std::vector<int64_t> vec1 = {};
    std::string result = webPattern->VectorIntToString(std::move(vec1));
    std::string expected = "";
    EXPECT_EQ(result, expected);
#endif
}

/**
 * @tc.name: WebNodeInfoToJsonValue_001
 * @tc.desc: WebNodeInfoToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, WebNodeInfoToJsonValue_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto mockNodeInfo = std::make_shared<NiceMock<MockNWebAccessibilityNodeInfo>>();
    EXPECT_CALL(*mockNodeInfo, GetSelectionEnd()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*mockNodeInfo, GetRectWidth()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*mockNodeInfo, GetRectHeight()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*mockNodeInfo, GetSelectionStart()).Times(0);
    EXPECT_CALL(*mockNodeInfo, GetRectX()).Times(0);
    EXPECT_CALL(*mockNodeInfo, GetRectY()).Times(0);
    auto jsonNodeArray = std::make_shared<OHOS::Ace::JsonValue>();
    std::string nodeTag = "test";
    webPattern->WebNodeInfoToJsonValue(jsonNodeArray, mockNodeInfo, nodeTag);
#endif
}

/**
 * @tc.name: WebNodeInfoToJsonValue_002
 * @tc.desc: WebNodeInfoToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, WebNodeInfoToJsonValue_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto mockNodeInfo = std::make_shared<NiceMock<MockNWebAccessibilityNodeInfo>>();
    EXPECT_CALL(*mockNodeInfo, GetSelectionEnd()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockNodeInfo, GetRectWidth()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockNodeInfo, GetRectHeight()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*mockNodeInfo, GetSelectionStart()).Times(1);
    EXPECT_CALL(*mockNodeInfo, GetRectX()).Times(1);
    EXPECT_CALL(*mockNodeInfo, GetRectY()).Times(1);
    auto jsonNodeArray = std::make_shared<OHOS::Ace::JsonValue>();
    std::string nodeTag = "test";
    webPattern->WebNodeInfoToJsonValue(jsonNodeArray, mockNodeInfo, nodeTag);
#endif
}

/**
 * @tc.name: WebNodeInfoToJsonValue_003
 * @tc.desc: WebNodeInfoToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, WebNodeInfoToJsonValue_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto mockNodeInfo = std::make_shared<NiceMock<MockNWebAccessibilityNodeInfo>>();
    EXPECT_CALL(*mockNodeInfo, GetSelectionEnd()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*mockNodeInfo, GetRectWidth()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockNodeInfo, GetRectHeight()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockNodeInfo, GetSelectionStart()).Times(0);
    EXPECT_CALL(*mockNodeInfo, GetRectX()).Times(1);
    EXPECT_CALL(*mockNodeInfo, GetRectY()).Times(1);
    auto jsonNodeArray = std::make_shared<OHOS::Ace::JsonValue>();
    std::string nodeTag = "test";
    webPattern->WebNodeInfoToJsonValue(jsonNodeArray, mockNodeInfo, nodeTag);
#endif
}

/**
 * @tc.name: WebNodeInfoToJsonValue_004
 * @tc.desc: WebNodeInfoToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, WebNodeInfoToJsonValue_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto mockNodeInfo = std::make_shared<NiceMock<MockNWebAccessibilityNodeInfo>>();
    EXPECT_CALL(*mockNodeInfo, GetSelectionEnd()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*mockNodeInfo, GetRectWidth()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*mockNodeInfo, GetRectHeight()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockNodeInfo, GetSelectionStart()).Times(0);
    EXPECT_CALL(*mockNodeInfo, GetRectX()).Times(1);
    EXPECT_CALL(*mockNodeInfo, GetRectY()).Times(1);
    auto jsonNodeArray = std::make_shared<OHOS::Ace::JsonValue>();
    std::string nodeTag = "test";
    webPattern->WebNodeInfoToJsonValue(jsonNodeArray, mockNodeInfo, nodeTag);
#endif
}

/**
 * @tc.name: GetWebAllInfosImpl_001
 * @tc.desc: GetWebAllInfosImpl.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, GetWebAllInfosImpl_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->delegate_ = nullptr;
    int32_t webId = 123;
    auto callback = [](std::shared_ptr<OHOS::Ace::JsonValue>& jsonNodeArray, int32_t receivedWebId) {};
    webPattern->GetWebAllInfosImpl(callback, webId);
#endif
}

/**
 * @tc.name: GetWebAllInfosImpl_002
 * @tc.desc: GetWebAllInfosImpl.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, GetWebAllInfosImpl_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    OHOS::Ace::SetReturnStatus("true");
    OHOS::Ace::SetComponentType("none");
    int32_t webId = 123;
    auto callback = [](std::shared_ptr<OHOS::Ace::JsonValue>& jsonNodeArray, int32_t receivedWebId) {};
    webPattern->GetWebAllInfosImpl(callback, webId);

    OHOS::Ace::SetReturnStatus("true");
    OHOS::Ace::SetComponentType("genericContainer");
    webPattern->GetWebAllInfosImpl(callback, webId);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: GetAllWebAccessibilityNodeInfos_001
 * @tc.desc: GetAllWebAccessibilityNodeInfos.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, GetAllWebAccessibilityNodeInfos_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    int32_t webId = 123;
    auto callback = [](std::shared_ptr<OHOS::Ace::JsonValue>& jsonNodeArray, int32_t receivedWebId) {};
    webPattern->GetAllWebAccessibilityNodeInfos(callback, webId);
    webPattern->GetAllWebAccessibilityNodeInfos(callback, webId, true);
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: RegisterWebComponentClickCallback_001
 * @tc.desc: RegisterWebComponentClickCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, RegisterWebComponentClickCallback_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto callback = [](int64_t id, const std::string& componentName) {};
    webPattern->RegisterWebComponentClickCallback(std::move(callback));
#endif
}

/**
 * @tc.name: UnregisterWebComponentClickCallback_001
 * @tc.desc: UnregisterWebComponentClickCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, UnregisterWebComponentClickCallback_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->UnregisterWebComponentClickCallback();
#endif
}

/**
 * @tc.name: RequestFocus_001
 * @tc.desc: RequestFocus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, RequestFocus_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->RequestFocus();
#endif
}

/**
 * @tc.name: OnRebuildFrame_001
 * @tc.desc: OnRebuildFrame.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, OnRebuildFrame_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnRebuildFrame();
#endif
}

/**
 * @tc.name: CreateOverlay_001
 * @tc.desc: CreateOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, CreateOverlay_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->imageAnalyzerManager_ = nullptr;
    RefPtr<OHOS::Ace::PixelMap> pixelMap = nullptr;
    int offsetX = 10;
    int offsetY = 20;
    int rectWidth = 30;
    int rectHeight = 40;
    int pointX = 5;
    int pointY = 6;
    webPattern->CreateOverlay(pixelMap, offsetX, offsetY, rectWidth, rectHeight, pointX, pointY);
    EXPECT_NE(webPattern->imageAnalyzerManager_->analyzerUIConfig_.onNotifySelectedStatus, nullptr);
    webPattern->imageAnalyzerManager_->analyzerUIConfig_.onNotifySelectedStatus(true);
    webPattern->imageAnalyzerManager_->analyzerUIConfig_.onNotifySelectedStatus(false);
#endif
}

/**
 * @tc.name: CreateOverlay_002
 * @tc.desc: CreateOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, CreateOverlay_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::WEB);
    RefPtr<OHOS::Ace::PixelMap> pixelMap = nullptr;
    int offsetX = 10;
    int offsetY = 20;
    int rectWidth = 30;
    int rectHeight = 40;
    int pointX = 5;
    int pointY = 6;
    webPattern->CreateOverlay(pixelMap, offsetX, offsetY, rectWidth, rectHeight, pointX, pointY);
    EXPECT_NE(webPattern->overlayCreating_, true);
#endif
}

/**
 * @tc.name: OnOverlayStateChanged_001
 * @tc.desc: OnOverlayStateChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, OnOverlayStateChanged_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->imageAnalyzerManager_ = nullptr;
    RefPtr<OHOS::Ace::PixelMap> pixelMap = nullptr;
    int offsetX = 10;
    int offsetY = 20;
    int rectWidth = 30;
    int rectHeight = 40;
    webPattern->OnOverlayStateChanged(offsetX, offsetY, rectWidth, rectHeight);
    EXPECT_EQ(webPattern->imageAnalyzerManager_->IsOverlayCreated(), false);
#endif
}

/**
 * @tc.name: OnOverlayStateChanged_002
 * @tc.desc: OnOverlayStateChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, OnOverlayStateChanged_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::WEB);
    RefPtr<OHOS::Ace::PixelMap> pixelMap = nullptr;
    int offsetX = 10;
    int offsetY = 20;
    int rectWidth = 30;
    int rectHeight = 40;
    webPattern->OnOverlayStateChanged(offsetX, offsetY, rectWidth, rectHeight);
    EXPECT_EQ(webPattern->imageAnalyzerManager_->IsOverlayCreated(), false);
#endif
}

/**
 * @tc.name: InitWebEventHubDragDropEnd001
 * @tc.desc: InitWebEventHubDragDropEnd.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, InitWebEventHubDragDropEnd001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    RefPtr<WebEventHub> gestureHub = AceType::MakeRefPtr<WebEventHub>();
    webPattern->InitWebEventHubDragDropEnd(gestureHub);
#endif
}

/**
 * @tc.name: IsImageDrag001
 * @tc.desc: IsImageDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, IsImageDrag001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    webPattern->delegate_ = nullptr;
    webPattern->IsImageDrag();
#endif
}

/**
 * @tc.name: IsImageDrag002
 * @tc.desc: IsImageDrag.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, IsImageDrag002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    webPattern->IsImageDrag();
#endif
}

/**
 * @tc.name: GetDragAcceptableStatus001
 * @tc.desc: GetDragAcceptableStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, GetDragAcceptableStatus001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    webPattern->GetDragAcceptableStatus();
#endif
}

/**
 * @tc.name: HandleDragStart001
 * @tc.desc: HandleDragStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, HandleDragStart001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    webPattern->HandleDragStart(1, 1);
#endif
}

/**
 * @tc.name: HandleOnDragEnter001
 * @tc.desc: HandleOnDragEnter.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, HandleOnDragEnter001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    WeakPtr<EventHub> eventHub = nullptr;
    RefPtr<OHOS::Ace::DragEvent> gestureHub = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    webPattern->HandleOnDragEnter(gestureHub);
#endif
}

/**
 * @tc.name: HandleOnDragEnter002
 * @tc.desc: HandleOnDragEnter.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, HandleOnDragEnter002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    RefPtr<OHOS::Ace::DragEvent> gestureHub = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    webPattern->HandleOnDragEnter(gestureHub);
#endif
}

/**
 * @tc.name: HandleOnDragDropLink001
 * @tc.desc: HandleOnDragDropLink.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, HandleOnDragDropLink001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    RefPtr<UnifiedDataMock> gestureHub = AceType::MakeRefPtr<UnifiedDataMock>();
    webPattern->HandleOnDragDropLink(gestureHub);
#endif
}

/**
 * @tc.name: HandleOnDragDropFile011
 * @tc.desc: HandleOnDragDropFile.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, HandleOnDragDropFile011, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    RefPtr<UnifiedDataMock> unifiedData = AceType::MakeRefPtr<UnifiedDataMock>();
    webPattern->HandleOnDragDropFile(unifiedData);
#endif
}

/**
 * @tc.name: HandleOnDragDrop012
 * @tc.desc: HandleOnDragDrop.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, HandleOnDragDrop012, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    RefPtr<OHOS::Ace::DragEvent> info = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    RefPtr<UnifiedDataMock> gestureHub = AceType::MakeRefPtr<UnifiedDataMock>();
    info->SetData(gestureHub);
    info->GetData();
    webPattern->HandleOnDragDrop(info);
#endif
}

/**
 * @tc.name: HandleOnDragLeave013
 * @tc.desc: HandleOnDragLeave.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, HandleOnDragLeave013, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    webPattern->HandleOnDragLeave(0, 0);
#endif
}

/**
 * @tc.name: GetDragPixelMapSize_001
 * @tc.desc: GetDragPixelMapSize.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, GetDragPixelMapSize_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    webPattern->GetDragPixelMapSize();
#endif
}

/**
 * @tc.name: GetDragPixelMapSize_002
 * @tc.desc: GetDragPixelMapSize.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, GetDragPixelMapSize_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    auto size = webpattern.GetDragPixelMapSize();
    EXPECT_EQ(size.Width(), 0);
#endif
}

/**
 * @tc.name: HandleDoubleClickEvent_001
 * @tc.desc: HandleDoubleClickEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, HandleDoubleClickEvent_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::NONE);
    std::queue<MouseClickInfo> empty;
    swap(empty, webPattern->mouseClickQueue_);
    webPattern->HandleDoubleClickEvent(info);
#endif
}

/**
 * @tc.name: HandleDoubleClickEvent_002
 * @tc.desc: HandleDoubleClickEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, HandleDoubleClickEvent_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::NONE);
    std::queue<MouseClickInfo> clickInfos;
    MouseClickInfo mouseInfo;
    mouseInfo.x = 1;
    mouseInfo.y = 1;
    clickInfos.push(mouseInfo);
    swap(clickInfos, webPattern->mouseClickQueue_);
    webPattern->HandleDoubleClickEvent(info);
#endif
}

/**
 * @tc.name: HandleDoubleClickEvent_003
 * @tc.desc: HandleDoubleClickEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, HandleDoubleClickEvent_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    MouseInfo info;
    webPattern->HandleDoubleClickEvent(info);
#endif
}

/**
 * @tc.name: HandleOnDragStart_001
 * @tc.desc: HandleOnDragStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, HandleOnDragStart_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<OHOS::Ace::DragEvent> info = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    webPattern->HandleOnDragStart(info);
#endif
}

/**
 * @tc.name: OnDragFileNameStart_001
 * @tc.desc: OnDragFileNameStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, OnDragFileNameStart_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<UnifiedDataMock> aceUnifiedData = AceType::MakeRefPtr<UnifiedDataMock>();
    EXPECT_NE(aceUnifiedData, nullptr);
    auto mockUdmfClient = AceType::DynamicCast<MockUdmfClient>(UdmfClient::GetInstance());
    EXPECT_NE(mockUdmfClient, nullptr);
    EXPECT_CALL(
        *mockUdmfClient, AddFileUriRecord(AceType::DynamicCast<UnifiedData>(aceUnifiedData),
                             ElementsAreArray({ "file:///data/storage/el2/base/haps/entry/temp/dragdrop/test.txt" })))
        .WillOnce(Return(false));
    webPattern->OnDragFileNameStart(aceUnifiedData, "test.txt");
#endif
}

/**
 * @tc.name: HandleOnDropMove_001
 * @tc.desc: HandleOnDragStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, HandleOnDropMove_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<OHOS::Ace::DragEvent> info = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    webPattern->HandleOnDropMove(info);
#endif
}

/**
 * @tc.name: InitCommonDragDropEvent_001
 * @tc.desc: InitCommonDragDropEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, InitCommonDragDropEvent_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    WeakPtr<EventHub> eventHub = nullptr;
    RefPtr<GestureEventHub> info = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    webPattern->InitCommonDragDropEvent(info);
#endif
}

/**
 * @tc.name: InitWebEventHubDragDropStart_001
 * @tc.desc: InitWebEventHubDragDropStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, InitWebEventHubDragDropStart_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<OHOS::Ace::NG::WebEventHub> info = AceType::MakeRefPtr<OHOS::Ace::NG::WebEventHub>();
    webPattern->InitWebEventHubDragDropStart(info);
#endif
}

/**
 * @tc.name: InitWebEventHubDragMove_001
 * @tc.desc: InitWebEventHubDragMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTouchTestNg, InitWebEventHubDragMove_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<OHOS::Ace::NG::WebEventHub> info = AceType::MakeRefPtr<OHOS::Ace::NG::WebEventHub>();
    webPattern->InitWebEventHubDragMove(info);
#endif
}
} // namespace OHOS::Ace::NG