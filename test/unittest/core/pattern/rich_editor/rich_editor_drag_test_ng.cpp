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
    richEditorNode_->GetEventHub<EventHub>()->gestureEventHub_ = AceType::MakeRefPtr<GestureEventHub>(eventHubWeakPtr);
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorNode_->GetEventHub<EventHub>()->gestureEventHub_->isTextDraggable_ = true;
    richEditorPattern->HandleDraggableFlag(true);
    EXPECT_FALSE(richEditorNode_->GetEventHub<EventHub>()->gestureEventHub_->isTextDraggable_);
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
 * @tc.name: HandleOnDragInsertValueOperation001
 * @tc.desc: test HandleOnDragInsertValueOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleOnDragInsertValueOperation001, TestSize.Level1)
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

    struct UpdateSpanStyle typingStyle;
    TextStyle textStyle(5);
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);
    std::u16string insertValue = u"test123";
    richEditorPattern->HandleOnDragInsertValueOperation(insertValue);
    EXPECT_TRUE(richEditorPattern->typingStyle_.has_value());
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
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);

    auto temp = richEditorPattern->caretPosition_;
    richEditorPattern->HandleOnDragDropTextOperation(INIT_VALUE_1, false);
    EXPECT_NE(richEditorPattern->caretPosition_, temp);
}

/**
 * @tc.name: GetThumbnailCallback001
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, GetThumbnailCallback001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto host = richEditorPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    gestureHub->InitDragDropEvent();
    gestureHub->SetThumbnailCallback(richEditorPattern->GetThumbnailCallback());
    EXPECT_EQ(richEditorPattern->dragNode_, nullptr);
}


/**
 * @tc.name: GetThumbnailCallback002
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, GetThumbnailCallback002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    richEditorPattern->InitDragDropEvent();
    EXPECT_EQ(richEditorPattern->dragNode_, nullptr);
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
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
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
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
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
    auto eventHub = host->GetEventHub<EventHub>();
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
 * @tc.name: HandleOnDragInsertValue001
 * @tc.desc: test HandleOnDragInsertValue
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNg, HandleOnDragInsertValue001, TestSize.Level1)
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
HWTEST_F(RichEditorDragTestNg, HandleOnDragInsertValue002, TestSize.Level1)
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
    richEditorPattern->HandleOnDragDropStyledString(event);
    auto host = richEditorPattern->GetHost();
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
    richEditorPattern->HandleOnDragDropStyledString(event);
    EXPECT_NE(event->GetData(), nullptr);
    auto host = richEditorPattern->GetHost();
    EXPECT_FALSE(host->isRestoreInfoUsed_);
}

} // namespace OHOS::Ace::NG