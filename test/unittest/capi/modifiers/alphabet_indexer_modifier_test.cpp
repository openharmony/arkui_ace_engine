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
#include "core/components_ng/pattern/indexer/indexer_event_hub.h"
#include "core/interfaces/arkoala/utility/converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
struct EventsTracker {
    static inline GENERATED_ArkUIAlphabetIndexerEventsReceiver alphabetIndexerEventReceiver {};

    static inline const GENERATED_ArkUIEventsAPI eventsApiImpl {
        .getAlphabetIndexerEventsReceiver = []() -> const GENERATED_ArkUIAlphabetIndexerEventsReceiver* {
            return &alphabetIndexerEventReceiver;
        }
    };
}; // EventsTracker

inline Ark_Resource ArkRes(Ark_String* name, int id = -1,
    NodeModifier::ResourceType type = NodeModifier::ResourceType::COLOR, const char* module = "",
    const char* bundle = "")
{
    return { .id = { .tag = ARK_TAG_INT32, .i32 = static_cast<Ark_Int32>(id) },
        .type = { .tag = ARK_TAG_INT32, .i32 = static_cast<Ark_Int32>(type) },
        .moduleName = { .chars = module },
        .bundleName = { .chars = bundle },
        .params = { .tag = ARK_TAG_OBJECT, .value = { .array = name, .length = name ? 1 : 0 } } };
}
} // namespace

// Prop names
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
const auto PROP_NAME_FONT = "font";
const auto PROP_NAME_FONT_SIZE = "fontSize";
const auto PROP_NAME_FONT_WEIGHT = "fontWeight";
const auto PROP_NAME_FONT_STYLE = "fontStyle";
const auto PROP_NAME_FONT_FAMILY = "fontFamily";
const auto PROP_NAME_AUTO_COLLAPSE = "autoCollapse";
const auto PROP_NAME_HAPTIC_FEEDBACK = "enableHapticFeedback";

// Default values
const auto ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE = 0;
const auto ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE = "#FFFFFFFF";
const auto ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK = "#FF000000";
const auto ATTRIBUTE_USING_POPUP_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_AUTOCOLLAPSE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_HAPTIC_FEEDBACK_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_FONT_DEFAULT_SIZE = "14.00px";

// Expected values
static const std::string EXPECTED_TRUE("true");
static const std::string EXPECTED_FALSE("false");

// Test plans
static const std::vector<int32_t> SELECTED_INDEX_TEST_PLAN = { 1, 10, 32, -1, -35, 832 };

const std::string COLOR_RED = "#FFFF0000";
const std::string COLOR_BLACK = "#FF000000";
const std::string COLOR_TRANSPARENT = "#00000000";
const Ark_String COLOR_NAME = Converter::ArkValue<Ark_String>("color_name");
typedef std::tuple<Ark_ResourceColor, std::string> ColorTestStep;
const std::vector<ColorTestStep> COLOR_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"), COLOR_BLACK },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), COLOR_TRANSPARENT }
};
const std::vector<ColorTestStep> COLOR_TEST_PLAN_RES = {
    { Converter::ArkUnion<Ark_ResourceColor, struct Ark_Resource>(ArkRes(const_cast<Ark_String*>(&COLOR_NAME))),
        COLOR_RED }, // Color::RED is result of mocked ThemeConstants::GetColorByName
    { Converter::ArkUnion<Ark_ResourceColor, struct Ark_Resource>(ArkRes(nullptr, 1234)),
        COLOR_RED }, // Color::RED is result of mocked ThemeConstants::GetColor(int)
    { Converter::ArkUnion<Ark_ResourceColor, struct Ark_Resource>(
        ArkRes(const_cast<Ark_String*>(&COLOR_NAME), 2, NodeModifier::ResourceType::STRING)),
        COLOR_BLACK } // Should be Color::RED, but converter from Resource works incorrect now.
                      // So modifier pass Color::BLACK to component in this case
};

const Ark_Int32 AINT32_POS(70);
const Ark_Int32 AINT32_NEG(INT_MIN);
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);
const auto CHECK_AINT32_POS = "70.00px";
const auto CHECK_AFLT32_POS = "1.23vp";

const auto RES_CONTENT = Converter::ArkValue<Ark_String>("aa.bb.cc");
const auto RES_NAME = Converter::ArkValue<Ark_String>("res_name");
const Opt_Union_String_Resource OPT_UNION_RESOURCE_RESOURCE =
    Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        ArkRes(const_cast<Ark_String*>(&RES_NAME), 1234, NodeModifier::ResourceType::STRING));
const std::string CHECK_RESOURCE_STR("aa.bb.cc");

typedef std::pair<Opt_Union_String_Resource, std::string> UnionStringResourceTestStep;
const std::vector<UnionStringResourceTestStep> UNION_RESOURCE_STRING_PLAN = {
    { Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(RES_CONTENT), CHECK_RESOURCE_STR },
    { OPT_UNION_RESOURCE_RESOURCE, CHECK_RESOURCE_STR }
};

typedef std::pair<Opt_Length, std::string> OptLengthTestStep;
const std::vector<OptLengthTestStep> OPT_LENGTH_TEST_PLAN = {
    { Converter::ArkValue<Opt_Length>(AINT32_POS), CHECK_AINT32_POS },
    { Converter::ArkValue<Opt_Length>(AINT32_NEG), ATTRIBUTE_FONT_DEFAULT_SIZE },
    { Converter::ArkValue<Opt_Length>(AFLT32_NEG), ATTRIBUTE_FONT_DEFAULT_SIZE },
    { Converter::ArkValue<Opt_Length>(AFLT32_POS), CHECK_AFLT32_POS } };

typedef std::pair<Opt_FontStyle, std::string> ArkFontStyleTestStep;
const std::vector<ArkFontStyleTestStep> FONT_STYLE_TEST_PLAN = {
    { { .tag = ARK_TAG_OBJECT, .value = ARK_FONT_STYLE_NORMAL }, "FontStyle.Normal" },
    { { .tag = ARK_TAG_OBJECT, .value = ARK_FONT_STYLE_ITALIC }, "FontStyle.Italic" },
    { { .tag = ARK_TAG_OBJECT, .value = static_cast<Ark_FontStyle>(2) }, "FontStyle.Normal" },
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
 * @tc.name: setOnSelected
 * @tc.desc: Check the functionality of AlphabetIndexer.OnSelectedImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setOnSelected, TestSize.Level1)
{
    Ark_Function func = {};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static int32_t selectedIndex = ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE;
    EventsTracker::alphabetIndexerEventReceiver.onSelected = [](Ark_Int32 nodeId, const Ark_Number value) {
        selectedIndex = Converter::Convert<int32_t>(value);
    };
    modifier_->setOnSelected(node_, func);
    EXPECT_EQ(selectedIndex, ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE);

    auto onSelect = eventHub->GetOnSelected();

    for (const auto& expected : SELECTED_INDEX_TEST_PLAN) {
        onSelect(expected);
        EXPECT_EQ(selectedIndex, expected);
    }
}

/**
 * @tc.name: setColor
 * @tc.desc: Check the functionality of AlphabetIndexer.ColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);
    
    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setColorRes
 * @tc.desc: Check the functionality of AlphabetIndexer.ColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setColorRes, TestSize.Level1)
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
 * @tc.desc: Check the functionality of AlphabetIndexer.SelectedColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setSelectedColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_SELECTED_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);
    
    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setSelectedColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTED_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setSelectedColorRes
 * @tc.desc: Check the functionality of AlphabetIndexer.SelectedColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setSelectedColorRes, TestSize.Level1)
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
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);
    
    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setPopupColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}
/**
 * @tc.name: setPopupColorRes
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setPopupColorRes, TestSize.Level1)
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
 * @tc.desc: Check the functionality of AlphabetIndexer.SelectedBackgroundColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setSelectedBackgroundColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedBackgroundColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_SELECTED_BACKGROUND_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);
    
    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setSelectedBackgroundColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTED_BACKGROUND_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setSelectedBackgroundColorRes
 * @tc.desc: Check the functionality of AlphabetIndexer.SelectedBackgroundColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setSelectedBackgroundColorRes, TestSize.Level1)
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
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupBackgroundImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupBackground, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupBackground, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_BACKGROUND);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_WHITE);
    
    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setPopupBackground(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_BACKGROUND);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupBackgroundRes
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupBackgroundImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setPopupBackgroundRes, TestSize.Level1)
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
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupSelectedColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupSelectedColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupSelectedColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_SELECTED_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK);
    
    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setPopupSelectedColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_SELECTED_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupSelectedColorRes
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupSelectedColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setPopupSelectedColorRes, TestSize.Level1)
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
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupUnselectedColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupUnselectedColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupUnselectedColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_UNSELECTED_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK);
    
    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setPopupUnselectedColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_UNSELECTED_COLOR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupUnselectedColorRes
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupUnselectedColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setPopupUnselectedColorRes, TestSize.Level1)
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
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupItemBackgroundColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupItemBackgroundColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupItemBackgroundColor, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME_POPUP_ITEM_BACKGROUND);
    EXPECT_EQ(checkVal, ATTRIBUTE_COLOR_DEFAULT_VALUE_BLACK);
    
    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setPopupItemBackgroundColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_POPUP_ITEM_BACKGROUND);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPopupItemBackgroundColorRes
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupItemBackgroundColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setPopupItemBackgroundColorRes, TestSize.Level1)
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
 * @tc.desc: Check the functionality of AlphabetIndexer.UsingPopupImpl
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
 * @tc.desc: Check the functionality of AlphabetIndexer.SelectedFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setSelectedFontTest1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
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
 * @tc.desc: Check the functionality of AlphabetIndexer.SelectedFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setSelectedFontTest2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
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
 * @tc.desc: Check the functionality of AlphabetIndexer.SelectedFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setSelectedFontTest3, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
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
 * @tc.desc: Check the functionality of AlphabetIndexer.SelectedFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setSelectedFontTest4, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto size : OPT_LENGTH_TEST_PLAN) {
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
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupFontTest1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
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
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupFontTest2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
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
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setPopupFontTest3, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
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
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupFontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupFontTest4, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto size : OPT_LENGTH_TEST_PLAN) {
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
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupItemFont
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupItemFont1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupItemFont, nullptr);
    Ark_Font font = {
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;

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
 * @tc.desc: Check the functionality of AlphabetIndexer.PopupItemFont
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setPopupItemFont2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPopupItemFont, nullptr);
    Ark_Font font = {
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto size : OPT_LENGTH_TEST_PLAN) {
        font.size = size.first;
        modifier_->setPopupItemFont(node_, &font);
        auto checkSize = GetStringAttribute(node_, PROP_NAME_POPUP_ITEM_FONT_SIZE);
        auto checkWeight = GetStringAttribute(node_, PROP_NAME_POPUP_ITEM_FONT_WEIGHT);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setFontTest1
 * @tc.desc: Check the functionality of AlphabetIndexer.FontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setFontTest1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
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
 * @tc.desc: Check the functionality of AlphabetIndexer.FontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setFontTest2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
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
 * @tc.desc: Check the functionality of AlphabetIndexer.FontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, DISABLED_setFontTest3, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
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
 * @tc.desc: Check the functionality of AlphabetIndexer.FontImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModifierTest, setFontTest4, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto size : OPT_LENGTH_TEST_PLAN) {
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
 * @tc.name: setAutoCollapse
 * @tc.desc: Check the functionality of AlphabetIndexer.AutoCollapseImpl
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
 * @tc.name: setEnableHapticFeedback
 * @tc.desc: Check the functionality of AlphabetIndexer.EnableHapticFeedbackImpl
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