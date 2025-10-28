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
#include "generated/test_fixtures.h"
#include "generated/type_helpers.h"

#include "core/interfaces/native/implementation/text_controller_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/text/text_event_hub.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using namespace TypeHelper;
using namespace Converter;

namespace {
const std::string FONT_COLOR_ATTR = "fontColor";
const std::string FONT_SIZE_ATTR = "fontSize";
const std::string FONT_STYLE_ATTR = "fontStyle";
const std::string FONT_FAMILY_ATTR = "fontFamily";
const std::string FONT_WEIGHT_ATTR = "fontWeight";

const std::string TEXT_ALIGN_ATTR = "textAlign";
const std::string TEXT_OVERFLOW_ATTR = "textOverflow";
const std::string TEXT_CASE_ATTR = "textCase";

const std::string LINE_HEIGHT_ATTR = "lineHeight";
const std::string MIN_FONT_SIZE_ATTR = "minFontSize";
const std::string MAX_FONT_SIZE_ATTR = "maxFontSize";
const std::string MIN_FONT_SCALE_ATTR = "minFontScale";
const std::string MAX_FONT_SCALE_ATTR = "maxFontScale";
const std::string MAX_LINES_ATTR = "maxLines";

const std::string DECORATION_ATTR = "decoration";
const std::string LETTER_SPACING_ATTR = "letterSpacing";
const std::string BASELINE_OFFSET_ATTR = "baselineOffset";
const std::string COPY_OPTIONS_ATTR = "copyOption";
const std::string DRAGGABLE_ATTR = "draggable";
const std::string TEXT_SHADOW_ATTR = "textShadow";
const std::string HEIGHT_ADAPTIVE_POLICY_ATTR = "heightAdaptivePolicy";
const std::string TEXT_INDENT_ATTR = "textIndent";
const std::string WORD_BREAK_ATTR = "wordBreak";
const std::string LINE_BREAK_STRATEGY_ATTR = "lineBreakStrategy";
const std::string ELLIPSIS_MODE_ATTR = "ellipsisMode";
const std::string TEXT_SELECTABLE_ATTR = "textSelectable";
const auto RES_NAME = NamedResourceId("aa.bb.cc", ResourceType::COLOR);
const auto RES_NAME1 = NamedResourceId("aa.bb.cc", ResourceType::FLOAT);

const auto CONTEXT_ID = 123;
static constexpr int TEST_RESOURCE_ID = 1000;
const uint32_t FLOAT_RES_0_ID = 1001;
const uint32_t FLOAT_RES_1_ID = 1002;
const uint32_t FLOAT_RES_2_ID = 1003;

const double FLOAT_RES_0_VALUE = 0.705f;
const Ark_Resource FLOAT_RES_0 = CreateResource(FLOAT_RES_0_ID, ResourceType::FLOAT);

const double FLOAT_RES_1_VALUE = 5.2f;
const Ark_Resource FLOAT_RES_1 = CreateResource(FLOAT_RES_1_ID, ResourceType::FLOAT);

const float FLOAT_RES_2_VALUE = 10.f;
const auto FLOAT_RES_2_STORED_VALUE = Dimension(FLOAT_RES_2_VALUE, DimensionUnit::PX);
const Ark_Resource FLOAT_RES_2 = CreateResource(FLOAT_RES_2_ID, ResourceType::FLOAT);

const auto FONT_SIZE_ATTR_DEFAULT_VALUE = "14.00px";
const auto TEXT_OVERFLOW_ATTR_DEFAULT_VALUE = "TextOverflow.Clip";

const auto ATTRIBUTE_FONT_NAME = "font";
const auto ATTRIBUTE_FONT_WEIGHT_NAME = "fontWeight";
const auto ATTRIBUTE_VARIABLE_FONT_WEIGHT_NAME = "variableFontWeight";
const auto ATTRIBUTE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE = "400";
const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_NAME = "enableVariableFontWeight";
const auto ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_TEXT_SHADOW_NAME = "textShadow";
const auto ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME = "radius";
const auto ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME = "type";
const auto ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME = "color";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME = "offsetX";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME = "offsetY";
const auto ATTRIBUTE_CONTENT_NAME = "content";
const auto ATTRIBUTE_CONTENT_DEFAULT_VALUE = "";
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_NAME = "dataDetectorConfig";
const auto ATTRIBUTE_MARQUEE_OPTIONS_NAME = "marqueeOptions";
const auto ATTRIBUTE_MARQUEE_OPTIONS_I_MARQUEE_START_POLICY_NAME = "startPolicy";
const auto ATTRIBUTE_MARQUEE_OPTIONS_I_MARQUEE_START_POLICY_DEFAULT_VALUE = "MarqueeStartPolicy.DEFAULT";

static constexpr int32_t NODE_ID = 555;
static bool g_isCalled = false;
struct CheckCBEvent {
    int32_t resourceId;
    Ark_NativePointer parentNode;
};
static std::optional<CheckCBEvent> checkCBEvent = std::nullopt;
static std::optional<RefPtr<UINode>> uiNode = std::nullopt;

struct SelectionRange {
    int32_t start;
    int32_t end;
};
} // namespace

class TextModifierTest : public ModifierTestBase<GENERATED_ArkUITextModifier,
    &GENERATED_ArkUINodeModifiers::getTextModifier, GENERATED_ARKUI_TEXT> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<TextTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }

        AddResource(FLOAT_RES_0_ID, FLOAT_RES_0_VALUE);
        AddResource(FLOAT_RES_1_ID, FLOAT_RES_1_VALUE);
        AddResource(FLOAT_RES_2_ID, FLOAT_RES_2_STORED_VALUE);
    }
    Opt_CustomNodeBuilder getBuilderCb()
    {
        auto checkCallback = [](
            const Ark_Int32 resourceId,
            const Ark_NativePointer parentNode,
            const Callback_Pointer_Void continuation) {
            checkCBEvent = {
                .resourceId = resourceId,
                .parentNode = parentNode
            };
            if (uiNode) {
                CallbackHelper(continuation).InvokeSync(AceType::RawPtr(uiNode.value()));
            }
        };
        return Converter::ArkCallback<Opt_CustomNodeBuilder>(checkCallback, TEST_RESOURCE_ID);
    }
};

namespace {
std::vector<std::tuple<std::string, Ark_Int32, std::string>> testFixtureVariableFontWeightNumbersValidValues = {
    { "100", Converter::ArkValue<Ark_Int32>(100), "100" },
    { "200", Converter::ArkValue<Ark_Int32>(200), "200" },
    { "300", Converter::ArkValue<Ark_Int32>(300), "300" },
    { "400", Converter::ArkValue<Ark_Int32>(400), "400" },
    { "500", Converter::ArkValue<Ark_Int32>(500), "500" },
    { "600", Converter::ArkValue<Ark_Int32>(600), "600" },
    { "700", Converter::ArkValue<Ark_Int32>(700), "700" },
    { "800", Converter::ArkValue<Ark_Int32>(800), "800" },
    { "900", Converter::ArkValue<Ark_Int32>(900), "900" },
    { "840", Converter::ArkValue<Ark_Int32>(840), "840" },
    { "860", Converter::ArkValue<Ark_Int32>(860), "860" },
};

std::vector<std::tuple<std::string, Ark_Int32, std::string>> testFixtureFontWeightNumbersValidValues = {
    { "100", Converter::ArkValue<Ark_Int32>(100), "100" },
    { "200", Converter::ArkValue<Ark_Int32>(200), "200" },
    { "300", Converter::ArkValue<Ark_Int32>(300), "300" },
    { "400", Converter::ArkValue<Ark_Int32>(400), "400" },
    { "500", Converter::ArkValue<Ark_Int32>(500), "500" },
    { "600", Converter::ArkValue<Ark_Int32>(600), "600" },
    { "700", Converter::ArkValue<Ark_Int32>(700), "700" },
    { "800", Converter::ArkValue<Ark_Int32>(800), "800" },
    { "900", Converter::ArkValue<Ark_Int32>(900), "900" },
};

std::vector<std::tuple<std::string, Ark_Int32>> testFixtureFontWeightNumbersInvalidValues = {
    { "0", Converter::ArkValue<Ark_Int32>(0) },
    { "1000", Converter::ArkValue<Ark_Int32>(1000) },
    { "-100", Converter::ArkValue<Ark_Int32>(-100) },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureVariableFontWeightStringsInvalidValues = {
    { "\"0\"", Converter::ArkValue<Ark_String>("0") },
    { "\"1000\"", Converter::ArkValue<Ark_String>("1000") },
    { "\"-100\"", Converter::ArkValue<Ark_String>("-100") },
    { "xxx", Converter::ArkValue<Ark_String>("xxx") },
    { "10x", Converter::ArkValue<Ark_String>("10x") },
    { "x10", Converter::ArkValue<Ark_String>("x10") },
    { "40000000000000", Converter::ArkValue<Ark_String>("40000000000000") },
    { "Bold", Converter::ArkValue<Ark_String>("Bold") },
    { "Bolder", Converter::ArkValue<Ark_String>("Bolder") },
    { "Lighter", Converter::ArkValue<Ark_String>("Lighter") },
    { "Normal", Converter::ArkValue<Ark_String>("Normal") },
    { "Medium", Converter::ArkValue<Ark_String>("Medium") },
    { "Regular", Converter::ArkValue<Ark_String>("Regular") },
};

std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureVariableFontWeightStringsValidValues = {
    { "\"100\"", Converter::ArkValue<Ark_String>("100"), "100" },
    { "\"200\"", Converter::ArkValue<Ark_String>("200"), "200" },
    { "\"300\"", Converter::ArkValue<Ark_String>("300"), "300" },
    { "\"400\"", Converter::ArkValue<Ark_String>("400"), "400" },
    { "\"500\"", Converter::ArkValue<Ark_String>("500"), "500" },
    { "\"600\"", Converter::ArkValue<Ark_String>("600"), "600" },
    { "\"700\"", Converter::ArkValue<Ark_String>("700"), "700" },
    { "\"800\"", Converter::ArkValue<Ark_String>("800"), "800" },
    { "\"900\"", Converter::ArkValue<Ark_String>("900"), "900" },
    { "\"840\"", Converter::ArkValue<Ark_String>("840"), "840" },
    { "\"860\"", Converter::ArkValue<Ark_String>("860"), "860" },
    { "bold", Converter::ArkValue<Ark_String>("bold"), "700" },
    { "bolder", Converter::ArkValue<Ark_String>("bolder"), "900" },
    { "lighter", Converter::ArkValue<Ark_String>("lighter"), "100" },
    { "normal", Converter::ArkValue<Ark_String>("normal"), "400" },
    { "medium", Converter::ArkValue<Ark_String>("medium"), "500" },
    { "regular", Converter::ArkValue<Ark_String>("regular"), "400" },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureTextMarqueeStepValidValues = {
    { "100", Converter::ArkValue<Ark_Float64>(100.), "100.00" },
    { "12.34", Converter::ArkValue<Ark_Float64>(12.34), "12.34" },
    { "1", Converter::ArkValue<Ark_Float64>(1.), "1.00" },
    { "0.09", Converter::ArkValue<Ark_Float64>(0.09), "0.09" },
};

std::vector<std::tuple<std::string, Ark_Int32, std::string>> testFixtureTextMarqueeLoopValidValues = {
    { "100", Converter::ArkValue<Ark_Int32>(100), "100" },
    { "7", Converter::ArkValue<Ark_Int32>(7), "7" },
    { "0", Converter::ArkValue<Ark_Int32>(0), "-1" },
    { "-100", Converter::ArkValue<Ark_Int32>(-100), "-1" },
};

std::vector<std::tuple<std::string, Ark_Int32, std::string>> testFixtureNumberNonNegIntFloorValidValues = {
    { "100", Converter::ArkValue<Ark_Int32>(100), "100" },
    { "0", Converter::ArkValue<Ark_Int32>(0), "0" },
    { "1", Converter::ArkValue<Ark_Int32>(1), "1" },
};
} //namespace

HWTEST_F(TextModifierTest, setFontColor, TestSize.Level1)
{
    const auto color1 = Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_GREEN);
    modifier_->setFontColor(node_, &color1);
    auto checkVal1 = GetStringAttribute(node_, FONT_COLOR_ATTR);
    EXPECT_EQ(checkVal1, "#FF008000");

    auto resNameColor = CreateResourceUnion<Opt_ResourceColor>(RES_NAME);
    modifier_->setFontColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, FONT_COLOR_ATTR);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName
}

HWTEST_F(TextModifierTest, setFontSize, TestSize.Level1)
{
    auto checkVal0 = GetStringAttribute(node_, FONT_SIZE_ATTR);
    EXPECT_EQ(checkVal0, FONT_SIZE_ATTR_DEFAULT_VALUE);

    const auto size1 = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(10.);
    modifier_->setFontSize(node_, &size1);
    auto checkVal1 = GetStringAttribute(node_, FONT_SIZE_ATTR);
    EXPECT_EQ(checkVal1, "10.00fp");

    const auto size2 = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("20.00vp");
    modifier_->setFontSize(node_, &size2);
    auto checkVal2 = GetStringAttribute(node_, FONT_SIZE_ATTR);
    EXPECT_EQ(checkVal2, "20.00vp");

    auto size3 = CreateResourceUnion<Opt_Union_F64_String_Resource>(RES_NAME);
    modifier_->setFontSize(node_, &size3);
    auto checkVal3 = GetStringAttribute(node_, FONT_SIZE_ATTR);
    EXPECT_EQ(checkVal3, FONT_SIZE_ATTR_DEFAULT_VALUE);
}

HWTEST_F(TextModifierTest, setMinFontSize, TestSize.Level1)
{
    const auto size1 = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(11.25);
    modifier_->setMinFontSize(node_, &size1);
    auto checkVal1 = GetStringAttribute(node_, MIN_FONT_SIZE_ATTR);
    EXPECT_EQ(checkVal1, "11.25fp");

    const auto size2 = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("11.25px");
    modifier_->setMinFontSize(node_, &size2);
    auto checkVal2 = GetStringAttribute(node_, MIN_FONT_SIZE_ATTR);
    EXPECT_EQ(checkVal2, "11.25px");

    auto size3 = CreateResourceUnion<Opt_Union_F64_String_Resource>(RES_NAME1);
    modifier_->setMinFontSize(node_, &size3);
    auto checkVal3 = GetStringAttribute(node_, MIN_FONT_SIZE_ATTR);
    EXPECT_EQ(checkVal3, "10.00px");
}

HWTEST_F(TextModifierTest, setMaxFontSize, TestSize.Level1)
{
    const auto size1 = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(11.25);
    modifier_->setMaxFontSize(node_, &size1);
    auto checkVal1 = GetStringAttribute(node_, MAX_FONT_SIZE_ATTR);
    EXPECT_EQ(checkVal1, "11.25fp");

    const auto size2 = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("11.25px");
    modifier_->setMaxFontSize(node_, &size2);
    auto checkVal2 = GetStringAttribute(node_, MAX_FONT_SIZE_ATTR);
    EXPECT_EQ(checkVal2, "11.25px");

    auto size3 = CreateResourceUnion<Opt_Union_F64_String_Resource>(RES_NAME1);
    modifier_->setMaxFontSize(node_, &size3);
    auto checkVal3 = GetStringAttribute(node_, MAX_FONT_SIZE_ATTR);
    EXPECT_EQ(checkVal3, "10.00px");
}

HWTEST_F(TextModifierTest, setMinFontScale, TestSize.Level1)
{
    const auto scale1 = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(0.825);
    modifier_->setMinFontScale(node_, &scale1);
    auto checkVal1 = GetStringAttribute(node_, MIN_FONT_SCALE_ATTR);
    EXPECT_EQ(checkVal1, "0.825000");

    const auto scale2 = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(FLOAT_RES_0);
    modifier_->setMinFontScale(node_, &scale2);
    auto checkVal2 = GetStringAttribute(node_, MIN_FONT_SCALE_ATTR);
    EXPECT_EQ(checkVal2, "0.705000");
}

HWTEST_F(TextModifierTest, setMaxFontScale, TestSize.Level1)
{
    const auto scale1 = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(1.25);
    modifier_->setMaxFontScale(node_, &scale1);
    auto checkVal1 = GetStringAttribute(node_, MAX_FONT_SCALE_ATTR);
    EXPECT_EQ(checkVal1, "1.250000");

    const auto scale2 = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(FLOAT_RES_1);
    modifier_->setMaxFontScale(node_, &scale2);
    auto checkVal2 = GetStringAttribute(node_, MAX_FONT_SCALE_ATTR);
    EXPECT_EQ(checkVal2, "5.200000");
}

HWTEST_F(TextModifierTest, setFontStyle, TestSize.Level1)
{
    auto inputVal = Converter::ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_NORMAL);
    modifier_->setFontStyle(node_, &inputVal);
    auto checkVal1 = GetStringAttribute(node_, FONT_STYLE_ATTR);
    EXPECT_EQ(checkVal1, "FontStyle.Normal");

    inputVal = Converter::ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_ITALIC);
    modifier_->setFontStyle(node_, &inputVal);
    auto checkVal2 = GetStringAttribute(node_, FONT_STYLE_ATTR);
    EXPECT_EQ(checkVal2, "FontStyle.Italic");
}

HWTEST_F(TextModifierTest, setFontWeight, TestSize.Level1)
{
    const auto w1 = Converter::ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(100);
    modifier_->setFontWeight(node_, &w1, nullptr);
    auto checkVal1 = GetStringAttribute(node_, FONT_WEIGHT_ATTR);
    EXPECT_EQ(checkVal1, "100");

    const auto w2 = Converter::ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(ARK_FONT_WEIGHT_MEDIUM);
    modifier_->setFontWeight(node_, &w2, nullptr);
    auto checkVal2 = GetStringAttribute(node_, FONT_WEIGHT_ATTR);
    EXPECT_EQ(checkVal2, "FontWeight.Medium");

    const auto w3 = Converter::ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("normal");
    modifier_->setFontWeight(node_, &w3, nullptr);
    auto checkVal3 = GetStringAttribute(node_, FONT_WEIGHT_ATTR);
    EXPECT_EQ(checkVal3, "FontWeight.Normal");
}

HWTEST_F(TextModifierTest, setTextAlign, TestSize.Level1)
{
    auto inputVal = Converter::ArkValue<Opt_TextAlign>(ARK_TEXT_ALIGN_START);
    modifier_->setTextAlign(node_, &inputVal);
    auto checkVal1 = GetStringAttribute(node_, TEXT_ALIGN_ATTR);
    EXPECT_EQ(checkVal1, "TextAlign.Start");

    inputVal = Converter::ArkValue<Opt_TextAlign>(ARK_TEXT_ALIGN_CENTER);
    modifier_->setTextAlign(node_, &inputVal);
    auto checkVal2 = GetStringAttribute(node_, TEXT_ALIGN_ATTR);
    EXPECT_EQ(checkVal2, "TextAlign.Center");

    inputVal = Converter::ArkValue<Opt_TextAlign>(ARK_TEXT_ALIGN_END);
    modifier_->setTextAlign(node_, &inputVal);
    auto checkVal3 = GetStringAttribute(node_, TEXT_ALIGN_ATTR);
    EXPECT_EQ(checkVal3, "TextAlign.End");

    inputVal = Converter::ArkValue<Opt_TextAlign>(ARK_TEXT_ALIGN_JUSTIFY);
    modifier_->setTextAlign(node_, &inputVal);
    auto checkVal4 = GetStringAttribute(node_, TEXT_ALIGN_ATTR);
    EXPECT_EQ(checkVal4, "TextAlign.Justify");
}

HWTEST_F(TextModifierTest, setLineHeight, TestSize.Level1)
{
    const auto size1 = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(11.);
    modifier_->setLineHeight(node_, &size1);
    auto checkVal1 = GetStringAttribute(node_, LINE_HEIGHT_ATTR);
    EXPECT_EQ(checkVal1, "11.00fp");

    const auto size2 = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("12.00vp");
    modifier_->setLineHeight(node_, &size2);
    auto checkVal2 = GetStringAttribute(node_, LINE_HEIGHT_ATTR);
    EXPECT_EQ(checkVal2, "12.00vp");

    const auto size3 = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_Resource>(FLOAT_RES_2);
    modifier_->setLineHeight(node_, &size3);
    auto checkVal3 = GetStringAttribute(node_, LINE_HEIGHT_ATTR);
    EXPECT_EQ(checkVal3, "10.00px");
}

HWTEST_F(TextModifierTest, setTextOverflow, TestSize.Level1)
{
    Ark_TextOverflowOptions v1 = { .overflow = Converter::ArkValue<Opt_TextOverflow>(ARK_TEXT_OVERFLOW_NONE) };
    auto inputVal = Converter::ArkValue<Opt_TextOverflowOptions>(v1);
    modifier_->setTextOverflow(node_, &inputVal);
    auto checkVal1 = GetStringAttribute(node_, TEXT_OVERFLOW_ATTR);
    EXPECT_EQ(checkVal1, "TextOverflow.None");

    Ark_TextOverflowOptions v2 = { .overflow = Converter::ArkValue<Opt_TextOverflow>(ARK_TEXT_OVERFLOW_CLIP) };
    inputVal = Converter::ArkValue<Opt_TextOverflowOptions>(v2);
    modifier_->setTextOverflow(node_, &inputVal);
    auto checkVal2 = GetStringAttribute(node_, TEXT_OVERFLOW_ATTR);
    EXPECT_EQ(checkVal2, "TextOverflow.Clip");

    Ark_TextOverflowOptions v3 = { .overflow = Converter::ArkValue<Opt_TextOverflow>(ARK_TEXT_OVERFLOW_ELLIPSIS) };
    inputVal = Converter::ArkValue<Opt_TextOverflowOptions>(v3);
    modifier_->setTextOverflow(node_, &inputVal);
    auto checkVal3 = GetStringAttribute(node_, TEXT_OVERFLOW_ATTR);
    EXPECT_EQ(checkVal3, "TextOverflow.Ellipsis");

    Ark_TextOverflowOptions v4 = { .overflow = Converter::ArkValue<Opt_TextOverflow>(ARK_TEXT_OVERFLOW_MARQUEE) };
    inputVal = Converter::ArkValue<Opt_TextOverflowOptions>(v4);
    modifier_->setTextOverflow(node_, &inputVal);
    auto checkVal4 = GetStringAttribute(node_, TEXT_OVERFLOW_ATTR);
    EXPECT_EQ(checkVal4, "TextOverflow.Marquee");
}

HWTEST_F(TextModifierTest, setTextOverflowTestDefaultValue, TestSize.Level1)
{
    auto checkVal1 = GetStringAttribute(node_, TEXT_OVERFLOW_ATTR);
    EXPECT_EQ(checkVal1, TEXT_OVERFLOW_ATTR_DEFAULT_VALUE);
}

HWTEST_F(TextModifierTest, setTextOverflowTestInvalidValue, TestSize.Level1)
{
    Ark_TextOverflowOptions v1 = { .overflow = Converter::ArkValue<Opt_TextOverflow>(ARK_TEXT_OVERFLOW_NONE) };
    auto inputVal = Converter::ArkValue<Opt_TextOverflowOptions>(v1);
    modifier_->setTextOverflow(node_, &inputVal);
    Ark_TextOverflowOptions invalidValue = {
        .overflow = Converter::ArkValue<Opt_TextOverflow>(static_cast<Ark_TextOverflow>(-1)),
    };
    inputVal = Converter::ArkValue<Opt_TextOverflowOptions>(invalidValue);
    modifier_->setTextOverflow(node_, &inputVal);
    auto checkVal1 = GetStringAttribute(node_, TEXT_OVERFLOW_ATTR);
    EXPECT_EQ(checkVal1, TEXT_OVERFLOW_ATTR_DEFAULT_VALUE);
}

HWTEST_F(TextModifierTest, setFontFamily, TestSize.Level1)
{
    auto v1 = Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>("testFontFamily");
    modifier_->setFontFamily(node_, &v1);
    auto checkVal1 = GetStringAttribute(node_, FONT_FAMILY_ATTR);
    EXPECT_EQ(checkVal1, "testFontFamily");
}

HWTEST_F(TextModifierTest, setMaxLines, TestSize.Level1)
{
    auto v1 = Converter::ArkValue<Opt_Int32>(10);
    modifier_->setMaxLines(node_, &v1);
    auto checkVal1 = GetStringAttribute(node_, MAX_LINES_ATTR);
    EXPECT_EQ(checkVal1, "10");
}

HWTEST_F(TextModifierTest, setDecoration, TestSize.Level1)
{
    Ark_DecorationStyleInterface v1 = {
        .type = Converter::ArkValue<Opt_TextDecorationType>(ARK_TEXT_DECORATION_TYPE_UNDERLINE),
        .style = Converter::ArkValue<Opt_TextDecorationStyle>(ARK_TEXT_DECORATION_STYLE_DASHED),
        .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_GREEN),
    };
    auto inputVal = Converter::ArkValue<Opt_DecorationStyleInterface>(v1);
    modifier_->setDecoration(node_, &inputVal);
    auto checkVal1 = GetStringAttribute(node_, DECORATION_ATTR);
    EXPECT_EQ(checkVal1,
        "{\"type\":\"TextDecorationType.Underline\",\"color\":\"#FF008000\",\"style\":\"TextDecorationStyle.DASHED\"}");
}

HWTEST_F(TextModifierTest, setLetterSpacing, TestSize.Level1)
{
    auto v1 = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(11.25);
    modifier_->setLetterSpacing(node_, &v1);
    auto checkVal1 = GetStringAttribute(node_, LETTER_SPACING_ATTR);
    EXPECT_EQ(checkVal1, "11.25fp");

    auto v2 = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("12.25vp");
    modifier_->setLetterSpacing(node_, &v2);
    auto checkVal2 = GetStringAttribute(node_, LETTER_SPACING_ATTR);
    EXPECT_EQ(checkVal2, "12.25vp");
}

HWTEST_F(TextModifierTest, setTextCase, TestSize.Level1)
{
    auto inputVal = Converter::ArkValue<Opt_TextCase>(ARK_TEXT_CASE_NORMAL);
    modifier_->setTextCase(node_, &inputVal);
    auto checkVal1 = GetStringAttribute(node_, TEXT_CASE_ATTR);
    EXPECT_EQ(checkVal1, "TextCase.Normal");

    inputVal = Converter::ArkValue<Opt_TextCase>(ARK_TEXT_CASE_LOWER_CASE);
    modifier_->setTextCase(node_, &inputVal);
    auto checkVal2 = GetStringAttribute(node_, TEXT_CASE_ATTR);
    EXPECT_EQ(checkVal2, "TextCase.LowerCase");

    inputVal = Converter::ArkValue<Opt_TextCase>(ARK_TEXT_CASE_UPPER_CASE);
    modifier_->setTextCase(node_, &inputVal);
    auto checkVal3 = GetStringAttribute(node_, TEXT_CASE_ATTR);
    EXPECT_EQ(checkVal3, "TextCase.UpperCase");
}

HWTEST_F(TextModifierTest, setBaselineOffset, TestSize.Level1)
{
    auto v1 = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(11.);
    modifier_->setBaselineOffset(node_, &v1);
    auto checkVal1 = GetStringAttribute(node_, BASELINE_OFFSET_ATTR);
    EXPECT_EQ(checkVal1, "11");

    auto v2 = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("12");
    modifier_->setBaselineOffset(node_, &v2);
    auto checkVal2 = GetStringAttribute(node_, BASELINE_OFFSET_ATTR);
    EXPECT_EQ(checkVal2, "12");
}

HWTEST_F(TextModifierTest, setCopyOption, TestSize.Level1)
{
    auto inputVal = Converter::ArkValue<Opt_CopyOptions>(ARK_COPY_OPTIONS_NONE);
    modifier_->setCopyOption(node_, &inputVal);
    auto checkVal1 = GetStringAttribute(node_, COPY_OPTIONS_ATTR);
    EXPECT_EQ(checkVal1, "CopyOptions.None");

    inputVal = Converter::ArkValue<Opt_CopyOptions>(ARK_COPY_OPTIONS_IN_APP);
    modifier_->setCopyOption(node_, &inputVal);
    auto checkVal2 = GetStringAttribute(node_, COPY_OPTIONS_ATTR);
    EXPECT_EQ(checkVal2, "CopyOptions.InApp");

    inputVal = Converter::ArkValue<Opt_CopyOptions>(ARK_COPY_OPTIONS_LOCAL_DEVICE);
    modifier_->setCopyOption(node_, &inputVal);
    auto checkVal3 = GetStringAttribute(node_, COPY_OPTIONS_ATTR);
    EXPECT_EQ(checkVal3, "CopyOptions.Local");
}

HWTEST_F(TextModifierTest, setTextShadow, TestSize.Level1)
{
    Ark_ShadowOptions shadow = {
        .radius = Converter::ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(1.5),
        .type = Converter::ArkValue<Opt_ShadowType>(ARK_SHADOW_TYPE_COLOR),
        .color = Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(ARK_COLOR_GREEN),
        .offsetX = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(2.5),
        .offsetY = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(3.5),
    };

    auto v1 = Converter::ArkUnion<Opt_Union_ShadowOptions_Array_ShadowOptions, Ark_ShadowOptions>(shadow);
    modifier_->setTextShadow(node_, &v1);
    auto checkVal1 = GetStringAttribute(node_, TEXT_SHADOW_ATTR);
    EXPECT_EQ(checkVal1,
        "{\"radius\":\"1.500000\",\"color\":\"#FF008000\","
        "\"offsetX\":\"2.500000\",\"offsetY\":\"3.500000\",\"type\":\"0\"}");
}

HWTEST_F(TextModifierTest, setHeightAdaptivePolicy, TestSize.Level1)
{
    auto inputVal = Converter::ArkValue<Opt_TextHeightAdaptivePolicy>(ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST);
    modifier_->setHeightAdaptivePolicy(node_, &inputVal);
    auto checkVal3 = GetStringAttribute(node_, HEIGHT_ADAPTIVE_POLICY_ATTR);
    EXPECT_EQ(checkVal3, "TextHeightAdaptivePolicy.MAX_LINES_FIRST");

    inputVal = Converter::ArkValue<Opt_TextHeightAdaptivePolicy>(ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MIN_FONT_SIZE_FIRST);
    modifier_->setHeightAdaptivePolicy(node_, &inputVal);
    auto checkVal4 = GetStringAttribute(node_, HEIGHT_ADAPTIVE_POLICY_ATTR);
    EXPECT_EQ(checkVal4, "TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST");

    inputVal = Converter::ArkValue<Opt_TextHeightAdaptivePolicy>(
        ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST);
    modifier_->setHeightAdaptivePolicy(node_, &inputVal);
    auto checkVal5 = GetStringAttribute(node_, HEIGHT_ADAPTIVE_POLICY_ATTR);
    EXPECT_EQ(checkVal5, "TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST");
}

HWTEST_F(TextModifierTest, DISABLED_setTextIndent, TestSize.Level1)
{
    auto v1 = Converter::ArkValue<Opt_Length>("11.25px");
    modifier_->setTextIndent(node_, &v1);
    auto checkVal1 = GetStringAttribute(node_, TEXT_INDENT_ATTR);
    EXPECT_EQ(checkVal1, "11.25px");
}

HWTEST_F(TextModifierTest, setWordBreak, TestSize.Level1)
{
    auto inputVal = Converter::ArkValue<Opt_WordBreak>(ARK_WORD_BREAK_NORMAL);
    modifier_->setWordBreak(node_, &inputVal);
    auto checkVal1 = GetStringAttribute(node_, WORD_BREAK_ATTR);
    EXPECT_EQ(checkVal1, "normal");

    inputVal = Converter::ArkValue<Opt_WordBreak>(ARK_WORD_BREAK_BREAK_ALL);
    modifier_->setWordBreak(node_, &inputVal);
    auto checkVal2 = GetStringAttribute(node_, WORD_BREAK_ATTR);
    EXPECT_EQ(checkVal2, "break-all");

    inputVal = Converter::ArkValue<Opt_WordBreak>(ARK_WORD_BREAK_BREAK_WORD);
    modifier_->setWordBreak(node_, &inputVal);
    auto checkVal3 = GetStringAttribute(node_, WORD_BREAK_ATTR);
    EXPECT_EQ(checkVal3, "break-word");
}

HWTEST_F(TextModifierTest, setLineBreakStrategy, TestSize.Level1)
{
    auto inputVal = Converter::ArkValue<Opt_LineBreakStrategy>(ARK_LINE_BREAK_STRATEGY_GREEDY);
    modifier_->setLineBreakStrategy(node_, &inputVal);
    auto checkVal3 = GetStringAttribute(node_, LINE_BREAK_STRATEGY_ATTR);
    EXPECT_EQ(checkVal3, "greedy");

    inputVal = Converter::ArkValue<Opt_LineBreakStrategy>(ARK_LINE_BREAK_STRATEGY_HIGH_QUALITY);
    modifier_->setLineBreakStrategy(node_, &inputVal);
    auto checkVal4 = GetStringAttribute(node_, LINE_BREAK_STRATEGY_ATTR);
    EXPECT_EQ(checkVal4, "high-quality");

    inputVal = Converter::ArkValue<Opt_LineBreakStrategy>(ARK_LINE_BREAK_STRATEGY_BALANCED);
    modifier_->setLineBreakStrategy(node_, &inputVal);
    auto checkVal5 = GetStringAttribute(node_, LINE_BREAK_STRATEGY_ATTR);
    EXPECT_EQ(checkVal5, "balanced");
}

HWTEST_F(TextModifierTest, setEllipsisMode, TestSize.Level1)
{
    auto inputVal = Converter::ArkValue<Opt_EllipsisMode>(ARK_ELLIPSIS_MODE_START);
    modifier_->setEllipsisMode(node_, &inputVal);
    auto checkVal1 = GetStringAttribute(node_, ELLIPSIS_MODE_ATTR);
    EXPECT_EQ(checkVal1, "EllipsisMode.START");

    inputVal = Converter::ArkValue<Opt_EllipsisMode>(ARK_ELLIPSIS_MODE_CENTER);
    modifier_->setEllipsisMode(node_, &inputVal);
    auto checkVal2 = GetStringAttribute(node_, ELLIPSIS_MODE_ATTR);
    EXPECT_EQ(checkVal2, "EllipsisMode.CENTER");

    inputVal = Converter::ArkValue<Opt_EllipsisMode>(ARK_ELLIPSIS_MODE_END);
    modifier_->setEllipsisMode(node_, &inputVal);
    auto checkVal3 = GetStringAttribute(node_, ELLIPSIS_MODE_ATTR);
    EXPECT_EQ(checkVal3, "EllipsisMode.END");
}

HWTEST_F(TextModifierTest, setSelectableMode, TestSize.Level1)
{
    auto inputVal = Converter::ArkValue<Opt_TextSelectableMode>(ARK_TEXT_SELECTABLE_MODE_SELECTABLE_UNFOCUSABLE);
    modifier_->setTextSelectable(node_, &inputVal);
    auto checkVal1 = GetStringAttribute(node_, TEXT_SELECTABLE_ATTR);
    EXPECT_EQ(checkVal1, "selectable-unfocusable");

    inputVal = Converter::ArkValue<Opt_TextSelectableMode>(ARK_TEXT_SELECTABLE_MODE_SELECTABLE_FOCUSABLE);
    modifier_->setTextSelectable(node_, &inputVal);
    auto checkVal2 = GetStringAttribute(node_, TEXT_SELECTABLE_ATTR);
    EXPECT_EQ(checkVal2, "selectable-focusable");

    inputVal = Converter::ArkValue<Opt_TextSelectableMode>(ARK_TEXT_SELECTABLE_MODE_UNSELECTABLE);
    modifier_->setTextSelectable(node_, &inputVal);
    auto checkVal3 = GetStringAttribute(node_, TEXT_SELECTABLE_ATTR);
    EXPECT_EQ(checkVal3, "unselectable");
}

HWTEST_F(TextModifierTest, setOnCopyTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextEventHub>();

    struct CopyEvent {
        int32_t nodeId;
        std::u16string value;
    };

    static std::optional<CopyEvent> checkEvent = std::nullopt;
    auto checkCallback =
        [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_String param) {
            checkEvent = {
                .nodeId = resourceId,
                .value =  Converter::Convert<std::u16string>(param)
            };
        };
    auto func = Converter::ArkCallback<Opt_Callback_String_Void>(checkCallback, CONTEXT_ID);

    modifier_->setOnCopy(node_, &func);

    // check true value
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireOnCopy(u"test_string");
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, CONTEXT_ID);
    EXPECT_EQ(checkEvent->value, u"test_string");
}

HWTEST_F(TextModifierTest, setOnSelectionChange, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextEventHub>();

    struct SelectionChangeEvent {
        int32_t nodeId;
        int32_t start;
        int32_t end;
    };

    static std::optional<SelectionChangeEvent> selectionEvent = std::nullopt;
    auto checkCallback =
        [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end) {
            selectionEvent = {
                .nodeId = resourceId,
                .start = Converter::Convert<int32_t>(start),
                .end = Converter::Convert<int32_t>(end)
            };
        };
    auto func = Converter::ArkCallback<Opt_Callback_I32_I32_Void>(checkCallback, CONTEXT_ID);

    modifier_->setOnTextSelectionChange(node_, &func);

    // check true value
    EXPECT_EQ(selectionEvent.has_value(), false);
    eventHub->FireOnSelectionChange(1, 10);
    EXPECT_EQ(selectionEvent.has_value(), true);
    EXPECT_EQ(selectionEvent->nodeId, CONTEXT_ID);
    EXPECT_EQ(selectionEvent->start, 1);
    EXPECT_EQ(selectionEvent->end, 10);
}

/*
 * @tc.name: setFontWeight0TestVariableFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontWeightTestVariableFontWeightValidValues, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input,
                          const Opt_Union_I32_FontWeight_String& value, const std::string& expectedStr) {
        auto inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight, nullptr);
        auto jsonValue = GetJsonValue(node_);
        auto font = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(font, ATTRIBUTE_VARIABLE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFontWeight0, attribute: fontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureVariableFontWeightEnumValidValues) {
        checkValue(input, ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(value), expected);
    }
    for (auto& [input, value, expected] : testFixtureVariableFontWeightNumbersValidValues) {
        checkValue(input, ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(value), expected);
    }
    for (auto& [input, value, expected] : testFixtureVariableFontWeightStringsValidValues) {
        checkValue(input, ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFontWeight0TestVariableFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontWeightTestVariableFontWeightInvalidValues, TestSize.Level1)
{
    // Initial setup
    auto initValueFontWeight = ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](
                          const std::string& input, const Opt_Union_I32_FontWeight_String& value) {
        auto inputValueFontWeight = initValueFontWeight;
        modifier_->setFontWeight(node_, &inputValueFontWeight, nullptr);
        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight, nullptr);
        auto jsonValue = GetJsonValue(node_);
        auto font = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(font, ATTRIBUTE_VARIABLE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFontWeight0, attribute: fontWeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureVariableFontWeightEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(value));
    }
    for (auto& [input, value] : testFixtureFontWeightNumbersInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(value));
    }
    for (auto& [input, value] : testFixtureVariableFontWeightStringsInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Empty>(nullptr));
    checkValue("undefined", ArkUnion<Opt_Union_I32_FontWeight_String>(Ark_Empty()));
}

/*
 * @tc.name: setFontWeight1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontWeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto font = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'fontWeight.weight'";

    resultStr =
        GetAttrValue<std::string>(font, ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'fontWeight.options.enableVariableFontWeight'";
}

/*
 * @tc.name: setFontWeight1TestFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontWeightTestFontWeightValidValues, TestSize.Level1)
{
    // Initial setup
    Ark_FontSettingOptions options = {
        .enableVariableFontWeight =
            ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]))
    };
    auto initValueOptions = ArkValue<Opt_FontSettingOptions>(options);

    auto checkValue = [this, &initValueOptions](const std::string& input,
                          const Opt_Union_I32_FontWeight_String& value, const std::string& expectedStr) {
        auto inputValueOptions = initValueOptions;
        auto inputValueWeight = value;
        modifier_->setFontWeight(node_, &inputValueWeight, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFontWeight1, attribute: fontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(value), expected);
    }
    for (auto& [input, value, expected] : testFixtureFontWeightNumbersValidValues) {
        checkValue(input, ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightStringsValidValues) {
        checkValue(input, ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFontWeight1TestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontWeightTestFontWeightInvalidValues, TestSize.Level1)
{
    // Initial setup
    auto initValueWeight = ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    Ark_FontSettingOptions options = {
        .enableVariableFontWeight =
            ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]))
    };
    auto initValueOptions = ArkValue<Opt_FontSettingOptions>(options);

    auto checkValue = [this, &initValueWeight, &initValueOptions](
                          const std::string& input, const Opt_Union_I32_FontWeight_String& value) {
        auto inputValueWeight = initValueWeight;
        auto inputValueOptions = initValueOptions;

        modifier_->setFontWeight(node_, &inputValueWeight, &inputValueOptions);
        inputValueWeight = value;
        modifier_->setFontWeight(node_, &inputValueWeight, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFontWeight1, attribute: fontWeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Empty>(nullptr));
    checkValue("undeifned", ArkUnion<Opt_Union_I32_FontWeight_String>(Ark_Empty()));
}

/*
 * @tc.name: setFontWeight1TestOptionsEnableVariableFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontWeightTestOptionsEnableVariableFontWeightValidValues, TestSize.Level1)
{
    // Initial setup
    auto initValueWeight = ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    Ark_FontSettingOptions options = {
        .enableVariableFontWeight =
            ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]))
    };
    auto initValueOptions = ArkValue<Opt_FontSettingOptions>(options);

    auto checkValue = [this, &initValueWeight, &initValueOptions](
                          const std::string& input, const Opt_Boolean& value, const std::string& expectedStr) {
        auto inputValueWeight = initValueWeight;
        auto inputValueOptions = initValueOptions;

        inputValueOptions.value.enableVariableFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueWeight, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto font = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(font, ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setFontWeight1, attribute: font.enableVariableFontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, ArkValue<Opt_Boolean>(value), expected);
    }
}

/*
 * @tc.name: setTextShadowTestArrayValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextShadowTestArrayValues, TestSize.Level1)
{
    std::string resultStr;
    Ark_ShadowOptions shadow1 = {
        .color = ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>("#FFAABB01"),
        .offsetX = ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(50.),
        .offsetY = ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(55.),
        .radius = ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(12.),
        .type = Converter::ArkValue<Opt_ShadowType>(ARK_SHADOW_TYPE_COLOR),
    };
    Ark_ShadowOptions shadow2 = {
        .color = ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>("#FFAABB22"),
        .offsetX = ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(70.),
        .offsetY = ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(75.),
        .radius = ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(20.),
        .type = Converter::ArkValue<Opt_ShadowType>(ARK_SHADOW_TYPE_BLUR),
    };
    std::vector<Ark_ShadowOptions> vec = { shadow1, shadow2 };
    Array_ShadowOptions array = { .array = vec.data(), .length = vec.size() };
    auto inputValueTextShadow = ArkUnion<Opt_Union_ShadowOptions_Array_ShadowOptions, Array_ShadowOptions>(array);
    modifier_->setTextShadow(node_, &inputValueTextShadow);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultTextShadow =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
    ASSERT_NE(resultTextShadow, nullptr);
    ASSERT_EQ(resultTextShadow->GetArraySize(), vec.size());

    std::unique_ptr<JsonValue> item;
    auto get = [&item](const std::string& attrName) {
        return GetAttrValue<std::string>(item, attrName);
    };

    item = resultTextShadow->GetArrayItem(0);
    ASSERT_NE(item, nullptr);
    EXPECT_EQ(get(ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME), "#FFAABB01");
    EXPECT_EQ(get(ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME), "50.000000");
    EXPECT_EQ(get(ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME), "55.000000");
    EXPECT_EQ(get(ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME), "12.000000");
    EXPECT_EQ(get(ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME), "0");

    item = resultTextShadow->GetArrayItem(1);
    ASSERT_NE(item, nullptr);
    EXPECT_EQ(get(ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME), "#FFAABB22");
    EXPECT_EQ(get(ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME), "70.000000");
    EXPECT_EQ(get(ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME), "75.000000");
    EXPECT_EQ(get(ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME), "20.000000");
    EXPECT_EQ(get(ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME), "1");
}

/*
 * @tc.name: setTextOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_DEFAULT_VALUE) << "Default value for attribute 'content'";
}

/*
 * @tc.name: setTextOptionsTestContentValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextOptionsTestContentValidValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto checkValue = [this, pattern](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        auto textOptions = Converter::ArkValue<Opt_TextOptions>(Ark_Empty());

        modifier_->setTextOptions(node_, &value, &textOptions);
        pattern->OnModifyDone(); // Need for correct processing
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextOptions, attribute: content";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setTextOptionsTestContentNull
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextOptionsTestContentNull, TestSize.Level1)
{
    // no crash should happen
    auto textOptions = Converter::ArkValue<Opt_TextOptions>();
    modifier_->setTextOptions(node_, nullptr, &textOptions);
}

/*
 * @tc.name: setTextOptionsTestContentEmpty
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextOptionsTestContentEmpty, TestSize.Level1)
{
    // no crash should happen
    auto textOptions = Converter::ArkValue<Opt_TextOptions>();
    auto emptyContent = Converter::ArkValue<Opt_Union_String_Resource>();
    modifier_->setTextOptions(node_, &emptyContent, &textOptions);
}

/*
 * @tc.name: setTextOptionsTestValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextOptionsTestValueValidValues, TestSize.Level1)
{
    auto text = ArkUnion<Opt_Union_String_Resource, Ark_String>("text");

    TextControllerPeer peer;
    Ark_TextOptions textOptions = {
        .controller = &peer,
    };
    auto textOptionsOpt = Converter::ArkValue<Opt_TextOptions>(textOptions);
    modifier_->setTextOptions(node_, &text, &textOptionsOpt);

    // get controller from node
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto baseController = pattern->GetTextController();
    auto textController = AceType::DynamicCast<TextController>(baseController);
    ASSERT_NE(textController, nullptr);

    // check that controller in peer is properly set
    EXPECT_EQ(peer.controller, textController);
}

/*
 * @tc.name: setTextOptionsTestValueNull
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextOptionsTestValueNull, TestSize.Level1)
{
    // no crash should happen
    auto text = ArkUnion<Opt_Union_String_Resource, Ark_String>("text");
    modifier_->setTextOptions(node_, &text, nullptr);
}

/*
 * @tc.name: setDataDetectorConfig
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setDataDetectorConfig, TestSize.Level1)
{
    Ark_TextDataDetectorConfig config;
    config.color = ArkUnion<Opt_ResourceColor, Ark_String>("#FFAABBCC");
    std::vector<Ark_TextDataDetectorType> types;
    types.push_back(ARK_TEXT_DATA_DETECTOR_TYPE_PHONE_NUMBER);
    types.push_back(ARK_TEXT_DATA_DETECTOR_TYPE_ADDRESS);
    config.types = Converter::ArkValue<Opt_Array_TextDataDetectorType>(types, Converter::FC);

    Ark_DecorationStyleInterface decoration;
    decoration.type = Converter::ArkValue<Opt_TextDecorationType>(ARK_TEXT_DECORATION_TYPE_LINE_THROUGH);
    decoration.color = ArkUnion<Opt_ResourceColor, Ark_String>("#FF112233");
    decoration.style = ArkValue<Opt_TextDecorationStyle>(ARK_TEXT_DECORATION_STYLE_WAVY);
    config.decoration = ArkValue<Opt_DecorationStyleInterface>(decoration);

    auto inputVal = Converter::ArkValue<Opt_TextDataDetectorConfig>(config);
    modifier_->setDataDetectorConfig(node_, &inputVal);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);

    auto json = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DATA_DETECTOR_CONFIG_NAME);
    auto resultColor = GetAttrValue<std::string>(json, "color");
    auto resultTypes = GetAttrValue<std::string>(json, "types");
    auto jsonDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(json, "decoration");
    auto resultDecorationType = GetAttrValue<std::string>(jsonDecoration, "type");
    auto resultDecorationColor = GetAttrValue<std::string>(jsonDecoration, "color");
    auto resultDecorationStyle = GetAttrValue<std::string>(jsonDecoration, "style");
    EXPECT_EQ(resultColor, "#FFAABBCC");
    EXPECT_EQ(resultTypes, "phoneNum,location");
    EXPECT_EQ(resultDecorationType, "3");
    EXPECT_EQ(resultDecorationColor, "#FF112233");
    EXPECT_EQ(resultDecorationStyle, "4");
}

/*
 * @tc.name: setDataDetectorConfigTestCallback
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setDataDetectorConfigTestCallback, TestSize.Level1)
{
    Ark_TextDataDetectorConfig config;
    static const int32_t expectedResourceId = 123;
    static const std::string expectedArg = "expected string value";
    static int32_t actualResourceId = -1;
    static std::string actualArg = "";

    auto callSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_String breakpoints)
    {
        actualResourceId = Converter::Convert<int32_t>(resourceId);
        actualArg = Converter::Convert<std::string>(breakpoints);
    };

    auto func = Converter::ArkCallback<Opt_Callback_String_Void>(callSyncFunc, expectedResourceId);
    config.onDetectResultUpdate = func;

    auto inputVal = Converter::ArkValue<Opt_TextDataDetectorConfig>(config);
    modifier_->setDataDetectorConfig(node_, &inputVal);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto adapter = pattern->GetDataDetectorAdapter();
    adapter->FireOnResult(expectedArg);

    EXPECT_EQ(actualResourceId, expectedResourceId);
    EXPECT_EQ(actualArg, expectedArg);
}

/**
 * @tc.name: setBindSelectionMenuTest
 * @tc.desc: Check the functionality of setBindSelectionMenu
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setBindSelectionMenuTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(modifier_->setBindSelectionMenu, nullptr);
    // Prepare callbacks
    auto onAppearCallback = [](const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end) {
        g_isCalled = true;
    };
    auto onDisappearCallback = [](const Ark_Int32 resourceId) {
        g_isCalled = true;
    };
    // Prepare options
    Ark_SelectionMenuOptions value;
    value.menuType = Converter::ArkValue<Opt_MenuType>(Ark_MenuType::ARK_MENU_TYPE_PREVIEW_MENU);
    value.onAppear = Converter::ArkCallback<Opt_MenuOnAppearCallback>(onAppearCallback);
    value.onDisappear = Converter::ArkCallback<Opt_VoidCallback>(onDisappearCallback);
    auto options = Converter::ArkValue<Opt_SelectionMenuOptions>(value);
    auto responseType = Converter::ArkValue<Opt_TextResponseType>(ARK_TEXT_RESPONSE_TYPE_RIGHT_CLICK);
    auto buildFunc = getBuilderCb();
    auto spanType = Converter::ArkValue<Opt_TextSpanType>(ARK_TEXT_SPAN_TYPE_TEXT);

    uiNode = BlankModelNG::CreateFrameNode(NODE_ID);
    checkCBEvent = std::nullopt;
    modifier_->setBindSelectionMenu(node_, &spanType, &buildFunc, &responseType, &options);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectOverlayInfo selectInfo;
    // responseType and selectedType accord in setBindSelectionMenu
#ifdef WRONG_API
    pattern->SetSelectedType(TextSpanType::TEXT);
#endif
    pattern->SetTextResponseType(TextResponseType::RIGHT_CLICK);
    pattern->CopySelectionMenuParams(selectInfo);
    ASSERT_NE(selectInfo.menuInfo.menuBuilder, nullptr);
    selectInfo.menuInfo.menuBuilder();
    ASSERT_EQ(checkCBEvent.has_value(), true);
    EXPECT_EQ(checkCBEvent->resourceId, TEST_RESOURCE_ID);
    uiNode = std::nullopt;
    checkCBEvent = std::nullopt;
    g_isCalled = false;
    ASSERT_NE(selectInfo.menuCallback.onAppear, nullptr);
    selectInfo.menuCallback.onAppear();
    EXPECT_TRUE(g_isCalled);
    g_isCalled = false;
    ASSERT_NE(selectInfo.menuCallback.onDisappear, nullptr);
    selectInfo.menuCallback.onDisappear();
    EXPECT_TRUE(g_isCalled);
}

/*
 * @tc.name: setSelectionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setSelectionTest, TestSize.Level1)
{
    static std::list<SelectionRange> range;

    auto textOptions = ArkValue<Opt_TextOptions>();
    auto value = ArkUnion<Opt_Union_String_Resource, Ark_String>("Some text value");
    modifier_->setTextOptions(node_, &value, &textOptions);

    auto selectable = ArkValue<Opt_TextSelectableMode>(ARK_TEXT_SELECTABLE_MODE_SELECTABLE_UNFOCUSABLE);
    modifier_->setTextSelectable(node_, &selectable);
    auto copyOpt = ArkValue<Opt_CopyOptions>(ARK_COPY_OPTIONS_IN_APP);
    modifier_->setCopyOption(node_, &copyOpt);
    Ark_TextOverflowOptions overflowOptions = {
        .overflow = ArkValue<Opt_TextOverflow>(ARK_TEXT_OVERFLOW_CLIP),
    };
    auto optOverflow = ArkValue<Opt_TextOverflowOptions>(overflowOptions);
    modifier_->setTextOverflow(node_, &optOverflow);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TextEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnSelectionChange([](int32_t start, int32_t end) {
        range.push_back({ .start = start, .end = end });
    });
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    const int32_t expectedStart = 4;
    const int32_t expectedEnd = 10;
    auto start = ArkValue<Opt_Int32>(expectedStart);
    auto end = ArkValue<Opt_Int32>(expectedEnd);
    modifier_->setSelection(node_, &start, &end);
    ASSERT_FALSE(range.empty());
    EXPECT_EQ(range.front().start, expectedStart);
    EXPECT_EQ(range.front().end, expectedEnd);
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsMarqueeStartPolicyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMarqueeOptionsTestMarqueeOptionsMarqueeStartPolicyValidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Float64>(std::get<1>(testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Int32>(std::get<1>(testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Int32>(std::get<1>(testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](const std::string& input, const std::string& expectedStr,
                          const Opt_MarqueeStartPolicy& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        WriteTo(inputValueMarqueeOptions).marqueeStartPolicy = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_MARQUEE_START_POLICY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setMarqueeOptions, attribute: marqueeOptions.marqueeStartPolicy";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumMarqueeStartPolicyValidValues) {
        checkValue(input, expected, ArkValue<Opt_MarqueeStartPolicy>(value));
    }
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsMarqueeStartPolicyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMarqueeOptionsTestMarqueeOptionsMarqueeStartPolicyInvalidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Float64>(std::get<1>(testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Int32>(std::get<1>(testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Int32>(std::get<1>(testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](const std::string& input, const Opt_MarqueeStartPolicy& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        WriteTo(inputValueMarqueeOptions).marqueeStartPolicy = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_MARQUEE_START_POLICY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MARQUEE_OPTIONS_I_MARQUEE_START_POLICY_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setMarqueeOptions, attribute: marqueeOptions.marqueeStartPolicy";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumMarqueeStartPolicyInvalidValues) {
        checkValue(input, ArkValue<Opt_MarqueeStartPolicy>(value));
    }
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsFromStartValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMarqueeOptionsTestMarqueeOptionsFromStartValidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Float64>(std::get<1>(testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Int32>(std::get<1>(testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Int32>(std::get<1>(testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](
                          const std::string& input, const MarqueeDirection& expected, const Opt_Boolean& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        WriteTo(inputValueMarqueeOptions).fromStart = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(layoutProperty, nullptr);
        std::optional<MarqueeDirection> direction = layoutProperty->GetTextMarqueeDirection();
        ASSERT_TRUE(direction.has_value());
        EXPECT_EQ(direction.value(), expected) <<
            "Input value is: " << input << ", method: setMarqueeOptions, attribute: marqueeOptions.fromStart";
    };

    std::vector<std::tuple<std::string, Ark_Boolean, MarqueeDirection>> fromStartValidValues = {
        { "true", Converter::ArkValue<Ark_Boolean>(true), MarqueeDirection::DEFAULT },
        { "false", Converter::ArkValue<Ark_Boolean>(false), MarqueeDirection::DEFAULT_REVERSE },
    };

    for (auto& [input, value, expected] : fromStartValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsFromStartInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMarqueeOptionsTestMarqueeOptionsFromStartInvalidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Float64>(std::get<1>(testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Int32>(std::get<1>(testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Int32>(std::get<1>(testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](const std::string& input, const Opt_Boolean& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        WriteTo(inputValueMarqueeOptions).fromStart = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(layoutProperty, nullptr);
        std::optional<MarqueeDirection> direction = layoutProperty->GetTextMarqueeDirection();
        EXPECT_FALSE(direction.has_value());
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setOnMarqueeStateChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setOnMarqueeStateChangeTest, TestSize.Level1)
{
    static std::optional<Ark_MarqueeState> checkMarqueeState;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, Ark_MarqueeState marqueeState) {
        checkMarqueeState = marqueeState;
    };

    // setup the callback object via C-API
    auto arkCallback = Converter::ArkCallback<Opt_Callback_MarqueeState_Void>(checkCallback);
    modifier_->setOnMarqueeStateChange(node_, &arkCallback);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TextEventHub>();
    ASSERT_NE(eventHub, nullptr);

    const int32_t start = 0;
    const int32_t bounce = 1;
    const int32_t finish = 2;
    const int32_t invalidValue = 100;

    eventHub->FireOnMarqueeStateChange(start);
    ASSERT_TRUE(checkMarqueeState.has_value());
    EXPECT_EQ(checkMarqueeState.value(), ARK_MARQUEE_STATE_START);

    eventHub->FireOnMarqueeStateChange(bounce);
    ASSERT_TRUE(checkMarqueeState.has_value());
    EXPECT_EQ(checkMarqueeState.value(), ARK_MARQUEE_STATE_BOUNCE);

    eventHub->FireOnMarqueeStateChange(finish);
    ASSERT_TRUE(checkMarqueeState.has_value());
    EXPECT_EQ(checkMarqueeState.value(), ARK_MARQUEE_STATE_FINISH);

    eventHub->FireOnMarqueeStateChange(invalidValue);
    ASSERT_TRUE(checkMarqueeState.has_value());
    EXPECT_EQ(checkMarqueeState.value(), static_cast<Ark_MarqueeState>(-1));
}

/*
 * @tc.name: setMarqueeOptionsTestEmpty
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMarqueeOptionsTestEmpty, TestSize.Level1)
{
    // Check that there is no crash

    // Case 1
    modifier_->setMarqueeOptions(node_, nullptr);

    // Case 2
    auto marqueeOptions = ArkValue<Opt_TextMarqueeOptions>();
    modifier_->setMarqueeOptions(node_, &marqueeOptions);
}
}
