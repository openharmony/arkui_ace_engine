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
#include "gtest/gtest.h"

#define private public
#define protected public
#include "core/components_ng/base/page_text_collector.h"
#include "core/components_ng/manager/content_change_manager/content_change_manager.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "core/components_ng/pattern/page_translate/page_translate_node.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/arkoala_lazy_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#undef private
#undef protected
#include "base/json/json_util.h"

namespace OHOS::Ace::NG {
class CountingPageTextLazyBuilder : public OHOS::Ace::Framework::MockLazyForEachBuilder {
    DECLARE_ACE_TYPE(CountingPageTextLazyBuilder, OHOS::Ace::Framework::MockLazyForEachBuilder);
public:
    int builds = 0;
    // 8 total items leave unbuilt entries beyond the children materialized by each lazy-list test.
    int32_t OnGetTotalCount() override { return 8; }
    std::pair<std::string, RefPtr<UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, LazyForEachCacheChild>& items) override
    {
        ++builds;
        return MockLazyForEachBuilder::OnGetChildByIndex(index, items);
    }
    std::pair<std::string, RefPtr<UINode>> OnGetChildByIndexNew(int32_t index,
        std::map<int32_t, LazyForEachChild>& items,
        std::unordered_map<std::string, LazyForEachCacheChild>& expiring) override
    {
        ++builds;
        return MockLazyForEachBuilder::OnGetChildByIndexNew(index, items, expiring);
    }
};

class PageTextCollectorTest : public testing::Test {
public:
    void SetUp() override
    {
        MockPipelineContext::SetUp();
        pipeline = MockPipelineContext::GetCurrent();
        pipeline->uiTranslateManager_ = std::make_shared<UiTranslateManagerImpl>(nullptr);
        MockContainer::SetUp(pipeline);
        MockContainer::Current()->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>());
        stage = FrameNode::CreateFrameNode("stage", 1, AceType::MakeRefPtr<StagePattern>());
        // Node ID 2 identifies the fixture page, distinct from the stage node with ID 1.
        page = FrameNode::CreateFrameNode("page", 2, AceType::MakeRefPtr<PagePattern>(nullptr));
        stage->AddChild(page);
        Mount(stage);
        Mount(page);
        pipeline->stageManager_ = AceType::MakeRefPtr<StageManager>(stage);
    }
    void TearDown() override
    {
        MockContainer::SetGetContainerCallback({});
        page.Reset();
        stage.Reset();
        pipeline.Reset();
        MockContainer::TearDown();
        MockPipelineContext::TearDown();
    }
    void Mount(const RefPtr<FrameNode>& node)
    {
        node->onMainTree_ = true;
        node->SetActive(true);
        auto render = AceType::MakeRefPtr<MockRenderContext>();
        // The 100 x 20 px paint rectangle gives the fixture positive dimensions for text collection.
        render->SetPaintRectWithTransform(RectF(0, 0, 100, 20));
        node->renderContext_ = render;
        // The 100 x 20 px layout size matches the fixture paint rectangle.
        node->GetGeometryNode()->SetFrameSize(SizeF(100, 20));
        pipeline->uiTranslateManager_->AddTranslateListener(WeakPtr<FrameNode>(node));
    }
    RefPtr<FrameNode> Text(int32_t id, std::u16string text, const RefPtr<FrameNode>& parent = nullptr)
    {
        auto pattern = AceType::MakeRefPtr<TextPattern>();
        auto node = FrameNode::CreateFrameNode("Text", id, pattern);
        pattern->textForDisplay_ = std::move(text);
        pattern->MarkPageTranslateTextDrawn();
        (parent ? parent : page)->AddChild(node);
        Mount(node);
        return node;
    }
    std::string Collect()
    {
        char* data = nullptr;
        uint32_t size = 0;
        const char* reason = nullptr;
        EXPECT_EQ(CollectPageText(0, &data, &size, &reason), 0);
        std::string result(data ? data : "", size);
        std::free(data);
        return result;
    }
    RefPtr<FrameNode> UnmountedText(int32_t id, const std::u16string& text)
    {
        auto pattern = AceType::MakeRefPtr<TextPattern>();
        auto node = FrameNode::CreateFrameNode("Text", id, pattern);
        pattern->textForDisplay_ = text;
        pattern->MarkPageTranslateTextDrawn();
        auto render = AceType::MakeRefPtr<MockRenderContext>();
        // The 100 x 20 px paint rectangle makes cached text eligible once its active state permits collection.
        render->SetPaintRectWithTransform(RectF(0, 0, 100, 20));
        node->renderContext_ = render;
        // The 100 x 20 px layout size matches the cached text paint rectangle.
        node->GetGeometryNode()->SetFrameSize(SizeF(100, 20));
        return node;
    }
    void Register(const RefPtr<FrameNode>& node)
    {
        pipeline->uiTranslateManager_->AddTranslateListener(WeakPtr<FrameNode>(node));
    }
    void ExpectContents(const std::vector<std::string>& expected)
    {
        auto json = JsonUtil::ParseJsonString(Collect());
        auto texts = json->GetValue("texts");
        std::vector<std::string> actual;
        for (int32_t i = 0; i < texts->GetArraySize(); ++i) {
            actual.push_back(texts->GetArrayItem(i)->GetString("content"));
        }
        EXPECT_EQ(actual, expected);
    }
    RefPtr<MockPipelineContext> pipeline;
    RefPtr<FrameNode> stage;
    RefPtr<FrameNode> page;
};

TEST_F(PageTextCollectorTest, emptyRegistryAndMissingPageOrManager)
{
    EXPECT_EQ(Collect(), "{\"texts\":[]}");
    auto node = Text(3, u"registered");
    pipeline->stageManager_.Reset();
    ExpectContents({ "registered" });
    pipeline->uiTranslateManager_.reset();
    EXPECT_EQ(Collect(), "{\"texts\":[]}");
}

TEST_F(PageTextCollectorTest, registryOrderDuplicatesAndIndependentNestedCarriers)
{
    auto first = Text(30, u"same");
    // Node ID 4 sorts before its parent ID 30, checking independent nested-carrier collection.
    Text(4, u"internal", first);
    // Node ID 5 provides a second carrier with the same text, which must not be deduplicated.
    Text(5, u"same");
    // Node ID 6 identifies the empty-text carrier that must be omitted.
    Text(6, u"");
    // Node ID 7 identifies the whitespace-only carrier that must be retained.
    Text(7, u" ");
    ExpectContents({ "internal", "same", " ", "same" });
    page->RemoveChild(first);
    page->AddChild(first);
    ExpectContents({ "internal", "same", " ", "same" });
}

TEST_F(PageTextCollectorTest, registryEligibilityMatchesOriginalTranslationReport)
{
    auto hidden = Text(3, u"self hidden");
    hidden->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
    auto inactive = Text(4, u"inactive");
    inactive->SetActive(false);
    auto detached = Text(5, u"detached");
    detached->onMainTree_ = false;
    auto ancestor = FrameNode::CreateFrameNode("Column", 6, AceType::MakeRefPtr<Pattern>());
    page->AddChild(ancestor);
    Mount(ancestor);
    ancestor->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
    // Node ID 7 identifies the child excluded because its ancestor is hidden.
    Text(7, u"hidden ancestor", ancestor);
    auto outside = Text(8, u"outside");
    AceType::DynamicCast<MockRenderContext>(outside->GetRenderContext())->SetPaintRectWithTransform(
        // Position (-10000, 5000) px places the 100 x 20 px text far outside the usual viewport.
        RectF(-10000, 5000, 100, 20));
    auto zero = Text(9, u"zero transform");
    AceType::DynamicCast<MockRenderContext>(zero->GetRenderContext())->SetPaintRectWithTransform(RectF());
    // Node ID 10 identifies the carrier whose registration is removed before collection.
    auto unregistered = Text(10, u"unregistered");
    // Remove the registration for node ID 10 while keeping the node alive in the tree.
    pipeline->uiTranslateManager_->RemoveTranslateListener(10);
    ExpectContents({ "self hidden", "detached", "outside" });
    // Use the real report filter as the oracle; only its service transport is mocked.
    auto manager = AceType::MakeRefPtr<ContentChangeManager>();
    manager->StartTextTranslateSnapshotReport();
    pipeline->uiTranslateManager_->ForEachArkUITranslateFrameNode([&](const WeakPtr<FrameNode>& node) {
        manager->ReportTranslateTextFrameNode(node, false);
    });
    auto json = JsonUtil::ParseJsonString(Collect());
    auto texts = json->GetValue("texts");
    ASSERT_EQ(texts->GetArraySize(), manager->translateTextSnapshotVersions_.size());
    for (int32_t i = 0; i < texts->GetArraySize(); ++i) {
        EXPECT_EQ(manager->translateTextSnapshotVersions_.count(texts->GetArrayItem(i)->GetInt("id")), 1U);
    }
}

TEST_F(PageTextCollectorTest, textDrawGateSourceSelectionAndSnapshot)
{
    auto node = Text(3, u"source");
    auto pattern = node->GetPattern<TextPattern>();
    pattern->lastDrawnPageTranslateContent_.clear();
    EXPECT_EQ(Collect(), "{\"texts\":[]}");
    EXPECT_TRUE(pattern->lastDrawnPageTranslateContent_.empty());
    pattern->MarkPageTranslateTextDrawn();
    auto old = Collect();
    pattern->pageTranslatedContent_ = u"translation";
    EXPECT_EQ(Collect(), old);
    pattern->textForDisplay_ = u"changed";
    EXPECT_EQ(Collect(), "{\"texts\":[]}");
    EXPECT_EQ(pattern->lastDrawnPageTranslateContent_, u"source");
    pattern->MarkPageTranslateTextDrawn();
    EXPECT_NE(Collect().find("changed"), std::string::npos);
    EXPECT_NE(old.find("source"), std::string::npos);
}

TEST_F(PageTextCollectorTest, obscuredAndSpanContentMatchesOriginalGetter)
{
    auto node = Text(3, u"source \ufffc symbol");
    auto pattern = node->GetPattern<TextPattern>();
    auto span = AceType::MakeRefPtr<SpanItem>();
    span->content = u"must not independently aggregate";
    pattern->spans_.push_back(span);
    node->GetRenderContext()->UpdateObscured({ ObscuredReasons::PLACEHOLDER });
    pattern->pageTranslatedContent_ = u"translated display";
    auto expected = pattern->GetPageTranslateTextForReport();
    auto json = JsonUtil::ParseJsonString(Collect());
    auto texts = json->GetValue("texts");
    ASSERT_EQ(texts->GetArraySize(), 1);
    EXPECT_EQ(texts->GetArrayItem(0)->GetString("content"), expected);
    EXPECT_EQ(expected, "source \ufffc symbol");
    pattern->spans_.clear();
    ASSERT_TRUE(pattern->IsSetObscured());
    auto obscuredJson = JsonUtil::ParseJsonString(Collect());
    EXPECT_EQ(obscuredJson->GetValue("texts")->GetArrayItem(0)->GetString("content"), expected);
}

TEST_F(PageTextCollectorTest, symbolCarrierIsNotIndependentlyFiltered)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto node = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, 3, pattern);
    page->AddChild(node);
    Mount(node);
    pattern->textForDisplay_ = u"getter symbol representation";
    pattern->MarkPageTranslateTextDrawn();
    auto json = JsonUtil::ParseJsonString(Collect());
    auto texts = json->GetValue("texts");
    ASSERT_EQ(texts->GetArraySize(), 1);
    EXPECT_EQ(texts->GetArrayItem(0)->GetString("content"), pattern->GetPageTranslateTextForReport());
}

TEST_F(PageTextCollectorTest, wrongThreadAbortsAndInvalidInstanceReturnsError)
{
    class WorkerExecutor : public MockTaskExecutor {
        bool WillRunOnCurrentThread(TaskType) const override { return false; }
    };
    MockContainer::Current()->SetTaskExecutor(AceType::MakeRefPtr<WorkerExecutor>());
    EXPECT_DEATH(Collect(), "");
    char* data = nullptr;
    uint32_t size = 0;
    const char* reason = nullptr;
    // The mock lookup returns the current container for any ID, like plugin redirection.
    // Instance ID 404 differs from the fixture instance; 190001 means ARKUI_ERROR_CODE_UI_CONTEXT_INVALID.
    EXPECT_EQ(CollectPageText(404, &data, &size, &reason), 190001);
    EXPECT_EQ(data, nullptr);
    MockContainer::SetGetContainerCallback([](int32_t) -> RefPtr<Container> { return nullptr; });
    // Instance ID 404 now has no container; 190001 means ARKUI_ERROR_CODE_UI_CONTEXT_INVALID.
    EXPECT_EQ(CollectPageText(404, &data, &size, &reason), 190001);
    EXPECT_EQ(data, nullptr);
}
TEST_F(PageTextCollectorTest, geometryMatchesDumpAndInvalidNumbersFail)
{
    auto node = Text(3, u"geometry");
    node->GetGeometryNode()->SetFrameSize(SizeF(123.5f, 21.25f));
    auto expected = node->GetPaintRectGlobalOffsetWithTranslate(false, true).first;
    auto json = JsonUtil::ParseJsonString(Collect());
    auto rect = json->GetValue("texts")->GetArrayItem(0)->GetValue("rect");
    EXPECT_DOUBLE_EQ(rect->GetArrayItem(0)->GetDouble(), expected.GetX());
    EXPECT_DOUBLE_EQ(rect->GetArrayItem(1)->GetDouble(), expected.GetY());
    // In rect [x, y, w, h], index 2 is the fixture width of 123.5 px.
    EXPECT_DOUBLE_EQ(rect->GetArrayItem(2)->GetDouble(), 123.5);
    // In rect [x, y, w, h], index 3 is the fixture height of 21.25 px.
    EXPECT_DOUBLE_EQ(rect->GetArrayItem(3)->GetDouble(), 21.25);
    // A width of -1 is invalid; the positive height of 20 px isolates the negative-width failure.
    node->GetGeometryNode()->SetFrameSize(SizeF(-1, 20));
    char* data = nullptr;
    uint32_t size = 0;
    const char* reason = nullptr;
    // 100001 is ARKUI_ERROR_CODE_INTERNAL_ERROR for the invalid geometry.
    EXPECT_EQ(CollectPageText(0, &data, &size, &reason), 100001);
    EXPECT_EQ(data, nullptr);
}

TEST_F(PageTextCollectorTest, registeredHistoryOverlayAndEmbeddedDescendantsFollowTranslation)
{
    // Node ID 3 identifies the history-page text and sorts before the current-page text.
    Text(3, u"history");
    // Node ID 4 identifies the new page, distinct from the original fixture page ID 2.
    page = FrameNode::CreateFrameNode("page", 4, AceType::MakeRefPtr<PagePattern>(nullptr));
    stage->AddChild(page);
    Mount(page);
    // Node ID 5 identifies the current-page text.
    Text(5, u"current");
    // Node ID 6 identifies overlay text attached outside the page subtree.
    Text(6, u"overlay", stage);
    auto embedded = FrameNode::CreateFrameNode("XComponent", 7, AceType::MakeRefPtr<Pattern>());
    page->AddChild(embedded);
    Mount(embedded);
    // Node ID 8 identifies registered text below the embedded-component node.
    Text(8, u"registered descendant", embedded);
    ExpectContents({ "history", "current", "overlay", "registered descendant" });
    stage->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
    EXPECT_EQ(Collect(), "{\"texts\":[]}");
}

TEST_F(PageTextCollectorTest, realLazyForEachSurvivesCacheInvalidationWithoutBuilding)
{
    auto builder = AceType::MakeRefPtr<CountingPageTextLazyBuilder>();
    auto lazy = AceType::MakeRefPtr<LazyForEachNode>(1000, builder);
    page->AddChild(lazy);
    lazy->onMainTree_ = true;
    std::vector<RefPtr<FrameNode>> nodes {
        UnmountedText(1001, u"first"), UnmountedText(1002, u"second"),
        UnmountedText(1003, u"hidden"), UnmountedText(1004, u"inactive")
    };
    for (int32_t i = 0; i < static_cast<int32_t>(nodes.size()); ++i) {
        builder->cachedItems_[i] = { std::to_string(i), nodes[i] };
        ASSERT_EQ(lazy->GetFrameChildByIndex(i, false, false, true), nodes[i]);
        Register(nodes[i]);
    }
    auto cached = UnmountedText(1005, u"unmounted cache");
    builder->expiringItem_["cache"] = { 4, cached };
    ASSERT_EQ(lazy->GetChildren().size(), nodes.size());
    ASSERT_TRUE(lazy->UINode::GetChildren().empty());
    nodes[2]->SetActive(false);
    nodes[3]->SetActive(false);
    ExpectContents({ "first", "second" });

    lazy->OnDataAdded(1);
    ASSERT_TRUE(lazy->children_.empty());
    const auto itemsBefore = builder->cachedItems_;
    const auto expiringBefore = builder->expiringItem_;
    const auto tempBefore = lazy->tempChildren_;
    const auto buildsBefore = builder->builds;
    const auto startBefore = builder->startIndex_;
    const auto endBefore = builder->endIndex_;
    ExpectContents({ "first", "second" });
    ExpectContents({ "first", "second" });
    EXPECT_TRUE(lazy->children_.empty());
    EXPECT_EQ(lazy->tempChildren_, tempBefore);
    EXPECT_EQ(builder->cachedItems_, itemsBefore);
    EXPECT_EQ(builder->expiringItem_, expiringBefore);
    EXPECT_EQ(builder->builds, buildsBefore);
    EXPECT_EQ(builder->startIndex_, startBefore);
    EXPECT_EQ(builder->endIndex_, endBefore);
    EXPECT_TRUE(nodes[0]->IsOnMainTree());
    EXPECT_TRUE(nodes[0]->IsActive());
    // Index 3 is the fourth fixture node, explicitly made inactive before collection.
    EXPECT_FALSE(nodes[3]->IsActive());
    EXPECT_FALSE(cached->IsOnMainTree());
    page->RemoveChild(lazy);
}

TEST_F(PageTextCollectorTest, realArkoalaLazyUsesMountedChildrenWithoutCallbacks)
{
    int callbacks = 0;
    auto lazy = AceType::MakeRefPtr<ArkoalaLazyNode>(1100);
    page->AddChild(lazy);
    lazy->onMainTree_ = true;
    std::vector<RefPtr<FrameNode>> nodes {
        UnmountedText(1101, u"first"), UnmountedText(1102, u"second"),
        UnmountedText(1103, u"hidden"), UnmountedText(1104, u"inactive"),
        UnmountedText(1105, u"unmounted cache")
    };
    lazy->SetCallbacks([&](int32_t index, bool) -> RefPtr<UINode> { ++callbacks; return nodes.at(index); },
        [&](int32_t, int32_t, int32_t, int32_t, bool) { ++callbacks; },
        [&]() { ++callbacks; }, [&](int32_t) { ++callbacks; });
    // 8 total items include the five created fixtures and three entries that remain uninstantiated.
    lazy->SetTotalCount(8);
    for (int32_t index : { 1, 0, 2, 3 }) {
        ASSERT_EQ(lazy->GetFrameChildByIndex(index, true, false, true), nodes[index]);
        Register(nodes[index]);
    }
    // Index 4 is the fifth fixture, requested only for the cache without adding it to the render tree.
    ASSERT_EQ(lazy->GetFrameChildByIndex(4, true, true, false), nodes[4]);
    nodes[2]->SetActive(false);
    nodes[3]->SetActive(false);
    lazy->RequestSyncTree();
    const int before = callbacks;
    ASSERT_TRUE(lazy->UINode::GetChildren().empty());
    ASSERT_TRUE(lazy->children_.empty());
    ExpectContents({ "first", "second" });
    EXPECT_TRUE(lazy->children_.empty());
    lazy->GetChildren();
    ExpectContents({ "first", "second" });
    lazy->RequestSyncTree();
    ASSERT_TRUE(lazy->children_.empty());
    ExpectContents({ "first", "second" });
    EXPECT_TRUE(lazy->children_.empty());
    EXPECT_EQ(callbacks, before);
    EXPECT_TRUE(nodes[0]->IsOnMainTree());
    // Index 4 is the cache-only fixture and must remain off the main tree.
    EXPECT_FALSE(nodes[4]->IsOnMainTree());
    page->RemoveChild(lazy);
}

TEST_F(PageTextCollectorTest, realRepeatVirtual2PreservesOrderAndCacheState)
{
    int callbacks = 0;
    auto repeat = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(1200, 8, 8, 0,
        [&](IndexType, bool, bool) -> std::pair<RIDType, uint32_t> { ++callbacks; return { 0, 0 }; },
        [&](IndexType, IndexType) { ++callbacks; },
        [&](int32_t, int32_t, int32_t, int32_t, bool, bool) { ++callbacks; },
        [&](IndexType, IndexType) { ++callbacks; }, [&]() { ++callbacks; },
        [&]() { ++callbacks; }, [&]() { ++callbacks; });
    page->AddChild(repeat);
    repeat->onMainTree_ = true;
    std::vector<RefPtr<FrameNode>> nodes {
        UnmountedText(1201, u"first"), UnmountedText(1202, u"second"),
        UnmountedText(1203, u"inactive"), UnmountedText(1204, u"hidden")
    };
    for (int32_t i : { 1, 0, 2, 3 }) {
        RefPtr<UINode> child = nodes[i];
        auto rid = static_cast<RIDType>(i + 10);
        repeat->caches_.cacheItem4Rid_[rid] = RepeatVirtualScroll2CacheItem::MakeCacheItem(child, true);
        repeat->caches_.l1Rid4Index_[i] = rid;
        ASSERT_EQ(repeat->GetFrameChildByIndex(i, false, false, true), child);
        Register(nodes[i]);
    }
    // Index 2 is the third fixture; make it inactive to verify exclusion.
    nodes[2]->SetActive(false);
    // Index 3 is the fourth fixture; also exclude it through the inactive state.
    nodes[3]->SetActive(false);
    // Node ID 1205 identifies the L2-only text, separate from L1 fixture IDs 1201 through 1204.
    RefPtr<UINode> cached = UnmountedText(1205, u"L2 cache");
    // RID 99 is an L2-only cache key, distinct from the L1 RIDs 10 through 13.
    repeat->caches_.cacheItem4Rid_[99] = RepeatVirtualScroll2CacheItem::MakeCacheItem(cached, false);
    const auto l1Before = repeat->caches_.l1Rid4Index_;
    const auto cacheBefore = repeat->caches_.cacheItem4Rid_;
    repeat->RequestContainerReLayout();
    const int before = callbacks;
    ASSERT_TRUE(repeat->UINode::GetChildren().empty());
    ASSERT_TRUE(repeat->children_.empty());
    ExpectContents({ "first", "second" });
    EXPECT_TRUE(repeat->children_.empty());
    repeat->GetChildren();
    ExpectContents({ "first", "second" });
    repeat->RequestContainerReLayout();
    ASSERT_TRUE(repeat->children_.empty());
    ExpectContents({ "first", "second" });
    EXPECT_TRUE(repeat->children_.empty());
    EXPECT_EQ(repeat->caches_.l1Rid4Index_, l1Before);
    EXPECT_EQ(repeat->caches_.cacheItem4Rid_, cacheBefore);
    EXPECT_EQ(callbacks, before);
    repeat->caches_.UpdateMoveFromTo(0, 1);
    ExpectContents({ "first", "second" }); // Registry ID order is unaffected by list movement.
    EXPECT_TRUE(repeat->children_.empty());
    EXPECT_TRUE(nodes[0]->IsOnMainTree());
    EXPECT_FALSE(cached->IsOnMainTree());
    page->RemoveChild(repeat);
}

TEST_F(PageTextCollectorTest, realRepeatVirtual1DoesNotInsertOrBuildDuringRead)
{
    int callbacks = 0;
    auto repeat = AceType::MakeRefPtr<RepeatVirtualScrollNode>(1300, 8,
        std::map<std::string, std::pair<bool, uint32_t>> {},
        [&](uint32_t) { ++callbacks; }, [&](const std::string&, uint32_t) { ++callbacks; },
        [&](uint32_t, uint32_t) -> std::list<std::string> { ++callbacks; return {}; },
        [&](uint32_t, uint32_t) -> std::list<std::string> { ++callbacks; return {}; },
        [&](int32_t, int32_t) { ++callbacks; });
    page->AddChild(repeat);
    repeat->onMainTree_ = true;
    for (int32_t i : { 1, 0 }) {
        auto node = UnmountedText(1301 + i, i == 0 ? u"first" : u"second");
        node->SetParent(AceType::WeakClaim(AceType::RawPtr(repeat)));
        Mount(node);
        auto key = std::to_string(i);
        repeat->caches_.node4key_[key] = { true, node };
        repeat->caches_.index4Key_[key] = i;
        repeat->caches_.activeNodeKeysInL1_.insert(key);
    }
    repeat->caches_.activeNodeKeysInL1_.insert("missing");
    // Index 7 is the last valid slot in the eight-item dataset but intentionally has no cached node.
    repeat->caches_.index4Key_["missing"] = 7;
    const auto cacheSize = repeat->caches_.node4key_.size();
    const int before = callbacks;
    ASSERT_TRUE(repeat->UINode::GetChildren().empty());
    ExpectContents({ "first", "second" });
    EXPECT_TRUE(repeat->children_.empty());
    EXPECT_EQ(repeat->caches_.node4key_.size(), cacheSize);
    EXPECT_EQ(callbacks, before);
    page->RemoveChild(repeat);
}

TEST_F(PageTextCollectorTest, registrationRemovalExpiryAndWebExclusion)
{
    // Node ID 3 is the live carrier used to exercise registration removal and re-registration.
    auto node = Text(3, u"registered");
    auto manager = pipeline->uiTranslateManager_;
    // Remove node ID 3 from the registry without destroying its text carrier.
    manager->RemoveTranslateListener(3);
    EXPECT_EQ(Collect(), "{\"texts\":[]}");
    Register(node);
    Register(node);
    ExpectContents({ "registered" });
    page->RemoveChild(node);
    node.Reset();
    EXPECT_EQ(Collect(), "{\"texts\":[]}");
    auto web = FrameNode::CreateFrameNode("Web", 4, AceType::MakeRefPtr<TextPattern>());
    page->AddChild(web);
    Mount(web);
    int visited = 0;
    manager->ForEachArkUITranslateFrameNode([&](const WeakPtr<FrameNode>& item) {
        if (item.Upgrade()) {
            ++visited;
        }
    });
    EXPECT_EQ(visited, 0);
    EXPECT_EQ(Collect(), "{\"texts\":[]}");
}

TEST_F(PageTextCollectorTest, queryDoesNotChangeContinuousOrSnapshotTranslationState)
{
    auto node = Text(3, u"source");
    auto manager = AceType::MakeRefPtr<ContentChangeManager>();
    pipeline->contentChangeMgr_ = manager;
    manager->StartTextTranslateReport();
    manager->ReportTranslateTextFrameNode(WeakPtr<FrameNode>(node));
    manager->StartTextTranslateSnapshotReport();
    manager->ReportTranslateTextFrameNode(WeakPtr<FrameNode>(node), false);
    const auto continuous = manager->translateTextVersions_;
    const auto snapshot = manager->translateTextSnapshotVersions_;
    const auto version = manager->translateTextSnapshotVersion_;
    const auto registrySize = pipeline->uiTranslateManager_->listenerMap_.size();
    node->GetPattern<TextPattern>()->pageTranslatedContent_ = u"translation";
    ExpectContents({ "source" });
    ExpectContents({ "source" });
    EXPECT_TRUE(manager->textTranslateActive_);
    EXPECT_EQ(manager->translateTextVersions_, continuous);
    EXPECT_EQ(manager->translateTextSnapshotVersions_, snapshot);
    EXPECT_EQ(manager->translateTextSnapshotVersion_, version);
    EXPECT_EQ(pipeline->uiTranslateManager_->listenerMap_.size(), registrySize);
    EXPECT_EQ(node->GetPattern<TextPattern>()->pageTranslatedContent_, std::optional<std::u16string>(u"translation"));
}

TEST_F(PageTextCollectorTest, richEditorPlaceholderUsesTranslationDrawGateAndSource)
{
    for (bool styled : { false, true }) {
        auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
        auto node = FrameNode::CreateFrameNode("RichEditor", ElementRegister::GetInstance()->MakeUniqueId(), pattern);
        page->AddChild(node);
        Mount(node);
        pattern->isShowPlaceholder_ = true;
        auto setSource = [&](const std::u16string& source) {
            if (styled) {
                pattern->styledPlaceholder_ = AceType::MakeRefPtr<SpanString>(source);
            } else {
                node->GetLayoutProperty<RichEditorLayoutProperty>()->UpdatePlaceholder(source);
            }
        };
        setSource(u"source");
        pattern->pageTranslatedContent_ = u"translation";
        EXPECT_EQ(Collect(), "{\"texts\":[]}");
        EXPECT_TRUE(pattern->lastDrawnPageTranslateContent_.empty());
        pattern->ReportPageTranslatePlaceholderDrawn();
        auto snapshot = Collect();
        auto json = JsonUtil::ParseJsonString(snapshot);
        auto texts = json->GetValue("texts");
        ASSERT_EQ(texts->GetArraySize(), 1);
        EXPECT_EQ(texts->GetArrayItem(0)->GetString("content"), "source");
        EXPECT_EQ(pattern->pageTranslatedContent_, std::optional<std::u16string>(u"translation"));
        setSource(u"changed");
        EXPECT_EQ(Collect(), "{\"texts\":[]}");
        EXPECT_EQ(pattern->lastDrawnPageTranslateContent_, u"source");
        pattern->ReportPageTranslatePlaceholderDrawn();
        EXPECT_NE(Collect().find("changed"), std::string::npos);
        EXPECT_NE(snapshot.find("source"), std::string::npos);
        setSource(u"");
        pattern->ReportPageTranslatePlaceholderDrawn();
        EXPECT_EQ(Collect(), "{\"texts\":[]}");
        pattern->isShowPlaceholder_ = false;
        pattern->textForDisplay_ = u"editor body";
        EXPECT_EQ(Collect(), "{\"texts\":[]}");
        page->RemoveChild(node);
    }
}

TEST_F(PageTextCollectorTest, textFieldPlaceholderUsesTranslationDrawGateAndSource)
{
    for (const auto* tag : { "TextInput", "TextArea", "SearchField" }) {
        for (bool styled : { false, true }) {
            auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
            auto node = FrameNode::CreateFrameNode(tag, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
            page->AddChild(node);
            Mount(node);
            auto setSource = [&](const std::u16string& source) {
                if (styled) {
                    pattern->SetPlaceholderStyledString(AceType::MakeRefPtr<SpanString>(source));
                    auto child = pattern->placeholderResponseArea_->GetFrameNode();
                    child->GetPattern<TextPattern>()->textForDisplay_ = source;
                } else {
                    node->GetLayoutProperty<TextFieldLayoutProperty>()->UpdatePlaceholder(source);
                }
            };
            setSource(u"source");
            pattern->pageTranslatedContent_ = u"translation";
            EXPECT_EQ(Collect(), "{\"texts\":[]}");
            EXPECT_TRUE(pattern->lastDrawnPageTranslateContent_.empty());
            pattern->ReportPageTranslatePlaceholderDrawn();
            auto json = JsonUtil::ParseJsonString(Collect());
            auto texts = json->GetValue("texts");
            ASSERT_EQ(texts->GetArraySize(), 1);
            EXPECT_EQ(texts->GetArrayItem(0)->GetString("content"), "source");
            EXPECT_EQ(pattern->pageTranslatedContent_, std::optional<std::u16string>(u"translation"));
            setSource(u"changed");
            EXPECT_EQ(Collect(), "{\"texts\":[]}");
            EXPECT_EQ(pattern->lastDrawnPageTranslateContent_, u"source");
            pattern->ReportPageTranslatePlaceholderDrawn();
            EXPECT_NE(Collect().find("changed"), std::string::npos);
            setSource(u"");
            pattern->ReportPageTranslatePlaceholderDrawn();
            EXPECT_EQ(Collect(), "{\"texts\":[]}");
            pattern->contentController_->SetTextValue(u"pending raw input");
            EXPECT_EQ(Collect(), "{\"texts\":[]}");
            page->RemoveChild(node);
        }
    }
}

TEST_F(PageTextCollectorTest, placeholderEncodingMatchesOriginalGetter)
{
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    auto node = FrameNode::CreateFrameNode("RichEditor", ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    page->AddChild(node);
    Mount(node);
    pattern->isShowPlaceholder_ = true;
    std::u16string source = u"中文";
    source.push_back(0);
    source.push_back(0xD800);
    source += u"\"\\\n";
    node->GetLayoutProperty<RichEditorLayoutProperty>()->UpdatePlaceholder(source);
    pattern->ReportPageTranslatePlaceholderDrawn();
    auto result = Collect();
    EXPECT_NE(result.find("中文�\\\"\\\\\\u000a"), std::string::npos);
    EXPECT_EQ(result.find("\\u0000"), std::string::npos);
    EXPECT_EQ(result.find('\0'), std::string::npos);
    EXPECT_EQ(pattern->lastDrawnPageTranslateContent_, source);
}

} // namespace OHOS::Ace::NG
