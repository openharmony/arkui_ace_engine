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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "generated/type_helpers.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_event_hub.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"
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
using namespace TypeHelper;
namespace  {
const float AINT32_NEG(-1234);
const float AINT32_ZERO(0);
const float AINT32_POS(1234);
const auto OPT_NUM_NEG = Converter::ArkValue<Opt_Number>(AINT32_NEG);
const auto OPT_NUM_ZERO = Converter::ArkValue<Opt_Number>(AINT32_ZERO);
const auto OPT_NUM_VALID = Converter::ArkValue<Opt_Number>(AINT32_POS);

const auto NUM_NEG = Converter::ArkValue<Ark_Number>(AINT32_NEG);
const auto NUM_ZERO = Converter::ArkValue<Ark_Number>(AINT32_ZERO);
const auto NUM_VALID = Converter::ArkValue<Ark_Number>(AINT32_POS);

const auto LEN_NUM_NEG = Converter::ArkValue<Ark_Length>("-1234.00px");
const auto LEN_NUM_ZERO = Converter::ArkValue<Ark_Length>("0.00px");
const auto LEN_NUM_VALID = Converter::ArkValue<Ark_Length>("1234.00px");

const auto OPT_LEN_NUM_NEG = Converter::ArkValue<Opt_Length>("-1234.00px");
const auto OPT_LEN_NUM_ZERO = Converter::ArkValue<Opt_Length>("0.00px");
const auto OPT_LEN_NUM_VALID = Converter::ArkValue<Opt_Length>("1234.00px");

const std::string EXPECTED_NUM_NEG("-1234.000000");
const std::string EXPECTED_NUM_VILID("1234.000000");
const std::string EXPECTED_NUM_ZERO("0.000000");
const std::string EXPECTED_DEF_MIN_CONTENT_WIDTH("360.000000");

const std::string EXPECTED_NUM_NEG_PX("-1234.00px");
const std::string EXPECTED_NUM_VILID_PX("1234.00px");
const std::string EXPECTED_NUM_ZERO_PX("0.00px");

const std::string ICON_STRING("icon.png");
const std::string ICON_STRING_DEF("");
const auto ARK_STR_ICON_VALID = Converter::ArkValue<Ark_String>(ICON_STRING);

const auto CUSTOM_COLOR_STRING("#FF123456");
const int CUSTOM_COLOR_INT(0xFF123456);
const float CUSTOM_COLOR_FLOAT(0.1f);

const Ark_ResourceColor COLOR_COLOR = Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(Ark_Color::ARK_COLOR_GREEN);
const Ark_ResourceColor COLOR_INT = Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(CUSTOM_COLOR_INT);
const Ark_ResourceColor COLOR_FLOAT = Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(CUSTOM_COLOR_FLOAT);
const Ark_ResourceColor COLOR_STRING = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(CUSTOM_COLOR_STRING);

const Opt_ResourceColor OPT_COLOR_COLOR = Converter::ArkValue<Opt_ResourceColor>(COLOR_COLOR);
const Opt_ResourceColor OPT_COLOR_INT = Converter::ArkValue<Opt_ResourceColor>(COLOR_INT);
const Opt_ResourceColor OPT_COLOR_FLOAT = Converter::ArkValue<Opt_ResourceColor>(COLOR_FLOAT);
const Opt_ResourceColor OPT_COLOR_STRING = Converter::ArkValue<Opt_ResourceColor>(COLOR_STRING);

const auto RES_SRC_TEST = "test_src";

const auto ATTRIBUTE_CONTAINER_TYPE = "type";
const auto ATTRIBUTE_CONTROL_BUTTON_NAME = "controlButton";
const auto ATTRIBUTE_SHOW_SIDE_BAR_NAME = "showSideBar";
const auto ATTRIBUTE_SHOW_SIDE_BAR_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_CONTROL_BUTTON_LEFT_NAME = "left";
const auto ATTRIBUTE_CONTROL_BUTTON_LEFT_DEFAULT_VALUE = "16.00vp";
const auto ATTRIBUTE_CONTROL_BUTTON_TOP_NAME = "top";
const auto ATTRIBUTE_CONTROL_BUTTON_TOP_DEFAULT_VALUE = "48.00vp";
const auto ATTRIBUTE_CONTROL_BUTTON_WIDTH_NAME = "width";
const auto ATTRIBUTE_CONTROL_BUTTON_WIDTH_DEFAULT_VALUE = "32.000000";
const auto ATTRIBUTE_CONTROL_BUTTON_HEIGHT_NAME = "height";
const auto ATTRIBUTE_CONTROL_BUTTON_HEIGHT_DEFAULT_VALUE = "32.000000";
const auto ATTRIBUTE_CONTROL_BUTTON_ICONS_NAME = "icon";
const auto ATTRIBUTE_CONTROL_BUTTON_ICONS_DEFAULT_VALUE = "";
const auto ATTRIBUTE_CONTROL_BUTTON_ICONS_SHOWN_NAME = "shown";
const auto ATTRIBUTE_CONTROL_BUTTON_ICONS_HIDDEN_NAME = "hidden";
const auto ATTRIBUTE_CONTROL_BUTTON_ICONS_SWITCH_NAME = "switching";
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
        AddResource(RES_SRC_TEST, ICON_STRING);
    }

    void checkControlButtonAttr(std::vector<std::tuple<std::string, Opt_Float64, std::string>> styleArray,
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
            auto valueOpt = Converter::ArkValue<Opt_ButtonStyle>(inputValue);
            modifier_->setControlButton(node_, &valueOpt);
            jsonValue = GetJsonValue(node_);
            cbJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONTROL_BUTTON_NAME);
            resultStr = GetAttrValue<std::string>(cbJson, attribute);
            EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed << " Attribute: " << attribute;
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
                inputValue.strokeWidth = checkVal;
            }
            if (attribute == ATTRIBUTE_DIVIDER_START_MARGIN) {
                inputValue.startMargin = checkVal;
            }
            if (attribute == ATTRIBUTE_DIVIDER_END_MARGIN) {
                inputValue.endMargin = checkVal;
            }
            auto divider = Converter::ArkValue<Opt_DividerStyle>(inputValue);
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
            auto divider = Converter::ArkValue<Opt_DividerStyle>(inputValue);
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
    for (auto [passed, checkVal, expected]: showSideBarValidValues) {
        auto inputValueShowSideBar = Converter::ArkUnion<Opt_Union_Boolean_Bindable, Ark_Boolean>(checkVal);
        modifier_->setShowSideBar(node_, &inputValueShowSideBar);
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

/*
 * @tc.name: setControlButtonTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setControlButtonTestValidValues, TestSize.Level1)
{
    static std::vector<std::tuple<std::string, Opt_Float64, std::string>> leftValues = {
        {"-1234", Converter::ArkValue<Opt_Float64>(-1234), "-1234.000000"},
        {"0", Converter::ArkValue<Opt_Float64>(0), "0.000000"},
        {"1234", Converter::ArkValue<Opt_Float64>(1234), "1234.000000"},
    };
    static std::vector<std::tuple<std::string, Opt_Float64, std::string>> topValues = {
        {"-1234", Converter::ArkValue<Opt_Float64>(-1234), "-1234.000000"},
        {"0", Converter::ArkValue<Opt_Float64>(0), "0.000000"},
        {"1234", Converter::ArkValue<Opt_Float64>(1234), "1234.000000"},
    };
    static std::vector<std::tuple<std::string, Opt_Float64, std::string>> widthValues = {
        {"-1234", Converter::ArkValue<Opt_Float64>(-1234), ATTRIBUTE_CONTROL_BUTTON_WIDTH_DEFAULT_VALUE},
        {"0", Converter::ArkValue<Opt_Float64>(0), "0.000000"},
        {"1234", Converter::ArkValue<Opt_Float64>(1234), "1234.000000"},
    };
    static std::vector<std::tuple<std::string, Opt_Float64, std::string>> heightValues = {
        {"-1234", Converter::ArkValue<Opt_Float64>(-1234), ATTRIBUTE_CONTROL_BUTTON_HEIGHT_DEFAULT_VALUE},
        {"0", Converter::ArkValue<Opt_Float64>(0), "0.000000"},
        {"1234", Converter::ArkValue<Opt_Float64>(1234), "1234.000000"},
    };
    checkControlButtonAttr(leftValues, ATTRIBUTE_CONTROL_BUTTON_LEFT_NAME);
    checkControlButtonAttr(topValues, ATTRIBUTE_CONTROL_BUTTON_TOP_NAME);
    checkControlButtonAttr(widthValues, ATTRIBUTE_CONTROL_BUTTON_WIDTH_NAME);
    checkControlButtonAttr(heightValues, ATTRIBUTE_CONTROL_BUTTON_HEIGHT_NAME);
}


// Valid values for attribute 'left' of method 'controlButton'
static std::vector<std::tuple<std::string, Ark_String, std::string>> controlButtonIconStringValues = {
    {ICON_STRING, ARK_STR_ICON_VALID, ICON_STRING},
    {ICON_STRING_DEF, Converter::ArkValue<Ark_String>(""), ICON_STRING_DEF},
};

Ark_ButtonStyle GetButtonStyle()
{
    Ark_ButtonStyle style;
    style.left = Converter::ArkValue<Opt_Float64>();
    style.top = Converter::ArkValue<Opt_Float64>();
    style.width = Converter::ArkValue<Opt_Float64>();
    style.height = Converter::ArkValue<Opt_Float64>();
    WriteTo(style.icons).shown = Converter::ArkUnion<Ark_Union_String_PixelMap_Resource, Ark_String>(
        ICON_STRING_DEF);
    WriteTo(style.icons).hidden = Converter::ArkUnion<Ark_Union_String_PixelMap_Resource, Ark_String>(
        ICON_STRING_DEF);
    WriteTo(style.icons).switching = Converter::ArkUnion<Opt_Union_String_PixelMap_Resource, Ark_String>(
        ICON_STRING_DEF);
    return style;
}

/*
 * @tc.name: setControlButtonTestIconsStringValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setControlButtonTestIconsStringValidValues, TestSize.Level1)
{
    auto style = GetButtonStyle();
    auto checkValue = [this, &style](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_String_PixelMap_Resource& value) {
        Ark_ButtonStyle inputStyle = style;
        WriteTo(inputStyle.icons).shown = value;
        WriteTo(inputStyle.icons).hidden = value;
        WriteTo(inputStyle.icons).switching = Converter::ArkValue<Opt_Union_String_PixelMap_Resource>(value);
        auto style = Converter::ArkValue<Opt_ButtonStyle>(inputStyle);
        modifier_->setControlButton(node_, &style);
        auto jsonValue = GetJsonValue(node_);
        auto resultControlButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONTROL_BUTTON_NAME);
        auto resultIcons =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultControlButton, ATTRIBUTE_CONTROL_BUTTON_ICONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultIcons, ATTRIBUTE_CONTROL_BUTTON_ICONS_SHOWN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setControlButton, attribute: controlButton.icons.shown";
        resultStr = GetAttrValue<std::string>(resultIcons, ATTRIBUTE_CONTROL_BUTTON_ICONS_HIDDEN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setControlButton, attribute: controlButton.icons.shown";
        resultStr = GetAttrValue<std::string>(resultIcons, ATTRIBUTE_CONTROL_BUTTON_ICONS_SWITCH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setControlButton, attribute: controlButton.icons.shown";
    };

    for (auto& [input, value, expected] : controlButtonIconStringValues) {
        checkValue(input, expected, Converter::ArkUnion<Ark_Union_String_PixelMap_Resource, Ark_String>(value));
    }
    auto res = CreateResource(RES_SRC_TEST, ResourceType::STRING);
    auto valueRes = Converter::ArkUnion<Ark_Union_String_PixelMap_Resource, Ark_Resource>(res);
    checkValue(ICON_STRING, ICON_STRING, valueRes);
}

/*
 * @tc.name: setControlButtonTestIconsPixelMapValidValues
 * @tc.desc: DISABLED due to Pixelmap case is under #if defined(PIXEL_MAP_SUPPORTED)
 * in CreateSourceInfo() SideBarContainerModelNG
 * Test is PASS if PIXEL_MAP_SUPPORTED
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, DISABLED_setControlButtonTestIconsPixelMapValidValues, TestSize.Level1)
{
    auto style = GetButtonStyle();
    void* ptr = reinterpret_cast<void*>(const_cast<char*>(ICON_STRING.data()));
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(ptr);
    image_PixelMapPeer pixelMapPeer;
    pixelMapPeer.pixelMap = pixelMap;
    auto checkValue = [this, &style, pixelMap](const std::string& input, const std::string& expectedStr,
        const Ark_Union_String_PixelMap_Resource& value) {
        Ark_ButtonStyle inputStyle = style;
        WriteTo(inputStyle.icons).shown = value;
        WriteTo(inputStyle.icons).hidden = value;
        WriteTo(inputStyle.icons).switching = Converter::ArkValue<Opt_Union_String_PixelMap_Resource>(value);
        auto style = Converter::ArkValue<Opt_ButtonStyle>(inputStyle);
        modifier_->setControlButton(node_, &style);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
        ASSERT_NE(layoutProperty, nullptr);
        auto info = layoutProperty->GetControlButtonShowIconInfo();
        ASSERT_NE(info, std::nullopt);
        EXPECT_TRUE(info->IsPixmap());
        EXPECT_EQ(info->GetPixmap(), pixelMap);
        info = layoutProperty->GetControlButtonHiddenIconInfo();
        ASSERT_NE(info, std::nullopt);
        EXPECT_TRUE(info->IsPixmap());
        EXPECT_EQ(info->GetPixmap(), pixelMap);
        info = layoutProperty->GetControlButtonSwitchingIconInfo();
        ASSERT_NE(info, std::nullopt);
        EXPECT_TRUE(info->IsPixmap());
        EXPECT_EQ(info->GetPixmap(), pixelMap);
    };
    auto valuePx = Converter::ArkUnion<Ark_Union_String_PixelMap_Resource, Ark_image_PixelMap>(&pixelMapPeer);
    checkValue(ICON_STRING, ICON_STRING, valuePx);
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

static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> showControlButtonValidValues = {
    {"true", Converter::ArkValue<Opt_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Opt_Boolean>(false), "false"},
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
    Opt_Boolean inputValue;
    for (auto [passed, checkVal, expected]: showControlButtonValidValues) {
        inputValue = checkVal;
        modifier_->setShowControlButton(node_, &inputValue);
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
HWTEST_F(SideBarContainerModifierTest, DISABLED_setOnChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t nodeId;
        bool value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_Boolean_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_Boolean value) {
            checkEvent = {
                .nodeId = nodeId,
                .value = Converter::Convert<bool>(value)
            };
        }
    };
    auto optCallback = Converter::ArkValue<Opt_Callback_Boolean_Void>(arkCallback);
    modifier_->setOnChange(node_, &optCallback);
    auto eventHub = frameNode->GetEventHub<NG::SideBarContainerEventHub>();
    eventHub->FireChangeEvent(true);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_TRUE(checkEvent->value);
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(true);
    EXPECT_TRUE(checkEvent->value);
}

/*
 * @tc.name: setSideBarWidth0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setSideBarWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SIDE_BAR_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SIDE_BAR_WIDTH_DEFAULT_VALUE);
}

// Valid values for attribute 'sideBarWidth' of method 'sideBarWidth'
static std::vector<std::tuple<std::string, float, std::string>> mSideBarWidthValidValues1 = {
    {EXPECTED_NUM_NEG, AINT32_NEG, ATTRIBUTE_SIDE_BAR_WIDTH_DEFAULT_VALUE},
    {EXPECTED_NUM_ZERO, AINT32_ZERO, EXPECTED_NUM_ZERO},
    {EXPECTED_NUM_VILID, AINT32_POS, EXPECTED_NUM_VILID},
};

/*
 * @tc.name: setSideBarWidth0TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setSideBarWidthTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    for (auto [passed, checkVal, expected]: mSideBarWidthValidValues1) {
        auto width = Converter::ArkUnion<Opt_Union_Length_Bindable, Ark_Length>(checkVal);
        modifier_->setSideBarWidth(node_, &width);
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
HWTEST_F(SideBarContainerModifierTest, setMinSideBarWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_SIDE_BAR_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_SIDE_BAR_WIDTH_DEFAULT_VALUE);
}

static std::vector<std::tuple<std::string, Opt_Length, std::string>> mMinSideBarWidthValidValues1 = {
    {"0", Converter::ArkValue<Opt_Length>("0"), "0.000000"},
    {"-123", Converter::ArkValue<Opt_Length>("-123"), ATTRIBUTE_MIN_SIDE_BAR_WIDTH_DEFAULT_VALUE},
    {"123", Converter::ArkValue<Opt_Length>("123"), "123.000000"},
};

/*
 * @tc.name: setMinSideBarWidth0TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setMinSideBarWidthTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    for (auto [passed, width, expected]: mMinSideBarWidthValidValues1) {
        modifier_->setMinSideBarWidth(node_, &width);
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
HWTEST_F(SideBarContainerModifierTest, setMaxSideBarWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_SIDE_BAR_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_SIDE_BAR_WIDTH_DEFAULT_VALUE);
}

// Valid values for attribute 'maxSideBarWidth' of method 'maxSideBarWidth'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> maxSideBarWidthValidValues1 = {
    {"0", Converter::ArkValue<Opt_Length>("0"), "0.000000"},
    {"-123", Converter::ArkValue<Opt_Length>("-123"), ATTRIBUTE_MAX_SIDE_BAR_WIDTH_DEFAULT_VALUE},
    {"123", Converter::ArkValue<Opt_Length>("123"), "123.000000"},
};

/*
 * @tc.name: setMaxSideBarWidth0TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setMaxSideBarWidthTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    for (auto [passed, width, expected]: maxSideBarWidthValidValues1) {
        modifier_->setMaxSideBarWidth(node_, &width);
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
};

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
static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> autoHideValidValues = {
    {"true", Converter::ArkValue<Opt_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Opt_Boolean>(false), "false"},
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
    Opt_Boolean inputValueAutoHide;
    for (auto [passed, checkVal, expected]: autoHideValidValues) {
        inputValueAutoHide = checkVal;
        modifier_->setAutoHide(node_, &inputValueAutoHide);
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
        auto position = Converter::ArkValue<Opt_SideBarPosition>(checkVal);
        modifier_->setSideBarPosition(node_, &position);
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
static std::vector<std::tuple<std::string, Opt_Dimension, std::string>> minContentWidthValidValues = {
    {"-1", Converter::ArkValue<Opt_Dimension>(-1.f), EXPECTED_DEF_MIN_CONTENT_WIDTH},
    {"0", Converter::ArkValue<Opt_Dimension>(0.f), EXPECTED_NUM_ZERO},
    {"1234.00px", Converter::ArkValue<Opt_Dimension>("1234.00px"), EXPECTED_NUM_VILID},
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
    Opt_Dimension inputValue;
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
};

// Valid values for attribute 'startMargin' of method 'setDivider'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> dividerStartMarginValidValues = {
    {EXPECTED_NUM_NEG_PX, OPT_LEN_NUM_NEG, ATTRIBUTE_DIVIDER_START_MARGIN_DEFAULT_VALUE},
    {EXPECTED_NUM_ZERO_PX, OPT_LEN_NUM_ZERO, EXPECTED_NUM_ZERO_PX},
    {EXPECTED_NUM_VILID_PX, OPT_LEN_NUM_VALID, EXPECTED_NUM_VILID_PX},
};

// Valid values for attribute 'endMargin' of method 'setDivider'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> dividerEndMarginValidValues = {
    {EXPECTED_NUM_NEG_PX, OPT_LEN_NUM_NEG, ATTRIBUTE_DIVIDER_END_MARGIN_DEFAULT_VALUE},
    {EXPECTED_NUM_ZERO_PX, OPT_LEN_NUM_ZERO, EXPECTED_NUM_ZERO_PX},
    {EXPECTED_NUM_VILID_PX, OPT_LEN_NUM_VALID, EXPECTED_NUM_VILID_PX},
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
HWTEST_F(SideBarContainerModifierTest, DISABLED_setDividerTestColorValidValues, TestSize.Level1)
{
    checkDividerColorAttr(dividerColorValidValues);
}

#ifdef WRONG_OLD_SDK
/*
 * @tc.name: setOnChangeEventSelectImpl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModifierTest, setOnChangeEventSelectImpl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::optional<bool> value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Opt_Boolean parameter) {
        checkEvent = {
            .nodeId = resourceId,
            .value = Converter::OptConvert<bool>(parameter)
        };
    };

    auto arkCallback = Converter::ArkValue<Callback_Opt_Boolean_Void>(checkCallback, contextId);
    modifier_->set_onChangeEvent_showSideBar(node_, &arkCallback);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireChangeEvent(true);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, true);
    eventHub->FireChangeEvent(false);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, false);
}
#endif

} // namespace OHOS::Ace::NG
