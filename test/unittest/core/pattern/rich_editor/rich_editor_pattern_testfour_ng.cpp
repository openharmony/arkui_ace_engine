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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorPatternTestFourNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorPatternTestFourNg::SetUp()
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

void RichEditorPatternTestFourNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorPatternTestFourNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: HandleDoubleClickOrLongPress001
 * @tc.desc: test HandleDoubleClickOrLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, HandleDoubleClickOrLongPress001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    GestureEvent info;
    RefPtr<FrameNode> imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 0, AceType::MakeRefPtr<ImagePattern>());
    richEditorPattern->caretUpdateType_ = CaretUpdateType::LONG_PRESSED;
    richEditorPattern->isEditing_ = true;
    richEditorPattern->selectOverlay_->hasTransform_ = true;

    richEditorPattern->HandleDoubleClickOrLongPress(info, imageNode);
    /**
     * @tc.steps: step2. add span and select text
     */
    AddSpan("test");
    RectF rect(0, 0, 5, 5);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 4);
    richEditorPattern->textSelector_.Update(3, 4);
    richEditorPattern->selectOverlay_->OnHandleMoveDone(rect, true);
    richEditorPattern->HandleDoubleClickOrLongPress(info, imageNode);

    EXPECT_TRUE(richEditorPattern->textSelector_.IsValid());
}

/**
 * @tc.name: HandleDoubleClickOrLongPress001
 * @tc.desc: test HandleDoubleClickOrLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, HandleDoubleClickOrLongPress002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    GestureEvent info;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::LONG_PRESSED;
    richEditorPattern->isEditing_ = true;
    richEditorPattern->selectOverlay_->hasTransform_ = true;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    PositionWithAffinity defaultPositionWithAffinity(2, TextAffinity::UPSTREAM);
    EXPECT_CALL(*mockParagraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(defaultPositionWithAffinity));
    paragraphInfo.paragraph = mockParagraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfo);
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);
}

/**
 * @tc.name: HandleMenuCallbackOnSelectAll001
 * @tc.desc: test HandleMenuCallbackOnSelectAll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, HandleMenuCallbackOnSelectAll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richeditor pattern and add add text span
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. create a scene where the text menu has popped up
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->textSelector_.Update(1, 2);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.step: step4. test OnMenuItemAction
     */
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::COPY, OptionMenuType::TOUCH_MENU);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 1);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 2);

    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::PASTE, OptionMenuType::NO_MENU);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);

    auto selectOverlayInfo = richEditorPattern->selectOverlay_->GetSelectOverlayInfo();
    richEditorPattern->selectOverlay_->isUsingMouse_ = true;
    EXPECT_EQ(richEditorPattern->selectOverlay_->IsUsingMouse(), true);
    richEditorPattern->HandleMenuCallbackOnSelectAll();
}

/**
 * @tc.name: ToStyledString002
 * @tc.desc: test ToStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, ToStyledString002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    int32_t start = 3;
    int32_t end = -2;
    AddSpan("test");
    RefPtr<SpanString> res = richEditorPattern->ToStyledString(start, end);
    ASSERT_NE(res, nullptr);
}

/**
 * @tc.name: GetTextStyleBySpanItem001
 * @tc.desc: test GetTextStyleBySpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, GetTextStyleBySpanItem001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->fontStyle = nullptr;
    spanItem->textLineStyle = nullptr;
    richEditorPattern->GetTextStyleBySpanItem(spanItem);
    ASSERT_EQ(spanItem->fontStyle, nullptr);
}

/**
 * @tc.name: GetImageStyleBySpanItem001
 * @tc.desc: test GetImageStyleBySpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, GetImageStyleBySpanItem001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    ImageSpanAttribute imageStyle;
    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    ImageSpanSize imageSize;
    CalcDimension imageSpanWidth;
    CalcDimension imageSpanHeight;
    imageSize.width = imageSpanWidth;
    imageSize.height = imageSpanHeight;
    imageStyle.size = imageSize;
    imageStyle.verticalAlign = VerticalAlign::TOP;
    imageStyle.objectFit = ImageFit::COVER;
    ImageSpanOptions option;
    option.imageAttribute = imageStyle;
    spanItem1->options = option;
    richEditorPattern->GetImageStyleBySpanItem(spanItem1);

    auto spanItem2 = AceType::MakeRefPtr<ImageSpanItem>();
    ImageSpanAttribute imageStyle2;
    ImageSpanOptions option2;
    option2.imageAttribute = imageStyle2;
    spanItem2->options = option2;
    richEditorPattern->GetImageStyleBySpanItem(spanItem2);

    ASSERT_EQ(spanItem1->options.imageAttribute.has_value(), true);
}

/**
 * @tc.name: RequestKeyboard001
 * @tc.desc: test RequestKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, RequestKeyboard001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    bool res = richEditorPattern->RequestKeyboard(true, true, true);

    res = richEditorPattern->RequestKeyboard(true, true, false);

    richEditorPattern->customKeyboardBuilder_ = []() {};
    res = richEditorPattern->RequestKeyboard(true, true, true);

    richEditorPattern->customKeyboardBuilder_ = []() {};
    res = richEditorPattern->RequestKeyboard(true, true, false);
    ASSERT_NE(res, true);
}

/**
 * @tc.name: ReplaceText001
 * @tc.desc: test ReplaceText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, ReplacePreviewText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan("test");
    PreviewRange previewRange;
    std::string previewTextValue;
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
HWTEST_F(RichEditorPatternTestFourNg, UpdatePreviewText002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewTextRecord_.startOffset = -99;
    richEditorPattern->previewTextRecord_.endOffset = 99;

    PreviewRange previewRange;

    std::string previewTextValue;
    previewRange.start = -2;
    previewRange.end = -2;
    bool res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -2;
    previewRange.end = 9;
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewTextValue = "abc";
    previewRange.start = -2;
    previewRange.end = -2;
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -2;
    previewRange.end = 9;
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->previewTextRecord_.previewContent = "";
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -1;
    previewRange.end = -2;
    richEditorPattern->previewTextRecord_.previewContent = "";
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -1;
    previewRange.end = -2;
    richEditorPattern->previewTextRecord_.previewContent = "abc";
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->previewTextRecord_.previewContent = "abc";
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    ASSERT_NE(res, false);
}

/**
 * @tc.name: UpdatePreviewText003
 * @tc.desc: test UpdatePreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, UpdatePreviewText003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewTextRecord_.startOffset = -99;
    richEditorPattern->previewTextRecord_.endOffset = 99;

    PreviewRange previewRange;

    std::string previewTextValue;

    previewRange.start = -2;
    previewRange.end = -1;
    richEditorPattern->previewTextRecord_.previewContent = "";
    bool res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -2;
    previewRange.end = -2;
    richEditorPattern->previewTextRecord_.previewContent = "";
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -2;
    previewRange.end = -2;
    richEditorPattern->previewTextRecord_.previewContent = "abc";
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    previewRange.start = -2;
    previewRange.end = -1;
    richEditorPattern->previewTextRecord_.previewContent = "abc";
    res = richEditorPattern->UpdatePreviewText(previewTextValue, previewRange);

    ASSERT_NE(res, true);
}

/**
 * @tc.name: FinishTextPreview004
 * @tc.desc: test FinishTextPreview
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, FinishTextPreview004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewTextRecord_.previewContent = "";
    richEditorPattern->FinishTextPreview();
    ASSERT_EQ(richEditorPattern->previewTextRecord_.previewContent.empty(), true);
}

/**
 * @tc.name: InsertValueToSpanNode001
 * @tc.desc: test InsertValueToSpanNode
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, InsertValueToSpanNode001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::string insertValue = "abc";

    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, 0);
    TextInsertValueInfo info;
    info.spanIndex_ = 0;
    info.SetOffsetInSpan(100);

    richEditorPattern->InsertValueToSpanNode(spanNode, insertValue, info);

    auto spanItem = spanNode->GetSpanItem();
    auto text = spanItem->content;
    std::wstring textTemp = StringUtils::ToWstring(text);
    auto textTempSize = static_cast<int32_t>(textTemp.size());

    ASSERT_EQ(textTempSize, 0);
}

/**
 * @tc.name: ResetFirstNodeStyle001
 * @tc.desc: test ResetFirstNodeStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, ResetFirstNodeStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. initalize symbol span properties
     */
    TextStyle style;
    style.SetFontSize(FONT_SIZE_VALUE);
    SymbolSpanOptions options;
    options.symbolId = SYMBOL_ID;
    options.style = style;

    /**
     * @tc.steps: step3. add symbol span
     */
    auto index1 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index2, 1);
    auto index3 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index3, 2);
    auto index4 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index4, 3);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 4);

    richEditorPattern->ResetFirstNodeStyle();

    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);
}

/**
 * @tc.name: DeleteBackward001
 * @tc.desc: test DeleteBackward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, DeleteBackward001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewTextRecord_.previewContent = "123";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;
    richEditorPattern->DeleteBackward(0);

    ASSERT_EQ(richEditorPattern->IsPreviewTextInputting(), true);
}

/**
 * @tc.name: DeleteForward001
 * @tc.desc: test DeleteForward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, DeleteForward001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewTextRecord_.previewContent = "123";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;
    richEditorPattern->DeleteForward(0);
    ASSERT_EQ(richEditorPattern->IsPreviewTextInputting(), true);
}

/**
 * @tc.name: ProcessInsertValue001
 * @tc.desc: test ProcessInsertValue
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, ProcessInsertValue001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::string insertValue = "abc";
    richEditorPattern->isDragSponsor_ = true;
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->previewTextRecord_.needReplacePreviewText = true;
    richEditorPattern->ProcessInsertValue(insertValue, OperationType::DEFAULT, false);

    ASSERT_EQ(richEditorPattern->previewTextRecord_.IsValid(), false);
}

/**
 * @tc.name: DeleteBackwardOperation001
 * @tc.desc: test DeleteBackwardOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, DeleteBackwardOperation001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->caretPosition_ = 100;
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->DeleteBackwardOperation(0);

    ASSERT_EQ(richEditorPattern->spans_.empty(), true);
}

/**
 * @tc.name: ProcessStyledString001
 * @tc.desc: test ProcessStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, ProcessStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());

    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = true;
    richEditorPattern->ProcessStyledString();

    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    richEditorPattern->ProcessStyledString();

    ASSERT_EQ(richEditorPattern->spans_.empty(), true);
}

/**
 * @tc.name: ProcessStyledString002
 * @tc.desc: test ProcessStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, ProcessStyledString002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->textDetectEnable_ = true;
    bool ret = false;
    ret = richEditorPattern->CanStartAITask();
    EXPECT_TRUE(ret);

    richEditorPattern->textForDisplay_ = INIT_VALUE_1;
    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = true;
    richEditorPattern->ProcessStyledString();

    EXPECT_FALSE(richEditorPattern->spans_.empty());
}

/**
 * @tc.name: ProcessStyledString003
 * @tc.desc: test ProcessStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, ProcessStyledString003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->textDetectEnable_ = true;
    bool ret = false;
    ret = richEditorPattern->CanStartAITask();
    EXPECT_TRUE(ret);

    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    richEditorPattern->ProcessStyledString();

    EXPECT_FALSE(richEditorPattern->spans_.empty());
}

/**
 * @tc.name: SetSelection007
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, SetSelection007, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    ASSERT_NE(richEditorPattern->contentMod_, nullptr);
    ASSERT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->previewTextRecord_.previewContent = "test";
    richEditorPattern->previewTextRecord_.startOffset = 1;
    richEditorPattern->previewTextRecord_.endOffset = 10;

    int32_t start = -1;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_TRUE(richEditorPattern->HasFocus());
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_TRUE(richEditorPattern->HasFocus());
}

/**
 * @tc.name: SetSelection008
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, SetSelection008, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    ASSERT_NE(richEditorPattern->contentMod_, nullptr);
    ASSERT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    std::string content = "TEST123";
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(content);
    richEditorPattern->previewTextRecord_.previewContent = "test";
    richEditorPattern->previewTextRecord_.startOffset = -1;
    richEditorPattern->previewTextRecord_.endOffset = 10;

    int32_t start = -1;
    int32_t end = -1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_TRUE(richEditorPattern->HasFocus());
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_TRUE(richEditorPattern->HasFocus());
}

/**
 * @tc.name: GetTextBoxes002
 * @tc.desc: test GetTextBoxes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, GetTextBoxes002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = "testShowHandles";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 3;

    std::vector<RectF> res;
    auto ret = richEditorPattern->GetTextBoxes();
    EXPECT_EQ(ret, res);

    TextLineMetrics lineMetrics;
    richEditorPattern->GetLineCount();
    EXPECT_EQ(richEditorPattern->GetLineHeight(), 0.0f);
    EXPECT_EQ(richEditorPattern->GetLetterSpacing(), 0.0f);
    auto retLineMetrics = richEditorPattern->GetLineMetrics(-1);
    EXPECT_EQ(retLineMetrics.x, 0);

    auto retLineMetricsS = richEditorPattern->GetLineMetrics(2);
    EXPECT_EQ(retLineMetricsS.x, 0);

    int32_t scroll_from_update = 1;
    richEditorPattern->richTextRect_ = RectF(0, 4, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 1, 100, 160);
    richEditorPattern->overlayMod_ = nullptr;
    richEditorPattern->UpdateScrollStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(10, scroll_from_update)) << "Reach Top Boundary";
}

/**
 * @tc.name: GetCrossOverHeight004
 * @tc.desc: test GetCrossOverHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, GetCrossOverHeight004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->CreateHandles();
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = false;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = false;
    richEditorPattern->keyboardAvoidance_ = false;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = false;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: GetCrossOverHeight005
 * @tc.desc: test GetCrossOverHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, GetCrossOverHeight005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->CreateHandles();
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = false;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = false;
    richEditorPattern->keyboardAvoidance_ = false;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = false;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RemoveEmptySpanNodes001
 * @tc.desc: test RemoveEmptySpanNodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, RemoveEmptySpanNodes001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto host = richEditorPattern->GetHost();
    EXPECT_NE(host, nullptr);

    richEditorPattern->spans_.clear();
    host->children_.clear();
    auto textframeNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textframeNode, nullptr);
    host->AddChild(textframeNode);
    textframeNode->SetParent(host);

    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imageSpanNode, nullptr);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);

    richEditorPattern->RemoveEmptySpanNodes();

    ASSERT_EQ(host->GetChildren().empty(), false);
}

/**
 * @tc.name: AddImageSpan001
 * @tc.desc: test AddImageSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, AddImageSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ImageSpanOptions options;
    int32_t res = richEditorPattern->AddImageSpan(options, true, 0, false);
    ASSERT_EQ(res, 0);
}

/**
 * @tc.name: DeleteSpansByRange001
 * @tc.desc: test DeleteSpansByRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, DeleteSpansByRange001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    SpanPositionInfo startInfo;
    SpanPositionInfo endInfo;
    startInfo.spanIndex_ = -1;

    auto host = richEditorPattern->GetHost();
    EXPECT_NE(host, nullptr);

    richEditorPattern->spans_.clear();
    host->children_.clear();
    auto textframeNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textframeNode, nullptr);
    host->AddChild(textframeNode);
    textframeNode->SetParent(host);

    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imageSpanNode, nullptr);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);

    richEditorPattern->DeleteSpansByRange(0, 0, startInfo, endInfo);

    ASSERT_EQ(startInfo.spanIndex_ >= static_cast<int32_t>(host->GetChildren().size()), false);
}

/**
 * @tc.name: CalcCursorOffsetByPosition001
 * @tc.desc: test CalcCursorOffsetByPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, CalcCursorOffsetByPosition001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    float selectLineHeight = 0;
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);

    AddSpan("test");
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);

    auto host = richEditorPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imageSpanNode, nullptr);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);

    richEditorPattern->spans_.clear();
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);

    ASSERT_EQ(richEditorPattern->GetTextContentLength() == 0, true);
}

/**
 * @tc.name: GetAdjustedSelectionInfo001
 * @tc.desc: test GetAdjustedSelectionInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, GetAdjustedSelectionInfo001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::vector<std::tuple<SelectSpanType, std::string, RefPtr<PixelMap>>> testTuples;
    testTuples.emplace_back(SelectSpanType::TYPEIMAGE, " ", PixelMap::CreatePixelMap(nullptr));
    testTuples.emplace_back(SelectSpanType::TYPEIMAGE, "", PixelMap::CreatePixelMap(nullptr));
    testTuples.emplace_back(SelectSpanType::TYPEIMAGE, " ", nullptr);
    testTuples.emplace_back(SelectSpanType::TYPEIMAGE, "", nullptr);
    testTuples.emplace_back(SelectSpanType::TYPESYMBOLSPAN, " ", PixelMap::CreatePixelMap(nullptr));
    testTuples.emplace_back(SelectSpanType::TYPESYMBOLSPAN, "", PixelMap::CreatePixelMap(nullptr));
    testTuples.emplace_back(SelectSpanType::TYPESYMBOLSPAN, " ", nullptr);
    testTuples.emplace_back(SelectSpanType::TYPESYMBOLSPAN, "", nullptr);
    std::list<ResultObject> resultObjectList;
    ResultObject obj;
    for (const auto& testcase : testTuples) {
        obj.type = std::get<0>(testcase);
        obj.valueString = std::get<1>(testcase);
        obj.valuePixelMap = std::get<2>(testcase);
        resultObjectList.emplace_back(obj);
    }

    SelectionInfo textSelectInfo;
    textSelectInfo.SetResultObjectList(resultObjectList);
    richEditorPattern->GetAdjustedSelectionInfo(textSelectInfo);

    ASSERT_EQ(resultObjectList.empty(), false);
}

/**
 * @tc.name: CopyTextSpanLineStyle001
 * @tc.desc: test CopyTextSpanLineStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, CopyTextSpanLineStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    LeadingMargin margin;
    RefPtr<SpanNode> source = OHOS::Ace::NG::SpanNode::CreateSpanNode(1);
    RefPtr<SpanNode> target = OHOS::Ace::NG::SpanNode::CreateSpanNode(2);
    source->UpdateLeadingMargin(margin);

    richEditorPattern->CopyTextSpanLineStyle(source, target, false);
    richEditorPattern->CopyTextSpanLineStyle(source, target, true);
    ASSERT_EQ(richEditorPattern->spans_.empty(), true);
}

/**
 * @tc.name: JudgeContentDraggable001
 * @tc.desc: test JudgeContentDraggable
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, JudgeContentDraggable001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->copyOption_ = CopyOptions::None;
    EXPECT_EQ(richEditorPattern->IsSelected(), false);
    richEditorPattern->JudgeContentDraggable();

    richEditorPattern->copyOption_ = CopyOptions::InApp;
    EXPECT_EQ(richEditorPattern->IsSelected(), false);
    richEditorPattern->JudgeContentDraggable();

    AddSpan("test");
    richEditorPattern->textSelector_.Update(3, 4);
    EXPECT_EQ(richEditorPattern->IsSelected(), true);

    richEditorPattern->copyOption_ = CopyOptions::None;
    richEditorPattern->JudgeContentDraggable();

    richEditorPattern->textSelector_.Update(3, 4);
    EXPECT_EQ(richEditorPattern->IsSelected(), true);

    richEditorPattern->copyOption_ = CopyOptions::InApp;
    bool res = richEditorPattern->JudgeContentDraggable();

    EXPECT_EQ(res, true);
}

/**
 * @tc.name: HandleDraggableFlag001
 * @tc.desc: test HandleDraggableFlag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, HandleDraggableFlag001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->HandleDraggableFlag(true);
    EXPECT_EQ(richEditorPattern->JudgeContentDraggable(), false);
}

/**
 * @tc.name: GetDeletedSpan001
 * @tc.desc: test GetDeletedSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, GetDeletedSpan001, TestSize.Level1)
{
    /**
     * @tc.step: step1. get richeditor pattern and add text span.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    int32_t innerPosition = 0;
    RichEditorChangeValue changeValue;

    richEditorPattern->usingMouseRightButton_ = false;
    richEditorPattern->isLongPress_ = false;
    richEditorPattern->isDragging_ = false;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = false;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->GetDeletedSpan(changeValue, innerPosition, -99, RichEditorDeleteDirection::BACKWARD);

    richEditorPattern->previewTextRecord_.previewContent = "abc";
    richEditorPattern->GetDeletedSpan(changeValue, innerPosition, -99, RichEditorDeleteDirection::BACKWARD);

    EXPECT_EQ(richEditorPattern->textSelector_.SelectNothing(), true);
}

/**
 * @tc.name: HandleTouchUp001
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, HandleTouchUp001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);
    richEditorPattern->editingLongPress_ = true;
    richEditorPattern->isEditing_ = false;
    richEditorPattern->HandleTouchUp();
    EXPECT_EQ(richEditorPattern->isMoveCaretAnywhere_, false);
    richEditorPattern->editingLongPress_ = true;
    richEditorPattern->isEditing_ = true;
    richEditorPattern->HandleTouchUp();
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
}

/**
 * @tc.name: CheckEditorTypeChange001
 * @tc.desc: test CheckEditorTypeChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, CheckEditorTypeChange001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->CheckEditorTypeChange();

    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = 143;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr, false);
    richEditorPattern->selectOverlayProxy_ = proxy;
    richEditorPattern->UpdateSelectOverlayOrCreate(selectOverlayInfo, true);
    richEditorPattern->CheckEditorTypeChange();

    richEditorPattern->selectOverlayProxy_->GetSelectOverlayMangerInfo().menuInfo.editorType =
        static_cast<int32_t>(TextSpanType::TEXT);
    richEditorPattern->CheckEditorTypeChange();

    richEditorPattern->selectOverlayProxy_->GetSelectOverlayMangerInfo().menuInfo.editorType =
        static_cast<int32_t>(TextSpanType::NONE);
    richEditorPattern->selectedType_ = TextSpanType::TEXT;
    richEditorPattern->CheckEditorTypeChange();

    richEditorPattern->selectOverlayProxy_->GetSelectOverlayMangerInfo().menuInfo.editorType =
        static_cast<int32_t>(TextSpanType::TEXT);
    richEditorPattern->selectedType_ = TextSpanType::TEXT;
    richEditorPattern->CheckEditorTypeChange();

    richEditorPattern->selectOverlayProxy_->selectOverlayId_ = 1;
    richEditorPattern->CheckEditorTypeChange();

    EXPECT_TRUE(richEditorPattern->selectOverlayProxy_);
}

/**
 * @tc.name: GetSelectSpansPositionInfo001
 * @tc.desc: test GetSelectSpansPositionInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, GetSelectSpansPositionInfo001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 2;
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    ClearSpan();
    AddSpan(INIT_VALUE_2);
    auto spanItem = richEditorPattern->spans_.back();
    spanItem->unicode = 1;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 2;
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    ClearSpan();
    AddImageSpan();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->textSelector_.baseOffset = 7;
    richEditorPattern->textSelector_.destinationOffset = 8;
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    EXPECT_FALSE(richEditorPattern->hasClicked_);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->textSelector_.baseOffset = 5;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    EXPECT_FALSE(richEditorPattern->hasClicked_);
}

/**
 * @tc.name: DoDeleteActions001
 * @tc.desc: test DoDeleteActions
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, DoDeleteActions001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto aboutToDeleteFunc = [](const RichEditorDeleteValue&) { return false; };
    eventHub->SetAboutToDelete(std::move(aboutToDeleteFunc));
    RichEditorDeleteValue info;
    richEditorPattern->DoDeleteActions(0, 0, info);

    richEditorPattern->previewTextRecord_.previewContent = "123";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;
    richEditorPattern->DeleteForward(0);
    richEditorPattern->DoDeleteActions(0, 0, info);
    ASSERT_EQ(richEditorPattern->IsPreviewTextInputting(), true);
}

/**
 * @tc.name: HandleSingleClickEvent001
 * @tc.desc: test RichEditorPattern HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, HandleSingleClickEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorPattern::OperationRecord record;
    AddSpan("hello1");

    RectF rect(0, 0, 5, 5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->DeleteSelectOperation(&record);

    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: SetPreviewText001
 * @tc.desc: test RichEditorPattern SetPreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, SetPreviewText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::string previewTextValue;
    PreviewRange range;

    range.start = -1;
    range.end = 0;

    richEditorPattern->previewTextRecord_.previewContent = "";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;

    richEditorPattern->SetPreviewText(previewTextValue, range);

    ASSERT_EQ(richEditorPattern->InitPreviewText(previewTextValue, range), false);
}

/**
 * @tc.name: DeleteValueInStyledString002
 * @tc.desc: test RichEditorPattern DeleteValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, DeleteValueInStyledString002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>("abc");
    richEditorPattern->caretVisible_ = false;
    richEditorPattern->previewLongPress_ = true;

    ASSERT_EQ(!richEditorPattern->BeforeStyledStringChange(0, 10, ""), false);

    richEditorPattern->DeleteValueInStyledString(0, 0, true, false);

    richEditorPattern->DeleteValueInStyledString(0, 0, false, false);

    ASSERT_EQ(!richEditorPattern->textSelector_.SelectNothing(), false);
}

/**
 * @tc.name: InsertValueOperation001
 * @tc.desc: test InsertValueOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, InsertValueOperation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);

    struct UpdateSpanStyle typingStyle;
    TextStyle textStyle(5);
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);
    std::string insertValue = "test123";
    RichEditorPattern::OperationRecord record;

    richEditorPattern->InsertValueOperation(insertValue, &record, OperationType::DEFAULT);

    EXPECT_TRUE(richEditorPattern->typingStyle_.has_value());
}

/**
 * @tc.name: GetLeftWordPosition001
 * @tc.desc: test GetLeftWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, GetLeftWordPosition001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan("hello1");
    int32_t res = richEditorPattern->GetLeftWordPosition(-9999);

    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: ProcessDeleteNodes001
 * @tc.desc: test ProcessDeleteNodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, ProcessDeleteNodes001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorAbstractSpanResult a;
    a.SetSpanType(SpanResultType::SYMBOL);
    std::list<RichEditorAbstractSpanResult> list;
    list.emplace_back(a);
    int32_t res = richEditorPattern->ProcessDeleteNodes(list);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, HandleSurfaceChanged001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->magnifierController_->isShowMagnifier_ = true;
    richEditorPattern->HandleSurfaceChanged(0, 0, 0, 0);

    EXPECT_EQ(richEditorPattern->magnifierController_->GetShowMagnifier(), false);
}

/**
 * @tc.name: InitSelection_ABOVE_LINE
 * @tc.desc: test InitSelection with SELECT_ABOVE_LINE
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, InitSelection_ABOVE_LINE, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    AddSpan("ab\n\nab");

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);

    PositionWithAffinity positionWithAffinity(3, TextAffinity::DOWNSTREAM);
    EXPECT_CALL(*paragraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(positionWithAffinity));

    Offset touchOffset = Offset(0.0f, 0.0f);
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->InitSelection(touchOffset);

    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 0);
}
} // namespace OHOS::Ace::NG