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
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
int32_t testSpanNodeId = 1;
int32_t testFrameNodeId = 1;
int32_t testNumber0 = 0;
int32_t testNumber1 = 1;
int32_t testNumber2 = 2;
int32_t testNumber3 = 3;
int32_t testNumber4 = 4;
int32_t testNumber5 = 5;
int32_t callBack1 = 0;
} // namespace

class RichEditorPatternTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorPatternTestNg::SetUp()
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

void RichEditorPatternTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorPatternTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: RichEditorPatternTestClearDragDropEvent001
 * @tc.desc: test RichEditorPattern
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorPatternTestClearDragDropEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->ClearDragDropEvent();

    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_EQ(eventHub->onDragStart_, nullptr);
}

/**
 * @tc.name: RichEditorPatternTestOnDragMove001
 * @tc.desc: test OnDragMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorPatternTestOnDragMove001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();

    auto oldThemeManager = PipelineBase::GetCurrentContext()->themeManager_;
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;

    auto overlayMod = richEditorPattern->overlayMod_;
    richEditorPattern->overlayMod_ = nullptr;
    richEditorPattern->OnDragMove(event);
    richEditorPattern->overlayMod_ = overlayMod;

    auto isShowPlaceholder = richEditorPattern->isShowPlaceholder_;
    richEditorPattern->isShowPlaceholder_ = !isShowPlaceholder;
    richEditorPattern->OnDragMove(event);
    richEditorPattern->isShowPlaceholder_ = isShowPlaceholder;

    richEditorPattern->prevAutoScrollOffset_.SetX(testNumber1);
    richEditorPattern->prevAutoScrollOffset_.SetY(testNumber1);
    richEditorPattern->richTextRect_.SetRect(testNumber0, testNumber0, testNumber5, testNumber5);

    event->SetX(testNumber3);
    event->SetY(testNumber3);
    richEditorPattern->OnDragMove(event);
    EXPECT_EQ(richEditorPattern->prevAutoScrollOffset_.GetX(), testNumber3);

    event->SetX(testNumber4);
    event->SetY(testNumber4);
    richEditorPattern->OnDragMove(event);
    EXPECT_EQ(richEditorPattern->prevAutoScrollOffset_.GetX(), testNumber4);

    PipelineBase::GetCurrentContext()->themeManager_ = oldThemeManager;
}

/**
 * @tc.name: RichEditorPatternTestResetDragSpanItems001
 * @tc.desc: test ResetDragSpanItems
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorPatternTestResetDragSpanItems001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->dragSpanItems_.clear();
    richEditorPattern->ResetDragSpanItems();

    auto firstItem = AceType::MakeRefPtr<ImageSpanItem>();
    firstItem->imageNodeId = testFrameNodeId;
    richEditorPattern->dragSpanItems_.emplace_back(firstItem);
    richEditorPattern->ResetDragSpanItems();
    ASSERT_EQ(richEditorPattern->dragSpanItems_.size(), 0);

    auto secondItem = AceType::MakeRefPtr<PlaceholderSpanItem>();
    secondItem->placeholderSpanNodeId = testFrameNodeId;
    richEditorPattern->dragSpanItems_.emplace_back(secondItem);
    richEditorPattern->ResetDragSpanItems();
    ASSERT_EQ(richEditorPattern->dragSpanItems_.size(), 0);

    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, testFrameNodeId, richEditorPattern);
    ASSERT_NE(childFrameNode, nullptr);
    host->children_.emplace_back(childFrameNode);
    auto thirdItem = AceType::MakeRefPtr<PlaceholderSpanItem>();
    thirdItem->placeholderSpanNodeId = testFrameNodeId;
    richEditorPattern->dragSpanItems_.clear();
    richEditorPattern->dragSpanItems_.emplace_back(thirdItem);
    richEditorPattern->ResetDragSpanItems();
    ASSERT_EQ(richEditorPattern->dragSpanItems_.size(), 0);
}

/**
 * @tc.name: RichEditorPatternTestRequestKeyboard001
 * @tc.desc: test RequestKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorPatternTestRequestKeyboard001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto func = [] {};

    auto customKeyboardBuilder = richEditorPattern->customKeyboardBuilder_;
    richEditorPattern->customKeyboardBuilder_ = func;
    ASSERT_EQ(richEditorPattern->RequestKeyboard(true, true, true), true);
    richEditorPattern->customKeyboardBuilder_ = customKeyboardBuilder;
}

/**
 * @tc.name: RichEditorPatternTestInitMouseEvent001
 * @tc.desc: test InitMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorPatternTestInitMouseEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->InitMouseEvent();

    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);

    MouseInfo mouseInfo;
    auto mouseEventActuator = inputHub->mouseEventActuator_;
    ASSERT_NE(mouseEventActuator, nullptr);
    auto mouseInputEvents = mouseEventActuator->inputEvents_;
    for (auto input : mouseInputEvents) {
        input->GetOnMouseEventFunc()(mouseInfo);
    }

    auto hoverEventActuator = inputHub->hoverEventActuator_;
    ASSERT_NE(hoverEventActuator, nullptr);
    auto hoverInputEvents = hoverEventActuator->inputEvents_;
    for (auto input : hoverInputEvents) {
        input->GetOnHoverEventFunc()(true);
    }

    ASSERT_EQ(richEditorPattern->mouseEventInitialized_, true);
}

/**
 * @tc.name: RichEditorPatternTestCloseCustomKeyboard001
 * @tc.desc: test CloseCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorPatternTestCloseCustomKeyboard001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CloseCustomKeyboard();

    auto func = []() {};
    auto oldFunc = richEditorPattern->customKeyboardBuilder_;

    richEditorPattern->customKeyboardBuilder_ = func;

    EXPECT_EQ(richEditorPattern->isCustomKeyboardAttached_, false);
    EXPECT_EQ(richEditorPattern->RequestCustomKeyboard(), true);
    EXPECT_EQ(richEditorPattern->RequestCustomKeyboard(), true);
    EXPECT_EQ(richEditorPattern->isCustomKeyboardAttached_, true);
    EXPECT_NE(richEditorPattern->keyboardOverlay_, nullptr);
    ASSERT_EQ(richEditorPattern->CloseCustomKeyboard(), true);

    richEditorPattern->customKeyboardBuilder_ = oldFunc;
}

/**
 * @tc.name: RichEditorPatternTestInsertDiffStyleValueInSpan001
 * @tc.desc: test InsertDiffStyleValueInSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorPatternTestInsertDiffStyleValueInSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanNode = AceType::MakeRefPtr<SpanNode>(testSpanNodeId);
    ASSERT_NE(spanNode, nullptr);

    TextInsertValueInfo info;
    std::string insertValue;
    struct UpdateSpanStyle typingStyle;
    TextStyle textStyle(5);
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);

    richEditorPattern->InsertDiffStyleValueInSpan(spanNode, info, insertValue, false);
    ASSERT_EQ(richEditorPattern->moveLength_, 0);
}

/**
 * @tc.name: RichEditorPatternTestCreateTextSpanNode001
 * @tc.desc: test CreateTextSpanNode
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorPatternTestCreateTextSpanNode001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanNode> spanNode;

    TextInsertValueInfo info;
    std::string insertValue;
    UpdateSpanStyle updateSpanStyle;
    TextStyle textStyle;

    updateSpanStyle.useThemeFontColor = false;

    auto typingStyle = richEditorPattern->typingStyle_;
    auto typingTextStyle = richEditorPattern->typingTextStyle_;

    richEditorPattern->typingStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = std::nullopt;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue, false);
    EXPECT_EQ(spanNode->GetSpanItem()->useThemeDecorationColor, true);

    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue, false);
    EXPECT_EQ(spanNode->GetSpanItem()->useThemeDecorationColor, true);

    richEditorPattern->typingStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = textStyle;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue, false);
    EXPECT_EQ(spanNode->GetSpanItem()->useThemeDecorationColor, true);

    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue, false);
    EXPECT_EQ(spanNode->GetSpanItem()->useThemeDecorationColor, true);

    richEditorPattern->typingStyle_ = typingStyle;
    richEditorPattern->typingTextStyle_ = typingTextStyle;
}

/**
 * @tc.name: RichEditorPatternTestInitPreviewText001
 * @tc.desc: test InitPreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorPatternTestInitPreviewText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::string previewTextValue;
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
 * @tc.name: ResetDragOption001
 * @tc.desc: test ResetDragOption
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, ResetDragOption001, TestSize.Level1)
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
    auto gestureEventHub = richEditorPattern->GetGestureEventHub();
    EXPECT_NE(gestureEventHub, nullptr);
    /**
     * @tc.steps: step2. init and call function.
     */
    gestureEventHub->isTextDraggable_ = true;
    richEditorPattern->ResetDragOption();
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
}

/**
 * @tc.name: VirtualKeyboardAreaChanged001
 * @tc.desc: test OnVirtualKeyboardAreaChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, VirtualKeyboardAreaChanged001, TestSize.Level1)
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
    float height = 0.0f;
    auto x = richEditorPattern->CalcCursorOffsetByPosition(richEditorPattern->textSelector_.GetStart(), height).GetX();
    richEditorPattern->OnVirtualKeyboardAreaChanged();
    EXPECT_EQ(richEditorPattern->textSelector_.selectionBaseOffset.GetX(), x);
}

/**
 * @tc.name: GetCaretMetrics001
 * @tc.desc: test GetCaretMetrics
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetCaretMetrics001, TestSize.Level1)
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

    CaretMetricsF caretCaretMetric;
    caretCaretMetric.height = 10.0f;
    richEditorPattern->GetCaretMetrics(caretCaretMetric);
    EXPECT_EQ(caretCaretMetric.height, 0.0f);
}

/**
 * @tc.name: RichEditorToJsonValue001
 * @tc.desc: test ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorToJsonValue001, TestSize.Level1)
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

    auto jsonObject = JsonUtil::Create(true);
    InspectorFilter filter;
    filter.filterFixed = 0;
    filter.filterExt.clear();
    auto ret1 = filter.IsFastFilter();
    richEditorPattern->ToJsonValue(jsonObject, filter);
    auto ret2 = filter.IsFastFilter();
    EXPECT_EQ(ret1, ret2);
}

/**
 * @tc.name: HandleOnDragStatusCallback001
 * @tc.desc: test HandleOnDragStatusCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, HandleOnDragStatusCallback001, TestSize.Level1)
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
    RefPtr<NotifyDragEvent> notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    DragEventType dragEventType1 = DragEventType::MOVE;
    notifyDragEvent->SetX(10.0f);
    notifyDragEvent->SetY(20.0f);
    richEditorPattern->HandleOnDragStatusCallback(dragEventType1, notifyDragEvent);
    EXPECT_TRUE(richEditorPattern->isDragging_);

    /**
     * @tc.steps: step3. change parameter and call function.
     */
    DragEventType dragEventType2 = DragEventType::LEAVE;
    notifyDragEvent->SetX(20.0f);
    notifyDragEvent->SetY(20.0f);
    richEditorPattern->HandleOnDragStatusCallback(dragEventType2, notifyDragEvent);
    EXPECT_EQ(richEditorPattern->isDragging_, true);

    /**
     * @tc.steps: step4. change parameter and call function.
     */
    DragEventType dragEventType3 = DragEventType::DROP;
    notifyDragEvent->SetX(20.0f);
    notifyDragEvent->SetY(10.0f);
    richEditorPattern->HandleOnDragStatusCallback(dragEventType3, notifyDragEvent);
    EXPECT_FALSE(richEditorPattern->isDragging_);

    /**
     * @tc.steps: step5. change parameter and call function.
     */
    DragEventType dragEventType4 = DragEventType::ENTER;
    notifyDragEvent->SetX(20.0f);
    notifyDragEvent->SetY(15.0f);
    richEditorPattern->HandleOnDragStatusCallback(dragEventType4, notifyDragEvent);
    EXPECT_EQ(richEditorPattern->isDragging_, false);
}

/**
 * @tc.name: HandleCursorOnDragLeaved001
 * @tc.desc: test HandleCursorOnDragLeaved
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, HandleCursorOnDragLeaved001, TestSize.Level1)
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
    RefPtr<NotifyDragEvent> notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    EXPECT_NE(notifyDragEvent, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->isCursorAlwaysDisplayed_ = false;
    richEditorPattern->HandleCursorOnDragLeaved(notifyDragEvent);
    EXPECT_EQ(richEditorPattern->isCursorAlwaysDisplayed_, false);
}

/**
 * @tc.name: HandleCursorOnDragMoved001
 * @tc.desc: test HandleCursorOnDragMoved
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, HandleCursorOnDragMoved001, TestSize.Level1)
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
    RefPtr<NotifyDragEvent> notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    EXPECT_NE(notifyDragEvent, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->isCursorAlwaysDisplayed_ = true;
    richEditorPattern->HandleCursorOnDragMoved(notifyDragEvent);
    EXPECT_EQ(richEditorPattern->isCursorAlwaysDisplayed_, true);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->isCursorAlwaysDisplayed_ = false;
    richEditorPattern->HandleCursorOnDragMoved(notifyDragEvent);
    EXPECT_EQ(richEditorPattern->isCursorAlwaysDisplayed_, true);
}

/**
 * @tc.name: IsClickBoundary001
 * @tc.desc: test IsClickBoundary
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, IsClickBoundary001, TestSize.Level1)
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
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    auto length = richEditorPattern->GetTextContentLength();
    auto caretPosition = length + 1;
    auto ret = richEditorPattern->IsClickBoundary(caretPosition);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: AdjustPlaceholderSelection001
 * @tc.desc: test AdjustPlaceholderSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, AdjustPlaceholderSelection001, TestSize.Level1)
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
    AddSpan(INIT_U16VALUE_1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    int32_t start = 10;
    int32_t end = 20;
    Offset touchPos(11.0f, 11.0f);
    richEditorPattern->AdjustPlaceholderSelection(start, end, touchPos);
    EXPECT_NE(start, end);
}

/**
 * @tc.name: OnAutoScroll001
 * @tc.desc: test OnAutoScroll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, OnAutoScroll001, TestSize.Level1)
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
    AutoScrollParam param;
    param.showScrollbar = true;
    param.offset = 0.0f;
    richEditorPattern->contentChange_ = false;
    richEditorPattern->contentRect_.SetRect(0, 0, 1, 1);
    richEditorPattern->richTextRect_.SetRect(0, 0, 1, 1);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    param.isFirstHandle = true;
    param.autoScrollEvent = AutoScrollEvent::HANDLE;
    richEditorPattern->OnAutoScroll(param);
    EXPECT_TRUE(param.showScrollbar);
    /**
     * @tc.steps: step3. change parameter and call function.
     */
    param.autoScrollEvent = AutoScrollEvent::DRAG;
    richEditorPattern->OnAutoScroll(param);
    EXPECT_TRUE(param.showScrollbar);
    /**
     * @tc.steps: step4. change parameter and call function.
     */
    param.autoScrollEvent = AutoScrollEvent::MOUSE;
    richEditorPattern->OnAutoScroll(param);
    EXPECT_TRUE(param.showScrollbar);
}

/**
 * @tc.name: ScheduleAutoScroll001
 * @tc.desc: test ScheduleAutoScroll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, ScheduleAutoScroll001, TestSize.Level1)
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
    AutoScrollParam param;
    param.isFirstRun_ = true;
    param.offset = 0.0f;
    richEditorPattern->contentRect_.SetRect(0, 1, 1, 1);
    richEditorPattern->richTextRect_.SetRect(0, 2, 1, 1);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->isAutoScrollRunning_ = true;
    richEditorPattern->ScheduleAutoScroll(param);
    EXPECT_TRUE(param.isFirstRun_);
}

/**
 * @tc.name: UpdateChildrenOffset001
 * @tc.desc: test UpdateChildrenOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, UpdateChildrenOffset001, TestSize.Level1)
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
    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    AddSpan(INIT_U16VALUE_1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->contentRect_ = { -500.0, -500.0, 500.0, 500.0 };
    richEditorPattern->isSpanStringMode_ = true;
    std::list<RefPtr<UINode>>& childrens = host->ModifyChildren();
    auto childNode2 = FrameNode::CreateFrameNode("childNode", 2, AceType::MakeRefPtr<ImagePattern>());
    auto childNode3 = FrameNode::CreateFrameNode("childNode", 3, AceType::MakeRefPtr<PlaceholderSpanPattern>());
    auto childNode4 = FrameNode::CreateFrameNode("childNode", 4, AceType::MakeRefPtr<ImagePattern>());
    auto childNode5 = FrameNode::CreateFrameNode("childNode", 5, AceType::MakeRefPtr<PlaceholderSpanPattern>());
    auto childNode6 = FrameNode::CreateFrameNode("childNode", 5, AceType::MakeRefPtr<Pattern>());
    childrens.emplace_back(childNode2);
    childrens.emplace_back(childNode3);
    childrens.emplace_back(childNode4);
    childrens.emplace_back(childNode5);
    richEditorPattern->UpdateChildrenOffset();
    EXPECT_NE(richEditorPattern->spans_.size(), 0);
}

/**
 * @tc.name: NeedAiAnalysis001
 * @tc.desc: test NeedAiAnalysis
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, NeedAiAnalysis001, TestSize.Level1)
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
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    std::string content = "";
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    CaretUpdateType targeType1 = CaretUpdateType::PRESSED;
    int32_t pos = 0;
    int32_t spanStart = 10;
    auto ret = richEditorPattern->NeedAiAnalysis(targeType1, pos, spanStart, content);
    EXPECT_FALSE(ret);
    /**
     * @tc.steps: step3. change parameter and call function.
     */
    CaretUpdateType targeType2 = CaretUpdateType::DOUBLE_CLICK;
    ret = richEditorPattern->NeedAiAnalysis(targeType2, pos, spanStart, content);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AdjustCursorPosition001
 * @tc.desc: test AdjustCursorPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, AdjustCursorPosition001, TestSize.Level1)
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
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    std::u16string content = u"TEST123";
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(content);
    int32_t pos = 0;
    richEditorPattern->AdjustCursorPosition(pos);
    EXPECT_EQ(pos, 0);
}

/**
 * @tc.name: OnScrollEndCallback001
 * @tc.desc: test OnScrollEndCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, OnScrollEndCallback001, TestSize.Level1)
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
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->contentRect_ = { -500.0, -500.0, 500.0, 500.0 };
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->OnScrollEndCallback();
    auto res = richEditorPattern->IsSelectAreaVisible();
    EXPECT_TRUE(res);
}

/**
 * @tc.name: IsCaretInContentArea001
 * @tc.desc: test IsCaretInContentArea
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, IsCaretInContentArea001, TestSize.Level1)
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
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    auto ret = richEditorPattern->IsCaretInContentArea();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: UpdateScrollBarOffset001
 * @tc.desc: test UpdateScrollBarOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, UpdateScrollBarOffset001, TestSize.Level1)
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
    auto tmpHost = richEditorPattern->GetHost();
    ASSERT_NE(tmpHost, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->scrollBar_ = nullptr;
    richEditorPattern->scrollBarProxy_ = nullptr;
    richEditorPattern->UpdateScrollBarOffset();
    EXPECT_FALSE(tmpHost->isPropertyDiffMarked_);
}

/**
 * @tc.name: GetChangeSpanStyle002
 * @tc.desc: test GetChangeSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetChangeSpanStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.textAlign = TextAlign::END;
    paragraphStyle.leadingMargin = std::make_optional<NG::LeadingMargin>();
    paragraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, paragraphStyle);
    std::optional<struct UpdateParagraphStyle> spanParaStyle = paragraphStyle;

    RichEditorChangeValue changeValue;
    RichEditorAbstractSpanResult span1;
    changeValue.originalSpans_.emplace_back(span1);
    RichEditorAbstractSpanResult span2;
    changeValue.originalSpans_.emplace_back(span2);

    RichEditorAbstractSpanResult& firstInfo = changeValue.originalSpans_.front();
    int32_t firstLength = static_cast<int32_t>(StringUtils::ToWstring(firstInfo.GetValue()).length());
    firstInfo.SetEraseLength(firstLength);
    RichEditorAbstractSpanResult& lastInfo = changeValue.originalSpans_.back();
    int32_t lastLength = static_cast<int32_t>(StringUtils::ToWstring(lastInfo.GetValue()).length());
    lastInfo.SetEraseLength(lastLength);

    std::optional<TextStyle> spanTextStyle;
    RefPtr<SpanNode> spanNode = OHOS::Ace::NG::SpanNode::CreateSpanNode(1);
    int32_t spanIndex = 0;
    richEditorPattern->spans_.clear();
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem3 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem3);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    lastInfo.SetSpanIndex(richEditorPattern->spans_.size() - 2);
    richEditorPattern->GetChangeSpanStyle(changeValue, spanTextStyle, spanParaStyle, spanNode, spanIndex);
    EXPECT_FALSE(spanTextStyle.has_value());
}

/**
 * @tc.name: GetReplacedSpan001
 * @tc.desc: test GetReplacedSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetReplacedSpan001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
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

    RichEditorChangeValue changeValue;
    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.textAlign = TextAlign::END;
    paragraphStyle.leadingMargin = std::make_optional<NG::LeadingMargin>();
    paragraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, paragraphStyle);
    std::optional<struct UpdateParagraphStyle> spanParaStyle = paragraphStyle;
    int32_t innerPosition = 0;
    std::string insertValue = "test123\n123";
    int32_t textIndex = 1;
    std::optional<TextStyle> textStyle = std::optional<TextStyle>(TextStyle());
    richEditorPattern->GetReplacedSpan(
        changeValue, innerPosition, insertValue, textIndex, textStyle, spanParaStyle, false, false);
    auto uiNode = host->GetChildAtIndex(0);
    EXPECT_NE(uiNode, nullptr);
    EXPECT_EQ(uiNode->GetTag(), V2::TEXT_ETS_TAG);
}

/**
 * @tc.name: GetReplacedSpanFission001
 * @tc.desc: test GetReplacedSpanFission
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetReplacedSpanFission001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorChangeValue changeValue;
    int32_t innerPosition = 0;
    std::u16string content = u"test123\n";
    int32_t startSpanIndex = 0;
    int32_t offsetInSpan = 0;
    std::optional<TextStyle> textStyle = std::optional<TextStyle>(TextStyle());
    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.textAlign = TextAlign::END;
    paragraphStyle.leadingMargin = std::make_optional<NG::LeadingMargin>();
    paragraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, paragraphStyle);
    std::optional<struct UpdateParagraphStyle> spanParaStyle = paragraphStyle;
    richEditorPattern->GetReplacedSpanFission(
        changeValue, innerPosition, content, startSpanIndex, offsetInSpan, textStyle, spanParaStyle);
    EXPECT_NE(innerPosition, 0);
}
/**
 * @tc.name: SetTextStyleToRet001
 * @tc.desc: test SetTextStyleToRet
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, SetTextStyleToRet001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorAbstractSpanResult retInfo;
    TextStyle textStyle;
    textStyle.fontFamilies_.emplace_back(INIT_VALUE_1);
    textStyle.fontFamilies_.emplace_back(INIT_VALUE_2);
    textStyle.fontFamilies_.emplace_back(INIT_VALUE_3);
    richEditorPattern->SetTextStyleToRet(retInfo, textStyle);
    EXPECT_EQ(retInfo.GetFontSize(), textStyle.GetFontSize().ConvertToVp());
}

/**
 * @tc.name: CalcInsertValueObj003
 * @tc.desc: test CalcInsertValueObj
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, CalcInsertValueObj003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->spans_.clear();
    AddSpan(u"");
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    auto it = richEditorPattern->spans_.front();
    TextInsertValueInfo info;
    it->content = u"";
    it->position = 0;
    int textIndex = 1;
    richEditorPattern->CalcInsertValueObj(info, textIndex, false);
    EXPECT_NE(info.GetSpanIndex(), richEditorPattern->spans_.size());

    /**
     * @tc.steps: step2. change parameter and call function.
     */
    it->content = u"test123\n";
    it->position = 18;
    textIndex = 18;
    richEditorPattern->CalcInsertValueObj(info, textIndex, false);
    EXPECT_NE(info.GetSpanIndex(), richEditorPattern->spans_.size());
}

/**
 * @tc.name: GetDelPartiallySpanItem001
 * @tc.desc: test GetDelPartiallySpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetDelPartiallySpanItem001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.clear();
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem3 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem3);
    RichEditorChangeValue changeValue;
    RichEditorAbstractSpanResult span1;
    changeValue.originalSpans_.emplace_back(span1);
    RichEditorAbstractSpanResult span2;
    changeValue.originalSpans_.emplace_back(span2);
    RichEditorAbstractSpanResult& firstInfo = changeValue.originalSpans_.front();
    firstInfo.SetValue("");
    RichEditorAbstractSpanResult& lastInfo = changeValue.originalSpans_.back();
    lastInfo.SetValue("test123\n");
    int32_t lastLength = static_cast<int32_t>(StringUtils::ToWstring(lastInfo.GetValue()).length());
    lastInfo.SetEraseLength(lastLength - 1);
    std::u16string originalStr;
    int32_t originalPos = 0;
    auto ret = richEditorPattern->GetDelPartiallySpanItem(changeValue, originalStr, originalPos);
    auto it = richEditorPattern->spans_.front();
    EXPECT_NE(ret, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    int32_t firstLength = static_cast<int32_t>(StringUtils::ToWstring(firstInfo.GetValue()).length());
    firstInfo.SetEraseLength(firstLength);
    lastLength = static_cast<int32_t>(StringUtils::ToWstring(lastInfo.GetValue()).length());
    lastInfo.SetEraseLength(lastLength);
    ret = richEditorPattern->GetDelPartiallySpanItem(changeValue, originalStr, originalPos);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: TestRichEditorBeforeChangeText002
 * @tc.desc: test BeforeChangeText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, TestRichEditorBeforeChangeText002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    RichEditorChangeValue changeValue;
    TextSpanOptions options;
    options.style = std::optional<TextStyle>(TextStyle(5));
    richEditorPattern->spans_.clear();
    auto ret = richEditorPattern->BeforeChangeText(changeValue, options);
    EXPECT_EQ(ret, true);
    /**
     * @tc.steps: step2. change parameters and call function.
     */
    options.offset = 200;
    ret = richEditorPattern->BeforeChangeText(changeValue, options);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: FixMoveDownChange001
 * @tc.desc: test FixMoveDownChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, FixMoveDownChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    RichEditorChangeValue changeValue;
    RichEditorAbstractSpanResult span1;
    span1.SetValue("test123");
    changeValue.originalSpans_.emplace_back(span1);
    RichEditorAbstractSpanResult span2;
    span2.SetValue("test");
    changeValue.replacedSpans_.emplace_back(span2);
    RichEditorAbstractSpanResult& firstInfo = changeValue.originalSpans_.front();
    int32_t firstLength = static_cast<int32_t>(StringUtils::ToWstring(firstInfo.GetValue()).length());
    firstInfo.SetEraseLength(firstLength);
    auto spanIndex = firstInfo.GetSpanIndex();
    richEditorPattern->FixMoveDownChange(changeValue, 0);
    EXPECT_EQ(spanIndex, firstInfo.GetSpanIndex());
}

/**
 * @tc.name: BeforeUndo001
 * @tc.desc: test BeforeUndo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, BeforeUndo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    RichEditorChangeValue changeValue;
    int32_t innerPosition = 0;
    RichEditorPattern::OperationRecord record;
    record.addText = "test123\n";
    record.afterCaretPosition = 1;
    /**
     * @tc.steps: step2. change parameters and call function.
     */
    record.deleteCaretPostion = 0;
    richEditorPattern->BeforeUndo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
    /**
     * @tc.steps: step3. change parameters and call function.
     */
    record.deleteCaretPostion = -1;
    record.deleteText = "test\n";
    richEditorPattern->BeforeUndo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
}

/**
 * @tc.name: BeforeRedo001
 * @tc.desc: test BeforeRedo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, BeforeRedo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    RichEditorChangeValue changeValue;
    int32_t innerPosition = 0;
    RichEditorPattern::OperationRecord record;
    record.addText = "test123\n";
    record.beforeCaretPosition = 20;
    /**
     * @tc.steps: step2. change parameters and call function.
     */
    record.deleteCaretPostion = 0;
    richEditorPattern->BeforeRedo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
    /**
     * @tc.steps: step3. change parameters and call function.
     */
    record.deleteCaretPostion = -1;
    record.deleteText = "test\n";
    richEditorPattern->BeforeRedo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
}

/**
 * @tc.name: BeforeDrag001
 * @tc.desc: test BeforeDrag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, BeforeDrag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
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
    RichEditorChangeValue changeValue;
    int32_t innerPosition = 0;
    RichEditorPattern::OperationRecord record;
    record.addText = "test123\n";
    record.beforeCaretPosition = 20;
    /**
     * @tc.steps: step2. change parameters and call function.
     */
    richEditorPattern->isDragSponsor_ = false;
    richEditorPattern->BeforeDrag(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
    /**
     * @tc.steps: step3. change parameters and call function.
     */
    richEditorPattern->isDragSponsor_ = true;
    richEditorPattern->BeforeDrag(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
}

/**
 * @tc.name: GetThumbnailCallback003
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetThumbnailCallback003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetThumbnailCallback()(Offset(1.0f, 10.0f));
    EXPECT_EQ(richEditorPattern->dragNode_, nullptr);
}

/**
 * @tc.name: InitScrollablePattern002
 * @tc.desc: test InitScrollablePattern and more.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, InitScrollablePattern002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));

    richEditorPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();
    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), true);

    Offset Offset = { 1, 4 };
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    richEditorPattern->isTextChange_ = false;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    int32_t scroll_from_update = 1;
    richEditorPattern->scrollBar_ = nullptr;
    richEditorPattern->richTextRect_ = RectF(0, 4, 100, 61);
    richEditorPattern->contentRect_ = RectF(0, 7, 100, 60);
    richEditorPattern->UpdateScrollStateAfterLayout(true);
    EXPECT_TRUE(richEditorPattern->OnScrollCallback(10, scroll_from_update));

    auto offsetF = OffsetF(5.0f, 30.0f);
    richEditorPattern->isShowPlaceholder_ = false;
    richEditorPattern->MoveCaretToContentRect(offsetF, 40.0f);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);

    auto offsetFtemp = OffsetF(5.0f, 6.0f);
    richEditorPattern->MoveCaretToContentRect(offsetFtemp, 40.0f);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);
}

/**
 * @tc.name: GetPreviewTextDecorationColor001
 * @tc.desc: test GetPreviewTextDecorationColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetPreviewTextDecorationColor001, TestSize.Level1)
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
HWTEST_F(RichEditorPatternTestNg, GetPreviewTextUnderlineWidth001, TestSize.Level1)
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
 * @tc.name: ToGestureSpan001
 * @tc.desc: test ToGestureSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, ToGestureSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();

    spanItem->onClick = [](GestureEvent& info) {};
    spanItem->onLongPress = [](GestureEvent& info) {};

    auto spanString = AceType::MakeRefPtr<SpanString>(INIT_U16VALUE_1);
    ASSERT_NE(spanString, nullptr);
    auto start = spanItem->position - spanItem->content.length();
    auto end = spanItem->position;
    EXPECT_NE(spanString->ToGestureSpan(spanItem, start, end), nullptr);
}

/**
 * @tc.name: AddSpanByPasteData001
 * @tc.desc: test AddSpanByPasteData
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, AddSpanByPasteData001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanString = AceType::MakeRefPtr<SpanString>(INIT_U16VALUE_1);
    ASSERT_NE(spanString, nullptr);

    richEditorPattern->SetSpanStringMode(true);
    richEditorPattern->AddSpanByPasteData(spanString);
    richEditorPattern->SetSpanStringMode(false);

    auto start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpanByPasteData(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + testNumber1);

    auto imageSpanItem = AceType::MakeRefPtr<NG::ImageSpanItem>();
    spanString->AppendSpanItem(imageSpanItem);
    start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpanByPasteData(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + testNumber2);
}

/**
 * @tc.name: FinishTextPreview001
 * @tc.desc: test FinishTextPreview
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, FinishTextPreview001, TestSize.Level1)
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
        auto newHost1 = richEditorPattern->GetHost();
        auto newHost2 = richEditorPattern->GetHost();
        ASSERT_EQ(newHost1, newHost2);

        newHost1->children_.emplace_back(childFrameNode);
        newHost1->children_.emplace_back(childSpanNode);
        ASSERT_EQ(newHost1, newHost2);
    } while (0);

    richEditorPattern->InitPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    richEditorPattern->InitPreviewText(PREVIEW_TEXT_VALUE2, previewRange);
    richEditorPattern->FinishTextPreview();
    EXPECT_EQ(richEditorPattern->previewTextRecord_.previewContent, "");
}

/**
 * @tc.name: OnBackPressed001
 * @tc.desc: test OnBackPressed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, OnBackPressed001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);

    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->OnHandleMoveDone(rect, true);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), true);

    auto func = []() {};
    richEditorPattern->SetCustomKeyboard(func);
    richEditorPattern->RequestCustomKeyboard();
    EXPECT_EQ(richEditorPattern->OnBackPressed(), true);

    richEditorPattern->imeShown_ = true;
    EXPECT_EQ(richEditorPattern->OnBackPressed(), true);
}

/**
 * @tc.name: AddUdmfData001
 * @tc.desc: test AddUdmfData
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, AddUdmfData001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    ResultObject resultObject;
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    resultObject.type = SelectSpanType::TYPESYMBOLSPAN;
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    resultObject.type = SelectSpanType::TYPEIMAGE;
    resultObject.valueString = INIT_U16VALUE_1;
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    resultObject.type = SelectSpanType::TYPEIMAGE;
    resultObject.valueString.clear();
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    resultObject.type = SelectSpanType::TYPEIMAGE;
    resultObject.valuePixelMap = PixelMap::CreatePixelMap(nullptr);
    ASSERT_NE(resultObject.valuePixelMap, nullptr);
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);

    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    richEditorPattern->AddUdmfData(event);
    if (UdmfClient::GetInstance()->CreateUnifiedData()) {
        EXPECT_NE(event->GetData(), 0);
    } else {
        EXPECT_EQ(event->GetData(), 0);
    }
}

/**
 * @tc.name: ToBaselineOffsetSpan001
 * @tc.desc: test ToBaselineOffsetSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, ToBaselineOffsetSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->textLineStyle->UpdateBaselineOffset(Dimension(testNumber5, DimensionUnit::PX));
    auto spanString = AceType::MakeRefPtr<SpanString>(INIT_U16VALUE_1);
    ASSERT_NE(spanString, nullptr);
    auto start = spanItem->position - spanItem->content.length();
    auto end = spanItem->position;
    EXPECT_NE(spanString->ToBaselineOffsetSpan(spanItem, start, end), nullptr);
}

/**
 * @tc.name: ToTextShadowSpan001
 * @tc.desc: test ToTextShadowSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, ToTextShadowSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    Shadow textShadow1 = Shadow();
    Shadow textShadow2 = Shadow();
    textShadow1.SetColor(Color::RED);
    textShadow2.SetColor(Color::WHITE);
    std::vector<Shadow> shadows { textShadow1, textShadow2 };
    spanItem->fontStyle->UpdateTextShadow(shadows);
    auto spanString = AceType::MakeRefPtr<SpanString>(INIT_U16VALUE_1);
    ASSERT_NE(spanString, nullptr);
    auto start = spanItem->position - spanItem->content.length();
    auto end = spanItem->position;
    EXPECT_NE(spanString->ToTextShadowSpan(spanItem, start, end), nullptr);
}

/**
 * @tc.name: GetPreviewTextRects001
 * @tc.desc: test GetPreviewTextRects
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetPreviewTextRects001, TestSize.Level1)
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
 * @tc.name: DeleteSelectOperation001
 * @tc.desc: test DeleteSelectOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, DeleteSelectOperation001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorPattern::OperationRecord record;
    richEditorPattern->DeleteSelectOperation(&record);

    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->OnHandleMoveDone(rect, true);

    EXPECT_TRUE(richEditorPattern->selectOverlay_->SelectOverlayIsOn());
    richEditorPattern->DeleteSelectOperation(nullptr);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->SelectOverlayIsOn());
}

/**
 * @tc.name: IsLineSeparatorInLast001
 * @tc.desc: test IsLineSeparatorInLast
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, IsLineSeparatorInLast001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanNode = AceType::MakeRefPtr<SpanNode>(testSpanNodeId);
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanNode, nullptr);

    spanItem->content = u"ni\nhao";
    EXPECT_FALSE(richEditorPattern->IsLineSeparatorInLast(spanNode));

    spanItem->content = u"nihao\n";
    EXPECT_TRUE(richEditorPattern->IsLineSeparatorInLast(spanNode));
}

/**
 * @tc.name: GetRichEditorController001
 * @tc.desc: test GetRichEditorController
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetRichEditorController001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto controller = richEditorModel.GetRichEditorController();
    ASSERT_NE(controller, nullptr);
}

/**
 * @tc.name: BindSelectionMenu001
 * @tc.desc: test BindSelectionMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, BindSelectionMenu001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    std::function<void()> buildFunc = []() {
        callBack1 = 1;
        return;
    };
    TextSpanType textSpanType = TextSpanType::TEXT;
    TextResponseType textResponseType = TextResponseType::LONG_PRESS;
    SelectMenuParam menuParam { .onAppear = [](int32_t, int32_t) {}, .onDisappear = []() {} };
    richEditorModel.BindSelectionMenu(textSpanType, textResponseType, buildFunc, menuParam);
}

/**
 * @tc.name: OnHandleMove001
 * @tc.desc: test OnHandleMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, OnHandleMove001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);
    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->OnHandleMove(rect, true);
}

/**
 * @tc.name: UpdateSelectorOnHandleMove001
 * @tc.desc: test UpdateSelectorOnHandleMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, UpdateSelectorOnHandleMove001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);
    auto offsetF = OffsetF(5.0f, 30.0f);
    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->UpdateSelectorOnHandleMove(offsetF, true);
}
} // namespace