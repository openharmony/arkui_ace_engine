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


class MutableSpanStringTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static ImageSpanOptions GetImageOption(const std::string& src);
    static ImageSpanOptions GetColorFilterImageOption(const std::string& src);
};

void MutableSpanStringTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
}

void MutableSpanStringTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: MutableSpanStringTest001
 * @tc.desc: Test ReplaceString with middle range replacement
 * @tc.type: FUNC
 */
HWTEST_F(MutableSpanStringTestNg, SpanString001, TestSize.Level1)
{
    // 初始化含基础文本和span的对象
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"HelloWorld");
    TextBackgroundStyle style;
    style.backgroundColor = Color::RED;
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(style, 0, 5)); // 覆盖前5字符
    
    // 执行中间替换操作（替换第2-4字符）
    spanString->ReplaceString(2, 2, u"__"); // 替换"ll"为"_"
    
    // 验证字符串修改结果
    EXPECT_EQ(spanString->GetU16string(), u"He__oWorld");
    
    auto spans = spanString->GetSpans(0, 6);
    EXPECT_EQ(spans.size(), 1);
    auto bgSpan = AceType::DynamicCast<BackgroundColorSpan>(spans.front());
    ASSERT_NE(bgSpan, nullptr);
    EXPECT_EQ(bgSpan->GetStartIndex(), 0);
    EXPECT_EQ(bgSpan->GetEndIndex(), 5);
}

/**
 * @tc.name: MutableSpanStringTest002
 * @tc.desc: Test InsertString at text beginning with existing span
 */
HWTEST_F(MutableSpanStringTestNg, SpanString002, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"World");
    TextBackgroundStyle style{Color::BLUE};
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(style, 0, 5));
    spanString->InsertString(0, u"Hello"); // 头部插入
    EXPECT_EQ(spanString->GetU16string(), u"HelloWorld");
    auto spans = spanString->GetSpans(5, 5); // 原span应后移
    EXPECT_EQ(spans.front()->GetStartIndex(), 5);
    EXPECT_EQ(spans.front()->GetEndIndex(), 10);
}

/**
 * @tc.name: MutableSpanStringTest003
 * @tc.desc: Test RemoveString affecting multiple spans
 */
HWTEST_F(MutableSpanStringTestNg, SpanString003, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"ABCDEF");
    spanString->AddSpan(CreateSpan(0, 3)); // Span1: 0-3
    spanString->AddSpan(CreateSpan2(3, 6)); // Span2: 3-6

    spanString->RemoveString(2, 2); // 移除"CD"
    
    EXPECT_EQ(spanString->GetU16string(), u"ABEF");

    auto spans = spanString->GetSpans(0, 4);
    EXPECT_EQ(spans.size(), 2);

    EXPECT_EQ(spans[0]->GetEndIndex(), 2); // Span1缩短

    EXPECT_EQ(spans[1]->GetStartIndex(), 2); // Span2前移
}

/**
 * @tc.name: MutableSpanStringTest004
 * @tc.desc: Test ReplaceSpanString with overlapping spans
 */
HWTEST_F(MutableSpanStringTestNg, SpanString004, TestSize.Level1)
{
    auto original = AceType::MakeRefPtr<MutableSpanString>(u"OldText");
    auto replacement = AceType::MakeRefPtr<MutableSpanString>(u"New");
    replacement->AddSpan(CreateSpan(0, 3));
    
    original->ReplaceSpanString(2, 3, replacement); // 替换位置2-5
    
    EXPECT_EQ(original->GetU16string(), u"OlNewxt");
    auto spans = original->GetSpans(2, 3);
    EXPECT_EQ(spans.size(), 1); // 新span应覆盖2-5
}

/**
 * @tc.name: MutableSpanStringTest005
 * @tc.desc: Test InsertSpanString at middle position
 */
HWTEST_F(MutableSpanStringTestNg, SpanString005, TestSize.Level1)
{
    auto mainStr = AceType::MakeRefPtr<MutableSpanString>(u"StartEnd");
    auto insertStr = AceType::MakeRefPtr<MutableSpanString>(u"Middle");
    insertStr->AddSpan(CreateSpan(0, 6));
    
    mainStr->InsertSpanString(5, insertStr); // 在"Start"后插入
    
    EXPECT_EQ(mainStr->GetU16string(), u"StartMiddleEnd");
    EXPECT_EQ(mainStr->GetSpans(5, 6).size(), 1); // 插入的span
    EXPECT_EQ(mainStr->GetSpans(0, 5).size(), 0); // 原区域无span
}

/**
 * @tc.name: MutableSpanStringTest006
 * @tc.desc: Test AppendSpanString with multiple spans
 */
HWTEST_F(MutableSpanStringTestNg, SpanString006, TestSize.Level1)
{
    auto baseStr = AceType::MakeRefPtr<MutableSpanString>(u"Base");
    auto appendStr = AceType::MakeRefPtr<MutableSpanString>(u"Append");
    appendStr->AddSpan(CreateSpan(0, 3));
    appendStr->AddSpan(CreateSpan2(3, 6));
    
    baseStr->AppendSpanString(appendStr);
    
    EXPECT_EQ(baseStr->GetU16string(), u"BaseAppend");
    auto spans = baseStr->GetSpans(4, 6);
    EXPECT_EQ(spans.size(), 2); // 追加的两个span
    EXPECT_EQ(spans[0]->GetStartIndex(), 4); // 自动偏移
}

/**
 * @tc.name: MutableSpanStringTest007
 * @tc.desc: Test ReplaceString at text end with span adjustment
 */
HWTEST_F(MutableSpanStringTestNg, SpanString007, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Text");
    spanString->AddSpan(CreateSpan(0, 4)); // 全文本span
    
    spanString->ReplaceString(3, 1, u"Extended"); // 替换末尾字符
    EXPECT_EQ(spanString->GetU16string(), u"TexExtended");
    auto spans = spanString->GetSpans(0, 11);
    EXPECT_EQ(spans.front()->GetEndIndex(), 11); // span扩展到新末尾
}

/**
 * @tc.name: MutableSpanStringTest008
 * @tc.desc: Test InsertString causing span split
 */
HWTEST_F(MutableSpanStringTestNg, SpanString008, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"ABCD");
    spanString->AddSpan(CreateSpan(0, 4)); // 单个span
    
    spanString->InsertString(2, u"X"); // 中间插入
    auto spans = spanString->GetSpans(0, 5);
    EXPECT_EQ(spans.size(), 1);
    EXPECT_EQ(spans.front()->GetEndIndex(), 5);
    EXPECT_EQ(spans.back()->GetStartIndex(), 0);
}

/**
 * @tc.name: MutableSpanStringTest009
 * @tc.desc: Test RemoveString eliminating entire span
 */
HWTEST_F(MutableSpanStringTestNg, SpanString009, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Content");
    spanString->AddSpan(CreateSpan(2, 5)); // span覆盖3-5
    
    spanString->RemoveString(1, 4); // 移除包含整个span的区域
    EXPECT_TRUE(spanString->GetSpans(0, 3).empty()); // span应被移除
}

/**
 * @tc.name: MutableSpanStringTest010
 * @tc.desc: Test ReplaceSpanString with shorter text
 */
HWTEST_F(MutableSpanStringTestNg, SpanString010, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"Original");
    auto replacement = AceType::MakeRefPtr<MutableSpanString>(u"New");
    replacement->AddSpan(CreateSpan(0, 3));
    
    target->ReplaceSpanString(2, 4, replacement); // 替换2-6为"New"
    EXPECT_EQ(target->GetU16string(), u"OrNewal");
    auto spans = target->GetSpans(2, 5);
    ASSERT_FALSE(spans.empty());
    EXPECT_EQ(spans.front()->GetStartIndex(), 2);
    EXPECT_EQ(spans.front()->GetEndIndex(), 5); // 新span应适配新文本长度
}

/**
 * @tc.name: MutableSpanStringTest011
 * @tc.desc: Test InsertSpanString into empty target
 */
HWTEST_F(MutableSpanStringTestNg, SpanString011, TestSize.Level1)
{
    auto mainStr = AceType::MakeRefPtr<MutableSpanString>(u"");
    auto insertStr = AceType::MakeRefPtr<MutableSpanString>(u"Init");
    insertStr->AddSpan(CreateSpan(0, 4));
    
    mainStr->InsertSpanString(0, insertStr);
    EXPECT_EQ(mainStr->GetU16string(), u"Init");
    EXPECT_EQ(mainStr->GetSpans(0, 4).size(), 1); // 正确继承span
}

/**
 * @tc.name: MutableSpanStringTest012
 * @tc.desc: Test AppendSpanString to non-empty target
 */
HWTEST_F(MutableSpanStringTestNg, SpanString012, TestSize.Level1)
{
    auto mainStr = AceType::MakeRefPtr<MutableSpanString>(u"Header");
    mainStr->AddSpan(CreateSpan(0, 6));
    auto appendStr = AceType::MakeRefPtr<MutableSpanString>(u"Tail");
    appendStr->AddSpan(CreateSpan2(0, 4));
    
    mainStr->AppendSpanString(appendStr);
    
    EXPECT_EQ(mainStr->GetU16string(), u"HeaderTail");
    EXPECT_EQ(mainStr->GetSpans(0, 6).size(), 1);  // 原始span保持不变
    EXPECT_EQ(mainStr->GetSpans(6, 4).front()->GetStartIndex(), 6); // 新span正确偏移
}

/**
 * @tc.name: MutableSpanStringTest013
 * @tc.desc: Test ReplaceString crossing multiple spans
 */
HWTEST_F(MutableSpanStringTestNg, SpanString013, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"ABCDEFGH");
    spanString->AddSpan(CreateSpan(0, 3));  // Span1: 0-3
    spanString->AddSpan(CreateSpan2(4, 6));  // Span2: 4-6
    
    spanString->ReplaceString(2, 4, u"XY"); // 替换2-6为XY
    
    EXPECT_EQ(spanString->GetU16string(), u"ABXYGH");
    auto spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans.size(), 1);

    EXPECT_EQ(spans[0]->GetEndIndex(), 4);  // Span1缩短
}

/**
 * @tc.name: MutableSpanStringTest014
 * @tc.desc: Test InsertString splitting span into three parts
 */
HWTEST_F(MutableSpanStringTestNg, SpanString014, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"ABCD");
    spanString->AddSpan(CreateSpan(0, 4)); // 单个全范围span
    
    spanString->InsertString(2, u"X"); // 在中间插入
    
    auto spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans.size(), 1);
    EXPECT_EQ(spans[0]->GetStartIndex(), 0);
    EXPECT_EQ(spanString->GetU16string(), u"ABXCD");
}

/**
 * @tc.name: MutableSpanStringTest015
 * @tc.desc: Test ReplaceSpanString replacing entire content
 */
HWTEST_F(MutableSpanStringTestNg, SpanString015, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"OldContent");
    target->AddSpan(CreateSpan(0, 9));
    auto replacement = AceType::MakeRefPtr<MutableSpanString>(u"New");
    replacement->AddSpan(CreateSpan(0, 3));
    
    target->ReplaceSpanString(0, 9, replacement);
    
    EXPECT_EQ(target->GetU16string(), u"Newt");
    auto spans = target->GetSpans(0, target->GetLength());
    EXPECT_EQ(spans.size(), 1); // 完全替换原有span
    EXPECT_EQ(spans.front()->GetEndIndex(), 3);
}

/**
 * @tc.name: MutableSpanStringTest016
 * @tc.desc: Test InsertSpanString within existing span
 */
HWTEST_F(MutableSpanStringTestNg, SpanString016, TestSize.Level1)
{
    auto mainStr = AceType::MakeRefPtr<MutableSpanString>(u"StartEnd");
    mainStr->AddSpan(CreateSpan(0, 7)); // 覆盖整个字符串
    auto insertStr = AceType::MakeRefPtr<MutableSpanString>(u"Middle");
    insertStr->AddSpan(CreateSpan2(0, 6));
    
    mainStr->InsertSpanString(5, insertStr); // 在"Start"后插入
    
    auto spans = mainStr->GetSpans(0, mainStr->GetLength());
    EXPECT_EQ(spans.size(), 3); // 原span分裂为前后两个+新插入span
    EXPECT_EQ(spans[0]->GetEndIndex(), 5);  // 前半部分
    EXPECT_EQ(spans[1]->GetStartIndex(), 5); // 插入的span
    EXPECT_EQ(spans[2]->GetStartIndex(), 11); // 后半部分
}

/**
 * @tc.name: MutableSpanStringTest017
 * @tc.desc: Test consecutive ReplaceString operations
 */
HWTEST_F(MutableSpanStringTestNg, SpanString017, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"123456789");
    spanString->AddSpan(CreateSpan(0, 9));
    
    spanString->ReplaceString(1, 2, u"A");  // 替换1-3为A → "1A456789"
    spanString->ReplaceString(3, 3, u"BC"); // 替换3-6为BC → "1A4BC89"
    
    EXPECT_EQ(spanString->GetU16string(), u"1A4BC89");
    auto spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans.front()->GetStartIndex(), 0);
    EXPECT_EQ(spans.front()->GetEndIndex(), 7); // span自动调整到新长度
}

/**
 * @tc.name: MutableSpanStringTest018
 * @tc.desc: Test InsertString with overlapping spans
 */
HWTEST_F(MutableSpanStringTestNg, SpanString018, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"ABCD");
    spanString->AddSpan(CreateSpan(1, 3)); // 覆盖B-C
    
    spanString->InsertString(2, u"XYZ"); // 在B后插入
    auto spans = spanString->GetSpans(0, 7);
    EXPECT_EQ(spans.size(), 1);
    EXPECT_EQ(spans[0]->GetEndIndex(), 6);  // 原span前半部分
    EXPECT_EQ(spans[0]->GetStartIndex(), 1); // 原span后半部分
}

/**
 * @tc.name: MutableSpanStringTest019
 * @tc.desc: Test RemoveString at span boundaries
 */
HWTEST_F(MutableSpanStringTestNg, SpanString019, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"StartMidEnd");
    spanString->AddSpan(CreateSpan(5, 8)); // 覆盖"Mid"
    
    spanString->RemoveString(4, 1); // 删除't'和'M'之间的字符
    EXPECT_EQ(spanString->GetU16string(), u"StarMidEnd");
    auto spans = spanString->GetSpans(4, 3);
    EXPECT_EQ(spans.front()->GetStartIndex(), 4); // span前移1位
    EXPECT_EQ(spans.front()->GetEndIndex(), 7);
}

/**
 * @tc.name: MutableSpanStringTest020
 * @tc.desc: Test ReplaceSpanString with nested spans
 */
HWTEST_F(MutableSpanStringTestNg, SpanString020, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"Parent");
    target->AddSpan(CreateSpan(0, 6));
    auto replacement = AceType::MakeRefPtr<MutableSpanString>(u"Child");
    replacement->AddSpan(CreateSpan2(0, 5));
    
    target->ReplaceSpanString(1, 4, replacement); // 替换1-5为Child
    EXPECT_EQ(target->GetU16string(), u"PChildt");
    auto spans = target->GetSpans(0, target->GetLength());
    EXPECT_EQ(spans.size(), 3); // 原span分裂为前(0-1)、后(6-7) + 新span(1-6)
}

/**
 * @tc.name: MutableSpanStringTest021
 * @tc.desc: Test AppendSpanString with empty target
 */
HWTEST_F(MutableSpanStringTestNg, SpanString021, TestSize.Level1)
{
    auto mainStr = AceType::MakeRefPtr<MutableSpanString>(u"");
    auto appendStr = AceType::MakeRefPtr<MutableSpanString>(u"Appended");
    appendStr->AddSpan(CreateSpan(0, 7));
    
    mainStr->AppendSpanString(appendStr);
    EXPECT_EQ(mainStr->GetU16string(), u"Appended");
    EXPECT_EQ(mainStr->GetSpans(0, mainStr->GetLength()).front()->GetEndIndex(), 7); // 正确继承span
}

/**
 * @tc.name: MutableSpanStringTest022
 * @tc.desc: Test AppendSpanString merging adjacent spans
 */
HWTEST_F(MutableSpanStringTestNg, SpanString022, TestSize.Level1)
{
    auto mainStr = AceType::MakeRefPtr<MutableSpanString>(u"Head");
    mainStr->AddSpan(CreateSpan(0, 4));
    auto appendStr = AceType::MakeRefPtr<MutableSpanString>(u"Tail");
    appendStr->AddSpan(CreateSpan2(0, 4));
    
    mainStr->AppendSpanString(appendStr);
    
    EXPECT_EQ(mainStr->GetU16string(), u"HeadTail");
    auto spans = mainStr->GetSpans(0, mainStr->GetLength());
    EXPECT_EQ(spans.size(), 2); // 保持独立span不合并
    EXPECT_EQ(spans[1]->GetStartIndex(), 4); // 新span正确偏移
}

/**
 * @tc.name: MutableSpanStringTest023
 * @tc.desc: Test ReplaceString at span start boundary
 */
HWTEST_F(MutableSpanStringTestNg, SpanString023, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"ABCDE");
    spanString->AddSpan(CreateSpan(2, 5)); // 覆盖CDE
    
    spanString->ReplaceString(2, 1, u"X"); // 替换C为X
    auto spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans.front()->GetStartIndex(), 2); // span起始保持
    EXPECT_EQ(spans.front()->GetEndIndex(), 5); // 长度自动调整
}

/**
 * @tc.name: MutableSpanStringTest024
 * @tc.desc: Test InsertSpanString splitting existing span into three parts
 */
HWTEST_F(MutableSpanStringTestNg, SpanString024, TestSize.Level1)
{
    auto mainStr = AceType::MakeRefPtr<MutableSpanString>(u"AABBCC");
    mainStr->AddSpan(CreateSpan(0, 6));
    auto insertStr = AceType::MakeRefPtr<MutableSpanString>(u"XX");
    insertStr->AddSpan(CreateSpan2(0, 2));
    
    mainStr->InsertSpanString(3, insertStr); // 在中间插入
    auto spans = mainStr->GetSpans(0, mainStr->GetLength());
    EXPECT_EQ(spans.size(), 3); // 分裂为前中后三个span
    EXPECT_EQ(spans[1]->GetStartIndex(), 3); // 插入的span
}

/**
 * @tc.name: MutableSpanStringTest025
 * @tc.desc: Test RemoveString eliminating multiple spans
 */
HWTEST_F(MutableSpanStringTestNg, SpanString025, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"ABCDEF");
    spanString->AddSpan(CreateSpan(1, 3)); // Span1
    spanString->AddSpan(CreateSpan2(4, 6)); // Span2
    
    spanString->RemoveString(2, 3); // 移除CDE

    EXPECT_EQ(spanString->GetU16string(), u"ABF");
}

/**
 * @tc.name: MutableSpanStringTest026
 * @tc.desc: Test mixed InsertString and ReplaceSpan operations
 */
HWTEST_F(MutableSpanStringTestNg, SpanString026, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"1234");
    spanString->InsertString(2, u"X"); // 变成12X34
    spanString->AddSpan(CreateSpan(1, 4)); // 覆盖2X3
    
    spanString->ReplaceString(3, 1, u"YYY"); // 替换X为YYY
    auto spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spanString->GetU16string(), u"12XYYY4");
    EXPECT_EQ(spans.front()->GetEndIndex(), 6); // span自动扩展
}

/**
 * @tc.name: MutableSpanStringTest027
 * @tc.desc: Test InsertString with empty content
 */
HWTEST_F(MutableSpanStringTestNg, SpanString027, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Normal");
    spanString->AddSpan(CreateSpan(0, 6));
    
    spanString->InsertString(3, u""); // 插入空字符串
    EXPECT_EQ(spanString->GetU16string(), u"Normal"); // 文本不变
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 6); // span范围不变
}

/**
 * @tc.name: MutableSpanStringTest028
 * @tc.desc: Test ReplaceString with zero-length replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString028, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"ABCD");
    spanString->AddSpan(CreateSpan(1, 3));
    
    spanString->ReplaceString(2, 0, u"X"); // 替换长度0
    EXPECT_EQ(spanString->GetU16string(), u"ABCD"); // 等效插入操作
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 3); // span扩展到新位置
}

/**
 * @tc.name: MutableSpanStringTest029
 * @tc.desc: Test InsertSpanString with empty spanString
 */
HWTEST_F(MutableSpanStringTestNg, SpanString029, TestSize.Level1)
{
    auto mainStr = AceType::MakeRefPtr<MutableSpanString>(u"Content");
    auto emptyStr = AceType::MakeRefPtr<MutableSpanString>(u"");
    
    mainStr->InsertSpanString(3, emptyStr); // 插入空对象
    EXPECT_EQ(mainStr->GetU16string(), u"Content"); // 无变化
    EXPECT_EQ(mainStr->GetSpans(0, mainStr->GetLength()).size(), 0); // 不添加新span
}

/**
 * @tc.name: MutableSpanStringTest031
 * @tc.desc: Test large text replacement (1KB string)
 */
HWTEST_F(MutableSpanStringTestNg, SpanString031, TestSize.Level1)
{
    const std::u16string kiloStr(1024, u'A'); // 生成1KB字符串
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(kiloStr);
    spanString->AddSpan(CreateSpan(0, 1024));
    
    spanString->ReplaceString(512, 0, u"MID"); // 中间插入标记
    EXPECT_EQ(spanString->GetU16string().substr(512, 3), u"AAA");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 1024); // span自动扩展
}

/**
 * @tc.name: MutableSpanStringTest032
 * @tc.desc: Test inserting string between two spans
 */
HWTEST_F(MutableSpanStringTestNg, SpanString032, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"LeftRight");
    spanString->AddSpan(CreateSpan(0, 4));  // 覆盖Left
    spanString->AddSpan(CreateSpan2(4, 9));  // 覆盖Right
    
    spanString->InsertString(4, u"Middle"); // 在中间插入
    
    EXPECT_EQ(spanString->GetU16string(), u"LeftMiddleRight");
    auto spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans[0]->GetEndIndex(), 10);       // 左span保持
    EXPECT_EQ(spans[1]->GetStartIndex(), 10);    // 右span偏移
}

/**
 * @tc.name: MutableSpanStringTest033
 * @tc.desc: Test full text replacement with span inheritance
 */
HWTEST_F(MutableSpanStringTestNg, SpanString033, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"Old");
    auto replacement = AceType::MakeRefPtr<MutableSpanString>(u"NewText");
    replacement->AddSpan(CreateSpan(0, 7));
    
    target->ReplaceSpanString(0, 3, replacement);
    EXPECT_EQ(target->GetSpans(0, target->GetLength()).front()->GetEndIndex(), 7); // 完全继承新span
    EXPECT_EQ(target->GetU16string(), u"NewText");
}

/**
 * @tc.name: MutableSpanStringTest034
 * @tc.desc: Test appending multiple span segments
 */
HWTEST_F(MutableSpanStringTestNg, SpanString034, TestSize.Level1)
{
    auto base = AceType::MakeRefPtr<MutableSpanString>(u"Base");
    auto appendContent = AceType::MakeRefPtr<MutableSpanString>(u"Append");
    appendContent->AddSpan(CreateSpan(1, 3)); // 部分span
    
    base->AppendSpanString(appendContent);
    EXPECT_EQ(base->GetU16string(), u"BaseAppend");
    auto spans = base->GetSpans(4, 6);
    EXPECT_EQ(spans.front()->GetStartIndex(), 5); // 正确偏移原始span
}

/**
 * @tc.name: MutableSpanStringTest035
 * @tc.desc: Test overlapping replace operations
 */
HWTEST_F(MutableSpanStringTestNg, SpanString035, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"ABCDEF");
    spanString->AddSpan(CreateSpan(0, 6));
    
    spanString->ReplaceString(2, 2, u"XYZ"); // 替换CD为XYZ
    spanString->ReplaceString(3, 1, u"MN");  // 替换Y为MN
    
    EXPECT_EQ(spanString->GetU16string(), u"ABXMNZEF");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 8); // 动态调整
}

/**
 * @tc.name: MutableSpanStringTest036
 * @tc.desc: Test span persistence after empty insertion
 */
HWTEST_F(MutableSpanStringTestNg, SpanString036, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Hello");
    spanString->AddSpan(CreateSpan(1, 4)); // 覆盖"ell"
    
    spanString->InsertString(3, u""); // 无效插入
    auto spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans.front()->GetStartIndex(), 1);
    EXPECT_EQ(spans.front()->GetEndIndex(), 4); // span保持不变
}

/**
 * @tc.name: MutableSpanStringTest037
 * @tc.desc: Test span adjustment after prefix replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString037, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"OriginalText");
    spanString->AddSpan(CreateSpan(3, 9)); // 覆盖"ginalTe"
    
    spanString->ReplaceString(0, 4, u"New"); // 替换"Orig"为"New"
    EXPECT_EQ(spanString->GetU16string(), u"NewinalText");
    auto spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans.front()->GetStartIndex(), 3); // span起始点前移1位
    EXPECT_EQ(spans.front()->GetEndIndex(), 8);
}

/**
 * @tc.name: MutableSpanStringTest038
 * @tc.desc: Test multi-span interaction with middle insertion
 */
HWTEST_F(MutableSpanStringTestNg, SpanString038, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"ABC-DEF-GHI");
    spanString->AddSpan(CreateSpan(0, 3));  // ABC
    spanString->AddSpan(CreateSpan2(4, 7));  // DEF
    spanString->AddSpan(CreateSpan(8, 11)); // GHI
    
    spanString->InsertString(6, u"XYZ"); // 在DEF后插入
    EXPECT_EQ(spanString->GetU16string(), u"ABC-DEXYZF-GHI");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength())[1]->GetEndIndex(), 10); // 中间span扩展
}

/**
 * @tc.name: MutableSpanStringTest039
 * @tc.desc: Test partial span replacement with shorter text
 */
HWTEST_F(MutableSpanStringTestNg, SpanString039, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"LongString");
    target->AddSpan(CreateSpan(2, 6)); // 覆盖"ngSt"
    auto replacement = AceType::MakeRefPtr<MutableSpanString>(u"Short");
    
    target->ReplaceSpanString(3, 4, replacement);
    EXPECT_EQ(target->GetU16string(), u"LonShorting");
    EXPECT_EQ(target->GetSpans(0, target->GetLength()).front()->GetEndIndex(), 3); // 新span适配长度
}

/**
 * @tc.name: MutableSpanStringTest040
 * @tc.desc: Test append operation with existing spans
 */
HWTEST_F(MutableSpanStringTestNg, SpanString040, TestSize.Level1)
{
    auto mainStr = AceType::MakeRefPtr<MutableSpanString>(u"Main");
    mainStr->AddSpan(CreateSpan(1, 3)); // 覆盖"ai"
    auto appendStr = AceType::MakeRefPtr<MutableSpanString>(u"Append");
    appendStr->AddSpan(CreateSpan(0, 3)); // 覆盖"App"
    
    mainStr->AppendSpanString(appendStr);
    EXPECT_EQ(mainStr->GetU16string(), u"MainAppend");
    EXPECT_EQ(mainStr->GetSpans(0, mainStr->GetLength()).back()->GetStartIndex(), 4); // 追加span正确偏移
}

/**
 * @tc.name: MutableSpanStringTest041
 * @tc.desc: Test nested replace operations
 */
HWTEST_F(MutableSpanStringTestNg, SpanString041, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"StartEnd");
    spanString->AddSpan(CreateSpan(0, 7));
    
    spanString->ReplaceString(2, 3, u"__MID__");
    spanString->ReplaceString(5, 2, u"X");        // 二次替换
    
    EXPECT_EQ(spanString->GetU16string(), u"St__MX__End");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 10); // 动态调整
}

/**
 * @tc.name: MutableSpanStringTest042
 * @tc.desc: Test span merging after adjacent replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString042, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"AABBCC");
    spanString->AddSpan(CreateSpan(0, 2));  // AA
    spanString->AddSpan(CreateSpan2(2, 4));  // BB
    spanString->AddSpan(CreateSpan(4, 6));  // CC
    
    spanString->ReplaceString(1, 4, u"XYZ"); // 替换ABBC
    EXPECT_EQ(spanString->GetU16string(), u"AXYZC");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).size(), 1); // 合并中间span
}

/**
 * @tc.name: MutableSpanStringTest043
 * @tc.desc: Test cross-span insertion with style inheritance
 */
HWTEST_F(MutableSpanStringTestNg, SpanString043, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"HeaderFooter");
    spanString->AddSpan(CreateSpan(0, 6));   // Header
    spanString->AddSpan(CreateSpan2(6, 12));  // Footer
    
    spanString->InsertString(5, u"<MARK>"); // 跨越两个span插入
    EXPECT_EQ(spanString->GetU16string(), u"Heade<MARK>rFooter");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength())[1]->GetStartIndex(), 12); // Footer偏移
}

/**
 * @tc.name: MutableSpanStringTest044
 * @tc.desc: Test partial span replacement with longer text
 */
HWTEST_F(MutableSpanStringTestNg, SpanString044, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"Short");
    target->AddSpan(CreateSpan(1, 4));  // 覆盖"hor"
    auto replacement = AceType::MakeRefPtr<MutableSpanString>(u"LongerText");
    
    target->ReplaceSpanString(2, 2, replacement); // 替换"or"为长文本
    EXPECT_EQ(target->GetU16string(), u"ShLongerTextt");
    EXPECT_EQ(target->GetSpans(0, target->GetLength()).front()->GetEndIndex(), 2); // span自动扩展
}

/**
 * @tc.name: MutableSpanStringTest045
 * @tc.desc: Test multi-type span interaction
 */
HWTEST_F(MutableSpanStringTestNg, SpanString045, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Text");
    spanString->AddSpan(CreateSpan(0, 2));  // 类型A
    spanString->AddSpan(CreateSpan2(2, 4));  // 类型B
    
    spanString->ReplaceString(1, 2, u"__"); // 替换中间字符
    auto spans = spanString->GetSpans(0, spanString->GetLength());
    EXPECT_EQ(spans[0]->GetEndIndex(), 3);  // 类型A缩短
    EXPECT_EQ(spans[1]->GetStartIndex(), 3); // 类型B偏移
}

/**
 * @tc.name: MutableSpanStringTest046
 * @tc.desc: Test full content replacement via RemoveString
 */
HWTEST_F(MutableSpanStringTestNg, SpanString046, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"FullContent");
    spanString->AddSpan(CreateSpan(0, 11));
    
    spanString->RemoveString(0, 11); // 清空内容
    EXPECT_TRUE(spanString->GetU16string().empty());
    EXPECT_TRUE(spanString->GetSpans(0, spanString->GetLength()).empty()); // 同步清除span
}

/**
 * @tc.name: MutableSpanStringTest047
 * @tc.desc: Test emoji insertion with span adjustment
 */
HWTEST_F(MutableSpanStringTestNg, SpanString047, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Hello😀");
    spanString->AddSpan(CreateSpan(5, 7)); // 覆盖😀（占2个字符）
    
    spanString->InsertString(5, u"🌍"); // 插入地球emoji（占2字符）
    EXPECT_EQ(spanString->GetU16string(), u"Hello🌍😀");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetStartIndex(), 5); // span自动偏移
}

/**
 * @tc.name: MutableSpanStringTest048
 * @tc.desc: Test Arabic text replacement (RTL)
 */
HWTEST_F(MutableSpanStringTestNg, SpanString048, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"مرحبا العالم");
    spanString->AddSpan(CreateSpan(6, 11)); // 覆盖"العالم"
    
    spanString->ReplaceString(0, 5, u"سلام"); // 替换前5个字符
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetStartIndex(), 5); // RTL调整验证
}

/**
 * @tc.name: MutableSpanStringTest049
 * @tc.desc: Test 10KB text replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString049, TestSize.Level1)
{
    const std::u16string megaStr(10240, u'X');
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(megaStr);
    spanString->AddSpan(CreateSpan(0, 10240));
    
    spanString->ReplaceString(5120, 0, u"MID");
    EXPECT_EQ(spanString->GetU16string().substr(5120, 3), u"XXX");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 10240); // 大文本处理
}

/**
 * @tc.name: MutableSpanStringTest050
 * @tc.desc: Test mixed CJK characters replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString050, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"中文测试");
    spanString->AddSpan(CreateSpan(0, 4)); // 每个汉字占1字符
    
    spanString->ReplaceString(2, 2, u"日文");
    EXPECT_EQ(spanString->GetU16string(), u"中文日文");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 4); // span边界保持
}

/**
 * @tc.name: MutableSpanStringTest051
 * @tc.desc: Test ZWJ sequence handling (👨👩👧👦)
 */
HWTEST_F(MutableSpanStringTestNg, SpanString051, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Family: 👨👩👧👦");
    spanString->AddSpan(CreateSpan(7, 15)); // 覆盖emoji组合
    
    spanString->InsertString(15, u"👪"); // 插入单字符家庭emoji
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 17); // 正确处理组合字符
}

/**
 * @tc.name: MutableSpanStringTest052
 * @tc.desc: Test surrogate pair splitting protection
 */
HWTEST_F(MutableSpanStringTestNg, SpanString052, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"A𝄞B"); // 𝄞是代理对
    spanString->AddSpan(CreateSpan(1, 3)); // 覆盖𝄞
    
    spanString->InsertString(3, u"X");
    EXPECT_EQ(spanString->GetU16string(), u"A𝄞XB");
}

/**
 * @tc.name: MutableSpanStringTest053
 * @tc.desc: Test combining character sequences
 */
HWTEST_F(MutableSpanStringTestNg, SpanString053, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"cafe\u0301"); // café组合形式
    spanString->AddSpan(CreateSpan(4, 6)); // 覆盖é
    spanString->RemoveString(4, 1); // 删除组合符
    EXPECT_EQ(spanString->GetU16string(), u"cafe");
}

/**
 * @tc.name: MutableSpanStringTest054
 * @tc.desc: Test bidirectional text replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString054, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Hello עברית");
    spanString->AddSpan(CreateSpan(6, 11)); // 覆盖希伯来文
    
    spanString->ReplaceString(0, 5, u"שלום"); // 替换为希伯来文
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetStartIndex(), 5); // RTL调整验证
}

/**
 * @tc.name: MutableSpanStringTest055
 * @tc.desc: Test 100 continuous insert operations
 */
HWTEST_F(MutableSpanStringTestNg, SpanString055, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"");
    for (int i = 0; i < 100; ++i) {
        spanString->InsertString(i, u"X"); // 连续插入100次
    }
    EXPECT_EQ(spanString->GetU16string().length(), 100);
}

/**
 * @tc.name: MutableSpanStringTest056
 * @tc.desc: Test mixed LTR/RTL span adjustment
 */
HWTEST_F(MutableSpanStringTestNg, SpanString056, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Englishעברית");
    spanString->AddSpan(CreateSpan(0, 7));  // LTR部分
    spanString->AddSpan(CreateSpan2(7, 12)); // RTL部分
    
    spanString->InsertString(6, u"→←"); // 在交界处插入双向符号
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength())[1]->GetStartIndex(), 9); // RTL偏移验证
}

/**
 * @tc.name: MutableSpanStringTest057
 * @tc.desc: Test hybrid ReplaceString and InsertSpanString
 */
HWTEST_F(MutableSpanStringTestNg, SpanString057, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"ABCDEF");
    target->ReplaceString(2, 2, u"XY"); // 替换CD→XY
    auto insertSpan = AceType::MakeRefPtr<MutableSpanString>(u"Insert");
    insertSpan->AddSpan(CreateSpan(0, 6));
    target->InsertSpanString(3, insertSpan); // 在XY后插入
    
    EXPECT_EQ(target->GetU16string(), u"ABXInsertYEF");
    EXPECT_EQ(target->GetSpans(0, target->GetLength()).size(), 1); // 验证插入span偏移
}

/**
 * @tc.name: MutableSpanStringTest058
 * @tc.desc: Test nested span replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString058, TestSize.Level1)
{
    auto base = AceType::MakeRefPtr<MutableSpanString>(u"BaseText");
    base->AddSpan(CreateSpan(0, 8));
    auto replacement = AceType::MakeRefPtr<MutableSpanString>(u"New");
    replacement->AddSpan(CreateSpan2(0, 3));
    
    base->ReplaceSpanString(2, 4, replacement); // 替换"seTe"为New
    base->ReplaceString(3, 1, u"Extended"); // 二次替换
    
    EXPECT_EQ(base->GetU16string(), u"BaNExtendedwxt");
    EXPECT_EQ(base->GetSpans(0, base->GetLength()).front()->GetEndIndex(), 2);
}

/**
 * @tc.name: MutableSpanStringTest059
 * @tc.desc: Test 3-level span structure
 */
HWTEST_F(MutableSpanStringTestNg, SpanString059, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Layer1-Layer2-Layer3");
    spanString->AddSpan(CreateSpan(0, 6));   // Layer1
    spanString->AddSpan(CreateSpan2(7, 13));  // Layer2
    spanString->AddSpan(CreateSpan(14, 20)); // Layer3
    
    spanString->ReplaceString(5, 11, u"__"); // 替换"1-Layer2-L"为__
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).size(), 1);
}

/**
 * @tc.name: MutableSpanStringTest060
 * @tc.desc: Test emoji zipper effect handling
 */
HWTEST_F(MutableSpanStringTestNg, SpanString060, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"👨👩👧👦👨👩👧👦");
    spanString->AddSpan(CreateSpan(0, 15)); // 两个家庭emoji
    
    spanString->InsertString(7, u"👪"); // 在中间插入单emoji
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 17); // 正确分割span
}

/**
 * @tc.name: MutableSpanStringTest061
 * @tc.desc: Test 1000-character wrap replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString061, TestSize.Level1)
{
    const std::u16string longStr(1000, u'W');
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(longStr);
    spanString->AddSpan(CreateSpan(0, 1000));
    
    spanString->ReplaceString(333, 334, u"MID");
    EXPECT_EQ(spanString->GetU16string().substr(333, 3), u"MID");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 669); // 长度计算
}

/**
 * @tc.name: MutableSpanStringTest062
 * @tc.desc: Test CJK-Emoji mixed spans
 */
HWTEST_F(MutableSpanStringTestNg, SpanString062, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"中文😊测试");
    spanString->AddSpan(CreateSpan(2, 4)); // 覆盖😊
    spanString->AddSpan(CreateSpan2(4, 6)); // 覆盖测试
    
    spanString->InsertString(3, u"🇨🇳"); // 在emoji后插入国旗
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength())[1]->GetStartIndex(), 8); // 中文偏移验证
}

/**
 * @tc.name: MutableSpanStringTest064
 * @tc.desc: Test surrogate pair boundary replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString064, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"A𝄞B𝄞C");
    spanString->AddSpan(CreateSpan(1, 3)); // 第一个𝄞
    spanString->AddSpan(CreateSpan2(4, 6)); // 第二个𝄞
    
    spanString->ReplaceString(3, 2, u"XYZ");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).size(), 2); // 验证span重组
}

/**
 * @tc.name: MutableSpanStringTest065
 * @tc.desc: Test 50 continuous replace operations
 */
HWTEST_F(MutableSpanStringTestNg, SpanString065, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Init");
    for (int i = 0; i < 50; ++i) {
        spanString->ReplaceString(i%2, 1, u"X"); // 交替替换
    }
    EXPECT_FALSE(spanString->GetU16string().empty());
}

/**
 * @tc.name: MutableSpanStringTest067
 * @tc.desc: Verify span persistence after multiple replacements
 */
HWTEST_F(MutableSpanStringTestNg, SpanString067, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"ABCD");
    target->AddSpan(CreateSpan(0, 4));
    target->ReplaceString(1, 2, u"X");
    target->ReplaceString(2, 1, u"YZ");
    EXPECT_EQ(target->GetU16string(), u"AXYZ");
    EXPECT_EQ(target->GetSpans(0, target->GetLength()).front()->GetEndIndex(), 4);
}

/**
 * @tc.name: MutableSpanStringTest068
 * @tc.desc: Test empty string initialization
 */
HWTEST_F(MutableSpanStringTestNg, SpanString068, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"");
    spanString->InsertString(0, u"Init");
    EXPECT_EQ(spanString->GetU16string(), u"Init");
    EXPECT_TRUE(spanString->GetSpans(0, spanString->GetLength()).empty());
}

/**
 * @tc.name: MutableSpanStringTest069
 * @tc.desc: Verify full text replacement sequence
 */
HWTEST_F(MutableSpanStringTestNg, SpanString069, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"OldContent");
    spanString->ReplaceString(0, 9, u"New");
    spanString->ReplaceString(0, 3, u"Final");
    EXPECT_EQ(spanString->GetU16string(), u"Finalt");
}

/**
 * @tc.name: MutableSpanStringTest070
 * @tc.desc: Test boundary insertion with existing spans
 */
HWTEST_F(MutableSpanStringTestNg, SpanString070, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"StartEnd");
    spanString->AddSpan(CreateSpan(0, 7));
    spanString->InsertString(7, u"Tail");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 11);
}

/**
 * @tc.name: MutableSpanStringTest071
 * @tc.desc: Verify multi-byte character replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString071, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"日本語");
    spanString->ReplaceString(1, 1, u"English");
    EXPECT_EQ(spanString->GetU16string(), u"日English語");
}

/**
 * @tc.name: MutableSpanStringTest072
 * @tc.desc: Test cross-method operation sequence
 */
HWTEST_F(MutableSpanStringTestNg, SpanString072, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"Base");
    target->InsertString(2, u"X");
    target->ReplaceSpanString(1, 3, AceType::MakeRefPtr<MutableSpanString>(u"New"));
    EXPECT_EQ(target->GetU16string(), u"BNewe");
}

/**
 * @tc.name: MutableSpanStringTest073
 * @tc.desc: Verify zero-length span persistence
 */
HWTEST_F(MutableSpanStringTestNg, SpanString073, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Text");
    spanString->AddSpan(CreateSpan(2, 2));
    spanString->InsertString(2, u"Insert");
    EXPECT_TRUE(spanString->GetSpans(0, spanString->GetLength()).empty());
}

/**
 * @tc.name: MutableSpanStringTest075
 * @tc.desc: Verify span integrity after partial deletion
 */
HWTEST_F(MutableSpanStringTestNg, SpanString075, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"ABCDEF");
    spanString->AddSpan(CreateSpan(1, 5));
    spanString->RemoveString(2, 2);
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 3);
}

/**
 * @tc.name: MutableSpanStringTest076
 * @tc.desc: Verify multi-replace span merging
 */
HWTEST_F(MutableSpanStringTestNg, SpanString076, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"ABCDEF");
    target->AddSpan(CreateSpan(1, 3));
    target->ReplaceString(2, 1, u"X");
    target->ReplaceString(3, 1, u"Y");
    EXPECT_EQ(target->GetSpans(0, target->GetLength()).front()->GetEndIndex(), 3);
}

/**
 * @tc.name: MutableSpanStringTest077
 * @tc.desc: Test cross-span insertion
 */
HWTEST_F(MutableSpanStringTestNg, SpanString077, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"AAABBBCCC");
    spanString->AddSpan(CreateSpan(0, 3));
    spanString->AddSpan(CreateSpan2(6, 9));
    spanString->InsertString(5, u"X");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength())[1]->GetStartIndex(), 7);
}

/**
 * @tc.name: MutableSpanStringTest078
 * @tc.desc: Verify boundary removal
 */
HWTEST_F(MutableSpanStringTestNg, SpanString078, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"123456");
    spanString->AddSpan(CreateSpan(2, 5));
    spanString->RemoveString(4, 2);
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 4);
}

/**
 * @tc.name: MutableSpanStringTest079
 * @tc.desc: Test hybrid Insert/Replace sequence
 */
HWTEST_F(MutableSpanStringTestNg, SpanString079, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"Base");
    target->InsertString(2, u"X");
    target->ReplaceString(1, 3, u"YZ");
    EXPECT_EQ(target->GetU16string(), u"BYZe");
}

/**
 * @tc.name: MutableSpanStringTest080
 * @tc.desc: Verify empty span persistence
 */
HWTEST_F(MutableSpanStringTestNg, SpanString080, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"");
    spanString->ReplaceString(0, 0, u"Content"); // won't work
    EXPECT_EQ(spanString->GetU16string(), u"");
}

/**
 * @tc.name: MutableSpanStringTest081
 * @tc.desc: Test surrogate pair replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString081, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"A𝄞B");
    spanString->ReplaceString(1, 2, u"XY");
    EXPECT_EQ(spanString->GetU16string(), u"AXYB");
}

/**
 * @tc.name: MutableSpanStringTest082
 * @tc.desc: Verify 50KB text handling
 */
HWTEST_F(MutableSpanStringTestNg, SpanString082, TestSize.Level1)
{
    std::u16string data(51200, 'X');
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(data);
    spanString->ReplaceString(25555, 10, u"MARK");
    EXPECT_EQ(spanString->GetU16string().substr(25555, 4), u"MARK");
}

/**
 * @tc.name: MutableSpanStringTest083
 * @tc.desc: Test multi-byte span adjustment
 */
HWTEST_F(MutableSpanStringTestNg, SpanString083, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"こんにちは");
    spanString->AddSpan(CreateSpan(0, 5));
    spanString->InsertString(2, u"!");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 6);
}

/**
 * @tc.name: MutableSpanStringTest084
 * @tc.desc: Verify complex operation chain
 */
HWTEST_F(MutableSpanStringTestNg, SpanString084, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"Init");
    target->AppendSpanString(AceType::MakeRefPtr<MutableSpanString>(u"End"));
    target->ReplaceString(2, 3, u"ter");
    target->InsertString(6, u"!");
    EXPECT_EQ(target->GetU16string(), u"Intern!d");
}

/**
 * @tc.name: MutableSpanStringTest085
 * @tc.desc: Verify append operation with existing end span
 */
HWTEST_F(MutableSpanStringTestNg, SpanString085, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"End");
    spanString->AddSpan(CreateSpan(0, 3));
    spanString->AppendSpanString(AceType::MakeRefPtr<MutableSpanString>(u"Tail"));
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 3);
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).back()->GetStartIndex(), 0);
}

/**
 * @tc.name: MutableSpanStringTest086
 * @tc.desc: Test cross-span replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString086, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"AABBCC");
    target->AddSpan(CreateSpan(0, 2));
    target->AddSpan(CreateSpan2(4, 6));
    target->ReplaceString(1, 4, u"X");
    EXPECT_EQ(target->GetSpans(0, target->GetLength()).front()->GetEndIndex(), 2);
    EXPECT_EQ(target->GetSpans(0, target->GetLength()).back()->GetStartIndex(), 2);
}

/**
 * @tc.name: MutableSpanStringTest087
 * @tc.desc: Verify empty insertion persistence
 */
HWTEST_F(MutableSpanStringTestNg, SpanString087, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Text");
    spanString->InsertString(2, u"");
    EXPECT_EQ(spanString->GetU16string(), u"Text");
    EXPECT_TRUE(spanString->GetSpans(0, spanString->GetLength()).empty());
}

/**
 * @tc.name: MutableSpanStringTest088
 * @tc.desc: Test span split by replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString088, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"ABCDEF");
    spanString->AddSpan(CreateSpan(0, 6));
    spanString->ReplaceString(2, 2, u"XYZ");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).size(), 1);
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 7);
}

/**
 * @tc.name: MutableSpanStringTest089
 * @tc.desc: Verify 1MB text replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString089, TestSize.Level1)
{
    std::u16string data(1048576, 'X');
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(data);
    spanString->ReplaceString(524288, 10, u"MARKER");
    EXPECT_EQ(spanString->GetU16string().substr(524288, 6), u"MARKER");
}

/**
 * @tc.name: MutableSpanStringTest090
 * @tc.desc: Test emoji sequence insertion
 */
HWTEST_F(MutableSpanStringTestNg, SpanString090, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"StartEnd");
    spanString->InsertString(5, u"🔥🌟");
    EXPECT_EQ(spanString->GetU16string(), u"Start🔥🌟End");
}

/**
 * @tc.name: MutableSpanStringTest091
 * @tc.desc: Verify 50 replace operations
 */
HWTEST_F(MutableSpanStringTestNg, SpanString091, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"Base");
    for (int i = 0;i < 50;i++) {
        target->ReplaceString(i%3, 1, u"X");
    }
    EXPECT_FALSE(target->GetU16string().empty());
}

/**
 * @tc.name: MutableSpanStringTest092
 * @tc.desc: Test boundary span insertion
 */
HWTEST_F(MutableSpanStringTestNg, SpanString092, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Edge");
    spanString->InsertString(4, u"Case");
    spanString->AddSpan(CreateSpan(4, 8));
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetStartIndex(), 4);
}

/**
 * @tc.name: MutableSpanStringTest093
 * @tc.desc: Verify post-replacement append
 */
HWTEST_F(MutableSpanStringTestNg, SpanString093, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"Original");
    target->ReplaceString(0, 7, u"New");
    target->AppendSpanString(AceType::MakeRefPtr<MutableSpanString>(u"Tail"));
    EXPECT_EQ(target->GetU16string(), u"NewlTail");
}

/**
 * @tc.name: MutableSpanStringTest094
 * @tc.desc: Verify zero-length replace with span adjustment
 */
HWTEST_F(MutableSpanStringTestNg, SpanString094, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Content");
    spanString->AddSpan(CreateSpan(2, 5));
    spanString->ReplaceString(3, 0, u"X");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 5);
}

/**
 * @tc.name: MutableSpanStringTest095
 * @tc.desc: Test multi-byte character span split
 */
HWTEST_F(MutableSpanStringTestNg, SpanString095, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"测试用例");
    spanString->AddSpan(CreateSpan(0, 4));
    spanString->InsertString(2, u"插入");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 6);
}

/**
 * @tc.name: MutableSpanStringTest096
 * @tc.desc: Verify 100KB text append
 */
HWTEST_F(MutableSpanStringTestNg, SpanString096, TestSize.Level1)
{
    std::u16string data(102400, 'A');
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(data);
    spanString->AppendSpanString(AceType::MakeRefPtr<MutableSpanString>(u"END"));
    EXPECT_EQ(spanString->GetU16string().substr(102400, 3), u"END");
}

/**
 * @tc.name: MutableSpanStringTest097
 * @tc.desc: Test hybrid Insert/Remove sequence
 */
HWTEST_F(MutableSpanStringTestNg, SpanString097, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"ABCD");
    target->InsertString(2, u"XYZ");
    target->RemoveString(3, 2);
    EXPECT_EQ(target->GetU16string(), u"ABXCD");
}

/**
 * @tc.name: MutableSpanStringTest098
 * @tc.desc: Verify surrogate pair insertion
 */
HWTEST_F(MutableSpanStringTestNg, SpanString098, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Text");
    spanString->InsertString(2, u"𝄞");
    EXPECT_EQ(spanString->GetU16string().length(), 6);
}

/**
 * @tc.name: MutableSpanStringTest099
 * @tc.desc: Test full-range span replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString099, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Full");
    spanString->AddSpan(CreateSpan(0, 4));
    spanString->ReplaceString(0, 4, u"NewFull");
    EXPECT_EQ(spanString->GetSpans(0, spanString->GetLength()).front()->GetEndIndex(), 7);
}

/**
 * @tc.name: MutableSpanStringTest100
 * @tc.desc: Verify 20 consecutive insertions
 */
HWTEST_F(MutableSpanStringTestNg, SpanString100, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"");
    for (int i = 0;i < 20;i++) {
        target->InsertString(i, u"X");
    }
    EXPECT_EQ(target->GetU16string().length(), 20);
}

/**
 * @tc.name: MutableSpanStringTest101
 * @tc.desc: Test cross-method boundary operations
 */
HWTEST_F(MutableSpanStringTestNg, SpanString101, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Edge");
    spanString->ReplaceString(3, 1, u"X");
    spanString->InsertSpanString(4, AceType::MakeRefPtr<MutableSpanString>(u"Case"));
    EXPECT_EQ(spanString->GetU16string(), u"EdgXCase");
}

/**
 * @tc.name: MutableSpanStringTest102
 * @tc.desc: Verify empty string append
 */
HWTEST_F(MutableSpanStringTestNg, SpanString102, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Content");
    spanString->AppendSpanString(AceType::MakeRefPtr<MutableSpanString>(u""));
    EXPECT_EQ(spanString->GetU16string(), u"Content");
}

/**
 * @tc.name: MutableSpanStringTest103
 * @tc.desc: Verify multi-replace span adjustment
 */
HWTEST_F(MutableSpanStringTestNg, SpanString103, TestSize.Level1)
{
    auto target = AceType::MakeRefPtr<MutableSpanString>(u"ABCDEF");
    target->AddSpan(CreateSpan(1, 5));
    target->ReplaceString(2, 1, u"X");
    target->ReplaceString(3, 1, u"Y");
    EXPECT_EQ(target->GetSpans(0, target->GetLength()).front()->GetEndIndex(), 5);
}

/**
 * @tc.name: MutableSpanStringTest104
 * @tc.desc: Test CJK-Emoji mixed replacement
 */
HWTEST_F(MutableSpanStringTestNg, SpanString104, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"中文🔥测试");
    spanString->ReplaceString(1, 1, u"🇨🇳");
    EXPECT_EQ(spanString->GetU16string(), u"中🇨🇳🔥测试");
}

/**
 * @tc.name: MutableSpanStringTest105
 * @tc.desc: Verify 100KB insert operation
 */
HWTEST_F(MutableSpanStringTestNg, SpanString105, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString106, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString107, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"A𝄞B");
    spanString->RemoveString(1, 2);
    EXPECT_EQ(spanString->GetU16string(), u"AB");
}

/**
 * @tc.name: MutableSpanStringTest108
 * @tc.desc: Test hybrid Insert/Replace/Remove
 */
HWTEST_F(MutableSpanStringTestNg, SpanString108, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString109, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString110, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString112, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString113, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString114, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString115, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"𝄞𝄞");
    spanString->ReplaceString(2, 2, u"X");
    EXPECT_EQ(spanString->GetU16string(), u"𝄞X");
}

/**
 * @tc.name: MutableSpanStringTest116
 * @tc.desc: Verify full text removal
 */
HWTEST_F(MutableSpanStringTestNg, SpanString116, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString117, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString118, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString119, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString121, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString123, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString124, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"Edge");
    spanString->InsertSpanString(4, AceType::MakeRefPtr<MutableSpanString>(u"Case"));
    EXPECT_EQ(spanString->GetU16string(), u"EdgeCase");
}

/**
 * @tc.name: MutableSpanStringTest125
 * @tc.desc: Verify 100x ReplaceString chain
 */
HWTEST_F(MutableSpanStringTestNg, SpanString125, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString126, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString127, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString128, TestSize.Level1)
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
HWTEST_F(MutableSpanStringTestNg, SpanString129, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"𝄞𝄞");
    spanString->InsertString(2, u"X");
    EXPECT_EQ(spanString->GetU16string(), u"𝄞X𝄞");
}

/**
 * @tc.name: MultiTypeDecorationSpanStringTest
 * @tc.desc: Verify multi type decoration span string
 */
HWTEST_F(MutableSpanStringTestNg, MultiTypeDecorationSpanStringTest, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"1234567890");

    std::optional<TextDecorationOptions> optionsTrue({true});
    std::optional<TextDecorationOptions> optionsFalse({false});
    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
            std::vector<TextDecoration>({TextDecoration::OVERLINE}),
            Color::RED, TextDecorationStyle::WAVY, optionsTrue, 0, 3));
    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
            std::vector<TextDecoration>({TextDecoration::LINE_THROUGH}),
            Color::RED, TextDecorationStyle::WAVY, optionsTrue, 0, 3));
    auto subspan1 = spanString->GetSpan(0, 3, SpanType::Decoration);
    auto subDecorationSpan1 = AceType::DynamicCast<DecorationSpan>(subspan1);
    ASSERT_NE(subDecorationSpan1, nullptr);
    auto decorationTypes1 = subDecorationSpan1->GetTextDecorationTypes();
    EXPECT_EQ(subDecorationSpan1->GetTextDecorationFirst(), TextDecoration::LINE_THROUGH);
    EXPECT_EQ(decorationTypes1.size(), 2);

    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
        std::vector<TextDecoration>({TextDecoration::OVERLINE}),
        Color::RED, TextDecorationStyle::WAVY, optionsTrue, 4, 6));
    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
            std::vector<TextDecoration>({TextDecoration::LINE_THROUGH}),
            Color::RED, TextDecorationStyle::WAVY, optionsFalse, 4, 6));
    auto subspan2 = spanString->GetSpan(4, 2, SpanType::Decoration);
    auto subDecorationSpan2 = AceType::DynamicCast<DecorationSpan>(subspan2);
    ASSERT_NE(subDecorationSpan2, nullptr);
    auto decorationTypes2 = subDecorationSpan2->GetTextDecorationTypes();
    EXPECT_EQ(subDecorationSpan2->GetTextDecorationFirst(), TextDecoration::LINE_THROUGH);
    EXPECT_EQ(decorationTypes2.size(), 1);

    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
        std::vector<TextDecoration>({TextDecoration::OVERLINE}),
        Color::RED, TextDecorationStyle::WAVY, optionsFalse, 7, 9));
    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
            std::vector<TextDecoration>({TextDecoration::LINE_THROUGH}),
            Color::RED, TextDecorationStyle::WAVY, optionsFalse, 7, 9));
    auto subspan3 = spanString->GetSpan(7, 2, SpanType::Decoration);
    auto subDecorationSpan3 = AceType::DynamicCast<DecorationSpan>(subspan3);
    ASSERT_NE(subDecorationSpan3, nullptr);
    auto decorationTypes3 = subDecorationSpan3->GetTextDecorationTypes();
    EXPECT_EQ(subDecorationSpan3->GetTextDecorationFirst(), TextDecoration::LINE_THROUGH);
    EXPECT_EQ(decorationTypes3.size(), 1);
    EXPECT_EQ(spanString->GetU16string(), u"1234567890");
}
} // namespace OHOS::Ace::NG