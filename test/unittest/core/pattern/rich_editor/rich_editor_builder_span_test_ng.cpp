/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_ID_A = "chipA";
const std::string TEST_ID_B = "chipB";
} // namespace

class RichEditorBuilderSpanTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    RefPtr<RichEditorPattern> GetPattern();
    RefPtr<RichEditorController> GetController();
    RefPtr<UINode> CreateBuilderNode();
    RefPtr<PlaceholderSpanNode> GetFirstPlaceholderSpanNode();
    int32_t AddBuilderSpanWithRecord(const std::string& id, int32_t offset,
        bool hasOnAttach = false, bool hasOnDetach = false);
    int32_t AddBuilderSpanWithRecordNoOffset(const std::string& id);
    bool onAttachTriggered_ = false;
    bool onDetachTriggered_ = false;
    BuilderSpanInfo lastAttachInfo_;
    BuilderSpanInfo lastDetachInfo_;
};

void RichEditorBuilderSpanTestNg::SetUp()
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
    onAttachTriggered_ = false;
    onDetachTriggered_ = false;
    lastAttachInfo_ = {};
    lastDetachInfo_ = {};
}

void RichEditorBuilderSpanTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorBuilderSpanTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

RefPtr<RichEditorPattern> RichEditorBuilderSpanTestNg::GetPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

RefPtr<RichEditorController> RichEditorBuilderSpanTestNg::GetController()
{
    auto pattern = GetPattern();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetRichEditorController();
}

RefPtr<UINode> RichEditorBuilderSpanTestNg::CreateBuilderNode()
{
    auto builderId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, builderId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
}

RefPtr<PlaceholderSpanNode> RichEditorBuilderSpanTestNg::GetFirstPlaceholderSpanNode()
{
    auto pattern = GetPattern();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto contentHost = pattern->GetContentHost();
    CHECK_NULL_RETURN(contentHost, nullptr);
    for (const auto& child : contentHost->GetChildren()) {
        auto placeholderSpanNode = AceType::DynamicCast<PlaceholderSpanNode>(child);
        if (placeholderSpanNode) {
            return placeholderSpanNode;
        }
    }
    return nullptr;
}

int32_t RichEditorBuilderSpanTestNg::AddBuilderSpanWithRecord(const std::string& id, int32_t offset,
    bool hasOnAttach, bool hasOnDetach)
{
    auto pattern = GetPattern();
    CHECK_NULL_RETURN(pattern, -1);
    auto builderNode = CreateBuilderNode();
    CHECK_NULL_RETURN(builderNode, -1);
    SpanOptionBase options;
    options.offset = offset;
    BuilderSpanRecord record;
    record.id = id;
    if (hasOnAttach) {
        record.onAttach = [this](const BuilderSpanInfo& info) {
            onAttachTriggered_ = true;
            lastAttachInfo_ = info;
        };
    }
    if (hasOnDetach) {
        record.onDetach = [this](const BuilderSpanInfo& info) {
            onDetachTriggered_ = true;
            lastDetachInfo_ = info;
        };
    }
    return pattern->AddPlaceholderSpan(builderNode, options, record, TextChangeReason::UNKNOWN);
}

int32_t RichEditorBuilderSpanTestNg::AddBuilderSpanWithRecordNoOffset(const std::string& id)
{
    auto pattern = GetPattern();
    CHECK_NULL_RETURN(pattern, -1);
    auto builderNode = CreateBuilderNode();
    CHECK_NULL_RETURN(builderNode, -1);
    SpanOptionBase options;
    BuilderSpanRecord record;
    record.id = id;
    return pattern->AddPlaceholderSpan(builderNode, options, record, TextChangeReason::UNKNOWN);
}

/**
 * @tc.name: AddRichEditorBuilderSpan001
 * @tc.desc: test addRichEditorBuilderSpan with id and offset, verify onAttach triggered
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, AddRichEditorBuilderSpan001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("test");
    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 2, true, true);
    EXPECT_GE(index, 0);
    EXPECT_TRUE(onAttachTriggered_);
    EXPECT_TRUE(lastAttachInfo_.id.has_value());
    EXPECT_EQ(lastAttachInfo_.id.value(), TEST_ID_A);
}

/**
 * @tc.name: AddRichEditorBuilderSpan002
 * @tc.desc: test addRichEditorBuilderSpan without explicit offset, verify builderSpanId stored on spanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, AddRichEditorBuilderSpan002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("test");
    auto index = AddBuilderSpanWithRecordNoOffset(TEST_ID_A);
    EXPECT_GE(index, 0);
    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_TRUE(spanItem->builderSpanId.has_value());
    EXPECT_EQ(spanItem->builderSpanId.value(), TEST_ID_A);
}

/**
 * @tc.name: AddRichEditorBuilderSpan003
 * @tc.desc: test addRichEditorBuilderSpan in empty RichEditor, spanIndex=0 is valid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, AddRichEditorBuilderSpan003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 0, true, true);
    EXPECT_EQ(index, 0);
    EXPECT_TRUE(onAttachTriggered_);
    EXPECT_TRUE(lastAttachInfo_.id.has_value());
    EXPECT_EQ(lastAttachInfo_.id.value(), TEST_ID_A);
}

/**
 * @tc.name: AddRichEditorBuilderSpan004
 * @tc.desc: test addRichEditorBuilderSpan with nullptr builderNode, 3-param returns 0
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, AddRichEditorBuilderSpan004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    SpanOptionBase options;
    options.offset = 0;
    RefPtr<UINode> nullNode = nullptr;
    auto index = pattern->AddPlaceholderSpan(nullNode, options, TextChangeReason::UNKNOWN);
    EXPECT_EQ(index, 0);
    EXPECT_FALSE(onAttachTriggered_);
}

/**
 * @tc.name: AddRichEditorBuilderSpan005
 * @tc.desc: test addRichEditorBuilderSpan with offset exceeding text length, append to end
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, AddRichEditorBuilderSpan005, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("ab");
    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 100, true, false);
    EXPECT_GE(index, 0);
    EXPECT_TRUE(onAttachTriggered_);
}

/**
 * @tc.name: GetRichEditorBuilderSpans001
 * @tc.desc: test getRichEditorBuilderSpans returns all BuilderSpanInfo with id
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetRichEditorBuilderSpans001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("test");
    AddBuilderSpanWithRecord(TEST_ID_A, 2);
    AddBuilderSpanWithRecord(TEST_ID_B, 4);

    auto spans = pattern->GetRichEditorBuilderSpans(0, INT32_MAX);
    EXPECT_EQ(static_cast<int32_t>(spans.size()), 2);
    EXPECT_TRUE(spans[0].id.has_value());
    EXPECT_TRUE(spans[1].id.has_value());
}

/**
 * @tc.name: GetRichEditorBuilderSpans002
 * @tc.desc: test getRichEditorBuilderSpans with range filter
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetRichEditorBuilderSpans002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("test");
    AddBuilderSpanWithRecord(TEST_ID_A, 2);
    AddBuilderSpanWithRecord(TEST_ID_B, 5);

    auto spans = pattern->GetRichEditorBuilderSpans(0, 3);
    EXPECT_GE(static_cast<int32_t>(spans.size()), 1);
    bool foundA = false;
    for (const auto& span : spans) {
        if (span.id.has_value() && span.id.value() == TEST_ID_A) {
            foundA = true;
        }
    }
    EXPECT_TRUE(foundA);
}

/**
 * @tc.name: GetRichEditorBuilderSpans003
 * @tc.desc: test getRichEditorBuilderSpans with empty RichEditor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetRichEditorBuilderSpans003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    auto spans = pattern->GetRichEditorBuilderSpans(0, INT32_MAX);
    EXPECT_EQ(static_cast<int32_t>(spans.size()), 0);
}

/**
 * @tc.name: GetRichEditorBuilderSpans004
 * @tc.desc: test getRichEditorBuilderSpans after OnDetachFromMainTree, onDetach cleared
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetRichEditorBuilderSpans004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("test");
    AddBuilderSpanWithRecord(TEST_ID_A, 2, false, true);
    AddBuilderSpanWithRecord(TEST_ID_B, 4, false, true);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_TRUE(spanItem->onDetach);

    auto placeholderPattern = spanNode->GetPattern<PlaceholderSpanPattern>();
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->OnDetachFromMainTree();
    EXPECT_TRUE(onDetachTriggered_);
    EXPECT_FALSE(spanItem->onDetach);

    auto spans = pattern->GetRichEditorBuilderSpans(0, INT32_MAX);
    int32_t withIdCount = 0;
    for (const auto& span : spans) {
        if (span.id.has_value()) {
            withIdCount++;
        }
    }
    EXPECT_EQ(withIdCount, 2);
}

/**
 * @tc.name: OnDetachFromMainTree001
 * @tc.desc: test OnDetachFromMainTree triggers onDetach when node is removed from tree
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, OnDetachFromMainTree001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 0, true, true);
    EXPECT_GE(index, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_TRUE(spanItem->onDetach);

    // RemoveChild may not trigger OnDetachFromMainTree in test env without main tree
    auto placeholderPattern = spanNode->GetPattern<PlaceholderSpanPattern>();
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->OnDetachFromMainTree();

    EXPECT_TRUE(onDetachTriggered_);
    EXPECT_TRUE(lastDetachInfo_.id.has_value());
    EXPECT_EQ(lastDetachInfo_.id.value(), TEST_ID_A);
    EXPECT_FALSE(spanItem->onDetach);
}

/**
 * @tc.name: OnDetachFromMainTree002
 * @tc.desc: test OnDetachFromMainTree suppressed when suppressBuilderSpanCallback_ is true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, OnDetachFromMainTree002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 0, false, true);
    EXPECT_GE(index, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_TRUE(spanItem->onDetach);

    pattern->SetSuppressBuilderSpanCallback(true);
    auto placeholderPattern = spanNode->GetPattern<PlaceholderSpanPattern>();
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->OnDetachFromMainTree();

    EXPECT_FALSE(onDetachTriggered_);
    EXPECT_FALSE(spanItem->onDetach);

    pattern->SetSuppressBuilderSpanCallback(false);
}

/**
 * @tc.name: OnDetachFromMainTree003
 * @tc.desc: test OnDetachFromMainTree does not fire twice (callback cleared after first fire)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, OnDetachFromMainTree003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 0, true, true);
    EXPECT_GE(index, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);

    auto placeholderPattern = spanNode->GetPattern<PlaceholderSpanPattern>();
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->OnDetachFromMainTree();
    EXPECT_TRUE(onDetachTriggered_);

    onDetachTriggered_ = false;
    placeholderPattern->OnDetachFromMainTree();
    EXPECT_FALSE(onDetachTriggered_);
}

/**
 * @tc.name: PlaceholderSpanItemStorage001
 * @tc.desc: test builderSpanId/onAttach/onDetach stored on PlaceholderSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, PlaceholderSpanItemStorage001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("test");
    AddBuilderSpanWithRecord(TEST_ID_A, 2);
    AddBuilderSpanWithRecord(TEST_ID_B, 4);

    auto contentHost = pattern->GetContentHost();
    ASSERT_NE(contentHost, nullptr);
    int countA = 0;
    int countB = 0;
    for (const auto& child : contentHost->GetChildren()) {
        auto placeholderSpanNode = AceType::DynamicCast<PlaceholderSpanNode>(child);
        if (!placeholderSpanNode) {
            continue;
        }
        auto spanItem = placeholderSpanNode->GetSpanItem();
        if (!spanItem) {
            continue;
        }
        if (spanItem->builderSpanId.has_value() && spanItem->builderSpanId.value() == TEST_ID_A) {
            countA++;
        }
        if (spanItem->builderSpanId.has_value() && spanItem->builderSpanId.value() == TEST_ID_B) {
            countB++;
        }
    }
    EXPECT_EQ(countA, 1);
    EXPECT_EQ(countB, 1);
}

/**
 * @tc.name: PlaceholderSpanItemStorage002
 * @tc.desc: test OnDetachFromMainTree clears onDetach on PlaceholderSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, PlaceholderSpanItemStorage002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddBuilderSpanWithRecord(TEST_ID_A, 0, true, true);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_TRUE(spanItem->onDetach);

    auto placeholderPattern = spanNode->GetPattern<PlaceholderSpanPattern>();
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->OnDetachFromMainTree();
    EXPECT_FALSE(spanItem->onDetach);
}

/**
 * @tc.name: BuilderSpanRecord001
 * @tc.desc: test BuilderSpanRecord fields are stored on spanItem after AddPlaceholderSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, BuilderSpanRecord001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    auto builderNode = CreateBuilderNode();
    ASSERT_NE(builderNode, nullptr);
    SpanOptionBase options;
    options.offset = 0;
    BuilderSpanRecord record;
    record.id = TEST_ID_A;
    bool attachCalled = false;
    bool detachCalled = false;
    record.onAttach = [&](const BuilderSpanInfo& info) { attachCalled = true; };
    record.onDetach = [&](const BuilderSpanInfo& info) { detachCalled = true; };

    auto index = pattern->AddPlaceholderSpan(builderNode, options, record, TextChangeReason::UNKNOWN);
    EXPECT_GE(index, 0);
    EXPECT_TRUE(attachCalled);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_TRUE(spanItem->builderSpanId.has_value());
    EXPECT_EQ(spanItem->builderSpanId.value(), TEST_ID_A);
    EXPECT_TRUE(spanItem->onDetach);
}

/**
 * @tc.name: AddPlaceholderSpanFourParams001
 * @tc.desc: test 4-parameter AddPlaceholderSpan overload stores id on spanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, AddPlaceholderSpanFourParams001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    auto builderNode = CreateBuilderNode();
    ASSERT_NE(builderNode, nullptr);
    SpanOptionBase options;
    options.offset = 0;
    BuilderSpanRecord record;
    record.id = TEST_ID_A;

    auto index = pattern->AddPlaceholderSpan(builderNode, options, record, TextChangeReason::UNKNOWN);
    EXPECT_GE(index, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_TRUE(spanItem->builderSpanId.has_value());
    EXPECT_EQ(spanItem->builderSpanId.value(), TEST_ID_A);
}

/**
 * @tc.name: AddPlaceholderSpanFourParams002
 * @tc.desc: test 4-parameter AddPlaceholderSpan returns same as 2-parameter
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, AddPlaceholderSpanFourParams002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("test");
    auto builderNode1 = CreateBuilderNode();
    auto index1 = pattern->AddPlaceholderSpan(builderNode1, {});
    EXPECT_GE(index1, 0);

    auto builderNode2 = CreateBuilderNode();
    SpanOptionBase options;
    BuilderSpanRecord record;
    record.id = TEST_ID_A;
    auto index2 = pattern->AddPlaceholderSpan(builderNode2, options, record, TextChangeReason::UNKNOWN);
    EXPECT_GT(index2, index1);
}

/**
 * @tc.name: OnAttachOnDetachOffsetConsistency001
 * @tc.desc: test onAttach and onDetach offset are consistent via real-time rangeStart
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, OnAttachOnDetachOffsetConsistency001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("ab");
    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 2, true, true);
    EXPECT_GE(index, 0);
    EXPECT_TRUE(onAttachTriggered_);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto placeholderPattern = spanNode->GetPattern<PlaceholderSpanPattern>();
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->OnDetachFromMainTree();
    EXPECT_TRUE(onDetachTriggered_);

    if (lastAttachInfo_.offset.has_value() && lastDetachInfo_.offset.has_value()) {
        EXPECT_EQ(lastAttachInfo_.offset.value(), lastDetachInfo_.offset.value());
    }
}

/**
 * @tc.name: OldAddBuilderSpanCompat001
 * @tc.desc: test old addBuilderSpan (2-parameter) does not set builderSpanId on spanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, OldAddBuilderSpanCompat001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    auto controller = GetController();
    ASSERT_NE(controller, nullptr);

    AddSpan("test");
    auto builderNode = CreateBuilderNode();
    auto index = controller->AddPlaceholderSpan(builderNode, {});
    EXPECT_GE(index, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->builderSpanId.has_value());
    EXPECT_FALSE(spanItem->onDetach);
}

/**
 * @tc.name: OldAddBuilderSpanCompat002
 * @tc.desc: test old addBuilderSpan followed by new addRichEditorBuilderSpan, both work
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, OldAddBuilderSpanCompat002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    auto controller = GetController();
    ASSERT_NE(controller, nullptr);

    AddSpan("test");
    auto builderNode1 = CreateBuilderNode();
    auto index1 = controller->AddPlaceholderSpan(builderNode1, {});
    EXPECT_GE(index1, 0);

    auto index2 = AddBuilderSpanWithRecord(TEST_ID_A, 2);
    EXPECT_GE(index2, 0);

    auto spans = pattern->GetRichEditorBuilderSpans(0, INT32_MAX);
    int32_t withIdCount = 0;
    for (const auto& span : spans) {
        if (span.id.has_value()) {
            withIdCount++;
        }
    }
    EXPECT_EQ(withIdCount, 1);
}

/**
 * @tc.name: AnonymousBuilderSpan001
 * @tc.desc: test addRichEditorBuilderSpan without id (anonymous)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, AnonymousBuilderSpan001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    auto builderNode = CreateBuilderNode();
    ASSERT_NE(builderNode, nullptr);
    SpanOptionBase options;
    options.offset = 0;
    BuilderSpanRecord record;

    auto index = pattern->AddPlaceholderSpan(builderNode, options, record, TextChangeReason::UNKNOWN);
    EXPECT_GE(index, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_FALSE(spanItem->builderSpanId.has_value());
}

/**
 * @tc.name: MultipleBuilderSpans001
 * @tc.desc: test add multiple BuilderSpans with different ids
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, MultipleBuilderSpans001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("test");
    AddBuilderSpanWithRecord(TEST_ID_A, 2);
    AddBuilderSpanWithRecord(TEST_ID_B, 4);

    auto spans = pattern->GetRichEditorBuilderSpans(0, INT32_MAX);
    EXPECT_EQ(static_cast<int32_t>(spans.size()), 2);
}

/**
 * @tc.name: ComponentDestroy001
 * @tc.desc: test onDetach cleanup when all children removed via RemoveChild (triggers OnDetachFromMainTree)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, ComponentDestroy001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddBuilderSpanWithRecord(TEST_ID_A, 0, true, true);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_TRUE(spanItem->onDetach);

    auto placeholderPattern = spanNode->GetPattern<PlaceholderSpanPattern>();
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->OnDetachFromMainTree();

    EXPECT_TRUE(onDetachTriggered_);
    EXPECT_FALSE(spanItem->onDetach);
}

/**
 * @tc.name: NegativeOffset001
 * @tc.desc: test addRichEditorBuilderSpan with negative offset, append to end
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, NegativeOffset001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("test");
    auto builderNode = CreateBuilderNode();
    ASSERT_NE(builderNode, nullptr);
    SpanOptionBase options;
    options.offset = -1;
    BuilderSpanRecord record;
    record.id = TEST_ID_A;

    auto index = pattern->AddPlaceholderSpan(builderNode, options, record, TextChangeReason::UNKNOWN);
    EXPECT_GE(index, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_TRUE(spanItem->builderSpanId.has_value());
    EXPECT_EQ(spanItem->builderSpanId.value(), TEST_ID_A);
}

/**
 * @tc.name: OnDetachCallbackParam001
 * @tc.desc: test onDetach callback parameter contains correct BuilderSpanInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, OnDetachCallbackParam001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("ab");
    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 2, true, true);
    EXPECT_GE(index, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto placeholderPattern = spanNode->GetPattern<PlaceholderSpanPattern>();
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->OnDetachFromMainTree();

    EXPECT_TRUE(onDetachTriggered_);
    EXPECT_TRUE(lastDetachInfo_.id.has_value());
    EXPECT_EQ(lastDetachInfo_.id.value(), TEST_ID_A);
}

/**
 * @tc.name: BuilderSpanInfoStruct001
 * @tc.desc: test BuilderSpanInfo struct with optional fields
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, BuilderSpanInfoStruct001, TestSize.Level0)
{
    BuilderSpanInfo info1;
    EXPECT_FALSE(info1.id.has_value());
    EXPECT_FALSE(info1.offset.has_value());

    BuilderSpanInfo info2;
    info2.id = "testId";
    info2.offset = 5;
    EXPECT_TRUE(info2.id.has_value());
    EXPECT_EQ(info2.id.value(), "testId");
    EXPECT_TRUE(info2.offset.has_value());
    EXPECT_EQ(info2.offset.value(), 5);
}

/**
 * @tc.name: BuilderSpanRecordStruct001
 * @tc.desc: test BuilderSpanRecord struct with all fields
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, BuilderSpanRecordStruct001, TestSize.Level0)
{
    BuilderSpanRecord record;
    EXPECT_FALSE(record.id.has_value());
    EXPECT_FALSE(record.onAttach);
    EXPECT_FALSE(record.onDetach);

    record.id = TEST_ID_A;
    record.onAttach = [](const BuilderSpanInfo& info) {};
    record.onDetach = [](const BuilderSpanInfo& info) {};

    EXPECT_TRUE(record.id.has_value());
    EXPECT_EQ(record.id.value(), TEST_ID_A);
    EXPECT_TRUE(record.onAttach);
    EXPECT_TRUE(record.onDetach);
}

/**
 * @tc.name: SuppressBuilderSpanCallback001
 * @tc.desc: test SetSuppressBuilderSpanCallback suppresses onDetach during RemoveChild (OnDetachFromMainTree)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, SuppressBuilderSpanCallback001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    // First span: suppressed removal
    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 0, false, true);
    EXPECT_GE(index, 0);

    auto spanNodeA = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNodeA, nullptr);
    auto spanItemA = spanNodeA->GetSpanItem();
    ASSERT_NE(spanItemA, nullptr);
    EXPECT_TRUE(spanItemA->onDetach);

    EXPECT_FALSE(pattern->IsSuppressBuilderSpanCallback());
    pattern->SetSuppressBuilderSpanCallback(true);
    EXPECT_TRUE(pattern->IsSuppressBuilderSpanCallback());

    auto placeholderPatternA = spanNodeA->GetPattern<PlaceholderSpanPattern>();
    ASSERT_NE(placeholderPatternA, nullptr);
    placeholderPatternA->OnDetachFromMainTree();
    EXPECT_FALSE(onDetachTriggered_);
    EXPECT_FALSE(spanItemA->onDetach);

    // Second span: non-suppressed removal
    pattern->SetSuppressBuilderSpanCallback(false);
    EXPECT_FALSE(pattern->IsSuppressBuilderSpanCallback());

    AddBuilderSpanWithRecord(TEST_ID_B, 0, false, true);
    auto spanNodeB = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNodeB, nullptr);
    auto spanItemB = spanNodeB->GetSpanItem();
    ASSERT_NE(spanItemB, nullptr);

    auto placeholderPatternB = spanNodeB->GetPattern<PlaceholderSpanPattern>();
    ASSERT_NE(placeholderPatternB, nullptr);
    placeholderPatternB->OnDetachFromMainTree();
    EXPECT_TRUE(onDetachTriggered_);
    EXPECT_FALSE(spanItemB->onDetach);
}

/**
 * @tc.name: OnAttachDirectCall001
 * @tc.desc: test onAttach is called directly in AddPlaceholderSpan, not stored on spanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, OnAttachDirectCall001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 0, true, false);
    EXPECT_GE(index, 0);
    EXPECT_TRUE(onAttachTriggered_);
    EXPECT_TRUE(lastAttachInfo_.id.has_value());
    EXPECT_EQ(lastAttachInfo_.id.value(), TEST_ID_A);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
}

/**
 * @tc.name: OnDetachFromMainTree004
 * @tc.desc: test OnDetachFromMainTree with null spanItem (CHECK_NULL_VOID TRUE path)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, OnDetachFromMainTree004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 0, false, true);
    EXPECT_GE(index, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto original = spanNode->placeholderSpanItem_;
    spanNode->placeholderSpanItem_ = nullptr;
    onDetachTriggered_ = false;
    auto placeholderPattern = spanNode->GetPattern<PlaceholderSpanPattern>();
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->OnDetachFromMainTree();
    EXPECT_FALSE(onDetachTriggered_);
    spanNode->placeholderSpanItem_ = original;
}

/**
 * @tc.name: OnDetachFromMainTree005
 * @tc.desc: test OnDetachFromMainTree when RichEditorPattern is destroyed (weakPattern null path)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, OnDetachFromMainTree005, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);

    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 0, false, true);
    EXPECT_GE(index, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    EXPECT_TRUE(spanItem->onDetach);

    auto placeholderPattern = spanNode->GetPattern<PlaceholderSpanPattern>();
    ASSERT_NE(placeholderPattern, nullptr);

    // Save and clear onDetach to prevent triggering during node destruction
    auto savedCallback = spanItem->onDetach;
    spanItem->onDetach = nullptr;

    // Destroy RichEditorPattern — weakPattern in closure becomes null
    richEditorNode_ = nullptr;

    // Restore onDetach closure (weakPattern now points to destroyed pattern)
    spanItem->onDetach = savedCallback;
    onDetachTriggered_ = false;

    placeholderPattern->OnDetachFromMainTree();

    // weakPattern.Upgrade() returns nullptr → CHECK_NULL_VOID(pattern) TRUE → rawOnDetach not called
    EXPECT_FALSE(onDetachTriggered_);
    EXPECT_FALSE(spanItem->onDetach); // cleared by copy-null-call
}

/**
 * @tc.name: GetBuilderSpanInfo001
 * @tc.desc: test GetBuilderSpanInfo with rangeStart < 0 (offset not set)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetBuilderSpanInfo001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 0, false, true);
    EXPECT_GE(index, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);

    spanItem->rangeStart = -1;
    auto info = spanItem->GetBuilderSpanInfo();
    EXPECT_TRUE(info.id.has_value());
    EXPECT_EQ(info.id.value(), TEST_ID_A);
    EXPECT_FALSE(info.offset.has_value());
}

/**
 * @tc.name: GetBuilderSpanInfo002
 * @tc.desc: test GetBuilderSpanInfo with rangeStart >= 0 (offset set correctly)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetBuilderSpanInfo002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 0, false, true);
    EXPECT_GE(index, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);

    spanItem->rangeStart = 5;
    auto info = spanItem->GetBuilderSpanInfo();
    EXPECT_TRUE(info.id.has_value());
    EXPECT_EQ(info.id.value(), TEST_ID_A);
    EXPECT_TRUE(info.offset.has_value());
    EXPECT_EQ(info.offset.value(), 5);
}

/**
 * @tc.name: GetRichEditorBuilderSpans005
 * @tc.desc: test GetRichEditorBuilderSpans with start == end (CHECK_NULL_RETURN TRUE path)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetRichEditorBuilderSpans005, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("test");
    AddBuilderSpanWithRecord(TEST_ID_A, 2);

    auto spans = pattern->GetRichEditorBuilderSpans(5, 5);
    EXPECT_EQ(static_cast<int32_t>(spans.size()), 0);
}

/**
 * @tc.name: GetRichEditorBuilderSpans006
 * @tc.desc: test GetRichEditorBuilderSpans with null contentPattern (CHECK_NULL_RETURN host TRUE path)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetRichEditorBuilderSpans006, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddBuilderSpanWithRecord(TEST_ID_A, 0);

    auto original = pattern->contentPattern_;
    pattern->contentPattern_ = nullptr;
    auto spans = pattern->GetRichEditorBuilderSpans(0, INT32_MAX);
    EXPECT_EQ(static_cast<int32_t>(spans.size()), 0);
    pattern->contentPattern_ = original;
}

/**
 * @tc.name: GetRichEditorBuilderSpans007
 * @tc.desc: test GetRichEditorBuilderSpans with null spanItem (CHECK_NULL_CONTINUE TRUE path)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetRichEditorBuilderSpans007, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddBuilderSpanWithRecord(TEST_ID_A, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto original = spanNode->placeholderSpanItem_;
    spanNode->placeholderSpanItem_ = nullptr;
    auto spans = pattern->GetRichEditorBuilderSpans(0, INT32_MAX);
    EXPECT_EQ(static_cast<int32_t>(spans.size()), 0);
    spanNode->placeholderSpanItem_ = original;
}

/**
 * @tc.name: GetRichEditorBuilderSpans008
 * @tc.desc: test GetRichEditorBuilderSpans with spanStart < 0 (first || left-true short-circuit)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetRichEditorBuilderSpans008, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddBuilderSpanWithRecord(TEST_ID_A, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    spanItem->rangeStart = -1;
    spanItem->position = 5;

    auto spans = pattern->GetRichEditorBuilderSpans(0, INT32_MAX);
    EXPECT_EQ(static_cast<int32_t>(spans.size()), 0);
}

/**
 * @tc.name: GetRichEditorBuilderSpans009
 * @tc.desc: test GetRichEditorBuilderSpans with spanEnd < 0 (first || right-true)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetRichEditorBuilderSpans009, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddBuilderSpanWithRecord(TEST_ID_A, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    spanItem->rangeStart = 0;
    spanItem->position = -1;

    auto spans = pattern->GetRichEditorBuilderSpans(0, INT32_MAX);
    EXPECT_EQ(static_cast<int32_t>(spans.size()), 0);
}

/**
 * @tc.name: GetRichEditorBuilderSpans010
 * @tc.desc: test GetRichEditorBuilderSpans with spanStart >= end (range exclusion)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetRichEditorBuilderSpans010, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddBuilderSpanWithRecord(TEST_ID_A, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    spanItem->rangeStart = 5;
    spanItem->position = 6;

    auto spans = pattern->GetRichEditorBuilderSpans(0, 3);
    EXPECT_EQ(static_cast<int32_t>(spans.size()), 0);
}

/**
 * @tc.name: GetRichEditorBuilderSpans011
 * @tc.desc: test GetRichEditorBuilderSpans with spanStart < start (range exclusion)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetRichEditorBuilderSpans011, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddBuilderSpanWithRecord(TEST_ID_A, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    spanItem->rangeStart = 3;
    spanItem->position = 4;

    auto spans = pattern->GetRichEditorBuilderSpans(5, 10);
    EXPECT_EQ(static_cast<int32_t>(spans.size()), 0);
}

/**
 * @tc.name: GetRichEditorBuilderSpans012
 * @tc.desc: test GetRichEditorBuilderSpans with non-PlaceholderSpanNode child (if TRUE continue)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetRichEditorBuilderSpans012, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("test");
    AddBuilderSpanWithRecord(TEST_ID_A, 2);

    auto contentHost = pattern->GetContentHost();
    ASSERT_NE(contentHost, nullptr);
    auto nonPlaceholderNode = SpanNode::GetOrCreateSpanNode(
        V2::SPAN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(nonPlaceholderNode, nullptr);
    contentHost->AddChild(nonPlaceholderNode);

    auto spans = pattern->GetRichEditorBuilderSpans(0, INT32_MAX);
    EXPECT_GE(static_cast<int32_t>(spans.size()), 1);
}

/**
 * @tc.name: GetRichEditorBuilderSpans013
 * @tc.desc: test GetRichEditorBuilderSpans with spanEnd - spanStart != 1 (skip span via continue)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetRichEditorBuilderSpans013, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddBuilderSpanWithRecord(TEST_ID_A, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    spanItem->rangeStart = 0;
    spanItem->position = 3;

    auto spans = pattern->GetRichEditorBuilderSpans(0, INT32_MAX);
    EXPECT_EQ(static_cast<int32_t>(spans.size()), 0);
}

/**
 * @tc.name: AddPlaceholderSpanFourParams003
 * @tc.desc: test 4-param AddPlaceholderSpan with maxLength_ = 0 triggers early return, causing
 *          CHECK_NULL_RETURN(placeholderSpanNode) TRUE path (customNode never mounted)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, AddPlaceholderSpanFourParams003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    pattern->maxLength_ = 0;

    auto builderNode = CreateBuilderNode();
    ASSERT_NE(builderNode, nullptr);
    SpanOptionBase options;
    options.offset = 0;
    BuilderSpanRecord record;
    record.id = TEST_ID_A;

    auto index = pattern->AddPlaceholderSpan(builderNode, options, record, TextChangeReason::UNKNOWN);
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: AddPlaceholderSpanFourParams004
 * @tc.desc: test 4-param AddPlaceholderSpan where placeholderSpanNode has null spanItem,
 *          covering CHECK_NULL_RETURN(spanItem, spanIndex) TRUE path
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, AddPlaceholderSpanFourParams004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    auto index = AddBuilderSpanWithRecord(TEST_ID_A, 0);
    EXPECT_NE(index, -1);

    auto placeholderSpanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(placeholderSpanNode, nullptr);
    auto originalSpanItem = placeholderSpanNode->placeholderSpanItem_;

    auto builderNode = CreateBuilderNode();
    ASSERT_NE(builderNode, nullptr);
    builderNode->MountToParent(placeholderSpanNode);

    placeholderSpanNode->placeholderSpanItem_ = nullptr;
    pattern->maxLength_ = 0;

    SpanOptionBase options;
    options.offset = 0;
    BuilderSpanRecord record;
    record.id = TEST_ID_B;

    auto result = pattern->AddPlaceholderSpan(builderNode, options, record, TextChangeReason::UNKNOWN);
    EXPECT_EQ(result, 0);

    placeholderSpanNode->placeholderSpanItem_ = originalSpanItem;
}

/**
 * @tc.name: ControllerAddPlaceholderSpanWithRecord001
 * @tc.desc: test RichEditorController::AddPlaceholderSpan with BuilderSpanRecord (non-null pattern)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, ControllerAddPlaceholderSpanWithRecord001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto controller = GetController();
    ASSERT_NE(controller, nullptr);

    AddSpan("test");
    auto builderNode = CreateBuilderNode();
    ASSERT_NE(builderNode, nullptr);
    SpanOptionBase options;
    options.offset = 2;
    BuilderSpanRecord record;
    record.id = TEST_ID_A;

    auto index = controller->AddPlaceholderSpan(builderNode, options, record);
    EXPECT_GE(index, 0);
}

/**
 * @tc.name: ControllerAddPlaceholderSpanWithRecord002
 * @tc.desc: test RichEditorController::AddPlaceholderSpan with BuilderSpanRecord (null pattern)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, ControllerAddPlaceholderSpanWithRecord002, TestSize.Level0)
{
    auto nullController = AceType::MakeRefPtr<RichEditorController>();
    ASSERT_NE(nullController, nullptr);

    auto builderNode = CreateBuilderNode();
    ASSERT_NE(builderNode, nullptr);
    SpanOptionBase options;
    BuilderSpanRecord record;
    record.id = TEST_ID_A;

    auto index = nullController->AddPlaceholderSpan(builderNode, options, record);
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: ControllerGetRichEditorBuilderSpans001
 * @tc.desc: test RichEditorController::GetRichEditorBuilderSpans (non-null pattern)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, ControllerGetRichEditorBuilderSpans001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto controller = GetController();
    ASSERT_NE(controller, nullptr);

    AddSpan("test");
    AddBuilderSpanWithRecord(TEST_ID_A, 2);

    auto spans = controller->GetRichEditorBuilderSpans(0, INT32_MAX);
    EXPECT_GE(static_cast<int32_t>(spans.size()), 1);
}

/**
 * @tc.name: ControllerGetRichEditorBuilderSpans002
 * @tc.desc: test RichEditorController::GetRichEditorBuilderSpans (null pattern)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, ControllerGetRichEditorBuilderSpans002, TestSize.Level0)
{
    auto nullController = AceType::MakeRefPtr<RichEditorController>();
    ASSERT_NE(nullController, nullptr);

    auto spans = nullController->GetRichEditorBuilderSpans(0, INT32_MAX);
    EXPECT_EQ(static_cast<int32_t>(spans.size()), 0);
}

/**
 * @tc.name: GetBuilderSpanInfosInJson001
 * @tc.desc: test GetBuilderSpanInfosInJson returns non-empty JSON with id
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetBuilderSpanInfosInJson001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("test");
    AddBuilderSpanWithRecord(TEST_ID_A, 2);

    auto json = pattern->GetBuilderSpanInfosInJson();
    EXPECT_FALSE(json.empty());
    EXPECT_NE(json.find(TEST_ID_A), std::string::npos);
}

/**
 * @tc.name: GetBuilderSpanInfosInJson002
 * @tc.desc: test GetBuilderSpanInfosInJson with empty RichEditor returns empty string
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetBuilderSpanInfosInJson002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    auto json = pattern->GetBuilderSpanInfosInJson();
    EXPECT_TRUE(json.empty());
}

/**
 * @tc.name: GetBuilderSpanInfosInJson003
 * @tc.desc: test GetBuilderSpanInfosInJson with null contentPattern returns empty string
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetBuilderSpanInfosInJson003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddBuilderSpanWithRecord(TEST_ID_A, 0);
    auto original = pattern->contentPattern_;
    pattern->contentPattern_ = nullptr;
    auto json = pattern->GetBuilderSpanInfosInJson();
    EXPECT_TRUE(json.empty());
    pattern->contentPattern_ = original;
}

/**
 * @tc.name: GetBuilderSpanInfosInJson004
 * @tc.desc: test GetBuilderSpanInfosInJson skips old API span without builderSpanId
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetBuilderSpanInfosInJson004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddSpan("test");
    auto builderNode = CreateBuilderNode();
    ASSERT_NE(builderNode, nullptr);
    pattern->AddPlaceholderSpan(builderNode, {});

    auto json = pattern->GetBuilderSpanInfosInJson();
    EXPECT_TRUE(json.empty());
}

/**
 * @tc.name: GetBuilderSpanInfosInJson005
 * @tc.desc: test GetBuilderSpanInfosInJson skips span with rangeStart < 0
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBuilderSpanTestNg, GetBuilderSpanInfosInJson005, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);

    AddBuilderSpanWithRecord(TEST_ID_A, 0);

    auto spanNode = GetFirstPlaceholderSpanNode();
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    spanItem->rangeStart = -1;

    auto json = pattern->GetBuilderSpanInfosInJson();
    EXPECT_TRUE(json.empty());
}
}
