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

#include <optional>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_resource_adapter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/test_ng.h"


#include "base/subwindow/subwindow_manager.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class ContainerModalViewEnhanceTestNg : public TestNG {
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

void ContainerModalViewEnhanceTestNg::SetUpTestSuite()
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

void ContainerModalViewEnhanceTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ContainerModalViewEnhanceTestNg::SetUp()
{
    SetMockWindow(WindowMode::WINDOW_MODE_FULLSCREEN);
}

void ContainerModalViewEnhanceTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void ContainerModalViewEnhanceTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ContainerModalPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ContainerModalAccessibilityProperty>();
}

RefPtr<FrameNode> ContainerModalViewEnhanceTestNg::CreateContent()
{
    return AceType::MakeRefPtr<FrameNode>("content", 0, AceType::MakeRefPtr<Pattern>());
}

void ContainerModalViewEnhanceTestNg::SetMockWindow(WindowMode windowMode)
{
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
}

void ContainerModalViewEnhanceTestNg::CreateContainerModal()
{
    ContainerModalView view;
    RefPtr<FrameNode> content = CreateContent();
    auto frameNode = view.Create(content);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    GetInstance();
    FlushLayoutTask(frameNode_);
}

void ContainerModalViewEnhanceTestNg::Touch(TouchLocationInfo locationInfo)
{
    auto touchEventHub = frameNode_->GetOrCreateGestureEventHub();
    auto touchEvent = touchEventHub->touchEventActuator_->userCallback_->GetTouchEventCallback();
    TouchEventInfo eventInfo("touch");
    eventInfo.AddChangedTouchLocationInfo(std::move(locationInfo));
    touchEvent(eventInfo);
}

void ContainerModalViewEnhanceTestNg::Touch(Offset downOffset, Offset moveOffset, Offset upOffset)
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

void ContainerModalViewEnhanceTestNg::Mouse(MouseInfo mouseInfo)
{
    auto mouseEventHub = frameNode_->GetOrCreateInputEventHub();
    auto mouseEvent = mouseEventHub->mouseEventActuator_->userCallback_->GetOnMouseEventFunc();
    mouseEvent(mouseInfo);
}

void ContainerModalViewEnhanceTestNg::Mouse(Offset moveOffset)
{
    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::MOVE);
    mouseInfo.SetLocalLocation(moveOffset);
    Mouse(mouseInfo);
}

void ContainerModalViewEnhanceTestNg::ClickBtn(int32_t index)
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

OnHoverEventFunc ContainerModalViewEnhanceTestNg::GetHovertEvent(int32_t index)
{
    auto container_modal_control_buttons = frameNode_->GetChildAtIndex(2);
    auto btn = AceType::DynamicCast<FrameNode>(container_modal_control_buttons->GetChildAtIndex(index));
    auto inputHub = btn->GetOrCreateInputEventHub();
    auto inputEvents = inputHub->hoverEventActuator_->inputEvents_;
    return inputEvents.front()->GetOnHoverEventFunc();
}

OnMouseEventFunc ContainerModalViewEnhanceTestNg::GetMouseEvent(int32_t index)
{
    auto container_modal_control_buttons = frameNode_->GetChildAtIndex(2);
    auto btn = AceType::DynamicCast<FrameNode>(container_modal_control_buttons->GetChildAtIndex(index));
    auto inputHub = btn->GetOrCreateInputEventHub();
    auto inputEvents = inputHub->mouseEventActuator_->inputEvents_;
    return inputEvents.front()->GetOnMouseEventFunc();
}

/**
 * @tc.name: ContainerModalViewEnhanceTest001
 * @tc.desc: Test SetTapGestureEvent with window mode split to recover window
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTest001, TestSize.Level1)
{
    CreateContainerModal();

    auto gestureRow = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(2));
    ContainerModalViewEnhance containerModalViewEnhance;
    containerModalViewEnhance.SetTapGestureEvent(frameNode_, gestureRow);
    ClickBtn(0);
    ClickBtn(1);
    ClickBtn(2);
    ClickBtn(3);
    EXPECT_TRUE(frameNode_);
}

/**
 * @tc.name: ContainerModalViewEnhanceTest002
 * @tc.desc: Test SetTapGestureEvent with window mode split to recover window
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTest002, TestSize.Level1)
{
    CreateContainerModal();

    auto gestureRow = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(2));
    ContainerModalViewEnhance containerModalViewEnhance;
    containerModalViewEnhance.AddControlButtons(frameNode_, gestureRow);
    ClickBtn(0);
    ClickBtn(1);
    ClickBtn(2);
    ClickBtn(3);
    EXPECT_TRUE(frameNode_);
}
} // namespace OHOS::Ace::NG