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
#include "core/interfaces/native/implementation/styled_string_peer.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

constexpr int TEST_LENGTH = 2;
constexpr int TEST_START_STR = 1;
constexpr int TEST_START_DCRN = TEST_START_STR + TEST_LENGTH + 1;
constexpr int TEST_START_BSL = TEST_START_DCRN + TEST_LENGTH + 1;
constexpr int TEST_START_LSP = TEST_START_BSL + TEST_LENGTH + 1;
constexpr int TEST_START_TSH = TEST_START_LSP + TEST_LENGTH + 1;
constexpr int TEST_START_LNHT = TEST_START_TSH + TEST_LENGTH + 1;
constexpr int TEST_START_BGCL = TEST_START_LNHT + TEST_LENGTH + 1;
constexpr int TEST_START_URL = TEST_START_BGCL + TEST_LENGTH + 1;
constexpr int TEST_START_PSST = TEST_START_URL + TEST_LENGTH + 1;
constexpr auto STRING_TEST_VALUE = "This is a test string for styled text, and more text to test it out.";

const std::tuple<std::string, int32_t> TEST_FONT_SIZE = { "16.00vp", 16 };
const std::tuple<Ace::FontWeight, int32_t> TEST_FONT_WEIGHT = { FontWeight::W900, 900 };
const std::vector<std::string> TEST_FONT_FAMILIES = { "Arial" };
const std::tuple<std::string, Ark_Color> TEST_FONT_COLOR =
        { "#FFFF0000", Converter::ArkValue<Ark_Color>(ARK_COLOR_RED) };
const Ace::FontStyle TEST_FONT_STYLE = Ace::FontStyle::ITALIC;
const std::tuple<std::string, Ark_Color> TEST_DCRN_COLOR =
        { "#FFFFFF00", Converter::ArkValue<Ark_Color>(ARK_COLOR_YELLOW) };
const Ace::TextDecoration TEST_DCRN_TYPE = Ace::TextDecoration::UNDERLINE;
const Ace::TextDecorationStyle TEST_DCRN_STYLE = TextDecorationStyle::SOLID;
const std::tuple<std::string, int> TEST_BASELINE_OFFSET = { "10.00vp", 10 };
const std::tuple<std::string, int> TEST_LETTER_SPACING = { "12.00vp", 12 };
const std::tuple<std::string, int> TEST_LINE_HEIGHT = { "14.00vp", 14 };
const int TEST_TEXT_SHADOW_RADIUS = 5;
const int TEST_TEXT_SHADOW_OFFSET = 3;
const std::tuple<ShadowType, Ark_ShadowType> TEST_TEXT_SHADOW_TYPE = {
    Ace::ShadowType::COLOR, ARK_SHADOW_TYPE_COLOR };
const std::tuple<std::string, Ark_Color> TEST_TEXT_SHADOW_COLOR =
        { "#FFFF0000", Converter::ArkValue<Ark_Color>(ARK_COLOR_RED) };
const std::tuple<std::string, Ark_Color> TEST_BGCL_COLOR =
        { "#FFFFFF00", Converter::ArkValue<Ark_Color>(ARK_COLOR_YELLOW) };
const std::tuple<std::string, int> TEST_BGCL_RADIUS = { "10.00px", 10 };
const std::string TEST_URL = "https://www.test.test";
const std::tuple<Ace::TextAlign, Ark_TextAlign> TEST_PSST_TEXT_ALIGN = {
    Ace::TextAlign::CENTER, ARK_TEXT_ALIGN_CENTER};
const int TEST_PSST_TEXT_INDEN = 5;
const int TEST_PSST_MAX_LINES = 8;
const std::tuple<Ace::TextOverflow, Ark_TextOverflow> TEST_PSST_OVERFLOW = {
    Ace::TextOverflow::ELLIPSIS, ARK_TEXT_OVERFLOW_ELLIPSIS };
const std::tuple<Ace::WordBreak, Ark_WordBreak> TEST_PSST_WORD_BREAK = {
    Ace::WordBreak::BREAK_ALL, ARK_WORD_BREAK_BREAK_ALL };
const std::tuple<std::string, int> TEST_PSST_LEADING_MARGIN = { "width: 2.00vp height: 2.00vp", 2 };


const std::vector<Ace::SpanType> SPAN_TYPE_TEST_VALUES = {
    Ace::SpanType::Font,
    Ace::SpanType::Decoration,
    Ace::SpanType::BaselineOffset,
    Ace::SpanType::LetterSpacing,
    Ace::SpanType::TextShadow,
    Ace::SpanType::LineHeight,
    Ace::SpanType::BackgroundColor,
    Ace::SpanType::Url,
    Ace::SpanType::ParagraphStyle,
    Ace::SpanType::ExtSpan, // not implement
    Ace::SpanType::Gesture // not implement
    };

namespace {
    const std::vector<Ark_StyleOptions> testArrayStyles = std::vector {
        Ark_StyleOptions {
            .start = Converter::ArkValue<Opt_Number>(TEST_START_STR),
            .length = Converter::ArkValue<Opt_Number>(TEST_LENGTH),
            .styledKey = Converter::ArkValue<Ark_StyledStringKey>(SPAN_TYPE_TEST_VALUES[0]),
            .styledValue = {
                .selector = 0, // Ark_TextStyle_styled_string
                .value0 = {
                    .fontColor = Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(TEST_FONT_COLOR)),
                    .fontFamily = Converter::ArkValue<Opt_String>(TEST_FONT_FAMILIES[0]),
                    .fontSize = Converter::ArkValue<Opt_Number>(std::get<1>(TEST_FONT_SIZE)),
                    .fontWeight = Converter::ArkValue<Opt_Number>(std::get<1>(TEST_FONT_WEIGHT)),
                    .fontStyle = Converter::ArkValue<Opt_FontStyle>(TEST_FONT_STYLE),
                }
            }
        },
        Ark_StyleOptions {
            .start = Converter::ArkValue<Opt_Number>(TEST_START_DCRN),
            .length = Converter::ArkValue<Opt_Number>(TEST_LENGTH),
            .styledKey = Converter::ArkValue<Ark_StyledStringKey>(SPAN_TYPE_TEST_VALUES[1]),
            .styledValue = {
                .selector = 1, // Ark_DecorationStyle
                .value1 = {
                    .type = Converter::ArkValue<Ark_TextDecorationType>(TEST_DCRN_TYPE),
                    .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(TEST_DCRN_COLOR)),
                    .style = Converter::ArkValue<Opt_TextDecorationStyle>(TEST_DCRN_STYLE),
                }
            }
        },
        Ark_StyleOptions {
            .start = Converter::ArkValue<Opt_Number>(TEST_START_BSL),
            .length = Converter::ArkValue<Opt_Number>(TEST_LENGTH),
            .styledKey = Converter::ArkValue<Ark_StyledStringKey>(SPAN_TYPE_TEST_VALUES[2]),
            .styledValue = {
                .selector = 2, // Ark_BaselineOffsetStyle
                .value2 = {
                    .baselineOffset = Converter::ArkValue<Ark_Number>(std::get<1>(TEST_BASELINE_OFFSET))
                }
            }
        },
        Ark_StyleOptions {
            .start = Converter::ArkValue<Opt_Number>(TEST_START_LSP),
            .length = Converter::ArkValue<Opt_Number>(TEST_LENGTH),
            .styledKey = Converter::ArkValue<Ark_StyledStringKey>(SPAN_TYPE_TEST_VALUES[3]),
            .styledValue = {
                .selector = 3, // Ark_LetterSpacingStyle
                .value3 = {
                    .letterSpacing = Converter::ArkValue<Ark_Number>(std::get<1>(TEST_LETTER_SPACING))
                }
    
            }
        },
        Ark_StyleOptions {
            .start = Converter::ArkValue<Opt_Number>(TEST_START_TSH),
            .length = Converter::ArkValue<Opt_Number>(TEST_LENGTH),
            .styledKey = Converter::ArkValue<Ark_StyledStringKey>(SPAN_TYPE_TEST_VALUES[4]),
            .styledValue = {
                .selector = 4, // Ark_TextShadowStyle
                .value4 = {
                    .textShadow = {
                        .array = new Ark_ShadowOptions[] {
                            {
                                .radius = Converter::ArkUnion<
                                    Ark_Union_Number_Resource, Ark_Number>(TEST_TEXT_SHADOW_RADIUS),
                                .type = Converter::ArkValue<Opt_ShadowType>(std::get<1>(TEST_TEXT_SHADOW_TYPE)),
                                .color= Converter::ArkUnion<
                                    Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
                                        std::get<1>(TEST_TEXT_SHADOW_COLOR)),
                                .offsetX = Converter::ArkUnion<
                                    Opt_Union_Number_Resource, Ark_Number>(TEST_TEXT_SHADOW_OFFSET),
                                .offsetY = Converter::ArkUnion<
                                    Opt_Union_Number_Resource, Ark_Number>(TEST_TEXT_SHADOW_OFFSET),
                                .fill = Converter::ArkValue<Opt_Boolean>(true)
                            }
                        },
                        .length = 1
                    }
                }
            }
        },
        Ark_StyleOptions {
            .start = Converter::ArkValue<Opt_Number>(TEST_START_LNHT),
            .length = Converter::ArkValue<Opt_Number>(TEST_LENGTH),
            .styledKey = Converter::ArkValue<Ark_StyledStringKey>(SPAN_TYPE_TEST_VALUES[5]),
            .styledValue = {
                .selector = 8, // Ark_LineHeightStyle
                .value8 = {
                    .lineHeight = Converter::ArkValue<Ark_Number>(std::get<1>(TEST_LINE_HEIGHT))
                }
            }
        },
        Ark_StyleOptions {
            .start = Converter::ArkValue<Opt_Number>(TEST_START_BGCL),
            .length = Converter::ArkValue<Opt_Number>(TEST_LENGTH),
            .styledKey = Converter::ArkValue<Ark_StyledStringKey>(SPAN_TYPE_TEST_VALUES[6]),
            .styledValue = {
                .selector = 12, // Ark_BackgroundColorStyle
                .value12 = {
                    .textBackgroundStyle = {
                        .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(TEST_BGCL_COLOR)),
                        .radius = Converter::ArkUnion<Opt_Union_Dimension_BorderRadiuses, Ark_Length>(std::get<1>(TEST_BGCL_RADIUS))
                    }
                }
            }
        },
        Ark_StyleOptions {
            .start = Converter::ArkValue<Opt_Number>(TEST_START_URL),
            .length = Converter::ArkValue<Opt_Number>(TEST_LENGTH),
            .styledKey = Converter::ArkValue<Ark_StyledStringKey>(SPAN_TYPE_TEST_VALUES[7]),
            .styledValue = {
                .selector = 9, // Ark_UrlStyle
                .value9 = {
                    .url= Converter::ArkValue<Ark_String>(TEST_URL)
                }
            }
        },
        Ark_StyleOptions {
            .start = Converter::ArkValue<Opt_Number>(TEST_START_PSST),
            .length = Converter::ArkValue<Opt_Number>(TEST_LENGTH),
            .styledKey = Converter::ArkValue<Ark_StyledStringKey>(SPAN_TYPE_TEST_VALUES[8]),
            .styledValue = {
                .selector = 7, // Ark_ParagraphStyle
                .value7 = {
                    .textAlign = Converter::ArkValue<Opt_TextAlign>(std::get<1>(TEST_PSST_TEXT_ALIGN)),
                    .textIndent = Converter::ArkValue<Opt_Number>(TEST_PSST_TEXT_INDEN),
                    .maxLines = Converter::ArkValue<Opt_Number>(TEST_PSST_MAX_LINES),
                    .overflow = Converter::ArkValue<Opt_TextOverflow>(std::get<1>(TEST_PSST_OVERFLOW)),
                    .wordBreak = Converter::ArkValue<Opt_WordBreak>(std::get<1>(TEST_PSST_WORD_BREAK)),
                    .leadingMargin = Converter::ArkUnion<
                        Opt_Union_Number_LeadingMarginPlaceholder, Ark_Number>(std::get<1>(TEST_PSST_LEADING_MARGIN)),
                }
            }
        }
    };
    Converter::ArkArrayHolder<Array_StyleOptions> holderStyles(testArrayStyles);
}

using namespace testing;
using namespace testing::ext;

struct StyledStringUnionNull {
    Ark_Union_String_ImageAttachment_CustomSpan* Union() { return nullptr; }
    Opt_Array_StyleOptions* Styles() { return nullptr; }
};
struct StyledStringUnionString {
    Ark_Union_String_ImageAttachment_CustomSpan value = Converter::ArkUnion<
            Ark_Union_String_ImageAttachment_CustomSpan, Ark_String>(STRING_TEST_VALUE);
    Opt_Array_StyleOptions stylesOpt = holderStyles.OptValue<Opt_Array_StyleOptions>();

    Ark_Union_String_ImageAttachment_CustomSpan* Union()
    {
        return &value;
    }
    Opt_Array_StyleOptions* Styles()
    {
        return &stylesOpt;
    }
};

template <typename V1>
class StyledStringAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIStyledStringAccessor,
    &GENERATED_ArkUIAccessors::getStyledStringAccessor, StyledStringPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestCtorBase::SetUp();
    }

    StyledStringPeer* CreatePeerInstance() override
    {
        auto value = settings.Union();
        auto styles = settings.Styles();
        return accessor_->ctor(value, styles);
    }

private:
    V1 settings;
};

using StyledStringAccessorUnionNullTest = StyledStringAccessorTest<StyledStringUnionNull>;
using StyledStringAccessorUnionStringTest = StyledStringAccessorTest<StyledStringUnionString>;

/**
 * @tc.name: peerSuccessed
 * @tc.desc: peer successed
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionNullTest, peerSuccessed, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
}

/**
 * @tc.name:styledStringCtorText
 * @tc.desc: Union string is casted
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionStringTest, styledStringCtorText, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetString(), STRING_TEST_VALUE);
}

/**
 * @tc.name:styledStringCtorSpansOn
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionStringTest, styledStringCtorSpansOn, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);
    auto spansStr = peer_->spanString->GetSpans(TEST_START_STR, TEST_LENGTH);
    EXPECT_EQ(spansStr.size(), 1);
    auto spansDcrn = peer_->spanString->GetSpans(TEST_START_DCRN, TEST_LENGTH);
    EXPECT_EQ(spansDcrn.size(), 1);
    auto spansBsl = peer_->spanString->GetSpans(TEST_START_BSL, TEST_LENGTH);
    EXPECT_EQ(spansBsl.size(), 1);
    auto spansLsp = peer_->spanString->GetSpans(TEST_START_LSP, TEST_LENGTH);
    EXPECT_EQ(spansLsp.size(), 1);
    auto spansShadow = peer_->spanString->GetSpans(TEST_START_TSH, TEST_LENGTH);
    EXPECT_EQ(spansShadow.size(), 1);
    auto spansLineHeight = peer_->spanString->GetSpans(TEST_START_LNHT, TEST_LENGTH);
    EXPECT_EQ(spansLineHeight.size(), 1);
    auto spansBackgroundColor = peer_->spanString->GetSpans(TEST_START_BGCL, TEST_LENGTH);
    EXPECT_EQ(spansBackgroundColor.size(), 1);
    auto spansUrl = peer_->spanString->GetSpans(TEST_START_URL, TEST_LENGTH);
    EXPECT_EQ(spansUrl.size(), 1);
    auto paragraphSpan = peer_->spanString->GetSpans(TEST_START_PSST, TEST_LENGTH);
    EXPECT_EQ(paragraphSpan.size(), 1);
}

/**
 * @tc.name:styledStringCtorSpansFont
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionStringTest, styledStringCtorSpansFont, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);

    auto spans = peer_->spanString->GetSpans(TEST_START_STR, TEST_LENGTH);
    EXPECT_EQ(spans.size(), 1);
    auto spanFont = AceType::DynamicCast<FontSpan>(spans[0]);
    EXPECT_NE(spanFont, nullptr);
    Font font = spanFont->GetFont();
    EXPECT_EQ(font.GetFontColor(), std::get<0>(TEST_FONT_COLOR));
    EXPECT_EQ(font.GetFontFamily(), TEST_FONT_FAMILIES[0]);
    EXPECT_TRUE(font.GetFontSize().has_value());
    if (font.GetFontSize().has_value()) {
        EXPECT_EQ(font.GetFontSize()->ToString(), std::get<0>(TEST_FONT_SIZE));
    }
    EXPECT_TRUE(font.GetFontStyle().has_value());
    if (font.GetFontStyle().has_value()) {
        EXPECT_EQ(font.GetFontStyle().value(), TEST_FONT_STYLE);
    }
    EXPECT_TRUE(font.GetFontWeight().has_value());
    if (font.GetFontWeight().has_value()) {
        EXPECT_EQ(font.GetFontWeight().value(), std::get<0>(TEST_FONT_WEIGHT));
    }

}

/**
 * @tc.name:styledStringCtorDecorationSpan
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionStringTest, styledStringCtorDecorationSpan, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);

    auto spans = peer_->spanString->GetSpans(TEST_START_DCRN, TEST_LENGTH);
    EXPECT_EQ(spans.size(), 1);
    auto decorationSpan = AceType::DynamicCast<DecorationSpan>(spans[0]);
    EXPECT_NE(decorationSpan, nullptr);
    EXPECT_EQ(decorationSpan->GetTextDecorationType(), TEST_DCRN_TYPE);
    EXPECT_TRUE(decorationSpan->GetColor().has_value());
    if (decorationSpan->GetColor()) {
        EXPECT_EQ(decorationSpan->GetColor()->ToString(), std::get<0>(TEST_DCRN_COLOR));
    }
    EXPECT_TRUE(decorationSpan->GetTextDecorationStyle().has_value());
    if (decorationSpan->GetTextDecorationStyle()) {
        EXPECT_EQ(decorationSpan->GetTextDecorationStyle().value(), TEST_DCRN_STYLE);
    }
}

/**
 * @tc.name:styledStringCtorBaselineOffsetSpan
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionStringTest, styledStringCtorBaselineOffsetSpan, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);

    auto spans = peer_->spanString->GetSpans(TEST_START_BSL, TEST_LENGTH);
    EXPECT_EQ(spans.size(), 1);
    auto baselineSpan = AceType::DynamicCast<BaselineOffsetSpan>(spans[0]);
    EXPECT_NE(baselineSpan, nullptr);
    EXPECT_EQ(baselineSpan->GetBaselineOffset().ToString(), std::get<0>(TEST_BASELINE_OFFSET));

}

/**
 * @tc.name:styledStringCtorLetterSpacing
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionStringTest, styledStringCtorLetterSpacing, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);

    auto spans = peer_->spanString->GetSpans(TEST_START_LSP, TEST_LENGTH);
    EXPECT_EQ(spans.size(), 1);
    auto letterSpacingSpan = AceType::DynamicCast<LetterSpacingSpan>(spans[0]);
    EXPECT_NE(letterSpacingSpan, nullptr);
    EXPECT_EQ(letterSpacingSpan->GetLetterSpacing().ToString(), std::get<0>(TEST_LETTER_SPACING));
}

/**
 * @tc.name:styledStringCtorTextShadow
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionStringTest, styledStringCtorTextShadow, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);

    auto spans = peer_->spanString->GetSpans(TEST_START_TSH, TEST_LENGTH);
    EXPECT_EQ(spans.size(), 1);
    auto spansShadow = AceType::DynamicCast<TextShadowSpan>(spans[0]);
    EXPECT_NE(spansShadow, nullptr);
    auto shadows = spansShadow->GetTextShadow();
    EXPECT_EQ(shadows.size(), 1);
    Ace::Shadow shadow = shadows[0];
    EXPECT_EQ(shadow.GetShadowType(), std::get<0>(TEST_TEXT_SHADOW_TYPE));
    EXPECT_EQ(shadow.GetColor().ToString(), std::get<0>(TEST_TEXT_SHADOW_COLOR));
    EXPECT_EQ(shadow.GetBlurRadius(), TEST_TEXT_SHADOW_RADIUS);
    EXPECT_EQ(shadow.GetOffset().GetX(), TEST_TEXT_SHADOW_OFFSET);
    EXPECT_EQ(shadow.GetOffset().GetY(), TEST_TEXT_SHADOW_OFFSET);
}

/**
 * @tc.name:styledStringCtorLineHeight
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionStringTest, styledStringCtorLineHeight, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);

    auto spans = peer_->spanString->GetSpans(TEST_START_LNHT, TEST_LENGTH);
    EXPECT_EQ(spans.size(), 1);
    auto lineHeight = AceType::DynamicCast<LineHeightSpan>(spans[0]);
    EXPECT_NE(lineHeight, nullptr);
    EXPECT_EQ(lineHeight->GetLineHeight().ToString(), std::get<0>(TEST_LINE_HEIGHT));
}

/**
 * @tc.name:styledStringCtorBackgroundColor
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionStringTest, styledStringCtorBackgroundColor, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);

    auto spans = peer_->spanString->GetSpans(TEST_START_BGCL, TEST_LENGTH);
    EXPECT_EQ(spans.size(), 1);
    auto backgroundColor = AceType::DynamicCast<BackgroundColorSpan>(spans[0]);
    EXPECT_NE(backgroundColor, nullptr);
    TextBackgroundStyle style = backgroundColor->GetBackgroundColor();
    EXPECT_TRUE(style.backgroundColor.has_value());
    if (style.backgroundColor.has_value()) {
        EXPECT_EQ(style.backgroundColor.value().ToString(), std::get<0>(TEST_BGCL_COLOR));
    }
    EXPECT_TRUE(style.backgroundRadius.has_value());
    if (style.backgroundRadius.has_value()) {
        EXPECT_TRUE(style.backgroundRadius->radiusTopLeft.has_value());
        if (auto radius = style.backgroundRadius->radiusTopLeft; radius) {
            EXPECT_EQ(radius->ToString(), std::get<0>(TEST_BGCL_RADIUS));
        }
        EXPECT_TRUE(style.backgroundRadius->radiusTopRight.has_value());
        if (auto radius = style.backgroundRadius->radiusTopRight; radius) {
            EXPECT_EQ(radius->ToString(), std::get<0>(TEST_BGCL_RADIUS));
        }
        EXPECT_TRUE(style.backgroundRadius->radiusBottomLeft.has_value());
        if (auto radius = style.backgroundRadius->radiusBottomLeft; radius) {
            EXPECT_EQ(radius->ToString(), std::get<0>(TEST_BGCL_RADIUS));
        }
        EXPECT_TRUE(style.backgroundRadius->radiusBottomRight.has_value());
        if (auto radius = style.backgroundRadius->radiusBottomRight; radius) {
            EXPECT_EQ(radius->ToString(), std::get<0>(TEST_BGCL_RADIUS));
        }
    }
}

/**
 * @tc.name:styledStringCtorUrl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionStringTest, styledStringCtorUrl, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);

    auto spans = peer_->spanString->GetSpans(TEST_START_URL, TEST_LENGTH);
    EXPECT_EQ(spans.size(), 1);
    auto urlSpan = AceType::DynamicCast<UrlSpan>(spans[0]);
    EXPECT_NE(urlSpan, nullptr);
    EXPECT_EQ(urlSpan->GetUrlSpanAddress(), TEST_URL);
}

/**
 * @tc.name:DISABLED_styledStringCtorGesture
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionStringTest, DISABLED_styledStringCtorGesture, TestSize.Level1)
{
    // not implement
}

/**
 * @tc.name:styledStringCtorParagraphStyle
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionStringTest, styledStringCtorParagraphStyle, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);

    auto spans = peer_->spanString->GetSpans(TEST_START_PSST, TEST_LENGTH);
    EXPECT_EQ(spans.size(), 1);
    auto paragraphSpan = AceType::DynamicCast<ParagraphStyleSpan>(spans[0]);
    EXPECT_NE(paragraphSpan, nullptr);
    SpanParagraphStyle style = paragraphSpan->GetParagraphStyle();
    EXPECT_TRUE(style.align.has_value());
    if (style.align.has_value()) {
        EXPECT_EQ(style.align.value(), std::get<0>(TEST_PSST_TEXT_ALIGN));
    }
    EXPECT_TRUE(style.maxLines.has_value());
    if (style.maxLines.has_value()) {
        EXPECT_EQ(style.maxLines.value(), TEST_PSST_MAX_LINES);
    }
    EXPECT_TRUE(style.wordBreak.has_value());
    if (style.wordBreak.has_value()) {
        EXPECT_EQ(style.wordBreak.value(), std::get<0>(TEST_PSST_WORD_BREAK));
    }
    EXPECT_TRUE(style.textOverflow.has_value());
    if (style.textOverflow.has_value()) {
        EXPECT_EQ(style.textOverflow.value(), std::get<0>(TEST_PSST_OVERFLOW));
    }
    EXPECT_TRUE(style.leadingMargin.has_value());
    if (style.leadingMargin.has_value()) {
        auto size = style.leadingMargin.value().size;
        EXPECT_EQ(size.ToString(), std::get<0>(TEST_PSST_LEADING_MARGIN));
    }
}

/**
 * @tc.name:DISABLED_styledStringCtorParagraphStylePixelMap
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionStringTest, DISABLED_styledStringCtorParagraphStylePixelMap, TestSize.Level1)
{
    // not implement PixelMap for leadingMargin
}

/**
 * @tc.name:DISABLED_styledStringCtorExtSpan
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringAccessorUnionStringTest, DISABLED_styledStringCtorExtSpan, TestSize.Level1)
{
    // not implement
}
} // namespace OHOS::Ace::NG

