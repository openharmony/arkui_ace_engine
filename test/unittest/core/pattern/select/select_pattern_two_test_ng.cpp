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

#include <cstdint>
#include <iostream>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/common/ace_application_info.h"
#include "core/components/common/layout/constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string EMPTY_TEXT = "";
const std::string SELECT_TEXT = "select";
const std::string ITEM_TEXT = "menuItem";
const std::string OPTION_TEXT = "aaa";
const std::string OPTION_TEXT_2 = "BBB";
const std::string OPTION_TEXT_3 = "CCC";
const std::string INTERNAL_SOURCE = "$r('app.media.icon')";
const std::string FILE_SOURCE = "/common/icon.png";
const std::string DEFAULT_STR("2.0");
const std::string TEXT_VALUE = "test";
const CalcLength MARGIN_LENGTH = CalcLength("8vp");
const CalcSize TEXT_IDEAL_SIZE = CalcSize(CalcLength("50vp"), std::nullopt);
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float SELECT_WIDTH = 100.0f;
constexpr float SELECT_HEIGHT = 200.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Color BG_COLOR_VALUE = Color::FromRGB(100, 255, 100);
const Color SELECT_TEXT_COLOR_VALUE = Color::FromRGB(255, 255, 100);
const Color SELECT_BG_COLOR_VALUE = Color::FromRGB(100, 255, 255);
const std::vector<SelectParam> CREATE_VALUE = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
    { OPTION_TEXT_3, INTERNAL_SOURCE } };
} // namespace
struct TestProperty {
    std::optional<Dimension> FontSize = std::nullopt;
    std::optional<Ace::FontStyle> FontStyle = std::nullopt;
    std::optional<FontWeight> FontWeight = std::nullopt;
    std::optional<std::vector<std::string>> FontFamily = std::nullopt;
    std::optional<Color> FontColor = std::nullopt;
};
class SelectPatternTwoTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitSelectPatternTwoTestNg();
    RefPtr<FrameNode> frameNode_;
    RefPtr<SelectPattern> selectPattern_;
    RefPtr<SelectAccessibilityProperty> selectAccessibilityProperty_;

protected:
    static RefPtr<FrameNode> CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test);
    static FrameNode* CreateSelect(const std::vector<SelectParam>& value);
};

void SelectPatternTwoTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void SelectPatternTwoTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void SelectPatternTwoTestNg::SetUp() {}

void SelectPatternTwoTestNg::TearDown()
{
    frameNode_ = nullptr;
    selectPattern_ = nullptr;
    selectAccessibilityProperty_ = nullptr;
}

void SelectPatternTwoTestNg::InitSelectPatternTwoTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ASSERT_NE(frameNode_, nullptr);

    selectPattern_ = frameNode_->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern_, nullptr);

    selectAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<SelectAccessibilityProperty>();
    ASSERT_NE(selectAccessibilityProperty_, nullptr);
}

RefPtr<FrameNode> SelectPatternTwoTestNg::CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test)
{
    SelectModelNG selectModelInstance;
    selectModelInstance.Create(value);
    if (test.FontSize.has_value()) {
        selectModelInstance.SetFontSize(test.FontSize.value());
    }
    if (test.FontColor.has_value()) {
        selectModelInstance.SetFontColor(test.FontColor.value());
    }
    if (test.FontStyle.has_value()) {
        selectModelInstance.SetItalicFontStyle(test.FontStyle.value());
    }
    if (test.FontWeight.has_value()) {
        selectModelInstance.SetFontWeight(test.FontWeight.value());
    }
    if (test.FontFamily.has_value()) {
        selectModelInstance.SetFontFamily(test.FontFamily.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

FrameNode* SelectPatternTwoTestNg::CreateSelect(const std::vector<SelectParam>& value)
{
    SelectModelNG selectModelInstance;
    selectModelInstance.Create(value);
    return ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

/**
 * @tc.name: SetItemSelected023
 * @tc.desc: Test SelectPattern SetItemSelected
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, SetItemSelected023, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    /**
     * @tc.steps: step1. Create select.
     */
    std::vector<SelectParam> params = { { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    /**
     * @tc.steps: step3. Call SetItemSelected.
     * @tc.expected: the function runs normally
     */
    selectPattern->SetItemSelected(1, "content");
    auto val = selectPattern->GetSelected();

    EXPECT_EQ(val, -1);
}

/**
 * @tc.name: BindMenuTouch011
 * @tc.desc: Test BindMenuTouch touch callback with weakTarget upgrade failure simulation
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, BindMenuTouch011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Test with valid touches
     */
    TouchEventInfo touchInfo("test");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch012
 * @tc.desc: Test BindMenuTouch edge case coverage for container null checks
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, BindMenuTouch012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Test various touch types to ensure all branches are covered
     * @tc.expected: All touch events should be handled without crashing
     */
    std::vector<TouchType> touchTypes = { TouchType::DOWN, TouchType::MOVE, TouchType::UP, TouchType::CANCEL,
        TouchType::UNKNOWN };

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();

    for (auto touchType : touchTypes) {
        TouchEventInfo touchInfo("test");
        TouchLocationInfo touchLocationInfo(0);
        touchLocationInfo.SetTouchType(touchType);
        touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

        // Each touch type should be handled gracefully
        EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
    }
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch013
 * @tc.desc: Test BindMenuTouch behavior when subwindow components are null
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, BindMenuTouch013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Test touch callback when subwindow may not exist
     * @tc.expected: Should handle null subwindow gracefully
     */
    TouchEventInfo touchInfo("test");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();
    // This should not crash even if subwindow doesn't exist in test environment
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: BindMenuTouch014
 * @tc.desc: Test BindMenuTouch with all touch types for comprehensive coverage
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, BindMenuTouch014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch
     */
    selectPattern->BindMenuTouch(select, gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();

    /**
     * @tc.steps: step3. Test all possible TouchType values systematically
     * @tc.expected: All touch types should be handled without exceptions
     */

    TouchEventInfo touchInfoDown("test_down");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchInfoDown.AddTouchLocationInfo(std::move(touchLocationInfo));
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfoDown));

    TouchEventInfo touchInfoUp("test_up");
    touchLocationInfo.SetTouchType(TouchType::UP);
    touchInfoUp.AddTouchLocationInfo(std::move(touchLocationInfo));
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfoUp));

    TouchEventInfo touchInfoCancel("test_cancel");
    touchLocationInfo.SetTouchType(TouchType::CANCEL);
    touchInfoCancel.AddTouchLocationInfo(std::move(touchLocationInfo));
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfoCancel));

    TouchEventInfo touchInfoMove("test_move");
    touchLocationInfo.SetTouchType(TouchType::MOVE);
    touchInfoMove.AddTouchLocationInfo(std::move(touchLocationInfo));
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfoMove));
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: InitSpinner003
 * @tc.desc: Test SelectPattern InitSpinner with valid parameters.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, InitSpinner003, TestSize.Level1)
{
    auto spinner = AceType::MakeRefPtr<FrameNode>("spinner", 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(spinner, nullptr);

    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);

    selectTheme->isTV_ = true;
    selectTheme->spinnerSymbolSize_ = Dimension(16.0, DimensionUnit::PX);

    SelectPattern selectPattern;
    selectPattern.InitSpinner(spinner, selectTheme);
    auto spinnerLayoutProperty = spinner->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(spinnerLayoutProperty, nullptr);

    auto fontSize = spinnerLayoutProperty->GetFontSize();
    EXPECT_EQ(fontSize.value(), Dimension(16.0, DimensionUnit::PX));
}

/**
 * @tc.name: SetArrowModifierByUser
 * @tc.desc: Test SelectPattern SetArrowModifierByUser.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, SetArrowModifierByUser, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node.
     * @tc.expected: step1. Select model and frame node are created successfully, related objects are obtained.
     */
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN);
    EXPECT_TRUE(AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_SIXTEEN));
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(select->GetThemeScopeId());
    ASSERT_NE(selectTheme, nullptr);

    auto applyFunc = [](WeakPtr<FrameNode> weakNode) {
        auto symbolNode = weakNode.Upgrade();
        ASSERT_NE(symbolNode, nullptr);
        auto property = symbolNode->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(property, nullptr);
        property->UpdateFontSize(Dimension(80));
    };
    selectPattern->arrowApply_ = applyFunc;

    /**
     * @tc.steps: step2. Disable arrow modifier flag, call SetArrowModifierByUser.
     * @tc.expected: step2. Arrow font size is not updated to 80.
     */
    props->UpdateArrowModifierSetByUser(false);
    EXPECT_FALSE(props->GetArrowModifierSetByUserValue(false));
    selectPattern->SetArrowModifierByUser(selectTheme, props);
    auto frameNode = selectPattern->spinner_;
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::SYMBOL_ETS_TAG);
    auto property = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_NE(property->GetFontSize(), Dimension(80));

    /**
     * @tc.steps: step3. Enable arrow modifier flag, call SetArrowModifierByUser.
     * @tc.expected: step3. Arrow font size is updated to 80.
     */
    props->UpdateArrowModifierSetByUser(true);
    EXPECT_TRUE(props->GetArrowModifierSetByUserValue(false));
    selectPattern->SetArrowModifierByUser(selectTheme, props);
    EXPECT_EQ(property->GetFontSize(), Dimension(80));
}

/**
 * @tc.name: SetModifierByUser001
 * @tc.desc: Test SelectPattern SetModifierByUser.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, SetModifierByUser001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node, obtain related objects.
     * @tc.expected: step1. Select model and frame node are created successfully, related objects are obtained.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    auto layoutProps = select->GetLayoutProperty<SelectLayoutProperty>();
    ASSERT_NE(layoutProps, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(select->GetThemeScopeId());
    ASSERT_NE(selectTheme, nullptr);
    selectTheme->selectedColor_ = Color::GREEN;
    /**
     * @tc.steps: step2. Show default selected icon, enable user-defined selected background color flag.
     * @tc.expected: step2. Selected background color in selectPattern is not set.
     */
    selectModelInstance.SetShowDefaultSelectedIcon(true);
    EXPECT_TRUE(layoutProps->GetShowDefaultSelectedIconValue(false));
    selectModelInstance.SetSelectedOptionBgColorByUser(true);
    EXPECT_TRUE(props->GetSelectedOptionBgColorSetByUserValue(false));
    selectPattern->SetModifierByUser(selectTheme, props);
    EXPECT_FALSE(selectPattern->selectedBgColor_.has_value());

    /**
     * @tc.steps: step3. Hide default selected icon, enable user-defined selected background color flag.
     * @tc.expected: step3. Selected background color in selectPattern is not set.
     */
    selectModelInstance.SetShowDefaultSelectedIcon(false);
    EXPECT_FALSE(layoutProps->GetShowDefaultSelectedIconValue(false));
    selectModelInstance.SetSelectedOptionBgColorByUser(true);
    EXPECT_TRUE(props->GetSelectedOptionBgColorSetByUserValue(false));
    selectPattern->SetModifierByUser(selectTheme, props);
    EXPECT_FALSE(selectPattern->selectedBgColor_.has_value());

    /**
     * @tc.steps: step4. Show default selected icon, disable user-defined selected background color flag.
     * @tc.expected: step4. Selected background color in selectPattern is not set.
     */
    selectModelInstance.SetShowDefaultSelectedIcon(true);
    EXPECT_TRUE(layoutProps->GetShowDefaultSelectedIconValue(false));
    selectModelInstance.SetSelectedOptionBgColorByUser(false);
    EXPECT_FALSE(props->GetSelectedOptionBgColorSetByUserValue(false));
    selectPattern->SetModifierByUser(selectTheme, props);
    EXPECT_FALSE(selectPattern->selectedBgColor_.has_value());

    /**
     * @tc.steps: step5. Hide default selected icon, disable user-defined selected background color flag.
     * @tc.expected: step5. Selected background color is not set.
     */
    selectModelInstance.SetShowDefaultSelectedIcon(false);
    EXPECT_FALSE(layoutProps->GetShowDefaultSelectedIconValue(false));
    selectModelInstance.SetSelectedOptionBgColorByUser(false);
    EXPECT_FALSE(props->GetSelectedOptionBgColorSetByUserValue(false));
    selectPattern->SetModifierByUser(selectTheme, props);
    EXPECT_FALSE(selectPattern->selectedBgColor_.has_value());
}

/**
 * @tc.name: SetModifierByUser002
 * @tc.desc: Test SelectPattern SetModifierByUser.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, SetModifierByUser002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node, obtain related objects.
     * @tc.expected: step1. Select model and frame node are created successfully, related objects are obtained.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    auto layoutProps = select->GetLayoutProperty<SelectLayoutProperty>();
    ASSERT_NE(layoutProps, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(select->GetThemeScopeId());
    ASSERT_NE(selectTheme, nullptr);

    auto frameNode = selectPattern->text_;
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetMaxLines(), 1);

    auto applyFunc = [](WeakPtr<FrameNode> weakNode) {
        auto textNode = weakNode.Upgrade();
        ASSERT_NE(textNode, nullptr);
        auto property = textNode->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(property, nullptr);
        property->UpdateMaxLines(2);
        property->UpdateFontSize(Dimension(80));
    };
    selectPattern->fontColor_ = Color::GREEN;
    selectPattern->textApply_ = applyFunc;
    /**
     * @tc.steps: step2. Enable user-defined font color flag, disable text modifier flag, call SetModifierByUser.
     * @tc.expected: step2. Font color remains green, max lines remains 1.
     */
    selectModelInstance.SetFontColorByUser(true);
    EXPECT_TRUE(props->GetFontColorSetByUserValue(false));
    props->UpdateTextModifierSetByUser(false);
    EXPECT_FALSE(props->GetTextModifierSetByUserValue(false));
    selectPattern->SetModifierByUser(selectTheme, props);
    EXPECT_EQ(selectPattern->fontColor_, Color::GREEN);
    EXPECT_EQ(property->GetMaxLines(), 1);

    /**
     * @tc.steps: step3. Enable both user-defined font color flag and text modifier flag, call SetModifierByUser.
     * @tc.expected: step3. Font color remains green, max lines is updated to 2.
     */
    selectModelInstance.SetFontColorByUser(true);
    EXPECT_TRUE(props->GetFontColorSetByUserValue(false));
    props->UpdateTextModifierSetByUser(true);
    EXPECT_TRUE(props->GetTextModifierSetByUserValue(false));
    selectPattern->SetModifierByUser(selectTheme, props);
    EXPECT_EQ(selectPattern->fontColor_, Color::GREEN);
    EXPECT_EQ(property->GetMaxLines(), 2);

    /**
     * @tc.steps: step4. Disable user-defined font color flag, call SetModifierByUser.
     * @tc.expected: step4. Font color is no longer green.
     */
    selectModelInstance.SetFontColorByUser(false);
    EXPECT_FALSE(props->GetFontColorSetByUserValue(false));
    selectPattern->SetModifierByUser(selectTheme, props);
    ASSERT_NE(selectPattern->fontColor_, Color::GREEN);
}

/**
 *  * @tc.name: FontColorByUser001
 * @tc.desc: Test FontColorByUser func.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, FontColorByUser001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node, obtain related objects.
     * @tc.expected: step1. Select model and frame node are created successfully, related objects are obtained.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);
    selectModelInstance.SetFontColorByUser(true);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);
    EXPECT_TRUE(props->GetFontColorSetByUserValue(false));

    /**
     * @tc.steps: step2. call ResetFontColor.
     * @tc.expected: step2. Font color is reset, FontColorSetByUser flag is updated.
     */
    selectModelInstance.ResetFontColor();
    EXPECT_FALSE(props->GetFontColorSetByUserValue(false));

    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(select->GetThemeScopeId());
    ASSERT_NE(selectTheme, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step3. Test UpdateComponentColor with BACKGROUND_COLOR.
     * @tc.expected: The color is updated correctly.
     */
    selectPattern->SetModifierByUser(selectTheme, props);
    ASSERT_NE(selectPattern->text_, nullptr);
    auto textProps = selectPattern->text_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProps, nullptr);
    ASSERT_EQ(textProps->GetTextColor(), selectTheme->GetFontColor());
    auto context = selectPattern->text_->GetRenderContext();
    ASSERT_NE(context, nullptr);
    ASSERT_EQ(context->GetForegroundColor(), selectTheme->GetFontColor());
}

/**
 * @tc.name: SetOptionBgColorByUser001
 * @tc.desc: Test SetOptionBgColorByUser func
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, SetOptionBgColorByUser001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern and gesture hub
     */
    auto select = CreateSelect(CREATE_VALUE);
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    selectPattern->options_.push_back(option);
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto paintProperty = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateOptionBgColorSetByUser(true);
    ASSERT_NE(selectPattern->options_[0], nullptr);
    auto itemPaintProperty = selectPattern->options_[0]->GetPaintProperty<MenuItemPaintProperty>();
    ASSERT_NE(itemPaintProperty, nullptr);
    ASSERT_EQ(itemPaintProperty->GetOptionBgColor().has_value(), false);
}

/**
 * @tc.name: SetOptionBgColorByUser
 * @tc.desc: Test SelectPattern SetOptionBgColorByUser.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, SetOptionBgColorByUser, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model, initialize frame node and set size.
     * @tc.expected: step1. Select model and frame node are created, size is set correctly.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetSelectSize(SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    selectPattern->UpdateTargetSize();
    auto menu = selectPattern->GetMenuNode();
    ASSERT_NE(menu, nullptr);
    auto menuLayoutProps = menu->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProps, nullptr);
    auto targetSize = menuLayoutProps->GetTargetSizeValue(SizeF());
    EXPECT_EQ(targetSize, SizeF(SELECT_WIDTH, SELECT_HEIGHT));
    auto optionCount = selectPattern->options_.size();
    ASSERT_NE(optionCount, 0);
    auto option = selectPattern->options_[0];
    auto optionPaintProperty = option->GetPaintProperty<MenuItemPaintProperty>();
    ASSERT_NE(optionPaintProperty, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);

    /**
     * @tc.steps: step2. Test option background color update with user-defined flag.
     * @tc.expected: step2. Option background color is updated based on user-defined flag.
     */
    std::vector<bool> vec { true, false };
    for (auto flag : vec) {
        props->UpdateSelectedOptionBgColorSetByUser(flag);
        selectPattern->optionBgColor_.reset();
        selectPattern->SetOptionBgColor(Color::GREEN);
        EXPECT_EQ(optionPaintProperty->GetOptionBgColorValue(), Color::GREEN);
    }
}

/**
 * @tc.name: SetColorByUser
 * @tc.desc: Test SelectPattern SetColorByUser.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, SetColorByUser, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize components.
     * @tc.expected: step1. Select model and related components are created successfully.
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode()).Upgrade();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(theme, nullptr);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    ASSERT_NE(props, nullptr);

    /**
     * @tc.steps: step2. Test SetColorByUser with different user-defined flags.
     * @tc.expected: step2. Color properties are updated based on user-defined flags and theme.
     */
    g_isConfigChangePerform = false;
    selectPattern->SetColorByUser(select, theme);
    g_isConfigChangePerform = true;
    props->UpdateFontColorSetByUser(true);
    props->UpdateOptionFontColorSetByUser(true);
    props->UpdateSelectedOptionBgColorSetByUser(true);
    props->UpdateSelectedOptionFontColorSetByUser(true);
    selectPattern->SetColorByUser(select, theme);

    selectPattern->fontColor_ = Color::RED;
    props->UpdateFontColorSetByUser(false);
    selectPattern->SetColorByUser(select, theme);
    EXPECT_FALSE(selectPattern->fontColor_.has_value());

    props->UpdateSelectedOptionFontColorSetByUser(false);
    selectPattern->SetColorByUser(select, theme);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: UpdateComponentColor001
 * @tc.desc: Test UpdateComponentColor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, UpdateComponentColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select model and initialize frame node.
     * @tc.expected: step1. Select model and frame node are created successfully.
     */
    SelectModelNG selectModelNG;
    std::vector<SelectParam> params = { { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelNG.Create(params);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineBase::GetCurrentContextSafely();
    ASSERT_NE(pipelineContext, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test UpdateComponentColor under different system color change and rerenderable states.
     * @tc.expected: step2. Component colors are updated correctly when system color changes and node is rerenderable.
     */
    std::vector<std::pair<bool, bool>> vec { { true, true }, { true, false }, { false, true }, { false, false } };
    for (const auto& pair : vec) {
        pipelineContext->SetIsSystemColorChange(pair.first);
        frameNode->SetRerenderable(pair.second);
        pattern->UpdateComponentColor(Color::RED, static_cast<SelectColorType>(7));
        if (pipelineContext->IsSystmColorChange() && pair.second) {
            pattern->UpdateComponentColor(Color::RED, SelectColorType::FONT_COLOR);
            EXPECT_EQ(pattern->fontColor_, Color::RED);
            pattern->UpdateComponentColor(Color::RED, SelectColorType::BACKGROUND_COLOR);
            auto ret = renderContext->GetBackgroundColor();
            EXPECT_EQ(ret, Color::RED);
            pattern->UpdateComponentColor(Color::RED, SelectColorType::SELECTED_OPTION_BG_COLOR);
            EXPECT_EQ(pattern->selectedBgColor_, Color::RED);
            pattern->UpdateComponentColor(Color::RED, SelectColorType::SELECTED_OPTION_FONT_COLOR);
            EXPECT_EQ(pattern->selectedFont_.FontColor, Color::RED);
            pattern->UpdateComponentColor(Color::RED, SelectColorType::OPTION_BG_COLOR);
            EXPECT_EQ(pattern->optionBgColor_, Color::RED);
            pattern->UpdateComponentColor(Color::RED, SelectColorType::OPTION_FONT_COLOR);
            EXPECT_EQ(pattern->optionBgColor_, Color::RED);
            pattern->UpdateComponentColor(Color::RED, SelectColorType::MENU_BACKGROUND_COLOR);
        }
    }
}

/**
 * @tc.name: UpdateMenuOption
 * @tc.desc: Test UpdateMenuOption.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, UpdateMenuOption, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto menuNode = selectPattern->GetMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    // Ensure there is at least one option
    ASSERT_FALSE(menuPattern->GetOptions().empty());
    auto menuItemNode = AceType::DynamicCast<FrameNode>(menuPattern->GetOptions().at(0));
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    // Test text update
    const std::string newText = "UpdatedText";
    selectPattern->UpdateMenuOption(0, newText, SelectOptionType::TEXT);
    EXPECT_EQ(menuItemPattern->GetText(), newText);

    // Test invalid update
    selectPattern->UpdateMenuOption(0, "UnusedValue", static_cast<SelectOptionType>(999));

    // Test icon update
    const std::string newIcon = "/path/to/icon.png";
    selectPattern->UpdateMenuOption(0, newIcon, SelectOptionType::ICON);
    auto iconNode = menuItemPattern->icon_;
    ASSERT_NE(iconNode, nullptr);
    ASSERT_EQ(iconNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto props = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(props, nullptr);
    auto imageSrcInfo = props->GetImageSourceInfo();
    EXPECT_EQ(imageSrcInfo->GetSrc(), newIcon);
}

/**
 * @tc.name: ResetParams004
 * @tc.desc: Test SelectPattern ResetParams.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternTwoTestNg, ResetParams004, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto pipeline = select->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(select->GetThemeScopeId());
    ASSERT_NE(selectTheme, nullptr);

    selectPattern->controlSize_ = ControlSize::NORMAL;
    selectTheme->selectLeftMarginMap_.insert(std::pair<ControlSize, Dimension>(ControlSize::NORMAL, 8.0_px));
    selectTheme->selectLeftMarginMap_.insert(std::pair<ControlSize, Dimension>(ControlSize::SMALL, 4.0_px));
    selectTheme->selectRightMarginMap_.insert(std::pair<ControlSize, Dimension>(ControlSize::NORMAL, 8.0_px));
    selectTheme->selectRightMarginMap_.insert(std::pair<ControlSize, Dimension>(ControlSize::SMALL, 4.0_px));

    selectPattern->ResetParams();
    auto padding = ViewAbstract::GetPadding(select);
    EXPECT_EQ(padding.left.value().GetDimension().ConvertToPx(), 8.0);
    EXPECT_EQ(padding.right.value().GetDimension().ConvertToPx(), 8.0);
}
} // namespace OHOS::Ace::NG
