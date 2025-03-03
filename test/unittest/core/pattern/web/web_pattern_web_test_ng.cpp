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
#include <list>

#include "gtest/gtest.h"
#include "src/core/SkVM.h"
#define protected public
#define private public
#include "foundation/arkui/ace_engine/frameworks/core/common/ai/image_analyzer_manager.h"
#include "foundation/arkui/ace_engine/interfaces/inner_api/ace/ai/image_analyzer.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#undef private
#undef protected
#include "base/web/webview/ohos_nweb/include/nweb.h"
#include "base/web/webview/ohos_nweb/include/nweb_handler.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/utils/system_properties.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::NWeb;

namespace {
constexpr int32_t COORDINATEID_UN = -1;
constexpr int32_t COORDINATEID_FA = 1;
constexpr int32_t POSITION_UN = 10;
constexpr int32_t POSITIONX_FA = 0;
constexpr int32_t POSITIONY_FA = 1;
constexpr int32_t VIEWPORT = 0;
constexpr float ALPHA_UN = -0.5;
constexpr float ALPHA_FA = 0.5;
constexpr float EDGEHEIGHT_UN = 0.0;
constexpr float EDGEHEIGHT_FA = 5.0;
constexpr float EDGEHEIGHT_TR = 1.0;
constexpr float EDGE_HEIGHT = 30.0;
} // namespace

namespace OHOS::NWeb {
class MockNWebTouchHandleStateImpl : public NWebTouchHandleState {
public:
    MockNWebTouchHandleStateImpl() = default;
    int32_t GetTouchHandleId() override
    {
        return -1;
    };
    int32_t GetX() override
    {
        return 0;
    };
    int32_t GetY() override
    {
        return 0;
    };
    int32_t GetViewPortX() override
    {
        return 0;
    };
    int32_t GetViewPortY() override
    {
        return 0;
    };
    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::SELECTION_END_HANDLE;
    };
    bool IsEnable() override
    {
        return true;
    };
    float GetAlpha() override
    {
        return 0.0;
    };
    float GetEdgeHeight() override
    {
        return edgeHeight_;
    };

private:
    float edgeHeight_ = EDGE_HEIGHT;
};
} // namespace OHOS::NWeb

namespace OHOS::Ace::NG {

class WebPatternWebTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternWebTest::SetUpTestCase() {}
void WebPatternWebTest::TearDownTestCase() {}
void WebPatternWebTest::SetUp()
{
    MockPipelineContext::SetUp();
}
void WebPatternWebTest::TearDown()
{
    MockPipelineContext::TearDown();
}

class NWebTouchHandleStateUN : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateUN() = default;
    int32_t GetTouchHandleId() override
    {
        return COORDINATEID_UN;
    };
    int32_t GetX() override
    {
        return POSITION_UN;
    };
    int32_t GetY() override
    {
        return POSITION_UN;
    };
    int32_t GetViewPortX() override
    {
        return VIEWPORT;
    };
    int32_t GetViewPortY() override
    {
        return VIEWPORT;
    };
    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::SELECTION_BEGIN_HANDLE;
    };
    bool IsEnable() override
    {
        return false;
    };
    float GetAlpha() override
    {
        return ALPHA_UN;
    };
    float GetEdgeHeight() override
    {
        return EDGEHEIGHT_UN;
    };
};

class NWebTouchHandleStateFA : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateFA() = default;
    int32_t GetTouchHandleId() override
    {
        return COORDINATEID_FA;
    };
    int32_t GetX() override
    {
        return POSITIONX_FA;
    };
    int32_t GetY() override
    {
        return POSITIONY_FA;
    };
    int32_t GetViewPortX() override
    {
        return VIEWPORT;
    };
    int32_t GetViewPortY() override
    {
        return VIEWPORT;
    };
    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::SELECTION_BEGIN_HANDLE;
    };
    bool IsEnable() override
    {
        return false;
    };
    float GetAlpha() override
    {
        return ALPHA_FA;
    };
    float GetEdgeHeight() override
    {
        return EDGEHEIGHT_FA;
    };
};

class NWebTouchHandleStateTR : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateTR() = default;
    int32_t GetTouchHandleId() override
    {
        return COORDINATEID_UN;
    };
    int32_t GetX() override
    {
        return POSITIONX_FA;
    };
    int32_t GetY() override
    {
        return POSITIONY_FA;
    };
    int32_t GetViewPortX() override
    {
        return VIEWPORT;
    };
    int32_t GetViewPortY() override
    {
        return VIEWPORT;
    };
    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::SELECTION_BEGIN_HANDLE;
    };
    bool IsEnable() override
    {
        return false;
    };
    float GetAlpha() override
    {
        return ALPHA_FA;
    };
    float GetEdgeHeight() override
    {
        return EDGEHEIGHT_TR;
    };
};

class MockRenderContextTest : public RenderContext {
public:
    RectF GetPaintRectWithoutTransform() override
    {
        return *retf;
    }
    std::shared_ptr<RectF> retf;
};

/**
 * @tc.name: InitInOfflineMode_001
 * @tc.desc: InitInOfflineMode
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, InitInOfflineMode_001, TestSize.Level1)
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
    webPattern->webSrc_ = "Another Value";
    webPattern->InitInOfflineMode();
    EXPECT_FALSE(webPattern->delegate_->LoadDataWithRichText());
#endif
}

/**
 * @tc.name: InitInOfflineMode_001
 * @tc.desc: InitInOfflineMode
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, InitInOfflineMode_002, TestSize.Level1)
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
    webPattern->webData_ = "Another Value";
    webPattern->InitInOfflineMode();
    EXPECT_FALSE(webPattern->delegate_->LoadDataWithRichText());
#endif
}

/**
 * @tc.name: IsNeedResizeVisibleViewport
 * @tc.desc: IsNeedResizeVisibleViewport.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, IsNeedResizeVisibleViewport, TestSize.Level1)
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
    Size size { 10, 10 };
    webPattern->visibleViewportSize_.SetSize(size);
    webPattern->lastKeyboardHeight_ = -0.0015;
    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_SHOW;
    EXPECT_TRUE(webPattern->IsNeedResizeVisibleViewport());
    webPattern->lastKeyboardHeight_ = 0.0;
    EXPECT_FALSE(webPattern->IsNeedResizeVisibleViewport());
    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_HIDE;
    EXPECT_FALSE(webPattern->IsNeedResizeVisibleViewport());
#endif
}

/**
 * @tc.name: ProcessVirtualKeyBoardHide
 * @tc.desc: ProcessVirtualKeyBoardHide.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, ProcessVirtualKeyBoardHide, TestSize.Level1)
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
    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_NONE;
    EXPECT_FALSE(webPattern->ProcessVirtualKeyBoardHide(10, 10, false));
    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_SHOW;
    EXPECT_TRUE(webPattern->ProcessVirtualKeyBoardHide(10, 10, false));
#endif
}

/**
 * @tc.name: ProcessVirtualKeyBoardShow
 * @tc.desc: ProcessVirtualKeyBoardShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, ProcessVirtualKeyBoardShow, TestSize.Level1)
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
    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_HIDE;
    webPattern->drawSizeCache_.SetHeight(50.00);
    ASSERT_TRUE(webPattern->ProcessVirtualKeyBoardShow(0, 0, 100.00, true));
    webPattern->OnModifyDone();
    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_SHOW;
    webPattern->drawSizeCache_.SetHeight(50.00);
    EXPECT_FALSE(webPattern->ProcessVirtualKeyBoardShow(0, 0, 0.00, true));
    EXPECT_FALSE(webPattern->ProcessVirtualKeyBoardShow(0, 0, 0.00, false));
    webPattern->layoutMode_ = WebLayoutMode::FIT_CONTENT;
    EXPECT_TRUE(webPattern->ProcessVirtualKeyBoardShow(0, 0, 0.00, false));
    RefPtr<FrameNode> node = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr); });
    frameNode->SetParent(node);
    EXPECT_FALSE(webPattern->ProcessVirtualKeyBoardShow(0, 0, 0.00, true));
#endif
}

/**
 * @tc.name: ProcessVirtualKeyBoard
 * @tc.desc: ProcessVirtualKeyBoard.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, ProcessVirtualKeyBoard, TestSize.Level1)
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
    webPattern->isFocus_ = true;
    webPattern->isVisible_ = true;
    EXPECT_FALSE(webPattern->ProcessVirtualKeyBoard(10, 10, 0.00));
    EXPECT_TRUE(webPattern->ProcessVirtualKeyBoard(10, 10, 10.00));
    webPattern->isFocus_ = false;
    webPattern->isVisible_ = false;
    EXPECT_FALSE(webPattern->ProcessVirtualKeyBoard(10, 10, 0.00));
    webPattern->isFocus_ = true;
    webPattern->isVisible_ = false;
    EXPECT_FALSE(webPattern->ProcessVirtualKeyBoard(10, 10, 0.00));
    webPattern->isFocus_ = false;
    webPattern->isVisible_ = true;
    EXPECT_FALSE(webPattern->ProcessVirtualKeyBoard(10, 10, 0.00));
#endif
}

/**
 * @tc.name: OnDetachContextAllTrue
 * @tc.desc: OnDetachContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, OnDetachContextAllTrue, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    auto dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();
    webPattern->OnDetachContext(Referenced::RawPtr(pipelineContext));
    ASSERT_NE(pipelineContext->GetDragDropManager(), nullptr);
#endif
}

/**
 * @tc.name: OnDetachContextAllFalse
 * @tc.desc: OnDetachContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, OnDetachContextAllFalse, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->tooltipId_ = 1;
    auto pipelineContext = MockPipelineContext::GetCurrent();
    webPattern->OnDetachContext(Referenced::RawPtr(pipelineContext));
    EXPECT_EQ(webPattern->tooltipId_, -1);
#endif
}

/**
 * @tc.name: OnDefaultTextEncodingFormatUpdate
 * @tc.desc: OnDefaultTextEncodingFormat.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, OnDefaultTextEncodingFormatUpdate, TestSize.Level1)
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
    std::string tag = "";
    webPattern->OnDefaultTextEncodingFormatUpdate(tag);
    auto canonicalEncodingName = webPattern->delegate_->GetCanonicalEncodingName(tag);
    EXPECT_EQ(canonicalEncodingName, tag);
#endif
}

/**
 * @tc.name: OnModifyDoneSurfaceTrue
 * @tc.desc: OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, OnModifyDoneSurfaceTrue, TestSize.Level1)
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
    webPattern->SetLayoutMode(WebLayoutMode::NONE);
    SystemProperties::SetExtSurfaceEnabled(true);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->renderSurface_, 0);
#endif
}

/**
 * @tc.name: OnModifyDonerenderModeTrue
 * @tc.desc: OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, OnModifyDonerenderModeTrue, TestSize.Level1)
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
    webPattern->SetRenderMode(RenderMode::SYNC_RENDER);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->renderSurface_, nullptr);
#endif
}

/**
 * @tc.name: OnModifyDoneLFIT
 * @tc.desc: OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, OnModifyDoneLFIT, TestSize.Level1)
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
    SystemProperties::SetExtSurfaceEnabled(true);
    webPattern->SetLayoutMode(WebLayoutMode::NONE);
    webPattern->OnModifyDone();
    EXPECT_TRUE(webPattern->GetZoomAccessEnabledValue(true));
#endif
}

/**
 * @tc.name: OnAttachContext
 * @tc.desc: OnAttachContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, OnAttachContext, TestSize.Level1)
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
    webPattern->updateInstanceIdCallback_ = [](int32_t instanceId) {
        std::cout << "Updating instance ID to: " << instanceId << std::endl;
    };
    auto dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    webPattern->OnAttachContext(Referenced::RawPtr(pipelineContext));
    ASSERT_NE(pipelineContext->GetDragDropManager(), nullptr);
#endif
}

/**
 * @tc.name: OnModifyDoneGetNull
 * @tc.desc: OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, OnModifyDoneGetNull, TestSize.Level1)
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
    webPattern->OnMetaViewportUpdate(false);
    webPattern->OnBlockNetworkUpdate(false);
    webPattern->OnUserAgentUpdate("");
    webPattern->OnInitialScaleUpdate(0.0);
    EXPECT_FALSE(webPattern->GetMetaViewport());
#endif
}

/**
 * @tc.name: ParseTouchInfo
 * @tc.desc: ParseTouchInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, ParseTouchInfo, TestSize.Level1)
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
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    TouchEventInfo event("touchstart");
    std::list<OHOS::Ace::NG::WebPattern::TouchInfo> touchInfos;
    webPattern->ParseTouchInfo(event, touchInfos);
    EXPECT_TRUE(event.GetChangedTouches().empty());
#endif
}

/**
 * @tc.name: UpdateLayoutAfterKeyboardShow
 * @tc.desc: UpdateLayoutAfterKeyboardShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, UpdateLayoutAfterKeyboardShow, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    RefPtr<WebPattern> webPattern = nullptr;
    RefPtr<FrameNode> frameNode = nullptr;
    const std::string src = "web_pattern_focus_test";
    RefPtr<WebController> webController = AceType::MakeRefPtr<WebController>();
    ASSERT_NE(webController, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId,
        [src, webController]() { return AceType::MakeRefPtr<WebPattern>(src, webController); });
    stack->Push(frameNode);
    webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebSrc(src);
    webPattern->SetWebController(webController);
    webPattern->OnModifyDone();
    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_NONE;
    webPattern->UpdateLayoutAfterKeyboardShow(1, 1, 1, 1);
    EXPECT_EQ(webPattern->isVirtualKeyBoardShow_, WebPattern::VkState::VK_NONE);
    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_SHOW;
    webPattern->UpdateLayoutAfterKeyboardShow(1, 1, 1, 0);
    EXPECT_EQ(webPattern->isVirtualKeyBoardShow_, WebPattern::VkState::VK_SHOW);
    webPattern->keyBoardAvoidMode_ = WebKeyboardAvoidMode::RESIZE_VISUAL;
    webPattern->drawSize_.SetWidth(10);
    webPattern->UpdateLayoutAfterKeyboardShow(1, 1, 1, 2);
    EXPECT_EQ(webPattern->visibleViewportSize_.Width(), 10);
    EXPECT_EQ(webPattern->visibleViewportSize_.Height(), 0);
    webPattern->keyBoardAvoidMode_ = WebKeyboardAvoidMode::OVERLAYS_CONTENT;
    webPattern->UpdateLayoutAfterKeyboardShow(1, 1, 1, 2);
    EXPECT_EQ(webPattern->visibleViewportSize_.Width(), 10);
    EXPECT_EQ(webPattern->visibleViewportSize_.Height(), 0);
    webPattern->keyBoardAvoidMode_ = WebKeyboardAvoidMode::RESIZE_CONTENT;
    webPattern->UpdateLayoutAfterKeyboardShow(1, 1, 1, 2);
    EXPECT_EQ(webPattern->visibleViewportSize_.Width(), -1);
    EXPECT_EQ(webPattern->visibleViewportSize_.Height(), -1);
    EXPECT_EQ(webPattern->drawSize_.Height(), 0);
    EXPECT_EQ(webPattern->heightAfterAvoid_, 0);
#endif
}

/**
 * @tc.name: BeforeSyncGeometryProperties
 * @tc.desc: BeforeSyncGeometryProperties.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, BeforeSyncGeometryProperties, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    RefPtr<WebPattern> webPattern = nullptr;
    RefPtr<FrameNode> frameNode = nullptr;
    const std::string src = "web_pattern_focus_test";
    RefPtr<WebController> webController = AceType::MakeRefPtr<WebController>();
    ASSERT_NE(webController, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId,
        [src, webController]() { return AceType::MakeRefPtr<WebPattern>(src, webController); });
    stack->Push(frameNode);
    webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebSrc(src);
    webPattern->SetWebController(webController);
    webPattern->OnModifyDone();
    webPattern->isResizeContentAvoid_ = false;
    DirtySwapConfig config;
    config.contentSizeChange = false;
    webPattern->isInWindowDrag_ = false;
    webPattern->BeforeSyncGeometryProperties(config);
    EXPECT_EQ(webPattern->isResizeContentAvoid_, false);
    EXPECT_EQ(webPattern->isInWindowDrag_, false);
    webPattern->isInWindowDrag_ = true;
    webPattern->BeforeSyncGeometryProperties(config);
    EXPECT_EQ(webPattern->isInWindowDrag_, true);
    config.contentSizeChange = true;
    webPattern->BeforeSyncGeometryProperties(config);
    EXPECT_EQ(config.contentSizeChange, true);
    webPattern->isInWindowDrag_ = false;
    webPattern->BeforeSyncGeometryProperties(config);
    EXPECT_EQ(webPattern->drawSize_.width_, 0.0);
    EXPECT_EQ(webPattern->drawSize_.height_, 0.0);
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdatePaintRect(RectF(0, 0, 1.7976931348623157e+308, 1.7976931348623157e+308));
    webPattern->BeforeSyncGeometryProperties(config);
    EXPECT_EQ(webPattern->drawSize_.width_, 100.0);
    EXPECT_EQ(webPattern->drawSize_.height_, 80.0);
    renderContext->UpdatePaintRect(RectF(0, 0, 1000000.0, 1000000.0));
    webPattern->BeforeSyncGeometryProperties(config);
    EXPECT_EQ(webPattern->drawSize_.width_, 100.0);
    EXPECT_EQ(webPattern->drawSize_.height_, 80.0);
    EXPECT_EQ(webPattern->drawSizeCache_.width_, 100.0);
    EXPECT_EQ(webPattern->drawSizeCache_.height_, 80.0);
    webPattern->layoutMode_ = WebLayoutMode::FIT_CONTENT;
    renderContext->UpdatePaintRect(RectF(0, 0, 10.0, 10.0));
    webPattern->BeforeSyncGeometryProperties(config);
    EXPECT_EQ(webPattern->drawSize_.width_, 100.0);
    EXPECT_EQ(webPattern->drawSize_.height_, 80.0);
    EXPECT_EQ(webPattern->drawSizeCache_.width_, 100.0);
    EXPECT_EQ(webPattern->drawSizeCache_.height_, 80.0);
    webPattern->layoutMode_ = WebLayoutMode::NONE;
    renderContext->UpdatePaintRect(RectF(0, 0, 10.0, 10.0));
    webPattern->BeforeSyncGeometryProperties(config);
    EXPECT_EQ(webPattern->drawSize_.width_, 10.0);
    EXPECT_EQ(webPattern->drawSize_.height_, 10.0);
    EXPECT_EQ(webPattern->drawSizeCache_.width_, 10.0);
    EXPECT_EQ(webPattern->drawSizeCache_.height_, 10.0);
#endif
}

/**
 * @tc.name: OnAreaChangedInner_002
 * @tc.desc: OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, OnAreaChangedInner_002, TestSize.Level1)
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
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->layoutMode_ = WebLayoutMode::NONE;
    webPattern->renderMode_ = RenderMode::SYNC_RENDER;
    webPattern->isInWindowDrag_ = true;
    webPattern->OnAreaChangedInner();
    EXPECT_EQ(webPattern->webOffset_.GetX(), 0);
#endif
}

/**
 * @tc.name: OnAreaChangedInner_003
 * @tc.desc: OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, OnAreaChangedInner_003, TestSize.Level1)
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
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->layoutMode_ = WebLayoutMode::FIT_CONTENT;
    webPattern->isInWindowDrag_ = false;
    webPattern->renderMode_ = RenderMode::ASYNC_RENDER;
    webPattern->OnAreaChangedInner();
    EXPECT_FALSE(webPattern->isKeyboardInSafeArea_);
#endif
}

/**
 * @tc.name: OnAreaChangedInner_004
 * @tc.desc: OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, OnAreaChangedInner_004, TestSize.Level1)
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
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->layoutMode_ = WebLayoutMode::FIT_CONTENT;
    webPattern->isInWindowDrag_ = false;
    webPattern->renderMode_ = RenderMode::SYNC_RENDER;
    webPattern->OnAreaChangedInner();
    EXPECT_NE(webPattern->layoutMode_, WebLayoutMode::NONE);
    EXPECT_FALSE(webPattern->isInWindowDrag_);
    EXPECT_EQ(webPattern->renderMode_, RenderMode::SYNC_RENDER);
#endif
}

/**
 * @tc.name: OnZoomAccessEnabledUpdate
 * @tc.desc: OnZoomAccessEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, OnZoomAccessEnabledUpdate, TestSize.Level1)
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
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->layoutMode_ = WebLayoutMode::NONE;
    webPattern->isEmbedModeEnabled_ = true;
    bool value = true;
    webPattern->OnZoomAccessEnabledUpdate(value);
    EXPECT_EQ(webPattern->layoutMode_, WebLayoutMode::NONE);
    EXPECT_TRUE(webPattern->isEmbedModeEnabled_);
    webPattern->layoutMode_ = WebLayoutMode::FIT_CONTENT;
    webPattern->OnZoomAccessEnabledUpdate(value);
    EXPECT_EQ(webPattern->layoutMode_, WebLayoutMode::FIT_CONTENT);
#endif
}

/**
 * @tc.name: OnInitialScaleUpdate
 * @tc.desc: OnInitialScaleUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, OnInitialScaleUpdate, TestSize.Level1)
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
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->layoutMode_ = WebLayoutMode::NONE;
    webPattern->isEmbedModeEnabled_ = true;
    float value = 1.0;
    webPattern->OnInitialScaleUpdate(value);
    EXPECT_EQ(webPattern->layoutMode_, WebLayoutMode::NONE);
    EXPECT_TRUE(webPattern->isEmbedModeEnabled_);
    webPattern->layoutMode_ = WebLayoutMode::FIT_CONTENT;
    webPattern->OnInitialScaleUpdate(value);
    EXPECT_EQ(webPattern->layoutMode_, WebLayoutMode::FIT_CONTENT);
#endif
}

/**
 * @tc.name: WebPatternTest
 * @tc.desc: OnAreaChangedInner,UpdateLayoutAfterKeyboardShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, WebPatternTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto expand = std::make_unique<SafeAreaExpandOpts>();
    expand->type = SAFE_AREA_TYPE_SYSTEM;
    expand->edges = SAFE_AREA_EDGE_BOTTOM;
    layoutProperty->safeAreaExpandOpts_ = std::move(expand);
    frameNode->SetLayoutProperty(layoutProperty);
    auto reder = AceType::MakeRefPtr<MockRenderContextTest>();
    auto rec = std::make_shared<RectF>(1.0, 1.0, 1.0, 1.0);
    reder->retf = rec;
    frameNode->renderContext_ = reder;
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->isInWindowDrag_ = true;
    webPattern->isKeyboardInSafeArea_ = true;
    Size size(1.0, 1.0);
    webPattern->areaChangeSize_ = size;
    webPattern->OnAreaChangedInner();
    EXPECT_EQ(webPattern->areaChangeSize_.Width(), frameNode->renderContext_->GetPaintRectWithoutTransform().Width());
    webPattern->isKeyboardInSafeArea_ = true;
    size.SetHeight(0.0);
    webPattern->OnAreaChangedInner();
    EXPECT_EQ(webPattern->areaChangeSize_.Width(), frameNode->renderContext_->GetPaintRectWithoutTransform().Height());
    webPattern->isKeyboardInSafeArea_ = true;
    size.SetWidth(0.0);
    webPattern->OnAreaChangedInner();
    EXPECT_EQ(webPattern->areaChangeSize_.Width(), frameNode->renderContext_->GetPaintRectWithoutTransform().Width());
    auto expandOpts = std::make_unique<SafeAreaExpandOpts>();
    expandOpts->type = SAFE_AREA_TYPE_KEYBOARD;
    expandOpts->edges = SAFE_AREA_EDGE_BOTTOM;
    layoutProperty->safeAreaExpandOpts_ = std::move(expandOpts);
    frameNode->SetLayoutProperty(layoutProperty);
    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_SHOW;
    webPattern->UpdateLayoutAfterKeyboardShow(1, 1, 1, 0);
    auto ret = webPattern->CheckSafeAreaKeyBoard();
    EXPECT_TRUE(ret);
#endif
}

/**
 * @tc.name: UpdateWebLayoutSize
 * @tc.desc: UpdateWebLayoutSize.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, UpdateWebLayoutSize, TestSize.Level1)
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
    webPattern->UpdateWebLayoutSize(10, 10, true, true);
    EXPECT_TRUE(webPattern->delegate_->ShouldVirtualKeyboardOverlay());
#endif
}

/**
 * @tc.name: HandleTouchDown
 * @tc.desc: HandleTouchDown.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, HandleTouchDown, TestSize.Level1)
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
    TouchEventInfo info("info");
    TouchLocationInfo touchInfo(1);
    info.changedTouches_.push_back(touchInfo);
    webPattern->HandleTouchDown(info, false);
    webPattern->overlayCreating_ = true;
    webPattern->UpdateNativeEmbedModeEnabled(true);
    webPattern->HandleTouchDown(info, true);
    EXPECT_FALSE(webPattern->isTouchUpEvent_);
#endif
}

/**
 * @tc.name: HandleTouchUp
 * @tc.desc: HandleTouchUp.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, HandleTouchUp, TestSize.Level1)
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
    TouchEventInfo info("info");
    TouchLocationInfo touchInfo(1);
    info.changedTouches_.push_back(touchInfo);
    webPattern->HandleTouchUp(info, true);
    webPattern->overlayCreating_ = true;
    webPattern->HandleTouchUp(info, true);
    webPattern->imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::IMAGE);
    webPattern->HandleTouchUp(info, false);
    EXPECT_FALSE(webPattern->overlayCreating_);
#endif
}

/**
 * @tc.name: HandleTouchMove
 * @tc.desc: HandleTouchMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, HandleTouchMove, TestSize.Level1)
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
    TouchEventInfo info("info");
    TouchLocationInfo touchInfo(1);
    auto pipeline = MockPipelineContext::GetCurrentContext();
    auto manager = pipeline->GetDragDropManager();
    webPattern->HandleTouchMove(info, true);
    info.changedTouches_.push_back(touchInfo);
    info.isTouchEventsEnd_ = true;
    webPattern->HandleTouchMove(info, false);
    webPattern->overlayCreating_ = true;
    webPattern->HandleTouchMove(info, true);
    manager->isDragged_ = true;
    webPattern->HandleTouchMove(info, true);
    ASSERT_EQ(webPattern->imageAnalyzerManager_, nullptr);
#endif
}

/**
 * @tc.name: HandleTouchCancel
 * @tc.desc: HandleTouchCancel.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, HandleTouchCancel, TestSize.Level1)
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
    RefPtr<UINode> son = frameNode;
    RefPtr<UINode> parent =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    RefPtr<UINode> grandParent =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    parent->exportTextureInfo_ = AceType::MakeRefPtr<ExportTextureInfo>();
    grandParent->exportTextureInfo_ = AceType::MakeRefPtr<ExportTextureInfo>();
    parent->exportTextureInfo_->SetCurrentRenderType(NodeRenderType::RENDER_TYPE_DISPLAY);
    grandParent->exportTextureInfo_->SetCurrentRenderType(NodeRenderType::RENDER_TYPE_TEXTURE);
    son->SetParent(parent);
    parent->SetParent(grandParent);
    TouchEventInfo info("info");
    webPattern->HandleTouchCancel(info);
    EXPECT_TRUE(webPattern->isTouchUpEvent_);
#endif
}

/**
 * @tc.name: HandleKeyEvent_001
 * @tc.desc: HandleKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, HandleKeyEvent_001, TestSize.Level1)
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
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern, nullptr);
    auto webEventhub = frameNode->GetEventHub<WebEventHub>();
    webEventhub->SetOnKeyEvent([](KeyEventInfo& keyEventInfo) { std::cout << "onkeyevent" << std::endl; });
    std::vector<KeyCode> code;
    code.push_back(KeyCode::KEY_HOME);
    std::vector<uint8_t> enhanceData;
    enhanceData.push_back(100);
    TimeStamp timeStamp;
    KeyEvent keuEvent(KeyCode::KEY_HOME, KeyAction::DOWN, code, 1, timeStamp, 1, 1, SourceType::KEYBOARD, enhanceData);
    bool flag = webPattern->HandleKeyEvent(keuEvent);
    EXPECT_FALSE(flag);
#endif
}

/**
 * @tc.name: HandleKeyEvent_002
 * @tc.desc: HandleKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, HandleKeyEvent_002, TestSize.Level1)
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
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern, nullptr);
    auto webEventhub = frameNode->GetEventHub<WebEventHub>();
    webEventhub->SetOnPreKeyEvent([](KeyEventInfo& keyEventInfo) {
        std::cout << "onPrekeyevent" << std::endl;
        return true;
    });
    std::vector<KeyCode> code;
    code.push_back(KeyCode::KEY_HOME);
    std::vector<uint8_t> enhanceData;
    enhanceData.push_back(100);
    TimeStamp timeStamp;
    KeyEvent keuEvent(KeyCode::KEY_HOME, KeyAction::DOWN, code, 1, timeStamp, 1, 1, SourceType::KEYBOARD, enhanceData);
    bool flag = webPattern->HandleKeyEvent(keuEvent);
    EXPECT_TRUE(flag);
#endif
}

/**
 * @tc.name: HandleKeyEvent_003
 * @tc.desc: HandleKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, HandleKeyEvent_003, TestSize.Level1)
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
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern, nullptr);
    auto webEventhub = frameNode->GetEventHub<WebEventHub>();
    webEventhub->SetOnPreKeyEvent([](KeyEventInfo& keyEventInfo) {
        std::cout << "onPrekeyevent" << std::endl;
        return false;
    });
    std::vector<KeyCode> code;
    code.push_back(KeyCode::KEY_HOME);
    std::vector<uint8_t> enhanceData;
    enhanceData.push_back(100);
    TimeStamp timeStamp;
    KeyEvent keuEvent(KeyCode::KEY_HOME, KeyAction::DOWN, code, 1, timeStamp, 1, 1, SourceType::KEYBOARD, enhanceData);
    bool flag = webPattern->HandleKeyEvent(keuEvent);
    EXPECT_FALSE(flag);
#endif
}

/**
 * @tc.name: OnModifyDoneNodestatus
 * @tc.desc: OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, OnModifyDoneNodestatus, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    stack->SetIsBuilderNode(true);
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    RefPtr<UINode> son = frameNode;
    son->SetParent(son);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern, nullptr);
    EXPECT_TRUE(webPattern->offlineWebInited_);
#endif
}

/**
 * @tc.name: BeforeSyncGeometryPropertiesTest
 * @tc.desc: BeforeSyncGeometryProperties.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, BeforeSyncGeometryPropertiesTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    RefPtr<WebPattern> webPattern = nullptr;
    RefPtr<FrameNode> frameNode = nullptr;
    const std::string src = "web_pattern_focus_test";
    RefPtr<WebController> webController = AceType::MakeRefPtr<WebController>();
    EXPECT_NE(webController, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId,
        [src, webController]() { return AceType::MakeRefPtr<WebPattern>(src, webController); });
    stack->Push(frameNode);
    webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebSrc(src);
    webPattern->SetWebController(webController);
    webPattern->OnModifyDone();
    DirtySwapConfig config;
    webPattern->isResizeContentAvoid_ = true;
    webPattern->BeforeSyncGeometryProperties(config);
    EXPECT_TRUE(webPattern->isResizeContentAvoid_);
    EXPECT_FALSE(frameNode->SelfExpansive());
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto safeAreaExpandOpts = std::make_unique<SafeAreaExpandOpts>();
    safeAreaExpandOpts->switchToNone = true;
    layoutProperty->safeAreaExpandOpts_ = move(safeAreaExpandOpts);
    frameNode->layoutProperty_ = layoutProperty;
    webPattern->isResizeContentAvoid_ = true;
    webPattern->BeforeSyncGeometryProperties(config);
    EXPECT_TRUE(frameNode->SelfExpansive());
#endif
}

/**
 * @tc.name: ClearKeyEventByKeyCodeTest
 * @tc.desc: ClearKeyEventByKeyCode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternWebTest, ClearKeyEventByKeyCodeTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    RefPtr<WebPattern> webPattern = nullptr;
    RefPtr<FrameNode> frameNode = nullptr;
    const std::string src = "web_pattern_focus_test";
    RefPtr<WebController> webController = AceType::MakeRefPtr<WebController>();
    EXPECT_NE(webController, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId,
        [src, webController]() { return AceType::MakeRefPtr<WebPattern>(src, webController); });
    stack->Push(frameNode);
    webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebSrc(src);
    webPattern->SetWebController(webController);
    webPattern->OnModifyDone();
    int32_t value = 1;
    webPattern->webKeyEvent_.clear();
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_HOME;
    webPattern->webKeyEvent_.push_front(keyEvent);
    webPattern->ClearKeyEventByKeyCode(value);
    EXPECT_TRUE(webPattern->webKeyEvent_.empty());
#endif
}
} // namespace OHOS::Ace::NG
