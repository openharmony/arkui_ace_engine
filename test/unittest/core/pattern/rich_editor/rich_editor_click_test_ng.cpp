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
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
} // namespace

class RichEditorClickTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorClickTestNg::SetUp()
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

void RichEditorClickTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorClickTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: HandleClickEvent001
 * @tc.desc: test handle click event
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, HandleClickEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    ParagraphStyle paragraphStyle;
    auto paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    richEditorPattern->pManager_->AddParagraph({ .paragraph = paragraph, .paragraphStyle = paragraphStyle });
    richEditorPattern->HandleClickEvent(info);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);

    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;

    richEditorPattern->isMouseSelect_ = true;
    richEditorPattern->hasClicked_ = false;
    richEditorPattern->clickInfo_.clear();
    richEditorPattern->HandleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 1);

    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->isMouseSelect_ = false;
    richEditorPattern->hasClicked_ = false;
    richEditorPattern->clickInfo_.clear();
    richEditorPattern->HandleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);

    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;

    richEditorPattern->isMouseSelect_ = true;
    richEditorPattern->hasClicked_ = false;
    richEditorPattern->clickInfo_.clear();
    richEditorPattern->HandleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 1);

    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->isMouseSelect_ = false;
    richEditorPattern->hasClicked_ = false;
    richEditorPattern->clickInfo_.clear();
    richEditorPattern->HandleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
}

/*
 * @tc.name: DoubleHandleClickEvent001
 * @tc.desc: test double click
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, DoubleHandleClickEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    richEditorPattern->isMouseSelect_ = false;
    richEditorPattern->caretVisible_ = true;
    richEditorPattern->HandleDoubleClickEvent(info);
    EXPECT_FALSE(richEditorPattern->caretVisible_);

    AddSpan(INIT_VALUE_3);
    info.localLocation_ = Offset(50, 50);
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->HandleDoubleClickEvent(info);
    EXPECT_NE(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_NE(richEditorPattern->textSelector_.destinationOffset, -1);
    EXPECT_NE(richEditorPattern->caretPosition_, -1);

    info.localLocation_ = Offset(0, 0);
    richEditorPattern->isMouseSelect_ = true;
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->HandleDoubleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 0);
}

/**
 * @tc.name: HandleEnabled
 * @tc.desc: test HandleEnabled
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, HandleEnabled, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create richEditorPattern and renderContext.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto renderContext = host->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step2. create richEditorEventHub and SetEnabled false.
     */
    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);

    /**
     * @tc.steps: step3. create richEditorTheme.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto richEditorTheme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(richEditorTheme));

    /**
     * @tc.steps: step4. test HandleEnabled.
     */
    richEditorPattern->HandleEnabled();
    EXPECT_TRUE(richEditorPattern->IsDisabled());
}

/**
 * @tc.name: MoveCaretOnLayoutSwap
 * @tc.desc: test MoveCaretOnLayoutSwap
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, MoveCaretOnLayoutSwap, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step2. add span
     */
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);

    /**
     * @tc.steps: step3. call the callback function without focus
     * @tc.expected: isTextChange_ is false
     */
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->moveDirection_ = MoveDirection::FORWARD;
    richEditorPattern->moveLength_ = 1;
    richEditorPattern->MoveCaretOnLayoutSwap();
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 1);
    EXPECT_EQ(richEditorPattern->moveLength_, 0);
    EXPECT_FALSE(richEditorPattern->isTextChange_);
}

/**
 * @tc.name: HandleBlurEvent
 * @tc.desc: test HandleBlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, HandleBlurEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step2. add span and select
     */
    AddSpan(u"test");
    richEditorPattern->textSelector_.Update(1, 3);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 3);

    /**
     * @tc.step: step3. Request focus and set blurReason_
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    focusHub->blurReason_ = BlurReason::FRAME_DESTROY;

    /**
     * @tc.step: step4. call the callback function
     */
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->HandleBlurEvent();
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
}

/**
 * @tc.name: CreateAndShowSingleHandle
 * @tc.desc: test CreateAndShowSingleHandle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, CreateAndShowSingleHandle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create richEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = -1;

    /**
     * @tc.steps: step2. Construct GestureEvent data and call CreatAndShowSingleHandle
     */
    ASSERT_NE(richEditorPattern->selectOverlay_, nullptr);
    richEditorPattern->CreateAndShowSingleHandle();
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
}

/**
 * @tc.name: HandleClickEvent002
 * @tc.desc: test RichEditorPattern HandleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, HandleClickEvent002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    ParagraphStyle paragraphStyle;
    auto paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    richEditorPattern->pManager_->AddParagraph({ .paragraph = paragraph, .paragraphStyle = paragraphStyle });
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    richEditorPattern->GetFocusHub()->focusType_ = FocusType::DISABLE;
    richEditorPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    richEditorPattern->HandleClickEvent(info);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: HandleSingleClickEvent001
 * @tc.desc: test RichEditorPattern HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, HandleSingleClickEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorPattern::OperationRecord record;
    richEditorPattern->DeleteSelectOperation(&record);

    RectF rect(0, 0, 5, 5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->selectOverlay_->OnHandleMoveDone(rect, true);

    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    ParagraphStyle paragraphStyle;
    auto paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    richEditorPattern->pManager_->AddParagraph({ .paragraph = paragraph, .paragraphStyle = paragraphStyle });
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    richEditorPattern->isMousePressed_ = true;

    richEditorPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = true;
    richEditorPattern->HandleSingleClickEvent(info);

    richEditorPattern->dataDetectorAdapter_->hasClickedAISpan_ = false;
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = false;
    richEditorPattern->HandleSingleClickEvent(info);

    richEditorPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = false;
    richEditorPattern->HandleSingleClickEvent(info);

    richEditorPattern->dataDetectorAdapter_->hasClickedAISpan_ = false;
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = true;
    richEditorPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: TestRichEditorHandleTripleClickEvent001
 * @tc.desc: test HandleTripleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, TestRichEditorHandleTripleClickEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    richEditorPattern->HandleTripleClickEvent(info);
    EXPECT_NE(richEditorPattern->GetFocusHub(), nullptr);
    EXPECT_EQ(richEditorPattern->GetFocusHub()->IsFocusable(), true);
}

/**
 * @tc.name: ClickAISpan001
 * @tc.desc: test RichEditorPattern ClickAISpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, ClickAISpan001, TestSize.Level1)
{
    AISpan aiSpan;
    aiSpan.start = 0;
    aiSpan.end = 10;
    aiSpan.content = "1234567";
    aiSpan.type = TextDataDetectType::PHONE_NUMBER;
    PointF textOffset = PointF(100, 100);
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    bool res = richEditorPattern->ClickAISpan(textOffset, aiSpan);
    EXPECT_EQ(res, false);
}

/**
 * @tc.name: ClickAISpan002
 * @tc.desc: Test ClickAISpan function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, ClickAISpan002, TestSize.Level1)
{
    PointF textOffset = {100.0, 100.0};
    AISpan aiSpan = {0, 10, "Test", TextDataDetectType::PHONE_NUMBER};
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.start = 3;
    info.end = 10;
    EXPECT_CALL(*mockParagraph, GetHeight())
        .WillRepeatedly(Return(10.0f));
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 100));
        }));
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->leftMousePress_ = true;
    EXPECT_TRUE(richEditorPattern->ClickAISpan(textOffset, aiSpan));
}

/**
 * @tc.name: ClickAISpan003
 * @tc.desc: Test ClickAISpan function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, ClickAISpan003, TestSize.Level1)
{
    PointF textOffset = {100.0, 100.0};
    AISpan aiSpan = {0, 10, "Test", TextDataDetectType::PHONE_NUMBER};
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.start = 3;
    info.end = 10;
    EXPECT_CALL(*mockParagraph, GetHeight())
        .WillRepeatedly(Return(10.0f));
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->leftMousePress_ = true;
    EXPECT_FALSE(richEditorPattern->ClickAISpan(textOffset, aiSpan));
}

/**
 * @tc.name: ClickAISpan004
 * @tc.desc: Test ClickAISpan function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, ClickAISpan004, TestSize.Level1)
{
    PointF textOffset = {100.0, 100.0};
    AISpan aiSpan = {0, 10, "Test", TextDataDetectType::PHONE_NUMBER};
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.start = 3;
    info.end = 10;
    EXPECT_CALL(*mockParagraph, GetHeight())
        .WillRepeatedly(Return(10.0f));
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->leftMousePress_ = false;
    EXPECT_FALSE(richEditorPattern->ClickAISpan(textOffset, aiSpan));
}

/**
 * @tc.name: ClickAISpan005
 * @tc.desc: Test ClickAISpan function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, ClickAISpan005, TestSize.Level1)
{
    PointF textOffset = {100.0, 100.0};
    AISpan aiSpan = {0, 10, "Test", TextDataDetectType::PHONE_NUMBER};
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.start = 3;
    info.end = 10;
    EXPECT_CALL(*mockParagraph, GetHeight())
        .WillRepeatedly(Return(10.0f));
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 100));
        }));
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_TRUE(richEditorPattern->ClickAISpan(textOffset, aiSpan));
}

} // namespace OHOS::Ace::NG