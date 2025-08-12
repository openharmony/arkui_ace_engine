/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#define private public
#include "core/common/frontend.h"
#include "core/common/window.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::NWeb;
using namespace OHOS::Ace;
using namespace OHOS::Rosen;

namespace OHOS::Ace::NG {
namespace {
#ifdef OHOS_STANDARD_SYSTEM
bool g_isEnable = false;
float g_alpha = 0;
int32_t g_Y = 1;
float g_height = 0;

int32_t g_editStateFlags = 0;

int32_t CONTRNT_WIDTH_SIZE = 1024;
int32_t CONTRNT_HEIGHT_SIZE = 99999;

std::shared_ptr<NWebTouchHandleState> g_insertHandle = nullptr;
std::shared_ptr<NWebTouchHandleState> g_startSelectionHandle = nullptr;
std::shared_ptr<NWebTouchHandleState> g_endSelectionHandle = nullptr;

RefPtr<WebPattern> g_webPattern = nullptr;
#endif
} // namespace

class WebPatternTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternTest::SetUpTestCase()
{
#ifdef OHOS_STANDARD_SYSTEM
    std::string src = "web_test";
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, [src, controller]() { return AceType::MakeRefPtr<WebPattern>(src, controller); });
    stack->Push(frameNode);

    g_webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(g_webPattern);
    g_webPattern->SetWebSrc(src);
    g_webPattern->SetWebController(controller);
#endif
}
void WebPatternTest::TearDownTestCase()
{
#ifdef OHOS_STANDARD_SYSTEM
    g_webPattern = nullptr;
#endif
}

void WebPatternTest::SetUp() {}
void WebPatternTest::TearDown() {}

#ifdef OHOS_STANDARD_SYSTEM
class NWebTouchHandleStateMock : public NWebTouchHandleState {
public:
    int32_t GetTouchHandleId() override
    {
        return 0;
    }

    int32_t GetX() override
    {
        return 0;
    }

    int32_t GetY() override
    {
        return g_Y;
    }

    int32_t GetViewPortX() override
    {
        return 0;
    }

    int32_t GetViewPortY() override
    {
        return 0;
    }

    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::INSERT_HANDLE;
    }

    bool IsEnable() override
    {
        return g_isEnable;
    }

    float GetAlpha() override
    {
        return g_alpha;
    }

    float GetEdgeHeight() override
    {
        return g_height;
    }
};

class NWebQuickMenuParamsMock : public NWebQuickMenuParams {
public:
    int32_t GetXCoord() override
    {
        return 0;
    }

    int32_t GetYCoord() override
    {
        return 0;
    }

    int32_t GetWidth() override
    {
        return 0;
    }

    int32_t GetHeight() override
    {
        return 0;
    }

    int32_t GetEditStateFlags() override
    {
        return g_editStateFlags;
    }

    int32_t GetSelectX() override
    {
        return 0;
    }
    int32_t GetSelectY() override
    {
        return 0;
    }

    int32_t GetSelectWidth() override
    {
        return 0;
    }

    int32_t GetSelectXHeight() override
    {
        return 0;
    }

    std::shared_ptr<NWebTouchHandleState> GetTouchHandleState(NWebTouchHandleState::TouchHandleType type) override
    {
        if (type == NWebTouchHandleState::TouchHandleType::INSERT_HANDLE) {
            return g_insertHandle;
        } else if (type == NWebTouchHandleState::TouchHandleType::SELECTION_BEGIN_HANDLE) {
            return g_startSelectionHandle;
        }
        return g_endSelectionHandle;
    }

    bool GetIsLongPressActived() override
    {
        return false;
    }
};

class NWebQuickMenuCallbackMock : public NWebQuickMenuCallback {
public:
    void Continue(int32_t commandId, MenuEventFlags flag) {}

    void Cancel() {}
};
#endif

/**
 * @tc.name: OnModifyDoneTest001
 * @tc.desc: Test OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTest, OnModifyDoneTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    g_webPattern->OnModifyDone();
    int32_t width = 1;
    int32_t height = 1;
    double keyboard = 0;
    g_webPattern->isFocus_ = false;
    bool result = g_webPattern->ProcessVirtualKeyBoard(width, height, keyboard);
    EXPECT_FALSE(result);
    g_webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_SHOW;
    result = g_webPattern->ProcessVirtualKeyBoard(width, height, keyboard);
    EXPECT_FALSE(result);
    g_webPattern->isFocus_ = true;
    result = g_webPattern->ProcessVirtualKeyBoard(width, height, keyboard);
    EXPECT_FALSE(result);
    keyboard = 1;
    result = g_webPattern->ProcessVirtualKeyBoard(width, height, keyboard);
    EXPECT_FALSE(result);
    g_webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_HIDE;
    result = g_webPattern->ProcessVirtualKeyBoard(width, height, keyboard);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: HandleTouchDownTest002
 * @tc.desc: Test HandleTouchDownTest002.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTest, HandleTouchDownTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int32_t fingerId = 0;
    g_webPattern->OnModifyDone();
    int32_t width = 1;
    int32_t height = 1;
    double keyboard = 1;
    g_webPattern->isFocus_ = true;
    g_webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_HIDE;
    auto drawSize = Size(CONTRNT_WIDTH_SIZE, CONTRNT_HEIGHT_SIZE);
    g_webPattern->drawSizeCache_ = drawSize;
    bool result = g_webPattern->ProcessVirtualKeyBoard(width, height, keyboard);
    EXPECT_FALSE(result);
    TouchLocationInfo info("webtest", fingerId);
    TouchEventInfo event("webtest");
    g_webPattern->HandleTouchUp(event, true);
    g_webPattern->HandleTouchDown(event, true);
    g_webPattern->HandleTouchMove(event, true);
    g_webPattern->isDragging_ = true;
    g_webPattern->HandleTouchMove(event, true);

    event.AddTouchLocationInfo(std::move(info));
    g_webPattern->HandleTouchUp(event, true);
    g_webPattern->HandleTouchDown(event, true);
    g_webPattern->HandleTouchMove(event, true);
    g_webPattern->HandleTouchCancel(event);
    g_webPattern->RequestFullScreen();
    g_webPattern->ExitFullScreen();
    g_webPattern->isFullScreen_ = true;
    g_webPattern->ExitFullScreen();
#endif
}

/**
 * @tc.name: OnOverviewUpdateTest008
 * @tc.desc: Test OnOverviewModeAccessEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTest, OnOverviewUpdateTest008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    g_webPattern->OnModifyDone();
    int32_t value = 0;
    float scale = 0;
    int x = 0;
    int y = 0;
    EXPECT_NE(g_webPattern->delegate_, nullptr);
    g_webPattern->OnPinchSmoothModeEnabledUpdate(true);
    g_webPattern->OnWebDebuggingAccessEnabledAndPortUpdate(std::make_tuple(true, 0));
    g_webPattern->OnTextZoomRatioUpdate(value);
    g_webPattern->OnDatabaseAccessEnabledUpdate(true);
    g_webPattern->OnFileFromUrlAccessEnabledUpdate(true);
    g_webPattern->OnOverviewModeAccessEnabledUpdate(true);
    g_webPattern->OnBackgroundColorUpdate(value);
    g_webPattern->OnInitialScaleUpdate(scale);
    g_webPattern->OnMultiWindowAccessEnabledUpdate(true);
    g_webPattern->HandleDragStart(x, y);
    g_webPattern->isW3cDragEvent_ = true;
    DragDropInfo dragDropInfo;
    bool result = g_webPattern->GenerateDragDropInfo(dragDropInfo);
    EXPECT_FALSE(result);
    g_webPattern->delegate_->pixelMap_ = nullptr;
    result = g_webPattern->GenerateDragDropInfo(dragDropInfo);
    EXPECT_FALSE(result);
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    RefPtr<WebPattern> webPattern = AceType::MakeRefPtr<WebPattern>("test", controller);
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnPinchSmoothModeEnabledUpdate(true);
    webPattern->OnWebDebuggingAccessEnabledAndPortUpdate(std::make_tuple(true, 0));
    webPattern->OnTextZoomRatioUpdate(value);
    webPattern->OnDatabaseAccessEnabledUpdate(true);
    webPattern->OnFileFromUrlAccessEnabledUpdate(true);
    webPattern->OnOverviewModeAccessEnabledUpdate(true);
    webPattern->OnBackgroundColorUpdate(value);
    webPattern->OnInitialScaleUpdate(scale);
    webPattern->OnMultiWindowAccessEnabledUpdate(true);
    webPattern->isW3cDragEvent_ = false;
    result = webPattern->GenerateDragDropInfo(dragDropInfo);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: HandleDoubleClickEventTest009
 * @tc.desc: Test HandleDoubleClickEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTest, HandleDoubleClickEventTest009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::NONE);
    std::queue<MouseClickInfo> empty;
    swap(empty, g_webPattern->mouseClickQueue_);
    g_webPattern->HandleDoubleClickEvent(info);
    EXPECT_FALSE(g_webPattern->HandleDoubleClickEvent(info));
#endif
}

/**
 * @tc.name: HandleDragUpdateTest010
 * @tc.desc: Test HandleDragUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTest, HandleDragUpdateTest010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    g_webPattern->OnModifyDone();
    GestureEvent info;
    int x = 0;
    int y = 0;
    g_webPattern->isW3cDragEvent_ = false;
    g_webPattern->HandleDragCancel();
    g_webPattern->HandleDragEnd(x, y);
    g_webPattern->isW3cDragEvent_ = true;
    g_webPattern->HandleDragCancel();
    g_webPattern->HandleDragEnd(x, y);
    g_webPattern->needUpdateWeb_ = false;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    g_webPattern->RegistVirtualKeyBoardListener(pipelineContext);

    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    RefPtr<WebPattern> webPattern = AceType::MakeRefPtr<WebPattern>("test", controller);
    EXPECT_NE(webPattern, nullptr);
    webPattern->isW3cDragEvent_ = true;
    webPattern->HandleDragEnd(x, y);
    g_webPattern->HandleDragCancel();
    webPattern->isW3cDragEvent_ = false;
    webPattern->HandleDragEnd(x, y);
    g_webPattern->HandleDragCancel();
#endif
}

/**
 * @tc.name: OnWindowShowTest011
 * @tc.desc: Test OnWindowShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTest, OnWindowShowTest011, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    g_webPattern->OnModifyDone();
    g_webPattern->isWindowShow_ = true;
    g_webPattern->OnWindowShow();
    g_webPattern->OnWindowHide();
    g_webPattern->isWindowShow_ = false;
    g_webPattern->OnWindowHide();
    g_webPattern->OnWindowShow();
    EXPECT_TRUE(g_webPattern->isWindowShow_);

    g_webPattern->isActive_ = true;
    g_webPattern->OnActive();
    g_webPattern->OnInActive();
    g_webPattern->isActive_ = false;
    g_webPattern->OnInActive();
    g_webPattern->OnActive();
    EXPECT_TRUE(g_webPattern->isActive_);

    g_webPattern->OnVisibleChange(false);
    g_webPattern->OnVisibleChange(true);
#endif
}

/**
 * @tc.name: MenuAvoidKeyboard
 * @tc.desc: Test MenuAvoidKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTest, MenuAvoidKeyboard, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    bool result = g_webPattern->MenuAvoidKeyboard(true, 0.0);
    EXPECT_TRUE(result);
    result = g_webPattern->MenuAvoidKeyboard(false, 0.0);
    EXPECT_TRUE(result);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: SetLinkPreviewSelectionMenu001
 * @tc.desc: Test SetPreviewSelectionMenu for link.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTest, SetLinkPreviewSelectionMenu001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    std::function<void()> menuBuilder = nullptr;
    std::function<void()> previewBuilder = nullptr;
    NG::MenuParam menuParam;
    std::shared_ptr<WebPreviewSelectionMenuParam> param = std::make_shared<WebPreviewSelectionMenuParam>(
        WebElementType::LINK, ResponseType::LONG_PRESS, menuBuilder, previewBuilder, menuParam);
    g_webPattern->SetPreviewSelectionMenu(param);
#endif
}

/**
 * @tc.name: ProcessVirtualKeyBoardShowAvoidMenu
 * @tc.desc: Test ProcessVirtualKeyBoardShowAvoidMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTest, ProcessVirtualKeyBoardShowAvoidMenu, TestSize.Level1)
{
    bool result;
    result = g_webPattern->ProcessVirtualKeyBoardShowAvoidMenu(0, 1280, 0.0, false);
    EXPECT_TRUE(result);
    result = g_webPattern->ProcessVirtualKeyBoardShowAvoidMenu(0, 1280, 0.0, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ProcessVirtualKeyBoardHideAvoidMenu
 * @tc.desc: Test ProcessVirtualKeyBoardHideAvoidMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTest, ProcessVirtualKeyBoardHideAvoidMenu, TestSize.Level1)
{
    bool result;
    g_webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_SHOW;
    result = g_webPattern->ProcessVirtualKeyBoardHideAvoidMenu(0, 1280, false);
    EXPECT_TRUE(result);

    g_webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_SHOW;
    result = g_webPattern->ProcessVirtualKeyBoardHideAvoidMenu(0, 1280, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: UpdateScrollBarWithBorderRadius
 * @tc.desc: Test UpdateScrollBarWithBorderRadius.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTest, UpdateScrollBarWithBorderRadius, TestSize.Level1)
{
    std::string src = "web_test";
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    ASSERT_NE(controller, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, [src, controller]() { return AceType::MakeRefPtr<WebPattern>(src, controller); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    RefPtr<WebPattern> webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    auto host = webPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto renderContext = host->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    BorderRadiusProperty borderRadius;

    webPattern->UpdateScrollBarWithBorderRadius();
    bool borderRadiusStructHasValue = renderContext->GetBorderRadius().has_value();
    EXPECT_FALSE(borderRadiusStructHasValue);
    webPattern->UpdateScrollBarWithBorderRadius();
    bool hasBorderRadiusValue = borderRadius.radiusTopLeft.has_value();
    EXPECT_FALSE(hasBorderRadiusValue);
    
    borderRadius.radiusTopLeft = Dimension(10.0f);
    borderRadius.radiusTopRight = Dimension(20.0f);
    borderRadius.radiusBottomLeft = Dimension(30.0f);
    borderRadius.radiusBottomRight = Dimension(40.0f);
    renderContext->UpdateBorderRadius(borderRadius);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto clipState = renderContext->GetClipEdge().value_or(false);
    webPattern->UpdateScrollBarWithBorderRadius();
    renderContext->UpdateClipEdge(true);
    clipState = renderContext->GetClipEdge().value_or(false);
    webPattern->UpdateScrollBarWithBorderRadius();

    borderRadiusStructHasValue = renderContext->GetBorderRadius().has_value();
    webPattern->UpdateScrollBarWithBorderRadius();
    EXPECT_TRUE(borderRadiusStructHasValue);
    hasBorderRadiusValue = !borderRadius.radiusTopLeft.has_value();
    webPattern->UpdateScrollBarWithBorderRadius();
    EXPECT_FALSE(hasBorderRadiusValue);
}

/**
 * @tc.name: IsShowHandle
 * @tc.desc: Test IsShowHandle.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTest, IsShowHandle, TestSize.Level1)
{
    std::string src = "web_test";
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    ASSERT_NE(controller, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, [src, controller]() { return AceType::MakeRefPtr<WebPattern>(src, controller); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    RefPtr<WebPattern> webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    auto result = webPattern->IsShowHandle();
    EXPECT_FALSE(result);
    webPattern->webSelectOverlay_ = AceType::MakeRefPtr<WebSelectOverlay>(webPattern);
    ASSERT_NE(webPattern->webSelectOverlay_, nullptr);
    webPattern->webSelectOverlay_->isShowHandle_ = true;
    result = webPattern->IsShowHandle();
    EXPECT_TRUE(result);
}
} // namespace OHOS::Ace::NG
