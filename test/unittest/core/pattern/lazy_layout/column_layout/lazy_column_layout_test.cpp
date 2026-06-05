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

#include "lazy_column_layout_test.h"

#include <vector>

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_model.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_model_ng.h"

namespace OHOS::Ace::NG {

using GetChildByIndexCallback = std::function<std::pair<std::string, RefPtr<NG::UINode>>(int32_t index)>;

class CustomLazyForEachBuilder : public Framework::MockLazyForEachBuilder {
public:
    CustomLazyForEachBuilder(int32_t itemCnt, GetChildByIndexCallback&& callback)
        : itemCnt_(itemCnt), getChildByIndexCallback_(std::move(callback))
    {}

protected:
    int32_t OnGetTotalCount() override
    {
        return itemCnt_;
    }

    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems) override
    {
        if (getChildByIndexCallback_) {
            return getChildByIndexCallback_(index);
        }
        return { std::to_string(index), nullptr };
    }

private:
    int32_t itemCnt_ = 0;
    GetChildByIndexCallback getChildByIndexCallback_ = nullptr;
};

void LazyColumnLayoutTest::CreateRepeatVirtualScrollNode(
    int32_t itemNumber, const std::function<std::pair<uint32_t, uint32_t>(int32_t, bool, bool)>& onGetRid4Index)
{
    RepeatVirtualScroll2ModelNG repeatModel;
    auto onActiveRange = [](int32_t start, int32_t end, int32_t cacheStart,
        int32_t cacheEnd, bool isCache, bool isImmediate) {};
    auto onPurge = []() {};
    auto onPurgeAll = []() {};
    auto onUpdateDirty = []() {};
    auto onRecycleItems = [](int32_t start, int32_t end) {};
    repeatModel.Create(
        itemNumber,
        itemNumber,
        0,
        onGetRid4Index,
        onRecycleItems,
        onActiveRange,
        nullptr,
        onPurge,
        onPurgeAll,
        onUpdateDirty);
}

void LazyColumnLayoutTest::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockAnimationManager::Enable(true);
}

void LazyColumnLayoutTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void LazyColumnLayoutTest::SetUp() {}

void LazyColumnLayoutTest::TearDown()
{
    RemoveFromStageNode();
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    MockAnimationManager::GetInstance().Reset();
}

RefPtr<FrameNode> LazyColumnLayoutTest::GetMainFrameNode()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    return AceType::DynamicCast<FrameNode>(element);
}

void LazyColumnLayoutTest::CreateLazyColumnLayout(VisibleIndexesChangeEvent&& callback)
{
    LazyColumnLayoutModel::Create();
    if (callback) {
        LazyColumnLayoutModel::SetOnVisibleIndexesChange(std::move(callback));
    }
    frameNode_ = GetMainFrameNode();
    pattern_ = frameNode_->GetPattern<LazyColumnLayoutPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<LazyColumnLayoutProperty>();
}

void LazyColumnLayoutTest::CreateLazyVGridLayout()
{
    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    gridModel.SetColumnsTemplate("1fr 1fr");
    lazyGridFrameNode_ = GetMainFrameNode();
    lazyGridPattern_ = lazyGridFrameNode_->GetPattern<LazyGridLayoutPattern>();
    lazyGridPattern_->axis_ = Axis::VERTICAL;
}

void LazyColumnLayoutTest::CreateStack(const CalcLength& width, const CalcLength& height)
{
    StackModelNG stackModel;
    stackModel.Create();
    ViewAbstract::SetWidth(width);
    ViewAbstract::SetHeight(height);
}

void LazyColumnLayoutTest::CreateContent(int32_t count, const CalcLength& width, const CalcLength& height)
{
    for (int32_t i = 0; i < count; i++) {
        CreateStack(width, height);
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void LazyColumnLayoutTest::CreateScroll()
{
    ScrollModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    scrollableFrameNode_ = GetMainFrameNode();
    scrollablePattern_ = scrollableFrameNode_->GetPattern<ScrollablePattern>();
}

void LazyColumnLayoutTest::CreateWaterFlow(WaterFlowLayoutMode mode)
{
    WaterFlowModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    model.SetLayoutMode(mode);
    scrollableFrameNode_ = GetMainFrameNode();
    scrollablePattern_ = scrollableFrameNode_->GetPattern<ScrollablePattern>();
}

void LazyColumnLayoutTest::CreateFlowItem()
{
    WaterFlowItemModelNG itemModel;
    itemModel.Create();
}

void LazyColumnLayoutTest::CreateList()
{
    ListModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    scrollableFrameNode_ = GetMainFrameNode();
    scrollablePattern_ = scrollableFrameNode_->GetPattern<ScrollablePattern>();
}

void LazyColumnLayoutTest::CreateListItems()
{
    // add 3 list items
    for (int32_t i = 0; i < 3; i++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        CreateStack(CalcLength(1, DimensionUnit::PERCENT), CalcLength(50)); // set the height of the list item to 50
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void LazyColumnLayoutTest::CreateListWithLazyColumnLayout(int32_t initialIndex, bool stackFromEnd)
{
    CreateList();
    ListModelNG::SetInitialIndex(AceType::RawPtr(scrollableFrameNode_), initialIndex);
    ListModelNG::SetListStackFromEnd(AceType::RawPtr(scrollableFrameNode_), stackFromEnd);
    CreateLazyColumnLayout();
    CreateContent(10);
    ViewStackProcessor::GetInstance()->Pop();
    CreateListItems();
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();
}

PaddingProperty LazyColumnLayoutTest::CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

void LazyColumnLayoutTest::AddChildAtIndex(int32_t index)
{
    CreateStack();
    RefPtr<UINode> currentNode = ViewStackProcessor::GetInstance()->Finish();
    auto currentFrameNode = AceType::DynamicCast<FrameNode>(currentNode);
    frameNode_->AddChild(currentFrameNode, index);
}

void LazyColumnLayoutTest::FlushIdleTask(const RefPtr<LazyColumnLayoutPattern>& pattern)
{
    CHECK_NULL_VOID(pattern);
    int32_t tryCount = 10;
    auto needPredict = pattern->layoutInfo_->NeedPredict();
    while (needPredict && tryCount > 0) {
        const int64_t time = GetSysTimestamp();
        auto pipeline = pattern->GetContext();
        pipeline->OnIdle(time + 16 * 1000000); // 16ms in nanoseconds
        auto host = pattern->GetHost();
        FlushUITasks(host);
        needPredict = pattern->layoutInfo_->NeedPredict();
        tryCount--;
    }
}

void LazyColumnLayoutTest::FlushListIdleTask(const RefPtr<ListPattern>& listPattern)
{
    CHECK_NULL_VOID(listPattern);
    int32_t tryCount = 10;
    auto predictParam = listPattern->GetPredictLayoutParamV2();
    while (predictParam && tryCount > 0) {
        const int64_t time = GetSysTimestamp();
        auto pipeline = listPattern->GetContext();
        pipeline->OnIdle(time + 16 * 1000000); // 16 * 1000000: 16ms
        auto host = listPattern->GetHost();
        FlushUITasks(host);
        predictParam = listPattern->GetPredictLayoutParamV2();
        tryCount--;
    }
}

/**
 * @tc.name: SpaceTest001
 * @tc.desc: Test Space property between items
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, SpaceTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy column layout with 10 items, no space
     * @tc.expected: total main size = 10 * ITEM_HEIGHT = 1000
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 10 * ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);

    /**
     * @tc.steps: step2. Update space to 20
     * @tc.expected: total main size = 10 * ITEM_HEIGHT + (10 - 1) * space = 1180
     */
    auto space = 20.0f;
    LazyColumnLayoutModel::SetSpace(AceType::RawPtr(frameNode_), Dimension(space));
    FlushUITasks(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 10 * ITEM_HEIGHT + 9 * space);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 3);

    /**
     * @tc.steps: step3. Update space to negative value
     * @tc.expected: negative space treated as 0, same as step1
     */
    LazyColumnLayoutModel::SetSpace(AceType::RawPtr(frameNode_), Dimension(-10));
    FlushUITasks(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 10 * ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
}

/**
 * @tc.name: AlignItemsTest001
 * @tc.desc: Test HorizontalAlign property (START, CENTER, END)
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, AlignItemsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy column layout with narrow children, default align is CENTER
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateContent(10, CalcLength(100));
    CreateDone();
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 100);

    /**
     * @tc.steps: step2. Default CENTER align
     * @tc.expected: child x offset is (200 - 100) / 2 = 50
     */
    EXPECT_EQ(GetChildX(frameNode_, 0), 50);

    /**
     * @tc.steps: step3. Update align to START
     * @tc.expected: child x offset is 0
     */
    LazyColumnLayoutModel::SetAlignItems(AceType::RawPtr(frameNode_), HorizontalAlign::START);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0);

    /**
     * @tc.steps: step4. Update align to END
     * @tc.expected: child x offset is 200 - 100 = 100
     */
    LazyColumnLayoutModel::SetAlignItems(AceType::RawPtr(frameNode_), HorizontalAlign::END);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 100);

    /**
     * @tc.steps: step5. Update align to CENTER
     * @tc.expected: child x offset is (200 - 100) / 2 = 50
     */
    LazyColumnLayoutModel::SetAlignItems(AceType::RawPtr(frameNode_), HorizontalAlign::CENTER);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 50);
}

/**
 * @tc.name: OnVisibleIndexesChangeTest001
 * @tc.desc: Verify callback returns -1,-1 when there are no child items
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, OnVisibleIndexesChangeTest001, TestSize.Level1)
{
    int32_t indexStart = -2; // Initialize to -2 to distinguish from callback value -1
    int32_t indexEnd = -2;
    auto callback = [&indexStart, &indexEnd](int32_t start, int32_t end) {
        indexStart = start;
        indexEnd = end;
    };

    CreateScroll();
    CreateLazyColumnLayout(std::move(callback));
    CreateDone();

    EXPECT_EQ(indexStart, -1);
    EXPECT_EQ(indexEnd, -1);
}

/**
 * @tc.name: OnVisibleIndexesChangeTest002
 * @tc.desc: Verify callback updates when scrolling
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, OnVisibleIndexesChangeTest002, TestSize.Level1)
{
    int32_t indexStart = -1;
    int32_t indexEnd = -1;
    auto callback = [&indexStart, &indexEnd](int32_t start, int32_t end) {
        indexStart = start;
        indexEnd = end;
    };

    CreateScroll();
    CreateLazyColumnLayout(std::move(callback));
    CreateContent(10);
    CreateDone();
    EXPECT_EQ(indexStart, 0);
    EXPECT_EQ(indexEnd, 4);

    /**
     * @tc.steps: step2. Scroll down incrementally: 50 + 50 + 100 = 200
     * @tc.expected: visible range updated via callback after each scroll
     */
    scrollablePattern_->UpdateCurrentOffset(-50, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(indexStart, 0);
    EXPECT_EQ(indexEnd, 5);

    scrollablePattern_->UpdateCurrentOffset(-50, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(indexStart, 0);
    EXPECT_EQ(indexEnd, 5);

    scrollablePattern_->UpdateCurrentOffset(-100, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(indexStart, 1);
    EXPECT_EQ(indexEnd, 6);
}

/**
 * @tc.name: OnVisibleIndexesChangeTest003
 * @tc.desc: Verify OnVisibleIndexesChange callback for two inner LazyColumnLayouts
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, OnVisibleIndexesChangeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll > LazyColumnLayout > two LazyColumnLayouts with callbacks
     * @tc.expected: first inner LazyColumnLayout callback returns 0, 4;
     *               second inner LazyColumnLayout callback returns -1, -1 (not visible)
     */
    int32_t indexStart1 = -2; // Initialize to -2 to distinguish from callback value -1
    int32_t indexEnd1 = -2;
    auto callback1 = [&indexStart1, &indexEnd1](int32_t start, int32_t end) {
        indexStart1 = start;
        indexEnd1 = end;
    };
    int32_t indexStart2 = -2; // Initialize to -2 to distinguish from callback value -1
    int32_t indexEnd2 = -2;
    auto callback2 = [&indexStart2, &indexEnd2](int32_t start, int32_t end) {
        indexStart2 = start;
        indexEnd2 = end;
    };

    CreateScroll();
    CreateLazyColumnLayout();
    CreateLazyColumnLayout(std::move(callback1));
    CreateContent(5);
    ViewStackProcessor::GetInstance()->Pop();
    CreateLazyColumnLayout(std::move(callback2));
    CreateContent(5);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->Pop();
    CreateDone();
    auto frameNode = GetChildFrameNode(scrollableFrameNode_, 0);
    auto pattern = frameNode->GetPattern<LazyColumnLayoutPattern>();

    FlushIdleTask(pattern);
    EXPECT_EQ(indexStart1, 0);
    EXPECT_EQ(indexEnd1, 4);
    EXPECT_EQ(indexStart2, -1);
    EXPECT_EQ(indexEnd2, -1);

    /**
     * @tc.steps: step2. Scroll to where both LazyColumnLayouts are visible
     * @tc.expected: both callbacks return valid visible ranges
     */
    scrollablePattern_->UpdateCurrentOffset(-300, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(indexStart1, 2);
    EXPECT_EQ(indexEnd1, 4);
    EXPECT_EQ(indexStart2, 0);
    EXPECT_EQ(indexEnd2, 2);

    /**
     * @tc.steps: step3. Scroll until first LazyColumnLayout is out of view
     * @tc.expected: first inner LazyColumnLayout callback returns -1, -1 (not visible);
     *               second inner LazyColumnLayout callback returns 0, 4
     */
    scrollablePattern_->UpdateCurrentOffset(-300, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    FlushIdleTask(pattern);
    EXPECT_EQ(indexStart1, -1);
    EXPECT_EQ(indexEnd1, -1);
    EXPECT_EQ(indexStart2, 0);
    EXPECT_EQ(indexEnd2, 4);
}

/**
 * @tc.name: PaddingMarginTest001
 * @tc.desc: Test padding and margin effects on layout
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, PaddingMarginTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy column layout
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();

    /**
     * @tc.steps: step2. Assert start and end index before padding
     * @tc.expected: startIndex and endIndex are correct before padding
     */
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);

    /**
     * @tc.steps: step3. Update padding top and bottom
     * @tc.expected: visible range reduced due to padding
     */
    PaddingProperty padding = CreatePadding(0, 100, 0, 100);
    layoutProperty_->UpdatePadding(padding);
    FlushUITasks(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1200);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 3);

    /**
     * @tc.steps: step4. Update margin top and bottom
     * @tc.expected: visible range further reduced
     */
    PaddingProperty margin = CreatePadding(0, 100, 0, 100);
    layoutProperty_->UpdateMargin(margin);
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 2);
}

/**
 * @tc.name: RTLTest001
 * @tc.desc: Test right-to-left layout with START, CENTER, END alignment
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, RTLTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy column layout with narrow children, align START
     */
    CreateScroll();
    CreateLazyColumnLayout();
    LazyColumnLayoutModel::SetAlignItems(AceType::RawPtr(frameNode_), HorizontalAlign::START);
    CreateContent(10, CalcLength(100));
    CreateDone();

    /**
     * @tc.steps: step2. Verify LTR START alignment
     * @tc.expected: child starts at x=0
     */
    EXPECT_EQ(GetChildX(frameNode_, 0), 0);

    /**
     * @tc.steps: step3. Update to RTL direction with START alignment
     * @tc.expected: child position mirrored to x=100
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 100);

    /**
     * @tc.steps: step4. RTL with CENTER alignment
     * @tc.expected: child centered at x=50
     */
    LazyColumnLayoutModel::SetAlignItems(AceType::RawPtr(frameNode_), HorizontalAlign::CENTER);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 50);

    /**
     * @tc.steps: step5. RTL with END alignment
     * @tc.expected: child at x=0
     */
    LazyColumnLayoutModel::SetAlignItems(AceType::RawPtr(frameNode_), HorizontalAlign::END);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0);
}

/**
 * @tc.name: WidthHeightTest001
 * @tc.desc: Test user-defined width and height
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, WidthHeightTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy column layout
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();

    /**
     * @tc.steps: step2. Update width and height
     * @tc.expected: dimensions updated
     */
    auto size = CalcSize(CalcLength(160), CalcLength(750));
    layoutProperty_->UpdateUserDefinedIdealSize(size);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildWidth(scrollableFrameNode_, 0), 160);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 750);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);

    /**
     * @tc.steps: step3. Reset user defined ideal size
     * @tc.expected: dimensions return to default
     */
    layoutProperty_->ClearUserDefinedIdealSize(true, true);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildWidth(scrollableFrameNode_, 0), SCROLL_WIDTH);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 10 * ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
}

/**
 * @tc.name: SizeConstraintTest001
 * @tc.desc: Test min/max size constraints
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, SizeConstraintTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy column layout
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();

    /**
     * @tc.steps: step2. Update max size
     * @tc.expected: dimensions constrained
     */
    auto size = CalcSize(CalcLength(160), CalcLength(750));
    layoutProperty_->UpdateCalcMaxSize(size);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildWidth(scrollableFrameNode_, 0), 160);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 750);

    /**
     * @tc.steps: step3. Reset max size, update min size
     * @tc.expected: dimensions constrained by min
     */
    layoutProperty_->ResetCalcMaxSize();
    size = CalcSize(CalcLength(240), CalcLength(1800));
    layoutProperty_->UpdateCalcMinSize(size);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildWidth(scrollableFrameNode_, 0), 240);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 1800);

    /**
     * @tc.steps: step4. Reset min size
     * @tc.expected: dimensions return to default
     */
    layoutProperty_->ResetCalcMinSize();
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildWidth(scrollableFrameNode_, 0), SCROLL_WIDTH);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 10 * ITEM_HEIGHT);
}

/**
 * @tc.name: LayoutPolicyTest001
 * @tc.desc: Test measure result when setting matchParent
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LayoutPolicyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyColumnLayout with MATCH_PARENT layout policy
     */
    RefPtr<FrameNode> lazyColumn;
    auto column = CreateColumn([this, &lazyColumn](ColumnModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        LazyColumnLayoutModel::Create();
        ViewAbstractModelNG viewModel;
        viewModel.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
        viewModel.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
        ViewStackProcessor::GetInstance()->PopContainer();
        lazyColumn = AceType::DynamicCast<FrameNode>(element);
    });
    ViewStackProcessor::GetInstance()->Finish();
    ASSERT_NE(column, nullptr);
    ASSERT_EQ(column->GetChildren().size(), 1);
    CreateLayoutTask(column);

    auto geometryNode = lazyColumn->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: AddDelChildrenTest001
 * @tc.desc: Test adding and removing children
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, AddDelChildrenTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy column layout with 10 items
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 10 * ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 10);

    /**
     * @tc.steps: step2. Remove 5 children
     * @tc.expected: totalMainSize and totalItemCount updated
     */
    for (int32_t i = 0; i < 5; i++) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 5 * ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 5);

    /**
     * @tc.steps: step3. Add 6 children
     * @tc.expected: totalMainSize and totalItemCount updated
     */
    for (int32_t i = 0; i < 6; i++) {
        AddChildAtIndex(0);
    }
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 11 * ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 11);
}

/**
 * @tc.name: AddDelChildrenTest002
 * @tc.desc: Test adding and removing all children
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, AddDelChildrenTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create empty lazy column layout
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateDone();
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 0);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 0);

    /**
     * @tc.steps: step2. Add 6 children
     * @tc.expected: totalMainSize and totalItemCount updated
     */
    for (int32_t i = 0; i < 6; i++) {
        AddChildAtIndex(0);
    }
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 6 * ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 6);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 6 * ITEM_HEIGHT);

    /**
     * @tc.steps: step3. Remove all children
     * @tc.expected: totalMainSize and totalItemCount reset to 0
     */
    for (int32_t i = 0; i < 6; i++) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 0);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 0);
}

/**
 * @tc.name: AddDelChildrenTest003
 * @tc.desc: Test onVisibleIndexesChange when deleting items while scrolled
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, AddDelChildrenTest003, TestSize.Level1)
{
    int32_t indexStart = -2;
    int32_t indexEnd = -2;
    auto callback = [&indexStart, &indexEnd](int32_t start, int32_t end) {
        indexStart = start;
        indexEnd = end;
    };

    /**
     * @tc.steps: step1. Create WaterFlow > LazyColumnLayout with 10 items and onVisibleIndexesChange callback
     * @tc.expected: callback fires with range 0-4
     */
    CreateWaterFlow();
    CreateLazyColumnLayout(std::move(callback));
    CreateContent(10);
    CreateDone();

    EXPECT_EQ(indexStart, 0);
    EXPECT_EQ(indexEnd, 4);

    /**
     * @tc.steps: step2. Scroll down 150px
     * @tc.expected: visible range updated to 1-6, scroll offset is -150
     */
    scrollablePattern_->UpdateCurrentOffset(-150, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 10);
    EXPECT_EQ(indexStart, 1);
    EXPECT_EQ(indexEnd, 6);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0), -150);

    /**
     * @tc.steps: step3. Delete child at index 0 (above visible area)
     * @tc.expected: totalItemCount decreases to 9, visible range and scroll offset unchanged
     */
    frameNode_->RemoveChildAtIndex(0);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 9);
    EXPECT_EQ(indexStart, 1);
    EXPECT_EQ(indexEnd, 6);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0), -150);

    /**
     * @tc.steps: step4. Scroll to bottom by additional -300px (total -450px)
     * @tc.expected: visible range updated to 4-8
     */
    scrollablePattern_->UpdateCurrentOffset(-300, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(indexStart, 4);
    EXPECT_EQ(indexEnd, 8);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0), -450);

    /**
     * @tc.steps: step5. Delete child at index 0 (above visible area) again
     * @tc.expected: totalItemCount decreases to 8, visible range recalculated to 3-7,
     *               scroll offset adjusted from -450 to -350
     */
    frameNode_->RemoveChildAtIndex(0);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 8);
    EXPECT_EQ(indexStart, 3);
    EXPECT_EQ(indexEnd, 7);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0), -350);
}

/**
 * @tc.name: AddDelChildrenTest004
 * @tc.desc: Test onVisibleIndexesChange when add items while scrolled
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, AddDelChildrenTest004, TestSize.Level1)
{
    int32_t indexStart = -2;
    int32_t indexEnd = -2;
    auto callback = [&indexStart, &indexEnd](int32_t start, int32_t end) {
        indexStart = start;
        indexEnd = end;
    };

    /**
     * @tc.steps: step1. Create WaterFlow > LazyColumnLayout with 10 items and onVisibleIndexesChange callback
     * @tc.expected: callback fires with range 0-4
     */
    CreateWaterFlow();
    CreateLazyColumnLayout(std::move(callback));
    CreateContent(10);
    CreateDone();

    EXPECT_EQ(indexStart, 0);
    EXPECT_EQ(indexEnd, 4);

    /**
     * @tc.steps: step2. Scroll down 150px
     * @tc.expected: visible range updated to 1-6, child 1 relative y offset is -50
     */
    scrollablePattern_->UpdateCurrentOffset(-150, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 10);
    EXPECT_EQ(indexStart, 1);
    EXPECT_EQ(indexEnd, 6);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0) + GetChildY(frameNode_, 1), -50);

    /**
     * @tc.steps: step3. Add child at the top (index 0, above visible area)
     * @tc.expected: totalItemCount increases to 11, visible range and child 1 relative position unchanged
     */
    AddChildAtIndex(0);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 11);
    EXPECT_EQ(indexStart, 1);
    EXPECT_EQ(indexEnd, 6);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0) + GetChildY(frameNode_, 1), -50);

    /**
     * @tc.steps: step4. Add child at the end (index 11, below visible area)
     * @tc.expected: totalItemCount increases to 12, visible range and child 1 relative position unchanged
     */
    AddChildAtIndex(11);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 12);
    EXPECT_EQ(indexStart, 1);
    EXPECT_EQ(indexEnd, 6);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0) + GetChildY(frameNode_, 1), -50);
}

/**
 * @tc.name: UpdateChildSizeTest001
 * @tc.desc: Test child position after dynamically modifying child size while scrolled
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, UpdateChildSizeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WaterFlow > LazyColumnLayout with 10 items (each 100px height)
     */
    CreateWaterFlow();
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();

    /**
     * @tc.steps: step2. Scroll down 150px (child 0 partially visible, child 1 visible)
     * @tc.expected: child 1 relative y offset (WaterFlow y + LazyColumnLayout y) is -50
     */
    scrollablePattern_->UpdateCurrentOffset(-150, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0) + GetChildY(frameNode_, 1), -50);

    /**
     * @tc.steps: step3. Shrink child 0 height from 100 to 50 (above visible area)
     * @tc.expected: child 1 relative y offset unchanged (-50), position is stable
     */
    auto child0 = GetChildFrameNode(frameNode_, 0);
    auto child0LayoutProp = child0->GetLayoutProperty();
    child0LayoutProp->UpdateUserDefinedIdealSize(CalcSize(CalcLength(1, DimensionUnit::PERCENT), CalcLength(50)));
    child0->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0) + GetChildY(frameNode_, 1), -50);

    /**
     * @tc.steps: step4. Grow child 0 height from 50 to 200 (above visible area)
     * @tc.expected: child 1 relative y offset unchanged (-50), position is stable
     */
    child0LayoutProp->UpdateUserDefinedIdealSize(CalcSize(CalcLength(1, DimensionUnit::PERCENT), CalcLength(200)));
    child0->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0) + GetChildY(frameNode_, 1), -50);

    /**
     * @tc.steps: step5. Grow child 2 height from 100 to 200 (within visible area)
     * @tc.expected: child 1 relative y offset unchanged (-50), position is stable
     */
    auto child2 = GetChildFrameNode(frameNode_, 2);
    auto child2LayoutProp = child2->GetLayoutProperty();
    child2LayoutProp->UpdateUserDefinedIdealSize(CalcSize(CalcLength(1, DimensionUnit::PERCENT), CalcLength(200)));
    child2->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0) + GetChildY(frameNode_, 1), -50);
}

/**
 * @tc.name: NeedPredictTest001
 * @tc.desc: Test NeedPredict returns correct value
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, NeedPredictTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy column layout
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();

    /**
     * @tc.steps: step2. After initial layout, check NeedPredict
     * @tc.expected: NeedPredict should be true when there are items beyond cache
     */
    bool needPredict = pattern_->layoutInfo_->NeedPredict();
    EXPECT_TRUE(needPredict);

    /**
     * @tc.steps: step3. After flushing idle tasks, check NeedPredict
     * @tc.expected: NeedPredict should be false when all cache is filled
     */
    FlushIdleTask(pattern_);
    needPredict = pattern_->layoutInfo_->NeedPredict();
    EXPECT_FALSE(needPredict);
}

/**
 * @tc.name: LazyColumnInScroll001
 * @tc.desc: Verify Scroll with LazyColumnLayout startIndex/endIndex and cached range
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll with LazyColumnLayout and 10 items
     * @tc.expected: layout visible items and predict items
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();

    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 6);

    /**
     * @tc.steps: step2. Scroll down
     * @tc.expected: start and end index updated
     */
    EXPECT_NE(scrollablePattern_, nullptr);
    scrollablePattern_->UpdateCurrentOffset(-200, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 6);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 8);

    /**
     * @tc.steps: step3. Scroll to bottom
     * @tc.expected: last items visible
     */
    scrollablePattern_->UpdateCurrentOffset(-350, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 5);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 9);

    /**
     * @tc.steps: step4. Scroll back to top
     * @tc.expected: start and end index restored to initial values
     */
    scrollablePattern_->UpdateCurrentOffset(550, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 6);
}

/**
 * @tc.name: LazyColumnInScrollWithScrollDirection001
 * @tc.desc: Verify Scroll with different scrollDirection property
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInScrollWithScrollDirection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create vertical Scroll with LazyColumnLayout
     * @tc.expected: LazyColumnLayout implements lazy loading
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();
    EXPECT_NE(scrollablePattern_, nullptr);
    EXPECT_EQ(scrollablePattern_->GetAxis(), Axis::VERTICAL);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);

    /**
     * @tc.steps: step2. Set Scroll axis to HORIZONTAL
     * @tc.expected: LazyColumnLayout fully expanded without lazy loading
     */
    ScrollModelNG::SetAxis(AceType::RawPtr(scrollableFrameNode_), Axis::HORIZONTAL);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
}

/**
 * @tc.name: LazyColumnInScrollWithInitialOffset001
 * @tc.desc: Verify Scroll with initialOffset affects LazyColumnLayout startIndex/endIndex
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInScrollWithInitialOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll with initialOffset and LazyColumnLayout
     * @tc.expected: LazyColumnLayout starts from offset position with correct indexes
     */
    CreateScroll();
    ScrollModelNG::SetInitialOffset(
        AceType::RawPtr(scrollableFrameNode_),
        OffsetT<CalcDimension>(CalcDimension(0), CalcDimension(200)));
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();

    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 6);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 8);

    /**
     * @tc.steps: step2. Scroll down further
     * @tc.expected: start and end index updated correctly
     */
    EXPECT_NE(scrollablePattern_, nullptr);
    scrollablePattern_->UpdateCurrentOffset(-200, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 8);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 9);
}

/**
 * @tc.name: LazyColumnInList001
 * @tc.desc: Verify List with LazyColumnLayout startIndex/endIndex and cached range
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInList001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with LazyColumnLayout and 10 items
     * @tc.expected: layout visible items and predict items
     */
    CreateList();
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();

    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 6);

    /**
     * @tc.steps: step2. Scroll down
     * @tc.expected: start and end index updated
     */
    EXPECT_NE(scrollablePattern_, nullptr);
    scrollablePattern_->UpdateCurrentOffset(-200, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 6);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 8);

    /**
     * @tc.steps: step3. Scroll to bottom
     * @tc.expected: last items visible
     */
    scrollablePattern_->UpdateCurrentOffset(-350, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 5);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 9);

    /**
     * @tc.steps: step4. Scroll back to top
     * @tc.expected: start and end index restored to initial values
     */
    scrollablePattern_->UpdateCurrentOffset(550, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 6);
}

/**
 * @tc.name: LazyColumnInListWithInitialIndex001
 * @tc.desc: Verify List with initialIndex=0, child 0 (first LazyColumnLayout) at y=0
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInListWithInitialIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with initialIndex=0
     *            List children: LazyColumnLayout(1000px) + 3 ListItems(50px each) + LazyColumnLayout(1000px)
     * @tc.expected: List has 5 children, child 0 at y=0
     */
    CreateListWithLazyColumnLayout(0);
    EXPECT_NE(scrollableFrameNode_, nullptr);
    auto children = scrollableFrameNode_->GetChildren();
    EXPECT_GE(children.size(), 5u);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0), 0);
}

/**
 * @tc.name: LazyColumnInListWithInitialIndex002
 * @tc.desc: Verify List with initialIndex=1, child 1 (first ListItem) at y=0
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInListWithInitialIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with initialIndex=1
     * @tc.expected: child 1 at y=0
     */
    CreateListWithLazyColumnLayout(1);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 1), 0);

    /**
     * @tc.steps: step2. Flush List idle task and check child 0's lazy layout range
     * @tc.expected: child 0's startIndex=-1, endIndex=-1 (not in viewport)
     */
    FlushListIdleTask(scrollableFrameNode_->GetPattern<ListPattern>());
    auto child0 = GetChildFrameNode(scrollableFrameNode_, 0);
    auto pattern0 = child0->GetPattern<LazyColumnLayoutPattern>();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, -1);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, -1);

    /**
     * @tc.steps: step3. Flush child 0's idle task to trigger cache layout
     * @tc.expected: child 0's cachedStartIndex=7, cachedEndIndex=9
     */
    FlushIdleTask(pattern0);
    EXPECT_EQ(pattern0->layoutInfo_->cachedStartIndex_, 7);
    EXPECT_EQ(pattern0->layoutInfo_->cachedEndIndex_, 9);

    /**
     * @tc.steps: step4. Check child 4's lazy layout range
     * @tc.expected: child 4's startIndex=0, endIndex=3
     */
    auto child4 = GetChildFrameNode(scrollableFrameNode_, 4);
    auto pattern4 = child4->GetPattern<LazyColumnLayoutPattern>();
    EXPECT_EQ(pattern4->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern4->layoutInfo_->endIndex_, 3);

    /**
     * @tc.steps: step5. Flush child 4's idle task to trigger cache layout
     * @tc.expected: child 4's cachedStartIndex=0, cachedEndIndex=5
     */
    FlushIdleTask(pattern4);
    EXPECT_EQ(pattern4->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern4->layoutInfo_->cachedEndIndex_, 5);
}

/**
 * @tc.name: LazyColumnInListWithInitialIndex003
 * @tc.desc: Verify List with initialIndex=3, child 3 (third ListItem) at y=0
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInListWithInitialIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with initialIndex=3
     * @tc.expected: List scrolls to child 3 (third ListItem, 50px) at y=0
     */
    CreateListWithLazyColumnLayout(3);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 3), 0);
}

/**
 * @tc.name: LazyColumnInListWithInitialIndex004
 * @tc.desc: Verify List with initialIndex=4, child 4 (second LazyColumnLayout) at y=0
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInListWithInitialIndex004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with initialIndex=4
     * @tc.expected: List scrolls to child 4 (second LazyColumnLayout, 1000px) at y=0
     */
    CreateListWithLazyColumnLayout(4);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 4), 0);
}

/**
 * @tc.name: LazyColumnInListWithStackFromEnd001
 * @tc.desc: Verify List with stackFromEnd=true and initialIndex=0, child 0 bottom-aligned at y=-550
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInListWithStackFromEnd001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with stackFromEnd=true, initialIndex=0
     * @tc.expected: child 0 (first LazyColumnLayout, 1000px) bottom-aligned,
     *               bottom edge at viewport bottom (y=450), top at y = 450 - 1000 = -550
     */
    CreateListWithLazyColumnLayout(0, true);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0), -550);
}

/**
 * @tc.name: LazyColumnInListWithStackFromEnd002
 * @tc.desc: Verify List with stackFromEnd=true and initialIndex=1, child 1 bottom-aligned at y=400
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInListWithStackFromEnd002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with stackFromEnd=true, initialIndex=1
     * @tc.expected: child 1 (first ListItem, 50px) bottom-aligned,
     *               bottom edge at viewport bottom (y=450), top at y = 450 - 50 = 400
     */
    CreateListWithLazyColumnLayout(1, true);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 1), 400);
}

/**
 * @tc.name: LazyColumnInListWithStackFromEnd003
 * @tc.desc: Verify List with stackFromEnd=true and initialIndex=3, child 3 bottom-aligned at y=400
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInListWithStackFromEnd003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with stackFromEnd=true, initialIndex=3
     * @tc.expected: child 3 (third ListItem, 50px) bottom-aligned,
     *               bottom edge at viewport bottom (y=450), top at y = 450 - 50 = 400
     */
    CreateListWithLazyColumnLayout(3, true);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 3), 400);
}

/**
 * @tc.name: LazyColumnInListWithStackFromEnd004
 * @tc.desc: Verify List with stackFromEnd=true and initialIndex=4, child 4 bottom-aligned at y=-550
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInListWithStackFromEnd004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with stackFromEnd=true, initialIndex=4
     * @tc.expected: child 4 (second LazyColumnLayout, 1000px) bottom-aligned,
     *               bottom edge at viewport bottom (y=450), top at y = 450 - 1000 = -550
     */
    CreateListWithLazyColumnLayout(4, true);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 4), -550);
}

/**
 * @tc.name: LazyColumnInListWithLanes001
 * @tc.desc: Verify LazyColumnLayout in List with lanes=2
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInListWithLanes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with lanes=2 and LazyColumnLayout with 10 items
     * @tc.expected: layout all items
     */
    CreateList();
    ListModelNG::SetLanes(AceType::RawPtr(scrollableFrameNode_), 2);
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();

    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
}

/**
 * @tc.name: LazyColumnInWaterFlow001
 * @tc.desc: Test basic lazy layout in WaterFlow container
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInWaterFlow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy column layout in WaterFlow
     * @tc.expected: layout visible items and predict items
     */
    CreateWaterFlow();
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), SCROLL_WIDTH);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 10 * ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 6);

    /**
     * @tc.steps: step2. Scroll down
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-200, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 6);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 8);

    /**
     * @tc.steps: step3. Scroll to bottom
     * @tc.expected: last items visible
     */
    scrollablePattern_->UpdateCurrentOffset(-350, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 5);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 9);

    /**
     * @tc.steps: step4. Scroll back to top
     * @tc.expected: start and end index restored to initial values
     */
    scrollablePattern_->UpdateCurrentOffset(550, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 6);
}

/**
 * @tc.name: LazyColumnInWaterFlow002
 * @tc.desc: Test lazy column in WaterFlow SW mode with space change above display area
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInWaterFlow002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create two lazy columns in WaterFlow SW mode
     */
    CreateWaterFlow(WaterFlowLayoutMode::SLIDING_WINDOW);
    CreateLazyColumnLayout();
    CreateContent(10);
    ViewStackProcessor::GetInstance()->Pop();
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();

    /**
     * @tc.steps: step2. Scroll to second lazy column
     * @tc.expected: first column out of view
     */
    scrollablePattern_->UpdateCurrentOffset(-1200, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    auto pattern1 = GetChildPattern<LazyColumnLayoutPattern>(scrollableFrameNode_, 1);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, 4);

    /**
     * @tc.steps: step3. Update first column space and scroll backward
     * @tc.expected: scroll offset adjusted by space change
     */
    auto pattern0 = GetChildPattern<LazyColumnLayoutPattern>(scrollableFrameNode_, 0);
    auto hostNode = pattern0->GetHost();
    LazyColumnLayoutModel::SetSpace(AceType::RawPtr(hostNode), Dimension(20));
    scrollablePattern_->UpdateCurrentOffset(400, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 6);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 9);
}

/**
 * @tc.name: LazyColumnInWaterFlow003
 * @tc.desc: Test lazy column with variable item heights in WaterFlow
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInWaterFlow003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy column with variable height items
     */
    CreateWaterFlow(WaterFlowLayoutMode::SLIDING_WINDOW);
    CreateLazyColumnLayout();
    std::array<float, 3> itemHeights = { 80, 100, 90 };
    for (int32_t i = 0; i < 10; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
        ViewAbstract::SetHeight(CalcLength(itemHeights[i % 3]));
        ViewStackProcessor::GetInstance()->Pop();
    }
    CreateDone();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 5);

    /**
     * @tc.steps: step2. Scroll down
     * @tc.expected: visible range updated correctly
     */
    scrollablePattern_->UpdateCurrentOffset(-350, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_GE(pattern_->layoutInfo_->startIndex_, 2);
    EXPECT_LE(pattern_->layoutInfo_->startIndex_, 4);
}

/**
 * @tc.name: NestedLazyColumnLayout001
 * @tc.desc: Test nested LazyColumnLayout in Scroll container
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, NestedLazyColumnLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll > LazyColumnLayout > LazyColumnLayout > 10 items
     * @tc.expected: inner LazyColumnLayout layout visible items and predict items
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateLazyColumnLayout();
    CreateContent(10);
    CreateDone();

    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 6);

    /**
     * @tc.steps: step2. Scroll down
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-200, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 6);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 8);
}

/**
 * @tc.name: NestedLazyGridLayout001
 * @tc.desc: Test nested LazyVGridLayout inside LazyColumnLayout in Scroll container
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, NestedLazyGridLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll > LazyColumnLayout > LazyVGridLayout > 30 items
     * @tc.expected: LazyVGridLayout layout visible items and predict items
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateLazyVGridLayout();
    CreateContent(30);
    CreateDone();

    /**
     * @tc.steps: step2. Verify LazyVGridLayout visible range
     * @tc.expected: 2 lanes, startIndex=0, endIndex=9
     */
    EXPECT_EQ(lazyGridPattern_->layoutInfo_->lanes_, 2);
    EXPECT_EQ(lazyGridPattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(lazyGridPattern_->layoutInfo_->endIndex_, 9);

    /**
     * @tc.steps: step3. Flush idle task and verify cached range
     * @tc.expected: cachedStartIndex=0, cachedEndIndex=13
     */
    int32_t tryCount = 10;
    while (lazyGridPattern_->layoutInfo_->NeedPredict() && tryCount > 0) {
        const int64_t time = GetSysTimestamp();
        auto pipeline = lazyGridPattern_->GetContext();
        pipeline->OnIdle(time + 16 * 1000000);
        FlushUITasks(lazyGridFrameNode_);
        tryCount--;
    }
    EXPECT_EQ(lazyGridPattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(lazyGridPattern_->layoutInfo_->cachedEndIndex_, 13);
}

/**
 * @tc.name: EdgeCase001
 * @tc.desc: Verify LazyColumnLayout with single item
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, EdgeCase001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyColumnLayout with single item
     * @tc.expected: startIndex and endIndex are 0, totalMainSize equals ITEM_HEIGHT
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateContent(1);
    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, ITEM_HEIGHT);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), ITEM_HEIGHT);
}

/**
 * @tc.name: EdgeCase002
 * @tc.desc: Verify LazyColumnLayout with no items
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, EdgeCase002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyColumnLayout with no items
     * @tc.expected: startIndex and endIndex are -1, totalMainSize is 0
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, -1);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, -1);
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 0);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 0);
}

/**
 * @tc.name: LazyForEachTest001
 * @tc.desc: Test LazyColumnLayout with LazyForEach generated children.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyForEachTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy column layout with LazyForEach
     * @tc.expected: layout visible items and predict items
     */
    CreateScroll();
    CreateLazyColumnLayout();
    auto mockLazy = AceType::MakeRefPtr<CustomLazyForEachBuilder>(10,
        [](int32_t index) -> std::pair<std::string, RefPtr<NG::UINode>> {
            StackModelNG stackModel;
            stackModel.Create();
            ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
            ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
            auto node = ViewStackProcessor::GetInstance()->Finish();
            return { std::to_string(index), node };
        }
    );
    LazyForEachModelNG lazyForEachModelNG;
    RefPtr<NG::LazyForEachBuilder> builder = mockLazy;
    lazyForEachModelNG.Create(builder);
    CreateDone();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 10 * ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 6);
    EXPECT_EQ(mockLazy->startIndex_, 0);
    EXPECT_EQ(mockLazy->endIndex_, 6);

    /**
     * @tc.steps: step2. Scroll down
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-200, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 6);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 8);
    EXPECT_EQ(mockLazy->startIndex_, 0);
    EXPECT_EQ(mockLazy->endIndex_, 8);
}

/**
 * @tc.name: RepeatVirtualScrollTest001
 * @tc.desc: Test LazyColumnLayout with Repeat generated children.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, RepeatVirtualScrollTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy column layout with RepeatVirtualScroll2
     * @tc.expected: layout visible items and predict items
     */
    CreateScroll();
    CreateLazyColumnLayout();
    CreateRepeatVirtualScrollNode(10,
        [](uint32_t index, bool inAnimation, bool restoreCache) -> std::pair<uint32_t, uint32_t> {
            StackModelNG stackModel;
            stackModel.Create();
            ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
            ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
            ViewStackProcessor::GetInstance()->Pop();
            return { 1, OnGetRid4IndexResult::CREATED_NEW_NODE };
        }
    );
    CreateDone();
    auto repeat = AceType::DynamicCast<RepeatVirtualScroll2Node>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(repeat, nullptr);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 10 * ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 6);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 6);
    EXPECT_EQ(repeat->prevActiveRangeStart_, 0);
    EXPECT_EQ(repeat->prevActiveRangeEnd_, 6);

    /**
     * @tc.steps: step2. Scroll down
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-200, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 6);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 8);
    EXPECT_EQ(repeat->prevActiveRangeStart_, 0);
    EXPECT_EQ(repeat->prevActiveRangeEnd_, 8);
}

/**
 * @tc.name: LazyColumnInFlowItem001
 * @tc.desc: Verify LazyColumnLayout inside WaterFlow FlowItem works with lazy loading
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, LazyColumnInFlowItem001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WaterFlow with 4 FlowItems, each containing LazyColumnLayout
     *           with 5 child items. This tests the nested scenario where LazyColumnLayout
     *           acts as the content of WaterFlow FlowItems.
     * @tc.expected: WaterFlow created with 4 FlowItems, each containing a LazyColumnLayout child
     */
    CreateWaterFlow(WaterFlowLayoutMode::TOP_DOWN);
    for (int32_t i = 0; i < 4; i++) {
        CreateFlowItem();
        CreateLazyColumnLayout();
        CreateContent(5);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->Pop();
    }
    CreateDone();

    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);

    /**
     * @tc.steps: step2. Check first FlowItem's LazyColumnLayout visible range.
     *           Verify that only the first FlowItem is laid out with all 5 items visible.
     * @tc.expected: First LazyColumnLayout visible range is [0, 4]
     */
    auto flowItem0 = GetChildFrameNode(scrollableFrameNode_, 0);
    ASSERT_NE(flowItem0, nullptr);
    auto lazyColumn0 = GetChildFrameNode(flowItem0, 0);
    ASSERT_NE(lazyColumn0, nullptr);
    auto pattern0 = lazyColumn0->GetPattern<LazyColumnLayoutPattern>();
    ASSERT_NE(pattern0, nullptr);
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 4);

    /**
     * @tc.steps: step3. Scroll WaterFlow down by 200px to reveal the second FlowItem.
     *           The first LazyColumnLayout loses its first item from viewport,
     *           the second LazyColumnLayout becomes partially visible.
     * @tc.expected: First LazyColumnLayout visible range shifts to [1, 4],
     *               second LazyColumnLayout visible range is [0, 1].
     *               After idle task, cache coverage extends:
     *               first [0, 4], second [0, 3].
     */
    scrollablePattern_->UpdateCurrentOffset(-200, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    auto flowItem1 = GetChildFrameNode(scrollableFrameNode_, 1);
    ASSERT_NE(flowItem1, nullptr);
    auto lazyColumn1 = GetChildFrameNode(flowItem1, 0);
    ASSERT_NE(lazyColumn1, nullptr);
    auto pattern1 = lazyColumn1->GetPattern<LazyColumnLayoutPattern>();
    ASSERT_NE(pattern1, nullptr);
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 1);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 4);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, 1);
    FlushIdleTask(pattern0);
    FlushIdleTask(pattern1);
    EXPECT_EQ(pattern0->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern0->layoutInfo_->cachedEndIndex_, 4);
    EXPECT_EQ(pattern1->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->cachedEndIndex_, 3);
}

/**
 * @tc.name: VisibleIndexWithBoundaryPadding001
 * @tc.desc: Test List with LazyColumnLayout, ContentClip BOUNDARY mode and scroll
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, VisibleIndexWithBoundaryPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with LazyColumnLayout, content clip and top/bottom padding
     */
    int32_t visibleStart = -1;
    int32_t visibleEnd = -1;

    CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(scrollableFrameNode_), ContentClipMode::BOUNDARY, nullptr);
    auto listLayoutProperty = scrollableFrameNode_->GetLayoutProperty();
    ASSERT_NE(listLayoutProperty, nullptr);
    PaddingProperty padding = CreatePadding(0, 100, 0, 150);
    listLayoutProperty->UpdatePadding(padding);

    auto callback = [&visibleStart, &visibleEnd](int32_t start, int32_t end) {
        visibleStart = start;
        visibleEnd = end;
    };
    CreateLazyColumnLayout(std::move(callback));
    CreateContent(10);
    CreateDone();

    /**
     * @tc.steps: step2. Check visible indexes
     * @tc.expected: visible indexes should exclude safe area padding
     */
    EXPECT_EQ(visibleStart, 0);
    EXPECT_EQ(visibleEnd, 2);
    EXPECT_EQ(visibleStart, pattern_->layoutInfo_->startIndex_);
    EXPECT_LE(visibleEnd, pattern_->layoutInfo_->endIndex_);

    /**
     * @tc.steps: step3. Scroll and check visible indexes
     * @tc.expected: visible indexes should update correctly after scroll
     */
    scrollablePattern_->UpdateCurrentOffset(-210, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);

    EXPECT_EQ(visibleStart, 2);
    EXPECT_EQ(visibleEnd, 4);
    EXPECT_GT(visibleStart, pattern_->layoutInfo_->startIndex_);
    EXPECT_LE(visibleEnd, pattern_->layoutInfo_->endIndex_);
}

/**
 * @tc.name: VisibleIndexWithSafeAreaPadding001
 * @tc.desc: Test List with LazyColumnLayout and ContentClip SAFE_AREA mode
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, VisibleIndexWithSafeAreaPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with LazyColumnLayout and SAFE_AREA content clip
     */
    int32_t visibleStart = -1;
    int32_t visibleEnd = -1;

    CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(scrollableFrameNode_), ContentClipMode::SAFE_AREA, nullptr);
    auto listLayoutProperty = scrollableFrameNode_->GetLayoutProperty();
    ASSERT_NE(listLayoutProperty, nullptr);
    PaddingProperty safeAreaPadding;
    safeAreaPadding.top = std::make_optional<CalcLength>(100);
    safeAreaPadding.bottom = std::make_optional<CalcLength>(150);
    listLayoutProperty->UpdateSafeAreaPadding(safeAreaPadding);

    auto callback = [&visibleStart, &visibleEnd](int32_t start, int32_t end) {
        visibleStart = start;
        visibleEnd = end;
    };
    CreateLazyColumnLayout(std::move(callback));
    CreateContent(10);
    CreateDone();

    /**
     * @tc.steps: step2. Check visible indexes
     * @tc.expected: visible indexes should exclude safe area padding
     */
    EXPECT_EQ(visibleStart, 0);
    EXPECT_EQ(visibleEnd, 2);
    EXPECT_EQ(visibleStart, pattern_->layoutInfo_->startIndex_);
    EXPECT_LE(visibleEnd, pattern_->layoutInfo_->endIndex_);

    /**
     * @tc.steps: step3. Scroll and check visible indexes
     * @tc.expected: visible indexes should update correctly after scroll
     */
    scrollablePattern_->UpdateCurrentOffset(-210, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);

    EXPECT_EQ(visibleStart, 2);
    EXPECT_EQ(visibleEnd, 4);
    EXPECT_GT(visibleStart, pattern_->layoutInfo_->startIndex_);
    EXPECT_LE(visibleEnd, pattern_->layoutInfo_->endIndex_);
}

namespace {
void CreateLazyEdge(float height)
{
    StackModelNG stackModel;
    stackModel.Create();
    ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewStackProcessor::GetInstance()->Pop();
}
} // namespace

/**
 * @tc.name: NestedGridItemsRenderWithHeaderFooter001
 * @tc.desc: A header/footer LazyVGridLayout nested under LazyColumnLayout must activate its content items.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, NestedGridItemsRenderWithHeaderFooter001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyColumnLayout();
    CreateLazyVGridLayout();
    LazyGridLayoutModel::SetSticky(StickyStyle::BOTH);
    LazyGridLayoutModel::SetHeader([]() { CreateLazyEdge(60.0f); });
    CreateContent(30);
    LazyGridLayoutModel::SetFooter([]() { CreateLazyEdge(40.0f); });
    CreateDone();

    ASSERT_NE(lazyGridPattern_, nullptr);
    EXPECT_EQ(lazyGridPattern_->layoutInfo_->startIndex_, 0);
    EXPECT_GT(lazyGridPattern_->layoutInfo_->endIndex_, 0);

    auto headerNode = lazyGridPattern_->GetHeaderNode();
    auto footerNode = lazyGridPattern_->GetFooterNode();
    ASSERT_NE(headerNode, nullptr);
    ASSERT_NE(footerNode, nullptr);
    EXPECT_TRUE(headerNode->IsActive());
    EXPECT_TRUE(footerNode->IsActive());

    auto firstItemWrapper = lazyGridFrameNode_->GetChildByIndex(1);
    ASSERT_NE(firstItemWrapper, nullptr);
    auto firstItemNode = firstItemWrapper->GetHostNode();
    ASSERT_NE(firstItemNode, nullptr);
    EXPECT_TRUE(firstItemNode->IsActive());
}

/**
 * @tc.name: StickyToggleKeepsHeaderLaidOut_001
 * @tc.desc: Toggling sticky at runtime must not drop the header. Regression for the header collapsing onto
 *           item 0 (headerMainSize -> 0) when a property-only relayout addressed a stale edge reference; the
 *           header must stay sized and keep items below it across BOTH -> NONE -> BOTH without a scroll.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, StickyToggleKeepsHeaderLaidOut_001, TestSize.Level1)
{
    constexpr float headerHeight = 40.0f;
    constexpr float footerHeight = 30.0f;

    CreateScroll();
    CreateLazyColumnLayout();
    LazyColumnLayoutModel::SetSticky(StickyStyle::BOTH);
    LazyColumnLayoutModel::SetHeader([]() { CreateLazyEdge(headerHeight); });
    CreateContent(12);
    LazyColumnLayoutModel::SetFooter([]() { CreateLazyEdge(footerHeight); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);
    auto headerNode = pattern_->GetHeaderNode();
    ASSERT_NE(headerNode, nullptr);
    EXPECT_TRUE(headerNode->IsActive());
    EXPECT_EQ(pattern_->GetHeaderMainSize(), headerHeight);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[0].startPos, headerHeight);

    // BOTH -> NONE: header must not be dropped.
    layoutProperty_->CleanDirty();
    LazyColumnLayoutModel::SetSticky(AceType::RawPtr(frameNode_), StickyStyle::NONE);
    frameNode_->MarkDirtyNode(layoutProperty_->GetPropertyChangeFlag());
    FlushUITasks();

    EXPECT_EQ(pattern_->GetStickyStyle(), StickyStyle::NONE);
    headerNode = pattern_->GetHeaderNode();
    ASSERT_NE(headerNode, nullptr);
    EXPECT_TRUE(headerNode->IsActive());
    EXPECT_EQ(pattern_->GetHeaderMainSize(), headerHeight);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[0].startPos, headerHeight);

    // NONE -> BOTH: header is still intact after toggling back.
    layoutProperty_->CleanDirty();
    LazyColumnLayoutModel::SetSticky(AceType::RawPtr(frameNode_), StickyStyle::BOTH);
    frameNode_->MarkDirtyNode(layoutProperty_->GetPropertyChangeFlag());
    FlushUITasks();

    EXPECT_EQ(pattern_->GetStickyStyle(), StickyStyle::BOTH);
    EXPECT_EQ(pattern_->GetHeaderMainSize(), headerHeight);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[0].startPos, headerHeight);
}

/**
 * @tc.name: HeaderFooterTotalStableOnIdle001
 * @tc.desc: A header+footer LazyColumnLayout must not inflate totalMainSize_ on predictive (idle) frames.
 *           Regression for the footer being double-counted on the PROPERTY_UPDATE_MEASURE_SELF predict path.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, HeaderFooterTotalStableOnIdle001, TestSize.Level1)
{
    constexpr float headerHeight = 60.0f;
    constexpr float footerHeight = 40.0f;

    CreateScroll();
    CreateLazyColumnLayout();
    LazyColumnLayoutModel::SetHeader([]() { CreateLazyEdge(headerHeight); });
    CreateContent(30);
    LazyColumnLayoutModel::SetFooter([]() { CreateLazyEdge(footerHeight); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    const float totalAfterLayout = pattern_->layoutInfo_->totalMainSize_;
    EXPECT_GT(totalAfterLayout, pattern_->GetHeaderMainSize() + pattern_->GetFooterMainSize());

    FlushIdleTask(pattern_);
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->totalMainSize_, totalAfterLayout);
    FlushIdleTask(pattern_);
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->totalMainSize_, totalAfterLayout);
}

/**
 * @tc.name: ListBackScrollWithFooter001
 * @tc.desc: A footer-backed LazyColumnLayout under a List must be able to scroll back from the bottom.
 * @tc.type: FUNC
 */
HWTEST_F(LazyColumnLayoutTest, ListBackScrollWithFooter001, TestSize.Level1)
{
    CreateList();
    CreateLazyColumnLayout();
    CreateContent(20);
    LazyColumnLayoutModel::SetFooter([]() { CreateLazyEdge(60.0f); });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);

    scrollablePattern_->UpdateCurrentOffset(-1500.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    const int32_t startAtBottom = pattern_->layoutInfo_->startIndex_;
    EXPECT_GT(startAtBottom, 0);

    // Back-scroll: the content must move back (start index decreases); the footer-leak bug pinned it at the bottom.
    scrollablePattern_->UpdateCurrentOffset(700.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_LT(pattern_->layoutInfo_->startIndex_, startAtBottom);
}
} // namespace OHOS::Ace::NG
