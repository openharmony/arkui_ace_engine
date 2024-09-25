/*
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

#include "gtest/gtest.h"
#define protected public
#define private public
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#undef private
#undef protected
#include "test/mock/core/common/mock_image_analyzer_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#define private public
#include "test/mock/base/mock_task_executor.h"

#include "base/web/webview/ohos_nweb/include/nweb_handler.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_pattern.cpp"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/utils/system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class WebPatternTestNgSupplement : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternTestNgSupplement::SetUpTestCase() {}
void WebPatternTestNgSupplement::TearDownTestCase() {}

void WebPatternTestNgSupplement::SetUp()
{
    MockPipelineContext::SetUp();
}

void WebPatternTestNgSupplement::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ParseDateTimeJson_001
 * @tc.desc: ParseDateTimeJson.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, ParseDateTimeJson_001, TestSize.Level1)
{
    NWeb::DateTime result;
    std::string testJson = R"({"year":2023,"month":10,"day":5,"hour":12,"minute":30})";

    bool ret = ParseDateTimeJson(testJson, result);

    ASSERT_TRUE(ret);
    ASSERT_EQ(result.year, 2023);
    ASSERT_EQ(result.month, 10);
    ASSERT_EQ(result.day, 5);
    ASSERT_EQ(result.hour, 12);
    ASSERT_EQ(result.minute, 30);
}

/**
 * @tc.name: ParseDateTimeJson_002
 * @tc.desc: ParseDateTimeJson.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, ParseDateTimeJson_002, TestSize.Level1)
{
    NWeb::DateTime result;
    std::string testJson = "";

    bool ret = ParseDateTimeJson(testJson, result);
    ASSERT_FALSE(ret);
}

/**
 * @tc.name: ParseDateTimeJson_003
 * @tc.desc: ParseDateTimeJson.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, ParseDateTimeJson_003, TestSize.Level1)
{
    NWeb::DateTime result;
    std::string testJson = R"({"year":"","month":"","day":"","hour":"","minute":""})";
    bool ret = ParseDateTimeJson(testJson, result);
    ASSERT_TRUE(ret);
}

/**
 * @tc.name: ParseTextJsonValue_001
 * @tc.desc: ParseTextJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, ParseTextJsonValue_001, TestSize.Level1)
{
    std::string jsonInput = R"({"value": "testString"})";
    std::string expectedOutput = "testString";

    EXPECT_EQ(ParseTextJsonValue(jsonInput), expectedOutput);
}

/**
 * @tc.name: ParseTextJsonValue_002
 * @tc.desc: ParseTextJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, ParseTextJsonValue_002, TestSize.Level1)
{
    std::string jsonInput = R"({"value": null})";
    EXPECT_EQ(ParseTextJsonValue(jsonInput), "");
}

/**
 * @tc.name: ParseTextJsonValue_003
 * @tc.desc: ParseTextJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, ParseTextJsonValue_003, TestSize.Level1)
{
    std::string jsonInput = "";
    EXPECT_EQ(ParseTextJsonValue(jsonInput), "");
}

/**
 * @tc.name: OnAttachToFrameNode_001
 * @tc.desc: OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnAttachToFrameNode_001, TestSize.Level1)
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
    webPattern->renderContextForSurface_ = nullptr;
    webPattern->renderContextForPopupSurface_ = nullptr;

    webPattern->OnAttachToFrameNode();
    EXPECT_NE(webPattern->renderContextForSurface_, nullptr);
    EXPECT_NE(webPattern->renderContextForPopupSurface_, nullptr);
#endif
}

/**
 * @tc.name: OnDetachFromFrameNode_001
 * @tc.desc: OnDetachFromFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnDetachFromFrameNode_001, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;

    auto pattern = AceType::MakeRefPtr<Pattern>();
    FrameNode node("exampleTag", 1, pattern, true, false);
    webPattern->transformHintChangedCallbackId_.reset();
    webPattern->OnDetachFromFrameNode(&node);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: getZoomOffset_001
 * @tc.desc: getZoomOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, getZoomOffset_001, TestSize.Level1)
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

    double scale = 2.0;
    double ret = webPattern->getZoomOffset(scale);
    EXPECT_EQ(ret, 0.0);
#endif
}

/**
 * @tc.name: getZoomOffset_002
 * @tc.desc: getZoomOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, getZoomOffset_002, TestSize.Level1)
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

    double scale = 0.0;
    double ret = webPattern->getZoomOffset(scale);
    EXPECT_NE(ret, 0.0);
#endif
}

/**
 * @tc.name: HandleScaleGestureChange_001
 * @tc.desc: HandleScaleGestureChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, HandleScaleGestureChange_001, TestSize.Level1)
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
    GestureEvent event;
    event.SetScale(0);
    webPattern->zoomStatus_ = 3;
    webPattern->zoomErrorCount_ = 5;
    webPattern->preScale_ = 1.0;
    webPattern->zoomOutSwitch_ = false;
    webPattern->startPageScale_ = 5.0;

    webPattern->HandleScaleGestureChange(event);
    EXPECT_EQ(webPattern->zoomErrorCount_, 0);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentStart001
 * @tc.desc: JavaScriptOnDocumentStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, JavaScriptOnDocumentStart001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "groupp";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webpattern.JavaScriptOnDocumentStart(scriptItems);
    EXPECT_EQ(webpattern.delegate_, nullptr);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentEnd002
 * @tc.desc: JavaScriptOnDocumentEnd.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, JavaScriptOnDocumentEnd002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "groupp";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webpattern.JavaScriptOnDocumentEnd(scriptItems);
    EXPECT_EQ(webpattern.delegate_, nullptr);
#endif
}

/**
 * @tc.name: UpdateJavaScriptOnDocumentStart003
 * @tc.desc: UpdateJavaScriptOnDocumentStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, UpdateJavaScriptOnDocumentStart003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "groupp";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webpattern.JavaScriptOnDocumentStart(scriptItems);
    webpattern.UpdateJavaScriptOnDocumentStart();
    EXPECT_EQ(webpattern.delegate_, nullptr);
#endif
}

/**
 * @tc.name: UpdateJavaScriptOnDocumentEnd004
 * @tc.desc: UpdateJavaScriptOnDocumentEnd.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, UpdateJavaScriptOnDocumentEnd004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "groupp";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webpattern.JavaScriptOnDocumentEnd(scriptItems);
    webpattern.UpdateJavaScriptOnDocumentEnd();
    EXPECT_EQ(webpattern.delegate_, nullptr);
#endif
}

/**
 * @tc.name: UpdateSlideOffset003
 * @tc.desc: UpdateSlideOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, UpdateSlideOffset003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->syncAxis_ = Axis::NONE;
    webPattern->UpdateSlideOffset();
#endif
}

/**
 * @tc.name: CalculateHorizontalDrawRect001
 * @tc.desc: CalculateHorizontalDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, CalculateHorizontalDrawRect001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->fitContentOffset_.SetX(-10);
    webPattern->isNeedReDrawRect_ = false;
    webPattern->CalculateHorizontalDrawRect();
    EXPECT_FALSE(webPattern->isNeedReDrawRect_);
#endif
}

/**
 * @tc.name: CalculateHorizontalDrawRect002
 * @tc.desc: CalculateHorizontalDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, CalculateHorizontalDrawRect002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->isNeedReDrawRect_ = true;
    webPattern->CalculateHorizontalDrawRect();
    EXPECT_FALSE(webPattern->isNeedReDrawRect_);
#endif
}

/**
 * @tc.name: CalculateVerticalDrawRect001
 * @tc.desc: CalculateVerticalDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, CalculateVerticalDrawRect001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->fitContentOffset_.SetY(-10);
    webPattern->isNeedReDrawRect_ = false;
    webPattern->CalculateVerticalDrawRect();
    EXPECT_FALSE(webPattern->isNeedReDrawRect_);
#endif
}

/**
 * @tc.name: CalculateVerticalDrawRect002
 * @tc.desc: CalculateVerticalDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, CalculateVerticalDrawRect002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->isNeedReDrawRect_ = true;
    webPattern->CalculateVerticalDrawRect();
    EXPECT_FALSE(webPattern->isNeedReDrawRect_);
#endif
}

/**
 * @tc.name: SetDrawRect002
 * @tc.desc: SetDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, SetDrawRect002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->SetDrawRect(10, 20, 0, 0);

    EXPECT_EQ(webPattern->drawRectWidth_, 0);
    EXPECT_EQ(webPattern->drawRectHeight_, 0);
#endif
}

/**
 * @tc.name: GetPendingSizeStatus002
 * @tc.desc: GetPendingSizeStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, GetPendingSizeStatus002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;
    EXPECT_FALSE(webPattern->GetPendingSizeStatus());
#endif
}

/**
 * @tc.name: GetPendingSizeStatus003
 * @tc.desc: GetPendingSizeStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, GetPendingSizeStatus003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ =
        AceType::MakeRefPtr<WebDelegate>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    EXPECT_FALSE(webPattern->GetPendingSizeStatus());
#endif
}

/**
 * @tc.name: GetAccessibilityNodeById004
 * @tc.desc: GetAccessibilityNodeById.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, GetAccessibilityNodeById004, TestSize.Level1)
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
    int32_t accessibilityId = 1;
    webPattern->accessibilityState_ = false;
    auto ret = webPattern->GetAccessibilityNodeById(accessibilityId);
    EXPECT_EQ(ret, nullptr);
#endif
}

/**
 * @tc.name: GetFocusedAccessibilityNode005
 * @tc.desc: GetFocusedAccessibilityNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, GetFocusedAccessibilityNode005, TestSize.Level1)
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
    int32_t accessibilityId = 1;
    bool isAccessibilityFocus = true;
    webPattern->accessibilityState_ = false;
    auto ret = webPattern->GetFocusedAccessibilityNode(accessibilityId, isAccessibilityFocus);
    EXPECT_EQ(ret, nullptr);
#endif
}

/**
 * @tc.name: GetAccessibilityNodeByFocusMove006
 * @tc.desc: GetAccessibilityNodeByFocusMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, GetAccessibilityNodeByFocusMove006, TestSize.Level1)
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
    int32_t accessibilityId = 1;
    int32_t direction = 1;
    webPattern->accessibilityState_ = false;
    auto ret = webPattern->GetAccessibilityNodeByFocusMove(accessibilityId, direction);
    EXPECT_EQ(ret, nullptr);
#endif
}

/**
 * @tc.name: SetAccessibilityState001
 * @tc.desc: SetAccessibilityState.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, SetAccessibilityState001, TestSize.Level1)
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
    webPattern->accessibilityState_ = false;
    webPattern->SetAccessibilityState(true);
    EXPECT_TRUE(webPattern->accessibilityState_);
#endif
}

/**
 * @tc.name: ClearFocusedAccessibilityId001
 * @tc.desc: ClearFocusedAccessibilityId.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, ClearFocusedAccessibilityId001, TestSize.Level1)
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
    webPattern->accessibilityState_ = false;
    webPattern->ClearFocusedAccessibilityId();
    EXPECT_EQ(webPattern->focusedAccessibilityId_, -1);
#endif
}

/**
 * @tc.name: ClearFocusedAccessibilityId002
 * @tc.desc: ClearFocusedAccessibilityId.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, ClearFocusedAccessibilityId002, TestSize.Level1)
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
    webPattern->accessibilityState_ = true;
    webPattern->ClearFocusedAccessibilityId();
    EXPECT_EQ(webPattern->focusedAccessibilityId_, -1);
#endif
}

/**
 * @tc.name: GetAccessibilityFocusRect001
 * @tc.desc: GetAccessibilityFocusRect.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, GetAccessibilityFocusRect001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->delegate_ =
        AceType::MakeRefPtr<WebDelegate>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    webPattern->accessibilityState_ = true;
    RectT<int32_t> paintRect;
    EXPECT_FALSE(webPattern->GetAccessibilityFocusRect(paintRect, 12345));
#endif
}

/**
 * @tc.name: SetTouchEventInfo001
 * @tc.desc: SetTouchEventInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, SetTouchEventInfo001, TestSize.Level1)
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
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::MOVE;
    touchEvent.x = 100.0f;
    touchEvent.y = 100.0f;
    TouchEventInfo touchEventInfo { "touchEvent" };

    webPattern->touchEventQueue_.push(touchEventInfo);
    webPattern->SetTouchEventInfo(touchEvent, touchEventInfo, "embedId");
    EXPECT_FALSE(webPattern->touchEventQueue_.empty());
#endif
}

/**
 * @tc.name: SetTouchEventInfo002
 * @tc.desc: SetTouchEventInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, SetTouchEventInfo002, TestSize.Level1)
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
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::DOWN;
    touchEvent.x = 100.0f;
    touchEvent.y = 100.0f;

    EventTarget target;
    TouchEventInfo touchEventInfo { "touchEvent" };
    TouchLocationInfo touchLocationInfo(1);
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    webPattern->touchEventQueue_.push(touchEventInfo);
    webPattern->SetTouchEventInfo(touchEvent, touchEventInfo, "embedId");
    EXPECT_TRUE(webPattern->touchEventQueue_.empty());
#endif
}

/**
 * @tc.name: SetTouchEventInfo003
 * @tc.desc: SetTouchEventInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, SetTouchEventInfo003, TestSize.Level1)
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

    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::UP;
    touchEvent.x = 100.0f;
    touchEvent.y = 100.0f;

    TouchEventInfo touchEventInfo { "touchEvent" };
    TouchLocationInfo touchLocationInfo(2);
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    webPattern->touchEventQueue_.push(touchEventInfo);
    webPattern->SetTouchEventInfo(touchEvent, touchEventInfo, "embedId");
    EXPECT_TRUE(webPattern->touchEventQueue_.empty());
#endif
}

/**
 * @tc.name: OnVisibleAreaChangeTest001
 * @tc.desc: OnVisibleAreaChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnVisibleAreaChangeTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto webPatternFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    stack->Push(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->OnVisibleAreaChange(true);
    ASSERT_EQ(webPattern->isVisible_, true);
#endif
}

/**
 * @tc.name: OnVisibleAreaChangeTest002
 * @tc.desc: OnVisibleAreaChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnVisibleAreaChangeTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto webPatternFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    stack->Push(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->isVisibleActiveEnable_ = true;
    webPattern->OnVisibleAreaChange(false);
    ASSERT_EQ(webPattern->isVisible_, false);
#endif
}

/**
 * @tc.name: OnVisibleAreaChangeTest003
 * @tc.desc: OnVisibleAreaChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnVisibleAreaChangeTest003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto webPatternFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    stack->Push(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->isVisible_ = false;
    webPattern->isVisibleActiveEnable_ = true;
    webPattern->OnVisibleAreaChange(true);
    ASSERT_EQ(webPattern->isVisible_, true);
#endif
}

/**
 * @tc.name: OnAttachToBuilderNodeTest001
 * @tc.desc: OnAttachToBuilderNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnAttachToBuilderNodeTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto webPatternFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    stack->Push(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->offlineWebInited_ = false;
    webPattern->OnAttachToBuilderNode(NodeStatus::NORMAL_NODE);
    ASSERT_EQ(webPattern->offlineWebInited_, false);
#endif
}

/**
 * @tc.name: OnAttachToBuilderNodeTest002
 * @tc.desc: OnAttachToBuilderNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnAttachToBuilderNodeTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto webPatternFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    stack->Push(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->delegate_ =
        AceType::MakeRefPtr<WebDelegate>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    webPattern->OnAttachToBuilderNode(NodeStatus::BUILDER_NODE_OFF_MAINTREE);
    ASSERT_EQ(webPattern->offlineWebInited_, true);
#endif
}

/**
 * @tc.name: OnNotifyMemoryLevelTest001
 * @tc.desc: OnNotifyMemoryLevel.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnNotifyMemoryLevelTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto webPatternFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    stack->Push(webPatternFrameNode);
    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->isMemoryLevelEnable_ = true;
    webPattern->delegate_ =
        AceType::MakeRefPtr<WebDelegate>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    webPattern->OnNotifyMemoryLevel(0);
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->isMemoryLevelEnable_ = false;
    webPattern->OnNotifyMemoryLevel(0);
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: OnNotifyMemoryLevelTest002
 * @tc.desc: OnNotifyMemoryLevel.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnNotifyMemoryLevelTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto webPatternFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    stack->Push(webPatternFrameNode);
    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->isMemoryLevelEnable_ = false;
    webPattern->delegate_ =
        AceType::MakeRefPtr<WebDelegate>(PipelineContext::GetCurrentContext(), nullptr, "", Container::CurrentId());
    webPattern->OnNotifyMemoryLevel(0);
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: GetSystemColorTest001
 * @tc.desc: GetSystemColor.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, GetSystemColorTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto webPatternFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    stack->Push(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    auto color = webPattern->GetSystemColor();
    ASSERT_NE(color, Color::GREEN);
#endif
}

/**
 * @tc.name: HandleScrollVelocityTest001
 * @tc.desc: HandleScrollVelocity.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, HandleScrollVelocityTest001, TestSize.Level1)
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
    RefPtr<MockNestableScrollContainer> parent = AccessibilityManager::MakeRefPtr<MockNestableScrollContainer>();
    webPattern->SetNestedScrollParent(parent);
    EXPECT_CALL(*parent, HandleScrollVelocity).Times(1).WillOnce(Return(true));
    EXPECT_TRUE(webPattern->HandleScrollVelocity(parent, 1.f));
#endif
}

/**
 * @tc.name: OnOverScrollFlingVelocityTest001
 * @tc.desc: OnOverScrollFlingVelocity.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnOverScrollFlingVelocityTest001, TestSize.Level1)
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
    webPattern->isNeedUpdateScrollAxis_ = true;
    webPattern->OnOverScrollFlingVelocity(1.0f, 2.0f, true);
    EXPECT_FALSE(webPattern->isFlingReachEdge_.atStart);
    EXPECT_FALSE(webPattern->isFlingReachEdge_.atEnd);
    webPattern->isNeedUpdateScrollAxis_ = false;
    webPattern->OnOverScrollFlingVelocity(1.0f, 2.0f, true);
    EXPECT_TRUE(webPattern->isFlingReachEdge_.atStart);
    EXPECT_FALSE(webPattern->isFlingReachEdge_.atEnd);
    webPattern->OnOverScrollFlingVelocity(1.0f, 2.0f, false);
    EXPECT_TRUE(webPattern->isFlingReachEdge_.atStart);
    EXPECT_FALSE(webPattern->isFlingReachEdge_.atEnd);
    webPattern->OnOverScrollFlingVelocity(-1.0f, -2.0f, true);
    EXPECT_TRUE(webPattern->isFlingReachEdge_.atStart);
    EXPECT_TRUE(webPattern->isFlingReachEdge_.atEnd);
    webPattern->OnOverScrollFlingVelocity(-1.0f, -2.0f, true);
    EXPECT_TRUE(webPattern->isFlingReachEdge_.atStart);
    EXPECT_TRUE(webPattern->isFlingReachEdge_.atEnd);
#endif
}

/**
 * @tc.name: OnOverScrollFlingVelocityHandlerTest001
 * @tc.desc: OnOverScrollFlingVelocityHandler.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnOverScrollFlingVelocityHandlerTest001, TestSize.Level1)
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
    webPattern->isFirstFlingScrollVelocity_ = true;
    webPattern->scrollState_ = true;
    webPattern->OnOverScrollFlingVelocityHandler(1.0f, false);
    ASSERT_TRUE(webPattern->isFirstFlingScrollVelocity_);
    webPattern->scrollState_ = false;
    webPattern->OnOverScrollFlingVelocityHandler(1.0f, true);
    ASSERT_TRUE(webPattern->isFirstFlingScrollVelocity_);
#endif
}

/**
 * @tc.name: OnScrollStateTest001
 * @tc.desc: OnScrollState.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnScrollStateTest001, TestSize.Level1)
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
    webPattern->OnScrollState(true);
    EXPECT_TRUE(webPattern->scrollState_);
    auto imageAnalyzerManager = std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::WEB);
    webPattern->imageAnalyzerManager_ = imageAnalyzerManager;
    webPattern->OnScrollState(false);
    EXPECT_FALSE(webPattern->scrollState_);
#endif
}

/**
 * @tc.name: ReleaseResizeHoldTest001
 * @tc.desc: ReleaseResizeHold.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, ReleaseResizeHoldTest001, TestSize.Level1)
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

    webPattern->layoutMode_ = WebLayoutMode::NONE;
    webPattern->rootLayerChangeSize_ = Size(100, 200);
    webPattern->ReleaseResizeHold();
    EXPECT_NE(webPattern->rootLayerChangeSize_.width_, webPattern->drawSize_.width_);
    EXPECT_NE(webPattern->rootLayerChangeSize_.height_, webPattern->drawSize_.height_);
#endif
}

/**
 * @tc.name: GetParentAxisTest001
 * @tc.desc: GetParentAxis.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, GetParentAxisTest001, TestSize.Level1)
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

    RefPtr<MockNestableScrollContainer> parent = AccessibilityManager::MakeRefPtr<MockNestableScrollContainer>();
    webPattern->SetNestedScrollParent(parent);
    EXPECT_CALL(*parent, GetAxis()).WillRepeatedly(testing::Return(Axis::HORIZONTAL));
    webPattern->axis_ = Axis::VERTICAL;
    webPattern->GetParentAxis();
    EXPECT_EQ(webPattern->axis_, Axis::HORIZONTAL);
#endif
}

/**
 * @tc.name: SetNestedScrollExtTest001
 * @tc.desc: SetNestedScrollExt.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, SetNestedScrollExtTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, [] { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    NestedScrollOptionsExt nestedScroll;
    nestedScroll.scrollUp = NestedScrollMode::SELF_ONLY;
    nestedScroll.scrollLeft = NestedScrollMode::SELF_ONLY;

    nestedScroll.scrollDown = NestedScrollMode::SELF_ONLY;
    nestedScroll.scrollRight = NestedScrollMode::SELF_ONLY;
    webPattern->SetNestedScrollExt(nestedScroll);
    EXPECT_EQ(webPattern->nestedScroll_.scrollUp, nestedScroll.scrollUp);
    EXPECT_EQ(webPattern->nestedScroll_.scrollLeft, nestedScroll.scrollLeft);
    EXPECT_EQ(webPattern->nestedScroll_.scrollDown, nestedScroll.scrollDown);
    EXPECT_EQ(webPattern->nestedScroll_.scrollRight, nestedScroll.scrollRight);
#endif
}

/**
 * @tc.name: OnRootLayerChangedTest001
 * @tc.desc: OnRootLayerChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnRootLayerChangedTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->layoutMode_ = WebLayoutMode::NONE;
    webPattern->OnRootLayerChanged(200, 300);
    EXPECT_EQ(webPattern->rootLayerWidth_, 200);
    EXPECT_EQ(webPattern->rootLayerHeight_, 300);
#endif
}

/**
 * @tc.name: OnRootLayerChangedTest002
 * @tc.desc: OnRootLayerChanged.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnRootLayerChangedTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->rootLayerWidth_ = 200;
    webPattern->rootLayerHeight_ = 300;
    webPattern->OnRootLayerChanged(200, 300);
    EXPECT_TRUE((webPattern->rootLayerWidth_ == 200) && (webPattern->rootLayerHeight_ == 300));
#endif
}

/**
 * @tc.name: SetLayoutModeTest001
 * @tc.desc: SetLayoutMode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, SetLayoutModeTest001, TestSize.Level1)
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
    auto mode = static_cast<OHOS::Ace::WebLayoutMode>(WebLayoutMode::FIT_CONTENT);
    webPattern->SetLayoutMode(mode);
    EXPECT_EQ(webPattern->layoutMode_, mode);
#endif
}

/**
 * @tc.name: FilterScrollEventHandlevVlocity_001
 * @tc.desc: FilterScrollEventHandlevVlocity.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, FilterScrollEventHandlevVlocity_001, TestSize.Level1)
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

    RefPtr<MockNestableScrollContainer> parent = AccessibilityManager::MakeRefPtr<MockNestableScrollContainer>();
    webPattern->parentsMap_ = { { Axis::HORIZONTAL, parent } };
    webPattern->expectedScrollAxis_ = Axis::HORIZONTAL;
    webPattern->nestedScroll_.scrollLeft = NestedScrollMode::PARENT_FIRST;
    webPattern->isParentReachEdge_ = true;
    webPattern->isFlingReachEdge_.atStart = false;
    webPattern->SetNestedScrollParent(parent);
    EXPECT_FALSE(webPattern->FilterScrollEventHandlevVlocity(2.0f));
#endif
}

/**
 * @tc.name: FilterScrollEventHandlevVlocity_002
 * @tc.desc: FilterScrollEventHandlevVlocity.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, FilterScrollEventHandlevVlocity_002, TestSize.Level1)
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

    RefPtr<MockNestableScrollContainer> parent = AccessibilityManager::MakeRefPtr<MockNestableScrollContainer>();
    webPattern->parentsMap_ = { { Axis::HORIZONTAL, parent } };
    webPattern->expectedScrollAxis_ = Axis::HORIZONTAL;
    webPattern->nestedScroll_.scrollLeft = NestedScrollMode::PARENT_FIRST;
    webPattern->SetNestedScrollParent(parent);
    EXPECT_CALL(*parent, HandleScrollVelocity).Times(1).WillOnce(Return(true));
    EXPECT_TRUE(webPattern->FilterScrollEventHandlevVlocity(2.0f));
#endif
}

/**
 * @tc.name: FilterScrollEventHandlevVlocity_003
 * @tc.desc: FilterScrollEventHandlevVlocity.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, FilterScrollEventHandlevVlocity_003, TestSize.Level1)
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

    RefPtr<MockNestableScrollContainer> parent = AccessibilityManager::MakeRefPtr<MockNestableScrollContainer>();
    webPattern->parentsMap_ = { { Axis::HORIZONTAL, parent } };
    webPattern->expectedScrollAxis_ = Axis::HORIZONTAL;
    webPattern->nestedScroll_.scrollUp = NestedScrollMode::PARENT_FIRST;
    webPattern->SetNestedScrollParent(parent);
    EXPECT_FALSE(webPattern->FilterScrollEventHandlevVlocity(2.0f));
#endif
}

/**
 * @tc.name: UpdateFlingReachEdgeState_001
 * @tc.desc: UpdateFlingReachEdgeState.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, UpdateFlingReachEdgeState_001, TestSize.Level1)
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

    webPattern->isFlingReachEdge_.atStart = false;
    webPattern->UpdateFlingReachEdgeState(0.0f, true);
    EXPECT_FALSE(webPattern->isFlingReachEdge_.atStart);

    webPattern->isFlingReachEdge_.atStart = false;
    webPattern->UpdateFlingReachEdgeState(-1.0f, true);
    EXPECT_FALSE(webPattern->isFlingReachEdge_.atStart);

    webPattern->isFlingReachEdge_.atStart = true;
    webPattern->UpdateFlingReachEdgeState(0.0f, false);
    EXPECT_TRUE(webPattern->isFlingReachEdge_.atStart);

    webPattern->isFlingReachEdge_.atStart = true;
    webPattern->UpdateFlingReachEdgeState(-1.0f, false);
    EXPECT_FALSE(webPattern->isFlingReachEdge_.atStart);
#endif
}

/**
 * @tc.name: InitSlideUpdateListener_001
 * @tc.desc: InitSlideUpdateListener.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, InitSlideUpdateListener_001, TestSize.Level1)
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

    RefPtr<FrameNode> node =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    node->tag_ = "Web";
    frameNode->SetParent(node);
    webPattern->InitSlideUpdateListener();
    EXPECT_NE(webPattern->renderSurface_, nullptr);
#endif
}

/**
 * @tc.name: UpdateFocusedAccessibilityId_001
 * @tc.desc: UpdateFocusedAccessibilityId.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, UpdateFocusedAccessibilityId_001, TestSize.Level1)
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

    webPattern->accessibilityState_ = true;
    webPattern->UpdateFocusedAccessibilityId(100);
    EXPECT_EQ(webPattern->focusedAccessibilityId_, 100);
#endif
}

/**
 * @tc.name: UpdateFocusedAccessibilityId_002
 * @tc.desc: UpdateFocusedAccessibilityId.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, UpdateFocusedAccessibilityId_002, TestSize.Level1)
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

    webPattern->accessibilityState_ = true;
    webPattern->UpdateFocusedAccessibilityId(101);
    EXPECT_EQ(webPattern->focusedAccessibilityId_, 101);
#endif
}

/**
 * @tc.name: UpdateFocusedAccessibilityId_003
 * @tc.desc: UpdateFocusedAccessibilityId.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, UpdateFocusedAccessibilityId_003, TestSize.Level1)
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

    webPattern->focusedAccessibilityId_ = -1;
    webPattern->accessibilityState_ = true;
    webPattern->UpdateFocusedAccessibilityId(-1);
    RectT<int32_t> rect;
    EXPECT_FALSE(webPattern->GetAccessibilityFocusRect(rect, -1));
#endif
}

/**
 * @tc.name: UpdateFocusedAccessibilityId_004
 * @tc.desc: UpdateFocusedAccessibilityId.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, UpdateFocusedAccessibilityId_004, TestSize.Level1)
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

    webPattern->focusedAccessibilityId_ = -1;
    webPattern->accessibilityState_ = true;
    webPattern->UpdateFocusedAccessibilityId(-2);
    RectT<int32_t> rect;
    EXPECT_TRUE(webPattern->GetAccessibilityFocusRect(rect, -2));
#endif
}

/**
 * @tc.name: SearchParentTest001
 * @tc.desc: SearchParent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, SearchParentTest001, TestSize.Level1)
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

    RefPtr<FrameNode> node =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    frameNode->SetParent(node);
    auto nodepattern = node->GetPattern<WebPattern>();
    nodepattern->axis_ = Axis::NONE;
    EXPECT_NE(webPattern->SearchParent(Axis::NONE), nullptr);
    nodepattern->axis_ = Axis::VERTICAL;
    EXPECT_NE(webPattern->SearchParent(Axis::NONE), nullptr);
    nodepattern->axis_ = Axis::VERTICAL;
    EXPECT_NE(webPattern->SearchParent(Axis::VERTICAL), nullptr);
    nodepattern->axis_ = Axis::NONE;
    EXPECT_EQ(webPattern->SearchParent(Axis::VERTICAL), nullptr);
#endif
}
} // namespace OHOS::Ace::NG
