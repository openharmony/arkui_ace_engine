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

#include "test/unittest/core/pattern/lazy_layout/lazy_edge_test_helper.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_algorithm.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_info.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_model.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_property.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"

namespace OHOS::Ace::NG {

namespace {

class LazyVWaterFlowLayoutHeaderFooterTest : public LazyWaterFlowLayoutTestBase {
protected:
    // Build header + items + footer, grow one edge to 120, and assert lane coords stay body-local invariant
    // while the section total grows by exactly the edge delta.
    void RunEdgeResizeLaneInvariance(const std::string& columnsTemplate, bool resizeFooter);
};

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

constexpr float PIXEL_CONTRACT_HEADER_HEIGHT = 40.0f;
constexpr float PIXEL_CONTRACT_FOOTER_HEIGHT = 30.0f;
constexpr float PIXEL_CONTRACT_ITEM_HEIGHT = 100.0f;
constexpr int32_t PIXEL_CONTRACT_ITEM_COUNT = 30;
constexpr float PIXEL_CONTRACT_MID_SCROLL_OFFSET = 200.0f;
constexpr int32_t PIXEL_CONTRACT_LAZY_FOREACH_CHILD_INDEX = 1; // header at 0 with sticky BOTH set
constexpr float PIXEL_CONTRACT_SLACK = 1.0f;

// Fixed-height mock for the sticky pixel-contract tests; exposes Insert/Erase by data-index so the
// prepend / prefix-delete preserve tests can mutate the data set.
class PixelContractMockLazy : public Framework::MockLazyForEachBuilder {
public:
    PixelContractMockLazy()
    {
        for (int32_t i = 0; i < PIXEL_CONTRACT_ITEM_COUNT; ++i) {
            ids_.push_back(nextId_++);
        }
    }

    // Insert at `index`; caller must follow with LazyForEachNode::OnDataAdded(index).
    void Insert(int32_t index)
    {
        const auto insertIndex = std::max(0, std::min(index, static_cast<int32_t>(ids_.size())));
        ids_.insert(ids_.begin() + insertIndex, nextId_++);
    }

    // Erase at `index`; caller pairs this with LazyForEachNode::OnDataDeleted(index).
    void Erase(int32_t index)
    {
        if (index < 0 || index >= static_cast<int32_t>(ids_.size())) {
            return;
        }
        ids_.erase(ids_.begin() + index);
    }

    int32_t Count() const
    {
        return static_cast<int32_t>(ids_.size());
    }

protected:
    int32_t OnGetTotalCount() override
    {
        return static_cast<int32_t>(ids_.size());
    }

    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems) override
    {
        ScopedViewStackProcessor scope;
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
        ViewAbstract::SetHeight(CalcLength(PIXEL_CONTRACT_ITEM_HEIGHT));
        auto node = ViewStackProcessor::GetInstance()->Finish();
        const std::string key = (index >= 0 && index < static_cast<int32_t>(ids_.size()))
                                    ? std::to_string(ids_[index])
                                    : std::to_string(index);
        return { key, node };
    }

private:
    int32_t nextId_ = 0;
    std::vector<int32_t> ids_;
};

void PixelContractCreateLazyForEach(const RefPtr<PixelContractMockLazy>& builder, int32_t elmtId)
{
    RefPtr<LazyForEachActuator> actuator = builder;
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(elmtId);
    LazyForEachModelNG lazyForEachModel;
    lazyForEachModel.Create(actuator);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
}

// finalPixelInParentContent = lazyHostMarginOffsetInParent + itemSelfLocalY (Scroll has baked
// parent.currentOffset into the host margin offset).
struct PixelContractChannels {
    float parentCurrentOffset = 0.0f;
    float lazyHostMarginOffsetInParent = 0.0f;
    float itemSelfLocalY = 0.0f;
    float finalPixelInParentContent = 0.0f;
};

class LazyVWaterFlowStickyScrollTest : public LazyWaterFlowLayoutTestBase {
protected:
    // Scroll > LazyVWaterFlow with sticky header / 30 items / sticky footer.
    void BuildDemo()
    {
        CreateScroll();
        CreateLazyWaterFlowLayout();
        LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
        LazyWaterFlowLayoutModel::SetSticky(StickyStyle::BOTH);
        LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(PIXEL_CONTRACT_HEADER_HEIGHT); });
        builder_ = AceType::MakeRefPtr<PixelContractMockLazy>();
        PixelContractCreateLazyForEach(builder_, GetElmtId());
        LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(PIXEL_CONTRACT_FOOTER_HEIGHT); });
        CreateDone();
    }

    // Capture pixel channels for an item; nullopt when it is outside the materialised window.
    std::optional<PixelContractChannels> CaptureChannels(int32_t probeItemIdx) const
    {
        if (!scrollablePattern_ || !frameNode_) {
            return std::nullopt;
        }
        auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(
            frameNode_->GetChildAtIndex(PIXEL_CONTRACT_LAZY_FOREACH_CHILD_INDEX));
        if (!lazyForEachNode) {
            return std::nullopt;
        }
        auto itemFrame = lazyForEachNode->GetFrameNode(probeItemIdx);
        if (!itemFrame) {
            return std::nullopt;
        }
        PixelContractChannels ch;
        ch.parentCurrentOffset = static_cast<float>(scrollablePattern_->GetTotalOffset());
        ch.lazyHostMarginOffsetInParent = frameNode_->GetGeometryNode()->GetMarginFrameOffset().GetY();
        ch.itemSelfLocalY = itemFrame->GetGeometryNode()->GetMarginFrameOffset().GetY();
        ch.finalPixelInParentContent = ch.lazyHostMarginOffsetInParent + ch.itemSelfLocalY;
        return ch;
    }

    // Insert one item at a data index and trigger OnDataAdded (drives the data-change relayout).
    void InsertItemAt(int32_t index)
    {
        ASSERT_NE(builder_, nullptr);
        auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(
            frameNode_->GetChildAtIndex(PIXEL_CONTRACT_LAZY_FOREACH_CHILD_INDEX));
        ASSERT_NE(lazyForEachNode, nullptr);
        builder_->Insert(index);
        lazyForEachNode->OnDataAdded(index);
        FlushUITasks();
    }

    // Erase one item at a data index and trigger OnDataDeleted.
    void EraseItemAt(int32_t index)
    {
        ASSERT_NE(builder_, nullptr);
        auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(
            frameNode_->GetChildAtIndex(PIXEL_CONTRACT_LAZY_FOREACH_CHILD_INDEX));
        ASSERT_NE(lazyForEachNode, nullptr);
        builder_->Erase(index);
        lazyForEachNode->OnDataDeleted(index);
        FlushUITasks();
    }

    RefPtr<PixelContractMockLazy> builder_;
};

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
    EXPECT_FLOAT_EQ(oldFirstPos->startPos, 0.0f);
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
    EXPECT_FLOAT_EQ(insertedPos->startPos, 0.0f);
    EXPECT_FLOAT_EQ(shiftedOldFirstPos->startPos, 100.0f);
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
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[1].startPos, 0.0f);
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
 * @tc.name: ReplaceAndRemoveHeaderFooter_001
 * @tc.desc: Verify header and footer can be replaced without duplicating children, then removed after layout
 *           (slots cleared, sizes reset, item 0 re-anchored at the section top).
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, ReplaceAndRemoveHeaderFooter_001, TestSize.Level1)
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

    pattern_->RemoveHeader();
    pattern_->RemoveFooter();
    FlushUITasks();

    EXPECT_EQ(frameNode_->GetChildren().size(), 2u);
    EXPECT_EQ(pattern_->GetHeader(), nullptr);
    EXPECT_EQ(pattern_->GetFooter(), nullptr);
    EXPECT_EQ(pattern_->GetHeaderMainSize(), 0.0f);
    EXPECT_EQ(pattern_->GetFooterMainSize(), 0.0f);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[0].startPos, 0.0f);
}

/**
 * @tc.name: ListStickyStyles_001
 * @tc.desc: Sticky styles under a List parent: HEADER pins the header to the viewport top, FOOTER pins the
 *           footer to the viewport bottom without requiring a header, and BOTH pins the two edges
 *           simultaneously.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, ListStickyStyles_001, TestSize.Level1)
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

    CreateList();
    CreateLazyWaterFlowLayout();
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::FOOTER);
    CreateContent(12);
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(30.0f); });
    CreateDone();
    EXPECT_EQ(pattern_->GetStickyStyle(), StickyStyle::FOOTER);
    EXPECT_EQ(frameNode_->GetChildIndex(pattern_->GetFooter()), 12);
    EXPECT_EQ(GetChildY(frameNode_, 12), 420.0f);
    scrollablePattern_->UpdateCurrentOffset(-120.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 12), 540.0f);

    CreateList();
    CreateLazyWaterFlowLayout();
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::BOTH);
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(40.0f); });
    CreateContent(12);
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(30.0f); });
    CreateDone();
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
 * @tc.name: CalcStickyEdgePosHonorsInsets_001
 * @tc.desc: Sticky position math with parent-reserved insets: the header pins below the top inset, a floating
 *           footer pins above the bottom inset, and a top inset cannot push the header above the content
 *           origin (top-overscroll cancels it).
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, CalcStickyEdgePosHonorsInsets_001, TestSize.Level1)
{
    constexpr float topInset = 30.0f;
    constexpr float bottomInset = 30.0f;
    HeaderFooterStickyMetrics metrics {
        .viewStart = 100.0f,
        .viewEnd = 800.0f,
        .totalMainSize = 5000.0f,
        .headerMainSize = 80.0f,
        .footerMainSize = 60.0f,
    };

    // Without an inset the header pins at viewStart; the inset pushes the pinned position down by topInset.
    EXPECT_FLOAT_EQ(HeaderFooterUtils::CalcStickyHeaderPos(metrics), metrics.viewStart);
    metrics.stickyTopInset = topInset;
    EXPECT_FLOAT_EQ(HeaderFooterUtils::CalcStickyHeaderPos(metrics), metrics.viewStart + topInset);

    // Without an inset the floating footer pins at viewEnd - footer; the inset lifts it up by bottomInset.
    EXPECT_FLOAT_EQ(HeaderFooterUtils::CalcStickyFooterPos(metrics), metrics.viewEnd - metrics.footerMainSize);
    metrics.stickyBottomInset = bottomInset;
    EXPECT_FLOAT_EQ(
        HeaderFooterUtils::CalcStickyFooterPos(metrics), metrics.viewEnd - bottomInset - metrics.footerMainSize);

    // Top-overscroll (viewStart == -inset) exactly cancels the inset: the header rests at the content
    // origin (0), not negative.
    metrics.viewStart = -45.0f;
    metrics.stickyTopInset = 45.0f;
    EXPECT_FLOAT_EQ(HeaderFooterUtils::CalcStickyHeaderPos(metrics), 0.0f);
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

/**
 * @tc.name: StickyToggleKeepsHeaderLaidOut_001
 * @tc.desc: Toggling sticky at runtime must not drop the header. Regression for the header collapsing onto
 *           item 0 (headerMainSize -> 0, items starting at 0) when a property-only relayout left the layout
 *           algorithm addressing a stale edge reference; the header must stay sized and keep items below it
 *           across BOTH -> NONE -> BOTH without needing a scroll.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, StickyToggleKeepsHeaderLaidOut_001, TestSize.Level1)
{
    constexpr float headerHeight = 40.0f;
    constexpr float footerHeight = 30.0f;

    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::BOTH);
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(headerHeight); });
    CreateContent(12);
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(footerHeight); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);
    EXPECT_EQ(frameNode_->GetChildIndex(pattern_->GetHeader()), 0);
    EXPECT_EQ(pattern_->GetHeaderMainSize(), headerHeight);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[0].startPos, 0.0f);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0.0f);

    // BOTH -> NONE: header must remain sized and keep item 0 below it (not collapse to the top).
    layoutProperty_->CleanDirty();
    LazyWaterFlowLayoutModel::SetSticky(AceType::RawPtr(frameNode_), StickyStyle::NONE);
    frameNode_->MarkDirtyNode(layoutProperty_->GetPropertyChangeFlag());
    FlushUITasks();

    EXPECT_EQ(pattern_->GetStickyStyle(), StickyStyle::NONE);
    EXPECT_EQ(frameNode_->GetChildIndex(pattern_->GetHeader()), 0);
    EXPECT_EQ(pattern_->GetHeaderMainSize(), headerHeight);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[0].startPos, 0.0f);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0.0f);

    // NONE -> BOTH: header is still intact after toggling back.
    layoutProperty_->CleanDirty();
    LazyWaterFlowLayoutModel::SetSticky(AceType::RawPtr(frameNode_), StickyStyle::BOTH);
    frameNode_->MarkDirtyNode(layoutProperty_->GetPropertyChangeFlag());
    FlushUITasks();

    EXPECT_EQ(pattern_->GetStickyStyle(), StickyStyle::BOTH);
    EXPECT_EQ(pattern_->GetHeaderMainSize(), headerHeight);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[0].startPos, 0.0f);
}

/**
 * @tc.name: ContentItemsRenderWithStickyHeaderFooter001
 * @tc.desc: A header+footer sticky LazyVWaterFlowLayout must render its content items, not just the header/footer.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, ContentItemsRenderWithStickyHeaderFooter001, TestSize.Level1)
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
    auto headerNode = AceType::DynamicCast<FrameNode>(pattern_->GetHeader());
    auto footerNode = AceType::DynamicCast<FrameNode>(pattern_->GetFooter());
    ASSERT_NE(headerNode, nullptr);
    ASSERT_NE(footerNode, nullptr);
    EXPECT_TRUE(headerNode->IsActive());
    EXPECT_TRUE(footerNode->IsActive());

    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_GT(pattern_->layoutInfo_->endIndex_, 0);
    auto firstItemPos = pattern_->layoutInfo_->GetPos(0);
    ASSERT_NE(firstItemPos, nullptr);
    EXPECT_FLOAT_EQ(firstItemPos->startPos, 0.0f);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 1), 40.0f);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 2), 140.0f);
}

/**
 * @tc.name: ListContentOffsetForwardsToLazyChildInset_001
 * @tc.desc: A List's contentStartOffset/contentEndOffset must be forwarded through the nested
 *           LazyVWaterFlowLayout's layout constraint, so sticky header/footer reserve that space.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, ListContentOffsetForwardsToLazyChildInset_001, TestSize.Level1)
{
    constexpr float startOffset = 30.0f;
    constexpr float endOffset = 20.0f;
    constexpr float headerHeight = 40.0f;
    constexpr float footerHeight = 30.0f;

    CreateList();
    ListModelNG::SetContentStartOffset(AceType::RawPtr(scrollableFrameNode_), startOffset);
    ListModelNG::SetContentEndOffset(AceType::RawPtr(scrollableFrameNode_), endOffset);
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::BOTH);
    LazyWaterFlowLayoutModel::SetHeader([headerHeight]() { CreateEdge(headerHeight); });
    CreateContent(12);
    LazyWaterFlowLayoutModel::SetFooter([footerHeight]() { CreateEdge(footerHeight); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);

    scrollablePattern_->UpdateCurrentOffset(-120.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    const auto lazyWaterFlowY = GetChildY(scrollableFrameNode_, 0);
    EXPECT_FLOAT_EQ(lazyWaterFlowY + GetChildY(frameNode_, 0), startOffset);
    EXPECT_FLOAT_EQ(lazyWaterFlowY + GetChildY(frameNode_, 13),
        LAZY_WATER_FLOW_SCROLL_HEIGHT - endOffset - footerHeight);
}

/**
 * @tc.name: HeaderFooterOnlyNoContent_001
 * @tc.desc: A header+footer LazyVWaterFlowLayout with zero content items still lays out both edges (header at
 *           the top, footer right below it, sizes intact, edges active) and the section total is exactly
 *           headerMainSize_ + footerMainSize_.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, HeaderFooterOnlyNoContent_001, TestSize.Level1)
{
    constexpr float headerHeight = 40.0f;
    constexpr float footerHeight = 30.0f;

    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::BOTH);
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(headerHeight); });
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(footerHeight); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto headerNode = AceType::DynamicCast<FrameNode>(pattern_->GetHeader());
    auto footerNode = AceType::DynamicCast<FrameNode>(pattern_->GetFooter());
    ASSERT_NE(headerNode, nullptr);
    ASSERT_NE(footerNode, nullptr);
    EXPECT_TRUE(headerNode->IsActive());
    EXPECT_TRUE(footerNode->IsActive());
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 0);
    EXPECT_EQ(frameNode_->GetChildren().size(), 2u);
    // Section total, edge sizes, and edge order (header at top, footer right below it).
    RunEmptyDataEdgesOnlyChecks(*this, headerHeight, footerHeight);
}

/**
 * @tc.name: DynamicHeaderHeightChangeReflows_001
 * @tc.desc: Growing the header height at runtime must re-measure the header and reflow the content below it
 *           (item 0 starts at the new header height), without needing a scroll.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, DynamicHeaderHeightChangeReflows_001, TestSize.Level1)
{
    constexpr float initialHeader = 40.0f;
    constexpr float grownHeader = 120.0f;

    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::BOTH);
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(initialHeader); });
    CreateContent(12);
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(30.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(pattern_->GetHeaderMainSize(), initialHeader);
    auto firstPos = pattern_->layoutInfo_->GetPos(0);
    ASSERT_NE(firstPos, nullptr);
    EXPECT_FLOAT_EQ(firstPos->startPos, 0.0f);

    auto headerNode = AceType::DynamicCast<FrameNode>(pattern_->GetHeader());
    ASSERT_NE(headerNode, nullptr);
    headerNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0f, DimensionUnit::PERCENT), CalcLength(grownHeader)));
    headerNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();

    EXPECT_EQ(pattern_->GetHeaderMainSize(), grownHeader);
    EXPECT_EQ(GetChildHeight(frameNode_, 0), grownHeader);
    firstPos = pattern_->layoutInfo_->GetPos(0);
    ASSERT_NE(firstPos, nullptr);
    EXPECT_FLOAT_EQ(firstPos->startPos, 0.0f);
}

/**
 * @tc.name: HeaderTallerThanViewport_001
 * @tc.desc: A header taller than the viewport must still lay out (size intact, content reflowed below it)
 *           without breaking the layout.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, HeaderTallerThanViewport_001, TestSize.Level1)
{
    const float tallHeader = LAZY_WATER_FLOW_SCROLL_HEIGHT + 50.0f;

    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    LazyWaterFlowLayoutModel::SetSticky(StickyStyle::BOTH);
    LazyWaterFlowLayoutModel::SetHeader([tallHeader]() { CreateEdge(tallHeader); });
    CreateContent(5);
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(30.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto headerNode = AceType::DynamicCast<FrameNode>(pattern_->GetHeader());
    ASSERT_NE(headerNode, nullptr);
    EXPECT_TRUE(headerNode->IsActive());
    EXPECT_EQ(pattern_->GetHeaderMainSize(), tallHeader);
    EXPECT_EQ(GetChildHeight(frameNode_, 0), tallHeader);
    auto firstPos = pattern_->layoutInfo_->GetPos(0);
    ASSERT_NE(firstPos, nullptr);
    EXPECT_FLOAT_EQ(firstPos->startPos, 0.0f); // body-local: item 0 at body 0 even with a viewport-taller header
}

/**
 * @tc.name: DemoStructureBaseline_001
 * @tc.desc: Verify steady-state pixel positions for a probe item after a mid scroll, and that
 *           lane.startPos init equals headerMainSize_ alone (no double-scroll).
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowStickyScrollTest, DemoStructureBaseline_001, TestSize.Level1)
{
    BuildDemo();

    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(pattern_->layoutInfo_, nullptr);
    ASSERT_FALSE(pattern_->layoutInfo_->lanes_.empty());

    /**
     * @tc.expected: at rest, lane base is body-local 0 (the header offset is applied only at layout time);
     *               no extra top margin offset folded into lane.startPos.
     */
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->headerMainSize_, PIXEL_CONTRACT_HEADER_HEIGHT);
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->lanes_[0].startPos, 0.0f);

    /**
     * @tc.steps: step1. Scroll parent to MID; capture 4 channels for the probe item.
     */
    scrollablePattern_->UpdateCurrentOffset(-PIXEL_CONTRACT_MID_SCROLL_OFFSET, SCROLL_FROM_UPDATE);
    FlushUITasks();

    // Viewport 450 - sticky header 40 - sticky footer 30 leaves items area [240, 620] at mid scroll;
    // item 3 sits at [340, 440] safely inside it.
    constexpr int32_t kProbeItemIdx = 3;
    auto channels = CaptureChannels(kProbeItemIdx);
    ASSERT_TRUE(channels.has_value())
        << "item " << kProbeItemIdx << " not materialised at parent offset " << PIXEL_CONTRACT_MID_SCROLL_OFFSET
        << "; pick a different probe idx or scroll offset";

    /**
     * @tc.expected: at parent_offset = 200, probe item 3 final pixel = 140
     *   (host margin Y = -200, item self-local Y = 40 + 3 * 100 = 340, final = -200 + 340).
     */
    EXPECT_FLOAT_EQ(channels->parentCurrentOffset, PIXEL_CONTRACT_MID_SCROLL_OFFSET);
    EXPECT_FLOAT_EQ(channels->lazyHostMarginOffsetInParent, -PIXEL_CONTRACT_MID_SCROLL_OFFSET);
    EXPECT_FLOAT_EQ(channels->itemSelfLocalY,
        PIXEL_CONTRACT_HEADER_HEIGHT + kProbeItemIdx * PIXEL_CONTRACT_ITEM_HEIGHT);
    EXPECT_FLOAT_EQ(channels->finalPixelInParentContent,
        -PIXEL_CONTRACT_MID_SCROLL_OFFSET + PIXEL_CONTRACT_HEADER_HEIGHT + kProbeItemIdx * PIXEL_CONTRACT_ITEM_HEIGHT);
}

/**
 * @tc.name: PureScrollPreservesContentInvariants_001
 * @tc.desc: Verify a pure-scroll round-trip keeps totalMainSize_ stable, returns parent
 *           offset to its starting value, and restores the probe item's final pixel.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowStickyScrollTest, PureScrollPreservesContentInvariants_001, TestSize.Level1)
{
    BuildDemo();
    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(pattern_->layoutInfo_, nullptr);

    constexpr int32_t kProbeItemIdx = 3; // visible at both rest (0..4) and mid (2..6)
    const float totalMainSizeAtRest = pattern_->layoutInfo_->totalMainSize_;
    const float parentOffsetAtRest = static_cast<float>(scrollablePattern_->GetTotalOffset());
    auto channelsAtRest = CaptureChannels(kProbeItemIdx);
    ASSERT_TRUE(channelsAtRest.has_value()) << "probe item " << kProbeItemIdx << " not materialised at rest";
    ASSERT_GT(totalMainSizeAtRest, 0.0f);

    // Down by MID; record state.
    scrollablePattern_->UpdateCurrentOffset(-PIXEL_CONTRACT_MID_SCROLL_OFFSET, SCROLL_FROM_UPDATE);
    FlushUITasks();
    const float totalMainSizeMid = pattern_->layoutInfo_->totalMainSize_;
    const float parentOffsetMid = static_cast<float>(scrollablePattern_->GetTotalOffset());
    auto channelsAtMid = CaptureChannels(kProbeItemIdx);
    ASSERT_TRUE(channelsAtMid.has_value()) << "probe item " << kProbeItemIdx << " not materialised at mid";

    // Equal-and-opposite scroll back; verify round-trip.
    scrollablePattern_->UpdateCurrentOffset(PIXEL_CONTRACT_MID_SCROLL_OFFSET, SCROLL_FROM_UPDATE);
    FlushUITasks();
    const float totalMainSizeBack = pattern_->layoutInfo_->totalMainSize_;
    const float parentOffsetBack = static_cast<float>(scrollablePattern_->GetTotalOffset());
    auto channelsBack = CaptureChannels(kProbeItemIdx);
    ASSERT_TRUE(channelsBack.has_value()) << "probe item " << kProbeItemIdx << " not materialised at back";

    /**
     * @tc.expected: totalMainSize_ stable across rest / mid / back; parent offset returns to
     *               its starting value exactly (no leak round-trip).
     */
    EXPECT_NEAR(totalMainSizeMid, totalMainSizeAtRest, PIXEL_CONTRACT_SLACK);
    EXPECT_NEAR(totalMainSizeBack, totalMainSizeAtRest, PIXEL_CONTRACT_SLACK);
    EXPECT_FLOAT_EQ(parentOffsetMid, PIXEL_CONTRACT_MID_SCROLL_OFFSET);
    EXPECT_NEAR(parentOffsetBack, parentOffsetAtRest, PIXEL_CONTRACT_SLACK);

    /**
     * @tc.expected: self-local Y is constant; final pixel shifts by exactly the scroll delta at
     *               MID and returns to the rest value at BACK.
     */
    EXPECT_NEAR(channelsAtMid->itemSelfLocalY, channelsAtRest->itemSelfLocalY, PIXEL_CONTRACT_SLACK);
    EXPECT_NEAR(channelsBack->itemSelfLocalY, channelsAtRest->itemSelfLocalY, PIXEL_CONTRACT_SLACK);
    EXPECT_NEAR(channelsAtMid->finalPixelInParentContent,
        channelsAtRest->finalPixelInParentContent - PIXEL_CONTRACT_MID_SCROLL_OFFSET, PIXEL_CONTRACT_SLACK);
    EXPECT_NEAR(channelsBack->finalPixelInParentContent,
        channelsAtRest->finalPixelInParentContent, PIXEL_CONTRACT_SLACK);
}

/**
 * @tc.name: TopBoundary_001
 * @tc.desc: Verify item 0 sits at headerMainSize_ at the top edge (parent_offset = 0). A
 *           regression that drops headerMainSize_ from lane.startPos would land item 0 at 0.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowStickyScrollTest, TopBoundary_001, TestSize.Level1)
{
    BuildDemo();
    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    auto channels = CaptureChannels(0);
    ASSERT_TRUE(channels.has_value());

    /**
     * @tc.expected: at parent_offset = 0, item 0 final pixel = headerMainSize_ (40).
     */
    EXPECT_FLOAT_EQ(channels->parentCurrentOffset, 0.0f);
    EXPECT_FLOAT_EQ(channels->lazyHostMarginOffsetInParent, 0.0f);
    EXPECT_FLOAT_EQ(channels->itemSelfLocalY, PIXEL_CONTRACT_HEADER_HEIGHT);
    EXPECT_FLOAT_EQ(channels->finalPixelInParentContent, PIXEL_CONTRACT_HEADER_HEIGHT);
}

/**
 * @tc.name: BottomBoundary_001
 * @tc.desc: Verify the last item lands inside the viewport after ScrollToEdge(SCROLL_BOTTOM),
 *           and that totalMainSize_ matches headerMainSize_ + N*itemHeight + footerMainSize_.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowStickyScrollTest, BottomBoundary_001, TestSize.Level1)
{
    BuildDemo();
    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(pattern_->layoutInfo_, nullptr);

    scrollablePattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();

    /**
     * @tc.expected: endIndex_ reaches the last item, maxHeight_ within
     *               header + N*itemH + footer + slack, parent.currentOffset > 0.
     */
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, PIXEL_CONTRACT_ITEM_COUNT - 1);
    const float bodyHeightUpperBound =
        PIXEL_CONTRACT_HEADER_HEIGHT + PIXEL_CONTRACT_ITEM_COUNT * PIXEL_CONTRACT_ITEM_HEIGHT
        + PIXEL_CONTRACT_FOOTER_HEIGHT + PIXEL_CONTRACT_SLACK;
    EXPECT_LE(pattern_->layoutInfo_->maxHeight_, bodyHeightUpperBound);
    EXPECT_GT(pattern_->layoutInfo_->maxHeight_, 0.0f);
    EXPECT_GT(scrollablePattern_->GetTotalOffset(), 0.0);

    /**
     * @tc.expected: last item self-local Y = headerMainSize + (N-1) * itemHeight,
     *               final pixel sits inside the viewport [0, viewport_height].
     */
    auto channels = CaptureChannels(PIXEL_CONTRACT_ITEM_COUNT - 1);
    ASSERT_TRUE(channels.has_value()) << "last item should be materialised at bottom edge";

    const float expectedItemSelfLocalY =
        PIXEL_CONTRACT_HEADER_HEIGHT + (PIXEL_CONTRACT_ITEM_COUNT - 1) * PIXEL_CONTRACT_ITEM_HEIGHT;
    const float expectedFinalPixel =
        -channels->parentCurrentOffset + expectedItemSelfLocalY;

    EXPECT_NEAR(channels->lazyHostMarginOffsetInParent, -channels->parentCurrentOffset, PIXEL_CONTRACT_SLACK);
    EXPECT_FLOAT_EQ(channels->itemSelfLocalY, expectedItemSelfLocalY);
    EXPECT_NEAR(channels->finalPixelInParentContent, expectedFinalPixel, PIXEL_CONTRACT_SLACK);
    // Last item is visible somewhere in viewport: final pixel + itemHeight covers some of
    // [0, parent_viewport_height] without going below 0 or above viewport.
    EXPECT_GE(channels->finalPixelInParentContent + PIXEL_CONTRACT_ITEM_HEIGHT, 0.0f - PIXEL_CONTRACT_SLACK);
    EXPECT_LE(channels->finalPixelInParentContent, LAZY_WATER_FLOW_SCROLL_HEIGHT + PIXEL_CONTRACT_SLACK);
}

// Data-change preserve tests. Inserting or deleting items in front of the retained window must
// keep the visible probe item at the same final pixel even though its data-index changes.

/**
 * @tc.name: PrependPreservesVisibleItemPosition_001
 * @tc.desc: Verify inserting an item at data-index 0 after a mid scroll keeps the visible
 *           probe item at the same final pixel even though its data-index shifts +1.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowStickyScrollTest, PrependPreservesVisibleItemPosition_001, TestSize.Level1)
{
    BuildDemo();
    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(pattern_->layoutInfo_, nullptr);

    /**
     * @tc.steps: step1. Scroll to mid so a probe item is materialized + visible.
     */
    scrollablePattern_->UpdateCurrentOffset(-PIXEL_CONTRACT_MID_SCROLL_OFFSET, SCROLL_FROM_UPDATE);
    FlushUITasks();
    constexpr int32_t kProbeIdxBefore = 4;
    auto channelsBefore = CaptureChannels(kProbeIdxBefore);
    ASSERT_TRUE(channelsBefore.has_value())
        << "probe item " << kProbeIdxBefore << " should be visible at mid";

    /**
     * @tc.steps: step2. Prepend one item at data-index 0. Probe item's new data-index is +1.
     * @tc.expected: visible probe item's final pixel UNCHANGED (preserve invariant).
     */
    InsertItemAt(0);

    constexpr int32_t kProbeIdxAfter = kProbeIdxBefore + 1;
    auto channelsAfter = CaptureChannels(kProbeIdxAfter);
    ASSERT_TRUE(channelsAfter.has_value())
        << "probe item " << kProbeIdxAfter << " should still be visible after prepend";

    EXPECT_NEAR(channelsAfter->finalPixelInParentContent,
        channelsBefore->finalPixelInParentContent, PIXEL_CONTRACT_SLACK)
        << "prepend preserve: visible item shifted by "
        << (channelsAfter->finalPixelInParentContent - channelsBefore->finalPixelInParentContent)
        << " px (lane geometry not absorbing prefix delta correctly)";
}

/**
 * @tc.name: PrefixDeletePreservesVisibleItemPosition_001
 * @tc.desc: Verify erasing the item at data-index 0 after a mid scroll keeps the visible
 *           probe item at the same final pixel even though its data-index shifts -1.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowStickyScrollTest, PrefixDeletePreservesVisibleItemPosition_001, TestSize.Level1)
{
    BuildDemo();
    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    scrollablePattern_->UpdateCurrentOffset(-PIXEL_CONTRACT_MID_SCROLL_OFFSET, SCROLL_FROM_UPDATE);
    FlushUITasks();
    constexpr int32_t kProbeIdxBefore = 4;
    auto channelsBefore = CaptureChannels(kProbeIdxBefore);
    ASSERT_TRUE(channelsBefore.has_value())
        << "probe item " << kProbeIdxBefore << " should be visible at mid";

    EraseItemAt(0);

    constexpr int32_t kProbeIdxAfter = kProbeIdxBefore - 1;
    auto channelsAfter = CaptureChannels(kProbeIdxAfter);
    ASSERT_TRUE(channelsAfter.has_value())
        << "probe item " << kProbeIdxAfter << " should still be visible after prefix-delete";

    EXPECT_NEAR(channelsAfter->finalPixelInParentContent,
        channelsBefore->finalPixelInParentContent, PIXEL_CONTRACT_SLACK)
        << "prefix-delete preserve: visible item shifted by "
        << (channelsAfter->finalPixelInParentContent - channelsBefore->finalPixelInParentContent)
        << " px (lane geometry not absorbing prefix delta correctly)";
}

/**
 * @tc.name: HeaderFooterTotalStableOnIdle_001
 * @tc.desc: A header+footer LazyVWaterFlow must not inflate totalMainSize_ on idle frames.
 *           Regression lock for the footer double-count across idle frames.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, HeaderFooterTotalStableOnIdle_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    LazyWaterFlowLayoutModel::SetHeader([]() { CreateEdge(60.0f); });
    CreateContent(30);
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(40.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(pattern_->layoutInfo_, nullptr);

    // Baseline: body height exceeds header + footer (real content present).
    const float totalAfterLayout = pattern_->layoutInfo_->totalMainSize_;
    EXPECT_GT(totalAfterLayout, pattern_->GetHeaderMainSize() + pattern_->GetFooterMainSize());

    // Two idle frames must keep totalMainSize_ at the baseline (footer counted once).
    FlushIdleTask();
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->totalMainSize_, totalAfterLayout);
    FlushIdleTask();
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->totalMainSize_, totalAfterLayout);
}

/**
 * @tc.name: ListBackScrollWithFooter_001
 * @tc.desc: A footer-backed LazyVWaterFlow under a List must be able to scroll back from the bottom.
 *           Regression for the footer-leak that pinned startIndex_ at the bottom and blocked back-scroll.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, ListBackScrollWithFooter_001, TestSize.Level1)
{
    CreateList();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    CreateContent(20);
    LazyWaterFlowLayoutModel::SetFooter([]() { CreateEdge(60.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);

    scrollablePattern_->UpdateCurrentOffset(-1500.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    const int32_t startAtBottom = pattern_->layoutInfo_->startIndex_;
    EXPECT_GT(startAtBottom, 0);

    // Back-scroll: start index must decrease (the footer-leak bug pinned it at the bottom).
    scrollablePattern_->UpdateCurrentOffset(700.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_LT(pattern_->layoutInfo_->startIndex_, startAtBottom);
}

namespace {

void LazyVWaterFlowLayoutHeaderFooterTest::RunEdgeResizeLaneInvariance(
    const std::string& columnsTemplate, bool resizeFooter)
{
    constexpr float headerHeight = 40.0f;
    constexpr float footerHeight = 30.0f;
    constexpr float grownSize = 120.0f;
    constexpr int32_t itemCount = 20;

    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate(columnsTemplate);
    LazyVWaterFlowLayoutModel::SetHeader([]() { CreateLazyTestEdge(headerHeight); });
    CreateContent(itemCount);
    LazyVWaterFlowLayoutModel::SetFooter([]() { CreateLazyTestEdge(footerHeight); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto edgeNode = resizeFooter ? pattern_->GetFooterNode() : pattern_->GetHeaderNode();
    ASSERT_NE(edgeNode, nullptr);
    const float totalBefore = pattern_->layoutInfo_->totalMainSize_;
    const float edgeBefore = resizeFooter ? footerHeight : headerHeight;
    std::map<int32_t, std::pair<float, float>> beforeCoords;
    for (int32_t i = 0; i < itemCount; i++) {
        auto* pos = pattern_->layoutInfo_->GetPos(i);
        if (pos) {
            beforeCoords[i] = { pos->startPos, pos->endPos };
        }
    }
    ASSERT_FALSE(beforeCoords.empty());

    ResizeLazyEdge(*this, edgeNode, grownSize);

    ASSERT_EQ(resizeFooter ? pattern_->GetFooterMainSize() : pattern_->GetHeaderMainSize(), grownSize);
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->totalMainSize_, totalBefore + (grownSize - edgeBefore));
    int32_t checkedItems = 0;
    for (const auto& [idx, coords] : beforeCoords) {
        auto* pos = pattern_->layoutInfo_->GetPos(idx);
        if (!pos) {
            continue; // a taller edge can shrink the measured window
        }
        EXPECT_FLOAT_EQ(pos->startPos, coords.first) << "item " << idx;
        EXPECT_FLOAT_EQ(pos->endPos, coords.second) << "item " << idx;
        ++checkedItems;
    }
    EXPECT_GT(checkedItems, 0);
}

} // namespace

/**
 * @tc.name: BodyLocalItemStartGateClearsAfterPartialScroll001
 * @tc.desc: Body-local boundary gate: itemStart_ must compare the viewport against body 0, not headerMainSize_.
 *           After a small scroll past the top the gate must clear.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, BodyLocalItemStartGateClearsAfterPartialScroll001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    LazyVWaterFlowLayoutModel::SetHeader([]() { CreateLazyTestEdge(40.0f); });
    CreateContent(30);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    EXPECT_TRUE(pattern_->layoutInfo_->itemStart_); // at rest: at the top

    scrollablePattern_->UpdateCurrentOffset(-50.0f, SCROLL_FROM_UPDATE); // 0 < scroll < 2*header
    FlushUITasks();
    EXPECT_FALSE(pattern_->layoutInfo_->itemStart_); // scrolled off the top => not at item start
}

/**
 * @tc.name: NeedPredictUsesBodyContentEnd001
 * @tc.desc: Body-local contract: NeedPredict's view-overlaps-content check must compare the (body-local)
 *           extendedViewStartPos_ against the BODY content end, not the section total. A view sitting past the body
 *           but within header+footer distance of the section total must not request predict work.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, NeedPredictUsesBodyContentEnd001, TestSize.Level1)
{
    auto info = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    info->totalItemCount_ = 10;
    info->cacheEndPos_ = 100.0f;
    info->headerMainSize_ = 50.0f;
    info->footerMainSize_ = 30.0f;
    info->totalMainSize_ = 200.0f;        // section total; body end = 120
    info->extendedViewEndPos_ = 160.0f;   // > 0
    info->extendedViewStartPos_ = 150.0f; // body coords: already past the body end (120)
    // posMap_ empty => NeedPredict returns the overlap check alone.
    EXPECT_FALSE(info->NeedPredict());
}

/**
 * @tc.name: BodyLocalItemEndGatesWithTallHeader001
 * @tc.desc: Body-local boundary gates with body height < header: the bottom boundary (itemEnd_) must fire and
 *           AlignBackMaxHeight must collapse maxHeight_ to the body height (not floored at headerMainSize_);
 *           a remeasure with the real section total must keep reporting "at end" (DetectItemBoundary adds the
 *           header back to body-local viewEnd_ for a like-for-like comparison).
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, BodyLocalItemEndGatesWithTallHeader001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    LazyVWaterFlowLayoutModel::SetHeader([]() { CreateLazyTestEdge(200.0f); });
    CreateContent({ 50.0f, 50.0f }); // body 100 < header 200; section total 330 < viewport 450
    LazyVWaterFlowLayoutModel::SetFooter([]() { CreateLazyTestEdge(30.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    EXPECT_TRUE(pattern_->layoutInfo_->itemEnd_); // all content fits => bottom boundary reached
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->maxHeight_, 100.0f); // body-only, not floored at header(200)

    // Remeasure now that totalMainSize_ holds the real section total (330): still fully visible => still at end.
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_TRUE(pattern_->layoutInfo_->itemEnd_);
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->maxHeight_, 100.0f);
}

/**
 * @tc.name: OffscreenKeepEmptyHeaderResizeRebuildsSectionTotal001
 * @tc.desc: Body-local contract: on the keep-empty path (body fully outside the view; here forced by a header taller
 *           than the viewport) the carried-forward body belief must be LAST frame's body. Deriving it from the stale
 *           section total minus the CURRENT header would freeze the section total across a header resize instead of
 *           growing it by headerDelta.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, OffscreenKeepEmptyHeaderResizeRebuildsSectionTotal001, TestSize.Level1)
{
    constexpr float initialHeader = 600.0f; // > viewport 450 => body viewport is fully before the content
    constexpr float grownHeader = 700.0f;
    constexpr float footerHeight = 30.0f;

    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    LazyVWaterFlowLayoutModel::SetHeader([]() { CreateLazyTestEdge(initialHeader); });
    CreateContent({ 50.0f, 50.0f }); // body = 100
    LazyVWaterFlowLayoutModel::SetFooter([]() { CreateLazyTestEdge(footerHeight); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    const float totalBefore = pattern_->layoutInfo_->totalMainSize_;
    EXPECT_FLOAT_EQ(totalBefore, 100.0f + initialHeader + footerHeight);

    auto headerNode = pattern_->GetHeaderNode();
    ASSERT_NE(headerNode, nullptr);
    ResizeLazyEdge(*this, headerNode, grownHeader);

    ASSERT_EQ(pattern_->GetHeaderMainSize(), grownHeader);
    // Body belief (100) is unchanged; the section total must grow by exactly headerDelta.
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->totalMainSize_, 100.0f + grownHeader + footerHeight);
}

/**
 * @tc.name: BodyLocalLaneCoordsInvariantOnEdgeResize001
 * @tc.desc: Resizing the header (single and multi column) or the footer must not move any lane item's stored
 *           startPos/endPos; the section total grows by exactly the edge delta (body-local contract).
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutHeaderFooterTest, BodyLocalLaneCoordsInvariantOnEdgeResize001, TestSize.Level1)
{
    RunEdgeResizeLaneInvariance("1fr", false);
    RunEdgeResizeLaneInvariance("1fr 1fr", false);
    RunEdgeResizeLaneInvariance("1fr", true);
}

} // namespace OHOS::Ace::NG
