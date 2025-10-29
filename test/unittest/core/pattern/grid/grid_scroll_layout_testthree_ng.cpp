/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "grid_test_ng.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_layout/grid_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_paint_method.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_with_options_layout_algorithm.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"

namespace OHOS::Ace::NG {
class GridScrollLayoutTestThreeNg : public GridTestNg {
public:
    void UpdateLayoutInfo();
    RefPtr<GridPaintMethod> UpdateOverlayModifier();
    RefPtr<GridPaintMethod> UpdateContentModifier();
};

void GridScrollLayoutTestThreeNg::UpdateLayoutInfo()
{
    GetGrid();
    ViewStackProcessor::GetInstance()->Finish();
    FlushUITasks(frameNode_);
    pattern_->info_.lineHeightMap_[0] = ITEM_MAIN_SIZE;
    pattern_->info_.gridMatrix_[0][0] = 0;
    pattern_->info_.gridMatrix_[0][1] = 1;
    pattern_->info_.gridMatrix_[1][0] = 0;
    pattern_->info_.gridMatrix_[1][1] = 1;
}

RefPtr<GridPaintMethod> GridScrollLayoutTestThreeNg::UpdateOverlayModifier()
{
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    RefPtr<GridPaintMethod> paintMethod = AceType::DynamicCast<GridPaintMethod>(paintWrapper->nodePaintImpl_);
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    return paintMethod;
}

RefPtr<GridPaintMethod> GridScrollLayoutTestThreeNg::UpdateContentModifier()
{
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    RefPtr<GridPaintMethod> paintMethod = AceType::DynamicCast<GridPaintMethod>(paintWrapper->nodePaintImpl_);
    paintMethod->UpdateContentModifier(AceType::RawPtr(paintWrapper));
    return paintMethod;
}

/**
 * @tc.name: ScrollLayoutRTL001
 * @tc.desc: Test Vertical Grid with Direction RTL
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, ScrollLayoutRTL001, TestSize.Level1)
{
    float itemWidth = 60.0f;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetIsRTL(TextDirection::RTL);
    CreateFixedItems(18);
    CreateDone();

    int32_t colsNumber = 4;
    for (int32_t index = 0; index < 8; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = WIDTH - index % colsNumber * itemWidth - itemWidth;
        float offsetY = floor(index / colsNumber) * ITEM_MAIN_SIZE;
        RectF expectRect = RectF(offsetX, offsetY, itemWidth, ITEM_MAIN_SIZE);
        EXPECT_TRUE(IsEqual(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: ScrollLayoutRTL002
 * @tc.desc: Test Horizontal Grid with Direction RTL
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, ScrollLayoutRTL002, TestSize.Level1)
{
    float itemWidth = 100.0f;
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetIsRTL(TextDirection::RTL);
    CreateFixedItems(18);
    CreateDone();

    int32_t rowsNumber = 4;
    for (int32_t index = 0; index < 8; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = WIDTH - floor(index / rowsNumber) * itemWidth - itemWidth;
        float offsetY = index % rowsNumber * ITEM_MAIN_SIZE;
        RectF expectRect = RectF(offsetX, offsetY, itemWidth, ITEM_MAIN_SIZE);
        EXPECT_TRUE(IsEqual(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: AdaptToChildMainSize005
 * @tc.desc: Test Vertical Grid with maxcount and 0 itemHeight
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, AdaptToChildMainSize005, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    ViewAbstract::SetHeight(CalcLength(100));
    model.SetMaxCount(1);
    CreateGridItems(1, 0, 0);
    CreateDone();
    EXPECT_EQ(pattern_->GetGridLayoutInfo().lastMainSize_, 100);
}

/*
 * @tc.name: GetResetMode001
 * @tc.desc: Test Reset Function when have bigItem
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, GetResetMode001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(40);
    CreateDone();

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<GridScrollLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto* wrapper = AceType::RawPtr(frameNode_);
    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, -1), std::make_pair(false, false));
    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, 1), std::make_pair(true, false));

    pattern_->ScrollToIndex(30, false, ScrollAlign::START);
    layoutAlgorithm->info_.startIndex_ = 30;
    frameNode_->childrenUpdatedFrom_ = 20;
    FlushUITasks();

    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, 0), std::make_pair(true, false));
    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, 10), std::make_pair(true, false));
    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, 25), std::make_pair(true, false));

    layoutAlgorithm->info_.hasBigItem_ = true;

    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, 0), std::make_pair(true, false));
    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, 10), std::make_pair(true, false));
    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, 25), std::make_pair(false, true));
}

/**
 * @tc.name: LayoutWithAutoStretch002
 * @tc.desc: Test Vertical Grid Layout with auto-stretch
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, LayoutWithAutoStretch002, TestSize.Level1)
{
    float itemWidth = 40.0f;
    float itemHeight = 75.0f;
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("repeat(auto-stretch, 75)");
    model.SetRowsGap(Dimension(5));
    model.SetColumnsGap(Dimension(5));
    CreateGridItems(25, itemWidth, itemHeight);
    CreateDone();

    int32_t rowsNumber = 5;
    int32_t columnsNumber = 5;
    float realColumnsGap = 5.f;
    float realRowsGap = 6.25f;
    for (int32_t index = 0; index < 25; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = index / columnsNumber * (itemWidth + realColumnsGap);
        float offsetY = index % rowsNumber * (itemHeight + realRowsGap);
        RectF expectRect = RectF(offsetX, offsetY, itemWidth, itemHeight);
        EXPECT_TRUE(IsEqual(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: LayoutWithAutoStretch003
 * @tc.desc: Test Horizental Grid Layout with auto-stretch
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, LayoutWithAutoStretch003, TestSize.Level1)
{
    float itemWidth = 40.0f;
    float itemHeight = 75.0f;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("repeat(auto-stretch, 40)");
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    CreateGridItems(25, itemWidth, itemHeight);
    CreateDone();

    int32_t rowsNumber = 5;
    int32_t columnsNumber = 5;
    float realColumnsGap = 10.f;
    float realRowsGap = 10.f;
    for (int32_t index = 0; index < 25; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = index % columnsNumber * (itemWidth + realColumnsGap);
        float offsetY = index / rowsNumber * (itemHeight + realRowsGap);
        RectF expectRect = RectF(offsetX, offsetY, itemWidth, itemHeight);
        EXPECT_TRUE(IsEqual(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: Stretch001
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, Stretch001, TestSize.Level1)
{
    /**
     * 0: [0], [1]
     *
     * 1 will stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetColumnsTemplate("1fr 1fr");

    CreateFixedHeightItems(1, 150);
    CreateAdaptChildSizeGridItems(1);

    CreateDone();
    FlushUITasks();

    auto childRect0 = pattern_->GetItemRect(0);
    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect0.Height(), childRect1.Height());
}

/**
 * @tc.name: Stretch002
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, Stretch002, TestSize.Level1)
{
    /**
     * 0: [0], [1]
     * 1: [0]
     *
     * 1 will not stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetColumnsTemplate("1fr 1fr");

    CreateBigItem(0, 1, 0, 0, ITEM_MAIN_SIZE, 200);
    CreateAdaptChildSizeGridItems(1);

    CreateDone();
    FlushUITasks();

    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect1.Height(), 0);
}

/**
 * @tc.name: Stretch003
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, Stretch003, TestSize.Level1)
{
    /**
     * 0: [0], [1]
     * 1: [0], [2]
     * 2: [3], [4]
     *
     * 1 and 2 will not stretch
     * 3 will stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetColumnsTemplate("1fr 1fr");

    CreateBigItem(0, 1, 0, 0, ITEM_MAIN_SIZE, 200);
    CreateAdaptChildSizeGridItems(3);
    CreateFixedHeightItems(1, 150);

    CreateDone();
    FlushUITasks();

    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect1.Height(), 0);

    auto childRect3 = pattern_->GetItemRect(3);
    auto childRect4 = pattern_->GetItemRect(4);
    EXPECT_EQ(childRect4.Height(), childRect3.Height());
}

/**
 * @tc.name: Stretch004
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, Stretch004, TestSize.Level1)
{
    /**
     * 0: [0], [0], [1]
     *
     * 1 will not stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetColumnsTemplate("1fr 1fr 1fr");

    CreateBigItem(0, 1, 0, 1, ITEM_MAIN_SIZE, 200);
    CreateAdaptChildSizeGridItems(1);

    CreateDone();
    FlushUITasks();

    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect1.Height(), 0);
    auto childRect2 = pattern_->GetItemRect(2);
    EXPECT_EQ(childRect2.Height(), 0);
}

/**
 * @tc.name: Stretch005
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, Stretch005, TestSize.Level1)
{
    /**
     *  0
     * [0]
     * [1]
     *
     * 1 will stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetRowsTemplate("1fr 1fr");

    CreateFixedHeightItems(1, 150);
    CreateAdaptChildSizeGridItems(1);

    CreateDone();
    FlushUITasks();

    auto childRect0 = pattern_->GetItemRect(0);
    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect0.Width(), childRect1.Width());
}

/**
 * @tc.name: Stretch006
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, Stretch006, TestSize.Level1)
{
    /**
     *  0
     * [0]
     * [0]
     * [1]
     *
     * 1 will not stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetRowsTemplate("1fr 1fr 1fr");

    CreateBigItem(0, 1, 0, 0, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateAdaptChildSizeGridItems(1);

    CreateDone();
    FlushUITasks();

    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect1.Width(), 0);
}

/**
 * @tc.name: Stretch007
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, Stretch007, TestSize.Level1)
{
    /**
     *  0    1    2
     * [0], [0], [3]
     * [1], [2], [4]
     *
     * 1 and 2 will not stretch
     * 3 will stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetRowsTemplate("1fr 1fr");

    CreateBigItem(0, 0, 0, 1, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateAdaptChildSizeGridItems(3);
    CreateFixedHeightItems(1, 150);

    CreateDone();
    FlushUITasks();

    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect1.Width(), 0);

    auto childRect3 = pattern_->GetItemRect(3);
    auto childRect4 = pattern_->GetItemRect(4);
    EXPECT_EQ(childRect4.Width(), childRect3.Width());
}

/**
 * @tc.name: Stretch008
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, Stretch008, TestSize.Level1)
{
    /**
     *  0    1
     * [0], [0]
     * [0], [0]
     * [1], [2]
     *
     * 1 and 2 will not stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetRowsTemplate("1fr 1fr 1fr");

    CreateBigItem(0, 1, 0, 1, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateAdaptChildSizeGridItems(2);

    CreateDone();
    FlushUITasks();

    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect1.Width(), 0);
    auto childRect2 = pattern_->GetItemRect(2);
    EXPECT_EQ(childRect2.Width(), 0);
}

/**
 * @tc.name: MarginPadding001
 * @tc.desc: Test margin/padding
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, MarginPadding001, TestSize.Level1)
{
    ColumnModelNG colModel;
    colModel.Create(Dimension(0), nullptr, "");
    auto colNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(4);
    CreateDone();

    MarginProperty margin = { CalcLength(1), CalcLength(3), CalcLength(5), CalcLength(7) };
    PaddingProperty padding = { CalcLength(2), CalcLength(4), CalcLength(6), CalcLength(8) };
    layoutProperty_->UpdateMargin(margin);
    layoutProperty_->UpdatePadding(padding);
    auto itemLayoutProperty = GetChildLayoutProperty<GridItemLayoutProperty>(frameNode_, 2);
    itemLayoutProperty->UpdateMargin(margin);
    itemLayoutProperty->UpdatePadding(padding);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameRect(), RectF(1, 5, 240, 400)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 2), RectF(3, 111, 113, 100)));
}

/**
 * @tc.name: SetEffectEdge001
 * @tc.desc: Test SetEffectEdge
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, SetEffectEdge001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::START);
    CreateFixedItems(3);
    CreateDone();
    EXPECT_EQ(pattern_->GetEffectEdge(), EffectEdge::START);

    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    UpdateCurrentOffset(-100);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0);

    UpdateCurrentOffset(200);
    ASSERT_TRUE(Positive(GetChildY(frameNode_, 0)));
}

/**
 * @tc.name: SetEffectEdge002
 * @tc.desc: Test SetEffectEdge
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, SetEffectEdge002, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::END);
    CreateFixedItems(3);
    CreateDone();
    EXPECT_EQ(pattern_->GetEffectEdge(), EffectEdge::END);

    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    UpdateCurrentOffset(100);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0);

    UpdateCurrentOffset(-200);
    
    EXPECT_LE(GetChildY(frameNode_, 0), 0);
}

/**
 * @tc.name: SpringAnimationTest001
 * @tc.desc: Test Grid change height during spring animation. GridItem is not fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, SpringAnimationTest001, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(3);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(-1200.f);
    info.SetMainDelta(-200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -57.300961);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and increase grid height during animation
     * @tc.expected: currentOffset will not change with the grid height
     */

    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT + 50))));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -28.650482);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_NEAR(0, pattern_->info_.currentOffset_, 0.1);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: SpringAnimationTest002
 * @tc.desc: Test Grid change height during spring animation. GridItem is not fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, SpringAnimationTest002, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(3);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(-1200.f);
    info.SetMainDelta(-200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -57.300961);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease grid height during animation
     * @tc.expected: currentOffset will not change with the grid height
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT - 50))));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -28.650482);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_NEAR(0, pattern_->info_.currentOffset_, 0.1);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: SpringAnimationTest003
 * @tc.desc: Test Grid change height during spring animation. GridItem is not fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, SpringAnimationTest003, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(3);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(1200.f);
    info.SetMainDelta(200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 216.41699);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and increase grid height during animation
     * @tc.expected: currentOffset will not change with the grid height
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT + 50))));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 108.2085);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: SpringAnimationTest004
 * @tc.desc: Test Grid change height during spring animation. GridItem is not fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, SpringAnimationTest004, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(3);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(1200.f);
    info.SetMainDelta(200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 216.41699);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease grid height during animation
     * @tc.expected: currentOffset will not change with the grid height
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT - 50))));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 108.2085);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: SpringAnimationTest005
 * @tc.desc: Test Grid change height during spring animation. GridItem is fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, SpringAnimationTest005, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateFixedItems(21);
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(-1200.f);
    info.SetMainDelta(-200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -16.417);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease grid height during animation
     * @tc.expected: currentOffset will change with the grid height
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT + 50))));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -58.208496);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -50);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -50);
}

/**
 * @tc.name: SpringAnimationTest006
 * @tc.desc: Test Grid change height during spring animation. GridItem is fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, SpringAnimationTest006, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(20);
    CreateDone();
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(-200.f);
    info.SetMainDelta(-200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -16.417);
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease grid height during animation
     * @tc.expected: currentOffset will change with the grid height
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT - 50))));
    FlushUITasks();
    // the value of (currentOffset + gridMainSizeDelta) is greater than lineHeight(200), so move to next line
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -58.208504);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -50);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -50);
}

/**
 * @tc.name: SpringAnimationTest007
 * @tc.desc: Test Grid change height during spring animation. GridItem is fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, SpringAnimationTest007, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(40);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(1400.f);
    info.SetMainDelta(200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 216.41699);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease grid height during animation
     * @tc.expected: currentOffset will not change with the grid height
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT + 50))));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 108.2085);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: SpringAnimationTest008
 * @tc.desc: Test Grid change height during spring animation. GridItem is not fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestThreeNg, SpringAnimationTest008, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(40);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(1400.f);
    info.SetMainDelta(200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 216.41699);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease grid height during animation
     * @tc.expected: currentOffset will not change with the grid height
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT - 50))));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 108.2085);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
}
} // namespace OHOS::Ace::NG