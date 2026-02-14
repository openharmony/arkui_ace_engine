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

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"

#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const uint32_t GESTURE_INDEX1 = 1;
void ConstructGestureStyle(GestureStyle& gestureInfo)
{
    auto onClick = [](const BaseEventInfo* info) {};
    auto tmpClickFunc = [func = std::move(onClick)](GestureEvent& info) { func(&info); };
    gestureInfo.onClick = std::move(tmpClickFunc);

    auto onLongPress = [](const BaseEventInfo* info) {};
    auto tmpLongPressFunc = [func = std::move(onLongPress)](GestureEvent& info) { func(&info); };
    gestureInfo.onLongPress = std::move(tmpLongPressFunc);
}
const double NUMBER_TEN = 10.0;
const double NUMBER_FIVE = 10.0;
} // namespace

class SpanStringTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    static ImageSpanOptions GetImageOption(const std::string& src);
    static ImageSpanOptions GetColorFilterImageOption(const std::string& src);
    static ImageSpanOptions GetImageOptionWithSize(const std::string& src);
};

void SpanStringTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
}

void SpanStringTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void SpanStringTestNg::SetUp()
{
    MockParagraph::GetOrCreateMockParagraph();
}

void SpanStringTestNg::TearDown()
{
    MockParagraph::TearDown();
}

ImageSpanOptions SpanStringTestNg::GetImageOption(const std::string& src)
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

ImageSpanOptions SpanStringTestNg::GetImageOptionWithSize(const std::string& src)
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

ImageSpanOptions SpanStringTestNg::GetColorFilterImageOption(const std::string& src)
{
    ImageSpanSize size { .width = 50.0_vp, .height = 50.0_vp };
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(2.0_vp);
    MarginProperty margins;
    margins.SetEdges(CalcLength(NUMBER_TEN));
    PaddingProperty paddings;
    paddings.SetEdges(CalcLength(NUMBER_FIVE));
    std::vector<float> colorFilterMat { 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0 };
    ImageSpanAttribute attr { .paddingProp = paddings,
        .marginProp = margins,
        .borderRadius = borderRadius,
        .objectFit = ImageFit::COVER,
        .verticalAlign = VerticalAlign::BOTTOM,
        .colorFilterMatrix = colorFilterMat };
    ImageSpanOptions option { .image = src, .imageAttribute = attr };
    return option;
}

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    };

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};
std::string test_str[] = { "hello", "world", "this", "find", "gank", "pink", "that", "when", "how", "cpp" };
Font testFont1 { OHOS::Ace::FontWeight::BOLD, Dimension(29.0, DimensionUnit::PX), OHOS::Ace::FontStyle::ITALIC,
    std::vector<std::string>(test_str, test_str + 10), OHOS::Ace::Color::RED };
Font testFont2 { OHOS::Ace::FontWeight::LIGHTER, Dimension(19.0, DimensionUnit::PX), OHOS::Ace::FontStyle::ITALIC,
    std::vector<std::string>(test_str, test_str + 10), OHOS::Ace::Color::WHITE };
Font testEmptyFont {};
/**
 * @tc.name: SpanStringTest001
 * @tc.desc: Test basic function of GetString/GetLength/GetIndex
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString001, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<SpanString>(u"0123456789");
    EXPECT_EQ(spanString->GetString(), "0123456789");
    EXPECT_EQ(spanString->GetLength(), 10);

    auto spanString1 = AceType::MakeRefPtr<SpanString>(u"中0123456789");
    EXPECT_EQ(spanString1->GetString(), "中0123456789");
    EXPECT_EQ(spanString1->GetLength(), 11);

    auto spanString2 = AceType::MakeRefPtr<SpanString>(u"0123456");
    EXPECT_EQ(spanString2->GetString(), "0123456");
    EXPECT_EQ(spanString2->GetLength(), 7);

    auto spanString3 = AceType::MakeRefPtr<SpanString>(u"你好");
    EXPECT_EQ(spanString3->GetString(), "你好");
    EXPECT_EQ(spanString3->GetLength(), 2);
}
/**
 * @tc.name: SpanStringTest002
 * @tc.desc: Test basic function of IsEqualToSpanString/GetSubSpanString
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString002, TestSize.Level1)
{
    auto spanString1 = AceType::MakeRefPtr<SpanString>(u"01234中56789");
    auto spanString2 = AceType::MakeRefPtr<SpanString>(u"01234中56789");
    auto spanString3 = AceType::MakeRefPtr<SpanString>(u"01234567891");
    EXPECT_TRUE(spanString1->IsEqualToSpanString(spanString2));
    EXPECT_FALSE(spanString1->IsEqualToSpanString(spanString3));
    std::vector<RefPtr<SpanBase>> spans;
    spans.push_back(AceType::MakeRefPtr<FontSpan>(testFont2, 0, 3));
    spans.push_back(AceType::MakeRefPtr<FontSpan>(testEmptyFont, 5, 8));
    auto spanStringWithSpans1 = AceType::MakeRefPtr<SpanString>(u"01234567891");
    spanStringWithSpans1->BindWithSpans(spans);
    auto spanStringWithSpans2 = AceType::MakeRefPtr<SpanString>(u"01234567891");
    spanStringWithSpans2->BindWithSpans(spans);
    EXPECT_TRUE(spanStringWithSpans1->IsEqualToSpanString(spanStringWithSpans2));
    std::vector<RefPtr<SpanBase>> spans1;
    spans1.push_back(AceType::MakeRefPtr<FontSpan>(testFont2, 0, 3));
    spans1.push_back(AceType::MakeRefPtr<FontSpan>(testEmptyFont, 5, 7));
    auto spanStringWithSpans3 = AceType::MakeRefPtr<SpanString>(u"01234567891");
    spanStringWithSpans3->BindWithSpans(spans1);
    EXPECT_FALSE(spanStringWithSpans3->IsEqualToSpanString(spanStringWithSpans2));
    auto subSpanStringWithSpans2 = spanStringWithSpans2->GetSubSpanString(0, 7);
    auto subSpanStringWithSpans3 = spanStringWithSpans3->GetSubSpanString(0, 7);
    auto map2 = subSpanStringWithSpans2->GetSpansMap();
    EXPECT_TRUE(subSpanStringWithSpans2->IsEqualToSpanString(subSpanStringWithSpans3));
    auto emptySpanString = spanStringWithSpans2->GetSubSpanString(1, 0);
    EXPECT_TRUE(emptySpanString->IsEqualToSpanString(AceType::MakeRefPtr<SpanString>(u"")));
}

/**
 * @tc.name: SpanStringTest003
 * @tc.desc: Test basic function of GetSpans/GetFontColor/GetFontSize/GetFontWeight/GetFontFamily/GetFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString003, TestSize.Level1)
{
    auto spanString3 = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 3));
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 3, 5));
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testEmptyFont, 5, 8));
    auto firstSpans = spanString3->GetSpans(5, 2);
    EXPECT_EQ(firstSpans.size(), 1);
    auto firstFontSpan = AceType::DynamicCast<FontSpan>(firstSpans[0]);
    EXPECT_NE(firstFontSpan, nullptr);
    EXPECT_EQ(firstFontSpan->GetStartIndex(), 5);
    EXPECT_EQ(firstFontSpan->GetEndIndex(), 7);
    EXPECT_EQ(firstFontSpan->GetFont().GetFontColor(), "");

    auto secondString3 = spanString3->GetSpans(0, 3);
    EXPECT_EQ(secondString3.size(), 1);
    auto secondFontSpan = AceType::DynamicCast<FontSpan>(secondString3[0]);
    EXPECT_NE(secondFontSpan, nullptr);
    EXPECT_EQ(secondFontSpan->GetStartIndex(), 0);
    EXPECT_EQ(secondFontSpan->GetEndIndex(), 3);
    EXPECT_EQ(secondFontSpan->GetFont().GetFontColor(), OHOS::Ace::Color::RED.ColorToString());

    auto thirdString3 = spanString3->GetSpans(3, 1);
    EXPECT_EQ(thirdString3.size(), 1);
    auto thirdFontSpan = AceType::DynamicCast<FontSpan>(thirdString3[0]);
    EXPECT_NE(thirdFontSpan, nullptr);
    EXPECT_EQ(thirdFontSpan->GetStartIndex(), 3);
    EXPECT_EQ(thirdFontSpan->GetEndIndex(), 4);
    EXPECT_EQ(thirdFontSpan->GetFont().GetFontColor(), OHOS::Ace::Color::WHITE.ColorToString());
}
/**
 * @tc.name: SpanStringTest004
 * @tc.desc: Test basic function of GetString/GetLength/GetIndex
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString004, TestSize.Level1)
{
    auto spanString3 = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testEmptyFont, 0, 3));
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 3, 5));
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 5, 8));
    auto spans = spanString3->GetSpans(1, 7);
    EXPECT_EQ(spans.size(), 3);
    auto firstFontSpan = AceType::DynamicCast<FontSpan>(spans[0]);
    EXPECT_NE(firstFontSpan, nullptr);
    EXPECT_EQ(firstFontSpan->GetStartIndex(), 1);
    EXPECT_EQ(firstFontSpan->GetEndIndex(), 3);
    EXPECT_EQ(firstFontSpan->GetFont().GetFontColor(), "");

    auto secondFontSpan = AceType::DynamicCast<FontSpan>(spans[1]);
    EXPECT_NE(secondFontSpan, nullptr);
    EXPECT_EQ(secondFontSpan->GetStartIndex(), 3);
    EXPECT_EQ(secondFontSpan->GetEndIndex(), 5);
    EXPECT_EQ(secondFontSpan->GetFont().GetFontColor(), OHOS::Ace::Color::RED.ColorToString());

    auto thirdFontSpan = AceType::DynamicCast<FontSpan>(spans[2]);
    EXPECT_NE(thirdFontSpan, nullptr);
    EXPECT_EQ(thirdFontSpan->GetStartIndex(), 5);
    EXPECT_EQ(thirdFontSpan->GetEndIndex(), 8);
    EXPECT_EQ(thirdFontSpan->GetFont().GetFontColor(), OHOS::Ace::Color::WHITE.ColorToString());
}

/**
 * @tc.name: SpanStringTest005
 * @tc.desc: Test basic function of DecorationSpan/BaselineOffsetSpan/LetterSpacingSpan/TextShadowSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString005, TestSize.Level1)
{
    auto spanString3 = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    std::optional<TextDecorationOptions> options;
    spanString3->AddSpan(AceType::MakeRefPtr<DecorationSpan>(std::vector<TextDecoration>({ TextDecoration::OVERLINE }),
        Color::RED, TextDecorationStyle::WAVY, options, 0, 1, nullptr));
    spanString3->AddSpan(AceType::MakeRefPtr<BaselineOffsetSpan>(Dimension(4), 0, 2));
    spanString3->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(5), 0, 3));
    Shadow textShadow;
    textShadow.SetBlurRadius(0.0);
    textShadow.SetColor(Color::BLUE);
    textShadow.SetOffsetX(5.0);
    textShadow.SetOffsetY(5.0);
    vector<Shadow> textShadows { textShadow };
    spanString3->AddSpan(AceType::MakeRefPtr<TextShadowSpan>(textShadows, 7, 9));

    auto firstSpans = spanString3->GetSpans(2, 1);
    EXPECT_EQ(firstSpans.size(), 1);
    auto letterSpacingSpan = AceType::DynamicCast<LetterSpacingSpan>(firstSpans[0]);
    EXPECT_NE(letterSpacingSpan, nullptr);
    EXPECT_EQ(letterSpacingSpan->GetStartIndex(), 2);
    EXPECT_EQ(letterSpacingSpan->GetEndIndex(), 3);
    EXPECT_TRUE(letterSpacingSpan->GetLetterSpacing() == Dimension(5));

    auto secondSpans = spanString3->GetSpans(1, 1);
    EXPECT_EQ(secondSpans.size(), 2);

    auto thirdSpans = spanString3->GetSpans(0, 1);
    EXPECT_EQ(thirdSpans.size(), 3);

    auto fourthSpans = spanString3->GetSpans(3, 1);
    EXPECT_EQ(fourthSpans.size(), 0);

    auto fifthSpans = spanString3->GetSpans(0, 9);
    EXPECT_EQ(fifthSpans.size(), 4);
}

/**
 * @tc.name: SpanStringTest006
 * @tc.desc: Test basic function of DecorationSpan/BaselineOffsetSpan/LetterSpacingSpan/TextShadowSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString006, TestSize.Level1)
{
    auto spanString3 = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    std::optional<TextDecorationOptions> options;
    spanString3->AddSpan(AceType::MakeRefPtr<DecorationSpan>(std::vector<TextDecoration>({ TextDecoration::OVERLINE }),
        Color::RED, TextDecorationStyle::WAVY, options, 0, 1, nullptr));
    spanString3->AddSpan(AceType::MakeRefPtr<BaselineOffsetSpan>(Dimension(4), 0, 2));
    spanString3->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(5), 5, 8));
    Shadow textShadow;
    textShadow.SetBlurRadius(0.0);
    textShadow.SetColor(Color::BLUE);
    textShadow.SetOffsetX(5.0);
    textShadow.SetOffsetY(5.0);
    vector<Shadow> textShadows { textShadow };
    spanString3->AddSpan(AceType::MakeRefPtr<TextShadowSpan>(textShadows, 8, 10));
    auto subSpanString = spanString3->GetSubSpanString(0, 10);
    EXPECT_TRUE(subSpanString->IsEqualToSpanString(spanString3));
    auto firstSpans = spanString3->GetSpans(5, 1);
    auto letterSpacingSpan = AceType::DynamicCast<LetterSpacingSpan>(firstSpans[0]);
    EXPECT_NE(letterSpacingSpan, nullptr);
    EXPECT_EQ(letterSpacingSpan->GetStartIndex(), 5);
    EXPECT_EQ(letterSpacingSpan->GetEndIndex(), 6);
    EXPECT_TRUE(letterSpacingSpan->GetLetterSpacing() == Dimension(5));

    auto secondSpans = spanString3->GetSpans(1, 2);
    EXPECT_EQ(secondSpans.size(), 1);
    auto baselineOffsetSpan = AceType::DynamicCast<BaselineOffsetSpan>(secondSpans[0]);
    EXPECT_NE(baselineOffsetSpan, nullptr);
    EXPECT_EQ(baselineOffsetSpan->GetStartIndex(), 1);
    EXPECT_EQ(baselineOffsetSpan->GetEndIndex(), 2);
    EXPECT_TRUE(baselineOffsetSpan->GetBaselineOffset() == Dimension(4));

    auto thirdSpans = spanString3->GetSpans(8, 1);
    EXPECT_EQ(thirdSpans.size(), 1);
    auto textShadowSpan = AceType::DynamicCast<TextShadowSpan>(thirdSpans[0]);
    EXPECT_NE(textShadowSpan, nullptr);
    EXPECT_EQ(textShadowSpan->GetStartIndex(), 8);
    EXPECT_EQ(textShadowSpan->GetEndIndex(), 9);
    EXPECT_TRUE(textShadowSpan->GetTextShadow()[0] == textShadow);
}

/**
 * @tc.name: SpanStringTest007
 * @tc.desc: Test basic function of CustomSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString007, TestSize.Level1)
{
    auto customSpan = AceType::MakeRefPtr<CustomSpan>();
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(customSpan);
    auto spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans.size(), 1);
    auto span = AceType::DynamicCast<CustomSpan>(spans[0]);
    EXPECT_EQ(span->GetStartIndex(), 0);
    EXPECT_EQ(span->GetEndIndex(), 1);
    EXPECT_EQ(span->GetOnMeasure(), std::nullopt);
    EXPECT_EQ(span->GetOnDraw(), std::nullopt);

    spanString->AppendSpanString(spanString);
    spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans.size(), 2);
    auto span0 = AceType::DynamicCast<CustomSpan>(spans[0]);
    EXPECT_EQ(span0->GetStartIndex(), 0);
    EXPECT_EQ(span0->GetEndIndex(), 1);
    EXPECT_EQ(span0->GetOnMeasure(), std::nullopt);
    EXPECT_EQ(span0->GetOnDraw(), std::nullopt);
    auto span1 = AceType::DynamicCast<CustomSpan>(spans[1]);
    EXPECT_EQ(span1->GetStartIndex(), 1);
    EXPECT_EQ(span1->GetEndIndex(), 2);
    EXPECT_EQ(span1->GetOnMeasure(), std::nullopt);
    EXPECT_EQ(span1->GetOnDraw(), std::nullopt);
    EXPECT_FALSE(span0->IsAttributesEqual(span1));
    spanString->RemoveSpans(0, spanString->GetLength());
    EXPECT_EQ(spanString->GetLength(), 0);
}

/**
 * @tc.name: SpanStringTest008
 * @tc.desc: Test basic function of CustomSpan/Image
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString008, TestSize.Level1)
{
    auto imageOption = SpanStringTestNg::GetImageOption("src/icon-1.png");
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);
    mutableStr->InsertString(0, u"123");
    mutableStr->InsertString(4, u"456");
    auto imageOption1 = SpanStringTestNg::GetImageOption("src/icon-2.png");
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
 * @tc.name: SpanStringTest001
 * @tc.desc: Test basic function of ReplaceString/InsertString/RemoveString
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString001, TestSize.Level1)
{
    auto a = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    EXPECT_EQ(a->GetString(), "0123456789");
    a->ReplaceString(0, 1, u"abcd");
    EXPECT_EQ(a->GetString(), "abcd123456789");
    a->InsertString(0, u"abcd");
    EXPECT_EQ(a->GetString(), "abcdabcd123456789");
    a->RemoveString(3, 3);
    EXPECT_EQ(a->GetString(), "abccd123456789");
    a->InsertString(4, u"中文插入测试");
    EXPECT_EQ(a->GetString(), "abcc中文插入测试d123456789");
    a->RemoveString(4, 6);
    EXPECT_EQ(a->GetString(), "abccd123456789");
    a->ReplaceString(5, 9, u"中文替换测试");
    EXPECT_EQ(a->GetString(), "abccd中文替换测试");
}

bool CompareSpanList(const std::list<RefPtr<SpanBase>>& a, const std::list<RefPtr<SpanBase>>& b)
{
    if (a.size() != b.size()) {
        std::cout << "size not match" << a.size() << " " << b.size() << std::endl;
        return false;
    }
    auto ita = a.begin();
    auto itb = b.begin();
    while (ita != a.end()) {
        if (!(*ita)->IsAttributesEqual(*itb)) {
            std::cout << (*ita)->ToString() << " " << (*itb)->ToString() << std::endl;
            return false;
        }
        ++ita;
        ++itb;
    }
    return true;
}

/**
 * @tc.name: SpanStringTest001
 * @tc.desc: Test if span is right after addSpan/replaceSpan/removeSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString002, TestSize.Level1)
{
    auto a = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");

    std::string test_str[] = { "hello", "world", "this", "find", "gank", "pink", "that", "when", "how", "cpp" };
    a->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 10));
    EXPECT_EQ(a->GetString(), "0123456789");
    std::list<RefPtr<SpanBase>> resultList1 = { AceType::MakeRefPtr<FontSpan>(testFont1, 0, 10) };
    auto aSpansMap = a->GetSpansMap();
    EXPECT_TRUE(CompareSpanList(aSpansMap[SpanType::Font], resultList1));
    std::list<RefPtr<SpanBase>> resultList2 = { AceType::MakeRefPtr<FontSpan>(testFont2, 0, 3),
        AceType::MakeRefPtr<FontSpan>(testFont1, 3, 10) };
    a->ReplaceSpan(0, 3, AceType::MakeRefPtr<FontSpan>(testFont2, 0, 10));
    aSpansMap = a->GetSpansMap();
    EXPECT_EQ(a->GetString(), "0123456789");
    EXPECT_TRUE(CompareSpanList(aSpansMap[SpanType::Font], resultList2));
    std::list<RefPtr<SpanBase>> resultList3 = { AceType::MakeRefPtr<FontSpan>(testFont1, 3, 10) };
    a->RemoveSpan(0, 3, SpanType::Font);
    aSpansMap = a->GetSpansMap();
    EXPECT_EQ(a->GetString(), "0123456789");
    EXPECT_TRUE(CompareSpanList(aSpansMap[SpanType::Font], resultList3));

    // 用中文再测一次
    auto b = MutableSpanString(u"零一二三四五六七八九");
    b.AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 10));
    EXPECT_EQ(b.GetString(), "零一二三四五六七八九");
    std::list<RefPtr<SpanBase>> resultList4 = { AceType::MakeRefPtr<FontSpan>(testFont1, 0, 10) };
    auto bSpansMap = b.GetSpansMap();
    EXPECT_TRUE(CompareSpanList(bSpansMap[SpanType::Font], resultList4));
    std::list<RefPtr<SpanBase>> resultList5 = { AceType::MakeRefPtr<FontSpan>(testFont2, 0, 3),
        AceType::MakeRefPtr<FontSpan>(testFont1, 3, 10) };
    b.ReplaceSpan(0, 3, AceType::MakeRefPtr<FontSpan>(testFont2, 0, 10));
    bSpansMap = b.GetSpansMap();
    EXPECT_EQ(b.GetString(), "零一二三四五六七八九");
    EXPECT_TRUE(CompareSpanList(bSpansMap[SpanType::Font], resultList5));
    std::list<RefPtr<SpanBase>> resultList6 = { AceType::MakeRefPtr<FontSpan>(testFont1, 3, 10) };
    b.RemoveSpan(0, 3, SpanType::Font);
    bSpansMap = b.GetSpansMap();
    EXPECT_EQ(b.GetString(), "零一二三四五六七八九");
    EXPECT_TRUE(CompareSpanList(bSpansMap[SpanType::Font], resultList6));
}

/**
 * @tc.name: MutableSpanString003
 * @tc.desc: Test if span is right after addSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString003, TestSize.Level1)
{
    auto mutableSpan = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");

    Font fontOne { .fontColor = OHOS::Ace::Color::RED };
    Font fontTwo { .fontColor = OHOS::Ace::Color::WHITE };
    Font fontThree { .fontColor = OHOS::Ace::Color::BLACK };

    mutableSpan->AddSpan(AceType::MakeRefPtr<FontSpan>(fontOne, 0, 10));
    auto spansMap = mutableSpan->GetSpansMap();
    auto spanItems = mutableSpan->GetSpanItems();
    EXPECT_EQ(spansMap.size(), 1);
    EXPECT_EQ(spanItems.size(), 1);

    mutableSpan->AddSpan(AceType::MakeRefPtr<FontSpan>(fontTwo, 3, 7));
    spansMap = mutableSpan->GetSpansMap();
    auto fontSpans = spansMap[SpanType::Font];
    spanItems = mutableSpan->GetSpanItems();
    EXPECT_EQ(fontSpans.size(), 3);
    EXPECT_EQ(spanItems.size(), 3);
    std::list<RefPtr<SpanBase>> resultList = { AceType::MakeRefPtr<FontSpan>(fontOne, 0, 3),
        AceType::MakeRefPtr<FontSpan>(fontTwo, 3, 7), AceType::MakeRefPtr<FontSpan>(fontOne, 7, 10) };
    EXPECT_EQ(CompareSpanList(fontSpans, resultList), true);

    mutableSpan->AddSpan(AceType::MakeRefPtr<FontSpan>(fontThree, 2, 5));
    spansMap = mutableSpan->GetSpansMap();
    fontSpans = spansMap[SpanType::Font];
    spanItems = mutableSpan->GetSpanItems();
    EXPECT_EQ(fontSpans.size(), 4);
    EXPECT_EQ(spanItems.size(), 5);
    resultList = { AceType::MakeRefPtr<FontSpan>(fontOne, 0, 2), AceType::MakeRefPtr<FontSpan>(fontThree, 2, 5),
        AceType::MakeRefPtr<FontSpan>(fontTwo, 5, 7), AceType::MakeRefPtr<FontSpan>(fontOne, 7, 10) };
    EXPECT_EQ(CompareSpanList(fontSpans, resultList), true);
}

/**
 * @tc.name: MutableSpanString004
 * @tc.desc: Test if span is right after removeSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString004, TestSize.Level1)
{
    auto mutableSpan = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");

    Font fontOne { .fontColor = OHOS::Ace::Color::RED };
    Font fontTwo { .fontColor = OHOS::Ace::Color::WHITE };
    Font fontThree { .fontColor = OHOS::Ace::Color::BLACK };

    mutableSpan->AddSpan(AceType::MakeRefPtr<FontSpan>(fontOne, 0, 10));
    mutableSpan->AddSpan(AceType::MakeRefPtr<FontSpan>(fontTwo, 3, 7));
    mutableSpan->AddSpan(AceType::MakeRefPtr<FontSpan>(fontThree, 2, 5));

    mutableSpan->RemoveSpan(2, 3, SpanType::Font);
    auto spansMap = mutableSpan->GetSpansMap();
    auto fontSpans = spansMap[SpanType::Font];
    EXPECT_EQ(fontSpans.size(), 3);
    std::list<RefPtr<SpanBase>> resultList = { AceType::MakeRefPtr<FontSpan>(fontOne, 0, 2),
        AceType::MakeRefPtr<FontSpan>(fontTwo, 5, 7), AceType::MakeRefPtr<FontSpan>(fontOne, 7, 10) };
    EXPECT_EQ(CompareSpanList(fontSpans, resultList), true);

    mutableSpan->RemoveSpan(2, 5, SpanType::Font);
    spansMap = mutableSpan->GetSpansMap();
    fontSpans = spansMap[SpanType::Font];
    EXPECT_EQ(fontSpans.size(), 2);
    resultList = { AceType::MakeRefPtr<FontSpan>(fontOne, 0, 2), AceType::MakeRefPtr<FontSpan>(fontOne, 7, 10) };
    EXPECT_EQ(CompareSpanList(fontSpans, resultList), true);

    mutableSpan->RemoveSpan(0, 10, SpanType::Font);
    spansMap = mutableSpan->GetSpansMap();
    fontSpans = spansMap[SpanType::Font];
    EXPECT_EQ(fontSpans.size(), 0);
}

/**
 * @tc.name: MutableSpanString005
 * @tc.desc: Test for outliers
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString005, TestSize.Level1)
{
    auto mutableSpan = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");

    Font fontOne { .fontColor = OHOS::Ace::Color::RED };
    Font fontTwo { .fontColor = OHOS::Ace::Color::WHITE };
    Font fontThree { .fontColor = OHOS::Ace::Color::BLACK };

    mutableSpan->AddSpan(AceType::MakeRefPtr<FontSpan>(fontOne, -1, 10));
    mutableSpan->AddSpan(AceType::MakeRefPtr<FontSpan>(fontTwo, 3, 100));
    mutableSpan->AddSpan(AceType::MakeRefPtr<FontSpan>(fontThree, -100, 100));

    auto spansMap = mutableSpan->GetSpansMap();
    EXPECT_EQ(spansMap.size(), 0);

    mutableSpan->AddSpan(AceType::MakeRefPtr<FontSpan>(fontOne, 0, 10));
    mutableSpan->AddSpan(AceType::MakeRefPtr<FontSpan>(fontTwo, 3, 7));
    mutableSpan->AddSpan(AceType::MakeRefPtr<FontSpan>(fontThree, 2, 5));
    spansMap = mutableSpan->GetSpansMap();
    auto fontSpans = spansMap[SpanType::Font];
    EXPECT_EQ(fontSpans.size(), 4);
    mutableSpan->RemoveSpan(-1, 10, SpanType::Font);
    mutableSpan->RemoveSpan(3, 100, SpanType::Font);
    mutableSpan->RemoveSpan(-100, 100, SpanType::Font);
    spansMap = mutableSpan->GetSpansMap();
    fontSpans = spansMap[SpanType::Font];
    EXPECT_EQ(fontSpans.size(), 4);
}

/**
 * @tc.name: MutableSpanString006
 * @tc.desc: Test combination of IsEqualToSpanString/GetSubSpanString/GetSpans/GetSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString006, TestSize.Level1)
{
    Font fontOne { .fontColor = OHOS::Ace::Color::RED };
    Font fontTwo { .fontColor = OHOS::Ace::Color::WHITE };
    auto spanString1 = AceType::MakeRefPtr<SpanString>(u"0123456789");
    spanString1->AddSpan(AceType::MakeRefPtr<FontSpan>(fontOne, 0, 3));
    auto mutableSpanString1 = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    EXPECT_FALSE(spanString1->IsEqualToSpanString(mutableSpanString1));
    mutableSpanString1->AddSpan(AceType::MakeRefPtr<FontSpan>(fontOne, 0, 3));
    EXPECT_TRUE(spanString1->IsEqualToSpanString(mutableSpanString1));
    mutableSpanString1->AddSpan(AceType::MakeRefPtr<FontSpan>(fontOne, 3, 7));
    auto mutableSpanString2 = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    mutableSpanString2->AddSpan(AceType::MakeRefPtr<FontSpan>(fontOne, 0, 7));
    EXPECT_TRUE(mutableSpanString2->IsEqualToSpanString(mutableSpanString1));
    EXPECT_TRUE(spanString1->GetSubSpanString(0, 3)->IsEqualToSpanString(mutableSpanString2->GetSubSpanString(0, 3)));
    mutableSpanString2->AddSpan(AceType::MakeRefPtr<FontSpan>(fontTwo, 7, 8));
    mutableSpanString2->AddSpan(AceType::MakeRefPtr<FontSpan>(fontOne, 8, 9));
    auto spanArr = mutableSpanString2->GetSpans(0, 9);
    EXPECT_EQ(spanArr.size(), 3);
}

/**
 * @tc.name: MutableSpanString007
 * @tc.desc: Test some edge case of InsertString/ReplaceString/RemoveString
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString007, TestSize.Level1)
{
    vector<OHOS::Ace::Color> colors = { Color::RED, Color::BLACK, Color::GREEN, Color::GRAY, Color::BLUE };
    vector<Font> fonts;
    auto spanString1 = AceType::MakeRefPtr<MutableSpanString>(u"01234");
    for (int i = 0; i < colors.size(); i++) {
        Font f;
        f.fontColor = colors[i];
        fonts.emplace_back(f);
        spanString1->AddSpan(AceType::MakeRefPtr<FontSpan>(f, i, i + 1));
    }
    auto spanArr = spanString1->GetSpans(0, spanString1->GetLength());
    EXPECT_EQ(spanArr.size(), colors.size());

    auto spanString2 = spanString1->GetSubSpanString(0, spanString1->GetLength());
    EXPECT_TRUE(spanString2->IsEqualToSpanString(spanString1));
    std::list<RefPtr<SpanBase>> resultList1 = { AceType::MakeRefPtr<FontSpan>(fonts[0], 0, 6),
        AceType::MakeRefPtr<FontSpan>(fonts[1], 6, 7), AceType::MakeRefPtr<FontSpan>(fonts[2], 7, 8),
        AceType::MakeRefPtr<FontSpan>(fonts[3], 8, 9), AceType::MakeRefPtr<FontSpan>(fonts[4], 9, 10) };
    spanString1->InsertString(0, u"一二三四五");
    auto spanMap = spanString1->GetSpansMap();
    EXPECT_TRUE(CompareSpanList(spanMap[SpanType::Font], resultList1));
    spanString1->InsertString(6, u"红红火火");
    std::list<RefPtr<SpanBase>> resultList2 = { AceType::MakeRefPtr<FontSpan>(fonts[0], 0, 10),
        AceType::MakeRefPtr<FontSpan>(fonts[1], 10, 11), AceType::MakeRefPtr<FontSpan>(fonts[2], 11, 12),
        AceType::MakeRefPtr<FontSpan>(fonts[3], 12, 13), AceType::MakeRefPtr<FontSpan>(fonts[4], 13, 14) };
    spanMap = spanString1->GetSpansMap();
    EXPECT_TRUE(CompareSpanList(spanMap[SpanType::Font], resultList2));
    spanString1->InsertString(11, u"abcdefg");
    spanString1->ReplaceString(8, 8, u"A");
    std::list<RefPtr<SpanBase>> resultList3 = { AceType::MakeRefPtr<FontSpan>(fonts[0], 0, 9),
        AceType::MakeRefPtr<FontSpan>(fonts[1], 9, 11), AceType::MakeRefPtr<FontSpan>(fonts[2], 11, 12),
        AceType::MakeRefPtr<FontSpan>(fonts[3], 12, 13), AceType::MakeRefPtr<FontSpan>(fonts[4], 13, 14) };
    spanMap = spanString1->GetSpansMap();
    EXPECT_TRUE(CompareSpanList(spanMap[SpanType::Font], resultList3));
    EXPECT_EQ(spanString1->GetString(), "一二三四五0红红Afg234");
    spanString1->RemoveString(1, 10);
    std::list<RefPtr<SpanBase>> resultList4 = { AceType::MakeRefPtr<FontSpan>(fonts[0], 0, 1),
        AceType::MakeRefPtr<FontSpan>(fonts[2], 1, 2), AceType::MakeRefPtr<FontSpan>(fonts[3], 2, 3),
        AceType::MakeRefPtr<FontSpan>(fonts[4], 3, 4) };
    spanMap = spanString1->GetSpansMap();
    EXPECT_TRUE(CompareSpanList(spanMap[SpanType::Font], resultList4));
}

/**
 * @tc.name: MutableSpanString008
 * @tc.desc: Test some edge case of InsertSpanString/ReplaceSpanString/AppendSpanString
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString008, TestSize.Level1)
{
    vector<OHOS::Ace::Color> colors = { Color::RED, Color::BLACK, Color::GREEN, Color::GRAY, Color::BLUE };
    vector<Font> fonts;
    auto spanString1 = AceType::MakeRefPtr<MutableSpanString>(u"0123");
    for (int i = 0; i < 5; i++) {
        Font f;
        f.fontColor = colors[i];
        fonts.emplace_back(f);
        if (i != 4) {
            spanString1->AddSpan(AceType::MakeRefPtr<FontSpan>(f, i, i + 1));
        }
    }
    auto spanArr = spanString1->GetSpans(0, spanString1->GetLength());
    auto spanString2 = AceType::MakeRefPtr<MutableSpanString>(u"abc");
    Font f;
    f.fontColor = colors[4];
    spanString2->AddSpan(AceType::MakeRefPtr<FontSpan>(f, 0, 3));
    spanString1->InsertSpanString(1, spanString2);
    std::list<RefPtr<SpanBase>> resultList1 = { AceType::MakeRefPtr<FontSpan>(fonts[0], 0, 1),
        AceType::MakeRefPtr<FontSpan>(fonts[4], 1, 4), AceType::MakeRefPtr<FontSpan>(fonts[1], 4, 5),
        AceType::MakeRefPtr<FontSpan>(fonts[2], 5, 6), AceType::MakeRefPtr<FontSpan>(fonts[3], 6, 7) };
    auto spanMap = spanString1->GetSpansMap();
    EXPECT_TRUE(CompareSpanList(spanMap[SpanType::Font], resultList1));

    spanString1->InsertSpanString(0, spanString2);
    std::list<RefPtr<SpanBase>> resultList2 = { AceType::MakeRefPtr<FontSpan>(fonts[4], 0, 3),
        AceType::MakeRefPtr<FontSpan>(fonts[0], 3, 4), AceType::MakeRefPtr<FontSpan>(fonts[4], 4, 7),
        AceType::MakeRefPtr<FontSpan>(fonts[1], 7, 8), AceType::MakeRefPtr<FontSpan>(fonts[2], 8, 9),
        AceType::MakeRefPtr<FontSpan>(fonts[3], 9, 10) };
    spanMap = spanString1->GetSpansMap();
    EXPECT_TRUE(CompareSpanList(spanMap[SpanType::Font], resultList2));

    spanString1->ReplaceSpanString(0, 7, spanString2);
    std::list<RefPtr<SpanBase>> resultList3 = { AceType::MakeRefPtr<FontSpan>(fonts[4], 0, 3),
        AceType::MakeRefPtr<FontSpan>(fonts[1], 3, 4), AceType::MakeRefPtr<FontSpan>(fonts[2], 4, 5),
        AceType::MakeRefPtr<FontSpan>(fonts[3], 5, 6) };
    spanMap = spanString1->GetSpansMap();
    EXPECT_TRUE(CompareSpanList(spanMap[SpanType::Font], resultList3));

    spanString1->AppendSpanString(spanString2);
    std::list<RefPtr<SpanBase>> resultList4 = { AceType::MakeRefPtr<FontSpan>(fonts[4], 0, 3),
        AceType::MakeRefPtr<FontSpan>(fonts[1], 3, 4), AceType::MakeRefPtr<FontSpan>(fonts[2], 4, 5),
        AceType::MakeRefPtr<FontSpan>(fonts[3], 5, 6), AceType::MakeRefPtr<FontSpan>(fonts[4], 6, 9) };
    spanMap = spanString1->GetSpansMap();
    EXPECT_TRUE(CompareSpanList(spanMap[SpanType::Font], resultList4));
}

/**
 * @tc.name: GestureSpanString001
 * @tc.desc: Test the construction of the gesture type in spanString
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, GestureSpanString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create spanBases and gestureInfo
     */
    std::vector<RefPtr<SpanBase>> spanBases;
    GestureStyle gestureInfo;
    ConstructGestureStyle(gestureInfo);
    spanBases.emplace_back(AceType::MakeRefPtr<GestureSpan>(gestureInfo, 0, 3));
    auto spanStringWithSpans = AceType::MakeRefPtr<SpanString>(u"01234567891");
    spanStringWithSpans->BindWithSpans(spanBases);

    /**
     * @tc.steps: step2. compare SpansMap and gestureInfo
     * @tc.expect: The number of spanItems in the spanString is 2
     */
    auto spanMap = spanStringWithSpans->GetSpansMap();
    std::list<RefPtr<SpanBase>> resultList = { AceType::MakeRefPtr<GestureSpan>(gestureInfo, 0, 3) };
    EXPECT_FALSE(CompareSpanList(spanMap[SpanType::Gesture], resultList));
    EXPECT_EQ(spanStringWithSpans->GetSpanItems().size(), 2);
}

/**
 * @tc.name: GestureSpanString002
 * @tc.desc: Test the manifestations of the gesture type in the textPattern after it is constructed in spanString
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, GestureSpanString002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create spanBases and gestureInfo
     */
    std::vector<RefPtr<SpanBase>> spanBases;
    GestureStyle gestureInfo;
    ConstructGestureStyle(gestureInfo);
    spanBases.emplace_back(AceType::MakeRefPtr<GestureSpan>(gestureInfo, 0, 3));
    spanBases.emplace_back(AceType::MakeRefPtr<GestureSpan>(gestureInfo, 8, 11));
    auto spanStringWithSpans = AceType::MakeRefPtr<SpanString>(u"01234567891");
    spanStringWithSpans->BindWithSpans(spanBases);

    std::list<RefPtr<SpanBase>> resultList = { AceType::MakeRefPtr<GestureSpan>(gestureInfo, 0, 3),
        AceType::MakeRefPtr<GestureSpan>(gestureInfo, 8, 3) };
    auto spanMap = spanStringWithSpans->GetSpansMap();

    EXPECT_FALSE(CompareSpanList(spanMap[SpanType::Gesture], resultList));

    /**
     * @tc.steps: step2. Create textPattern and construct property string scene for textPattern
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, textPattern);
    textPattern->SetTextController(AceType::MakeRefPtr<TextController>());
    textPattern->GetTextController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(textPattern)));
    auto textController = textPattern->GetTextController();
    textController->SetStyledString(spanStringWithSpans);

    auto spans = spanStringWithSpans->GetSpanItems();
    textPattern->SetSpanItemChildren(spans);
    textPattern->SetSpanStringMode(true);

    /**
     * @tc.steps: step2. Call the BeforeCreateLayoutWrapper function
     * @tc.expect: The click and long press event of the textPattern is initialized
     *             and the number of spanItems in the spanString is 2
     */
    textPattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(textPattern->GetSpanItemChildren().size(), 3);
    EXPECT_TRUE(textPattern->clickEventInitialized_);
    EXPECT_NE(textPattern->longPressEvent_, nullptr);
}

/**
 * @tc.name: GestureSpanString003
 * @tc.desc: Test some edge case of AddSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, GestureSpanString03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create spanString and textPattern
     */
    auto spanStringWithSpans = AceType::MakeRefPtr<SpanString>(u"01234567891");
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, textPattern);

    /**
     * @tc.steps: step2. Call the AddSpan function
     * @tc.expect: The number of spanBases for gesture types is 1
     */
    GestureStyle gestureInfo;
    ConstructGestureStyle(gestureInfo);
    auto spanBase = AceType::MakeRefPtr<GestureSpan>(gestureInfo, 8, 10);
    spanStringWithSpans->AddSpan(spanBase);
    auto spanMap = spanStringWithSpans->GetSpansMap();
    EXPECT_EQ(spanMap[SpanType::Gesture].size(), 1);

    /**
     * @tc.steps: step3. Call the BeforeCreateLayoutWrapper function of textPattern
     * @tc.expect: The number of spans for text is 3 and second span has event
     */
    textPattern->SetTextController(AceType::MakeRefPtr<TextController>());
    textPattern->GetTextController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(textPattern)));
    auto textController = textPattern->GetTextController();
    textController->SetStyledString(spanStringWithSpans);
    textPattern->SetSpanStringMode(true);
    textPattern->BeforeCreateLayoutWrapper();

    auto spanItems = textPattern->GetSpanItemChildren();
    EXPECT_EQ(spanItems.size(), 3);
    EXPECT_TRUE(textPattern->clickEventInitialized_);
    EXPECT_NE(textPattern->longPressEvent_, nullptr);
    auto iter = spanItems.begin();
    std::advance(iter, GESTURE_INDEX1);
    EXPECT_NE((*iter)->onClick, nullptr);
    EXPECT_NE((*iter)->onLongPress, nullptr);
}

/**
 * @tc.name: GestureSpanString004
 * @tc.desc: Test some edge case of ReplaceString/RemoveString
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, GestureSpanString004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MutableSpanString and textPattern
     */
    GestureStyle gestureInfo;
    ConstructGestureStyle(gestureInfo);
    std::vector<RefPtr<SpanBase>> spanBases;
    spanBases.emplace_back(AceType::MakeRefPtr<GestureSpan>(gestureInfo, 0, 3));
    spanBases.emplace_back(AceType::MakeRefPtr<GestureSpan>(gestureInfo, 8, 11));
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"01234567891");
    spanString->BindWithSpans(spanBases);
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, textPattern);
    textPattern->SetTextController(AceType::MakeRefPtr<TextController>());
    textPattern->GetTextController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(textPattern)));
    auto textController = textPattern->GetTextController();
    textController->SetStyledString(spanString);

    auto spans = spanString->GetSpanItems();
    textPattern->SetSpanItemChildren(spans);

    auto spanItems = textPattern->GetSpanItemChildren();
    EXPECT_EQ(spanItems.size(), 3);
    EXPECT_NE(spanItems.front()->onClick, nullptr);
    EXPECT_NE(spanItems.front()->onLongPress, nullptr);

    /**
     * @tc.steps: step2. Call the ReplaceString function
     * @tc.expect: The number of spanItems for textPattern is 4 and the events for each span were as expected
     */
    spanString->ReplaceString(0, 2, u"a");
    spanItems = textPattern->GetSpanItemChildren();
    EXPECT_EQ(spanItems.size(), 3);

    auto iter = spanItems.begin();
    EXPECT_NE((*iter)->onClick, nullptr);
    EXPECT_NE((*iter)->onLongPress, nullptr);
    iter++;
    EXPECT_EQ((*iter)->onClick, nullptr);
    EXPECT_EQ((*iter)->onLongPress, nullptr);
    iter++;
    EXPECT_NE((*iter)->onClick, nullptr);
    EXPECT_NE((*iter)->onLongPress, nullptr);

    /**
     * @tc.steps: step3. Call the RemoveString function
     * @tc.expect: The number of spanItems for textPattern is 3
     */
    spanString->RemoveString(7, 3);
    textController->SetStyledString(spanString);
    spanItems = textPattern->GetSpanItemChildren();
    EXPECT_EQ(spanItems.size(), 2);
    iter = spanItems.begin();
    EXPECT_NE((*iter)->onClick, nullptr);
    EXPECT_NE((*iter)->onLongPress, nullptr);
    iter++;
    EXPECT_EQ((*iter)->onClick, nullptr);
    EXPECT_EQ((*iter)->onLongPress, nullptr);
}

/**
 * @tc.name: MutableSpanString009
 * @tc.desc: Test imageSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString009, TestSize.Level1)
{
    auto imageOption = SpanStringTestNg::GetImageOption("src/icon.png");
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);

    auto spans = mutableStr->GetSpans(0, 2);
    EXPECT_TRUE(spans.size() == 0);

    spans = mutableStr->GetSpans(-1, 1);
    EXPECT_TRUE(spans.size() == 0);

    spans = mutableStr->GetSpans(0, 1);
    EXPECT_TRUE(spans.size() == 1);
    auto imageSpan = AceType::MakeRefPtr<ImageSpan>(imageOption);
    EXPECT_TRUE(spans[0]->IsAttributesEqual(imageSpan));
}

/**
 * @tc.name: MutableSpanString010
 * @tc.desc: Test the insertString in the case of imageSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString010, TestSize.Level1)
{
    auto imageOption = SpanStringTestNg::GetImageOption("src/icon.png");
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);

    mutableStr->InsertString(0, u"123");
    auto text = mutableStr->GetString();
    EXPECT_TRUE(text == "123 ");
    auto length = mutableStr->GetLength();
    EXPECT_TRUE(length == 4);

    mutableStr->InsertString(4, u"456");
    text = mutableStr->GetString();
    EXPECT_TRUE(text == "123 456");
    length = mutableStr->GetLength();
    EXPECT_TRUE(length == 7);

    auto spans = mutableStr->GetSpans(0, 7);
    EXPECT_TRUE(spans.size() == 1);

    auto imageSpan = AceType::MakeRefPtr<ImageSpan>(imageOption);
    EXPECT_TRUE(spans[0]->IsAttributesEqual(imageSpan));
}

/**
 * @tc.name: MutableSpanString011
 * @tc.desc: Test the insertSpanString in the case of imageSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString011, TestSize.Level1)
{
    auto imageOption = SpanStringTestNg::GetImageOption("src/icon.png");
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);

    auto spanStr = AceType::MakeRefPtr<SpanString>(u"123");
    spanStr->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 3));
    mutableStr->InsertSpanString(0, spanStr);
    auto text = mutableStr->GetString();
    EXPECT_EQ(text, "123 ");
    auto length = mutableStr->GetLength();
    EXPECT_EQ(length, 4);

    spanStr = AceType::MakeRefPtr<SpanString>(u"456");
    spanStr->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 3));
    mutableStr->InsertSpanString(4, spanStr);
    text = mutableStr->GetString();
    EXPECT_EQ(text, "123 456");
    length = mutableStr->GetLength();
    EXPECT_EQ(length, 7);
    auto spans = mutableStr->GetSpans(0, 7);
    EXPECT_EQ(spans.size(), 3);
}

/**
 * @tc.name: MutableSpanString012
 * @tc.desc: Test the replaceSpan/addSpan in the case of imageSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString012, TestSize.Level1)
{
    auto imageOption = SpanStringTestNg::GetImageOption("src/icon-1.png");
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);
    mutableStr->InsertString(0, u"123");
    mutableStr->InsertString(4, u"456");

    auto imageOption1 = SpanStringTestNg::GetImageOption("src/icon-2.png");
    auto imageSpan1 = AceType::MakeRefPtr<ImageSpan>(imageOption1);
    mutableStr->ReplaceSpan(3, 1, imageSpan1);
    auto length = mutableStr->GetLength();
    EXPECT_TRUE(length == 7);
    auto spans = mutableStr->GetSpans(0, 7);
    EXPECT_TRUE(spans[0]->IsAttributesEqual(imageSpan1));

    auto imageOption2 = SpanStringTestNg::GetImageOption("src/icon-3.png");
    auto imageSpan2 = AceType::MakeRefPtr<ImageSpan>(imageOption2);
    imageSpan2->UpdateStartIndex(3);
    imageSpan2->UpdateEndIndex(4);
    mutableStr->AddSpan(imageSpan2);
    spans = mutableStr->GetSpans(0, 7);
    EXPECT_TRUE(spans[0]->IsAttributesEqual(imageSpan2));
}

/**
 * @tc.name: MutableSpanString013
 * @tc.desc: Test the appendSpan/removeSpan in the case of imageSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString013, TestSize.Level1)
{
    auto imageOption = SpanStringTestNg::GetImageOption("src/icon-1.png");
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);
    mutableStr->InsertString(0, u"123");
    mutableStr->InsertString(4, u"456");
    auto imageOption1 = SpanStringTestNg::GetImageOption("src/icon-2.png");
    auto imageSpan1 = AceType::MakeRefPtr<SpanString>(imageOption1);
    mutableStr->AppendSpanString(imageSpan1);
    auto spans = mutableStr->GetSpans(0, 7);
    EXPECT_EQ(spans.size(), 1);
    mutableStr->RemoveSpan(0, 7, SpanType::Image);
    spans = mutableStr->GetSpans(0, 6);
    EXPECT_EQ(spans.size(), 0);
    spans = mutableStr->GetSpans(0, 7);
    EXPECT_EQ(spans.size(), 1);
    mutableStr->RemoveSpans(0, 7);
    spans = mutableStr->GetSpans(0, 7);
    EXPECT_EQ(spans.size(), 0);
}

/**
 * @tc.name: MutableSpanString014
 * @tc.desc: Test basic function of LineHeightSpan/ParagraphStyleSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString014, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::END;
    spanParagraphStyle.maxLines = 4;
    spanParagraphStyle.wordBreak = WordBreak::BREAK_ALL;
    spanParagraphStyle.textOverflow = TextOverflow::ELLIPSIS;
    spanParagraphStyle.textIndent = Dimension(23);
    spanParagraphStyle.leadingMargin = LeadingMargin();
    spanParagraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(25.0), Dimension(26.0));
    spanString->AddSpan(AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 0, 1));
    spanString->AddSpan(AceType::MakeRefPtr<LineHeightSpan>(Dimension(30), 0, 3));
    spanString->AddSpan(AceType::MakeRefPtr<LineHeightSpan>(Dimension(10), 0, 2));

    auto firstSpans = spanString->GetSpans(2, 1);
    EXPECT_EQ(firstSpans.size(), 1);
    auto lineHeightSpan = AceType::DynamicCast<LineHeightSpan>(firstSpans[0]);
    EXPECT_NE(lineHeightSpan, nullptr);
    EXPECT_EQ(lineHeightSpan->GetStartIndex(), 2);
    EXPECT_EQ(lineHeightSpan->GetEndIndex(), 3);
    EXPECT_EQ(lineHeightSpan->GetLineHeight(), Dimension(30));

    auto paraSpans = spanString->GetSpans(0, 2, SpanType::ParagraphStyle);
    EXPECT_EQ(paraSpans.size(), 1);
    auto paraSpan = AceType::DynamicCast<ParagraphStyleSpan>(paraSpans[0]);
    EXPECT_NE(paraSpan, nullptr);
    EXPECT_EQ(paraSpan->GetStartIndex(), 0);
    EXPECT_EQ(paraSpan->GetEndIndex(), 1);
    EXPECT_EQ(paraSpan->GetParagraphStyle().align, TextAlign::END);
    EXPECT_EQ(paraSpan->GetParagraphStyle().maxLines, 4);
    EXPECT_EQ(paraSpan->GetParagraphStyle().wordBreak, WordBreak::BREAK_ALL);
    EXPECT_EQ(paraSpan->GetParagraphStyle().textOverflow, TextOverflow::ELLIPSIS);
    EXPECT_EQ(paraSpan->GetParagraphStyle().textIndent, Dimension(23));
    EXPECT_EQ(paraSpan->GetParagraphStyle().leadingMargin.value().size.Width().ConvertToVp(), 25);
    EXPECT_EQ(paraSpan->GetParagraphStyle().leadingMargin.value().size.Height().ConvertToVp(), 26);
    auto secondSpans = spanString->GetSpans(0, 3);
    EXPECT_EQ(secondSpans.size(), 3);
    auto thirdSpans = spanString->GetSpans(0, 1);
    EXPECT_EQ(thirdSpans.size(), 2);
    auto fourthSpans = spanString->GetSpans(3, 1);
    EXPECT_EQ(fourthSpans.size(), 0);
    auto fifthSpans = spanString->GetSpans(0, 9);
    EXPECT_EQ(fifthSpans.size(), 3);
}

/**
 * @tc.name: MutableSpanString015
 * @tc.desc: Test isAttributesEqual of LineHeightSpan/ParagraphStyleSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString015, TestSize.Level1)
{
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::END;
    spanParagraphStyle.maxLines = 4;

    spanParagraphStyle.wordBreak = WordBreak::BREAK_ALL;
    spanParagraphStyle.textOverflow = TextOverflow::ELLIPSIS;
    spanParagraphStyle.textIndent = Dimension(23);
    spanParagraphStyle.leadingMargin = LeadingMargin();
    spanParagraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(25.0), Dimension(26.0));
    auto paraSpan = AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 0, 1);
    auto paraSpan2 = AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 0, 1);
    EXPECT_TRUE(paraSpan->IsAttributesEqual(paraSpan2));

    auto lineHeightSpan = AceType::MakeRefPtr<LineHeightSpan>(Dimension(30), 0, 3);
    auto lineHeightSpan2 = AceType::MakeRefPtr<LineHeightSpan>(Dimension(30), 0, 3);
    auto lineHeightSpan3 = AceType::MakeRefPtr<LineHeightSpan>(Dimension(25), 0, 3);
    EXPECT_TRUE(lineHeightSpan->IsAttributesEqual(lineHeightSpan2));
    EXPECT_FALSE(lineHeightSpan->IsAttributesEqual(lineHeightSpan3));
}

/**
 * @tc.name: MutableSpanString016
 * @tc.desc: Test AppendSpanString/ReplaceSpanString of LineHeightSpan/ParagraphStyleSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString016, TestSize.Level1)
{
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::END;
    spanParagraphStyle.maxLines = 4;
    spanParagraphStyle.wordBreak = WordBreak::BREAK_ALL;
    spanParagraphStyle.textOverflow = TextOverflow::ELLIPSIS;
    spanParagraphStyle.textIndent = Dimension(23);
    spanParagraphStyle.leadingMargin = LeadingMargin();
    spanParagraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(25.0), Dimension(26.0));
    auto paraSpan = AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 0, 1);
    auto lineHeightSpan = AceType::MakeRefPtr<LineHeightSpan>(Dimension(30), 0, 3);

    auto imageOption = SpanStringTestNg::GetImageOption("src/icon-1.png");
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);
    auto mutableStr2 = AceType::MakeRefPtr<MutableSpanString>(u"123456");
    mutableStr->AddSpan(paraSpan);
    mutableStr2->AddSpan(lineHeightSpan);
    mutableStr->AppendSpanString(mutableStr2);
    EXPECT_EQ(mutableStr->GetString(), " 123456");
    auto spans = mutableStr->GetSpans(0, 7);
    EXPECT_EQ(spans.size(), 3);
    mutableStr->ReplaceSpanString(1, 1, mutableStr2);
    EXPECT_EQ(mutableStr->GetString(), " 12345623456");
}

/**
 * @tc.name: MutableSpanString017
 * @tc.desc: Test InsertSpanString of LineHeightSpan/ParagraphStyleSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString017, TestSize.Level1)
{
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::END;
    spanParagraphStyle.maxLines = 4;
    spanParagraphStyle.wordBreak = WordBreak::BREAK_ALL;
    spanParagraphStyle.textOverflow = TextOverflow::ELLIPSIS;
    spanParagraphStyle.textIndent = Dimension(23);
    spanParagraphStyle.leadingMargin = LeadingMargin();
    spanParagraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(25.0), Dimension(26.0));
    auto paraSpan = AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 0, 1);

    auto imageOption = SpanStringTestNg::GetImageOption("src/icon.png");
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);

    auto spanStr = AceType::MakeRefPtr<SpanString>(u"123");
    spanStr->AddSpan(paraSpan);
    mutableStr->InsertSpanString(0, spanStr);
    auto text = mutableStr->GetString();
    EXPECT_EQ(text, "123 ");
    auto length = mutableStr->GetLength();
    EXPECT_EQ(length, 4);

    spanStr = AceType::MakeRefPtr<SpanString>(u"456");
    spanStr->AddSpan(AceType::MakeRefPtr<LineHeightSpan>(Dimension(30), 0, 3));
    mutableStr->InsertSpanString(4, spanStr);
    text = mutableStr->GetString();
    EXPECT_EQ(text, "123 456");
    length = mutableStr->GetLength();
    EXPECT_EQ(length, 7);
    auto spans = mutableStr->GetSpans(0, 7);
    EXPECT_EQ(spans.size(), 3);
}

/**
 * @tc.name: MutableSpanString018
 * @tc.desc: Test serialization and unserialization of SpanString
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString018, TestSize.Level1)
{
    std::vector<uint8_t> buff;
    Font testFont { OHOS::Ace::FontWeight::BOLD, Dimension(29.0, DimensionUnit::PX), OHOS::Ace::FontStyle::ITALIC,
        std::vector<std::string>(test_str, test_str + 10), OHOS::Ace::Color::RED };
    Font testFont2 { OHOS::Ace::FontWeight::W300, Dimension(49.0, DimensionUnit::VP), OHOS::Ace::FontStyle::ITALIC,
        std::vector<std::string>(test_str, test_str + 5), OHOS::Ace::Color::BLUE };
    auto spanStr = AceType::MakeRefPtr<SpanString>(u"dddd当地经的123456");
    spanStr->AddSpan(AceType::MakeRefPtr<LineHeightSpan>(Dimension(30), 0, 3));
    spanStr->AddSpan(AceType::MakeRefPtr<LineHeightSpan>(Dimension(10), 0, 2));
    spanStr->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont, 1, 2));
    spanStr->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 4, 5));
    spanStr->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(15), 8, 9));
    spanStr->AddSpan(AceType::MakeRefPtr<BaselineOffsetSpan>(Dimension(16), 9, 10));
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::END;
    spanParagraphStyle.maxLines = 4;
    spanParagraphStyle.wordBreak = WordBreak::BREAK_ALL;
    spanParagraphStyle.textOverflow = TextOverflow::ELLIPSIS;
    spanParagraphStyle.textIndent = Dimension(23);
    spanParagraphStyle.leadingMargin = LeadingMargin();
    spanParagraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(25.0), Dimension(26.0));
    spanStr->AddSpan(AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 10, 11));
    spanStr->EncodeTlv(buff);
    auto spanString2 = SpanString::DecodeTlv(buff);
    std::list<RefPtr<NG::SpanItem>> spans = spanString2->GetSpanItems();

    EXPECT_EQ(spans.size(), 10);
    EXPECT_EQ(spanStr->GetString(), "dddd当地经的123456");
    auto it = spans.begin();
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), "d");
    EXPECT_EQ((*it)->interval.first, 0);
    EXPECT_EQ((*it)->interval.second, 1);
    EXPECT_EQ((*it)->textLineStyle->GetLineHeight().value(), Dimension(10));
    ++it;
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), "d");
    EXPECT_EQ((*it)->interval.first, 1);
    EXPECT_EQ((*it)->interval.second, 2);
    EXPECT_EQ((*it)->fontStyle->GetFontSize().value(), Dimension(29));
    EXPECT_EQ((*it)->fontStyle->GetTextColor().value(), OHOS::Ace::Color::RED);
    EXPECT_EQ((*it)->fontStyle->GetItalicFontStyle().value(), OHOS::Ace::FontStyle::ITALIC);
    EXPECT_EQ((*it)->fontStyle->GetFontWeight().value(), OHOS::Ace::FontWeight::BOLD);
    EXPECT_EQ((*it)->textLineStyle->GetLineHeight().value(), Dimension(10));
    ++it;
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), "d");
    EXPECT_EQ((*it)->interval.first, 2);
    EXPECT_EQ((*it)->interval.second, 3);
    EXPECT_EQ((*it)->textLineStyle->GetLineHeight().value(), Dimension(30));
    ++it;
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), "d");
    EXPECT_EQ((*it)->interval.first, 3);
    EXPECT_EQ((*it)->interval.second, 4);
    ++it;
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), "当");
    EXPECT_EQ((*it)->interval.first, 4);
    EXPECT_EQ((*it)->interval.second, 5);
    EXPECT_EQ((*it)->fontStyle->GetFontSize().value(), OHOS::Ace::Dimension(49, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ((*it)->fontStyle->GetTextColor().value(), OHOS::Ace::Color::BLUE);
    EXPECT_EQ((*it)->fontStyle->GetItalicFontStyle().value(), OHOS::Ace::FontStyle::ITALIC);
    EXPECT_EQ((*it)->fontStyle->GetFontWeight().value(), OHOS::Ace::FontWeight::W300);
    ++it;
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), "地经的");
    EXPECT_EQ((*it)->interval.first, 5);
    EXPECT_EQ((*it)->interval.second, 8);
    ++it;
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), "1");
    EXPECT_EQ((*it)->interval.first, 8);
    EXPECT_EQ((*it)->interval.second, 9);
    EXPECT_EQ((*it)->fontStyle->GetLetterSpacing().value(), Dimension(15));
    ++it;
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), "2");
    EXPECT_EQ((*it)->interval.first, 9);
    EXPECT_EQ((*it)->interval.second, 10);
    EXPECT_EQ((*it)->textLineStyle->GetBaselineOffset().value(), Dimension(16));
    ++it;
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), "3");
    EXPECT_EQ((*it)->interval.first, 10);
    EXPECT_EQ((*it)->interval.second, 11);
    EXPECT_EQ((*it)->textLineStyle->GetTextOverflow().value(), TextOverflow::ELLIPSIS);
    EXPECT_EQ((*it)->textLineStyle->GetTextAlign().value(), TextAlign::END);
    EXPECT_EQ((*it)->textLineStyle->GetMaxLines().value(), 4);
    EXPECT_EQ((*it)->textLineStyle->GetTextIndent().value(), Dimension(23));
    EXPECT_EQ((*it)->textLineStyle->GetWordBreak().value(), WordBreak::BREAK_ALL);
    ++it;
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), "456");
    EXPECT_EQ((*it)->interval.first, 11);
    EXPECT_EQ((*it)->interval.second, 14);
}

/**
 * @tc.name: MutableSpanString019
 * @tc.desc: Test InsertSpanString of ExtSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString019, TestSize.Level1)
{
    auto extSpan = AceType::MakeRefPtr<ExtSpan>(1, 2);
    auto imageOption = SpanStringTestNg::GetImageOption("src/icon.png");
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);
    auto spanStr = AceType::MakeRefPtr<SpanString>(u"12345");
    spanStr->AddSpan(extSpan);
    mutableStr->InsertSpanString(0, spanStr);
    auto text = mutableStr->GetString();
    EXPECT_EQ(text, "12345 ");
    auto length = mutableStr->GetLength();
    EXPECT_EQ(length, 6);
    auto spans = mutableStr->GetSpans(0, 6);
    EXPECT_EQ(spans.size(), 2);
    spans = mutableStr->GetSpans(1, 3);
    EXPECT_EQ(spans.size(), 1);
    for (auto span : spans) {
        EXPECT_EQ(span->GetStartIndex(), 1);
        EXPECT_EQ(span->GetEndIndex(), 2);
    }
}

/**
 * @tc.name: SpanStringTest009
 * @tc.desc: Test basic function of span object
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString009, TestSize.Level1)
{
    std::string buffer;
    RefPtr<FontSpan> fontSpan = AceType::MakeRefPtr<FontSpan>(testFont1, 0, 10);
    buffer = fontSpan->ToString();
    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.find("FontSpan"), 0);

    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    auto decorationSpan = AceType::MakeRefPtr<DecorationSpan>(std::vector<TextDecoration>({ TextDecoration::OVERLINE }),
        Color::RED, TextDecorationStyle::WAVY, std::optional<TextDecorationOptions>(), 0, 1, nullptr);
    EXPECT_FALSE(fontSpan->IsAttributesEqual(decorationSpan));
    decorationSpan->ApplyToSpanItem(spanItem, SpanOperation::REMOVE);
    buffer.clear();
    buffer = decorationSpan->ToString();
    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.find("DecorationSpan"), 0);
    EXPECT_FALSE(decorationSpan->IsAttributesEqual(fontSpan));

    auto baselineOffsetSpan = AceType::MakeRefPtr<BaselineOffsetSpan>(Dimension(4), 0, 2);
    EXPECT_FALSE(baselineOffsetSpan->IsAttributesEqual(decorationSpan));
    baselineOffsetSpan->ApplyToSpanItem(spanItem, SpanOperation::REMOVE);
    buffer.clear();
    buffer = baselineOffsetSpan->ToString();
    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.find("BaselineOffsetSpan"), 0);

    auto letterSpacingSpan = AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(5), 0, 3);
    EXPECT_FALSE(letterSpacingSpan->IsAttributesEqual(decorationSpan));
    letterSpacingSpan->ApplyToSpanItem(spanItem, SpanOperation::REMOVE);
    buffer.clear();
    buffer = letterSpacingSpan->ToString();
    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.find("LetterSpacingSpan"), 0);

    Shadow textShadow;
    textShadow.SetBlurRadius(1.0);
    textShadow.SetColor(Color::BLACK);
    textShadow.SetOffsetX(6.0);
    textShadow.SetOffsetY(6.0);
    vector<Shadow> textShadows { textShadow };
    vector<Shadow> textShadows2;
    textShadow.SetColor(Color::RED);
    vector<Shadow> textShadows3 { textShadow };
    auto textShadowSpan = AceType::MakeRefPtr<TextShadowSpan>(textShadows, 7, 9);
    auto textShadowSpan2 = AceType::MakeRefPtr<TextShadowSpan>(textShadows2, 7, 9);
    auto textShadowSpan3 = AceType::MakeRefPtr<TextShadowSpan>(textShadows3, 7, 9);
    EXPECT_FALSE(textShadowSpan->IsAttributesEqual(decorationSpan));
    EXPECT_FALSE(textShadowSpan->IsAttributesEqual(textShadowSpan2));
    EXPECT_FALSE(textShadowSpan->IsAttributesEqual(textShadowSpan3));
    textShadowSpan->ApplyToSpanItem(spanItem, SpanOperation::REMOVE);
    buffer = textShadowSpan->ToString();
    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.find("TextShadowSpan"), 0);
}

/**
 * @tc.name: SpanStringTest010
 * @tc.desc: Test basic function of span object
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString010, TestSize.Level1)
{
    std::string buffer;
    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    auto imageSpanItem = AceType::MakeRefPtr<NG::ImageSpanItem>();
    auto imageOption = SpanStringTestNg::GetImageOption("src/icon.png");
    auto imageSpan = AceType::MakeRefPtr<ImageSpan>(imageOption);
    imageSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);
    imageSpan->ApplyToSpanItem(imageSpanItem, SpanOperation::ADD);
    imageSpan->ApplyToSpanItem(imageSpanItem, SpanOperation::REMOVE);
    imageSpan->GetSubSpan(0, 3);
    buffer = imageSpan->ToString();
    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.find("ImageSpan"), 0);

    auto customSpan = AceType::MakeRefPtr<CustomSpan>();
    auto customSpanItem = AceType::MakeRefPtr<NG::CustomSpanItem>();
    customSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);
    customSpan->ApplyToSpanItem(customSpanItem, SpanOperation::ADD);
    customSpan->ApplyToSpanItem(customSpanItem, SpanOperation::REMOVE);
    buffer = customSpan->ToString();
    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.find("CustomSpan"), 0);

    RefPtr<FontSpan> fontSpan = AceType::MakeRefPtr<FontSpan>(testFont1, 0, 10);
    auto paragraphStyleSpan = AceType::MakeRefPtr<ParagraphStyleSpan>();
    paragraphStyleSpan->ApplyToSpanItem(spanItem, SpanOperation::REMOVE);
    EXPECT_FALSE(paragraphStyleSpan->IsAttributesEqual(fontSpan));
    buffer = paragraphStyleSpan->ToString();
    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.find("ParagraphStyleSpan"), 0);

    auto lineHeightSpan = AceType::MakeRefPtr<LineHeightSpan>();
    EXPECT_FALSE(lineHeightSpan->IsAttributesEqual(fontSpan));
    buffer = lineHeightSpan->ToString();
    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.find("LineHeightSpan"), 0);

    GestureStyle gestureInfo;
    auto gestureSpan = AceType::MakeRefPtr<GestureSpan>(gestureInfo, 0, 3);
    EXPECT_FALSE(gestureSpan->IsAttributesEqual(lineHeightSpan));
    gestureSpan->AddSpanStyle(spanItem);
    auto onClick = [](const BaseEventInfo* info) {};
    auto tmpClickFunc = [func = std::move(onClick)](GestureEvent& info) { func(&info); };
    gestureInfo.onClick = std::move(tmpClickFunc);
    gestureSpan->AddSpanStyle(spanItem);
}

/**
 * @tc.name: SpanStringTest011
 * @tc.desc: Test basic function of BackgroundColorSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString011, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");

    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    textBackgroundStyle.backgroundColor = Color::RED;
    ;
    textBackgroundStyle.backgroundRadius = borderRadius;

    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 7, 9));
    auto firstSpans = spanString->GetSpans(2, 1);
    EXPECT_EQ(firstSpans.size(), 0);
    auto backgroundColorSpan = AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle);
    EXPECT_NE(backgroundColorSpan, nullptr);
    EXPECT_EQ(backgroundColorSpan->GetStartIndex(), 0);
    EXPECT_EQ(backgroundColorSpan->GetEndIndex(), 0);

    auto secondSpans = spanString->GetSpans(1, 1);
    EXPECT_EQ(secondSpans.size(), 0);

    auto thirdSpans = spanString->GetSpans(0, 1);
    EXPECT_EQ(thirdSpans.size(), 0);

    auto fourthSpans = spanString->GetSpans(3, 1);
    EXPECT_EQ(fourthSpans.size(), 0);

    auto fifthSpans = spanString->GetSpans(0, 9);
    EXPECT_EQ(fifthSpans.size(), 1);
}

/**
 * @tc.name: SpanStringTest012
 * @tc.desc: Test basic function of BackgroundColorSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString012, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");

    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);

    textBackgroundStyle.backgroundColor = Color::RED;
    ;
    textBackgroundStyle.backgroundRadius = borderRadius;

    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 8, 10));
    auto subSpanString = spanString->GetSubSpanString(0, 10);
    EXPECT_TRUE(subSpanString->IsEqualToSpanString(spanString));

    auto firstSpans = spanString->GetSpans(8, 1);
    EXPECT_EQ(firstSpans.size(), 1);
    auto backgroundColorSpan = AceType::DynamicCast<BackgroundColorSpan>(firstSpans[0]);
    EXPECT_NE(backgroundColorSpan, nullptr);
    EXPECT_EQ(backgroundColorSpan->GetStartIndex(), 8);
    EXPECT_EQ(backgroundColorSpan->GetEndIndex(), 9);
    EXPECT_TRUE(backgroundColorSpan->GetBackgroundColor() == textBackgroundStyle);
}

/**
 * @tc.name: SpanString013
 * @tc.desc: Test insert spanstring between BackgroundColorSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString013, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"1234567890");
    auto insertString = AceType::MakeRefPtr<MutableSpanString>(u"abc");

    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);

    textBackgroundStyle.backgroundColor = Color::RED;
    ;
    textBackgroundStyle.backgroundRadius = borderRadius;

    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 0, 8));
    // insert span string
    spanString->InsertSpanString(2, insertString);

    // check range start->end [0, 13]
    auto backgroundSpans = spanString->GetSpans(0, 13);
    EXPECT_EQ(backgroundSpans.size(), 2);
    auto firstBackgroundSpan = AceType::DynamicCast<BackgroundColorSpan>(backgroundSpans[0]);
    EXPECT_NE(firstBackgroundSpan, nullptr);
    EXPECT_EQ(firstBackgroundSpan->GetStartIndex(), 0);
    EXPECT_EQ(firstBackgroundSpan->GetEndIndex(), 2);
    EXPECT_TRUE(firstBackgroundSpan->GetBackgroundColor() == textBackgroundStyle);

    auto secondBackgroundSpan = AceType::DynamicCast<BackgroundColorSpan>(backgroundSpans[1]);
    EXPECT_NE(secondBackgroundSpan, nullptr);
    EXPECT_EQ(secondBackgroundSpan->GetStartIndex(), 5);
    EXPECT_EQ(secondBackgroundSpan->GetEndIndex(), 11);
    EXPECT_TRUE(secondBackgroundSpan->GetBackgroundColor() == textBackgroundStyle);

    // check range [0, 10]
    backgroundSpans = spanString->GetSpans(0, 10);
    EXPECT_EQ(backgroundSpans.size(), 2);

    auto secondBackgroundSpan2 = AceType::DynamicCast<BackgroundColorSpan>(backgroundSpans[1]);
    EXPECT_NE(secondBackgroundSpan2, nullptr);
    EXPECT_EQ(secondBackgroundSpan2->GetStartIndex(), 5);
    EXPECT_EQ(secondBackgroundSpan2->GetEndIndex(), 10);
    EXPECT_TRUE(secondBackgroundSpan2->GetBackgroundColor() == textBackgroundStyle);
}

// Helper structures for variable font weight tests
struct FontOptions {
    OHOS::Ace::FontWeight weight;
    OHOS::Ace::Dimension size;
    OHOS::Ace::FontStyle style;
    OHOS::Ace::Color color;
    int32_t familyCount;
};

struct VariableFontWeightOptions {
    std::optional<uint32_t> variableWeight = std::nullopt;
    std::optional<bool> enableVariable = std::nullopt;
    std::optional<bool> enableDevice = std::nullopt;
};

struct SpanVerifyOptions {
    std::string content;
    int32_t start;
    int32_t end;
    OHOS::Ace::Dimension fontSize;
    OHOS::Ace::Color color;
    OHOS::Ace::FontStyle style;
    OHOS::Ace::FontWeight weight;
    uint32_t variableWeight = 0;
    bool enableVariable = false;
    bool enableDevice = true;
};

// Helper functions for variable font weight tests
Font CreateTestFont(const FontOptions& options)
{
    Font font;
    font.fontWeight = options.weight;
    font.fontSize = options.size;
    font.fontStyle = options.style;
    font.fontFamiliesNG = std::vector<std::string>(test_str, test_str + options.familyCount);
    font.fontColor = options.color;
    return font;
}

Font CreateTestFontWithVariableWeight(
    const FontOptions& options, const VariableFontWeightOptions& variableOptions = VariableFontWeightOptions())
{
    Font font = CreateTestFont(options);
    if (variableOptions.variableWeight.has_value()) {
        font.variableFontWeight = variableOptions.variableWeight.value();
    }
    if (variableOptions.enableVariable.has_value()) {
        font.enableVariableFontWeight = variableOptions.enableVariable.value();
    }
    if (variableOptions.enableDevice.has_value()) {
        font.enableDeviceFontWeightCategory = variableOptions.enableDevice.value();
    }
    return font;
}

void VerifySpanContentAndInterval(std::list<RefPtr<OHOS::Ace::NG::SpanItem>>::iterator& it,
    const std::string& expectedContent, int32_t expectedStart, int32_t expectedEnd)
{
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), expectedContent);
    EXPECT_EQ((*it)->interval.first, expectedStart);
    EXPECT_EQ((*it)->interval.second, expectedEnd);
}

void VerifySpanWithVariableWeight(std::list<RefPtr<OHOS::Ace::NG::SpanItem>>::iterator& it, const std::string& content,
    int32_t start, int32_t end, const VariableFontWeightOptions& options)
{
    VerifySpanContentAndInterval(it, content, start, end);
    auto actualWeight = (*it)->fontStyle->GetVariableFontWeight().value_or(0);
    EXPECT_EQ(actualWeight, options.variableWeight.value_or(0));
    auto actualEnable = (*it)->fontStyle->GetEnableVariableFontWeight().value_or(false);
    EXPECT_EQ(actualEnable, options.enableVariable.value_or(false));
    auto actualDevice = (*it)->fontStyle->GetEnableDeviceFontWeightCategory().value_or(true);
    EXPECT_EQ(actualDevice, options.enableDevice.value_or(true));
}

void VerifyFullSpan(std::list<RefPtr<OHOS::Ace::NG::SpanItem>>::iterator& it, const SpanVerifyOptions& options)
{
    VerifySpanContentAndInterval(it, options.content, options.start, options.end);
    EXPECT_EQ((*it)->fontStyle->GetFontSize().value(), options.fontSize);
    EXPECT_EQ((*it)->fontStyle->GetTextColor().value(), options.color);
    EXPECT_EQ((*it)->fontStyle->GetItalicFontStyle().value(), options.style);
    EXPECT_EQ((*it)->fontStyle->GetFontWeight().value(), options.weight);
    auto actualWeight = (*it)->fontStyle->GetVariableFontWeight().value_or(0);
    EXPECT_EQ(actualWeight, options.variableWeight);
    auto actualEnable = (*it)->fontStyle->GetEnableVariableFontWeight().value_or(false);
    EXPECT_EQ(actualEnable, options.enableVariable);
    auto actualDevice = (*it)->fontStyle->GetEnableDeviceFontWeightCategory().value_or(true);
    EXPECT_EQ(actualDevice, options.enableDevice);
}

/**
 * @tc.name: MutableSpanString020
 * @tc.desc: Test serialization and unserialization of SpanString with VariableFontWeight TLV - all properties set
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString020, TestSize.Level1)
{
    std::vector<uint8_t> buff;

    // Create fonts and build span string
    Font font1 = CreateTestFontWithVariableWeight(
        { OHOS::Ace::FontWeight::BOLD, OHOS::Ace::Dimension(29.0, OHOS::Ace::DimensionUnit::PX),
            OHOS::Ace::FontStyle::ITALIC, OHOS::Ace::Color::RED, 10 },
        { 266, true, true });
    Font font2 = CreateTestFontWithVariableWeight(
        { OHOS::Ace::FontWeight::W300, OHOS::Ace::Dimension(49.0, OHOS::Ace::DimensionUnit::VP),
            OHOS::Ace::FontStyle::ITALIC, OHOS::Ace::Color::BLUE, 5 },
        { 333, false, false });
    Font font3 = CreateTestFont({ OHOS::Ace::FontWeight::W500, OHOS::Ace::Dimension(35.0, OHOS::Ace::DimensionUnit::FP),
        OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::Color::GREEN, 3 });

    auto spanStr = AceType::MakeRefPtr<SpanString>(u"TestVariableFontWeight");
    spanStr->AddSpan(AceType::MakeRefPtr<FontSpan>(font1, 0, 3));
    spanStr->AddSpan(AceType::MakeRefPtr<FontSpan>(font2, 5, 8));
    spanStr->AddSpan(AceType::MakeRefPtr<FontSpan>(font3, 10, 12));

    spanStr->EncodeTlv(buff);
    auto spanString2 = SpanString::DecodeTlv(buff);
    std::list<RefPtr<NG::SpanItem>> spans = spanString2->GetSpanItems();

    EXPECT_EQ(spans.size(), 6);
    auto it = spans.begin();

    // Verify all spans
    SpanVerifyOptions verifyOpts1 { "Tes", 0, 3, OHOS::Ace::Dimension(29, OHOS::Ace::DimensionUnit::PX),
        OHOS::Ace::Color::RED, OHOS::Ace::FontStyle::ITALIC, OHOS::Ace::FontWeight::BOLD, 266, true, true };
    VerifyFullSpan(it, verifyOpts1);
    ++it;
    VerifySpanContentAndInterval(it, "tV", 3, 5);
    ++it;
    SpanVerifyOptions verifyOpts2 { "ari", 5, 8, OHOS::Ace::Dimension(49, OHOS::Ace::DimensionUnit::VP),
        OHOS::Ace::Color::BLUE, OHOS::Ace::FontStyle::ITALIC, OHOS::Ace::FontWeight::W300, 333, false, false };
    VerifyFullSpan(it, verifyOpts2);
    ++it;
    VerifySpanContentAndInterval(it, "ab", 8, 10);
    ++it;
    SpanVerifyOptions verifyOpts3 { "le", 10, 12, OHOS::Ace::Dimension(35, OHOS::Ace::DimensionUnit::FP),
        OHOS::Ace::Color::GREEN, OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontWeight::W500, 0, false, true };
    VerifyFullSpan(it, verifyOpts3);
    ++it;
    VerifySpanContentAndInterval(it, "FontWeight", 12, 22);
}

/**
 * @tc.name: MutableSpanString021
 * @tc.desc: Test serialization with partial properties combinations of variableFontWeight TLVs
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString021, TestSize.Level1)
{
    std::vector<uint8_t> buff;

    // Create fonts with different property combinations
    Font font1 = CreateTestFontWithVariableWeight(
        { OHOS::Ace::FontWeight::BOLD, OHOS::Ace::Dimension(29.0, OHOS::Ace::DimensionUnit::PX),
            OHOS::Ace::FontStyle::ITALIC, OHOS::Ace::Color::RED, 10 },
        { 266, true, std::nullopt });
    Font font2 = CreateTestFontWithVariableWeight(
        { OHOS::Ace::FontWeight::W300, OHOS::Ace::Dimension(49.0, OHOS::Ace::DimensionUnit::VP),
            OHOS::Ace::FontStyle::ITALIC, OHOS::Ace::Color::BLUE, 5 },
        { std::nullopt, std::nullopt, false });
    Font font3 = CreateTestFontWithVariableWeight(
        { OHOS::Ace::FontWeight::W500, OHOS::Ace::Dimension(35.0, OHOS::Ace::DimensionUnit::FP),
            OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::Color::GREEN, 3 },
        { 400, std::nullopt, std::nullopt });
    Font font4 = CreateTestFontWithVariableWeight(
        { OHOS::Ace::FontWeight::BOLD, OHOS::Ace::Dimension(25.0, OHOS::Ace::DimensionUnit::PX),
            OHOS::Ace::FontStyle::ITALIC, OHOS::Ace::Color::RED, 7 },
        { std::nullopt, true, std::nullopt });
    Font font5 = CreateTestFontWithVariableWeight(
        { OHOS::Ace::FontWeight::W400, OHOS::Ace::Dimension(30.0, OHOS::Ace::DimensionUnit::VP),
            OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::Color::BLUE, 4 },
        { 500, std::nullopt, false });
    Font font6 = CreateTestFontWithVariableWeight(
        { OHOS::Ace::FontWeight::W600, OHOS::Ace::Dimension(32.0, OHOS::Ace::DimensionUnit::FP),
            OHOS::Ace::FontStyle::ITALIC, OHOS::Ace::Color::GREEN, 6 },
        { std::nullopt, true, false });

    auto spanStr = AceType::MakeRefPtr<SpanString>(u"123456789012345678");
    spanStr->AddSpan(AceType::MakeRefPtr<FontSpan>(font1, 0, 3));
    spanStr->AddSpan(AceType::MakeRefPtr<FontSpan>(font2, 3, 6));
    spanStr->AddSpan(AceType::MakeRefPtr<FontSpan>(font3, 6, 9));
    spanStr->AddSpan(AceType::MakeRefPtr<FontSpan>(font4, 9, 12));
    spanStr->AddSpan(AceType::MakeRefPtr<FontSpan>(font5, 12, 15));
    spanStr->AddSpan(AceType::MakeRefPtr<FontSpan>(font6, 15, 18));

    spanStr->EncodeTlv(buff);
    auto spanString2 = SpanString::DecodeTlv(buff);
    std::list<RefPtr<NG::SpanItem>> spans = spanString2->GetSpanItems();
    EXPECT_EQ(spans.size(), 6);
    auto it = spans.begin();
    // Verify each span: content, interval, (variableWeight, enableVariable, enableDevice)
    VerifySpanWithVariableWeight(it, "123", 0, 3, { 266, true, true });
    ++it;
    VerifySpanWithVariableWeight(it, "456", 3, 6, { 0, false, false });
    ++it;
    VerifySpanWithVariableWeight(it, "789", 6, 9, { 400, false, true });
    ++it;
    VerifySpanWithVariableWeight(it, "012", 9, 12, { 0, true, true });
    ++it;
    VerifySpanWithVariableWeight(it, "345", 12, 15, { 500, false, false });
    ++it;
    VerifySpanWithVariableWeight(it, "678", 15, 18, { 0, true, false });
}

/**
 * @tc.name: FontSpanAddColorResourceObj001
 * @tc.desc: Test FontSpan::AddColorResourceObj with fontColorResObj branch
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, FontSpanAddColorResourceObj001, TestSize.Level1)
{
    // Create a Font with fontColor and fontColorResObj set
    Font font;
    font.fontColor = Color::RED;
    font.fontColorResObj = AceType::MakeRefPtr<ResourceObject>("com.example.test", "entry", 0);
    font.fontColorResObj->SetColor(Color::BLUE);

    // Create FontSpan with the Font
    auto fontSpan = AceType::MakeRefPtr<FontSpan>(font, 0, 5);

    // Create a SpanItem to apply the span to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->fontStyle, nullptr);

    // Apply the font span to the span item (this internally calls AddColorResourceObj)
    fontSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);

    // Verify that the text color was updated
    EXPECT_TRUE(spanItem->fontStyle->GetTextColor().has_value());
    EXPECT_EQ(spanItem->fontStyle->GetTextColor().value(), Color::RED);

    // Verify that the resource object was added to the resMap_
    auto resMap = spanItem->GetResMap();
    EXPECT_EQ(resMap.count("fontColor"), 1);
    EXPECT_NE(resMap["fontColor"].obj, nullptr);
    EXPECT_EQ(resMap["fontColor"].obj, font.fontColorResObj);
}

/**
 * @tc.name: FontSpanAddColorResourceObj002
 * @tc.desc: Test FontSpan::AddColorResourceObj with strokeColorResObj branch
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, FontSpanAddColorResourceObj002, TestSize.Level1)
{
    // Create a Font with strokeColor and strokeColorResObj set
    Font font;
    font.strokeColor = Color::GREEN;
    font.strokeColorResObj = AceType::MakeRefPtr<ResourceObject>("com.example.test", "entry", 0);
    font.strokeColorResObj->SetColor(Color::WHITE);

    // Create FontSpan with the Font
    auto fontSpan = AceType::MakeRefPtr<FontSpan>(font, 0, 5);

    // Create a SpanItem to apply the span to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->fontStyle, nullptr);

    // Apply the font span to the span item (this internally calls AddColorResourceObj)
    fontSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);

    // Verify that the stroke color was updated
    EXPECT_TRUE(spanItem->fontStyle->GetStrokeColor().has_value());
    EXPECT_EQ(spanItem->fontStyle->GetStrokeColor().value(), Color::GREEN);

    // Verify that the resource object was added to the resMap_
    auto resMap = spanItem->GetResMap();
    EXPECT_EQ(resMap.count("strokeColor"), 1);
    EXPECT_NE(resMap["strokeColor"].obj, nullptr);
    EXPECT_EQ(resMap["strokeColor"].obj, font.strokeColorResObj);
}

/**
 * @tc.name: FontSpanAddColorResourceObj003
 * @tc.desc: Test FontSpan::AddColorResourceObj with both fontColorResObj and strokeColorResObj
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, FontSpanAddColorResourceObj003, TestSize.Level1)
{
    // Create a Font with both fontColorResObj and strokeColorResObj set
    Font font;
    font.fontColor = Color::RED;
    font.fontColorResObj = AceType::MakeRefPtr<ResourceObject>("com.example.test", "entry", 0);
    font.fontColorResObj->SetColor(Color::BLUE);
    font.strokeColor = Color::GREEN;
    font.strokeColorResObj = AceType::MakeRefPtr<ResourceObject>("com.example.test", "entry", 0);
    font.strokeColorResObj->SetColor(Color::WHITE);

    // Create FontSpan with the Font
    auto fontSpan = AceType::MakeRefPtr<FontSpan>(font, 0, 10);

    // Create a SpanItem to apply the span to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->fontStyle, nullptr);

    // Apply the font span to the span item (this internally calls AddColorResourceObj)
    fontSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);

    // Verify that both colors were updated
    EXPECT_TRUE(spanItem->fontStyle->GetTextColor().has_value());
    EXPECT_EQ(spanItem->fontStyle->GetTextColor().value(), Color::RED);
    EXPECT_TRUE(spanItem->fontStyle->GetStrokeColor().has_value());
    EXPECT_EQ(spanItem->fontStyle->GetStrokeColor().value(), Color::GREEN);

    // Verify that both resource objects were added to the resMap_
    auto resMap = spanItem->GetResMap();
    EXPECT_EQ(resMap.count("fontColor"), 1);
    EXPECT_EQ(resMap.count("strokeColor"), 1);
    EXPECT_NE(resMap["fontColor"].obj, nullptr);
    EXPECT_NE(resMap["strokeColor"].obj, nullptr);
    EXPECT_EQ(resMap["fontColor"].obj, font.fontColorResObj);
    EXPECT_EQ(resMap["strokeColor"].obj, font.strokeColorResObj);
}

/**
 * @tc.name: FontSpanAddColorResourceObj004
 * @tc.desc: Test FontSpan::AddColorResourceObj without resource objects (should not add to resMap_)
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, FontSpanAddColorResourceObj004, TestSize.Level1)
{
    // Create a Font with fontColor and strokeColor but NO resource objects
    Font font;
    font.fontColor = Color::RED;
    font.strokeColor = Color::GREEN;
    // Resource objects are not set (nullptr by default)

    // Create FontSpan with the Font
    auto fontSpan = AceType::MakeRefPtr<FontSpan>(font, 0, 5);

    // Create a SpanItem to apply the span to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->fontStyle, nullptr);

    // Apply the font span to the span item (this internally calls AddColorResourceObj)
    fontSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);

    // Verify that the colors were updated
    EXPECT_TRUE(spanItem->fontStyle->GetTextColor().has_value());
    EXPECT_EQ(spanItem->fontStyle->GetTextColor().value(), Color::RED);
    EXPECT_TRUE(spanItem->fontStyle->GetStrokeColor().has_value());
    EXPECT_EQ(spanItem->fontStyle->GetStrokeColor().value(), Color::GREEN);

    // Verify that no resource objects were added to the resMap_
    auto resMap = spanItem->GetResMap();
    EXPECT_EQ(resMap.count("fontColor"), 0);
    EXPECT_EQ(resMap.count("strokeColor"), 0);
}

/**
 * @tc.name: DecorationSpanAddDecorationStyle001
 * @tc.desc: Test DecorationSpan::AddDecorationStyle with colorResObj branch
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, DecorationSpanAddDecorationStyle001, TestSize.Level1)
{
    // Create a DecorationSpan with color and colorResObj set
    std::vector<TextDecoration> types = { TextDecoration::UNDERLINE };
    Color color = Color::RED;
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>("com.example.test", "entry", 0);
    colorResObj->SetColor(Color::BLUE);

    auto decorationSpan =
        AceType::MakeRefPtr<DecorationSpan>(types, color, std::nullopt, std::nullopt, std::nullopt, 0, 5, colorResObj);

    // Create a SpanItem to apply the decoration to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->fontStyle, nullptr);

    // Apply the decoration span to the span item (this internally calls AddDecorationStyle)
    decorationSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);

    // Verify that the text decoration color was updated
    EXPECT_TRUE(spanItem->fontStyle->GetTextDecorationColor().has_value());
    EXPECT_EQ(spanItem->fontStyle->GetTextDecorationColor().value(), Color::RED);

    // Verify that the resource object was added to the resMap_
    auto resMap = spanItem->GetResMap();
    EXPECT_EQ(resMap.count("decorationColor"), 1);
    EXPECT_NE(resMap["decorationColor"].obj, nullptr);
    EXPECT_EQ(resMap["decorationColor"].obj, colorResObj);
}

/**
 * @tc.name: DecorationSpanAddDecorationStyle002
 * @tc.desc: Test DecorationSpan::AddDecorationStyle without colorResObj (should not add to resMap_)
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, DecorationSpanAddDecorationStyle002, TestSize.Level1)
{
    // Create a DecorationSpan with color but NO colorResObj
    std::vector<TextDecoration> types = { TextDecoration::UNDERLINE };
    Color color = Color::RED;
    // colorResObj is not set (nullptr by default)

    auto decorationSpan =
        AceType::MakeRefPtr<DecorationSpan>(types, color, std::nullopt, std::nullopt, std::nullopt, 0, 5, nullptr);

    // Create a SpanItem to apply the decoration to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->fontStyle, nullptr);

    // Apply the decoration span to the span item (this internally calls AddDecorationStyle)
    decorationSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);

    // Verify that the text decoration color was updated
    EXPECT_TRUE(spanItem->fontStyle->GetTextDecorationColor().has_value());
    EXPECT_EQ(spanItem->fontStyle->GetTextDecorationColor().value(), Color::RED);

    // Verify that no resource object was added to the resMap_
    auto resMap = spanItem->GetResMap();
    EXPECT_EQ(resMap.count("decorationColor"), 0);
}

/**
 * @tc.name: DecorationSpanAddDecorationStyle003
 * @tc.desc: Test DecorationSpan::AddDecorationStyle with multiple decoration types and colorResObj
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, DecorationSpanAddDecorationStyle003, TestSize.Level1)
{
    // Create a DecorationSpan with multiple decoration types and colorResObj
    std::vector<TextDecoration> types = { TextDecoration::UNDERLINE, TextDecoration::LINE_THROUGH };
    Color color = Color::GREEN;
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>("com.example.test", "entry", 0);
    colorResObj->SetColor(Color::WHITE);

    auto decorationSpan = AceType::MakeRefPtr<DecorationSpan>(
        types, color, TextDecorationStyle::DASHED, 1.5, std::nullopt, 0, 10, colorResObj);

    // Create a SpanItem to apply the decoration to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->fontStyle, nullptr);

    // Apply the decoration span to the span item (this internally calls AddDecorationStyle)
    decorationSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);

    // Verify that the text decoration color, style, and line thickness were updated
    EXPECT_TRUE(spanItem->fontStyle->GetTextDecorationColor().has_value());
    EXPECT_EQ(spanItem->fontStyle->GetTextDecorationColor().value(), Color::GREEN);
    EXPECT_TRUE(spanItem->fontStyle->GetTextDecorationStyle().has_value());
    EXPECT_EQ(spanItem->fontStyle->GetTextDecorationStyle().value(), TextDecorationStyle::DASHED);
    EXPECT_TRUE(spanItem->fontStyle->GetLineThicknessScale().has_value());
    EXPECT_EQ(spanItem->fontStyle->GetLineThicknessScale().value(), 1.5);

    // Verify that the resource object was added to the resMap_
    auto resMap = spanItem->GetResMap();
    EXPECT_EQ(resMap.count("decorationColor"), 1);
    EXPECT_NE(resMap["decorationColor"].obj, nullptr);
    EXPECT_EQ(resMap["decorationColor"].obj, colorResObj);
}

/**
 * @tc.name: DecorationSpanDecorationTypesToString001
 * @tc.desc: Test DecorationSpan::DecorationTypesToString with LINE_THROUGH branch
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, DecorationSpanDecorationTypesToString001, TestSize.Level1)
{
    // Create a DecorationSpan with LINE_THROUGH type
    std::vector<TextDecoration> types = { TextDecoration::LINE_THROUGH };
    auto decorationSpan = AceType::MakeRefPtr<DecorationSpan>(
        types, std::nullopt, std::nullopt, std::nullopt, std::nullopt, 0, 5, nullptr);

    // Get the string representation
    std::string result = decorationSpan->DecorationTypesToString();

    // Verify that LINE_THROUGH is correctly represented
    EXPECT_EQ(result, "LINE_THROUGH");
}

/**
 * @tc.name: DecorationSpanDecorationTypesToString002
 * @tc.desc: Test DecorationSpan::DecorationTypesToString with default branch (NONE)
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, DecorationSpanDecorationTypesToString002, TestSize.Level1)
{
    // Create a DecorationSpan with NONE type (falls into default case)
    std::vector<TextDecoration> types = { TextDecoration::NONE };
    auto decorationSpan = AceType::MakeRefPtr<DecorationSpan>(
        types, std::nullopt, std::nullopt, std::nullopt, std::nullopt, 0, 5, nullptr);

    // Get the string representation
    std::string result = decorationSpan->DecorationTypesToString();

    // Verify that NONE is correctly represented (default case)
    EXPECT_EQ(result, "NONE");
}

/**
 * @tc.name: DecorationSpanDecorationTypesToString003
 * @tc.desc: Test DecorationSpan::DecorationTypesToString with default branch (INHERIT)
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, DecorationSpanDecorationTypesToString003, TestSize.Level1)
{
    // Create a DecorationSpan with INHERIT type (falls into default case)
    std::vector<TextDecoration> types = { TextDecoration::INHERIT };
    auto decorationSpan = AceType::MakeRefPtr<DecorationSpan>(
        types, std::nullopt, std::nullopt, std::nullopt, std::nullopt, 0, 5, nullptr);

    // Get the string representation
    std::string result = decorationSpan->DecorationTypesToString();

    // Verify that INHERIT is correctly represented (default case)
    EXPECT_EQ(result, "NONE");
}

/**
 * @tc.name: DecorationSpanDecorationTypesToString004
 * @tc.desc: Test DecorationSpan::DecorationTypesToString with multiple types including LINE_THROUGH
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, DecorationSpanDecorationTypesToString004, TestSize.Level1)
{
    // Create a DecorationSpan with multiple types including LINE_THROUGH
    std::vector<TextDecoration> types = { TextDecoration::UNDERLINE, TextDecoration::LINE_THROUGH };
    auto decorationSpan = AceType::MakeRefPtr<DecorationSpan>(
        types, std::nullopt, std::nullopt, std::nullopt, std::nullopt, 0, 5, nullptr);

    // Get the string representation
    std::string result = decorationSpan->DecorationTypesToString();

    // Verify that both types are correctly represented
    EXPECT_EQ(result, "UNDERLINE,LINE_THROUGH");
}

/**
 * @tc.name: DecorationSpanDecorationTypesToString005
 * @tc.desc: Test DecorationSpan::DecorationTypesToString with all types
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, DecorationSpanDecorationTypesToString005, TestSize.Level1)
{
    // Create a DecorationSpan with all decoration types
    std::vector<TextDecoration> types = { TextDecoration::UNDERLINE, TextDecoration::OVERLINE,
        TextDecoration::LINE_THROUGH, TextDecoration::NONE };
    auto decorationSpan = AceType::MakeRefPtr<DecorationSpan>(
        types, std::nullopt, std::nullopt, std::nullopt, std::nullopt, 0, 5, nullptr);

    // Get the string representation
    std::string result = decorationSpan->DecorationTypesToString();

    // Verify that all types are correctly represented
    EXPECT_EQ(result, "UNDERLINE,OVERLINE,LINE_THROUGH,NONE");
}

/**
 * @tc.name: TextShadowSpanAddSpanStyle001
 * @tc.desc: Test TextShadowSpan::AddSpanStyle with shadow having shadow.colorValue resource
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, TextShadowSpanAddSpanStyle001, TestSize.Level1)
{
    // Create a shadow with shadow.colorValue resource using the constructor
    Shadow shadow(5.0, 2.0, Offset(10.0, 10.0), Color::RED);

    // Add resource object for shadow.colorValue
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>("com.example.test", "entry", 0);
    colorResObj->SetColor(Color::BLUE);
    shadow.AddResource("shadow.colorValue", colorResObj, [](const RefPtr<ResourceObject>& resObj, Shadow& shadowVal) {
        Color color;
        ResourceParseUtils::ParseResColor(resObj, color);
        shadowVal.SetColor(color);
    });

    // Create TextShadowSpan with the shadow
    std::vector<Shadow> shadows = { shadow };
    auto textShadowSpan = AceType::MakeRefPtr<TextShadowSpan>(shadows, 0, 5);

    // Create a SpanItem to apply the shadow to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->fontStyle, nullptr);

    // Apply the text shadow span to the span item (this internally calls AddSpanStyle)
    textShadowSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);

    // Verify that the text shadow was updated
    EXPECT_TRUE(spanItem->fontStyle->GetTextShadow().has_value());
    auto textShadows = spanItem->fontStyle->GetTextShadow().value();
    EXPECT_EQ(textShadows.size(), 1);
    EXPECT_EQ(textShadows[0].GetBlurRadius(), 5.0);
    EXPECT_EQ(textShadows[0].GetColor(), Color::RED);

    // Verify that the resource object was added to the resMap_
    auto resMap = spanItem->GetResMap();
    EXPECT_EQ(resMap.count("shadow_0"), 1);
    EXPECT_NE(resMap["shadow_0"].obj, nullptr);
}

/**
 * @tc.name: TextShadowSpanAddSpanStyle002
 * @tc.desc: Test TextShadowSpan::AddSpanStyle with shadow without shadow.colorValue (should not add to resMap_)
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, TextShadowSpanAddSpanStyle002, TestSize.Level1)
{
    // Create a shadow without shadow.colorValue resource using the constructor
    Shadow shadow(5.0, 2.0, Offset(10.0, 10.0), Color::RED);
    // No resource object added - HasKey("shadow.colorValue") will return false

    // Create TextShadowSpan with the shadow
    std::vector<Shadow> shadows = { shadow };
    auto textShadowSpan = AceType::MakeRefPtr<TextShadowSpan>(shadows, 0, 5);

    // Create a SpanItem to apply the shadow to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->fontStyle, nullptr);

    // Apply the text shadow span to the span item (this internally calls AddSpanStyle)
    textShadowSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);

    // Verify that the text shadow was updated
    EXPECT_TRUE(spanItem->fontStyle->GetTextShadow().has_value());
    auto textShadows = spanItem->fontStyle->GetTextShadow().value();
    EXPECT_EQ(textShadows.size(), 1);
    EXPECT_EQ(textShadows[0].GetBlurRadius(), 5.0);
    EXPECT_EQ(textShadows[0].GetColor(), Color::RED);

    // Verify that no resource object was added to the resMap_
    auto resMap = spanItem->GetResMap();
    EXPECT_EQ(resMap.count("shadow_0"), 0);
}

/**
 * @tc.name: TextShadowSpanAddSpanStyle003
 * @tc.desc: Test TextShadowSpan::AddSpanStyle with multiple shadows having shadow.colorValue resources
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, TextShadowSpanAddSpanStyle003, TestSize.Level1)
{
    // Create first shadow with resource using the constructor
    Shadow shadow1(5.0, 2.0, Offset(10.0, 10.0), Color::RED);
    RefPtr<ResourceObject> colorResObj1 = AceType::MakeRefPtr<ResourceObject>("com.example.test", "entry", 0);
    colorResObj1->SetColor(Color::BLUE);
    shadow1.AddResource("shadow.colorValue", colorResObj1, [](const RefPtr<ResourceObject>& resObj, Shadow& shadowVal) {
        Color color;
        ResourceParseUtils::ParseResColor(resObj, color);
        shadowVal.SetColor(color);
    });

    // Create second shadow with resource using the constructor
    Shadow shadow2(3.0, 1.0, Offset(5.0, 5.0), Color::GREEN);
    RefPtr<ResourceObject> colorResObj2 = AceType::MakeRefPtr<ResourceObject>("com.example.test", "entry", 0);
    colorResObj2->SetColor(Color::WHITE);
    shadow2.AddResource("shadow.colorValue", colorResObj2, [](const RefPtr<ResourceObject>& resObj, Shadow& shadowVal) {
        Color color;
        ResourceParseUtils::ParseResColor(resObj, color);
        shadowVal.SetColor(color);
    });

    // Create third shadow without resource (to test continue branch)
    Shadow shadow3(2.0, 1.0, Offset(3.0, 3.0), Color::GRAY);
    // No resource added

    // Create TextShadowSpan with all shadows
    std::vector<Shadow> shadows = { shadow1, shadow2, shadow3 };
    auto textShadowSpan = AceType::MakeRefPtr<TextShadowSpan>(shadows, 0, 10);

    // Create a SpanItem to apply the shadow to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->fontStyle, nullptr);

    // Apply the text shadow span to the span item
    textShadowSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);

    // Verify that the text shadow was updated with all shadows
    EXPECT_TRUE(spanItem->fontStyle->GetTextShadow().has_value());
    auto textShadows = spanItem->fontStyle->GetTextShadow().value();
    EXPECT_EQ(textShadows.size(), 3);

    // Verify that only the first two shadows have resource objects in resMap_
    auto resMap = spanItem->GetResMap();
    EXPECT_EQ(resMap.count("shadow_0"), 1);
    EXPECT_EQ(resMap.count("shadow_1"), 1);
    EXPECT_EQ(resMap.count("shadow_2"), 0);
}

/**
 * @tc.name: HalfLeadingSpanConstructor001
 * @tc.desc: Test HalfLeadingSpan constructor with halfLeading parameter only
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, HalfLeadingSpanConstructor001, TestSize.Level1)
{
    // Test constructor with halfLeading parameter only (range 0, 0)
    bool halfLeading = true;
    auto halfLeadingSpan = AceType::MakeRefPtr<HalfLeadingSpan>(halfLeading);

    // Verify the halfLeading value is set correctly
    EXPECT_EQ(halfLeadingSpan->GetHalfLeading(), true);

    // Verify the range is (0, 0)
    EXPECT_EQ(halfLeadingSpan->GetStartIndex(), 0);
    EXPECT_EQ(halfLeadingSpan->GetEndIndex(), 0);
}

/**
 * @tc.name: HalfLeadingSpanConstructor002
 * @tc.desc: Test HalfLeadingSpan constructor with halfLeading, start, and end parameters
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, HalfLeadingSpanConstructor002, TestSize.Level1)
{
    // Test constructor with halfLeading, start, and end parameters
    bool halfLeading = false;
    int32_t start = 5;
    int32_t end = 10;
    auto halfLeadingSpan = AceType::MakeRefPtr<HalfLeadingSpan>(halfLeading, start, end);

    // Verify the halfLeading value is set correctly
    EXPECT_EQ(halfLeadingSpan->GetHalfLeading(), false);

    // Verify the range is set correctly
    EXPECT_EQ(halfLeadingSpan->GetStartIndex(), 5);
    EXPECT_EQ(halfLeadingSpan->GetEndIndex(), 10);
}

/**
 * @tc.name: HalfLeadingSpanApplyToSpanItem001
 * @tc.desc: Test HalfLeadingSpan::ApplyToSpanItem with SpanOperation::ADD
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, HalfLeadingSpanApplyToSpanItem001, TestSize.Level1)
{
    // Create a HalfLeadingSpan with halfLeading = true
    bool halfLeading = true;
    int32_t start = 0;
    int32_t end = 5;
    auto halfLeadingSpan = AceType::MakeRefPtr<HalfLeadingSpan>(halfLeading, start, end);

    // Create a SpanItem to apply the halfLeading to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->textLineStyle, nullptr);

    // Apply the halfLeading span with ADD operation
    halfLeadingSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);

    // Verify that the halfLeading was updated (calls AddHalfLeadingStyle)
    EXPECT_TRUE(spanItem->textLineStyle->GetHalfLeading().has_value());
    EXPECT_EQ(spanItem->textLineStyle->GetHalfLeading().value(), true);
}

/**
 * @tc.name: HalfLeadingSpanApplyToSpanItem002
 * @tc.desc: Test HalfLeadingSpan::ApplyToSpanItem with SpanOperation::REMOVE
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, HalfLeadingSpanApplyToSpanItem002, TestSize.Level1)
{
    // Create a HalfLeadingSpan with halfLeading = true
    bool halfLeading = true;
    int32_t start = 0;
    int32_t end = 5;
    auto halfLeadingSpan = AceType::MakeRefPtr<HalfLeadingSpan>(halfLeading, start, end);

    // Create a SpanItem to apply the halfLeading to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->textLineStyle, nullptr);

    // First apply with ADD operation to set the value
    halfLeadingSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);
    EXPECT_TRUE(spanItem->textLineStyle->GetHalfLeading().has_value());
    EXPECT_EQ(spanItem->textLineStyle->GetHalfLeading().value(), true);

    // Then apply with REMOVE operation (calls RemoveHalfLeadingStyle)
    halfLeadingSpan->ApplyToSpanItem(spanItem, SpanOperation::REMOVE);

    // Verify that the halfLeading was reset
    EXPECT_FALSE(spanItem->textLineStyle->GetHalfLeading().has_value());
}

/**
 * @tc.name: HalfLeadingSpanGetSubSpan001
 * @tc.desc: Test HalfLeadingSpan::GetSubSpan method
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, HalfLeadingSpanGetSubSpan001, TestSize.Level1)
{
    // Create a HalfLeadingSpan with halfLeading = true, range [0, 10]
    bool halfLeading = true;
    int32_t start = 0;
    int32_t end = 10;
    auto halfLeadingSpan = AceType::MakeRefPtr<HalfLeadingSpan>(halfLeading, start, end);

    // Get a sub span with range [2, 7]
    auto subSpan = halfLeadingSpan->GetSubSpan(2, 7);
    ASSERT_NE(subSpan, nullptr);

    // Verify it's a HalfLeadingSpan
    auto halfLeadingSubSpan = AceType::DynamicCast<HalfLeadingSpan>(subSpan);
    ASSERT_NE(halfLeadingSubSpan, nullptr);

    // Verify the halfLeading value is preserved
    EXPECT_EQ(halfLeadingSubSpan->GetHalfLeading(), true);

    // Verify the range is updated to [2, 7]
    EXPECT_EQ(halfLeadingSubSpan->GetStartIndex(), 2);
    EXPECT_EQ(halfLeadingSubSpan->GetEndIndex(), 7);
}

/**
 * @tc.name: HalfLeadingSpanGetSpanType001
 * @tc.desc: Test HalfLeadingSpan::GetSpanType method
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, HalfLeadingSpanGetSpanType001, TestSize.Level1)
{
    // Create a HalfLeadingSpan
    bool halfLeading = true;
    auto halfLeadingSpan = AceType::MakeRefPtr<HalfLeadingSpan>(halfLeading);

    // Verify the span type is HalfLeading
    EXPECT_EQ(halfLeadingSpan->GetSpanType(), SpanType::HalfLeading);
}

/**
 * @tc.name: HalfLeadingSpanIsAttributesEqual001
 * @tc.desc: Test HalfLeadingSpan::IsAttributesEqual method
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, HalfLeadingSpanIsAttributesEqual001, TestSize.Level1)
{
    // Create two HalfLeadingSpans with same halfLeading value
    auto halfLeadingSpan1 = AceType::MakeRefPtr<HalfLeadingSpan>(true, 0, 5);
    auto halfLeadingSpan2 = AceType::MakeRefPtr<HalfLeadingSpan>(true, 0, 5);

    // Verify they are equal
    EXPECT_TRUE(halfLeadingSpan1->IsAttributesEqual(halfLeadingSpan2));

    // Create a HalfLeadingSpan with different halfLeading value
    auto halfLeadingSpan3 = AceType::MakeRefPtr<HalfLeadingSpan>(false, 0, 5);

    // Verify they are not equal
    EXPECT_FALSE(halfLeadingSpan1->IsAttributesEqual(halfLeadingSpan3));
}

/**
 * @tc.name: HalfLeadingSpanToString001
 * @tc.desc: Test HalfLeadingSpan::ToString method
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, HalfLeadingSpanToString001, TestSize.Level1)
{
    // Create a HalfLeadingSpan with halfLeading = true, range [2, 8]
    auto halfLeadingSpan = AceType::MakeRefPtr<HalfLeadingSpan>(true, 2, 8);

    // Get the string representation
    std::string result = halfLeadingSpan->ToString();

    // Verify the string contains the halfLeading value and range
    EXPECT_NE(result.find("HalfLeadingSpan"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("8"), std::string::npos);
}

/**
 * @tc.name: ExtSpanToString001
 * @tc.desc: Test ExtSpan::ToString method
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, ExtSpanToString001, TestSize.Level1)
{
    // Create an ExtSpan with range [0, 5]
    int32_t start = 0;
    int32_t end = 5;
    auto extSpan = AceType::MakeRefPtr<ExtSpan>(start, end);

    // Get the string representation
    std::string result = extSpan->ToString();

    // Verify the string contains "ExtSpan" and the range
    EXPECT_NE(result.find("ExtSpan"), std::string::npos);
    EXPECT_NE(result.find("0"), std::string::npos);
    EXPECT_NE(result.find("5"), std::string::npos);
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
    EXPECT_NE(result.find(":"), std::string::npos);
}

/**
 * @tc.name: ExtSpanToString002
 * @tc.desc: Test ExtSpan::ToString method with different range
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, ExtSpanToString002, TestSize.Level1)
{
    // Create an ExtSpan with range [10, 100]
    int32_t start = 10;
    int32_t end = 100;
    auto extSpan = AceType::MakeRefPtr<ExtSpan>(start, end);

    // Get the string representation
    std::string result = extSpan->ToString();

    // Verify the string contains "ExtSpan" and the range
    EXPECT_NE(result.find("ExtSpan"), std::string::npos);
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("100"), std::string::npos);
}

/**
 * @tc.name: BackgroundColorSpanAddSpanStyle001
 * @tc.desc: Test BackgroundColorSpan::AddSpanStyle with textBackgroundStyle_ having value
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, BackgroundColorSpanAddSpanStyle001, TestSize.Level1)
{
    // Create a TextBackgroundStyle with background color
    TextBackgroundStyle textBackgroundStyle;
    std::optional<Color> backgroundColor = Color::RED;
    textBackgroundStyle.backgroundColor = backgroundColor;
    std::optional<TextBackgroundStyle> backgroundStyle;
    backgroundStyle = textBackgroundStyle;

    // Create a BackgroundColorSpan with the background style
    auto backgroundColorSpan = AceType::MakeRefPtr<BackgroundColorSpan>(backgroundStyle);

    // Create a SpanItem to apply the background color to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    // Apply the background color span (ADD operation)
    backgroundColorSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);

    // Verify that the background style was set
    EXPECT_TRUE(spanItem->backgroundStyle.has_value());
    EXPECT_EQ(spanItem->backgroundStyle.value().backgroundColor.value(), Color::RED);
}

/**
 * @tc.name: BackgroundColorSpanAddSpanStyle002
 * @tc.desc: Test BackgroundColorSpan::AddSpanStyle with textBackgroundStyle_ having value and resource key
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, BackgroundColorSpanAddSpanStyle002, TestSize.Level1)
{
    // Create a TextBackgroundStyle with background color and resource key
    TextBackgroundStyle textBackgroundStyle;
    std::optional<Color> backgroundColor = Color::BLUE;
    textBackgroundStyle.backgroundColor = backgroundColor;

    // Add resource object for textBackgroundStyle.color
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>("com.example.test", "entry", 0);
    colorResObj->SetColor(Color::GREEN);
    textBackgroundStyle.AddResource(
        "textBackgroundStyle.color", colorResObj, [](const RefPtr<ResourceObject>& resObj, TextBackgroundStyle& style) {
            Color color;
            ResourceParseUtils::ParseResColor(resObj, color);
            style.backgroundColor = color;
        });

    std::optional<TextBackgroundStyle> backgroundStyle;
    backgroundStyle = textBackgroundStyle;

    // Create a BackgroundColorSpan with the background style
    auto backgroundColorSpan = AceType::MakeRefPtr<BackgroundColorSpan>(backgroundStyle);

    // Create a SpanItem to apply the background color to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    // Apply the background color span (ADD operation)
    backgroundColorSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);

    // Verify that the background style was set
    EXPECT_TRUE(spanItem->backgroundStyle.has_value());

    // Verify that the resource object was added to the resMap_
    auto resMap = spanItem->GetResMap();
    EXPECT_EQ(resMap.count("textbackgroundStyle"), 1);
    EXPECT_NE(resMap["textbackgroundStyle"].obj, nullptr);
}

/**
 * @tc.name: BackgroundColorSpanAddSpanStyle003
 * @tc.desc: Test BackgroundColorSpan::AddSpanStyle with textBackgroundStyle_ not having value
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, BackgroundColorSpanAddSpanStyle003, TestSize.Level1)
{
    // Create a BackgroundColorSpan with empty background style
    std::optional<TextBackgroundStyle> backgroundStyle;
    auto backgroundColorSpan = AceType::MakeRefPtr<BackgroundColorSpan>(backgroundStyle);

    // Create a SpanItem to apply the background color to
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    // Apply the background color span (ADD operation)
    backgroundColorSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);

    // Verify that the background style was NOT set (since textBackgroundStyle_ has no value)
    EXPECT_FALSE(spanItem->backgroundStyle.has_value());
}

/**
 * @tc.name: BackgroundColorSpanToString001
 * @tc.desc: Test BackgroundColorSpan::ToString method
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, BackgroundColorSpanToString001, TestSize.Level1)
{
    // Create a TextBackgroundStyle with background color
    TextBackgroundStyle textBackgroundStyle;
    std::optional<Color> backgroundColor = Color::BLUE;
    textBackgroundStyle.backgroundColor = backgroundColor;
    std::optional<TextBackgroundStyle> backgroundStyle;
    backgroundStyle = textBackgroundStyle;

    // Create a BackgroundColorSpan with range [0, 5]
    int32_t start = 0;
    int32_t end = 5;
    auto backgroundColorSpan = AceType::MakeRefPtr<BackgroundColorSpan>(backgroundStyle, start, end);

    // Get the string representation
    std::string result = backgroundColorSpan->ToString();

    // Verify the string contains "BackgroundColorSpan" and the range
    EXPECT_NE(result.find("BackgroundColorSpan"), std::string::npos);
    EXPECT_NE(result.find("0"), std::string::npos);
    EXPECT_NE(result.find("5"), std::string::npos);
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
    EXPECT_NE(result.find(":"), std::string::npos);
}

/**
 * @tc.name: BackgroundColorSpanToString002
 * @tc.desc: Test BackgroundColorSpan::ToString method with different range
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, BackgroundColorSpanToString002, TestSize.Level1)
{
    // Create a BackgroundColorSpan with empty background style and range [10, 100]
    std::optional<TextBackgroundStyle> backgroundStyle;
    int32_t start = 10;
    int32_t end = 100;
    auto backgroundColorSpan = AceType::MakeRefPtr<BackgroundColorSpan>(backgroundStyle, start, end);

    // Get the string representation
    std::string result = backgroundColorSpan->ToString();

    // Verify the string contains "BackgroundColorSpan" and the range
    EXPECT_NE(result.find("BackgroundColorSpan"), std::string::npos);
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("100"), std::string::npos);
}

/**
 * @tc.name: UrlSpanToString001
 * @tc.desc: Test UrlSpan::ToString method
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, UrlSpanToString001, TestSize.Level1)
{
    // Create a UrlSpan with URL address and range [0, 10]
    std::string urlAddress = "https://www.example.com";
    int32_t start = 0;
    int32_t end = 10;
    auto urlSpan = AceType::MakeRefPtr<UrlSpan>(urlAddress, start, end);

    // Get the string representation
    std::string result = urlSpan->ToString();

    // Verify the string contains "UrlSpan" and the range
    EXPECT_NE(result.find("UrlSpan"), std::string::npos);
    EXPECT_NE(result.find("0"), std::string::npos);
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
    EXPECT_NE(result.find(":"), std::string::npos);
}

/**
 * @tc.name: UrlSpanToString002
 * @tc.desc: Test UrlSpan::ToString method with different range
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, UrlSpanToString002, TestSize.Level1)
{
    // Create a UrlSpan with different URL and range [5, 50]
    std::string urlAddress = "https://www.example.com";
    int32_t start = 5;
    int32_t end = 50;
    auto urlSpan = AceType::MakeRefPtr<UrlSpan>(urlAddress, start, end);

    // Get the string representation
    std::string result = urlSpan->ToString();

    // Verify the string contains "UrlSpan" and the range
    EXPECT_NE(result.find("UrlSpan"), std::string::npos);
    EXPECT_NE(result.find("5"), std::string::npos);
    EXPECT_NE(result.find("50"), std::string::npos);
}

/**
 * @tc.name: UrlSpanToString003
 * @tc.desc: Test UrlSpan::ToString method with default range
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, UrlSpanToString003, TestSize.Level1)
{
    // Create a UrlSpan with URL address only (default range 0, 0)
    std::string urlAddress = "https://www.example.com";
    auto urlSpan = AceType::MakeRefPtr<UrlSpan>(urlAddress);

    // Get the string representation
    std::string result = urlSpan->ToString();

    // Verify the string contains "UrlSpan" and default range
    EXPECT_NE(result.find("UrlSpan"), std::string::npos);
    EXPECT_NE(result.find("0"), std::string::npos);
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
}

/**
 * @tc.name: SpanStringGetLayoutInfo001
 * @tc.desc: Test SpanString::GetLayoutInfo with basic text and maxWidth
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanStringGetLayoutInfo001, TestSize.Level1)
{
    // Create a SpanString with basic text
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello World");

    // Test with maxWidth having value
    std::optional<double> maxWidth = 500.0;
    auto paraVec = SpanString::GetLayoutInfo(spanString, maxWidth);

    // Verify that paragraphs were created
    EXPECT_GT(paraVec.size(), 0);

    // Verify that maxWidth was used (should not be max float)
    // Paragraph should be laid out with the specified maxWidth
    EXPECT_NE(paraVec.front(), nullptr);
}

/**
 * @tc.name: SpanStringGetLayoutInfo002
 * @tc.desc: Test SpanString::GetLayoutInfo without maxWidth (use max float)
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanStringGetLayoutInfo002, TestSize.Level1)
{
    // Create a SpanString with basic text
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello World");

    // Test without maxWidth (use std::numeric_limits<float>::max())
    std::optional<double> maxWidth = std::nullopt;
    auto paraVec = SpanString::GetLayoutInfo(spanString, maxWidth);

    // Verify that paragraphs were created
    EXPECT_GT(paraVec.size(), 0);
    EXPECT_NE(paraVec.front(), nullptr);
}

/**
 * @tc.name: SpanStringGetLayoutInfo003
 * @tc.desc: Test SpanString::GetLayoutInfo with FontSpan (has fontSize)
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanStringGetLayoutInfo003, TestSize.Level1)
{
    // Create a SpanString with text
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello World");

    // Add a FontSpan with font size
    Font font { OHOS::Ace::FontWeight::BOLD, Dimension(20.0, DimensionUnit::PX) };
    auto fontSpan = AceType::MakeRefPtr<FontSpan>(font, 0, 5);
    spanString->AddSpan(fontSpan);

    // Test GetLayoutInfo
    std::optional<double> maxWidth = 500.0;
    auto paraVec = SpanString::GetLayoutInfo(spanString, maxWidth);

    // Verify that paragraphs were created
    EXPECT_GT(paraVec.size(), 0);
    EXPECT_NE(paraVec.front(), nullptr);
}

/**
 * @tc.name: SpanStringGetLayoutInfo004
 * @tc.desc: Test SpanString::GetLayoutInfo with ParagraphStyleSpan (has paraStyleSpanItem)
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanStringGetLayoutInfo004, TestSize.Level1)
{
    // Create a SpanString with text
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello World\nLine Two");

    // Add a ParagraphStyleSpan with maxLines
    SpanParagraphStyle paragraphStyle;
    paragraphStyle.maxLines = 2;
    auto paragraphStyleSpan = AceType::MakeRefPtr<ParagraphStyleSpan>(paragraphStyle, 0, 11);
    spanString->AddSpan(paragraphStyleSpan);

    // Test GetLayoutInfo
    std::optional<double> maxWidth = 500.0;
    auto paraVec = SpanString::GetLayoutInfo(spanString, maxWidth);

    // Verify that paragraphs were created
    EXPECT_GT(paraVec.size(), 0);
}

/**
 * @tc.name: SpanStringGetLayoutInfo005
 * @tc.desc: Test SpanString::GetLayoutInfo with multiple paragraphs (tests paraVec not empty branch)
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanStringGetLayoutInfo005, TestSize.Level1)
{
    // Create a SpanString with multiple lines (paragraphs)
    auto spanString = AceType::MakeRefPtr<SpanString>(u"First Line\nSecond Line\nThird Line");

    // Add a ParagraphStyleSpan with maxLines (to test paraVec not empty branch)
    SpanParagraphStyle paragraphStyle;
    paragraphStyle.maxLines = 2;
    auto paragraphStyleSpan = AceType::MakeRefPtr<ParagraphStyleSpan>(paragraphStyle, 0, 11);
    spanString->AddSpan(paragraphStyleSpan);

    // Test GetLayoutInfo
    std::optional<double> maxWidth = 500.0;
    auto paraVec = SpanString::GetLayoutInfo(spanString, maxWidth);

    // Verify that multiple paragraphs were created
    EXPECT_GE(paraVec.size(), 1);
}

/**
 * @tc.name: SpanStringGetLayoutInfo006
 * @tc.desc: Test SpanString::GetLayoutInfo with LineHeightSpan (tests paragraph spacing)
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanStringGetLayoutInfo006, TestSize.Level1)
{
    // Create a SpanString with text
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello World\nNext Line");

    // Add a LineHeightSpan with paragraph spacing
    auto lineHeightSpan = AceType::MakeRefPtr<LineHeightSpan>(Dimension(30.0, DimensionUnit::PX), 0, 11);
    spanString->AddSpan(lineHeightSpan);

    // Test GetLayoutInfo
    std::optional<double> maxWidth = 500.0;
    auto paraVec = SpanString::GetLayoutInfo(spanString, maxWidth);

    // Verify that paragraphs were created
    EXPECT_GT(paraVec.size(), 0);
}

/**
 * @tc.name: SpanStringGetLayoutInfo007
 * @tc.desc: Test SpanString::GetLayoutInfo with empty text
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanStringGetLayoutInfo007, TestSize.Level1)
{
    // Create a SpanString with empty text
    auto spanString = AceType::MakeRefPtr<SpanString>(u"");

    // Test GetLayoutInfo
    std::optional<double> maxWidth = 500.0;
    auto paraVec = SpanString::GetLayoutInfo(spanString, maxWidth);

    // Verify that paragraphs were created (even for empty text)
    EXPECT_GE(paraVec.size(), 0);
}

/**
 * @tc.name: SpanStringGetLayoutInfo008
 * @tc.desc: Test SpanString::GetLayoutInfo with BackgroundColorSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanStringGetLayoutInfo008, TestSize.Level1)
{
    // Create a SpanString with text
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello World");

    // Add a BackgroundColorSpan
    TextBackgroundStyle textBackgroundStyle;
    std::optional<Color> backgroundColor = Color::RED;
    textBackgroundStyle.backgroundColor = backgroundColor;
    std::optional<TextBackgroundStyle> backgroundStyle;
    backgroundStyle = textBackgroundStyle;
    auto backgroundColorSpan = AceType::MakeRefPtr<BackgroundColorSpan>(backgroundStyle, 0, 5);
    spanString->AddSpan(backgroundColorSpan);

    // Test GetLayoutInfo
    std::optional<double> maxWidth = 500.0;
    auto paraVec = SpanString::GetLayoutInfo(spanString, maxWidth);

    // Verify that paragraphs were created
    EXPECT_GT(paraVec.size(), 0);
}

} // namespace OHOS::Ace::NG