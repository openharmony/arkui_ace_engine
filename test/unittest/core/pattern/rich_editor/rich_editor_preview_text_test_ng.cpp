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

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
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
    auto previewTextSpan = previewTextRecord.previewTextSpan;
    EXPECT_NE(previewTextSpan, nullptr);
    EXPECT_EQ(previewTextSpan->content, PREVIEW_TEXT_VALUE1);
    EXPECT_EQ(previewTextRecord.startOffset, 0);
    auto length = static_cast<int32_t>(StringUtils::ToWstring(PREVIEW_TEXT_VALUE1).length());
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
    auto previewTextRecord = richEditorPattern->previewTextRecord_;
    auto previewTextSpan = previewTextRecord.previewTextSpan;
    EXPECT_NE(previewTextSpan, nullptr);
    EXPECT_EQ(previewTextSpan->content, PREVIEW_TEXT_VALUE2);
    EXPECT_EQ(previewTextRecord.startOffset, 0);
    auto length = static_cast<int32_t>(StringUtils::ToWstring(PREVIEW_TEXT_VALUE2).length());
    EXPECT_EQ(previewTextRecord.endOffset, previewTextRecord.startOffset + length);
    /**
     * @tc.steps: step4. delete content  previewText
     */
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE3, previewRange);
    EXPECT_NE(previewTextSpan, nullptr);
    EXPECT_EQ(previewTextSpan->content, PREVIEW_TEXT_VALUE3);
    EXPECT_EQ(previewTextRecord.startOffset, 0);
    length = static_cast<int32_t>(StringUtils::ToWstring(PREVIEW_TEXT_VALUE3).length());
    EXPECT_EQ(richEditorPattern->previewTextRecord_.endOffset, previewTextRecord.startOffset + length);
}

/**
 * @tc.name: SetPreviewText003
 * @tc.desc: test setPreviewText init, update, and delete available
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPreviewTextTestNg, SetPreviewText003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. set typingStyle
     */
    TextStyle textStyle;
    textStyle.SetTextColor(TEXT_COLOR_VALUE);
    textStyle.SetTextShadows(SHADOWS);
    textStyle.SetFontSize(FONT_SIZE_VALUE);
    textStyle.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    textStyle.SetFontWeight(FONT_WEIGHT_VALUE);
    textStyle.SetFontFamilies(FONT_FAMILY_VALUE);
    textStyle.SetTextDecoration(TEXT_DECORATION_VALUE);
    textStyle.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    UpdateSpanStyle typingStyle;
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);
    /**
     * @tc.steps: step2. set previewText
     */
    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    /**
     * @tc.steps: step3. test previewText span textStyle
     */
    auto previewTextRecord = richEditorPattern->previewTextRecord_;
    auto previewTextSpan = previewTextRecord.previewTextSpan;
    ASSERT_NE(previewTextSpan, nullptr);
    auto style = previewTextSpan->GetTextStyle();
    EXPECT_EQ(style->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(style->GetTextShadows(), SHADOWS);
    EXPECT_EQ(style->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(style->GetFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(style->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(style->GetFontFamilies(), FONT_FAMILY_VALUE);
    EXPECT_EQ(style->GetTextDecoration(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(style->GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
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
    auto previewTextSpan = previewTextRecord.previewTextSpan;
    EXPECT_EQ(previewTextSpan, nullptr);
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

} // namespace OHOS::Ace::NG