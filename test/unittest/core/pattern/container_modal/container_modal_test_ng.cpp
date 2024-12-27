/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "test/mock/core/common/mock_resource_adapter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/log/log_wrapper.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr double MOUSE_MOVE_POPUP_DISTANCE = 5.0; // 5.0px
} // namespace
class ContainerModelTestNg : public TestNG {
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
    MockPipelineContext::SetUp();
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_CONTAINER_MODAL);
    auto containerModalTheme = ContainerModalTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(containerModalTheme));
    EXPECT_CALL(*themeManager, GetThemeConstants()).WillRepeatedly(Return(themeConstants));
}

void ContainerModelTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
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
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
}

void ContainerModelTestNg::CreateContainerModal()
{
    ContainerModalView view;
    RefPtr<FrameNode> content = CreateContent();
    auto frameNode = view.Create(content);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    GetInstance();
    FlushLayoutTask(frameNode_);
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
    auto container_modal_control_buttons = frameNode_->GetChildAtIndex(2);
    auto btn = AceType::DynamicCast<FrameNode>(container_modal_control_buttons->GetChildAtIndex(index));
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
    auto container_modal_control_buttons = frameNode_->GetChildAtIndex(2);
    auto btn = AceType::DynamicCast<FrameNode>(container_modal_control_buttons->GetChildAtIndex(index));
    auto inputHub = btn->GetOrCreateInputEventHub();
    auto inputEvents = inputHub->hoverEventActuator_->inputEvents_;
    return inputEvents.front()->GetOnHoverEventFunc();
}

OnMouseEventFunc ContainerModelTestNg::GetMouseEvent(int32_t index)
{
    auto container_modal_control_buttons = frameNode_->GetChildAtIndex(2);
    auto btn = AceType::DynamicCast<FrameNode>(container_modal_control_buttons->GetChildAtIndex(index));
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
     *      |--container_modal_custom_title(row)
     *          |--custom_node(js)
     *      |--stack
     *          |--container_modal_content(stage)
     *              |--page
     *          |--dialog(when show)
     *   |--container_modal_custom_floating_title(row)
     *          |--custom_node(js)
     *   |--container_modal_control_buttons(row)
     *          |--[leftSplit, maxRecover, minimize, close](button)
     */
    CreateContainerModal();

    EXPECT_EQ(frameNode_->GetTag(), "ContainerModal");
    EXPECT_EQ(frameNode_->GetChildren().size(), 3);
    auto column = frameNode_->GetChildAtIndex(0);
    EXPECT_EQ(column->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(column->GetChildren().size(), 2);
    auto container_modal_custom_title = column->GetChildAtIndex(0);
    EXPECT_EQ(container_modal_custom_title->GetTag(), V2::ROW_ETS_TAG);
    EXPECT_EQ(container_modal_custom_title->GetChildren().size(), 1);
    auto stack = column->GetChildAtIndex(1);
    EXPECT_EQ(stack->GetTag(), V2::STACK_ETS_TAG);
    EXPECT_EQ(stack->GetChildren().size(), 1);
    auto container_modal_content = stack->GetChildAtIndex(0);
    EXPECT_EQ(container_modal_content->GetTag(), "content");
    auto container_modal_custom_floating_title = frameNode_->GetChildAtIndex(1);
    EXPECT_EQ(container_modal_custom_floating_title->GetTag(), V2::ROW_ETS_TAG);
    EXPECT_EQ(container_modal_custom_floating_title->GetChildren().size(), 1);
    auto container_modal_control_buttons = frameNode_->GetChildAtIndex(2);
    EXPECT_EQ(container_modal_control_buttons->GetTag(), V2::ROW_ETS_TAG);
    EXPECT_EQ(container_modal_control_buttons->GetChildren().size(), 4);
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
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
    CreateContainerModal();
    pattern_->ShowTitle(true, true);
    ClickBtn(0);
    ClickBtn(1);
    ClickBtn(2);
    ClickBtn(3);
    EXPECT_FALSE(isWindowStartMove);
    EXPECT_FALSE(iswindowSplitPrimary);
    EXPECT_FALSE(iswindowRecover);
    EXPECT_FALSE(windowMaximize);
    EXPECT_FALSE(windowMinimize);
    EXPECT_FALSE(windowClose);
}

/**
 * @tc.name: Test003
 * @tc.desc: Test event
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, Test003, TestSize.Level1)
{
    CreateContainerModal();
    GetHovertEvent(0)(true);
    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::PRESS);
    mouseInfo.SetLocalLocation(Offset(0, 0));
    GetMouseEvent(0)(mouseInfo);
    mouseInfo.SetAction(MouseAction::MOVE);
    GetMouseEvent(0)(mouseInfo);

    GetHovertEvent(0)(false);
    mouseInfo.SetAction(MouseAction::MOVE);
    GetMouseEvent(0)(mouseInfo);
    EXPECT_EQ(mouseInfo.GetAction(), MouseAction::MOVE);
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
    auto floatingTitleNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(1));
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

    // Set needUpdate to true
    pattern_->ShowTitle(true, true, true);
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
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::VISIBLE);

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
 * @tc.name: Test005
 * @tc.desc: WindowFocus.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, Test005, TestSize.Level1)
{
    CreateContainerModal();

    /**
     * @tc.steps: step1. set foused true.
     * @tc.expected: isFocus_ is true.
     */
    pattern_->OnWindowFocused();
    EXPECT_TRUE(pattern_->isFocus_);

    /**
     * @tc.steps: step2. set foused false.
     * @tc.expected: isFocus_ is false.
     */
    pattern_->OnWindowUnfocused();
    EXPECT_FALSE(pattern_->isFocus_);

    // coverage OnWindowForceUnfocused
    pattern_->OnWindowForceUnfocused();

    /**
     * @tc.steps: step3. Alter maxId.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_->SetCurrentWindowMaximizeMode(MaximizeMode::MODE_AVOID_SYSTEM_BAR);
    pattern_->OnWindowFocused();
    EXPECT_TRUE(pattern_->isFocus_);
}
/**
 * @tc.name: Test006
 * @tc.desc: CanShowFloatingTitle windowMode_.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, Test006, TestSize.Level1)
{
    CreateContainerModal();
    pattern_->windowMode_ = WindowMode::WINDOW_MODE_FLOATING;
    bool bResult = pattern_->CanShowFloatingTitle();
    EXPECT_FALSE(bResult);
}
/**
 * @tc.name: Test009
 * @tc.desc: AddButtonStyleMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, Test009, TestSize.Level1)
{
    CreateContainerModal();
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AccessibilityManager::MakeRefPtr<ButtonPattern>());
    auto imageIcon = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AccessibilityManager::MakeRefPtr<ImagePattern>());
    ContainerModalView::AddButtonStyleMouseEvent(buttonNode, imageIcon, false);
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

/**
 * @tc.name: VisibleTest009
 * @tc.desc: Test SetContainerModalTitleVisible.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, VisibleTest009, TestSize.Level1)
{
    CreateContainerModal();
    auto customRow = pattern_->GetCustomTitleRow();
    ASSERT_NE(customRow, nullptr);
    auto customLayoutProperty = customRow->GetLayoutProperty();
    ASSERT_NE(customLayoutProperty, nullptr);

    pattern_->windowMode_ = WindowMode::WINDOW_MODE_FLOATING;
    pattern_->SetContainerModalTitleVisible(true, true);
    EXPECT_EQ(customLayoutProperty->GetVisibility(), std::nullopt);
    pattern_->SetContainerModalTitleVisible(false, false);
    EXPECT_EQ(customLayoutProperty->GetVisibility(), VisibleType::GONE);

    pattern_->windowMode_ = WindowMode::WINDOW_MODE_FULLSCREEN;
    pattern_->SetContainerModalTitleVisible(true, true);
    EXPECT_EQ(customLayoutProperty->GetVisibility(), VisibleType::GONE);
    pattern_->SetContainerModalTitleVisible(false, false);
    EXPECT_EQ(customLayoutProperty->GetVisibility(), VisibleType::GONE);
}

/**
 * @tc.name: TitleHeightTest010
 * @tc.desc: Test SetContainerModalHeight and GetContainerModalTitleHeight.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, TitleHeightTest010, TestSize.Level1)
{
    CreateContainerModal();

    pattern_->windowMode_ = WindowMode::WINDOW_MODE_FLOATING;
    const int32_t height1 = -1;
    const int32_t height2 = 100;

    pattern_->SetContainerModalTitleVisible(true, true);
    pattern_->SetContainerModalTitleHeight(height1);
    EXPECT_EQ(pattern_->GetContainerModalTitleHeight(), 0);

    pattern_->SetContainerModalTitleVisible(false, false);
    EXPECT_EQ(pattern_->GetContainerModalTitleHeight(), 0);

    pattern_->SetContainerModalTitleHeight(height2);
    EXPECT_EQ(pattern_->GetContainerModalTitleHeight(), height2);

    pattern_->SetContainerModalTitleVisible(true, true);
    EXPECT_EQ(pattern_->GetContainerModalTitleHeight(), height2);
}

/**
 * @tc.name: ButtonsRectTest011
 * @tc.desc: Test function about ButtonsRect.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, ButtonsRectTest011, TestSize.Level1)
{
    CreateContainerModal();
    RectF containerModalRect;
    RectF buttonsRect;
    pattern_->GetContainerModalButtonsRect(containerModalRect, buttonsRect);

    auto column = pattern_->GetColumnNode();
    ASSERT_NE(column, nullptr);
    EXPECT_EQ(containerModalRect, column->GetGeometryNode()->GetFrameRect());

    auto buttonsRow = pattern_->GetControlButtonRow();
    ASSERT_NE(buttonsRow, nullptr);
    auto children = buttonsRow->GetChildren();
    auto firstButtonRect = AceType::DynamicCast<FrameNode>(children.front())->GetGeometryNode()->GetFrameRect();
    auto lastButtonRect = AceType::DynamicCast<FrameNode>(children.back())->GetGeometryNode()->GetFrameRect();
    auto childrenRect = firstButtonRect.CombineRectT(lastButtonRect);
    childrenRect.SetLeft(childrenRect.GetX() - TITLE_PADDING_START.ConvertToPx());
    childrenRect.SetTop(0);
    childrenRect.SetHeight(pattern_->titleHeight_.ConvertToPx());
    childrenRect.SetWidth(childrenRect.Width() + (TITLE_PADDING_START + TITLE_PADDING_END).ConvertToPx());
    EXPECT_EQ(buttonsRect, childrenRect);

    bool callbackTriggered = false;
    auto callback = [&callbackTriggered](RectF&, RectF&) { callbackTriggered = true; };
    pattern_->SubscribeContainerModalButtonsRectChange(std::move(callback));
    pattern_->CallButtonsRectChange();
    EXPECT_TRUE(callbackTriggered);
}

/**
 * @tc.name: AccessibilityProperty002
 * @tc.desc: Test GetText of containerModal.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, AccessibilityProperty002, TestSize.Level1)
{
    ContainerModalView view;
    RefPtr<FrameNode> content = CreateContent();
    auto frameNode = view.Create(content);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    GetInstance();
    FlushLayoutTask(frameNode_);
    pattern_->appLabel_ = "abc";
    EXPECT_EQ(accessibilityProperty_->GetText(), "abc");
}

/**
 * @tc.name: UpdateGestureRowVisible
 * @tc.desc: Test GUpdateGestureRowVisible.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, UpdateGestureRowVisible, TestSize.Level1)
{
    bool result = true;
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPattern>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPattern>();
    auto gestureRow = containerPattern->GetGestureRow();
    CHECK_NULL_VOID(gestureRow);
    auto customTitleRow = containerPattern->GetCustomTitleRow();
    CHECK_NULL_VOID(customTitleRow);
    auto buttonsRow = containerPattern->GetControlButtonRow();
    CHECK_NULL_VOID(buttonsRow);
    auto gestureRowProp = gestureRow->GetLayoutProperty();
    auto customTitleRowProp = customTitleRow->GetLayoutProperty();
    auto buttonsRowProp = buttonsRow->GetLayoutProperty();
    customTitleRowProp->UpdateVisibility(VisibleType::GONE);
    buttonsRowProp->UpdateVisibility(VisibleType::GONE);
    containerPattern->UpdateGestureRowVisible();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: UpdateGestureRowVisible2
 * @tc.desc: Test GUpdateGestureRowVisible.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, UpdateGestureRowVisible2, TestSize.Level1)
{
    bool result = true;
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPattern>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPattern>();
    auto gestureRow = containerPattern->GetGestureRow();
    CHECK_NULL_VOID(gestureRow);
    auto customTitleRow = containerPattern->GetCustomTitleRow();
    CHECK_NULL_VOID(customTitleRow);
    auto buttonsRow = containerPattern->GetControlButtonRow();
    CHECK_NULL_VOID(buttonsRow);
    auto gestureRowProp = gestureRow->GetLayoutProperty();
    auto customTitleRowProp = customTitleRow->GetLayoutProperty();
    auto buttonsRowProp = buttonsRow->GetLayoutProperty();
    customTitleRowProp->UpdateVisibility(VisibleType::GONE);
    buttonsRowProp->UpdateVisibility(VisibleType::VISIBLE);
    containerPattern->UpdateGestureRowVisible();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: UpdateGestureRowVisible3
 * @tc.desc: Test GUpdateGestureRowVisible.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, UpdateGestureRowVisible3, TestSize.Level1)
{
    bool result = true;
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPattern>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPattern>();
    auto gestureRow = containerPattern->GetGestureRow();
    CHECK_NULL_VOID(gestureRow);
    auto customTitleRow = containerPattern->GetCustomTitleRow();
    CHECK_NULL_VOID(customTitleRow);
    auto buttonsRow = containerPattern->GetControlButtonRow();
    CHECK_NULL_VOID(buttonsRow);
    auto gestureRowProp = gestureRow->GetLayoutProperty();
    auto customTitleRowProp = customTitleRow->GetLayoutProperty();
    auto buttonsRowProp = buttonsRow->GetLayoutProperty();
    customTitleRowProp->UpdateVisibility(VisibleType::VISIBLE);
    buttonsRowProp->UpdateVisibility(VisibleType::VISIBLE);
    containerPattern->UpdateGestureRowVisible();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: UpdateGestureRowVisible4
 * @tc.desc: Test GUpdateGestureRowVisible.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, UpdateGestureRowVisible4, TestSize.Level1)
{
    bool result = true;
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPattern>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPattern>();
    auto gestureRow = containerPattern->GetGestureRow();
    CHECK_NULL_VOID(gestureRow);
    auto customTitleRow = containerPattern->GetCustomTitleRow();
    CHECK_NULL_VOID(customTitleRow);
    auto buttonsRow = containerPattern->GetControlButtonRow();
    CHECK_NULL_VOID(buttonsRow);
    auto gestureRowProp = gestureRow->GetLayoutProperty();
    auto customTitleRowProp = customTitleRow->GetLayoutProperty();
    auto buttonsRowProp = buttonsRow->GetLayoutProperty();
    customTitleRowProp->UpdateVisibility(VisibleType::VISIBLE);
    buttonsRowProp->UpdateVisibility(VisibleType::GONE);
    containerPattern->UpdateGestureRowVisible();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GetContainerModalButtonsRect
 * @tc.desc: Test GetContainerModalButtonsRect
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, GetContainerModalButtonsRect, TestSize.Level1)
{
    bool result = true;
    CreateContainerModal();
    RectF containerModalRect;
    RectF buttonsRect;
    auto column = pattern_->GetColumnNode();
    auto geomeNode = column->GetGeometryNode();
    geomeNode->frame_.rect_ = { 0, 0, 0, 0 };
    pattern_->GetContainerModalButtonsRect(containerModalRect, buttonsRect);
    EXPECT_TRUE(result);
}

HWTEST_F(ContainerModelTestNg, GetContainerModalButtonsRect2, TestSize.Level1)
{
    bool result = true;
    CreateContainerModal();
    auto controlButtonsRow = pattern_->GetControlButtonRow();
    auto children = controlButtonsRow->GetChildren();
    for (auto& child : children) {
        auto node = AceType::DynamicCast<FrameNode>(child);
        node->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    }
    RectF containerModalRect;
    RectF buttonsRect;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    pattern_->GetContainerModalButtonsRect(containerModalRect, buttonsRect);
    EXPECT_TRUE(result);
}

HWTEST_F(ContainerModelTestNg, GetContainerModalButtonsRect3, TestSize.Level1)
{
    bool result = true;
    CreateContainerModal();
    RectF containerModalRect;
    RectF buttonsRect;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    pattern_->GetContainerModalButtonsRect(containerModalRect, buttonsRect);
    pattern_->InitButtonsLayoutProperty();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GetCustomTitleHeight
 * @tc.desc: Test GetCustomTitleHeight.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, GetCustomTitleHeight, TestSize.Level1)
{
    bool result = true;
    CreateContainerModal();
    pattern_->GetCustomTitleHeight();
    auto customTitleRow = pattern_->GetCustomTitleRow();
    auto property = customTitleRow->GetLayoutProperty();
    property->UpdateVisibility(VisibleType::GONE);
    pattern_->GetCustomTitleHeight();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: InitColumnTouchTestFunc
 * @tc.desc: Test InitColumnTouchTestFunc.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, InitColumnTouchTestFunc, TestSize.Level1)
{
    bool result = true;
    CreateContainerModal();
    pattern_->InitColumnTouchTestFunc();
    auto column = pattern_->GetColumnNode();
    auto eventHub = column->GetOrCreateGestureEventHub();
    const auto& Callback = eventHub->GetOnTouchTestFunc();
    std::vector<TouchTestInfo> touchInfos;
    TouchTestInfo info;
    info.id = CONTAINER_MODAL_STACK_ID;
    touchInfos.emplace_back(info);
    Callback(touchInfos);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: InitColumnTouchTestFunc2
 * @tc.desc: Test InitColumnTouchTestFunc.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, InitColumnTouchTestFunc2, TestSize.Level1)
{
    bool result = true;
    CreateContainerModal();
    pattern_->InitColumnTouchTestFunc();
    auto column = pattern_->GetColumnNode();
    auto eventHub = column->GetOrCreateGestureEventHub();
    const auto& Callback = eventHub->GetOnTouchTestFunc();
    std::vector<TouchTestInfo> touchInfos;
    TouchTestInfo info;
    touchInfos.emplace_back(info);
    Callback(touchInfos);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AddButtonHoverEvent
 * @tc.desc: Test AddButtonHoverEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, AddButtonHoverEvent, TestSize.Level1)
{
    bool result = true;
    CreateContainerModal();
    pattern_->InitColumnTouchTestFunc();
    RefPtr<FrameNode> content = CreateContent();
    ContainerModalView view;
    auto frameNode = view.Create(content);
    auto frameNode2 = view.Create(content);
    auto inputEventHub = frameNode_->GetOrCreateInputEventHub();
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    frameNode2->layoutProperty_ = imageLayoutProperty;
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo("file://data/data/com.example.test/res/example.svg", Dimension(300.0), Dimension(200.0)));
    imageLayoutProperty->UpdateAlt(
        ImageSourceInfo("file://data/data/com.example.test/res/exampleAlt.jpg", Dimension(100.0), Dimension(200.0)));
    view.AddButtonHoverEvent(inputEventHub, frameNode, frameNode2, false);

    auto hoverEventActuator = inputEventHub->hoverEventActuator_;
    auto Events = hoverEventActuator->inputEvents_;
    for (const auto& callback : Events) {
        (*callback)(false);
    }
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AddButtonHoverEvent2
 * @tc.desc: Test AddButtonHoverEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, AddButtonHoverEvent2, TestSize.Level1)
{
    bool result = true;
    CreateContainerModal();
    pattern_->InitColumnTouchTestFunc();
    RefPtr<FrameNode> content = CreateContent();
    ContainerModalView view;
    auto frameNode = view.Create(content);
    auto frameNode2 = view.Create(content);
    auto inputEventHub = frameNode_->GetOrCreateInputEventHub();
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    frameNode2->layoutProperty_ = imageLayoutProperty;
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo("file://data/data/com.example.test/res/example.svg", Dimension(300.0), Dimension(200.0)));
    imageLayoutProperty->UpdateAlt(
        ImageSourceInfo("file://data/data/com.example.test/res/exampleAlt.jpg", Dimension(100.0), Dimension(200.0)));
    view.AddButtonHoverEvent(inputEventHub, frameNode, frameNode2, true);

    auto hoverEventActuator = inputEventHub->hoverEventActuator_;
    auto Events = hoverEventActuator->inputEvents_;
    for (const auto& callback : Events) {
        (*callback)(true);
    }
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AddButtonOnEvent
 * @tc.desc: Test AddButtonOnEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, AddButtonOnEvent, TestSize.Level1)
{
    bool result = true;
    CreateContainerModal();
    pattern_->InitColumnTouchTestFunc();
    RefPtr<FrameNode> content = CreateContent();
    ContainerModalView view;
    auto frameNode = view.Create(content);
    auto frameNode2 = view.Create(content);
    auto inputEventHub = frameNode_->GetOrCreateInputEventHub();
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    frameNode2->layoutProperty_ = imageLayoutProperty;
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo("file://data/data/com.example.test/res/example.svg", Dimension(300.0), Dimension(200.0)));
    imageLayoutProperty->UpdateAlt(
        ImageSourceInfo("file://data/data/com.example.test/res/exampleAlt.jpg", Dimension(100.0), Dimension(200.0)));
    view.AddButtonOnEvent(inputEventHub, frameNode, frameNode2, true);

    auto mouseEventActuator_ = inputEventHub->mouseEventActuator_;
    auto Events = mouseEventActuator_->inputEvents_;
    MouseInfo mouseInfo;
    for (const auto& callback : Events) {
        (*callback)(mouseInfo);
    }
    mouseInfo.action_ = MouseAction::PRESS;
    for (const auto& callback : Events) {
        (*callback)(mouseInfo);
    }
    mouseInfo.action_ = MouseAction::RELEASE;
    for (const auto& callback : Events) {
        (*callback)(mouseInfo);
    }
    EXPECT_TRUE(result);
}
} // namespace OHOS::Ace::NG
