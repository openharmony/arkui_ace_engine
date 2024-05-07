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

#include <functional>
#include <memory>
#include <optional>
#include <vector>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/measure_property.h"

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
    auto spanString = AceType::MakeRefPtr<SpanString>("0123456789");
    EXPECT_EQ(spanString->GetString(), "0123456789");
    EXPECT_EQ(spanString->GetLength(), 10);

    auto spanString1 = AceType::MakeRefPtr<SpanString>("中0123456789");
    EXPECT_EQ(spanString1->GetString(), "中0123456789");
    EXPECT_EQ(spanString1->GetLength(), 11);

    auto spanString2 = AceType::MakeRefPtr<SpanString>("0123456");
    EXPECT_EQ(spanString2->GetString(), "0123456");
    EXPECT_EQ(spanString2->GetLength(), 7);

    auto spanString3 = AceType::MakeRefPtr<SpanString>("你好");
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
    auto spanString1 = AceType::MakeRefPtr<SpanString>("01234中56789");
    auto spanString2 = AceType::MakeRefPtr<SpanString>("01234中56789");
    auto spanString3 = AceType::MakeRefPtr<SpanString>("01234567891");
    EXPECT_TRUE(spanString1->IsEqualToSpanString(spanString2));
    EXPECT_FALSE(spanString1->IsEqualToSpanString(spanString3));
    std::vector<RefPtr<SpanBase>> spans;
    spans.push_back(AceType::MakeRefPtr<FontSpan>(testFont2, 0, 3));
    spans.push_back(AceType::MakeRefPtr<FontSpan>(testEmptyFont, 5, 8));
    auto spanStringWithSpans1 = AceType::MakeRefPtr<SpanString>("01234567891");
    spanStringWithSpans1->BindWithSpans(spans);
    auto spanStringWithSpans2 = AceType::MakeRefPtr<SpanString>("01234567891");
    spanStringWithSpans2->BindWithSpans(spans);
    EXPECT_TRUE(spanStringWithSpans1->IsEqualToSpanString(spanStringWithSpans2));
    std::vector<RefPtr<SpanBase>> spans1;
    spans1.push_back(AceType::MakeRefPtr<FontSpan>(testFont2, 0, 3));
    spans1.push_back(AceType::MakeRefPtr<FontSpan>(testEmptyFont, 5, 7));
    auto spanStringWithSpans3 = AceType::MakeRefPtr<SpanString>("01234567891");
    spanStringWithSpans3->BindWithSpans(spans1);
    EXPECT_FALSE(spanStringWithSpans3->IsEqualToSpanString(spanStringWithSpans2));
    auto subSpanStringWithSpans2 = spanStringWithSpans2->GetSubSpanString(0, 7);
    auto subSpanStringWithSpans3 = spanStringWithSpans3->GetSubSpanString(0, 7);
    auto map2 = subSpanStringWithSpans2->GetSpansMap();
    EXPECT_TRUE(subSpanStringWithSpans2->IsEqualToSpanString(subSpanStringWithSpans3));
    auto emptySpanString = spanStringWithSpans2->GetSubSpanString(1, 0);
    EXPECT_TRUE(emptySpanString->IsEqualToSpanString(AceType::MakeRefPtr<SpanString>("")));
}

/**
 * @tc.name: SpanStringTest003
 * @tc.desc: Test basic function of GetSpans/GetFontColor/GetFontSize/GetFontWeight/GetFontFamily/GetFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, SpanString003, TestSize.Level1)
{
    auto spanString3 = AceType::MakeRefPtr<MutableSpanString>("0123456789");
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
    auto spanString3 = AceType::MakeRefPtr<MutableSpanString>("0123456789");
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
    auto spanString3 = AceType::MakeRefPtr<MutableSpanString>("0123456789");
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
    auto spanString3 = AceType::MakeRefPtr<MutableSpanString>("0123456789");
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
 * @tc.name: SpanStringTest001
 * @tc.desc: Test basic function of ReplaceString/InsertString/RemoveString
 * @tc.type: FUNC
 */
HWTEST_F(SpanStringTestNg, MutableSpanString001, TestSize.Level1)
{
    auto a = AceType::MakeRefPtr<MutableSpanString>("0123456789");
    EXPECT_EQ(a->GetString(), "0123456789");
    a->ReplaceString(0, 1, "abcd");
    EXPECT_EQ(a->GetString(), "abcd123456789");
    a->InsertString(0, "abcd");
    EXPECT_EQ(a->GetString(), "abcdabcd123456789");
    a->RemoveString(3, 3);
    EXPECT_EQ(a->GetString(), "abccd123456789");
    a->InsertString(4, "中文插入测试");
    EXPECT_EQ(a->GetString(), "abcc中文插入测试d123456789");
    a->RemoveString(4, 6);
    EXPECT_EQ(a->GetString(), "abccd123456789");
    a->ReplaceString(5, 9, "中文替换测试");
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
    auto a = AceType::MakeRefPtr<MutableSpanString>("0123456789");

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
    auto b = MutableSpanString("零一二三四五六七八九");
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
    auto mutableSpan = AceType::MakeRefPtr<MutableSpanString>("0123456789");

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
    auto mutableSpan = AceType::MakeRefPtr<MutableSpanString>("0123456789");

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
    auto mutableSpan = AceType::MakeRefPtr<MutableSpanString>("0123456789");

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
    auto spanString1 = AceType::MakeRefPtr<SpanString>("0123456789");
    spanString1->AddSpan(AceType::MakeRefPtr<FontSpan>(fontOne, 0, 3));
    auto mutableSpanString1 = AceType::MakeRefPtr<MutableSpanString>("0123456789");
    EXPECT_FALSE(spanString1->IsEqualToSpanString(mutableSpanString1));
    mutableSpanString1->AddSpan(AceType::MakeRefPtr<FontSpan>(fontOne, 0, 3));
    EXPECT_TRUE(spanString1->IsEqualToSpanString(mutableSpanString1));
    mutableSpanString1->AddSpan(AceType::MakeRefPtr<FontSpan>(fontOne, 3, 7));
    auto mutableSpanString2 = AceType::MakeRefPtr<MutableSpanString>("0123456789");
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
    auto spanString1 = AceType::MakeRefPtr<MutableSpanString>("01234");
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
    spanString1->InsertString(0, "一二三四五");
    auto spanMap = spanString1->GetSpansMap();
    EXPECT_TRUE(CompareSpanList(spanMap[SpanType::Font], resultList1));
    spanString1->InsertString(6, "红红火火");
    std::list<RefPtr<SpanBase>> resultList2 = { AceType::MakeRefPtr<FontSpan>(fonts[0], 0, 10),
        AceType::MakeRefPtr<FontSpan>(fonts[1], 10, 11), AceType::MakeRefPtr<FontSpan>(fonts[2], 11, 12),
        AceType::MakeRefPtr<FontSpan>(fonts[3], 12, 13), AceType::MakeRefPtr<FontSpan>(fonts[4], 13, 14) };
    spanMap = spanString1->GetSpansMap();
    EXPECT_TRUE(CompareSpanList(spanMap[SpanType::Font], resultList2));
    spanString1->InsertString(11, "abcdefg");
    spanString1->ReplaceString(8, 8, "A");
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
    auto spanString1 = AceType::MakeRefPtr<MutableSpanString>("0123");
    for (int i = 0; i < 5; i++) {
        Font f;
        f.fontColor = colors[i];
        fonts.emplace_back(f);
        if (i != 4) {
            spanString1->AddSpan(AceType::MakeRefPtr<FontSpan>(f, i, i + 1));
        }
    }
    auto spanArr = spanString1->GetSpans(0, spanString1->GetLength());
    auto spanString2 = AceType::MakeRefPtr<MutableSpanString>("abc");
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
    auto spanStringWithSpans = AceType::MakeRefPtr<SpanString>("01234567891");
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
    auto spanStringWithSpans = AceType::MakeRefPtr<SpanString>("01234567891");
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
    auto spanStringWithSpans = AceType::MakeRefPtr<SpanString>("01234567891");
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
    auto spanString = AceType::MakeRefPtr<MutableSpanString>("01234567891");
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
    spanString->ReplaceString(0, 2, "a");
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

    mutableStr->InsertString(0, "123");
    auto text = mutableStr->GetString();
    EXPECT_TRUE(text == "123 ");
    auto length = mutableStr->GetLength();
    EXPECT_TRUE(length == 4);

    mutableStr->InsertString(4, "456");
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

    auto spanStr = AceType::MakeRefPtr<SpanString>("123");
    spanStr->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 3));
    mutableStr->InsertSpanString(0, spanStr);
    auto text = mutableStr->GetString();
    EXPECT_EQ(text, "123 ");
    auto length = mutableStr->GetLength();
    EXPECT_EQ(length, 4);

    spanStr = AceType::MakeRefPtr<SpanString>("456");
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
    mutableStr->InsertString(0, "123");
    mutableStr->InsertString(4, "456");

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
    mutableStr->InsertString(0, "123");
    mutableStr->InsertString(4, "456");
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
    auto spanString = AceType::MakeRefPtr<MutableSpanString>("0123456789");
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
 * @tc.desc: Test isAttributesEqual of LineHeightSpan/ParagraphStyleSpan
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
    auto paraSpan2 = AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 0, 1);
    EXPECT_TRUE(paraSpan->IsAttributesEqual(paraSpan2));

    auto lineHeightSpan = AceType::MakeRefPtr<LineHeightSpan>(Dimension(30), 0, 3);
    auto lineHeightSpan2 = AceType::MakeRefPtr<LineHeightSpan>(Dimension(30), 0, 3);
    auto lineHeightSpan3 = AceType::MakeRefPtr<LineHeightSpan>(Dimension(25), 0, 3);
    EXPECT_TRUE(lineHeightSpan->IsAttributesEqual(lineHeightSpan2));
    EXPECT_FALSE(lineHeightSpan->IsAttributesEqual(lineHeightSpan3));
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

    auto spanStr = AceType::MakeRefPtr<SpanString>("123");
    spanStr->AddSpan(paraSpan);
    mutableStr->InsertSpanString(0, spanStr);
    auto text = mutableStr->GetString();
    EXPECT_EQ(text, "123 ");
    auto length = mutableStr->GetLength();
    EXPECT_EQ(length, 4);

    spanStr = AceType::MakeRefPtr<SpanString>("456");
    spanStr->AddSpan(AceType::MakeRefPtr<LineHeightSpan>(Dimension(30), 0, 3));
    mutableStr->InsertSpanString(4, spanStr);
    text = mutableStr->GetString();
    EXPECT_EQ(text, "123 456");
    length = mutableStr->GetLength();
    EXPECT_EQ(length, 7);
    auto spans = mutableStr->GetSpans(0, 7);
    EXPECT_EQ(spans.size(), 3);
}

} // namespace OHOS::Ace::NG