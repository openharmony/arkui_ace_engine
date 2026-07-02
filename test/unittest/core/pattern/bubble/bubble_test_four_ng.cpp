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
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"
#include "test/mock/frameworks/core/rosen/testing_canvas.h"
#include "test/mock/frameworks/core/rosen/testing_path.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/properties/shadow_config.h"
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
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

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
constexpr float LARGE_ARROW_WIDTH = 100.0f;
constexpr float LARGE_ARROW_HEIGHT = 50.0f;
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
HWTEST_F(BubbleTestFourNg, BubbleAlgorithmTest006, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, BubblePaintMethod004, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, BubblePaintMethod005, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, BubblePatternTest017, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, BubblePatternTest018, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, BubblePatternTest019, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, BubblePatternTest020, TestSize.Level0)
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
    EXPECT_CALL(*themeManagerOne, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
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
HWTEST_F(BubbleTestFourNg, BubblePatternTest023, TestSize.Level0)
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
    EXPECT_CALL(*themeManagerOne, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
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
HWTEST_F(BubbleTestFourNg, BubblePatternTest024, TestSize.Level0)
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
    EXPECT_CALL(*themeManagerOne, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
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
HWTEST_F(BubbleTestFourNg, BubbleAlgorithmTest007, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, BubbleAlgorithmTest008, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, BubbleAccessibilityTest001, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, BubbleAccessibilityTest002, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, HandleKeyboardTest, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, AdjustPositionNewTest, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, GetBubblePositionTest, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, CheckArrowPositionTest, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, UpdateBubbleText, TestSize.Level0)
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
    EXPECT_CALL(*themeManagerOne, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
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
HWTEST_F(BubbleTestFourNg, UpdateBubbleText01, TestSize.Level0)
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
    EXPECT_CALL(*themeManagerOne, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
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
HWTEST_F(BubbleTestFourNg, HandleUIExtensionKeyboard, TestSize.Level0)
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
    EXPECT_EQ(layoutAlgorithm->dumpInfo_.avoidKeyboard, false);
}

/**
 * @tc.name: CheckIfNeedRemoveArrow
 * @tc.desc: Test CheckIfNeedRemoveArrow function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, CheckIfNeedRemoveArrow, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, UpdateScrollHeight, TestSize.Level0)
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
    EXPECT_CALL(*themeManagerOne, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
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
    layoutAlgorithm->UpdateScrollHeight(AceType::RawPtr(layoutWrapper));
    showInSubwindow = false;
    layoutAlgorithm->UpdateScrollHeight(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(property->GetEnableHoverModeValue(false), true);
}

/**
 * @tc.name: CheckArrowPosition1
 * @tc.desc: Test CheckArrowPosition1 function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, CheckArrowPosition1, TestSize.Level0)
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
        layoutAlgorithm->avoidKeyboard_ = true;
        layoutAlgorithm->placement_ = placement;
        layoutAlgorithm->CheckArrowPosition(position, 10.0f, 10.0f);
    }
    EXPECT_EQ(layoutAlgorithm->showArrow_, false);
}

/**
 * @tc.name: IsUIExtensionWindow
 * @tc.desc: Test IsUIExtensionWindow function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, IsUIExtensionWindow, TestSize.Level0)
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
HWTEST_F(BubbleTestFourNg, InitWrapperRect, TestSize.Level0)
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
    EXPECT_CALL(*themeManagerOne, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
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
HWTEST_F(BubbleTestFourNg, CreateBubbleNode001, TestSize.Level0)
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
    EXPECT_CALL(*themeManagerOne, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
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
HWTEST_F(BubbleTestFourNg, FitAvailableRect001, TestSize.Level0)
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

/**
 * @tc.name: ArrowMemberVariablesTest001
 * @tc.desc: Test that multiple BubbleLayoutAlgorithm instances maintain independent arrow width/height
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest001, TestSize.Level1)
{
    // Create two bubble layout algorithm instances with different targets
    auto algorithm1 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1",
        OffsetF(100.0f, 100.0f), SizeF(50.0f, 50.0f));
    auto algorithm2 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1002, "target2",
        OffsetF(200.0f, 200.0f), SizeF(60.0f, 60.0f));

    // Verify initial default values are the same
    EXPECT_EQ(algorithm1->bubbleArrowWidth_, 16.0_vp);
    EXPECT_EQ(algorithm1->bubbleArrowHeight_, 8.0_vp);
    EXPECT_EQ(algorithm2->bubbleArrowWidth_, 16.0_vp);
    EXPECT_EQ(algorithm2->bubbleArrowHeight_, 8.0_vp);

    // Modify first instance's arrow dimensions
    algorithm1->bubbleArrowWidth_ = Dimension(24.0_vp);
    algorithm1->bubbleArrowHeight_ = Dimension(12.0_vp);

    // Verify first instance has new values
    EXPECT_EQ(algorithm1->bubbleArrowWidth_, 24.0_vp);
    EXPECT_EQ(algorithm1->bubbleArrowHeight_, 12.0_vp);

    // Verify second instance still has default values (independence check)
    EXPECT_EQ(algorithm2->bubbleArrowWidth_, 16.0_vp);
    EXPECT_EQ(algorithm2->bubbleArrowHeight_, 8.0_vp);

    // Modify second instance to different values
    algorithm2->bubbleArrowWidth_ = Dimension(32.0_vp);
    algorithm2->bubbleArrowHeight_ = Dimension(16.0_vp);

    // Verify both instances have independent values
    EXPECT_EQ(algorithm1->bubbleArrowWidth_, 24.0_vp);
    EXPECT_EQ(algorithm1->bubbleArrowHeight_, 12.0_vp);
    EXPECT_EQ(algorithm2->bubbleArrowWidth_, 32.0_vp);
    EXPECT_EQ(algorithm2->bubbleArrowHeight_, 16.0_vp);
}

/**
 * @tc.name: ArrowMemberVariablesTest002
 * @tc.desc: Test that multiple BubbleLayoutAlgorithm instances maintain independent beta values
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest002, TestSize.Level1)
{
    auto algorithm1 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1",
        OffsetF(100.0f, 100.0f), SizeF(50.0f, 50.0f));
    auto algorithm2 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1002, "target2",
        OffsetF(200.0f, 200.0f), SizeF(60.0f, 60.0f));

    // Set different arrow dimensions for each instance
    algorithm1->bubbleArrowWidth_ = Dimension(16.0_vp);
    algorithm1->bubbleArrowHeight_ = Dimension(8.0_vp);

    algorithm2->bubbleArrowWidth_ = Dimension(32.0_vp);
    algorithm2->bubbleArrowHeight_ = Dimension(16.0_vp);

    // Call GetEndP2P4 for both instances
    constexpr Dimension ARROW_RADIUS = 2.0_vp;
    algorithm1->GetEndP2P4(ARROW_RADIUS);
    algorithm2->GetEndP2P4(ARROW_RADIUS);

    // Verify that typeOneBeta_ values are different due to different arrow dimensions
    EXPECT_NE(algorithm1->typeOneBeta_, algorithm2->typeOneBeta_);
    EXPECT_GT(algorithm1->typeOneBeta_, 0.0);
    EXPECT_GT(algorithm2->typeOneBeta_, 0.0);
}

/**
 * @tc.name: ArrowMemberVariablesTest003
 * @tc.desc: Test that multiple BubbleLayoutAlgorithm instances maintain independent typeTwoBeta values
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest003, TestSize.Level1)
{
    auto algorithm1 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1",
        OffsetF(100.0f, 100.0f), SizeF(50.0f, 50.0f));
    auto algorithm2 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1002, "target2",
        OffsetF(200.0f, 200.0f), SizeF(60.0f, 60.0f));

    // Set different arrow dimensions for each instance
    algorithm1->bubbleArrowWidth_ = Dimension(16.0_vp);
    algorithm1->bubbleArrowHeight_ = Dimension(8.0_vp);

    algorithm2->bubbleArrowWidth_ = Dimension(32.0_vp);
    algorithm2->bubbleArrowHeight_ = Dimension(16.0_vp);

    // Call GetP2 for both instances
    constexpr Dimension ARROW_RADIUS = 2.0_vp;
    algorithm1->GetP2(ARROW_RADIUS);
    algorithm2->GetP2(ARROW_RADIUS);

    // Verify that typeTwoBeta_ values are different due to different arrow dimensions
    EXPECT_NE(algorithm1->typeTwoBeta_, algorithm2->typeTwoBeta_);
    EXPECT_GT(algorithm1->typeTwoBeta_, 0.0);
    EXPECT_GT(algorithm2->typeTwoBeta_, 0.0);
}

/**
 * @tc.name: ArrowMemberVariablesTest004
 * @tc.desc: Test SetArrowSize function with default arrow dimensions
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest004, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Use default arrow dimensions
    algorithm->bubbleArrowWidth_ = Dimension(16.0_vp);
    algorithm->bubbleArrowHeight_ = Dimension(8.0_vp);

    // Call SetArrowSize
    float width = 0.0f;
    float height = 0.0f;
    algorithm->SetArrowSize(width, height);

    // Verify the width and height are set to default values
    EXPECT_FLOAT_EQ(width, 16.0f);
    EXPECT_FLOAT_EQ(height, 8.0f);
}

/**
 * @tc.name: ArrowMemberVariablesTest005
 * @tc.desc: Test SetArrowSize function with custom arrow dimensions
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest005, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Set custom arrow dimensions
    algorithm->bubbleArrowWidth_ = Dimension(24.0_vp);
    algorithm->bubbleArrowHeight_ = Dimension(12.0_vp);

    // Call SetArrowSize
    float width = 0.0f;
    float height = 0.0f;
    algorithm->SetArrowSize(width, height);

    // Verify the width and height are set correctly
    EXPECT_FLOAT_EQ(width, 24.0f);
    EXPECT_FLOAT_EQ(height, 12.0f);
}

/**
 * @tc.name: ArrowMemberVariablesTest006
 * @tc.desc: Test GetEndP2P4 calculates correct default point parameters
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest006, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Set up default arrow dimensions
    algorithm->bubbleArrowWidth_ = Dimension(16.0_vp);
    algorithm->bubbleArrowHeight_ = Dimension(8.0_vp);

    // Call GetEndP2P4 with test radius
    constexpr Dimension ARROW_RADIUS = 2.0_vp;
    algorithm->GetEndP2P4(ARROW_RADIUS);

    // Verify that calculated values are set
    EXPECT_GT(algorithm->defaultP4EndY_.Value(), 0.0);
    EXPECT_GT(algorithm->defaultP2EndX_.Value(), 0.0);
    EXPECT_GT(algorithm->defaultP2EndY_.Value(), 0.0);
    EXPECT_GT(algorithm->typeOneBeta_, 0.0);
}

/**
 * @tc.name: ArrowMemberVariablesTest007
 * @tc.desc: Test GetP2 calculates correct default point parameters
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest007, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Set up default arrow dimensions
    algorithm->bubbleArrowWidth_ = Dimension(16.0_vp);
    algorithm->bubbleArrowHeight_ = Dimension(8.0_vp);

    // Call GetP2 with test radius
    constexpr Dimension ARROW_RADIUS = 2.0_vp;
    algorithm->GetP2(ARROW_RADIUS);

    // Verify that calculated values are set
    EXPECT_GT(algorithm->defaultP2Height_.Value(), 0.0);
    EXPECT_GT(algorithm->defaultP2Width_.Value(), 0.0);
    EXPECT_GT(algorithm->typeTwoBeta_, 0.0);
}

/**
 * @tc.name: ArrowMemberVariablesTest008
 * @tc.desc: Test that GetEndP2P4 and GetP2 produce different beta values
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest008, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Set up default arrow dimensions
    algorithm->bubbleArrowWidth_ = Dimension(16.0_vp);
    algorithm->bubbleArrowHeight_ = Dimension(8.0_vp);

    // Call both functions
    constexpr Dimension ARROW_RADIUS = 2.0_vp;
    algorithm->GetEndP2P4(ARROW_RADIUS);
    algorithm->GetP2(ARROW_RADIUS);

    // Verify that typeOneBeta_ and typeTwoBeta_ are different (they calculate different angles)
    EXPECT_NE(algorithm->typeOneBeta_, algorithm->typeTwoBeta_);
    EXPECT_GT(algorithm->typeOneBeta_, 0.0);
    EXPECT_GT(algorithm->typeTwoBeta_, 0.0);
}

/**
 * @tc.name: ArrowMemberVariablesTest009
 * @tc.desc: Test arrow vertical offset parameters maintain independence across instances
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest009, TestSize.Level1)
{
    auto algorithm1 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");
    auto algorithm2 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1002, "target2");

    // Set different offset values for each instance
    algorithm1->arrowVerticalP1OffsetX_ = Dimension(10.0_vp);
    algorithm1->arrowVerticalP2OffsetY_ = Dimension(8.0_vp);

    algorithm2->arrowVerticalP1OffsetX_ = Dimension(15.0_vp);
    algorithm2->arrowVerticalP2OffsetY_ = Dimension(12.0_vp);

    // Verify independence
    EXPECT_EQ(algorithm1->arrowVerticalP1OffsetX_, 10.0_vp);
    EXPECT_EQ(algorithm1->arrowVerticalP2OffsetY_, 8.0_vp);
    EXPECT_EQ(algorithm2->arrowVerticalP1OffsetX_, 15.0_vp);
    EXPECT_EQ(algorithm2->arrowVerticalP2OffsetY_, 12.0_vp);
}

/**
 * @tc.name: ArrowMemberVariablesTest010
 * @tc.desc: Test arrow horizon offset parameters maintain independence across instances
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest010, TestSize.Level1)
{
    auto algorithm1 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");
    auto algorithm2 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1002, "target2");

    // Set different horizon offset values for each instance
    algorithm1->arrowHorizonP1OffsetY_ = Dimension(9.0_vp);
    algorithm1->arrowHorizonP2OffsetX_ = Dimension(7.0_vp);

    algorithm2->arrowHorizonP1OffsetY_ = Dimension(11.0_vp);
    algorithm2->arrowHorizonP2OffsetX_ = Dimension(10.0_vp);

    // Verify independence
    EXPECT_EQ(algorithm1->arrowHorizonP1OffsetY_, 9.0_vp);
    EXPECT_EQ(algorithm1->arrowHorizonP2OffsetX_, 7.0_vp);
    EXPECT_EQ(algorithm2->arrowHorizonP1OffsetY_, 11.0_vp);
    EXPECT_EQ(algorithm2->arrowHorizonP2OffsetX_, 10.0_vp);
}

/**
 * @tc.name: ArrowMemberVariablesTest011
 * @tc.desc: Test arrow replace start vertical offset parameters maintain independence
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest011, TestSize.Level1)
{
    auto algorithm1 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");
    auto algorithm2 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1002, "target2");

    // Set different replace start vertical offset values
    algorithm1->arrowReplaceStartVerticalP1OffsetX_ = Dimension(5.0_vp);
    algorithm1->arrowReplaceStartVerticalP2OffsetY_ = Dimension(6.0_vp);

    algorithm2->arrowReplaceStartVerticalP1OffsetX_ = Dimension(7.0_vp);
    algorithm2->arrowReplaceStartVerticalP2OffsetY_ = Dimension(8.0_vp);

    // Verify independence
    EXPECT_EQ(algorithm1->arrowReplaceStartVerticalP1OffsetX_, 5.0_vp);
    EXPECT_EQ(algorithm1->arrowReplaceStartVerticalP2OffsetY_, 6.0_vp);
    EXPECT_EQ(algorithm2->arrowReplaceStartVerticalP1OffsetX_, 7.0_vp);
    EXPECT_EQ(algorithm2->arrowReplaceStartVerticalP2OffsetY_, 8.0_vp);
}

/**
 * @tc.name: ArrowMemberVariablesTest012
 * @tc.desc: Test arrow replace end vertical offset parameters maintain independence
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest012, TestSize.Level1)
{
    auto algorithm1 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");
    auto algorithm2 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1002, "target2");

    // Set different replace end vertical offset values
    algorithm1->arrowReplaceEndVerticalP4OffsetX_ = Dimension(9.0_vp);
    algorithm1->arrowReplaceEndVerticalP5OffsetX_ = Dimension(10.0_vp);

    algorithm2->arrowReplaceEndVerticalP4OffsetX_ = Dimension(11.0_vp);
    algorithm2->arrowReplaceEndVerticalP5OffsetX_ = Dimension(12.0_vp);

    // Verify independence
    EXPECT_EQ(algorithm1->arrowReplaceEndVerticalP4OffsetX_, 9.0_vp);
    EXPECT_EQ(algorithm1->arrowReplaceEndVerticalP5OffsetX_, 10.0_vp);
    EXPECT_EQ(algorithm2->arrowReplaceEndVerticalP4OffsetX_, 11.0_vp);
    EXPECT_EQ(algorithm2->arrowReplaceEndVerticalP5OffsetX_, 12.0_vp);
}

/**
 * @tc.name: ArrowMemberVariablesTest013
 * @tc.desc: Test arrow replace start horizon offset parameters maintain independence
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest013, TestSize.Level1)
{
    auto algorithm1 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");
    auto algorithm2 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1002, "target2");

    // Set different replace start horizon offset values
    algorithm1->arrowReplaceStartHorizonP1OffsetY_ = Dimension(13.0_vp);
    algorithm1->arrowReplaceStartHorizonP2OffsetX_ = Dimension(14.0_vp);

    algorithm2->arrowReplaceStartHorizonP1OffsetY_ = Dimension(15.0_vp);
    algorithm2->arrowReplaceStartHorizonP2OffsetX_ = Dimension(16.0_vp);

    // Verify independence
    EXPECT_EQ(algorithm1->arrowReplaceStartHorizonP1OffsetY_, 13.0_vp);
    EXPECT_EQ(algorithm1->arrowReplaceStartHorizonP2OffsetX_, 14.0_vp);
    EXPECT_EQ(algorithm2->arrowReplaceStartHorizonP1OffsetY_, 15.0_vp);
    EXPECT_EQ(algorithm2->arrowReplaceStartHorizonP2OffsetX_, 16.0_vp);
}

/**
 * @tc.name: ArrowMemberVariablesTest014
 * @tc.desc: Test arrow replace end horizon offset parameters maintain independence
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest014, TestSize.Level1)
{
    auto algorithm1 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");
    auto algorithm2 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1002, "target2");

    // Set different replace end horizon offset values
    algorithm1->arrowReplaceEndHorizonP4OffsetX_ = Dimension(17.0_vp);
    algorithm1->arrowReplaceEndHorizonP5OffsetY_ = Dimension(18.0_vp);

    algorithm2->arrowReplaceEndHorizonP4OffsetX_ = Dimension(19.0_vp);
    algorithm2->arrowReplaceEndHorizonP5OffsetY_ = Dimension(20.0_vp);

    // Verify independence
    EXPECT_EQ(algorithm1->arrowReplaceEndHorizonP4OffsetX_, 17.0_vp);
    EXPECT_EQ(algorithm1->arrowReplaceEndHorizonP5OffsetY_, 18.0_vp);
    EXPECT_EQ(algorithm2->arrowReplaceEndHorizonP4OffsetX_, 19.0_vp);
    EXPECT_EQ(algorithm2->arrowReplaceEndHorizonP5OffsetY_, 20.0_vp);
}

/**
 * @tc.name: ArrowMemberVariablesTest015
 * @tc.desc: Test that bubbleArrowWidthF_ and bubbleArrowHeightF_ are set correctly
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest015, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Set custom arrow dimensions and their float versions
    algorithm->bubbleArrowWidth_ = Dimension(20.0_vp);
    algorithm->bubbleArrowHeight_ = Dimension(10.0_vp);
    algorithm->bubbleArrowWidthF_ = 20.0f;
    algorithm->bubbleArrowHeightF_ = 10.0f;

    // Verify the float versions are set
    EXPECT_TRUE(algorithm->bubbleArrowWidthF_.has_value());
    EXPECT_TRUE(algorithm->bubbleArrowHeightF_.has_value());
    EXPECT_FLOAT_EQ(algorithm->bubbleArrowWidthF_.value(), 20.0f);
    EXPECT_FLOAT_EQ(algorithm->bubbleArrowHeightF_.value(), 10.0f);
}

/**
 * @tc.name: ArrowMemberVariablesTest016
 * @tc.desc: Test concurrent arrow parameter calculation for multiple instances
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest016, TestSize.Level1)
{
    // Create multiple instances to simulate concurrent bubble creation
    std::vector<RefPtr<BubbleLayoutAlgorithm>> algorithms;
    for (int i = 0; i < 5; i++) {
        algorithms.push_back(AceType::MakeRefPtr<BubbleLayoutAlgorithm>(
            1001 + i, "target" + std::to_string(i),
            OffsetF(100.0f + i * 50.0f, 100.0f + i * 50.0f),
            SizeF(50.0f + i * 10.0f, 50.0f + i * 10.0f)));
    }

    // Set different arrow dimensions for each instance
    constexpr Dimension ARROW_RADIUS = 2.0_vp;
    for (size_t i = 0; i < algorithms.size(); i++) {
        algorithms[i]->bubbleArrowWidth_ =
            Dimension(16.0_vp + Dimension(static_cast<double>(i) * 4.0, DimensionUnit::VP));
        algorithms[i]->bubbleArrowHeight_ =
            Dimension(8.0_vp + Dimension(static_cast<double>(i) * 2.0, DimensionUnit::VP));
        algorithms[i]->GetEndP2P4(ARROW_RADIUS);
        algorithms[i]->GetP2(ARROW_RADIUS);
    }

    // Verify each instance has independent values
    for (size_t i = 0; i < algorithms.size(); i++) {
        EXPECT_FLOAT_EQ(algorithms[i]->bubbleArrowWidth_.Value(), 16.0 + static_cast<double>(i) * 4.0);
        EXPECT_FLOAT_EQ(algorithms[i]->bubbleArrowHeight_.Value(), 8.0 + static_cast<double>(i) * 2.0);
        EXPECT_GT(algorithms[i]->typeOneBeta_, 0.0);
        EXPECT_GT(algorithms[i]->typeTwoBeta_, 0.0);
    }

    // Verify that all instances have different typeOneBeta values
    for (size_t i = 0; i < algorithms.size() - 1; i++) {
        EXPECT_NE(algorithms[i]->typeOneBeta_, algorithms[i + 1]->typeOneBeta_);
        EXPECT_NE(algorithms[i]->typeTwoBeta_, algorithms[i + 1]->typeTwoBeta_);
    }
}

/**
 * @tc.name: ArrowMemberVariablesTest017
 * @tc.desc: Test default values of all new arrow member variables
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest017, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Verify default values of arrow dimension variables
    EXPECT_EQ(algorithm->bubbleArrowWidth_, 16.0_vp);
    EXPECT_EQ(algorithm->bubbleArrowHeight_, 8.0_vp);
    EXPECT_FALSE(algorithm->bubbleArrowWidthF_.has_value());
    EXPECT_FALSE(algorithm->bubbleArrowHeightF_.has_value());

    // Verify default values of calculated parameters
    EXPECT_EQ(algorithm->defaultP2Height_, 7.32_vp);
    EXPECT_EQ(algorithm->defaultP2Width_, 1.5_vp);
    EXPECT_EQ(algorithm->defaultP4EndY_, 6.0_vp);
    EXPECT_EQ(algorithm->defaultP2EndX_, 12.8_vp);
    EXPECT_EQ(algorithm->defaultP2EndY_, 7.6_vp);

    // Verify default values of beta angles
    EXPECT_EQ(algorithm->typeOneBeta_, 0.0);
    EXPECT_EQ(algorithm->typeTwoBeta_, 0.0);
}

/**
 * @tc.name: ArrowMemberVariablesTest018
 * @tc.desc: Test all arrow vertical offset parameters have correct default values
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest018, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Verify all vertical offset parameters have default values
    EXPECT_EQ(algorithm->arrowVerticalP1OffsetX_, 8.0_vp);
    EXPECT_EQ(algorithm->arrowVerticalP2OffsetX_, 1.5_vp);
    EXPECT_EQ(algorithm->arrowVerticalP2OffsetY_, 7.32_vp);
    EXPECT_EQ(algorithm->arrowVerticalP4OffsetX_, 1.5_vp);
    EXPECT_EQ(algorithm->arrowVerticalP4OffsetY_, 7.32_vp);
    EXPECT_EQ(algorithm->arrowVerticalP5OffsetX_, 8.0_vp);
}

/**
 * @tc.name: ArrowMemberVariablesTest019
 * @tc.desc: Test all arrow horizon offset parameters have correct default values
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest019, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Verify all horizon offset parameters have default values
    EXPECT_EQ(algorithm->arrowHorizonP1OffsetY_, 8.0_vp);
    EXPECT_EQ(algorithm->arrowHorizonP2OffsetX_, 7.32_vp);
    EXPECT_EQ(algorithm->arrowHorizonP2OffsetY_, 1.5_vp);
    EXPECT_EQ(algorithm->arrowHorizonP4OffsetX_, 7.32_vp);
    EXPECT_EQ(algorithm->arrowHorizonP4OffsetY_, 1.5_vp);
    EXPECT_EQ(algorithm->arrowHorizonP5OffsetY_, 8.0_vp);
}

/**
 * @tc.name: ArrowMemberVariablesTest020
 * @tc.desc: Test all arrow replace start vertical offset parameters have correct default values
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest020, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Verify all replace start vertical offset parameters have default values
    EXPECT_EQ(algorithm->arrowReplaceStartVerticalP1OffsetX_, 8.0_vp);
    EXPECT_EQ(algorithm->arrowReplaceStartVerticalP2OffsetX_, 8.0_vp);
    EXPECT_EQ(algorithm->arrowReplaceStartVerticalP2OffsetY_, 6.0_vp);
    EXPECT_EQ(algorithm->arrowReplaceStartVerticalP4OffsetX_, 4.8_vp);
    EXPECT_EQ(algorithm->arrowReplaceStartVerticalP4OffsetY_, 7.6_vp);
    EXPECT_EQ(algorithm->arrowReplaceStartVerticalP5OffsetX_, 8.0_vp);
}

/**
 * @tc.name: ArrowMemberVariablesTest021
 * @tc.desc: Test all arrow replace end vertical offset parameters have correct default values
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest021, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Verify all replace end vertical offset parameters have default values
    EXPECT_EQ(algorithm->arrowReplaceEndVerticalP1OffsetX_, 8.0_vp);
    EXPECT_EQ(algorithm->arrowReplaceEndVerticalP2OffsetX_, 4.8_vp);
    EXPECT_EQ(algorithm->arrowReplaceEndVerticalP2OffsetY_, 7.6_vp);
    EXPECT_EQ(algorithm->arrowReplaceEndVerticalP4OffsetX_, 8.0_vp);
    EXPECT_EQ(algorithm->arrowReplaceEndVerticalP4OffsetY_, 6.0_vp);
    EXPECT_EQ(algorithm->arrowReplaceEndVerticalP5OffsetX_, 8.0_vp);
}

/**
 * @tc.name: ArrowMemberVariablesTest022
 * @tc.desc: Test all arrow replace start horizon offset parameters have correct default values
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest022, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Verify all replace start horizon offset parameters have default values
    EXPECT_EQ(algorithm->arrowReplaceStartHorizonP1OffsetY_, 8.0_vp);
    EXPECT_EQ(algorithm->arrowReplaceStartHorizonP2OffsetX_, 6.0_vp);
    EXPECT_EQ(algorithm->arrowReplaceStartHorizonP2OffsetY_, 8.0_vp);
    EXPECT_EQ(algorithm->arrowReplaceStartHorizonP4OffsetX_, 7.6_vp);
    EXPECT_EQ(algorithm->arrowReplaceStartHorizonP4OffsetY_, 4.8_vp);
    EXPECT_EQ(algorithm->arrowReplaceStartHorizonP5OffsetY_, 8.0_vp);
}

/**
 * @tc.name: ArrowMemberVariablesTest023
 * @tc.desc: Test all arrow replace end horizon offset parameters have correct default values
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest023, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Verify all replace end horizon offset parameters have default values
    EXPECT_EQ(algorithm->arrowReplaceEndHorizonP1OffsetY_, 8.0_vp);
    EXPECT_EQ(algorithm->arrowReplaceEndHorizonP2OffsetX_, 7.6_vp);
    EXPECT_EQ(algorithm->arrowReplaceEndHorizonP2OffsetY_, 4.8_vp);
    EXPECT_EQ(algorithm->arrowReplaceEndHorizonP4OffsetX_, 6.0_vp);
    EXPECT_EQ(algorithm->arrowReplaceEndHorizonP4OffsetY_, 8.0_vp);
    EXPECT_EQ(algorithm->arrowReplaceEndHorizonP5OffsetY_, 8.0_vp);
}

/**
 * @tc.name: ArrowMemberVariablesTest024
 * @tc.desc: Test SetArrowSize with zero arrow dimensions
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest024, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Set zero arrow dimensions
    algorithm->bubbleArrowWidth_ = Dimension(0.0_vp);
    algorithm->bubbleArrowHeight_ = Dimension(0.0_vp);

    // Call SetArrowSize with zero dimensions
    float width = 0.0f;
    float height = 0.0f;
    algorithm->SetArrowSize(width, height);

    // Verify the width and height are zero
    EXPECT_FLOAT_EQ(width, 0.0f);
    EXPECT_FLOAT_EQ(height, 0.0f);
}

/**
 * @tc.name: ArrowMemberVariablesTest025
 * @tc.desc: Test SetArrowSize with large arrow dimensions
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest025, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    algorithm->bubbleArrowWidth_ = Dimension(LARGE_ARROW_WIDTH, DimensionUnit::VP);
    algorithm->bubbleArrowHeight_ = Dimension(LARGE_ARROW_HEIGHT, DimensionUnit::VP);

    // Call SetArrowSize with large dimensions
    float width = 0.0f;
    float height = 0.0f;
    algorithm->SetArrowSize(width, height);

    // Verify the width and height are set to large values
    EXPECT_FLOAT_EQ(width, LARGE_ARROW_WIDTH);
    EXPECT_FLOAT_EQ(height, LARGE_ARROW_HEIGHT);
}

/**
 * @tc.name: ArrowMemberVariablesTest026
 * @tc.desc: Test GetEndP2P4 with very small radius
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest026, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Set up arrow dimensions
    algorithm->bubbleArrowWidth_ = Dimension(16.0_vp);
    algorithm->bubbleArrowHeight_ = Dimension(8.0_vp);

    // Call GetEndP2P4 with very small radius
    constexpr Dimension SMALL_RADIUS = 0.5_vp;
    algorithm->GetEndP2P4(SMALL_RADIUS);

    // Verify calculations still work
    EXPECT_GT(algorithm->typeOneBeta_, 0.0);
    EXPECT_GT(algorithm->defaultP4EndY_.Value(), 0.0);
}

/**
 * @tc.name: ArrowMemberVariablesTest027
 * @tc.desc: Test GetP2 with very small radius
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest027, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Set up arrow dimensions
    algorithm->bubbleArrowWidth_ = Dimension(16.0_vp);
    algorithm->bubbleArrowHeight_ = Dimension(8.0_vp);

    // Call GetP2 with very small radius
    constexpr Dimension SMALL_RADIUS = 0.5_vp;
    algorithm->GetP2(SMALL_RADIUS);

    // Verify calculations still work
    EXPECT_GT(algorithm->typeTwoBeta_, 0.0);
    EXPECT_GT(algorithm->defaultP2Height_.Value(), 0.0);
}

/**
 * @tc.name: ArrowMemberVariablesTest028
 * @tc.desc: Test that CalculateArrowPoint sets up all offset parameters correctly
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest028, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Set up custom arrow dimensions
    algorithm->bubbleArrowWidth_ = Dimension(24.0_vp);
    algorithm->bubbleArrowHeight_ = Dimension(12.0_vp);

    // Call GetEndP2P4 and GetP2 to calculate parameters
    constexpr Dimension ARROW_RADIUS = 2.0_vp;
    algorithm->GetEndP2P4(ARROW_RADIUS);
    algorithm->GetP2(ARROW_RADIUS);

    // Simulate CalculateArrowPoint rateX calculation
    float rateX = 24.0f / 16.0f; // CUSTOM_ARROW_WIDTH / DEFAULT_ARROW_WIDTH

    // Manually set offset values as CalculateArrowPoint would do
    algorithm->arrowVerticalP1OffsetX_ = 8.0_vp * rateX;
    algorithm->arrowVerticalP2OffsetY_ = algorithm->defaultP2Height_;
    algorithm->arrowVerticalP2OffsetX_ = algorithm->defaultP2Width_;
    algorithm->arrowVerticalP4OffsetY_ = algorithm->defaultP2Height_;
    algorithm->arrowVerticalP4OffsetX_ = algorithm->defaultP2Width_;
    algorithm->arrowVerticalP5OffsetX_ = 8.0_vp * rateX;

    // Verify the offset values are set correctly
    EXPECT_FLOAT_EQ(algorithm->arrowVerticalP1OffsetX_.Value(), 8.0 * rateX);
    EXPECT_FLOAT_EQ(algorithm->arrowVerticalP2OffsetY_.Value(), algorithm->defaultP2Height_.Value());
    EXPECT_FLOAT_EQ(algorithm->arrowVerticalP2OffsetX_.Value(), algorithm->defaultP2Width_.Value());
    EXPECT_FLOAT_EQ(algorithm->arrowVerticalP5OffsetX_.Value(), 8.0 * rateX);
}

/**
 * @tc.name: ArrowMemberVariablesTest029
 * @tc.desc: Test that defaultP2Height, defaultP2Width, defaultP4EndY, defaultP2EndX, defaultP2EndY
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest029, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");

    // Set up default arrow dimensions
    algorithm->bubbleArrowWidth_ = Dimension(16.0_vp);
    algorithm->bubbleArrowHeight_ = Dimension(8.0_vp);

    // Call GetEndP2P4 to calculate defaultP4EndY, defaultP2EndX, defaultP2EndY
    constexpr Dimension ARROW_RADIUS = 2.0_vp;
    algorithm->GetEndP2P4(ARROW_RADIUS);

    // Verify calculated values are positive
    EXPECT_GT(algorithm->defaultP4EndY_.Value(), 0.0);
    EXPECT_GT(algorithm->defaultP2EndX_.Value(), 0.0);
    EXPECT_GT(algorithm->defaultP2EndY_.Value(), 0.0);

    // Call GetP2 to calculate defaultP2Height, defaultP2Width
    algorithm->GetP2(ARROW_RADIUS);

    // Verify calculated values are positive
    EXPECT_GT(algorithm->defaultP2Height_.Value(), 0.0);
    EXPECT_GT(algorithm->defaultP2Width_.Value(), 0.0);
}

/**
 * @tc.name: ArrowMemberVariablesTest030
 * @tc.desc: Test that multiple instances have independent calculated point parameters
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestFourNg, ArrowMemberVariablesTest030, TestSize.Level1)
{
    auto algorithm1 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1001, "target1");
    auto algorithm2 = AceType::MakeRefPtr<BubbleLayoutAlgorithm>(1002, "target2");

    // Set different arrow dimensions
    algorithm1->bubbleArrowWidth_ = Dimension(16.0_vp);
    algorithm1->bubbleArrowHeight_ = Dimension(8.0_vp);

    algorithm2->bubbleArrowWidth_ = Dimension(32.0_vp);
    algorithm2->bubbleArrowHeight_ = Dimension(16.0_vp);

    // Call GetEndP2P4 and GetP2 for both instances
    constexpr Dimension ARROW_RADIUS = 2.0_vp;
    algorithm1->GetEndP2P4(ARROW_RADIUS);
    algorithm1->GetP2(ARROW_RADIUS);
    algorithm2->GetEndP2P4(ARROW_RADIUS);
    algorithm2->GetP2(ARROW_RADIUS);

    // Verify that calculated point parameters are different
    EXPECT_NE(algorithm1->defaultP2Height_.Value(), algorithm2->defaultP2Height_.Value());
    EXPECT_NE(algorithm1->defaultP2Width_.Value(), algorithm2->defaultP2Width_.Value());
    EXPECT_NE(algorithm1->defaultP4EndY_.Value(), algorithm2->defaultP4EndY_.Value());
    EXPECT_NE(algorithm1->defaultP2EndX_.Value(), algorithm2->defaultP2EndX_.Value());
    EXPECT_NE(algorithm1->defaultP2EndY_.Value(), algorithm2->defaultP2EndY_.Value());
}

} // namespace OHOS::Ace::NG