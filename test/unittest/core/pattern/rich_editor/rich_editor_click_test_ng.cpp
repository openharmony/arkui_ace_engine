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
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
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
 * @tc.name: OnVisibleChange
 * @tc.desc: test OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, OnVisibleChange, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richeditor pattern and add text span
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step2. add text span and Select text
     */
    AddSpan(INIT_VALUE_1);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 1);
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->textSelector_ = TextSelector(0, 2);

    /**
     * @tc.steps: step3. test OnVisibleChange
     */
    richEditorPattern->OnVisibleChange(false);
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    EXPECT_FALSE(richEditorPattern->caretTwinkling_);

    /**
     * @tc.steps: step4. change value and test again
     */
    richEditorPattern->caretTwinkling_ = true;
    richEditorPattern->caretVisible_ = true;
    richEditorPattern->OnVisibleChange(true);
    EXPECT_FALSE(richEditorPattern->caretVisible_);
    EXPECT_FALSE(richEditorPattern->caretTwinkling_);
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
 * @tc.name: SetCaretOffset
 * @tc.desc: test SetCaretOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, SetCaretOffset, TestSize.Level1)
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
    AddSpan(u"test");
    EXPECT_FALSE(richEditorPattern->caretVisible_);

    /**
     * @tc.step: step3. Request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.steps: step4. call the callback function
     */
    richEditorPattern->SetCaretOffset(2);
    EXPECT_TRUE(richEditorPattern->caretTwinkling_);
    EXPECT_TRUE(richEditorPattern->caretVisible_);
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
 * @tc.name: JudgeContentDraggable
 * @tc.desc: test JudgeContentDraggable
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, JudgeContentDraggable, TestSize.Level1)
{
    /**
     * @tc.step: step1. Get frameNode and pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.step: step2. Verify that JudgeContentDraggable was executed successfully
     */
    bool testSelectAreaVisible = richEditorPattern->JudgeContentDraggable();
    EXPECT_FALSE(testSelectAreaVisible);
}
} // namespace OHOS::Ace::NG