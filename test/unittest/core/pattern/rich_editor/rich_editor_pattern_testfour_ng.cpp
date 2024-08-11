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
#define private public
#define protected public

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
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
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
 * @tc.name: ReplacePreviewText001
 * @tc.desc: test ReplacePreviewText
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
    richEditorPattern->ReplacePreviewText(previewTextValue, previewRange);

    previewRange.start = -3;
    previewRange.end = -2;
    richEditorPattern->ReplacePreviewText(previewTextValue, previewRange);

    previewRange.start = 1;
    previewRange.end = 0;
    richEditorPattern->ReplacePreviewText(previewTextValue, previewRange);

    previewRange.start = 10;
    previewRange.end = 20;
    richEditorPattern->ReplacePreviewText(previewTextValue, previewRange);

    previewRange.start = 15;
    previewRange.end = 10;
    richEditorPattern->ReplacePreviewText(previewTextValue, previewRange);

    previewRange.start = 1;
    previewRange.end = 2;
    bool res = richEditorPattern->ReplacePreviewText(previewTextValue, previewRange);
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
 * @tc.name: InsertValueAfterBeforeSpan001
 * @tc.desc: test InsertValueAfterBeforeSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, InsertValueAfterBeforeSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RefPtr<SpanNode> spanNodeBefore = OHOS::Ace::NG::SpanNode::CreateSpanNode(1);
    RefPtr<SpanNode> spanNode = OHOS::Ace::NG::SpanNode::CreateSpanNode(2);
    TextInsertValueInfo info;
    std::string insertValue = "abc";
    UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.isSymbolStyle = true;

    TextStyle textStyle;
    spanNodeBefore->GetSpanItem()->textStyle_ = textStyle;

    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->InsertValueAfterBeforeSpan(spanNodeBefore, spanNode, info, insertValue, true);

    ASSERT_EQ(richEditorPattern->HasSameTypingStyle(spanNodeBefore), false);
    ASSERT_EQ(richEditorPattern->typingStyle_.has_value(), true);
}

/**
 * @tc.name: InsertValueWithoutSpan001
 * @tc.desc: test InsertValueWithoutSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, InsertValueWithoutSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::string insertValue = "abc";

    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, 0);
    TextInsertValueInfo info;
    info.spanIndex_ = 0;

    richEditorPattern->InsertValueWithoutSpan(spanNode, info, insertValue, true);
    info.spanIndex_ = 1;
    richEditorPattern->InsertValueWithoutSpan(spanNode, info, insertValue, true);

    info.spanIndex_ = 0;
    spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_COMPONENT_TAG, 0);
    richEditorPattern->InsertValueWithoutSpan(spanNode, info, insertValue, true);

    info.spanIndex_ = 1;
    spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, 0);
    richEditorPattern->InsertValueWithoutSpan(spanNode, info, insertValue, true);

    ASSERT_EQ(spanNode->GetTag(), V2::SPAN_ETS_TAG);
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
    richEditorPattern->previewTextRecord_.isPreviewTextInputting = true;
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
    richEditorPattern->previewTextRecord_.isPreviewTextInputting = true;
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
    richEditorPattern->previewTextRecord_.hasDiff = true;
    richEditorPattern->ProcessInsertValue(insertValue, false, false);

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
} // namespace OHOS::Ace::NG