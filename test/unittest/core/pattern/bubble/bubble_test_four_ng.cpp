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
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/placement.h"
#include "core/components/popup/popup_theme.h"
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
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float ZERO = 0.0f;

constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float CONTAINER_WIDTH = 600.0f;
constexpr float CONTAINER_HEIGHT = 1000.0f;
constexpr float TARGET_WIDTH = 100.0f;
constexpr float TARGET_HEIGHT = 200.0f;
constexpr float TARGET_X = 100.0f;
constexpr float TARGET_Y = 150.0f;
constexpr int CHILD_SIZE_X = 1;
constexpr int CHILD_SIZE_Y = 2;
constexpr float FONT_MAX_SIZE_SCALE = 2.0f;
constexpr float FONT_SIZE_SCALE_TEST1 = 1.75f;
constexpr float FONT_SIZE_SCALE_TEST2 = 3.20f;
constexpr bool BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_TRUE = true;
constexpr bool BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_FALSE = false;
constexpr bool BUBBLE_PROPERTY_SHOW = true;
const OffsetF BUBBLE_POSITION_OFFSET = OffsetF(100.0f, 100.0f);
constexpr Dimension BUBBLE_CHILD_OFFSET = 8.0_vp;
constexpr Dimension DEFAULT_RADIUS = 20.0_px;
constexpr Dimension DEFAULT_ARROW_HEIGHT = 20.0_px;
constexpr Dimension DEFAULT_ARROW_WIDTH = 20.0_px;
const SafeAreaInsets::Inset KEYBOARD_INSET = { .start = 500.f, .end = 1000.f };

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
const std::string ARROW_PATH_EMPTY = "";
const std::vector<Placement> BUBBLE_LAYOUT_PROPERTY_PLACEMENTS = { Placement::LEFT, Placement::RIGHT, Placement::TOP,
    Placement::BOTTOM, Placement::TOP_LEFT, Placement::TOP_RIGHT, Placement::BOTTOM_LEFT, Placement::BOTTOM_RIGHT,
    Placement::LEFT_BOTTOM, Placement::LEFT_TOP, Placement::RIGHT_BOTTOM, Placement::RIGHT_TOP, Placement::NONE };
const Offset POPUP_PARAM_POSITION_OFFSET = Offset(100.0f, 100.0f);
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

class BubbleTestFourNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
protected:
    static RefPtr<FrameNode> CreateBubbleNode(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateTargetNode();
};

void BubbleTestFourNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void BubbleTestFourNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

PaddingProperty BubbleTestFourNg::CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

RefPtr<FrameNode> BubbleTestFourNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

RefPtr<FrameNode> BubbleTestFourNg::CreateBubbleNode(const TestProperty& testProperty)
{
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto layoutProperty = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto renderProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
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
 * @tc.name: BubbleAlgorithmTest006
 * @tc.desc: Test GetPositionWithPlacement
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, BubbleAlgorithmTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    bubbleLayoutAlgorithm->targetSecurity_ = 0;
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    /**
     * @tc.steps: step2. excute GetPositionWithPlacement
     * @tc.expected: step2. check whether the properties is correct.
     */
    for (auto placement : BUBBLE_LAYOUT_PROPERTY_PLACEMENTS) {
        OffsetF childPosition(ZERO, ZERO), arrowPosition(ZERO, ZERO);
        bubbleLayoutAlgorithm->GetPositionWithPlacement(childPosition, arrowPosition, childSize, placement);
        if (placement == Placement::NONE) {
            EXPECT_EQ(childPosition.GetY(), ZERO);
            EXPECT_EQ(childPosition.GetX(), ZERO);
        }
    }
}

/*
 * @tc.name: BubblePaintMethod004
 * @tc.desc: Test BubblePaintMethod PaintOuterBorder.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, BubblePaintMethod004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the BubblePaintMethod.
     */
    BubblePaintMethod bubblePaintMethod;
    Testing::MockCanvas canvas;

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
     * @tc.steps: step2. Call the function PaintOuterBorder and PaintInnerBorder.
     */
    auto theme = AceType::MakeRefPtr<PopupTheme>();
    bubblePaintMethod.GetInnerBorderOffset(theme);
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    bubblePaintMethod.PaintOuterBorder(canvas, paintWrapper);
    bubblePaintMethod.PaintInnerBorder(canvas, paintWrapper);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    bubblePaintMethod.PaintOuterBorder(canvas, paintWrapper);
    bubblePaintMethod.PaintInnerBorder(canvas, paintWrapper);
    /**
     * @tc.steps: step3. call SetArrowWidth.
     * @tc.expected: step3. Check the property.
     */
    float arrowWidth = 2.0;
    bubblePaintMethod.SetArrowWidth(arrowWidth);
    EXPECT_EQ(bubblePaintMethod.arrowWidth_, 2.0);
}

/*
 * @tc.name: BubblePaintMethod005
 * @tc.desc: Test BubblePaintMethod BuildDoubleBorderPath.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, BubblePaintMethod005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the BubblePaintMethod.
     */
    BubblePaintMethod bubblePaintMethod;
    Testing::TestingPath Path;
    /**
     * @tc.steps: step2. Call the function BuildDoubleBorderPath.
     */
    auto popupTheme = AceType::MakeRefPtr<PopupTheme>();
    ASSERT_NE(popupTheme, nullptr);
    bubblePaintMethod.needPaintOuterBorder_ = false;
    bubblePaintMethod.arrowPlacement_ = Placement::NONE;
    bubblePaintMethod.BuildDoubleBorderPath(Path, popupTheme);
    bubblePaintMethod.needPaintOuterBorder_ = true;
    bubblePaintMethod.arrowPlacement_ = Placement::BOTTOM;
    bubblePaintMethod.BuildDoubleBorderPath(Path, popupTheme);
    bubblePaintMethod.arrowPlacement_ = Placement::LEFT;
    bubblePaintMethod.BuildDoubleBorderPath(Path, popupTheme);
    bubblePaintMethod.arrowPlacement_ = Placement::RIGHT;
    bubblePaintMethod.BuildDoubleBorderPath(Path, popupTheme);
    bubblePaintMethod.arrowPlacement_ = Placement::TOP;
    bubblePaintMethod.BuildDoubleBorderPath(Path, popupTheme);
    /**
     * @tc.steps: step3. call SetShowArrow.
     * @tc.expected: step3. Check the property.
     */
    bubblePaintMethod.SetShowArrow(true);
    EXPECT_TRUE(bubblePaintMethod.showArrow_);
}

/**
 * @tc.name: BubblePatternTest017
 * @tc.desc: Test CreateCustomBubbleNode with with Offset, Radius, ArrowHeight, ArrowWidth and Shadow.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, BubblePatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    ASSERT_NE(frameNode, nullptr);
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    /**
     * @tc.steps: step2. call OnColorConfigurationUpdate.
     * @tc.expected: step2. Check the property is correct.
     */
    bubblePattern->isCustomPopup_ = true;
    bubblePattern->OnColorConfigurationUpdate();
    bubblePattern->isCustomPopup_ = false;
    bubblePattern->OnColorConfigurationUpdate();
    EXPECT_EQ(bubblePattern->colorMode_, ColorMode::LIGHT);
}

/**
 * @tc.name: BubblePatternTest018
 * @tc.desc: Test CreateCustomBubbleNode with with Offset, Radius, ArrowHeight, ArrowWidth and Shadow.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, BubblePatternTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get bubblePattern.
     */
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    ASSERT_NE(frameNode, nullptr);
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutProp = frameNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);

    /**
     * @tc.steps: step2. call OnWindowSizeChanged.
     * @tc.expected: step2. Check the property is correct.
     */
    bubblePattern->OnWindowSizeChanged(20, 10, WindowSizeChangeReason::RESIZE);
    layoutProp->UpdateShowInSubWindow(false);
    bubblePattern->OnWindowSizeChanged(20, 10, WindowSizeChangeReason::TRANSFORM);
    bubblePattern->OnWindowHide();
    EXPECT_FALSE(layoutProp->GetShowInSubWindow().value_or(false));
    layoutProp->UpdateShowInSubWindow(true);
    bubblePattern->OnWindowSizeChanged(20, 10, WindowSizeChangeReason::TRANSFORM);
    bubblePattern->OnWindowHide();
    EXPECT_TRUE(layoutProp->GetShowInSubWindow().value_or(false));
    layoutProp->UpdateShowInSubWindow(true);
    bubblePattern->OnWindowSizeChanged(20, 10, WindowSizeChangeReason::AVOID_AREA_CHANGE);
    bubblePattern->OnWindowHide();
    EXPECT_TRUE(layoutProp->GetShowInSubWindow().value_or(false));
}

/**
 * @tc.name: BubblePatternTest019
 * @tc.desc: Test bubble pattern InitTouchEvent HandleTouchEvent HandleTouchDOWN.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, BubblePatternTest019, TestSize.Level1)
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
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    RefPtr<GestureEventHub> gestureHub =
        AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    bubblePattern->InitTouchEvent();

    bubblePattern->SetInteractiveDismiss(false);
    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(100.0, 100.0));
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    bubblePattern->HandleTouchEvent(touchEventInfo);

    bubblePattern->touchRegion_ = RectF(0, 0, 200, 200);
    TouchEventInfo touchEventInfo1 = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo1 = TouchLocationInfo(1);
    touchLocationInfo1.SetLocalLocation(Offset(100.0, 100.0));
    touchLocationInfo1.SetTouchType(TouchType::DOWN);
    touchEventInfo1.AddTouchLocationInfo(std::move(touchLocationInfo1));
    bubblePattern->HandleTouchEvent(touchEventInfo1);

    bubblePaintProperty->UpdateAutoCancel(BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_TRUE);
}

/**
 * @tc.name: BubblePatternTest020
 * @tc.desc: Test bubble GetButtonRowNode.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, BubblePatternTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set value to popupParam.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
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
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
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
     * @tc.expected: after hover callback, isHover_ equal to true.
     */
    auto buttonRowNode = pattern->GetButtonRowNode();
}

/**
 * @tc.name: BubblePatternTest023
 * @tc.desc: Test bubble callback function
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, BubblePatternTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set value to popupParam.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
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
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. Register bubble state callback function，and call this function.
     * @tc.expected: Check callNum value
     */
    int32_t callNum = 0;
    std::function<void(const std::string&)> callback = [&](const std::string& param) { callNum++; };
    pattern->RegisterDoubleBindCallback(callback);
    pattern->CallDoubleBindCallback("false");
    EXPECT_EQ(callNum, 1);
}

/**
 * @tc.name: BubblePatternTest024
 * @tc.desc: Test bubble callback function
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, BubblePatternTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set value to popupParam.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
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
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. Update bubble param.
     * @tc.expected: Check callNum value
     */
    popupParam->SetMessage(BUBBLE_NEW_MESSAGE);
    ButtonProperties buttonProperties0 { true, "Button0" };
    ButtonProperties buttonProperties1 { true, "Button1" };
    popupParam->SetPrimaryButtonProperties(buttonProperties0);
    popupParam->SetSecondaryButtonProperties(buttonProperties1);
    auto popupId = popupNode->GetId();
    BubbleView::UpdatePopupParam(popupId, popupParam, targetNode);
    auto columnNode = popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);
    auto combinedChild = columnNode->GetFirstChild();
    ASSERT_NE(combinedChild, nullptr);
    auto scrollNode = combinedChild->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(scrollNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetContent().value(), u"Good");
}

/**
 * @tc.name: BubbleAlgorithmTest007
 * @tc.desc: Test bubble ClipBubbleWithPath.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, BubbleAlgorithmTest007, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and create layoutAlgorithm.
     */
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step3. test GetArrowBuildPlacement ClipBubbleWithPath
     */
    Placement arrowBuildPlacement = Placement::NONE;

    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM;
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::TOP_RIGHT);
    auto path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");

    layoutAlgorithm->arrowPlacement_ = Placement::TOP;
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::BOTTOM);
    path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");

    layoutAlgorithm->arrowPlacement_ = Placement::LEFT;
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::RIGHT);
    path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");

    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT;
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::LEFT);
    path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");
}

/**
 * @tc.name: BubbleAlgorithmTest008
 * @tc.desc: Test bubble UpdateChildPosition.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, BubbleAlgorithmTest008, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);

    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. test UpdateChildPosition.
     */
    layoutAlgorithm->enableArrow_ = false;
    OffsetF offset = OffsetF(0, 0);
    layoutAlgorithm->placement_ = Placement::TOP;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetY(), BUBBLE_CHILD_OFFSET.ConvertToPx());

    offset = OffsetF(0, 0);
    layoutAlgorithm->placement_ = Placement::BOTTOM;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetY(), -BUBBLE_CHILD_OFFSET.ConvertToPx());

    offset = OffsetF(0, 0);
    layoutAlgorithm->placement_ = Placement::LEFT;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetX(), BUBBLE_CHILD_OFFSET.ConvertToPx());

    offset = OffsetF(0, 0);
    layoutAlgorithm->placement_ = Placement::RIGHT;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetX(), -BUBBLE_CHILD_OFFSET.ConvertToPx());

    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(layoutAlgorithm->showArrow_, false);
    layoutAlgorithm->enableArrow_ = false;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(layoutAlgorithm->showArrow_, false);
}

/**
 * @tc.name: BubbleAccessibilityTest001
 * @tc.desc: Test BubblePattern::CreateAccessibilityProperty function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, BubbleAccessibilityTest001, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. get BubbleAccessibilityProperty.
     * @tc.expected: step2. BubbleAccessibilityProperty is not nullptr.
     */
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<BubbleAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
}

/**
 * @tc.name: BubbleAccessibilityTest002
 * @tc.desc: Test BubbleAccessibilityProperty::SetShowedState function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, BubbleAccessibilityTest002, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. BubbleAccessibilityProperty is not nullptr.
     */
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<BubbleAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step3. set showedState 0.
     * @tc.expected: step3 get showedState 0.
     */
    accessibilityProperty->SetShowedState(0);
    auto showedState = accessibilityProperty->GetShowedState();
    EXPECT_EQ(showedState, 0);

    /**
     * @tc.steps: step4. set showedState 1.
     * @tc.expected: step4 get showedState 1.
     */
    accessibilityProperty->SetShowedState(1);
    showedState = accessibilityProperty->GetShowedState();
    EXPECT_EQ(showedState, 1);
}

/**
 * @tc.name: HandleKeyboardTest
 * @tc.desc: Test HandleKeyboard function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, HandleKeyboardTest, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);

    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test HandleKeyboard.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    manager->keyboardInset_ = KEYBOARD_INSET;
    layoutAlgorithm->wrapperSize_ = {1000.0f, 1000.0f};
    bool isShowInSubwindow = false;
    layoutAlgorithm->avoidKeyboard_ = true;
    layoutAlgorithm->HandleKeyboard(AceType::RawPtr(layoutWrapper), isShowInSubwindow);
    EXPECT_EQ(layoutAlgorithm->wrapperSize_.Height(), 1000.0f);
    layoutAlgorithm->wrapperSize_ = {1000.0f, 1000.0f};
    isShowInSubwindow = true;
    layoutAlgorithm->HandleKeyboard(AceType::RawPtr(layoutWrapper), isShowInSubwindow);
    EXPECT_EQ(layoutAlgorithm->wrapperSize_.Height(), 1000.0f);
}

/**
 * @tc.name: AdjustPositionNewTest
 * @tc.desc: Test AdjustPositionNew function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, AdjustPositionNewTest, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);

    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test AdjustPositionNew.
     */
    layoutAlgorithm->wrapperSize_ = {1000.0f, 1000.0f};
    OffsetF position = {10.0f, 10.0f};
    float height = 200.0f;
    float width = 200.0f;
    auto result = layoutAlgorithm->AdjustPositionNew(position, height, width);
    EXPECT_EQ(result, position);
    position = {1000.0f, 1000.0f};
    result = layoutAlgorithm->AdjustPositionNew(position, height, width);
    EXPECT_EQ(result, OffsetF(800.0f, 800.0f));
    position = {200.0f, 1000.0f};
    result = layoutAlgorithm->AdjustPositionNew(position, height, width);
    EXPECT_EQ(result, OffsetF(200.0f, 800.0f));
    position = {1000.0f, 200.0f};
    result = layoutAlgorithm->AdjustPositionNew(position, height, width);
    EXPECT_EQ(result, OffsetF(800.0f, 200.0f));
}

/**
 * @tc.name: GetBubblePositionTest
 * @tc.desc: Test GetBubblePosition function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, GetBubblePositionTest, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);

    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test GetBubblePosition.
     */
    layoutAlgorithm->placement_ = Placement::LEFT;
    float xMin = 200.0f;
    float xMax = 1000.0f;
    float yMin = 200.0f;
    float yMax = 1000.0f;
    OffsetF position = {10.0f, 10.0f};
    layoutAlgorithm->showArrow_ = true;
    auto result = layoutAlgorithm->GetBubblePosition(position, xMin, xMax, yMin, yMax);
    EXPECT_EQ(layoutAlgorithm->showArrow_, true);
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->avoidKeyboard_ = true;
    result = layoutAlgorithm->GetBubblePosition(position, xMin, xMax, yMin, yMax);
    EXPECT_EQ(layoutAlgorithm->showArrow_, false);
}

/**
 * @tc.name: CheckArrowPositionTest
 * @tc.desc: Test CheckArrowPosition function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, CheckArrowPositionTest, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);

    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test CheckArrowPosition.
     */
    layoutAlgorithm->placement_ = Placement::LEFT;
    float xMin = 200.0f;
    float xMax = 1000.0f;
    float yMin = 200.0f;
    float yMax = 1000.0f;
    OffsetF position = {10.0f, 10.0f};
    layoutAlgorithm->showArrow_ = true;
    auto result = layoutAlgorithm->GetBubblePosition(position, xMin, xMax, yMin, yMax);
    EXPECT_EQ(layoutAlgorithm->showArrow_, true);
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->avoidKeyboard_ = true;
    result = layoutAlgorithm->GetBubblePosition(position, xMin, xMax, yMin, yMax);
    EXPECT_EQ(layoutAlgorithm->showArrow_, false);
}

/**
 * @tc.name: UpdateBubbleText
 * @tc.desc: Test UpdateBubbleText function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, UpdateBubbleText, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set value to popupParam.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetFollowSystem(true);
    pipeline->SetMaxAppFontScale(FONT_SIZE_SCALE_TEST1);
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
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
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. test UpdateBubbleText.
     */
    pattern->UpdateBubbleText();
    auto columnNode = popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);
    auto combinedChild = columnNode->GetFirstChild();
    ASSERT_NE(combinedChild, nullptr);
    auto scrollNode = combinedChild->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(scrollNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto popupTheme = pattern->GetPopupTheme();
    auto color = popupTheme->GetFontPrimaryColor();
    EXPECT_EQ(layoutProperty->GetTextColor().value(), color);
    EXPECT_EQ(layoutProperty->GetMaxFontScale().value(), FONT_SIZE_SCALE_TEST1);
}

/**
 * @tc.name: UpdateBubbleText01
 * @tc.desc: Test UpdateBubbleText function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, UpdateBubbleText01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set value to popupParam.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetFollowSystem(true);
    pipeline->SetMaxAppFontScale(FONT_SIZE_SCALE_TEST2);
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
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. test UpdateBubbleText.
     */
    pattern->UpdateBubbleText();
    auto columnNode = popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);
    auto combinedChild = columnNode->GetFirstChild();
    ASSERT_NE(combinedChild, nullptr);
    auto scrollNode = combinedChild->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(scrollNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetMaxFontScale().value(), FONT_MAX_SIZE_SCALE);
}

/**
 * @tc.name: HandleUIExtensionKeyboard
 * @tc.desc: Test HandleUIExtensionKeyboard function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, HandleUIExtensionKeyboard, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);

    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test HandleUIExtensionKeyboard.
     */
    layoutAlgorithm->showArrow_ = false;
    bool showInSubwindow = true;
    layoutAlgorithm->avoidKeyboard_ = true;
    layoutAlgorithm->HandleUIExtensionKeyboard(AceType::RawPtr(layoutWrapper), showInSubwindow);
    showInSubwindow = true;
    layoutAlgorithm->avoidKeyboard_ = false;
    layoutAlgorithm->HandleUIExtensionKeyboard(AceType::RawPtr(layoutWrapper), showInSubwindow);
    showInSubwindow = false;
    layoutAlgorithm->avoidKeyboard_ = true;
    layoutAlgorithm->HandleUIExtensionKeyboard(AceType::RawPtr(layoutWrapper), showInSubwindow);
    showInSubwindow = false;
    layoutAlgorithm->avoidKeyboard_ = false;
    layoutAlgorithm->HandleUIExtensionKeyboard(AceType::RawPtr(layoutWrapper), showInSubwindow);
    EXPECT_EQ(layoutAlgorithm->showArrow_, false);
}

/**
 * @tc.name: CheckIfNeedRemoveArrow
 * @tc.desc: Test CheckIfNeedRemoveArrow function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, CheckIfNeedRemoveArrow, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);

    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test CheckIfNeedRemoveArrow.
     */
    float xMin = 0.0;
    float xMax = 100.0;
    float yMin = 0.0;
    float yMax = 100.0;
    Dimension BUBBLE_ARROW_HEIGHT = 8.0_vp;
    layoutAlgorithm->arrowHeight_ = BUBBLE_ARROW_HEIGHT.ConvertToPx();

    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->avoidKeyboard_ = true;
    layoutAlgorithm->placement_ = Placement::TOP;
    yMin = yMax + layoutAlgorithm->arrowHeight_ - 1.0;
    auto result = layoutAlgorithm->CheckIfNeedRemoveArrow(xMin, xMax, yMin, yMax);
    EXPECT_EQ(result, true);

    layoutAlgorithm->showArrow_ = true;
    yMin = yMax + layoutAlgorithm->arrowHeight_ + 1.0;
    result = layoutAlgorithm->CheckIfNeedRemoveArrow(xMin, xMax, yMin, yMax);
    EXPECT_EQ(result, false);

    layoutAlgorithm->placement_ = Placement::LEFT;
    yMin = 0;
    layoutAlgorithm->showArrow_ = true;
    xMin = xMax + layoutAlgorithm->arrowHeight_ - 1.0;
    result = layoutAlgorithm->CheckIfNeedRemoveArrow(xMin, xMax, yMin, yMax);
    EXPECT_EQ(result, true);

    layoutAlgorithm->showArrow_ = true;
    xMin = xMax + layoutAlgorithm->arrowHeight_ + 1.0;
    result = layoutAlgorithm->CheckIfNeedRemoveArrow(xMin, xMax, yMin, yMax);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: UpdateScrollHeight
 * @tc.desc: Test UpdateScrollHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, UpdateScrollHeight, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
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
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);

    auto bubblePattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(popupNode, geometryNode, popupNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test UpdateScrollHeight.
     */
    auto property = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateEnableHoverMode(true);
    bool showInSubwindow = true;
    layoutAlgorithm->UpdateScrollHeight(AceType::RawPtr(layoutWrapper), showInSubwindow);
    showInSubwindow = false;
    layoutAlgorithm->UpdateScrollHeight(AceType::RawPtr(layoutWrapper), showInSubwindow);
    EXPECT_EQ(property->GetEnableHoverModeValue(false), true);
}

/**
 * @tc.name: CheckArrowPosition1
 * @tc.desc: Test CheckArrowPosition1 function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, CheckArrowPosition1, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);

    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test CheckArrowPosition1.
     */
    
    std::vector<Placement> curPlaceStates = { Placement::LEFT, Placement::RIGHT, Placement::TOP,
        Placement::BOTTOM, Placement::NONE };

    for (auto &placement : curPlaceStates) {
        OffsetF position = {0.0f, 0.0f};
        layoutAlgorithm->showArrow_ = true;
        layoutAlgorithm->avoidKeyboard_ = true;
        layoutAlgorithm->placement_ = placement;
        layoutAlgorithm->CheckArrowPosition(position, 10.0f, 10.0f);
    }
    EXPECT_EQ(layoutAlgorithm->avoidKeyboard_, true);
}

/**
 * @tc.name: IsUIExtensionWindow
 * @tc.desc: Test IsUIExtensionWindow function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, IsUIExtensionWindow, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);

    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test IsUIExtensionWindow.
     */

    EXPECT_EQ(layoutAlgorithm->IsUIExtensionWindow(), false);
}

/**
 * @tc.name: InitWrapperRect
 * @tc.desc: Test InitWrapperRect function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, InitWrapperRect, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
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
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);

    auto bubblePattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(popupNode, geometryNode, popupNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test InitWrapperRect.
     */
    auto property = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateEnableHoverMode(true);
    layoutAlgorithm->isHalfFoldHover_ = true;
    layoutAlgorithm->InitWrapperRect(AceType::RawPtr(layoutWrapper), property);
    EXPECT_EQ(property->GetEnableHoverModeValue(false), true);
}

/**
 * @tc.name: CreateBubbleNode001
 * @tc.desc: Test CreateBubbleNode with istips Offset, Radius, ArrowHeight, ArrowWidth and Shadow.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, CreateBubbleNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set popup value to popupParam.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetTargetOffset(POPUP_PARAM_POSITION_OFFSET);

    Shadow shadow = ShadowConfig::DefaultShadowL;
    popupParam->SetRadius(DEFAULT_RADIUS);
    popupParam->SetTipsFlag(true);
    popupParam->SetArrowHeight(DEFAULT_ARROW_HEIGHT);
    popupParam->SetArrowWidth(DEFAULT_ARROW_WIDTH);
    popupParam->SetShadow(shadow);
    popupParam->SetAnchorType(TipsAnchorType::CURSOR);

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
    EXPECT_EQ(property->GetRadius().value(), DEFAULT_RADIUS);
    EXPECT_EQ(property->GetArrowHeight().value(), DEFAULT_ARROW_HEIGHT);
    EXPECT_EQ(property->GetArrowWidth().value(), DEFAULT_ARROW_WIDTH);
    EXPECT_EQ(property->GetShowAtAnchor().value(), TipsAnchorType::CURSOR);
}

/**
 * @tc.name: FitAvailableRect001
 * @tc.desc: Test CreateBubbleNode with istips Offset, Radius, ArrowHeight, ArrowWidth and Shadow.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, FitAvailableRect001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(bubbleLayoutProperty, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto pipelineContext = frameNode->GetContextRefPtr();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->UpdateDisplayAvailableRect(Rect(0.0f, 0.0f, 0.0f, 0.0f));
    layoutAlgorithm->FitAvailableRect(AceType::RawPtr(layoutWrapper), false);
    layoutAlgorithm->FitAvailableRect(AceType::RawPtr(layoutWrapper), true);
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(0.0f, 0.0f));
}
} // namespace OHOS::Ace::NG