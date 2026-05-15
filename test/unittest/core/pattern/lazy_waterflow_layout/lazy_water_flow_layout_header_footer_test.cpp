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

#include "lazy_water_flow_layout_test.h"

#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_algorithm.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_info.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_model.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_property.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"

namespace OHOS::Ace::NG {

namespace {

class LazyVWaterFlowLayoutHeaderFooterTest : public LazyWaterFlowLayoutTestBase {};

// Local mock builder mirroring lazy_water_flow_layout_test.cpp's LazyWaterFlowMockLazy: helpers there live in
// anonymous namespaces and are not externally visible, so each test translation unit keeps its own copy.
class LazyWaterFlowMockLazy : public Framework::MockLazyForEachBuilder {
public:
    explicit LazyWaterFlowMockLazy(const std::vector<float>& heights)
    {
        for (auto height : heights) {
            items_.push_back({ nextId_++, height });
        }
    }

    void Insert(int32_t index, float height)
    {
        auto insertIndex = std::max(0, std::min(index, static_cast<int32_t>(items_.size())));
        items_.insert(items_.begin() + insertIndex, { nextId_++, height });
    }

protected:
    int32_t OnGetTotalCount() override
    {
        return static_cast<int32_t>(items_.size());
    }

    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems) override
    {
        ScopedViewStackProcessor scope;
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
        auto height = index >= 0 && index < static_cast<int32_t>(items_.size()) ?
            items_[index].height : LAZY_WATER_FLOW_ITEM_HEIGHT;
        ViewAbstract::SetHeight(CalcLength(height));
        auto node = ViewStackProcessor::GetInstance()->Finish();
        auto key = index >= 0 && index < static_cast<int32_t>(items_.size()) ?
            std::to_string(items_[index].id) : std::to_string(index);
        return { key, node };
    }

private:
    struct Item {
        int32_t id = 0;
        float height = 0.0f;
    };

    int32_t nextId_ = 0;
    std::vector<Item> items_;
};

void CreateEdge(float height)
{
    StackModelNG stackModel;
    stackModel.Create();
    ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewStackProcessor::GetInstance()->Pop();
}

void CreateLazyForEach(const RefPtr<LazyWaterFlowMockLazy>& mockLazy, int32_t elmtId)
{
    RefPtr<LazyForEachActuator> mockLazyActuator = mockLazy;
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(elmtId);
    LazyForEachModelNG lazyForEachModel;
    lazyForEachModel.Create(mockLazyActuator);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
}

RefPtr<LazyForEachNode> GetLazyForEachNode(const RefPtr<FrameNode>& frameNode, int32_t childIndex)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    return AceType::DynamicCast<LazyForEachNode>(frameNode->GetChildAtIndex(childIndex));
}

void InsertLazyItems(
    const RefPtr<LazyWaterFlowMockLazy>& mockLazy, const RefPtr<LazyForEachNode>& lazyForEachNode,
    int32_t startIndex, const std::vector<float>& heights)
{
    CHECK_NULL_VOID(mockLazy);
    CHECK_NULL_VOID(lazyForEachNode);
    for (int32_t i = 0; i < static_cast<int32_t>(heights.size()); ++i) {
        auto insertIndex = startIndex + i;
        mockLazy->Insert(insertIndex, heights[i]);
        lazyForEachNode->OnDataAdded(insertIndex);
    }
}

} // namespace

/**
 * @tc.name: LazyForEachTopInsertWithHeaderKeepsVisiblePosition_001
 * @tc.desc: Verify top insert before a header-backed viewport still returns adjust offset for the old first item.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, LazyForEachTopInsertWithHeaderKeepsVisiblePosition_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(40.0f); });

    auto mockLazy = AceType::MakeRefPtr<LazyWaterFlowMockLazy>(std::vector<float>(10, 100.0f));
    RefPtr<LazyForEachActuator> mockLazyActuator = mockLazy;
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    LazyForEachModelNG lazyForEachModel;
    lazyForEachModel.Create(mockLazyActuator);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(1));
    ASSERT_NE(lazyForEachNode, nullptr);
    EXPECT_FLOAT_EQ(static_cast<float>(scrollablePattern_->GetTotalOffset()), 0.0f);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0.0f);
    auto oldFirstPos = pattern_->layoutInfo_->GetPos(0);
    ASSERT_NE(oldFirstPos, nullptr);
    EXPECT_FLOAT_EQ(oldFirstPos->startPos, 40.0f);
    const auto oldFirstViewportY =
        oldFirstPos->startPos - static_cast<float>(scrollablePattern_->GetTotalOffset());

    mockLazy->Insert(0, 100.0f);
    lazyForEachNode->OnDataAdded(0);
    FlushUITasks();

    const auto offsetAfter = static_cast<float>(scrollablePattern_->GetTotalOffset());
    EXPECT_FLOAT_EQ(offsetAfter, 100.0f);
    auto insertedPos = pattern_->layoutInfo_->GetPos(0);
    auto shiftedOldFirstPos = pattern_->layoutInfo_->GetPos(1);
    ASSERT_NE(insertedPos, nullptr);
    ASSERT_NE(shiftedOldFirstPos, nullptr);
    EXPECT_FLOAT_EQ(insertedPos->startPos, 40.0f);
    EXPECT_FLOAT_EQ(shiftedOldFirstPos->startPos, 140.0f);
    EXPECT_FLOAT_EQ(shiftedOldFirstPos->startPos - offsetAfter, oldFirstViewportY);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
}

/**
 * @tc.name: ScrollStickyEdgesInsertBeforeViewportKeepsActiveRange_001
 * @tc.desc: Verify insertions above a Scroll viewport keep sticky edges and active range
 *           aligned after adjust offset.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, ScrollStickyEdgesInsertBeforeViewportKeepsActiveRange_001,
    TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::BOTH);
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(40.0f); });

    auto mockLazy = AceType::MakeRefPtr<LazyWaterFlowMockLazy>(std::vector<float>(10, 100.0f));
    CreateLazyForEach(mockLazy, GetElmtId());
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(30.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    auto lazyForEachNode = GetLazyForEachNode(frameNode_, 1);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto headerNode = AceType::DynamicCast<FrameNode>(pattern_->GetHeader());
    auto footerNode = AceType::DynamicCast<FrameNode>(pattern_->GetFooter());
    ASSERT_NE(headerNode, nullptr);
    ASSERT_NE(footerNode, nullptr);

    scrollablePattern_->UpdateCurrentOffset(-250.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    const auto firstVisibleIndex = pattern_->layoutInfo_->startIndex_;
    auto firstVisiblePos = pattern_->layoutInfo_->GetPos(firstVisibleIndex);
    ASSERT_NE(firstVisiblePos, nullptr);
    const auto offsetBefore = static_cast<float>(scrollablePattern_->GetTotalOffset());
    const auto firstVisibleViewportY = firstVisiblePos->startPos - offsetBefore;

    InsertLazyItems(mockLazy, lazyForEachNode, 0, { 100.0f });
    FlushUITasks();

    const auto offsetAfter = static_cast<float>(scrollablePattern_->GetTotalOffset());
    auto shiftedVisiblePos = pattern_->layoutInfo_->GetPos(firstVisibleIndex + 1);
    ASSERT_NE(shiftedVisiblePos, nullptr);
    EXPECT_FLOAT_EQ(offsetAfter, offsetBefore + 100.0f);
    EXPECT_FLOAT_EQ(shiftedVisiblePos->startPos - offsetAfter, firstVisibleViewportY);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, firstVisibleIndex + 1);
    EXPECT_TRUE(headerNode->IsActive());
    EXPECT_TRUE(footerNode->IsActive());
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), offsetAfter);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 12), offsetAfter + LAZY_WATER_FLOW_SCROLL_HEIGHT - 30.0f);

    scrollablePattern_->UpdateCurrentOffset(120.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    auto insertedPos = pattern_->layoutInfo_->GetPos(firstVisibleIndex);
    shiftedVisiblePos = pattern_->layoutInfo_->GetPos(firstVisibleIndex + 1);
    ASSERT_NE(insertedPos, nullptr);
    ASSERT_NE(shiftedVisiblePos, nullptr);
    EXPECT_FLOAT_EQ(insertedPos->endPos, shiftedVisiblePos->startPos);
}

/**
 * @tc.name: HeaderFooterStayActiveWithContentCache_001
 * @tc.desc: Verify header and footer stay active when content items use a separate visible/cache range.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, HeaderFooterStayActiveWithContentCache_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::BOTH);
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(40.0f); });
    CreateContent(30);
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(30.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto headerNode = AceType::DynamicCast<FrameNode>(pattern_->GetHeader());
    auto footerNode = AceType::DynamicCast<FrameNode>(pattern_->GetFooter());
    ASSERT_NE(headerNode, nullptr);
    ASSERT_NE(footerNode, nullptr);
    ASSERT_GE(pattern_->layoutInfo_->cachedEndIndex_, pattern_->layoutInfo_->layoutedEndIndex_);
    EXPECT_TRUE(headerNode->IsActive());
    EXPECT_TRUE(footerNode->IsActive());

    FlushIdleTask();

    ASSERT_GE(pattern_->layoutInfo_->cachedEndIndex_, pattern_->layoutInfo_->layoutedEndIndex_);
    EXPECT_TRUE(headerNode->IsActive());
    EXPECT_TRUE(footerNode->IsActive());
}

/**
 * @tc.name: HeaderFooterLazyForEachKeepsCacheEndActive_001
 * @tc.desc: Verify header raw-index offset is not subtracted twice when forwarding active range to LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, HeaderFooterLazyForEachKeepsCacheEndActive_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::BOTH);
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(40.0f); });

    auto mockLazy = AceType::MakeRefPtr<LazyWaterFlowMockLazy>(std::vector<float>(30, 100.0f));
    CreateLazyForEach(mockLazy, GetElmtId());
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(30.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto lazyForEachNode = GetLazyForEachNode(frameNode_, 1);
    ASSERT_NE(lazyForEachNode, nullptr);
    const auto cachedEnd = pattern_->layoutInfo_->cachedEndIndex_;
    ASSERT_GE(cachedEnd, 0);
    auto cachedEndIter = lazyForEachNode->builder_->cachedItems_.find(cachedEnd);
    ASSERT_NE(cachedEndIter, lazyForEachNode->builder_->cachedItems_.end());
    EXPECT_NE(cachedEndIter->second.second, nullptr);
}

/**
 * @tc.name: HeaderFooter_001
 * @tc.desc: Verify header and footer stay at the leading/trailing child slots and are excluded from item indexing.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, HeaderFooter_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(60.0f); });

    int32_t callCount = 0;
    std::pair<int32_t, int32_t> visibleRange = { -1, -1 };
    LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange([&callCount, &visibleRange](int32_t start, int32_t end) {
        ++callCount;
        visibleRange = { start, end };
    });

    CreateContent(4);
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(40.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(frameNode_->GetChildren().size(), 6u);
    EXPECT_EQ(frameNode_->GetChildIndex(pattern_->GetHeader()), 0);
    EXPECT_EQ(frameNode_->GetChildIndex(pattern_->GetFooter()), 5);
    EXPECT_EQ(pattern_->GetHeaderMainSize(), 60.0f);
    EXPECT_EQ(pattern_->GetFooterMainSize(), 40.0f);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_.size(), 4u);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[0].startPos, 60.0f);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[1].startPos, 60.0f);
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 300.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 1), 60.0f);
    EXPECT_EQ(GetChildY(frameNode_, 5), 260.0f);
    EXPECT_GT(callCount, 0);
    EXPECT_EQ(visibleRange.first, 0);
    EXPECT_EQ(visibleRange.second, 3);
    pattern_->SetOnVisibleIndexesChange(nullptr);
}

/**
 * @tc.name: ReplaceHeaderFooter_001
 * @tc.desc: Verify header and footer can be replaced without duplicating children.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, ReplaceHeaderFooter_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(20.0f); });
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(80.0f); });
    CreateContent(2);
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(30.0f); });
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(50.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(frameNode_->GetChildren().size(), 4u);
    EXPECT_EQ(pattern_->GetHeaderMainSize(), 80.0f);
    EXPECT_EQ(pattern_->GetFooterMainSize(), 50.0f);
    EXPECT_EQ(GetChildHeight(frameNode_, 0), 80.0f);
    EXPECT_EQ(GetChildHeight(frameNode_, 3), 50.0f);
}

/**
 * @tc.name: RemoveHeaderFooter_001
 * @tc.desc: Verify header and footer can be removed after initial layout.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, RemoveHeaderFooter_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(40.0f); });
    CreateContent(4);
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(40.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(frameNode_->GetChildren().size(), 6u);

    pattern_->RemoveHeader();
    pattern_->RemoveFooter();
    FlushUITasks();

    EXPECT_EQ(frameNode_->GetChildren().size(), 4u);
    EXPECT_EQ(pattern_->GetHeader(), nullptr);
    EXPECT_EQ(pattern_->GetFooter(), nullptr);
    EXPECT_EQ(pattern_->GetHeaderMainSize(), 0.0f);
    EXPECT_EQ(pattern_->GetFooterMainSize(), 0.0f);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[0].startPos, 0.0f);
}

/**
 * @tc.name: ListStickyHeader_001
 * @tc.desc: Verify sticky header follows the List viewport inside LazyVWaterFlowLayout.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, ListStickyHeader_001, TestSize.Level1)
{
    CreateList();
    CreateLazyWaterFlowLayout();
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::HEADER);
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(40.0f); });
    CreateContent(12);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);

    scrollablePattern_->UpdateCurrentOffset(-120.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    EXPECT_EQ(pattern_->GetStickyStyle(), StickyStyle::HEADER);
    EXPECT_EQ(GetChildY(frameNode_, 0), 120.0f);
}

/**
 * @tc.name: ListStickyFooter_001
 * @tc.desc: Verify sticky footer follows the List viewport without requiring a sticky header.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, ListStickyFooter_001, TestSize.Level1)
{
    CreateList();
    CreateLazyWaterFlowLayout();
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::FOOTER);
    CreateContent(12);
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(30.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    EXPECT_EQ(pattern_->GetStickyStyle(), StickyStyle::FOOTER);
    EXPECT_EQ(frameNode_->GetChildIndex(pattern_->GetFooter()), 12);
    EXPECT_EQ(GetChildY(frameNode_, 12), 420.0f);

    scrollablePattern_->UpdateCurrentOffset(-120.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    EXPECT_EQ(GetChildY(frameNode_, 12), 540.0f);
}

/**
 * @tc.name: ListStickyBoth_001
 * @tc.desc: Verify sticky header and footer are both offset inside the List viewport.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, ListStickyBoth_001, TestSize.Level1)
{
    CreateList();
    CreateLazyWaterFlowLayout();
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::BOTH);
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(40.0f); });
    CreateContent(12);
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(30.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);

    scrollablePattern_->UpdateCurrentOffset(-120.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    EXPECT_EQ(GetChildY(frameNode_, 0), 120.0f);
    EXPECT_EQ(GetChildY(frameNode_, 13), 540.0f);
}

/**
 * @tc.name: ModifierSwitchStickyHeaderToFooter_001
 * @tc.desc: Verify modifier-style sticky updates re-layout header/footer when switching from HEADER to FOOTER.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, ModifierSwitchStickyHeaderToFooter_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::HEADER);
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(40.0f); });
    CreateContent(12);
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(30.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    scrollablePattern_->UpdateCurrentOffset(-120.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 0), 120.0f);

    layoutProperty_->CleanDirty();
    LazyWaterFlowLayoutModel::SetSticky(AceType::RawPtr(frameNode_), StickyStyle::FOOTER);
    EXPECT_TRUE(layoutProperty_->GetPropertyChangeFlag() & PROPERTY_UPDATE_MEASURE);
    frameNode_->MarkDirtyNode(layoutProperty_->GetPropertyChangeFlag());
    FlushUITasks();

    EXPECT_EQ(pattern_->GetStickyStyle(), StickyStyle::FOOTER);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 13), 540.0f);
}

/**
 * @tc.name: StickyFooterUndersizedContent_001
 * @tc.desc: Verify sticky footer does not move above the header when section metrics are under-sized.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, StickyFooterUndersizedContent_001, TestSize.Level1)
{
    HeaderFooterStickyMetrics metrics {
        .viewStart = 0.0f,
        .viewEnd = 120.0f,
        .totalMainSize = 70.0f,
        .headerMainSize = 40.0f,
        .footerMainSize = 50.0f,
    };

    EXPECT_FLOAT_EQ(HeaderFooterUtils::CalcStickyHeaderPos(metrics), 0.0f);
    EXPECT_FLOAT_EQ(HeaderFooterUtils::CalcStickyFooterPos(metrics), metrics.headerMainSize);
}

/**
 * @tc.name: ScrollStickyBothFooterBeforeContent_001
 * @tc.desc: Verify footer is normalized to the trailing child slot even when it is mounted before lazy content.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, ScrollStickyBothFooterBeforeContent_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::BOTH);
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(40.0f); });
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(30.0f); });
    CreateContent(12);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);

    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 12);
    EXPECT_EQ(frameNode_->GetChildIndex(pattern_->GetHeader()), 0);
    EXPECT_EQ(frameNode_->GetChildIndex(pattern_->GetFooter()), 13);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 1), 40.0f);
    EXPECT_EQ(GetChildY(frameNode_, 13), 420.0f);

    scrollablePattern_->UpdateCurrentOffset(-120.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    EXPECT_EQ(GetChildY(frameNode_, 0), 120.0f);
    EXPECT_EQ(GetChildY(frameNode_, 13), 540.0f);
}

/**
 * @tc.name: ScrollStickyHeader_001
 * @tc.desc: Verify sticky header follows the Scroll viewport without List integration.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, ScrollStickyHeader_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::HEADER);
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(40.0f); });
    CreateContent(12);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);

    scrollablePattern_->UpdateCurrentOffset(-120.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    EXPECT_EQ(GetChildY(frameNode_, 0), 120.0f);
}

/**
 * @tc.name: StickyHeaderKeepsUserZIndex_001
 * @tc.desc: Verify sticky promotion does not overwrite an explicit header zIndex.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, StickyHeaderKeepsUserZIndex_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::HEADER);
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(40.0f); });
    CreateContent(12);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto headerNode = AceType::DynamicCast<FrameNode>(pattern_->GetHeader());
    ASSERT_NE(headerNode, nullptr);
    auto renderContext = headerNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateZIndex(10);

    scrollablePattern_->UpdateCurrentOffset(-120.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    auto zIndex = renderContext->GetZIndex();
    ASSERT_TRUE(zIndex.has_value());
    EXPECT_EQ(zIndex.value(), 10);
}

/**
 * @tc.name: StickyHeaderFooterRtlAlignment_001
 * @tc.desc: Verify narrow sticky header/footer stay right-aligned in RTL layout.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, StickyHeaderFooterRtlAlignment_001, TestSize.Level1)
{
    constexpr float kHeaderWidth = 80.0f;
    constexpr float kFooterWidth = 60.0f;

    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::BOTH);
    LazyWaterFlowLayoutModel::SetHeader([kHeaderWidth]() {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(kHeaderWidth));
        ViewAbstract::SetHeight(CalcLength(40.0f));
        ViewStackProcessor::GetInstance()->Pop();
    });
    CreateContent(12);
    LazyWaterFlowLayoutModel::SetFooter([kFooterWidth]() {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(kFooterWidth));
        ViewAbstract::SetHeight(CalcLength(30.0f));
        ViewStackProcessor::GetInstance()->Pop();
    });
    CreateDone();

    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks();

    const auto crossSize = frameNode_->GetGeometryNode()->GetFrameSize().Width();
    EXPECT_FLOAT_EQ(GetChildX(frameNode_, 0), crossSize - kHeaderWidth);
    EXPECT_FLOAT_EQ(GetChildX(frameNode_, 13), crossSize - kFooterWidth);

    scrollablePattern_->UpdateCurrentOffset(-120.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    EXPECT_FLOAT_EQ(GetChildX(frameNode_, 0), crossSize - kHeaderWidth);
    EXPECT_FLOAT_EQ(GetChildX(frameNode_, 13), crossSize - kFooterWidth);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 120.0f);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 13), 540.0f);
}

} // namespace OHOS::Ace::NG
