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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "gtest/hwext/gtest-ext.h"
#include "gtest/hwext/gtest-tag.h"
#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"

#include "core/components_ng/render/paragraph.h"
#include "core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RichEditorPatternTestSevenNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

class MockTextInputConnection : public TextInputConnection {
public:
    MockTextInputConnection(const WeakPtr<TextInputClient>& client, const RefPtr<TaskExecutor>& taskExecutor)
        : TextInputConnection(client, taskExecutor)
    {}

    MOCK_METHOD(void, Show, (bool isFocusViewChanged, int32_t instanceId), (override));
    MOCK_METHOD(void, SetEditingState, (const TextEditingValue& value, int32_t instanceId, bool needFireChangeEvent),
        (override));
    MOCK_METHOD(void, Close, (int32_t instanceId), (override));
};

class MockTextInputClient : public TextInputClient {
public:
    MOCK_METHOD(void, UpdateEditingValue, (const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent),
        (override));
    MOCK_METHOD(void, PerformAction, (TextInputAction action, bool forceCloseKeyboard), (override));
};

class MockTaskExecutor : public TaskExecutor {
public:
    MOCK_METHOD(void, AddTaskObserver, (Task && callback), (override));
    MOCK_METHOD(void, RemoveTaskObserver, (), (override));
    MOCK_METHOD(bool, WillRunOnCurrentThread, (TaskType type), (const, override));
    MOCK_METHOD(void, RemoveTask, (TaskType type, const std::string& name), (override));

    MOCK_METHOD(bool, OnPostTask,
        (Task && task, TaskType type, uint32_t delayTime, const std::string& name, PriorityType priorityType),
        (const, override));
    MOCK_METHOD(Task, WrapTaskWithTraceId, (Task && task, int32_t id), (const, override));
    MOCK_METHOD(bool, OnPostTaskWithoutTraceId,
        (Task && task, TaskType type, uint32_t delayTime, const std::string& name, PriorityType priorityType),
        (const, override));
};

void RichEditorPatternTestSevenNg::SetUp()
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

void RichEditorPatternTestSevenNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorPatternTestSevenNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: GetTextBoxes003
 * @tc.desc: test GetTextBoxes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, GetTextBoxes003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = u"testShowHandles";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;

    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([&](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    const OHOS::Ace::NG::ParagraphStyle expectedStyle;
    LeadingMargin leadingMarginOne;
    EXPECT_CALL(*mockParagraph, GetParagraphStyle()).WillRepeatedly(ReturnRef(expectedStyle));
    paragraphInfo.paragraph = mockParagraph;
    paragraphInfo.paragraphStyle = expectedStyle;
    paragraphInfo.start = 0;
    paragraphInfo.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfo);
    richEditorPattern->paragraphs_.AddParagraph(std::move(paragraphInfo));
    auto textBoxes = richEditorPattern->GetTextBoxes();
    EXPECT_NE(textBoxes.size(), 0);
}

/**
 * @tc.name: GetTextBoxes004
 * @tc.desc: test GetTextBoxes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, GetTextBoxes004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = u"testShowHandles";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;

    ParagraphStyle paragraphStyle = {};
    paragraphStyle.leadingMargin = LeadingMargin();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    ParagraphManager::ParagraphInfo paragraphInfoOne;
    RefPtr<MockParagraph> mockParagraphOne = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraphOne, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([&](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    LeadingMargin leadingMarginOne;
    EXPECT_CALL(*mockParagraphOne, GetParagraphStyle()).WillRepeatedly(ReturnRef(paragraphStyle));
    paragraphInfoOne.paragraph = mockParagraphOne;
    paragraphInfoOne.paragraphStyle = paragraphStyle;
    paragraphInfoOne.start = 0;
    paragraphInfoOne.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfoOne);
    richEditorPattern->paragraphs_.AddParagraph(std::move(paragraphInfoOne));
    auto textBoxes = richEditorPattern->GetTextBoxes();
    EXPECT_NE(textBoxes.size(), 0);
}

/**
 * @tc.name: HandleOnDragDropStyledString001
 * @tc.desc: test HandleOnDragDropStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, HandleOnDragDropStyledString001, TestSize.Level1)
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
HWTEST_F(RichEditorPatternTestSevenNg, HandleOnDragDropStyledString002, TestSize.Level1)
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
HWTEST_F(RichEditorPatternTestSevenNg, HandleOnDragDropStyledString003, TestSize.Level1)
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
HWTEST_F(RichEditorPatternTestSevenNg, HandleOnDragDropStyledString004, TestSize.Level1)
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
HWTEST_F(RichEditorPatternTestSevenNg, HandleOnDragDropStyledString005, TestSize.Level1)
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
HWTEST_F(RichEditorPatternTestSevenNg, HandleOnDragDropStyledString006, TestSize.Level1)
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

/**
 * @tc.name: FloatingCaretTest001
 * @tc.desc: test FloatingCaret
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, FloatingCaretTest001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    richEditorPattern->AddTextSpan(options);

    CaretMetricsF caretMetricsBegin = { OffsetF(20.0f, 0), 50.0f };
    CaretMetricsF caretMetricsEnd = { OffsetF(100.0f, 0), 50.0f };
    TestParagraphItem paragraphItem = { .start = 0, .end = 7,
        .testCursorItems = { { 0, caretMetricsBegin, caretMetricsBegin}, {6, caretMetricsEnd, caretMetricsEnd} } };
    AddParagraph(paragraphItem);
    richEditorPattern->richTextRect_.SetSize({ 200.f, 200.f });
    richEditorPattern->contentRect_ = { 0.0, 0.0, 500.0, 500.0 };

    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->floatingCaretState_.Reset();
    richEditorPattern->caretAffinityPolicy_ = CaretAffinityPolicy::DOWNSTREAM_FIRST;
    richEditorPattern->SetCaretTouchMoveOffset(Offset(0.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(0.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);
    richEditorPattern->SetCaretTouchMoveOffset(Offset(20.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(20.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_FALSE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);

    richEditorPattern->caretPosition_ = 6;
    richEditorPattern->floatingCaretState_.Reset();
    richEditorPattern->caretAffinityPolicy_ = CaretAffinityPolicy::UPSTREAM_FIRST;
    richEditorPattern->SetCaretTouchMoveOffset(Offset(100.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(100.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_FALSE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);
    richEditorPattern->SetCaretTouchMoveOffset(Offset(120.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(120.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);
}

/**
 * @tc.name: FloatingCaretTest002
 * @tc.desc: test FloatingCaret
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, FloatingCaretTest002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorPattern->AddTextSpan(options);

    CaretMetricsF caretMetricsLineEndUp = { OffsetF(100.0f, 0), 50.0f };
    CaretMetricsF caretMetricsLineEndDown = { OffsetF(0, 50.0f), 50.0f };
    CaretMetricsF caretMetricsInLine = { OffsetF(50.0f, 0), 50.0f };
    TestParagraphItem paragraphItem = { .start = 0, .end = 38,
        .testCursorItems = { { 5, caretMetricsInLine, caretMetricsInLine},
        { 10, caretMetricsLineEndDown, caretMetricsLineEndUp} } };
    AddParagraph(paragraphItem);
    richEditorPattern->richTextRect_.SetSize({ 200.f, 200.f });
    richEditorPattern->contentRect_ = { 0.0, 0.0, 500.0, 500.0 };

    richEditorPattern->caretPosition_ = 5;
    richEditorPattern->floatingCaretState_.Reset();
    richEditorPattern->caretAffinityPolicy_ = CaretAffinityPolicy::UPSTREAM_FIRST;
    richEditorPattern->SetCaretTouchMoveOffset(Offset(50.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(50.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_FALSE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);
    richEditorPattern->SetCaretTouchMoveOffset(Offset(70.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(70.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_FALSE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);

    richEditorPattern->caretPosition_ = 10;
    richEditorPattern->floatingCaretState_.Reset();
    richEditorPattern->caretAffinityPolicy_ = CaretAffinityPolicy::UPSTREAM_FIRST;
    richEditorPattern->SetCaretTouchMoveOffset(Offset(100.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(100.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_FALSE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);
    richEditorPattern->SetCaretTouchMoveOffset(Offset(120.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(120.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);
}

/**
 * @tc.name: FloatingCaretTest003
 * @tc.desc: test FloatingCaret
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, FloatingCaretTest003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<RichEditorPaintMethod>(richEditorPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    auto richEditorOverlay = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    ASSERT_NE(richEditorOverlay, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    auto paintProperty = richEditorPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);

    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorPattern->AddTextSpan(options);
    CaretMetricsF caretMetricsLineEndUp = { OffsetF(100.0f, 0), 50.0f };
    CaretMetricsF caretMetricsLineEndDown = { OffsetF(0, 50.0f), 50.0f };
    TestParagraphItem paragraphItem = { .start = 0, .end = 38,
        .testCursorItems = { { 10, caretMetricsLineEndDown, caretMetricsLineEndUp} } };
    AddParagraph(paragraphItem);
    richEditorPattern->richTextRect_.SetSize({ 200.f, 200.f });
    richEditorPattern->contentRect_ = { 0.0, 0.0, 500.0, 500.0 };

    richEditorPattern->caretPosition_ = 10;
    richEditorPattern->floatingCaretState_.Reset();
    richEditorPattern->caretAffinityPolicy_ = CaretAffinityPolicy::UPSTREAM_FIRST;
    richEditorPattern->SetCaretTouchMoveOffset(Offset(100.0, 0));
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(richEditorOverlay->floatingCaretOffset_->Get(), OffsetF(100.0f, 0));
    EXPECT_TRUE(richEditorOverlay->floatingCaretVisible_->Get());
    EXPECT_FALSE(richEditorOverlay->originCaretVisible_->Get());
    richEditorPattern->SetCaretTouchMoveOffset(Offset(120.0, 0));
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(richEditorOverlay->floatingCaretOffset_->Get(), OffsetF(120.0f, 0));
    EXPECT_TRUE(richEditorOverlay->floatingCaretVisible_->Get());
    EXPECT_TRUE(richEditorOverlay->originCaretVisible_->Get());
}

/**
 * @tc.name: UnableStandardInput002
 * @tc.desc: test RichEditorPattern UnableStandardInput
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, UnableStandardInput002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto client = AceType::MakeRefPtr<MockTextInputClient>();
    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->connection_ = AceType::MakeRefPtr<MockTextInputConnection>(client, taskExecutor);
    richEditorPattern->imeAttached_ = true;
    bool res = richEditorPattern->UnableStandardInput(false);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: IsStopBackPress001
 * @tc.desc: test IsStopBackPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, IsStopBackPress001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isStopBackPress_ = false;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    auto result = richEditorPattern->OnBackPressed();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ShiftMultipleSelection001
 * @tc.desc: test richEditor shift multiple selection function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, ShiftMultipleSelection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(textOptions);

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_SHIFT_LEFT;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.pressedCodes.push_back(KeyCode::KEY_SHIFT_LEFT);
    keyEvent.pressedCodes.push_back(KeyCode::KEY_DPAD_RIGHT);
    richEditorPattern->UpdateShiftFlag(keyEvent);
    EXPECT_TRUE(richEditorPattern->shiftFlag_);

    MouseInfo mouseInfo;
    mouseInfo.button_ = MouseButton::LEFT_BUTTON;
    mouseInfo.action_ = MouseAction::PRESS;
    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    mouseInfo.SetGlobalLocation(Offset(0, 0));
    richEditorPattern->SetCaretPosition(10);
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 10);
    richEditorPattern->textSelector_.Update(10, 20);
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 10);

    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    info.deviceType_ = SourceType::MOUSE;
    richEditorPattern->SetCaretPosition(10);
    richEditorPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 10);
    richEditorPattern->textSelector_.Update(10, 20);
    richEditorPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 10);

    keyEvent.action = KeyAction::UP;
    keyEvent.pressedCodes.pop_back();
    richEditorPattern->UpdateShiftFlag(keyEvent);
    EXPECT_TRUE(richEditorPattern->shiftFlag_);
    keyEvent.pressedCodes.pop_back();
    richEditorPattern->UpdateShiftFlag(keyEvent);
    EXPECT_FALSE(richEditorPattern->shiftFlag_);
}

/**
 * @tc.name: PageScrollTest001
 * @tc.desc: test richEditor pageup and pagedown function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, PageScrollTest001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto geometryNode = richEditorNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(150.0f, 150.0f));
    richEditorPattern->richTextRect_ = RectF(0, 0, 150.0f, 400.0f);
    richEditorPattern->contentRect_ = RectF(0, 0, 150.0f, 150.0f);

    richEditorPattern->HandleOnPageDown();
    EXPECT_EQ(richEditorPattern->scrollOffset_, -150.0f);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), -150.0f);
    richEditorPattern->HandleOnPageUp();
    EXPECT_EQ(richEditorPattern->scrollOffset_, 0);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), 0);
}
} // namespace OHOS::Ace::NG
