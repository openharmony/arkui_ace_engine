/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "accessor_test_utils.h"
#include "base/utils/measure_util.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace {
MeasureContext* MeasureUtilGetMeasureCtx();
} // OHOS::Ace

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class GlobalScopeOhosMeasureUtilsAccessorTest
    : public StaticAccessorTest<GENERATED_ArkUIGlobalScope_ohos_measure_utilsAccessor,
          &GENERATED_ArkUIAccessors::getGlobalScope_ohos_measure_utilsAccessor> {
};

namespace {
const int32_t TEST_SIZE_VALUE = 10;
const std::string TEST_TEXT = "Have a nice day!";
const std::string TEST_DIM_14 = "14px";
const std::string TEST_DIM_15 = "15px";
const std::string TEST_DIM_16 = "16px";
const std::string TEST_DIM_17 = "17px";
const std::string TEST_DIM_18 = "18px";
const std::string TEST_DIM_19 = "19px";
const OHOS::Ace::FontStyle TEST_FONT_STYLE = OHOS::Ace::FontStyle::ITALIC;
const FontWeight TEST_FONT_WEIGHT = FontWeight::BOLD;
const std::string TEST_FONT_WEIGHT_STR = "bold";
const std::string TEST_FONT_FAMILY = "serif";
const TextAlign TEST_ALIGN = TextAlign::END;
const auto ARK_TEST_ALIGN = ARK_TEXT_ALIGN_END;
const TextOverflow TEST_OVERFLOW = TextOverflow::MARQUEE;
const int32_t TEST_MAX_LINES = 3;
const int32_t TEST_TEXT_CASE = static_cast<int32_t>(TextCase::UPPERCASE);
const WordBreak TEST_WORD_BREAK = WordBreak::BREAK_WORD;
const auto ARK_TEST_WORD_BREAK = ARK_WORD_BREAK_BREAK_WORD;

Ark_MeasureOptions GetOptions()
{
    return Ark_MeasureOptions {
        .textContent = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(TEST_TEXT),
        .constraintWidth = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(TEST_DIM_14),
        .fontSize = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(TEST_DIM_15),
        .fontStyle = Converter::ArkUnion<Opt_Union_I32_FontStyle, Ark_FontStyle>(TEST_FONT_STYLE),
        .fontWeight = Converter::ArkUnion<Opt_Union_I32_String_FontWeight, Ark_FontWeight>(TEST_FONT_WEIGHT),
        .fontFamily = Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(TEST_FONT_FAMILY),
        .letterSpacing = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>(TEST_DIM_16),
        .textAlign = Converter::ArkUnion<Opt_Union_I32_TextAlign, Ark_TextAlign>(ARK_TEST_ALIGN),
        .overflow =  Converter::ArkUnion<Opt_Union_I32_TextOverflow, Ark_TextOverflow>(TEST_OVERFLOW),
        .maxLines = Converter::ArkValue<Opt_Int32>(TEST_MAX_LINES),
        .lineHeight = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(TEST_DIM_17),
        .baselineOffset = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>(TEST_DIM_18),
        .textCase = Converter::ArkUnion<Opt_Union_I32_TextCase, Ark_Int32>(TEST_TEXT_CASE),
        .textIndent = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>(TEST_DIM_19),
        .wordBreak = Converter::ArkValue<Opt_WordBreak>(ARK_TEST_WORD_BREAK),
    };
}
} // namespace

/**
 * @tc.name: measureTextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeOhosMeasureUtilsAccessorTest, DISABLED_measureTextTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->measureText, nullptr);

    auto options = GetOptions();
    auto value = accessor_->measureText(&options);
    auto testValue = Converter::Convert<int32_t>(value);
    EXPECT_EQ(testValue, TEST_SIZE_VALUE);

    MeasureContext* ctx = MeasureUtilGetMeasureCtx();
    EXPECT_EQ(ctx->textContent, TEST_TEXT);
    EXPECT_EQ(ctx->constraintWidth->ConvertToPx(), Dimension::FromString(TEST_DIM_14).ConvertToPx());
    EXPECT_EQ(ctx->fontSize->ConvertToPx(), Dimension::FromString(TEST_DIM_15).ConvertToPx());
    EXPECT_EQ(ctx->fontStyle, TEST_FONT_STYLE);
    EXPECT_EQ(ctx->fontWeight, TEST_FONT_WEIGHT_STR);
    EXPECT_EQ(ctx->fontFamily, TEST_FONT_FAMILY);
    EXPECT_EQ(ctx->letterSpacing->ConvertToPx(), Dimension::FromString(TEST_DIM_16).ConvertToPx());
    EXPECT_EQ(ctx->textAlign, TEST_ALIGN);
    EXPECT_EQ(ctx->textOverlayFlow, TEST_OVERFLOW);
    EXPECT_EQ(ctx->maxlines, TEST_MAX_LINES);
    EXPECT_EQ(ctx->lineHeight->ConvertToPx(), Dimension::FromString(TEST_DIM_17).ConvertToPx());
    EXPECT_EQ(ctx->baselineOffset->ConvertToPx(), Dimension::FromString(TEST_DIM_18).ConvertToPx());
    EXPECT_EQ(ctx->textCase, TextCase::UPPERCASE);
    EXPECT_EQ(ctx->textIndent->ConvertToPx(), Dimension::FromString(TEST_DIM_19).ConvertToPx());
    EXPECT_EQ(ctx->wordBreak, TEST_WORD_BREAK);
}

/**
 * @tc.name: measureTextSizeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeOhosMeasureUtilsAccessorTest, DISABLED_measureTextSizeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->measureTextSize, nullptr);

    auto options = GetOptions();
    Ark_SizeOptions value = accessor_->measureTextSize(&options);
    auto testValue = Converter::OptConvert<Dimension>(value.width).value_or(Dimension(-1));
    EXPECT_EQ(testValue.ConvertToPx(), TEST_SIZE_VALUE);
    testValue = Converter::OptConvert<Dimension>(value.height).value_or(Dimension(-1));
    EXPECT_EQ(testValue.ConvertToPx(), TEST_SIZE_VALUE);

    MeasureContext* ctx = MeasureUtilGetMeasureCtx();
    EXPECT_EQ(ctx->textContent, TEST_TEXT);
    EXPECT_EQ(ctx->constraintWidth->ConvertToPx(), Dimension::FromString(TEST_DIM_14).ConvertToPx());
    EXPECT_EQ(ctx->fontSize->ConvertToPx(), Dimension::FromString(TEST_DIM_15).ConvertToPx());
    EXPECT_EQ(ctx->fontStyle, TEST_FONT_STYLE);
    EXPECT_EQ(ctx->fontWeight, TEST_FONT_WEIGHT_STR);
    EXPECT_EQ(ctx->fontFamily, TEST_FONT_FAMILY);
    EXPECT_EQ(ctx->letterSpacing->ConvertToPx(), Dimension::FromString(TEST_DIM_16).ConvertToPx());
    EXPECT_EQ(ctx->textAlign, TEST_ALIGN);
    EXPECT_EQ(ctx->textOverlayFlow, TEST_OVERFLOW);
    EXPECT_EQ(ctx->maxlines, TEST_MAX_LINES);
    EXPECT_EQ(ctx->lineHeight->ConvertToPx(), Dimension::FromString(TEST_DIM_17).ConvertToPx());
    EXPECT_EQ(ctx->baselineOffset->ConvertToPx(), Dimension::FromString(TEST_DIM_18).ConvertToPx());
    EXPECT_EQ(ctx->textCase, TextCase::UPPERCASE);
    EXPECT_EQ(ctx->textIndent->ConvertToPx(), Dimension::FromString(TEST_DIM_19).ConvertToPx());
    EXPECT_EQ(ctx->wordBreak, TEST_WORD_BREAK);
}

} // namespace OHOS::Ace::NG