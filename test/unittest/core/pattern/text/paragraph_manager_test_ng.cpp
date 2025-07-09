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

#include "test/mock/core/render/mock_paragraph.h"

#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/text/paragraph_util.h"
#include "core/components_ng/pattern/text/span_node.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t POSITION_WITH_AFFINITY = 2;
constexpr int32_t PARAM_NUMBER_FOUR = 4;
constexpr int32_t PARAM_NUMBER_FIVE = 5;
} // namespace
class ParagraphManagerTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;

    void ConstructParagraphs(RefPtr<ParagraphManager>& pManager);

    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
};

void ParagraphManagerTestNg::SetUp()
{
    MockParagraph::GetOrCreateMockParagraph();
    ConstructParagraphs(pManager);
}

void ParagraphManagerTestNg::TearDown()
{
    MockParagraph::TearDown();
}

void ParagraphManagerTestNg::ConstructParagraphs(RefPtr<ParagraphManager>& pManager)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(100.f));
    EXPECT_CALL(*paragraph, GetLongestLine()).WillRepeatedly(Return(100.f));
    EXPECT_CALL(*paragraph, GetMaxWidth()).WillRepeatedly(Return(100.f));
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(1));
    EXPECT_CALL(*paragraph, GetTextWidth()).WillRepeatedly(Return(100.f));
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(4));
    PositionWithAffinity positionWithAffinity(POSITION_WITH_AFFINITY, TextAffinity::UPSTREAM);
    EXPECT_CALL(*paragraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(positionWithAffinity));
    TextLineMetrics textLineMetrics;
    textLineMetrics.lineNumber = 0;
    EXPECT_CALL(*paragraph, GetLineMetrics(_)).WillRepeatedly(Return(textLineMetrics));
    std::vector<RectF> selectedRects;
    std::vector<TextDirection> textDirections;
    RectF rect = RectF(10, 10, 40, 20);
    selectedRects.emplace_back(rect);
    textDirections.emplace_back(TextDirection::RTL);
    EXPECT_CALL(*paragraph, TxtGetRectsForRange(_, _, _, _, _, _))
        .WillRepeatedly(DoAll(SetArgReferee<PARAM_NUMBER_FOUR>(selectedRects),
            SetArgReferee<PARAM_NUMBER_FIVE>(textDirections)));
    EXPECT_CALL(*paragraph, GetWordBoundary(_, _, _))
        .WillRepeatedly(DoAll(SetArgReferee<1>(0), SetArgReferee<2>(1), Return(true)));
    pManager->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 20 });

    pManager->AddParagraph({ .paragraph = paragraph, .start = 20, .end = 35 });

    pManager->AddParagraph({ .paragraph = paragraph, .start = 35, .end = 40 });
}

/**
 * @tc.name: GetGlyphIndexByCoordinate001
 * @tc.desc: Test GetGlyphIndexByCoordinate.
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphManagerTestNg, GetGlyphIndexByCoordinate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pManager and construct paragraphs.
     */

    /**
     * @tc.steps: step2. call GetGlyphIndexByCoordinate.
     * @tc.expected: the position of the acquisition is in the first paragraph.
     */
    auto offset = Offset(50.0, 80.0);
    auto result = pManager->GetGlyphIndexByCoordinate(offset);
    EXPECT_EQ(result, 4);

    /**
     * @tc.steps: step3. call GetGlyphIndexByCoordinate.
     * @tc.expected: the position of the acquisition is in the second paragraph.
     */
    offset = Offset(50.0, 110.0);
    result = pManager->GetGlyphIndexByCoordinate(offset);
    EXPECT_EQ(result, 24);

    /**
     * @tc.steps: step4. call GetGlyphIndexByCoordinate.
     * @tc.expected: the position of the acquisition is in the third paragraph.
     */
    offset = Offset(50.0, 210.0);
    result = pManager->GetGlyphIndexByCoordinate(offset);
    EXPECT_EQ(result, 39);

    /**
     * @tc.steps: step4. call GetGlyphIndexByCoordinate.
     * @tc.expected: the position of the acquisition is in the third paragraph.
     */
    offset = Offset(50.0, 310.0);
    result = pManager->GetGlyphIndexByCoordinate(offset);
    EXPECT_EQ(result, 39);
}

/**
 * @tc.name: GetWordBoundary001
 * @tc.desc: Test GetWordBoundary.
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphManagerTestNg, GetWordBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pManager and construct paragraphs.
     */
    int32_t start;
    int32_t end;

    /**
     * @tc.steps: step2. call GetWordBoundary.
     * @tc.expected: the position of the acquisition is in the first paragraph.
     */
    auto offset = 10;
    pManager->GetWordBoundary(offset, start, end);
    EXPECT_EQ(start, 0);
    EXPECT_EQ(end, 1);

    /**
     * @tc.steps: step3. call GetWordBoundary.
     * @tc.expected: the position of the acquisition is in the first paragraph.
     */
    offset = 25;
    pManager->GetWordBoundary(offset, start, end);
    EXPECT_EQ(start, 20);
    EXPECT_EQ(end, 21);

    /**
     * @tc.steps: step4. call GetWordBoundary.
     * @tc.expected: the position of the acquisition is in the first paragraph.
     */
    offset = 37;
    pManager->GetWordBoundary(offset, start, end);
    EXPECT_EQ(start, 35);
    EXPECT_EQ(end, 36);
}

/**
 * @tc.name: GetLongestLine001
 * @tc.desc: Test GetLongestLine.
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphManagerTestNg, GetLongestLine001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pManager and construct paragraphs.
     */

    /**
     * @tc.steps: step2. call GetLongestLine.
     * @tc.expected: the LongestLine of the paragraphs is correct.
     */
    auto result = pManager->GetLongestLine();
    EXPECT_EQ(result, 100);

    /**
     * @tc.steps: step3. call GetGetMaxWidth.
     * @tc.expected: the MaxWidth of the paragraphs is correct.
     */
    result = pManager->GetLongestLine();
    EXPECT_EQ(result, 100);

    /**
     * @tc.steps: step4. call GetLineCount.
     * @tc.expected: the number of lines is the sum of the paragraphs.
     */
    result = pManager->GetLineCount();
    EXPECT_EQ(result, 3);
}

/**
 * @tc.name: GetGlyphPositionAtCoordinate001
 * @tc.desc: Test GetGlyphPositionAtCoordinate.
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphManagerTestNg, GetGlyphPositionAtCoordinate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pManager and construct paragraphs.
     */

    /**
     * @tc.steps: step2. call GetGlyphPositionAtCoordinate.
     * @tc.expected: the position of the paragraphs is 2.
     */
    auto result = pManager->GetGlyphPositionAtCoordinate(Offset(10.0, 50.0)).position_;
    EXPECT_EQ(result, 2);

    /**
     * @tc.steps: step3. call GetGlyphPositionAtCoordinate.
     * @tc.expected: the position of the paragraphs is 22.
     */
    result = pManager->GetGlyphPositionAtCoordinate(Offset(10.0, 150.0)).position_;
    EXPECT_EQ(result, 22);

    /**
     * @tc.steps: step4. call GetGlyphPositionAtCoordinate.
     * @tc.expected: the position of the paragraphs is 37.
     */
    result = pManager->GetGlyphPositionAtCoordinate(Offset(10.0, 250.0)).position_;
    EXPECT_EQ(result, 37);
}

/**
 * @tc.name: GetLineMetrics001
 * @tc.desc: Test GetLineMetrics.
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphManagerTestNg, GetLineMetrics001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pManager and construct paragraphs.
     */

    /**
     * @tc.steps: step2. call GetLineMetrics.
     * @tc.expected: the lineNumber of the paragraphs is 0.
     */
    auto result = pManager->GetLineMetrics(0).lineNumber;
    EXPECT_EQ(result, 0);

    /**
     * @tc.steps: step3. call GetLineMetrics.
     * @tc.expected: the lineNumber of the paragraphs is 1.
     */
    result = pManager->GetLineMetrics(1).lineNumber;
    EXPECT_EQ(result, 1);

    /**
     * @tc.steps: step4. call GetLineMetrics.
     * @tc.expected: the lineNumber of the paragraphs is 2.
     */
    result = pManager->GetLineMetrics(2).lineNumber;
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: GetRectsForRange001
 * @tc.desc: Test GetRectsForRange.
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphManagerTestNg, GetRectsForRange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pManager and construct paragraphs.
     */

    /**
     * @tc.steps: step2. call GetRectsForRange.
     * @tc.expected: the position of the rect is in the first paragraph.
     */
    auto result =
        pManager->GetRectsForRange(0, 10, OHOS::Ace::RectHeightStyle::TIGHT, OHOS::Ace::RectWidthStyle::TIGHT);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].rect_.GetX(), 10.0f);
    EXPECT_EQ(result[0].rect_.GetY(), 10.0f);
    EXPECT_EQ(result[0].rect_.Height(), 20.0f);
    EXPECT_EQ(result[0].rect_.Width(), 40.0f);

    /**
     * @tc.steps: step3. call GetRectsForRange.
     * @tc.expected: the position of the rect is spans two paragraphs.
     */
    result = pManager->GetRectsForRange(15, 30, OHOS::Ace::RectHeightStyle::TIGHT, OHOS::Ace::RectWidthStyle::TIGHT);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[1].rect_.GetX(), 10.0f);
    EXPECT_EQ(result[1].rect_.GetY(), 110.0f);
    EXPECT_EQ(result[1].rect_.Height(), 20.0f);
    EXPECT_EQ(result[1].rect_.Width(), 40.0f);

    /**
     * @tc.steps: step4. call GetRectsForRange.
     * @tc.expected: the position of the rect is in the last paragraph.
     */
    result = pManager->GetRectsForRange(37, 39, OHOS::Ace::RectHeightStyle::TIGHT, OHOS::Ace::RectWidthStyle::TIGHT);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].rect_.GetX(), 10.0f);
    EXPECT_EQ(result[0].rect_.GetY(), 210.0f);
    EXPECT_EQ(result[0].rect_.Height(), 20.0f);
    EXPECT_EQ(result[0].rect_.Width(), 40.0f);

    /**
     * @tc.steps: step5. call GetRectsForRange.
     * @tc.expected: exceeding paragraphs scope.
     */
    result = pManager->GetRectsForRange(40, 50, OHOS::Ace::RectHeightStyle::TIGHT, OHOS::Ace::RectWidthStyle::TIGHT);
    EXPECT_TRUE(result.empty());

    /**
     * @tc.steps: step6. call GetRectsForRange.
     * @tc.expected: start greater than end.
     */
    result = pManager->GetRectsForRange(25, 20, OHOS::Ace::RectHeightStyle::TIGHT, OHOS::Ace::RectWidthStyle::TIGHT);
    EXPECT_TRUE(result.empty());
}


/**
 * @tc.name: ParagraphUtil001
 * @tc.desc: test ParagraphUtil GetParagraphStyle
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphManagerTestNg, ParagraphUtil001, TestSize.Level1)
{
    TextStyle textStyle;
    textStyle.SetFontSize(Dimension(10));
    ParagraphStyle paraStyle = ParagraphUtil::GetParagraphStyle(textStyle);
    paraStyle.fontSize = textStyle.GetFontSize().ConvertToPx();
    EXPECT_EQ(paraStyle.fontSize, 10.0);
}

/**
 * @tc.name: ParagraphUtil002
 * @tc.desc: test ParagraphUtil GetTextDirectionByContent
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphManagerTestNg, ParagraphUtil002, TestSize.Level1)
{
    TextDirection direction;
    direction = ParagraphUtil::GetTextDirectionByContent(u"error");
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: ParagraphUtil003
 * @tc.desc: test ParagraphUtil ConstructParagraphSpanGroup
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphManagerTestNg, ParagraphUtil003, TestSize.Level1)
{
    // std::list<RefPtr<SpanItem>> spans;
    std::vector<std::list<RefPtr<SpanItem>>> spanGroupVec;
    std::list<RefPtr<SpanItem>> spans;
    RefPtr<SpanItem> span1 = AceType::MakeRefPtr<SpanItem>();
    span1->content = u"span1";
    uint32_t MAX_LINES_VALUE0 = 3;
    span1->textLineStyle->propMaxLines = MAX_LINES_VALUE0;
    spans.emplace_back(span1);
    spanGroupVec.emplace_back(spans);

    bool hasMaxLines = false;
    ParagraphUtil::ConstructParagraphSpanGroup(spans, spanGroupVec, hasMaxLines);
    EXPECT_EQ(spanGroupVec.size(), 2);
    EXPECT_TRUE(hasMaxLines);
    EXPECT_TRUE(spans.empty());
}

/**
 * @tc.name: ParagraphUtil004
 * @tc.desc: test ParagraphUtil CreateImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphManagerTestNg, ParagraphUtil004, TestSize.Level1)
{
    ImageSpanOptions textOptions;
    auto ret = ParagraphUtil::CreateImageSourceInfo(textOptions);
    EXPECT_FALSE(textOptions.imageAttribute.has_value());

    textOptions.image = "";
    textOptions.bundleName = "";
    textOptions.moduleName = "";
    textOptions.imagePixelMap = nullptr;
    ParagraphUtil::CreateImageSourceInfo(textOptions);

    textOptions.image = "textImage";
    textOptions.bundleName = "textBundleName";
    textOptions.moduleName = "textModuleName";
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    textOptions.imagePixelMap = pixelMap;
    ParagraphUtil::CreateImageSourceInfo(textOptions);
    EXPECT_TRUE(textOptions.image.has_value());
    EXPECT_TRUE(textOptions.bundleName.has_value());
    EXPECT_TRUE(textOptions.moduleName.has_value());
}
} // namespace OHOS::Ace::NG