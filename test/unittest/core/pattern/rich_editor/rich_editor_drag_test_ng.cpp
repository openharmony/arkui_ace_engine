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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
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
} // namespace

class RichEditorDragTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorDragTestNg::SetUp()
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

void RichEditorDragTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorDragTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: RichEditorDragTest001
 * @tc.desc: test the drag of RichEditor without developer's onDragStart function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, RichEditorDragTest001, TestSize.Level1)
{
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    host->draggable_ = true;
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gesture = host->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    EXPECT_TRUE(gesture->GetTextDraggable());
    gesture->SetIsTextDraggable(true);
    pattern->InitDragDropEvent();
    EXPECT_TRUE(eventHub->HasDefaultOnDragStart());
    auto controller = pattern->GetRichEditorController();
    ASSERT_NE(controller, nullptr);
    TextStyle style;
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    auto index = controller->AddTextSpan(options);
    EXPECT_EQ(index, 0);
    ImageSpanOptions imageOptions;
    imageOptions.image = IMAGE_VALUE;
    controller->AddImageSpan(imageOptions);
    pattern->textSelector_.Update(0, 6);
    auto onDragStart = eventHub->GetDefaultOnDragStart();
    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto dragDropInfo = onDragStart(event, "");
    EXPECT_EQ(dragDropInfo.extraInfo, "");
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
    EXPECT_EQ(pattern->status_, Status::DRAGGING);
    eventHub->FireOnDragMove(event, "");
    auto onDragEnd = eventHub->GetOnDragEnd();
    onDragEnd(event);
    EXPECT_EQ(pattern->status_, Status::NONE);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorDragTest002
 * @tc.desc: test the drag of RichEditor with developer's onDragStart function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, RichEditorDragTest002, TestSize.Level1)
{
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    host->draggable_ = true;
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gesture = host->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    EXPECT_TRUE(gesture->GetTextDraggable());
    gesture->SetIsTextDraggable(true);
    auto dragStart = [](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) -> NG::DragDropInfo {
        NG::DragDropInfo info;
        info.extraInfo = TEST_STR;
        return info;
    };
    eventHub->SetOnDragStart(std::move(dragStart));
    EXPECT_TRUE(eventHub->HasOnDragStart());
    pattern->InitDragDropEvent();
    EXPECT_TRUE(eventHub->HasDefaultOnDragStart());
    auto controller = pattern->GetRichEditorController();
    ASSERT_NE(controller, nullptr);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    controller->AddTextSpan(options);
    ImageSpanOptions imageOptions;
    imageOptions.image = IMAGE_VALUE;
    controller->AddImageSpan(imageOptions);
    pattern->textSelector_.Update(0, 6);
    auto onDragStart = eventHub->GetOnDragStart();
    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto dragDropInfo = onDragStart(event, "");
    EXPECT_EQ(dragDropInfo.extraInfo, TEST_STR);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 6);
    EXPECT_EQ(pattern->status_, Status::NONE);
    eventHub->FireOnDragMove(event, "");
    auto onDragEnd = eventHub->GetOnDragEnd();
    onDragEnd(event);
    EXPECT_EQ(pattern->status_, Status::NONE);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorDragTest003
 * @tc.desc: test the drag of RichEditor with developer's onDragDrop function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, RichEditorDragTest003, TestSize.Level1)
{
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    host->draggable_ = true;
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gesture = host->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    EXPECT_TRUE(gesture->GetTextDraggable());
    gesture->SetIsTextDraggable(true);
    pattern->InitDragDropEvent();
    EXPECT_TRUE(eventHub->HasDefaultOnDragStart());
    EXPECT_TRUE(eventHub->HasOnDrop());
    auto controller = pattern->GetRichEditorController();
    ASSERT_NE(controller, nullptr);
    TextStyle style;
    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    options.style = style;
    auto index = controller->AddTextSpan(options);
    EXPECT_EQ(index, 0);
    pattern->textSelector_.Update(0, 6);
    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->FireOnDrop(event, "");
    EXPECT_EQ(pattern->status_, Status::NONE);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorDragTest004
 * @tc.desc: test the drag of RichEditor with developer's HandleOnDragDropTextOperation function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, RichEditorDragTest004, TestSize.Level1)
{
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    host->draggable_ = true;
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gesture = host->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    EXPECT_TRUE(gesture->GetTextDraggable());
    gesture->SetIsTextDraggable(true);
    pattern->InitDragDropEvent();
    EXPECT_TRUE(eventHub->HasOnDrop());
    auto controller = pattern->GetRichEditorController();
    ASSERT_NE(controller, nullptr);
    TextStyle style;
    TextSpanOptions options;
    options.value = INIT_VALUE_1 + INIT_VALUE_1;
    options.style = style;
    auto index = controller->AddTextSpan(options);
    EXPECT_EQ(index, 0);
    pattern->dragRange_.first = 0;
    pattern->caretPosition_ = options.value.length();
    pattern->HandleOnDragDropTextOperation(INIT_VALUE_1, true);
    pattern->dragRange_.first = options.value.length();
    pattern->caretPosition_ = 0;
    pattern->HandleOnDragDropTextOperation(INIT_VALUE_1, true);
    EXPECT_EQ(pattern->status_, Status::NONE);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: OnDragEnd001
 * @tc.desc: test OnDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, OnDragEnd001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    bool isTestAddObject = false;
    ResultObject resultObject;
    if (richEditorPattern->recoverDragResultObjects_.empty()) {
        isTestAddObject = true;
        richEditorPattern->recoverDragResultObjects_.emplace_back(resultObject);
    }

    RefPtr<Ace::DragEvent> event = nullptr;
    richEditorPattern->showSelect_ = false;
    richEditorPattern->OnDragEnd(event);
    ASSERT_EQ(richEditorPattern->showSelect_, false);

    event = AceType::MakeRefPtr<Ace::DragEvent>();
    event->SetResult(DragRet::DRAG_SUCCESS);
    richEditorPattern->showSelect_ = false;
    richEditorPattern->OnDragEnd(event);
    ASSERT_EQ(richEditorPattern->showSelect_, false);

    if (isTestAddObject) {
        richEditorPattern->recoverDragResultObjects_.clear();
    }
}


/**
 * @tc.name: OnDragEnd002
 * @tc.desc: test OnDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, OnDragEnd002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    bool isTestAddObject = false;
    ResultObject resultObject;
    if (richEditorPattern->recoverDragResultObjects_.empty()) {
        isTestAddObject = true;
        richEditorPattern->recoverDragResultObjects_.emplace_back(resultObject);
    }

    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    richEditorPattern->showSelect_ = false;
    richEditorNode_.Reset();
    richEditorPattern->OnDragEnd(event);
    EXPECT_FALSE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: OnDragEnd003
 * @tc.desc: test OnDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, OnDragEnd003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    bool isTestAddObject = false;
    ResultObject resultObject;
    if (richEditorPattern->recoverDragResultObjects_.empty()) {
        isTestAddObject = true;
        richEditorPattern->recoverDragResultObjects_.emplace_back(resultObject);
    }

    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    richEditorPattern->showSelect_ = false;
    event->dragRet_ = DragRet::DRAG_SUCCESS;
    richEditorPattern->OnDragEnd(event);
    EXPECT_FALSE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: OnDragEnd004
 * @tc.desc: test OnDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, OnDragEnd004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    bool isTestAddObject = false;
    ResultObject resultObject;
    if (richEditorPattern->recoverDragResultObjects_.empty()) {
        isTestAddObject = true;
        richEditorPattern->recoverDragResultObjects_.emplace_back(resultObject);
    }

    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    richEditorPattern->showSelect_ = false;
    richEditorNode_->eventHub_->focusHub_->focusType_ = FocusType::DISABLE;
    richEditorPattern->OnDragEnd(event);
    EXPECT_FALSE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: HandleCursorOnDragEnded001
 * @tc.desc: test HandleCursorOnDragEnded
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleCursorOnDragEnded001, TestSize.Level1)
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
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    RefPtr<NotifyDragEvent> notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    EXPECT_NE(notifyDragEvent, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->isCursorAlwaysDisplayed_ = false;
    richEditorPattern->HandleCursorOnDragEnded(notifyDragEvent);
    EXPECT_EQ(richEditorPattern->caretTwinkling_, false);

    /**
     * @tc.steps: step3. change parameter and call function.
     */
    richEditorPattern->isCursorAlwaysDisplayed_ = true;

    focusHub->currentFocus_ = false;
    richEditorPattern->HandleCursorOnDragEnded(notifyDragEvent);
    EXPECT_EQ(richEditorPattern->isCursorAlwaysDisplayed_, false);

    /**
     * @tc.steps: step4. change parameter and call function.
     */
    richEditorPattern->isCursorAlwaysDisplayed_ = true;
    focusHub->currentFocus_ = true;
    richEditorPattern->HandleCursorOnDragEnded(notifyDragEvent);
    EXPECT_EQ(richEditorPattern->isCursorAlwaysDisplayed_, false);
}


/**
 * @tc.name: HandleDraggableFlag001
 * @tc.desc: test HandleDraggableFlag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleDraggableFlag001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHubRefPtr = AceType::MakeRefPtr<EventHub>();
    auto eventHubWeakPtr = AceType::WeakClaim(AceType::RawPtr(eventHubRefPtr));
    richEditorNode_->eventHub_->gestureEventHub_ = AceType::MakeRefPtr<GestureEventHub>(eventHubWeakPtr);
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorNode_->eventHub_->gestureEventHub_->isTextDraggable_ = true;
    richEditorPattern->HandleDraggableFlag(true);
    EXPECT_FALSE(richEditorNode_->eventHub_->gestureEventHub_->isTextDraggable_);
}

/**
 * @tc.name: HandleDraggableFlag002
 * @tc.desc: test InsertValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleDraggableFlag002, TestSize.Level1)
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

    /**
     * @tc.steps: step3. select text
     */
    richEditorPattern->textSelector_.Update(1, 3);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 3);

    /**
     * @tc.steps: step4. test HandleDraggableFlag
     */
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->HandleDraggableFlag(true);
    auto gestureHub = richEditorPattern->GetGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_TRUE(richEditorPattern->JudgeContentDraggable());
    EXPECT_TRUE(gestureHub->GetIsTextDraggable());
}

} // namespace OHOS::Ace::NG