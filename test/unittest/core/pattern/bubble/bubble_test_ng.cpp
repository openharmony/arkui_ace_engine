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
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/placement.h"
#include "core/components/popup/popup_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
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
constexpr bool BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_TRUE = true;
constexpr bool BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_FALSE = false;
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
const Color BUBBLE_PAINT_PROPERTY_MASK_COLOR = Color(0XFFFF0000);
const Color BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR = Color(0XFFFFFF00);
const Color BUBBLE_PAINT_PROPERTY_TEXT_COLOR = Color(0XFFFF0000);
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const SizeF TARGET_SIZE(TARGET_WIDTH, TARGET_HEIGHT);
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const Dimension BUBBLE_PAINT_PROPERTY_TARGET_SPACE = Dimension(20.1, DimensionUnit::PX);
const Dimension BUBBLE_PAINT_PROPERTY_FONT_SIZE = Dimension(20.1, DimensionUnit::PX);
const Ace::FontWeight BUBBLE_PAINT_PROPERTY_FONT_WEIGHT = Ace::FontWeight::W100;
constexpr Dimension BUBBLE_PAINT_PROPERTY_ARROW_OFFSET = 20.0_px;
constexpr Placement BUBBLE_LAYOUT_PROPERTY_PLACEMENT = Placement::LEFT;
constexpr Dimension BORDER_EDGE = 1.0_px;
constexpr Dimension BORDER_EDGE_LARGE = 20.0_px;
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

class BubbleTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static RefPtr<FrameNode> CreateBubbleNode(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateTargetNode();
};

void BubbleTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void BubbleTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

PaddingProperty CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

RefPtr<FrameNode> BubbleTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

RefPtr<FrameNode> BubbleTestNg::CreateBubbleNode(const TestProperty& testProperty)
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
 * @tc.name: BubblePatternTest001
 * @tc.desc: Test all the properties of bubble.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of bubble.
     */
    TestProperty testProperty;
    testProperty.enableArrow = std::make_optional(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
    testProperty.useCustom = std::make_optional(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_TRUE);
    testProperty.placement = std::make_optional(BUBBLE_LAYOUT_PROPERTY_PLACEMENT);
    testProperty.showInSubWindow = std::make_optional(BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW);

    testProperty.displayWindowOffset = std::make_optional(DISPLAY_WINDOW_OFFSET);
    testProperty.autoCancel = std::make_optional(BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_TRUE);
    testProperty.maskColor = std::make_optional(BUBBLE_PAINT_PROPERTY_MASK_COLOR);
    testProperty.backgroundColor = std::make_optional(BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR);
    testProperty.arrowOffset = std::make_optional(BUBBLE_PAINT_PROPERTY_ARROW_OFFSET);

    /**
     * @tc.steps: step2. create list frameNode and get LayoutProperty and paintProperty.
     * @tc.expected: step2. get LayoutProperty and paintProperty success.
     */

    RefPtr<FrameNode> frameNode = CreateBubbleNode(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<BubbleLayoutProperty> bubbleLayoutProperty = AceType::DynamicCast<BubbleLayoutProperty>(layoutProperty);
    EXPECT_NE(bubbleLayoutProperty, nullptr);

    RefPtr<BubbleRenderProperty> bubblePaintProperty = frameNode->GetPaintProperty<BubbleRenderProperty>();
    EXPECT_NE(bubblePaintProperty, nullptr);

    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_EQ(bubbleLayoutProperty->GetEnableArrow(), BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
    EXPECT_EQ(bubbleLayoutProperty->GetUseCustom(), BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_TRUE);
    EXPECT_EQ(bubbleLayoutProperty->GetPlacement(), BUBBLE_LAYOUT_PROPERTY_PLACEMENT);
    EXPECT_EQ(bubbleLayoutProperty->GetShowInSubWindow(), BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW);
    EXPECT_EQ(bubbleLayoutProperty->GetDisplayWindowOffset(), DISPLAY_WINDOW_OFFSET);

    EXPECT_EQ(bubblePaintProperty->GetAutoCancel(), BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_TRUE);
    EXPECT_EQ(bubblePaintProperty->GetMaskColor(), BUBBLE_PAINT_PROPERTY_MASK_COLOR);
    EXPECT_EQ(bubblePaintProperty->GetBackgroundColor(), BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR);
    EXPECT_EQ(bubblePaintProperty->GetArrowOffset(), BUBBLE_PAINT_PROPERTY_ARROW_OFFSET);
}

/**
 * @tc.name: BubblePatternTest002
 * @tc.desc: Verify whether the layout property, layoutAlgorithm and event functions are created.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and create layout property,paint property layoutAlgorithm, event.
     * @tc.expected: step2. related function is called.
     */
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    EXPECT_NE(bubblePattern, nullptr);
    auto bubbleLayoutProperty = bubblePattern->CreateLayoutProperty();
    EXPECT_NE(bubbleLayoutProperty, nullptr);
    auto bubblePaintProperty = bubblePattern->CreatePaintProperty();
    EXPECT_NE(bubblePaintProperty, nullptr);
    auto layoutAlgorithm = bubblePattern->CreateLayoutAlgorithm();
    EXPECT_NE(layoutAlgorithm, nullptr);
    auto paintMethod = bubblePattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto eventHub = bubblePattern->GetEventHub<BubbleEventHub>();
    EXPECT_NE(eventHub, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    EXPECT_NE(layoutAlgorithmWrapper, nullptr);
    auto bubbleLayoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_NE(bubbleLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: BubblePatternTest003
 * @tc.desc: Test event function of bubble.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, PanelPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set bubble event.
     * @tc.expected: step2. function is called.
     */
    auto bubbleHub = frameNode->GetEventHub<BubbleEventHub>();
    EXPECT_NE(bubbleHub, nullptr);
    std::string stateChange = STATE;
    auto onStateChange = [&stateChange](const std::string& change) { stateChange = change; };
    bubbleHub->SetOnStateChange(onStateChange);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    bubbleHub->FireChangeEvent(false);
    auto jsonFalse = JsonUtil::Create(true);
    jsonFalse->Put("isVisible", false);
    EXPECT_EQ(stateChange, jsonFalse->ToString());

    bubbleHub->FireChangeEvent(true);
    auto jsonTrue = JsonUtil::Create(true);
    jsonTrue->Put("isVisible", true);
    EXPECT_EQ(stateChange, jsonTrue->ToString());
}

/**
 * @tc.name: BubblePatternTest004
 * @tc.desc: Test bubble onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto bubbleLayoutProperty = frameNode->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_NE(bubbleLayoutProperty, nullptr);
    auto bubblePaintProperty = frameNode->GetPaintProperty<BubbleRenderProperty>();
    EXPECT_NE(bubblePaintProperty, nullptr);
    // update layout property
    bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
    bubbleLayoutProperty->UpdatePlacement(BUBBLE_LAYOUT_PROPERTY_PLACEMENT);
    // update paint property
    bubblePaintProperty->UpdateArrowOffset(BUBBLE_PAINT_PROPERTY_ARROW_OFFSET);
    bubblePaintProperty->UpdateAutoCancel(BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_TRUE);

    /**
     * @tc.steps: step3. frameNode markOnModifyDone.
     * @tc.expected: step3. check whether the properties is correct.
     */
    frameNode->MarkModifyDone();
    auto layoutProp = frameNode->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_NE(layoutProp, nullptr);
    EXPECT_EQ(layoutProp->GetEnableArrow().value_or(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_FALSE),
        BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
    EXPECT_EQ(layoutProp->GetPlacement().value_or(Placement::BOTTOM), BUBBLE_LAYOUT_PROPERTY_PLACEMENT);
    auto paintProp = frameNode->GetPaintProperty<BubbleRenderProperty>();
    EXPECT_NE(paintProp, nullptr);
    EXPECT_EQ(paintProp->GetArrowOffset(), BUBBLE_PAINT_PROPERTY_ARROW_OFFSET);
    EXPECT_EQ(paintProp->GetAutoCancel(), BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_TRUE);
}

/**
 * @tc.name: BubblePatternTest005
 * @tc.desc: Test bubble OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    EXPECT_NE(frameNode, nullptr);
    auto blankFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(blankFrameNode, nullptr);
    frameNode->AddChild(blankFrameNode);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    EXPECT_NE(bubblePattern, nullptr);
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_NE(bubbleLayoutProperty, nullptr);
    // update layoutProperty
    bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
    bubbleLayoutProperty->UpdateUseCustom(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_TRUE);
    bubbleLayoutProperty->UpdatePlacement(Placement::BOTTOM);
    bubbleLayoutProperty->UpdateShowInSubWindow(BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    EXPECT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT));

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BUBBLE_WIDTH), CalcLength(BUBBLE_HEIGHT)));

    /**
     * @tc.steps: step4. frameNode onDirtyLayoutWrapperSwap.
     */
    DirtySwapConfig config;
    config.skipLayout = false;
    config.skipMeasure = false;
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    EXPECT_NE(layoutAlgorithmWrapper, nullptr);
    auto bubbleLayoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_NE(bubbleLayoutAlgorithm, nullptr);
    auto host = bubblePattern->GetHost();
    auto childNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    EXPECT_NE(childNode, nullptr);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    bool flag = bubblePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config.skipMeasure, config.skipLayout);
    EXPECT_EQ(flag, true);
    bool flagTwo = bubblePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_EQ(flagTwo, false);
}

/**
 * @tc.name: BubblePatternTest006
 * @tc.desc: Test bubble pattern InitTouchEvent HandleTouchEvent HandleTouchDOWN.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create pattern and update paintProperty gestureHub and test InitTouchEvent.
     * @tc.expected: step2. check whether the gestureEvent info is correct.
     */
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    EXPECT_NE(bubblePattern, nullptr);
    auto paintProperty = bubblePattern->CreatePaintProperty();
    EXPECT_NE(paintProperty, nullptr);
    auto bubblePaintProperty = AceType::DynamicCast<BubbleRenderProperty>(paintProperty);
    EXPECT_NE(bubblePaintProperty, nullptr);
    bubblePaintProperty->UpdateAutoCancel(BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_FALSE);

    /**
     * @tc.steps: step3. create gestureHub and test InitTouchEvent HandleTouchEvent.
     * @tc.expected: step3. check whether the function is executed.
     */
    // test InitTouchEvent
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    RefPtr<GestureEventHub> gestureHub =
        AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    bubblePattern->InitTouchEvent();

    // test HandleTouchEvent
    TouchEventInfo touchEventInfo = TouchEventInfo("");
    bubblePattern->HandleTouchEvent(touchEventInfo);

    TouchEventInfo touchEventInfo1 = TouchEventInfo("");
    TouchLocationInfo touchLocationInfo1 = TouchLocationInfo(1);
    touchLocationInfo1.SetLocalLocation(Offset(100.0, 100.0));
    touchLocationInfo1.SetTouchType(TouchType::UP);
    touchEventInfo1.AddTouchLocationInfo(std::move(touchLocationInfo1));
    bubblePattern->HandleTouchEvent(touchEventInfo1);

    TouchEventInfo touchEventInfo2 = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo2 = TouchLocationInfo(1);
    touchLocationInfo2.SetLocalLocation(Offset(100.0, 100.0));
    touchLocationInfo2.SetTouchType(TouchType::DOWN);
    touchEventInfo2.AddTouchLocationInfo(std::move(touchLocationInfo2));
    bubblePattern->HandleTouchEvent(touchEventInfo2);

    bubblePaintProperty->UpdateAutoCancel(BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_TRUE);
}

/**
 * @tc.name: BubblePatternTest007
 * @tc.desc: Test CreateBubbleNode with message and Update.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest007, TestSize.Level1)
{
    // set value to popupParam
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetArrowOffset(BUBBLE_PAINT_PROPERTY_ARROW_OFFSET);
    popupParam->SetEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_FALSE);
    popupParam->SetPlacement(Placement::BOTTOM_RIGHT);
    popupParam->SetUseCustomComponent(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    popupParam->SetMaskColor(BUBBLE_PAINT_PROPERTY_MASK_COLOR);
    popupParam->SetHasAction(false);
    popupParam->SetBackgroundColor(BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR);
    popupParam->SetTargetSpace(BUBBLE_PAINT_PROPERTY_TARGET_SPACE);
    popupParam->SetTextColor(BUBBLE_PAINT_PROPERTY_TEXT_COLOR);
    popupParam->SetFontSize(BUBBLE_PAINT_PROPERTY_FONT_SIZE);
    popupParam->SetFontWeight(BUBBLE_PAINT_PROPERTY_FONT_WEIGHT);
    popupParam->SetFontStyle(Ace::FontStyle::ITALIC);
    popupParam->SetHasTransition(true);

    // create bubbleNode
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(targetNode, nullptr);
    // set popupTheme and  buttonTheme to themeManager before using themeManager
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    EXPECT_NE(popupNode, nullptr);
    EXPECT_EQ(popupNode->GetPattern<BubblePattern>()->GetHasTransition(), true);
    auto firstTextNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    EXPECT_NE(firstTextNode, nullptr);

    // update BubbleNode
    auto popupId = popupNode->GetId();
    popupParam->SetPlacement(Placement::LEFT);
    popupParam->SetMessage(BUBBLE_NEW_MESSAGE);
    popupParam->SetUseCustomComponent(!popupParam->IsUseCustom());
    popupParam->SetHasAction(true);
    BubbleView::UpdatePopupParam(popupId, popupParam, targetNode);
    EXPECT_EQ(popupNode->GetPattern<BubblePattern>()->GetHasTransition(), true);
    auto secondTextNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    EXPECT_NE(secondTextNode, nullptr);
}

/**
 * @tc.name: BubblePatternTest008
 * @tc.desc: Test CreateCustomBubbleNode and Update.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set value to popupParam.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetArrowOffset(BUBBLE_PAINT_PROPERTY_ARROW_OFFSET);
    popupParam->SetShowInSubWindow(BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW);
    popupParam->SetEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
    popupParam->SetPlacement(Placement::BOTTOM_RIGHT);
    popupParam->SetUseCustomComponent(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_TRUE);
    popupParam->SetMaskColor(BUBBLE_PAINT_PROPERTY_MASK_COLOR);
    popupParam->SetHasAction(false);
    popupParam->SetBackgroundColor(BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR);
    popupParam->SetTargetSpace(BUBBLE_PAINT_PROPERTY_TARGET_SPACE);
    popupParam->SetTextColor(BUBBLE_PAINT_PROPERTY_TEXT_COLOR);
    popupParam->SetFontSize(BUBBLE_PAINT_PROPERTY_FONT_SIZE);
    popupParam->SetFontWeight(BUBBLE_PAINT_PROPERTY_FONT_WEIGHT);
    popupParam->SetHasTransition(true);
    /**
     * @tc.steps: step2. create custom bubble and get popupNode.
     * @tc.expected: Check the popupNode were created successfully.
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
    EXPECT_EQ(popupNode->GetPattern<BubblePattern>()->GetHasTransition(), true);
    /**
     * @tc.steps: step3. update customBubbleNode.
     */
    auto popupId = popupNode->GetId();
    popupParam->SetPlacement(Placement::LEFT);
    popupParam->SetMessage(BUBBLE_NEW_MESSAGE);
    popupParam->SetHasAction(true);
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    BubbleView::UpdateCustomPopupParam(popupId, popupParam);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    BubbleView::UpdateCustomPopupParam(popupId, popupParam);
    EXPECT_EQ(popupNode->GetPattern<BubblePattern>()->GetHasTransition(), true);
    /**
     * @tc.steps: step4. using default param to create custom bubble and get popupNode.
     * @tc.expected: Check the popupNode were created successfully.
     */
    auto popupParam2 = AceType::MakeRefPtr<PopupParam>();
    auto popupNode2 =
        BubbleView::CreateCustomBubbleNode(targetNode->GetTag(), targetNode->GetId(), rowFrameNode, popupParam2);
    ASSERT_NE(popupNode2, nullptr);
    BubbleView::UpdateCustomPopupParam(popupId, popupParam2);
}

/**
 * @tc.name: BubblePatternTest009
 * @tc.desc: Test StartEnteringAnimation and StartExitingAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto pattern = AceType::MakeRefPtr<BubblePattern>(targetId, targetTag);
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, pattern);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. call StartEnteringAnimation and StartExitingAnimation without finish callback.
     * @tc.expected: pattern->transitionStatus_ changed.
     */
    pattern->GetPopupTheme();
    pattern->arrowPlacement_ = Placement::BOTTOM;
    pattern->StartEnteringAnimation(nullptr);
    EXPECT_EQ(pattern->transitionStatus_, TransitionStatus::NORMAL);
    pattern->StartExitingAnimation(nullptr);
    EXPECT_EQ(pattern->transitionStatus_, TransitionStatus::INVISIABLE);

    /**
     * @tc.steps: step3. call StartEnteringAnimation and StartExitingAnimation with finish callback.
     * @tc.expected: pattern->transitionStatus_ changed.
     */
    pattern->transitionStatus_ = TransitionStatus::INVISIABLE;
    pattern->StartEnteringAnimation([]() {});
    EXPECT_EQ(pattern->transitionStatus_, TransitionStatus::NORMAL);
    pattern->StartExitingAnimation([]() {});
    EXPECT_EQ(pattern->transitionStatus_, TransitionStatus::INVISIABLE);

    pattern->transitionStatus_ = TransitionStatus::INVISIABLE;
    pattern->StartEnteringTransitionEffects(frameNode, []() {});
    pattern->StartExitingTransitionEffects(frameNode, []() {});

    /**
     * @tc.steps: step4. call StartEnteringAnimation and StartExitingAnimation while animating.
     * @tc.expected: pattern->transitionStatus_ has no changed.
     */
    pattern->transitionStatus_ = TransitionStatus::ENTERING;
    pattern->StartEnteringAnimation(nullptr);
    EXPECT_EQ(pattern->transitionStatus_, TransitionStatus::ENTERING);
    pattern->transitionStatus_ = TransitionStatus::EXITING;
    pattern->StartExitingAnimation(nullptr);
    EXPECT_EQ(pattern->transitionStatus_, TransitionStatus::INVISIABLE);
}

/**
 * @tc.name: BubblePatternTest010
 * @tc.desc: Test IsOnShow.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble.
     */
    auto pattern = AceType::MakeRefPtr<BubblePattern>(-1, "target");
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. call IsOnShow.
     */
    pattern->transitionStatus_ = TransitionStatus::ENTERING;
    EXPECT_TRUE(pattern->IsOnShow());
    pattern->transitionStatus_ = TransitionStatus::NORMAL;
    EXPECT_TRUE(pattern->IsOnShow());
    pattern->transitionStatus_ = TransitionStatus::EXITING;
    EXPECT_FALSE(pattern->IsOnShow());
    pattern->transitionStatus_ = TransitionStatus::INVISIABLE;
    EXPECT_FALSE(pattern->IsOnShow());
}

/**
 * @tc.name: BubblePatternTest011
 * @tc.desc: Test GetInvisibleOffset.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble.
     */
    auto pattern = AceType::MakeRefPtr<BubblePattern>(-1, "target");
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. call GetInvisibleOffset.
     */
    OffsetT<Dimension> offset;
    pattern->arrowPlacement_.reset();
    offset = pattern->GetInvisibleOffset();
    EXPECT_EQ(offset.GetX().Value(), 0);
    EXPECT_EQ(offset.GetY().Value(), 0);
    pattern->arrowPlacement_ = Placement::LEFT;
    offset = pattern->GetInvisibleOffset();
    EXPECT_GT(offset.GetX().Value(), 0);
    pattern->arrowPlacement_ = Placement::LEFT_TOP;
    offset = pattern->GetInvisibleOffset();
    EXPECT_GT(offset.GetX().Value(), 0);
    pattern->arrowPlacement_ = Placement::LEFT_BOTTOM;
    offset = pattern->GetInvisibleOffset();
    EXPECT_GT(offset.GetX().Value(), 0);
    pattern->arrowPlacement_ = Placement::RIGHT;
    offset = pattern->GetInvisibleOffset();
    EXPECT_LT(offset.GetX().Value(), 0);
    pattern->arrowPlacement_ = Placement::RIGHT_TOP;
    offset = pattern->GetInvisibleOffset();
    EXPECT_LT(offset.GetX().Value(), 0);
    pattern->arrowPlacement_ = Placement::RIGHT_BOTTOM;
    offset = pattern->GetInvisibleOffset();
    EXPECT_LT(offset.GetX().Value(), 0);
    pattern->arrowPlacement_ = Placement::TOP;
    offset = pattern->GetInvisibleOffset();
    EXPECT_GT(offset.GetY().Value(), 0);
    pattern->arrowPlacement_ = Placement::TOP_LEFT;
    offset = pattern->GetInvisibleOffset();
    EXPECT_GT(offset.GetY().Value(), 0);
    pattern->arrowPlacement_ = Placement::TOP_RIGHT;
    offset = pattern->GetInvisibleOffset();
    EXPECT_GT(offset.GetY().Value(), 0);
    pattern->arrowPlacement_ = Placement::BOTTOM;
    offset = pattern->GetInvisibleOffset();
    EXPECT_LT(offset.GetY().Value(), 0);
    pattern->arrowPlacement_ = Placement::BOTTOM_LEFT;
    offset = pattern->GetInvisibleOffset();
    EXPECT_LT(offset.GetY().Value(), 0);
    pattern->arrowPlacement_ = Placement::BOTTOM_RIGHT;
    offset = pattern->GetInvisibleOffset();
    EXPECT_LT(offset.GetY().Value(), 0);
    pattern->arrowPlacement_ = Placement::NONE;
    offset = pattern->GetInvisibleOffset();
    EXPECT_EQ(offset.GetX().Value(), 0);
    EXPECT_EQ(offset.GetY().Value(), 0);
}

/**
 * @tc.name: BubblePatternTest012
 * @tc.desc: Test start animation in OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto pattern = AceType::MakeRefPtr<BubblePattern>(targetId, targetTag);
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto blankFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(blankFrameNode, nullptr);
    frameNode->AddChild(blankFrameNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step2. call StartEnteringAnimation.
     * @tc.expected: pattern->transitionStatus_ has no changed.
     */
    pattern->StartEnteringAnimation(nullptr);
    EXPECT_EQ(pattern->transitionStatus_, TransitionStatus::INVISIABLE);

    /**
     * @tc.steps: step3. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: pattern->transitionStatus_ has changed.
     */
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_EQ(pattern->transitionStatus_, TransitionStatus::NORMAL);
}

/*
 * @tc.name: BubblePaintMethod001
 * @tc.desc: Test BubblePaintMethod PaintBorder PaintBubble.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the BubblePaintMethod.
     */
    BubblePaintMethod bubblePaintMethod;
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Create the GeometryNode and PaintWrapper.Set the progressPaintProperty.
     * @tc.expected: step2. Check the GeometryNode and PaintWrapper were created successfully.
     */
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateBubbleNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto bubblePaintProperty = frameNode->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(bubblePaintProperty, nullptr);

    auto renderContext = frameNode->GetRenderContext();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, bubblePaintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    /**
     * @tc.steps: step3. Set the different properties.Call the function PaintBorder.
     * @tc.expected: step3. Check the properties.
     */
    // PaintBorder border_.IsAllEqual, border_.HasValue.
    bubblePaintMethod.border_.SetBorderEdge(BorderEdge(Color::BLACK, BORDER_EDGE, BorderStyle::SOLID));
    bubblePaintMethod.PaintBorder(canvas, paintWrapper);
    EXPECT_TRUE(bubblePaintMethod.border_.HasValue());
    EXPECT_TRUE(bubblePaintMethod.border_.IsAllEqual());

    // PaintBorder !border_.IsAllEqual, border_.HasValue.
    bubblePaintMethod.border_.SetLeftEdge(BorderEdge(Color::BLUE, BORDER_EDGE_LARGE, BorderStyle::DOTTED));
    ASSERT_FALSE(bubblePaintMethod.border_.IsAllEqual());
    bubblePaintMethod.PaintBorder(canvas, paintWrapper);
    bubblePaintMethod.border_.SetLeftEdge(BorderEdge(Color::BLUE, BORDER_EDGE_LARGE, BorderStyle::DASHED));
    ASSERT_FALSE(bubblePaintMethod.border_.IsAllEqual());
    bubblePaintMethod.PaintBorder(canvas, paintWrapper);
    bubblePaintMethod.border_.SetLeftEdge(BorderEdge(Color::BLUE, BORDER_EDGE_LARGE, BorderStyle::NONE));
    ASSERT_FALSE(bubblePaintMethod.border_.IsAllEqual());
    bubblePaintMethod.PaintBorder(canvas, paintWrapper);
    EXPECT_TRUE(bubblePaintMethod.border_.IsAllEqual());

    /**
     * @tc.steps: step4. Set the different properties.Call the function PaintBubble.
     * @tc.expected: step4. Check the properties.
     */
    bubblePaintMethod.SetShowArrow(true);
    bubblePaintMethod.enableArrow_ = true;
    bubblePaintMethod.PaintBubble(canvas, paintWrapper);
    bubblePaintMethod.clipFrameNode_ = frameNode;
    bubblePaintMethod.clipPath_ = CLIP_PATH;
    bubblePaintMethod.ClipBubble(paintWrapper);
    EXPECT_TRUE(bubblePaintMethod.showArrow_);

    bubblePaintMethod.SetShowArrow(false);
    bubblePaintMethod.PaintBubble(canvas, paintWrapper);
    bubblePaintMethod.clipFrameNode_ = frameNode;
    bubblePaintMethod.clipPath_ = CLIP_PATH;
    bubblePaintMethod.ClipBubble(paintWrapper);
    ASSERT_FALSE(bubblePaintMethod.showArrow_);

    bubblePaintMethod.SetShowArrow(true);
    for (size_t i = 0; i < BUBBLE_LAYOUT_PROPERTY_PLACEMENTS.size(); i++) {
        bubblePaintProperty->UpdatePlacement(BUBBLE_LAYOUT_PROPERTY_PLACEMENTS[i]);
        bubblePaintMethod.PaintBubble(canvas, paintWrapper);
    }
}

/*
 * @tc.name: BubblePaintMethod002
 * @tc.desc: Test BubblePaintMethod UpdateArrowOffset.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the BubblePaintMethod.
     */
    BubblePaintMethod bubblePaintMethod;
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    /**
     * @tc.steps: step2. Create the GeometryNode and PaintWrapper.Set the progressPaintProperty.
     * @tc.expected: Check the GeometryNode and PaintWrapper were created successfully.
     */
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateBubbleNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto bubblePaintProperty = frameNode->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(bubblePaintProperty, nullptr);

    WeakPtr<RenderContext> renderContext;
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, bubblePaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    /**
     * @tc.steps: step4. Set the different properties.Call the function UpdateArrowOffset.
     * @tc.expected: Check the properties.
     */
    auto paintProperty = AceType::DynamicCast<BubbleRenderProperty>(paintWrapper->GetPaintProperty());
    ASSERT_NE(paintProperty, nullptr);
    bubblePaintMethod.UpdateArrowOffset(Dimension(10.0), paintProperty->GetPlacement().value_or(Placement::BOTTOM));
    EXPECT_EQ(bubblePaintMethod.arrowOffset_.Value(), 10.0);
    bubblePaintMethod.UpdateArrowOffset(
        Dimension(10.0, DimensionUnit::PERCENT), paintProperty->GetPlacement().value_or(Placement::BOTTOM));
    EXPECT_EQ(bubblePaintMethod.arrowOffset_.Value(), 1.0);
    bubblePaintMethod.UpdateArrowOffset(std::nullopt, paintProperty->GetPlacement().value_or(Placement::TOP_LEFT));
    EXPECT_EQ(bubblePaintMethod.arrowOffset_.Value(), ARROW_ZERO_PERCENT_VALUE.Value());
    bubblePaintMethod.UpdateArrowOffset(std::nullopt, paintProperty->GetPlacement().value_or(Placement::TOP_RIGHT));
    EXPECT_EQ(bubblePaintMethod.arrowOffset_.Value(), ARROW_ONE_HUNDRED_PERCENT_VALUE.Value());
    bubblePaintMethod.UpdateArrowOffset(std::nullopt, paintProperty->GetPlacement().value_or(Placement::NONE));
}

/*
 * @tc.name: BubblePaintMethod003
 * @tc.desc: Test BubblePaintMethod PaintMask.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePaintMethod003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the BubblePaintMethod.
     */
    BubblePaintMethod bubblePaintMethod;
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(1);
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    /**
     * @tc.steps: step2. Create the GeometryNode and PaintWrapper.Set the progressPaintProperty.
     * @tc.expected: Check the GeometryNode and PaintWrapper were created successfully.
     */
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateBubbleNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto bubblePaintProperty = frameNode->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(bubblePaintProperty, nullptr);

    auto renderContext = frameNode->GetRenderContext();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, bubblePaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    /**
     * @tc.steps: step4. Call the function PaintMask.
     */
    bubblePaintMethod.PaintMask(canvas, paintWrapper);
}

/**
 * @tc.name: BubblePatternTest013
 * @tc.desc: Test bubble onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set value to popupParam.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    ButtonProperties buttonProperties { true, "Button" };
    buttonProperties.action = AceType::MakeRefPtr<ClickEvent>(nullptr);
    popupParam->SetPrimaryButtonProperties(buttonProperties);
    popupParam->SetSecondaryButtonProperties(buttonProperties);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetArrowOffset(BUBBLE_PAINT_PROPERTY_ARROW_OFFSET);
    popupParam->SetEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_FALSE);
    popupParam->SetPlacement(Placement::BOTTOM_RIGHT);
    popupParam->SetUseCustomComponent(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    popupParam->SetMaskColor(BUBBLE_PAINT_PROPERTY_MASK_COLOR);
    popupParam->SetHasAction(false);
    popupParam->SetBackgroundColor(BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR);
    popupParam->SetTargetSpace(BUBBLE_PAINT_PROPERTY_TARGET_SPACE);
    popupParam->SetTextColor(BUBBLE_PAINT_PROPERTY_TEXT_COLOR);
    popupParam->SetFontSize(BUBBLE_PAINT_PROPERTY_FONT_SIZE);
    popupParam->SetFontWeight(BUBBLE_PAINT_PROPERTY_FONT_WEIGHT);
    popupParam->SetFontStyle(Ace::FontStyle::ITALIC);
    /**
     * @tc.steps: step2. create bubble and get popupNode.
     * @tc.expected: Check the popupNode were created successfully.
     */
    auto targetNode = CreateTargetNode();
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProps = pattern->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(paintProps, nullptr);
    /**
     * @tc.steps: step3. set properties and call MarkModifyDone function.
     */
    auto layoutNode = BubbleView::CreateButtons(popupParam, popupNode->GetId(), targetNode->GetId());
    auto buttons = layoutNode->GetChildren();
    BubbleView::UpdateBubbleButtons(buttons, popupParam);
    pattern->mouseEventInitFlag_ = true;
    pattern->touchEventInitFlag_ = true;
    popupNode->MarkModifyDone();
    pattern->mouseEventInitFlag_ = false;
    pattern->touchEventInitFlag_ = false;
    paintProps->UpdateUseCustom(true);
    popupNode->MarkModifyDone();
    paintProps->UpdateUseCustom(false);
    paintProps->UpdatePrimaryButtonShow(true);
    paintProps->UpdateSecondaryButtonShow(true);
    popupNode->MarkModifyDone();
}

/**
 * @tc.name: BubblePatternTest014
 * @tc.desc: Test bubble hover and touch callback.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set value to popupParam.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    ButtonProperties buttonProperties { true, "Button" };
    buttonProperties.action = AceType::MakeRefPtr<ClickEvent>(nullptr);
    popupParam->SetPrimaryButtonProperties(buttonProperties);
    popupParam->SetSecondaryButtonProperties(buttonProperties);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    /**
     * @tc.steps: step2. create bubble and get popupNode.
     * @tc.expected: Check the popupNode were created successfully.
     */
    auto targetNode = CreateTargetNode();
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProps = pattern->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(paintProps, nullptr);
    /**
     * @tc.steps: step3. set properties and call MarkModifyDone function.
     */
    paintProps->UpdateUseCustom(false);
    paintProps->UpdatePrimaryButtonShow(true);
    paintProps->UpdateSecondaryButtonShow(true);
    popupNode->MarkModifyDone();
    /**
     * @tc.steps: step4. call hover, touch callback.
     * @tc.expected: now can't callback ButtonOnHover, isHover_ can't change.
     */
    auto buttonRowNode = pattern->GetButtonRowNode();
    ASSERT_NE(buttonRowNode, nullptr);
    for (const auto& child : buttonRowNode->GetChildren()) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(child);
        ASSERT_NE(buttonNode, nullptr);
        auto inputHub = buttonNode->GetOrCreateInputEventHub();
        ASSERT_NE(inputHub->hoverEventActuator_, nullptr);
        auto inputEvents = inputHub->hoverEventActuator_->inputEvents_;
        for (auto& event : inputEvents) {
            event->GetOnHoverEventFunc()(false);
            event->GetOnHoverEventFunc()(true);
        }
        EXPECT_FALSE(pattern->isHover_);

        auto gestureHub = buttonNode->GetOrCreateGestureEventHub();
        auto touchEvents = gestureHub->touchEventActuator_->touchEvents_;
        TouchEventInfo touchEventInfo("default");
        TouchLocationInfo touch(0);
        touch.SetTouchType(TouchType::DOWN);
        touchEventInfo.AddTouchLocationInfo(std::move(touch));
        for (auto& event : touchEvents) {
            pattern->isHover_ = true;
            event->GetTouchEventCallback()(touchEventInfo);
            pattern->isHover_ = false;
            event->GetTouchEventCallback()(touchEventInfo);
        }
        touch.SetTouchType(TouchType::UP);
        touchEventInfo.touches_.clear();
        touchEventInfo.AddTouchLocationInfo(std::move(touch));
        for (auto& event : touchEvents) {
            pattern->isHover_ = true;
            event->GetTouchEventCallback()(touchEventInfo);
            pattern->isHover_ = false;
            event->GetTouchEventCallback()(touchEventInfo);
        }
    }
}

/**
 * @tc.name: BubblePatternTest015
 * @tc.desc: Test CreateBubbleNode with Offset, Radius, ArrowHeight, ArrowWidth and Shadow.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set popup value to popupParam.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetTargetOffset(POPUP_PARAM_POSITION_OFFSET);

    Dimension radius = 20.0_px;
    Dimension arrowHeight = 20.0_px;
    Dimension arrowWidth = 20.0_px;
    Shadow shadow = ShadowConfig::DefaultShadowL;
    popupParam->SetRadius(radius);
    popupParam->SetArrowHeight(arrowHeight);
    popupParam->SetArrowWidth(arrowWidth);
    popupParam->SetShadow(shadow);

    /**
     * @tc.steps: step2. create BubbleNode with position offset
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(targetNode, nullptr);
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto firstTextNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    ASSERT_NE(firstTextNode, nullptr);

    /**
     * @tc.steps: step3. use BubbleLayoutProperty to check PositionOffset.
     * @tc.expected: check whether GetPositionOffset value is correct.
     */
    auto property = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_EQ(property->GetPositionOffset().value(), BUBBLE_POSITION_OFFSET);
    EXPECT_EQ(property->GetRadius().value(), radius);
    EXPECT_EQ(property->GetArrowHeight().value(), arrowHeight);
    EXPECT_EQ(property->GetArrowWidth().value(), arrowWidth);

    auto childNode = AceType::DynamicCast<FrameNode>(popupNode->GetFirstChild());
    ASSERT_NE(childNode, nullptr);
    auto renderContext = childNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackShadow().value(), shadow);

    auto popupId = popupNode->GetId();
    Dimension radiusNew = 40.0_px;
    Dimension arrowHeightNew = 40.0_px;
    Dimension arrowWidthNew = 40.0_px;
    Shadow shadowNew = ShadowConfig::DefaultShadowM;
    popupParam->SetRadius(radiusNew);
    popupParam->SetArrowHeight(arrowHeightNew);
    popupParam->SetArrowWidth(arrowWidthNew);
    popupParam->SetShadow(shadowNew);
    BubbleView::UpdateCommonParam(popupId, popupParam);
    EXPECT_EQ(property->GetRadius().value(), radiusNew);
    EXPECT_EQ(property->GetArrowHeight().value(), arrowHeightNew);
    EXPECT_EQ(property->GetArrowWidth().value(), arrowWidthNew);
    EXPECT_EQ(renderContext->GetBackShadow().value(), shadowNew);
}

/**
 * @tc.name: BubblePatternTest016
 * @tc.desc: Test CreateCustomBubbleNode with with Offset, Radius, ArrowHeight, ArrowWidth and Shadow.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set popup value to popupParam.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetTargetOffset(POPUP_PARAM_POSITION_OFFSET);

    Dimension radius = 20.0_px;
    Dimension arrowHeight = 20.0_px;
    Dimension arrowWidth = 20.0_px;
    Shadow shadow = ShadowConfig::DefaultShadowL;
    popupParam->SetRadius(radius);
    popupParam->SetArrowHeight(arrowHeight);
    popupParam->SetArrowWidth(arrowWidth);
    popupParam->SetShadow(shadow);

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
    auto property = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_EQ(property->GetPositionOffset().value(), BUBBLE_POSITION_OFFSET);
    EXPECT_EQ(property->GetRadius().value(), radius);
    EXPECT_EQ(property->GetArrowHeight().value(), arrowHeight);
    EXPECT_EQ(property->GetArrowWidth().value(), arrowWidth);

    auto childNode = AceType::DynamicCast<FrameNode>(popupNode->GetFirstChild());
    ASSERT_NE(childNode, nullptr);
    auto renderContext = childNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackShadow().value(), shadow);
}

/**
 * @tc.name: BubblePatternTest021
 * @tc.desc: Test UpdateCommonParam with with Offset, Radius, ArrowHeight, ArrowWidth and Shadow.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubblePatternTest021, TestSize.Level1)
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
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    BubbleView::UpdateCommonParam(popupNode->GetId(), popupParam);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    auto property = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_EQ(property->GetPositionOffset().value(), BUBBLE_POSITION_OFFSET);
}

/**
 * @tc.name: BubbleLayoutTest001
 * @tc.desc: Test BubbleNode layout
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestNg, BubbleLayoutTest001, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BubbleLayoutTest002, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BubbleLayoutTest003, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BubbleLayoutTest004, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BubbleLayoutTest005, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BubbleLayoutTest006, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BubbleLayoutTest007, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BubbleLayoutTest008, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BubbleLayoutTest009, TestSize.Level1)
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

HWTEST_F(BubbleTestNg, BubbleLayoutTest010, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BubbleBorderTest010, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BubblePatternTest022, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BorderLinearGradientPointTest001, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BorderLinearGradientPointTest002, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BorderLinearGradientColorsTest001, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BorderLinearGradientColorsTest002, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BubbleLayoutTest011, TestSize.Level1)
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
HWTEST_F(BubbleTestNg, BorderLinearGradientColorsTest003, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
