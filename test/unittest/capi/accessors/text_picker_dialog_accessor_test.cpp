/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "node_api.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "test/unittest/capi/stubs/mock_text_picker_dialog_view.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"

namespace OHOS::Ace::NG {

namespace {
const std::string TEST_NAME1 = "aa";
const std::string TEST_NAME2 = "bb";
const std::string TEST_NAME3 = "cc";
const std::vector<std::string> testValues { TEST_NAME1, TEST_NAME2, TEST_NAME3 };
const std::vector<uint32_t> testIndexes = { 1, 2, 3 };
const std::vector<std::pair<std::string, std::string>> rangeVectorValues {
    { TEST_NAME1, "ic1" },
    { TEST_NAME2, "ic2" },
    { TEST_NAME3, "ic3" }
};
std::vector<Ark_TextPickerRangeContent> rangeVector {
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(
        Converter::ArkValue<Ark_String>(std::get<1>(rangeVectorValues.at(0)))),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(
            Converter::ArkValue<Ark_String>(std::get<0>(rangeVectorValues.at(0)))) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(
        Converter::ArkValue<Ark_String>(std::get<1>(rangeVectorValues.at(1)))),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(
            Converter::ArkValue<Ark_String>(std::get<0>(rangeVectorValues.at(1)))) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(
        Converter::ArkValue<Ark_String>(std::get<1>(rangeVectorValues.at(2)))),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(
            Converter::ArkValue<Ark_String>(std::get<0>(rangeVectorValues.at(2)))) }
};

std::vector<Ark_TextCascadePickerRangeContent> cascadeOptions {
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(testValues[0]),
        Converter::ArkValue<Opt_Array_TextCascadePickerRangeContent>(Ark_Empty()) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(testValues[1]),
        Converter::ArkValue<Opt_Array_TextCascadePickerRangeContent>(Ark_Empty()) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(testValues[2]),
        Converter::ArkValue<Opt_Array_TextCascadePickerRangeContent>(Ark_Empty()) }
};

typedef std::tuple<std::vector<uint32_t>, std::vector<uint32_t>, std::vector<std::string>> SelectedIndexTestStep;
const std::vector<SelectedIndexTestStep> CASCADE_SELECTED_INDEX_TEST_PLAN = {
    { { 0, 0 }, { 0, 0 }, { TEST_NAME1, TEST_NAME1 } },
    { { 1, 5 }, { 1, 0 }, { TEST_NAME2, TEST_NAME1 } },
    { { 2, 3 }, { 2, 0 }, { TEST_NAME3, TEST_NAME1 } },
    { { 10, 10 }, { 0, 0 }, { TEST_NAME1, TEST_NAME1 } }
};

typedef std::tuple<std::vector<std::string>, std::vector<uint32_t>, std::vector<std::string>> SelectedValueTestStep;
const std::vector<SelectedValueTestStep> CASCADE_SELECTED_VALUE_TEST_PLAN = {
    { { TEST_NAME1, TEST_NAME1 }, { 0, 0 }, { TEST_NAME1, TEST_NAME1 } },
    { { TEST_NAME2, "dd" }, { 1, 0 }, { TEST_NAME2, TEST_NAME1 } },
    { { TEST_NAME3, TEST_NAME1 }, { 2, 0 }, { TEST_NAME3, TEST_NAME1 } },
    { { "dd", "ee" }, { 0, 0 }, { TEST_NAME1, TEST_NAME1 } }
};

const std::string TEST_COLOR = "#FF012345";
const float TEST_SIZE = 13.0f;
const float TEST_RADIUS_SIZE = 5.0f;
const std::string TEST_VALUE_STR = testValues[0];
} // namespace

using namespace testing;
using namespace testing::ext;

class TextPickerDialogAccessorTest : public StaticAccessorTest<GENERATED_ArkUITextPickerDialogAccessor,
    &GENERATED_ArkUIAccessors::getTextPickerDialogAccessor> {
};

/**
 * @tc.name: textPickerDialogAccessorDialogPropertiesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDialogAccessorTest, textPickerDialogAccessorDialogPropertiesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TextPickerDialogOptions arkOptions;
    arkOptions.alignment = Converter::ArkValue<Opt_DialogAlignment>(ARK_DIALOG_ALIGNMENT_TOP);
    Ark_Offset offset = {
        .dx = Converter::ArkValue<Ark_Length>(TEST_SIZE),
        .dy = Converter::ArkValue<Ark_Length>(TEST_SIZE)
    };
    arkOptions.offset = Converter::ArkValue<Opt_Offset>(offset);
    arkOptions.backgroundBlurStyle = Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_BACKGROUND_ULTRA_THICK);
    arkOptions.backgroundColor =
        Converter::ArkValue<Opt_ResourceColor>(Converter::ArkUnion<Ark_ResourceColor, Ark_String>(TEST_COLOR));
    Ark_ShadowOptions shadow = {
        .color = Converter::ArkUnion<
            Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy, Ark_String>(TEST_COLOR),
        .offsetX = Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(TEST_SIZE),
        .offsetY = Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(TEST_SIZE),
        .radius = Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(TEST_RADIUS_SIZE),
        .type = Converter::ArkValue<Opt_ShadowType>(ARK_SHADOW_TYPE_COLOR),
    };
    arkOptions.shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(shadow);
    arkOptions.enableHoverMode = Converter::ArkValue<Opt_Boolean>(true);
    arkOptions.hoverModeArea = Converter::ArkValue<Opt_HoverModeAreaType>(ARK_HOVER_MODE_AREA_TYPE_BOTTOM_SCREEN);

    Opt_TextPickerDialogOptions options = Converter::ArkValue<Opt_TextPickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    auto props = MockTextPickerDialogView::GetDialogProperties();
    EXPECT_EQ(props.alignment, DialogAlignment::TOP);
    EXPECT_EQ(props.offset, DimensionOffset(
        Dimension(TEST_SIZE, DimensionUnit::VP),
        Dimension(TEST_SIZE, DimensionUnit::VP)));
    EXPECT_EQ(props.backgroundBlurStyle.value(), static_cast<uint32_t>(BlurStyle::BACKGROUND_ULTRA_THICK));
    EXPECT_TRUE(props.backgroundColor->MatchColorHexString(TEST_COLOR));
    ASSERT_TRUE(props.shadow.has_value());
    EXPECT_TRUE(props.shadow->GetColor().MatchColorHexString(TEST_COLOR));
    EXPECT_EQ(props.shadow->GetOffset(), Offset(TEST_SIZE, TEST_SIZE));
    EXPECT_EQ(props.shadow->GetBlurRadius(), TEST_RADIUS_SIZE);
    EXPECT_EQ(props.shadow->GetShadowType(), ShadowType::COLOR);
    EXPECT_TRUE(props.enableHoverMode);
    EXPECT_EQ(props.hoverModeArea, HoverModeAreaType::BOTTOM_SCREEN);
}

/**
 * @tc.name: textPickerDialogAccessorDialogPropertiesCallbacksTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDialogAccessorTest, textPickerDialogAccessorDialogPropertiesCallbacksTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TextPickerDialogOptions arkOptions;
    static uint32_t contextId = 123;
    static bool willAppearCalled = false;
    static bool didAppearCalled = false;
    static bool willDisappearCalled = false;
    static bool didDisappearCalled = false;

    auto willAppearCallback = [](const Ark_Int32 resourceId) {
        willAppearCalled = true;
    };
    auto didAppearCallback = [](const Ark_Int32 resourceId) {
        didAppearCalled = true;
    };
    auto willDisappearCallback = [](const Ark_Int32 resourceId) {
        willDisappearCalled = true;
    };
    auto didDisappearCallback = [](const Ark_Int32 resourceId) {
        didDisappearCalled = true;
    };

    arkOptions.onWillAppear = Converter::ArkValue<Opt_Callback_Void>(
        Converter::ArkValue<Callback_Void>(willAppearCallback, contextId));
    arkOptions.onDidAppear = Converter::ArkValue<Opt_Callback_Void>(
        Converter::ArkValue<Callback_Void>(didAppearCallback, contextId));
    arkOptions.onWillDisappear = Converter::ArkValue<Opt_Callback_Void>(
        Converter::ArkValue<Callback_Void>(willDisappearCallback, contextId));
    arkOptions.onDidDisappear = Converter::ArkValue<Opt_Callback_Void>(
        Converter::ArkValue<Callback_Void>(didDisappearCallback, contextId));

    Opt_TextPickerDialogOptions options = Converter::ArkValue<Opt_TextPickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    EXPECT_FALSE(willAppearCalled);
    EXPECT_FALSE(didAppearCalled);
    EXPECT_FALSE(willDisappearCalled);
    EXPECT_FALSE(didDisappearCalled);

    MockTextPickerDialogView::FireWillAppear();
    EXPECT_TRUE(willAppearCalled);
    MockTextPickerDialogView::FireDidAppear();
    EXPECT_TRUE(didAppearCalled);
    MockTextPickerDialogView::FireWillDisappear();
    EXPECT_TRUE(willDisappearCalled);
    MockTextPickerDialogView::FireDidDisappear();
    EXPECT_TRUE(didDisappearCalled);
}

/**
 * @tc.name: textPickerDialogAccessorSettingDataCommonTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDialogAccessorTest, textPickerDialogAccessorSettingDataCommonTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TextPickerDialogOptions arkOptions;
    arkOptions.defaultPickerItemHeight = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(
        Converter::ArkValue<Ark_Number>(TEST_SIZE));
    arkOptions.canLoop = Converter::ArkValue<Opt_Boolean>(false);
    Ark_Font font = {
        .size = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(TEST_SIZE)),
    };
    Ark_PickerTextStyle style = {
        .font = Converter::ArkValue<Opt_arkui_component_units_Font>(font)
    };
    arkOptions.textStyle = Converter::ArkValue<Opt_PickerTextStyle>(style);
    arkOptions.disappearTextStyle = Converter::ArkValue<Opt_PickerTextStyle>(style);
    arkOptions.selectedTextStyle = Converter::ArkValue<Opt_PickerTextStyle>(style);

    Opt_TextPickerDialogOptions options = Converter::ArkValue<Opt_TextPickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    auto settingData = MockTextPickerDialogView::GetSettingData();
    EXPECT_EQ(settingData.height, Dimension(TEST_SIZE, DimensionUnit::VP));
    EXPECT_FALSE(settingData.canLoop);
    EXPECT_EQ(settingData.properties.normalTextStyle_.fontSize.value(), Dimension(TEST_SIZE, DimensionUnit::VP));
    EXPECT_EQ(settingData.properties.disappearTextStyle_.fontSize.value(), Dimension(TEST_SIZE, DimensionUnit::VP));
    EXPECT_EQ(settingData.properties.selectedTextStyle_.fontSize.value(), Dimension(TEST_SIZE, DimensionUnit::VP));
}

/**
 * @tc.name: textPickerDialogAccessorSettingDataRangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDialogAccessorTest, textPickerDialogAccessorSettingDataRangeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TextPickerDialogOptions arkOptions;
    Converter::ArkArrayHolder<Array_TextPickerRangeContent> holder(rangeVector);
    Array_TextPickerRangeContent holderValue = holder.ArkValue();
    arkOptions.range = Converter::ArkUnion<Ark_Type_TextPickerOptions_range, Array_TextPickerRangeContent>(
        holderValue);

    arkOptions.value = Converter::ArkUnion<Opt_Union_String_Array_String, Ark_String>(
        Converter::ArkValue<Ark_String>(TEST_VALUE_STR)
    );
    arkOptions.selected =
        Converter::ArkUnion<Opt_Union_Number_Array_Number, Ark_Number>(
            Converter::ArkValue<Ark_Number>(testIndexes.at(0)));

    Opt_TextPickerDialogOptions options = Converter::ArkValue<Opt_TextPickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    auto settingData = MockTextPickerDialogView::GetSettingData();
    EXPECT_EQ(settingData.options.size(), 0);
    ASSERT_EQ(settingData.rangeVector.size(), rangeVector.size());
    for (int i = 0; i < settingData.rangeVector.size(); i++) {
        EXPECT_EQ(settingData.rangeVector.at(i).text_, std::get<0>(rangeVectorValues.at(i)));
        EXPECT_EQ(settingData.rangeVector.at(i).icon_, std::get<1>(rangeVectorValues.at(i)));
    }
    EXPECT_EQ(settingData.selected, testIndexes.at(0));
}

/**
 * @tc.name: textPickerDialogAccessorSettingDataCascadeTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDialogAccessorTest, textPickerDialogAccessorSettingDataCascadeTest001, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TextPickerDialogOptions arkOptions;
    Converter::ArkArrayHolder<Array_TextCascadePickerRangeContent> cascadeHolder(cascadeOptions);
    Array_TextCascadePickerRangeContent cascadeHolderValue = cascadeHolder.ArkValue();
    arkOptions.range = Converter::ArkUnion<Ark_Type_TextPickerOptions_range, Array_TextCascadePickerRangeContent>(
        cascadeHolderValue);

    arkOptions.value = Converter::ArkUnion<Opt_Union_String_Array_String, Ark_String>(
        Converter::ArkValue<Ark_String>(TEST_VALUE_STR)
    );
    arkOptions.selected =
        Converter::ArkUnion<Opt_Union_Number_Array_Number, Ark_Number>(
            Converter::ArkValue<Ark_Number>(testIndexes.at(0)));

    Opt_TextPickerDialogOptions options = Converter::ArkValue<Opt_TextPickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    auto settingData = MockTextPickerDialogView::GetSettingData();
    EXPECT_EQ(settingData.rangeVector.size(), 0);
    ASSERT_EQ(settingData.options.size(), cascadeOptions.size());
    for (int i = 0; i < settingData.options.size(); i++) {
        EXPECT_EQ(settingData.options.at(i).rangeResult.at(0), testValues[i]);
    }
    EXPECT_EQ(settingData.values.size(), 1);
    EXPECT_EQ(settingData.values.at(0), testValues.at(testIndexes.at(0)));
    EXPECT_EQ(settingData.selectedValues.size(), 1);
    EXPECT_EQ(settingData.selectedValues.at(0), testIndexes.at(0));
}

/**
 * @tc.name: textPickerDialogAccessorSettingDataCascadeTest002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDialogAccessorTest, textPickerDialogAccessorSettingDataCascadeTest002, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);
    Ark_TextPickerDialogOptions arkOptions;

    Ark_TextCascadePickerRangeContent child;
    child.text = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(
        Converter::ArkValue<Ark_String>(TEST_NAME1));
    std::vector<Ark_TextCascadePickerRangeContent> childrenVector;
    childrenVector.push_back(child);
    Converter::ArkArrayHolder<Array_TextCascadePickerRangeContent> holderChildrenVector(childrenVector);
    Opt_Array_TextCascadePickerRangeContent optArrayChildren =
        holderChildrenVector.OptValue<Opt_Array_TextCascadePickerRangeContent>();

    std::vector<Ark_TextCascadePickerRangeContent> array;
    for (int i = 0; i < static_cast<int32_t>(testValues.size()); i++) {
        Ark_TextCascadePickerRangeContent item;
        item.text = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(
            Converter::ArkValue<Ark_String>(testValues.at(i)));
        item.children = optArrayChildren;
        array.push_back(item);
    }

    Converter::ArkArrayHolder<Array_TextCascadePickerRangeContent> arkHolder(array);
    Array_TextCascadePickerRangeContent holderValue = arkHolder.ArkValue();

    arkOptions.range =
        Converter::ArkUnion<Ark_Type_TextPickerOptions_range, Array_TextCascadePickerRangeContent>(holderValue);

    for (int i = 0; i < CASCADE_SELECTED_INDEX_TEST_PLAN.size(); i++) {
        auto testArray = std::get<0>(CASCADE_SELECTED_INDEX_TEST_PLAN.at(i));
        Converter::ArkArrayHolder<Array_Number> arkValueHolder(testArray);
        Array_Number arkValue = arkValueHolder.ArkValue();

        arkOptions.selected = Converter::ArkUnion<Opt_Union_Number_Array_Number, Array_Number>(arkValue);

        Opt_TextPickerDialogOptions options = Converter::ArkValue<Opt_TextPickerDialogOptions>(arkOptions);
        accessor_->show(&options);

        auto settingData = MockTextPickerDialogView::GetSettingData();
        auto expectedIndexesArray = std::get<1>(CASCADE_SELECTED_INDEX_TEST_PLAN.at(i));
        auto expectedValuesArray = std::get<2>(CASCADE_SELECTED_INDEX_TEST_PLAN.at(i));
        ASSERT_EQ(settingData.selectedValues.size(), expectedIndexesArray.size());
        ASSERT_EQ(settingData.values.size(), expectedValuesArray.size());

        for (int j = 0; j < expectedValuesArray.size(); j++) {
            EXPECT_EQ(settingData.selectedValues.at(j), expectedIndexesArray.at(j));
            EXPECT_EQ(settingData.values.at(j), expectedValuesArray.at(j));
        }
    }
}

/**
 * @tc.name: textPickerDialogAccessorSettingDataCascadeTest003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDialogAccessorTest, textPickerDialogAccessorSettingDataCascadeTest003, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);
    Ark_TextPickerDialogOptions arkOptions;

    Ark_TextCascadePickerRangeContent child;
    child.text = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(
        Converter::ArkValue<Ark_String>(TEST_NAME1));
    std::vector<Ark_TextCascadePickerRangeContent> childrenVector;
    childrenVector.push_back(child);
    Converter::ArkArrayHolder<Array_TextCascadePickerRangeContent> holderChildrenVector(childrenVector);
    Opt_Array_TextCascadePickerRangeContent optArrayChildren =
        holderChildrenVector.OptValue<Opt_Array_TextCascadePickerRangeContent>();

    std::vector<Ark_TextCascadePickerRangeContent> array;
    for (int i = 0; i < static_cast<int32_t>(testValues.size()); i++) {
        Ark_TextCascadePickerRangeContent item;
        item.text = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(
            Converter::ArkValue<Ark_String>(testValues.at(i)));
        item.children = optArrayChildren;
        array.push_back(item);
    }

    Converter::ArkArrayHolder<Array_TextCascadePickerRangeContent> arkHolder(array);
    Array_TextCascadePickerRangeContent holderValue = arkHolder.ArkValue();

    arkOptions.range =
        Converter::ArkUnion<Ark_Type_TextPickerOptions_range, Array_TextCascadePickerRangeContent>(holderValue);

    for (int i = 0; i < CASCADE_SELECTED_VALUE_TEST_PLAN.size(); i++) {
        auto testArray = std::get<0>(CASCADE_SELECTED_VALUE_TEST_PLAN.at(i));
        Converter::ArkArrayHolder<Array_String> arkValueHolder(testArray);
        Array_String arkValue = arkValueHolder.ArkValue();

        arkOptions.value = Converter::ArkUnion<Opt_Union_String_Array_String, Array_String>(arkValue);

        std::vector<uint32_t> empty;
        Converter::ArkArrayHolder<Array_Number> numberHolder(empty);
        Array_Number numberHolderValue = numberHolder.ArkValue();
        arkOptions.selected = Converter::ArkUnion<Opt_Union_Number_Array_Number, Array_Number>(numberHolderValue);

        Opt_TextPickerDialogOptions options = Converter::ArkValue<Opt_TextPickerDialogOptions>(arkOptions);
        accessor_->show(&options);

        auto settingData = MockTextPickerDialogView::GetSettingData();
        auto expectedIndexesArray = std::get<1>(CASCADE_SELECTED_VALUE_TEST_PLAN.at(i));
        auto expectedValuesArray = std::get<2>(CASCADE_SELECTED_VALUE_TEST_PLAN.at(i));
        ASSERT_EQ(settingData.selectedValues.size(), expectedIndexesArray.size());
        ASSERT_EQ(settingData.values.size(), expectedValuesArray.size());

        for (int j = 0; j < expectedValuesArray.size(); j++) {
            EXPECT_EQ(settingData.selectedValues.at(j), expectedIndexesArray.at(j));
            EXPECT_EQ(settingData.values.at(j), expectedValuesArray.at(j));
        }
    }
}

/**
 * @tc.name: textPickerDialogAccessorButtonInfosTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDialogAccessorTest, textPickerDialogAccessorButtonInfosTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TextPickerDialogOptions arkOptions;

    Ark_PickerDialogButtonStyle buttonStyle = {
        .fontSize = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(TEST_SIZE)),
        .fontColor = Converter::ArkValue<Opt_ResourceColor>(
            Converter::ArkUnion<Ark_ResourceColor, Ark_String>(TEST_COLOR))
    };
    arkOptions.acceptButtonStyle = Converter::ArkValue<Opt_PickerDialogButtonStyle>(buttonStyle);
    arkOptions.cancelButtonStyle = Converter::ArkValue<Opt_PickerDialogButtonStyle>(buttonStyle);

    Opt_TextPickerDialogOptions options = Converter::ArkValue<Opt_TextPickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    auto buttonInfos = MockTextPickerDialogView::GetButtonInfos();
    ASSERT_EQ(buttonInfos.size(), 2);
    auto acceptStyle = buttonInfos.at(0);
    EXPECT_EQ(acceptStyle.fontSize, Dimension(TEST_SIZE, DimensionUnit::VP));
    EXPECT_TRUE(acceptStyle.fontColor->MatchColorHexString(TEST_COLOR));
    auto cancelStyle = buttonInfos.at(1);
    EXPECT_EQ(cancelStyle.fontSize, Dimension(TEST_SIZE, DimensionUnit::VP));
    EXPECT_TRUE(cancelStyle.fontColor->MatchColorHexString(TEST_COLOR));
}

/**
 * @tc.name: textPickerDialogAccessorCancelCallbackTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDialogAccessorTest, textPickerDialogAccessorCancelCallbackTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TextPickerDialogOptions arkOptions;
    static uint32_t contextId = 123;
    static bool wasCancelled = false;
    auto onCancelCallback = [](const Ark_Int32 resourceId) {
        EXPECT_EQ(contextId, Converter::Convert<int32_t>(resourceId));
        wasCancelled = true;
    };
    arkOptions.onCancel = Converter::ArkValue<Opt_Callback_Void>(
        Converter::ArkValue<Callback_Void>(onCancelCallback, contextId));

    Opt_TextPickerDialogOptions options = Converter::ArkValue<Opt_TextPickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    EXPECT_FALSE(wasCancelled);
    MockTextPickerDialogView::FireCancelEvent();
    EXPECT_TRUE(wasCancelled);
}

/**
 * @tc.name: textPickerDialogAccessorAcceptCallbackTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDialogAccessorTest, textPickerDialogAccessorAcceptCallbackTest001, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TextPickerDialogOptions arkOptions;
    auto strValue = TextPickerPattern::GetSelectedObjectStr(testValues.at(0), testIndexes.at(0));
    static uint32_t contextId = 123;

    auto onAcceptCallback = [](const Ark_Int32 resourceId, const Ark_TextPickerResult info) {
        EXPECT_EQ(contextId, Converter::Convert<int32_t>(resourceId));

        auto acceptedValue = Converter::OptConvert<std::string>(info.value);
        ASSERT_TRUE(acceptedValue.has_value());
        EXPECT_EQ(*acceptedValue, testValues.at(0));

        auto acceptedIndex = Converter::OptConvert<uint32_t>(info.index);
        ASSERT_TRUE(acceptedIndex.has_value());
        EXPECT_EQ(*acceptedIndex, testIndexes.at(0));
    };
    arkOptions.onAccept = Converter::ArkValue<Opt_Callback_TextPickerResult_Void>(
        Converter::ArkValue<Callback_TextPickerResult_Void>(onAcceptCallback, contextId));

    Opt_TextPickerDialogOptions options = Converter::ArkValue<Opt_TextPickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    MockTextPickerDialogView::FireAcceptEvent(strValue);
}

/**
 * @tc.name: textPickerDialogAccessorAcceptCallbackTest002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDialogAccessorTest, textPickerDialogAccessorAcceptCallbackTest002, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TextPickerDialogOptions arkOptions;
    auto strValue = TextPickerPattern::GetSelectedObjectMulti(testValues, testIndexes, 0);
    static uint32_t contextId = 123;

    auto onAcceptCallback = [](const Ark_Int32 resourceId, const Ark_TextPickerResult info) {
        EXPECT_EQ(contextId, Converter::Convert<int32_t>(resourceId));

        auto acceptedValues = Converter::OptConvert<std::vector<std::string>>(info.value);
        ASSERT_TRUE(acceptedValues.has_value());
        EXPECT_EQ(acceptedValues->size(), testValues.size());
        for (int i = 0; i < static_cast<int32_t>(acceptedValues->size()); i++) {
            EXPECT_EQ(acceptedValues->at(i), testValues.at(i));
        }

        auto acceptedIndexes = Converter::OptConvert<std::vector<uint32_t>>(info.index);
        ASSERT_TRUE(acceptedIndexes.has_value());
        EXPECT_EQ(acceptedIndexes->size(), testIndexes.size());
        for (int i = 0; i < static_cast<int32_t>(acceptedIndexes->size()); i++) {
            EXPECT_EQ(acceptedIndexes->at(i), testIndexes.at(i));
        }
    };
    arkOptions.onAccept = Converter::ArkValue<Opt_Callback_TextPickerResult_Void>(
        Converter::ArkValue<Callback_TextPickerResult_Void>(onAcceptCallback, contextId));

    Opt_TextPickerDialogOptions options = Converter::ArkValue<Opt_TextPickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    MockTextPickerDialogView::FireAcceptEvent(strValue);
}

/**
 * @tc.name: textPickerDialogAccessorChangeCallbackTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDialogAccessorTest, textPickerDialogAccessorChangeCallbackTest001, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TextPickerDialogOptions arkOptions;
    auto strValue = TextPickerPattern::GetSelectedObjectStr(testValues.at(0), testIndexes.at(0));
    static uint32_t contextId = 123;

    auto onChangeCallback = [](const Ark_Int32 resourceId, const Ark_TextPickerResult info) {
        EXPECT_EQ(contextId, Converter::Convert<int32_t>(resourceId));

        auto changedValue = Converter::OptConvert<std::string>(info.value);
        ASSERT_TRUE(changedValue.has_value());
        EXPECT_EQ(*changedValue, testValues.at(0));

        auto changedIndex = Converter::OptConvert<uint32_t>(info.index);
        ASSERT_TRUE(changedIndex.has_value());
        EXPECT_EQ(*changedIndex, testIndexes.at(0));
    };
    arkOptions.onChange = Converter::ArkValue<Opt_Callback_TextPickerResult_Void>(
        Converter::ArkValue<Callback_TextPickerResult_Void>(onChangeCallback, contextId));

    Opt_TextPickerDialogOptions options = Converter::ArkValue<Opt_TextPickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    MockTextPickerDialogView::FireChangeEvent(strValue);
}

/**
 * @tc.name: textPickerDialogAccessorChangeCallbackTest002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDialogAccessorTest, textPickerDialogAccessorChangeCallbackTest002, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TextPickerDialogOptions arkOptions;
    auto strValue = TextPickerPattern::GetSelectedObjectMulti(testValues, testIndexes, 0);
    static uint32_t contextId = 123;

    auto onChangeCallback = [](const Ark_Int32 resourceId, const Ark_TextPickerResult info) {
        EXPECT_EQ(contextId, Converter::Convert<int32_t>(resourceId));

        auto changedValues = Converter::OptConvert<std::vector<std::string>>(info.value);
        ASSERT_TRUE(changedValues.has_value());
        EXPECT_EQ(changedValues->size(), testValues.size());
        for (int i = 0; i < static_cast<int32_t>(changedValues->size()); i++) {
            EXPECT_EQ(changedValues->at(i), testValues.at(i));
        }

        auto changedIndexes = Converter::OptConvert<std::vector<uint32_t>>(info.index);
        ASSERT_TRUE(changedIndexes.has_value());
        EXPECT_EQ(changedIndexes->size(), testIndexes.size());
        for (int i = 0; i < static_cast<int32_t>(changedIndexes->size()); i++) {
            EXPECT_EQ(changedIndexes->at(i), testIndexes.at(i));
        }
    };
    arkOptions.onChange = Converter::ArkValue<Opt_Callback_TextPickerResult_Void>(
        Converter::ArkValue<Callback_TextPickerResult_Void>(onChangeCallback, contextId));

    Opt_TextPickerDialogOptions options = Converter::ArkValue<Opt_TextPickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    MockTextPickerDialogView::FireAcceptEvent(strValue);
}
} // namespace OHOS::Ace
