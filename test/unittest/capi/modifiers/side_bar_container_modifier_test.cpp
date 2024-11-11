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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_event_hub.h"
#include "core/components_ng/pattern/side_bar/side_bar_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_SideBarContainerType& dst, const SideBarContainerType& src)
{
    switch (src) {
        case SideBarContainerType::EMBED: dst = ARK_SIDE_BAR_CONTAINER_TYPE_EMBED; break;
        case SideBarContainerType::OVERLAY: dst = ARK_SIDE_BAR_CONTAINER_TYPE_OVERLAY; break;
        case SideBarContainerType::AUTO: dst = ARK_SIDE_BAR_CONTAINER_TYPE_AUTO; break;
        default: dst = static_cast<Ark_SideBarContainerType>(-1);
            LOGE("Unexpected enum value in SideBarContainerType: %{public}d", src);
    }
}
}

namespace OHOS::Ace::NG {
namespace  {
const Ark_Int32 AINT32_NEG(-1234);
const Ark_Int32 AINT32_ZERO(0);
const Ark_Int32 AINT32_POS(1234);
const Ark_Int32 AINT32_INT_MAX(INT_MAX);
const auto OPT_NUM_NEG = Converter::ArkValue<Opt_Number>(AINT32_NEG);
const auto OPT_NUM_ZERO = Converter::ArkValue<Opt_Number>(AINT32_ZERO);
const auto OPT_NUM_VALID = Converter::ArkValue<Opt_Number>(AINT32_POS);
const auto OPT_NUM_MAX = Converter::ArkValue<Opt_Number>(AINT32_INT_MAX);

const auto NUM_NEG = Converter::ArkValue<Ark_Number>(AINT32_NEG);
const auto NUM_ZERO = Converter::ArkValue<Ark_Number>(AINT32_ZERO);
const auto NUM_VALID = Converter::ArkValue<Ark_Number>(AINT32_POS);
const auto NUM_MAX = Converter::ArkValue<Ark_Number>(AINT32_INT_MAX);

const auto LEN_NUM_NEG = Converter::ArkValue<Ark_Length>(AINT32_NEG);
const auto LEN_NUM_ZERO = Converter::ArkValue<Ark_Length>(AINT32_ZERO);
const auto LEN_NUM_VALID = Converter::ArkValue<Ark_Length>(AINT32_POS);
const auto LEN_NUM_MAX = Converter::ArkValue<Ark_Length>(AINT32_INT_MAX);

const auto OPT_LEN_NUM_NEG = Converter::ArkValue<Opt_Length>(AINT32_NEG);
const auto OPT_LEN_NUM_ZERO = Converter::ArkValue<Opt_Length>(AINT32_ZERO);
const auto OPT_LEN_NUM_VALID = Converter::ArkValue<Opt_Length>(AINT32_POS);
const auto OPT_LEN_NUM_MAX = Converter::ArkValue<Opt_Length>(AINT32_INT_MAX);

const std::string EXPECTED_NUM_NEG("-1234.000000");
const std::string EXPECTED_NUM_VILID("1234.000000");
const std::string EXPECTED_NUM_MAX("2147483648.000000");
const std::string EXPECTED_NUM_ZERO("0.000000");
const std::string EXPECTED_DEF_MIN_CONTENT_WIDTH("360.000000");

const std::string EXPECTED_NUM_NEG_PX("-1234.00px");
const std::string EXPECTED_NUM_VILID_PX("1234.00px");
const std::string EXPECTED_NUM_MAX_PX("2147483648.00px");
const std::string EXPECTED_NUM_ZERO_PX("0.00px");

const auto CUSTOM_COLOR_STRING("#FF123456");
const int CUSTOM_COLOR_INT(0xFF123456);
const float CUSTOM_COLOR_FLOAT(0.1f);

const Ark_ResourceColor COLOR_COLOR = { .selector = 0, .value0 = Ark_Color::ARK_COLOR_GREEN };
const Ark_ResourceColor COLOR_INT = { .selector = 1, .value1 = Converter::ArkValue<Ark_Number>(CUSTOM_COLOR_INT) };
const Ark_ResourceColor COLOR_FLOAT = { .selector = 1, .value1 = Converter::ArkValue<Ark_Number>(CUSTOM_COLOR_FLOAT) };
const Ark_ResourceColor COLOR_STRING = {
    .selector = 2,
    .value2 = Converter::ArkValue<Ark_String>(CUSTOM_COLOR_STRING)
};

const Opt_ResourceColor OPT_COLOR_COLOR = { .tag = ARK_TAG_OBJECT, .value = COLOR_COLOR };
const Opt_ResourceColor OPT_COLOR_INT = { .tag = ARK_TAG_OBJECT, .value = COLOR_INT };
const Opt_ResourceColor OPT_COLOR_FLOAT = { .tag = ARK_TAG_OBJECT, .value = COLOR_FLOAT };
const Opt_ResourceColor OPT_COLOR_STRING = { .tag = ARK_TAG_OBJECT, .value = COLOR_STRING };

static bool g_isCheckedTest = true;
static auto sideBarOnChange(Ark_Int32 nodeId, const Ark_Boolean isChecked)
{
    g_isCheckedTest = !g_isCheckedTest;
};
static GENERATED_ArkUISideBarContainerEventsReceiver recv {
    .onChange = sideBarOnChange
};
static const GENERATED_ArkUISideBarContainerEventsReceiver* getSideBarContainerEventsReceiverTest()
{
    return &recv;
};
static const GENERATED_ArkUIEventsAPI* GetArkUiEventsAPITest()
{
static const GENERATED_ArkUIEventsAPI eventsImpl = {
    .getSideBarContainerEventsReceiver = getSideBarContainerEventsReceiverTest };
    return &eventsImpl;
};

const auto ATTRIBUTE_CONTAINER_TYPE = "type";
const auto ATTRIBUTE_CONTROL_BUTTON_NAME = "controlButton";
const auto ATTRIBUTE_SHOW_SIDE_BAR_NAME = "showSideBar";
const auto ATTRIBUTE_SHOW_SIDE_BAR_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_CONTROL_BUTTON_LEFT_NAME = "left";
const auto ATTRIBUTE_CONTROL_BUTTON_LEFT_DEFAULT_VALUE = "16.00vp";
const auto ATTRIBUTE_CONTROL_BUTTON_TOP_NAME = "top";
const auto ATTRIBUTE_CONTROL_BUTTON_TOP_DEFAULT_VALUE = "48.00vp";
const auto ATTRIBUTE_CONTROL_BUTTON_WIDTH_NAME = "width";
const auto ATTRIBUTE_CONTROL_BUTTON_WIDTH_DEFAULT_VALUE = "24.00vp";
const auto ATTRIBUTE_CONTROL_BUTTON_HEIGHT_NAME = "height";
const auto ATTRIBUTE_CONTROL_BUTTON_HEIGHT_DEFAULT_VALUE = "24.00vp";
const auto ATTRIBUTE_CONTROL_BUTTON_ICONS_NAME = "icons";
const auto ATTRIBUTE_CONTROL_BUTTON_ICONS_DEFAULT_VALUE = "";
const auto ATTRIBUTE_SHOW_CONTROL_BUTTON_NAME = "showControlButton";
const auto ATTRIBUTE_SHOW_CONTROL_BUTTON_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_SIDE_BAR_WIDTH_NAME = "sideBarWidth";
const auto ATTRIBUTE_SIDE_BAR_WIDTH_DEFAULT_VALUE = "240.000000";
const auto ATTRIBUTE_MIN_SIDE_BAR_WIDTH_NAME = "minSideBarWidth";
const auto ATTRIBUTE_MIN_SIDE_BAR_WIDTH_DEFAULT_VALUE = "240.000000";
const auto ATTRIBUTE_MAX_SIDE_BAR_WIDTH_NAME = "maxSideBarWidth";
const auto ATTRIBUTE_MAX_SIDE_BAR_WIDTH_DEFAULT_VALUE = "280.000000";
const auto ATTRIBUTE_AUTO_HIDE_NAME = "autoHide";
const auto ATTRIBUTE_AUTO_HIDE_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_SIDE_BAR_POSITION_NAME = "sideBarPosition";
const auto ATTRIBUTE_SIDE_BAR_POSITION_DEFAULT_VALUE = "SideBarPosition.Start";
const auto ATTRIBUTE_MIN_CONTENT_WIDTH_NAME = "minContentWidth";
const auto ATTRIBUTE_MIN_CONTENT_WIDTH_DEFAULT_VALUE = "360.000000";
const auto ATTRIBUTE_DIVIDER_NAME = "divider";
const auto ATTRIBUTE_DIVIDER_STROKE_WIDTH = "strokeWidth";
const auto ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE = "1.00vp";
const auto ATTRIBUTE_DIVIDER_START_MARGIN = "startMargin";
const auto ATTRIBUTE_DIVIDER_START_MARGIN_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_DIVIDER_END_MARGIN = "endMargin";
const auto ATTRIBUTE_DIVIDER_END_MARGIN_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_DIVIDER_COLOR = "color";
const auto ATTRIBUTE_DIVIDER_COLOR_DEFAULT_VALUE = "#08000000";
} // namespace

class SideBarContainerModifierTest : public ModifierTestBase<GENERATED_ArkUISideBarContainerModifier,
    &GENERATED_ArkUINodeModifiers::getSideBarContainerModifier, GENERATED_ARKUI_SIDE_BAR_CONTAINER> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<SideBarTheme>();
        fullAPI_->setArkUIEventsAPI(GetArkUiEventsAPITest());
    }

    void checkControlButtonAttr(std::vector<std::tuple<std::string, Opt_Number, std::string>> styleArray,
        std::string attribute)
    {
        std::unique_ptr<JsonValue> jsonValue;
        std::unique_ptr<JsonValue> cbJson;
        std::string resultStr;
        Ark_ButtonStyle inputValue;
        for (auto [passed, checkVal, expected]: styleArray) {
            if (attribute == ATTRIBUTE_CONTROL_BUTTON_LEFT_NAME) {
                inputValue.left = checkVal;
            }
            if (attribute == ATTRIBUTE_CONTROL_BUTTON_TOP_NAME) {
                inputValue.top = checkVal;
            }
            if (attribute == ATTRIBUTE_CONTROL_BUTTON_WIDTH_NAME) {
                inputValue.width = checkVal;
            }
            if (attribute == ATTRIBUTE_CONTROL_BUTTON_HEIGHT_NAME) {
                inputValue.height = checkVal;
            }
            modifier_->setControlButton(node_, &inputValue);
            jsonValue = GetJsonValue(node_);
            cbJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONTROL_BUTTON_NAME);
            resultStr = GetAttrValue<std::string>(cbJson, attribute);
            EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
        }
    }

    void checkDividerLengthAttr(std::vector<std::tuple<std::string, Opt_Length, std::string>> styleArray,
        std::string attribute)
    {
        std::unique_ptr<JsonValue> jsonValue;
        std::unique_ptr<JsonValue> divJson;
        std::string resultStr;
        Ark_DividerStyle inputValue;
        for (auto [passed, checkVal, expected]: styleArray) {
            if (attribute == ATTRIBUTE_DIVIDER_STROKE_WIDTH) {
                inputValue.strokeWidth = checkVal.value;
            }
            if (attribute == ATTRIBUTE_DIVIDER_START_MARGIN) {
                inputValue.startMargin = checkVal;
            }
            if (attribute == ATTRIBUTE_DIVIDER_END_MARGIN) {
                inputValue.endMargin = checkVal;
            }
            auto divider = Converter::ArkUnion<Ark_Union_DividerStyle_Undefined,
                Ark_DividerStyle>(inputValue);
            modifier_->setDivider(node_, &divider);
            jsonValue = GetJsonValue(node_);
            divJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DIVIDER_NAME);
            resultStr = GetAttrValue<std::string>(divJson, attribute);
            EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
        }
    }

    void checkDividerColorAttr(std::vector<std::tuple<std::string, Opt_ResourceColor, std::string>> styleArray)
    {
        std::unique_ptr<JsonValue> jsonValue;
        std::unique_ptr<JsonValue> divJson;
        std::string resultStr;
        Ark_DividerStyle inputValue;
        for (auto [passed, checkVal, expected]: styleArray) {
            inputValue.color = checkVal;
            auto divider = Converter::ArkUnion<Ark_Union_DividerStyle_Undefined,
                Ark_DividerStyle>(inputValue);
            modifier_->setDivider(node_, &divider);
            jsonValue = GetJsonValue(node_);
            divJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DIVIDER_NAME);
            resultStr = GetAttrValue<std::string>(divJson, ATTRIBUTE_DIVIDER_COLOR);
            EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
        }
    }
};

static std::vector<std::tuple<Ark_SideBarContainerType, Opt_SideBarContainerType, std::string>> sbTypeValidValues = {
    {ARK_SIDE_BAR_CONTAINER_TYPE_EMBED,
        Converter::ArkValue<Opt_SideBarContainerType>(ARK_SIDE_BAR_CONTAINER_TYPE_EMBED),
        "SideBarContainerType.Embed"},
    {ARK_SIDE_BAR_CONTAINER_TYPE_OVERLAY,
        Converter::ArkValue<Opt_SideBarContainerType>(ARK_SIDE_BAR_CONTAINER_TYPE_OVERLAY),
        "SideBarContainerType.OVERLAY"},
    {ARK_SIDE_BAR_CONTAINER_TYPE_AUTO,
        Converter::ArkValue<Opt_SideBarContainerType>(ARK_SIDE_BAR_CONTAINER_TYPE_AUTO),
        "SideBarContainerType.OVERLAY"},
};

/*
 * @tc.name: sideBarContainerTypeTestValidValues
 * @tc.desc: SideBarContainer Type Valid Values
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, sideBarContainerTypeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Opt_SideBarContainerType inputValue;
    for (auto [passed, checkVal, expected]: sbTypeValidValues) {
        inputValue = checkVal;
        modifier_->setSideBarContainerOptions(node_, &inputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTAINER_TYPE);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setShowSideBarTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setShowSideBarTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_SIDE_BAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_SIDE_BAR_DEFAULT_VALUE);
}

static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> showSideBarValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setShowSideBarTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setShowSideBarTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueShowSideBar;
    for (auto [passed, checkVal, expected]: showSideBarValidValues) {
        inputValueShowSideBar = checkVal;
        modifier_->setShowSideBar(node_, inputValueShowSideBar);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_SIDE_BAR_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setControlButtonTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, DISABLED_setControlButtonTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultControlButton =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONTROL_BUTTON_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultControlButton, ATTRIBUTE_CONTROL_BUTTON_LEFT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_BUTTON_LEFT_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultControlButton, ATTRIBUTE_CONTROL_BUTTON_TOP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_BUTTON_TOP_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultControlButton, ATTRIBUTE_CONTROL_BUTTON_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_BUTTON_WIDTH_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultControlButton, ATTRIBUTE_CONTROL_BUTTON_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_BUTTON_HEIGHT_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultControlButton, ATTRIBUTE_CONTROL_BUTTON_ICONS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_BUTTON_ICONS_DEFAULT_VALUE);
}

// Valid values for attribute 'left' of method 'controlButton'
static std::vector<std::tuple<std::string, Opt_Number, std::string>> controlButtonLeftValidValues = {
    {EXPECTED_NUM_NEG, OPT_NUM_NEG, EXPECTED_NUM_NEG},
    {EXPECTED_NUM_ZERO, OPT_NUM_ZERO, EXPECTED_NUM_ZERO},
    {EXPECTED_NUM_VILID, OPT_NUM_VALID, EXPECTED_NUM_VILID},
    {EXPECTED_NUM_MAX, OPT_NUM_MAX, EXPECTED_NUM_MAX},
};

// Valid values for attribute 'top' of method 'controlButton'
static std::vector<std::tuple<std::string, Opt_Number, std::string>> controlButtonTopValidValues = {
    {EXPECTED_NUM_NEG, OPT_NUM_NEG, EXPECTED_NUM_NEG},
    {EXPECTED_NUM_ZERO, OPT_NUM_ZERO, EXPECTED_NUM_ZERO},
    {EXPECTED_NUM_VILID, OPT_NUM_VALID, EXPECTED_NUM_VILID},
    {EXPECTED_NUM_MAX, OPT_NUM_MAX, EXPECTED_NUM_MAX},
};

// Valid values for attribute 'width' of method 'controlButton'
static std::vector<std::tuple<std::string, Opt_Number, std::string>> controlButtonWidthValidValues = {
    {EXPECTED_NUM_NEG, OPT_NUM_NEG, EXPECTED_NUM_NEG},
    {EXPECTED_NUM_ZERO, OPT_NUM_ZERO, EXPECTED_NUM_ZERO},
    {EXPECTED_NUM_VILID, OPT_NUM_VALID, EXPECTED_NUM_VILID},
    {EXPECTED_NUM_MAX, OPT_NUM_MAX, EXPECTED_NUM_MAX},
};

// Valid values for attribute 'height' of method 'controlButton'
static std::vector<std::tuple<std::string, Opt_Number, std::string>> controlButtonHeightValidValues = {
    {EXPECTED_NUM_NEG, OPT_NUM_NEG, EXPECTED_NUM_NEG},
    {EXPECTED_NUM_ZERO, OPT_NUM_ZERO, EXPECTED_NUM_ZERO},
    {EXPECTED_NUM_VILID, OPT_NUM_VALID, EXPECTED_NUM_VILID},
    {EXPECTED_NUM_MAX, OPT_NUM_MAX, EXPECTED_NUM_MAX},
};

/*
 * @tc.name: setControlButtonTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, DISABLED_setControlButtonTestValidValues, TestSize.Level1)
{
    checkControlButtonAttr(controlButtonLeftValidValues, ATTRIBUTE_CONTROL_BUTTON_LEFT_NAME);
    checkControlButtonAttr(controlButtonTopValidValues, ATTRIBUTE_CONTROL_BUTTON_TOP_NAME);
    checkControlButtonAttr(controlButtonWidthValidValues, ATTRIBUTE_CONTROL_BUTTON_WIDTH_NAME);
    checkControlButtonAttr(controlButtonHeightValidValues, ATTRIBUTE_CONTROL_BUTTON_HEIGHT_NAME);
}

/*
 * @tc.name: setShowControlButtonTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setShowControlButtonTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_CONTROL_BUTTON_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_CONTROL_BUTTON_DEFAULT_VALUE);
}

static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> showControlButtonValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setShowControlButtonTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setShowControlButtonTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_Boolean inputValue;
    for (auto [passed, checkVal, expected]: showControlButtonValidValues) {
        inputValue = checkVal;
        modifier_->setShowControlButton(node_, inputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_CONTROL_BUTTON_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setOnChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setOnChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_Boolean_Void func{};
    modifier_->setOnChange(node_, &func);
    auto eventHub = frameNode->GetEventHub<NG::SideBarContainerEventHub>();
    eventHub->FireChangeEvent(true);
    EXPECT_EQ(g_isCheckedTest, false);
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(true);
    EXPECT_EQ(g_isCheckedTest, true);
}

/*
 * @tc.name: setSideBarWidth0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setSideBarWidth0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SIDE_BAR_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SIDE_BAR_WIDTH_DEFAULT_VALUE);
}

// Valid values for attribute 'sideBarWidth' of method 'sideBarWidth'
static std::vector<std::tuple<std::string, Ark_Number, std::string>> mSideBarWidthValidValues1 = {
    {EXPECTED_NUM_NEG, NUM_NEG, ATTRIBUTE_SIDE_BAR_WIDTH_DEFAULT_VALUE},
    {EXPECTED_NUM_ZERO, NUM_ZERO, EXPECTED_NUM_ZERO},
    {EXPECTED_NUM_VILID, NUM_VALID, EXPECTED_NUM_VILID},
    {EXPECTED_NUM_MAX, NUM_MAX, EXPECTED_NUM_MAX},
};

/*
 * @tc.name: setSideBarWidth0TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setSideBarWidth0TestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_Number inputValueSideBarWidth;
    for (auto [passed, checkVal, expected]: mSideBarWidthValidValues1) {
        inputValueSideBarWidth = checkVal;
        modifier_->setSideBarWidth0(node_, &inputValueSideBarWidth);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SIDE_BAR_WIDTH_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setMinSideBarWidth0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setMinSideBarWidth0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_SIDE_BAR_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_SIDE_BAR_WIDTH_DEFAULT_VALUE);
}

static std::vector<std::tuple<std::string, Ark_Number, std::string>> mMinSideBarWidthValidValues1 = {
    {EXPECTED_NUM_NEG, NUM_NEG, ATTRIBUTE_SIDE_BAR_WIDTH_DEFAULT_VALUE},
    {EXPECTED_NUM_ZERO, NUM_ZERO, EXPECTED_NUM_ZERO},
    {EXPECTED_NUM_VILID, NUM_VALID, EXPECTED_NUM_VILID},
    {EXPECTED_NUM_MAX, NUM_MAX, EXPECTED_NUM_MAX},
};

/*
 * @tc.name: setMinSideBarWidth0TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, DISABLED_setMinSideBarWidth0TestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Number inputValueMinSideBarWidth;
    for (auto [passed, checkVal, expected]: mMinSideBarWidthValidValues1) {
        inputValueMinSideBarWidth = checkVal;
        modifier_->setMinSideBarWidth0(node_, &inputValueMinSideBarWidth);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_SIDE_BAR_WIDTH_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setMaxSideBarWidth0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setMaxSideBarWidth0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_SIDE_BAR_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_SIDE_BAR_WIDTH_DEFAULT_VALUE);
}

// Valid values for attribute 'maxSideBarWidth' of method 'maxSideBarWidth'
static std::vector<std::tuple<std::string, Ark_Number, std::string>> maxSideBarWidthValidValues1 = {
    {EXPECTED_NUM_NEG, NUM_NEG, ATTRIBUTE_MAX_SIDE_BAR_WIDTH_DEFAULT_VALUE},
    {EXPECTED_NUM_ZERO, NUM_ZERO, EXPECTED_NUM_ZERO},
    {EXPECTED_NUM_VILID, NUM_VALID, EXPECTED_NUM_VILID},
    {EXPECTED_NUM_MAX, NUM_MAX, EXPECTED_NUM_MAX},
};

/*
 * @tc.name: setMaxSideBarWidth0TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, DISABLED_setMaxSideBarWidth0TestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_Number inputValueMaxSideBarWidth;
    for (auto [passed, checkVal, expected]: maxSideBarWidthValidValues1) {
        inputValueMaxSideBarWidth = checkVal;
        modifier_->setMaxSideBarWidth0(node_, &inputValueMaxSideBarWidth);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_SIDE_BAR_WIDTH_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

// Valid values for attribute 'sideBarWidth' of method 'sideBarWidth'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> sideBarWidthValidValues2 = {
    {EXPECTED_NUM_NEG, LEN_NUM_NEG, ATTRIBUTE_SIDE_BAR_WIDTH_DEFAULT_VALUE},
    {EXPECTED_NUM_ZERO, LEN_NUM_ZERO, EXPECTED_NUM_ZERO},
    {EXPECTED_NUM_VILID, LEN_NUM_VALID, EXPECTED_NUM_VILID},
    {EXPECTED_NUM_MAX, LEN_NUM_MAX, EXPECTED_NUM_MAX},
};

/*
 * @tc.name: setSideBarWidth1TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, DISABLED_setSideBarWidth1TestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_Length inputValueSideBarWidth;
    for (auto [passed, checkVal, expected]: sideBarWidthValidValues2) {
        inputValueSideBarWidth = checkVal;
        modifier_->setSideBarWidth1(node_, &inputValueSideBarWidth);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SIDE_BAR_WIDTH_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

// Valid values for attribute 'minSideBarWidth' of method 'minSideBarWidth'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> mMinSideBarWidthValidValues2 = {
    {EXPECTED_NUM_NEG, LEN_NUM_NEG, ATTRIBUTE_MIN_SIDE_BAR_WIDTH_DEFAULT_VALUE},
    {EXPECTED_NUM_ZERO, LEN_NUM_ZERO, EXPECTED_NUM_ZERO},
    {EXPECTED_NUM_VILID, LEN_NUM_VALID, EXPECTED_NUM_VILID},
    {EXPECTED_NUM_MAX, LEN_NUM_MAX, EXPECTED_NUM_MAX},
};

/*
 * @tc.name: setMinSideBarWidth1TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, DISABLED_setMinSideBarWidth1TestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueMinSideBarWidth;
    for (auto [passed, checkVal, expected]: mMinSideBarWidthValidValues2) {
        inputValueMinSideBarWidth = checkVal;
        modifier_->setMinSideBarWidth1(node_, &inputValueMinSideBarWidth);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_SIDE_BAR_WIDTH_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

// Valid values for attribute 'maxSideBarWidth' of method 'maxSideBarWidth'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> mMaxSideBarWidthValidValues2 = {
    {EXPECTED_NUM_NEG, LEN_NUM_NEG, ATTRIBUTE_MAX_SIDE_BAR_WIDTH_DEFAULT_VALUE},
    {EXPECTED_NUM_ZERO, LEN_NUM_ZERO, EXPECTED_NUM_ZERO},
    {EXPECTED_NUM_VILID, LEN_NUM_VALID, EXPECTED_NUM_VILID},
    {EXPECTED_NUM_MAX, LEN_NUM_MAX, EXPECTED_NUM_MAX},
};

/*
 * @tc.name: setMaxSideBarWidth1TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setMaxSideBarWidth1TestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_Length inputValue;
    for (auto [passed, checkVal, expected]: mMaxSideBarWidthValidValues2) {
        inputValue = checkVal;
        modifier_->setMaxSideBarWidth1(node_, &inputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_SIDE_BAR_WIDTH_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setAutoHideTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setAutoHideTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_HIDE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_AUTO_HIDE_DEFAULT_VALUE);
}

// Valid values for attribute 'autoHide' of method 'autoHide'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> autoHideValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setAutoHideTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setAutoHideTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_Boolean inputValueAutoHide;
    for (auto [passed, checkVal, expected]: autoHideValidValues) {
        inputValueAutoHide = checkVal;
        modifier_->setAutoHide(node_, inputValueAutoHide);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_HIDE_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setSideBarPositionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setSideBarPositionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SIDE_BAR_POSITION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SIDE_BAR_POSITION_DEFAULT_VALUE);
}

// Valid values for attribute 'sideBarPosition' of method 'sideBarPosition'
static std::vector<std::tuple<std::string, enum Ark_SideBarPosition, std::string>> sbPositionValidValues = {
    {"ARK_SIDE_BAR_POSITION_START",
        Converter::ArkValue<enum Ark_SideBarPosition>(ARK_SIDE_BAR_POSITION_START), "SideBarPosition.Start"},
    {"ARK_SIDE_BAR_POSITION_END",
        Converter::ArkValue<enum Ark_SideBarPosition>(ARK_SIDE_BAR_POSITION_END), "SideBarPosition.End"},
};

/*
 * @tc.name: setSideBarPositionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setSideBarPositionTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    for (auto [passed, checkVal, expected]: sbPositionValidValues) {
        modifier_->setSideBarPosition(node_, checkVal);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SIDE_BAR_POSITION_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setMinContentWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setMinContentWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_CONTENT_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_CONTENT_WIDTH_DEFAULT_VALUE);
}

// Valid values for attribute 'minContentWidth' of method 'minContentWidth'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> minContentWidthValidValues = {
    {EXPECTED_NUM_NEG, LEN_NUM_NEG, EXPECTED_DEF_MIN_CONTENT_WIDTH},
    {EXPECTED_NUM_ZERO, LEN_NUM_ZERO, EXPECTED_NUM_ZERO},
    {EXPECTED_NUM_VILID, LEN_NUM_VALID, EXPECTED_NUM_VILID},
    {EXPECTED_NUM_MAX, LEN_NUM_MAX, EXPECTED_NUM_MAX},
};

/*
 * @tc.name: setMinContentWidthTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setMinContentWidthTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_Length inputValue;
    for (auto [passed, checkVal, expected]: minContentWidthValidValues) {
        inputValue = checkVal;
        modifier_->setMinContentWidth(node_, &inputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_CONTENT_WIDTH_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setDividerTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setDividerTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> divJson;
    std::string resultStr;
    divJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DIVIDER_NAME);
    resultStr = GetAttrValue<std::string>(divJson, ATTRIBUTE_DIVIDER_STROKE_WIDTH);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE);
    resultStr = GetAttrValue<std::string>(divJson, ATTRIBUTE_DIVIDER_START_MARGIN);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIVIDER_START_MARGIN_DEFAULT_VALUE);
    resultStr = GetAttrValue<std::string>(divJson, ATTRIBUTE_DIVIDER_END_MARGIN);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIVIDER_END_MARGIN_DEFAULT_VALUE);
    resultStr = GetAttrValue<std::string>(divJson, ATTRIBUTE_DIVIDER_COLOR);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIVIDER_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'strokeWidth' of method 'setDivider'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> dividerStrokeValidValues = {
    {EXPECTED_NUM_NEG_PX, OPT_LEN_NUM_NEG, ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE},
    {EXPECTED_NUM_ZERO_PX, OPT_LEN_NUM_ZERO, EXPECTED_NUM_ZERO_PX},
    {EXPECTED_NUM_VILID_PX, OPT_LEN_NUM_VALID, EXPECTED_NUM_VILID_PX},
    {EXPECTED_NUM_MAX_PX, OPT_LEN_NUM_MAX, EXPECTED_NUM_MAX_PX},
};

// Valid values for attribute 'startMargin' of method 'setDivider'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> dividerStartMarginValidValues = {
    {EXPECTED_NUM_NEG_PX, OPT_LEN_NUM_NEG, EXPECTED_NUM_NEG_PX},
    {EXPECTED_NUM_ZERO_PX, OPT_LEN_NUM_ZERO, EXPECTED_NUM_ZERO_PX},
    {EXPECTED_NUM_VILID_PX, OPT_LEN_NUM_VALID, EXPECTED_NUM_VILID_PX},
    {EXPECTED_NUM_MAX_PX, OPT_LEN_NUM_MAX, EXPECTED_NUM_MAX_PX},
};

// Valid values for attribute 'endMargin' of method 'setDivider'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> dividerEndMarginValidValues = {
    {EXPECTED_NUM_NEG_PX, OPT_LEN_NUM_NEG, EXPECTED_NUM_NEG_PX},
    {EXPECTED_NUM_ZERO_PX, OPT_LEN_NUM_ZERO, EXPECTED_NUM_ZERO_PX},
    {EXPECTED_NUM_VILID_PX, OPT_LEN_NUM_VALID, EXPECTED_NUM_VILID_PX},
    {EXPECTED_NUM_MAX_PX, OPT_LEN_NUM_MAX, EXPECTED_NUM_MAX_PX},
};

/*
 * @tc.name: setDividerTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setDividerTestValidValues, TestSize.Level1)
{
    checkDividerLengthAttr(dividerStrokeValidValues, ATTRIBUTE_DIVIDER_STROKE_WIDTH);
    checkDividerLengthAttr(dividerStartMarginValidValues, ATTRIBUTE_DIVIDER_START_MARGIN);
    checkDividerLengthAttr(dividerEndMarginValidValues, ATTRIBUTE_DIVIDER_END_MARGIN);
}


// Valid values for attribute 'endMargin' of method 'setDivider'
static std::vector<std::tuple<std::string, Opt_ResourceColor, std::string>> dividerColorValidValues = {
    {"#FF008000", OPT_COLOR_COLOR, "#FF008000"},
    {"#FF123456", OPT_COLOR_INT, "#FF123456"},
    {"#00000000", OPT_COLOR_FLOAT, "#00000000"},
    {"#FF123456", OPT_COLOR_STRING, "#FF123456"},
};

/*
 * @tc.name: setDividerTestColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setDividerTestColorValidValues, TestSize.Level1)
{
    checkDividerColorAttr(dividerColorValidValues);
}

} // namespace OHOS::Ace::NG
