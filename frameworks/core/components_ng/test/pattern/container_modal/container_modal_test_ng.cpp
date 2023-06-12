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
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float DEVICE_WIDTH = 480.f;
constexpr float DEVICE_HEIGHT = 800.f;
const std::string CONTAINER_MODAL_NODE_TAG = "ContainerModalNode";
const std::string TITLE_NODE_TAG = "TitleNode";
const std::string TITLE_LABEL_NODE_TAG = "TitleLabelNode";
} // namespace
class ContainerModelTestNg : public testing::Test {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    RefPtr<LayoutWrapper> RunMeasureAndLayout(float width = DEVICE_WIDTH, float height = DEVICE_HEIGHT);
    static void SetWidth(const Dimension& width);
    static void SetHeight(const Dimension& height);
    RefPtr<FrameNode> CreateContent();
    void SetMockWindow(WindowMode windowMode);
    void CreateContainerModal();
    void Touch(TouchLocationInfo locationInfo);
    void Touch(Offset downOffset, Offset moveOffset, Offset upOffset);
    void Mouse(MouseInfo mouseInfo);
    void Mouse(Offset moveOffset);

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

RefPtr<LayoutWrapper> ContainerModelTestNg::RunMeasureAndLayout(float width, float height)
{
    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
    LayoutConstraint.percentReference = { DEVICE_WIDTH, DEVICE_HEIGHT };
    LayoutConstraint.selfIdealSize = { width, height };
    LayoutConstraint.maxSize = { width, height };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
    return layoutWrapper;
}

void ContainerModelTestNg::SetWidth(const Dimension& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), std::nullopt));
}

void ContainerModelTestNg::SetHeight(const Dimension& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(height)));
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
    RunMeasureAndLayout();
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
 * @tc.desc: Test InitContainerEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, Test002, TestSize.Level1)
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
     * @tc.steps: step9. Mouse move > mouseMovePopupDistance
     * @tc.expected: Do nothing
     */
    constexpr double mouseMovePopupDistance = 5.0;
    
    Mouse(Offset(0, mouseMovePopupDistance + 1));
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::GONE);

    /**
     * @tc.steps: step10. Mouse move outSide
     * @tc.expected: Do nothing
     */
    Mouse(Offset(0, titlePopupDistance));
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::GONE);

    /**
     * @tc.steps: step11. Mouse move <= mouseMovePopupDistance
     * @tc.expected: float node would VISIBLE
     */
    Mouse(Offset(0, mouseMovePopupDistance));
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::VISIBLE);

    /**
     * @tc.steps: step12. Mouse move <= mouseMovePopupDistance again
     * @tc.expected: The CanShowFloatingTitle() is false, Do nothing
     */
    Mouse(Offset(0, mouseMovePopupDistance));
    EXPECT_EQ(floatingLayoutProperty->GetVisibility(), VisibleType::VISIBLE);

    /**
     * @tc.steps: step13. Mouse move outSide
     * @tc.expected: float node would GONE by Animate()
     */
    Mouse(Offset(0, titlePopupDistance));
    floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
}

/**
 * @tc.name: ContainerModalPatternTest001
 * @tc.desc: Test IsMeasureBoundary and IsAtomicNode.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, ContainerModalPatternTest001, TestSize.Level1)
{
    auto containerModalPattern = AceType::MakeRefPtr<ContainerModalPattern>();
    EXPECT_TRUE(containerModalPattern->IsMeasureBoundary());
    EXPECT_FALSE(containerModalPattern->IsAtomicNode());
}

/**
 * @tc.name: ContainerModalPatternTest008
 * @tc.desc: Test ChangeFloatingTitle.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, ContainerModalPatternTest008, TestSize.Level1)
{
    auto containerModalPattern = AceType::MakeRefPtr<ContainerModalPattern>();

    const std::string tag = "test";
    containerModalPattern->frameNode_ = AceType::MakeRefPtr<FrameNode>(tag, 0, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> result = containerModalPattern->GetHost();
    containerModalPattern->ChangeFloatingTitle(result, true);
}

/**
 * @tc.name: ContainerModalPatternTest009
 * @tc.desc: Test ChangeTitleButtonIcon.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, ContainerModalPatternTest009, TestSize.Level1)
{
    std::string tag = "Button";
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, 0, AceType::MakeRefPtr<Pattern>());
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewStackProcessor::GetInstance()->Push(frameNode);
    ASSERT_NE(frameNode, nullptr);

    auto containerModalPattern = AceType::MakeRefPtr<ContainerModalPattern>();
    containerModalPattern->ChangeTitleButtonIcon(
        frameNode, InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT, true);
}

/**
 * @tc.name: ContainerModalAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of containerModal.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelTestNg, ContainerModalAccessibilityPropertyGetText001, TestSize.Level1)
{
    auto containerModalNode = AceType::MakeRefPtr<FrameNode>(
        CONTAINER_MODAL_NODE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(containerModalNode, nullptr);

    auto columnNode = AceType::MakeRefPtr<FrameNode>(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);

    auto titleNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(titleNode, nullptr);

    auto titleLabelNodeOne = AceType::MakeRefPtr<FrameNode>(
        TITLE_LABEL_NODE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(titleLabelNodeOne, nullptr);

    auto titleLabelNodeTwo = AceType::MakeRefPtr<FrameNode>(
        TITLE_LABEL_NODE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(titleLabelNodeTwo, nullptr);

    auto textLayoutProperty = titleLabelNodeTwo->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(CONTAINER_MODAL_NODE_TAG);

    titleNode->AddChild(titleLabelNodeOne);
    titleNode->AddChild(titleLabelNodeTwo);
    columnNode->AddChild(titleNode);
    containerModalNode->AddChild(columnNode);

    ContainerModalAccessibilityProperty containerModalAccessibilityProperty;
    containerModalAccessibilityProperty.SetHost(containerModalNode);

    EXPECT_EQ(containerModalAccessibilityProperty.GetText(), CONTAINER_MODAL_NODE_TAG);
}
} // namespace OHOS::Ace::NG
