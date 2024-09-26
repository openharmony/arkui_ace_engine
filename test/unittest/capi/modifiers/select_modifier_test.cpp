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
#include "node_api.h"

#include "core/components/select/select_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_pattern.h"

#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
const auto THEME_SPACE = Dimension(23, DimensionUnit::PX);
const double THEME_FONT_OPACITY = 0.5;
const Color THEME_BACKGROUND_COLOR(0xFFAABBC1);
const Color THEME_FONT_COLOR(0xFFAABBC3);
const Color THEME_SELECTED_OPTION_FONT_COLOR(0xFFAABBC4);

const std::vector<SelectParam> SELECT_PARAMS = {
    { .text = "Option A" },
    { .text = "Option B" },
    { .text = "Option C" }
};

// length values
const Ark_Int32 AINT32_POS(1234);
const Ark_Int32 AINT32_NEG(INT_MIN);
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);
const auto ALEN_PX_POS = ArkValue<Ark_Length>(AINT32_POS);
const auto ALEN_PX_NEG = ArkValue<Ark_Length>(AINT32_NEG);
const auto ALEN_VP_POS = ArkValue<Ark_Length>(AFLT32_POS);
const auto ALEN_VP_NEG = ArkValue<Ark_Length>(AFLT32_NEG);

// check length
const std::string CHECK_POSITIVE_VALUE_INT("1234.00px");
const std::string CHECK_NEGATIVE_VALUE_INT("-2147483648.00px");
const std::string CHECK_POSITIVE_VALUE_FLOAT("1.23vp");
const std::string CHECK_POSITIVE_VALUE_FLOAT_PX("1.23px");
const std::string CHECK_NEGATIVE_VALUE_FLOAT("-5.68vp");

struct MenuAlignTest {
    Ark_MenuAlignType menuAlignType;
    Ark_Offset offset;
    std::string expectedMenuAlignType;
    float expectedDx;
    float expectedDy;
};

inline Ark_Resource ArkRes(Ark_String *name, int id = -1,
    NodeModifier::ResourceType type = NodeModifier::ResourceType::COLOR,
    const char *module = "", const char *bundle = "")
{
    return {
        .id = {.tag= ARK_TAG_INT32, .i32 = static_cast<Ark_Int32>(id) },
        .type = {.tag= ARK_TAG_INT32, .i32 = static_cast<Ark_Int32>(type)},
        .moduleName = {.chars = module},
        .bundleName = {.chars = bundle},
        .params = { .tag = ARK_TAG_OBJECT, .value = {.array = name, .length = name ? 1 : 0} }
    };
}

int g_eventOnSelectIndex;
std::string g_eventOnSelectValue;

GENERATED_ArkUISelectEventsReceiver recv {
    .onSelect = [](Ark_Int32 nodeId, const Ark_Number index, const Ark_String value) {
        g_eventOnSelectIndex = Convert<int>(index);
        g_eventOnSelectValue = Convert<std::string>(value);
    }
};

const GENERATED_ArkUISelectEventsReceiver* getSelectEventsReceiverTest()
{
    return &recv;
};

const GENERATED_ArkUIEventsAPI* GetArkUiEventsAPITest()
{
    static const GENERATED_ArkUIEventsAPI eventsImpl = { .getSelectEventsReceiver = getSelectEventsReceiverTest };
    return &eventsImpl;
};
} // namespace

class SelectModifierTest : public ModifierTestBase<GENERATED_ArkUISelectModifier,
    &GENERATED_ArkUINodeModifiers::getSelectModifier, GENERATED_ARKUI_SELECT> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = SetupThemeStyle("select_pattern");
        themeStyle->SetAttr("content_spinner_padding", { .value = THEME_SPACE });
        themeStyle->SetAttr("bg_color", { .value = THEME_BACKGROUND_COLOR });
        themeStyle->SetAttr("text_color", { .value = THEME_FONT_COLOR });
        themeStyle->SetAttr("text_color_selected", { .value = THEME_SELECTED_OPTION_FONT_COLOR });
        themeStyle->SetAttr("menu_text_primary_alpha", { .value = THEME_FONT_OPACITY });

        SetupTheme<SelectTheme>();
        SetupTheme<TextTheme>();
        SetupTheme<IconTheme>();

        fullAPI_->setArkUIEventsAPI(GetArkUiEventsAPITest());
    }

    void SetUp(void) override
    {
        ModifierTestBase::SetUp();
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        if (frameNode) {
            SelectModelNG::InitSelect(frameNode, SELECT_PARAMS);
            auto selectPattern = frameNode->GetPatternPtr<SelectPattern>();
            std::vector<RefPtr<FrameNode>> options = selectPattern->GetOptions();
            options[0]->GetPattern()->OnModifyDone(); // Init selectTheme
        }
    }
};

/**
 * @tc.name: setFontColorTest
 * @tc.desc: Test setFontColor function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontColorTest, TestSize.Level1)
{
    const std::string propName("fontColor");
    const Color defaultColor = THEME_FONT_COLOR.BlendOpacity(THEME_FONT_OPACITY);

    ASSERT_NE(modifier_->setFontColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, defaultColor.ToString());

    Ark_ResourceColor color = ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    modifier_->setFontColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");

    Ark_ResourceColor numberInt = ArkUnion<Ark_ResourceColor, Ark_Number>(0x123401);
    modifier_->setFontColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal3, "#FF123401");

    Ark_ResourceColor numberFlt = ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f);
    modifier_->setFontColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal4, "#00000000");
 
    Ark_ResourceColor strColor = ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    modifier_->setFontColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = ArkUnion<Ark_ResourceColor, Ark_String>("65535");
    modifier_->setFontColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal6, "#FF00FFFF");

    auto resName = ArkValue<Ark_String>("aa.bb.cc");
    Ark_ResourceColor resNameColor = ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(&resName));
    modifier_->setFontColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    Ark_ResourceColor resIdColor = ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(nullptr, 1234));
    modifier_->setFontColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)
}

/**
 * @tc.name: setMenuBackgroundColorTest
 * @tc.desc: Test setMenuBackgroundColor function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuBackgroundColorTest, TestSize.Level1)
{
    const std::string propName("menuBackgroundColor");
    ASSERT_NE(modifier_->setMenuBackgroundColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, THEME_BACKGROUND_COLOR.ToString());

    Ark_ResourceColor color = ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    modifier_->setMenuBackgroundColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");
 
    Ark_ResourceColor numberInt = ArkUnion<Ark_ResourceColor, Ark_Number>(0x123401);
    modifier_->setMenuBackgroundColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal3, "#FF123401");

    Ark_ResourceColor numberFlt = ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f);
    modifier_->setMenuBackgroundColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    modifier_->setMenuBackgroundColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = ArkUnion<Ark_ResourceColor, Ark_String>("65535");
    modifier_->setMenuBackgroundColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal6, "#FF00FFFF");
 
    auto resName = ArkValue<Ark_String>("aa.bb.cc");
    Ark_ResourceColor resNameColor = ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(&resName));
    modifier_->setMenuBackgroundColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    Ark_ResourceColor resIdColor = ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(nullptr, 1234));
    modifier_->setMenuBackgroundColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)
}

/**
 * @tc.name: setSelectedOptionBgColorTest
 * @tc.desc: Test setSelectedOptionBgColor function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionBgColorTest, TestSize.Level1)
{
    const std::string propName("selectedOptionBgColor");
    ASSERT_NE(modifier_->setSelectedOptionBgColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, "");

    Ark_ResourceColor color = ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    modifier_->setSelectedOptionBgColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");

    Ark_ResourceColor numberInt = ArkUnion<Ark_ResourceColor, Ark_Number>(0x123401);
    modifier_->setSelectedOptionBgColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal3, "#FF123401");

    Ark_ResourceColor numberFlt = ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f);
    modifier_->setSelectedOptionBgColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    modifier_->setSelectedOptionBgColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = ArkUnion<Ark_ResourceColor, Ark_String>("65535");
    modifier_->setSelectedOptionBgColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal6, "#FF00FFFF");

    auto resName = ArkValue<Ark_String>("aa.bb.cc");
    Ark_ResourceColor resNameColor = ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(&resName));
    modifier_->setSelectedOptionBgColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    Ark_ResourceColor resIdColor = ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(nullptr, 1234));
    modifier_->setSelectedOptionBgColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)
}

/**
 * @tc.name: setSelectedOptionFontColorTest
 * @tc.desc: Test setSelectedOptionFontColor function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontColorTest, TestSize.Level1)
{
    const std::string propName("selectedOptionFontColor");
    ASSERT_NE(modifier_->setSelectedOptionFontColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, THEME_SELECTED_OPTION_FONT_COLOR.ToString());

    Ark_ResourceColor color = ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    modifier_->setSelectedOptionFontColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");

    Ark_ResourceColor numberInt = ArkUnion<Ark_ResourceColor, Ark_Number>(0x123401);
    modifier_->setSelectedOptionFontColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal3, "#FF123401");

    Ark_ResourceColor numberFlt = ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f);
    modifier_->setSelectedOptionFontColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    modifier_->setSelectedOptionFontColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = ArkUnion<Ark_ResourceColor, Ark_String>("65535");
    modifier_->setSelectedOptionFontColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal6, "#FF00FFFF");

    auto resName = ArkValue<Ark_String>("aa.bb.cc");
    Ark_ResourceColor resNameColor = ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(&resName));
    modifier_->setSelectedOptionFontColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    Ark_ResourceColor resIdColor = ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(nullptr, 1234));
    modifier_->setSelectedOptionFontColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)
}

/**
 * @tc.name: setOptionBgColorTest
 * @tc.desc: Test setOptionBgColor function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionBgColorTest, TestSize.Level1)
{
    const std::string propName("optionBgColor");
    ASSERT_NE(modifier_->setOptionBgColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, THEME_BACKGROUND_COLOR.ToString());

    Ark_ResourceColor color = ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    modifier_->setOptionBgColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");
 
    Ark_ResourceColor numberInt = ArkUnion<Ark_ResourceColor, Ark_Number>(0x123401);
    modifier_->setOptionBgColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal3, "#FF123401");

    Ark_ResourceColor numberFlt = ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f);
    modifier_->setOptionBgColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    modifier_->setOptionBgColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = ArkUnion<Ark_ResourceColor, Ark_String>("65535");
    modifier_->setOptionBgColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal6, "#FF00FFFF");
 
    auto resName = ArkValue<Ark_String>("aa.bb.cc");
    Ark_ResourceColor resNameColor = ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(&resName));
    modifier_->setOptionBgColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    Ark_ResourceColor resIdColor = ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(nullptr, 1234));
    modifier_->setOptionBgColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)
}

/**
 * @tc.name: setOptionFontColorTest
 * @tc.desc: Test setOptionFontColor function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFontColorTest, TestSize.Level1)
{
    const std::string propName("optionFontColor");
    ASSERT_NE(modifier_->setOptionFontColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, THEME_FONT_COLOR.ToString());

    Ark_ResourceColor color = ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    modifier_->setOptionFontColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");

    Ark_ResourceColor numberInt = ArkUnion<Ark_ResourceColor, Ark_Number>(0x123401);
    modifier_->setOptionFontColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal3, "#FF123401");

    Ark_ResourceColor numberFlt = ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f);
    modifier_->setOptionFontColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    modifier_->setOptionFontColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = ArkUnion<Ark_ResourceColor, Ark_String>("65535");
    modifier_->setOptionFontColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal6, "#FF00FFFF");

    auto resName = ArkValue<Ark_String>("aa.bb.cc");
    Ark_ResourceColor resNameColor = ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(&resName));
    modifier_->setOptionFontColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    Ark_ResourceColor resIdColor = ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(nullptr, 1234));
    modifier_->setOptionFontColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)
}

/**
 * @tc.name: setControlSizeTest
 * @tc.desc: Test setControlSize function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setControlSizeTest, TestSize.Level1)
{
    const auto propName("controlSize");
    ASSERT_NE(modifier_->setControlSize, nullptr);

    modifier_->setControlSize(node_, ARK_CONTROL_SIZE_NORMAL);
    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, "ControlSize.NORMAL");

    modifier_->setControlSize(node_, ARK_CONTROL_SIZE_SMALL);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "ControlSize.SMALL");
}

/**
 * @tc.name: setMenuBackgroundBlurStyleTest
 * @tc.desc: Test setMenuBackgroundBlurStyle function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuBackgroundBlurStyleTest, TestSize.Level1)
{
    const auto propName("menuBackgroundBlurStyle");

    using Pair = std::pair<Ark_BlurStyle, std::string>;
    const std::vector<Pair> BLUR_STYLE_TEST_PLAN = {
        { ARK_BLUR_STYLE_THIN, "BlurStyle.Thin" },
        { ARK_BLUR_STYLE_REGULAR, "BlurStyle.Regular" },
        { ARK_BLUR_STYLE_THICK, "BlurStyle.Thick" },
        { ARK_BLUR_STYLE_BACKGROUND_THIN, "BlurStyle.BACKGROUND_THIN" },
        { ARK_BLUR_STYLE_BACKGROUND_REGULAR, "BlurStyle.BACKGROUND_REGULAR" },
        { ARK_BLUR_STYLE_BACKGROUND_THICK, "BlurStyle.BACKGROUND_THICK" },
        { ARK_BLUR_STYLE_BACKGROUND_ULTRA_THICK, "BlurStyle.BACKGROUND_ULTRA_THICK" },
        { ARK_BLUR_STYLE_NONE, "BlurStyle.NONE" },
        { ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN, "BlurStyle.COMPONENT_ULTRA_THIN" },
        { ARK_BLUR_STYLE_COMPONENT_THIN, "BlurStyle.COMPONENT_THIN" },
        { ARK_BLUR_STYLE_COMPONENT_REGULAR, "BlurStyle.COMPONENT_REGULAR" },
        { ARK_BLUR_STYLE_COMPONENT_THICK, "BlurStyle.COMPONENT_THICK" },
        { ARK_BLUR_STYLE_COMPONENT_ULTRA_THICK, "BlurStyle.COMPONENT_ULTRA_THICK" }
    };

    ASSERT_NE(modifier_->setMenuBackgroundBlurStyle, nullptr);

    for (auto blurStyle: BLUR_STYLE_TEST_PLAN) {
        modifier_->setMenuBackgroundBlurStyle(node_, blurStyle.first);
        auto checkVal = GetStringAttribute(node_, propName);
        EXPECT_EQ(checkVal, blurStyle.second);
    }
}

/**
 * @tc.name: setMenuAlignTest
 * @tc.desc: Test setMenuAlign function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuAlignTest, TestSize.Level1)
{
    const float offsetX1 = 11.f;
    const float offsetY1 = 35.f;
    const Ark_Offset offset1 = { .dx = ArkValue<Ark_Length>(offsetX1), .dy = ArkValue<Ark_Length>(offsetY1) };

    const float offsetX2 = 25.f;
    const float offsetY2 = 40.f;
    const Ark_Offset offset2 = { .dx = ArkValue<Ark_Length>(offsetX2), .dy = ArkValue<Ark_Length>(offsetY2) };

    const std::vector<MenuAlignTest> MENU_ALIGN_TEST_PLAN = {
        {
            .menuAlignType = ARK_MENU_ALIGN_TYPE_START, .expectedMenuAlignType = "MenuAlignType.Start",
            .offset = offset1, .expectedDx = offsetX1, .expectedDy = offsetY1
        },
        {
            .menuAlignType = ARK_MENU_ALIGN_TYPE_CENTER, .expectedMenuAlignType = "MenuAlignType.Center",
            .offset = offset1, .expectedDx = offsetX1, .expectedDy = offsetY1
        },
        {
            .menuAlignType = ARK_MENU_ALIGN_TYPE_END, .expectedMenuAlignType = "MenuAlignType.End",
            .offset = offset1, .expectedDx = offsetX1, .expectedDy = offsetY1
        },
        {
            .menuAlignType = ARK_MENU_ALIGN_TYPE_END, .expectedMenuAlignType = "MenuAlignType.End",
            .offset = offset2, .expectedDx = offsetX2, .expectedDy = offsetY2
        }
    };

    ASSERT_NE(modifier_->setMenuAlign, nullptr);

    for (const auto& data: MENU_ALIGN_TEST_PLAN) {
        auto optOffset = ArkValue<Opt_Offset>(data.offset);
        modifier_->setMenuAlign(node_, data.menuAlignType, &optOffset);

        auto fullJson = GetJsonValue(node_);
        auto menuAlignJson = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "menuAlign");
        ASSERT_NE(menuAlignJson, nullptr);

        auto alignTypeStr = GetAttrValue<std::string>(menuAlignJson, "alignType");
        EXPECT_EQ(alignTypeStr, data.expectedMenuAlignType);

        auto offsetJson = GetAttrValue<std::unique_ptr<JsonValue>>(menuAlignJson, "offset");
        ASSERT_NE(offsetJson, nullptr);
        auto actualDx = GetAttrValue<double>(offsetJson, "dX");
        auto actualDy = GetAttrValue<double>(offsetJson, "dY");
        EXPECT_FLOAT_EQ(actualDx, data.expectedDx);
        EXPECT_FLOAT_EQ(actualDy, data.expectedDy);
    };
}

/**
 * @tc.name: setSpaceTest
 * @tc.desc: Test setSpace function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSpaceTest, TestSize.Level1)
{
    const auto propName("space");

    const std::string expectedDefaultSpace("23.00px");

    using Pair = std::pair<Ark_Length, std::string>;
    const std::vector<Pair> SPACE_TEST_PLAN = {
        { ALEN_PX_POS, CHECK_POSITIVE_VALUE_INT },
        { ALEN_PX_NEG, expectedDefaultSpace },
        { ALEN_VP_NEG, expectedDefaultSpace },
        { ALEN_VP_POS, CHECK_POSITIVE_VALUE_FLOAT }
    };

    ASSERT_NE(modifier_->setSpace, nullptr);

    for (const auto &[value, expectVal]: SPACE_TEST_PLAN) {
        modifier_->setSpace(node_, &value);
        auto checkVal = GetStringAttribute(node_, propName);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setArrowPositionTest
 * @tc.desc: Test setArrowPosition function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setArrowPositionTest, TestSize.Level1)
{
    const auto propName("arrowPosition");
    ASSERT_NE(modifier_->setArrowPosition, nullptr);

    modifier_->setArrowPosition(node_, Ark_ArrowPosition::ARK_ARROW_POSITION_START);
    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, "ArrowPosition.START");

    modifier_->setArrowPosition(node_, Ark_ArrowPosition::ARK_ARROW_POSITION_END);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "ArrowPosition.END");
}

/**
 * @tc.name: setOptionHeightTest
 * @tc.desc: Test setOptionHeight function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionHeightTest, TestSize.Level1)
{
    const auto propName("optionHeight");

    using Pair = std::pair<Ark_Length, float>;
    const std::vector<Pair> OPTION_HEIGHT_TEST_PLAN = {
        { ALEN_PX_POS, 1234.f },
        { ALEN_PX_NEG, 1234.f }, // check that negative value is ignored
        { ALEN_VP_NEG, 1234.f }, // check that negative value is ignored
        { ALEN_VP_POS, 1.234f }
    };

    ASSERT_NE(modifier_->setOptionHeight, nullptr);

    for (const auto &[value, expectVal]: OPTION_HEIGHT_TEST_PLAN) {
        modifier_->setOptionHeight(node_, &value);
        auto checkVal = GetStringAttribute(node_, propName);
        EXPECT_FLOAT_EQ(std::stof(checkVal), expectVal);
    }
}

/**
 * @tc.name: setSelectedTest
 * @tc.desc: Test setSelected function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedTest, TestSize.Level1)
{
    const auto propName("selected");
    ASSERT_NE(modifier_->setSelected, nullptr);

    const int size = SELECT_PARAMS.size();
    const int defaultValue = -1;
    std::vector<std::pair<Union_Number_Resource, int>> TEST_PLAN = {
        { ArkUnion<Union_Number_Resource, Ark_Number>(1), 1 },
        { ArkUnion<Union_Number_Resource, Ark_Number>(0), 0 },
        { ArkUnion<Union_Number_Resource, Ark_Number>(size), defaultValue }, // check invalid value
        { ArkUnion<Union_Number_Resource, Ark_Number>(size - 1), size - 1 },
        { ArkUnion<Union_Number_Resource, Ark_Number>(-10), defaultValue }, // check invalid value
        { ArkUnion<Union_Number_Resource, Ark_Number>(1.8f), 1 }
    };

    auto checkVal0 = GetStringAttribute(node_, propName);
    EXPECT_EQ(std::stoi(checkVal0), defaultValue);

    for (const auto& data: TEST_PLAN) {
        modifier_->setSelected(node_, &data.first);
        auto checkVal = GetStringAttribute(node_, propName);
        EXPECT_EQ(std::stoi(checkVal), data.second);
    }
}

/**
 * @tc.name: setOnSelectTest
 * @tc.desc: Test setOnSelect function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOnSelectTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnSelect, nullptr);

    g_eventOnSelectIndex = 0;
    g_eventOnSelectValue = "";

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Ark_Function func = {};
    modifier_->setOnSelect(node_, func);
    auto selectEventHub = frameNode->GetEventHub<SelectEventHub>();
    EXPECT_EQ(g_eventOnSelectIndex, 0);
    EXPECT_EQ(g_eventOnSelectValue, "");

    SelectEvent selectEvent = selectEventHub->GetSelectEvent();
    ASSERT_NE(selectEvent, nullptr);
    const int index = 1;
    const std::string value = "Option B";
    selectEvent(index, value);
    EXPECT_EQ(g_eventOnSelectIndex, index);
    EXPECT_EQ(g_eventOnSelectValue, value);

    ASSERT_NE(&recv, nullptr);
}

} // namespace OHOS::Ace::NG
