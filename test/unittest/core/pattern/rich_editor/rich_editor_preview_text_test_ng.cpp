/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
int32_t testFrameNodeId = 1;
int32_t testSpanNodeId = 1;
int32_t testNumber0 = 0;
int32_t testNumber2 = 2;
int32_t testNumber4 = 4;
int32_t testNumber5 = 5;
} // namespace

class RichEditorPreviewTextTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorPreviewTextTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorPreviewTextTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorPreviewTextTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: SetPreviewText001
 * @tc.desc: test setPreviewText and decoration available
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, SetPreviewText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto property = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdatePreviewTextStyle("underline");
    /**
     * @tc.steps: step1. set previewText
     */
    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    /**
     * @tc.steps: step2. test previewText content
     */
    auto previewTextRecord = richEditorPattern->previewTextRecord_;
    auto previewContent = previewTextRecord.previewContent;
    EXPECT_EQ(previewContent, PREVIEW_TEXT_VALUE1);
    EXPECT_EQ(previewTextRecord.startOffset, 0);
    auto length = static_cast<int32_t>(PREVIEW_TEXT_VALUE1.length());
    EXPECT_EQ(previewTextRecord.endOffset, previewTextRecord.startOffset + length);
    /**
     * @tc.steps: step3. set previewTextDecoration
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    auto paintProperty = richEditorPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    auto paintMethod = AceType::DynamicCast<RichEditorPaintMethod>(richEditorPattern->CreateNodePaintMethod());
    paintMethod->SetPreviewTextDecoration(AceType::RawPtr(paintWrapper));
    auto overlayMod =
        AceType::DynamicCast<RichEditorOverlayModifier>(paintMethod->GetOverlayModifier(AceType::RawPtr(paintWrapper)));
    ASSERT_NE(overlayMod, nullptr);
    /**
     * @tc.steps: step4. test previewTextDecoration
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    overlayMod->PaintPreviewTextDecoration(context);
    EXPECT_EQ(overlayMod->showPreviewTextDecoration_->Get(), true);
}

/**
 * @tc.name: SetPreviewText002
 * @tc.desc: test setPreviewText init, update, and delete available
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, SetPreviewText002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. set previewText
     */
    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    /**
     * @tc.steps: step2. update previewText
     */
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE2, previewRange);
    /**
     * @tc.steps: step3. test previewText content
     */
    auto& previewTextRecord = richEditorPattern->previewTextRecord_;
    auto previewContent = previewTextRecord.previewContent;
    EXPECT_EQ(previewContent, PREVIEW_TEXT_VALUE2);
    EXPECT_EQ(previewTextRecord.startOffset, 0);
    auto length = static_cast<int32_t>(PREVIEW_TEXT_VALUE2.length());
    EXPECT_EQ(previewTextRecord.endOffset, previewTextRecord.startOffset + length);
    /**
     * @tc.steps: step4. delete content  previewText
     */
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE3, previewRange);
    auto previewContent2 = previewTextRecord.previewContent;
    EXPECT_EQ(previewContent2, PREVIEW_TEXT_VALUE3);
    EXPECT_EQ(previewTextRecord.startOffset, 0);
    length = static_cast<int32_t>(PREVIEW_TEXT_VALUE3.length());
    EXPECT_EQ(richEditorPattern->previewTextRecord_.endOffset, previewTextRecord.startOffset + length);
}

/**
 * @tc.name: SetPreviewText003
 * @tc.desc: test SetPreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, SetPreviewText003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto property = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdatePreviewTextStyle("underline");
    std::vector<std::tuple<int, int, std::u16string, int>> testPreviewList;
    testPreviewList.emplace_back(-1, -1, PREVIEW_TEXT_VALUE1, 0);
    testPreviewList.emplace_back(0, -1, PREVIEW_TEXT_VALUE1, -1);
    testPreviewList.emplace_back(-1, 0, PREVIEW_TEXT_VALUE1, -1);
    testPreviewList.emplace_back(0, 0, PREVIEW_TEXT_VALUE1, 0);
    PreviewRange previewRange;
    for (const auto& testCase : testPreviewList) {
        previewRange.start = std::get<0>(testCase);
        previewRange.end = std::get<1>(testCase);
        ASSERT_EQ(richEditorPattern->SetPreviewText(std::get<2>(testCase), previewRange), std::get<3>(testCase));
    }
}


/**
 * @tc.name: SetPreviewText004
 * @tc.desc: test RichEditorPattern SetPreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, SetPreviewText004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::u16string previewTextValue;
    PreviewRange range;

    range.start = -1;
    range.end = 0;

    richEditorPattern->previewTextRecord_.previewContent = u"";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;

    richEditorPattern->SetPreviewText(previewTextValue, range);

    ASSERT_EQ(richEditorPattern->InitPreviewText(previewTextValue, range), false);

    range.start = -1;
    range.end = -1;
    richEditorPattern->previewTextRecord_.previewContent = u"";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = false;
    ASSERT_EQ(richEditorPattern->InitPreviewText(previewTextValue, range), true);
}

/**
 * @tc.name: FinishTextPreview001
 * @tc.desc: test FinishTextPreview available
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, FinishTextPreview001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. set previewText
     */
    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    /**
     * @tc.steps: step2.  FinishTextPreview
     */
    richEditorPattern->FinishTextPreview();
    /**
     * @tc.steps: step3. test previewText content
     */
    auto previewTextRecord = richEditorPattern->previewTextRecord_;
    auto previewContent = previewTextRecord.previewContent;
    EXPECT_EQ(previewContent, u"");
    EXPECT_EQ(previewTextRecord.startOffset, -1);
    EXPECT_EQ(previewTextRecord.endOffset, -1);
}

/**
 * @tc.name: FinishTextPreview002
 * @tc.desc: test FinishTextPreview by insertValue available
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, FinishTextPreview002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto property = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdatePreviewTextStyle("underline");

    /**
     * @tc.steps: step1. set previewText
     */
    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    /**
     * @tc.steps: step2.  test insertValue when previewTextInputting
     */
    richEditorPattern->InsertValue(PREVIEW_TEXT_VALUE1);
    EXPECT_EQ(richEditorPattern->spans_.size(), 1);
    auto it = richEditorPattern->spans_.begin();
    EXPECT_EQ((*it)->content, PREVIEW_TEXT_VALUE1);
}

/**
 * @tc.name: GetPreviewTextInfo001
 * @tc.desc: test RichEditorPattern GetPreviewTextInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, GetPreviewTextInfo001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    PreviewTextInfo info = richEditorPattern->GetPreviewTextInfo();
    ASSERT_EQ(richEditorPattern->previewTextRecord_.previewContent.empty(), true);

    richEditorPattern->previewTextRecord_.previewContent = u"abc";
    info = richEditorPattern->GetPreviewTextInfo();
    ASSERT_EQ(richEditorPattern->previewTextRecord_.previewContent.empty(), false);
}

/**
 * @tc.name: UpdatePreviewText001
 * @tc.desc: test UpdatePreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, UpdatePreviewText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto property = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdatePreviewTextStyle("underline");

    std::u16string previewTextValue = INIT_VALUE_1;
    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange);

    previewRange.start = -1;
    previewRange.end = -1;
    EXPECT_EQ(richEditorPattern->UpdatePreviewText(previewTextValue, previewRange), true);

    previewRange.start = 0;
    previewRange.end = -1;
    EXPECT_EQ(richEditorPattern->UpdatePreviewText(previewTextValue, previewRange), false);

    previewRange.start = -1;
    previewRange.end = 0;
    EXPECT_EQ(richEditorPattern->UpdatePreviewText(previewTextValue, previewRange), false);

    previewRange.start = 0;
    previewRange.end = 0;
    EXPECT_EQ(richEditorPattern->UpdatePreviewText(previewTextValue, previewRange), true);

    previewRange.start = richEditorPattern->previewTextRecord_.startOffset;
    previewRange.end = richEditorPattern->previewTextRecord_.endOffset;
    EXPECT_EQ(richEditorPattern->UpdatePreviewText(previewTextValue, previewRange), true);
}

/**
 * @tc.name: RichEditorPatternTestUpdatePreviewText001
 * @tc.desc: test UpdatePreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, RichEditorPatternTestUpdatePreviewText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::u16string previewTextValue;
    PreviewRange previewRange;

    previewRange.start = 0;
    previewRange.end = 0;
    ASSERT_EQ(richEditorPattern->UpdatePreviewText(previewTextValue, previewRange), false);
}

/**
 * @tc.name: PaintPreviewTextDecoration001
 * @tc.desc: test PaintPreviewTextDecoration
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, PaintPreviewTextDecoration001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto overlayMod = richEditorNode_->GetOverlayNode();
    auto richEditorOverlay = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    richEditorOverlay->SetPreviewTextStyle(PreviewTextStyle::NORMAL);
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100, 100 };
    richEditorOverlay->PaintPreviewTextDecoration(context);
    EXPECT_NE(richEditorOverlay->previewTextUnderlineWidth_, 0);
}

/**
 * @tc.name: RichEditorPatternTestInitPreviewText001
 * @tc.desc: test InitPreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, RichEditorPatternTestInitPreviewText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::u16string previewTextValue;
    PreviewRange range;

    range.start = -1;
    range.end = 0;
    ASSERT_EQ(richEditorPattern->InitPreviewText(previewTextValue, range), false);

    range.start = 0;
    range.end = -1;
    ASSERT_EQ(richEditorPattern->InitPreviewText(previewTextValue, range), false);

    range.start = -1;
    range.end = -1;
    ASSERT_EQ(richEditorPattern->InitPreviewText(previewTextValue, range), true);

    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    ASSERT_EQ(richEditorPattern->InitPreviewText(previewTextValue, range), true);
}

/**
 * @tc.name: GetPreviewTextDecorationColor001
 * @tc.desc: test GetPreviewTextDecorationColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, GetPreviewTextDecorationColor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto layoutproperty = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutproperty, nullptr);
    layoutproperty->UpdatePreviewTextStyle("underline");

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));

    auto oldThemeManager = PipelineBase::GetCurrentContext()->themeManager_;
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;

    RichEditorTheme richEditorTheme;
    EXPECT_EQ(richEditorPattern->GetPreviewTextDecorationColor(), richEditorTheme.GetPreviewUnderLineColor());

    auto property = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(property, nullptr);

    property->UpdatePreviewTextStyle("normal");
    EXPECT_EQ(richEditorPattern->GetPreviewTextDecorationColor(), Color::TRANSPARENT);

    PipelineBase::GetCurrentContext()->themeManager_ = oldThemeManager;
}

/**
 * @tc.name: GetPreviewTextUnderlineWidth001
 * @tc.desc: test GetPreviewTextUnderlineWidth
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, GetPreviewTextUnderlineWidth001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));

    auto oldThemeManager = PipelineBase::GetCurrentContext()->themeManager_;
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;

    RichEditorTheme richEditorTheme;
    EXPECT_EQ(
        richEditorPattern->GetPreviewTextUnderlineWidth(), richEditorTheme.GetPreviewUnderlineWidth().ConvertToPx()
    );

    PipelineBase::GetCurrentContext()->themeManager_ = oldThemeManager;
}

/**
 * @tc.name: FinishTextPreview003
 * @tc.desc: test FinishTextPreview
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, FinishTextPreview003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;

    richEditorPattern->InitPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    richEditorPattern->InitPreviewText(PREVIEW_TEXT_VALUE2, previewRange);
    richEditorPattern->FinishTextPreview();

    auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, testFrameNodeId, richEditorPattern);
    ASSERT_NE(childFrameNode, nullptr);
    auto childSpanNode = AceType::MakeRefPtr<SpanNode>(testSpanNodeId);
    ASSERT_NE(childSpanNode, nullptr);

    do {
        auto newHost1 = richEditorPattern->GetContentHost();
        auto newHost2 = richEditorPattern->GetContentHost();
        ASSERT_EQ(newHost1, newHost2);

        newHost1->children_.emplace_back(childFrameNode);
        newHost1->children_.emplace_back(childSpanNode);
        ASSERT_EQ(newHost1, newHost2);
    } while (0);

    richEditorPattern->InitPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    richEditorPattern->InitPreviewText(PREVIEW_TEXT_VALUE2, previewRange);
    richEditorPattern->FinishTextPreview();
    EXPECT_EQ(richEditorPattern->previewTextRecord_.previewContent, u"");
}

/**
 * @tc.name: GetPreviewTextRects001
 * @tc.desc: test GetPreviewTextRects
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, GetPreviewTextRects001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->InitPreviewText(PREVIEW_TEXT_VALUE1, previewRange);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> firstRects { RectF(testNumber0, testNumber0, testNumber5, testNumber5) };
    EXPECT_CALL(*paragraph, GetTightRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(firstRects));
    richEditorPattern->paragraphs_.AddParagraph(
        { .paragraph = paragraph, .start = testNumber0, .end = testNumber2 });
    richEditorPattern->paragraphs_.AddParagraph(
        { .paragraph = paragraph, .start = testNumber2, .end = testNumber4 });

    EXPECT_NE(richEditorPattern->GetPreviewTextRects().size(), 0);
}

/**
 * @tc.name: ReplaceText001
 * @tc.desc: test ReplaceText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, ReplacePreviewText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan("test");
    PreviewRange previewRange;
    std::u16string previewTextValue;
    previewRange.start = -1;
    previewRange.end = -2;
    richEditorPattern->ReplaceText(previewTextValue, previewRange);

    previewRange.start = -3;
    previewRange.end = -2;
    richEditorPattern->ReplaceText(previewTextValue, previewRange);

    previewRange.start = 1;
    previewRange.end = 0;
    richEditorPattern->ReplaceText(previewTextValue, previewRange);

    previewRange.start = 10;
    previewRange.end = 20;
    richEditorPattern->ReplaceText(previewTextValue, previewRange);

    previewRange.start = 15;
    previewRange.end = 10;
    richEditorPattern->ReplaceText(previewTextValue, previewRange);

    previewRange.start = 1;
    previewRange.end = 2;
    bool res = richEditorPattern->ReplaceText(previewTextValue, previewRange);
    ASSERT_NE(res, false);
}

/**
 * @tc.name: UpdatePreviewText002
 * @tc.desc: test UpdatePreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, UpdatePreviewText002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewTextRecord_.startOffset = -99;
    richEditorPattern->previewTextRecord_.endOffset = 99;

    PreviewRange previewRange;

    std::u16string previewTextValue;
    previewRange.start = -2;
    previewRange.end = -2;
    bool res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -2;
    previewRange.end = 9;
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewTextValue = u"abc";
    previewRange.start = -2;
    previewRange.end = -2;
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -2;
    previewRange.end = 9;
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->previewTextRecord_.previewContent = u"";
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -1;
    previewRange.end = -2;
    richEditorPattern->previewTextRecord_.previewContent = u"";
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -1;
    previewRange.end = -2;
    richEditorPattern->previewTextRecord_.previewContent = u"abc";
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->previewTextRecord_.previewContent = u"abc";
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    ASSERT_NE(res, false);
}

/**
 * @tc.name: UpdatePreviewText003
 * @tc.desc: test UpdatePreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, UpdatePreviewText003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewTextRecord_.startOffset = -99;
    richEditorPattern->previewTextRecord_.endOffset = 99;

    PreviewRange previewRange;

    std::u16string previewTextValue;

    previewRange.start = -2;
    previewRange.end = -1;
    richEditorPattern->previewTextRecord_.previewContent = u"";
    bool res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -2;
    previewRange.end = -2;
    richEditorPattern->previewTextRecord_.previewContent = u"";
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -2;
    previewRange.end = -2;
    richEditorPattern->previewTextRecord_.previewContent = u"abc";
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -2;
    previewRange.end = -1;
    richEditorPattern->previewTextRecord_.previewContent = u"abc";
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    ASSERT_NE(res, true);
}

/**
 * @tc.name: FinishTextPreview004
 * @tc.desc: test FinishTextPreview
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, FinishTextPreview004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewTextRecord_.previewContent = u"";
    richEditorPattern->FinishTextPreview();
    ASSERT_EQ(richEditorPattern->previewTextRecord_.previewContent.empty(), true);

    richEditorPattern->previewTextRecord_.previewContent = INIT_VALUE_1;
    richEditorPattern->FinishTextPreview();
    ASSERT_EQ(richEditorPattern->GetTextContentLength(), 6);
}

/**
 * @tc.name: RichEditorPatternTestGetPreviewTextStyle001
 * @tc.desc: test GetPreviewTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, RichEditorPatternTestGetPreviewTextStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);

    auto layoutProperty = host->layoutProperty_;
    host->layoutProperty_ = nullptr;
    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::NORMAL);
    host->layoutProperty_ = layoutProperty;

    ASSERT_NE(host->layoutProperty_, nullptr);
    auto property = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(property, nullptr);

    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::NORMAL);

    property->UpdatePreviewTextStyle("normal");
    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::NORMAL);

    property->UpdatePreviewTextStyle("underline");
    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::UNDERLINE);

    property->UpdatePreviewTextStyle("unknown");
    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::NORMAL);
}
} // namespace OHOS::Ace::NG