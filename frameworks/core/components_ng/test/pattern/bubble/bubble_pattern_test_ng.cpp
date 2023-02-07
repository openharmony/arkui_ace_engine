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
#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/properties/placement.h"
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/test/mock/rosen/testing_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

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

constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float CONTAINER_WIDTH = 600.0f;
constexpr float CONTAINER_HEIGHT = 1000.0f;
constexpr float BUBBLE_WIDTH = 80.0f;
constexpr float BUBBLE_HEIGHT = 50.0f;

const std::string BUBBLE_MESSAGE = "Hello World";
const std::string BUBBLE_NEW_MESSAGE = "Good";
const std::string STATE = "true";
const OffsetF DISPLAY_WINDOW_OFFSET = OffsetF(ZERO, ZERO);
const Color BUBBLE_PAINT_PROPERTY_MASK_COLOR = Color(0XFFFF0000);
const Color BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR = Color(0XFFFFFF00);
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
constexpr Dimension BUBBLE_PAINT_PROPERTY_ARROW_OFFSET = 20.0_px;
constexpr Placement BUBBLE_LAYOUT_PROPERTY_PLACEMENT = Placement::LEFT;
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

class BubblePatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static RefPtr<FrameNode> CreateBubbleNode(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateTargetNode();
};

void BubblePatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}
void BubblePatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
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

RefPtr<FrameNode> BubblePatternTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

RefPtr<FrameNode> BubblePatternTestNg::CreateBubbleNode(const TestProperty& testProperty)
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
HWTEST_F(BubblePatternTestNg, BubblePatternTest001, TestSize.Level1)
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
HWTEST_F(BubblePatternTestNg, BubblePatternTest002, TestSize.Level1)
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
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
HWTEST_F(BubblePatternTestNg, PanelPatternTest003, TestSize.Level1)
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
HWTEST_F(BubblePatternTestNg, BubblePatternTest004, TestSize.Level1)
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
HWTEST_F(BubblePatternTestNg, BubblePatternTest005, TestSize.Level1)
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
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
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
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    bool flag = bubblePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config.skipMeasure, config.skipLayout);
    EXPECT_EQ(flag, true);
    bool flagTwo = bubblePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_EQ(flagTwo, false);
}

/**
 * @tc.name: BubblePatternTest006
 * @tc.desc: Test bubble pattern InitTouchEvent HandleTouchEvent HandleTouchDown.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePatternTestNg, BubblePatternTest006, TestSize.Level1)
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
    bubblePattern->InitTouchEvent(gestureHub);

    // test HandleTouchEvent
    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(100.0, 100.0));
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    bubblePattern->HandleTouchEvent(touchEventInfo);

    bubblePaintProperty->UpdateAutoCancel(BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_TRUE);
    bubblePattern->targetNodeId_ = targetId;
    bubblePattern->touchRegion_ = RectF(OffsetF(50, 50), SizeF(100, 100));
    bubblePattern->HandleTouchDown(Offset(100.0, 100.0));
}

/**
 * @tc.name: BubblePatternTest007
 * @tc.desc: Test CreateBubbleNode with message and Update.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePatternTestNg, BubblePatternTest007, TestSize.Level1)
{
    // set value to popupParam
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetArrowOffset(BUBBLE_PAINT_PROPERTY_ARROW_OFFSET);
    popupParam->SetShowInSubWindow(BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW);
    popupParam->SetEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_FALSE);
    popupParam->SetPlacement(Placement::BOTTOM_RIGHT);
    popupParam->SetUseCustomComponent(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    popupParam->SetMaskColor(BUBBLE_PAINT_PROPERTY_MASK_COLOR);
    popupParam->SetHasAction(false);
    popupParam->SetBackgroundColor(BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR);

    // create bubbleNode
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(targetNode, nullptr);
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    EXPECT_NE(popupNode, nullptr);
    auto firstTextNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    EXPECT_NE(firstTextNode, nullptr);

    // update BubbleNode
    auto popupId = popupNode->GetId();
    popupParam->SetPlacement(Placement::LEFT);
    popupParam->SetMessage(BUBBLE_NEW_MESSAGE);
    popupParam->SetUseCustomComponent(!popupParam->IsUseCustom());
    popupParam->SetHasAction(true);
    BubbleView::UpdatePopupParam(popupId, popupParam, targetNode);
    auto secondTextNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    EXPECT_NE(secondTextNode, nullptr);
}

/**
 * @tc.name: BubblePatternTest008
 * @tc.desc: Test CreateBubbleNode with CombinedChild and Update..
 * @tc.type: FUNC
 */
HWTEST_F(BubblePatternTestNg, BubblePatternTest008, TestSize.Level1)
{
    // set value to popupParam
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetShowInSubWindow(BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW);
    popupParam->SetEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
    popupParam->SetPlacement(Placement::BOTTOM_RIGHT);
    popupParam->SetUseCustomComponent(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    popupParam->SetHasAction(false);
    ButtonProperties primaryProperties;
    primaryProperties.showButton = true;
    primaryProperties.value = BUBBLE_MESSAGE;
    popupParam->SetPrimaryButtonProperties(primaryProperties);
    ButtonProperties secondProperties;
    secondProperties.showButton = true;
    secondProperties.value = BUBBLE_NEW_MESSAGE;
    popupParam->SetSecondaryButtonProperties(secondProperties);

    // create bubbleNode
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(targetNode, nullptr);

    // set popupTheme and  buttonTheme to themeManager before using themeManager
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<ButtonTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<ButtonTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<ButtonTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<ButtonTheme>()))
        .WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));

    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    EXPECT_NE(popupNode, nullptr);
    // update Property
    primaryProperties.showButton = false;
    popupParam->SetPrimaryButtonProperties(primaryProperties);
    auto popupNodeTwo = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    EXPECT_NE(popupNodeTwo, nullptr);

    primaryProperties.showButton = true;
    secondProperties.showButton = false;
    popupParam->SetPrimaryButtonProperties(primaryProperties);
    popupParam->SetSecondaryButtonProperties(secondProperties);
    auto popupNodeThree = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    EXPECT_NE(popupNodeThree, nullptr);
}

/**
 * @tc.name: BubblePatternTest009
 * @tc.desc: Test CreateCustomBubbleNode and Update.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePatternTestNg, BubblePatternTest009, TestSize.Level1)
{
    // set value to popupParam
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

    // create customBubbleNode
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(targetNode, nullptr);
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_NE(rowFrameNode, nullptr);
    auto blankFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(blankFrameNode, nullptr);
    rowFrameNode->AddChild(blankFrameNode);
    auto popupNode =
        BubbleView::CreateCustomBubbleNode(targetNode->GetTag(), targetNode->GetId(), rowFrameNode, popupParam);
    EXPECT_NE(popupNode, nullptr);

    // update customBubbleNode
    auto popupId = popupNode->GetId();
    popupParam->SetPlacement(Placement::LEFT);
    popupParam->SetMessage(BUBBLE_NEW_MESSAGE);
    popupParam->SetHasAction(true);
    BubbleView::UpdatePopupParam(popupId, popupParam, targetNode);
}
} // namespace OHOS::Ace::NG