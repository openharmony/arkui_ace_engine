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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const int32_t STEP_TWO = 2;
} // namespace

class RichEditorStyledUndoTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorStyledUndoTestNg::SetUp()
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
    richEditorPattern->SetSupportStyledUndo(true);
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorStyledUndoTestNg::TearDown()
{
    richEditorNode_ = nullptr;
}

void RichEditorStyledUndoTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: RecordOperation001
 * @tc.desc: Test RecordOperation by insert or delete.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledUndoTestNg, RecordOperation001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& undoRecords = richEditorPattern->undoManager_->undoRecords_;
    // step1 insert value
    struct UpdateSpanStyle typingStyle;
    TextStyle textStyle(5);
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValue(INIT_VALUE_1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 1);
    auto undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 0);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 6);

    // step2 insert value with selection
    richEditorPattern->textSelector_.Update(0, 2);
    richEditorPattern->InsertValue(INIT_VALUE_2);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 2);
    undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 2);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 6);

    // step3 delete forward
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 3);
    undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 1);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 0);

    // step4 delete backward
    richEditorPattern->SetCaretPosition(8);
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 4);
    undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 7);
    EXPECT_EQ(undoRecord.rangeBefore.end, 8);
    EXPECT_EQ(undoRecord.rangeAfter.start, 7);
    EXPECT_EQ(undoRecord.rangeAfter.end, 7);

    // step5 delete with selection
    richEditorPattern->textSelector_.Update(2, 4);
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 5);
    undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 2);
    EXPECT_EQ(undoRecord.rangeBefore.end, 4);
    EXPECT_EQ(undoRecord.rangeAfter.start, 2);
    EXPECT_EQ(undoRecord.rangeAfter.end, 2);
}

/**
 * @tc.name: RecordOperation002
 * @tc.desc: Test RecordOperation by paste or drag.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledUndoTestNg, RecordOperation002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& undoRecords = richEditorPattern->undoManager_->undoRecords_;

    // step1 paste string
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValueByPaste(INIT_VALUE_1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 1);
    auto undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 0);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 6);

    // step2 paste string with selection
    richEditorPattern->textSelector_.Update(0, 2);
    richEditorPattern->InsertValueByPaste(INIT_VALUE_2);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 2);
    undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 2);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 6);

    // step3 internal drag
    richEditorPattern->ResetSelection();
    richEditorPattern->SetCaretPosition(8);
    richEditorPattern->dragRange_ = std::make_pair(0, 6);
    richEditorPattern->HandleOnDragDropTextOperation(INIT_VALUE_2, true, false);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 4);
    undoRecord = undoRecords.back();
    EXPECT_TRUE(undoRecord.restoreBuilderSpan);
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 6);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 0);
    undoRecord = undoRecords.at(undoRecords.size() - STEP_TWO);
    EXPECT_EQ(undoRecord.rangeBefore.start, 8);
    EXPECT_EQ(undoRecord.rangeBefore.end, 8);
    EXPECT_EQ(undoRecord.rangeAfter.start, 8);
    EXPECT_EQ(undoRecord.rangeAfter.end, 14);

    // step4 external drag
    richEditorPattern->SetCaretPosition(5);
    richEditorPattern->HandleOnDragDropTextOperation(INIT_VALUE_1, false, false);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 5);
    undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 5);
    EXPECT_EQ(undoRecord.rangeBefore.end, 5);
    EXPECT_EQ(undoRecord.rangeAfter.start, 5);
    EXPECT_EQ(undoRecord.rangeAfter.end, 11);
}

/**
 * @tc.name: RecordOperation003
 * @tc.desc: Test RecordOperation by add or delete span.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledUndoTestNg, RecordOperation003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& undoRecords = richEditorPattern->undoManager_->undoRecords_;

    // step1 AddTextSpan
    auto textSpanOptions = TEXT_SPAN_OPTIONS_1;
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 1);
    auto undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 0);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 6);

    // step2 AddImageSpan
    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 2);
    undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 6);
    EXPECT_EQ(undoRecord.rangeBefore.end, 6);
    EXPECT_EQ(undoRecord.rangeAfter.start, 6);
    EXPECT_EQ(undoRecord.rangeAfter.end, 7);

    // step3 AddSymbolSpan
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 3);
    undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 7);
    EXPECT_EQ(undoRecord.rangeBefore.end, 7);
    EXPECT_EQ(undoRecord.rangeAfter.start, 7);
    EXPECT_EQ(undoRecord.rangeAfter.end, 9);

    // step4 DeleteSpan
    RangeOptions options;
    options.start = 0;
    options.end = 9;
    richEditorPattern->DeleteSpans(options);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 4);
    undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 9);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 0);

    // step5 Invalid SpanType
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    auto spanItem = spanNode->GetSpanItem();
    richEditorPattern->undoManager_->RecordAddSpanOperation(spanItem, static_cast<SpanOptionsType>(4));
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 4);
    auto resultObject = ResultObject { .type = static_cast<SelectSpanType>(4) };
    auto spanOptions = richEditorPattern->undoManager_->builder_->CreateSpanOptionsBySpanObject(resultObject);
    EXPECT_TRUE(std::holds_alternative<TextSpanOptions>(spanOptions));
}

/**
 * @tc.name: RecordOperation004
 * @tc.desc: Test RecordOperation by update style.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledUndoTestNg, RecordOperation004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto& undoRecords = richEditorPattern->undoManager_->undoRecords_;
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValueByPaste(INIT_VALUE_1);
    richEditorPattern->ClearOperationRecords();

    // step1 UpdateSpanStyle
    TextStyle textStyle;
    textStyle.SetFontSize(FONT_SIZE_VALUE_2);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE_2;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;
    richEditorController->UpdateSpanStyle(0, 4, textStyle, imageStyle);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 1);
    auto undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 4);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 4);
    EXPECT_TRUE(undoRecord.isOnlyStyleChange);

    // step2 UpdateParagraphStyle
    struct UpdateParagraphStyle style1;
    style1.textAlign = TextAlign::END;
    richEditorPattern->UpdateParagraphStyle(0, 6, style1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 2);
    undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 6);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 6);
    EXPECT_TRUE(undoRecord.isOnlyStyleChange);

    richEditorPattern->UpdateParagraphStyle(0, 3, style1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 3);
    undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 6);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 6);
    EXPECT_TRUE(undoRecord.isOnlyStyleChange);
}

/**
 * @tc.name: RecordOperation005
 * @tc.desc: Test RecordOperation symbol with paragraph style.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledUndoTestNg, RecordOperation005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& undoRecords = richEditorPattern->undoManager_->undoRecords_;
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValueByPaste(INIT_VALUE_1);
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
    richEditorPattern->ClearOperationRecords();

    // step1 UpdateParagraphStyle
    struct UpdateParagraphStyle style1;
    style1.textAlign = TextAlign::END;
    style1.leadingMargin = std::make_optional<NG::LeadingMargin>();
    style1.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    style1.wordBreak = WordBreak::BREAK_ALL;
    style1.lineBreakStrategy = LineBreakStrategy::HIGH_QUALITY;
    style1.paragraphSpacing = Dimension(10.0f, DimensionUnit::PX);
    style1.textVerticalAlign = TextVerticalAlign::BASELINE;
    richEditorPattern->UpdateParagraphStyle(0, 8, style1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 1);
    auto undoRecord = undoRecords.back();
    EXPECT_TRUE(undoRecord.optionsListAfter.has_value());
    auto optionsList = undoRecord.optionsListAfter.value();
    EXPECT_EQ(optionsList.size(), 2);
    auto lastOption = &optionsList.back();
    auto options = std::get_if<SymbolSpanOptions>(lastOption);
    ASSERT_NE(options, nullptr);
    SymbolSpanOptions symbolOptions = *options;
    auto paraStyle = symbolOptions.paraStyle;
    EXPECT_TRUE(paraStyle.has_value());
    EXPECT_EQ(style1.ToString(), paraStyle->ToString());

    // step2 Delete Symbol
    richEditorPattern->SetCaretPosition(8);
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 2);
    undoRecord = undoRecords.back();
    EXPECT_TRUE(undoRecord.optionsListBefore.has_value());
    optionsList = undoRecord.optionsListBefore.value();
    EXPECT_EQ(optionsList.size(), 1);
    lastOption = &optionsList.back();
    options = std::get_if<SymbolSpanOptions>(lastOption);
    ASSERT_NE(options, nullptr);
    symbolOptions = *options;
    paraStyle = symbolOptions.paraStyle;
    EXPECT_TRUE(paraStyle.has_value());
    EXPECT_EQ(style1.ToString(), paraStyle->ToString());
}

/**
 * @tc.name: RecordOperation006
 * @tc.desc: Test RecordOperation PasteSpanStringData and NotifyExitTextPreview.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledUndoTestNg, RecordOperation006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    auto& undoRecords = richEditorPattern->undoManager_->undoRecords_;

    // step1 paste styled string
    auto styledString = AceType::MakeRefPtr<SpanString>(INIT_VALUE_1);
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->AddSpanByPasteData(styledString);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 1);
    auto undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 0);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 6);

    // step2 paste styled string with selection
    richEditorPattern->textSelector_.Update(2, 4);
    richEditorPattern->AddSpanByPasteData(styledString);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 3);
    undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 2);
    EXPECT_EQ(undoRecord.rangeBefore.end, 2);
    EXPECT_EQ(undoRecord.rangeAfter.start, 2);
    EXPECT_EQ(undoRecord.rangeAfter.end, 8);
    undoRecord = undoRecords.at(undoRecords.size() - STEP_TWO);
    EXPECT_EQ(undoRecord.rangeBefore.start, 2);
    EXPECT_EQ(undoRecord.rangeBefore.end, 4);
    EXPECT_EQ(undoRecord.rangeAfter.start, 2);
    EXPECT_EQ(undoRecord.rangeAfter.end, 2);

    // step3 NotifyExitTextPreview
    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    richEditorPattern->NotifyExitTextPreview(true);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 3);
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    richEditorPattern->NotifyExitTextPreview(false);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 4);
    undoRecord = undoRecords.back();
    EXPECT_EQ(undoRecord.rangeBefore.start, 0);
    EXPECT_EQ(undoRecord.rangeBefore.end, 0);
    EXPECT_EQ(undoRecord.rangeAfter.start, 0);
    EXPECT_EQ(undoRecord.rangeAfter.end, 5);
}

/**
 * @tc.name: RecordOperation007
 * @tc.desc: Test RecordOperation UpdateSpanStyle.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledUndoTestNg, RecordOperation007, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto& undoRecords = richEditorPattern->undoManager_->undoRecords_;
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
    richEditorPattern->ClearOperationRecords();

    // step1 UpdateSpanStyle
    TextStyle textStyle;
    textStyle.SetFontSize(FONT_SIZE_VALUE_2);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE_2;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;
    richEditorController->UpdateSpanStyle(0, 1, textStyle, imageStyle);

    // step2 DeleteBackward
    richEditorPattern->SetCaretPosition(1);
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 2);
    auto undoRecord = undoRecords.back();
    EXPECT_TRUE(undoRecord.optionsListBefore.has_value());
    auto optionsList = undoRecord.optionsListBefore.value();
    EXPECT_EQ(optionsList.size(), 1);
    auto lastOption = &optionsList.back();
    auto options = std::get_if<ImageSpanOptions>(lastOption);
    ASSERT_NE(options, nullptr);
    ImageSpanOptions imageOptions = *options;
    auto imageAttribute = imageOptions.imageAttribute;
    EXPECT_TRUE(imageAttribute.has_value());
    EXPECT_EQ(*imageAttribute, IMAGE_SPAN_ATTRIBUTE_1);
}

/**
 * @tc.name: RecordOperation008
 * @tc.desc: Test RecordOperation UpdateSpanStyle.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledUndoTestNg, RecordOperation008, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto& undoRecords = richEditorPattern->undoManager_->undoRecords_;
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
    richEditorPattern->ClearOperationRecords();

    // step1 UpdateImageStyle
    MarginProperty margins;
    margins.SetEdges(CalcLength{ 10.0, DimensionUnit::CALC });
    ImageSpanSize imageSize{ .width = 100.0_px, .height = 50.0_px };
    BorderRadiusProperty borderRadius = { 4.0_vp, 4.0_vp, 4.0_vp, 4.0_vp };
    ImageSpanAttribute imageStyle{ .size = imageSize,
        .marginProp = margins,
        .borderRadius = borderRadius,
        .objectFit = ImageFit::COVER,
        .verticalAlign = VerticalAlign::BOTTOM };
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateImageWidth = imageSize.width;
    updateSpanStyle.updateImageHeight = imageSize.height;
    updateSpanStyle.marginProp = margins;
    updateSpanStyle.updateImageFit = ImageFit::COVER;
    updateSpanStyle.updateImageVerticalAlign = VerticalAlign::BOTTOM;
    updateSpanStyle.borderRadius = borderRadius;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    TextStyle textStyle;
    richEditorController->UpdateSpanStyle(0, 1, textStyle, imageStyle);

    // step2 DeleteBackward
    richEditorPattern->SetCaretPosition(1);
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 2);
    auto undoRecord = undoRecords.back();
    EXPECT_TRUE(undoRecord.optionsListBefore.has_value());
    auto optionsList = undoRecord.optionsListBefore.value();
    EXPECT_EQ(optionsList.size(), 1);
    auto lastOption = &optionsList.back();
    auto options = std::get_if<ImageSpanOptions>(lastOption);
    ASSERT_NE(options, nullptr);
    ImageSpanOptions imageOptions = *options;
    auto imageAttribute = imageOptions.imageAttribute;
    EXPECT_TRUE(imageAttribute.has_value());
    EXPECT_EQ(*imageAttribute, imageStyle);
}
}