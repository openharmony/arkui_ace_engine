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
#define protected public
#define private public
#include "base/geometry/dimension.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/toggle_button_event_hub.h"
#include "core/components_ng/pattern/button/toggle_button_paint_property.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/checkbox/checkbox_event_hub.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/toggle/switch_event_hub.h"
#include "core/components_ng/pattern/toggle/switch_paint_method.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"
#include "core/components_ng/pattern/toggle/toggle_model.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/root/root_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_ON = true;
constexpr bool SKIP_MEASURE = true;
constexpr bool NO_SKIP_MEASURE = false;
constexpr float CONTAINER_WIDTH = 200.0f;
constexpr float CONTAINER_HEIGHT = 100.0f;
constexpr Color SELECTED_COLOR = Color(0XFFFF0000);
constexpr Color SWITCH_POINT_COLOR = Color(0XFFFFFF00);
constexpr Color BACKGROUND_COLOR = Color(0XFFFF0000);
constexpr Dimension ZERO = 0.0_px;
constexpr Dimension TOGGLE_WIDTH = 60.0_px;
constexpr Dimension TOGGLE_HEIGH = 20.0_px;
constexpr float SWITCH_WIDTH = 100.0f;
constexpr float SWITCH_HEIGHT = 50.0f;
constexpr Dimension PADDING = Dimension(5.0);
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const Alignment ALIGNMENT = Alignment::BOTTOM_RIGHT;
const std::vector<NG::ToggleType> TOGGLE_TYPE = { ToggleType::CHECKBOX, ToggleType::BUTTON, ToggleType::SWITCH };
} // namespace

class ToggleTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static PaddingPropertyF CreatePadding(Dimension length);
};

void ToggleTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void ToggleTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

PaddingPropertyF ToggleTestNg::CreatePadding(Dimension length)
{
    PaddingPropertyF padding;
    padding.left = length.ConvertToPx();
    padding.right = length.ConvertToPx();
    padding.top = length.ConvertToPx();
    padding.bottom = length.ConvertToPx();
    return padding;
}

/**
 * @tc.name: TogglePatternTest001
 * @tc.desc: test the process of toggle created with checkbox.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);
    auto checkBoxFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(checkBoxFrameNode, nullptr);
    EXPECT_EQ(checkBoxFrameNode->GetTag(), V2::CHECKBOX_ETS_TAG);

    /**
     * @tc.steps: step2.get checkBox property and check whether the property value is correct.
     */
    auto pattern = AceType::DynamicCast<CheckBoxPattern>(checkBoxFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetCheckBoxSelect(), IS_ON);
    EXPECT_EQ(paintProperty->GetCheckBoxSelectedColor(), SELECTED_COLOR);
    ViewStackProcessor::GetInstance()->ClearStack();

    // update different toggle type
    for (size_t i = 0; i < TOGGLE_TYPE.size(); ++i) {
        ToggleModelNG toggleModelNG;
        toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);

        auto isOn = i % 2 == 0 ? true : false;
        toggleModelNG.Create(TOGGLE_TYPE[i], isOn);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_NE(frameNode, nullptr);

        auto pattern = frameNode->GetPattern();
        EXPECT_NE(pattern, nullptr);
        if (AceType::InstanceOf<CheckBoxPattern>(pattern)) {
            auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
            EXPECT_NE(paintProperty, nullptr);
            EXPECT_EQ(paintProperty->GetCheckBoxSelect(), isOn);
        }
        if (AceType::InstanceOf<SwitchPattern>(pattern)) {
            auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
            EXPECT_NE(paintProperty, nullptr);
            EXPECT_EQ(paintProperty->GetIsOn(), isOn);
        }
        if (AceType::InstanceOf<ToggleButtonPattern>(pattern)) {
            auto paintProperty = pattern->GetPaintProperty<ToggleButtonPaintProperty>();
            EXPECT_NE(paintProperty, nullptr);
            EXPECT_EQ(paintProperty->GetIsOn(), isOn);
        }
        ViewStackProcessor::GetInstance()->ClearStack();
    }
}

/**
 * @tc.name: TogglePatternTest002
 * @tc.desc: test the process of toggle created with button.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(buttonFrameNode, nullptr);
    EXPECT_EQ(buttonFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);

    /**
     * @tc.steps: step2.get button property and check whether the property value is correct.
     */
    auto paintProperty = buttonFrameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetIsOn(), IS_ON);
    EXPECT_EQ(paintProperty->GetSelectedColor(), SELECTED_COLOR);
}

/**
 * @tc.name: TogglePatternTest003
 * @tc.desc: test the process of toggle created with switch.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);
    toggleModelNG.SetSwitchPointColor(SWITCH_POINT_COLOR);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    EXPECT_EQ(switchFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);
    EXPECT_EQ(toggleModelNG.IsToggle(), false);

    /**
     * @tc.steps: step2.get switch property and check whether the property value is correct.
     */
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetIsOn(), IS_ON);
    EXPECT_EQ(paintProperty->GetSelectedColor(), SELECTED_COLOR);
    EXPECT_EQ(paintProperty->GetSwitchPointColor(), SWITCH_POINT_COLOR);
}

/**
 * @tc.name: TogglePatternTest004
 * @tc.desc: test toggle created SetWidth SetHeight SetBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);
    toggleModelNG.SetWidth(TOGGLE_WIDTH);
    toggleModelNG.SetHeight(TOGGLE_HEIGH);
    toggleModelNG.SetBackgroundColor(BACKGROUND_COLOR, true);
    auto padding = CreatePadding(ZERO);
    NG::PaddingProperty newPadding(
        { NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp) });
    toggleModelNG.SetPadding(padding, newPadding);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(buttonFrameNode, nullptr);
    EXPECT_EQ(buttonFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);

    /**
     * @tc.steps: step2.get button property and check whether the property value is correct.
     */
    auto paintProperty = buttonFrameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetIsOn(), IS_ON);
    EXPECT_EQ(paintProperty->GetSelectedColor(), SELECTED_COLOR);
    EXPECT_EQ(paintProperty->GetBackgroundColor(), BACKGROUND_COLOR);
}

/**
 * @tc.name: TogglePatternTest005
 * @tc.desc: Test event function of toggle with checkbox.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);

    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    bool stateChange = true;
    auto onChange = [&stateChange](bool flag) { stateChange = flag; };
    toggleModelNG.OnChange(onChange);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    auto checkBoxFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(checkBoxFrameNode, nullptr);
    EXPECT_EQ(checkBoxFrameNode->GetTag(), V2::CHECKBOX_ETS_TAG);
    auto eventHub = checkBoxFrameNode->GetOrCreateEventHub<CheckBoxEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    eventHub->UpdateChangeEvent(false);
    EXPECT_EQ(stateChange, false);

    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(stateChange, true);
}

/**
 * @tc.name: TogglePatternTest006
 * @tc.desc: Test event function of toggle with button.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);

    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    bool stateChange = true;
    auto onChange = [&stateChange](bool flag) { stateChange = flag; };
    toggleModelNG.OnChange(onChange);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(buttonFrameNode, nullptr);
    EXPECT_EQ(buttonFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);
    auto eventHub = buttonFrameNode->GetOrCreateEventHub<ToggleButtonEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    eventHub->UpdateChangeEvent(false);
    EXPECT_EQ(stateChange, false);

    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(stateChange, true);
}

/**
 * @tc.name: TogglePatternTest007
 * @tc.desc: Test event function of toggle with switch.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);
    toggleModelNG.SetSwitchPointColor(SWITCH_POINT_COLOR);

    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    bool stateChange = true;
    auto onChange = [&stateChange](bool flag) { stateChange = flag; };
    toggleModelNG.OnChange(onChange);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    EXPECT_EQ(switchFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);
    auto eventHub = switchFrameNode->GetOrCreateEventHub<SwitchEventHub>();
    EXPECT_NE(eventHub, nullptr);
    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(stateChange, true);
}

/**
 * @tc.name: TogglePatternTest008
 * @tc.desc: Test toggle OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2. create switch frameNode, get switchPattern.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    EXPECT_NE(switchPattern, nullptr);
    auto layoutProperty = switchFrameNode->GetLayoutProperty();

    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SwitchTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SwitchTheme>()));
    switchPattern->OnModifyDone();

    // update layoutProperty and execute OnModifyDone again
    layoutProperty->UpdateAlignment(ALIGNMENT);
    MarginProperty margin;
    margin.left = CalcLength(PADDING.ConvertToPx());
    margin.right = CalcLength(PADDING.ConvertToPx());
    margin.top = CalcLength(PADDING.ConvertToPx());
    margin.bottom = CalcLength(PADDING.ConvertToPx());
    layoutProperty->UpdateMargin(margin); // GetMarginProperty
    switchPattern->isOn_ = false;
    switchPattern->OnModifyDone();
    EXPECT_EQ(ALIGNMENT, layoutProperty->GetPositionProperty()->GetAlignmentValue());
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(PADDING.ConvertToPx()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(), CalcLength(PADDING.ConvertToPx()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->top.value(), CalcLength(PADDING.ConvertToPx()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->bottom.value(), CalcLength(PADDING.ConvertToPx()));

    auto geometryNode = switchFrameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(SWITCH_WIDTH, SWITCH_HEIGHT));
    auto paintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    switchPattern->isOn_ = false;
    paintProperty->UpdateIsOn(true);
    switchPattern->OnModifyDone();
    EXPECT_EQ(switchPattern->isOn_, true);
    EXPECT_EQ(paintProperty->GetIsOnValue(), true);
}

/**
 * @tc.name: TogglePatternTest009
 * @tc.desc: Test toggle OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    /**
     * @tc.steps: step2.  get switchPattern and switchWrapper.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(switchPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = switchFrameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(switchFrameNode, geometryNode, layoutProperty);
    EXPECT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. call switchPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap success and result correct.
     */
    auto switchLayoutAlgorithm = AceType::MakeRefPtr<SwitchLayoutAlgorithm>();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm, SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     * @tc.steps: step4. call switchPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step4. OnDirtyLayoutWrapperSwap success and result correct.
     */
    bool first_case = switchPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_FALSE(first_case);
    bool second_case = switchPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_FALSE(second_case);
    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm, NO_SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    switchPattern->isOn_ = true;
    bool third_case = switchPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(third_case);
    bool forth_case = switchPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, true);
    EXPECT_TRUE(forth_case);
    switchPattern->isOn_ = false;
    bool fifth_case = switchPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, true);
    EXPECT_TRUE(fifth_case);
}

/**
 * @tc.name: TogglePatternTest0010
 * @tc.desc: Test toggle OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    /**
     * @tc.steps: step2.  get switchPattern and switchWrapper.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(switchPattern, nullptr);

    /**
     * @tc.steps: step3  execute event function.
     * @tc.expected: step2. check whether event function is executed successfully.
     */
    auto hub = switchPattern->GetOrCreateEventHub<EventHub>();
    EXPECT_NE(hub, nullptr);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureHub, nullptr);
    // InitPanEvent()
    switchPattern->InitPanEvent(gestureHub);
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    switchPattern->panEvent_->actionStart_(info);
    switchPattern->panEvent_->actionUpdate_(info);
    switchPattern->panEvent_->actionEnd_(info);
    switchPattern->panEvent_->actionCancel_();
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);
    switchPattern->panEvent_->actionStart_(info);
    switchPattern->panEvent_->actionUpdate_(info);
    switchPattern->panEvent_->actionEnd_(info);
    switchPattern->InitPanEvent(gestureHub);
    // InitClickEvent()
    switchPattern->InitClickEvent();
    switchPattern->InitClickEvent();
    // InitTouchEvent()
    switchPattern->InitTouchEvent();
    switchPattern->InitTouchEvent();
    TouchEventInfo touchInfo("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::DOWN);
    touchInfo.AddTouchLocationInfo(std::move(touchInfo1));
    switchPattern->touchListener_->GetTouchEventCallback()(touchInfo);
    TouchLocationInfo touchInfo2(2);
    touchInfo2.SetTouchType(TouchType::UP);
    touchInfo.AddTouchLocationInfo(std::move(touchInfo2));
    switchPattern->touchListener_->GetTouchEventCallback()(touchInfo);
    TouchLocationInfo touchInfo3(3);
    touchInfo2.SetTouchType(TouchType::CANCEL);
    touchInfo.AddTouchLocationInfo(std::move(touchInfo3));
    switchPattern->touchListener_->GetTouchEventCallback()(touchInfo);

    // InitMouseEvent()
    switchPattern->InitMouseEvent();
    EXPECT_NE(switchPattern->mouseEvent_, nullptr);
    switchPattern->InitMouseEvent();

    switchPattern->isOn_ = true;
    switchPattern->OnClick();
    switchPattern->OnTouchDown();
    switchPattern->OnTouchUp();
    switchPattern->UpdateChangeEvent();

    // execute Handle function
    switchPattern->HandleMouseEvent(true);
    info.SetMainDelta(10.0f);
    switchPattern->HandleDragUpdate(info);
    info.SetMainDelta(0.0f);
    switchPattern->HandleDragUpdate(info);

    switchPattern->HandleDragEnd();
    switchPattern->isOn_ = false;
    switchPattern->HandleDragEnd();
    // other branch
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(20, 10));
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = switchFrameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(switchFrameNode, geometryNode, layoutProperty);
    EXPECT_NE(layoutWrapper, nullptr);
    auto switchLayoutAlgorithm = AceType::MakeRefPtr<SwitchLayoutAlgorithm>();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm, SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    EXPECT_EQ(geometryNode->GetContentSize().Width(), 20);
    switchPattern->HandleDragEnd();
    switchPattern->isOn_ = true;
    switchPattern->HandleDragEnd();
    switchPattern->OnClick();
}

/**
 * @tc.name: TogglePaintTest0011
 * @tc.desc: Test toggle SetSelectedColor(undefined).
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    std::optional<Color> selectedColor = std::optional<Color>();

    /**
     * @tc.steps: step1. test checkbox
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkboxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkboxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkboxTheme));

    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    toggleModelNG.SetSelectedColor(selectedColor);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto checkboxPattern = AceType::DynamicCast<CheckBoxPattern>(frameNode->GetPattern());
    EXPECT_NE(checkboxPattern, nullptr);
    auto checkboxPaintProperty = checkboxPattern->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(checkboxPaintProperty, nullptr);
    EXPECT_NE(checkboxPaintProperty->GetCheckBoxSelectedColor(), checkboxTheme->GetActiveColor());

    /**
     * @tc.steps: step2. test button
     */
    themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto toggleButtonTheme = AceType::MakeRefPtr<ToggleTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(toggleButtonTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(toggleButtonTheme));

    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    toggleModelNG.SetSelectedColor(selectedColor);

    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto buttonPaintProperty = frameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_NE(buttonPaintProperty, nullptr);
    EXPECT_NE(buttonPaintProperty->GetSelectedColor(), toggleButtonTheme->GetCheckedColor());

    /**
     * @tc.steps: step3. test switch
     */
    themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    toggleModelNG.SetSelectedColor(selectedColor);

    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto switchPattern = AceType::DynamicCast<SwitchPattern>(frameNode->GetPattern());
    EXPECT_NE(switchPattern, nullptr);
    auto switchPaintProperty = switchPattern->GetPaintProperty<SwitchPaintProperty>();
    EXPECT_NE(switchPaintProperty, nullptr);
    EXPECT_NE(switchPaintProperty->GetSelectedColor(), switchTheme->GetActiveColor());
}

/**
 * @tc.name: TogglePatternTest0012
 * @tc.desc: Test toggle OnModifyDone default margin.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2. create switch frameNode, get switchPattern.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    EXPECT_NE(switchPattern, nullptr);
    auto layoutProperty = switchFrameNode->GetLayoutProperty();

    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    MarginProperty margin;
    margin.left = CalcLength(PADDING.ConvertToPx());
    layoutProperty->UpdateMargin(margin); // GetMarginProperty

    switchPattern->OnModifyDone();
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(PADDING.ConvertToPx()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(),
        CalcLength(switchTheme->GetHotZoneHorizontalPadding().Value()));
    EXPECT_EQ(
        layoutProperty->GetMarginProperty()->top.value(), CalcLength(switchTheme->GetHotZoneVerticalPadding().Value()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->bottom.value(),
        CalcLength(switchTheme->GetHotZoneVerticalPadding().Value()));

    MarginProperty margin1;
    margin1.right = CalcLength(PADDING.ConvertToPx());
    layoutProperty->UpdateMargin(margin1); // GetMarginProperty

    switchPattern->OnModifyDone();
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(), CalcLength(PADDING.ConvertToPx()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(),
        CalcLength(switchTheme->GetHotZoneHorizontalPadding().Value()));
    EXPECT_EQ(
        layoutProperty->GetMarginProperty()->top.value(), CalcLength(switchTheme->GetHotZoneVerticalPadding().Value()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->bottom.value(),
        CalcLength(switchTheme->GetHotZoneVerticalPadding().Value()));
}

/**
 * @tc.name: TogglePatternTest0013
 * @tc.desc: Test Toggle pattern method HandleMouseEvent, OnTouchUp and OnTouchDown.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Toggle node
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);

    /**
     * @tc.steps: step2. Get Toggle pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set Toggle pattern variable and call HandleMouseEvent, OnTouchUp and OnTouchDown
     * @tc.expected: step3. Check the Toggle pattern value
     */
    pattern->isTouch_ = true;
    pattern->isHover_ = false;
    pattern->HandleMouseEvent(true);
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::HOVER);
    EXPECT_EQ(pattern->isTouch_, true);
    pattern->HandleMouseEvent(false);
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::NONE);

    pattern->isTouch_ = true;
    pattern->isHover_ = false;
    pattern->OnTouchUp();
    EXPECT_EQ(pattern->isTouch_, false);
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::NONE);
    pattern->isHover_ = true;
    pattern->OnTouchUp();
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::PRESS_TO_HOVER);

    pattern->isTouch_ = false;
    pattern->isHover_ = false;
    pattern->OnTouchDown();
    EXPECT_EQ(pattern->isTouch_, true);
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::PRESS);
    pattern->isHover_ = true;
    pattern->OnTouchDown();
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::HOVER_TO_PRESS);
}

/**
 * @tc.name: TogglePatternTest0018
 * @tc.desc: Test toggle OnModifyDone default margin.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2. create switch frameNode, get switchPattern.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    EXPECT_NE(switchPattern, nullptr);
    auto layoutProperty = switchFrameNode->GetLayoutProperty();

    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    MarginProperty margin;
    margin.left = CalcLength(PADDING.ConvertToPx());
    layoutProperty->UpdateMargin(margin); // GetMarginProperty

    switchPattern->OnModifyDone();
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        EXPECT_EQ(switchPattern->direction_, TextDirection::RTL);
    } else {
        EXPECT_EQ(switchPattern->direction_, TextDirection::LTR);
    }
}

/**
 * @tc.name: ToggleLayoutTest001
 * @tc.desc: Test toggle layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleLayoutTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2.  get switchPattern and switchWrapper.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(switchPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(switchFrameNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(switchFrameNode, geometryNode, switchFrameNode->GetLayoutProperty());
    auto switchLayoutAlgorithm = AceType::DynamicCast<SwitchLayoutAlgorithm>(switchPattern->CreateLayoutAlgorithm());
    EXPECT_NE(switchLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    // update switchTheme values
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGH;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), 36);

    LayoutConstraintF layoutConstraintSizeFirst;
    layoutConstraintSizeFirst.maxSize = SizeF(30, 10);

    // different branch: update frameWidth = frameHeight = 0
    auto switchSizeOne = switchLayoutAlgorithm->MeasureContent(layoutConstraintSizeFirst, &layoutWrapper);
    EXPECT_EQ(switchSizeOne->Width(), 18);

    LayoutConstraintF layoutConstraintSizeSecond;
    layoutConstraintSizeSecond.maxSize = CONTAINER_SIZE;
    // different branch: update (frameWidth / frameHeight) > ratio = 1.8
    layoutConstraintSizeSecond.selfIdealSize.SetSize(SizeF(SWITCH_WIDTH, SWITCH_HEIGHT));
    auto switchSizeSecond = switchLayoutAlgorithm->MeasureContent(layoutConstraintSizeSecond, &layoutWrapper);
    EXPECT_EQ(switchSizeSecond->Width(), 90);

    LayoutConstraintF layoutConstraintSizeThird;
    layoutConstraintSizeThird.maxSize = CONTAINER_SIZE;
    // different branch: update (frameWidth / frameHeight) < ratio = 1.8
    layoutConstraintSizeThird.selfIdealSize.SetSize(SizeF(60, 40));
    auto switchSizeThird = switchLayoutAlgorithm->MeasureContent(layoutConstraintSizeThird, &layoutWrapper);
    EXPECT_EQ(switchSizeThird->Width(), 60);

    LayoutConstraintF layoutConstraintSizeForth;
    layoutConstraintSizeForth.maxSize = CONTAINER_SIZE;
    // different branch: update (frameWidth / frameHeight) = ratio = 1.8
    layoutConstraintSizeForth.selfIdealSize.SetSize(SizeF(180, 100));
    auto switchSizeForth = switchLayoutAlgorithm->MeasureContent(layoutConstraintSizeForth, &layoutWrapper);
    EXPECT_EQ(switchSizeForth->Width(), 180);
}

/**
 * @tc.name: TogglePaintTest001
 * @tc.desc: Test toggle PaintContent.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePaintTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod();

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    RefPtr<RenderContext> renderContext = switchFrameNode->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    auto switchPaintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    EXPECT_NE(switchPaintProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, switchPaintProperty);
    EXPECT_NE(paintWrapper, nullptr);
    EXPECT_NE(switchPaintMethod.GetContentModifier(paintWrapper), nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGH;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(AtLeast(1));

    auto contentSize = SizeF(100, 50);
    auto contentOffset = OffsetF(0, 0);
    switchPaintMethod.switchModifier_->PaintSwitch(rsCanvas, contentOffset, contentSize);
}

/**
 * @tc.name: TogglePaintTest002
 * @tc.desc: Test Toggle UpdateAnimatableProperty and SetBoardColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePaintTest002, TestSize.Level1)
{
    auto switchModifier =
        AceType::MakeRefPtr<SwitchModifier>(SizeF(), OffsetF(), 0.0, false, SELECTED_COLOR, SWITCH_POINT_COLOR, 0.0f);
    SizeF toggleSize(SWITCH_WIDTH, SWITCH_HEIGHT);
    switchModifier->SetSize(toggleSize);
    switchModifier->hoverColor_ = Color::RED;
    switchModifier->clickEffectColor_ = Color::BLUE;
    switchModifier->touchHoverType_ = TouchHoverAnimationType::HOVER;
    switchModifier->UpdateAnimatableProperty();
    switchModifier->animateTouchHoverColor_ =
        AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));
    switchModifier->touchHoverType_ = TouchHoverAnimationType::PRESS_TO_HOVER;
    switchModifier->UpdateAnimatableProperty();
    EXPECT_EQ(switchModifier->animateTouchHoverColor_->Get(), LinearColor(Color::RED));
    switchModifier->touchHoverType_ = TouchHoverAnimationType::NONE;
    switchModifier->UpdateAnimatableProperty();
    EXPECT_EQ(switchModifier->animateTouchHoverColor_->Get(), LinearColor(Color::RED.BlendOpacity(0)));
    switchModifier->touchHoverType_ = TouchHoverAnimationType::HOVER_TO_PRESS;
    switchModifier->UpdateAnimatableProperty();
    EXPECT_EQ(switchModifier->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));
    switchModifier->touchHoverType_ = TouchHoverAnimationType::PRESS;
    switchModifier->UpdateAnimatableProperty();
    EXPECT_EQ(switchModifier->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));
    switchModifier->isDragEvent_ = true;
    switchModifier->SetDragOffsetX(0.0f);
    switchModifier->UpdateAnimatableProperty();
    EXPECT_EQ(switchModifier->pointOffset_->Get(), 0.0f);
}

/**
 * @tc.name: TogglePaintTest004
 * @tc.desc: Test SwitchPaintMethod GetContentModifier UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePaintTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchModifier =
        AceType::MakeRefPtr<SwitchModifier>(SizeF(), OffsetF(), 0.0, IS_ON, SELECTED_COLOR, SWITCH_POINT_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod();
    switchPaintMethod.switchModifier_ = switchModifier;
    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGH;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    EXPECT_EQ(switchModifier, switchPaintMethod.GetContentModifier(paintWrapper));
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_EQ(switchModifier->activeColor_, switchTheme->GetActiveColor());
}

/**
 * @tc.name: TogglePaintTest003
 * @tc.desc: Test SwitchPaintMethod GetSwitchWidth.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePaintTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchModifier =
        AceType::MakeRefPtr<SwitchModifier>(SizeF(), OffsetF(), 0.0, IS_ON, SELECTED_COLOR, SWITCH_POINT_COLOR, 0.0f);

    auto switchTheme = MockPipelineContext::GetCurrent()->GetTheme<SwitchTheme>();
    ASSERT_NE(switchTheme, nullptr);
    switchTheme->height_ = TOGGLE_HEIGH;
    switchTheme->hotZoneVerticalPadding_ = ZERO;

    SizeF size(80.0f, 20.0f);
    auto switchWidth = switchModifier->GetSwitchWidth(size);
    EXPECT_EQ(switchWidth, 62.0f);
}

/**
 * @tc.name: TogglePaintTest005
 * @tc.desc: Test Toggle UpdateAnimatableProperty and SetDirection.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePaintTest005, TestSize.Level1)
{
    auto switchModifier =
        AceType::MakeRefPtr<SwitchModifier>(SizeF(), OffsetF(), 0.0, false, SELECTED_COLOR, SWITCH_POINT_COLOR, 0.0f);
    SizeF toggleSize(SWITCH_WIDTH, SWITCH_HEIGHT);
    switchModifier->SetSize(toggleSize);
    switchModifier->hoverColor_ = Color::RED;
    switchModifier->clickEffectColor_ = Color::BLUE;
    /**
     * @tc.steps: step1. direction is auto
     */
    switchModifier->direction_ = TextDirection::AUTO;
    switchModifier->isDragEvent_ = false;
    switchModifier->isFirstCreated_ = true;
    switchModifier->SetDragOffsetX(0.0f);
    switchModifier->UpdateAnimatableProperty();
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        EXPECT_EQ(switchModifier->pointOffset_->Get(),
            switchModifier->actualSize_.Width() - switchModifier->actualSize_.Height());
    } else {
        EXPECT_EQ(switchModifier->pointOffset_->Get(), 0.0f);
    }
    /**
     * @tc.steps: step2. direction is ltr
     */
    switchModifier->direction_ = TextDirection::LTR;
    switchModifier->isDragEvent_ = false;
    switchModifier->isFirstCreated_ = true;
    switchModifier->SetDragOffsetX(0.0f);
    switchModifier->UpdateAnimatableProperty();
    EXPECT_EQ(switchModifier->pointOffset_->Get(), 0.0f);
    /**
     * @tc.steps: step3. direction is rtl
     */
    switchModifier->direction_ = TextDirection::RTL;
    switchModifier->isDragEvent_ = false;
    switchModifier->isFirstCreated_ = true;
    switchModifier->SetDragOffsetX(0.0f);
    switchModifier->UpdateAnimatableProperty();
    EXPECT_EQ(switchModifier->pointOffset_->Get(),
        switchModifier->actualSize_.Width() - switchModifier->actualSize_.Height());
}

/**
 * @tc.name: TogglePatternTest0017
 * @tc.desc: Test toggle AddHotZoneRect RemoveLastHotZoneRect.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    OffsetF offsetF(0.0f, 0.0f);
    SizeF sizeF(80.0f, 20.0f);
    geometryNode->SetContentOffset(offsetF);
    geometryNode->SetContentSize(sizeF);
    auto layoutProperty = switchFrameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(switchFrameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    auto switchLayoutAlgorithm = AceType::MakeRefPtr<SwitchLayoutAlgorithm>();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    bool result = switchPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_TRUE(result);
    /**
     * cover method AddHotZoneRect
     */
    switchPattern->AddHotZoneRect();
    EXPECT_EQ(switchPattern->hotZoneOffset_.GetX(), 0.0f);
    EXPECT_EQ(switchPattern->hotZoneSize_.Width(), 80.0f);
    /**
     * cover method RemoveLastHotZoneRect
     */
    switchPattern->RemoveLastHotZoneRect();
    int count = switchFrameNode->GetOrCreateGestureEventHub()->responseRegion_.size();
    for (size_t i = 0; i < count; i++) {
        switchPattern->RemoveLastHotZoneRect();
    }

    EXPECT_EQ(switchFrameNode->GetOrCreateGestureEventHub()->isResponseRegion_, false);
}

/**
 * @tc.name: TogglePatternTest0014
 * @tc.desc: Test toggle clickCallback of InitClickEvent InitMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();

    auto gesture = switchFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    /**
     * fire click event
     */
    gesture->ActClick();
    /**
     * fire mouse event
     */
    auto eventHub = switchFrameNode->GetOrCreateEventHub<SwitchEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    auto hoverEventActuator = inputHub->hoverEventActuator_;
    ASSERT_NE(hoverEventActuator, nullptr);
    auto mouseEvents = hoverEventActuator->inputEvents_;
    ASSERT_NE(mouseEvents.size(), 0);
    for (const auto& callback : mouseEvents) {
        (*callback)(false);
    }
}

/**
 * @tc.name: TogglePatternTest0015
 * @tc.desc: Test toggle clickCallback of InitOnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();

    auto eventHub = switchFrameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    /**
     * test event.action != KeyAction::DOWN
     */
    KeyEvent keyEventOne(KeyCode::KEY_A, KeyAction::UP);
    eventHub->ProcessOnKeyEventInternal(keyEventOne);
    /**
     * test event.action == KeyAction::DOWN and event.code == KeyCode::KEY_ENTER
     */
    KeyEvent keyEventTwo(KeyCode::KEY_A, KeyAction::DOWN);
    eventHub->ProcessOnKeyEventInternal(keyEventTwo);
    /**
     * test event.action == KeyAction::DOWN and event.code != KeyCode::KEY_ENTER
     */
    KeyEvent keyEventThr(KeyCode::KEY_ENTER, KeyAction::DOWN);
    eventHub->ProcessOnKeyEventInternal(keyEventThr);
}

/**
 * @tc.name: TogglePatternTest0020
 * @tc.desc: test the process of toggle created with switch.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    toggleModelNG.SetPointRadius(Dimension(10));
    toggleModelNG.SetUnselectedColor(Color(0x00000000));
    toggleModelNG.SetTrackBorderRadius(Dimension(10));

    /**
     * @tc.steps: step2.get switch property and check whether the property value is correct.
     */
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetPointRadius(), Dimension(10));
    EXPECT_EQ(paintProperty->GetUnselectedColor(), Color(0x00000000));
    EXPECT_EQ(paintProperty->GetTrackBorderRadius(), Dimension(10));
}

/**
 * @tc.name: TogglePatternTest0021
 * @tc.desc: test the process of toggle created with switch.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    toggleModelNG.ResetPointRadius();
    toggleModelNG.ResetTrackBorderRadius();

    /**
     * @tc.steps: step2.get switch property and check whether the property value is correct.
     */
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_FALSE(paintProperty->GetPointRadius().has_value());
    EXPECT_FALSE(paintProperty->GetTrackBorderRadius().has_value());
}

/**
 * @tc.name: TogglePatternTest0022
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get parament to pattern SwitchIsOn
     */
    pattern->SetSwitchIsOn(IS_ON);
    /**
     * @tc.steps: step3.get paint property.
     * @tc.expected: check the switch property value.
     */
    auto switchPaintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(switchPaintProperty, nullptr);
    bool isOn = false;
    if (switchPaintProperty->HasIsOn()) {
        isOn = switchPaintProperty->GetIsOnValue();
    } else {
        isOn = false;
    }
    EXPECT_EQ(isOn, IS_ON);
}

/**
 * @tc.name: TogglePatternTest0023
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get parament to pattern SwitchIsOn
     */
    pattern->SetSwitchIsOn(false);
    /**
     * @tc.steps: step3.get paint property.
     * @tc.expected: check the switch property value.
     */
    auto switchPaintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(switchPaintProperty, nullptr);
    bool isOn = false;
    if (switchPaintProperty->HasIsOn()) {
        isOn = switchPaintProperty->GetIsOnValue();
    } else {
        isOn = false;
    }
    EXPECT_EQ(isOn, false);
}

/**
 * @tc.name: TogglePatternTest0024
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get parament to pattern SwitchIsOn
     */
    pattern->SetSwitchIsOn(IS_ON);
    /**
     * @tc.steps: step3.get paint property.
     * @tc.expected: check the switch property value.
     */
    auto switchPaintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(switchPaintProperty, nullptr);
    bool isOn = false;
    if (switchPaintProperty->HasIsOn()) {
        isOn = switchPaintProperty->GetIsOnValue();
    } else {
        isOn = false;
    }
    EXPECT_EQ(isOn, IS_ON);
}

/**
 * @tc.name: TogglePatternTest0025
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get parament to pattern SwitchIsOn
     */
    pattern->SetSwitchIsOn(false);
    /**
     * @tc.steps: step3.get paint property.
     * @tc.expected: check the switch property value.
     */
    auto switchPaintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(switchPaintProperty, nullptr);
    bool isOn = false;
    if (switchPaintProperty->HasIsOn()) {
        isOn = switchPaintProperty->GetIsOnValue();
    } else {
        isOn = false;
    }
    EXPECT_EQ(isOn, false);
}

/**
 * @tc.name: ToggleModelTest001
 * @tc.desc: Test toggle create.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleModelTest001, TestSize.Level1)
{
    const RefPtr<FrameNode> frameParent = FrameNode::CreateFrameNode("parent", 0, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    EXPECT_EQ(switchFrameNode->GetId(), 100);
    switchFrameNode->SetParent(frameParent);
    /**
     * Create again,cover all branches in function Create for switch
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
}

/**
 * @tc.name: ToggleModelTest002
 * @tc.desc: Test toggle create.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleModelTest002, TestSize.Level1)
{
    const RefPtr<FrameNode> frameParent = FrameNode::CreateFrameNode("parent", 0, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    /**
     * @tc.steps: step1. create checkbox and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    EXPECT_EQ(switchFrameNode->GetId(), 100);
    switchFrameNode->SetParent(frameParent);
    /**
     * Create again,cover all branches in function Create for checkbox
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
}

/**
 * @tc.name: ToggleModelTest003
 * @tc.desc: Test toggle create.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleModelTest003, TestSize.Level1)
{
    const RefPtr<FrameNode> frameParent = FrameNode::CreateFrameNode("parent", 0, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    /**
     * @tc.steps: step1. create ToggleButton and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    EXPECT_EQ(switchFrameNode->GetId(), 100);
    switchFrameNode->SetParent(frameParent);
    /**
     * Create again,cover all branches in function Create for ToggleButton
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
}

/**
 * @tc.name: TogglePatternTest0019
 * @tc.desc: Test toggle HandleDragEnd.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, TogglePatternTest0019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(SWITCH_WIDTH, SWITCH_HEIGHT));
    /**
     * @tc.steps: step2. call function HandleDragEnd.
     */
    pattern->dragOffsetX_ = 0;
    pattern->HandleDragEnd();
    pattern->dragOffsetX_ = SWITCH_WIDTH;
    pattern->HandleDragEnd();
    EXPECT_FALSE(pattern->isDragEvent_);
    /**
     * cover isOn_ == false branch.
     */
    pattern->isOn_ = false;
    pattern->HandleDragEnd();
    pattern->dragOffsetX_ = 0;
    pattern->HandleDragEnd();
    EXPECT_FALSE(pattern->isDragEvent_);
}

/**
 * @tc.name: TogglePatternTest020
 * @tc.desc: Switch test Select and ClearSelection.
 */
HWTEST_F(ToggleTestNg, TogglePatternTest020, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isOn_ = false;
    pattern->SetAccessibilityAction();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<SwitchAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->ActActionSelect());

    bool isSelected = true;
    pattern->isOn_ = false;
    pattern->UpdateSelectStatus(isSelected);
    EXPECT_TRUE(accessibilityProperty->ActActionClearSelection());
}

/**
 * @tc.name: ToggleModelTest004
 * @tc.desc: Test checkbox create twice.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleModelTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create the first checkbox.
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto checkboxNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(checkboxNode, nullptr);
    EXPECT_EQ(checkboxNode->GetId(), 100);
    /**
     * @tc.steps: step2. create the second checkbox.
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
}

/**
 * @tc.name: ToggleModelTest005
 * @tc.desc: Test ToggleButton create twice.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleModelTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create the first ToggleButton.
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    auto buttonNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(buttonNode, nullptr);
    EXPECT_EQ(buttonNode->GetId(), 100);
    /**
     * @tc.steps: step2. create the second ToggleButton.
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
}

/**
 * @tc.name: ToggleModelTest006
 * @tc.desc: Test OnChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleModelTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. generate ChangeEvent.
     */
    ChangeEvent changeEvent;
    /**
     * @tc.steps: step2. create checkbox toggle and trigger OnChangeEvent.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    toggleModelNG.OnChangeEvent(std::move(changeEvent));
    /**
     * @tc.steps: step3. create ToggleButton and trigger OnChangeEvent.
     */
    ToggleModelNG toggleModelNG2;
    toggleModelNG2.Create(TOGGLE_TYPE[1], IS_ON);
    frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    toggleModelNG2.OnChangeEvent(std::move(changeEvent));
    /**
     * @tc.steps: step4. create switch toggle and trigger OnChangeEvent.
     */
    ToggleModelNG toggleModelNG3;
    toggleModelNG3.Create(TOGGLE_TYPE[2], IS_ON);
    frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    toggleModelNG3.OnChangeEvent(std::move(changeEvent));
}

/**
 * @tc.name: ToggleModelDistributedTest001
 * @tc.desc: Test the distributed capability of Toggle
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleModelDistributedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto switchPaintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(switchPaintProperty, nullptr);

    /**
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    pattern->isOn_ = false;
    std::string ret = pattern->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"IsOn":false})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"IsOn":true})";
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_TRUE(switchPaintProperty->GetIsOnValue(false));
    restoreInfo_ = "invalid_json_string";
    pattern->OnRestoreInfo(restoreInfo_);
    ASSERT_NE(switchPaintProperty, nullptr);
    EXPECT_TRUE(switchPaintProperty->GetIsOnValue(false));
}

/**
 * @tc.name: ToggleAccessibilityPropertyTestNg001
 * @tc.desc: Test the IsCheckable and IsChecked properties of ToggleButton.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleAccessibilityPropertyTestNg001, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::BUTTON, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto accessibility = frameNode->GetAccessibilityProperty<ToggleButtonAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_TRUE(accessibility->IsCheckable());
    EXPECT_TRUE(accessibility->IsChecked());

    auto paintProperty = frameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateIsOn(false);
    EXPECT_FALSE(accessibility->IsChecked());
}

/**
 * @tc.name: ToggleAccessibilityPropertyTestNg002
 * @tc.desc: Test the IsCheckable and IsChecked properties of Switch.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleAccessibilityPropertyTestNg002, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto accessibility = frameNode->GetAccessibilityProperty<SwitchAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_TRUE(accessibility->IsCheckable());

    auto pattern = AceType::DynamicCast<SwitchPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    pattern->isOn_ = false;
    EXPECT_FALSE(accessibility->IsChecked());

    pattern->isOn_ = true;
    EXPECT_TRUE(accessibility->IsChecked());
}

/**
 * @tc.name: SwitchPatternTest001
 * @tc.desc: Test the IsCheckable and IsChecked properties of Switch.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, SwitchPatternTest001, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto accessibility = frameNode->GetAccessibilityProperty<SwitchAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_TRUE(accessibility->IsCheckable());

    auto pattern = AceType::DynamicCast<SwitchPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    pattern->isOn_ = false;
    EXPECT_FALSE(accessibility->IsChecked());

    pattern->isOn_ = true;
    EXPECT_TRUE(accessibility->IsChecked());

    pattern->OnAfterModifyDone();
}

/**
 * @tc.name: ToggleModelTest007
 * @tc.desc: Test ToggleModelNG::ReplaceAllChild
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleModelTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.CreateFrameNode(0, ToggleType::CHECKBOX, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create oldframenode with RootPattern and call ReplaceAllChild.
     */
    auto oldFrameNodeRoot = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto childRootNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    childRootNode->MountToParent(oldFrameNodeRoot);
    toggleModelNG.ReplaceAllChild(oldFrameNodeRoot);
    auto children = oldFrameNodeRoot->GetChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: ToggleModelTest008
 * @tc.desc: Test ToggleModelNG::ReplaceAllChild
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleModelTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.CreateFrameNode(1, ToggleType::CHECKBOX, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2 - 1. create oldframenode with switchPattern and call ReplaceAllChild.
     */
    auto oldFrameNodeSwitch = FrameNode::CreateFrameNode(V2::SWITCH_ETS_TAG, 1, AceType::MakeRefPtr<SwitchPattern>());
    auto childNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    childNode->MountToParent(oldFrameNodeSwitch);
    auto switchPattern = oldFrameNodeSwitch->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);
    auto modifierNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    switchPattern->contentModifierNode_ = modifierNode;
    switchPattern->nodeId_ = childNode->GetId();
    toggleModelNG.ReplaceAllChild(oldFrameNodeSwitch);
    auto children = oldFrameNodeSwitch->GetChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: ToggleModelTest009
 * @tc.desc: Test ToggleModelNG::ReplaceAllChild
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleModelTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.CreateFrameNode(0, ToggleType::SWITCH, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2 - 2. create oldframenode with checkboxPattern and call ReplaceAllChild.
     */
    auto oldFrameNodeCheckbox =
        FrameNode::CreateFrameNode(V2::CHECKBOX_ETS_TAG, 1, AceType::MakeRefPtr<CheckBoxPattern>());
    auto childCheckboxNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    childCheckboxNode->MountToParent(oldFrameNodeCheckbox);
    auto checkboxPattern = oldFrameNodeCheckbox->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkboxPattern, nullptr);
    auto modifierNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    checkboxPattern->contentModifierNode_ = modifierNode;
    toggleModelNG.ReplaceAllChild(oldFrameNodeCheckbox);
    auto children = oldFrameNodeCheckbox->GetChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: ToggleModelTest010
 * @tc.desc: Test ToggleModelNG::ReplaceAllChild
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleModelTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.CreateFrameNode(0, ToggleType::SWITCH, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2 - 3. create oldframenode with toggleButtonPattern and call ReplaceAllChild.
     */
    auto oldFrameNodeToggle =
        FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, 1, AceType::MakeRefPtr<ToggleButtonPattern>());
    auto childToggleNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    childToggleNode->MountToParent(oldFrameNodeToggle);
    auto togglePattern = oldFrameNodeToggle->GetPattern<ToggleButtonPattern>();
    ASSERT_NE(togglePattern, nullptr);
    auto modifierNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    togglePattern->contentModifierNode_ = modifierNode;
    togglePattern->nodeId_ = childToggleNode->GetId();
    toggleModelNG.ReplaceAllChild(oldFrameNodeToggle);
    auto children = oldFrameNodeToggle->GetChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: ToggleModelTest011
 * @tc.desc: Test ToggleModelNG::SetUnselectedColor
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleModelTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    /**
     * @tc.steps: step2. set Modifer.
     */
    ToggleModelNG toggleModelNGEx;
    toggleModelNGEx.SetUnselectedColor(AceType::RawPtr(switchFrameNode), SELECTED_COLOR);
    toggleModelNGEx.SetTrackBorderRadius(AceType::RawPtr(switchFrameNode), TOGGLE_WIDTH);
    toggleModelNGEx.ResetTrackBorderRadius(AceType::RawPtr(switchFrameNode));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: ToggleModelTest012
 * @tc.desc: Test ToggleModelNG::CreateTypeNode and ToggleModelNG::SetToggleState
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleModelTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Toggle node.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::CHECKBOX, false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. SetToggleState.
     */
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    ToggleModelNG::SetToggleState(node, true);

    /**
     * @tc.steps: step3. assert ToggleState.
     */
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetCheckBoxSelectValue(), true);
}

/**
 * @tc.name: ToggleModelTest013
 * @tc.desc: Test InitOnKeyEvent().
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ToggleModelTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto eventHub = switchFrameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. test event.action != KeyAction::DOWN and event.code == KeyCode::KEY_FUNCTION
     * @tc.expected: step3. check the switch checked status
     */
    KeyEvent keyEventOne(KeyCode::KEY_FUNCTION, KeyAction::UP);
    bool ret = eventHub->ProcessOnKeyEventInternal(keyEventOne);
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_FALSE(ret);
    bool isChecked = pattern->IsChecked();
    EXPECT_EQ(isChecked, IS_ON);
    /**
     * @tc.steps: step4. test event.action == KeyAction::DOWN and event.code != KeyCode::KEY_FUNCTION
     * @tc.expected: step5. check the checked status
     */
    KeyEvent keyEventTwo(KeyCode::KEY_A, KeyAction::DOWN);
    ret = eventHub->ProcessOnKeyEventInternal(keyEventTwo);
    EXPECT_FALSE(ret);
    isChecked = pattern->IsChecked();
    EXPECT_EQ(isChecked, IS_ON);
    /**
     * @tc.steps: step4. test event.action != KeyAction::DOWN and event.code != KeyCode::KEY_FUNCTION
     * @tc.expected: step5. check the checked status
     */
    KeyEvent keyEventThree(KeyCode::KEY_F1, KeyAction::UP);
    ret = eventHub->ProcessOnKeyEventInternal(keyEventThree);
    EXPECT_FALSE(ret);
    isChecked = pattern->IsChecked();
    EXPECT_EQ(isChecked, IS_ON);
    /**
     * @tc.steps: step4. test event.action == KeyAction::DOWN and event.code == KeyCode::KEY_FUNCTION
     * @tc.expected: step5. check the checked status
     */
    KeyEvent keyEventFour(KeyCode::KEY_FUNCTION, KeyAction::DOWN);
    ret = eventHub->ProcessOnKeyEventInternal(keyEventFour);
    EXPECT_TRUE(ret);
    isChecked = pattern->IsChecked();
    EXPECT_EQ(isChecked, !IS_ON);
}

/**
 * @tc.name: SetSelectedColor001
 * @tc.desc: Test SetSelectedColor() for CheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, SetSelectedColor001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));
    /**
     * @tc.steps: step1. Create checkbox and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<CheckBoxPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    std::optional<Color> emptySelectedColor = std::optional<Color>();

    /**
     * @tc.steps: step2. Set valid selected color.
     * @tc.expected: The selected color flag should be true.
     */
    toggleModelNG.SetSelectedColor(frameNode, SELECTED_COLOR);
    EXPECT_TRUE(paintProperty->GetCheckBoxSelectedColorFlagByUserValue(false));

    /**
     * @tc.steps: step3. Set empty selected color.
     * @tc.expected: The selected color flag should still be true.
     */
    toggleModelNG.SetSelectedColor(frameNode, emptySelectedColor);
    EXPECT_TRUE(paintProperty->GetCheckBoxSelectedColorFlagByUserValue(false));

    /**
     * @tc.steps: step4. Set valid selected color with configuration change.
     * @tc.expected: The selected color flag should be true.
     */
    g_isConfigChangePerform = true;
    toggleModelNG.SetSelectedColor(frameNode, SELECTED_COLOR);
    EXPECT_TRUE(paintProperty->GetCheckBoxSelectedColorFlagByUserValue(false));

    /**
     * @tc.steps: step5. Set empty selected color with configuration change.
     * @tc.expected: The selected color flag should be false.
     */
    toggleModelNG.SetSelectedColor(frameNode, emptySelectedColor);
    EXPECT_FALSE(paintProperty->GetCheckBoxSelectedColorFlagByUserValue(true));
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetSelectedColor002
 * @tc.desc: Test SetSelectedColor() for Button.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, SetSelectedColor002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    /**
     * @tc.steps: step1. Create button and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    std::optional<Color> emptySelectedColor = std::optional<Color>();

    /**
     * @tc.steps: step2. Set valid selected color.
     * @tc.expected: The selected color flag should be true.
     */
    toggleModelNG.SetSelectedColor(frameNode, SELECTED_COLOR);
    EXPECT_TRUE(paintProperty->GetSelectedColorSetByUserValue(false));

    /**
     * @tc.steps: step3. Set empty selected color.
     * @tc.expected: The selected color flag should still be true.
     */
    toggleModelNG.SetSelectedColor(frameNode, emptySelectedColor);
    EXPECT_TRUE(paintProperty->GetSelectedColorSetByUserValue(false));

    /**
     * @tc.steps: step4. Set valid selected color with configuration change.
     * @tc.expected: The selected color flag should be true.
     */
    g_isConfigChangePerform = true;
    toggleModelNG.SetSelectedColor(frameNode, SELECTED_COLOR);
    EXPECT_TRUE(paintProperty->GetSelectedColorSetByUserValue(false));

    /**
     * @tc.steps: step5. Set empty selected color with configuration change.
     * @tc.expected: The selected color flag should be false.
     */
    toggleModelNG.SetSelectedColor(frameNode, emptySelectedColor);
    EXPECT_FALSE(paintProperty->GetSelectedColorSetByUserValue(true));
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: ColorTypeToStringTest001
 * @tc.desc: test ColorTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, ColorTypeToStringTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare test data pairs of ToggleColorType and expected string values.
     * @tc.expected: step1. Test data contains valid color type to string mappings.
     */
    std::vector<std::pair<ToggleColorType, std::string>> types = { { ToggleColorType::SELECTED_COLOR, "SelectedColor" },
        { ToggleColorType::SWITCH_POINT_COLOR, "SwitchPointColor" },
        { ToggleColorType::UN_SELECTED_COLOR, "UnselectedColor" }, { static_cast<ToggleColorType>(3), "Unknown" } };

    /**
     * @tc.steps: step2. Iterate through each test pair and call ColorTypeToString.
     * @tc.expected: step2. The function returns the expected string for each color type.
     */
    for (const auto& [type, val] : types) {
        auto ret = ToggleModelNG::ColorTypeToString(type);
        EXPECT_EQ(val, ret);
    }
}

/**
 * @tc.name: DimensionTypeToStringTest001
 * @tc.desc: test DimensionTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, DimensionTypeToStringTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare test data pairs of ToggleDimensionType and expected string values.
     * @tc.expected: step1. Test data contains valid dimension type to string mappings.
     */
    std::vector<std::pair<ToggleDimensionType, std::string>> types = {
        { ToggleDimensionType::POINT_RADIUS, "PointRadius" },
        { ToggleDimensionType::TRACK_BORDER_RADIUS, "TrackBorderRadius" },
        { static_cast<ToggleDimensionType>(2), "Unknown" } };

    /**
     * @tc.steps: step2. Iterate through each test pair and call DimensionTypeToString.
     * @tc.expected: step2. The function returns the expected string for each dimension type.
     */
    for (const auto& [type, val] : types) {
        auto ret = ToggleModelNG::DimensionTypeToString(type);
        EXPECT_EQ(val, ret);
    }
}

/**
 * @tc.name: SetCheckboxDefaultColorTest001
 * @tc.desc: test SetCheckboxDefaultColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, SetCheckboxDefaultColorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a toggle model and verify frame node and paint property setup.
     * @tc.expected: step1. Frame node and paint property are created and valid, selected color is not set initially.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto colorRet = paintProperty->GetSelectedColor();
    EXPECT_FALSE(colorRet.has_value());

    /**
     * @tc.steps: step2. Create a checkbox and mock theme manager to provide checkbox theme.
     * @tc.expected: step2. Checkbox theme is retrieved successfully from the mock manager.
     */
    ToggleModelNG toggleModelNG2;
    toggleModelNG2.Create(TOGGLE_TYPE[0], IS_ON);
    auto checkboxFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(checkboxFrameNode, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkboxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    ASSERT_NE(checkboxTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkboxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkboxTheme));
    auto color = checkboxTheme->GetActiveColor();

    /**
     * @tc.steps: step3. Test default color setting with invalid and valid color types.
     * @tc.expected: step3. Selected color is updated to theme's active color when valid type is used.
     */
    toggleModelNG.SetCheckboxDefaultColor(checkboxFrameNode, static_cast<ToggleColorType>(3));
    toggleModelNG.SetCheckboxDefaultColor(checkboxFrameNode, ToggleColorType::SELECTED_COLOR);
    colorRet = paintProperty->GetSelectedColor();
    EXPECT_EQ(colorRet.value_or(Color::BLACK), color);
}

/**
 * @tc.name: SetCheckboxDefaultColorTest002
 * @tc.desc: test SetCheckboxDefaultColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, SetCheckboxDefaultColorTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a toggle model and verify frame node and paint property setup.
     * @tc.expected: step1. Frame node and paint property are created and valid, selected color is not set initially.
     */
    ToggleModelNG toggleModelNG;
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto toggleNode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, 1, AceType::MakeRefPtr<ToggleButtonPattern>());
    EXPECT_NE(toggleNode, nullptr);
    auto pattern = AceType::DynamicCast<ToggleButtonPattern>(toggleNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    stack->Push(toggleNode);

    /**
     * @tc.steps: step2. Test default color setting for BACKGROUND_COLOR type.
     * @tc.expected: step2. Background color is reset and no longer has a valid value after setting default color.
     */
    paintProperty->UpdateBackgroundColor(Color::BLACK);
    EXPECT_TRUE(paintProperty->GetBackgroundColor().has_value());
    toggleModelNG.SetCheckboxDefaultColor(AceType::RawPtr(toggleNode), ToggleColorType::BACKGROUND_COLOR);
    EXPECT_FALSE(paintProperty->GetBackgroundColor().has_value());
}

/**
 * @tc.name: SetSwitchDefaultColorTest001
 * @tc.desc: test SetSwitchDefaultColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, SetSwitchDefaultColorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a toggle model and verify initial color properties are not set.
     * @tc.expected: step1. Frame node and paint property are valid, all color properties are initially unset.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto colorRet = paintProperty->GetUnselectedColor();
    EXPECT_FALSE(colorRet.has_value());
    colorRet = paintProperty->GetSwitchPointColor();
    EXPECT_FALSE(colorRet.has_value());
    colorRet = paintProperty->GetSelectedColor();
    EXPECT_FALSE(colorRet.has_value());

    /**
     * @tc.steps: step2. Mock theme manager to provide switch theme.
     * @tc.expected: step2. Mock theme manager returns valid switch theme instances.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    ASSERT_NE(switchTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SwitchTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SwitchTheme>()));

    /**
     * @tc.steps: step3. Test setting default colors for different color types.
     * @tc.expected: step3. Each color property is updated to the corresponding theme color when set.
     */
    toggleModelNG.SetSwitchDefaultColor(frameNode, static_cast<ToggleColorType>(3));
    auto color = switchTheme->GetActiveColor();
    toggleModelNG.SetSwitchDefaultColor(frameNode, ToggleColorType::SELECTED_COLOR);
    colorRet = paintProperty->GetSelectedColor();
    EXPECT_EQ(colorRet.value_or(Color::BLACK), color);
    color = switchTheme->GetPointColor();
    toggleModelNG.SetSwitchDefaultColor(frameNode, ToggleColorType::SWITCH_POINT_COLOR);
    colorRet = paintProperty->GetSwitchPointColor();
    EXPECT_EQ(colorRet.value_or(Color::BLACK), color);
    color = switchTheme->GetInactiveColor();
    toggleModelNG.SetSwitchDefaultColor(frameNode, ToggleColorType::UN_SELECTED_COLOR);
    colorRet = paintProperty->GetUnselectedColor();
    EXPECT_EQ(colorRet.value_or(Color::BLACK), color);

    auto toggleNode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, 1, AceType::MakeRefPtr<ToggleButtonPattern>());
    EXPECT_NE(toggleNode, nullptr);
    auto pattern = AceType::DynamicCast<ToggleButtonPattern>(toggleNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProp = pattern->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_NE(paintProp, nullptr);
    toggleModelNG.SetSwitchDefaultColor(AceType::RawPtr(toggleNode), ToggleColorType::BACKGROUND_COLOR);
    EXPECT_FALSE(paintProp->GetBackgroundColor().has_value());
}

/**
 * @tc.name: SetButtonDefaultColorTest001
 * @tc.desc: test SetButtonDefaultColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, SetButtonDefaultColorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a toggle model and verify initial selected color is not set.
     * @tc.expected: step1. Frame node and paint property are valid, selected color is initially unset.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto colorRet = paintProperty->GetSelectedColor();
    EXPECT_FALSE(colorRet.has_value());

    /**
     * @tc.steps: step2. Create a button toggle and mock theme manager to provide toggle theme.
     * @tc.expected: step2. Button frame node is valid and theme manager returns valid toggle theme.
     */
    ToggleModelNG toggleModelNG2;
    toggleModelNG2.Create(TOGGLE_TYPE[1], IS_ON);
    auto buttonFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonFrameNode, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ToggleTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    auto color = buttonTheme->GetCheckedColor();

    /**
     * @tc.steps: step3. Test setting default color with invalid and valid color types.
     * @tc.expected: step3. Selected color is updated to theme's checked color when valid type is used.
     */
    toggleModelNG.SetButtonDefaultColor(buttonFrameNode, static_cast<ToggleColorType>(3));
    toggleModelNG.SetButtonDefaultColor(buttonFrameNode, ToggleColorType::SELECTED_COLOR);
    colorRet = paintProperty->GetSelectedColor();
    EXPECT_EQ(colorRet.value_or(Color::BLACK), color);
}

/**
 * @tc.name: SetButtonDefaultColorTest002
 * @tc.desc: test SetButtonDefaultColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, SetButtonDefaultColorTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a toggle model and verify frame node and paint property setup.
     * @tc.expected: step1. Frame node and paint property are created and valid, selected color is not set initially.
     */
    ToggleModelNG toggleModelNG;
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto toggleNode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, 1, AceType::MakeRefPtr<ToggleButtonPattern>());
    EXPECT_NE(toggleNode, nullptr);
    auto pattern = AceType::DynamicCast<ToggleButtonPattern>(toggleNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    stack->Push(toggleNode);

    /**
     * @tc.steps: step2. Test default color setting for BACKGROUND_COLOR type.
     * @tc.expected: step2. Background color is reset and no longer has a valid value after setting default color.
     */
    paintProperty->UpdateBackgroundColor(Color::BLACK);
    EXPECT_TRUE(paintProperty->GetBackgroundColor().has_value());
    toggleModelNG.SetButtonDefaultColor(AceType::RawPtr(toggleNode), ToggleColorType::BACKGROUND_COLOR);
    EXPECT_FALSE(paintProperty->GetBackgroundColor().has_value());
}

/**
 * @tc.name: CreateWithSwitchResourceObj
 * @tc.desc: Test CreateWithSwitchResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, CreateWithSwitchResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a switch toggle and prepare resource objects.
     * @tc.expected: step1. Frame node is created and marked as modified.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. Attempt to create resource with null object and verify no resource is added.
     * @tc.expected: step2. Resource map does not contain the key after null resource creation.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    std::string key = "toggle" + toggleModelNG.ColorTypeToString(ToggleColorType::SELECTED_COLOR);
    toggleModelNG.CreateWithSwitchResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SELECTED_COLOR, nullptr, key);
    auto pattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 0);

    /**
     * @tc.steps: step3. Create resource with valid objects for different color types.
     * @tc.expected: step3. Resource map contains exactly one entry after valid resource creation.
     */
    ResourceObjectParams params { .value = "", .type = ResourceObjectParamType::NONE };
    RefPtr<ResourceObject> resObjWithParams =
        AceType::MakeRefPtr<ResourceObject>(-1, 10003, std::vector<ResourceObjectParams> { params }, "", "", 100000);
    toggleModelNG.CreateWithSwitchResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SELECTED_COLOR, resObj, key);
    toggleModelNG.CreateWithSwitchResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SWITCH_POINT_COLOR, resObjWithParams, key);
    toggleModelNG.CreateWithSwitchResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::UN_SELECTED_COLOR, resObjWithParams, key);
    toggleModelNG.CreateWithSwitchResourceObj(
        const_cast<FrameNode*>(switchFrameNode), static_cast<ToggleColorType>(3), resObjWithParams, key);
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: CreateWithCheckBoxResourceObj
 * @tc.desc: Test CreateWithCheckBoxResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, CreateWithCheckBoxResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a checkbox toggle and prepare resource objects.
     * @tc.expected: step1. Frame node is created and marked as modified.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. Attempt to create resource with null object and verify no resource is added.
     * @tc.expected: step2. Resource map does not contain the key after null resource creation.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    std::string key = "toggle" + toggleModelNG.ColorTypeToString(ToggleColorType::SELECTED_COLOR);
    toggleModelNG.CreateWithCheckBoxResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SELECTED_COLOR, nullptr, key);
    auto pattern = switchFrameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 0);

    /**
     * @tc.steps: step3. Create resource with valid objects for different color types.
     * @tc.expected: step3. Resource map contains exactly one entry after valid resource creation.
     */
    ResourceObjectParams params { .value = "", .type = ResourceObjectParamType::NONE };
    RefPtr<ResourceObject> resObjWithParams =
        AceType::MakeRefPtr<ResourceObject>(-1, 10003, std::vector<ResourceObjectParams> { params }, "", "", 100000);
    toggleModelNG.CreateWithCheckBoxResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SELECTED_COLOR, resObj, key);
    toggleModelNG.CreateWithCheckBoxResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SWITCH_POINT_COLOR, resObj, key);
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: CreateWithButtonResourceObj
 * @tc.desc: Test CreateWithButtonResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, CreateWithButtonResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a button toggle and prepare resource objects.
     * @tc.expected: step1. Frame node is created and marked as modified.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. Attempt to create resource with null object and verify no resource is added.
     * @tc.expected: step2. Resource map does not contain the key after null resource creation.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    std::string key = "toggle" + toggleModelNG.ColorTypeToString(ToggleColorType::SELECTED_COLOR);
    toggleModelNG.CreateWithButtonResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SELECTED_COLOR, nullptr, key);
    auto pattern = switchFrameNode->GetPattern<ToggleButtonPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 0);

    /**
     * @tc.steps: step3. Create resource with valid objects for different color types.
     * @tc.expected: step3. Resource map contains exactly one entry after valid resource creation.
     */
    ResourceObjectParams params { .value = "", .type = ResourceObjectParamType::NONE };
    RefPtr<ResourceObject> resObjWithParams =
        AceType::MakeRefPtr<ResourceObject>(-1, 10003, std::vector<ResourceObjectParams> { params }, "", "", 100000);
    toggleModelNG.CreateWithButtonResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SELECTED_COLOR, resObj, key);
    toggleModelNG.CreateWithButtonResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SWITCH_POINT_COLOR, resObj, key);
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: CreateWithDimensionVpResourceObj
 * @tc.desc: Test CreateWithDimensionVpResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleTestNg, CreateWithDimensionVpResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a switch toggle and prepare resource objects.
     * @tc.expected: step1. Frame node is created and marked as modified.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. Attempt to create resource with null object and verify no resource is added.
     * @tc.expected: step2. Resource map does not contain the key after null resource creation.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    std::string key = "toggle" + toggleModelNG.DimensionTypeToString(ToggleDimensionType::POINT_RADIUS);
    toggleModelNG.CreateWithDimensionVpResourceObj(nullptr, ToggleDimensionType::POINT_RADIUS);
    auto pattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 0);

    /**
     * @tc.steps: step3. Create resource with valid objects for different dimension types.
     * @tc.expected: step3. Resource map contains exactly one entry after valid resource creation.
     */
    ResourceObjectParams params { .value = "", .type = ResourceObjectParamType::NONE };
    RefPtr<ResourceObject> resObjWithParams =
        AceType::MakeRefPtr<ResourceObject>(-1, 10003, std::vector<ResourceObjectParams> { params }, "", "", 100000);
    toggleModelNG.CreateWithDimensionVpResourceObj(resObjWithParams, ToggleDimensionType::POINT_RADIUS);
    toggleModelNG.CreateWithDimensionVpResourceObj(resObjWithParams, ToggleDimensionType::TRACK_BORDER_RADIUS);
    toggleModelNG.CreateWithDimensionVpResourceObj(resObjWithParams, static_cast<ToggleDimensionType>(2));
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
}
} // namespace OHOS::Ace::NG
