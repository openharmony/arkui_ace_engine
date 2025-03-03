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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const auto BUILDER_NODE_1 = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG,
    ElementRegister::GetInstance()->MakeUniqueId(),
    []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
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
    objImage.valueString = u" ";
    objImage.valuePixelMap = PixelMap::CreatePixelMap(nullptr);
    ResultObject objBuilder;
    objBuilder.type = SelectSpanType::TYPEIMAGE;
    objBuilder.valueString = u" ";
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
    auto manager = richEditorPattern->selectOverlay_->GetManager<SelectContentOverlayManager>();
    ASSERT_NE(manager, nullptr);
    manager->ShowOptionMenu();
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

/**
 * @tc.name: GetUrlSpanColor001
 * @tc.desc: Test get color in urlSpan theme.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, GetUrlSpanColor001, TestSize.Level1)
{
    // 0: Get richEditor Node and richEditor Pattern
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // 1: Get richEditorTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));

    // 2: Backup old richEditorTheme and set new richEditorTheme
    auto oldThemeManager = PipelineBase::GetCurrentContext()->themeManager_;
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;

    // 3: Test whether richEditor pattern->GetUrlHoverColor() and theme-GetUrlHoverColor() are the same color
    RichEditorTheme richEditorTheme;
    EXPECT_EQ(richEditorPattern->GetUrlHoverColor(), richEditorTheme.GetUrlHoverColor());

    // 4: Test whether richEditor pattern->GetUrlPressColor() and theme-GetUrlPressColor() are the same color
    EXPECT_EQ(richEditorPattern->GetUrlPressColor(), richEditorTheme.GetUrlPressColor());

    // 5: Restore old richEditorTheme
    PipelineBase::GetCurrentContext()->themeManager_ = oldThemeManager;
}

/**
 * @tc.name: GetUrlSpanShowShadow001
 * @tc.desc: Test set urlSpan showShadow
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, GetUrlSpanShowShadow001, TestSize.Level1)
{
    // 0: Get richEditor Node and richEditor Pattern
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // 1: Mock location
    Offset localLocation = Offset(54.0, 20.0);
    Offset globalLocation = Offset(54.0, 20.0);

    // 2: Mock contentRect position and width and height
    richEditorPattern->contentRect_.x_ = 25.0f;
    richEditorPattern->contentRect_.y_ = 13.0f;
    richEditorPattern->contentRect_.width_ = 526.0f;
    richEditorPattern->contentRect_.height_ = 56.0f;

    // 3: Create urlSpan with hyperlink address
    std::string address = "https://www.example.com";
    auto urlSpan = AceType::MakeRefPtr<UrlSpan>(address);

    // 4: Create spanItem and set to spans list
    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    urlSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);
    spanItem->position = 2;
    std::list<RefPtr<NG::SpanItem>> spans;
    spans.push_back(spanItem);

    // 5: Create ParagraphManager and set to richEditorPattern
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    ASSERT_NE(pManager, nullptr);
    richEditorPattern->pManager_ = pManager;

    // 6: Create MutableSpanString and set to richEditorPattern
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"click here");
    spanString->AddSpan(AceType::MakeRefPtr<UrlSpan>(address, 0, 10));
    richEditorPattern->SetStyledString(spanString);

    // 7: Create TextOverlayModifier and set to richEditorPattern
    richEditorPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();

    // 8: Create Paragraph and set to richEditorPattern
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    // 9: spans list set to richEditorPattern
    richEditorPattern->spans_ = spans;

    // 10: call HandleUrlSpanShowShadow method
    bool show = richEditorPattern->HandleUrlSpanShowShadow(localLocation, globalLocation, Color(Color::BLUE));

    // 11: Asserts that the ShowShadow result is true
    EXPECT_TRUE(show);
}

/**
 * @tc.name: HandleExtendAction001
 * @tc.desc: test HandleExtendAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleExtendAction001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->HandleExtendAction(ACTION_SELECT_ALL);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: HandleExtendAction002
 * @tc.desc: test HandleExtendAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleExtendAction002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->HandleExtendAction(ACTION_CUT);
    EXPECT_EQ(richEditorPattern->copyOption_, CopyOptions::None);
}

/**
 * @tc.name: HandleExtendAction003
 * @tc.desc: test HandleExtendAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleExtendAction003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->HandleExtendAction(ACTION_COPY);
    EXPECT_EQ(richEditorPattern->copyOption_, CopyOptions::None);
}

/**
 * @tc.name: HandleExtendAction004
 * @tc.desc: test HandleExtendAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleExtendAction004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorNode_->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextCommonEvent event;
    eventHub->FireOnPaste(event);
    richEditorPattern->HandleExtendAction(ACTION_PASTE);
    EXPECT_EQ(richEditorPattern->clipboard_, nullptr);
}

/**
 * @tc.name: HandleExtendAction005
 * @tc.desc: test HandleExtendAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleExtendAction005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->HandleExtendAction(2);
    EXPECT_TRUE(richEditorPattern->selectMenuInfo_.showCopyAll);
}

/**
 * @tc.name: HandleAISpanHoverEvent001
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleAISpanHoverEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    richEditorPattern->HandleAISpanHoverEvent(info);
    EXPECT_NE(info.GetAction(), MouseAction::MOVE);
}

/**
 * @tc.name: HandleAISpanHoverEvent002
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleAISpanHoverEvent002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    info.SetAction(MouseAction::MOVE);
    richEditorPattern->HandleAISpanHoverEvent(info);
    EXPECT_EQ(info.GetAction(), MouseAction::MOVE);
}

/**
 * @tc.name: HandleAISpanHoverEvent003
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleAISpanHoverEvent003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    info.SetAction(MouseAction::MOVE);
    AISpan aiSpan;
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_.insert({ 11, aiSpan });
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->HandleAISpanHoverEvent(info);
    EXPECT_EQ(richEditorPattern->currentMouseStyle_, MouseFormat::TEXT_CURSOR);
}

/**
 * @tc.name: HandleAISpanHoverEvent004
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleAISpanHoverEvent004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    info.SetAction(MouseAction::MOVE);
    AISpan aiSpan;
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_.insert({ 11, aiSpan });
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    richEditorPattern->scrollBar_->SetHover(true);
    richEditorPattern->HandleAISpanHoverEvent(info);
    EXPECT_TRUE(richEditorPattern->scrollBar_->isHover_);
}

/**
 * @tc.name: HandleAISpanHoverEvent005
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleAISpanHoverEvent005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    info.SetAction(MouseAction::MOVE);
    AISpan aiSpan;
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_.insert({ 11, aiSpan });
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    richEditorPattern->scrollBar_->SetPressed(true);
    richEditorPattern->HandleAISpanHoverEvent(info);
    EXPECT_TRUE(richEditorPattern->scrollBar_->isPressed_);
}

/**
 * @tc.name: HandleAISpanHoverEvent006
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleAISpanHoverEvent006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    info.SetAction(MouseAction::MOVE);
    AISpan aiSpan;
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_.insert({ 11, aiSpan });
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->scrollBar_ = nullptr;
    richEditorPattern->HandleAISpanHoverEvent(info);
    EXPECT_EQ(richEditorPattern->scrollBar_, nullptr);
}

/**
 * @tc.name: HandleAISpanHoverEvent007
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleAISpanHoverEvent007, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    info.SetAction(MouseAction::MOVE);
    AISpan aiSpan;
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_.insert({ 11, aiSpan });
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->dataDetectorAdapter_->aiSpanRects_.push_back(NG::RectF { 0.0f, 0.0f, 0.0f, 0.0f });
    richEditorPattern->dataDetectorAdapter_->aiSpanRects_.push_back(NG::RectF { 100.0f, 200.0f, 0.0f, 0.0f });
    richEditorPattern->HandleAISpanHoverEvent(info);
    EXPECT_NE(richEditorPattern->dataDetectorAdapter_->aiSpanRects_.size(), 0);
    EXPECT_TRUE(NearZero(richEditorPattern->dataDetectorAdapter_->aiSpanRects_[0].width_));
}

/**
 * @tc.name: HandleAISpanHoverEvent008
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleAISpanHoverEvent008, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    info.SetAction(MouseAction::MOVE);
    AISpan aiSpan;
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_.insert({ 11, aiSpan });
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->dataDetectorAdapter_->aiSpanRects_.push_back(NG::RectF { 0.0f, 0.0f, 100.0f, 200.0f });
    richEditorPattern->dataDetectorAdapter_->aiSpanRects_.push_back(NG::RectF { 100.0f, 200.0f, 300.0f, 400.0f });
    richEditorPattern->dataDetectorAdapter_->aiSpanRects_.push_back(NG::RectF { 200.0f, 300.0f, 400.0f, 500.0f });
    richEditorPattern->HandleAISpanHoverEvent(info);
    EXPECT_EQ(richEditorPattern->currentMouseStyle_, MouseFormat::HAND_POINTING);
}

/**
 * @tc.name: HandleAISpanHoverEvent009
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleAISpanHoverEvent009, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    info.SetAction(MouseAction::MOVE);
    AISpan aiSpan;
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_.insert({ 11, aiSpan });
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->dataDetectorAdapter_->aiSpanRects_.push_back(NG::RectF { 0.0f, 0.0f, 100.0f, 200.0f });
    richEditorPattern->dataDetectorAdapter_->aiSpanRects_.push_back(NG::RectF { 100.0f, 200.0f, 300.0f, 400.0f });
    richEditorPattern->dataDetectorAdapter_->aiSpanRects_.push_back(NG::RectF { 200.0f, 300.0f, 400.0f, 500.0f });
    richEditorPattern->currentMouseStyle_ = MouseFormat::HAND_POINTING;
    richEditorPattern->HandleAISpanHoverEvent(info);
    EXPECT_EQ(richEditorPattern->currentMouseStyle_, MouseFormat::HAND_POINTING);
}

/**
 * @tc.name: HandleAISpanHoverEvent010
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleAISpanHoverEvent010, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    info.SetAction(MouseAction::MOVE);
    AISpan aiSpan;
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_.insert({ 11, aiSpan });
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->currentMouseStyle_ = MouseFormat::TEXT_CURSOR;
    richEditorPattern->HandleAISpanHoverEvent(info);
    EXPECT_EQ(richEditorPattern->currentMouseStyle_, MouseFormat::TEXT_CURSOR);
}

/**
 * @tc.name: GetSelectSpanSplit001
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, GetSelectSpanSplit001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto newFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    auto newPlusFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    richEditorNode_->children_.push_back(newFrameNode);
    richEditorNode_->children_.push_back(newPlusFrameNode);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    EXPECT_TRUE(richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo).empty());
}

/**
 * @tc.name: GetSelectSpanSplit002
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, GetSelectSpanSplit002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::RICH_EDITOR_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::RICH_EDITOR_ETS_TAG, nodeId);
    richEditorNode_->children_.push_back(spanNode);
    richEditorNode_->children_.push_back(spanNodeNew);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 0);
}

/**
 * @tc.name: GetSelectSpanSplit003
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, GetSelectSpanSplit003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    richEditorNode_->children_.push_back(spanNode);
    richEditorNode_->children_.push_back(spanNodeNew);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.front().spanIndex, 0);
}

/**
 * @tc.name: HandleOnDragInsertStyledString001
 * @tc.desc: test HandleOnDragInsertStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleOnDragInsertStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanString> spanStringRef = AceType::MakeRefPtr<SpanString>(PREVIEW_TEXT_VALUE2);
    richEditorPattern->HandleOnDragInsertStyledString(spanStringRef);
    EXPECT_FALSE(richEditorPattern->isDragSponsor_);
}

/**
 * @tc.name: HandleOnDragInsertStyledString002
 * @tc.desc: test HandleOnDragInsertStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleOnDragInsertStyledString002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanString> spanStringRef = AceType::MakeRefPtr<SpanString>(PREVIEW_TEXT_VALUE2);
    richEditorPattern->isDragSponsor_ = true;
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->HandleOnDragInsertStyledString(spanStringRef);
    EXPECT_FALSE(richEditorPattern->caretPosition_ < richEditorPattern->dragRange_.first);
}

/**
 * @tc.name: HandleOnDragInsertStyledString003
 * @tc.desc: test HandleOnDragInsertStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleOnDragInsertStyledString003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanString> spanStringRef = AceType::MakeRefPtr<SpanString>(PREVIEW_TEXT_VALUE2);
    richEditorPattern->isDragSponsor_ = true;
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->dragRange_ = { 2, 8 };
    richEditorPattern->HandleOnDragInsertStyledString(spanStringRef);
    EXPECT_TRUE(richEditorPattern->caretPosition_ < richEditorPattern->dragRange_.first);
}

/**
 * @tc.name: InsertValueToBeforeSpan001
 * @tc.desc: test InsertValueToBeforeSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, InsertValueToBeforeSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNodeBefore = SpanNode::GetOrCreateSpanNode(V2::RICH_EDITOR_ETS_TAG, nodeId);
    std::u16string insertValue = PREVIEW_TEXT_VALUE3;
    spanNodeBefore->GetSpanItem()->content = PREVIEW_TEXT_VALUE2;
    richEditorPattern->InsertValueToBeforeSpan(spanNodeBefore, insertValue);
    EXPECT_EQ(spanNodeBefore->GetSpanItem()->position, 4);
}

/**
 * @tc.name: InsertValueToBeforeSpan002
 * @tc.desc: test InsertValueToBeforeSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, InsertValueToBeforeSpan002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNodeBefore = SpanNode::GetOrCreateSpanNode(V2::RICH_EDITOR_ETS_TAG, nodeId);
    spanNodeBefore->GetSpanItem()->content = EXCEPT_VALUE;
    richEditorPattern->InsertValueToBeforeSpan(spanNodeBefore, EXCEPT_VALUE);
    EXPECT_EQ(spanNodeBefore->GetSpanItem()->position, -1);
}

/**
 * @tc.name: ResetSelectionAfterAddSpan001
 * @tc.desc: test ResetSelectionAfterAddSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, ResetSelectionAfterAddSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->isEditing_ = true;
    richEditorPattern->ResetSelectionAfterAddSpan(false);
    EXPECT_TRUE(richEditorPattern->caretTwinklingTask_.Cancel());
}

/**
 * @tc.name: HandlePointWithTransform001
 * @tc.desc: test HandlePointWithTransform
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandlePointWithTransform001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorNode_->tag_ = V2::WINDOW_SCENE_ETS_TAG;
    OffsetF point(0, 0);
    richEditorPattern->HandlePointWithTransform(point);
    EXPECT_EQ(point.GetX(), 0);
    EXPECT_EQ(point.GetY(), 0);
}

/**
 * @tc.name: HandlePointWithTransform002
 * @tc.desc: test HandlePointWithTransform
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandlePointWithTransform002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorNode_->tag_ = V2::SCREEN_ETS_TAG;
    OffsetF point(0, 0);
    richEditorPattern->HandlePointWithTransform(point);
    EXPECT_EQ(point.GetX(), 0);
    EXPECT_EQ(point.GetY(), 0);
}

/**
 * @tc.name: AddSpanHoverEven001
 * @tc.desc: test AddSpanHoverEven
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, AddSpanHoverEven001, TestSize.Level1)
{
    // 0: Get richEditor Node and richEditor Pattern
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.clear();

    // 1: addImageSpan
    ImageSpanOptions options;
    UserMouseOptions mouseOption;
    UserGestureOptions gestureOption;
    auto gestureFunc = [](GestureEvent& info) -> void {};
    auto hoverFunc = [](bool, HoverInfo& info) -> void {};
    gestureOption.onDoubleClick = gestureFunc;
    mouseOption.onHover = hoverFunc;
    options.userMouseOption = mouseOption;
    options.userGestureOption = gestureOption;
    richEditorPattern->AddImageSpan(options);

    // 2: check doubleClick and hover func.
    EXPECT_EQ(richEditorPattern->spans_.size(), 1);
    auto it = richEditorPattern->spans_.begin();
    auto imageSpanItem = AceType::DynamicCast<ImageSpanItem>(*it);
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_NE(imageSpanItem->options.userMouseOption.onHover, nullptr);
    EXPECT_NE(imageSpanItem->options.userGestureOption.onDoubleClick, nullptr);
}

/**
 * @tc.name: HandleSelectParagraghPos001
 * @tc.desc: test HandleSelectParagraghPos
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleSelectParagraghPos001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_->text_ = u"HandleSelectParagraghPos";
    richEditorPattern->caretPosition_ = 1;
    EXPECT_EQ(richEditorPattern->HandleSelectParagraghPos(true), 0);
}

/**
 * @tc.name: HandleSelectParagraghPos002
 * @tc.desc: test HandleSelectParagraghPos
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleSelectParagraghPos002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    EXPECT_EQ(richEditorPattern->HandleSelectParagraghPos(true), 0);
}

/**
 * @tc.name: HandleSelectParagraghPos003
 * @tc.desc: test HandleSelectParagraghPos
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleSelectParagraghPos003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_->text_ = u"HandleSelectParagraghPos";
    richEditorPattern->caretPosition_ = 1;
    EXPECT_EQ(richEditorPattern->HandleSelectParagraghPos(false), 2);
}

/**
 * @tc.name: HandleSelectParagraghPos004
 * @tc.desc: test HandleSelectParagraghPos
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleSelectParagraghPos004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    EXPECT_EQ(richEditorPattern->HandleSelectParagraghPos(false), 0);
}

/**
 * @tc.name: HandleSelectFontStyle001
 * @tc.desc: test HandleSelectFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleSelectFontStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = -2;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_SEARCH);
    EXPECT_TRUE(richEditorPattern->textSelector_.SelectNothing());
}

/**
 * @tc.name: CursorMoveLineBegin001
 * @tc.desc: test CursorMoveLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, CursorMoveLineBegin001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 0;
    EXPECT_FALSE(richEditorPattern->CursorMoveLineBegin());
}

/**
 * @tc.name: HandleKbVerticalSelection001
 * @tc.desc: test HandleKbVerticalSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleKbVerticalSelection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 0;
    richEditorPattern->caretPosition_ = 1;
    EXPECT_EQ(richEditorPattern->HandleKbVerticalSelection(true), 0);
}

/**
 * @tc.name: HandleKbVerticalSelection002
 * @tc.desc: test HandleKbVerticalSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleKbVerticalSelection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 0;
    richEditorPattern->caretPosition_ = 1;
    EXPECT_EQ(richEditorPattern->HandleKbVerticalSelection(true), 0);
}

/**
 * @tc.name: HandleTouchUp001
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleTouchUp001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->moveCaretState_.isMoveCaret = true;
    richEditorPattern->HandleTouchUp();
    EXPECT_FALSE(richEditorPattern->isCursorAlwaysDisplayed_);
}

/**
 * @tc.name: HandleTouchUp002
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleTouchUp002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->magnifierController_->isShowMagnifier_ = true;
    auto removeFrameNode = richEditorPattern->magnifierController_->removeFrameNode_;
    richEditorPattern->magnifierController_.Reset();
    richEditorPattern->HandleTouchUp();
    EXPECT_FALSE(removeFrameNode);
}

/**
 * @tc.name: HandleMouseLeftButtonPress001
 * @tc.desc: test HandleMouseLeftButtonPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleMouseLeftButtonPress001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    richEditorPattern->HandleMouseLeftButtonPress(info);
    EXPECT_FALSE(richEditorPattern->blockPress_);
}

/**
 * @tc.name: HandleMouseLeftButtonPress002
 * @tc.desc: test HandleMouseLeftButtonPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleMouseLeftButtonPress002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TestParagraphRect paragraphRect = { .start = 0, .end = 10, .rects = { { 0, 0, 100, 20 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 10,
        .indexOffsetMap = { { 0, Offset(0, 0) }, { 6, Offset(50, 0) } },
        .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    MouseInfo info;
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    richEditorPattern->HandleMouseLeftButtonPress(info);
    EXPECT_TRUE(richEditorPattern->blockPress_);
}

/**
 * @tc.name: HandleMouseLeftButtonPress003
 * @tc.desc: test HandleMouseLeftButtonPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleMouseLeftButtonPress003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TestParagraphRect paragraphRect = { .start = 0, .end = 1, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 1,
        .indexOffsetMap = { { 0, Offset(0, 0) }, { 6, Offset(50, 0) } },
        .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    MouseInfo info;
    richEditorPattern->GetFocusHub()->focusType_ = FocusType::DISABLE;
    richEditorPattern->HandleMouseLeftButtonPress(info);
    EXPECT_FALSE(richEditorPattern->GetFocusHub()->IsFocusable());
}

/**
 * @tc.name: HandleMouseRightButton001
 * @tc.desc: test HandleMouseRightButton
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleMouseRightButton001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    info.action_ = MouseAction::RELEASE;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([&](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    ASSERT_NE(mockParagraph, nullptr);
    PositionWithAffinity positionWithAffinity(2, TextAffinity::UPSTREAM);
    EXPECT_CALL(*mockParagraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(positionWithAffinity));
    paragraphInfo.paragraph = mockParagraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfo);
    richEditorPattern->HandleMouseRightButton(info);
    EXPECT_FALSE(richEditorPattern->usingMouseRightButton_);
}

/**
 * @tc.name: MouseRightFocus001
 * @tc.desc: test MouseRightFocus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, MouseRightFocus001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    richEditorPattern->HandleMouseRightButton(info);
    EXPECT_FALSE(richEditorPattern->usingMouseRightButton_);
}

/**
 * @tc.name: ShowHandles001
 * @tc.desc: test ShowHandles
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, ShowHandles001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isMousePressed_ = true;
    auto info = richEditorPattern->GetSpansInfo(richEditorPattern->textSelector_.GetTextStart(),
        richEditorPattern->textSelector_.GetTextEnd(), GetSpansMethod::ONSELECT);
    auto selResult = info.GetSelection().resultObjects;
    richEditorPattern->ShowHandles(false);
    EXPECT_NE(selResult.size(), 1);
}

/**
 * @tc.name: CursorMoveToParagraphEnd001
 * @tc.desc: test CursorMoveToParagraphEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, CursorMoveToParagraphEnd001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    EXPECT_FALSE(richEditorPattern->CursorMoveToParagraphEnd());
}

/**
 * @tc.name: DumpInfo001
 * @tc.desc: test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, DumpInfo001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto context = richEditorNode_->GetContextRefPtr();
    auto pipe = richEditorNode_->GetContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    std::function<void()> test;
    richEditorPattern->customKeyboardBuilder_ = test;
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    richEditorPattern->DumpInfo(json);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->HasRenderTransform());
}

/**
 * @tc.name: DumpInfo002
 * @tc.desc: test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, DumpInfo002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto context = richEditorNode_->GetContextRefPtr();
    auto pipe = richEditorNode_->GetContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    std::function<void()> test = []() {};
    richEditorPattern->customKeyboardBuilder_ = test;
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    richEditorPattern->DumpInfo(json);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->HasRenderTransform());
}

/**
 * @tc.name: HandleOnDragInsertValue001
 * @tc.desc: test HandleOnDragInsertValue
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleOnDragInsertValue001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::u16string insertValue;
    richEditorPattern->textSelector_.baseOffset = -2;
    richEditorPattern->textSelector_.destinationOffset = -2;
    richEditorPattern->HandleOnDragInsertValue(insertValue);
    EXPECT_FALSE(richEditorPattern->textSelector_.IsValid());
}

/**
 * @tc.name: HandleOnDragInsertValue002
 * @tc.desc: test HandleOnDragInsertValue
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleOnDragInsertValue002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::u16string insertValue;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->HandleOnDragInsertValue(insertValue);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), 2);
}

/**
 * @tc.name: UpdateMagnifierStateAfterLayout001
 * @tc.desc: test UpdateMagnifierStateAfterLayout
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, UpdateMagnifierStateAfterLayout001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    WeakPtr<TextBase> textBase;
    richEditorPattern->selectOverlay_ = AceType::MakeRefPtr<RichEditorSelectOverlay>(textBase);
    richEditorPattern->magnifierController_.Reset();
    richEditorPattern->UpdateMagnifierStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->caretVisible_);
}

/**
 * @tc.name: UpdateMagnifierStateAfterLayout002
 * @tc.desc: test UpdateMagnifierStateAfterLayout
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, UpdateMagnifierStateAfterLayout002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    WeakPtr<TextBase> textBase;
    richEditorPattern->selectOverlay_ = AceType::MakeRefPtr<RichEditorSelectOverlay>(textBase);
    WeakPtr<Pattern> pattern;
    richEditorPattern->magnifierController_ = AceType::MakeRefPtr<MagnifierController>(pattern);
    richEditorPattern->magnifierController_->magnifierNodeExist_ = true;
    richEditorPattern->UpdateMagnifierStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->caretVisible_);
}

/**
 * @tc.name: SetCaretPosition001
 * @tc.desc: test SetCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, SetCaretPosition001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"SetCaretPosition");
    richEditorPattern->caretChangeListener_ = [](int32_t x) {};
    EXPECT_TRUE(richEditorPattern->SetCaretPosition(2, false));
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleSurfaceChanged001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->magnifierController_.Reset();
    richEditorPattern->HandleSurfaceChanged(1, 1, 2, 2, WindowSizeChangeReason::DRAG);
    EXPECT_FALSE(richEditorPattern->originIsMenuShow_);
}

/**
 * @tc.name: GetCaretOffsetInfoByPosition001
 * @tc.desc: test GetCaretOffsetInfoByPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, GetCaretOffsetInfoByPosition001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    CaretOffsetInfo result = richEditorPattern->GetCaretOffsetInfoByPosition(1);
    EXPECT_EQ(result.caretOffsetUp.GetX(), 0);
    EXPECT_EQ(result.caretOffsetUp.GetY(), 0);
}

/**
 * @tc.name: SetSubSpans001
 * @tc.desc: test SetSubSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, SetSubSpans001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    RefPtr<SpanItem> spanItem1 = AceType::MakeRefPtr<SpanItem>();
    spanItem->spanItemType = SpanItemType::SYMBOL;
    spanItem1->spanItemType = SpanItemType::NORMAL;
    spanItem1->position = 0;
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->spans_.push_back(spanItem1);
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(INIT_VALUE_1);
    richEditorPattern->SetSubSpans(spanString, 1, 1);
    EXPECT_EQ(spanString->spans_.size(), 0);
}

/**
 * @tc.name: GetSelectSpanSplit004
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, GetSelectSpanSplit004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    richEditorNode_->children_.push_back(spanNode);
    richEditorNode_->children_.push_back(spanNodeNew);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    startPositionSpanInfo.spanOffset_ = 1;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: GetSelectSpanSplit005
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, GetSelectSpanSplit005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeAnother = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    richEditorNode_->children_.push_back(spanNode);
    richEditorNode_->children_.push_back(spanNodeNew);
    richEditorNode_->children_.push_back(spanNodeAnother);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    endPositionSpanInfo.spanIndex_ = 1;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 2);
}

/**
 * @tc.name: GetSelectSpanSplit006
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, GetSelectSpanSplit006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeAnother = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    richEditorNode_->children_.push_back(spanNode);
    richEditorNode_->children_.push_back(spanNodeNew);
    richEditorNode_->children_.push_back(spanNodeAnother);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    endPositionSpanInfo.spanIndex_ = 1;
    endPositionSpanInfo.spanOffset_ = 1;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 2);
}

/**
 * @tc.name: GetSelectSpanSplit007
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, GetSelectSpanSplit007, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeAnother = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    richEditorNode_->children_.push_back(spanNode);
    richEditorNode_->children_.push_back(spanNodeNew);
    richEditorNode_->children_.push_back(spanNodeAnother);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    endPositionSpanInfo.spanIndex_ = 2;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 3);
}

/**
 * @tc.name: HandleMouseEvent001
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleMouseEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    richEditorPattern->selectOverlay_->ProcessOverlay({ .animation = false });
    auto manager = richEditorPattern->selectOverlay_->GetManager<SelectContentOverlayManager>();
    ASSERT_NE(manager, nullptr);
    SelectOverlayInfo selectInfo;
    manager->CreateSelectOverlay(selectInfo);
    manager->shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>();
    ASSERT_NE(manager->shareOverlayInfo_, nullptr);
    richEditorPattern->HandleMouseEvent(info);
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::NONE);
}

/**
 * @tc.name: HandleMouseEvent002
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleMouseEvent002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    richEditorPattern->selectOverlay_->ProcessOverlay({ .animation = false });
    auto manager = richEditorPattern->selectOverlay_->GetManager<SelectContentOverlayManager>();
    ASSERT_NE(manager, nullptr);
    SelectOverlayInfo selectInfo;
    manager->CreateSelectOverlay(selectInfo);
    manager->shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>();
    ASSERT_NE(manager->shareOverlayInfo_, nullptr);
    info.SetAction(MouseAction::PRESS);
    richEditorPattern->HandleMouseEvent(info);
    EXPECT_TRUE(info.GetAction() == MouseAction::PRESS);
}

/**
 * @tc.name: HandleMouseEvent003
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleMouseEvent003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    richEditorPattern->scrollBar_.Reset();
    richEditorPattern->HandleMouseEvent(info);
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::NONE);
}

/**
 * @tc.name: HandleMouseEvent004
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleMouseEvent004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    richEditorPattern->scrollBar_->isPressed_ = true;
    richEditorPattern->HandleMouseEvent(info);
    EXPECT_EQ(richEditorPattern->currentMouseStyle_, MouseFormat::DEFAULT);
}

/**
 * @tc.name: HandleMouseEvent005
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleMouseEvent005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    richEditorPattern->hasUrlSpan_ = true;
    richEditorPattern->HandleMouseEvent(info);
    EXPECT_EQ(richEditorPattern->currentMouseStyle_, MouseFormat::TEXT_CURSOR);
}

/**
 * @tc.name: HandleMouseEvent006
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleMouseEvent006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    RefPtr<SpanItem> spanItemAnother = AceType::MakeRefPtr<SpanItem>();
    spanItem->position = 2;
    spanItemAnother->position = 2;
    spanItem->urlOnRelease = []() {};
    spanItemAnother->urlOnRelease = []() {};
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->spans_.push_back(spanItemAnother);
    richEditorPattern->hasUrlSpan_ = true;
    richEditorPattern->baselineOffset_ = 5;
    richEditorPattern->contentRect_ = RectF(10, 20, 100, 200);
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    paragraphInfo.paragraph = mockParagraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfo);
    richEditorPattern->HandleMouseEvent(info);
    EXPECT_EQ(richEditorPattern->currentMouseStyle_, MouseFormat::HAND_POINTING);
}

/**
 * @tc.name: GetThumbnailCallback001
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, GetThumbnailCallback001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    paragraphInfo.paragraph = mockParagraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfo);
    auto thumbnailCallback = richEditorPattern->GetThumbnailCallback();
    Offset point(10, 10);
    thumbnailCallback(point);
    EXPECT_TRUE(richEditorPattern->textSelector_.IsValid());
}

/**
 * @tc.name: HandleClickSelection001
 * @tc.desc: test HandleClickSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, HandleClickSelection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->selectOverlay_->bindManager_.Reset();
    OHOS::Ace::GestureEvent info;
    EXPECT_TRUE(richEditorPattern->HandleClickSelection(info));
}

/**
 * @tc.name: RepeatClickCaret001
 * @tc.desc: test RepeatClickCaret
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, RepeatClickCaret001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretTwinkling_ = true;
    Offset offset = Offset(50.0, 50.0);
    RectF lastCaretRect;
    EXPECT_FALSE(richEditorPattern->RepeatClickCaret(offset, lastCaretRect));
}

/**
 * @tc.name: CloseSystemMenu001
 * @tc.desc: test CloseSystemMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFiveNg, CloseSystemMenu001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->selectOverlay_->bindManager_.Reset();
    richEditorPattern->CloseSystemMenu();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
}
} // namespace OHOS::Ace::NG
