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
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"
#include "core/components_ng/pattern/text/span/tlv_util.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
int32_t testNumber0 = 0;
int32_t testNumber1 = 1;
int32_t testNumber3 = 3;
int32_t testNumber4 = 4;
int32_t testNumber5 = 5;
int32_t testFrameNodeId = 1;
} // namespace

class RichEditorDragTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    RefPtr<RichEditorPattern> GetRichEditorPattern();
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

RefPtr<RichEditorPattern> RichEditorDragTestNg::GetRichEditorPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

/**
 * @tc.name: RichEditorDragTest001
 * @tc.desc: test the drag of RichEditor without developer's onDragStart function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, RichEditorDragTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    host->draggable_ = true;
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
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
    pattern->isMousePressed_ = true;
    auto onDragEnd = eventHub->GetOnDragEnd();
    onDragEnd(event);
    EXPECT_EQ(pattern->status_, Status::NONE);
    EXPECT_FALSE(pattern->isMousePressed_);
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
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    host->draggable_ = true;
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
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
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    host->draggable_ = true;
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
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
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    host->draggable_ = true;
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
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

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::DRAG);
        changeReason = changeValue.changeReason_;
        return true;
    };
    model.SetOnWillChange(std::move(onWillChange));

    pattern->dragRange_.first = 0;
    pattern->caretPosition_ = options.value.length();
    pattern->HandleOnDragDropTextOperation(INIT_VALUE_1, true);
    EXPECT_EQ(changeReason, TextChangeReason::DRAG);
    pattern->dragRange_.first = options.value.length();
    pattern->caretPosition_ = 0;
    changeReason = TextChangeReason::UNKNOWN;
    pattern->HandleOnDragDropTextOperation(INIT_VALUE_1, true);
    EXPECT_EQ(changeReason, TextChangeReason::DRAG);
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
    richEditorNode_->focusHub_->focusType_ = FocusType::DISABLE;
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
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
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
    richEditorNode_->GetOrCreateEventHub<EventHub>()->gestureEventHub_ =
        AceType::MakeRefPtr<GestureEventHub>(eventHubWeakPtr);
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorNode_->GetOrCreateEventHub<EventHub>()->gestureEventHub_->isTextDraggable_ = true;
    richEditorPattern->HandleDraggableFlag(true);
    EXPECT_FALSE(richEditorNode_->GetOrCreateEventHub<EventHub>()->gestureEventHub_->isTextDraggable_);
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

/**
 * @tc.name: JudgeContentDraggable
 * @tc.desc: test JudgeContentDraggable
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, JudgeContentDraggable, TestSize.Level1)
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

/**
 * @tc.name: HandleOnDragDropTextOperation001
 * @tc.desc: test HandleOnDragDropTextOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleOnDragDropTextOperation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);

    auto temp = richEditorPattern->caretPosition_;
    richEditorPattern->HandleOnDragDropTextOperation(INIT_VALUE_1, false);
    EXPECT_NE(richEditorPattern->caretPosition_, temp);
}

/**
 * @tc.name: HandleOnDragDrop001
 * @tc.desc: test HandleOnDragDrop
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleOnDragDrop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<UnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->HandleOnDragDrop(event);
    EXPECT_NE(event->GetData(), nullptr);
}


/**
 * @tc.name: HandleOnDragDrop001
 * @tc.desc: test HandleOnDragDrop
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleOnDragDrop002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;

    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<UnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);

    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->HandleOnDragDrop(event);
    EXPECT_NE(event->GetData(), nullptr);
}


/**
 * @tc.name: RichEditorPatternTestClearDragDropEvent001
 * @tc.desc: test RichEditorPattern
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, RichEditorPatternTestClearDragDropEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->ClearDragDropEvent();

    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_EQ(eventHub->onDragStart_, nullptr);
}

/**
 * @tc.name: RichEditorPatternTestOnDragMove001
 * @tc.desc: test OnDragMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, RichEditorPatternTestOnDragMove001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
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
HWTEST_F(RichEditorDragTestNg, RichEditorPatternTestResetDragSpanItems001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->dragSpanItems_.clear();
    richEditorPattern->ResetDragSpanItems();

    auto firstItem = AceType::MakeRefPtr<ImageSpanItem>();
    firstItem->nodeId_ = testFrameNodeId;
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
 * @tc.name: HandleOnDragInsertStyledString001
 * @tc.desc: test HandleOnDragInsertStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleOnDragInsertStyledString001, TestSize.Level1)
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
HWTEST_F(RichEditorDragTestNg, HandleOnDragInsertStyledString002, TestSize.Level1)
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
HWTEST_F(RichEditorDragTestNg, HandleOnDragInsertStyledString003, TestSize.Level1)
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
 * @tc.name: JudgeContentDraggable001
 * @tc.desc: test JudgeContentDraggable
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, JudgeContentDraggable001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->copyOption_ = CopyOptions::None;
    EXPECT_EQ(richEditorPattern->IsSelected(), false);
    richEditorPattern->JudgeContentDraggable();

    richEditorPattern->copyOption_ = CopyOptions::InApp;
    EXPECT_EQ(richEditorPattern->IsSelected(), false);
    richEditorPattern->JudgeContentDraggable();

    AddSpan("test");
    richEditorPattern->textSelector_.Update(3, 4);
    EXPECT_EQ(richEditorPattern->IsSelected(), true);

    richEditorPattern->copyOption_ = CopyOptions::None;
    richEditorPattern->JudgeContentDraggable();

    richEditorPattern->textSelector_.Update(3, 4);
    EXPECT_EQ(richEditorPattern->IsSelected(), true);

    richEditorPattern->copyOption_ = CopyOptions::InApp;
    bool res = richEditorPattern->JudgeContentDraggable();

    EXPECT_EQ(res, true);
}

/**
 * @tc.name: HandleDraggableFlag003
 * @tc.desc: test HandleDraggableFlag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleDraggableFlag003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->HandleDraggableFlag(true);
    EXPECT_EQ(richEditorPattern->JudgeContentDraggable(), false);
}


/**
 * @tc.name: HandleOnDragDropStyledString001
 * @tc.desc: test HandleOnDragDropStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleOnDragDropStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<MockUnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();

    ASSERT_NE(unifiedData, nullptr);
    std::vector<uint8_t> expectedReturnUnint8_t = { 1, 2, 3 };

    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_END);

    UdmfClient* client = UdmfClient::GetInstance();
    MockUdmfClient* mockClient = static_cast<MockUdmfClient*>(client);
    EXPECT_CALL(*mockClient, GetSpanStringRecord(_)).WillRepeatedly(Return(expectedReturnUnint8_t));

    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->HandleOnDragDropStyledString(event);
    auto host = richEditorPattern->GetHost();
    EXPECT_TRUE(host->isRestoreInfoUsed_);
}

/**
 * @tc.name: HandleOnDragDropStyledString002
 * @tc.desc: test HandleOnDragDropStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleOnDragDropStyledString002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<MockUnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();

    ASSERT_NE(unifiedData, nullptr);
    std::vector<uint8_t> expectedReturnUnint8_t = { 1, 2, 3 };

    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_END);

    UdmfClient* client = UdmfClient::GetInstance();
    MockUdmfClient* mockClient = static_cast<MockUdmfClient*>(client);
    EXPECT_CALL(*mockClient, GetSpanStringRecord(_)).WillRepeatedly(Return(expectedReturnUnint8_t));

    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->HandleOnDragDropStyledString(event);
    EXPECT_NE(event->GetData(), nullptr);
    auto host = richEditorPattern->GetHost();
    EXPECT_FALSE(host->isRestoreInfoUsed_);
}

/**
 * @tc.name: HandleOnDragDropStyledString003
 * @tc.desc: test HandleOnDragDropStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleOnDragDropStyledString003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<MockUnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();

    ASSERT_NE(unifiedData, nullptr);
    std::vector<uint8_t> expectedReturnUnint8_t = { 1, 2, 3 };

    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_END);

    UdmfClient* client = UdmfClient::GetInstance();
    MockUdmfClient* mockClient = static_cast<MockUdmfClient*>(client);
    EXPECT_CALL(*mockClient, GetSpanStringRecord(_)).WillRepeatedly(Return(expectedReturnUnint8_t));

    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->HandleOnDragDropStyledString(event);
    EXPECT_NE(event->GetData(), nullptr);
    auto host = richEditorPattern->GetHost();
    EXPECT_FALSE(host->isRestoreInfoUsed_);
}

/**
 * @tc.name: HandleOnDragDropStyledString004
 * @tc.desc: test HandleOnDragDropStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleOnDragDropStyledString004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<UnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    std::vector<uint8_t> expectedReturnUnint8_t = { 1, 2, 3 };
    std::vector<std::string> expectedReturnString = { "some", "string", "content" };

    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_END);

    UdmfClient* client = UdmfClient::GetInstance();
    MockUdmfClient* mockClient = static_cast<MockUdmfClient*>(client);
    EXPECT_CALL(*mockClient, GetSpanStringRecord(_)).WillRepeatedly(Return(expectedReturnUnint8_t));
    EXPECT_CALL(*mockClient, GetPlainTextRecords(_)).WillRepeatedly(Return(expectedReturnString));

    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->HandleOnDragDropStyledString(event);
    EXPECT_NE(event->GetData(), nullptr);
    auto host = richEditorPattern->GetHost();
    EXPECT_FALSE(host->isRestoreInfoUsed_);
}

/**
 * @tc.name: HandleOnDragDropStyledString005
 * @tc.desc: test HandleOnDragDropStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleOnDragDropStyledString005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<UnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    std::vector<uint8_t> expectedReturnUnint8_t = { 1, 2, 3 };
    std::vector<std::string> expectedReturnString = { "some", "string", "content" };

    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_END);

    UdmfClient* client = UdmfClient::GetInstance();
    MockUdmfClient* mockClient = static_cast<MockUdmfClient*>(client);
    EXPECT_CALL(*mockClient, GetSpanStringRecord(_)).WillRepeatedly(Return(expectedReturnUnint8_t));
    EXPECT_CALL(*mockClient, GetPlainTextRecords(_)).WillRepeatedly(Return(expectedReturnString));

    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->HandleOnDragDropStyledString(event);
    auto host = richEditorPattern->GetContentHost();
    EXPECT_TRUE(host->isRestoreInfoUsed_);
}

/**
 * @tc.name: HandleOnDragDsropStyledString006
 * @tc.desc: test HandleOnDragDropStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleOnDragDropStyledString006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<UnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    std::vector<uint8_t> expectedReturnUnint8_t = { 1, 2, 3 };
    std::vector<std::string> expectedReturnString = { "" };

    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_END);

    UdmfClient* client = UdmfClient::GetInstance();
    MockUdmfClient* mockClient = static_cast<MockUdmfClient*>(client);
    EXPECT_CALL(*mockClient, GetSpanStringRecord(_)).WillRepeatedly(Return(expectedReturnUnint8_t));
    EXPECT_CALL(*mockClient, GetPlainTextRecords(_)).WillRepeatedly(Return(expectedReturnString));

    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->HandleOnDragDropStyledString(event);
    EXPECT_NE(event->GetData(), nullptr);
    auto host = richEditorPattern->GetHost();
    EXPECT_FALSE(host->isRestoreInfoUsed_);
}

/**
 * @tc.name: ResetDragOption001
 * @tc.desc: test ResetDragOption
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, ResetDragOption001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
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
 * @tc.name: HandleOnDragStatusCallback001
 * @tc.desc: test HandleOnDragStatusCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleOnDragStatusCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    RefPtr<NotifyDragEvent> notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    DragEventType dragEventType1 = DragEventType::MOVE;
    notifyDragEvent->SetX(10.0f);
    notifyDragEvent->SetY(20.0f);
    richEditorPattern->HandleOnDragStatusCallback(dragEventType1, notifyDragEvent);
    EXPECT_TRUE(richEditorPattern->isOnlyRequestFocus_);
}

/**
 * @tc.name: HandleCursorOnDragLeaved001
 * @tc.desc: test HandleCursorOnDragLeaved
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleCursorOnDragLeaved001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
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
HWTEST_F(RichEditorDragTestNg, HandleCursorOnDragMoved001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
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
 * @tc.name: BeforeDrag001
 * @tc.desc: test BeforeDrag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, BeforeDrag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    struct UpdateSpanStyle typingStyle;
    TextStyle textStyle(5);
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);
    RichEditorChangeValue changeValue;
    int32_t innerPosition = 0;
    RichEditorPattern::OperationRecord record;
    record.addText = u"test123\n";
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
 * @tc.name: SetSelfAndChildDraggableFalse001
 * @tc.desc: test SetSelfAndChildDraggableFalse
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, SetSelfAndChildDraggableFalse001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t nodeId = 2;
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<Pattern>();
    RefPtr<FrameNode> customNode = AceType::MakeRefPtr<FrameNode>(V2::IMAGE_ETS_TAG, nodeId, pattern, false, false);
    auto eventHub = customNode->GetOrCreateEventHub<EventHub>();
    RefPtr<EventHub> sharedEventHub = RefPtr<EventHub>(new EventHub());
    WeakPtr<EventHub> weakEventHub(sharedEventHub);
    eventHub->gestureEventHub_ = AceType::MakeRefPtr<GestureEventHub>(weakEventHub);
    eventHub->gestureEventHub_->isDragForbiddenForWholeSubTree_ = false;
    richEditorPattern->SetSelfAndChildDraggableFalse(customNode);
    EXPECT_TRUE(eventHub->gestureEventHub_->isDragForbiddenForWholeSubTree_);
}

/**
 * @tc.name: HandleDraggableFlag004
 * @tc.desc: test HandleDraggableFlag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleDraggableFlag004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHubRefPtr = AceType::MakeRefPtr<EventHub>();
    auto eventHubWeakPtr = AceType::WeakClaim(AceType::RawPtr(eventHubRefPtr));
    richEditorNode_->GetOrCreateEventHub<EventHub>()->gestureEventHub_ =
        AceType::MakeRefPtr<GestureEventHub>(eventHubWeakPtr);
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorNode_->GetOrCreateEventHub<EventHub>()->gestureEventHub_->isTextDraggable_ = true;
    richEditorPattern->HandleDraggableFlag(true);
    EXPECT_FALSE(richEditorNode_->GetOrCreateEventHub<EventHub>()->gestureEventHub_->isTextDraggable_);
}

/**
 * @tc.name: OnDragEnd005
 * @tc.desc: test OnDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, OnDragEnd005, TestSize.Level1)
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
 * @tc.name: OnDragEnd006
 * @tc.desc: test OnDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, OnDragEnd006, TestSize.Level1)
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
 * @tc.name: OnDragEnd007
 * @tc.desc: test OnDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, OnDragEnd007, TestSize.Level1)
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
    richEditorNode_->focusHub_->focusType_ = FocusType::DISABLE;
    richEditorPattern->OnDragEnd(event);
    EXPECT_FALSE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: BeforeDrag002
 * @tc.desc: test BeforeDrag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, BeforeDrag002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    struct UpdateSpanStyle typingStyle;
    TextStyle textStyle;
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);
    richEditorPattern->typingTextStyle_.reset();
    RichEditorChangeValue changeValue;
    int32_t innerPosition = 0;
    RichEditorPattern::OperationRecord record;
    record.addText = u"test123\n";
    record.beforeCaretPosition = 20;

    richEditorPattern->BeforeDrag(changeValue, innerPosition, record);
    EXPECT_FALSE(richEditorPattern->typingTextStyle_.has_value());
    EXPECT_NE(innerPosition, 0);
}

/**
 * @tc.name: HandleDragStart001
 * @tc.desc: test HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleDragStart001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto dragEvent = AceType::MakeRefPtr<Ace::DragEvent>();
    std::string extraParams = "text";
    richEditorPattern->isDragSponsor_ = true;
    richEditorPattern->HandleDragStart(dragEvent, extraParams);
    EXPECT_EQ(richEditorPattern->recoverStart_, -1);
    EXPECT_EQ(richEditorPattern->recoverEnd_, -1);
}

/**
 * @tc.name: HandleDraggableFlag005
 * @tc.desc: test HandleDraggableFlag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleDraggableFlag005, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->HandleDraggableFlag(false);
    EXPECT_EQ(richEditorPattern->JudgeContentDraggable(), false);
}

/**
 * @tc.name: CalcDragSpeed001
 * @tc.desc: test CalcDragSpeed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, CalcDragSpeed001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    float speed = 0.0f;
    float hotAreaStart = 1.1f;
    float hotAreaEnd = 101.1f;
    float point = 50.1f;
    float result = 17.472723f;
    speed = richEditorPattern->CalcDragSpeed(hotAreaStart, hotAreaEnd, point);
    EXPECT_EQ(result, speed);
}

/**
 * @tc.name: HandleOnDragDropStyledString007
 * @tc.desc: test HandleOnDragDropStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleOnDragDropStyledString007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<UnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->HandleOnDragDropStyledString(event);
    EXPECT_NE(event->GetData(), nullptr);
}
} // namespace OHOS::Ace::NG
