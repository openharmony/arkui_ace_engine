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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CUSTOM_CONTENT_LENGTH = 1;
constexpr int32_t PLACEHOLDER_LENGTH = 6;
} // namespace

class RichEditorPlaceholderSpanTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    RefPtr<RichEditorPattern> GetRichEditorPattern();
    static void TearDownTestSuite();
};

void RichEditorPlaceholderSpanTestNg::SetUp()
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

void RichEditorPlaceholderSpanTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorPlaceholderSpanTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

RefPtr<RichEditorPattern> RichEditorPlaceholderSpanTestNg::GetRichEditorPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

/**
 * @tc.name: AddPlaceholderSpan001
 * @tc.desc: test add builder span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, AddPlaceholderSpan001, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    RefPtr<GeometryNode> containerGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(containerGeometryNode == nullptr);
    containerGeometryNode->SetFrameSize(SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT));
    ASSERT_NE(richEditorNode_->GetLayoutProperty(), nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(richEditorNode_, containerGeometryNode, richEditorNode_->GetLayoutProperty());

    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));

    auto builderId = ElementRegister::GetInstance()->MakeUniqueId();
    auto builderNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, builderId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto index = richEditorController->AddPlaceholderSpan(builderNode, {});
    EXPECT_EQ(index, 0);
    EXPECT_EQ(contentNode->GetChildren().size(), 1);
    auto builderSpanChildren = contentNode->GetChildren();
    ASSERT_NE(static_cast<int32_t>(builderSpanChildren.size()), 0);
    auto builderSpan = builderSpanChildren.begin();
    auto builderSpanChild = AceType::DynamicCast<FrameNode>(*builderSpan);
    ASSERT_NE(builderSpanChild, nullptr);
    EXPECT_EQ(builderSpanChild->GetTag(), V2::PLACEHOLDER_SPAN_ETS_TAG);

    auto richEditorLayoutAlgorithm = richEditorPattern->CreateLayoutAlgorithm();
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(richEditorLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(BUILDER_SIZE);
    RefPtr<GeometryNode> builderGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    builderGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> builderLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        builderSpanChild, builderGeometryNode, builderSpanChild->GetLayoutProperty());
    EXPECT_FALSE(builderLayoutWrapper == nullptr);
    auto builderPattern = builderSpanChild->GetPattern();
    builderLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto firstItemLayoutAlgorithm = builderPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(firstItemLayoutAlgorithm == nullptr);
}

/**
 * @tc.name: AddPlaceholderSpan002
 * @tc.desc: test add builder span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, AddPlaceholderSpan002, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    AddSpan("test");
    auto builderId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto builderNode1 = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, builderId1, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto index1 = richEditorController->AddPlaceholderSpan(builderNode1, {});
    EXPECT_EQ(index1, 1);
    EXPECT_EQ(static_cast<int32_t>(contentNode->GetChildren().size()), 2);
    auto builderSpanChildren = contentNode->GetChildren();
    ASSERT_NE(static_cast<int32_t>(builderSpanChildren.size()), 0);
    auto builderSpanChild = builderSpanChildren.begin();
    EXPECT_EQ((*builderSpanChild)->GetTag(), "Span");
    ClearSpan();
}

/**
 * @tc.name: AddPlaceholderSpan003
 * @tc.desc: test AddPlaceholderSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, AddPlaceholderSpan003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create richEditorNode_ and layoutWrapper.
     */
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    RefPtr<GeometryNode> containerGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(containerGeometryNode == nullptr);
    containerGeometryNode->SetFrameSize(SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT));
    ASSERT_NE(richEditorNode_->GetLayoutProperty(), nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(richEditorNode_, containerGeometryNode, richEditorNode_->GetLayoutProperty());

    /**
     * @tc.steps: step2. get richEditorPattern and richEditorController.
     */
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    AddSpan("test");

    /**
     * @tc.steps: step3. test AddPlaceholderSpan.
     */
    auto builderId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto builderNode1 = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, builderId1, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });

    auto index1 = richEditorController->AddPlaceholderSpan(builderNode1, {});
    EXPECT_EQ(index1, 1);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);
    auto builderSpanChildren = contentNode->GetChildren();
    ASSERT_NE(static_cast<int32_t>(builderSpanChildren.size()), 0);
    auto eventHub = builderNode1->GetEventHub<EventHub>();
    EXPECT_NE(eventHub, nullptr);
}

/**
 * @tc.name: AddPlaceholderSpan004
 * @tc.desc: test AddPlaceholderSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, AddPlaceholderSpan004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto builderNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    SpanOptionBase options = {};
    auto host = richEditorPattern->GetHost();
    EXPECT_NE(host, nullptr);
    AddSpan("test");
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem);
    richEditorPattern->spans_.emplace_back(spanItem);
    richEditorPattern->spans_.emplace_back(spanItem);
    auto ret = richEditorPattern->AddPlaceholderSpan(builderNode, {});
    EXPECT_NE(ret, host->GetChildren().size());
}

/**
 * @tc.name: AddPlaceholderSpan005
 * @tc.desc: test add builder span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, AddPlaceholderSpan005, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    AddSpan("test");
    RefPtr<FrameNode> builderNode1 = nullptr;
    auto index1 = richEditorController->AddPlaceholderSpan(builderNode1, {});
    EXPECT_EQ(index1, 0);
    EXPECT_EQ(static_cast<int32_t>(contentNode->GetChildren().size()), 1);
    ClearSpan();
}

/**
 * @tc.name: InitPlaceholderSpansMap001
 * @tc.desc: test InitPlaceholderSpansMap
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, InitPlaceholderSpansMap001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto newSpanItem = AceType::MakeRefPtr<OHOS::Ace::NG::SpanItem>();
    auto spanItem = AceType::MakeRefPtr<OHOS::Ace::NG::SpanItem>();
    size_t index = 0;
    size_t placeholderGains = 0;
    spanItem->spanItemType = SpanItemType::CustomSpan;
    richEditorPattern->InitPlaceholderSpansMap(newSpanItem, spanItem, index, placeholderGains);
    EXPECT_EQ(placeholderGains, placeholderGains += PLACEHOLDER_LENGTH - CUSTOM_CONTENT_LENGTH);
}

/**
 * @tc.name: InitPlaceholderSpansMap002
 * @tc.desc: test InitPlaceholderSpansMap
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, InitPlaceholderSpansMap002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto newSpanItem = AceType::MakeRefPtr<OHOS::Ace::NG::SpanItem>();
    auto spanItem = AceType::MakeRefPtr<OHOS::Ace::NG::SpanItem>();
    size_t index = 0;
    size_t placeholderGains = 0;
    spanItem->spanItemType = SpanItemType::CustomSpan;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->InitPlaceholderSpansMap(newSpanItem, spanItem, index, placeholderGains);
    EXPECT_EQ(placeholderGains, placeholderGains += PLACEHOLDER_LENGTH - CUSTOM_CONTENT_LENGTH);
}

/**
 * @tc.name: InitPlaceholderSpansMap003
 * @tc.desc: test InitPlaceholderSpansMap
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, InitPlaceholderSpansMap003, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto newSpanItem = AceType::MakeRefPtr<OHOS::Ace::NG::SpanItem>();
    auto spanItem = AceType::MakeRefPtr<OHOS::Ace::NG::SpanItem>();
    size_t index = 0;
    size_t placeholderGains = 0;
    spanItem->spanItemType = SpanItemType::IMAGE;
    richEditorPattern->InitPlaceholderSpansMap(newSpanItem, spanItem, index, placeholderGains);
    EXPECT_EQ(placeholderGains, placeholderGains += PLACEHOLDER_LENGTH - CUSTOM_CONTENT_LENGTH);
}

/**
 * @tc.name: ReplacePlaceholderWithCustomSpan001
 * @tc.desc: test ReplacePlaceholderWithCustomSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, ReplacePlaceholderWithCustomSpan001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<CustomSpanItem>();
    EXPECT_NE(spanItem, nullptr);
    size_t index = 1;
    size_t textIndex = 1;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->ReplacePlaceholderWithCustomSpan(spanItem, index, textIndex);
    EXPECT_EQ(richEditorPattern->textSelector_.IsValid(), false);
    EXPECT_EQ(textIndex, PLACEHOLDER_LENGTH + index);
}

/**
 * @tc.name: ReplacePlaceholderWithCustomSpan002
 * @tc.desc: test ReplacePlaceholderWithCustomSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, ReplacePlaceholderWithCustomSpan002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<CustomSpanItem>();
    EXPECT_NE(spanItem, nullptr);
    size_t index = 1;
    size_t textIndex = 1;
    richEditorPattern->isSpanStringMode_ = false;
    spanItem->spanItemType = SpanItemType::CustomSpan;
    auto builderId = ElementRegister::GetInstance()->MakeUniqueId();
    auto builderNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, builderId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    spanItem->SetCustomNode(builderNode);
    richEditorPattern->ReplacePlaceholderWithCustomSpan(spanItem, index, textIndex);
    EXPECT_EQ(textIndex, PLACEHOLDER_LENGTH + index);
}

/**
 * @tc.name: ReplacePlaceholderWithCustomSpan003
 * @tc.desc: test ReplacePlaceholderWithCustomSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, ReplacePlaceholderWithCustomSpan003, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<CustomSpanItem>();
    EXPECT_NE(spanItem, nullptr);
    spanItem->GetSameStyleSpanItem();
    size_t index = 1;
    size_t textIndex = 1;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    spanItem->onMeasure.emplace();
    spanItem->onDraw.emplace();
    richEditorPattern->ReplacePlaceholderWithCustomSpan(spanItem, index, textIndex);
    EXPECT_EQ(textIndex, PLACEHOLDER_LENGTH + index);
}

/**
 * @tc.name: ReplacePlaceholderWithImageSpan001
 * @tc.desc: test ReplacePlaceholderWithImageSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, ReplacePlaceholderWithImageSpan001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    EXPECT_NE(spanItem, nullptr);
    size_t index = 1;
    size_t textIndex = 1;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->ReplacePlaceholderWithImageSpan(spanItem, index, textIndex);
    EXPECT_EQ(richEditorPattern->textSelector_.IsValid(), false);
    EXPECT_EQ(textIndex, PLACEHOLDER_LENGTH + index);
}

/**
 * @tc.name: ReplacePlaceholderWithImageSpan002
 * @tc.desc: test ReplacePlaceholderWithImageSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, ReplacePlaceholderWithImageSpan002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    EXPECT_NE(spanItem, nullptr);
    size_t index = 1;
    size_t textIndex = 1;
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->ReplacePlaceholderWithImageSpan(spanItem, index, textIndex);
    EXPECT_EQ(textIndex, PLACEHOLDER_LENGTH + index);
}

/**
 * @tc.name: ReplacePlaceholderWithRawSpans001
 * @tc.desc: test ReplacePlaceholderWithRawSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, ReplacePlaceholderWithRawSpans001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto customSpanItem = AceType::MakeRefPtr<NG::CustomSpanItem>();
    ASSERT_NE(customSpanItem, nullptr);

    customSpanItem->spanItemType = SpanItemType::CustomSpan;
    auto builderId = ElementRegister::GetInstance()->MakeUniqueId();
    auto builderNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, builderId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    customSpanItem->SetCustomNode(builderNode);
    size_t index = 0;
    size_t textIndex = 0;
    size_t sum = 6;
    richEditorPattern->ReplacePlaceholderWithRawSpans(customSpanItem, index, textIndex);
    EXPECT_EQ(textIndex, sum);
}

/**
 * @tc.name: ReplacePlaceholderWithRawSpans002
 * @tc.desc: test ReplacePlaceholderWithRawSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, ReplacePlaceholderWithRawSpans002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto imageSpanItem = AceType::MakeRefPtr<NG::ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);

    imageSpanItem->spanItemType = SpanItemType::IMAGE;
    size_t index = 0;
    size_t textIndex = 0;
    size_t sum = 6;
    richEditorPattern->ReplacePlaceholderWithRawSpans(imageSpanItem, index, textIndex);
    EXPECT_EQ(textIndex, sum);
}

/**
 * @tc.name: ReplacePlaceholderWithRawSpans003
 * @tc.desc: test ReplacePlaceholderWithRawSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderSpanTestNg, ReplacePlaceholderWithRawSpans003, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto imageSpanItem = AceType::MakeRefPtr<NG::ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);

    imageSpanItem->spanItemType = SpanItemType::PLACEHOLDER;
    size_t index = 0;
    size_t textIndex = 0;
    richEditorPattern->ReplacePlaceholderWithRawSpans(imageSpanItem, index, textIndex);
    EXPECT_EQ(textIndex, 0);
}

}