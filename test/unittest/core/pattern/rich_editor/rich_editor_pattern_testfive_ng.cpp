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

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

} // namespace

class RichEditorPatternTestFiveNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorPatternTestFiveNg::SetUp()
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

void RichEditorPatternTestFiveNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorPatternTestFiveNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: RichEditorAddSpanAutoScroll001
 * @tc.desc: Test auto scroll when adding a span after the richEditor is ready.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, RichEditorAddSpanAutoScroll001, TestSize.Level1)
{
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isRichEditorInit_ = true;

    // 0: AddTextSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
    EXPECT_TRUE(richEditorPattern->needMoveCaretToContentRect_);

    // 1: AddImageSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 7);
    EXPECT_TRUE(richEditorPattern->needMoveCaretToContentRect_);

    // 2: AddSymbolSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 9);
    EXPECT_TRUE(richEditorPattern->needMoveCaretToContentRect_);

    // 3: AddPlaceholderSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddPlaceholderSpan(BUILDER_NODE_1, {});
    EXPECT_EQ(richEditorPattern->caretPosition_, 10);
    EXPECT_TRUE(richEditorPattern->needMoveCaretToContentRect_);
}

/**
 * @tc.name: RichEditorAddSpanAutoScroll002
 * @tc.desc: Test no auto scroll when adding a span before the richEditor is ready.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, RichEditorAddSpanAutoScroll002, TestSize.Level1)
{
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isRichEditorInit_ = false;

    // 0: AddTextSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    EXPECT_FALSE(richEditorPattern->needMoveCaretToContentRect_);

    // 1: AddImageSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
    EXPECT_FALSE(richEditorPattern->needMoveCaretToContentRect_);

    // 2: AddSymbolSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
    EXPECT_FALSE(richEditorPattern->needMoveCaretToContentRect_);

    // 3: AddPlaceholderSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddPlaceholderSpan(BUILDER_NODE_1, {});
    EXPECT_FALSE(richEditorPattern->needMoveCaretToContentRect_);
}

/**
 * @tc.name: BuilderSpanBindSelectionMenu001
 * @tc.desc: Test bind selection menu on BuilderSpan.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, BuilderSpanBindSelectionMenu001, TestSize.Level1)
{
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ResultObject objText;
    objText.type = SelectSpanType::TYPESPAN;
    ResultObject objImage;
    objImage.type = SelectSpanType::TYPEIMAGE;
    objImage.valueString = " ";
    objImage.valuePixelMap = PixelMap::CreatePixelMap(nullptr);
    ResultObject objBuilder;
    objBuilder.type = SelectSpanType::TYPEIMAGE;
    objBuilder.valueString = " ";
    objBuilder.valuePixelMap = nullptr;
    SelectionInfo originalSelection;
    SelectionInfo adjustedSelection;

    // 0: Select BuilderSpan
    originalSelection.selection_.resultObjects.push_front(objBuilder);
    adjustedSelection = richEditorPattern->GetAdjustedSelectionInfo(originalSelection);
    richEditorPattern->UpdateSelectionType(adjustedSelection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::BUILDER);

    // 1: Select BuilderSpan and TextSpan
    originalSelection.selection_.resultObjects.push_front(objText);
    adjustedSelection = richEditorPattern->GetAdjustedSelectionInfo(originalSelection);
    richEditorPattern->UpdateSelectionType(adjustedSelection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::MIXED);

    // 2: Select BuilderSpan、TextSpan and ImageSpan
    originalSelection.selection_.resultObjects.push_front(objImage);
    adjustedSelection = richEditorPattern->GetAdjustedSelectionInfo(originalSelection);
    richEditorPattern->UpdateSelectionType(adjustedSelection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::MIXED);
}

/**
 * @tc.name: SelectionMenuInteraction001
 * @tc.desc: Test the interaction between selection menu and click event.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, SelectionMenuInteraction001, TestSize.Level1)
{
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::vector<RectF> rects { RectF(0.0, 0.0, 200.0, 200.0) };
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    
    // 0: Show selectOverlay
    richEditorPattern->textSelector_.Update(0, 1);
    ASSERT_NE(richEditorPattern->selectOverlay_, nullptr);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    ASSERT_TRUE(richEditorPattern->SelectOverlayIsOn());

    // 1: Toggle the menu when the selection area is clicked
    GestureEvent info;
    info.deviceType_ = SourceType::TOUCH;
    info.localLocation_ = Offset(50, 50);
    info.globalLocation_ = Offset(50, 50);
    richEditorPattern->HandleClickSelection(info);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->GetSelectOverlayInfo()->menuInfo.menuIsShow);
    richEditorPattern->HandleClickSelection(info);
    EXPECT_TRUE(richEditorPattern->selectOverlay_->GetSelectOverlayInfo()->menuInfo.menuIsShow);
}

/**
 * @tc.name: SelectionMenuInteraction002
 * @tc.desc: Test the interaction between selection menu and click event.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, SelectionMenuInteraction002, TestSize.Level1)
{
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // 0: Show selectOverlay
    richEditorPattern->textSelector_.Update(0, 1);
    ASSERT_NE(richEditorPattern->selectOverlay_, nullptr);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    ASSERT_TRUE(richEditorPattern->SelectOverlayIsOn());

    // 1: Hide the menu when clicking on the blank area outside richEditor.
    richEditorPattern->selectOverlay_->OnHandleGlobalTouchEvent(SourceType::TOUCH, TouchType::UP);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->GetSelectOverlayInfo()->menuInfo.menuIsShow);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    // 2: Show SingleHandle
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->isEditing_ = true;
    richEditorPattern->CreateAndShowSingleHandle();
    ASSERT_TRUE(richEditorPattern->SelectOverlayIsOn());

    // 3: Resume caret twinkling when clicking on the blank area outside richEditor.
    richEditorPattern->selectOverlay_->OnHandleGlobalTouchEvent(SourceType::TOUCH, TouchType::UP);
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_TRUE(richEditorPattern->caretTwinkling_);
}
} // namespace OHOS::Ace::NG
