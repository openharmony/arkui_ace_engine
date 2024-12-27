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
int32_t callBack1 = 0;
int32_t callBack2 = 0;
int32_t callBack3 = 0;
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
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);

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
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);

    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->isMouseSelect_ = false;
    richEditorPattern->hasClicked_ = false;
    richEditorPattern->clickInfo_.clear();
    richEditorPattern->HandleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
}

/**
 * @tc.name: HandleMouseLeftButton001
 * @tc.desc: test HandleMouseLeftButton
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, HandleMouseLeftButton001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    MouseInfo mouseInfo;
    mouseInfo.action_ = MouseAction::MOVE;
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();

    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    richEditorPattern->leftMousePress_ = false;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::NONE);

    auto paragraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(0));
    richEditorPattern->paragraphs_.paragraphs_.push_front({ paragraph });
    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    richEditorPattern->blockPress_ = false;
    richEditorPattern->leftMousePress_ = true;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::MOVE);

    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    richEditorPattern->isFirstMouseSelect_ = true;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::MOVE);

    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    richEditorPattern->isFirstMouseSelect_ = false;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::MOVE);
}

/**
 * @tc.name: HandleMouseLeftButton002
 * @tc.desc: test HandleMouseLeftButton
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, HandleMouseLeftButton002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    AddSpan(INIT_U16VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo mouseInfo;
    mouseInfo.action_ = MouseAction::RELEASE;
    mouseInfo.SetGlobalLocation(MOUSE_GLOBAL_LOCATION);
    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::RELEASED);
    richEditorPattern->textSelector_ = TextSelector(0, 2);
    std::vector<TextSpanType> selectType = { TextSpanType::TEXT, TextSpanType::IMAGE, TextSpanType::MIXED };
    SelectOverlayInfo selectInfo;
    selectInfo.isUsingMouse = true;
    for (int32_t i = 0; i < static_cast<int32_t>(selectType.size()); i++) {
        richEditorPattern->selectedType_ = selectType[i];
        richEditorPattern->HandleMouseLeftButton(mouseInfo);
        EXPECT_NE(richEditorPattern->selectionMenuOffsetByMouse_.GetX(),
            static_cast<float>(mouseInfo.GetGlobalLocation().GetX()));
        EXPECT_NE(richEditorPattern->selectionMenuOffsetByMouse_.GetY(),
            static_cast<float>(mouseInfo.GetGlobalLocation().GetY()));
    }
    std::function<void()> buildFunc = []() {
        callBack1 = 1;
        return;
    };
    std::function<void(int32_t, int32_t)> onAppear = [](int32_t a, int32_t b) {
        callBack2 = 2;
        return;
    };
    std::function<void()> onDisappear = []() {
        callBack3 = 3;
        return;
    };
    richEditorPattern->mouseStatus_ = MouseStatus::MOVE;
    for (int32_t i = 0; i < static_cast<int32_t>(selectType.size()); i++) {
        richEditorPattern->selectedType_ = selectType[i];
        auto key = std::make_pair(selectType[i], TextResponseType::SELECTED_BY_MOUSE);
        std::shared_ptr<SelectionMenuParams> params1 = std::make_shared<SelectionMenuParams>(
            selectType[i], buildFunc, onAppear, onDisappear, TextResponseType::SELECTED_BY_MOUSE);
        richEditorPattern->selectionMenuMap_[key] = params1;
        richEditorPattern->mouseStatus_ = MouseStatus::MOVE;
        richEditorPattern->HandleMouseLeftButton(mouseInfo);
        EXPECT_EQ(richEditorPattern->selectionMenuOffsetByMouse_.GetX(),
            static_cast<float>(mouseInfo.GetGlobalLocation().GetX()));
        EXPECT_EQ(richEditorPattern->selectionMenuOffsetByMouse_.GetY(),
            static_cast<float>(mouseInfo.GetGlobalLocation().GetY()));
    }
}

/**
 * @tc.name: HandleMouseLeftButton003
 * @tc.desc: test HandleMouseLeftButton
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, HandleMouseLeftButton003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    MouseInfo mouseInfo;
    mouseInfo.action_ = MouseAction::MOVE;
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();

    mouseInfo.action_ = MouseAction::PRESS;
    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    mouseInfo.SetGlobalLocation(Offset(2, 5));
    richEditorPattern->textSelector_.baseOffset = 3;
    richEditorPattern->textSelector_.destinationOffset = 4;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::PRESSED);

    mouseInfo.action_ = MouseAction::PRESS;
    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    mouseInfo.SetGlobalLocation(Offset(2, 5));
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 8;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::PRESSED);

    mouseInfo.action_ = MouseAction::RELEASE;
    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::RELEASED);

    mouseInfo.action_ = MouseAction::NONE;
    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::NONE);
}

/**
 * @tc.name: HandleMouseRightButton001
 * @tc.desc: test HandleMouseRightButton
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, HandleMouseRightButton001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ClipboardProxy::GetInstance()->SetDelegate(nullptr);

    MouseInfo mouseInfo;
    mouseInfo.action_ = MouseAction::PRESS;
    richEditorPattern->isMousePressed_ = false;
    richEditorPattern->HandleMouseRightButton(mouseInfo);
    EXPECT_TRUE(richEditorPattern->isMousePressed_);

    mouseInfo.action_ = MouseAction::HOVER;
    richEditorPattern->isMousePressed_ = false;
    richEditorPattern->HandleMouseRightButton(mouseInfo);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);

    mouseInfo.action_ = MouseAction::RELEASE;
    richEditorPattern->isMousePressed_ = true;
    mouseInfo.SetGlobalLocation({ 1, 5 });
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->HandleMouseRightButton(mouseInfo);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);

    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 3;
    richEditorPattern->HandleMouseRightButton(mouseInfo);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);

    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 9;
    richEditorPattern->HandleMouseRightButton(mouseInfo);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);
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
    AddSpan(INIT_U16VALUE_1);
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    richEditorPattern->isMouseSelect_ = false;
    richEditorPattern->caretVisible_ = true;
    richEditorPattern->HandleDoubleClickEvent(info);
    EXPECT_FALSE(richEditorPattern->caretVisible_);

    AddSpan(INIT_U16VALUE_3);
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
 * @tc.name: HandleMouseEvent001
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, HandleMouseEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    MouseInfo mouseInfo;

    mouseInfo.action_ = MouseAction::PRESS;
    mouseInfo.button_ = MouseButton::LEFT_BUTTON;
    richEditorPattern->isMousePressed_ = false;
    richEditorPattern->HandleMouseEvent(mouseInfo);
    EXPECT_TRUE(richEditorPattern->isMousePressed_);

    mouseInfo.button_ = MouseButton::RIGHT_BUTTON;
    richEditorPattern->isMousePressed_ = false;
    richEditorPattern->HandleMouseEvent(mouseInfo);
    EXPECT_TRUE(richEditorPattern->isMousePressed_);

    mouseInfo.button_ = MouseButton::BACK_BUTTON;
    richEditorPattern->isMousePressed_ = false;
    richEditorPattern->HandleMouseEvent(mouseInfo);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);
}

/**
 * @tc.name: HandleMouseEvent002
 * @tc.desc: test handle mouse event
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, HandleMouseEvent002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    richEditorPattern->HandleMouseEvent(info);
    info.action_ = MouseAction::PRESS;
    richEditorPattern->HandleMouseEvent(info);
    EXPECT_TRUE(richEditorPattern->isMousePressed_);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::MOVE;
    richEditorPattern->leftMousePress_ = true;
    richEditorPattern->HandleMouseEvent(info);
    info.action_ = MouseAction::PRESS;
    richEditorPattern->HandleMouseEvent(info);
    info.action_ = MouseAction::RELEASE;
    EXPECT_TRUE(richEditorPattern->isMousePressed_);
    richEditorPattern->HandleMouseEvent(info);
    EXPECT_FALSE(richEditorPattern->blockPress_);
    EXPECT_FALSE(richEditorPattern->leftMousePress_);
    EXPECT_FALSE(richEditorPattern->isMouseSelect_);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);
    EXPECT_TRUE(richEditorPattern->isFirstMouseSelect_);
}

/**
 * @tc.name: MouseRightFocus001
 * @tc.desc: test MouseRightFocus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorClickTestNg, MouseRightFocus001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(u"test1");
    AddImageSpan();
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->moveLength_ = 0;
    MouseInfo info;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 0;
    richEditorPattern->MouseRightFocus(info);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
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
    AddSpan(INIT_U16VALUE_1);
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
    AddSpan(INIT_U16VALUE_1);
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