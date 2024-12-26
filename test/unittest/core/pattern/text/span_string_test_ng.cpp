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
} // namespace

class SpanStringTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static ImageSpanOptions GetImageOption(const std::string& src);
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

ImageSpanOptions SpanStringTestNg::GetImageOption(const std::string& src)
{
    ImageSpanSize size { .width = 50.0_vp, .height = 50.0_vp };
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(2.0_vp);
    MarginProperty margins;
    margins.SetEdges(CalcLength(10.0));
    PaddingProperty paddings;
    paddings.SetEdges(CalcLength(5.0));
    ImageSpanAttribute attr { .paddingProp = paddings,
        .marginProp = margins,
        .borderRadius = borderRadius,
        .objectFit = ImageFit::COVER,
        .verticalAlign = VerticalAlign::BOTTOM };
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
    spanString3->AddSpan(
        AceType::MakeRefPtr<DecorationSpan>(TextDecoration::OVERLINE, Color::RED, TextDecorationStyle::WAVY, 0, 1));
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
    spanString3->AddSpan(
        AceType::MakeRefPtr<DecorationSpan>(TextDecoration::OVERLINE, Color::RED, TextDecorationStyle::WAVY, 0, 1));
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
    EXPECT_EQ((*it)->fontStyle->GetFontSize().value(), Dimension(49, OHOS::Ace::DimensionUnit::VP));
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
    auto decorationSpan =
        AceType::MakeRefPtr<DecorationSpan>(TextDecoration::OVERLINE, Color::RED, TextDecorationStyle::WAVY, 0, 1);
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
    vector<Shadow> textShadows3 {textShadow};
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
    textBackgroundStyle.backgroundColor = Color::RED;;
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

    textBackgroundStyle.backgroundColor = Color::RED;;
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

    textBackgroundStyle.backgroundColor = Color::RED;;
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

/**
 * @tc.name: SpanString014
 * @tc.desc: Test append spanstring after BackgroundColorSpan
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString014, TestSize.Level1)
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
HWTEST_F(SpanStringTestNg, SpanString015, TestSize.Level1)
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
HWTEST_F(SpanStringTestNg, SpanString016, TestSize.Level1)
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
HWTEST_F(SpanStringTestNg, SpanString017, TestSize.Level1)
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
HWTEST_F(SpanStringTestNg, SpanString018, TestSize.Level1)
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
 * @tc.name: Tlv001
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, Tlv001, TestSize.Level1)
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
HWTEST_F(SpanStringTestNg, Tlv002, TestSize.Level1)
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
HWTEST_F(SpanStringTestNg, Tlv003, TestSize.Level1)
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
HWTEST_F(SpanStringTestNg, Tlv004, TestSize.Level1)
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
HWTEST_F(SpanStringTestNg, Tlv005, TestSize.Level1)
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
HWTEST_F(SpanStringTestNg, Tlv006, TestSize.Level1)
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
HWTEST_F(SpanStringTestNg, Tlv007, TestSize.Level1)
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
HWTEST_F(SpanStringTestNg, Tlv008, TestSize.Level1)
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
HWTEST_F(SpanStringTestNg, Tlv009, TestSize.Level1)
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
 * @tc.name: Tlv010
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, Tlv010, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(2.0_vp);
    MarginProperty margins;
    margins.SetEdges(CalcLength(10.0));
    PaddingProperty paddings;
    paddings.SetEdges(CalcLength(5.0));
    ImageSpanAttribute writeImageSpanAttribute { .paddingProp = paddings,
        .marginProp = margins,
        .borderRadius = borderRadius,
        .objectFit = ImageFit::COVER,
        .verticalAlign = VerticalAlign::BOTTOM };
    std::vector<uint8_t> result = { 0x3a, 0x3c, 0x2c, 0x3, 0x3d, 0x2d, 0x2, 0x3e, 0x46, 0x49, 0x2b, 0x20, 0x0, 0x24,
        0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x24, 0x40, 0x0, 0x4a, 0x2b, 0x20, 0x0, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x24, 0x40, 0x0, 0x47, 0x2b, 0x20, 0x0, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x24, 0x40, 0x0, 0x48,
        0x2b, 0x20, 0x0, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x24, 0x40, 0x0, 0x4b, 0x3f, 0x27, 0x24, 0x21, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x1, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x1, 0x24, 0x21,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x1, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x1, 0x40,
        0x46, 0x49, 0x2b, 0x20, 0x0, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x14, 0x40, 0x0, 0x4a, 0x2b, 0x20, 0x0,
        0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x14, 0x40, 0x0, 0x47, 0x2b, 0x20, 0x0, 0x24, 0x21, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x14, 0x40, 0x0, 0x48, 0x2b, 0x20, 0x0, 0x24, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x14, 0x40,
        0x0, 0x4b, 0x41 };
    TLVUtil::WriteImageSpanAttribute(buffer, writeImageSpanAttribute);
    EXPECT_TRUE(buffer == result);

    int32_t cursor = 0;
    ImageSpanAttribute readImageSpanAttribute = TLVUtil::ReadImageSpanAttribute(buffer, cursor);
    EXPECT_TRUE(writeImageSpanAttribute == readImageSpanAttribute);
    buffer.clear();
    cursor = 0;
    readImageSpanAttribute = TLVUtil::ReadImageSpanAttribute(buffer, cursor);
    EXPECT_FALSE(writeImageSpanAttribute == readImageSpanAttribute);
}

/**
 * @tc.name: Tlv011
 * @tc.desc: Test basic function of TLV
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, Tlv011, TestSize.Level1)
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
 * @tc.name: GetSpanResultObject001
 * @tc.desc: Test GetSpanResultObject
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, GetSpanResultObject001, TestSize.Level1)
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
HWTEST_F(SpanStringTestNg, GetSpanResultObject002, TestSize.Level1)
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
HWTEST_F(SpanStringTestNg, GetSpanResultObject003, TestSize.Level1)
{
    auto customSpanItem = AceType::MakeRefPtr<NG::CustomSpanItem>();
    ASSERT_NE(customSpanItem, nullptr);
    customSpanItem->interval.first = 1;
    customSpanItem->interval.second = 4;
    auto resultObject = customSpanItem->GetSpanResultObject(0, 3);
    EXPECT_FALSE(resultObject.isInit);
}
} // namespace OHOS::Ace::NG