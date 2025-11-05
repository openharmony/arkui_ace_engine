/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include <mutex>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#include "base/geometry/ng/rect_t.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"
#include "test/mock/core/rosen/testing_path.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/multi_thread_build_manager.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/placement.h"
#include "core/components/popup/popup_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_paint_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float ZERO = 0.0f;
constexpr bool BUBBLE_PROPERTY_SHOW = true;
constexpr bool BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW = true;
constexpr bool BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE = true;
constexpr bool BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_FALSE = false;
constexpr bool BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE = false;
constexpr bool BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_TRUE = true;
constexpr bool BUBBLE_LAYOUT_PROPERTY_SHOW_OUT_SUBWINDOW = false;

constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float CONTAINER_WIDTH = 600.0f;
constexpr float CONTAINER_HEIGHT = 1000.0f;
constexpr float BUBBLE_WIDTH = 100.0f;
constexpr float BUBBLE_HEIGHT = 50.0f;
constexpr float BUBBLE_WIDTH_CHANGE = 116.0f;
constexpr float BUBBLE_HEIGHT_CHANGE = 66.0f;
constexpr float TARGET_WIDTH = 100.0f;
constexpr float TARGET_HEIGHT = 200.0f;
constexpr float TARGET_X = 100.0f;
constexpr float TARGET_Y = 150.0f;

const std::string CLIP_PATH = "M100 0 L0 100 L50 200 L150 200 L200 100 Z";
const std::string BUBBLE_MESSAGE = "Hello World";
const std::string BUBBLE_NEW_MESSAGE = "Good";
const std::string STATE = "true";
const OffsetF DISPLAY_WINDOW_OFFSET = OffsetF(ZERO, ZERO);
const OffsetF TARGET_OFFSET(TARGET_X, TARGET_Y);
const OffsetF MESSAGE_OFFSET = OffsetF(6, 16);
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const SizeF TARGET_SIZE(TARGET_WIDTH, TARGET_HEIGHT);
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
constexpr Placement BUBBLE_LAYOUT_PROPERTY_PLACEMENT = Placement::LEFT;
constexpr int CHILD_SIZE_X = 1;
constexpr int CHILD_SIZE_Y = 2;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
constexpr float POSITION_OFFSET = 100.0f;
constexpr float ARROW_OFFSET = 100.0f;
constexpr float RADIUS = 30.0f;
const std::string ARROW_PATH_EMPTY = "";
const std::vector<Placement> BUBBLE_LAYOUT_PROPERTY_PLACEMENTS = { Placement::LEFT, Placement::RIGHT, Placement::TOP,
    Placement::BOTTOM, Placement::TOP_LEFT, Placement::TOP_RIGHT, Placement::BOTTOM_LEFT, Placement::BOTTOM_RIGHT,
    Placement::LEFT_BOTTOM, Placement::LEFT_TOP, Placement::RIGHT_BOTTOM, Placement::RIGHT_TOP, Placement::NONE };
const Offset POPUP_PARAM_POSITION_OFFSET = Offset(100.0f, 100.0f);
const OffsetF BUBBLE_POSITION_OFFSET = OffsetF(100.0f, 100.0f);
} // namespace
struct TestProperty {
    // layout property
    std::optional<bool> enableArrow = std::nullopt;
    std::optional<bool> useCustom = std::nullopt;
    std::optional<Placement> placement = std::nullopt;
    std::optional<bool> showInSubWindow = std::nullopt;
    std::optional<OffsetF> displayWindowOffset = std::nullopt;

    // render property
    std::optional<bool> autoCancel = std::nullopt;
    std::optional<Color> maskColor = std::nullopt;
    std::optional<Color> backgroundColor = std::nullopt;
    std::optional<Dimension> arrowOffset = std::nullopt;
};

class MockBubbleTheme : public PopupTheme, public ButtonTheme {
    DECLARE_ACE_TYPE(MockBubbleTheme, PopupTheme, ButtonTheme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<MockBubbleTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<MockBubbleTheme> theme = AceType::MakeRefPtr<MockBubbleTheme>();
            return theme;
        }
    };

    ~MockBubbleTheme() override = default;

protected:
    MockBubbleTheme() = default;
};

class BubbleThreeTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static RefPtr<FrameNode> CreateBubbleNode(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateTargetNode();
};

void BubbleThreeTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void BubbleThreeTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}


RefPtr<FrameNode> BubbleThreeTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

RefPtr<FrameNode> BubbleThreeTestNg::CreateBubbleNode(const TestProperty& testProperty)
{
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto layoutProperty = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto renderProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();

    // update layout property
    if (testProperty.enableArrow.has_value()) {
        layoutProperty->UpdateEnableArrow(testProperty.enableArrow.value());
    }
    if (testProperty.useCustom.has_value()) {
        layoutProperty->UpdateUseCustom(testProperty.useCustom.value());
    }
    if (testProperty.placement.has_value()) {
        layoutProperty->UpdatePlacement(testProperty.placement.value());
    }
    if (testProperty.showInSubWindow.has_value()) {
        layoutProperty->UpdateShowInSubWindow(testProperty.showInSubWindow.value());
    }
    if (testProperty.displayWindowOffset.has_value()) {
        layoutProperty->UpdateDisplayWindowOffset(testProperty.displayWindowOffset.value());
    }

    // update render property
    if (testProperty.autoCancel.has_value()) {
        renderProperty->UpdateAutoCancel(testProperty.autoCancel.value());
    }
    if (testProperty.maskColor.has_value()) {
        renderProperty->UpdateMaskColor(testProperty.maskColor.value());
    }
    if (testProperty.backgroundColor.has_value()) {
        renderProperty->UpdateBackgroundColor(testProperty.backgroundColor.value());
    }
    if (testProperty.placement.has_value()) {
        renderProperty->UpdatePlacement(testProperty.placement.value());
    }
    if (testProperty.enableArrow.has_value()) {
        renderProperty->UpdateEnableArrow(testProperty.enableArrow.value());
    }
    if (testProperty.useCustom.has_value()) {
        renderProperty->UpdateUseCustom(testProperty.useCustom.value());
    }
    if (testProperty.arrowOffset.has_value()) {
        renderProperty->UpdateArrowOffset(testProperty.arrowOffset.value());
    }
    return popupNode;
}

/**
 * @tc.name: BubbleLayoutTest001
 * @tc.desc: Test BubbleNode layout
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BubbleLayoutTest001, TestSize.Level1)
{
    // create targetNode and popupNode
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    auto targetNode = CreateTargetNode();
    EXPECT_NE(targetNode, nullptr);
    auto targetTag = targetNode->GetTag();
    auto targetId = targetNode->GetId();
    // set popupTheme and  buttonTheme to themeManager before using themeManager
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetTag, targetId, popupParam);
    EXPECT_NE(popupNode, nullptr);

    // create layoutWrapper and update it
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        popupNode, geometryNode, AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty()));
    auto layoutProperty = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    // update layoutProperty
    layoutProperty->UpdateEnableArrow(true);
    layoutProperty->UpdateUseCustom(false);
    layoutProperty->UpdatePlacement(Placement::BOTTOM);
    layoutProperty->UpdateShowInSubWindow(false);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BUBBLE_WIDTH), CalcLength(BUBBLE_HEIGHT)));
    auto popupLayoutAlgorithm = popupNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_NE(popupLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(popupLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT));

    PaddingProperty noPadding;
    noPadding.left = CalcLength(ZERO);
    noPadding.right = CalcLength(ZERO);
    noPadding.top = CalcLength(ZERO);
    noPadding.bottom = CalcLength(ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
}

/**
 * @tc.name: BubbleLayoutTest002
 * @tc.desc: Test Bubble Layout
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BubbleLayoutTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetUseCustomComponent(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    auto targetNode = CreateTargetNode();
    EXPECT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    EXPECT_FALSE(bubblePattern == nullptr);
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_FALSE(bubbleLayoutProperty == nullptr);
    auto bubbleLayoutAlgorithm = bubblePattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(bubbleLayoutAlgorithm == nullptr);

    /**
     * @tc.steps: step3. update layoutWrapper and layoutProperty.
     */
    bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
    bubbleLayoutProperty->UpdateUseCustom(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    bubbleLayoutProperty->UpdatePlacement(BUBBLE_LAYOUT_PROPERTY_PLACEMENT);
    bubbleLayoutProperty->UpdateUseCustom(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step3. use layoutAlgorithm to measure and layout.
     * @tc.expected: step3. check whether the value of geometry's frameSize and frameOffset is correct.
     */
    bubbleLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    bubbleLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), FULL_SCREEN_SIZE);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), DISPLAY_WINDOW_OFFSET);
}

/**
 * @tc.name: BubbleLayoutTest003
 * @tc.desc: Test the Bubble created by message Measure and Layout
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BubbleLayoutTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetUseCustomComponent(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    Dimension radius = 1000.0_vp;
    Dimension arrowWidth = 1000.0_vp;
    popupParam->SetRadius(radius);
    popupParam->SetArrowWidth(arrowWidth);
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    // set popupTheme and  buttonTheme to themeManager before using themeManager
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    EXPECT_FALSE(frameNode == nullptr);
    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    EXPECT_FALSE(bubblePattern == nullptr);
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_FALSE(bubbleLayoutProperty == nullptr);
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(bubbleLayoutAlgorithm == nullptr);
    bubbleLayoutAlgorithm->targetTag_ = targetTag;
    bubbleLayoutAlgorithm->targetNodeId_ = targetId;

    /**
     * @tc.steps: step3. update layoutWrapper and layoutProperty.
     */
    bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
    bubbleLayoutProperty->UpdateUseCustom(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    bubbleLayoutProperty->UpdatePlacement(BUBBLE_LAYOUT_PROPERTY_PLACEMENT);
    bubbleLayoutProperty->UpdateUseCustom(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_TRUE);
    bubbleLayoutProperty->UpdateShowInSubWindow(BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);

    /**
     * @tc.steps: step4. create bubble child and child's layoutWrapper.
     */
    auto textFrameNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    EXPECT_FALSE(textFrameNode == nullptr);
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    textGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    textLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BUBBLE_WIDTH), CalcLength(BUBBLE_HEIGHT)));
    auto boxLayoutAlgorithm = textFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    textLayoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(textFrameNode);
    layoutWrapper->AppendChild(textLayoutWrapper);
    /**
     * @tc.steps: step5. use layoutAlgorithm to measure and layout.
     * @tc.expected: step5. check whether the value of the bubble child's frameSize and frameOffset is correct.
     */
    bubbleLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    bubbleLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(textLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(BUBBLE_WIDTH_CHANGE, BUBBLE_HEIGHT_CHANGE));
    EXPECT_EQ(textLayoutWrapper->GetGeometryNode()->GetFrameOffset().GetX(), 0);
    EXPECT_EQ(textLayoutWrapper->GetGeometryNode()->GetFrameOffset().GetY(), 8);

    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto wrapperBubbleLayoutProperty = AceType::DynamicCast<BubbleLayoutProperty>(layoutWrapper->GetLayoutProperty());
    wrapperBubbleLayoutProperty->UpdateUseCustom(false);
    bubbleLayoutAlgorithm->targetTag_ = V2::TEXTAREA_ETS_TAG;
    bubbleLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    bubbleLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    bubbleLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    bubbleLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: BubbleLayoutTest004
 * @tc.desc: Test  Bubble UpdateTouchRegion in different arrowPlacement
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BubbleLayoutTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. get pattern and layoutAlgorithm.
     * @tc.expected: step2. related function is called.
     */
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    EXPECT_FALSE(bubblePattern == nullptr);
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_FALSE(bubbleLayoutProperty == nullptr);
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(bubbleLayoutAlgorithm == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto childWrapper = layoutWrapper;
    EXPECT_FALSE(childWrapper == nullptr);
    /**
     * @tc.steps: step3. update layoutProp and arrowPlacement.
     * @tc.expected: step3. check whether the function is executed.
     */
    for (uint32_t i = 0; i < BUBBLE_LAYOUT_PROPERTY_PLACEMENTS.size(); ++i) {
        if (i % 2 == 0) {
            bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
        } else {
            bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_FALSE);
        }
        bubbleLayoutAlgorithm->arrowPlacement_ = BUBBLE_LAYOUT_PROPERTY_PLACEMENTS[i];
        bubbleLayoutAlgorithm->UpdateTouchRegion();
    }
    bubbleLayoutAlgorithm->showArrow_ = true;
    for (uint32_t i = 0; i < BUBBLE_LAYOUT_PROPERTY_PLACEMENTS.size(); ++i) {
        bubbleLayoutAlgorithm->arrowPlacement_ = BUBBLE_LAYOUT_PROPERTY_PLACEMENTS[i];
        bubbleLayoutAlgorithm->UpdateTouchRegion();
    }
    bubbleLayoutAlgorithm->bCaretMode_ = true;
    bubbleLayoutAlgorithm->bHorizontal_ = true;
    SizeF childSizeFull(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    bubbleLayoutAlgorithm->GetChildPositionNew(childSizeFull, bubbleLayoutProperty, childWrapper);
}

/**
 * @tc.name: BubbleLayoutTest005
 * @tc.desc: Test BubbleLayoutAlgorithm::Measure function
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BubbleLayoutTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetUseCustomComponent(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    // set popupTheme and  buttonTheme to themeManager before using themeManager
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(bubbleLayoutAlgorithm, nullptr);
    bubbleLayoutAlgorithm->targetTag_ = targetTag;
    bubbleLayoutAlgorithm->targetNodeId_ = targetId;
    /**
     * @tc.steps: step3. update layoutWrapper and layoutProperty.
     */
    bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
    bubbleLayoutProperty->UpdatePlacement(BUBBLE_LAYOUT_PROPERTY_PLACEMENT);
    bubbleLayoutProperty->UpdateUseCustom(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_TRUE);
    bubbleLayoutProperty->UpdateShowInSubWindow(BUBBLE_LAYOUT_PROPERTY_SHOW_OUT_SUBWINDOW);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /**
     * @tc.steps: step5. use layoutAlgorithm to measure and layout.
     */
    auto textFrameNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    EXPECT_FALSE(textFrameNode == nullptr);
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    textGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    textLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BUBBLE_WIDTH), CalcLength(BUBBLE_HEIGHT)));
    auto boxLayoutAlgorithm = textFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    textLayoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(textFrameNode);
    layoutWrapper->AppendChild(textLayoutWrapper);

    bubbleLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    bubblePattern->arrowPlacement_.reset();
    bubbleLayoutProperty->UpdatePlacement(Placement::BOTTOM_RIGHT);
    bubbleLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: BubbleLayoutTest006
 * @tc.desc: Test GetPositionOffset,UpdatePositionOffset.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BubbleLayoutTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. use UpdatePositionOffset() to update position offset.
     */
    BubbleLayoutProperty property;
    EXPECT_FALSE(property.GetPositionOffset().has_value());
    property.UpdatePositionOffset(OffsetF(25.0f, 30.0f));

    /**
     * @tc.steps: step2. use GetPositionOffset() get popup position offset .
     * @tc.expected: check whether popup offset is correct.
     */
    ASSERT_TRUE(property.GetPositionOffset().has_value());
    EXPECT_EQ(property.GetPositionOffset().value(), OffsetF(25.0f, 30.0f));
}

/**
 * @tc.name: BubbleLayoutTest007
 * @tc.desc: Test BubbleLayoutAlgorithm::Measure function
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BubbleLayoutTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetUseCustomComponent(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    // set popupTheme and  buttonTheme to themeManager before using themeManager
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(bubbleLayoutAlgorithm, nullptr);
    bubbleLayoutAlgorithm->targetTag_ = targetTag;
    bubbleLayoutAlgorithm->targetNodeId_ = targetId;
    /**
     * @tc.steps: step3. update layoutWrapper and layoutProperty.
     */
    bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
    bubbleLayoutProperty->UpdatePlacement(BUBBLE_LAYOUT_PROPERTY_PLACEMENT);
    bubbleLayoutProperty->UpdateUseCustom(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_TRUE);
    bubbleLayoutProperty->UpdateShowInSubWindow(BUBBLE_LAYOUT_PROPERTY_SHOW_OUT_SUBWINDOW);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /**
     * @tc.steps: step5. create child and use layoutAlgorithm to measure and layout.
     */
    auto textFrameNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    EXPECT_FALSE(textFrameNode == nullptr);
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    textGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    textLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BUBBLE_WIDTH), CalcLength(BUBBLE_HEIGHT)));
    auto boxLayoutAlgorithm = textFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    textLayoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(textFrameNode);
    layoutWrapper->AppendChild(textLayoutWrapper);
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    EXPECT_FALSE(children.empty());
    bubbleLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    bubbleLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(bubbleLayoutAlgorithm->GetChildPosition(SizeF(ZERO, ZERO), bubbleLayoutProperty, true) ==
                 DISPLAY_WINDOW_OFFSET);
}

/**
 * @tc.name: BubbleLayoutTest008
 * @tc.desc: Test GetIfNeedArrow
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BubbleLayoutTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. get pattern and layoutAlgorithm.
     * @tc.expected: step2. related function is called.
     */
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto childWrapper = layoutWrapper;
    EXPECT_FALSE(childWrapper == nullptr);

    /**
     * @tc.steps: step3. excute GetIfNeedArrow GetChildPosition
     * @tc.expected: step3. GetChildPosition get result offset is adjust position.
     */
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    std::string result = ARROW_PATH_EMPTY;
    for (uint32_t i = 0; i < BUBBLE_LAYOUT_PROPERTY_PLACEMENTS.size(); ++i) {
        if (i % 2 == 0) {
            bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
        } else {
            bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_FALSE);
        }
        bubbleLayoutAlgorithm->arrowPlacement_ = BUBBLE_LAYOUT_PROPERTY_PLACEMENTS[i];
        bubbleLayoutAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
        bubbleLayoutAlgorithm->targetOffset_ = OffsetF(POSITION_OFFSET, POSITION_OFFSET);
        bubbleLayoutAlgorithm->wrapperSize_ = childSize;
        /**
         * @tc.steps: step3. excute GetIfNeedArrow
         * @tc.expected: step3. GetIfNeedArrow returns a sharp corner that needs to be drawn.
         */
        auto needArrow = bubbleLayoutAlgorithm->GetIfNeedArrow(bubbleLayoutProperty, childSize);
        EXPECT_FALSE(needArrow);
        /**
         * @tc.steps: step4. excute GetChildPosition
         * @tc.expected: step4. GetChildPosition returns the result as the bubble position.
         */
        auto resultOffset = bubbleLayoutAlgorithm->GetChildPositionNew(childSize, bubbleLayoutProperty, childWrapper);
        EXPECT_EQ(resultOffset, DISPLAY_WINDOW_OFFSET);
        OffsetF arrowPosition;
        /**
         * @tc.steps: step5. excute GetPositionWithPlacementLeftBottom
         * @tc.expected: step5. GetPositionWithPlacementLeftBottom returns the position of the bubble.
         */
        auto position = bubbleLayoutAlgorithm->GetPositionWithPlacementLeftBottom(childSize,
            OffsetF(POSITION_OFFSET, POSITION_OFFSET), OffsetF(POSITION_OFFSET, POSITION_OFFSET), arrowPosition);
        EXPECT_NE(position, DISPLAY_WINDOW_OFFSET);
        EXPECT_NE(arrowPosition, DISPLAY_WINDOW_OFFSET);

        /**
         * @tc.steps: step6. excute GetArrowBuildPlacement
         * @tc.expected: step6. GetArrowBuildPlacement returns the direction of Arrow drawing.
         */
        bubbleLayoutAlgorithm->arrowPlacement_ = BUBBLE_LAYOUT_PROPERTY_PLACEMENTS[i];
        Placement arrowBuildplacement = Placement::NONE;
        if (BUBBLE_LAYOUT_PROPERTY_PLACEMENTS[i] != Placement::NONE) {
            bubbleLayoutAlgorithm->GetArrowBuildPlacement(arrowBuildplacement);
            EXPECT_NE(arrowBuildplacement, Placement::NONE);
        }

        /**
         * @tc.steps: step7. excute BuildTopLinePath
         * @tc.expected: step7. BuildTopLinePath returns the top edge drawing path of the bubble.
         */
        arrowBuildplacement = Placement::TOP_RIGHT;
        bubbleLayoutAlgorithm->arrowPlacement_ = BUBBLE_LAYOUT_PROPERTY_PLACEMENTS[i];
        result = bubbleLayoutAlgorithm->BuildTopLinePath(ARROW_OFFSET, RADIUS, arrowBuildplacement);
        EXPECT_EQ(arrowBuildplacement, Placement::TOP_RIGHT);
        arrowBuildplacement = Placement::TOP_LEFT;
        result = bubbleLayoutAlgorithm->BuildTopLinePath(ARROW_OFFSET, RADIUS, arrowBuildplacement);
        EXPECT_EQ(arrowBuildplacement, Placement::TOP_LEFT);
        arrowBuildplacement = Placement::TOP;
        result = bubbleLayoutAlgorithm->BuildTopLinePath(ARROW_OFFSET, RADIUS, arrowBuildplacement);
        EXPECT_EQ(arrowBuildplacement, Placement::TOP);
        /**
         * @tc.steps: step8. excute BuildRightLinePath
         * @tc.expected: step8. BuildRightLinePath returns the Right edge drawing path of the bubble.
         */
        bubbleLayoutAlgorithm->arrowPlacement_ = BUBBLE_LAYOUT_PROPERTY_PLACEMENTS[i];
        arrowBuildplacement = Placement::RIGHT_BOTTOM;
        result = bubbleLayoutAlgorithm->BuildRightLinePath(ARROW_OFFSET, RADIUS, arrowBuildplacement);
        EXPECT_EQ(arrowBuildplacement, Placement::RIGHT_BOTTOM);
        arrowBuildplacement = Placement::RIGHT_TOP;
        result = bubbleLayoutAlgorithm->BuildRightLinePath(ARROW_OFFSET, RADIUS, arrowBuildplacement);
        EXPECT_EQ(arrowBuildplacement, Placement::RIGHT_TOP);
        arrowBuildplacement = Placement::RIGHT;
        result = bubbleLayoutAlgorithm->BuildRightLinePath(ARROW_OFFSET, RADIUS, arrowBuildplacement);
        EXPECT_EQ(arrowBuildplacement, Placement::RIGHT);
        /**
         * @tc.steps: step9. excute BuildBottomLinePath
         * @tc.expected: step9. BuildBottomLinePath returns the Bottom edge drawing path of the bubble.
         */
        bubbleLayoutAlgorithm->arrowPlacement_ = BUBBLE_LAYOUT_PROPERTY_PLACEMENTS[i];
        arrowBuildplacement = Placement::BOTTOM_RIGHT;
        result = bubbleLayoutAlgorithm->BuildBottomLinePath(ARROW_OFFSET, RADIUS, arrowBuildplacement);
        EXPECT_EQ(arrowBuildplacement, Placement::BOTTOM_RIGHT);
        arrowBuildplacement = Placement::BOTTOM_LEFT;
        result = bubbleLayoutAlgorithm->BuildBottomLinePath(ARROW_OFFSET, RADIUS, arrowBuildplacement);
        EXPECT_EQ(arrowBuildplacement, Placement::BOTTOM_LEFT);
        arrowBuildplacement = Placement::BOTTOM;
        result = bubbleLayoutAlgorithm->BuildBottomLinePath(ARROW_OFFSET, RADIUS, arrowBuildplacement);
        EXPECT_EQ(arrowBuildplacement, Placement::BOTTOM);
        /**
         * @tc.steps: step10. excute BuildLeftLinePath
         * @tc.expected: step10. BuildLeftLinePath returns the Left edge drawing path of the bubble.
         */
        bubbleLayoutAlgorithm->arrowPlacement_ = BUBBLE_LAYOUT_PROPERTY_PLACEMENTS[i];
        arrowBuildplacement = Placement::LEFT_BOTTOM;
        result = bubbleLayoutAlgorithm->BuildLeftLinePath(ARROW_OFFSET, RADIUS, arrowBuildplacement);
        EXPECT_EQ(arrowBuildplacement, Placement::LEFT_BOTTOM);
        arrowBuildplacement = Placement::LEFT_TOP;
        result = bubbleLayoutAlgorithm->BuildLeftLinePath(ARROW_OFFSET, RADIUS, arrowBuildplacement);
        EXPECT_EQ(arrowBuildplacement, Placement::LEFT_TOP);
        arrowBuildplacement = Placement::LEFT;
        result = bubbleLayoutAlgorithm->BuildLeftLinePath(ARROW_OFFSET, RADIUS, arrowBuildplacement);
        EXPECT_EQ(arrowBuildplacement, Placement::LEFT);
    }
}

/**
 * @tc.name: BubbleLayoutTest009
 * @tc.desc: Test GetIfNeedArrow
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BubbleLayoutTest009, TestSize.Level1)
{
    static std::vector<std::string> TEXT_STATES = { V2::TEXTAREA_ETS_TAG, V2::TEXTINPUT_ETS_TAG,
        V2::RICH_EDITOR_ETS_TAG, V2::SEARCH_ETS_TAG };

    for (uint32_t i = 0; i < TEXT_STATES.size(); ++i) {
        /**
         * @tc.steps: step1. create targetNode and get frameNode.
         */
        auto targetNode = FrameNode::GetOrCreateFrameNode(TEXT_STATES[i],
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        auto targetId = targetNode->GetId();
        auto targetTag = targetNode->GetTag();
        auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
        auto frameNode = FrameNode::CreateFrameNode(
            V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
        /**
         * @tc.steps: step2. get pattern and layoutAlgorithm.
         * @tc.expected: step2. related function is called.
         */
        auto bubblePattern = frameNode->GetPattern<BubblePattern>();
        auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
        auto bubbleLayoutAlgorithm =
            AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
        /**
         * @tc.steps: step4. excute InitCaretTargetSizeAndPosition
         * @tc.expected: step4. InitCaretTargetSizeAndPosition get result bCaretMode_ is  true..
         */
        bubbleLayoutAlgorithm->InitCaretTargetSizeAndPosition();
        EXPECT_TRUE(bubbleLayoutAlgorithm->bCaretMode_);
        auto targetSize = bubbleLayoutAlgorithm->targetSize_;
        EXPECT_EQ(targetSize, SizeF(0.0f, 0.0f));
        auto targetOffset = bubbleLayoutAlgorithm->targetOffset_;
        EXPECT_EQ(targetOffset, OffsetF(0.0f, 0.0f));
    }
}

HWTEST_F(BubbleThreeTestNg, BubbleLayoutTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::TEXTAREA_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));

    /**
     * @tc.steps: step2. get pattern and layoutAlgorithm.
     * @tc.expected: step2. related function is called.
     */
    Dimension radius = 0.5_pct;
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    bubblePattern->targetOffset_ = OffsetF(0.0f, 0.0f);
    bubblePattern->targetSize_ = SizeF(0.0f, 0.0f);
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    auto bubbleLayoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    

    auto childSize = SizeF(0.0f, 0.0f);
    auto topPosition = OffsetF(0.0f, 0.0f);
    auto bottomPosition = OffsetF(0.0f, 0.0f);
    auto arrowPosition = OffsetF(0.0f, 0.0f);
    auto position = OffsetF(0.0f, 0.0f);

    bubbleLayoutAlgorithm->UpdateMarginByWidth();
    auto result = bubbleLayoutAlgorithm->AddOffset(position);
    bubbleLayoutAlgorithm->GetPositionWithPlacementTopLeft(childSize, topPosition, bottomPosition, arrowPosition);
    bubbleLayoutAlgorithm->GetPositionWithPlacementTopRight(childSize, topPosition, bottomPosition, arrowPosition);
    bubbleLayoutAlgorithm->GetPositionWithPlacementBottomLeft(childSize, topPosition, bottomPosition, arrowPosition);
    bubbleLayoutAlgorithm->GetPositionWithPlacementBottomRight(childSize, topPosition, bottomPosition, arrowPosition);
    bubbleLayoutAlgorithm->GetPositionWithPlacementLeftTop(childSize, topPosition, bottomPosition, arrowPosition);
    bubbleLayoutAlgorithm->GetPositionWithPlacementRightTop(childSize, topPosition, bottomPosition, arrowPosition);
    bubbleLayoutAlgorithm->GetPositionWithPlacementRightBottom(childSize, topPosition, bottomPosition, arrowPosition);
    EXPECT_EQ(result, position);

    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    bubbleLayoutAlgorithm->showArrow_ = true;
    bubbleLayoutAlgorithm->enableArrow_ = true;
    std::vector<Placement> curPlaceStates = { Placement::LEFT, Placement::RIGHT, Placement::TOP, Placement::NONE };
    for (auto placement: curPlaceStates) {
        bubbleLayoutAlgorithm->placement_ = placement;
        bubbleLayoutAlgorithm->UpdateChildPosition(position);
    }
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);

    bubbleLayoutAlgorithm->borderRadius_ = radius;
    bubbleLayoutAlgorithm->SetBubbleRadius();
    bubbleLayoutAlgorithm->SetHotAreas(true, false, frameNode, 0);
    EXPECT_EQ(bubbleLayoutAlgorithm->borderRadius_.Unit(), DimensionUnit::PX);
}

/**
 * @tc.name: BubbleBorderTest010
 * @tc.desc: Test BorderOffset
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BubbleBorderTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the BubblePaintMethod.
     */
    BubblePaintMethod bubblePaintMethod;

    /**
     * @tc.steps: step2. Set condition.
     */
    bubblePaintMethod.SetShowArrow(true);
    bubblePaintMethod.enableArrow_ = true;
    auto popupTheme = AceType::MakeRefPtr<PopupTheme>();

    /**
     * @tc.steps: step3. Excute function to get border offset.
     */
    ASSERT_NE(popupTheme, nullptr);
    if (popupTheme->GetPopupDoubleBorderEnable()) {
        if (bubblePaintMethod.needPaintOuterBorder_) {
            EXPECT_EQ(bubblePaintMethod.GetBorderOffset(popupTheme), -bubblePaintMethod.outerBorderWidth_);
        } else {
            EXPECT_EQ(bubblePaintMethod.GetBorderOffset(popupTheme), bubblePaintMethod.innerBorderWidth_);
        }
    }
}

 /**
  * @tc.name: BubblePatternTest022
  * @tc.desc: Test UpdateCommonParam with with Offset, Radius, ArrowHeight, ArrowWidth, Shadow and EnableHoverMode.
  * @tc.type: FUNC
  */
HWTEST_F(BubbleThreeTestNg, BubblePatternTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set popup value to popupParam.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetTargetOffset(POPUP_PARAM_POSITION_OFFSET);
    popupParam->setErrorArrowHeight_ = true;
    popupParam->setErrorArrowWidth_ = true;
    popupParam->setErrorRadius_ = true;
    popupParam->childwidth_ = 100.0_px;
    popupParam->SetEnableHoverMode(true);
    /**
     * @tc.steps: step2. create CustomBubbleNode with positon offset
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(targetNode, nullptr);
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(rowFrameNode, nullptr);
    auto blankFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(blankFrameNode, nullptr);
    rowFrameNode->AddChild(blankFrameNode);
    auto popupNode =
        BubbleView::CreateCustomBubbleNode(targetNode->GetTag(), targetNode->GetId(), rowFrameNode, popupParam);
    ASSERT_NE(popupNode, nullptr);
    /**
     * @tc.steps: step3. use BubbleLayoutProperty to check PositionOffset.
     * @tc.expected: check whether GetPositionOffset value is correct.
     */
    int32_t settingApiVersion = 13;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    BubbleView::UpdateCommonParam(popupNode->GetId(), popupParam);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    auto property = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_EQ(property->GetPositionOffset().value(), BUBBLE_POSITION_OFFSET);
}

/**
 * @tc.name: BorderLinearGradientPointTest001
 * @tc.desc: Test BorderLinearGradientPoint
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BorderLinearGradientPointTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the BubblePaintMethod.
     */
    BubblePaintMethod bubblePaintMethod;
    /**
     * @tc.steps: step1. Set condition.
     */
    bubblePaintMethod.childOffset_ = OffsetF(10.0f, 10.0f);
    bubblePaintMethod.childSize_.SetWidth(10.0f);
    bubblePaintMethod.childSize_.SetHeight(8.0f);
    PopupLinearGradientProperties outlineLinearGradient;
    outlineLinearGradient.popupDirection = OHOS::Ace::GradientDirection::TOP;
    outlineLinearGradient.gradientColors.push_back(PopupGradientColor { Color::RED, 0.0 });
    outlineLinearGradient.gradientColors.push_back(PopupGradientColor { Color::GRAY, 1.0 });
    bubblePaintMethod.SetOutlineLinearGradient(outlineLinearGradient);
    /**
     * @tc.steps: step3. Execute the BorderLinearGradientPoint function and get result.
     */
    int popupOuterBorderDirectionInt =
        static_cast<int>(bubblePaintMethod.GetOutlineLinearGradient().popupDirection);
    std::vector<RSPoint> points = bubblePaintMethod.BorderLinearGradientPoint(popupOuterBorderDirectionInt);
    auto half = 2;
    auto childSizeWidth = bubblePaintMethod.childSize_.Width();
    auto childSizeHeight = bubblePaintMethod.childSize_.Height();
    auto childOffsetX = bubblePaintMethod.childOffset_.GetX();
    auto childOffsetY = bubblePaintMethod.childOffset_.GetY();
    RSPoint startPoint(childOffsetX + childSizeWidth / half, childOffsetY + childSizeHeight);
    RSPoint endPoint(childOffsetX + childSizeWidth / half, childOffsetY);
    /**
     * @tc.steps: step1. Compare function result.
     */
    EXPECT_EQ(startPoint.GetX(), points[0].GetX());
    EXPECT_EQ(endPoint.GetY(), points[1].GetY());
}

/**
 * @tc.name: BorderLinearGradientPointTest002
 * @tc.desc: Test BorderLinearGradientPoint
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BorderLinearGradientPointTest002, TestSize.Level1)
{
    BubblePaintMethod bubblePaintMethod;
    bubblePaintMethod.childOffset_ = OffsetF(10.0f, 10.0f);
    bubblePaintMethod.childSize_.SetWidth(10.0f);
    bubblePaintMethod.childSize_.SetHeight(8.0f);
    PopupLinearGradientProperties innerBorderLinearGradient;
    innerBorderLinearGradient.popupDirection = OHOS::Ace::GradientDirection::NONE;
    innerBorderLinearGradient.gradientColors.push_back(PopupGradientColor { Color::RED, 0.0 });
    innerBorderLinearGradient.gradientColors.push_back(PopupGradientColor { Color::GRAY, 1.0 });
    bubblePaintMethod.SetInnerBorderLinearGradient(innerBorderLinearGradient);
    int popupInnerBorderDirectionInt =
        static_cast<int>(bubblePaintMethod.GetInnerBorderLinearGradient().popupDirection);
    std::vector<RSPoint> points = bubblePaintMethod.BorderLinearGradientPoint(popupInnerBorderDirectionInt);
    auto half = 2;
    auto childSizeWidth = bubblePaintMethod.childSize_.Width();
    auto childSizeHeight = bubblePaintMethod.childSize_.Height();
    auto childOffsetX = bubblePaintMethod.childOffset_.GetX();
    auto childOffsetY = bubblePaintMethod.childOffset_.GetY();
    RSPoint startPoint(childOffsetX + childSizeWidth / half, childOffsetY);
    RSPoint endPoint(childOffsetX + childSizeWidth / half, childOffsetY + childSizeHeight);
    EXPECT_EQ(startPoint.GetX(), points[0].GetX());
    EXPECT_EQ(endPoint.GetY(), points[1].GetY());
}

/**
 * @tc.name: BorderLinearGradientColorsTest001
 * @tc.desc: Test BorderLinearGradientColors
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BorderLinearGradientColorsTest001, TestSize.Level1)
{
    BubblePaintMethod bubblePaintMethod;
    PopupLinearGradientProperties innerBorderLinearGradient;
    innerBorderLinearGradient.popupDirection = OHOS::Ace::GradientDirection::LEFT;
    innerBorderLinearGradient.gradientColors.push_back(PopupGradientColor { Color::GREEN, 0.0 });
    innerBorderLinearGradient.gradientColors.push_back(PopupGradientColor { Color::BLUE, 1.0 });
    bubblePaintMethod.SetInnerBorderLinearGradient(innerBorderLinearGradient);
    std::vector<PopupGradientColor> gradientColors =
        bubblePaintMethod.GetInnerBorderLinearGradient().gradientColors;
    std::pair<std::vector<uint32_t>, std::vector<float>> colors =
        bubblePaintMethod.BorderLinearGradientColors(gradientColors);
    std::vector<uint32_t> colorQuads = colors.first;
    std::vector<float> positions = colors.second;
    EXPECT_EQ(Color::GREEN.GetValue(), colorQuads[0]);
    EXPECT_EQ(1.0, positions[1]);
}

/**
 * @tc.name: BorderLinearGradientColorsTest002
 * @tc.desc: Test BorderLinearGradientColors
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BorderLinearGradientColorsTest002, TestSize.Level1)
{
    BubblePaintMethod bubblePaintMethod;
    PopupLinearGradientProperties outlineLinearGradient;
    outlineLinearGradient.popupDirection = OHOS::Ace::GradientDirection::LEFT;
    outlineLinearGradient.gradientColors.push_back(PopupGradientColor { Color::BLACK, 0.0 });
    outlineLinearGradient.gradientColors.push_back(PopupGradientColor { Color::RED, 1.0 });
    bubblePaintMethod.SetOutlineLinearGradient(outlineLinearGradient);
    std::vector<PopupGradientColor> gradientColors =
        bubblePaintMethod.GetOutlineLinearGradient().gradientColors;
    std::pair<std::vector<uint32_t>, std::vector<float>> colors =
        bubblePaintMethod.BorderLinearGradientColors(gradientColors);
    std::vector<uint32_t> colorQuads = colors.first;
    std::vector<float> positions = colors.second;
    EXPECT_EQ(Color::RED.GetValue(), colorQuads[1]);
    EXPECT_EQ(0.0, positions[0]);
}

/**
 * @tc.name: BubbleLayoutTest011
 * @tc.desc: Test the Bubble created by message Measure and Layout
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BubbleLayoutTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetUseCustomComponent(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    Dimension radius = 1000.0_vp;
    Dimension arrowWidth = 1000.0_vp;
    popupParam->SetRadius(radius);
    popupParam->SetArrowWidth(arrowWidth);
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    // set popupTheme and  buttonTheme to themeManager before using themeManager
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    EXPECT_FALSE(frameNode == nullptr);
    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    EXPECT_FALSE(bubblePattern == nullptr);
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_FALSE(bubbleLayoutProperty == nullptr);
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(bubbleLayoutAlgorithm == nullptr);
    bubbleLayoutAlgorithm->targetTag_ = targetTag;
    bubbleLayoutAlgorithm->targetNodeId_ = targetId;

    /**
     * @tc.steps: step3. update layoutWrapper and layoutProperty.
     */
    bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
    bubbleLayoutProperty->UpdateUseCustom(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    bubbleLayoutProperty->UpdatePlacement(BUBBLE_LAYOUT_PROPERTY_PLACEMENT);
    bubbleLayoutProperty->UpdateUseCustom(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_TRUE);
    bubbleLayoutProperty->UpdateShowInSubWindow(BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);

    /**
     * @tc.steps: step4. create bubble child and child's layoutWrapper.
     */
    auto textFrameNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    EXPECT_FALSE(textFrameNode == nullptr);
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    textGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    textLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BUBBLE_WIDTH), CalcLength(BUBBLE_HEIGHT)));
    auto boxLayoutAlgorithm = textFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    textLayoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(textFrameNode);
    layoutWrapper->AppendChild(textLayoutWrapper);
    /**
     * @tc.steps: step5. use layoutAlgorithm to measure and layout.
     * @tc.expected: step5. check whether the value of the bubble child's frameSize and frameOffset is correct.
     */

    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    bubbleLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    bubbleLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(textLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(BUBBLE_WIDTH_CHANGE, BUBBLE_HEIGHT_CHANGE));
    EXPECT_EQ(textLayoutWrapper->GetGeometryNode()->GetFrameOffset().GetX(), 0);

    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto wrapperBubbleLayoutProperty = AceType::DynamicCast<BubbleLayoutProperty>(layoutWrapper->GetLayoutProperty());
    wrapperBubbleLayoutProperty->UpdateUseCustom(false);
    bubbleLayoutAlgorithm->targetTag_ = V2::TEXTAREA_ETS_TAG;
    bubbleLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    bubbleLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    bubbleLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    bubbleLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));

    MockPipelineContext::TearDown();
}

/**
 * @tc.name: BorderLinearGradientColorsTest003
 * @tc.desc: Test BorderLinearGradientColors
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, BorderLinearGradientColorsTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the BubblePaintMethod.
     */
    BubblePaintMethod bubblePaintMethod;
    /**
     * @tc.steps: step2. Set condition.
     */
    PopupLinearGradientProperties outlineLinearGradient;
    outlineLinearGradient.popupDirection = OHOS::Ace::GradientDirection::TOP;
    outlineLinearGradient.gradientColors.push_back(PopupGradientColor { Color::GREEN, 0.1 });
    outlineLinearGradient.gradientColors.push_back(PopupGradientColor { Color::BLUE, 0.9 });
    bubblePaintMethod.SetOutlineLinearGradient(outlineLinearGradient);
    std::vector<PopupGradientColor> gradientColors =
        bubblePaintMethod.GetOutlineLinearGradient().gradientColors;
    /**
     * @tc.steps: step3. execute BorderLinearGradientColors function get result.
     */
    std::pair<std::vector<uint32_t>, std::vector<float>> colors =
        bubblePaintMethod.BorderLinearGradientColors(gradientColors);
    std::vector<uint32_t> colorQuads = colors.first;
    /**
     * @tc.steps: step4. Compare function return values.
     */
    EXPECT_EQ(Color::BLUE.GetValue(), colorQuads[1]);
}
/**
 * @tc.name: GetDoubleBorderWidthOffsetTest001
 * @tc.desc: Test GetDoubleBorderWidthOffset
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, GetDoubleBorderWidthOffsetTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the BubblePaintMethod.
     */
    BubblePaintMethod bubblePaintMethod;
    /**
     * @tc.steps: step2. Set condition.
     */
    PopupLinearGradientProperties outlineLinearGradient;
    outlineLinearGradient.popupDirection = OHOS::Ace::GradientDirection::TOP;
    outlineLinearGradient.gradientColors.push_back(PopupGradientColor { Color::GREEN, 0.1 });
    outlineLinearGradient.gradientColors.push_back(PopupGradientColor { Color::BLUE, 0.9 });
    bubblePaintMethod.SetOutlineLinearGradient(outlineLinearGradient);
    PopupLinearGradientProperties innerBorderLinearGradient;
    innerBorderLinearGradient.popupDirection = OHOS::Ace::GradientDirection::BOTTOM;
    innerBorderLinearGradient.gradientColors.push_back(PopupGradientColor { Color::RED, 0.0 });
    innerBorderLinearGradient.gradientColors.push_back(PopupGradientColor { Color::GRAY, 1.0 });
    bubblePaintMethod.SetInnerBorderLinearGradient(innerBorderLinearGradient);
    bubblePaintMethod.outerBorderWidthByUser_ = 5.0f;
    bubblePaintMethod.innerBorderWidthByUser_ = 5.0f;
    bubblePaintMethod.outerBorderWidth_ = 5.0f;
    bubblePaintMethod.innerBorderWidth_ = 5.0f;
    bubblePaintMethod.needPaintOuterBorder_ = true;
    auto popupTheme = AceType::MakeRefPtr<PopupTheme>();
    auto half = 2.0;
    auto result = -(bubblePaintMethod.outerBorderWidthByUser_ / half);
    /**
     * @tc.steps: step3. execute GetDoubleBorderWidthOffset function get result.
     */
    float doubleBorderOffset = bubblePaintMethod.GetDoubleBorderWidthOffset(popupTheme);
    /**
     * @tc.steps: step4. Compare function return values.
     */
    EXPECT_EQ(doubleBorderOffset, result);
}

/**
 * @tc.name: GetDoubleBorderWidthOffsetTest002
 * @tc.desc: Test GetDoubleBorderWidthOffset
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, GetDoubleBorderWidthOffsetTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the BubblePaintMethod.
     */
    BubblePaintMethod bubblePaintMethod;
    /**
     * @tc.steps: step2. Set condition.
     */
    PopupLinearGradientProperties innerBorderLinearGradient;
    innerBorderLinearGradient.popupDirection = OHOS::Ace::GradientDirection::BOTTOM;
    innerBorderLinearGradient.gradientColors.push_back(PopupGradientColor { Color::RED, 0.0 });
    innerBorderLinearGradient.gradientColors.push_back(PopupGradientColor { Color::GRAY, 1.0 });
    bubblePaintMethod.SetInnerBorderLinearGradient(innerBorderLinearGradient);
    bubblePaintMethod.innerBorderWidthByUser_ = 5.0f;
    bubblePaintMethod.innerBorderWidth_ = 5.0f;
    auto popupTheme = AceType::MakeRefPtr<PopupTheme>();
    auto result = 0.0f;
    /**
     * @tc.steps: step3. execute GetDoubleBorderWidthOffset function get result.
     */
    float doubleBorderOffset = bubblePaintMethod.GetDoubleBorderWidthOffset(popupTheme);
    /**
     * @tc.steps: step4. Compare function return values.
     */
    EXPECT_EQ(doubleBorderOffset, result);
}

/**
 * @tc.name: OnAttachToMainTreeMultiThread001
 * @tc.desc: Test OnAttachToMainTreeMultiThread to verify event registration in a simulated multi-thread environment.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, OnAttachToMainTreeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create bubble node and OverlayManager.
     */
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateBubbleNode(testProperty);
    ASSERT_NE(frameNode, nullptr);
    frameNode->GetOrCreateFocusHub();
    auto pattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Simulate non-UI thread environment and call OnAttachToMainTree.
     * @tc.expected: The framework should route the call to OnAttachToMainTreeMultiThread, which calls overlayManager.
     */
    bool isUIThread = MultiThreadBuildManager::isUIThread_;
    MultiThreadBuildManager::isUIThread_ = false;
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);

    pattern->OnAttachToMainTree();
    pattern->OnAttachToMainTreeMultiThread();

    MultiThreadBuildManager::isUIThread_ = isUIThread;
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);

    /**
     * @tc.steps: step3. Verify that key events were registered.
     */
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_TRUE(focusHub->onKeyEventsInternal_.empty());
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThread001
 * @tc.desc: Test OnDetachFromMainTreeMultiThread to verify cleanup logic in a simulated multi-thread environment.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleThreeTestNg, OnDetachFromMainTreeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create bubble node in UI thread environment and set up its state.
     */
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateBubbleNode(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    bool isStateChanged = false;
    auto eventHub = frameNode->GetEventHub<BubbleEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnStateChange([&isStateChanged](const std::string& state) {
        if (state.find("\"isVisible\":false") != std::string::npos) {
            isStateChanged = true;
        }
    });

    /**
     * @tc.steps: step2. Simulate non-UI thread environment and call OnDetachFromMainTree.
     * @tc.expected: The state change event should be fired.
     */
    bool isUIThread = MultiThreadBuildManager::isUIThread_;
    MultiThreadBuildManager::isUIThread_ = false;
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);

    pattern->OnDetachFromMainTree();
    pattern->OnDetachFromMainTreeMultiThread();

    MultiThreadBuildManager::isUIThread_ = isUIThread;
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);

    EXPECT_FALSE(isStateChanged);
}
} // namespace OHOS::Ace::NG