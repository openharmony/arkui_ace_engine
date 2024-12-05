/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/checkbox/checkbox_event_hub.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_MARK_NAME = "mark";
    const auto ATTRIBUTE_SELECT_NAME = "select";
    const auto ATTRIBUTE_GROUP_NAME = "group";
    const auto ATTRIBUTE_GROUP_TEST_VALUE = "group 1";
    const auto ATTRIBUTE_GROUP_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_NAME_NAME = "name";
    const auto ATTRIBUTE_NAME_TEST_VALUE = "name 1";
    const auto ATTRIBUTE_NAME_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_SELECT_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_SELECTED_COLOR_NAME = "selectedColor";
    const auto ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE = "#FF007DFF";
    const auto ATTRIBUTE_SELECTED_COLOR_INVALID_VALUE = "#00000000";
    const auto ATTRIBUTE_SHAPE_NAME = "shape";
    const auto ATTRIBUTE_SHAPE_DEFAULT_VALUE = "0";
    const auto ATTRIBUTE_UNSELECTED_COLOR_NAME = "unselectedColor";
    const auto ATTRIBUTE_UNSELECTED_COLOR_DEFAULT_VALUE = "#FF000000";
    const auto ATTRIBUTE_UNSELECTED_COLOR_INVALID_VALUE = "#00000000";
    const auto ATTRIBUTE_MARK_STROKE_COLOR_NAME = "strokeColor";
    const auto ATTRIBUTE_MARK_STROKE_COLOR_DEFAULT_VALUE = "#FF000000";
    const auto ATTRIBUTE_MARK_STROKE_COLOR_TEST_VALUE = "#FF123456";
    const auto ATTRIBUTE_MARK_SIZE_NAME = "size";
    const auto ATTRIBUTE_MARK_SIZE_DEFAULT_VALUE = "0.00vp";
    const auto ATTRIBUTE_MARK_SIZE_TEST_VALUE = "111.00px";
    const auto ATTRIBUTE_MARK_STROKE_WIDTH_NAME = "strokeWidth";
    const auto ATTRIBUTE_MARK_STROKE_WIDTH_DEFAULT_VALUE = "0.00px";
    const auto ATTRIBUTE_MARK_STROKE_WIDTH_TEST_VALUE = "222.00px";
    static constexpr int SIZE1 = 111;
    static constexpr int SIZE2 = 222;

    struct EventsTracker {
    static inline GENERATED_ArkUICheckboxEventsReceiver checkboxEventReceiver {};

    static inline const GENERATED_ArkUIEventsAPI eventsApiImpl {
        .getCheckboxEventsReceiver = [] () -> const GENERATED_ArkUICheckboxEventsReceiver* {
            return &checkboxEventReceiver;
        }
    };
}; // EventsTracker

} // namespace

class CheckboxModifierTest : public ModifierTestBase<GENERATED_ArkUICheckboxModifier,
    &GENERATED_ArkUINodeModifiers::getCheckboxModifier, GENERATED_ARKUI_CHECKBOX> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<CheckboxTheme>();

        // setup the test event handler
        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};

/**
 * @tc.name: setCheckboxOnChangeTest
 * @tc.desc: Test Checkbox setOnChange event.
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, DISABLED_setChackboxOnChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxEventHub = frameNode->GetEventHub<CheckBoxEventHub>();
    ASSERT_NE(checkBoxEventHub, nullptr);

    struct CheckEvent {
        bool value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::checkboxEventReceiver.onChange = [](Ark_Int32 nodeId, const Ark_Boolean value) {
        checkEvent = {
           .value = value,
        };
    };

    modifier_->setOnChange(node_, {});

    EXPECT_EQ(checkEvent.has_value(), false);
    checkBoxEventHub->UpdateChangeEvent(false);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->value, false);
    checkBoxEventHub->UpdateChangeEvent(true);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->value, true);
}

/*
 * @tc.name: setCheckboxOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setCheckboxOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;

    jsonValue = GetJsonValue(node_);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_GROUP_NAME);
    expectedStr = ATTRIBUTE_GROUP_DEFAULT_VALUE;
    EXPECT_EQ(resultStr, expectedStr);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAME_NAME);
    expectedStr = ATTRIBUTE_NAME_DEFAULT_VALUE;
    EXPECT_EQ(resultStr, expectedStr);
}

/*
 * @tc.name: setCheckboxOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setCheckboxOptionsTestValidValues, TestSize.Level1)
{
    Opt_CheckboxOptions options;
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;

    options.value.group = Converter::ArkValue<Opt_String>(ATTRIBUTE_GROUP_TEST_VALUE);
    options.value.name = Converter::ArkValue<Opt_String>(ATTRIBUTE_NAME_TEST_VALUE);
    modifier_->setCheckboxOptions(node_, &options);

    jsonValue = GetJsonValue(node_);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_GROUP_NAME);
    expectedStr = ATTRIBUTE_GROUP_TEST_VALUE;
    EXPECT_EQ(resultStr, expectedStr);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAME_NAME);
    expectedStr = ATTRIBUTE_NAME_TEST_VALUE;
    EXPECT_EQ(resultStr, expectedStr);
}

/*
 * @tc.name: setSelectTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setSelectTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECT_DEFAULT_VALUE);
}

// Valid values for attribute 'select' of method 'select'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> selectSelectValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setSelectTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setSelectTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueSelect;
    Ark_Boolean initValueSelect;

    // Initial setup
    initValueSelect = std::get<1>(selectSelectValidValues[0]);

    // Verifying attribute's  values
    inputValueSelect = initValueSelect;
    for (auto&& value: selectSelectValidValues) {
        inputValueSelect = std::get<1>(value);
        modifier_->setSelect(node_, inputValueSelect);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setSelectedColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setSelectedColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'selectedColor' of method 'selectedColor'
static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>> selectedColorSelectedColorValidValues = {
    { "ARK_COLOR_BLUE", Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { "ARK_COLOR_RED", Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_RED), "#FFFF0000" },
};

/*
 * @tc.name: setSelectedColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setSelectedColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ResourceColor inputValueSelectedColor;
    Ark_ResourceColor initValueSelectedColor;

    // Initial setup
    initValueSelectedColor = std::get<1>(selectedColorSelectedColorValidValues[0]);
    modifier_->setSelect(node_, Converter::ArkValue<Ark_Boolean>(true));

    // Verifying attribute's  values
    inputValueSelectedColor = initValueSelectedColor;
    for (auto&& value: selectedColorSelectedColorValidValues) {
        inputValueSelectedColor = std::get<1>(value);
        modifier_->setSelectedColor(node_, &inputValueSelectedColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setSelectedColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setSelectedColorTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ResourceColor inputValueSelectedColor;

    // Initial setup
    modifier_->setSelect(node_, Converter::ArkValue<Ark_Boolean>(true));

    // Verifying attribute's  values

    inputValueSelectedColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xffffffff + 1);
    modifier_->setSelectedColor(node_, &inputValueSelectedColor);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
    expectedStr = ATTRIBUTE_SELECTED_COLOR_INVALID_VALUE;
    EXPECT_EQ(resultStr, expectedStr);
}

/*
 * @tc.name: setUnselectedColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setUnselectedColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UNSELECTED_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_UNSELECTED_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'unselectedColor' of method 'unselectedColor'
static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>> unselectedColorUnselectedColorValidValues = {
    { "ARK_COLOR_BLUE", Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { "ARK_COLOR_RED", Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_RED), "#FFFF0000" },
};

/*
 * @tc.name: setUnselectedColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setUnselectedColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ResourceColor inputValueUnselectedColor;
    Ark_ResourceColor initValueUnselectedColor;

    // Initial setup
    initValueUnselectedColor = std::get<1>(unselectedColorUnselectedColorValidValues[0]);

    // Verifying attribute's  values
    inputValueUnselectedColor = initValueUnselectedColor;
    for (auto&& value: unselectedColorUnselectedColorValidValues) {
        inputValueUnselectedColor = std::get<1>(value);
        modifier_->setUnselectedColor(node_, &inputValueUnselectedColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UNSELECTED_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setUnselectedColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setUnselectedColorTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ResourceColor inputValueUnselectedColor;

    // Initial setup
    modifier_->setSelect(node_, Converter::ArkValue<Ark_Boolean>(true));

    // Verifying attribute's  values

    inputValueUnselectedColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xffffffff + 1);
    modifier_->setUnselectedColor(node_, &inputValueUnselectedColor);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UNSELECTED_COLOR_NAME);
    expectedStr = ATTRIBUTE_UNSELECTED_COLOR_INVALID_VALUE;
    EXPECT_EQ(resultStr, expectedStr);
}

/*
 * @tc.name: setShapeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setShapeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHAPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHAPE_DEFAULT_VALUE);
}

// Valid values for attribute 'shape' of method 'shape'
static std::vector<std::tuple<std::string, enum Ark_CheckBoxShape, std::string>> shapeShapeValidValues = {
    {"ARK_CHECK_BOX_SHAPE_CIRCLE",
        Converter::ArkValue<enum Ark_CheckBoxShape>(ARK_CHECK_BOX_SHAPE_CIRCLE), "0"},
    {"ARK_CHECK_BOX_SHAPE_ROUNDED_SQUARE",
        Converter::ArkValue<enum Ark_CheckBoxShape>(ARK_CHECK_BOX_SHAPE_ROUNDED_SQUARE), "1"},
};

/*
 * @tc.name: setShapeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setShapeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_CheckBoxShape inputValueShape;
    Ark_CheckBoxShape initValueShape;

    // Initial setup
    initValueShape = std::get<1>(shapeShapeValidValues[0]);

    // Verifying attribute's  values
    inputValueShape = initValueShape;
    for (auto&& value: shapeShapeValidValues) {
        inputValueShape = std::get<1>(value);
        modifier_->setShape(node_, inputValueShape);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHAPE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'shape' of method 'shape'
static std::vector<std::tuple<std::string, enum Ark_CheckBoxShape>> shapeShapeInvalidValues = {
    {"static_cast<enum Ark_CheckBoxShape>(-1)",
        Converter::ArkValue<enum Ark_CheckBoxShape>(static_cast<enum Ark_CheckBoxShape>(-1))},
};

/*
 * @tc.name: setShapeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setShapeTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_CheckBoxShape inputValueShape;
    Ark_CheckBoxShape initValueShape;

    // Initial setup
    initValueShape = std::get<1>(shapeShapeValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: shapeShapeInvalidValues) {
        inputValueShape = initValueShape;
        modifier_->setShape(node_, inputValueShape);
        inputValueShape = std::get<1>(value);
        modifier_->setShape(node_, inputValueShape);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHAPE_NAME);
        expectedStr = ATTRIBUTE_SHAPE_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/**
 * @tc.name: setMarkTestDefaultValues
 * @tc.desc: setMark test
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setMarkTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> resultMark;
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;

    jsonValue = GetJsonValue(node_);

    resultMark = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_NAME);
    resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_STROKE_COLOR_NAME);
    expectedStr = ATTRIBUTE_MARK_STROKE_COLOR_DEFAULT_VALUE;
    EXPECT_EQ(resultStr, expectedStr);

    resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_SIZE_NAME);
    expectedStr = ATTRIBUTE_MARK_SIZE_DEFAULT_VALUE;
    EXPECT_EQ(resultStr, expectedStr);

    resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_STROKE_WIDTH_NAME);
    expectedStr = ATTRIBUTE_MARK_STROKE_WIDTH_DEFAULT_VALUE;
    EXPECT_EQ(resultStr, expectedStr);
}

/**
 * @tc.name: setMarkTestValidValues
 * @tc.desc: setMark test
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setMarkTestValidValues, TestSize.Level1)
{
    Ark_MarkStyle style;
    Ark_ResourceColor color = Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xFF123456);
    Ark_Length len1 = Converter::ArkValue<Ark_Length>(SIZE1);
    Ark_Length len2 = Converter::ArkValue<Ark_Length>(SIZE2);
    Opt_Length opt1 = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(len1));
    Opt_Length opt2 = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(len2));

    std::unique_ptr<JsonValue> resultMark;
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;

    style.strokeColor.value = color;
    style.size = opt1;
    style.strokeWidth = opt2;
    modifier_->setMark(node_, &style);

    jsonValue = GetJsonValue(node_);

    resultMark = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_NAME);
    resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_STROKE_COLOR_NAME);
    expectedStr = ATTRIBUTE_MARK_STROKE_COLOR_TEST_VALUE;
    EXPECT_EQ(resultStr, expectedStr);

    resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_SIZE_NAME);
    expectedStr = ATTRIBUTE_MARK_SIZE_TEST_VALUE;
    EXPECT_EQ(resultStr, expectedStr);

    resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_STROKE_WIDTH_NAME);
    expectedStr = ATTRIBUTE_MARK_STROKE_WIDTH_TEST_VALUE;
    EXPECT_EQ(resultStr, expectedStr);
}

/**
 * @tc.name: setMarkTestDefaultValidValues
 * @tc.desc: setMark test
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setMarkTestInvalidValues, TestSize.Level1)
{
    Ark_MarkStyle style;
    std::unique_ptr<JsonValue> resultMark;
    std::unique_ptr<JsonValue> jsonValue;
    Ark_ResourceColor color = Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x00000000);
    Ark_Length len1 = Converter::ArkValue<Ark_Length>(0);
    Ark_Length len2 = Converter::ArkValue<Ark_Length>(0);
    Opt_Length opt1 = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(len1));
    Opt_Length opt2 = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(len2));
    std::string resultStr;
    std::string expectedStr;

    style.strokeColor.value = color;
    style.size = opt1;
    style.strokeWidth = opt2;
    modifier_->setMark(node_, &style);

    jsonValue = GetJsonValue(node_);

    resultMark = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_NAME);
    resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_STROKE_COLOR_NAME);
    expectedStr = "#00000000";
    EXPECT_EQ(resultStr, expectedStr);

    resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_SIZE_NAME);
    expectedStr = "0.00px";
    EXPECT_EQ(resultStr, expectedStr);

    resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_STROKE_WIDTH_NAME);
    expectedStr = "0.00px";
    EXPECT_EQ(resultStr, expectedStr);
}

} // namespace OHOS::Ace::NG
