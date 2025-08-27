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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
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

class RichEditorSpanNodeTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorSpanNodeTestNg::SetUp()
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

void RichEditorSpanNodeTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorSpanNodeTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: RichEditorPatternTestCreateTextSpanNode001
 * @tc.desc: test CreateTextSpanNode
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanNodeTestNg, RichEditorPatternTestCreateTextSpanNode001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanNode> spanNode;

    TextInsertValueInfo info;
    std::u16string insertValue;
    UpdateSpanStyle updateSpanStyle;
    TextStyle textStyle;

    updateSpanStyle.useThemeFontColor = false;

    auto typingStyle = richEditorPattern->typingStyle_;
    auto typingTextStyle = richEditorPattern->typingTextStyle_;

    richEditorPattern->typingStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = std::nullopt;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue);
    EXPECT_EQ(spanNode->GetSpanItem()->useThemeDecorationColor, true);

    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue);
    EXPECT_EQ(spanNode->GetSpanItem()->useThemeDecorationColor, true);

    richEditorPattern->typingStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = textStyle;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue);
    EXPECT_EQ(spanNode->GetSpanItem()->useThemeDecorationColor, true);

    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue);
    EXPECT_EQ(spanNode->GetSpanItem()->useThemeDecorationColor, true);

    richEditorPattern->typingStyle_ = typingStyle;
    richEditorPattern->typingTextStyle_ = typingTextStyle;
}

/**
 * @tc.name: InsertValueToSpanNode001
 * @tc.desc: test InsertValueToSpanNode
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanNodeTestNg, InsertValueToSpanNode001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::u16string insertValue = u"abc";

    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, 0);
    TextInsertValueInfo info;
    info.spanIndex_ = 0;
    info.SetOffsetInSpan(100);

    richEditorPattern->InsertValueToSpanNode(spanNode, insertValue, info);

    auto spanItem = spanNode->GetSpanItem();
    auto text = spanItem->content;
    auto textTempSize = static_cast<int32_t>(text.size());

    ASSERT_EQ(textTempSize, 0);
}

/**
 * @tc.name: RemoveEmptySpanNodes001
 * @tc.desc: test RemoveEmptySpanNodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanNodeTestNg, RemoveEmptySpanNodes001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto host = richEditorPattern->GetContentHost();
    EXPECT_NE(host, nullptr);

    richEditorPattern->spans_.clear();
    host->children_.clear();
    auto textframeNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textframeNode, nullptr);
    host->AddChild(textframeNode);
    textframeNode->SetParent(host);

    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imageSpanNode, nullptr);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);

    richEditorPattern->RemoveEmptySpanNodes();

    ASSERT_EQ(host->GetChildren().empty(), false);
}

/**
 * @tc.name: RemoveEmptySpanNodes002
 * @tc.desc: test RichEditorPattern RemoveEmptySpanNodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanNodeTestNg, RemoveEmptySpanNodes002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->RemoveEmptySpanNodes();
    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);
}

/**
 * @tc.name: RemoveEmptySpanNodes003
 * @tc.desc: test RemoveEmptySpanNodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanNodeTestNg, RemoveEmptySpanNodes003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto newFrameNode = ImageSpanNode::GetOrCreateSpanNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    auto newAddFrameNode = ImageSpanNode::GetOrCreateSpanNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    richEditorNode_->children_.push_back(newFrameNode);
    richEditorNode_->children_.push_back(newAddFrameNode);
    richEditorPattern->RemoveEmptySpanNodes();
    bool nonSpanNodeStillExists = false;
    for (const auto& child : richEditorNode_->children_) {
        if (child == newFrameNode) {
            nonSpanNodeStillExists = true;
            break;
        }
    }
    EXPECT_TRUE(nonSpanNodeStillExists);
}

/**
 * @tc.name: RemoveEmptySpanNodes004
 * @tc.desc: test RemoveEmptySpanNodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanNodeTestNg, RemoveEmptySpanNodes004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto newFrameNode = SpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG, nodeId);
    auto newAddFrameNode = SpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG, nodeId);
    newAddFrameNode->GetSpanItem()->content = INIT_VALUE_3;
    contentNode->children_.push_back(newFrameNode);
    contentNode->children_.push_back(newAddFrameNode);
    richEditorPattern->RemoveEmptySpanNodes();
    bool emptySpanNodeRemoved = true;
    for (const auto& child : contentNode->children_) {
        auto spanNode = AceType::DynamicCast<SpanNode>(child);
        if (spanNode && spanNode->GetSpanItem()->content.empty()) {
            emptySpanNodeRemoved = false;
            break;
        }
    }
    EXPECT_TRUE(emptySpanNodeRemoved);
}

/**
 * @tc.name: GetSpanNodeBySpanItem001
 * @tc.desc: test GetSpanNodeBySpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanNodeTestNg, GetSpanNodeBySpanItem001, TestSize.Level2)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    ASSERT_EQ(richEditorPattern->GetSpanNodeBySpanItem(nullptr), nullptr);
}

}