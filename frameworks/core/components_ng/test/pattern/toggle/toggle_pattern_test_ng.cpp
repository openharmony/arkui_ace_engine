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

#include <cstddef>
#include <optional>
#include <vector>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#define protected public
#define private public
#include "base/geometry/dimension.h"
#include "core/components/checkable/checkable_theme.h"
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
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/rosen/testing_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

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

class TogglePatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static PaddingPropertyF CreatePadding(Dimension length);
};

void TogglePatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void TogglePatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

PaddingPropertyF TogglePatternTestNg::CreatePadding(Dimension length)
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
HWTEST_F(TogglePatternTestNg, TogglePatternTest001, TestSize.Level1)
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
HWTEST_F(TogglePatternTestNg, TogglePatternTest002, TestSize.Level1)
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
HWTEST_F(TogglePatternTestNg, TogglePatternTest003, TestSize.Level1)
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
HWTEST_F(TogglePatternTestNg, TogglePatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);
    toggleModelNG.SetWidth(TOGGLE_WIDTH);
    toggleModelNG.SetHeight(TOGGLE_HEIGH);
    toggleModelNG.SetBackgroundColor(BACKGROUND_COLOR);
    auto padding = CreatePadding(ZERO);
    toggleModelNG.SetPadding(padding);
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
HWTEST_F(TogglePatternTestNg, TogglePatternTest005, TestSize.Level1)
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
    auto eventHub = checkBoxFrameNode->GetEventHub<CheckBoxEventHub>();
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
HWTEST_F(TogglePatternTestNg, TogglePatternTest006, TestSize.Level1)
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
    auto eventHub = buttonFrameNode->GetEventHub<ToggleButtonEventHub>();
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
HWTEST_F(TogglePatternTestNg, TogglePatternTest007, TestSize.Level1)
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
    auto eventHub = switchFrameNode->GetEventHub<SwitchEventHub>();
    EXPECT_NE(eventHub, nullptr);
    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(stateChange, true);
}

/**
 * @tc.name: TogglePatternTest008
 * @tc.desc: Test toggle OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TogglePatternTestNg, TogglePatternTest008, TestSize.Level1)
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
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SwitchTheme>()));
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
}

/**
 * @tc.name: TogglePatternTest009
 * @tc.desc: Test toggle OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(TogglePatternTestNg, TogglePatternTest009, TestSize.Level1)
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
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(switchFrameNode, geometryNode, layoutProperty);
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
}

/**
 * @tc.name: TogglePatternTest0010
 * @tc.desc: Test toggle OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(TogglePatternTestNg, TogglePatternTest0010, TestSize.Level1)
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
    auto hub = switchPattern->GetEventHub<EventHub>();
    EXPECT_NE(hub, nullptr);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureHub, nullptr);
    RefPtr<PanEvent> panEvent = AceType::MakeRefPtr<PanEvent>(nullptr, nullptr, nullptr, nullptr);
    switchPattern->panEvent_ = panEvent;
    switchPattern->InitPanEvent(gestureHub);

    RefPtr<ClickEvent> clickEvent = AceType::MakeRefPtr<ClickEvent>(nullptr);
    switchPattern->clickListener_ = clickEvent;
    switchPattern->InitClickEvent();

    RefPtr<TouchEventImpl> touchEvent = AceType::MakeRefPtr<TouchEventImpl>(nullptr);
    switchPattern->touchListener_ = touchEvent;
    switchPattern->InitTouchEvent();

    // std::move(mouseTask)
    auto mouseTask = [](bool isHover) {};
    RefPtr<InputEvent> inputEvent = AceType::MakeRefPtr<InputEvent>(std::move(mouseTask));
    switchPattern->mouseEvent_ = inputEvent;
    switchPattern->InitMouseEvent();

    switchPattern->isOn_ = true;
    switchPattern->OnClick();
    switchPattern->OnTouchDown();
    switchPattern->OnTouchUp();
    switchPattern->UpdateChangeEvent();

    // execute Handle function
    switchPattern->HandleMouseEvent(true);
    GestureEvent info;
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
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(switchFrameNode, geometryNode, layoutProperty);
    EXPECT_NE(layoutWrapper, nullptr);
    auto switchLayoutAlgorithm = AceType::MakeRefPtr<SwitchLayoutAlgorithm>();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm, SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    EXPECT_EQ(geometryNode->GetContentSize().Width(), 20);
    switchPattern->HandleDragEnd();
    switchPattern->isOn_ = true;
    switchPattern->HandleDragEnd();
}

/**
 * @tc.name: ToggleLayoutTest001
 * @tc.desc: Test toggle layout.
 * @tc.type: FUNC
 */
HWTEST_F(TogglePatternTestNg, ToggleLayoutTest001, TestSize.Level1)
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
    LayoutWrapper layoutWrapper = LayoutWrapper(switchFrameNode, geometryNode, switchFrameNode->GetLayoutProperty());
    auto switchLayoutAlgorithm = AceType::DynamicCast<SwitchLayoutAlgorithm>(switchPattern->CreateLayoutAlgorithm());
    EXPECT_NE(switchLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);

    // update switchTheme values
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGH;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

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
 * @tc.desc: Test toggle GetContentDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(TogglePatternTestNg, TogglePaintTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(1, true, true, true);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    RefPtr<RenderContext> renderContext;
    auto switchPaintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    EXPECT_NE(switchPaintProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, switchPaintProperty);
    EXPECT_NE(paintWrapper, nullptr);
    switchPaintMethod.GetContentDrawFunction(paintWrapper);
}

/**
 * @tc.name: TogglePaintTest001
 * @tc.desc: Test toggle GetContentDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(TogglePatternTestNg, TogglePaintTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(1, true, true, true);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    RefPtr<RenderContext> renderContext;
    auto switchPaintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    EXPECT_NE(switchPaintProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, switchPaintProperty);
    EXPECT_NE(paintWrapper, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGH;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(9);
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(3);

    auto contentSize = SizeF(100, 50);
    auto contentOffset = OffsetF(0, 0);
    switchPaintMethod.PaintContent(rsCanvas, switchPaintProperty, contentSize, contentOffset);
    switchPaintMethod.enabled_ = false;
    switchPaintMethod.PaintContent(rsCanvas, switchPaintProperty, contentSize, contentOffset);

    // update switchPaintMethod member value
    switchPaintMethod.isTouch_ = false;
    switchPaintMethod.isHover_ = false;
    switchPaintMethod.mainDelta_ = 0;
    switchPaintMethod.PaintContent(rsCanvas, switchPaintProperty, contentSize, contentOffset);
}
} // namespace OHOS::Ace::NG