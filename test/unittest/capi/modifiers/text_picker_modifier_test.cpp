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
#include "core/components/picker/picker_theme.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_RANGE_NAME = "range";
    const auto ATTRIBUTE_VALUE_NAME = "value";
    const auto ATTRIBUTE_VALUE_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_VALUES_NAME = "values";
    const auto ATTRIBUTE_VALUES_DEFAULT_COUNT = 0;
    const auto ATTRIBUTE_SELECTED_NAME = "selected";
    const auto ATTRIBUTE_SELECTED_DEFAULT_VALUE = "0";
    const auto ATTRIBUTE_SELECTEDS_NAME = "selecteds";
    const auto ATTRIBUTE_SELECTEDS_DEFAULT_COUNT = 0;
    const auto RES_STR_1_ID = IntResourceId{111, NodeModifier::ResourceType::STRING};
    const auto RES_STR_2_ID = IntResourceId{222, NodeModifier::ResourceType::STRING};
    const auto RES_STR_3_ID = IntResourceId{333, NodeModifier::ResourceType::STRING};
    const auto RES_PIC_1_ID = IntResourceId{444, NodeModifier::ResourceType::STRING};
    const auto RES_PIC_2_ID = IntResourceId{555, NodeModifier::ResourceType::STRING};
    const auto RES_PIC_3_ID = IntResourceId{666, NodeModifier::ResourceType::STRING};
    const auto TEST_COMMENT_ID = 0;
    const auto RANGE_ID = 1;
    const auto VALUES_ID = 2;
    const auto SELECTS_ID = 3;
    const auto HAS_VALUES_ID = 4;
    const auto HAS_SELECTS_ID = 5;
    const auto RANGE_RES_ID = 6;
    const auto VALUES_RES_ID = 7;
    const auto SELECTS_RES_ID = 8;
    const auto NAME_SUBCATEGORY_1 = "Subcategory 1";
    const auto NAME_SUBCATEGORY_2 = "Subcategory 2";
    const auto NAME_SUBCATEGORY_3 = "Subcategory 3";
    const auto NAME_ITEM_1 = "item1";
    const auto NAME_ITEM_2 = "item2";
    const auto NAME_ITEM_3 = "item3";
    const auto NAME_CATEGORY_1 = "Category 1";
    const auto NAME_CATEGORY_2 = "Category 2";
} // namespace

class TextPickerModifierTest : public ModifierTestBase<GENERATED_ArkUITextPickerModifier,
    &GENERATED_ArkUINodeModifiers::getTextPickerModifier, GENERATED_ARKUI_TEXT_PICKER> {
    public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<PickerTheme>();
        AddResource(RES_STR_1_ID, "str1");
        AddResource(RES_STR_2_ID, "str2");
        AddResource(RES_STR_3_ID, "str3");
        AddResource(RES_PIC_1_ID, "pic1");
        AddResource(RES_PIC_2_ID, "pic2");
        AddResource(RES_PIC_3_ID, "pic3");
    }
};


/*
 * @tc.name: setTextPickerOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setTextPickerOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);

    EXPECT_EQ(false, jsonValue->Contains(ATTRIBUTE_RANGE_NAME));

    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE);

    auto resultJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUES_NAME);
    ASSERT_NE(resultJson.get(), nullptr);
    EXPECT_EQ(true, resultJson.get()->IsArray());
    EXPECT_EQ(ATTRIBUTE_VALUES_DEFAULT_COUNT, resultJson.get()->GetArraySize());

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_DEFAULT_VALUE);

    resultJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTEDS_NAME);
    ASSERT_NE(resultJson.get(), nullptr);
    EXPECT_EQ(true, resultJson.get()->IsArray());
    EXPECT_EQ(ATTRIBUTE_SELECTEDS_DEFAULT_COUNT, resultJson.get()->GetArraySize());
}

static std::vector<std::tuple<std::string, std::vector<std::string>, std::string, int32_t, bool, bool,
    std::string, std::string, std::string>> textPickerOptionsAsStringArray = {
    {"single-column-picker#0", {"aa", "bb", "cc"}, "bb", -1, true, true,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "bb", "0"},
    {"single-column-picker#1", {"aa", "bb", "cc"}, "bb", 1, true, true,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "bb", "1"},
    {"single-column-picker#2", {"aa", "bb", "cc"}, "aa", 2, true, true,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "aa", "2"},
    {"single-column-picker#1", {"aa", "bb", "cc"}, "cc", 1, true, true,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "cc", "1"},
    {"single-column-picker#3", {"aa", "bb", "cc"}, "bb", 1, false, false,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "aa", "0"},
    {"single-column-picker#4", {"aa", "bb", "cc"}, "cc", 0, true, false,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "cc", "2"},
    {"single-column-picker#5", {"aa", "bb", "cc"}, "dd", 1, true, false,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "dd", "0"},
    {"single-column-picker#6", {"aa", "bb", "cc"}, "", 2, false, true,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "aa", "2"},
    {"single-column-picker#7", {"aa", "bb", "cc"}, "", 3, false, true,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "aa", "0"},
};

/*
 * @tc.name: setTextPickerOptionsAsStringArray
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setTextPickerOptionsAsStringArray, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;

    for (auto&& value: textPickerOptionsAsStringArray) {
        Ark_TextPickerOptions arkTextPickerOptions;
        Converter::ArkArrayHolder<Array_String> stringHolder(std::get<RANGE_ID>(value));
        Array_String stringHolderValue = stringHolder.ArkValue();
        arkTextPickerOptions.range = Converter::ArkUnion<
            Ark_Type_TextPickerOptions_range,
            Array_String>(stringHolderValue);

        if (std::get<HAS_VALUES_ID>(value)) {
            Ark_String arkValue = Converter::ArkValue<Ark_String>(std::get<VALUES_ID>(value));
            arkTextPickerOptions.value = Converter::ArkUnion<Opt_Union_String_Array_String, Ark_String>(arkValue);
        } else {
            arkTextPickerOptions.value = Converter::ArkUnion<Opt_Union_String_Array_String>(Ark_Empty());
        }

        if (std::get<HAS_SELECTS_ID>(value)) {
            Ark_Number arkSelected = Converter::ArkValue<Ark_Number>(std::get<SELECTS_ID>(value));
            arkTextPickerOptions.selected =
                Converter::ArkUnion<Opt_Union_Number_Array_Number, Ark_Number>(arkSelected);
        } else {
            arkTextPickerOptions.selected =
                Converter::ArkUnion<Opt_Union_Number_Array_Number>(Ark_Empty());
        }
        Opt_TextPickerOptions inputValueOptions = Converter::ArkValue<Opt_TextPickerOptions>(arkTextPickerOptions);

        modifier_->setTextPickerOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
             
        //check "range"
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RANGE_NAME);
        expectedStr = std::get<RANGE_RES_ID>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);

        //check "value"
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        expectedStr = std::get<VALUES_RES_ID>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);

        //check "values"
        auto resultJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUES_NAME);
        ASSERT_NE(resultJson.get(), nullptr);
        EXPECT_EQ(true, resultJson.get()->IsArray()) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
        EXPECT_EQ(ATTRIBUTE_VALUES_DEFAULT_COUNT, resultJson.get()->GetArraySize())
            << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);

        //check "selected"
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_NAME);
        expectedStr = std::get<SELECTS_RES_ID>(value);
        EXPECT_EQ(resultStr, expectedStr)  << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);

        //check "selecteds"
        resultJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTEDS_NAME);
        ASSERT_NE(resultJson.get(), nullptr);
        EXPECT_EQ(true, resultJson.get()->IsArray()) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
        EXPECT_EQ(ATTRIBUTE_SELECTEDS_DEFAULT_COUNT, resultJson.get()->GetArraySize())
            << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    }
}

std::vector<Ark_TextPickerRangeContent> rangeContents {
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("ic1")),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("aa")) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("ic2")),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("bb")) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("ic3")),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("cc")) }
};

std::vector<Ark_TextPickerRangeContent> rangeContentsRes {
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_Resource>(CreateResource(RES_PIC_1_ID)),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_STR_1_ID)) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_Resource>(CreateResource(RES_PIC_2_ID)),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_STR_2_ID)) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_Resource>(CreateResource(RES_PIC_3_ID)),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_STR_3_ID)) }
};

std::vector<Ark_TextPickerRangeContent> rangeContentsMix {
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("icon0")),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("txt0")) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_Resource>(CreateResource(RES_PIC_1_ID)),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("txt1")) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("icon2")),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_STR_2_ID)) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_Resource>(CreateResource(RES_PIC_3_ID)),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_STR_3_ID)) }
};

static std::vector<std::tuple<std::string, std::vector<Ark_TextPickerRangeContent>, std::string, int32_t, bool, bool,
    std::string, std::string, std::string>> textPickerOptionsAsRangeArray = {
    {"range-picker#0", rangeContents, "bb", -1, true, true,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "0"},
    {"range-picker#1", rangeContents, "bb", 1, true, true,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "1"},
    {"range-picker#2", rangeContents, "aa", 2, true, true,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "2"},
    {"range-picker#3", rangeContents, "cc", 1, true, true,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "1"},
    {"range-picker#4", rangeContents, "bb", 1, false, false,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "0"},
    {"range-picker#5", rangeContents, "cc", 0, true, false,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "0"},
    {"range-picker#6", rangeContents, "dd", 1, true, false,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "0"},
    {"range-picker#7", rangeContents, "", 2, false, true,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "2"},
    {"range-picker#8", rangeContents, "dd", 3, true, true,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "0"},
    {"range-picker#9", rangeContentsRes, "", 0, false, false,
        "[\"icon:pic1,text:str1\",\"icon:pic2,text:str2\",\"icon:pic3,text:str3\"]", "", "0"},
    {"range-picker#10", rangeContentsMix, "", 0, false, false,
        "[\"icon:icon0,text:txt0\",\"icon:pic1,text:txt1\",\"icon:icon2,text:str2\",\"icon:pic3,text:str3\"]",
        "", "0"}
};

/*
 * @tc.name: setTextPickerOptionsAsRangeArray
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setTextPickerOptionsAsRangeArray, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;

    for (auto&& value: textPickerOptionsAsRangeArray) {
        Ark_TextPickerOptions arkTextPickerOptions;
        Converter::ArkArrayHolder<Array_TextPickerRangeContent> holder(std::get<RANGE_ID>(value));
        Array_TextPickerRangeContent holderValue = holder.ArkValue();
        arkTextPickerOptions.range = Converter::ArkUnion<
            Ark_Type_TextPickerOptions_range,
            Array_TextPickerRangeContent>(holderValue);

        if (std::get<HAS_VALUES_ID>(value)) {
            Ark_String arkValue = Converter::ArkValue<Ark_String>(std::get<VALUES_ID>(value));
            arkTextPickerOptions.value = Converter::ArkUnion<Opt_Union_String_Array_String, Ark_String>(arkValue);
        } else {
            arkTextPickerOptions.value = Converter::ArkUnion<Opt_Union_String_Array_String>(Ark_Empty());
        }

        if (std::get<HAS_SELECTS_ID>(value)) {
            Ark_Number arkSelected = Converter::ArkValue<Ark_Number>(std::get<SELECTS_ID>(value));
            arkTextPickerOptions.selected =
                Converter::ArkUnion<Opt_Union_Number_Array_Number, Ark_Number>(arkSelected);
        } else {
            arkTextPickerOptions.selected =
                Converter::ArkUnion<Opt_Union_Number_Array_Number>(Ark_Empty());
        }
        Opt_TextPickerOptions inputValueOptions = Converter::ArkValue<Opt_TextPickerOptions>(arkTextPickerOptions);

        modifier_->setTextPickerOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
             
        //check "range"
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RANGE_NAME);
        expectedStr = std::get<RANGE_RES_ID>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);

        //check "value"
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        expectedStr = std::get<VALUES_RES_ID>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);

        //check "values"
        auto resultJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUES_NAME);
        ASSERT_NE(resultJson.get(), nullptr);
        EXPECT_EQ(true, resultJson.get()->IsArray()) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
        EXPECT_EQ(ATTRIBUTE_VALUES_DEFAULT_COUNT, resultJson.get()->GetArraySize())
            << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);

        //check "selected"
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_NAME);
        expectedStr = std::get<SELECTS_RES_ID>(value);
        EXPECT_EQ(resultStr, expectedStr)  << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);

        //check "selecteds"
        resultJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTEDS_NAME);
        ASSERT_NE(resultJson.get(), nullptr);
        EXPECT_EQ(true, resultJson.get()->IsArray()) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
        EXPECT_EQ(ATTRIBUTE_SELECTEDS_DEFAULT_COUNT, resultJson.get()->GetArraySize())
            << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    }
}

typedef std::tuple<std::string, std::vector<std::vector<std::string>>, std::vector<std::string>,
    std::vector<int32_t>, bool, bool, std::string, std::vector<std::string>,
    std::vector<std::string>> multu_array_test_data;

static std::vector<multu_array_test_data> textPickerOptionsAsStringMultiArray = {
    {"multi-column-picker#0", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {}, {}, false, false,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"aa\"", "\"dd\""}, {"\"0\"", "\"0\""}},
    {"multi-column-picker#1", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb", "ee"}, {}, true, false,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"ee\""}, {"\"1\"", "\"1\""}},
    {"multi-column-picker#2", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb", "ee"}, {}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"ee\""}, {"\"0\"", "\"0\""}},
    {"multi-column-picker#3", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb", "ee"}, {1, 2}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"ee\""}, {"\"1\"", "\"2\""}},
    {"multi-column-picker#4", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {}, {2, 1}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"aa\"", "\"dd\""}, {"\"2\"", "\"1\""}},
    {"multi-column-picker#5", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {}, {}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"aa\"", "\"dd\""}, {"\"0\"", "\"0\""}},
    {"multi-column-picker#6", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb"}, {}, true, false,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"dd\""}, {"\"1\"", "\"0\""}},
    {"multi-column-picker#7", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb"}, {}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"dd\""}, {"\"0\"", "\"0\""}},
    {"multi-column-picker#8", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb"}, {2}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"dd\""}, {"\"2\"", "\"0\""}},
    {"multi-column-picker#9", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"hh", "gg"}, {}, true, false,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"aa\"", "\"dd\""}, {"\"0\"", "\"0\""}},
    {"multi-column-picker#10", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb", "ee", "hh"}, {}, true, false,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"ee\""}, {"\"1\"", "\"1\""}},
    {"multi-column-picker#11", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb", "ee"}, {3, 3}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"ee\""}, {"\"0\"", "\"0\""}},
    {"multi-column-picker#12", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"aa", "dd"}, {1, 1, 1}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"aa\"", "\"dd\""}, {"\"1\"", "\"1\""}},
    {"multi-column-picker#13", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"cc", "ff"}, {-1, -1}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"cc\"", "\"ff\""}, {"\"0\"", "\"0\""}}
};

void MultiArrayPickerTestProcedure (std::unique_ptr<JsonValue>& jsonValue, multu_array_test_data value)
{
    std::string resultStr;
    std::string expectedStr;

    //check "range"
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RANGE_NAME);
    expectedStr = std::get<RANGE_RES_ID>(value);
    EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);

    //check "value"
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    expectedStr = ATTRIBUTE_VALUE_DEFAULT_VALUE;
    EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);

    //check "values"
    auto attrValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUES_NAME);
    auto resultJson = attrValue.get();
    ASSERT_NE(resultJson, nullptr);
    EXPECT_EQ(true, resultJson->IsArray()) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    auto requiredValuesCount = std::get<RANGE_ID>(value).size();
    ASSERT_EQ(requiredValuesCount, resultJson->GetArraySize())
        << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    ASSERT_EQ(requiredValuesCount, std::get<VALUES_RES_ID>(value).size())
        << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    for (int i = 0; i < requiredValuesCount; i++) {
        resultStr = resultJson->GetArrayItem(i)->ToString();
        expectedStr = std::get<VALUES_RES_ID>(value)[i];
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    }

    //check "selected"
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_NAME);
    expectedStr = ATTRIBUTE_SELECTED_DEFAULT_VALUE;
    EXPECT_EQ(resultStr, expectedStr)  << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);

    //check "selecteds"
    attrValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTEDS_NAME);
    resultJson = attrValue.get();
    ASSERT_NE(resultJson, nullptr);
    EXPECT_EQ(true, resultJson->IsArray()) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    auto requiredSelectedsCount = std::get<RANGE_ID>(value).size();
    ASSERT_EQ(true, (requiredSelectedsCount <= resultJson->GetArraySize()))
        << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    ASSERT_EQ(requiredSelectedsCount, std::get<SELECTS_RES_ID>(value).size())
        << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    for (int i = 0; i < requiredSelectedsCount; i++) {
        resultStr = resultJson->GetArrayItem(i)->ToString();
        expectedStr = std::get<SELECTS_RES_ID>(value)[i];
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    }
}

/*
 * @tc.name: setTextPickerOptionsAsStringMultiArray
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setTextPickerOptionsAsStringMultiArray, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;

    for (auto&& value: textPickerOptionsAsStringMultiArray) {
        Ark_TextPickerOptions arkTextPickerOptions;

        std::vector<Array_String> vectorArrayString;
        auto rangeData = std::get<RANGE_ID>(value);
        Converter::ArkArrayHolder<Array_String> stringHolder1(rangeData[0]);
        Array_String stringHolderValue1 = stringHolder1.ArkValue();
        vectorArrayString.emplace_back(stringHolderValue1);

        Converter::ArkArrayHolder<Array_String> stringHolder2(rangeData[1]);
        Array_String stringHolderValue2 = stringHolder2.ArkValue();
        vectorArrayString.emplace_back(stringHolderValue2);

        Converter::ArkArrayHolder<Array_Array_String> holder(vectorArrayString);
        Array_Array_String stringMultiArray = holder.ArkValue();

        arkTextPickerOptions.range = Converter::ArkUnion<
            Ark_Type_TextPickerOptions_range,
            Array_Array_String>(stringMultiArray);

        Converter::ArkArrayHolder<Array_String> arkValueHolder(std::get<VALUES_ID>(value));
        Array_String arkValue = arkValueHolder.ArkValue();

        if (std::get<HAS_VALUES_ID>(value)) {
            arkTextPickerOptions.value = Converter::ArkUnion<Opt_Union_String_Array_String, Array_String>(arkValue);
        } else {
            arkTextPickerOptions.value = Converter::ArkUnion<Opt_Union_String_Array_String>(Ark_Empty());
        }

        Converter::ArkArrayHolder<Array_Number> arkSelectedHolder(std::get<SELECTS_ID>(value));
        Array_Number arkSelected = arkSelectedHolder.ArkValue();

        if (std::get<HAS_SELECTS_ID>(value)) {
            arkTextPickerOptions.selected =
                Converter::ArkUnion<Opt_Union_Number_Array_Number, Array_Number>(arkSelected);
        } else {
            arkTextPickerOptions.selected = Converter::ArkUnion<Opt_Union_Number_Array_Number>(Ark_Empty());
        }
        Opt_TextPickerOptions inputValueOptions = Converter::ArkValue<Opt_TextPickerOptions>(arkTextPickerOptions);

        modifier_->setTextPickerOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);

        MultiArrayPickerTestProcedure(jsonValue, value);
    }
}

static std::string CASCADE1 =
    "[{\"text\":\"Category 1\", "
    "\"children\":[{\"text\":\"Subcategory 1\", "
    "\"children\":[{\"text\":\"Subcategory 2\"},{\"text\":\"Subcategory 3\"}]},"
    "{\"text\":\"item1\", "
    "\"children\":[{\"text\":\"item2\"},{\"text\":\"item3\"}]}]},"
    "{\"text\":\"Category 2\", \"children\":[{\"text\":\"Subcategory 1\", "
    "\"children\":[{\"text\":\"Subcategory 2\"},{\"text\":\"Subcategory 3\"}]},"
    "{\"text\":\"item1\", \"children\":[{\"text\":\"item2\"},{\"text\":\"item3\"}]}]}]";

typedef std::tuple<std::string, std::string, std::vector<std::string>, std::vector<int32_t>, bool, bool,
    std::string, std::vector<std::string>, std::vector<std::string>> cascade_test_data;

static std::vector<cascade_test_data> textPickerOptionsAsCascadeArray = {
    {"cascade-picker#1", "", {}, {}, false, false, CASCADE1,
        {"\"Category 1\"", "\"Subcategory 1\"", "\"Subcategory 2\""}, {"\"0\"", "\"0\"", "\"0\""}}
};

Ark_TextCascadePickerRangeContent createCascadeLevel1(std::string str)
{
    Ark_String itemText = Converter::ArkValue<Ark_String>(str);
    Ark_TextCascadePickerRangeContent item;
    item.text = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(itemText);
    item.children = Converter::ArkValue<Opt_Array_TextCascadePickerRangeContent>(Ark_Empty());
    return item;
}

void InitChild(Ark_TextCascadePickerRangeContent& child, std::string name)
{
    Ark_String arkName = Converter::ArkValue<Ark_String>(name);
    child.text = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(arkName);
}

void CreateOptions(Array_TextCascadePickerRangeContent& arrayRoot,
    cascade_test_data value,
    Ark_TextPickerOptions& arkTextPickerOptions)
{
    arkTextPickerOptions.range = Converter::ArkUnion<Ark_Type_TextPickerOptions_range,
        Array_TextCascadePickerRangeContent>(arrayRoot);
    Converter::ArkArrayHolder<Array_String> arkValueHolder(std::get<VALUES_ID>(value));
    Array_String arkValue = arkValueHolder.ArkValue();
    if (std::get<HAS_VALUES_ID>(value)) {
        arkTextPickerOptions.value = Converter::ArkUnion<Opt_Union_String_Array_String, Array_String>(arkValue);
    } else {
        arkTextPickerOptions.value = Converter::ArkUnion<Opt_Union_String_Array_String>(Ark_Empty());
    }
    Converter::ArkArrayHolder<Array_Number> arkSelectedHolder(std::get<SELECTS_ID>(value));
    Array_Number arkSelected = arkSelectedHolder.ArkValue();
    if (std::get<HAS_SELECTS_ID>(value)) {
        arkTextPickerOptions.selected =
            Converter::ArkUnion<Opt_Union_Number_Array_Number, Array_Number>(arkSelected);
    } else {
        arkTextPickerOptions.selected = Converter::ArkUnion<Opt_Union_Number_Array_Number>(Ark_Empty());
    }
}

void CascadePickerTestProcedure (std::unique_ptr<JsonValue>& jsonValue, cascade_test_data value)
{
    std::string resultStr;
    std::string expectedStr;
             
    //check "range"
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RANGE_NAME);
    expectedStr = std::get<RANGE_RES_ID>(value);
    EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    //check "value"
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    expectedStr = ATTRIBUTE_VALUE_DEFAULT_VALUE;
    EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    //check "values"
    auto attrValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUES_NAME);
    auto resultJson = attrValue.get();
    ASSERT_NE(resultJson, nullptr);
    EXPECT_EQ(true, resultJson->IsArray()) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    ASSERT_EQ(resultJson->GetArraySize(), std::get<VALUES_RES_ID>(value).size())
        << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    for (int i = 0; i < resultJson->GetArraySize(); i++) {
        resultStr = resultJson->GetArrayItem(i)->ToString();
        expectedStr = std::get<VALUES_RES_ID>(value)[i];
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    }
    //check "select"
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_NAME);
    expectedStr = ATTRIBUTE_SELECTED_DEFAULT_VALUE;
    EXPECT_EQ(resultStr, expectedStr)  << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    //check "selects"
    attrValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTEDS_NAME);
    resultJson = attrValue.get();
    ASSERT_NE(resultJson, nullptr);
    EXPECT_EQ(true, resultJson->IsArray()) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    ASSERT_EQ(resultJson->GetArraySize(), std::get<SELECTS_RES_ID>(value).size())
        << "Passed value is: "<< std::get<TEST_COMMENT_ID>(value);
    for (int i = 0; i < resultJson->GetArraySize(); i++) {
        resultStr = resultJson->GetArrayItem(i)->ToString();
        expectedStr = std::get<SELECTS_RES_ID>(value)[i];
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    }
}
/*
 * @tc.name: setTextPickerOptionsAsCascadeArray
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setTextPickerOptionsAsCascadeArray, TestSize.Level1)
{
    std::vector<Ark_TextCascadePickerRangeContent> subcategoryVector;
    subcategoryVector.push_back(createCascadeLevel1(NAME_SUBCATEGORY_2));
    subcategoryVector.push_back(createCascadeLevel1(NAME_SUBCATEGORY_3));
    Converter::ArkArrayHolder<Array_TextCascadePickerRangeContent> holderSubcategoryVector(subcategoryVector);
    Opt_Array_TextCascadePickerRangeContent optArraySubcategory =
        holderSubcategoryVector.OptValue<Opt_Array_TextCascadePickerRangeContent>();
    Ark_TextCascadePickerRangeContent child1;
    InitChild(child1, NAME_SUBCATEGORY_1);
    child1.children = optArraySubcategory;

    std::vector<Ark_TextCascadePickerRangeContent> itemVector;
    itemVector.push_back(createCascadeLevel1(NAME_ITEM_2));
    itemVector.push_back(createCascadeLevel1(NAME_ITEM_3));
    Converter::ArkArrayHolder<Array_TextCascadePickerRangeContent> holderItemVector(itemVector);
    Opt_Array_TextCascadePickerRangeContent optArrayItem =
        holderItemVector.OptValue<Opt_Array_TextCascadePickerRangeContent>();
    Ark_TextCascadePickerRangeContent child2;
    InitChild(child2, NAME_ITEM_1);
    child2.children = optArrayItem;

    std::vector<Ark_TextCascadePickerRangeContent> childrenVector;
    childrenVector.push_back(child1);
    childrenVector.push_back(child2);
    Converter::ArkArrayHolder<Array_TextCascadePickerRangeContent> holderChildrenVector(childrenVector);
    Opt_Array_TextCascadePickerRangeContent optArrayChildren =
        holderChildrenVector.OptValue<Opt_Array_TextCascadePickerRangeContent>();
    Ark_TextCascadePickerRangeContent main1;
    InitChild(main1, NAME_CATEGORY_1);
    main1.children = optArrayChildren;
    Ark_TextCascadePickerRangeContent main2;
    InitChild(main2, NAME_CATEGORY_2);
    main2.children = optArrayChildren;

    std::vector<Ark_TextCascadePickerRangeContent> rootVector;
    rootVector.push_back(main1);
    rootVector.push_back(main2);
    Converter::ArkArrayHolder<Array_TextCascadePickerRangeContent> holderRootVector(rootVector);
    Array_TextCascadePickerRangeContent arrayRoot = holderRootVector.ArkValue();
    
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    for (auto&& value: textPickerOptionsAsCascadeArray) {
        Ark_TextPickerOptions arkTextPickerOptions;
        CreateOptions(arrayRoot, value, arkTextPickerOptions);
        Opt_TextPickerOptions inputValueOptions = Converter::ArkValue<Opt_TextPickerOptions>(arkTextPickerOptions);

        modifier_->setTextPickerOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        CascadePickerTestProcedure(jsonValue, value);
    }
}


/*
 * @tc.name: DISABLED_setOnChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, DISABLED_setOnChangeTest, TestSize.Level1)
{
    // Callback implementation is blocked
}

} // namespace OHOS::Ace::NG
