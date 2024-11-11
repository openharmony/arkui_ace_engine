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

#include "core/components/indexer/indexer_theme.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/indexer/indexer_event_hub.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
struct EventsTracker {
    static inline GENERATED_ArkUIAlphabetIndexerEventsReceiver alphabetIndexerEventReceiver {};

    static inline const GENERATED_ArkUIEventsAPI eventsApiImpl {
        .getAlphabetIndexerEventsReceiver = []() -> const GENERATED_ArkUIAlphabetIndexerEventsReceiver* {
            return &alphabetIndexerEventReceiver;
        }
    };
}; // EventsTracker
} // namespace

// Prop names
const auto PROP_NAME_ARRAY_VALUE = "arrayValue";
const auto PROP_NAME_COLOR = "color";
const auto PROP_NAME_SELECTED_COLOR = "selectedColor";
const auto PROP_NAME_POPUP_COLOR = "popupColor";
const auto PROP_NAME_SELECTED_BACKGROUND_COLOR = "selectedBackgroundColor";
const auto PROP_NAME_POPUP_BACKGROUND = "popupBackground";
const auto PROP_NAME_POPUP_SELECTED_COLOR = "popupSelectedColor";
const auto PROP_NAME_POPUP_UNSELECTED_COLOR = "popupUnselectedColor";
const auto PROP_NAME_POPUP_ITEM_BACKGROUND = "popupItemBackground";
const auto PROP_NAME_USING_POPUP = "usingPopup";
const auto PROP_NAME_SELECTED_FONT = "selectedFont";
const auto PROP_NAME_POPUP_FONT = "popupFont";
const auto PROP_NAME_POPUP_ITEM_FONT_SIZE = "popupItemFontSize";
const auto PROP_NAME_POPUP_ITEM_FONT_WEIGHT = "popupItemFontWeight";
const auto PROP_NAME_ITEM_SIZE = "itemSize";
const auto PROP_NAME_FONT = "font";
const auto PROP_NAME_FONT_SIZE = "fontSize";
const auto PROP_NAME_FONT_WEIGHT = "fontWeight";
const auto PROP_NAME_FONT_STYLE = "fontStyle";
const auto PROP_NAME_FONT_FAMILY = "fontFamily";
const auto PROP_NAME_ALIGN_STYLE = "alignStyle";
const auto PROP_NAME_POPUP_HORIZONTAL_SPACE = "popupHorizontalSpace";
const auto PROP_NAME_SELECTED = "selected";
const auto PROP_NAME_POPUP_POSITION = "popupPosition";
const auto PROP_NAME_POPUP_POSITION_X = "popupPositionX";
const auto PROP_NAME_POPUP_POSITION_Y = "popupPositionY";
const auto PROP_NAME_AUTO_COLLAPSE = "autoCollapse";
const auto PROP_NAME_POPUP_ITEM_BORDER_RADIUS = "popupItemBorderRadius";
const auto PROP_NAME_POPUP_BORDER_RADIUS = "popupBorderRadius";
const auto PROP_NAME_ITEM_BORDER_RADIUS = "itemBorderRadius";
const auto PROP_NAME_INDEXER_BORDER_RADIUS = "indexerBorderRadius";
const auto PROP_NAME_POPUP_BACKGROUND_BLUR_STYLE = "popupBackgroundBlurStyle";
const auto PROP_NAME_POPUP_TITLE_BACKGROUND = "popupTitleBackground";
const auto PROP_NAME_HAPTIC_FEEDBACK = "enableHapticFeedback";

// Default values
const auto ATTRIBUTE_ARRAY_VALUE_DEFAULT_VALUE = "[]";
const auto ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE = 0;
const auto ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE = "#FFFFFFFF";
const auto ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK = "#FF000000";
const auto ATTRIBUTE_USING_POPUP_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_ITEM_SIZE_INITIAL_VALUE = "0.00vp";
const auto ATTRIBUTE_ITEM_SIZE_DEFAULT_VALUE = "16.00vp";
const auto ATTRIBUTE_FONT_DEFAULT_SIZE = "14.00px";
const auto ATTRIBUTE_ALIGN_STYLE_DEFAULT_VALUE = "IndexerAlign.End";
const auto ATTRIBUTE_POPUP_HORIZONTAL_SPACE_DEFAULT_VALUE = "-1.00vp";
const auto ATTRIBUTE_SELECTED_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_POPUP_POSITION_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_AUTOCOLLAPSE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_POPUP_ITEM_BORDER_RADIUS_DEFAULT_VALUE = "24.00vp";
const auto ATTRIBUTE_ITEM_BORDER_RADIUS_DEFAULT_VALUE = "8.00vp";
const auto ATTRIBUTE_POPUP_BACKGROUND_BLUR_STYLE_DEFAULT_VALUE = "BlurStyle.COMPONENT_REGULAR";
const auto ATTRIBUTE_HAPTIC_FEEDBACK_DEFAULT_VALUE = "true";

// Expected values
static const std::string EXPECTED_TRUE("true");
static const std::string EXPECTED_FALSE("false");

// Test plans
typedef std::pair<std::vector<std::string>, std::string> ArrayValueTestStep;
static const std::vector<ArrayValueTestStep> ARRAY_VALUE_TEST_PLAN = {
    { { "a" }, "[\"a\"]" },
    { { "a", "b" }, "[\"a\",\"b\"]" },
    { { "a", "b", "c" }, "[\"a\",\"b\",\"c\"]" },
    { { }, ATTRIBUTE_ARRAY_VALUE_DEFAULT_VALUE },
    { { "a", "b", "c", "d", "e", "f" }, "[\"a\",\"b\",\"c\",\"d\",\"e\",\"f\"]" }
};
static const std::vector<int32_t> SELECTED_INDEX_TEST_PLAN = { 1, 10, 32, -1, -35, 832 };

typedef std::pair<Ark_Number, std::string> ArkNumberTestStep;
static const std::vector<ArkNumberTestStep> BORDER_RADIUS_TEST_PLAN = {
    { ArkValue<Ark_Number>(10), StringUtils::DoubleToString(10 + RADIUS_OFFSET).append("vp") },
    { ArkValue<Ark_Number>(832.599345f), StringUtils::DoubleToString(832.599345f + RADIUS_OFFSET).append("vp") },
    { ArkValue<Ark_Number>(-123), "0.00vp" },
    { ArkValue<Ark_Number>(25.01), StringUtils::DoubleToString(25.01 + RADIUS_OFFSET).append("vp") },
    { ArkValue<Ark_Number>(-832.5f), "0.00vp" },
    { ArkValue<Ark_Number>(0.0f), StringUtils::DoubleToString(RADIUS_OFFSET).append("vp") },
};
static const std::vector<ArkNumberTestStep> SELECTED_TEST_PLAN = {
    { ArkValue<Ark_Number>(10), "10" },
    { ArkValue<Ark_Number>(-10), "0"},
    { ArkValue<Ark_Number>(12.5), "12"},
    { ArkValue<Ark_Number>(-5.5), "0"},
    { ArkValue<Ark_Number>(832), "832"},
    { ArkValue<Ark_Number>(1.0f), "1"}
};

typedef std::pair<Ark_Union_String_Number, std::string> ItemSizeTestStep;
static const std::vector<ItemSizeTestStep> ITEM_SIZE_TEST_PLAN = {
    { { .selector = 1, .value1 = Converter::ArkValue<Ark_Number>(45.0f) }, "45.00vp"},
    { { .selector = 1, .value1 = Converter::ArkValue<Ark_Number>(-45) }, ATTRIBUTE_ITEM_SIZE_DEFAULT_VALUE},
    { { .selector = 1, .value1 = Converter::ArkValue<Ark_Number>(32) }, "32.00vp"},
    { { .selector = 1, .value1 = Converter::ArkValue<Ark_Number>(0) }, ATTRIBUTE_ITEM_SIZE_DEFAULT_VALUE},
    { { .selector = 0, .value0 = Converter::ArkValue<Ark_String>("15px") }, "15.00px"},
    { { .selector = 0, .value0 = Converter::ArkValue<Ark_String>("99%") }, ATTRIBUTE_ITEM_SIZE_DEFAULT_VALUE},
    { { .selector = 0, .value0 = Converter::ArkValue<Ark_String>("45vp") }, "45.00vp"},
    { { .selector = 0, .value0 = Converter::ArkValue<Ark_String>("-13px") }, ATTRIBUTE_ITEM_SIZE_DEFAULT_VALUE}
};

const std::string COLOR_RED = "#FFFF0000";
const std::string COLOR_BLACK = "#FF000000";
const std::string COLOR_TRANSPARENT = "#00000000";
const Ark_String COLOR_NAME = Converter::ArkValue<Ark_String>("color_name");

typedef std::tuple<Ark_ResourceColor, std::string> ColorTestStep;
const std::vector<ColorTestStep> COLOR_TEST_PLAN_BLACK = {
    { Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"), ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK }
};
const std::vector<ColorTestStep> COLOR_TEST_PLAN_WHITE = {
    { Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"), ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE }
};
const auto RES_COLOR_NAME = NamedResourceId{"color_name", NodeModifier::ResourceType::COLOR};
const auto RES_COLOR_ID = IntResourceId{123456, NodeModifier::ResourceType::COLOR};
const auto INVALID_ID_COLOR = IntResourceId{-1, NodeModifier::ResourceType::COLOR};
const std::vector<ColorTestStep> COLOR_TEST_PLAN_RES = {
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_NAME)),
        COLOR_RED },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_ID)),
        COLOR_RED },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(INVALID_ID_COLOR)),
        COLOR_RED }
};

const Ark_Int32 AINT32_POS(70);
const Ark_Int32 AINT32_NEG(INT_MIN);
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);
const auto CHECK_AINT32_POS = "70.00px";
const auto CHECK_AFLT32_POS = "1.23vp";

const auto RES_CONTENT = Converter::ArkValue<Ark_String>("aa.bb.cc");
const auto RES_NAME = NamedResourceId{"res_name", NodeModifier::ResourceType::STRING};
const Opt_Union_String_Resource OPT_UNION_RESOURCE_RESOURCE = CreateResourceUnion<Opt_Union_String_Resource>(RES_NAME);
const std::string CHECK_RESOURCE_STR("aa.bb.cc");

typedef std::pair<Opt_Union_String_Resource, std::string> UnionStringResourceTestStep;
const std::vector<UnionStringResourceTestStep> UNION_RESOURCE_STRING_PLAN = {
    { Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(RES_CONTENT), CHECK_RESOURCE_STR },
    { OPT_UNION_RESOURCE_RESOURCE, CHECK_RESOURCE_STR }
};

typedef std::pair<Opt_Length, std::string> OptLengthTestStep;
const std::vector<OptLengthTestStep> FONT_SIZE_TEST_PLAN = {
    { Converter::ArkValue<Opt_Length>(AINT32_POS), CHECK_AINT32_POS },
    { Converter::ArkValue<Opt_Length>(AINT32_NEG), ATTRIBUTE_FONT_DEFAULT_SIZE },
    { Converter::ArkValue<Opt_Length>(AFLT32_NEG), ATTRIBUTE_FONT_DEFAULT_SIZE },
    { Converter::ArkValue<Opt_Length>(AFLT32_POS), CHECK_AFLT32_POS }
};

typedef std::pair<Opt_FontStyle, std::string> ArkFontStyleTestStep;
const std::vector<ArkFontStyleTestStep> FONT_STYLE_TEST_PLAN = {
    { { .tag = ARK_TAG_OBJECT, .value = ARK_FONT_STYLE_NORMAL }, "FontStyle::NORMAL" },
    { { .tag = ARK_TAG_OBJECT, .value = ARK_FONT_STYLE_ITALIC }, "FontStyle::ITALIC" },
    { { .tag = ARK_TAG_OBJECT, .value = static_cast<Ark_FontStyle>(2) }, "FontStyle::NORMAL" },
};

typedef std::pair<Opt_Union_FontWeight_Number_String, std::string> ArkFontWeightTest;
const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN = {
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_LIGHTER),
        "FontWeight.Lighter" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_NORMAL),
        "FontWeight.Normal" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_REGULAR),
        "FontWeight.Regular" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_MEDIUM),
        "FontWeight.Medium" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD),
        "FontWeight.Bold" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLDER),
        "FontWeight.Bolder" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("lighter")),
        "FontWeight.Lighter" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("normal")),
        "FontWeight.Normal" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("regular")),
        "FontWeight.Regular" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("medium")),
        "FontWeight.Medium" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("bold")),
        "FontWeight.Bold" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("bolder")),
        "FontWeight.Bolder" }
};

const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN2 = {
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(100)),
        "100" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(200)),
        "200" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(300)),
        "300" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(400)),
        "400" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(500)),
        "500" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(600)),
        "600" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(700)),
        "700" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(800)),
        "800" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(900)),
        "900" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("100")),
        "100" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("200")),
        "200" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("300")),
        "300" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("400")),
        "400" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("500")),
        "500" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("600")),
        "600" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("700")),
        "700" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("800")),
        "800" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("900")),
        "900" }
};

typedef std::pair<Ark_IndexerAlign, std::string> AlignTestStep;
const std::vector<AlignTestStep> ALIGN_TEST_PLAN = {
    { Ark_IndexerAlign::ARK_INDEXER_ALIGN_START, "IndexerAlign.Start" },
    { Ark_IndexerAlign::ARK_INDEXER_ALIGN_END, "IndexerAlign.End" },
    { Ark_IndexerAlign::ARK_INDEXER_ALIGN_LEFT, "IndexerAlign.Left" },
    { Ark_IndexerAlign::ARK_INDEXER_ALIGN_RIGHT, "IndexerAlign.Right" }
};

const std::vector<OptLengthTestStep> POPUP_HORIZONTAL_OFFSET_TEST_PLAN = {
    { Converter::ArkValue<Opt_Length>(10), "10.00px" },
    { Converter::ArkValue<Opt_Length>(0), "0.00px" },
    { Converter::ArkValue<Opt_Length>(-20), ATTRIBUTE_POPUP_HORIZONTAL_SPACE_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>(15.4f), "15.40vp" },
    { Converter::ArkValue<Opt_Length>(22.11_px), "22.11px" },
    { Converter::ArkValue<Opt_Length>("99.00%"), "99.00%" },
    { Converter::ArkValue<Opt_Length>(13.0_vp), "13.00vp" },
    { Converter::ArkValue<Opt_Length>("-55.00%"), ATTRIBUTE_POPUP_HORIZONTAL_SPACE_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>("55.00%"), "55.00%" },
    { Converter::ArkValue<Opt_Length>(-3.12_px), ATTRIBUTE_POPUP_HORIZONTAL_SPACE_DEFAULT_VALUE }
};

typedef std::pair<Ark_Length, std::string> PopupPositionTestStep;
static const std::vector<PopupPositionTestStep> POPUP_POSITION_TEST_PLAN = {
    { Converter::ArkValue<Ark_Length>(10), "10.00px" },
    { Converter::ArkValue<Ark_Length>(0), "0.00px" },
    { Converter::ArkValue<Ark_Length>(-20), "-20.00px" },
    { Converter::ArkValue<Ark_Length>(15.4f), "15.40vp" },
    { Converter::ArkValue<Ark_Length>(22.11_px), "22.11px" },
    { Converter::ArkValue<Ark_Length>("99.00%"), "99.00%" },
    { Converter::ArkValue<Ark_Length>(13.0_vp), "13.00vp" },
    { Converter::ArkValue<Ark_Length>("-55.00%"), "-55.00%" },
    { Converter::ArkValue<Ark_Length>("55.00%"), "55.00%" },
    { Converter::ArkValue<Ark_Length>(-3.12_px), "-3.12px" }
};

typedef std::pair<Ark_BlurStyle, std::string> BlurStyleTestStep;
static const std::vector<BlurStyleTestStep> BLUR_STYLE_TEST_PLAN = {
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
    { ARK_BLUR_STYLE_COMPONENT_ULTRA_THICK, "BlurStyle.COMPONENT_ULTRA_THICK" },
    { static_cast<Ark_BlurStyle>(177), "BlurStyle.COMPONENT_REGULAR" }
};

class IndexerModifierTest
    : public ModifierTestBase<GENERATED_ArkUIAlphabetIndexerModifier,
          &GENERATED_ArkUINodeModifiers::getAlphabetIndexerModifier, GENERATED_ARKUI_ALPHABET_INDEXER> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<IndexerTheme>();

        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};

/**
 * @tc.name: setAlphabetIndexerOptionsArrayValue
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.SetAlphabetIndexerOptionsImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setAlphabetIndexerOptionsArrayValue, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAlphabetIndexerOptions, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_ARRAY_VALUE);
    EXPECT_EQ(checkVal, ATTRIBUTE_ARRAY_VALUE_DEFAULT_VALUE);

    Ark_AlphabetIndexerOptions options;
    for (const auto& [value, expectVal] : ARRAY_VALUE_TEST_PLAN) {
        Converter::ArkArrayHolder<Array_String> vecHolder(value);
        auto stringArrayResult = vecHolder.ArkValue();
        options.arrayValue = stringArrayResult;
        modifier_->setAlphabetIndexerOptions(node_, &options);
        checkVal = GetStringAttribute(node_, PROP_NAME_ARRAY_VALUE);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setAlphabetIndexerOptionsSelected
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.SetAlphabetIndexerOptionsImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setAlphabetIndexerOptionsSelected, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAlphabetIndexerOptions, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_SELECTED);
    EXPECT_EQ(checkVal, ATTRIBUTE_SELECTED_DEFAULT_VALUE);

    Ark_AlphabetIndexerOptions options;
    for (const auto& [value, expectVal] : SELECTED_TEST_PLAN) {
        options.selected = value;
        modifier_->setAlphabetIndexerOptions(node_, &options);
        checkVal = GetStringAttribute(node_, PROP_NAME_SELECTED);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setOnSelected
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.OnSelectedImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setOnSelected, TestSize.Level1)
{
    Callback_Number_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static int32_t selectedIndex = ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE;
    EventsTracker::alphabetIndexerEventReceiver.onSelected = [](Ark_Int32 nodeId, const Ark_Number value) {
        selectedIndex = Converter::Convert<int32_t>(value);
    };
    modifier_->setOnSelected(node_, &func);
    EXPECT_EQ(selectedIndex, ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE);

    auto onSelect = eventHub->GetOnSelected();

    for (const auto& expected : SELECTED_INDEX_TEST_PLAN) {
        onSelect(expected);
        EXPECT_EQ(selectedIndex, expected);
    }
}

/**
 * @tc.name: setColor
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.ColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_WHITE) {
        modifier_->setColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setColorRes
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.ColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setColorRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        modifier_->setColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setSelectedColor
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.SelectedColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setSelectedColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_SELECTED_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_WHITE) {
        modifier_->setSelectedColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTED_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setSelectedColorRes
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.SelectedColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setSelectedColorRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_SELECTED_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        modifier_->setSelectedColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTED_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupColor
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_WHITE) {
        modifier_->setPopupColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}
/**
 * @tc.name: setPopupColorRes
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupColorRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        modifier_->setPopupColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setSelectedBackgroundColor
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.SelectedBackgroundColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setSelectedBackgroundColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedBackgroundColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_SELECTED_BACKGROUND_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_WHITE) {
        modifier_->setSelectedBackgroundColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTED_BACKGROUND_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setSelectedBackgroundColorRes
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.SelectedBackgroundColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setSelectedBackgroundColorRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedBackgroundColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_SELECTED_BACKGROUND_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        modifier_->setSelectedBackgroundColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTED_BACKGROUND_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupBackground
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupBackgroundImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupBackground, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupBackground, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_BACKGROUND);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_WHITE) {
        modifier_->setPopupBackground(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_BACKGROUND);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupBackgroundRes
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupBackgroundImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupBackgroundRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupBackground, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_BACKGROUND);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        modifier_->setPopupBackground(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_BACKGROUND);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupSelectedColor
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupSelectedColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupSelectedColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupSelectedColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_SELECTED_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_BLACK) {
        modifier_->setPopupSelectedColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_SELECTED_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupSelectedColorRes
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupSelectedColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupSelectedColorRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupSelectedColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_SELECTED_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        modifier_->setPopupSelectedColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_SELECTED_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupUnselectedColor
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupUnselectedColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupUnselectedColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupUnselectedColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_UNSELECTED_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_BLACK) {
        modifier_->setPopupUnselectedColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_UNSELECTED_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupUnselectedColorRes
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupUnselectedColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupUnselectedColorRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupUnselectedColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_UNSELECTED_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        modifier_->setPopupUnselectedColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_UNSELECTED_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupItemBackgroundColor
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupItemBackgroundColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupItemBackgroundColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupItemBackgroundColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_ITEM_BACKGROUND);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_BLACK) {
        modifier_->setPopupItemBackgroundColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_ITEM_BACKGROUND);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupItemBackgroundColorRes
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupItemBackgroundColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupItemBackgroundColorRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupItemBackgroundColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_ITEM_BACKGROUND);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        modifier_->setPopupItemBackgroundColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_ITEM_BACKGROUND);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setUsingPopup
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.UsingPopupImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setUsingPopup, TestSize.Level1)
{
    static const std::string& DEFAULT_VALUE(ATTRIBUTE_USING_POPUP_DEFAULT_VALUE);
    ASSERT_NE(modifier_->setUsingPopup, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, PROP_NAME_USING_POPUP);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    modifier_->setUsingPopup(node_, true);
    auto checkVal2 = GetAttrValue<std::string>(node_, PROP_NAME_USING_POPUP);
    EXPECT_EQ(checkVal2, EXPECTED_TRUE);

    modifier_->setUsingPopup(node_, false);
    auto checkVal3 = GetAttrValue<std::string>(node_, PROP_NAME_USING_POPUP);
    EXPECT_EQ(checkVal3, EXPECTED_FALSE);
}

/**
 * @tc.name: setSelectedFontTest1
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.SelectedFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setSelectedFontTest1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        modifier_->setSelectedFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setSelectedFontTest2
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.SelectedFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setSelectedFontTest2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        modifier_->setSelectedFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        modifier_->setSelectedFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setSelectedFontTest3
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.SelectedFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setSelectedFontTest3, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto family : UNION_RESOURCE_STRING_PLAN) {
        font.family = family.first;
        modifier_->setSelectedFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setSelectedFontTest4
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.SelectedFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setSelectedFontTest4, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        modifier_->setSelectedFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setPopupFontTest1
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupFontTest1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        modifier_->setPopupFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_POPUP_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setPopupFontTest2
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupFontTest2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        modifier_->setPopupFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_POPUP_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        modifier_->setPopupFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_POPUP_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);;
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setPopupFontTest3
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setPopupFontTest3, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto family : UNION_RESOURCE_STRING_PLAN) {
        font.family = family.first;
        modifier_->setPopupFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_POPUP_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setPopupFontTest4
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupFontTest4, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        modifier_->setPopupFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_POPUP_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}


/**
 * @tc.name: setPopupItemFont1
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupItemFont
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupItemFont1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupItemFont, nullptr);
    Ark_Font font = {
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        modifier_->setPopupItemFont(node_, &font);
        auto checkSize = GetStringAttribute(node_, PROP_NAME_POPUP_ITEM_FONT_SIZE);
        auto checkWeight = GetStringAttribute(node_, PROP_NAME_POPUP_ITEM_FONT_WEIGHT);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        modifier_->setPopupItemFont(node_, &font);
        auto checkSize = GetStringAttribute(node_, PROP_NAME_POPUP_ITEM_FONT_SIZE);
        auto checkWeight = GetStringAttribute(node_, PROP_NAME_POPUP_ITEM_FONT_WEIGHT);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setPopupItemFont2
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupItemFont
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupItemFont2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupItemFont, nullptr);
    Ark_Font font = {
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        modifier_->setPopupItemFont(node_, &font);
        auto checkSize = GetStringAttribute(node_, PROP_NAME_POPUP_ITEM_FONT_SIZE);
        auto checkWeight = GetStringAttribute(node_, PROP_NAME_POPUP_ITEM_FONT_WEIGHT);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setItemSize
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.ItemSizeImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setItemSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setItemSize, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, PROP_NAME_ITEM_SIZE);
    EXPECT_EQ(checkVal, ATTRIBUTE_ITEM_SIZE_INITIAL_VALUE);

    for (const auto& [size, expectVal] : ITEM_SIZE_TEST_PLAN) {
        modifier_->setItemSize(node_, &size);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_ITEM_SIZE);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setFontTest1
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.FontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setFontTest1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        modifier_->setFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setFontTest2
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.FontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setFontTest2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        modifier_->setFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        modifier_->setFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setFontTest3
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.FontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setFontTest3, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto family : UNION_RESOURCE_STRING_PLAN) {
        font.family = family.first;
        modifier_->setFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setFontTest4
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.FontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setFontTest4, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        modifier_->setFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setAlignStyle
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.AlignStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setAlignStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAlignStyle, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, PROP_NAME_ALIGN_STYLE);
    EXPECT_EQ(checkVal, ATTRIBUTE_ALIGN_STYLE_DEFAULT_VALUE);

    const auto& arkOffset = Converter::ArkValue<Opt_Length>(Ark_Empty());
    for (const auto& [value, expectVal] : ALIGN_TEST_PLAN) {
        modifier_->setAlignStyle(node_, value, &arkOffset);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_ALIGN_STYLE);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setAlignStyleOffset
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.AlignStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setAlignStyleOffset, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAlignStyle, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_HORIZONTAL_SPACE);
    EXPECT_EQ(checkVal, ATTRIBUTE_POPUP_HORIZONTAL_SPACE_DEFAULT_VALUE);

    for (const auto& [value, expectVal] : POPUP_HORIZONTAL_OFFSET_TEST_PLAN) {
        modifier_->setAlignStyle(node_, ARK_INDEXER_ALIGN_START, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_HORIZONTAL_SPACE);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setOnSelect
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.OnSelectImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setOnSelect, TestSize.Level1)
{
    OnAlphabetIndexerSelectCallback func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static int32_t selectedIndex = ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE;
    EventsTracker::alphabetIndexerEventReceiver.onSelect = [](Ark_Int32 nodeId, const Ark_Number value) {
        selectedIndex = Converter::Convert<int32_t>(value);
    };
    modifier_->setOnSelect(node_, &func);
    EXPECT_EQ(selectedIndex, ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE);

    auto onChange = eventHub->GetChangeEvent();

    for (const auto& expected : SELECTED_INDEX_TEST_PLAN) {
        onChange(expected);
        EXPECT_EQ(selectedIndex, expected);
    }
}

/**
 * @tc.name: setOnRequestPopupData
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.OnRequestPopupDataImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setOnRequestPopupData, TestSize.Level1)
{
    // blocked Arkoala
}

/**
 * @tc.name: setOnPopupSelect
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.OnPopupSelectImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setOnPopupSelect, TestSize.Level1)
{
    OnAlphabetIndexerPopupSelectCallback func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static int32_t selectedIndex = ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE;
    EventsTracker::alphabetIndexerEventReceiver.onPopupSelect = [](Ark_Int32 nodeId, const Ark_Number value) {
        selectedIndex = Converter::Convert<int32_t>(value);
    };
    modifier_->setOnPopupSelect(node_, &func);
    EXPECT_EQ(selectedIndex, ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE);

    auto onPopupSelected = eventHub->GetOnPopupSelected();

    for (const auto& expected : SELECTED_INDEX_TEST_PLAN) {
        onPopupSelected(expected);
        EXPECT_EQ(selectedIndex, expected);
    }
}

/**
 * @tc.name: setSelected
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.SelectedImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setSelected, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelected, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTED);
    EXPECT_EQ(checkVal, ATTRIBUTE_SELECTED_DEFAULT_VALUE);

    for (const auto& [value, expectVal] : SELECTED_TEST_PLAN) {
        modifier_->setSelected(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTED);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupPosition
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupPositionImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupPositionX, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupPosition, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto posObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_POPUP_POSITION);
    auto checkValX = GetAttrValue<std::string>(posObject, PROP_NAME_POPUP_POSITION_X);
    EXPECT_EQ(checkValX, ATTRIBUTE_POPUP_POSITION_DEFAULT_VALUE);

    for (const auto &[value, expectVal] : POPUP_POSITION_TEST_PLAN) {
        const Ark_Position& position = {
            Converter::ArkValue<Opt_Length>(std::optional(value)),
            Converter::ArkValue<Opt_Length>(Ark_Empty())
        };
        modifier_->setPopupPosition(node_, &position);

        fullJson = GetJsonValue(node_);
        posObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_POPUP_POSITION);
        checkValX = GetAttrValue<std::string>(posObject, PROP_NAME_POPUP_POSITION_X);
        EXPECT_EQ(checkValX, expectVal);
    }
}

/**
 * @tc.name: setPopupPositionY
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupPositionImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupPositionY, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupPosition, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto posObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_POPUP_POSITION);
    auto checkValY = GetAttrValue<std::string>(posObject, PROP_NAME_POPUP_POSITION_Y);
    EXPECT_EQ(checkValY, ATTRIBUTE_POPUP_POSITION_DEFAULT_VALUE);

    for (const auto &[value, expectVal] : POPUP_POSITION_TEST_PLAN) {
        const Ark_Position& position = {
            Converter::ArkValue<Opt_Length>(Ark_Empty()),
            Converter::ArkValue<Opt_Length>(std::optional(value))
        };
        modifier_->setPopupPosition(node_, &position);

        fullJson = GetJsonValue(node_);
        posObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_POPUP_POSITION);
        checkValY = GetAttrValue<std::string>(posObject, PROP_NAME_POPUP_POSITION_Y);
        EXPECT_EQ(checkValY, expectVal);
    }
}

/**
 * @tc.name: setAutoCollapse
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.AutoCollapseImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setAutoCollapse, TestSize.Level1)
{
    static const std::string& DEFAULT_VALUE(ATTRIBUTE_AUTOCOLLAPSE_DEFAULT_VALUE);
    ASSERT_NE(modifier_->setAutoCollapse, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, PROP_NAME_AUTO_COLLAPSE);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    modifier_->setAutoCollapse(node_, true);
    auto checkVal2 = GetAttrValue<std::string>(node_, PROP_NAME_AUTO_COLLAPSE);
    EXPECT_EQ(checkVal2, EXPECTED_TRUE);

    modifier_->setAutoCollapse(node_, false);
    auto checkVal3 = GetAttrValue<std::string>(node_, PROP_NAME_AUTO_COLLAPSE);
    EXPECT_EQ(checkVal3, EXPECTED_FALSE);
}

/**
 * @tc.name: setPopupItemBorderRadius
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupItemBorderRadiusImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupItemBorderRadius, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupItemBorderRadius, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_ITEM_BORDER_RADIUS);
    EXPECT_EQ(checkVal, ATTRIBUTE_POPUP_ITEM_BORDER_RADIUS_DEFAULT_VALUE);

    for (const auto& [value, expectVal] : BORDER_RADIUS_TEST_PLAN) {
        modifier_->setPopupItemBorderRadius(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_ITEM_BORDER_RADIUS);
        EXPECT_EQ(checkVal, expectVal);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_BORDER_RADIUS);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setItemBorderRadius
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.ItemBorderRadiusImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setItemBorderRadius, TestSize.Level1)
{
    ASSERT_NE(modifier_->setItemBorderRadius, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, PROP_NAME_ITEM_BORDER_RADIUS);
    EXPECT_EQ(checkVal, ATTRIBUTE_ITEM_BORDER_RADIUS_DEFAULT_VALUE);

    for (const auto& [value, expectVal] : BORDER_RADIUS_TEST_PLAN) {
        modifier_->setItemBorderRadius(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_ITEM_BORDER_RADIUS);
        EXPECT_EQ(checkVal, expectVal);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_INDEXER_BORDER_RADIUS);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupBackgroundBlurStyle
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupBackgroundBlurStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupBackgroundBlurStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupBackgroundBlurStyle, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_BACKGROUND_BLUR_STYLE);
    EXPECT_EQ(checkVal, ATTRIBUTE_POPUP_BACKGROUND_BLUR_STYLE_DEFAULT_VALUE);

    for (const auto& [value, expectVal] : BLUR_STYLE_TEST_PLAN) {
        modifier_->setPopupBackgroundBlurStyle(node_, value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_BACKGROUND_BLUR_STYLE);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupTitleBackground
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupTitleBackgroundImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupTitleBackground, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupTitleBackground, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_TITLE_BACKGROUND);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_BLACK) {
        modifier_->setPopupTitleBackground(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_TITLE_BACKGROUND);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupTitleBackgroundRes
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.PopupTitleBackgroundImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupTitleBackgroundRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupTitleBackground, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_TITLE_BACKGROUND);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        modifier_->setPopupTitleBackground(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_TITLE_BACKGROUND);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setEnableHapticFeedback
 * @tc.desc: Check the functionality of AlphabetIndexerModifier.EnableHapticFeedbackImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setEnableHapticFeedback, TestSize.Level1)
{
    static const std::string& DEFAULT_VALUE(ATTRIBUTE_HAPTIC_FEEDBACK_DEFAULT_VALUE);
    ASSERT_NE(modifier_->setEnableHapticFeedback, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, PROP_NAME_HAPTIC_FEEDBACK);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    modifier_->setEnableHapticFeedback(node_, false);
    auto checkVal2 = GetAttrValue<std::string>(node_, PROP_NAME_HAPTIC_FEEDBACK);
    EXPECT_EQ(checkVal2, EXPECTED_FALSE);

    modifier_->setEnableHapticFeedback(node_, true);
    auto checkVal3 = GetAttrValue<std::string>(node_, PROP_NAME_HAPTIC_FEEDBACK);
    EXPECT_EQ(checkVal3, EXPECTED_TRUE);
}
} // namespace OHOS::Ace::NG
