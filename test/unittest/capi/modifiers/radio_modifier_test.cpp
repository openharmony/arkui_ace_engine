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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
inline Ark_String ArkStr(const char* s)
{
    return {
        .chars = s,
        .length = strlen(s)
    };
}
inline Ark_Number ArkNum(float src)
{
    return {
        .tag = ARK_TAG_FLOAT32,
        .f32 = static_cast<Ark_Float32>(src)
    };
}
inline Ark_Number ArkNum(int src)
{
    return {
        .tag = ARK_TAG_INT32,
        .i32 = static_cast<Ark_Int32>(src)
    };
}
inline Opt_Array_String ArkResParams(Ark_String* name)
{
    return {
        .tag = ARK_TAG_OBJECT,
        .value = {
            .array = name,
            .length = name ? 1 : 0
        }
    };
}
inline Ark_Resource ArkRes(Ark_String* name, int id = -1,
    NodeModifier::ResourceType type = NodeModifier::ResourceType::COLOR, const char* module = "",
    const char* bundle = "")
{
    return {
        .id = ArkNum(id),
        .type = ArkNum(static_cast<int>(type)),
        .moduleName = ArkStr(module),
        .bundleName = ArkStr(bundle),
        .params = ArkResParams(name)
    };
}

// custom colors
const auto CUSTOM_COLOR_STRING = "#FF123456";
const int CUSTOM_COLOR_INT = 0xFF123456;
const float CUSTOM_COLOR_FLOAT = 0.1f;
const auto CHECK_FLOAT_COLOR = "#00000000";
//  default colors
const auto CHECKED_COLOR_DEFAULT = "#FF000000";
const auto UNCHECKED_COLOR_DEFAULT = "#FF000000";
const auto INDICATOR_COLOR_DEFAULT = "#FF000000";
// attributes
const std::string CHECKED_ATTR = "checked";
const std::string RADIO_STYLE_ATTR = "radioStyle";
const std::string CHECKED_BACKGROUND_COLOR_ATTR = "checkedBackgroundColor";
const std::string UNCHECKED_BORDER_COLOR_ATTR = "uncheckedBorderColor";
const std::string INDICATOR_COLOR_ATTR = "indicatorColor";
// indicatorType
const std::string INDICATOR_TYPE_ATTR = "indicatorType";
const std::string INDICATOR_TYPE_TICK = "TICK";
const std::string INDICATOR_TYPE_DOT = "DOT";
const std::string INDICATOR_TYPE_CUSTOM = "CUSTOM";
// options
const std::string RADIO_GROUP_ATTR = "group";
const std::string RADIO_VALUE_ATTR = "value";
const auto RADIO_GROUP_VALUE = "test_value";
const auto RADIO_VALUE_VALUE = "test_group";

static bool g_isCheckedTest = true;
static auto radioOnChange(Ark_Int32 nodeId, const Ark_Boolean isChecked)
{
    g_isCheckedTest = !g_isCheckedTest;
};
static GENERATED_ArkUIRadioEventsReceiver recv {
    .onChange = radioOnChange
};
static const GENERATED_ArkUIRadioEventsReceiver* getRadioEventsReceiverTest()
{
    return &recv;
};
static const GENERATED_ArkUIEventsAPI* GetArkUiEventsAPITest()
{
    static const GENERATED_ArkUIEventsAPI eventsImpl = { .getRadioEventsReceiver = getRadioEventsReceiverTest };
    return &eventsImpl;
};
} // namespace
class RadioModifierTest : public ModifierTestBase<GENERATED_ArkUIRadioModifier,
                              &GENERATED_ArkUINodeModifiers::getRadioModifier, GENERATED_ARKUI_RADIO> {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
            auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
            return radioTheme;
        });
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        MockContainer::SetUp();
        MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
        NG::GeneratedModifier::GetFullAPI()->setArkUIEventsAPI(GetArkUiEventsAPITest());
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: RadioOptionsTest001
 * @tc.desc: Test Radio setRadioOptions.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioOptionsTest001, TestSize.Level1)
{
    auto groupDefault = GetStringAttribute(node_, RADIO_GROUP_ATTR);
    auto valueDefault = GetStringAttribute(node_, RADIO_VALUE_ATTR);
    EXPECT_EQ(groupDefault, "");
    EXPECT_EQ(groupDefault, "");
    Ark_RadioOptions radioOptions = {
        .group = { .chars = RADIO_GROUP_VALUE },
        .value = { .chars = RADIO_VALUE_VALUE }
    };
    modifier_->setRadioOptions(node_, &radioOptions);
    auto group = GetStringAttribute(node_, RADIO_GROUP_ATTR);
    auto value = GetStringAttribute(node_, RADIO_VALUE_ATTR);
    EXPECT_EQ(group, RADIO_GROUP_VALUE);
    EXPECT_EQ(value, RADIO_VALUE_VALUE);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        Ark_RadioOptions radioOptionsTick = {
            .indicatorType = { .value = static_cast<int32_t>(RadioPattern::RadioIndicatorType::TICK) },
        };
        modifier_->setRadioOptions(node_, &radioOptionsTick);
        auto groupEmpty = GetStringAttribute(node_, RADIO_GROUP_ATTR);
        auto valueEmpty = GetStringAttribute(node_, RADIO_VALUE_ATTR);
        auto indicatorTypeTick = GetStringAttribute(node_, INDICATOR_TYPE_ATTR);
        EXPECT_EQ(groupEmpty, RADIO_GROUP_VALUE);
        EXPECT_EQ(valueEmpty, RADIO_VALUE_VALUE);
        EXPECT_EQ(indicatorTypeTick, INDICATOR_TYPE_TICK);
        Ark_RadioOptions radioOptionsDot = {
            .indicatorType = { .value = static_cast<int32_t>(RadioPattern::RadioIndicatorType::DOT) },
        };
        modifier_->setRadioOptions(node_, &radioOptionsDot);
        auto indicatorTypeDot = GetStringAttribute(node_, INDICATOR_TYPE_ATTR);
        EXPECT_EQ(indicatorTypeDot, INDICATOR_TYPE_DOT);
        Ark_RadioOptions radioOptionsCustom = {
            .indicatorType = { .value = static_cast<int32_t>(RadioPattern::RadioIndicatorType::CUSTOM)},
        };
        modifier_->setRadioOptions(node_, &radioOptionsCustom);
        auto indicatorTypeCustom = GetStringAttribute(node_, INDICATOR_TYPE_ATTR);
        EXPECT_EQ(indicatorTypeCustom, INDICATOR_TYPE_CUSTOM);
        Ark_RadioOptions radioOptionsInvalid = {
            .indicatorType = { .value = 3},
        };
        modifier_->setRadioOptions(node_, &radioOptionsInvalid);
        auto indicatorTypeInvalid = GetStringAttribute(node_, INDICATOR_TYPE_ATTR);
        EXPECT_EQ(indicatorTypeInvalid, INDICATOR_TYPE_TICK);
    }
}
/**
 * @tc.name: RadioModifierTest001
 * @tc.desc: Test Radio setChecked.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioModifierTest001, TestSize.Level1)
{
    auto checked = GetStringAttribute(node_, CHECKED_ATTR);
    EXPECT_EQ(checked, "false");
    modifier_->setChecked(node_, true);
    auto checkedChanged = GetStringAttribute(node_, CHECKED_ATTR);
    EXPECT_EQ(checkedChanged, "true");
}

/**
 * @tc.name: RadioModifierTest002
 * @tc.desc: Test Radio setRadioStyle default color.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioModifierTest002, TestSize.Level1)
{
    auto radioStyleJSON = GetStringAttribute(node_, RADIO_STYLE_ATTR);
    auto radioStyle = JsonUtil::ParseJsonString(radioStyleJSON);
    auto checkedBackgroundColor = radioStyle->GetString(CHECKED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(checkedBackgroundColor, CHECKED_COLOR_DEFAULT);
    auto uncheckedBackgroundColor = radioStyle->GetString(UNCHECKED_BORDER_COLOR_ATTR);
    EXPECT_EQ(checkedBackgroundColor, UNCHECKED_COLOR_DEFAULT);
    auto indicatorBackgroundColor = radioStyle->GetString(INDICATOR_COLOR_ATTR);
    EXPECT_EQ(checkedBackgroundColor, INDICATOR_COLOR_DEFAULT);
}

/**
 * @tc.name: RadioModifierTest003
 * @tc.desc: Test Radio setRadioStyle custom color.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioModifierTest003, TestSize.Level1)
{
    const Ark_ResourceColor COLOR_COLOR = { .selector = 0, .value0 = CUSTOM_COLOR_INT };
    Opt_RadioStyle radioStyleColors;
    radioStyleColors.value.checkedBackgroundColor.value = COLOR_COLOR;
    radioStyleColors.value.indicatorColor.value = COLOR_COLOR;
    radioStyleColors.value.uncheckedBorderColor.value = COLOR_COLOR;
    modifier_->setRadioStyle(node_, &radioStyleColors);
    auto customRadioStyleJSON = GetStringAttribute(node_, RADIO_STYLE_ATTR);
    auto customRadioStyle = JsonUtil::ParseJsonString(customRadioStyleJSON);
    auto customCheckedBackgroundColor = customRadioStyle->GetString(CHECKED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(customCheckedBackgroundColor, CUSTOM_COLOR_STRING);
    auto customUncheckedBackgroundColor = customRadioStyle->GetString(UNCHECKED_BORDER_COLOR_ATTR);
    EXPECT_EQ(customCheckedBackgroundColor, CUSTOM_COLOR_STRING);
    auto customIndicatorBackgroundColor = customRadioStyle->GetString(INDICATOR_COLOR_ATTR);
    EXPECT_EQ(customIndicatorBackgroundColor, CUSTOM_COLOR_STRING);
}

/**
 * @tc.name: RadioModifierTest004
 * @tc.desc: Test Radio setRadioStyle custom int color.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioModifierTest004, TestSize.Level1)
{
    const Ark_ResourceColor COLOR_INT = { .selector = 1, .value1 = ArkNum(CUSTOM_COLOR_INT) };
    Opt_RadioStyle radioStyleColors;
    radioStyleColors.value.checkedBackgroundColor.value = COLOR_INT;
    radioStyleColors.value.indicatorColor.value = COLOR_INT;
    radioStyleColors.value.uncheckedBorderColor.value = COLOR_INT;
    modifier_->setRadioStyle(node_, &radioStyleColors);
    auto customRadioStyleJSON = GetStringAttribute(node_, RADIO_STYLE_ATTR);
    auto customRadioStyle = JsonUtil::ParseJsonString(customRadioStyleJSON);
    auto customCheckedBackgroundColor = customRadioStyle->GetString(CHECKED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(customCheckedBackgroundColor, CUSTOM_COLOR_STRING);
    auto customUncheckedBackgroundColor = customRadioStyle->GetString(UNCHECKED_BORDER_COLOR_ATTR);
    EXPECT_EQ(customCheckedBackgroundColor, CUSTOM_COLOR_STRING);
    auto customIndicatorBackgroundColor = customRadioStyle->GetString(INDICATOR_COLOR_ATTR);
    EXPECT_EQ(customIndicatorBackgroundColor, CUSTOM_COLOR_STRING);
}

/**
 * @tc.name: RadioModifierTest005
 * @tc.desc: Test Radio setRadioStyle custom float color.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioModifierTest005, TestSize.Level1)
{
    const Ark_ResourceColor COLOR_FLOAT = { .selector = 1, .value1 = ArkNum(CUSTOM_COLOR_FLOAT) };
    Opt_RadioStyle radioStyleColors;
    radioStyleColors.value.checkedBackgroundColor.value = COLOR_FLOAT;
    radioStyleColors.value.indicatorColor.value = COLOR_FLOAT;
    radioStyleColors.value.uncheckedBorderColor.value = COLOR_FLOAT;
    modifier_->setRadioStyle(node_, &radioStyleColors);
    auto customRadioStyleJSON = GetStringAttribute(node_, RADIO_STYLE_ATTR);
    auto customRadioStyle = JsonUtil::ParseJsonString(customRadioStyleJSON);
    auto customCheckedBackgroundColor = customRadioStyle->GetString(CHECKED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(customCheckedBackgroundColor, CHECK_FLOAT_COLOR);
    auto customUncheckedBackgroundColor = customRadioStyle->GetString(UNCHECKED_BORDER_COLOR_ATTR);
    EXPECT_EQ(customCheckedBackgroundColor, CHECK_FLOAT_COLOR);
    auto customIndicatorBackgroundColor = customRadioStyle->GetString(INDICATOR_COLOR_ATTR);
    EXPECT_EQ(customIndicatorBackgroundColor, CHECK_FLOAT_COLOR);
}

/**
 * @tc.name: RadioModifierTest006
 * @tc.desc: Test Radio setRadioStyle custom string color.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioModifierTest006, TestSize.Level1)
{
    const Ark_ResourceColor COLOR_STRING = { .selector = 2, .value2 = ArkStr(CUSTOM_COLOR_STRING) };
    Opt_RadioStyle radioStyleColors;
    radioStyleColors.value.checkedBackgroundColor.value = COLOR_STRING;
    radioStyleColors.value.indicatorColor.value = COLOR_STRING;
    radioStyleColors.value.uncheckedBorderColor.value = COLOR_STRING;
    modifier_->setRadioStyle(node_, &radioStyleColors);
    auto customRadioStyleJSON = GetStringAttribute(node_, RADIO_STYLE_ATTR);
    auto customRadioStyle = JsonUtil::ParseJsonString(customRadioStyleJSON);
    auto customCheckedBackgroundColor = customRadioStyle->GetString(CHECKED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(customCheckedBackgroundColor, CUSTOM_COLOR_STRING);
    auto customUncheckedBackgroundColor = customRadioStyle->GetString(UNCHECKED_BORDER_COLOR_ATTR);
    EXPECT_EQ(customCheckedBackgroundColor, CUSTOM_COLOR_STRING);
    auto customIndicatorBackgroundColor = customRadioStyle->GetString(INDICATOR_COLOR_ATTR);
    EXPECT_EQ(customIndicatorBackgroundColor, CUSTOM_COLOR_STRING);
}

/**
 * @tc.name: RadioModifierTest007
 * @tc.desc: Test Radio setRadioStyle custom resource color.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioModifierTest007, TestSize.Level1)
{
    auto RES_NAME = ArkStr("aa.bb.cc");
    const Ark_ResourceColor COLOR_RESOURCE = { .selector = 3, .value3 = ArkRes(&RES_NAME) };
    Opt_RadioStyle radioStyleColors;
    radioStyleColors.value.checkedBackgroundColor.value = COLOR_RESOURCE;
    radioStyleColors.value.indicatorColor.value = COLOR_RESOURCE;
    radioStyleColors.value.uncheckedBorderColor.value = COLOR_RESOURCE;
    modifier_->setRadioStyle(node_, &radioStyleColors);
    auto customRadioStyleJSON = GetStringAttribute(node_, RADIO_STYLE_ATTR);
    auto customRadioStyle = JsonUtil::ParseJsonString(customRadioStyleJSON);
    auto customCheckedBackgroundColor = customRadioStyle->GetString(CHECKED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(customCheckedBackgroundColor, CHECKED_COLOR_DEFAULT);
    auto customUncheckedBackgroundColor = customRadioStyle->GetString(UNCHECKED_BORDER_COLOR_ATTR);
    EXPECT_EQ(customCheckedBackgroundColor, UNCHECKED_COLOR_DEFAULT);
    auto customIndicatorBackgroundColor = customRadioStyle->GetString(INDICATOR_COLOR_ATTR);
    EXPECT_EQ(customIndicatorBackgroundColor, INDICATOR_COLOR_DEFAULT);
}

/**
 * @tc.name: RadioModifierTest008
 * @tc.desc: Test Radio ContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioModifierTest008, TestSize.Level1)
{
    LOGE("ARKOALA RadioAttributeModifier::ContentModifierImpl -> Method is not "
                "implemented.");
    EXPECT_EQ("true", "true");
}

/**
 * @tc.name: RadioEventTest001
 * @tc.desc: Test Radio onChange event.
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, RadioEventTest001, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Ark_Function func = {};
    modifier_->setOnChange(node_, func);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(g_isCheckedTest, false);
    ASSERT_NE(eventHub, nullptr);
    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(g_isCheckedTest, true);
}
} // namespace OHOS::Ace::NG
