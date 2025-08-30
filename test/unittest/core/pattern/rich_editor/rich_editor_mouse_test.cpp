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
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t callBack1 = 0;
int32_t callBack2 = 0;
int32_t callBack3 = 0;
} // namespace

class RichEditorMouseTest : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorMouseTest::SetUp()
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

void RichEditorMouseTest::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorMouseTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}


/**
 * @tc.name: HandleMouseLeftButton001
 * @tc.desc: test HandleMouseLeftButton
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseLeftButton001, TestSize.Level1)
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
    auto& paragraphs = richEditorPattern->paragraphs_.paragraphs_;
    paragraphs.insert(paragraphs.begin(), { paragraph });
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
HWTEST_F(RichEditorMouseTest, HandleMouseLeftButton002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    AddSpan(INIT_VALUE_1);
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
HWTEST_F(RichEditorMouseTest, HandleMouseLeftButton003, TestSize.Level1)
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
 * @tc.name: OnHover001
 * @tc.desc: test on hover
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, OnHover001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto id = host->GetId();
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    HoverInfo hoverInfo;
    richEditorPattern->OnHover(true, hoverInfo);
    auto mouseStyleManager = pipeline->eventManager_->GetMouseStyleManager();
    EXPECT_EQ(mouseStyleManager->mouseStyleNodeId_.value(), id);
    richEditorPattern->OnHover(false, hoverInfo);
    EXPECT_FALSE(mouseStyleManager->mouseStyleNodeId_.has_value());
}

/**
 * @tc.name: MouseRightFocus001
 * @tc.desc: test MouseRightFocus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, MouseRightFocus001, TestSize.Level1)
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
 * @tc.name: MouseRightFocus002
 * @tc.desc: test MouseRightFocus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, MouseRightFocus002, TestSize.Level1)
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
 * @tc.name: MouseRightFocus003
 * @tc.desc: test MouseRightFocus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, MouseRightFocus003, TestSize.Level1)
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
    EXPECT_TRUE(richEditorPattern->HasFocus());
}

/**
 * @tc.name: MouseRightFocus004
 * @tc.desc: test MouseRightFocus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, MouseRightFocus004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = PREVIEW_TEXT_VALUE2;
    spanItem->spanItemType = SpanItemType::IMAGE;
    spanItem->position = 0;
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->spans_.push_back(spanItem);
    MouseInfo info;
    info.SetGlobalLocation({ 0, 0 });
    richEditorPattern->MouseRightFocus(info);
    EXPECT_NE(richEditorPattern->selectedType_, TextSpanType::IMAGE);
}

/**
 * @tc.name: MouseRightFocus005
 * @tc.desc: test MouseRightFocus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, MouseRightFocus005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = PREVIEW_TEXT_VALUE2;
    spanItem->spanItemType = SpanItemType::NORMAL;
    spanItem->position = 0;
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->spans_.push_back(spanItem);
    MouseInfo info;
    info.SetGlobalLocation({ 0, 0 });
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    richEditorPattern->previewLongPress_ = true;
    focusHub->RequestFocusImmediately();
    EXPECT_EQ(richEditorPattern->isEditing_, false);
    richEditorPattern->MouseRightFocus(info);
    EXPECT_EQ(richEditorPattern->isEditing_, true);
}

/**
 * @tc.name: MouseRightFocus006
 * @tc.desc: test MouseRightFocus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, MouseRightFocus006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(u"test1");
    AddImageSpan();
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    richEditorPattern->textSelector_.Update(4, 5);
    MouseInfo info;
    richEditorPattern->MouseRightFocus(info);
    EXPECT_TRUE(richEditorPattern->textSelector_.SelectNothing());
}

/**
 * @tc.name: RichEditorPatternTestInitMouseEvent001
 * @tc.desc: test InitMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, RichEditorPatternTestInitMouseEvent001, TestSize.Level1)
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
        CHECK_NULL_CONTINUE(input);
        (*input)(true);
    }

    ASSERT_EQ(richEditorPattern->mouseEventInitialized_, true);
}

/**
 * @tc.name: HandleMouseRightButton001
 * @tc.desc: test HandleMouseRightButton
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseRightButton001, TestSize.Level1)
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

/**
 * @tc.name: HandleMouseRightButton002
 * @tc.desc: test HandleMouseRightButton
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseRightButton002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::DISABLE;
    MouseInfo info;
    richEditorPattern->HandleMouseRightButton(info);
    EXPECT_FALSE(focusHub->IsFocusable());
}


/**
 * @tc.name: HandleMouseRightButton003
 * @tc.desc: test HandleMouseRightButton
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseRightButton003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    EXPECT_NE(richEditorPattern->GetFocusHub(), nullptr);
    EXPECT_EQ(richEditorPattern->GetFocusHub()->IsFocusable(), true);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    MouseInfo info;
    info.action_ = MouseAction::RELEASE;
    info.button_ = MouseButton::EXTRA_BUTTON;
    richEditorPattern->textSelector_.baseOffset = -2;
    richEditorPattern->textSelector_.destinationOffset = -3;
    richEditorPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    richEditorPattern->HandleMouseRightButton(info);
    EXPECT_FALSE(richEditorPattern->dataDetectorAdapter_->hasClickedAISpan_);
    /**
     * @tc.steps: step3. change parameter and call function.
     */
    info.globalLocation_.deltaX_ = 50.0;
    info.globalLocation_.deltaY_ = 150.0;
    richEditorPattern->textSelector_.baseOffset = 10;
    richEditorPattern->textSelector_.destinationOffset = 50;
    richEditorPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->HandleMouseRightButton(info);
    EXPECT_FALSE(richEditorPattern->dataDetectorAdapter_->hasClickedAISpan_);
}


/**
 * @tc.name: HandleMouseRightButton004
 * @tc.desc: test HandleMouseRightButton
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseRightButton004, TestSize.Level1)
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
 * @tc.name: HandleMouseLeftButtonMove001
 * @tc.desc: test HandleMouseLeftButtonMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseLeftButtonMove001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_NE(richEditorPattern->GetFocusHub(), nullptr);
    EXPECT_EQ(richEditorPattern->GetFocusHub()->IsFocusable(), true);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    MouseInfo info;
    info.action_ = MouseAction::RELEASE;
    info.button_ = MouseButton::EXTRA_BUTTON;
    richEditorPattern->blockPress_ = true;
    richEditorPattern->leftMousePress_ = false;
    richEditorPattern->HandleMouseLeftButtonMove(info);
    EXPECT_FALSE(richEditorPattern->isMouseSelect_);
    /**
     * @tc.steps: step3. change parameter and call function.
     */
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = true;
    richEditorPattern->blockPress_ = false;
    richEditorPattern->leftMousePress_ = true;
    richEditorPattern->textSelector_.Update(0, 0);
    richEditorPattern->HandleMouseLeftButtonMove(info);
    EXPECT_TRUE(richEditorPattern->isMouseSelect_);
    /**
     * @tc.steps: step4. change parameter and call function.
     */
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = false;
    focusHub->currentFocus_ = false;
    richEditorPattern->blockPress_ = false;
    richEditorPattern->leftMousePress_ = true;
    richEditorPattern->HandleMouseLeftButtonMove(info);
    EXPECT_TRUE(richEditorPattern->isMouseSelect_);
    /**
     * @tc.steps: step5. change parameter and call function.
     */
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = true;
    focusHub->currentFocus_ = true;
    richEditorPattern->blockPress_ = false;
    richEditorPattern->leftMousePress_ = true;
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 3;
    richEditorPattern->HandleMouseLeftButtonMove(info);
    EXPECT_TRUE(richEditorPattern->isMouseSelect_);
}


/**
 * @tc.name: HandleAISpanHoverEvent001
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleAISpanHoverEvent001, TestSize.Level1)
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
HWTEST_F(RichEditorMouseTest, HandleAISpanHoverEvent002, TestSize.Level1)
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
HWTEST_F(RichEditorMouseTest, HandleAISpanHoverEvent003, TestSize.Level1)
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
HWTEST_F(RichEditorMouseTest, HandleAISpanHoverEvent004, TestSize.Level1)
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
HWTEST_F(RichEditorMouseTest, HandleAISpanHoverEvent005, TestSize.Level1)
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
HWTEST_F(RichEditorMouseTest, HandleAISpanHoverEvent006, TestSize.Level1)
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
HWTEST_F(RichEditorMouseTest, HandleAISpanHoverEvent007, TestSize.Level1)
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
HWTEST_F(RichEditorMouseTest, HandleAISpanHoverEvent008, TestSize.Level1)
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
HWTEST_F(RichEditorMouseTest, HandleAISpanHoverEvent009, TestSize.Level1)
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
HWTEST_F(RichEditorMouseTest, HandleAISpanHoverEvent010, TestSize.Level1)
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
 * @tc.name: HandleMouseLeftButtonPress001
 * @tc.desc: test HandleMouseLeftButtonPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseLeftButtonPress001, TestSize.Level1)
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
HWTEST_F(RichEditorMouseTest, HandleMouseLeftButtonPress002, TestSize.Level1)
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
HWTEST_F(RichEditorMouseTest, HandleMouseLeftButtonPress003, TestSize.Level1)
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
 * @tc.name: HandleMouseEvent001
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseEvent001, TestSize.Level1)
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
HWTEST_F(RichEditorMouseTest, HandleMouseEvent002, TestSize.Level1)
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
 * @tc.name: HandleMouseEvent003
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto scrollBar = richEditorPattern->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    scrollBar->isHover_ = true;
    scrollBar->isPressed_ = true;
    MouseInfo info;
    richEditorPattern->HandleMouseEvent(info);
    auto mouseStyleManager = pipeline->eventManager_->GetMouseStyleManager();
    EXPECT_TRUE(mouseStyleManager->mouseStyleNodeId_.has_value());
}

/**
 * @tc.name: HandleMouseEvent004
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseEvent004, TestSize.Level1)
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
 * @tc.name: HandleMouseEvent005
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseEvent005, TestSize.Level1)
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

    richEditorPattern->textResponseType_ = TextResponseType::RIGHT_CLICK;
    richEditorPattern->selectOverlay_->ProcessOverlay({ .animation = false });
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: HandleMouseEvent006
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseEvent006, TestSize.Level1)
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
 * @tc.name: HandleMouseEvent007
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseEvent007, TestSize.Level1)
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
 * @tc.name: HandleMouseEvent008
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseEvent008, TestSize.Level1)
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
 * @tc.name: HandleMouseEvent009
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseEvent009, TestSize.Level1)
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
 * @tc.name: MouseDoubleClickParagraphEnd001
 * @tc.desc: test RichEditorPattern MouseDoubleClickParagraphEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, MouseDoubleClickParagraphEnd001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan("TEST123");
    std::u16string content = u"TEST123";
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(content);
    richEditorPattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));

    richEditorPattern->typingStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = std::nullopt;
    richEditorPattern->InsertValueInStyledString(content);

    richEditorPattern->caretUpdateType_ = CaretUpdateType::DOUBLE_CLICK;
    richEditorPattern->sourceType_ = SourceType::MOUSE;
    int32_t index = 7;
    int32_t index2 = 2;
    richEditorPattern->MouseDoubleClickParagraphEnd(index2);
    richEditorPattern->MouseDoubleClickParagraphEnd(index);
    EXPECT_EQ(richEditorPattern->GetParagraphEndPosition(index), 7);
}

/**
 * @tc.name: OnPlaceholderHover001
 * @tc.desc: test OnPlaceholderHover
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, OnPlaceholderHover001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->currentMouseStyle_ = MouseFormat::DEFAULT;
    richEditorPattern->OnPlaceholderHover(true);
    EXPECT_NE(richEditorPattern->currentMouseStyle_, MouseFormat::TEXT_CURSOR);

    richEditorPattern->OnPlaceholderHover(false);
    EXPECT_EQ(richEditorPattern->currentMouseStyle_, MouseFormat::TEXT_CURSOR);
}

/**
 * @tc.name: HandleMouseLeftButtonRelease001
 * @tc.desc: test HandleMouseLeftButtonRelease
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseLeftButtonRelease001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = true;
    richEditorPattern->mouseStatus_ = MouseStatus::PRESSED;
    richEditorPattern->status_ = Status::ON_DROP;
    MouseInfo info;
    richEditorPattern->HandleMouseLeftButtonRelease(info);
    EXPECT_FALSE(richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_);
}

/**
 * @tc.name: HandleMouseLeftButtonRelease002
 * @tc.desc: test HandleMouseLeftButtonRelease
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseLeftButtonRelease002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    richEditorPattern->showSelect_ = false;
    richEditorPattern->HandleMouseLeftButtonRelease(info);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: HandleMouseLeftButtonRelease003
 * @tc.desc: test HandleMouseLeftButtonRelease
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseLeftButtonRelease003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = true;
    richEditorPattern->mouseStatus_ = MouseStatus::MOVE;
    richEditorPattern->status_ = Status::ON_DROP;
    richEditorPattern->HandleMouseLeftButtonRelease(info);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: HandleMouseLeftButtonRelease004
 * @tc.desc: test HandleMouseLeftButtonRelease
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseLeftButtonRelease004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = true;
    richEditorPattern->mouseStatus_ = MouseStatus::MOVE;
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->HandleMouseLeftButtonRelease(info);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: HandleMouseLeftButtonRelease005
 * @tc.desc: test HandleMouseLeftButtonRelease
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleMouseLeftButtonRelease005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = true;
    richEditorPattern->mouseStatus_ = MouseStatus::MOVE;
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->isEditing_ = false;
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    MouseInfo info;
    richEditorPattern->HandleMouseLeftButtonRelease(info);

    EXPECT_TRUE(richEditorPattern->isEditing_);
}

/**
 * @tc.name: OnHandleMouseEvent001
 * @tc.desc: test OnHandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, OnHandleMouseEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo event;
    event.SetAction(MouseAction::PRESS);
    richEditorPattern->selectOverlay_->OnHandleMouseEvent(event);
    EXPECT_EQ(event.GetAction(), MouseAction::PRESS);
}

/**
 * @tc.name: OnHandleMouseEvent002
 * @tc.desc: test OnHandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, OnHandleMouseEvent002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo event;
    event.SetAction(MouseAction::RELEASE);
    richEditorPattern->selectOverlay_->OnHandleMouseEvent(event);
    EXPECT_EQ(event.GetAction(), MouseAction::RELEASE);
}

/**
 * @tc.name: AdjustMouseLocalOffset
 * @tc.desc: test AdjustMouseLocalOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, AdjustMouseLocalOffset, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(140.0f));
    auto offsetStart = Offset(0, 0);
    auto offsetEnd = Offset(100, 200);
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(offsetStart, _)).WillRepeatedly(Return(0));
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(offsetEnd, _)).WillRepeatedly(Return(6));
    PositionWithAffinity defaultPositionWithAffinity(0, TextAffinity::DOWNSTREAM);
    EXPECT_CALL(*paragraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(defaultPositionWithAffinity));
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 6 });

    MouseInfo info;
    info.localLocation_ = Offset(0, 0);
    info.globalLocation_ = Offset(0, 0);
    richEditorPattern->HandleMouseLeftButtonPress(info);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
    richEditorPattern->textSelector_.Update(3, 3);
    richEditorPattern->HandleMouseLeftButtonMove(info);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 3);

    richEditorPattern->ResetSelection();
    info.localLocation_ = Offset(50, 200);
    info.globalLocation_ = Offset(50, 200);
    richEditorPattern->HandleMouseLeftButtonPress(info);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
    richEditorPattern->textSelector_.Update(3, 3);
    richEditorPattern->HandleMouseLeftButtonMove(info);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 3);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 6);
}

/**
 * @tc.name: HandleImageHoverEventTest001
 * @tc.desc: test HandleImageHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMouseTest, HandleImageHoverEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::MOVE);
    mouseInfo.SetLocalLocation(MOUSE_LOCAL_LOCATION);
    richEditorPattern->isMousePressed_ = false;
    OffsetF frameOffset{ 0.0f, 0.0f };
    SizeF frameSize{ 10.0f, 10.0f };

    WeakPtr<ImageSpanNode> hoverableNode1;

    auto imageSpanNode2 = AceType::MakeRefPtr<ImageSpanNode>(V2::IMAGE_ETS_TAG, 0);
    WeakPtr<ImageSpanNode> hoverableNode2 = imageSpanNode2;

    auto imageSpanNode3 = AceType::MakeRefPtr<ImageSpanNode>(V2::IMAGE_ETS_TAG, 0);
    imageSpanNode3->SetImageItem(nullptr);
    WeakPtr<ImageSpanNode> hoverableNode3 = imageSpanNode3;
    
    auto imageSpanNode4 = AceType::MakeRefPtr<ImageSpanNode>(V2::IMAGE_ETS_TAG, 0);
    imageSpanNode4->GetSpanItem()->onHover_ = [](bool inHover, HoverInfo& info) {};
    WeakPtr<ImageSpanNode> hoverableNode4 = imageSpanNode4;
    
    auto imageSpanNode5 = AceType::MakeRefPtr<ImageSpanNode>(V2::IMAGE_ETS_TAG, 0);
    imageSpanNode5->GetSpanItem()->onHover_ = [](bool inHover, HoverInfo& info) {};
    imageSpanNode5->GetGeometryNode()->SetFrameOffset(frameOffset);
    imageSpanNode5->GetGeometryNode()->SetFrameSize(frameSize);
    WeakPtr<ImageSpanNode> hoverableNode5 = imageSpanNode5;

    richEditorPattern->hoverableNodes.push_back(hoverableNode1);
    richEditorPattern->hoverableNodes.push_back(hoverableNode2);
    richEditorPattern->hoverableNodes.push_back(hoverableNode3);
    richEditorPattern->hoverableNodes.push_back(hoverableNode4);
    richEditorPattern->hoverableNodes.push_back(hoverableNode5);

    richEditorPattern->lastHoverSpanItem_ = nullptr;
    richEditorPattern->HandleImageHoverEvent(mouseInfo);

    richEditorPattern->lastHoverSpanItem_ = imageSpanNode4->GetSpanItem();
    richEditorPattern->HandleImageHoverEvent(mouseInfo);
}

}