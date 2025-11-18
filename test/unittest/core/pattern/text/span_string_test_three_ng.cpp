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

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const double NUMBER_TEN = 10.0;
const double NUMBER_FIVE = 10.0;
std::string test_str[] = { "hello", "world", "this", "find", "gank", "pink", "that", "when", "how", "cpp" };
Font testFont1 { OHOS::Ace::FontWeight::BOLD, Dimension(29.0, DimensionUnit::PX), OHOS::Ace::FontStyle::ITALIC,
    std::vector<std::string>(test_str, test_str + 10), OHOS::Ace::Color::RED };
Font testFont2 { OHOS::Ace::FontWeight::LIGHTER, Dimension(19.0, DimensionUnit::PX), OHOS::Ace::FontStyle::ITALIC,
    std::vector<std::string>(test_str, test_str + 10), OHOS::Ace::Color::WHITE };
RefPtr<SpanBase> CreateSpan(int32_t start, int32_t end)
{
    return AceType::MakeRefPtr<FontSpan>(testFont1, start, end);
}
RefPtr<SpanBase> CreateSpan2(int32_t start, int32_t end)
{
    return AceType::MakeRefPtr<FontSpan>(testFont2, start, end);
}
} // namespace

class SpanStringTestThreeNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static ImageSpanOptions GetImageOption(const std::string& src);
    static ImageSpanOptions GetColorFilterImageOption(const std::string& src);
    static ImageSpanOptions GetImageOptionWithSize(const std::string& src);
};

void SpanStringTestThreeNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
}

void SpanStringTestThreeNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

ImageSpanOptions SpanStringTestThreeNg::GetImageOption(const std::string& src)
{
    ImageSpanSize size { .width = 50.0_vp, .height = 50.0_vp };
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(2.0_vp);
    MarginProperty margins;
    margins.SetEdges(CalcLength(NUMBER_TEN));
    PaddingProperty paddings;
    paddings.SetEdges(CalcLength(NUMBER_FIVE));
    ImageSpanAttribute attr { .paddingProp = paddings,
        .marginProp = margins,
        .borderRadius = borderRadius,
        .objectFit = ImageFit::COVER,
        .verticalAlign = VerticalAlign::BOTTOM };
    ImageSpanOptions option { .image = src, .imageAttribute = attr };
    return option;
}

ImageSpanOptions SpanStringTestThreeNg::GetImageOptionWithSize(const std::string& src)
{
    ImageSpanSize size { .width = 100.0_vp, .height = 100.0_vp };
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(2.0_vp);
    MarginProperty margins;
    margins.SetEdges(CalcLength(NUMBER_TEN));
    PaddingProperty paddings;
    paddings.SetEdges(CalcLength(NUMBER_FIVE));
    ImageSpanAttribute attr { .paddingProp = paddings,
        .marginProp = margins,
        .borderRadius = borderRadius,
        .objectFit = ImageFit::COVER,
        .verticalAlign = VerticalAlign::BOTTOM,
        .size = size };
    ImageSpanOptions option { .image = src, .imageAttribute = attr };
    return option;
}

ImageSpanOptions SpanStringTestThreeNg::GetColorFilterImageOption(const std::string& src)
{
    ImageSpanSize size { .width = 50.0_vp, .height = 50.0_vp };
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(2.0_vp);
    MarginProperty margins;
    margins.SetEdges(CalcLength(NUMBER_TEN));
    PaddingProperty paddings;
    paddings.SetEdges(CalcLength(NUMBER_FIVE));
    std::vector<float> colorFilterMat {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0};
    ImageSpanAttribute attr { .paddingProp = paddings,
        .marginProp = margins,
        .borderRadius = borderRadius,
        .objectFit = ImageFit::COVER,
        .verticalAlign = VerticalAlign::BOTTOM,
        .colorFilterMatrix = colorFilterMat };
    ImageSpanOptions option { .image = src, .imageAttribute = attr };
    return option;
}

/**
 * @tc.name: MutableSpanStringTest104
 * @tc.desc: Test CJK-Emoji mixed replacement
 */
HWTEST_F(SpanStringTestThreeNg, SpanString104, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"中文🔥测试");
    spanString->ReplaceString(1, 1, u"🇨🇳");
    EXPECT_EQ(spanString->GetU16string(), u"中🇨🇳🔥测试");
}

/**
 * @tc.name: MutableSpanStringTest105
 * @tc.desc: Verify 100KB insert operation
 */
HWTEST_F(SpanStringTestThreeNg, SpanString105, TestSize.Level1)
{
    std::u16string data(102400, 'A');
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(data);
    spanString->InsertString(51200, u"MID");
    EXPECT_EQ(spanString->GetU16string().substr(51200, 3), u"MID");
}

/**
 * @tc.name: MutableSpanStringTest106
 * @tc.desc: Test cross-span append
 */
HWTEST_F(SpanStringTestThreeNg, SpanString106, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Start");
    spanString->AddSpan(CreateSpan(0, 5));
    spanString->AppendSpanString(AceType::MakeRefPtr<MutableSpanString>(u"End"));
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).back()->GetStartIndex(), 0);
}

/**
 * @tc.name: MutableSpanStringTest107
 * @tc.desc: Verify surrogate pair removal
 */
HWTEST_F(SpanStringTestThreeNg, SpanString107, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"A𝄞B");
    spanString->RemoveString(1, 2);
    EXPECT_EQ(spanString->GetU16string(), u"AB");
}

/**
 * @tc.name: MutableSpanStringTest108
 * @tc.desc: Test hybrid Insert/Replace/Remove
 */
HWTEST_F(SpanStringTestThreeNg, SpanString108, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"Base");
    target->InsertString(2, u"X");
    target->ReplaceString(1, 3, u"Y");
    target->RemoveString(0, 1);
    EXPECT_EQ(target->GetU16string(), u"Ye");
}

/**
 * @tc.name: MutableSpanStringTest109
 * @tc.desc: Verify 50 consecutive appends
 */
HWTEST_F(SpanStringTestThreeNg, SpanString109, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"");
    for (int i = 0;i < 50;i++) {
        spanString->AppendSpanString(AceType::MakeRefPtr<MutableSpanString>(u"X"));
    }
    EXPECT_EQ(spanString->GetU16string().length(), 50);
}

/**
 * @tc.name: MutableSpanStringTest110
 * @tc.desc: Test boundary replacement with span
 */
HWTEST_F(SpanStringTestThreeNg, SpanString110, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"EdgeCase");
    spanString->AddSpan(CreateSpan(0, 8));
    spanString->ReplaceString(7, 1, u"!");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 8);
}

/**
 * @tc.name: MutableSpanStringTest112
 * @tc.desc: Verify multi-byte span replacement
 */
HWTEST_F(SpanStringTestThreeNg, SpanString112, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"测试");
    spanString->AddSpan(CreateSpan(0, 2));
    spanString->ReplaceString(1, 1, u"试");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 2);
}

/**
 * @tc.name: MutableSpanStringTest113
 * @tc.desc: Test 1000x Insert/Replace cycle
 */
HWTEST_F(SpanStringTestThreeNg, SpanString113, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"");
    for (int i = 0;i < 1000;i++) {
        i%2 ? target->InsertString(0, u"X") : target->ReplaceString(0, 1, u"Y");
    }
    EXPECT_FALSE(target->GetU16string().empty());
}

/**
 * @tc.name: MutableSpanStringTest114
 * @tc.desc: Verify cross-span append
 */
HWTEST_F(SpanStringTestThreeNg, SpanString114, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"AB-CD");
    spanString->AddSpan(CreateSpan(0, 2));
    spanString->AddSpan(CreateSpan2(3, 5));
    spanString->AppendSpanString(AceType::MakeRefPtr<MutableSpanString>(u"EF"));
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).back()->GetStartIndex(), 3);
}

/**
 * @tc.name: MutableSpanStringTest115
 * @tc.desc: Test surrogate pair boundary
 */
HWTEST_F(SpanStringTestThreeNg, SpanString115, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"𝄞𝄞");
    spanString->ReplaceString(2, 2, u"X");
    EXPECT_EQ(spanString->GetU16string(), u"𝄞X");
}

/**
 * @tc.name: MutableSpanStringTest116
 * @tc.desc: Verify full text removal
 */
HWTEST_F(SpanStringTestThreeNg, SpanString116, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Content");
    spanString->RemoveString(0, 7);
    EXPECT_TRUE(spanString->GetU16string().empty());
    EXPECT_TRUE(spanString->GetSpans(0, spanString->GetLength()).empty());
}

/**
 * @tc.name: MutableSpanStringTest117
 * @tc.desc: Test hybrid CJK-Emoji span
 */
HWTEST_F(SpanStringTestThreeNg, SpanString117, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"日🔥本");
    spanString->AddSpan(CreateSpan(0, 3));
    spanString->InsertString(1, u"🇯🇵");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 7);
}

/**
 * @tc.name: MutableSpanStringTest118
 * @tc.desc: Verify 1MB append operation
 */
HWTEST_F(SpanStringTestThreeNg, SpanString118, TestSize.Level1)
{
    std::u16string data(1048576, 'A');
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(data);
    spanString->AppendSpanString(AceType::MakeRefPtr<MutableSpanString>(u"END"));
    EXPECT_EQ(spanString->GetU16string().substr(1048576, 3), u"END");
}

/**
 * @tc.name: MutableSpanStringTest119
 * @tc.desc: Test multi-span merge
 */
HWTEST_F(SpanStringTestThreeNg, SpanString119, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"AABBCC");
    spanString->AddSpan(CreateSpan(0, 2));
    spanString->AddSpan(CreateSpan2(2, 4));
    spanString->ReplaceString(1, 3, u"X");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).size(), 1);
}

/**
 * @tc.name: MutableSpanStringTest121
 * @tc.desc: Verify cross-span replacement with merging
 */
HWTEST_F(SpanStringTestThreeNg, SpanString121, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"AABBCC");
    spanString->AddSpan(CreateSpan(0, 2));
    spanString->AddSpan(CreateSpan2(2, 4));
    spanString->ReplaceString(1, 3, u"XYZ");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).size(), 1);
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 4);
}

/**
 * @tc.name: MutableSpanStringTest123
 * @tc.desc: Verify 2MB text handling
 */
HWTEST_F(SpanStringTestThreeNg, SpanString123, TestSize.Level1)
{
    std::u16string data(2097152, 'X');
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(data);
    spanString->ReplaceString(1048576, 10, u"MID");
    EXPECT_EQ(spanString->GetU16string().substr(1048576, 3), u"MID");
}

/**
 * @tc.name: MutableSpanStringTest124
 * @tc.desc: Test boundary InsertSpanString
 */
HWTEST_F(SpanStringTestThreeNg, SpanString124, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Edge");
    spanString->InsertSpanString(4, AceType::MakeRefPtr<MutableSpanString>(u"Case"));
    EXPECT_EQ(spanString->GetU16string(), u"EdgeCase");
}

/**
 * @tc.name: MutableSpanStringTest125
 * @tc.desc: Verify 100x ReplaceString chain
 */
HWTEST_F(SpanStringTestThreeNg, SpanString125, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"Base");
    for (int i = 0;i < 100;i++) {
        target->ReplaceString(i%3, 1, u"X");
    }
    EXPECT_FALSE(target->GetU16string().empty());
}

/**
 * @tc.name: MutableSpanStringTest126
 * @tc.desc: Test CJK-Emoji-Latin mixed spans
 */
HWTEST_F(SpanStringTestThreeNg, SpanString126, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"中🔥A");
    spanString->AddSpan(CreateSpan(0, 3));
    spanString->ReplaceString(1, 2, u"🇨🇳");
    EXPECT_EQ(spanString->GetU16string(), u"中🇨🇳A");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 5);
}

/**
 * @tc.name: MutableSpanStringTest127
 * @tc.desc: Verify zero-length operations
 */
HWTEST_F(SpanStringTestThreeNg, SpanString127, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Stable");
    spanString->ReplaceString(3, 0, u"");
    EXPECT_EQ(spanString->GetU16string(), u"Stable");
    EXPECT_TRUE(spanString->GetSpans(0, spanString->GetLength()).empty());
}

/**
 * @tc.name: MutableSpanStringTest128
 * @tc.desc: Test multi-span append
 */
HWTEST_F(SpanStringTestThreeNg, SpanString128, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"AB|CD");
    spanString->AddSpan(CreateSpan(0, 2));
    spanString->AddSpan(CreateSpan2(3, 5));
    spanString->AppendSpanString(AceType::MakeRefPtr<MutableSpanString>(u"EF"));
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).back()->GetStartIndex(), 3);
}

/**
 * @tc.name: MutableSpanStringTest129
 * @tc.desc: Verify surrogate pair boundary
 */
HWTEST_F(SpanStringTestThreeNg, SpanString129, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"𝄞𝄞");
    spanString->InsertString(2, u"X");
    EXPECT_EQ(spanString->GetU16string(), u"𝄞X𝄞");
}

/**
 * @tc.name: MultiTypeDecorationSpanStringTest
 * @tc.desc: Verify multi type decoration span string
 */
HWTEST_F(SpanStringTestThreeNg, MultiTypeDecorationSpanStringTest, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"1234567890");

    std::optional<TextDecorationOptions> optionsTrue({true});
    std::optional<TextDecorationOptions> optionsFalse({false});
    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
            std::vector<TextDecoration>({TextDecoration::OVERLINE}),
            Color::RED, TextDecorationStyle::WAVY, optionsTrue, 0, 3, nullptr));
    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
            std::vector<TextDecoration>({TextDecoration::LINE_THROUGH}),
            Color::RED, TextDecorationStyle::WAVY, optionsTrue, 0, 3, nullptr));
    auto subspan1 = spanString->GetSpan(0, 3, SpanType::Decoration);
    auto subDecorationSpan1 = AceType::DynamicCast<DecorationSpan>(subspan1);
    ASSERT_NE(subDecorationSpan1, nullptr);
    auto decorationTypes1 = subDecorationSpan1->GetTextDecorationTypes();
    EXPECT_EQ(subDecorationSpan1->GetTextDecorationFirst(), TextDecoration::LINE_THROUGH);
    EXPECT_EQ(decorationTypes1.size(), 2);

    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
        std::vector<TextDecoration>({TextDecoration::OVERLINE}),
        Color::RED, TextDecorationStyle::WAVY, optionsTrue, 4, 6, nullptr));
    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
            std::vector<TextDecoration>({TextDecoration::LINE_THROUGH}),
            Color::RED, TextDecorationStyle::WAVY, optionsFalse, 4, 6, nullptr));
    auto subspan2 = spanString->GetSpan(4, 2, SpanType::Decoration);
    auto subDecorationSpan2 = AceType::DynamicCast<DecorationSpan>(subspan2);
    ASSERT_NE(subDecorationSpan2, nullptr);
    auto decorationTypes2 = subDecorationSpan2->GetTextDecorationTypes();
    EXPECT_EQ(subDecorationSpan2->GetTextDecorationFirst(), TextDecoration::LINE_THROUGH);
    EXPECT_EQ(decorationTypes2.size(), 1);

    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
        std::vector<TextDecoration>({TextDecoration::OVERLINE}),
        Color::RED, TextDecorationStyle::WAVY, optionsFalse, 7, 9, nullptr));
    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
            std::vector<TextDecoration>({TextDecoration::LINE_THROUGH}),
            Color::RED, TextDecorationStyle::WAVY, optionsFalse, 7, 9, nullptr));
    auto subspan3 = spanString->GetSpan(7, 2, SpanType::Decoration);
    auto subDecorationSpan3 = AceType::DynamicCast<DecorationSpan>(subspan3);
    ASSERT_NE(subDecorationSpan3, nullptr);
    auto decorationTypes3 = subDecorationSpan3->GetTextDecorationTypes();
    EXPECT_EQ(subDecorationSpan3->GetTextDecorationFirst(), TextDecoration::LINE_THROUGH);
    EXPECT_EQ(decorationTypes3.size(), 1);
    EXPECT_EQ(spanString->GetU16string(), u"1234567890");
}

/**
 * @tc.name: SpanString014
 * @tc.desc: Test append spanstring after BackgroundColorSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString014, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"1234567890");
    auto appendString = AceType::MakeRefPtr<MutableSpanString>(u"abc");

    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);

    textBackgroundStyle.backgroundColor = Color::RED;;
    textBackgroundStyle.backgroundRadius = borderRadius;

    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 0, 10));
    // append span string
    spanString->AppendSpanString(appendString);

    // check range
    auto backgroundSpans = spanString->GetSpans(0, 13);
    EXPECT_EQ(backgroundSpans.size(), 1);
    auto firstBackgroundSpan = AceType::DynamicCast<BackgroundColorSpan>(backgroundSpans[0]);
    EXPECT_NE(firstBackgroundSpan, nullptr);
    EXPECT_EQ(firstBackgroundSpan->GetStartIndex(), 0);
    EXPECT_EQ(firstBackgroundSpan->GetEndIndex(), 10);
    EXPECT_TRUE(firstBackgroundSpan->GetBackgroundColor() == textBackgroundStyle);
}

/**
 * @tc.name: SpanString015
 * @tc.desc: Test insert string between BackgroundColorSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString015, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"1234567890");

    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);

    textBackgroundStyle.backgroundColor = Color::BLUE;;
    textBackgroundStyle.backgroundRadius = borderRadius;
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 0, 5));

    // insert value
    spanString->InsertString(2, u"abc");

    // check range of span
    auto backgroundSpans = spanString->GetSpans(0, 10);
    EXPECT_EQ(backgroundSpans.size(), 1);
    auto backgroundSpan = AceType::DynamicCast<BackgroundColorSpan>(backgroundSpans[0]);
    EXPECT_NE(backgroundSpan, nullptr);
    EXPECT_EQ(backgroundSpan->GetStartIndex(), 0);
    EXPECT_EQ(backgroundSpan->GetEndIndex(), 8);
    EXPECT_TRUE(backgroundSpan->GetBackgroundColor() == textBackgroundStyle);
}

/**
 * @tc.name: SpanString016
 * @tc.desc: Test remove string between BackgroundColorSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString016, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"1234567890");

    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);

    textBackgroundStyle.backgroundColor = Color::BLUE;;
    textBackgroundStyle.backgroundRadius = borderRadius;

    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 0, 5));
    // remove string
    spanString->RemoveString(2, 1);

    // check range of span
    auto backgroundSpans = spanString->GetSpans(0, 7);
    EXPECT_EQ(backgroundSpans.size(), 1);
    auto backgroundSpan = AceType::DynamicCast<BackgroundColorSpan>(backgroundSpans[0]);
    EXPECT_NE(backgroundSpan, nullptr);
    EXPECT_EQ(backgroundSpan->GetStartIndex(), 0);
    EXPECT_EQ(backgroundSpan->GetEndIndex(), 4);
    EXPECT_TRUE(backgroundSpan->GetBackgroundColor() == textBackgroundStyle);

    // remove multi times
    spanString->RemoveString(2, 2);
    backgroundSpans = spanString->GetSpans(0, 7);
    EXPECT_EQ(backgroundSpans.size(), 1);
    backgroundSpan = AceType::DynamicCast<BackgroundColorSpan>(backgroundSpans[0]);
    EXPECT_NE(backgroundSpan, nullptr);
    EXPECT_EQ(backgroundSpan->GetStartIndex(), 0);
    EXPECT_EQ(backgroundSpan->GetEndIndex(), 2);
    EXPECT_TRUE(backgroundSpan->GetBackgroundColor() == textBackgroundStyle);
}

/**
 * @tc.name: SpanString017
 * @tc.desc: Test remove span of BackgroundColorSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString017, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"1234567890");

    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);

    textBackgroundStyle.backgroundColor = Color::BLUE;;
    textBackgroundStyle.backgroundRadius = borderRadius;

    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 0, 5));
    // remove string
    spanString->RemoveSpan(0, 5, SpanType::BackgroundColor);

    // check span count
    auto backgroundSpans = spanString->GetSpans(0, 10);
    EXPECT_EQ(backgroundSpans.size(), 0);

    // add again
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 0, 5));
    backgroundSpans = spanString->GetSpans(0, 10);
    EXPECT_EQ(backgroundSpans.size(), 1);

    auto backgroundSpan = AceType::DynamicCast<BackgroundColorSpan>(backgroundSpans[0]);
    EXPECT_NE(backgroundSpan, nullptr);
    EXPECT_EQ(backgroundSpan->GetStartIndex(), 0);
    EXPECT_EQ(backgroundSpan->GetEndIndex(), 5);
}

/**
 * @tc.name: SpanString018
 * @tc.desc: Test remove span of BackgroundColorSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString018, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"1234567890");

    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);

    textBackgroundStyle.backgroundColor = Color::BLUE;;
    textBackgroundStyle.backgroundRadius = borderRadius;

    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 0, 5));
    // remove string
    spanString->RemoveSpan(0, 5, SpanType::BackgroundColor);

    // check span count
    auto spans = spanString->GetSpans(0, 10);
    EXPECT_EQ(spans.size(), 0);

    // add again
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 0, 5));
    spans = spanString->GetSpans(0, 10);
    EXPECT_EQ(spans.size(), 1);

    auto backgroundSpan = AceType::DynamicCast<BackgroundColorSpan>(spans[0]);
    EXPECT_NE(backgroundSpan, nullptr);
    EXPECT_EQ(backgroundSpan->GetStartIndex(), 0);
    EXPECT_EQ(backgroundSpan->GetEndIndex(), 5);

    // remove all spans
    spanString->ClearAllSpans();
    spans = spanString->GetSpans(0, 10);
    EXPECT_EQ(spans.size(), 0);
}

/**
 * @tc.name: SpanStringTest019
 * @tc.desc: Test basic function of ImageAttachment setting color filter
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString019, TestSize.Level1)
{
    auto imageOption = SpanStringTestThreeNg::GetColorFilterImageOption("src/icon-1.png");
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);
    auto imageSpan = AceType::MakeRefPtr<ImageSpan>(imageOption);
    EXPECT_EQ(imageSpan->GetImageSpanOptions().imageAttribute, imageOption.imageAttribute);
    mutableStr->InsertString(0, u"123");
    mutableStr->InsertString(4, u"456");
    auto imageOption1 = SpanStringTestThreeNg::GetColorFilterImageOption("src/icon-2.png");
    auto imageSpan1 = AceType::MakeRefPtr<SpanString>(imageOption1);
    mutableStr->AppendSpanString(imageSpan1);
    auto customSpan = AceType::MakeRefPtr<CustomSpan>();
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(customSpan);
    spanString->AppendSpanString(mutableStr);
    auto spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans.size(), 3);
    spanString->AppendSpanString(spanString);
    spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans.size(), 6);
}

/**
 * @tc.name: SpanStringTest035
 * @tc.desc: Test basic properties of ImageAttachment
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString035, TestSize.Level1)
{
    auto customSpan = AceType::MakeRefPtr<CustomSpan>();
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(customSpan);
    auto imageOption = SpanStringTestThreeNg::GetImageOptionWithSize("src/icon-1.png");
    auto imageSpan = AceType::MakeRefPtr<SpanString>(imageOption);
    spanString->AppendSpanString(imageSpan);
    auto imageSpans = spanString->GetSpans(0, spanString->GetLength(), SpanType::Image);
    EXPECT_EQ(imageSpans.size(), 1);
    auto imageSpanInList = AceType::DynamicCast<ImageSpan>(imageSpans.front());
    ImageSpanAttribute imageAttribute = imageSpanInList->GetImageAttribute().value();
    ImageSpanSize imageSize = imageAttribute.size.value();
    EXPECT_EQ(imageSize.width->ConvertToVp(), 100.0);
    EXPECT_EQ(imageSize.height->ConvertToVp(), 100.0);
}

/*
 * @tc.name: SpanStringTest020
 * @tc.desc: Test InsertString method adjusts span positions correctly
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString020, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    textBackgroundStyle.backgroundColor = Color::RED;
    textBackgroundStyle.backgroundRadius = borderRadius;

    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 7, 9));
    spanString->InsertString(3, u"ab"); // 在位置3插入2字符
    
    auto spans = spanString->GetSpans(9, 2); // 原span范围7-9变为7-11
    EXPECT_EQ(spans.size(), 1);
    if (!spans.empty()) {
        auto span = AceType::DynamicCast<BackgroundColorSpan>(spans.front());
        EXPECT_NE(span, nullptr);
        EXPECT_EQ(span->GetStartIndex(), 9);  // 7 + 2 = 9
        EXPECT_EQ(span->GetEndIndex(), 11);   // 9 + 2 = 11
    }
}

/**
 * @tc.name: SpanStringTest021
 * @tc.desc: Test RemoveString shortens span positions
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString021, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    TextBackgroundStyle textBackgroundStyle;
    textBackgroundStyle.backgroundColor = Color::BLUE;
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 3, 7));
    
    spanString->RemoveString(5, 2); // 删除位置5的两个字符
    
    auto spans = spanString->GetSpans(3, 2); // 原3-7变为3-5
    EXPECT_EQ(spans.size(), 1);
    if (!spans.empty()) {
        EXPECT_EQ(spans.front()->GetEndIndex(), 5);
    }
}

/**
 * @tc.name: SpanStringTest022
 * @tc.desc: Test ReplaceSpan replaces existing span
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString022, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    TextBackgroundStyle oldStyle;
    oldStyle.backgroundColor = Color::GRAY;
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(oldStyle, 2, 5));

    TextBackgroundStyle newStyle;
    newStyle.backgroundColor = Color::GREEN;
    auto newSpan = AceType::MakeRefPtr<BackgroundColorSpan>(newStyle, 2, 5);
    
    spanString->ReplaceSpan(2, 3, newSpan); // 替换2-5范围的span
    
    auto spans = spanString->GetSpans(2, 3);
    EXPECT_EQ(spans.size(), 1);
    EXPECT_EQ(AceType::DynamicCast<BackgroundColorSpan>(spans.front())->GetBackgroundColor().backgroundColor.value(),
        Color::GREEN);
}

/**
 * @tc.name: SpanStringTest023
 * @tc.desc: Test RemoveSpans removes spans in range
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString023, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    TextBackgroundStyle style;
    style.backgroundColor = Color::RED;
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(style, 1, 3));
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(style, 4, 6));
    
    spanString->RemoveSpans(2, 3, true); // 移除2-5区间
    
    EXPECT_EQ(spanString->GetSpans(1, 6).size(), 2); // 剩余2个span
}

/**
 * @tc.name: SpanStringTest024
 * @tc.desc: Test ClearAllSpans removes all spans
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString024, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    TextBackgroundStyle style;
    style.backgroundColor = Color::RED;
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(style, 0, 2));
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(style, 5, 8));
    
    spanString->ClearAllSpans();
    
    EXPECT_EQ(spanString->GetSpans(0, 10).size(), 0);
}

/**
 * @tc.name: SpanStringTest025
 * @tc.desc: Test ReplaceSpanString replaces text and spans
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString025, TestSize.Level1)
{
    auto original = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    TextBackgroundStyle originalStyle;
    originalStyle.backgroundColor = Color::BLACK;
    original->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(originalStyle, 2, 5));

    auto replacement = AceType::MakeRefPtr<MutableSpanString>(u"abc");
    TextBackgroundStyle newStyle;
    newStyle.backgroundColor = Color::WHITE;
    replacement->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(newStyle, 0, 3));
    
    original->ReplaceSpanString(3, 2, replacement); // 替换位置3的2字符为"abc"
    
    auto spans = original->GetSpans(3, 3); // 新插入的span应位于3-6
    EXPECT_EQ(spans.size(), 1);
    EXPECT_EQ(AceType::DynamicCast<BackgroundColorSpan>(spans.front())->GetBackgroundColor().backgroundColor.value(),
        Color::WHITE);
}

/**
 * @tc.name: SpanStringTest026
 * @tc.desc: Test InsertSpanString merges spans correctly
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString026, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"0123");
    auto source = AceType::MakeRefPtr<MutableSpanString>(u"abc");
    TextBackgroundStyle style;
    style.backgroundColor = Color::RED;
    source->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(style, 0, 3));
    
    target->InsertSpanString(2, source); // 在位置2插入"abc"
    
    auto spans = target->GetSpans(2, 3); // 检查插入的span是否在2-5
    EXPECT_EQ(spans.size(), 1);
    EXPECT_EQ(spans.front()->GetEndIndex(), 5);
}

/**
 * @tc.name: SpanStringTest027
 * @tc.desc: Test AppendSpanString adds to the end
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString027, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"start");
    auto source = AceType::MakeRefPtr<MutableSpanString>(u"end");
    TextBackgroundStyle style;
    style.backgroundColor = Color::TRANSPARENT;
    source->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(style, 0, 3));
    
    target->AppendSpanString(source);
    
    auto spans = target->GetSpans(5, 3); // 检查追加后的span在5-8
    EXPECT_EQ(spans.size(), 1);
    EXPECT_EQ(spans.front()->GetEndIndex(), 8);
}

/**
 * @tc.name: SpanStringTest028
 * @tc.desc: Test span adjustment when inserting at text beginning
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString028, TestSize.Level1)
{
    // 初始化10字符文本+span覆盖5-8区间
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    TextBackgroundStyle style;
    style.backgroundColor = Color::FromRGB(255, 0, 0);
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(style, 5, 8));

    // 在文本开头插入3个字符
    spanString->InsertString(0, u"ABC");
    
    // 验证span位置偏移
    auto spans = spanString->GetSpans(8, 3); // 原5-8应变为8-11
    EXPECT_EQ(spans.size(), 1);
    if (!spans.empty()) {
        auto span = AceType::DynamicCast<BackgroundColorSpan>(spans.front());
        EXPECT_EQ(span->GetStartIndex(), 8);
        EXPECT_EQ(span->GetEndIndex(), 11);
    }

    // 验证原始文本内容
    EXPECT_EQ(spanString->GetString(), "ABC0123456789");
}

/**
 * @tc.name: SpanStringTest029
 * @tc.desc: Test overlapping spans after multiple insertions
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString029, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"base text");
    
    // 添加三个重叠span
    TextBackgroundStyle redStyle, blueStyle, greenStyle;
    redStyle.backgroundColor = Color::RED;
    blueStyle.backgroundColor = Color::BLUE;
    greenStyle.backgroundColor = Color::GREEN;
    
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(redStyle, 2, 6));   // 覆盖2-6
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(blueStyle, 4, 8));  // 覆盖4-8
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(greenStyle, 0, 3)); // 覆盖0-3

    // 在位置5插入3个字符
    spanString->InsertString(5, u"XYZ");

    // 验证span位置调整
    auto spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans.size(), 3); // 应保持三个span

    auto frontSpan = AceType::DynamicCast<BackgroundColorSpan>(spans.front());
    EXPECT_EQ(frontSpan->GetStartIndex(), 0);
    EXPECT_EQ(frontSpan->GetEndIndex(), 3);
    

    auto midSpan = AceType::DynamicCast<BackgroundColorSpan>(*(std::next(spans.begin())));
    EXPECT_EQ(midSpan->GetStartIndex(), 3);
    EXPECT_EQ(midSpan->GetEndIndex(), 4);
    
    auto lastSpan = AceType::DynamicCast<BackgroundColorSpan>(spans.back());
    EXPECT_EQ(lastSpan->GetStartIndex(), 4);
    EXPECT_EQ(lastSpan->GetEndIndex(), 11);
}

/**
 * @tc.name: SpanStringTest030
 * @tc.desc: Test span removal with partial overlap
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString030, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"abcdefghijklmn");
    TextBackgroundStyle style;
    style.backgroundColor = Color::FromARGB(255, 100, 150, 200);
    
    // 添加两个相邻span
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(style, 3, 7));  // span1:3-7
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(style, 7, 10)); // span2:7-10

    // 删除6-9区间的字符（影响两个span）
    spanString->RemoveString(6, 3); // 删除位置6的3字符（字符6,7,8）
    
    // 验证span调整
    auto spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans.size(), 2);
    
    // span1调整后：3-6（原3-7，删除位置6导致结束变为6）
    auto firstSpan = AceType::DynamicCast<BackgroundColorSpan>(spans.front());
    EXPECT_EQ(firstSpan->GetStartIndex(), 3);
    EXPECT_EQ(firstSpan->GetEndIndex(), 6);
    
    // span2调整后：6-7（原7-10，删除3字符后位置变为7-3=4 → 7→4, 10→7）
    auto secondSpan = AceType::DynamicCast<BackgroundColorSpan>(spans.back());
    EXPECT_EQ(secondSpan->GetStartIndex(), 6); // 7 - (6 <= pos <9被删除)
    EXPECT_EQ(secondSpan->GetEndIndex(), 7);   // 10 - 3 =7
}

/**
 * @tc.name: SpanStringTest031
 * @tc.desc: Test complex span replacement scenarios
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString031, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Hello World");
    
    // 创建三种样式
    TextBackgroundStyle styleA, styleB, styleC;
    styleA.backgroundColor = Color(0xFFFF0000); // ARGB
    styleB.backgroundColor = Color(0xFF00FF00);
    styleC.backgroundColor = Color(0xFF0000FF);
    
    // 添加交错span
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(styleA, 0, 5));   // Hello
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(styleB, 3, 8));   // lo Wo
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(styleC, 6, 11));  // World

    // 替换4-6区间的文本为"XXX"（3字符）
    spanString->ReplaceString(4, 2, u"XXX");

    // 验证文本内容
    EXPECT_EQ(spanString->GetString(), "HellXXXWorld");
    
    // 验证span调整（总长度增加1）
    auto spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans.size(), 3);
    
    auto spanA = AceType::DynamicCast<BackgroundColorSpan>(spans.front());
    EXPECT_EQ(spanA->GetStartIndex(), 0);
    EXPECT_EQ(spanA->GetEndIndex(), 3);

    auto spanB = AceType::DynamicCast<BackgroundColorSpan>(*(std::next(spans.begin())));
    EXPECT_EQ(spanB->GetStartIndex(), 3);
    EXPECT_EQ(spanB->GetEndIndex(), 7);
    
    auto spanC = AceType::DynamicCast<BackgroundColorSpan>(spans.back());
    EXPECT_EQ(spanC->GetStartIndex(), 7);
    EXPECT_EQ(spanC->GetEndIndex(), 12);
}

/**
 * @tc.name: SpanStringTest032
 * @tc.desc: Test inserting at span start boundary
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString032, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"ABCDEFGHIJ");
    TextBackgroundStyle style;
    style.backgroundColor = Color::BLUE;
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(style, 3, 7));

    // 在span起始位置前插入2字符
    spanString->InsertString(3, u"XY");
    
    auto spans = spanString->GetSpans(5, 4); // 原3-7变为5-9
    EXPECT_EQ(spans.size(), 1);
    EXPECT_EQ(spans.front()->GetStartIndex(), 5);
    EXPECT_EQ(spans.front()->GetEndIndex(), 9);
}

/**
 * @tc.name: SpanStringTest033
 * @tc.desc: Test removing entire span coverage
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString033, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"1234567890");
    TextBackgroundStyle style;
    style.backgroundColor = Color::GREEN;
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(style, 2, 6));

    // 删除完全覆盖span的区域
    spanString->RemoveString(2, 4);
    
    auto spans = spanString->GetSpans(2, 4);
    EXPECT_TRUE(spans.empty());
}

/**
 * @tc.name: SpanStringTest034
 * @tc.desc: Test replacing span with larger range
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanString034, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"TestString");
    TextBackgroundStyle oldStyle, newStyle;
    oldStyle.backgroundColor = Color::RED;
    newStyle.backgroundColor = Color::BLUE;
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(oldStyle, 1, 4));

    // 替换span为更大范围
    auto newSpan = AceType::MakeRefPtr<BackgroundColorSpan>(newStyle, 0, 5);
    spanString->ReplaceSpan(1, 3, newSpan);
    
    auto spans = spanString->GetSpans(0, 5);
    EXPECT_EQ(spans.size(), 1);
    EXPECT_EQ(AceType::DynamicCast<BackgroundColorSpan>(spans.front())->GetBackgroundColor().backgroundColor.value(),
        Color::BLUE);
}

/**
 * @tc.name: Tlv001
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv001, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    std::vector<std::string> writeFontFamily = { "f1", "f2" };
    std::vector<uint8_t> result = { 0x25, 0x2, 0x20, 0x2, 0x66, 0x31, 0x20, 0x2, 0x66, 0x32 };
    TLVUtil::WriteFontFamily(buffer, writeFontFamily);
    EXPECT_TRUE(buffer == result);

    int32_t cursor = 0;
    std::vector<std::string> readFontFamily = TLVUtil::ReadFontFamily(buffer, cursor);
    EXPECT_TRUE(writeFontFamily == readFontFamily);
    buffer.clear();
    readFontFamily.clear();
    cursor = 0;
    readFontFamily = TLVUtil::ReadFontFamily(buffer, cursor);
    EXPECT_TRUE(readFontFamily.empty());
}

/**
 * @tc.name: Tlv002
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv002, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    Shadow textShadow1;
    textShadow1.SetBlurRadius(2.0);
    textShadow1.SetColor(Color::BLACK);
    textShadow1.SetOffsetX(8.0);
    textShadow1.SetOffsetY(8.0);
    std::vector<uint8_t> result = { 0x23, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x22, 0xff, 0x0, 0x0, 0x0, 0x0,
        0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x40, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x40 };
    TLVUtil::WriteTextShadow(buffer, textShadow1);
    EXPECT_TRUE(buffer == result);

    int32_t cursor = 0;
    Shadow readShadow = TLVUtil::ReadTextShadow(buffer, cursor);
    EXPECT_TRUE(textShadow1 == readShadow);
    buffer.clear();
    Shadow errShadow = TLVUtil::ReadTextShadow(buffer, cursor);
    EXPECT_FALSE(textShadow1 == errShadow);

    std::vector<Shadow> writeShadows = { textShadow1 };
    std::vector<uint8_t> result2 = { 0x26, 0x1, 0x23, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x22, 0xff, 0x0,
        0x0, 0x0, 0x0, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x40, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x40 };
    buffer.clear();
    TLVUtil::WriteTextShadows(buffer, writeShadows);
    EXPECT_TRUE(buffer == result2);

    cursor = 0;
    std::vector<Shadow> readShadows = TLVUtil::ReadTextShadows(buffer, cursor);
    EXPECT_TRUE(writeShadows == readShadows);
    buffer.clear();
    cursor = 0;
    std::vector<Shadow> errShadows = TLVUtil::ReadTextShadows(buffer, cursor);
    EXPECT_TRUE(errShadows.empty());
}

/**
 * @tc.name: Tlv003
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv003, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    std::list<std::pair<std::string, int32_t>> writeFontFeature = { { "f1", 1 }, { "f2", 2 } };
    std::vector<uint8_t> result = { 0x29, 0x2, 0x20, 0x2, 0x66, 0x31, 0x1, 0x20, 0x2, 0x66, 0x32, 0x2 };
    TLVUtil::WriteFontFeature(buffer, writeFontFeature);
    EXPECT_TRUE(buffer == result);

    int32_t cursor = 0;
    std::list<std::pair<std::string, int32_t>> readFontFeature = TLVUtil::ReadFontFeature(buffer, cursor);
    EXPECT_TRUE(writeFontFeature == readFontFeature);
    buffer.clear();
    readFontFeature.clear();
    cursor = 0;
    readFontFeature = TLVUtil::ReadFontFeature(buffer, cursor);
    EXPECT_TRUE(readFontFeature.empty());
}

/**
 * @tc.name: Tlv004
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv004, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    NG::BorderRadiusProperty writeBorderRadiusProperty;
    writeBorderRadiusProperty.SetRadius(2.0_vp);
    std::vector<uint8_t> result = { 0x27, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x1, 0x24, 0x21, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x1, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x1, 0x24, 0x21,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x1 };
    TLVUtil::WriteBorderRadiusProperty(buffer, writeBorderRadiusProperty);
    EXPECT_TRUE(buffer == result);

    int32_t cursor = 0;
    NG::BorderRadiusProperty readBorderRadiusProperty = TLVUtil::ReadBorderRadiusProperty(buffer, cursor);
    EXPECT_TRUE(writeBorderRadiusProperty == readBorderRadiusProperty);
    buffer.clear();
    cursor = 0;
    readBorderRadiusProperty = TLVUtil::ReadBorderRadiusProperty(buffer, cursor);
    EXPECT_FALSE(writeBorderRadiusProperty == readBorderRadiusProperty);
}

/**
 * @tc.name: Tlv005
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv005, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    RefPtr<Ace::PixelMap> writePixelMap = Ace::PixelMap::CreatePixelMap(nullptr);
    std::vector<uint8_t> result = { 0x28, 0x0 };
    TLVUtil::WritePixelMap(buffer, writePixelMap);
    EXPECT_TRUE(buffer == result);

    int32_t cursor = 0;
    RefPtr<Ace::PixelMap> readPixelMap = TLVUtil::ReadPixelMap(buffer, cursor);
    EXPECT_FALSE(writePixelMap == readPixelMap);
    buffer.clear();
    cursor = 0;
    readPixelMap = TLVUtil::ReadPixelMap(buffer, cursor);
    EXPECT_FALSE(writePixelMap == readPixelMap);
}

/**
 * @tc.name: Tlv006
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv006, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    Dimension dim(8);
    CalcDimension writeCalcDimension = CalcDimension(dim);
    std::vector<uint8_t> result = { 0x2a, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x40, 0x0 };
    TLVUtil::WriteCalcDimension(buffer, writeCalcDimension);
    EXPECT_TRUE(buffer == result);

    int32_t cursor = 0;
    CalcDimension readCalcDimension = TLVUtil::ReadCalcDimension(buffer, cursor);
    EXPECT_TRUE(writeCalcDimension == readCalcDimension);
    buffer.clear();
    cursor = 0;
    readCalcDimension = TLVUtil::ReadCalcDimension(buffer, cursor);
    EXPECT_FALSE(writeCalcDimension == readCalcDimension);
}

/**
 * @tc.name: Tlv007
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv007, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    NG::CalcLength writeCalcLength(8);
    std::vector<uint8_t> result = { 0x2b, 0x20, 0x0, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x40, 0x0 };
    TLVUtil::WriteCalcLength(buffer, writeCalcLength);
    EXPECT_TRUE(buffer == result);

    int32_t cursor = 0;
    NG::CalcLength readCalcLength = TLVUtil::ReadCalcLength(buffer, cursor);
    EXPECT_TRUE(writeCalcLength == readCalcLength);
    buffer.clear();
    cursor = 0;
    readCalcLength = TLVUtil::ReadCalcLength(buffer, cursor);
    EXPECT_FALSE(writeCalcLength == readCalcLength);
}

/**
 * @tc.name: Tlv008
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv008, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    ImageSpanSize writeImageSpanSize { .width = 60.0_vp, .height = 60.0_vp };
    std::vector<uint8_t> result = { 0x42, 0x43, 0x2a, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4e, 0x40, 0x1, 0x44,
        0x2a, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4e, 0x40, 0x1, 0x45 };
    TLVUtil::WriteImageSpanSize(buffer, writeImageSpanSize);
    EXPECT_TRUE(buffer == result);

    int32_t cursor = 0;
    ImageSpanSize readImageSpanSize = TLVUtil::ReadImageSpanSize(buffer, cursor);
    EXPECT_TRUE(writeImageSpanSize == readImageSpanSize);
    buffer.clear();
    cursor = 0;
    readImageSpanSize = TLVUtil::ReadImageSpanSize(buffer, cursor);
    EXPECT_FALSE(writeImageSpanSize == readImageSpanSize);
}

/**
 * @tc.name: Tlv009
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv009, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    NG::PaddingProperty writePaddingProperty;
    writePaddingProperty.left = CalcLength(5);
    writePaddingProperty.right = CalcLength(5);
    writePaddingProperty.top = CalcLength(8);
    writePaddingProperty.bottom = CalcLength(8);
    std::vector<uint8_t> result = { 0x46, 0x49, 0x2b, 0x20, 0x0, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x14, 0x40,
        0x0, 0x4a, 0x2b, 0x20, 0x0, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x14, 0x40, 0x0, 0x47, 0x2b, 0x20, 0x0,
        0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x40, 0x0, 0x48, 0x2b, 0x20, 0x0, 0x24, 0x21, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x20, 0x40, 0x0, 0x4b };
    TLVUtil::WritePaddingProperty(buffer, writePaddingProperty);
    EXPECT_TRUE(buffer == result);

    int32_t cursor = 0;
    NG::PaddingProperty readPaddingProperty = TLVUtil::ReadPaddingProperty(buffer, cursor);
    EXPECT_TRUE(writePaddingProperty == readPaddingProperty);
    buffer.clear();
    cursor = 0;
    readPaddingProperty = TLVUtil::ReadPaddingProperty(buffer, cursor);
    EXPECT_FALSE(writePaddingProperty == readPaddingProperty);
}

/**
 * @tc.name: Tlv011
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv011, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    NG::LeadingMargin writeLeadingMargin;
    writeLeadingMargin.size = LeadingMarginSize(Dimension(12.0), Dimension(48.0));
    std::vector<uint8_t> result = { 0x4c, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x28, 0x40, 0x0, 0x24, 0x21, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x48, 0x40, 0x0, 0x4e };
    TLVUtil::WriteLeadingMargin(buffer, writeLeadingMargin);
    EXPECT_TRUE(buffer == result);

    int32_t cursor = 0;
    NG::LeadingMargin readLeadingMargin = TLVUtil::ReadLeadingMargin(buffer, cursor);
    EXPECT_TRUE(writeLeadingMargin == readLeadingMargin);
    buffer.clear();
    cursor = 0;
    readLeadingMargin = TLVUtil::ReadLeadingMargin(buffer, cursor);
    EXPECT_FALSE(writeLeadingMargin == readLeadingMargin);
}

/**
 * @tc.name: Tlv012
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv012, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    TLVUtil::WriteUint8(buffer, TLV_TEXTSHADOW_TAG);
    TLVUtil::WriteInt32(buffer, -100);

    int32_t cursor = 0;
    std::vector<Shadow> readShadows = TLVUtil::ReadTextShadows(buffer, cursor);
    EXPECT_TRUE(readShadows.empty());
}

/**
 * @tc.name: Tlv013
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv013, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    TLVUtil::WriteUint8(buffer, TLV_FONTFAMILIES_TAG);
    TLVUtil::WriteInt32(buffer, -100);

    int32_t cursor = 0;
    std::vector<std::string> vec = TLVUtil::ReadFontFamily(buffer, cursor);
    EXPECT_TRUE(vec.empty());
}


/**
 * @tc.name: Tlv014
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv014, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    TLVUtil::WriteInt32(buffer, -100);

    int32_t cursor = 0;
    std::vector<TextDecoration> vec = TLVUtil::ReadTextDecorations(buffer, cursor);
    EXPECT_TRUE(vec.empty());
}

/**
 * @tc.name: Tlv015
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv015, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    TLVUtil::WriteUint8(buffer, TLV_FONTFEATURE_TAG);
    TLVUtil::WriteInt32(buffer, -100);

    int32_t cursor = 0;
    std::list<std::pair<std::string, int32_t>> list = TLVUtil::ReadFontFeature(buffer, cursor);
    EXPECT_TRUE(list.empty());
}

/**
 * @tc.name: Tlv016
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, Tlv016, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    bool writeSupportSvg2 = true;
    std::vector<uint8_t> result = { 0x01 };
    TLVUtil::WriteBool(buffer, writeSupportSvg2);
    EXPECT_EQ(buffer, result);

    int32_t cursor = 0;
    bool readSupportSvg2 = TLVUtil::ReadBool(buffer, cursor);
    EXPECT_EQ(writeSupportSvg2, readSupportSvg2);
    buffer.clear();
    cursor = 0;
    readSupportSvg2 = TLVUtil::ReadBool(buffer, cursor);
    EXPECT_NE(writeSupportSvg2, readSupportSvg2);
}

/**
 * @tc.name: GetSpanResultObject001
 * @tc.desc: Test GetSpanResultObject
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, GetSpanResultObject001, TestSize.Level1)
{
    auto customSpanItem = AceType::MakeRefPtr<NG::CustomSpanItem>();
    ASSERT_NE(customSpanItem, nullptr);
    customSpanItem->interval.first = 1;
    customSpanItem->interval.second = 2;
    auto resultObject = customSpanItem->GetSpanResultObject(0, 3);
    EXPECT_TRUE(resultObject.isInit);
}

/**
 * @tc.name: GetSpanResultObject002
 * @tc.desc: Test GetSpanResultObject
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, GetSpanResultObject002, TestSize.Level1)
{
    auto customSpanItem = AceType::MakeRefPtr<NG::CustomSpanItem>();
    ASSERT_NE(customSpanItem, nullptr);
    customSpanItem->interval.first = 1;
    customSpanItem->interval.second = 2;
    auto resultObject = customSpanItem->GetSpanResultObject(2, 3);
    EXPECT_FALSE(resultObject.isInit);
}

/**
 * @tc.name: GetSpanResultObject003
 * @tc.desc: Test GetSpanResultObject
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, GetSpanResultObject003, TestSize.Level1)
{
    auto customSpanItem = AceType::MakeRefPtr<NG::CustomSpanItem>();
    ASSERT_NE(customSpanItem, nullptr);
    customSpanItem->interval.first = 1;
    customSpanItem->interval.second = 4;
    auto resultObject = customSpanItem->GetSpanResultObject(0, 3);
    EXPECT_FALSE(resultObject.isInit);
}

/**
 * @tc.name: SpanLineThicknessScaleTest001
 * @tc.desc: Test new attribute of DecorationSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanLineThicknessScaleTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize a spanString and AddSpan
     * @tc.expected: The SpanString and style should be successfully created and applied
     */
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"SpanLineThicknessScaleTest123");
    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
        std::vector<TextDecoration>({TextDecoration::UNDERLINE}), Color::BLACK,
        TextDecorationStyle::WAVY, 1.0f, std::optional<TextDecorationOptions>(), 0, 1, nullptr));
    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
        std::vector<TextDecoration>({TextDecoration::LINE_THROUGH}), Color::BLACK,
        TextDecorationStyle::DASHED, 5.0f, std::optional<TextDecorationOptions>(), 0, 2, nullptr));
    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
        std::vector<TextDecoration>({TextDecoration::OVERLINE}), Color::BLACK,
        TextDecorationStyle::DOTTED, 10.0f, std::optional<TextDecorationOptions>(), 0, 3, nullptr));
    Shadow textShadow;
    textShadow.SetBlurRadius(1.0);
    textShadow.SetOffsetX(2.0);
    textShadow.SetOffsetY(3.0);
    vector<Shadow> textShadows { textShadow };
    spanString->AddSpan(AceType::MakeRefPtr<TextShadowSpan>(textShadows, 7, 9));

    /**
     * @tc.steps2: call GetSpans to get spans
     * @tc.expected: The SpanString should be successfully created
     */
    auto firstSpans = spanString->GetSpans(0, 9);
    EXPECT_NE(firstSpans.size(), 0);
}

/**
 * @tc.name: SpanLineThicknessScaleTest002
 * @tc.desc: Test new attribute of DecorationSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, SpanLineThicknessScaleTest002, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize a spanString and AddSpan
     * @tc.expected: The SpanString and style should be successfully created and applied
     */
    std::string buffer;
    RefPtr<FontSpan> fontSpan = AceType::MakeRefPtr<FontSpan>(testFont1, 0, 9);
    buffer = fontSpan->ToString();
    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.find("FontSpan"), 0);

    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    auto decorationSpan1 = AceType::MakeRefPtr<DecorationSpan>(
        std::vector<TextDecoration>({TextDecoration::UNDERLINE}),
        Color::RED, TextDecorationStyle::WAVY, 1.0f, std::optional<TextDecorationOptions>(), 0, 1, nullptr);
    EXPECT_FALSE(fontSpan->IsAttributesEqual(decorationSpan1));
    decorationSpan1->ApplyToSpanItem(spanItem, SpanOperation::REMOVE);
    buffer.clear();
    buffer = decorationSpan1->ToString();
    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.find("DecorationSpan"), 0);

    auto decorationSpan2 = AceType::MakeRefPtr<DecorationSpan>(
        std::vector<TextDecoration>({TextDecoration::OVERLINE}),
        Color::RED, TextDecorationStyle::DASHED, 6.0f, std::optional<TextDecorationOptions>(), 0, 1, nullptr);
    EXPECT_FALSE(fontSpan->IsAttributesEqual(decorationSpan2));
    decorationSpan2->ApplyToSpanItem(spanItem, SpanOperation::REMOVE);
    buffer.clear();
    buffer = decorationSpan2->ToString();
    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.find("DecorationSpan"), 0);
}

/**
 * @tc.name: TextLayoutTest001
 * @tc.desc: Test new attribute of TextLayoutInfo
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestThreeNg, TextLayoutTest001, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::START;
    spanParagraphStyle.maxLines = 2;
    spanParagraphStyle.wordBreak = WordBreak::BREAK_ALL;
    spanParagraphStyle.textOverflow = TextOverflow::ELLIPSIS;
    spanParagraphStyle.textIndent = Dimension(30);
    spanParagraphStyle.leadingMargin = LeadingMargin();
    spanParagraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(25.0), Dimension(26.0));
    spanString->AddSpan(AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 0, 1));
    spanString->AddSpan(AceType::MakeRefPtr<LineHeightSpan>(Dimension(30), 0, 3));
    spanString->AddSpan(AceType::MakeRefPtr<LineHeightSpan>(Dimension(10), 0, 2));
    auto firstSpans = spanString->GetSpans(2, 1);
    EXPECT_EQ(firstSpans.size(), 1);
    auto paraSpans = spanString->GetSpans(0, 2, SpanType::ParagraphStyle);
    EXPECT_EQ(paraSpans.size(), 1);
    auto paraSpan = AceType::DynamicCast<ParagraphStyleSpan>(paraSpans[0]);
    EXPECT_NE(paraSpan, nullptr);
    EXPECT_EQ(paraSpan->GetStartIndex(), 0);
    EXPECT_EQ(paraSpan->GetEndIndex(), 1);
    EXPECT_EQ(paraSpan->GetParagraphStyle().align, TextAlign::START);
    EXPECT_EQ(paraSpan->GetParagraphStyle().maxLines, 2);
    EXPECT_EQ(paraSpan->GetParagraphStyle().wordBreak, WordBreak::BREAK_ALL);
    EXPECT_EQ(paraSpan->GetParagraphStyle().textOverflow, TextOverflow::ELLIPSIS);
    EXPECT_EQ(paraSpan->GetParagraphStyle().textIndent, Dimension(30));
    EXPECT_EQ(paraSpan->GetParagraphStyle().leadingMargin.value().size.Width().ConvertToVp(), 25);
    EXPECT_EQ(paraSpan->GetParagraphStyle().leadingMargin.value().size.Height().ConvertToVp(), 26);
}
} // namespace OHOS::Ace::NG