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
 * @tc.name: UpdateSelectionAndHandleVisibility001
 * @tc.desc: test UpdateSelectionAndHandleVisibility
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, UpdateSelectionAndHandleVisibility001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->sourceTool_ = SourceTool::MOUSE;
    richEditorPattern->releaseInDrop_ = true;
    AddSpan("test--test");

    richEditorPattern->textSelector_.Update(5, 10);
    richEditorPattern->caretPosition_ = 5;
    richEditorPattern->insertValueLength_ = 5;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->UpdateSelectionAndHandleVisibility();
    ASSERT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    ASSERT_EQ(richEditorPattern->textSelector_.destinationOffset, 5);
}

/**
 * @tc.name: UpdateSelectionAndHandleVisibility002
 * @tc.desc: test UpdateSelectionAndHandleVisibility
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, UpdateSelectionAndHandleVisibility002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->sourceTool_ = SourceTool::MOUSE;
    richEditorPattern->releaseInDrop_ = true;
    AddSpan("test--test");

    richEditorPattern->textSelector_.Update(5, 10);
    richEditorPattern->lastCaretPosition_ = 5;
    richEditorPattern->insertValueLength_ = 5;
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->UpdateSelectionAndHandleVisibility();
    ASSERT_EQ(richEditorPattern->textSelector_.baseOffset, 5);
    ASSERT_EQ(richEditorPattern->textSelector_.destinationOffset, 10);
}

/**
 * @tc.name: ProvidePlaceHolderText001
 * @tc.desc: test provide placeholder information to inputmethod function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, ProvidePlaceHolderText, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
#if defined(ENABLE_STANDARD_INPUT)
    auto miscTextConfig = richEditorPattern->GetMiscTextConfig();
    auto textconfig = miscTextConfig.value();
    auto placeholder = UtfUtils::Str16ToStr8(textconfig.inputAttribute.placeholder).c_str();
    size_t count = 0;
    size_t i = 0;
    while (i < placeholder.size()) {
        count++;
        i += (placeholder[i] >= 0xD800 && placeholder[i] <= 0xDBFF) ? 2 : 1;
    }
    EXPECT_NE(count, 0);
#endif
}
/**
 * @tc.name: ProvideabilityNameText001
 * @tc.desc: test provide abilityName information to inputmethod function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, ProvideabilityNameText, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
#if defined(ENABLE_STANDARD_INPUT)
    auto miscTextConfig = richEditorPattern->GetMiscTextConfig();
    auto textconfig = miscTextConfig.value();
    auto abilityName = UtfUtils::Str16ToStr8(textconfig.inputAttribute.abilityName).c_str();
    size_t count = 0;
    size_t i = 0;
    while (i < abilityName.size()) {
        count++;
        i += (abilityName[i] >= 0xD800 && abilityName[i] <= 0xDBFF) ? 2 : 1;
    }
    EXPECT_NE(count, 0);
#endif
}

} // namespace OHOS::Ace::NG
