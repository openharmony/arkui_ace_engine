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

#include "lazy_grid_layout_test.h"

#include <vector>

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_property.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"

namespace OHOS::Ace::NG {

namespace {
using VisibleRange = std::pair<int32_t, int32_t>;
}

void LazyGridLayoutTest::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockAnimationManager::Enable(true);
    g_segmentedWaterflow = false;
}

void LazyGridLayoutTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void LazyGridLayoutTest::SetUp() {}

void LazyGridLayoutTest::TearDown()
{
    RemoveFromStageNode();
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    MockAnimationManager::GetInstance().Reset();
}

RefPtr<FrameNode> LazyGridLayoutTest::GetMainFrameNode()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    return AceType::DynamicCast<FrameNode>(element);
}

void LazyGridLayoutTest::CreateStack(Axis axis)
{
    StackModelNG stackModel;
    stackModel.Create();
    if (axis == Axis::HORIZONTAL) {
        ViewAbstract::SetHeight(CalcLength(1, DimensionUnit::PERCENT));
        ViewAbstract::SetWidth(CalcLength(ITEM_HEIGHT));
    } else {
        ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
        ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
    }
}

void LazyGridLayoutTest::CreateLazyGridLayout(Axis axis)
{
    LazyVGridLayoutModel model;
    model.Create();
    if (axis == Axis::HORIZONTAL) {
        ViewAbstract::SetHeight(CalcLength(SCROLL_WIDTH));
    } else {
        ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    }
    model.SetColumnsTemplate("1fr 1fr");
    frameNode_ = GetMainFrameNode();
    pattern_ = frameNode_->GetPattern<LazyGridLayoutPattern>();
    pattern_->axis_ = axis;
    layoutProperty_ = frameNode_->GetLayoutProperty<LazyGridLayoutProperty>();
}

void LazyGridLayoutTest::CreateContent(int32_t count)
{
    for (int32_t i = 0; i < count; i++) {
        CreateStack();
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void LazyGridLayoutTest::CreateWaterFlow(WaterFlowLayoutMode mode)
{
    WaterFlowModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    model.SetLayoutMode(mode);
    scrollableFrameNode_ = GetMainFrameNode();
    scrollablePattern_ = scrollableFrameNode_->GetPattern<ScrollablePattern>();
}

void LazyGridLayoutTest::CreateList()
{
    ListModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    scrollableFrameNode_ = GetMainFrameNode();
    scrollablePattern_ = scrollableFrameNode_->GetPattern<ScrollablePattern>();
    listFrameNode_ = scrollableFrameNode_;
    listPattern_ = listFrameNode_->GetPattern<ListPattern>();
}

void LazyGridLayoutTest::CreateScroll()
{
    ScrollModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    scrollableFrameNode_ = GetMainFrameNode();
    scrollablePattern_ = scrollableFrameNode_->GetPattern<ScrollablePattern>();
}

PaddingProperty LazyGridLayoutTest::CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

void LazyGridLayoutTest::AddChild()
{
    CreateStack(Axis::VERTICAL);
    RefPtr<UINode> currentNode = ViewStackProcessor::GetInstance()->Finish();
    auto currentFrameNode = AceType::DynamicCast<FrameNode>(currentNode);
    currentFrameNode->MountToParent(frameNode_);
}

void LazyGridLayoutTest::FlushIdleTask(const RefPtr<LazyGridLayoutPattern>& pattern)
{
    int32_t tryCount = 10;
    auto needPredict = pattern->layoutInfo_->NeedPredict();
    while (needPredict && tryCount > 0) {
        const int64_t time = GetSysTimestamp();
        auto pipeline = pattern->GetContext();
        pipeline->OnIdle(time + 16 * 1000000); // 16 * 1000000: 16ms
        FlushUITasks();
        needPredict = pattern->layoutInfo_->NeedPredict();
        tryCount--;
    }
}

/**
 * @tc.name: ColumnsTemplateTest001
 * @tc.desc: Test ColumnsTemplate.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, ColumnsTemplateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     * @tc.expected: layout visible items and predict items
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1500);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 200);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 13);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 13);

    /**
     * @tc.steps: step2. UpdateColumnsTemplate 1fr
     * @tc.expected: start and end index updated
     */
    layoutProperty_->UpdateColumnsTemplate("1fr");
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 3000);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 6);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 6);

    /**
     * @tc.steps: step3. UpdateColumnsTemplate 1fr 1fr 1fr
     * @tc.expected: start and end index updated
     */
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1000);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 14);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 20);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 20);
}

/**
 * @tc.name: ColumnsTemplateTest002
 * @tc.desc: Test ColumnsTemplate repeat mode.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, ColumnsTemplateTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();

    /**
     * @tc.steps: step2. UpdateColumnsTemplate 'repeat(auto-fit, x)'
     * @tc.expected: start and end index updated
     */
    layoutProperty_->UpdateColumnsTemplate("repeat(auto-fit, 80)");
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1500);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 100);
    EXPECT_EQ(GetChildX(frameNode_, 1), 100);
    layoutProperty_->UpdateColumnsTemplate("repeat(auto-fit, 120)");
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 3000);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 1);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 200);

    /**
     * @tc.steps: step3. UpdateColumnsTemplate 'repeat(auto-fit, x)'
     * @tc.expected: start and end index updated
     */
    layoutProperty_->UpdateColumnsTemplate("repeat(auto-fill, 80)");
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1500);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 80);
    EXPECT_EQ(GetChildX(frameNode_, 1), 80);
    layoutProperty_->UpdateColumnsTemplate("repeat(auto-fill, 120)");
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 3000);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 1);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 120);

    /**
     * @tc.steps: step4. UpdateColumnsTemplate 'repeat(auto-stretch, x)'
     * @tc.expected: start and end index updated
     */
    layoutProperty_->UpdateColumnsTemplate("repeat(auto-stretch, 80)");
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1500);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 80);
    EXPECT_EQ(GetChildX(frameNode_, 1), 120);
    layoutProperty_->UpdateColumnsTemplate("repeat(auto-stretch, 60)");
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1000);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 60);
}

/**
 * @tc.name: ColumnsGapTest001
 * @tc.desc: Test ColumnsGap.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, ColumnsGapTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();

    /**
     * @tc.steps: step2. UpdateColumnGap 20
     * @tc.expected: start and end index updated
     */
    layoutProperty_->UpdateColumnGap(Dimension(20));
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1500);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 90);
    EXPECT_EQ(GetChildX(frameNode_, 1), 110);
}

/**
 * @tc.name: RowsGapTest001
 * @tc.desc: Test RowsGap.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, RowsGapTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();

    /**
     * @tc.steps: step2. UpdateColumnGap 20
     * @tc.expected: start and end index updated
     */
    layoutProperty_->UpdateRowGap(Dimension(20));
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1780);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 7);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 11);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 11);
}

/**
 * @tc.name: PaddingMarginTest001
 * @tc.desc: Test padding and margin.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, PaddingMarginTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();

    /**
     * @tc.steps: step2. Update padding top and bottom.
     * @tc.expected: start and end index updated
     */
    PaddingProperty padding = CreatePadding(0, 100, 0, 100);;
    layoutProperty_->UpdatePadding(padding);
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1700);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 7);

    /**
     * @tc.steps: step3. Update margin top and bottom.
     * @tc.expected: start and end index updated
     */
    PaddingProperty margin = CreatePadding(0, 100, 0, 100);;
    layoutProperty_->UpdateMargin(margin);
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1700);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 5);
}

/**
 * @tc.name: RTLTest001
 * @tc.desc: Test RTL layout.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, RTLTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();

    /**
     * @tc.steps: step2. Update padding top and bottom.
     * @tc.expected: start and end index updated
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), 100);
    EXPECT_EQ(GetChildX(frameNode_, 1), 0);
    EXPECT_EQ(GetChildX(frameNode_, 2), 100);
    EXPECT_EQ(GetChildX(frameNode_, 3), 0);
}

/**
 * @tc.name: WidthHeightTest001
 * @tc.desc: Test LazyGrid set width height.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, WidthHeightTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();

    /**
     * @tc.steps: step2. Update width and height.
     * @tc.expected: width and height updated
     */
    auto size = CalcSize(CalcLength(160), CalcLength(750));
    layoutProperty_->UpdateUserDefinedIdealSize(size);
    FlushUITasks();
    EXPECT_EQ(GetChildWidth(scrollableFrameNode_, 0), 160);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 750);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    EXPECT_EQ(GetChildX(frameNode_, 1), 80);

    /**
     * @tc.steps: step3. Update width and height.
     * @tc.expected: width and height updated
     */
    size = CalcSize(CalcLength(240), CalcLength(150));
    layoutProperty_->UpdateUserDefinedIdealSize(size);
    FlushUITasks();
    EXPECT_EQ(GetChildWidth(scrollableFrameNode_, 0), 240);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 150);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    EXPECT_EQ(GetChildX(frameNode_, 1), 120);

    /**
     * @tc.steps: step4. Reset user defined ideal size.
     * @tc.expected: width and height updated
     */
    layoutProperty_->ClearUserDefinedIdealSize(true, true);
    FlushUITasks();
    EXPECT_EQ(GetChildWidth(scrollableFrameNode_, 0), 200);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 1500);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    EXPECT_EQ(GetChildX(frameNode_, 1), 100);
}

/**
 * @tc.name: SizeConstraintTest001
 * @tc.desc: Test LazyGrid set size constraint.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, SizeConstraintTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();

    /**
     * @tc.steps: step2. Update max size.
     * @tc.expected: width and height updated
     */
    auto size = CalcSize(CalcLength(160), CalcLength(750));
    layoutProperty_->UpdateCalcMaxSize(size);
    FlushUITasks();
    EXPECT_EQ(GetChildWidth(scrollableFrameNode_, 0), 160);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 750);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    EXPECT_EQ(GetChildX(frameNode_, 1), 80);

    /**
     * @tc.steps: step3. Update min size.
     * @tc.expected: width and height updated
     */
    layoutProperty_->ResetCalcMaxSize();
    size = CalcSize(CalcLength(240), CalcLength(1800));
    layoutProperty_->UpdateCalcMinSize(size);
    FlushUITasks();
    EXPECT_EQ(GetChildWidth(scrollableFrameNode_, 0), 240);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 1800);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    EXPECT_EQ(GetChildX(frameNode_, 1), 120);

    /**
     * @tc.steps: step4. reset min size.
     * @tc.expected: width and height updated
     */
    layoutProperty_->ResetCalcMinSize();
    FlushUITasks();
    EXPECT_EQ(GetChildWidth(scrollableFrameNode_, 0), 200);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 1500);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    EXPECT_EQ(GetChildX(frameNode_, 1), 100);
}

/**
 * @tc.name: WaterFlowLayoutTest001
 * @tc.desc: Lazy layout in WaterFlow
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, WaterFlowLayoutTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     * @tc.expected: layout visible items and predict items
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1500);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 200);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 13);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 13);

    /**
     * @tc.steps: step2. Update refences position
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-120, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 2);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 11);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 15);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 15);

    /**
     * @tc.steps: step3. Scroll to bottom
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-1500, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 20);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 29);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 16);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 29);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 16);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 29);
}

/**
 * @tc.name: WaterFlowLayoutTest002
 * @tc.desc: Lazy layout in WaterFlow, waterFlow adjust offset.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, WaterFlowLayoutTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     * @tc.expected: layout visible items and predict items
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();

    /**
     * @tc.steps: step2. Update refences position
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-420, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 8);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 17);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 2);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 21);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 2);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 21);

    /**
     * @tc.steps: step3. UpdateColumnsTemplate
     * @tc.expected: waterFlow adjust offset
     */
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    FlushUITasks();
    EXPECT_EQ(scrollablePattern_->GetTotalOffset(), 220);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 6);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 20);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 26);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 26);
}

/**
 * @tc.name: WaterFlowLayoutTest003
 * @tc.desc: Lazy layout in WaterFlow SW mode, update LazyGrid column template above display area.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, WaterFlowLayoutTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     * @tc.expected: layout visible items and predict items
     */
    CreateWaterFlow(WaterFlowLayoutMode::SLIDING_WINDOW);
    CreateLazyGridLayout();
    CreateContent(19);
    ViewStackProcessor::GetInstance()->Pop();
    CreateLazyGridLayout();
    CreateContent(19);
    CreateDone();

    /**
     * @tc.steps: step2. Update refences position
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-420, SCROLL_FROM_UPDATE);
    FlushUITasks();
    auto pattern0 = GetChildPattern<LazyGridLayoutPattern>(scrollableFrameNode_, 0);
    auto pattern1 = GetChildPattern<LazyGridLayoutPattern>(scrollableFrameNode_, 1);
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 8);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 17);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, -1);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, -1);
    FlushIdleTask(pattern0);
    EXPECT_EQ(pattern0->layoutInfo_->cachedStartIndex_, 2);
    EXPECT_EQ(pattern0->layoutInfo_->cachedEndIndex_, 18);
    EXPECT_EQ(pattern0->layoutInfo_->layoutedStartIndex_, 2);
    EXPECT_EQ(pattern0->layoutInfo_->layoutedEndIndex_, 18);

    /**
     * @tc.steps: step3. Update refences position, LazyGrid0 out of view.
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-600, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, 9);

    /**
     * @tc.steps: step3. Update LazyGrid0 lanes and scroll backward.
     * @tc.expected: start and end index updated
     */
    auto layoutProperty0 = pattern0->GetLayoutProperty<LazyGridLayoutProperty>();
    layoutProperty0->UpdateColumnsTemplate("1fr 1fr 1fr");
    scrollablePattern_->UpdateCurrentOffset(300, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 12);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 18);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, 3);
}

/**
 * @tc.name: WaterFlowLayoutTest004
 * @tc.desc: Lazy layout in WaterFlow SW mode, update LazyGrid row gap above display area.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, WaterFlowLayoutTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     * @tc.expected: layout visible items and predict items
     */
    CreateWaterFlow(WaterFlowLayoutMode::SLIDING_WINDOW);
    CreateLazyGridLayout();
    CreateContent(19);
    ViewStackProcessor::GetInstance()->Pop();
    CreateLazyGridLayout();
    CreateContent(19);
    CreateDone();

    /**
     * @tc.steps: step2. Update refences position
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-420, SCROLL_FROM_UPDATE);
    FlushUITasks();
    auto pattern0 = GetChildPattern<LazyGridLayoutPattern>(scrollableFrameNode_, 0);
    auto pattern1 = GetChildPattern<LazyGridLayoutPattern>(scrollableFrameNode_, 1);
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 8);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 17);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, -1);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, -1);
    FlushIdleTask(pattern0);
    EXPECT_EQ(pattern0->layoutInfo_->cachedStartIndex_, 2);
    EXPECT_EQ(pattern0->layoutInfo_->cachedEndIndex_, 18);
    EXPECT_EQ(pattern0->layoutInfo_->layoutedStartIndex_, 2);
    EXPECT_EQ(pattern0->layoutInfo_->layoutedEndIndex_, 18);

    /**
     * @tc.steps: step3. Update refences position, LazyGrid0 out of view.
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-600, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, 9);

    /**
     * @tc.steps: step3. Update LazyGrid0 lanes and scroll backward.
     * @tc.expected: start and end index updated
     */
    auto layoutProperty0 = pattern0->GetLayoutProperty<LazyGridLayoutProperty>();
    layoutProperty0->UpdateRowGap(Dimension(10));
    scrollablePattern_->UpdateCurrentOffset(300, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 14);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 18);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 1), 280);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, 3);
}

/**
 * @tc.name: WaterFlowLayoutTest005
 * @tc.desc: First LazyGird only display bottom padding, Update column template.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, WaterFlowLayoutTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     */
    CreateWaterFlow(WaterFlowLayoutMode::SLIDING_WINDOW);
    CreateLazyGridLayout();
    PaddingProperty padding = CreatePadding(0, 100, 0, 100);;
    layoutProperty_->UpdatePadding(padding);
    CreateContent(19);
    ViewStackProcessor::GetInstance()->Pop();
    CreateLazyGridLayout();
    CreateContent(19);
    CreateDone();

    /**
     * @tc.steps: step2. Update padding top and bottom.
     * @tc.expected: start and end index updated
     */
    auto pattern0 = GetChildPattern<LazyGridLayoutPattern>(scrollableFrameNode_, 0);
    auto pattern1 = GetChildPattern<LazyGridLayoutPattern>(scrollableFrameNode_, 1);
    FlushUITasks();
    EXPECT_EQ(pattern0->GetHost()->GetGeometryNode()->GetFrameSize().Height(), 1200);
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 7);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0), 0);

    /**
     * @tc.steps: step3. Update refences position
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-520, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 8);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 17);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, -1);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, -1);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0), -520);

    /**
     * @tc.steps: step4. Update refences position
     * @tc.expected: LazyGrid0 out of view.
     */
    scrollablePattern_->UpdateCurrentOffset(-600, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 19);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 19);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 1), 80);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, 7);

    /**
     * @tc.steps: step5. Update columns template
     * @tc.expected: Display content not change.
     */
    auto layoutProperty0 = pattern0->GetLayoutProperty<LazyGridLayoutProperty>();
    layoutProperty0->UpdateColumnsTemplate("1fr 1fr 1fr");
    FlushUITasks();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 19);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 19);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, 7);

    /**
     * @tc.steps: step6. Scroll backward.
     * @tc.expected:  start and end index updated.
     */
    scrollablePattern_->UpdateCurrentOffset(300, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 12);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 18);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, 1);
}

/**
 * @tc.name: WaterFlowLayoutTest006
 * @tc.desc: First LazyGird only display bottom padding, Update rows gap.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, WaterFlowLayoutTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     */
    CreateWaterFlow(WaterFlowLayoutMode::SLIDING_WINDOW);
    CreateLazyGridLayout();
    PaddingProperty padding = CreatePadding(0, 100, 0, 100);;
    layoutProperty_->UpdatePadding(padding);
    CreateContent(19);
    ViewStackProcessor::GetInstance()->Pop();
    CreateLazyGridLayout();
    CreateContent(19);
    CreateDone();

    /**
     * @tc.steps: step2. Update padding top and bottom.
     * @tc.expected: start and end index updated
     */
    auto pattern0 = GetChildPattern<LazyGridLayoutPattern>(scrollableFrameNode_, 0);
    auto pattern1 = GetChildPattern<LazyGridLayoutPattern>(scrollableFrameNode_, 1);
    FlushUITasks();
    EXPECT_EQ(pattern0->GetHost()->GetGeometryNode()->GetFrameSize().Height(), 1200);
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 7);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0), 0);

    /**
     * @tc.steps: step3. Update refences position
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-520, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 8);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 17);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, -1);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, -1);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 0), -520);

    /**
     * @tc.steps: step4. Update refences position
     * @tc.expected: LazyGrid0 out of view.
     */
    scrollablePattern_->UpdateCurrentOffset(-600, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 19);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 19);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 1), 80);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, 7);

    /**
     * @tc.steps: step5. Update columns template
     * @tc.expected: Display content not change.
     */
    auto layoutProperty0 = pattern0->GetLayoutProperty<LazyGridLayoutProperty>();
    layoutProperty0->UpdateRowGap(Dimension(10));
    FlushUITasks();
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 1290);
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 19);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 19);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 1), 80);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, 7);

    /**
     * @tc.steps: step6. Scroll backward.
     * @tc.expected:  start and end index updated.
     */
    scrollablePattern_->UpdateCurrentOffset(300, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 14);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 18);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 1), 380);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, 1);
}

/**
 * @tc.name: WaterFlowLayoutTest007
 * @tc.desc: Lazy layout in WaterFlow SW mode, update LazyGrid all children height above display area.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, WaterFlowLayoutTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     * @tc.expected: layout visible items and predict items
     */
    CreateWaterFlow(WaterFlowLayoutMode::SLIDING_WINDOW);
    CreateLazyGridLayout();
    CreateContent(19);
    ViewStackProcessor::GetInstance()->Pop();
    CreateLazyGridLayout();
    CreateContent(19);
    CreateDone();
    auto pattern0 = GetChildPattern<LazyGridLayoutPattern>(scrollableFrameNode_, 0);
    auto pattern1 = GetChildPattern<LazyGridLayoutPattern>(scrollableFrameNode_, 1);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 1000);
    /**
     * @tc.steps: step2. Update refences position
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-420, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 8);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 17);
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, -1);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, -1);

    /**
     * @tc.steps: step3. Update refences position, LazyGrid0 out of view.
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-600, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, 9);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 1), -20);

    /**
     * @tc.steps: step3. Update LazyGrid0 lanes and scroll backward.
     * @tc.expected: start and end index updated
     */
    auto frameNode0 = GetChildFrameNode(scrollableFrameNode_, 0);
    for (auto& child : frameNode0->GetChildren()) {
        auto property = AceType::DynamicCast<FrameNode>(child)->GetLayoutProperty();
        property->UpdateUserDefinedIdealSize(CalcSize(CalcLength(SCROLL_WIDTH), CalcLength(200.f)));
    }
    scrollablePattern_->UpdateCurrentOffset(200, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 18);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 18);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 1), 180);
    scrollablePattern_->UpdateCurrentOffset(200, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 16);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 18);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 1), 380);
    scrollablePattern_->UpdateCurrentOffset(200, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 14);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 18);
    EXPECT_EQ(GetChildY(scrollableFrameNode_, 1), 580);
}

/**
 * @tc.name: WaterFlowLayoutTest008
 * @tc.desc: Test LazyGrid child different height
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, WaterFlowLayoutTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     * @tc.expected: layout visible items and predict items
     */
    CreateWaterFlow(WaterFlowLayoutMode::SLIDING_WINDOW);
    CreateLazyGridLayout();
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    float itemHeight[3] = {80, 100, 90};
    for (int32_t i = 0; i < 10; i++) {
        for (int32_t j = 0; j < 3; j++) {
            StackModelNG stackModel;
            stackModel.Create();
            ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
            ViewAbstract::SetHeight(CalcLength(itemHeight[j]));
            ViewStackProcessor::GetInstance()->Pop();
        }
    }
    CreateDone();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1000);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 14);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 20);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 20);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEnd_, 700);

    /**
     * @tc.steps: step2. Update refences position.
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(-420, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 12);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 26);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 29);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStart_, 100);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 29);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEnd_, 1000);
}

/**
 * @tc.name: WaterFlowLayoutTest009
 * @tc.desc: Test LazyGrid child different height, predict backward.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, WaterFlowLayoutTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     * @tc.expected: layout visible items and predict items
     */
    CreateWaterFlow(WaterFlowLayoutMode::SLIDING_WINDOW);
    CreateLazyGridLayout();
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    float itemHeight[3] = {80, 100, 90};
    for (int32_t i = 0; i < 10; i++) {
        for (int32_t j = 0; j < 3; j++) {
            StackModelNG stackModel;
            stackModel.Create();
            ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
            ViewAbstract::SetHeight(CalcLength(itemHeight[j]));
            ViewStackProcessor::GetInstance()->Pop();
        }
    }
    ViewStackProcessor::GetInstance()->Pop();
    CreateLazyGridLayout();
    CreateContent(20);
    CreateDone();
    auto pattern0 = GetChildPattern<LazyGridLayoutPattern>(scrollableFrameNode_, 0);
    auto pattern1 = GetChildPattern<LazyGridLayoutPattern>(scrollableFrameNode_, 1);
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 14);

    scrollablePattern_->ScrollToIndex(1);
    FlushUITasks();
    EXPECT_EQ(pattern1->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern1->layoutInfo_->endIndex_, 9);

    /**
     * @tc.steps: step2. Update refences position.
     * @tc.expected: start and end index updated
     */
    scrollablePattern_->UpdateCurrentOffset(220, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern0->layoutInfo_->startIndex_, 21);
    EXPECT_EQ(pattern0->layoutInfo_->endIndex_, 29);
    FlushIdleTask(pattern0);
    EXPECT_EQ(pattern0->layoutInfo_->cachedStartIndex_, 15);
    EXPECT_EQ(pattern0->layoutInfo_->cachedEndIndex_, 29);
    EXPECT_EQ(pattern0->layoutInfo_->layoutedStartIndex_, 15);
    EXPECT_EQ(pattern0->layoutInfo_->layoutedStart_, 500);
    EXPECT_EQ(pattern0->layoutInfo_->layoutedEndIndex_, 29);
    EXPECT_EQ(pattern0->layoutInfo_->layoutedEnd_, 1000);
}

/**
 * @tc.name: AddDelChildrenTest001
 * @tc.desc: Test add and del children in LazyVGridLayout
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, AddDelChildrenTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateContent(30);
    CreateDone();
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 1500);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 30);

    /**
     * @tc.steps: step2. Remove 10 children
     * @tc.expected: totalMainSize_ and totalItemCount_ index updated
     */
    for (int32_t i = 0; i < 10; i++) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 1000);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 20);

    /**
     * @tc.steps: step3. Add 6 children
     * @tc.expected: totalMainSize_ and totalItemCount_ index updated
     */
    for (int32_t i = 0; i < 6; i++) {
        AddChild();
    }
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 1300);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 26);
}

/**
 * @tc.name: AddDelChildrenTest002
 * @tc.desc: Test add and del all children in LazyVGridLayout
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, AddDelChildrenTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateDone();
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 0);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 0);

    /**
     * @tc.steps: step2. Add 6 children
     * @tc.expected: totalMainSize_ and totalItemCount_ index updated
     */
    for (int32_t i = 0; i < 6; i++) {
        AddChild();
    }
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 300);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 6);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 300);

    /**
     * @tc.steps: step3. Remove 6 children
     * @tc.expected: totalMainSize_ and totalItemCount_ index updated
     */
    for (int32_t i = 0; i < 6; i++) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->totalItemCount_, 0);
    EXPECT_EQ(GetChildHeight(scrollableFrameNode_, 0), 0);
}

/**
 * @tc.name: OnVisibleIndexesChangeTest001
 * @tc.desc: Verify callback fires with initial visible range.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, OnVisibleIndexesChangeTest001, TestSize.Level1)
{
    CreateWaterFlow();
    LazyVGridLayoutModel model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    model.SetColumnsTemplate("1fr 1fr");
    frameNode_ = GetMainFrameNode();
    pattern_ = frameNode_->GetPattern<LazyGridLayoutPattern>();
    pattern_->axis_ = Axis::VERTICAL;
    layoutProperty_ = frameNode_->GetLayoutProperty<LazyGridLayoutProperty>();

    int32_t indexStart = 0;
    int32_t indexEnd = 0;
    auto onVisibleIndexesChangeCallback = [&indexStart, &indexEnd](int32_t start, int32_t end) {
        indexStart = start;
        indexEnd = end;
    };
    model.SetOnVisibleIndexesChange(onVisibleIndexesChangeCallback);

    CreateContent(30);
    CreateDone();

    EXPECT_EQ(indexStart, 0);
    EXPECT_EQ(indexEnd, 9);
}

/**
 * @tc.name: OnVisibleIndexesChangeTest002
 * @tc.desc: Verify callback returns -1,-1 when there are no child items.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, OnVisibleIndexesChangeTest002, TestSize.Level1)
{
    CreateWaterFlow();
    LazyVGridLayoutModel model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    model.SetColumnsTemplate("1fr 1fr");

    int indexStart = 0;
    int indexEnd = 0;
    auto onVisibleIndexesChangeCallback = [&indexStart, &indexEnd](int32_t start, int32_t end) {
        indexStart = start;
        indexEnd = end;
    };
    model.SetOnVisibleIndexesChange(onVisibleIndexesChangeCallback);
    CreateDone();

    EXPECT_EQ(indexStart, -1);
    EXPECT_EQ(indexEnd, -1);
}

/**
 * @tc.name: OnVisibleIndexesChangeTest003
 * @tc.desc: Verify callback returns -1,-1 when LazyGrid becomes fully out of viewport above.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, OnVisibleIndexesChangeTest003, TestSize.Level1)
{
    CreateWaterFlow(WaterFlowLayoutMode::SLIDING_WINDOW);
    LazyVGridLayoutModel model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    model.SetColumnsTemplate("1fr 1fr");

    int indexStart = 0;
    int indexEnd = 0;
    auto onVisibleIndexesChangeCallback = [&indexStart, &indexEnd](int32_t start, int32_t end) {
        indexStart = start;
        indexEnd = end;
    };
    model.SetOnVisibleIndexesChange(onVisibleIndexesChangeCallback);
    CreateContent(19);
    ViewStackProcessor::GetInstance()->Pop();
    CreateLazyGridLayout();
    CreateContent(19);
    CreateDone();

    scrollablePattern_->UpdateCurrentOffset(-420, SCROLL_FROM_UPDATE);
    FlushUITasks();
    scrollablePattern_->UpdateCurrentOffset(-600, SCROLL_FROM_UPDATE);
    FlushUITasks();

    EXPECT_EQ(indexStart, -1);
    EXPECT_EQ(indexEnd, -1);
}

/**
 * @tc.name: IsVerticalScrollableParent001
 * @tc.desc: Verify IsVerticalScrollableParent returns false for null node
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, IsVerticalScrollableParent001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateDone();
    EXPECT_NE(pattern_, nullptr);
    RefPtr<UINode> nullNode = nullptr;
    bool result = LazyLayoutUtils::IsVerticalScrollableParent(nullNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsVerticalScrollableParent002
 * @tc.desc: Verify IsVerticalScrollableParent returns true for vertical WaterFlow
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, IsVerticalScrollableParent002, TestSize.Level1)
{
    CreateWaterFlow();
    CreateLazyGridLayout(Axis::VERTICAL);
    CreateDone();
    EXPECT_NE(pattern_, nullptr);
    bool result = LazyLayoutUtils::IsVerticalScrollableParent(scrollableFrameNode_);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsVerticalScrollableParent003
 * @tc.desc: Verify IsVerticalScrollableParent returns true for vertical List
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, IsVerticalScrollableParent003, TestSize.Level1)
{
    ListModelNG listModel;
    listModel.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    auto listNode = GetMainFrameNode();
    EXPECT_NE(listNode, nullptr);
    auto listPattern = listNode->GetPattern<ListPattern>();
    EXPECT_NE(listPattern, nullptr);
    EXPECT_EQ(listPattern->GetAxis(), Axis::VERTICAL);
    CreateLazyGridLayout(Axis::VERTICAL);
    EXPECT_NE(pattern_, nullptr);
    CreateDone();

    bool result = LazyLayoutUtils::IsVerticalScrollableParent(listNode);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsVerticalScrollableParent004
 * @tc.desc: Verify IsVerticalScrollableParent returns true for vertical Scroll
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, IsVerticalScrollableParent004, TestSize.Level1)
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    auto scrollNode = GetMainFrameNode();
    EXPECT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollablePattern>();
    EXPECT_NE(scrollPattern, nullptr);
    EXPECT_EQ(scrollPattern->GetAxis(), Axis::VERTICAL);
    CreateLazyGridLayout(Axis::VERTICAL);
    EXPECT_NE(pattern_, nullptr);
    CreateDone();

    bool result = LazyLayoutUtils::IsVerticalScrollableParent(scrollNode);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsVerticalScrollableParent005
 * @tc.desc: Verify IsVerticalScrollableParent returns false for non-scrollable container
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, IsVerticalScrollableParent005, TestSize.Level1)
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    auto scrollNode = GetMainFrameNode();
    EXPECT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollablePattern>();
    EXPECT_NE(scrollPattern, nullptr);
    EXPECT_EQ(scrollPattern->GetAxis(), Axis::VERTICAL);
    CreateLazyGridLayout(Axis::VERTICAL);
    EXPECT_NE(pattern_, nullptr);
    CreateDone();

    StackModelNG stackModel;
    stackModel.Create();
    auto stackNode = GetMainFrameNode();
    EXPECT_NE(stackNode, nullptr);
    CreateDone();

    bool result = LazyLayoutUtils::IsVerticalScrollableParent(stackNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: LazyGridInList001
 * @tc.desc: Verify LazyVGrid works in vertical List without abort
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList001, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 10; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(80));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(listFrameNode_, nullptr);
    EXPECT_GE(listFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridInList002
 * @tc.desc: Verify List with LazyVGrid can scroll and offset updates
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList002, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 30; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(80));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();

    EXPECT_NE(listPattern_, nullptr);
    EXPECT_NE(scrollablePattern_, nullptr);

    double initialOffset = scrollablePattern_->GetTotalOffset();
    scrollablePattern_->UpdateCurrentOffset(-200.0f, SCROLL_FROM_UPDATE);
    FlushUITasks(listFrameNode_);
    double offsetAfterScroll = scrollablePattern_->GetTotalOffset();

    EXPECT_NE(initialOffset, offsetAfterScroll);
    EXPECT_GT(offsetAfterScroll, initialOffset);
}

/**
 * @tc.name: LazyGridInList003
 * @tc.desc: Verify LazyVGrid with different columns template in List
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList003, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr 1fr");

    for (int i = 0; i < 15; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(66));
        ViewAbstract::SetHeight(CalcLength(80));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(listFrameNode_, nullptr);
    EXPECT_GE(listFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridInList004
 * @tc.desc: Verify LazyVGrid with gaps in List
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList004, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");
    gridModel.SetRowGap(Dimension(10.0));
    gridModel.SetColumnGap(Dimension(15.0));

    for (int i = 0; i < 15; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(listFrameNode_, nullptr);
}

/**
 * @tc.name: LazyGridInList005
 * @tc.desc: Verify LazyVGrid with repeat(auto-fit) in List
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList005, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("repeat(auto-fit, 80)");

    for (int i = 0; i < 15; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(listFrameNode_, nullptr);
}

/**
 * @tc.name: LazyGridInList006
 * @tc.desc: Verify empty LazyVGrid works in List
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList006, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(listFrameNode_, nullptr);
    EXPECT_GE(listFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridInList007
 * @tc.desc: Verify scroll back to top works in List with LazyVGrid
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList007, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 20; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollablePattern_, nullptr);

    scrollablePattern_->UpdateCurrentOffset(-300.0f, SCROLL_FROM_UPDATE);
    FlushUITasks(listFrameNode_);
    double offsetDown = scrollablePattern_->GetTotalOffset();

    scrollablePattern_->UpdateCurrentOffset(300.0f, SCROLL_FROM_UPDATE);
    FlushUITasks(listFrameNode_);
    double offsetUp = scrollablePattern_->GetTotalOffset();

    EXPECT_GT(offsetDown, 0.0);
    EXPECT_EQ(offsetUp, 0.0);
}

/**
 * @tc.name: LazyGridInList008
 * @tc.desc: Verify multiple LazyVGrid children in List
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList008, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel1;
    gridModel1.Create();
    gridModel1.SetColumnsTemplate("1fr 1fr");
    for (int i = 0; i < 8; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(80));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    LazyVGridLayoutModel gridModel2;
    gridModel2.Create();
    gridModel2.SetColumnsTemplate("1fr 1fr");
    for (int i = 0; i < 10; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(80));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(listFrameNode_, nullptr);
    auto children = listFrameNode_->GetChildren();
    EXPECT_GE(children.size(), 2u);
}

// ==================== LazyVGrid in Scroll Tests ====================

/**
 * @tc.name: LazyGridInScroll001
 * @tc.desc: Verify LazyVGrid works in vertical Scroll without abort
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInScroll001, TestSize.Level1)
{
    CreateScroll();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 10; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridInScroll002
 * @tc.desc: Verify Scroll with LazyVGrid can scroll and offset updates
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInScroll002, TestSize.Level1)
{
    CreateScroll();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 30; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollablePattern_, nullptr);

    double initialOffset = scrollablePattern_->GetTotalOffset();
    scrollablePattern_->UpdateCurrentOffset(-200.0f, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    double offsetAfterScroll = scrollablePattern_->GetTotalOffset();

    EXPECT_NE(initialOffset, offsetAfterScroll);
    EXPECT_GT(offsetAfterScroll, initialOffset);
}

/**
 * @tc.name: LazyGridInScroll003
 * @tc.desc: Verify Scroll with LazyVGrid can scroll back to top
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInScroll003, TestSize.Level1)
{
    CreateScroll();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 20; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollablePattern_, nullptr);

    scrollablePattern_->UpdateCurrentOffset(-250.0f, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    double offsetDown = scrollablePattern_->GetTotalOffset();

    scrollablePattern_->UpdateCurrentOffset(250.0f, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollableFrameNode_);
    double offsetUp = scrollablePattern_->GetTotalOffset();

    EXPECT_GT(offsetDown, 0.0);
    EXPECT_EQ(offsetUp, 0.0);
}

/**
 * @tc.name: LazyGridInScroll005
 * @tc.desc: Verify LazyVGrid with 3 columns in Scroll
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInScroll005, TestSize.Level1)
{
    CreateScroll();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr 1fr");

    for (int i = 0; i < 15; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(66));
        ViewAbstract::SetHeight(CalcLength(80));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridInScroll006
 * @tc.desc: Verify LazyVGrid with columnGap in Scroll
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInScroll006, TestSize.Level1)
{
    CreateScroll();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");
    gridModel.SetColumnGap(Dimension(10.0));

    for (int i = 0; i < 12; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(95));
        ViewAbstract::SetHeight(CalcLength(80));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridInScroll007
 * @tc.desc: Verify LazyVGrid with rowGap and columnGap in Scroll
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInScroll007, TestSize.Level1)
{
    CreateScroll();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr 1fr");
    gridModel.SetRowGap(Dimension(8.0));
    gridModel.SetColumnGap(Dimension(12.0));

    for (int i = 0; i < 18; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(60));
        ViewAbstract::SetHeight(CalcLength(70));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
}

/**
 * @tc.name: LazyGridInScroll008
 * @tc.desc: Verify LazyVGrid with large dataset in Scroll
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInScroll008, TestSize.Level1)
{
    CreateScroll();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 50; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(80));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    auto scrollNode = GetMainFrameNode();
    EXPECT_NE(scrollNode, nullptr);
    CreateDone();
    auto scrollPattern = scrollNode->GetPattern<ScrollablePattern>();
    EXPECT_NE(scrollPattern, nullptr);

    scrollPattern->UpdateCurrentOffset(-400.0f, SCROLL_FROM_UPDATE);
    FlushUITasks(scrollNode);
    double offsetAfterScroll = scrollPattern->GetTotalOffset();

    EXPECT_GT(offsetAfterScroll, 0.0);
}

/**
 * @tc.name: LazyGridInScroll009
 * @tc.desc: Verify LazyVGrid with variable item sizes in Scroll
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInScroll009, TestSize.Level1)
{
    CreateScroll();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 20; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        float height = (i % 3 == 0) ? 120.0f : 80.0f;
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(height));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridInScroll010
 * @tc.desc: Verify Scroll axis verification for LazyVGrid container
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInScroll010, TestSize.Level1)
{
    CreateScroll();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 10; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(90));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollablePattern_, nullptr);
    EXPECT_EQ(scrollablePattern_->GetAxis(), Axis::VERTICAL);
}

/**
 * @tc.name: LazyGridColumnsTemplate001
 * @tc.desc: Verify LazyVGrid with single column template
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridColumnsTemplate001, TestSize.Level1)
{
    CreateWaterFlow();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr");

    for (int i = 0; i < 15; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(200));
        ViewAbstract::SetHeight(CalcLength(60));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridColumnsTemplate003
 * @tc.desc: Verify LazyVGrid with mixed fixed and fr columns
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridColumnsTemplate003, TestSize.Level1)
{
    CreateWaterFlow();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("50px 1fr 50px");

    for (int i = 0; i < 12; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(70));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridGaps001
 * @tc.desc: Verify LazyVGrid with only rowGap
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridGaps001, TestSize.Level1)
{
    CreateWaterFlow();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");
    gridModel.SetRowGap(Dimension(16.0));

    for (int i = 0; i < 15; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(80));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    auto frameNode = GetMainFrameNode();
    CreateDone();
    EXPECT_NE(frameNode, nullptr);
    EXPECT_GE(frameNode->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridGaps003
 * @tc.desc: Verify LazyVGrid with VP dimension gaps
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridGaps003, TestSize.Level1)
{
    CreateWaterFlow();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");
    gridModel.SetRowGap(Dimension(12.0, DimensionUnit::VP));
    gridModel.SetColumnGap(Dimension(8.0, DimensionUnit::VP));

    for (int i = 0; i < 12; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(90));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridItemSize002
 * @tc.desc: Verify LazyVGrid with tall items
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridItemSize002, TestSize.Level1)
{
    CreateWaterFlow();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 12; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(150));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridItemSize004
 * @tc.desc: Verify LazyVGrid with small items
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridItemSize004, TestSize.Level1)
{
    CreateWaterFlow();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");

    for (int i = 0; i < 24; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(50));
        ViewAbstract::SetHeight(CalcLength(50));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridInList009
 * @tc.desc: Verify List axis verification for LazyVGrid container
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList009, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 10; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(90));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(listPattern_, nullptr);
    EXPECT_EQ(scrollablePattern_->GetAxis(), Axis::VERTICAL);
}

/**
 * @tc.name: LazyGridInList010
 * @tc.desc: Verify LazyVGrid with different columnGap in List
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList010, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr 1fr");
    gridModel.SetColumnGap(Dimension(16.0));

    for (int i = 0; i < 15; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(60));
        ViewAbstract::SetHeight(CalcLength(75));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(listFrameNode_, nullptr);
    EXPECT_GE(listFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridInList011
 * @tc.desc: Verify LazyVGrid with only rowGap in List
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList011, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");
    gridModel.SetRowGap(Dimension(20.0));

    for (int i = 0; i < 12; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(85));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(listFrameNode_, nullptr);
}

/**
 * @tc.name: LazyGridInList012
 * @tc.desc: Verify LazyVGrid with large items in List
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList012, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr");

    for (int i = 0; i < 8; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(200));
        ViewAbstract::SetHeight(CalcLength(120));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollablePattern_, nullptr);

    scrollablePattern_->UpdateCurrentOffset(-200.0f, SCROLL_FROM_UPDATE);
    FlushUITasks(listFrameNode_);
    double offset = scrollablePattern_->GetTotalOffset();

    EXPECT_GT(offset, 0.0);
}

/**
 * @tc.name: LazyGridInList013
 * @tc.desc: Verify LazyVGrid with 4 columns in List
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList013, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");

    for (int i = 0; i < 20; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(50));
        ViewAbstract::SetHeight(CalcLength(60));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(listFrameNode_, nullptr);
    EXPECT_GE(listFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridInList014
 * @tc.desc: Verify LazyVGrid with mixed size items in List
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList014, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 16; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        float height = (i % 4 == 0) ? 140.0f : 70.0f;
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(height));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(listFrameNode_, nullptr);
}

/**
 * @tc.name: LazyGridInList015
 * @tc.desc: Verify List with LazyVGrid maintains children hierarchy
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridInList015, TestSize.Level1)
{
    CreateList();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 10; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(80));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(listFrameNode_, nullptr);

    auto children = listFrameNode_->GetChildren();
    EXPECT_GT(children.size(), 0u);

    for (auto& child : children) {
        EXPECT_NE(child, nullptr);
    }
}

/**
 * @tc.name: LazyGridEdgeCase001
 * @tc.desc: Verify LazyVGrid with single item
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridEdgeCase001, TestSize.Level1)
{
    CreateWaterFlow();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    StackModelNG stackModel;
    stackModel.Create();
    ViewAbstract::SetWidth(CalcLength(100));
    ViewAbstract::SetHeight(CalcLength(100));
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridEdgeCase002
 * @tc.desc: Verify LazyVGrid with two items (exactly one row)
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridEdgeCase002, TestSize.Level1)
{
    CreateWaterFlow();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 2; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
}

/**
 * @tc.name: LazyGridEdgeCase003
 * @tc.desc: Verify LazyVGrid with three items (one full row + partial)
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridEdgeCase003, TestSize.Level1)
{
    CreateWaterFlow();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 3; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(90));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridEdgeCase004
 * @tc.desc: Verify LazyVGrid with exactly one full row of 3 columns
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridEdgeCase004, TestSize.Level1)
{
    CreateWaterFlow();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr 1fr");

    for (int i = 0; i < 3; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(66));
        ViewAbstract::SetHeight(CalcLength(66));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
}

/**
 * @tc.name: LazyGridEdgeCase005
 * @tc.desc: Verify LazyVGrid with very small item height
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridEdgeCase005, TestSize.Level1)
{
    CreateWaterFlow();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 20; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(20));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LazyGridEdgeCase006
 * @tc.desc: Verify LazyVGrid with very large item height
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridEdgeCase006, TestSize.Level1)
{
    CreateWaterFlow();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr");

    for (int i = 0; i < 6; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(200));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
}

/**
 * @tc.name: LazyGridEdgeCase007
 * @tc.desc: Verify LazyVGrid with 5 columns template
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridEdgeCase007, TestSize.Level1)
{
    CreateWaterFlow();

    LazyVGridLayoutModel gridModel;
    gridModel.Create();
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");

    for (int i = 0; i < 25; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(40));
        ViewAbstract::SetHeight(CalcLength(40));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();
    EXPECT_NE(scrollableFrameNode_, nullptr);
    EXPECT_GE(scrollableFrameNode_->GetChildren().size(), 1u);
}

/**
 * @tc.name: LayoutPolicyTest001
 * @tc.desc: test the measure result when setting matchParent.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LayoutPolicyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyVGridLayout
     */
    RefPtr<FrameNode> lazyGrid;
    auto column = CreateColumn([this, &lazyGrid](ColumnModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        LazyVGridLayoutModel lazyGridModel;
        lazyGridModel.Create();
        ViewAbstractModelNG model1;
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
        ViewStackProcessor::GetInstance()->PopContainer();
        lazyGrid = AceType::DynamicCast<FrameNode>(element);
    });
    ViewStackProcessor::GetInstance()->Finish();
    ASSERT_NE(column, nullptr);
    ASSERT_EQ(column->GetChildren().size(), 1);
    CreateLayoutTask(column);

    // Expect LazyVGridLayout's width is 500, height is 300 land offset is [0.0, 0.0].
    auto geometryNode = lazyGrid->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
}
/**
 * @tc.name: FirstFrameWindowSeedsWithUnknownBody001
 * @tc.desc: First layout with an already-scrolled viewport (body extent unknown): the forward window must fall back
 *           to measuring from item 0 (no past-the-end clamp), and the backward window seeds the last item at body 0.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, FirstFrameWindowSeedsWithUnknownBody001, TestSize.Level1)
{
    auto info = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    info->totalItemCount_ = 10;
    LazyGridLayoutAlgorithm algorithm(info);
    algorithm.totalItemCount_ = 10;
    algorithm.hadMeasuredItems_ = false; // true first layout
    algorithm.prevBodyMainSize_ = 0.0f;
    algorithm.startPos_ = 200.0f; // viewport already scrolled when this child first measures
    algorithm.endPos_ = 650.0f;

    int32_t index = -2;
    float pos = -1.0f;
    algorithm.GetStartIndexInfo(index, pos);
    EXPECT_EQ(index, 0);
    EXPECT_FLOAT_EQ(pos, 0.0f);

    index = -2;
    pos = -1.0f;
    algorithm.GetEndIndexInfo(index, pos);
    EXPECT_EQ(index, 9);
    EXPECT_FLOAT_EQ(pos, 0.0f);
}
} // namespace OHOS::Ace::NG
