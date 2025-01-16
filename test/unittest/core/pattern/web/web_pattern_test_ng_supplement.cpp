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
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/utils/system_properties.h"
#include "test/unittest/core/pattern/web/mock_web_delegate.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class WebContextMenuParamShow : public WebContextMenuParam {
public:
    MOCK_METHOD(int32_t, GetXCoord, (), (const, override));
    MOCK_METHOD(int32_t, GetYCoord, (), (const, override));
    MOCK_METHOD(std::string, GetLinkUrl, (), (const, override));
    MOCK_METHOD(std::string, GetUnfilteredLinkUrl, (), (const, override));
    MOCK_METHOD(std::string, GetSourceUrl, (), (const, override));
    MOCK_METHOD(bool, HasImageContents, (), (const, override));
    MOCK_METHOD(bool, IsEditable, (), (const, override));
    MOCK_METHOD(int, GetEditStateFlags, (), (const, override));
    MOCK_METHOD(int, GetSourceType, (), (const, override));
    MOCK_METHOD(int, GetMediaType, (), (const, override));
    MOCK_METHOD(int, GetInputFieldType, (), (const, override));
    MOCK_METHOD(std::string, GetSelectionText, (), (const, override));
};

class ContextMenuResultShow : public ContextMenuResult {
    DECLARE_ACE_TYPE(ContextMenuResultShow, ContextMenuResult);
public:
    ContextMenuResultShow() = default;
    ~ContextMenuResultShow() override = default;

    MOCK_METHOD(void, Cancel, (), (const, override));
    MOCK_METHOD(void, CopyImage, (), (const, override));
    MOCK_METHOD(void, Copy, (), (const, override));
    MOCK_METHOD(void, Paste, (), (const, override));
    MOCK_METHOD(void, Cut, (), (const, override));
    MOCK_METHOD(void, SelectAll, (), (const, override));
};
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
    OHOS::Ace::SetReturnStatus("");
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
    EXPECT_EQ(webPattern->renderContextForPopupSurface_, nullptr);
#endif
}

/**
 * @tc.name: OnAttachToFrameNode_002
 * @tc.desc: OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnAttachToFrameNode_002, TestSize.Level1)
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
    webPattern->renderContextForSurface_ = RenderContext::Create();
    webPattern->renderContextForPopupSurface_ = RenderContext::Create();
    webPattern->OnAttachToFrameNode();
    EXPECT_TRUE(webPattern->transformHintChangedCallbackId_.has_value());
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
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->textBlurAccessibilityEnable_ = true;
    auto pattern = AceType::MakeRefPtr<Pattern>();
    FrameNode node("exampleTag", 1, pattern, true, false);
    webPattern->transformHintChangedCallbackId_ = 1;
    webPattern->OnDetachFromFrameNode(&node);
    EXPECT_TRUE(webPattern->transformHintChangedCallbackId_.has_value());
    webPattern->transformHintChangedCallbackId_.reset();
    webPattern->OnDetachFromFrameNode(&node);
    EXPECT_FALSE(webPattern->transformHintChangedCallbackId_.has_value());

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
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnDocumentStart(scriptItems);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentEnd001
 * @tc.desc: JavaScriptOnDocumentEnd.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, JavaScriptOnDocumentEnd001, TestSize.Level1)
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
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnDocumentEnd(scriptItems);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: UpdateJavaScriptOnDocumentStart001
 * @tc.desc: UpdateJavaScriptOnDocumentStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, UpdateJavaScriptOnDocumentStart001, TestSize.Level1)
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

    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->onDocumentStartScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->UpdateJavaScriptOnDocumentStart();
    EXPECT_FALSE(webPattern->onDocumentStartScriptItems_.has_value());
    webPattern->UpdateJavaScriptOnDocumentStart();
    webPattern->delegate_ = nullptr;
    webPattern->UpdateJavaScriptOnDocumentStart();
    webPattern->onDocumentStartScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->UpdateJavaScriptOnDocumentStart();
    EXPECT_TRUE(webPattern->onDocumentStartScriptItems_.has_value());
#endif
}

/**
 * @tc.name: UpdateJavaScriptOnDocumentEnd004
 * @tc.desc: UpdateJavaScriptOnDocumentEnd.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, UpdateJavaScriptOnDocumentEnd001, TestSize.Level1)
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

    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->onDocumentEndScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->UpdateJavaScriptOnDocumentEnd();
    EXPECT_FALSE(webPattern->onDocumentEndScriptItems_.has_value());
    webPattern->UpdateJavaScriptOnDocumentEnd();
    webPattern->delegate_ = nullptr;
    webPattern->UpdateJavaScriptOnDocumentEnd();
    webPattern->onDocumentEndScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->UpdateJavaScriptOnDocumentEnd();
    EXPECT_TRUE(webPattern->onDocumentEndScriptItems_.has_value());
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentStartByOrder005
 * @tc.desc: JavaScriptOnDocumentStartByOrder.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, JavaScriptOnDocumentStartByOrder005, TestSize.Level1)
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
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::vector<std::string> scriptItemsByOrder;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnDocumentStartByOrder(scriptItems, scriptItemsByOrder);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentEndByOrder005
 * @tc.desc: JavaScriptOnDocumentEndByOrder.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, JavaScriptOnDocumentEndByOrder005, TestSize.Level1)
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
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::vector<std::string> scriptItemsByOrder;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnDocumentEndByOrder(scriptItems, scriptItemsByOrder);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: UpdateJavaScriptOnDocumentStartByOrder005
 * @tc.desc: UpdateJavaScriptOnDocumentStartByOrder.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, UpdateJavaScriptOnDocumentStartByOrder005, TestSize.Level1)
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

    std::map<std::string, std::vector<std::string>> scriptItems;
    std::vector<std::string> scriptItemsByOrder;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->onDocumentStartScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->onDocumentStartScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    webPattern->UpdateJavaScriptOnDocumentStartByOrder();
    EXPECT_FALSE(webPattern->onDocumentStartScriptItems_.has_value());
    webPattern->UpdateJavaScriptOnDocumentStartByOrder();
    webPattern->delegate_ = nullptr;
    webPattern->UpdateJavaScriptOnDocumentStartByOrder();
    webPattern->onDocumentStartScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->onDocumentStartScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    webPattern->UpdateJavaScriptOnDocumentStartByOrder();
    EXPECT_TRUE(webPattern->onDocumentStartScriptItems_.has_value());
#endif
}

/**
 * @tc.name: UpdateJavaScriptOnDocumentEndByOrder005
 * @tc.desc: UpdateJavaScriptOnDocumentEndByOrder.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, UpdateJavaScriptOnDocumentEndByOrder005, TestSize.Level1)
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

    std::map<std::string, std::vector<std::string>> scriptItems;
    std::vector<std::string> scriptItemsByOrder;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->onDocumentEndScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->onDocumentEndScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    webPattern->UpdateJavaScriptOnDocumentEndByOrder();
    EXPECT_FALSE(webPattern->onDocumentEndScriptItems_.has_value());
    webPattern->UpdateJavaScriptOnDocumentEndByOrder();
    webPattern->delegate_ = nullptr;
    webPattern->UpdateJavaScriptOnDocumentEndByOrder();
    webPattern->onDocumentEndScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->onDocumentEndScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    webPattern->UpdateJavaScriptOnDocumentEndByOrder();
    EXPECT_TRUE(webPattern->onDocumentEndScriptItems_.has_value());
#endif
}

/**
 * @tc.name: JavaScriptOnHeadReadyByOrder001
 * @tc.desc: JavaScriptOnHeadReadyByOrder.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, JavaScriptOnHeadReadyByOrder001, TestSize.Level1)
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
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::vector<std::string> scriptItemsByOrder;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnHeadReadyByOrder(scriptItems, scriptItemsByOrder);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: UpdateJavaScriptOnHeadReadyByOrder001
 * @tc.desc: UpdateJavaScriptOnHeadReadyByOrder.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, UpdateJavaScriptOnHeadReadyByOrder001, TestSize.Level1)
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

    std::map<std::string, std::vector<std::string>> scriptItems;
    std::vector<std::string> scriptItemsByOrder;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->onHeadReadyScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->onHeadReadyScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    webPattern->UpdateJavaScriptOnHeadReadyByOrder();
    EXPECT_FALSE(webPattern->onHeadReadyScriptItems_.has_value());
    webPattern->UpdateJavaScriptOnHeadReadyByOrder();
    webPattern->delegate_ = nullptr;
    webPattern->UpdateJavaScriptOnHeadReadyByOrder();
    webPattern->onHeadReadyScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    webPattern->onHeadReadyScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    webPattern->UpdateJavaScriptOnHeadReadyByOrder();
    EXPECT_TRUE(webPattern->onHeadReadyScriptItems_.has_value());
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
 * @tc.name: SetDrawRect001
 * @tc.desc: SetDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, SetDrawRect001, TestSize.Level1)
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

    webPattern->drawRectWidth_ = 10;
    webPattern->drawRectHeight_ = 20;
    webPattern->SetDrawRect(10, 20, 10, 20);
    webPattern->drawRectHeight_ = 5;
    webPattern->SetDrawRect(10, 20, 10, 20);
    EXPECT_EQ(webPattern->drawRectHeight_, 20);
    webPattern->drawRectWidth_ = 5;
    webPattern->SetDrawRect(10, 20, 10, 20);
    EXPECT_EQ(webPattern->drawRectWidth_, 10);
    webPattern->drawRectWidth_ = 5;
    webPattern->drawRectHeight_ = 5;
    webPattern->SetDrawRect(10, 20, 10, 20);
    EXPECT_EQ(webPattern->drawRectWidth_, 10);
    EXPECT_EQ(webPattern->drawRectHeight_, 20);
#endif
}

/**
 * @tc.name: GetPendingSizeStatus001
 * @tc.desc: GetPendingSizeStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, GetPendingSizeStatus001, TestSize.Level1)
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
    EXPECT_FALSE(webPattern->GetPendingSizeStatus());
    webPattern->delegate_ = nullptr;
    EXPECT_FALSE(webPattern->GetPendingSizeStatus());
#endif
}

/**
 * @tc.name: GetAccessibilityNodeById001
 * @tc.desc: GetAccessibilityNodeById.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, GetAccessibilityNodeById001, TestSize.Level1)
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
    webPattern->accessibilityState_ = true;
    OHOS::Ace::SetReturnStatus("true");
    ret = webPattern->GetAccessibilityNodeById(accessibilityId);
    EXPECT_NE(ret, nullptr);
#endif
}

/**
 * @tc.name: GetFocusedAccessibilityNode001
 * @tc.desc: GetFocusedAccessibilityNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, GetFocusedAccessibilityNode001, TestSize.Level1)
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
    webPattern->accessibilityState_ = true;
    OHOS::Ace::SetReturnStatus("true");
    ret = webPattern->GetFocusedAccessibilityNode(accessibilityId, isAccessibilityFocus);
    EXPECT_NE(ret, nullptr);
#endif
}

/**
 * @tc.name: GetAccessibilityNodeByFocusMove001
 * @tc.desc: GetAccessibilityNodeByFocusMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, GetAccessibilityNodeByFocusMove001, TestSize.Level1)
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
    webPattern->accessibilityState_ = true;
    OHOS::Ace::SetReturnStatus("true");
    ret = webPattern->GetAccessibilityNodeByFocusMove(accessibilityId, direction);
    EXPECT_NE(ret, nullptr);
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

    webPattern->accessibilityState_ = true;
    webPattern->SetAccessibilityState(true);
    EXPECT_TRUE(webPattern->accessibilityState_);
    webPattern->inspectorAccessibilityEnable_ = false;
    webPattern->textBlurAccessibilityEnable_ = false;
    webPattern->SetAccessibilityState(false);
    EXPECT_FALSE(webPattern->accessibilityState_);
    webPattern->inspectorAccessibilityEnable_ = false;
    webPattern->textBlurAccessibilityEnable_ = false;
    webPattern->SetAccessibilityState(false);
    EXPECT_FALSE(webPattern->accessibilityState_);
    webPattern->inspectorAccessibilityEnable_ = false;
    webPattern->textBlurAccessibilityEnable_ = true;
    webPattern->SetAccessibilityState(false);
    EXPECT_FALSE(webPattern->accessibilityState_);
    webPattern->inspectorAccessibilityEnable_ = true;
    webPattern->textBlurAccessibilityEnable_ = false;
    webPattern->SetAccessibilityState(false);
    EXPECT_FALSE(webPattern->accessibilityState_);
    webPattern->inspectorAccessibilityEnable_ = true;
    webPattern->textBlurAccessibilityEnable_ = true;
    webPattern->SetAccessibilityState(false);
    EXPECT_FALSE(webPattern->accessibilityState_);
    webPattern->accessibilityState_ = true;
    webPattern->inspectorAccessibilityEnable_ = false;
    webPattern->textBlurAccessibilityEnable_ = true;
    webPattern->SetAccessibilityState(false);
    EXPECT_TRUE(webPattern->accessibilityState_);
    webPattern->inspectorAccessibilityEnable_ = true;
    webPattern->textBlurAccessibilityEnable_ = false;
    webPattern->SetAccessibilityState(false);
    EXPECT_TRUE(webPattern->accessibilityState_);
    webPattern->inspectorAccessibilityEnable_ = true;
    webPattern->textBlurAccessibilityEnable_ = true;
    webPattern->SetAccessibilityState(false);
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
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
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

    webPattern->SetTouchEventInfo(touchEvent, touchEventInfo, "embedId");
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
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnVisibleAreaChange(true);
    EXPECT_TRUE(webPattern->isVisible_);
    webPattern->isVisible_ = false;
    webPattern->isVisibleActiveEnable_ = false;
    webPattern->OnVisibleAreaChange(true);
    ASSERT_EQ(webPattern->isVisible_, true);
    webPattern->isVisible_ = false;
    webPattern->isActive_ = false;
    webPattern->isVisibleActiveEnable_ = true;
    webPattern->OnVisibleAreaChange(true);
    EXPECT_TRUE(webPattern->isActive_);
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
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    RefPtr<FrameNode> node = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr); });
    webPatternFrameNode->SetParent(node);
    webPattern->isVisible_ = true;
    webPattern->isVisibleActiveEnable_ = true;
    webPattern->isFocus_ = false;
    webPattern->isActive_ = true;
    webPattern->OnVisibleAreaChange(false);
    EXPECT_FALSE(webPattern->isActive_);
    EXPECT_FALSE(webPattern->isDragEndMenuShow_);
    webPattern->isActive_ = true;
    webPattern->isFocus_ = true;
    webPattern->isVisible_ = true;
    webPattern->OnVisibleAreaChange(false);
    EXPECT_TRUE(webPattern->isActive_);
    webPattern->isVisibleActiveEnable_ = false;
    webPattern->isVisible_ = true;
    webPattern->OnVisibleAreaChange(false);
    EXPECT_TRUE(webPattern->isActive_);
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
    webPattern->isVisible_ = true;
    webPattern->OnVisibleAreaChange(true);
    ASSERT_EQ(webPattern->isVisible_, true);
#endif
}

/**
 * @tc.name: OnVisibleAreaChangeTest004
 * @tc.desc: OnVisibleAreaChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnVisibleAreaChangeTest004, TestSize.Level1)
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

    RefPtr<FrameNode> node = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr); });
    webPatternFrameNode->SetParent(node);
    webPattern->isVisible_ = true;
    webPattern->isVisibleActiveEnable_ = false;
    webPattern->isFocus_ = true;
    webPattern->OnVisibleAreaChange(false);
    EXPECT_FALSE(webPattern->isDragEndMenuShow_);
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

    webPattern->offlineWebInited_ = false;
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
    webPattern->isMemoryLevelEnable_ = true;
    webPattern->OnNotifyMemoryLevel(0);
    webPattern->isMemoryLevelEnable_ = false;
    webPattern->OnNotifyMemoryLevel(0);
    ASSERT_NE(webPattern->delegate_, nullptr);
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
 * @tc.name: HandleScrollVelocityTest002
 * @tc.desc: HandleScrollVelocity.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, HandleScrollVelocityTest002, TestSize.Level1)
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
    EXPECT_CALL(*parent, HandleScrollVelocity).Times(1).WillOnce(Return(false));
    EXPECT_FALSE(webPattern->HandleScrollVelocity(parent, 1.f));
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
    webPattern->OnOverScrollFlingVelocity(1.0f, 2.0f, true);
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

    RefPtr<MockNestableScrollContainer> parent = AccessibilityManager::MakeRefPtr<MockNestableScrollContainer>();
    webPattern->parentsMap_ = { { Axis::HORIZONTAL, parent } };
    webPattern->expectedScrollAxis_ = Axis::HORIZONTAL;
    webPattern->nestedScroll_.scrollRight = NestedScrollMode::SELF_FIRST;
    webPattern->scrollState_ = true;
    EXPECT_CALL(*parent, HandleScroll)
        .Times(2)
        .WillRepeatedly(Return(ScrollResult { .remain = 0.1f, .reachEdge = true }));
    webPattern->OnOverScrollFlingVelocityHandler(1.0f, false);
    ASSERT_TRUE(webPattern->isFirstFlingScrollVelocity_);
    webPattern->scrollState_ = false;
    webPattern->OnOverScrollFlingVelocityHandler(1.0f, false);
    ASSERT_TRUE(webPattern->isFirstFlingScrollVelocity_);
#endif
}

/**
 * @tc.name: OnOverScrollFlingVelocityHandlerTest002
 * @tc.desc: OnOverScrollFlingVelocityHandler.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnOverScrollFlingVelocityHandlerTest002, TestSize.Level1)
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
    webPattern->parentsMap_ = { { Axis::HORIZONTAL, parent } };
    webPattern->expectedScrollAxis_ = Axis::HORIZONTAL;
    webPattern->scrollState_ = true;
    webPattern->nestedScroll_.scrollDown = NestedScrollMode::SELF_ONLY;
    webPattern->OnOverScrollFlingVelocityHandler(1.0f, false);
    webPattern->nestedScroll_.scrollDown = NestedScrollMode::SELF_FIRST;
    webPattern->OnOverScrollFlingVelocityHandler(1.0f, false);
    ASSERT_TRUE(webPattern->isFirstFlingScrollVelocity_);
    webPattern->OnOverScrollFlingVelocityHandler(1.0f, true);
    webPattern->isFirstFlingScrollVelocity_ = true;
    webPattern->nestedScroll_.scrollLeft = NestedScrollMode::SELF_ONLY;
    webPattern->OnOverScrollFlingVelocityHandler(1.0f, true);
    webPattern->nestedScroll_.scrollLeft = NestedScrollMode::SELF_FIRST;
    EXPECT_CALL(*parent, HandleScrollVelocity).Times(1).WillOnce(Return(false));
    webPattern->OnOverScrollFlingVelocityHandler(1.0f, true);
    EXPECT_FALSE(webPattern->isFirstFlingScrollVelocity_);
    webPattern->OnOverScrollFlingVelocityHandler(1.0f, true);
    EXPECT_FALSE(webPattern->isFirstFlingScrollVelocity_);
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
    webPattern->OnScrollState(true);
    webPattern->OnScrollState(false);
    EXPECT_FALSE(webPattern->scrollState_);
#endif
}

/**
 * @tc.name: OnScrollStartTest001
 * @tc.desc: OnScrollStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnScrollStartTest001, TestSize.Level1)
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
    webPattern->OnScrollStart(2.0f, 1.0f);
    EXPECT_TRUE(webPattern->scrollState_);
    EXPECT_EQ(webPattern->expectedScrollAxis_, Axis::HORIZONTAL);
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

    webPattern->layoutMode_ = WebLayoutMode::FIT_CONTENT;
    webPattern->ReleaseResizeHold();
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

    webPattern->axis_ = Axis::VERTICAL;
    webPattern->GetParentAxis();
    RefPtr<MockNestableScrollContainer> parent = AccessibilityManager::MakeRefPtr<MockNestableScrollContainer>();
    webPattern->SetNestedScrollParent(parent);

    EXPECT_CALL(*parent, GetAxis()).Times(1).WillOnce(testing::Return(Axis::HORIZONTAL));
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
 * @tc.name: SetNestedScrollExtTest002
 * @tc.desc: SetNestedScrollExt.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, SetNestedScrollExtTest002, TestSize.Level1)
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
    nestedScroll.scrollLeft = NestedScrollMode::SELF_FIRST;
    nestedScroll.scrollDown = NestedScrollMode::SELF_ONLY;
    nestedScroll.scrollRight = NestedScrollMode::SELF_FIRST;
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
    webPattern->layoutMode_ = WebLayoutMode::FIT_CONTENT;
    webPattern->OnRootLayerChanged(100, 100);
    EXPECT_EQ(webPattern->rootLayerWidth_, 100);
    EXPECT_EQ(webPattern->rootLayerHeight_, 100);
    webPattern->OnRootLayerChanged(100, 300);
    EXPECT_EQ(webPattern->rootLayerWidth_, 100);
    EXPECT_EQ(webPattern->rootLayerHeight_, 300);
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

    webPattern->rootLayerWidth_ = 200;
    webPattern->rootLayerHeight_ = 300;
    webPattern->OnRootLayerChanged(200, 300);
    EXPECT_TRUE((webPattern->rootLayerWidth_ == 200) && (webPattern->rootLayerHeight_ == 300));
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
    OHOS::Ace::SetReturnStatus("true");
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
    OHOS::Ace::SetReturnStatus("");
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
    OHOS::Ace::SetReturnStatus("");
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
    OHOS::Ace::SetReturnStatus("true");
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

/**
 * @tc.name: ExecuteAction_001
 * @tc.desc: ExecuteAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, ExecuteAction_001, TestSize.Level1)
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
    std::map<std::string, std::string> arguments = { { "arg1", "value1" } };
    EXPECT_FALSE(webPattern->ExecuteAction(1, AceAction::ACTION_NONE, arguments));
    webPattern->accessibilityState_ = true;
    webPattern->delegate_->accessibilityState_ = true;
    EXPECT_FALSE(webPattern->ExecuteAction(1, AceAction::ACTION_CLICK, arguments));
#endif
}

/**
 * @tc.name: FilterScrollEventHandleOffset_001
 * @tc.desc: FilterScrollEventHandleOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, FilterScrollEventHandleOffset_001, TestSize.Level1)
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
    EXPECT_CALL(*parent, HandleScroll).Times(1).WillOnce(Return(ScrollResult { .remain = 0.001f, .reachEdge = true }));
    EXPECT_TRUE(webPattern->FilterScrollEventHandleOffset(2.0f));
#endif
}

/**
 * @tc.name: FilterScrollEventHandleOffset_002
 * @tc.desc: FilterScrollEventHandleOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, FilterScrollEventHandleOffset_002, TestSize.Level1)
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
    webPattern->nestedScroll_.scrollLeft = NestedScrollMode::SELF_FIRST;
    webPattern->SetNestedScrollParent(parent);
    EXPECT_TRUE(webPattern->FilterScrollEventHandleOffset(2.0f));
#endif
}

/**
 * @tc.name: FilterScrollEventHandleOffset_003
 * @tc.desc: FilterScrollEventHandleOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, FilterScrollEventHandleOffset_003, TestSize.Level1)
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
    EXPECT_TRUE(webPattern->FilterScrollEventHandleOffset(2.0f));
#endif
}

/**
 * @tc.name: FilterScrollEventHandleOffset_004
 * @tc.desc: FilterScrollEventHandleOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, FilterScrollEventHandleOffset_004, TestSize.Level1)
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
    EXPECT_CALL(*parent, HandleScroll).Times(2).WillOnce(Return(ScrollResult { .remain = 0.1f, .reachEdge = true }));
    EXPECT_TRUE(webPattern->FilterScrollEventHandleOffset(2.0f));
#endif
}

/**
 * @tc.name: OnScrollStartRecursive_001
 * @tc.desc: OnScrollStartRecursive.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnScrollStartRecursive_001, TestSize.Level1)
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
    webPattern->parentsMap_ = { { Axis::HORIZONTAL, parent }, { Axis::VERTICAL, nullptr } };
    EXPECT_CALL(*parent, OnScrollStartRecursive).Times(1);
    webPattern->OnScrollStartRecursive(1.0f);
    EXPECT_TRUE(webPattern->isFirstFlingScrollVelocity_);
#endif
}

/**
 * @tc.name: OnScrollStartRecursive_002
 * @tc.desc: OnScrollStartRecursive.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnScrollStartRecursive_002, TestSize.Level1)
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
    webPattern->parentsMap_ = { { Axis::HORIZONTAL, parent }, { Axis::VERTICAL, nullptr } };
    webPattern->OnScrollStartRecursive(1.0f);
    EXPECT_TRUE(webPattern->isFirstFlingScrollVelocity_);
#endif
}

/**
 * @tc.name: OnScrollEndRecursive_001
 * @tc.desc: OnScrollEndRecursive.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnScrollEndRecursive_001, TestSize.Level1)
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
    webPattern->parentsMap_ = { { Axis::HORIZONTAL, parent }, { Axis::VERTICAL, nullptr } };
    std::optional<float> velocity = 1.f;
    webPattern->isScrollStarted_ = true;
    EXPECT_CALL(*parent, OnScrollEndRecursive).Times(1);
    webPattern->OnScrollEndRecursive(velocity);
    EXPECT_FALSE(webPattern->isScrollStarted_);
#endif
}

/**
 * @tc.name: IsDialogNestedTest001
 * @tc.desc: IsDialogNested.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, IsDialogNestedTest001, TestSize.Level1)
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

    RefPtr<FrameNode> node = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr); });
    webPatternFrameNode->SetParent(node);
    EXPECT_TRUE(webPattern->IsDialogNested());
#endif
}

/**
 * @tc.name: IsDialogNestedTest002
 * @tc.desc: IsDialogNested.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, IsDialogNestedTest002, TestSize.Level1)
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

    RefPtr<FrameNode> node =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    webPatternFrameNode->SetParent(node);
    EXPECT_FALSE(webPattern->IsDialogNested());
#endif
}

/**
 * @tc.name: FilterScrollEvent_001
 * @tc.desc: FilterScrollEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, FilterScrollEvent_001, TestSize.Level1)
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
    webPattern->expectedScrollAxis_ = Axis::VERTICAL;
    EXPECT_FALSE(webPattern->FilterScrollEvent(1.0f, 0.5f, 1.0f, 2.0f));
#endif
}

/**
 * @tc.name: OnContextMenuShow_001
 * @tc.desc: OnContextMenuShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgSupplement, OnContextMenuShow_001, TestSize.Level1)
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

    RefPtr<WebContextMenuParam> menuParam = AceType::MakeRefPtr<WebContextMenuParamShow>();
    RefPtr<ContextMenuResult> menuResult = AceType::MakeRefPtr<ContextMenuResultShow>();
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(menuParam, menuResult);
    webPattern->contextSelectOverlay_ = nullptr;
    webPattern->OnContextMenuShow(eventInfo, false, true);
    EXPECT_EQ(webPattern->contextSelectOverlay_, nullptr);
#endif
}
} // namespace OHOS::Ace::NG
