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
} // namespace OHOS::Ace::NG
