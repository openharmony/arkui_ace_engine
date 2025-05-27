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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_clipboard.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::u16string TEST_INSERT_LINE_SPACE = u" ";
constexpr int32_t CALCLINEEND_POSITION = 0;
constexpr int32_t PERFORM_ACTION = 1;
} // namespace

class RichEditorPatternTestThreeNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    RefPtr<RichEditorPattern> GetRichEditorPattern();
};

void RichEditorPatternTestThreeNg::SetUp()
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
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorPatternTestThreeNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorPatternTestThreeNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

RefPtr<RichEditorPattern> RichEditorPatternTestThreeNg::GetRichEditorPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

/**
 * @tc.name: SetInputMethodStatus001
 * @tc.desc: test SetInputMethodStatus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, SetInputMethodStatus001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    richEditorPattern->SetInputMethodStatus(true);
    EXPECT_TRUE(richEditorPattern->imeShown_);
    richEditorPattern->SetInputMethodStatus(false);
    EXPECT_FALSE(richEditorPattern->imeShown_);
#endif
}

/**
 * @tc.name: BeforeStatusCursorMove001
 * @tc.desc: test BeforeStatusCursorMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, BeforeStatusCursorMove001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);

    SelectOverlayInfo overlayInfo;
    auto shareOverlayInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);
    auto overlayNode = SelectOverlayNode::CreateSelectOverlayNode(shareOverlayInfo);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    manager->selectOverlayNode_ = overlayNode;
    richEditorPattern->textSelector_.Update(1, 2);
    EXPECT_FALSE(richEditorPattern->BeforeStatusCursorMove(true));
}

/**
 * @tc.name: CursorMoveToParagraphBegin001
 * @tc.desc: test CursorMoveToParagraphBegin
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveToParagraphBegin001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_FALSE(richEditorPattern->CursorMoveToParagraphBegin());
    AddSpan(TEST_INSERT_LINE_SEP);
    richEditorPattern->caretPosition_ = 1;
    EXPECT_TRUE(richEditorPattern->CursorMoveToParagraphBegin());
}

/**
 * @tc.name: CursorMoveEnd001
 * @tc.desc: test CursorMoveToParagraphBegin
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveEnd001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_FALSE(richEditorPattern->CursorMoveToParagraphBegin());
}

/**
 * @tc.name: CursorMoveEnd002
 * @tc.desc: test CursorMoveEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveEnd002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 2;
    EXPECT_TRUE(richEditorPattern->CursorMoveEnd());
}

/**
 * @tc.name: CursorMoveEnd003
 * @tc.desc: test CursorMoveEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveEnd003, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = 2;
    EXPECT_FALSE(richEditorPattern->CursorMoveEnd());
}

/**
 * @tc.name: GetLeftWordPosition001
 * @tc.desc: test GetLeftWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetLeftWordPosition001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->GetLeftWordPosition(richEditorPattern->caretPosition_), 0);
    AddSpan(INIT_VALUE_1 + TEST_INSERT_LINE_SPACE);
    EXPECT_EQ(richEditorPattern->GetLeftWordPosition(richEditorPattern->GetTextContentLength()), 0);
}

/**
 * @tc.name: GetRightWordPosition001
 * @tc.desc: test GetRightWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetRightWordPosition001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->GetLeftWordPosition(richEditorPattern->caretPosition_), 0);
    AddSpan(INIT_VALUE_1 + TEST_INSERT_LINE_SPACE);
    EXPECT_EQ(richEditorPattern->GetRightWordPosition(richEditorPattern->GetTextContentLength()),
        richEditorPattern->GetTextContentLength());
}

/**
 * @tc.name: HandleOnEscape001
 * @tc.desc: test HandleOnEscape
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleOnEscape001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_FALSE(richEditorPattern->HandleOnEscape());
}

/**
 * @tc.name: ClearContent001
 * @tc.desc: test ClearContent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, ClearContent001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto placeholderSpanNode = PlaceholderSpanNode::GetOrCreateSpanNode(V2::PLACEHOLDER_SPAN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<PlaceholderSpanPattern>(); });
    auto placeholderSpanItem = placeholderSpanNode->GetSpanItem();
    ASSERT_NE(placeholderSpanItem, nullptr);
    placeholderSpanItem->content = u" ";
    placeholderSpanNode->MountToParent(richEditorNode_);
    richEditorPattern->ClearContent(placeholderSpanNode);
    EXPECT_TRUE(placeholderSpanItem->content.empty());
}

/**
 * @tc.name: UpdateTextFieldManager001
 * @tc.desc: test UpdateTextFieldManager
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, UpdateTextFieldManager001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    textFieldManager->SetHeight(20);
    context->SetTextFieldManager(textFieldManager);

    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    context->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    Offset Offset = { 1, 4 };
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_NE(textFieldManager->GetOnFocusTextField().Upgrade(), nullptr);
}

/**
 * @tc.name: GetRightWordPosition002
 * @tc.desc: test GetRightWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetRightWordPosition002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    std::u16string firstText = u"text";
    AddSpan(firstText);
    std::u16string space = u" ";
    std::u16string secondText = u"content";
    AddSpan(space + secondText);
    auto initCaretPosition = firstText.size();
    EXPECT_EQ(richEditorPattern->GetRightWordPosition(initCaretPosition), initCaretPosition + space.size());
}

/**
 * @tc.name: GetRightWordPosition003
 * @tc.desc: test GetRightWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetRightWordPosition003, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    std::u16string firstText = u"Text ";
    AddSpan(firstText);
    std::u16string secondText = u"Content\n";
    AddSpan(secondText);
    AddSpan(INIT_VALUE_3);

    auto initCaretPosition = firstText.size() + secondText.size() - 1;
    EXPECT_EQ(richEditorPattern->GetRightWordPosition(initCaretPosition), initCaretPosition + 1);
}

/**
 * @tc.name: InitScrollablePattern001
 * @tc.desc: test InitScrollablePattern when update padding property
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, InitScrollablePattern001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto layoutProperty = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PaddingProperty padding;
    padding.top = CalcLength(10);
    padding.left = CalcLength(10);
    padding.right = CalcLength(10);
    padding.bottom = CalcLength(10);
    layoutProperty->UpdatePadding(padding);
    richEditorPattern->InitScrollablePattern();
    EXPECT_TRUE(IsEqual(richEditorPattern->richTextRect_.GetOffset(), OffsetF(10.0f, 10.0f)));
}

/**
 * @tc.name: GetRectsForRange001
 * @tc.desc: test GetRectsForRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetRectsForRange001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    int32_t start = 0;
    int32_t end = 10;
    RectHeightStyle heightStyle = RectHeightStyle::TIGHT;
    RectWidthStyle widthStyle = RectWidthStyle::TIGHT;
    auto result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetRectsForRange002
 * @tc.desc: test GetRectsForRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetRectsForRange002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    int32_t start = -5;
    int32_t end = 10;
    RectHeightStyle heightStyle = RectHeightStyle::TIGHT;
    RectWidthStyle widthStyle = RectWidthStyle::TIGHT;
    auto result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetRectsForRange003
 * @tc.desc: test GetRectsForRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetRectsForRange003, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    int32_t start = 0;
    int32_t end = -5;
    RectHeightStyle heightStyle = RectHeightStyle::TIGHT;
    RectWidthStyle widthStyle = RectWidthStyle::TIGHT;
    auto result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetRectsForRange004
 * @tc.desc: test GetRectsForRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetRectsForRange004, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    int32_t start = 10;
    int32_t end = 0;
    RectHeightStyle heightStyle = RectHeightStyle::TIGHT;
    RectWidthStyle widthStyle = RectWidthStyle::TIGHT;
    auto result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: CursorMoveUp001
 * @tc.desc: test CursorMoveUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveUp001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("hello1");
    richEditorPattern->caretPosition_ = 1;
    EXPECT_TRUE(richEditorPattern->CursorMoveUp());
}

/**
 * @tc.name: CursorMoveUp002
 * @tc.desc: test CursorMoveUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveUp002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("hello1");
    richEditorPattern->caretPosition_ = 1;
    OffsetF paintOffset = { -10, 1 };
    richEditorPattern->richTextRect_.SetOffset(paintOffset);
    EXPECT_TRUE(richEditorPattern->CursorMoveUp());
}

/**
 * @tc.name: CursorMoveDown
 * @tc.desc: test CursorMoveDown
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveDown, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("hello1");
    richEditorPattern->caretPosition_ = 1;
    OffsetF paintOffset = { -10, 1 };
    richEditorPattern->richTextRect_.SetOffset(paintOffset);
    EXPECT_TRUE(richEditorPattern->CursorMoveDown());
}

/**
 * @tc.name: OnColorConfigurationUpdate
 * @tc.desc: test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, OnColorConfigurationUpdate, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipe = richEditorNode_->GetContext();
    auto spanNode = SpanNode::GetOrCreateSpanNode(1);
    richEditorNode_->children_.push_back(spanNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    richEditorPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(richEditorPattern->scrollBar_, nullptr);
}

/**
 * @tc.name: IsTextEditableForStylus001
 * @tc.desc: test IsTextEditableForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, IsTextEditableForStylus001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    bool tag = richEditorPattern->IsTextEditableForStylus();
    EXPECT_TRUE(tag);
}

/**
 * @tc.name: IsTextEditableForStylus002
 * @tc.desc: test IsTextEditableForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, IsTextEditableForStylus002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetFocusHub()->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(richEditorPattern->GetFocusHub()->IsFocusable());
    bool tag = richEditorPattern->IsTextEditableForStylus();
    EXPECT_FALSE(tag);
}

/**
 * @tc.name: IsTextEditableForStylus003
 * @tc.desc: test IsTextEditableForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, IsTextEditableForStylus003, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetFocusHub()->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(richEditorPattern->GetFocusHub()->IsFocusable());
    EXPECT_TRUE(richEditorNode_->IsVisible());
    richEditorNode_->layoutProperty_->OnVisibilityUpdate(VisibleType::INVISIBLE);
    EXPECT_FALSE(richEditorNode_->IsVisible());
    bool tag = richEditorPattern->IsTextEditableForStylus();
    EXPECT_FALSE(tag);
}

/**
 * @tc.name: CalcLineEndPosition
 * @tc.desc: test CalcLineEndPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CalcLineEndPosition, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->richTextRect_.y_ = 10.0f;
    richEditorPattern->contentRect_.y_ = 20.0f;
    EXPECT_EQ(richEditorPattern->CalcLineEndPosition(10), CALCLINEEND_POSITION);
}

/**
 * @tc.name: PerformAction
 * @tc.desc: test PerformAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, PerformAction, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(options2);
    int count = 0;
    TextFieldCommonEvent event2;
    auto callback = [&count, &event2](int32_t key, NG::TextFieldCommonEvent& event) {
        event2 = event;
        if (count > 0) {
            event.SetKeepEditable(true);
        }
        count = count + 1;
    };
    eventHub->SetOnSubmit(std::move(callback));
    TextInputAction action2 = TextInputAction::SEARCH;
    bool forceCloseKeyboard = false;
    richEditorPattern->PerformAction(action2, forceCloseKeyboard);
    EXPECT_EQ(count, PERFORM_ACTION);
}

/**
 * @tc.name: TripleClickSection001
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, TripleClickSection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    auto pipe = richEditorNode_->GetContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    richEditorPattern->TripleClickSection(info, 1, 1, 1);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: TripleClickSection002
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, TripleClickSection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);
    auto pipe = richEditorNode_->GetContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    richEditorPattern->TripleClickSection(info, 1, 1, 1);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: TripleClickSection003
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, TripleClickSection003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);
    auto pipe = richEditorNode_->GetContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    richEditorPattern->TripleClickSection(info, 1, 5, 1);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: UpdateSelectionType
 * @tc.desc: test UpdateSelectionType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, UpdateSelectionType, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SelectionInfo textSelectInfo;
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN);
    richEditorPattern->UpdateSelectionType(textSelectInfo);
    EXPECT_EQ(richEditorPattern->selectedType_, TextSpanType::NONE);
}

/**
 * @tc.name: AdjustIndexSkipLineSeparator001
 * @tc.desc: test AdjustIndexSkipLineSeparator
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, AdjustIndexSkipLineSeparator001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t currentPosition = 1;
    bool ret = richEditorPattern->AdjustIndexSkipLineSeparator(currentPosition);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AdjustIndexSkipLineSeparator002
 * @tc.desc: test AdjustIndexSkipLineSeparator
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, AdjustIndexSkipLineSeparator002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t currentPosition = 0;
    bool ret = richEditorPattern->AdjustIndexSkipLineSeparator(currentPosition);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AdjustIndexSkipLineSeparator003
 * @tc.desc: test AdjustIndexSkipLineSeparator
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, AdjustIndexSkipLineSeparator003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t currentPosition = 10;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = u"AdjustInd\nxSkipLineSeparator";
    richEditorPattern->spans_.push_back(spanItem);
    EXPECT_TRUE(richEditorPattern->AdjustIndexSkipLineSeparator(currentPosition));
}

/**
 * @tc.name: FireOnSelectionChange001
 * @tc.desc: test FireOnSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, FireOnSelectionChange001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    bool isForced = true;
    richEditorPattern->caretTwinkling_ = true;
    richEditorPattern->selectOverlay_->isSingleHandle_ = true;
    auto range = richEditorPattern->lastSelectionRange_;
    richEditorPattern->FireOnSelectionChange(start, end, isForced);
    EXPECT_FALSE(richEditorPattern->lastSelectionRange_ == range);
}

/**
 * @tc.name: FireOnSelectionChange002
 * @tc.desc: test FireOnSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, FireOnSelectionChange002, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    bool isForced = true;
    richEditorPattern->caretTwinkling_ = false;
    richEditorPattern->selectOverlay_->isSingleHandle_ = true;
    auto range = richEditorPattern->lastSelectionRange_;
    richEditorPattern->FireOnSelectionChange(start, end, isForced);
    EXPECT_FALSE(richEditorPattern->lastSelectionRange_ == range);
}

/**
 * @tc.name: FireOnSelectionChange003
 * @tc.desc: test FireOnSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, FireOnSelectionChange003, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    bool isForced = true;
    richEditorPattern->caretTwinkling_ = false;
    richEditorPattern->selectOverlay_->isSingleHandle_ = false;
    auto range = richEditorPattern->lastSelectionRange_;
    richEditorPattern->FireOnSelectionChange(start, end, isForced);
    EXPECT_TRUE(richEditorPattern->lastSelectionRange_ == range);
}

/**
 * @tc.name: SetResultObjectText001
 * @tc.desc: test SetResultObjectText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, SetResultObjectText001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ResultObject resultObject;
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    EXPECT_NE(spanItem, nullptr);
    spanItem->content = u"test";
    richEditorPattern->previewTextRecord_.previewContent = u"text";
    richEditorPattern->SetResultObjectText(resultObject, spanItem);
    EXPECT_EQ(resultObject.previewText, richEditorPattern->previewTextRecord_.previewContent);
    richEditorPattern->previewTextRecord_.endOffset = 0;
    richEditorPattern->SetResultObjectText(resultObject, spanItem);
    EXPECT_EQ(resultObject.previewText, richEditorPattern->previewTextRecord_.previewContent);
}

/**
 * @tc.name: CalcMoveUpPos001
 * @tc.desc: test CalcMoveUpPos
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CalcMoveUpPos001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    CaretOffsetInfo caretInfo = richEditorPattern->GetCaretOffsetInfoByPosition();
    float leadingMarginOffset = 1.0;
    OffsetF offset = { 20, 20 };
    float height = 10;
    auto overlayMod = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    overlayMod->SetCaretOffsetAndHeight(offset, height);
    auto caretOffsetOverlay = overlayMod->GetCaretOffset();
    auto minDet =
        richEditorPattern->paragraphs_.minParagraphFontSize.value_or(richEditorPattern->GetTextThemeFontSize());
    float textOffsetY = richEditorPattern->richTextRect_.GetY() + (minDet / 2.0);
    float textOffsetDownY = caretInfo.caretOffsetLine.GetY() + caretInfo.caretHeightLine - textOffsetY;
    Offset textOffset = Offset(caretOffsetOverlay.GetX() - richEditorPattern->richTextRect_.GetX(), textOffsetDownY);
    auto caretPosition = richEditorPattern->CalcMoveUpPos(leadingMarginOffset);
    EXPECT_EQ(caretPosition, richEditorPattern->paragraphs_.GetIndex(textOffset));
}

/**
 * @tc.name: CalcMoveDownPos001
 * @tc.desc: test CalcMoveDownPos
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CalcMoveDownPos001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    CaretOffsetInfo caretInfo = richEditorPattern->GetCaretOffsetInfoByPosition();
    float leadingMarginOffset = 1;
    richEditorPattern->caretPosition_ = 0;
    OffsetF offset = { 20, 20 };
    float height = 10;
    auto overlayMod = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    overlayMod->SetCaretOffsetAndHeight(offset, height);
    auto caretOffsetOverlay = overlayMod->GetCaretOffset();
    auto minDet =
        richEditorPattern->paragraphs_.minParagraphFontSize.value_or(richEditorPattern->GetTextThemeFontSize());
    float textOffsetY = richEditorPattern->richTextRect_.GetY() + (minDet / 2.0);
    float textOffsetDownY = caretInfo.caretOffsetLine.GetY() + caretInfo.caretHeightLine - textOffsetY;
    Offset textOffset = Offset(caretOffsetOverlay.GetX() - richEditorPattern->richTextRect_.GetX(), textOffsetDownY);
    auto caretPositionEnd = richEditorPattern->CalcMoveDownPos(leadingMarginOffset);
    EXPECT_EQ(caretPositionEnd, richEditorPattern->paragraphs_.GetIndex(textOffset));
}

/**
 * @tc.name: CalcMoveDownPos002
 * @tc.desc: test CalcMoveDownPos
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CalcMoveDownPos002, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    CaretOffsetInfo caretInfo = richEditorPattern->GetCaretOffsetInfoByPosition();
    float leadingMarginOffset = 1;
    richEditorPattern->caretPosition_ = 1;
    OffsetF offset = { 20, 20 };
    float height = 10;
    auto overlayMod = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    overlayMod->SetCaretOffsetAndHeight(offset, height);
    auto caretOffsetOverlay = overlayMod->GetCaretOffset();
    auto minDet =
        richEditorPattern->paragraphs_.minParagraphFontSize.value_or(richEditorPattern->GetTextThemeFontSize());
    float textOffsetY = richEditorPattern->richTextRect_.GetY() + (minDet / 2.0);
    float textOffsetDownY = caretInfo.caretOffsetLine.GetY() + caretInfo.caretHeightLine - textOffsetY;
    Offset textOffset = Offset(caretOffsetOverlay.GetX() - richEditorPattern->richTextRect_.GetX(), textOffsetDownY);
    auto caretPositionEnd = richEditorPattern->CalcMoveDownPos(leadingMarginOffset);
    EXPECT_EQ(caretPositionEnd, richEditorPattern->paragraphs_.GetIndex(textOffset));
}

/**
 * @tc.name: GetParagraphEndPosition001
 * @tc.desc: test GetParagraphEndPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetParagraphEndPosition001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t caretPosition = 10;
    AddSpan(EXCEPT_VALUE);
    auto iter = richEditorPattern->spans_.cbegin();
    auto span = *iter;
    ASSERT_NE(span, nullptr);
    int32_t position = span->position - static_cast<int32_t>(span->content.length());
    richEditorPattern->GetParagraphEndPosition(caretPosition);
    EXPECT_EQ(position, span->position - static_cast<int32_t>(span->content.length()));
    caretPosition = 1;
    richEditorPattern->GetParagraphEndPosition(caretPosition);
    EXPECT_EQ(position, span->position - static_cast<int32_t>(span->content.length()));
}

} // namespace OHOS::Ace::NG