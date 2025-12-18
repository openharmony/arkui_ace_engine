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
#include "accessor_test_base.h"
#include "gmock/gmock.h"
#include "node_api.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "test/unittest/capi/stubs/mock_time_picker_dialog_view.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

namespace {
const std::string TEST_COLOR = "#FF012345";
const float TEST_SIZE = 13.0f;
const float TEST_RADIUS_SIZE = 5.0f;
const PickerTime TEST_PICKER_TIME(23, 11, 58);
} // namespace

using namespace testing;
using namespace testing::ext;

class TimePickerDialogAccessorTest : public StaticAccessorTest<GENERATED_ArkUITimePickerDialogAccessor,
    &GENERATED_ArkUIAccessors::getTimePickerDialogAccessor> {
};

/**
 * @tc.name: timePickerDialogAccessorDialogPropertiesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogAccessorTest, timePickerDialogAccessorDialogPropertiesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TimePickerDialogOptions arkOptions;
    arkOptions.alignment = Converter::ArkValue<Opt_DialogAlignment>(ARK_DIALOG_ALIGNMENT_TOP);
    Ark_Offset offset = { .dx = Converter::ArkValue<Ark_Length>(TEST_SIZE),
        .dy = Converter::ArkValue<Ark_Length>(TEST_SIZE) };
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

    Opt_TimePickerDialogOptions options = Converter::ArkValue<Opt_TimePickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    auto props = MockTimePickerDialogView::GetDialogProperties();
    EXPECT_EQ(props.alignment, DialogAlignment::TOP);
    EXPECT_EQ(
        props.offset, DimensionOffset(
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
 * @tc.name: timePickerDialogAccessorDialogPropertiesCallbacksTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogAccessorTest, timePickerDialogAccessorDialogPropertiesCallbacksTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TimePickerDialogOptions arkOptions;
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

    Opt_TimePickerDialogOptions options = Converter::ArkValue<Opt_TimePickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    EXPECT_FALSE(willAppearCalled);
    EXPECT_FALSE(didAppearCalled);
    EXPECT_FALSE(willDisappearCalled);
    EXPECT_FALSE(didDisappearCalled);

    MockTimePickerDialogView::FireWillAppear();
    EXPECT_TRUE(willAppearCalled);
    MockTimePickerDialogView::FireDidAppear();
    EXPECT_TRUE(didAppearCalled);
    MockTimePickerDialogView::FireWillDisappear();
    EXPECT_TRUE(willDisappearCalled);
    MockTimePickerDialogView::FireDidDisappear();
    EXPECT_TRUE(didDisappearCalled);
}

/**
 * @tc.name: timePickerDialogAccessorButtonInfosTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogAccessorTest, timePickerDialogAccessorButtonInfosTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TimePickerDialogOptions arkOptions;

    Ark_PickerDialogButtonStyle buttonStyle = {
        .fontSize = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(TEST_SIZE)),
        .fontColor = Converter::ArkValue<Opt_ResourceColor>(
            Converter::ArkUnion<Ark_ResourceColor, Ark_String>(TEST_COLOR))
    };
    arkOptions.acceptButtonStyle = Converter::ArkValue<Opt_PickerDialogButtonStyle>(buttonStyle);
    arkOptions.cancelButtonStyle = Converter::ArkValue<Opt_PickerDialogButtonStyle>(buttonStyle);

    Opt_TimePickerDialogOptions options = Converter::ArkValue<Opt_TimePickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    auto buttonInfos = MockTimePickerDialogView::GetButtonInfos();
    ASSERT_EQ(buttonInfos.size(), 2);
    auto acceptStyle = buttonInfos.at(0);
    EXPECT_EQ(acceptStyle.fontSize, Dimension(TEST_SIZE, DimensionUnit::VP));
    EXPECT_TRUE(acceptStyle.fontColor->MatchColorHexString(TEST_COLOR));
    auto cancelStyle = buttonInfos.at(1);
    EXPECT_EQ(cancelStyle.fontSize, Dimension(TEST_SIZE, DimensionUnit::VP));
    EXPECT_TRUE(cancelStyle.fontColor->MatchColorHexString(TEST_COLOR));
}

/**
 * @tc.name: timePickerDialogAccessorSettingDataTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogAccessorTest, timePickerDialogAccessorSettingDataTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TimePickerDialogOptions arkOptions;

    arkOptions.useMilitaryTime = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(true));
    arkOptions.format = Converter::ArkValue<Opt_TimePickerFormat>(ARK_TIME_PICKER_FORMAT_HOUR_MINUTE_SECOND);
    Ark_Font font = {
        .size = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(TEST_SIZE)),
    };
    Ark_PickerTextStyle style = {
        .font = Converter::ArkValue<Opt_arkui_component_units_Font>(font)
    };
    arkOptions.textStyle = Converter::ArkValue<Opt_PickerTextStyle>(style);
    arkOptions.disappearTextStyle = Converter::ArkValue<Opt_PickerTextStyle>(style);
    arkOptions.selectedTextStyle = Converter::ArkValue<Opt_PickerTextStyle>(style);

    Opt_TimePickerDialogOptions options = Converter::ArkValue<Opt_TimePickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    auto settingData = MockTimePickerDialogView::GetSettingData();
    EXPECT_TRUE(settingData.showSecond);
    EXPECT_TRUE(settingData.isUseMilitaryTime);
    EXPECT_EQ(settingData.properties.normalTextStyle_.fontSize.value(), Dimension(TEST_SIZE, DimensionUnit::VP));
    EXPECT_EQ(settingData.properties.disappearTextStyle_.fontSize.value(), Dimension(TEST_SIZE, DimensionUnit::VP));
    EXPECT_EQ(settingData.properties.selectedTextStyle_.fontSize.value(), Dimension(TEST_SIZE, DimensionUnit::VP));
}

/**
 * @tc.name: timePickerDialogAccessorPickerPropertyTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogAccessorTest, timePickerDialogAccessorPickerPropertyTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);
    std::tm tm {};
    tm.tm_hour = 3;
    tm.tm_min = 25;
    tm.tm_sec = 17;
    auto timestamp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    auto duration = timestamp.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    Ark_Date arkDate = static_cast<Ark_Date>(milliseconds);
    Opt_Date testDate = Converter::ArkValue<Opt_Date>(arkDate);

    Ark_TimePickerDialogOptions arkOptions;
    arkOptions.selected = testDate;

    Opt_TimePickerDialogOptions options = Converter::ArkValue<Opt_TimePickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    auto pickerTime = MockTimePickerDialogView::GetPickerTime();
    EXPECT_EQ(pickerTime.GetHour(), 3);
    EXPECT_EQ(pickerTime.GetMinute(), 25);
    EXPECT_EQ(pickerTime.GetSecond(), 17);
}

/**
 * @tc.name: timePickerDialogAccessorCallbacksTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogAccessorTest, timePickerDialogAccessorCallbacksTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->show, nullptr);

    Ark_TimePickerDialogOptions arkOptions;

    auto json = JsonUtil::Create(true);
    json->Put("hour", static_cast<int32_t>(TEST_PICKER_TIME.GetHour()));
    json->Put("minute", static_cast<int32_t>(TEST_PICKER_TIME.GetMinute()));
    json->Put("second", static_cast<int32_t>(TEST_PICKER_TIME.GetSecond()));

    static uint32_t contextId = 123;
    static bool wasCancelled = false;
    auto onCancelCallback = [](const Ark_Int32 resourceId) {
        wasCancelled = true;
    };
    static std::optional<Ark_TimePickerResult> acceptedRes;
    auto onAcceptCallback = [](const Ark_Int32 resourceId, const Ark_TimePickerResult info) {
        acceptedRes = info;
    };
    static std::optional<Ark_TimePickerResult> changedRes;
    auto onChangeCallback = [](const Ark_Int32 resourceId, const Ark_TimePickerResult info) {
        changedRes = info;
    };
    arkOptions.onCancel = Converter::ArkValue<Opt_Callback_Void>(
        Converter::ArkValue<Callback_Void>(onCancelCallback, contextId));
    arkOptions.onAccept = Converter::ArkValue<Opt_Callback_TimePickerResult_Void>(
        Converter::ArkValue<Callback_TimePickerResult_Void>(onAcceptCallback, contextId));
    arkOptions.onChange = Converter::ArkValue<Opt_Callback_TimePickerResult_Void>(
        Converter::ArkValue<Callback_TimePickerResult_Void>(onChangeCallback, contextId));

    Opt_TimePickerDialogOptions options = Converter::ArkValue<Opt_TimePickerDialogOptions>(arkOptions);
    accessor_->show(&options);

    EXPECT_FALSE(wasCancelled);
    MockTimePickerDialogView::FireCancelEvent();
    EXPECT_TRUE(wasCancelled);

    EXPECT_FALSE(acceptedRes.has_value());
    MockTimePickerDialogView::FireAcceptEvent(json->ToString());
    ASSERT_TRUE(acceptedRes.has_value());
    auto acceptedTime = Converter::OptConvert<PickerTime>(*acceptedRes);
    ASSERT_TRUE(acceptedTime.has_value());
    EXPECT_EQ(acceptedTime->GetHour(), TEST_PICKER_TIME.GetHour());
    EXPECT_EQ(acceptedTime->GetMinute(), TEST_PICKER_TIME.GetMinute());
    EXPECT_EQ(acceptedTime->GetSecond(), TEST_PICKER_TIME.GetSecond());

    EXPECT_FALSE(changedRes.has_value());
    MockTimePickerDialogView::FireChangeEvent(json->ToString());
    ASSERT_TRUE(changedRes.has_value());
    auto changedTime = Converter::OptConvert<PickerTime>(*changedRes);
    ASSERT_TRUE(changedTime.has_value());
    EXPECT_EQ(changedTime->GetHour(), TEST_PICKER_TIME.GetHour());
    EXPECT_EQ(changedTime->GetMinute(), TEST_PICKER_TIME.GetMinute());
    EXPECT_EQ(changedTime->GetSecond(), TEST_PICKER_TIME.GetSecond());
}
} // namespace OHOS::Ace::NG
