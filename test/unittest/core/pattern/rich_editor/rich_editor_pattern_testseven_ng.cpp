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
#include "test/mock/base/mock_task_executor.h"

#include "core/components_ng/render/paragraph.h"

#define private public
#define protected public

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RichEditorPatternTestSevenNg : public TestNG {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    RefPtr<FrameNode> richEditorNode;
};

void RichEditorPatternTestSevenNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode->GetGeometryNode()->SetContentSize({});
}

void RichEditorPatternTestSevenNg::TearDown()
{
    richEditorNode = nullptr;
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
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
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
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
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
} // namespace OHOS::Ace::NG
