/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#define protected public
#include "base/log/log_wrapper.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/test/mock/mock_resource_adapter.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_ng/test/pattern/test_ng.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr double MOUSE_MOVE_POPUP_DISTANCE = 5.0; // 5.0px
} // namespace
class ContainerModelTestNg : public testing::Test, public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    RefPtr<FrameNode> CreateContent();
    void SetMockWindow(WindowMode windowMode);
    void CreateContainerModal();
    void Touch(TouchLocationInfo locationInfo);
    void Touch(Offset downOffset, Offset moveOffset, Offset upOffset);
    void Mouse(MouseInfo mouseInfo);
    void Mouse(Offset moveOffset);
    void ClickBtn(int32_t index);
    OnHoverEventFunc GetHovertEvent(int32_t index);
    OnMouseEventFunc GetMouseEvent(int32_t index);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ContainerModalPattern> pattern_;
    RefPtr<LayoutProperty> layoutProperty_;
    RefPtr<ContainerModalAccessibilityProperty> accessibilityProperty_;
};

void ContainerModelTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(*themeManager, GetThemeConstants()).WillRepeatedly(Return(themeConstants));
}

void ContainerModelTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

void ContainerModelTestNg::SetUp()
{
    SetMockWindow(WindowMode::WINDOW_MODE_FULLSCREEN);
}

void ContainerModelTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void ContainerModelTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ContainerModalPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ContainerModalAccessibilityProperty>();
}

RefPtr<FrameNode> ContainerModelTestNg::CreateContent()
{
    return AceType::MakeRefPtr<FrameNode>("content", 0, AceType::MakeRefPtr<Pattern>());
}

void ContainerModelTestNg::SetMockWindow(WindowMode windowMode)
{
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    auto pipeline = MockPipelineBase::GetCurrent();
    pipeline->windowManager_ = windowManager;
}

void ContainerModelTestNg::CreateContainerModal()
{
    ContainerModalView view;
    RefPtr<FrameNode> content = CreateContent();
    auto frameNode = view.Create(content);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    GetInstance();
    RunMeasureAndLayout(frameNode_);
}

void ContainerModelTestNg::Touch(TouchLocationInfo locationInfo)
{
    auto touchEventHub = frameNode_->GetOrCreateGestureEventHub();
    auto touchEvent = touchEventHub->touchEventActuator_->userCallback_->GetTouchEventCallback();
    TouchEventInfo eventInfo("touch");
    eventInfo.AddChangedTouchLocationInfo(std::move(locationInfo));
    touchEvent(eventInfo);
}

void ContainerModelTestNg::Touch(Offset downOffset, Offset moveOffset, Offset upOffset)
{
    TouchLocationInfo locationInfo(1);
    locationInfo.SetTouchType(TouchType::DOWN);
    locationInfo.SetGlobalLocation(downOffset);
    Touch(locationInfo);
    locationInfo.SetTouchType(TouchType::MOVE);
    locationInfo.SetGlobalLocation(moveOffset);
    Touch(locationInfo);
    locationInfo.SetTouchType(TouchType::UP);
    locationInfo.SetGlobalLocation(upOffset);
    Touch(locationInfo);
}

void ContainerModelTestNg::Mouse(MouseInfo mouseInfo)
{
    auto mouseEventHub = frameNode_->GetOrCreateInputEventHub();
    auto mouseEvent = mouseEventHub->mouseEventActuator_->userCallback_->GetOnMouseEventFunc();
    mouseEvent(mouseInfo);
}

void ContainerModelTestNg::Mouse(Offset moveOffset)
{
    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::MOVE);
    mouseInfo.SetLocalLocation(moveOffset);
    Mouse(mouseInfo);
}

void ContainerModelTestNg::ClickBtn(int32_t index)
{
    auto column = frameNode_->GetChildAtIndex(0);
    auto container_modal_title = column->GetChildAtIndex(0);
    auto btn = AceType::DynamicCast<FrameNode>(container_modal_title->GetChildAtIndex(index));
    auto eventHub = btn->GetOrCreateGestureEventHub();
    eventHub->clickEventActuator_ =
        AceType::MakeRefPtr<ClickEventActuator>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    GestureEventFunc callback = [](GestureEvent& info) {};
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(callback));
    eventHub->clickEventActuator_->AddClickEvent(clickEvent);
    auto clickEvents = eventHub->clickEventActuator_->clickEvents_;
    GestureEvent info;
    clickEvents.front()->GetGestureEventFunc()(info);
}

OnHoverEventFunc ContainerModelTestNg::GetHovertEvent(int32_t index)
{
    auto column = frameNode_->GetChildAtIndex(0);
    auto container_modal_title = column->GetChildAtIndex(0);
    auto btn = AceType::DynamicCast<FrameNode>(container_modal_title->GetChildAtIndex(index));
    auto inputHub = btn->GetOrCreateInputEventHub();
    auto inputEvents = inputHub->hoverEventActuator_->inputEvents_;
    return inputEvents.front()->GetOnHoverEventFunc();
}

OnMouseEventFunc ContainerModelTestNg::GetMouseEvent(int32_t index)
{
    auto column = frameNode_->GetChildAtIndex(0);
    auto container_modal_title = column->GetChildAtIndex(0);
    auto btn = AceType::DynamicCast<FrameNode>(container_modal_title->GetChildAtIndex(index));
    auto inputHub = btn->GetOrCreateInputEventHub();
    auto inputEvents = inputHub->mouseEventActuator_->inputEvents_;
    return inputEvents.front()->GetOnMouseEventFunc();
}

/**
 * @tc.name: Test001
 * @tc.desc: Test ContainerModel Child
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, Test001, TestSize.Level1)
{
    /**
     * The structure of container_modal is designed as follows :
     * |--container_modal(stack)
     *   |--column
     *      |--container_modal_title(row)
     *          |--icon(image), label(text), [leftSplit, maxRecover, minimize, close](button)
     *      |--stack
     *          |--container_modal_content(stage)
     *              |--page
     *          |--dialog(when show)
     *   |--container_modal_floating_title(row)
     *          |--icon(image), label(text), [leftSplit, maxRecover, minimize, close](button)
     */
    CreateContainerModal();

    EXPECT_EQ(frameNode_->GetTag(), "ContainerModal");
    EXPECT_EQ(frameNode_->GetChildren().size(), 2);
    auto column = frameNode_->GetChildAtIndex(0);
    EXPECT_EQ(column->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(column->GetChildren().size(), 2);
    auto container_modal_title = column->GetChildAtIndex(0);
    EXPECT_EQ(container_modal_title->GetTag(), V2::ROW_ETS_TAG);
    EXPECT_EQ(container_modal_title->GetChildren().size(), 6);
    auto stack = column->GetChildAtIndex(1);
    EXPECT_EQ(stack->GetTag(), V2::STACK_ETS_TAG);
    EXPECT_EQ(stack->GetChildren().size(), 1);
    auto container_modal_content = stack->GetChildAtIndex(0);
    EXPECT_EQ(container_modal_content->GetTag(), "content");
    auto container_modal_floating_title = frameNode_->GetChildAtIndex(1);
    EXPECT_EQ(container_modal_floating_title->GetTag(), V2::ROW_ETS_TAG);
    EXPECT_EQ(container_modal_title->GetChildren().size(), 6);
}

/**
 * @tc.name: Test002
 * @tc.desc: Test event
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, Test002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set callback
     * @tc.expected: call is triggered
     */
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    MaximizeMode maximizeMode = MaximizeMode::MODE_AVOID_SYSTEM_BAR;
    windowManager->SetCurrentWindowMaximizeMode(maximizeMode);
    WindowMode windowMode = WindowMode::WINDOW_MODE_FULLSCREEN;
    auto windowModeCallback = [&windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    bool isWindowStartMove = false;
    bool iswindowSplitPrimary = false;
    bool iswindowRecover = false;
    bool windowMaximize = false;
    bool windowMinimize = false;
    bool windowClose = false;
    auto windowStartMoveCallBack = [&isWindowStartMove]() { isWindowStartMove = true; };
    auto windowSplitPrimaryCallBack = [&iswindowSplitPrimary]() { iswindowSplitPrimary = true; };
    auto windowRecoverCallBack = [&iswindowRecover]() { iswindowRecover = true; };
    auto windowMaximizeCallBack = [&windowMaximize]() { windowMaximize = true; };
    auto windowMinimizeCallBack = [&windowMinimize]() { windowMinimize = true; };
    auto windowCloseCallBack = [&windowClose]() { windowClose = true; };
    windowManager->SetWindowStartMoveCallBack(std::move(windowStartMoveCallBack));
    windowManager->SetWindowSplitPrimaryCallBack(std::move(windowSplitPrimaryCallBack));
    windowManager->SetWindowRecoverCallBack(std::move(windowRecoverCallBack));
    windowManager->SetWindowMaximizeCallBack(std::move(windowMaximizeCallBack));
    windowManager->SetWindowMinimizeCallBack(std::move(windowMinimizeCallBack));
    windowManager->SetWindowCloseCallBack(std::move(windowCloseCallBack));
    auto pipeline = MockPipelineBase::GetCurrent();
    pipeline->windowManager_ = windowManager;
    CreateContainerModal();
    auto column = frameNode_->GetChildAtIndex(0);
    auto container_modal_title = AceType::DynamicCast<FrameNode>(column->GetChildAtIndex(0));
    auto eventHub = container_modal_title->GetOrCreateGestureEventHub();
    GestureEvent info;
    auto panEvents = eventHub->panEventActuator_->panEvents_;
    panEvents.front()->GetActionStartEventFunc()(info);
    ClickBtn(2);
    ClickBtn(3);
    ClickBtn(4);
    ClickBtn(5);
    EXPECT_FALSE(isWindowStartMove);
    EXPECT_TRUE(iswindowSplitPrimary);
    EXPECT_TRUE(iswindowRecover);
    EXPECT_FALSE(windowMaximize);
    EXPECT_TRUE(windowMinimize);
    EXPECT_TRUE(windowClose);

    /**
     * @tc.steps: step2. set callback
     * @tc.expected: call is triggered
     */
    maximizeMode = MaximizeMode::MODE_FULL_FILL;
    windowManager->SetCurrentWindowMaximizeMode(maximizeMode);
    windowMode = WindowMode::WINDOW_MODE_SPLIT_PRIMARY;
    CreateContainerModal();
    column = frameNode_->GetChildAtIndex(0);
    container_modal_title = AceType::DynamicCast<FrameNode>(column->GetChildAtIndex(0));
    eventHub = container_modal_title->GetOrCreateGestureEventHub();
    panEvents = eventHub->panEventActuator_->panEvents_;
    panEvents.front()->GetActionStartEventFunc()(info);
    ClickBtn(3);
    EXPECT_TRUE(isWindowStartMove);
    EXPECT_TRUE(windowMaximize);
}

/**
 * @tc.name: Test003
 * @tc.desc: Test event
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, Test003, TestSize.Level1)
{
    CreateContainerModal();
    GetHovertEvent(2)(true);
    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::PRESS);
    mouseInfo.SetLocalLocation(Offset(0, 0));
    GetMouseEvent(2)(mouseInfo);
    mouseInfo.SetAction(MouseAction::MOVE);
    GetMouseEvent(2)(mouseInfo);

    GetHovertEvent(2)(false);
    mouseInfo.SetAction(MouseAction::MOVE);
    GetMouseEvent(2)(mouseInfo);
    SUCCEED();
}

/**
 * @tc.name: Test004
 * @tc.desc: Test InitContainerEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, Test004, TestSize.Level1)
{
    CreateContainerModal();

    /**
     * @tc.steps: step1. When hasDeco_ is false
     * @tc.expected: Do nothing
     */
    pattern_->ShowTitle(true, false);
    auto floatingTitleNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildren().back());
    auto floatingLayoutProperty = floatingTitleNode->GetLayoutProperty();
    Touch(Offset::Zero(), Offset::Zero(), Offset::Zero());
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::GONE);

    Mouse(Offset::Zero());
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::GONE);

    /**
     * @tc.steps: step2. When MouseAction is not MOVE
     * @tc.expected: Do nothing
     */
    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::PRESS);
    mouseInfo.SetLocalLocation(Offset(0, 0));
    Mouse(mouseInfo);
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::GONE);

    /**
     * @tc.steps: step3. Set hasDeco_ to true
     */
    pattern_->ShowTitle(true, true);

    /**
     * @tc.steps: step4. Touch outSide
     * @tc.expected: Do nothing
     */
    constexpr double movePopupDistanceX = 10.0;
    constexpr double movePopupDistanceY = 20.0;
    constexpr double titlePopupDistance = 37.0;

    Offset outOffset = Offset(0, titlePopupDistance + 1);
    Touch(outOffset, outOffset, outOffset);
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::GONE);

    /**
     * @tc.steps: step5. Touch inSide but deltaMoveY < movePopupDistanceY
     * @tc.expected: Do nothing
     */
    Offset inOffset_1 = Offset(movePopupDistanceX, movePopupDistanceY - 1);
    Touch(Offset::Zero(), inOffset_1, inOffset_1);
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::GONE);

    /**
     * @tc.steps: step6. Touch inSide but deltaMoveX > movePopupDistanceX
     * @tc.expected: Do nothing
     */
    Offset inOffset_2 = Offset(movePopupDistanceX + 1, movePopupDistanceY);
    Touch(Offset::Zero(), inOffset_2, inOffset_2);
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::GONE);

    /**
     * @tc.steps: step7. Touch inSide
     * @tc.expected: float node would VISIBLE
     */
    Offset inOffset_3 = Offset(movePopupDistanceX, movePopupDistanceY);
    Touch(Offset::Zero(), inOffset_3, inOffset_3);
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::VISIBLE);

    /**
     * @tc.steps: step8. Touch outSide
     * @tc.expected: float node would GONE by Animate()
     */
    Touch(outOffset, outOffset, outOffset);
    floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);

    /**
     * @tc.steps: step9. Mouse move > MOUSE_MOVE_POPUP_DISTANCE
     * @tc.expected: Do nothing
     */
    Mouse(Offset(0, MOUSE_MOVE_POPUP_DISTANCE + 1));
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::GONE);

    /**
     * @tc.steps: step10. Mouse move outSide
     * @tc.expected: Do nothing
     */
    Mouse(Offset(0, titlePopupDistance));
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::GONE);

    /**
     * @tc.steps: step11. Mouse move <= MOUSE_MOVE_POPUP_DISTANCE
     * @tc.expected: float node would VISIBLE
     */
    Mouse(Offset(0, MOUSE_MOVE_POPUP_DISTANCE));
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::VISIBLE);

    /**
     * @tc.steps: step12. Mouse move <= MOUSE_MOVE_POPUP_DISTANCE again
     * @tc.expected: The CanShowFloatingTitle() is false, Do nothing
     */
    Mouse(Offset(0, MOUSE_MOVE_POPUP_DISTANCE));
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::VISIBLE);

    /**
     * @tc.steps: step13. Mouse move outSide
     * @tc.expected: float node would GONE by Animate()
     */
    Mouse(Offset(0, titlePopupDistance));
    floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
}

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test GetText of containerModal.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, AccessibilityProperty001, TestSize.Level1)
{
    CreateContainerModal();
    EXPECT_EQ(accessibilityProperty_->GetText(), "");
}
} // namespace OHOS::Ace::NG
