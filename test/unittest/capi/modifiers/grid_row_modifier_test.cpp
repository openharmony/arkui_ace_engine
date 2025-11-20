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

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "generated/test_fixtures.h"
#include "generated/type_helpers.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/grid_row/grid_row_event_hub.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
    struct GutterOption {
        std::optional<Dimension> x;
        std::optional<Dimension> y;
    };
    struct GridRowSizeOption {
        std::optional<Dimension> xs;
        std::optional<Dimension> sm;
        std::optional<Dimension> md;
        std::optional<Dimension> lg;
        std::optional<Dimension> xl;
        std::optional<Dimension> xxl;
    };
    using GridRowColumnOption = GridRowSizeOption;

    struct BreakPoints {
        std::optional<std::vector<std::string>> value;
        std::optional<Ark_BreakpointsReference> reference;
    };
    struct GridRowOptions {
        std::optional<GutterOption> gutter;
        std::optional<GridRowColumnOption> columns;
        std::optional<BreakPoints> breakpoints;
        std::optional<Ark_GridRowDirection> direction;
    };
    struct GutterOptionTest {
        float x;
        float y;
    };
    struct BreakPointsTest {
        std::vector<std::string> value;
        Ark_BreakpointsReference reference;
        std::string referenceStr;
    };
    struct GridRowOptionsTest {
        GutterOptionTest gutter;
        std::string columns;
        BreakPointsTest breakpoints;
        Ark_GridRowDirection direction;
        std::string directionStr;
    };
    void AssignArkValue(Ark_GutterOption& dst, const GutterOption& src)
    {
        auto emptyValue = Converter::ArkUnion<Opt_Union_Length_GridRowSizeOption>(Ark_Empty());
        if (src.x.has_value()) {
            auto arkLength = Converter::ArkValue<Ark_Length>(src.x.value());
            auto arkUnion = Converter::ArkUnion<Ark_Union_Length_GridRowSizeOption, Ark_Length>(arkLength);
            auto arkUnionOptnl = std::optional<Ark_Union_Length_GridRowSizeOption>(arkUnion);
            dst.x = Converter::ArkValue<Opt_Union_Length_GridRowSizeOption>(arkUnionOptnl);
        } else {
            dst.x = emptyValue;
        }
        if (src.y.has_value()) {
            auto arkLength = Converter::ArkValue<Ark_Length>(src.y.value());
            auto arkUnion = Converter::ArkUnion<Ark_Union_Length_GridRowSizeOption, Ark_Length>(arkLength);
            auto arkUnionOptnl = std::optional<Ark_Union_Length_GridRowSizeOption>(arkUnion);
            dst.y = Converter::ArkValue<Opt_Union_Length_GridRowSizeOption>(arkUnionOptnl);
        } else {
            dst.y = emptyValue;
        }
    }
    void AssignArkValue(Ark_GridRowSizeOption& dst, const Dimension& src)
    {
        auto optLenValue = Converter::ArkValue<Opt_Length>(src);
        dst.xs = optLenValue;
        dst.sm = optLenValue;
        dst.md = optLenValue;
        dst.lg = optLenValue;
        dst.xl = optLenValue;
        dst.xxl = optLenValue;
    }
    void AssignArkValue(Ark_GridRowColumnOption& dst, const int32_t& src)
    {
        auto dimensionValue = Dimension(src);
        auto optValue = Converter::ArkValue<Opt_Int32>(dimensionValue);
        dst.xs = optValue;
        dst.sm = optValue;
        dst.md = optValue;
        dst.lg = optValue;
        dst.xl = optValue;
        dst.xxl = optValue;
    }
    void AssignArkValue(Ark_GridRowColumnOption& dst, const GridRowColumnOption& src)
    {
        dst.xs = Converter::ArkValue<Opt_Int32>(src.xs);
        dst.sm = Converter::ArkValue<Opt_Int32>(src.sm);
        dst.md = Converter::ArkValue<Opt_Int32>(src.md);
        dst.lg = Converter::ArkValue<Opt_Int32>(src.lg);
        dst.xl = Converter::ArkValue<Opt_Int32>(src.xl);
        dst.xxl = Converter::ArkValue<Opt_Int32>(src.xxl);
    }
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_GUTTER_NAME = "gutter";
const auto ATTRIBUTE_GUTTER_I_X_NAME = "x";
const auto ATTRIBUTE_GUTTER_I_X_DEFAULT_VALUE = 0.0;
const auto ATTRIBUTE_GUTTER_I_Y_NAME = "y";
const auto ATTRIBUTE_GUTTER_I_Y_DEFAULT_VALUE = 0.0;
const auto ATTRIBUTE_COLUMNS_NAME = "columns";
const auto ATTRIBUTE_COLUMNS_DEFAULT_VALUE = "12";
const auto ATTRIBUTE_BREAKPOINTS_NAME = "breakpoints";
const auto ATTRIBUTE_BREAKPOINTS_I_VALUE_NAME = "value";
const auto ATTRIBUTE_BREAKPOINTS_I_VALUE_DEFAULT_VALUE = std::vector<std::string>({ "320vp", "600vp", "840vp" });
const auto ATTRIBUTE_BREAKPOINTS_I_REFERENCE_NAME = "reference";
const auto ATTRIBUTE_BREAKPOINTS_I_REFERENCE_DEFAULT_VALUE = "BreakPointsReference.WindowSize";
const auto ATTRIBUTE_DIRECTION_NAME = "gridRowDirection";
const auto ATTRIBUTE_DIRECTION_DEFAULT_VALUE = "GridRowDirection.Row";
const auto ATTRIBUTE_ALIGN_ITEMS_NAME = "itemAlign"; // "alignSelf" ???
const auto ATTRIBUTE_ALIGN_ITEMS_DEFAULT_VALUE = "ItemAlign.Start";
} // namespace

class GridRowModifierTest : public ModifierTestBase<GENERATED_ArkUIGridRowModifier,
                                &GENERATED_ArkUINodeModifiers::getGridRowModifier, GENERATED_ARKUI_GRID_ROW> {
public:
    // Auto generated method
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }
};

/*
 * @tc.name: setGridRowOptionsTestDefaultValues
 * @tc.desc: Checking the options default values.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowModifierTest, DISABLED_setGridRowOptionsTestDefaultValues, TestSize.Level1)
{
    CHECK_NULL_VOID(node_);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    CHECK_NULL_VOID(jsonValue);
    // Gutter test
    std::unique_ptr<JsonValue> resultGutter =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_GUTTER_NAME);
    auto resultX =
        std::stof(GetAttrValue<std::string>(resultGutter, ATTRIBUTE_GUTTER_I_X_NAME));
    auto resultY =
        std::stof(GetAttrValue<std::string>(resultGutter, ATTRIBUTE_GUTTER_I_Y_NAME));
    EXPECT_EQ(resultX, ATTRIBUTE_GUTTER_I_X_DEFAULT_VALUE) << "Default value for attribute 'options.gutter.x'";
    EXPECT_EQ(resultY, ATTRIBUTE_GUTTER_I_Y_DEFAULT_VALUE) << "Default value for attribute 'options.gutter.y'";
    // Columns test
    auto resultColumns = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLUMNS_NAME);
    EXPECT_EQ(resultColumns, ATTRIBUTE_COLUMNS_DEFAULT_VALUE) << "Default value for attribute 'options.columns'";
    // Breakpoints test
    auto resultBreakpoints = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BREAKPOINTS_NAME);
    auto resultBreakpointsValues =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultBreakpoints, ATTRIBUTE_BREAKPOINTS_I_VALUE_NAME);
    std::string valStr;
    auto lenArray = resultBreakpointsValues->IsArray() ? resultBreakpointsValues->GetArraySize() : 0;
    for (int32_t idx = 0; idx < lenArray; idx++) {
        valStr = resultBreakpointsValues->GetArrayItem(idx)->GetString();
        EXPECT_EQ(valStr, ATTRIBUTE_BREAKPOINTS_I_VALUE_DEFAULT_VALUE[idx]) <<
            "Default value for attribute 'options.breakpoints.values'";
    }
    auto resultStr = GetAttrValue<std::string>(resultBreakpoints, ATTRIBUTE_BREAKPOINTS_I_REFERENCE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BREAKPOINTS_I_REFERENCE_DEFAULT_VALUE) <<
        "Default value for attribute 'options.breakpoints.reference'";
    // Direction test
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIRECTION_DEFAULT_VALUE) << "Default value for attribute 'options.direction'";
}

using TupleGutterOptionTest = std::tuple<GutterOptionTest, GutterOption, GutterOptionTest>;
static std::vector<TupleGutterOptionTest> testGutterOptionValidValues = {
    {{.x=0, .y=0}, {Dimension(0), Dimension(0)}, {.x=0, .y=0}},
    {{.x=1, .y=2}, {Dimension(1), Dimension(2)}, {.x=1, .y=2}},
    {{.x=2, .y=1}, {Dimension(2), Dimension(1)}, {.x=2, .y=1}},
    {{.x=3, .y=4}, {Dimension(3), Dimension(4)}, {.x=3, .y=4}},
    {{.x=4, .y=3}, {Dimension(4), Dimension(3)}, {.x=4, .y=3}},
};

static std::vector<TupleGutterOptionTest> testGutterOptionInvalidValues = {
    {{.x=0, .y=0}, {Dimension(-1), Dimension(-1)}, {.x=0, .y=0}},
    {{.x=0, .y=0}, {Dimension(-2), Dimension(-2)}, {.x=0, .y=0}},
};

using TupleColumnsOptionTest = std::tuple<std::string, int32_t, std::string>;
static std::vector<TupleColumnsOptionTest> testColumnsOptionValidValues = {
    {"0", 0, "0"},
    {"1", 1, "1"},
    {"6", 6, "6"},
    {"12", 12, "12"},
    {"18", 18, "18"},
};

using TupleColumnsOptionTest = std::tuple<std::string, int32_t, std::string>;
static std::vector<TupleColumnsOptionTest> testColumnsOptionInvalidValues = {
    {"-1", -1, "12"},
    {"-2", -2, "12"},
};

using tupleBreakPointsArrayOptionTest =
    std::tuple<std::vector<std::string>, std::vector<std::string>, std::vector<std::string>>;
std::vector<tupleBreakPointsArrayOptionTest> testBreakPointsArrayOptionValidValues = {
    {{"321vp", "601vp"}, {"321vp", "601vp"}, {"321vp", "601vp"}},
    {{"321vp", "601vp", "841vp"}, {"321vp", "601vp", "841vp"}, {"321vp", "601vp", "841vp"}},
    {{"322vp", "602vp", "842vp", "1024vp"}, {"322vp", "602vp", "842vp", "1024vp"},
        {"322vp", "602vp", "842vp", "1024vp"}},
    {{"322vp", "602vp", "842vp", "1024vp", "1280vp"}, {"322vp", "602vp", "842vp", "1024vp", "1280vp"},
        {"322vp", "602vp", "842vp", "1024vp", "1280vp"}},
    {{"322vp", "602vp", "842vp", "1024vp", "1280vp", "1440vp"}, //
        {"322vp", "602vp", "842vp", "1024vp", "1280vp", "1440vp"}, //
        {"322vp", "602vp", "842vp", "1024vp", "1280vp", "1440vp"}},
};

std::vector<tupleBreakPointsArrayOptionTest> testBreakPointsArrayOptionInvalidValues = {
    {{"320vp", "600vp", "840vp"}, {}, {"320vp", "600vp", "840vp"}},
    {{"320vp", "600vp", "840vp"}, {}, {"320vp", "600vp", "840vp"}},
};

std::vector<std::tuple<Ark_BreakpointsReference, Ark_BreakpointsReference, std::string>>
    testBreakPointsReferenceOptionValidValues = {
        {ARK_BREAKPOINTS_REFERENCE_WINDOW_SIZE, ARK_BREAKPOINTS_REFERENCE_WINDOW_SIZE,
            "BreakPointsReference.WindowSize"},
        {ARK_BREAKPOINTS_REFERENCE_COMPONENT_SIZE, ARK_BREAKPOINTS_REFERENCE_COMPONENT_SIZE,
            "BreakPointsReference.ComponentSize"},
        {ARK_BREAKPOINTS_REFERENCE_WINDOW_SIZE, ARK_BREAKPOINTS_REFERENCE_WINDOW_SIZE,
            "BreakPointsReference.WindowSize"},
        {ARK_BREAKPOINTS_REFERENCE_COMPONENT_SIZE, ARK_BREAKPOINTS_REFERENCE_COMPONENT_SIZE,
            "BreakPointsReference.ComponentSize"},
        {ARK_BREAKPOINTS_REFERENCE_WINDOW_SIZE, ARK_BREAKPOINTS_REFERENCE_WINDOW_SIZE,
            "BreakPointsReference.WindowSize"},
};

std::vector<std::tuple<Ark_BreakpointsReference, Ark_BreakpointsReference, std::string>>
    testBreakPointsReferenceOptionInvalidValues = {
        {static_cast<Ark_BreakpointsReference>(-1), static_cast<Ark_BreakpointsReference>(-1),
            "Unknown"},
        {static_cast<Ark_BreakpointsReference>(INT_MAX), static_cast<Ark_BreakpointsReference>(INT_MAX),
            "Unknown"},
};

std::vector<std::tuple<Ark_GridRowDirection, Ark_GridRowDirection, std::string>>
    testDirectionOptionValidValues = {
        {ARK_GRID_ROW_DIRECTION_ROW, ARK_GRID_ROW_DIRECTION_ROW,
            "GridRowDirection.Row"},
        {ARK_GRID_ROW_DIRECTION_ROW_REVERSE, ARK_GRID_ROW_DIRECTION_ROW_REVERSE,
            "GridRowDirection.RowReverse"},
        {ARK_GRID_ROW_DIRECTION_ROW, ARK_GRID_ROW_DIRECTION_ROW,
            "GridRowDirection.Row"},
        {ARK_GRID_ROW_DIRECTION_ROW_REVERSE, ARK_GRID_ROW_DIRECTION_ROW_REVERSE,
            "GridRowDirection.RowReverse"},
        {ARK_GRID_ROW_DIRECTION_ROW, ARK_GRID_ROW_DIRECTION_ROW,
            "GridRowDirection.Row"},
};

std::vector<std::tuple<Ark_GridRowDirection, Ark_GridRowDirection, std::string>>
    testDirectionOptionInvalidValues = {
        {static_cast<Ark_GridRowDirection>(-1), static_cast<Ark_GridRowDirection>(-1),
            "Unknown"},
        {static_cast<Ark_GridRowDirection>(INT_MAX), static_cast<Ark_GridRowDirection>(INT_MAX),
            "Unknown"},
};

/*
 * @tc.name: setGridRowOptionsTestColumnsValidValues
 * @tc.desc: Checking the options valid values.
 * @tc.type: FUNC
 */
void checkOptionValue(std::unique_ptr<JsonValue> jsonValue, const GridRowOptionsTest& value,
                      const Ark_GridRowOptions& input, const GridRowOptionsTest& expected)
{
    // Gutter test
    std::unique_ptr<JsonValue> resultGutter =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_GUTTER_NAME);
    auto resultX =
        std::stof(GetAttrValue<std::string>(resultGutter, ATTRIBUTE_GUTTER_I_X_NAME));
    auto resultY =
        std::stof(GetAttrValue<std::string>(resultGutter, ATTRIBUTE_GUTTER_I_Y_NAME));
    EXPECT_EQ(resultX, expected.gutter.x) <<
        "Input value is: " << value.gutter.x << ", method: setGridRowOptions, attribute: gutter.x";
    EXPECT_EQ(resultY, expected.gutter.y) <<
        "Input value is: " << value.gutter.y << ", method: setGridRowOptions, attribute: gutter.y";
    // Columns test
    auto columnsResultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLUMNS_NAME);
    EXPECT_EQ(columnsResultStr, expected.columns) <<
        "Input value is: " << value.columns << ", method: setGridRowOptions, attribute: Columns";
    // Breakpoints value test
    auto breakPointsJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BREAKPOINTS_NAME);
    auto breakPointsValueJson =
        GetAttrValue<std::unique_ptr<JsonValue>>(breakPointsJson, ATTRIBUTE_BREAKPOINTS_I_VALUE_NAME);
    std::string valStr;
    auto lenArray = breakPointsValueJson->IsArray() ? breakPointsValueJson->GetArraySize() : 0;
    for (int32_t idx = 0; idx < lenArray; idx++) {
        valStr = breakPointsValueJson->GetArrayItem(idx)->GetString();
        EXPECT_EQ(valStr, expected.breakpoints.value[idx]) <<
            "Input value is: " << value.breakpoints.value[idx]
            << ", method: setGridRowOptions, attribute: Breakpoints.value";
    }
    // Breakpoints reference test
    auto resultStr = GetAttrValue<std::string>(breakPointsJson, ATTRIBUTE_BREAKPOINTS_I_REFERENCE_NAME);
    EXPECT_EQ(resultStr, expected.breakpoints.referenceStr) <<
        "Input value is: " << value.breakpoints.referenceStr
        << ", method: setGridRowOptions, attribute: Breakpoints.reference";
    // direction test
    auto directionResultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
    EXPECT_EQ(directionResultStr, expected.directionStr) <<
        "Input value is: " << value.directionStr << ", method: setGridRowOptions, attribute: Direction";
}

HWTEST_F(GridRowModifierTest, DISABLED_setGridRowOptionsTestValidValues, TestSize.Level1)
{
    CHECK_NULL_VOID(node_);
    Ark_GridRowOptions inputValue;
    GridRowOptionsTest value = {};
    GridRowOptionsTest expected = {};

    // Initial setup
    auto initValueGutter = [this, &inputValue](const GutterOption& initValue) {
        GutterOption val = {initValue.x, initValue.y};
        Ark_GutterOption arkVal = Converter::ArkValue<Ark_GutterOption>(val);
        auto arkUnion = Converter::ArkUnion<Ark_Union_Length_GutterOption, Ark_GutterOption>(arkVal);
        auto arkUnionOptnl = std::optional<Ark_Union_Length_GutterOption>(arkUnion);
        inputValue.gutter = Converter::ArkValue<Opt_Union_Length_GutterOption>(arkUnionOptnl);
    };

    auto initValueColumns = [this, &inputValue](const int32_t& initValue) {
        auto ArkUnion = Converter::ArkUnion<Ark_Union_I32_GridRowColumnOption, Ark_Int32>(initValue);
        auto ArkUnionOptnl = std::optional<Ark_Union_I32_GridRowColumnOption>(ArkUnion);
        inputValue.columns = Converter::ArkValue<Opt_Union_I32_GridRowColumnOption>(ArkUnionOptnl);
    };

    auto initValueDirection = [this, &inputValue](const Ark_GridRowDirection& initValue) {
        inputValue.direction =
            Converter::ArkValue<Opt_GridRowDirection>(initValue);
    };

    for (auto idx = 0; idx < testGutterOptionValidValues.size(); idx++) {
        auto& [gutterValue, gutterInput, gutterExpected] = testGutterOptionValidValues[idx];
        auto& [columnsValue, columnsInput, columnsExpected] = testColumnsOptionValidValues[idx];
        auto& [arrayValue, arrayInput, arrayExpected] = testBreakPointsArrayOptionValidValues[idx];
        auto& [referenceValue, referenceInput, referenceExpected] = testBreakPointsReferenceOptionValidValues[idx];
        auto& [directionValue, directionInput, directionExpected] = testDirectionOptionValidValues[idx];
        initValueGutter(gutterInput);
        initValueColumns(columnsInput);
        Converter::ArkArrayHolder<Array_String> listHolder(arrayInput);
        auto optArrayString = listHolder.OptValue<Opt_Array_String>();
        auto optBreakpointsReference = Converter::ArkValue<Opt_BreakpointsReference>(referenceInput);
        Ark_BreakPoints arkBreakPoints = {.value=optArrayString, .reference=optBreakpointsReference};
        inputValue.breakpoints =  Converter::ArkValue<Opt_BreakPoints>(arkBreakPoints);
        initValueDirection(directionInput);
        expected.gutter = gutterExpected;
        expected.columns = columnsExpected;
        expected.breakpoints = {arrayExpected, referenceValue, referenceExpected};
        expected.direction = directionValue;
        expected.directionStr = directionExpected;
        // set valid values
        auto optInputValue = Converter::ArkValue<Opt_GridRowOptions>(inputValue);
        modifier_->setGridRowOptions(node_, &optInputValue);
        // Check valid values
        checkOptionValue(GetJsonValue(node_), value, inputValue, expected);
    }
}

/*
 * @tc.name: setGridRowOptionsTestInvalidValues
 * @tc.desc: Checking the options invalid values.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowModifierTest, DISABLED_setGridRowOptionsTestInvalidValues, TestSize.Level1)
{
    CHECK_NULL_VOID(node_);
    Ark_GridRowOptions inputValue;
    GridRowOptionsTest value = {}, expected = {};

    // Initial setup
    auto initValueGutter = [this, &inputValue](const GutterOption& initValue) {
        GutterOption val = {initValue.x, initValue.y};
        Ark_GutterOption arkVal = Converter::ArkValue<Ark_GutterOption>(val);
        auto arkUnion = Converter::ArkUnion<Ark_Union_Length_GutterOption, Ark_GutterOption>(arkVal);
        auto arkUnionOptnl = std::optional<Ark_Union_Length_GutterOption>(arkUnion);
        inputValue.gutter = Converter::ArkValue<Opt_Union_Length_GutterOption>(arkUnionOptnl);
    };

    auto initValueColumns = [this, &inputValue](const int32_t& initValue) {
        auto ArkUnion = Converter::ArkUnion<Ark_Union_I32_GridRowColumnOption, Ark_Int32>(initValue);
        auto ArkUnionOptnl = std::optional<Ark_Union_I32_GridRowColumnOption>(ArkUnion);
        inputValue.columns = Converter::ArkValue<Opt_Union_I32_GridRowColumnOption>(ArkUnionOptnl);
    };

    auto initValueDirection = [this, &inputValue](const Ark_GridRowDirection& initValue) {
        inputValue.direction =
            Converter::ArkValue<Opt_GridRowDirection>(initValue);
    };

    for (auto idx = 0; idx < testGutterOptionInvalidValues.size(); idx++) {
        auto& [gutterValue, gutterInput, gutterExpected] = testGutterOptionInvalidValues[idx];
        auto& [columnsValue, columnsInput, columnsExpected] = testColumnsOptionInvalidValues[idx];
        auto& [arrayValue, arrayInput, arrayExpected] = testBreakPointsArrayOptionInvalidValues[idx];
        auto& [referenceValue, referenceInput, referenceExpected] = testBreakPointsReferenceOptionInvalidValues[idx];
        auto& [directionValue, directionInput, directionExpected] = testDirectionOptionInvalidValues[idx];
        initValueGutter(gutterInput);
        initValueColumns(columnsInput);
        Converter::ArkArrayHolder<Array_String> listHolder(arrayInput);
        auto optArrayString = listHolder.OptValue<Opt_Array_String>();
        auto optBreakpointsReference = Converter::ArkValue<Opt_BreakpointsReference>(referenceInput);
        Ark_BreakPoints arkBreakPoints = {.value=optArrayString, .reference=optBreakpointsReference};
        inputValue.breakpoints =  Converter::ArkValue<Opt_BreakPoints>(arkBreakPoints);
        initValueDirection(directionInput);

        value = {.gutter = gutterValue, .columns = columnsValue,
            .breakpoints = {arrayValue, referenceValue, referenceExpected}, .direction = directionValue,
            .directionStr = directionExpected};
        expected = {.gutter = gutterExpected, .columns = columnsExpected,
            .breakpoints = {arrayExpected, referenceValue, referenceExpected}, .direction = directionValue,
            .directionStr = directionExpected};
        // set invalid values
        auto optInputValue = Converter::ArkValue<Opt_GridRowOptions>(inputValue);
        modifier_->setGridRowOptions(node_, &optInputValue);
        // Check invalid values
        checkOptionValue(GetJsonValue(node_), value, inputValue, expected);
    }
}

/*
 * @tc.name: setAlignItemsTestDefaultValues
 * @tc.desc: Checking the AlignItems default values.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowModifierTest, DISABLED_setAlignItemsTestDefaultValues, TestSize.Level1)
{
    CHECK_NULL_VOID(node_);
     // Without this initializations, GetJsonValue() crashes.
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    CHECK_NULL_VOID(jsonValue);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALIGN_ITEMS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_ITEMS_DEFAULT_VALUE) << "Default value for attribute 'alignItems'";
}

std::vector<std::tuple<std::string, Ark_ItemAlign, std::string>> testItemAlignValidValues = {
    {"ARK_ITEM_ALIGN_AUTO", ARK_ITEM_ALIGN_AUTO, "ItemAlign.Auto"},
    {"ARK_ITEM_ALIGN_START", ARK_ITEM_ALIGN_START, "ItemAlign.Start"},
    {"ARK_ITEM_ALIGN_CENTER", ARK_ITEM_ALIGN_CENTER, "ItemAlign.Center"},
    {"ARK_ITEM_ALIGN_END", ARK_ITEM_ALIGN_END, "ItemAlign.End"},
    {"ARK_ITEM_ALIGN_BASELINE", ARK_ITEM_ALIGN_BASELINE, "ItemAlign.Baseline"},
    {"ARK_ITEM_ALIGN_STRETCH", ARK_ITEM_ALIGN_STRETCH, "ItemAlign.Stretch"},
};

/*
 * @tc.name: setAlignItemsTestAlignItemsValidValues
 * @tc.desc: Checking the AlignItems valid values.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowModifierTest, DISABLED_setAlignItemsTestAlignItemsValidValues, TestSize.Level1)
{
    CHECK_NULL_VOID(node_);
    // Without this initializations, GetJsonValue() crashes.
    Ark_ItemAlign initValueAlignItems;

    // Initial setup
    initValueAlignItems = std::get<1>(testItemAlignValidValues[0]);

    auto checkValue = [this, &initValueAlignItems](
                          const std::string& input, const Ark_ItemAlign& value, const std::string& expectedStr) {
        Ark_ItemAlign inputValueAlignItems = initValueAlignItems;

        inputValueAlignItems = value;
        auto optInputValueAlignItems = Converter::ArkValue<Opt_ItemAlign>(inputValueAlignItems);
        modifier_->setAlignItems(node_, &optInputValueAlignItems);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALIGN_ITEMS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignItems, attribute: alignItems";
    };

    for (auto& [input, value, expected] : testItemAlignValidValues) {
        checkValue(input, value, expected);
    }
}

std::vector<std::tuple<std::string, Ark_ItemAlign, std::string>> testItemAlignInvalidValues = {
    {"ARK_ITEM_ALIGN_START", static_cast<Ark_ItemAlign>(-1), "ItemAlign.Start"},
    {"ARK_ITEM_ALIGN_START", static_cast<Ark_ItemAlign>(INT_MAX), "ItemAlign.Start"},
};

/*
 * @tc.name: setAlignItemsTestAlignItemsInvalidValues
 * @tc.desc: Checking the AlignItems invalid values.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowModifierTest, DISABLED_setAlignItemsTestAlignItemsInvalidValues, TestSize.Level1)
{
    CHECK_NULL_VOID(node_);
    // Without this initializations, GetJsonValue() crashes.
    Ark_ItemAlign initValueAlignItems;
    // Initial setup
    initValueAlignItems = std::get<1>(testItemAlignInvalidValues[0]);
    auto checkValue = [this, &initValueAlignItems](
                          const std::string& input, const Ark_ItemAlign& value, const std::string& expectedStr) {
        Ark_ItemAlign inputValueAlignItems = initValueAlignItems;

        inputValueAlignItems = value;
        auto optInputValueAlignItems = Converter::ArkValue<Opt_ItemAlign>(inputValueAlignItems);
        modifier_->setAlignItems(node_, &optInputValueAlignItems);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALIGN_ITEMS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignItems, attribute: alignItems";
    };
    for (auto& [input, value, expected] : testItemAlignInvalidValues) {
        checkValue(input, value, expected);
    }
}

/* Auto generated test
 * @tc.name: setOnBreakpointChangeTest
 * @tc.desc: Checking the callback operation for a change in breakpoint.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowModifierTest, DISABLED_setOnBreakpointChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridRowEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        std::string breakpoint;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onBreakpointChange = [](Ark_Int32 nodeId, const Ark_String breakpoint) {
        checkEvent = {
            .nodeId = nodeId,
            .breakpoint = Converter::Convert<std::string>(breakpoint),
        };
    };

    Callback_String_Void callBackValue = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onBreakpointChange
    };

    auto optCallBackValue = Converter::ArkValue<Opt_Callback_String_Void>(callBackValue);
    modifier_->setOnBreakpointChange(node_, &optCallBackValue);

    EXPECT_FALSE(checkEvent.has_value());

    eventHub->FireChangeEvent("320vp");
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->breakpoint, "320vp");

    checkEvent.reset();

    eventHub->FireChangeEvent("600vp");
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->breakpoint, "600vp");
}
} // namespace OHOS::Ace::NG
