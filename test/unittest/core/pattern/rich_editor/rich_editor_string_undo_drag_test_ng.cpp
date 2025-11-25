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
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::u16string INIT_TEST_CONTENT = u"RichEditor拖拽";
    const std::u16string INIT_DRAG_CONTENT = u"拖拽";
    const std::u16string PASTE_TEST_CONTENT = u"插入内容";
    const std::u16string RICH_EDITOR_TEST_CONTENT = u"RichEditor";
    const std::u16string DRAG_TEST_CONTENT = u"拖拽插入内容";
    const std::u16string SYMBOL_TEST_CONTENT = u"  ";
    const std::u16string BUILDER_TEST_CONTENT = u" ";
}

class RichEditorStringUndoDragTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    void InitContent();
    static void TearDownTestSuite();
};

void RichEditorStringUndoDragTestNg::SetUp()
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

void RichEditorStringUndoDragTestNg::TearDown()
{
    richEditorNode_ = nullptr;
}

void RichEditorStringUndoDragTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void RichEditorStringUndoDragTestNg::InitContent()
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->InsertValue(INIT_TEST_CONTENT);
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
    TextSpanOptions options;
    options.value = PASTE_TEST_CONTENT;
    richEditorPattern->AddTextSpan(options);
    auto builderNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    richEditorPattern->AddPlaceholderSpan(builderNode, {});
}

/**
 * @tc.name: UndoDragTest
 * @tc.desc: Test undo drag.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStringUndoDragTestNg, UndoDragTest, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContent();

    richEditorPattern->ResetSelection();
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->dragRange_ = std::make_pair(10, 19);
    richEditorPattern->HandleOnDragDropTextOperation(DRAG_TEST_CONTENT, true, false);

    std::u16string contentAfterDrag;
    std::u16string expectContent =
        DRAG_TEST_CONTENT + RICH_EDITOR_TEST_CONTENT + SYMBOL_TEST_CONTENT +BUILDER_TEST_CONTENT;
    richEditorPattern->GetContentBySpans(contentAfterDrag);
    EXPECT_EQ(contentAfterDrag, expectContent);

    richEditorPattern->HandleOnUndoAction();
    std::u16string contentAfterUndoStep1;
    expectContent = DRAG_TEST_CONTENT + RICH_EDITOR_TEST_CONTENT + INIT_DRAG_CONTENT +SYMBOL_TEST_CONTENT +
        PASTE_TEST_CONTENT + BUILDER_TEST_CONTENT;
    richEditorPattern->GetContentBySpans(contentAfterUndoStep1);
    EXPECT_EQ(contentAfterUndoStep1, expectContent);

    richEditorPattern->HandleOnUndoAction();
    std::u16string contentAfterUndoStep2;
    expectContent = INIT_TEST_CONTENT + SYMBOL_TEST_CONTENT + PASTE_TEST_CONTENT + BUILDER_TEST_CONTENT;
    richEditorPattern->GetContentBySpans(contentAfterUndoStep2);
    EXPECT_EQ(contentAfterUndoStep2, expectContent);

    richEditorPattern->HandleOnRedoAction();
    std::u16string contentAfterRedoStep1;
    expectContent = DRAG_TEST_CONTENT + RICH_EDITOR_TEST_CONTENT + INIT_DRAG_CONTENT +SYMBOL_TEST_CONTENT +
        PASTE_TEST_CONTENT + BUILDER_TEST_CONTENT;
    richEditorPattern->GetContentBySpans(contentAfterRedoStep1);
    EXPECT_EQ(contentAfterRedoStep1, expectContent);

    richEditorPattern->HandleOnRedoAction();
    std::u16string contentAfterRedoStep2;
    expectContent = DRAG_TEST_CONTENT + RICH_EDITOR_TEST_CONTENT + SYMBOL_TEST_CONTENT + BUILDER_TEST_CONTENT;
    richEditorPattern->GetContentBySpans(contentAfterRedoStep2);
    EXPECT_EQ(contentAfterRedoStep2, expectContent);
}
}