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

#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"

namespace OHOS::Ace::NG {

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
    auto frameNode = GetMainFrameNode();
    scrollablePattern_ = frameNode->GetPattern<ScrollablePattern>();
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
 * @tc.desc: Lazy layout in WaterFlow
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
} // namespace OHOS::Ace::NG
