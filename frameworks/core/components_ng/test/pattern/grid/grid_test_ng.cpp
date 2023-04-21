/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <map>
#include <memory>

#include "gtest/gtest.h"

#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/utils/utils.h"
#define private public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/button_view.h"
#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

#define protected public
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float DEVICE_WIDTH = 720.0f;
constexpr float DEVICE_HEIGHT = 1136.0f;
constexpr float PREV_OFFSET_FIRST = 1.0f;
constexpr float PREV_OFFSET_SECOND = 2.0f;
constexpr float CURRENT_OFFSET_FIRST = 2.0f;
constexpr float CURRENT_OFFSET_SECOND = 1.0f;
constexpr int32_t START_INDEX = 1;
constexpr int32_t START_MAIN_LINE_INDEX = 0;
constexpr int32_t END_INDEX = -100;
constexpr int32_t START_INDEX_END = -100;
constexpr int32_t CHILDREN_COUNT = 100;
constexpr int32_t ALGORITHM_RELATE_LALUE_FIRST = 2;
constexpr int32_t ALGORITHM_RELATE_LALUE_SECOND = 0;
const SizeF CONTAINER_SIZE(DEVICE_WIDTH, DEVICE_HEIGHT);
const Dimension GRID_ROWS_GAP = Dimension(5, DimensionUnit::PX);
const std::string SCROLL_BAR_COLOR = "#909090";
constexpr float DEFAULT_ROOT_WIDTH = 720.f;
constexpr float DEFAULT_ROOT_HEIGHT = 1136.f;
constexpr float DEFAULT_ITEM_MAIN_LENGTH = 100.f;
} // namespace

class GridTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetGridInstance();
    static void SetWidth(const Dimension& width);
    static void SetHeight(const Dimension& height);
    void CreateGridItem(int32_t number);
    void CreateGridItemWithButton(int32_t number);
    void CreateHorizontalGridItemWithButton(int32_t number);
    void RunMeasureAndLayout();
    RefPtr<FrameNode> GetItemFrameNode(int32_t index);
    RefPtr<GridItemPattern> GetItemPattern(int32_t index);
    RefPtr<FocusHub> GetItemFocusHub(int32_t index);

    RefPtr<FrameNode> frameNode_;
    RefPtr<GridPattern> pattern_;
    RefPtr<GridEventHub> eventHub_;
    RefPtr<GridLayoutProperty> layoutProperty_;
    RefPtr<GridAccessibilityProperty> accessibility_;
};

void GridTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
}

void GridTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

void GridTestNg::SetUp() {}

void GridTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibility_ = nullptr;
}

void GridTestNg::GetGridInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<GridPattern>();
    eventHub_ = frameNode_->GetEventHub<GridEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<GridLayoutProperty>();
    accessibility_ = frameNode_->GetAccessibilityProperty<GridAccessibilityProperty>();
}

void GridTestNg::SetWidth(const Dimension& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), std::nullopt));
}

void GridTestNg::SetHeight(const Dimension& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(height)));
}

void GridTestNg::CreateGridItem(int32_t number)
{
    for (int32_t i = 0; i < number; i++) {
        GridItemModelNG gridItemModel;
        gridItemModel.Create();
        SetHeight(Dimension(DEFAULT_ITEM_MAIN_LENGTH));
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void GridTestNg::CreateGridItemWithButton(int32_t number)
{
    for (int32_t i = 0; i < number; i++) {
        GridItemModelNG gridItemModel;
        gridItemModel.Create();
        SetHeight(Dimension(DEFAULT_ITEM_MAIN_LENGTH));
        {
            ButtonView::Create("Button");
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void GridTestNg::CreateHorizontalGridItemWithButton(int32_t number)
{
    for (int32_t i = 0; i < number; i++) {
        GridItemModelNG gridItemModel;
        gridItemModel.Create();
        SetWidth(Dimension(DEFAULT_ITEM_MAIN_LENGTH));
        SetHeight(Dimension(DEFAULT_ITEM_MAIN_LENGTH));
        {
            ButtonView::Create("Button");
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void GridTestNg::RunMeasureAndLayout()
{
    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
}

RefPtr<FrameNode> GridTestNg::GetItemFrameNode(int32_t index)
{
    auto item = frameNode_->GetChildAtIndex(index);
    return AceType::DynamicCast<FrameNode>(item);
}

RefPtr<GridItemPattern> GridTestNg::GetItemPattern(int32_t index)
{
    auto item = frameNode_->GetChildAtIndex(index);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    return itemFrameNode->GetPattern<GridItemPattern>();
}

RefPtr<FocusHub> GridTestNg::GetItemFocusHub(int32_t index)
{
    auto item = frameNode_->GetChildAtIndex(index);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    return itemFrameNode->GetOrCreateFocusHub();
}

/**
 * @tc.name: GridTest001
 * @tc.desc: Fill all items to grid with fixed row and column
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr 1fr");
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr");
    CreateGridItem(9);
    GetGridInstance();

    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();

    /**
     * @tc.steps: step1. When setting fixed rows and columns, check the status of child nodes in the grid.
     * @tc.expected: All child nodes are active.
     */
    for (int32_t i = 0; i < 9; ++i) {
        EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: GridTest002
 * @tc.desc: Set fixed columns only Fill all items in the grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr");
    gridModelNG.SetColumnsGap(Dimension(10));
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(10);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Set different KeyEvent to verify the OnKeyEvent function.
     * @tc.expected: Check whether the return value is correct.
     */
    KeyEvent event;
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_PAGE_DOWN;
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
    event.code = KeyCode::KEY_PAGE_UP;
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
    EXPECT_FALSE(pattern_->HandleDirectionKey(event.code));
    EXPECT_TRUE(pattern_->HandleDirectionKey(KeyCode::KEY_DPAD_UP));
    EXPECT_TRUE(pattern_->HandleDirectionKey(KeyCode::KEY_DPAD_DOWN));
}

/**
 * @tc.name: GridTest003
 * @tc.desc: Set fixed rows only Fill all items in the grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest003, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(Dimension(5));
    gridModelNG.SetScrollBarColor("#909090");
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(10);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.expected: step1. Check whether the updated properties and parameters are correct.
     */
    EXPECT_TRUE(pattern_->multiSelectable_);
    EXPECT_TRUE(pattern_->isMouseEventInit_);
    EXPECT_TRUE(pattern_->isConfigScrollable_);

    /**
     * @tc.steps: step2. Change MultiSelectable and Call OnModifyDone  function.
     * @tc.expected: Check whether the updated properties and parameters are correct.
     */
    pattern_->SetMultiSelectable(false);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->multiSelectable_);
    EXPECT_FALSE(pattern_->isMouseEventInit_);

    /**
     * @tc.steps: step3. Call the AddScrollEvent function to add a scroll position callback event.
     * @tc.expected: Call and check the return value of the callback function.
     */
    pattern_->AddScrollEvent();
    ASSERT_NE(pattern_->scrollableEvent_, nullptr);
    auto callback = pattern_->scrollableEvent_->GetScrollPositionCallback();
    ASSERT_NE(callback, nullptr);
    auto ret = callback(1.f, SCROLL_FROM_START);
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step4. When isConfigScrollable_ is false, call related functions.
     * @tc.expected: Check the return value of the related function.
     */
    pattern_->isConfigScrollable_ = false;
    EXPECT_EQ(pattern_->AnimateTo(100.f, 200.f, Curves::LINEAR), false);
    EXPECT_EQ(pattern_->UpdateCurrentOffset(1.f, SCROLL_FROM_UPDATE), true);
    EXPECT_EQ(pattern_->UpdateStartIndex(1.0), false);

    /**
     * @tc.steps: step8. When isConfigScrollable_ is true, call AnimateTo functions.
     * @tc.expected: step8. Check the return value and related parameters.
     */
    pattern_->ScrollPage(false);
    pattern_->isConfigScrollable_ = true;
    EXPECT_EQ(pattern_->AnimateTo(100.f, 200.f, Curves::LINEAR), true);
    ASSERT_NE(pattern_->animator_, nullptr);

    /**
     * @tc.steps: step9. Call AnimateTo functions again.
     * @tc.expected: step9. Check the return value and related parameters.
     */
    pattern_->animator_->status_ = Animator::Status::STOPPED;
    EXPECT_EQ(pattern_->AnimateTo(100.f, 200.f, Curves::LINEAR), true);
    ASSERT_NE(pattern_->animator_, nullptr);

    /**
     * @tc.steps: step10. When offsetEnd_ and reachStart_ are true, call OnScrollCallback functions.
     * @tc.expected: step10. Check whether the return value is correct.
     */
    pattern_->gridLayoutInfo_.offsetEnd_ = true;
    pattern_->gridLayoutInfo_.reachStart_ = true;
    EXPECT_EQ(pattern_->OnScrollCallback(0.0f, SCROLL_FROM_ANIMATION), true);
    EXPECT_EQ(pattern_->OnScrollCallback(1.f, SCROLL_FROM_ANIMATION), false);
    EXPECT_EQ(pattern_->gridLayoutInfo_.offsetEnd_, true);
    EXPECT_EQ(pattern_->OnScrollCallback(-1.0f, SCROLL_FROM_ANIMATION), false);
    EXPECT_EQ(pattern_->gridLayoutInfo_.reachStart_, true);
}

/**
 * @tc.name: GridTest004
 * @tc.desc: When fixed rows and columns are not set and direction is row, all items in the grid are filled.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest004, TestSize.Level1)
{
    GridModelNG gridModelNG;
    RefPtr<ScrollControllerBase> positionController = gridModelNG.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModelNG.CreateScrollBarProxy();
    gridModelNG.Create(positionController, scrollBarProxy);
    gridModelNG.SetColumnsGap(Dimension(10));
    gridModelNG.SetRowsGap(Dimension(5));
    gridModelNG.SetLayoutDirection(FlexDirection::ROW);
    gridModelNG.SetMaxCount(10);
    gridModelNG.SetMinCount(1);
    gridModelNG.SetCellLength(200);
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(10);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get grid layout properties.
     * @tc.expected: Check whether the updated properties is correct.
     */
    EXPECT_EQ(layoutProperty_->GetGridDirectionStr(), "GridDirection.Row");

    /**
     * @tc.steps: step2. Get the pattern_ to call the related functions in the positionController.
     */
    ASSERT_NE(pattern_->positionController_, nullptr);

    /**
     * @tc.steps: step3. When Axis is VERTICAL and ScrollEdgeType is SCROLL_TOP, call the related functions in
     * positionController.
     * @tc.expected: Check whether the return value is correct.
     */
    pattern_->gridLayoutInfo_.axis_ = Axis::VERTICAL;
    ScrollEdgeType scrollEdgeType = ScrollEdgeType::SCROLL_TOP;
    pattern_->positionController_->ScrollToEdge(scrollEdgeType, true);
    pattern_->positionController_->ScrollPage(true, true);
    auto axis = pattern_->positionController_->GetScrollDirection();
    EXPECT_EQ(axis, Axis::VERTICAL);

    /**
     * @tc.steps: step4. When Axis is HORIZONTAL and ScrollEdgeType is SCROLL_RIGHT, call the related functions in
     * positionController.
     * @tc.expected: Check whether the return value is correct.
     */
    pattern_->gridLayoutInfo_.axis_ = Axis::HORIZONTAL;
    scrollEdgeType = ScrollEdgeType::SCROLL_RIGHT;
    pattern_->positionController_->ScrollToEdge(scrollEdgeType, true);
    pattern_->positionController_->ScrollPage(true, true);
    axis = pattern_->positionController_->GetScrollDirection();
    EXPECT_EQ(axis, Axis::HORIZONTAL);

    /**
     * @tc.steps: step5. When Axis is NONE, call the related functions in positionController.
     * @tc.expected: Check whether the return value is correct.
     */
    pattern_->gridLayoutInfo_.axis_ = Axis::NONE;
    auto offset = pattern_->positionController_->GetCurrentOffset();
    EXPECT_EQ(offset, Offset::Zero());
}

/**
 * @tc.name: GridTest005
 * @tc.desc: When fixed rows and columns are not set and direction is RowReverse, all items in the grid are filled.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest005, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsGap(Dimension(10));
    gridModelNG.SetRowsGap(Dimension(5));
    gridModelNG.SetLayoutDirection(FlexDirection::ROW_REVERSE);
    gridModelNG.SetMaxCount(10);
    gridModelNG.SetMinCount(1);
    gridModelNG.SetCellLength(200);
    gridModelNG.SetScrollBarMode(static_cast<int32_t>(NG::DisplayMode::AUTO));
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(10);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get grid layout properties.
     * @tc.expected: Check whether the updated properties is correct.
     */
    EXPECT_EQ(layoutProperty_->GetGridDirectionStr(), "GridDirection.RowReverse");
}

/**
 * @tc.name: GridTest006
 * @tc.desc: When fixed rows and columns are not set and direction is Column, all items in the grid are filled.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest006, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsGap(Dimension(10));
    gridModelNG.SetRowsGap(Dimension(5));
    gridModelNG.SetLayoutDirection(FlexDirection::COLUMN);
    gridModelNG.SetMaxCount(10);
    gridModelNG.SetMinCount(1);
    gridModelNG.SetCellLength(200);
    gridModelNG.SetScrollBarMode(static_cast<int32_t>(NG::DisplayMode::ON));
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(10);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get grid layout properties.
     * @tc.expected: Check whether the updated properties is correct.
     */
    EXPECT_EQ(layoutProperty_->GetGridDirectionStr(), "GridDirection.Column");
}

/**
 * @tc.name: GridTest007
 * @tc.desc: When fixed rows and columns are not set and direction is ColumnReverse, all items in the grid are filled.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest007, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsGap(Dimension(10));
    gridModelNG.SetRowsGap(Dimension(5));
    gridModelNG.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
    gridModelNG.SetMaxCount(10);
    gridModelNG.SetMinCount(1);
    gridModelNG.SetCellLength(200);
    gridModelNG.SetScrollBarMode(static_cast<int32_t>(NG::DisplayMode::OFF));
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(10);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get grid layout properties.
     * @tc.expected: Check whether the updated properties is correct.
     */
    EXPECT_EQ(layoutProperty_->GetGridDirectionStr(), "GridDirection.ColumnReverse");

    /**
     * @tc.steps: step2. Get grid EventHub to call related function.
     * @tc.expected: Check whether the related parameters is correct.
     */
    GestureEvent info;
    info.globalPoint_.SetX(1.0f);
    info.globalPoint_.SetY(1.0f);
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
    eventHub_->HandleOnItemDragUpdate(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
    eventHub_->HandleOnItemDragEnd(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
    eventHub_->HandleOnItemDragCancel();
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
}

RefPtr<FrameNode> TestScrollGrid(OptionalSizeF gridSize, double gridItemHeight, int32_t gridItemFrom,
    int32_t gridItemTo, float scrollOffset = 0.0f, int32_t totalItemCount = 9)
{
    /**
     * @tc.steps: step1. Create grid node and initialize width, height, properties.
     */
    GridModelNG grid;
    RefPtr<V2::GridPositionController> positionController;
    RefPtr<ScrollProxy> scrollBarProxy = grid.CreateScrollBarProxy();
    grid.Create(positionController, scrollBarProxy);
    grid.SetColumnsTemplate("1fr 1fr 1fr");

    /**
     * @tc.steps: step2. Create the child nodes gridItem of the grid.
     */
    GridItemModelNG gridItem;
    for (int32_t i = 0; i < totalItemCount; ++i) {
        gridItem.Create();
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_RETURN(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty();
        CHECK_NULL_RETURN(layoutProperty, frameNode);
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, NG::CalcLength(Dimension(gridItemHeight))));
        ViewStackProcessor::GetInstance()->Pop();
    }

    /**
     * @tc.steps: step3. Get grid frameNode and set layoutConstraint.
     * @tc.expected: step3. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.UpdateIllegalSelfIdealSizeWithCheck(gridSize);

    /**
     * @tc.steps: step4. Call the measure and layout function of grid to calculate the size and layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();

    // scroll
    if (!NearZero(scrollOffset)) {
        auto gridPattern = frameNode->GetPattern<GridPattern>();
        EXPECT_FALSE(gridPattern == nullptr);
        gridPattern->UpdateCurrentOffset(scrollOffset, SCROLL_FROM_UPDATE);
        layoutWrapper = frameNode->CreateLayoutWrapper();
        LayoutConstraintF constraint;
        constraint.UpdateIllegalSelfIdealSizeWithCheck(gridSize);
        layoutWrapper->Measure(constraint);
        layoutWrapper->Layout();

        // save current grid info to grid pattern for next operation
        DirtySwapConfig config { false, false, false, false };
        auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
        CHECK_NULL_RETURN(layoutAlgorithmWrapper, frameNode);
        config.skipMeasure = layoutAlgorithmWrapper->SkipMeasure() || layoutWrapper->SkipMeasureContent();
        config.skipLayout = layoutAlgorithmWrapper->SkipLayout();
        gridPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    }
    /**
     * @tc.steps: step5. When setting fixed rows and columns, check the status of child nodes in the grid.
     * @tc.expected: step3. All child nodes are active.
     */
    for (int32_t i = gridItemFrom; i < gridItemTo; ++i) {
        EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }

    return frameNode;
}

/**
 * @tc.name: GridTest008
 * @tc.desc: grid with fixed column
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest008, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 900.0f);
    const int32_t itemCount = 9;
    constexpr double gridItemHeight = 300.0f;
    TestScrollGrid(gridSize, gridItemHeight, 0, itemCount);
}

/**
 * @tc.name: GridTest009
 * @tc.desc: grid with fixed column, some griditem not show
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest009, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t itemCount = 6;
    constexpr double gridItemHeight = 300.0f;
    TestScrollGrid(gridSize, gridItemHeight, 0, itemCount);
}

/**
 * @tc.name: GridTest010
 * @tc.desc: grid with fixed column, some griditem not fully show
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest010, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 800.0f);
    const int32_t itemCount = 9;
    constexpr double gridItemHeight = 300.0f;
    TestScrollGrid(gridSize, gridItemHeight, 0, itemCount);
}

/**
 * @tc.name: GridTest011
 * @tc.desc: grid with fixed column, scroll to show one more line
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest011, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t itemCount = 9;
    constexpr double gridItemHeight = 300.0f;
    TestScrollGrid(gridSize, gridItemHeight, 0, itemCount, -100.0f);
}

/**
 * @tc.name: GridTest012
 * @tc.desc: grid with fixed column, scroll to end
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest012, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t itemCount = 9;
    constexpr double gridItemHeight = 300.0f;
    TestScrollGrid(gridSize, gridItemHeight, 3, itemCount, -300.0f);
}

/**
 * @tc.name: GridTest013
 * @tc.desc: grid with fixed column, scroll to index not fully showed at last line
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest013, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t itemCount = 9;
    constexpr double gridItemHeight = 300.0f;
    auto frameNode = TestScrollGrid(gridSize, gridItemHeight, 0, itemCount, -100.0f);
    ASSERT_NE(frameNode, nullptr);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    gridPattern->UpdateStartIndex(8);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.UpdateIllegalSelfIdealSizeWithCheck(gridSize);
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    for (int32_t i = 0; i < 3; ++i) {
        EXPECT_FALSE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: GridTest014
 * @tc.desc: grid with fixed column, scroll to index not fully showed at first line
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest014, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t itemCount = 9;
    constexpr double gridItemHeight = 300.0f;
    auto frameNode = TestScrollGrid(gridSize, gridItemHeight, 0, itemCount, -100.0f);
    ASSERT_NE(frameNode, nullptr);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    gridPattern->UpdateStartIndex(1);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.UpdateIllegalSelfIdealSizeWithCheck(gridSize);
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    for (int32_t i = 6; i < itemCount; ++i) {
        EXPECT_FALSE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: GridTest015
 * @tc.desc: grid with fixed column, scroll to index fully showed
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest015, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t itemCount = 9;
    constexpr double gridItemHeight = 300.0f;
    auto frameNode = TestScrollGrid(gridSize, gridItemHeight, 0, itemCount, -100.0f);
    ASSERT_NE(frameNode, nullptr);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    gridPattern->UpdateStartIndex(3);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.UpdateIllegalSelfIdealSizeWithCheck(gridSize);
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    for (int32_t i = 0; i < itemCount; ++i) {
        EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: GridTest016
 * @tc.desc: grid with fixed column, scroll to index not fully showed at last line
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest016, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t itemCount = 9;
    constexpr double gridItemHeight = 300.0f;
    auto frameNode = TestScrollGrid(gridSize, gridItemHeight, 0, itemCount, -100.0f, 10);
    ASSERT_NE(frameNode, nullptr);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    gridPattern->UpdateStartIndex(8);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.UpdateIllegalSelfIdealSizeWithCheck(gridSize);
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_FALSE(layoutWrapper->GetOrCreateChildByIndex(9, false)->IsActive());
}

/**
 * @tc.name: GridTest017
 * @tc.desc: grid with fixed column, scroll to index out of view
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest017, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t itemCount = 9;
    constexpr double gridItemHeight = 300.0f;
    // scroll to show index 0-8
    auto frameNode = TestScrollGrid(gridSize, gridItemHeight, 0, itemCount, -100.0f, 10);

    // scroll to index 9
    ASSERT_NE(frameNode, nullptr);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    gridPattern->UpdateStartIndex(9);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.UpdateIllegalSelfIdealSizeWithCheck(gridSize);
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(9, false)->IsActive());
    EXPECT_FALSE(layoutWrapper->GetOrCreateChildByIndex(0, false)->IsActive());

    // save current grid info to grid pattern_ for next operation
    DirtySwapConfig config { false, false, false, false };
    auto layoutAlgorithmWrapper = layoutWrapper->GetLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    config.skipMeasure = layoutAlgorithmWrapper->SkipMeasure() || layoutWrapper->SkipMeasureContent();
    config.skipLayout = layoutAlgorithmWrapper->SkipLayout();
    gridPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);

    // scroll to index 0
    gridPattern->UpdateStartIndex(0);
    layoutWrapper = frameNode->CreateLayoutWrapper();
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_FALSE(layoutWrapper->GetOrCreateChildByIndex(9, false)->IsActive());
    EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(0, false)->IsActive());
}

/**
 * @tc.name: GridTest018
 * @tc.desc: Test all the properties of grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest018, TestSize.Level1)
{
    GridModelNG gridModelNG;
    RefPtr<ScrollControllerBase> positionController = gridModelNG.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModelNG.CreateScrollBarProxy();
    gridModelNG.Create(positionController, scrollBarProxy);
    gridModelNG.SetRowsTemplate("1fr 1fr 1fr");
    gridModelNG.SetColumnsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(Dimension(5));
    gridModelNG.SetColumnsGap(Dimension(10));
    gridModelNG.SetCachedCount(5);
    gridModelNG.SetLayoutDirection(FlexDirection::ROW);
    gridModelNG.SetMaxCount(10);
    gridModelNG.SetMinCount(1);
    gridModelNG.SetCellLength(200);
    gridModelNG.SetEditable(true);
    gridModelNG.SetScrollBarMode(static_cast<int32_t>(NG::DisplayMode::ON));
    gridModelNG.SetScrollBarWidth("10px");
    gridModelNG.SetScrollBarColor("#909090");
    CreateGridItem(10);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. compare grid properties and expected value.
     * @tc.expected: grid properties equals expected value.
     */
    EXPECT_EQ(layoutProperty_->GetRowsTemplate(), "1fr 1fr 1fr");
    EXPECT_EQ(layoutProperty_->GetColumnsTemplate(), "1fr 1fr");
    EXPECT_EQ(layoutProperty_->GetRowsGap(), Dimension(5));
    EXPECT_EQ(layoutProperty_->GetColumnsGap(), Dimension(10));
    EXPECT_EQ(layoutProperty_->GetCachedCount(), 5);
    EXPECT_EQ(layoutProperty_->GetGridDirection(), FlexDirection::ROW);
    EXPECT_EQ(layoutProperty_->GetMaxCount(), 10);
    EXPECT_EQ(layoutProperty_->GetMinCount(), 1);
    EXPECT_EQ(layoutProperty_->GetCellLength(), 200);
    EXPECT_EQ(layoutProperty_->GetEditable(), true);

    auto paintProperty = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetScrollBarMode(), NG::DisplayMode::ON);
    EXPECT_EQ(paintProperty->GetScrollBarWidth(), StringUtils::StringToDimensionWithUnit("10px"));
    EXPECT_EQ(paintProperty->GetScrollBarColor(), Color::FromString("#909090"));
}

/**
 * @tc.name: GridTest019
 * @tc.desc: Test all the properties of grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest019, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("abcd1234 *&^%$");
    gridModelNG.SetColumnsTemplate("abcd1234 *&^%$");
    CreateGridItem(10);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. compare grid properties and expected value after change.
     * @tc.expected: grid properties equals expected value after change.
     */
    EXPECT_EQ(layoutProperty_->GetRowsTemplate(), "");
    EXPECT_EQ(layoutProperty_->GetColumnsTemplate(), "");
}

/**
 * @tc.name: GridTest020
 * @tc.desc: Test function of grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest020, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetMultiSelectable(true);
    gridModelNG.SetSupportAnimation(true);
    gridModelNG.SetOnScrollToIndex([](const BaseEventInfo*) {});
    CreateGridItem(10);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Check whether the updated properties and parameters are correct.
     * @tc.expected: parameters are correct.
     */
    EXPECT_TRUE(pattern_->multiSelectable_);
    EXPECT_TRUE(pattern_->supportAnimation_);
}

/**
 * @tc.name: GridTest021
 * @tc.desc: Test all the properties of gridItem.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gridItem and Set properties.
     */
    GridItemModelNG gridItemModelNG;
    gridItemModelNG.Create([](int32_t) {}, true);
    gridItemModelNG.SetRowStart(1);
    gridItemModelNG.SetRowEnd(2);
    gridItemModelNG.SetColumnStart(1);
    gridItemModelNG.SetColumnEnd(2);
    gridItemModelNG.SetForceRebuild(true);
    gridItemModelNG.SetSelectable(false);
    gridItemModelNG.SetOnSelect([](bool) {});

    /**
     * @tc.steps: step2. Get frameNode and properties.
     * @tc.expected: step2. Check properties is correct.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetRowStart(), 1);
    EXPECT_EQ(layoutProperty->GetRowEnd(), 2);
    EXPECT_EQ(layoutProperty->GetColumnStart(), 1);
    EXPECT_EQ(layoutProperty->GetColumnEnd(), 2);
    EXPECT_EQ(layoutProperty->GetCustomCrossIndex(Axis::VERTICAL), 1);
    EXPECT_EQ(layoutProperty->GetMainSpan(Axis::VERTICAL), 2);
    EXPECT_EQ(layoutProperty->GetCrossSpan(Axis::VERTICAL), 2);
    EXPECT_EQ(layoutProperty->GetMainStart(Axis::VERTICAL), 1);
    EXPECT_EQ(layoutProperty->GetCrossStart(Axis::VERTICAL), 1);
    EXPECT_EQ(layoutProperty->GetCustomCrossIndex(Axis::HORIZONTAL), 1);
    EXPECT_EQ(layoutProperty->GetMainSpan(Axis::HORIZONTAL), 2);
    EXPECT_EQ(layoutProperty->GetCrossSpan(Axis::HORIZONTAL), 2);
    EXPECT_EQ(layoutProperty->GetMainStart(Axis::HORIZONTAL), 1);
    EXPECT_EQ(layoutProperty->GetCrossStart(Axis::HORIZONTAL), 1);
    auto pattern = frameNode->GetPattern<GridItemPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->forceRebuild_);
    EXPECT_FALSE(pattern->selectable_);
    auto eventHub = frameNode->GetEventHub<GridItemEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(eventHub->onSelect_, nullptr);
}

/**
 * @tc.name: GridTest022
 * @tc.desc: Test GetInsertPosition func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest022, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Mock GetPaintRectWithTransform.
     */
    RectF gridRect(0.f, 0.f, DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT);
    EXPECT_CALL(
        *(AceType::RawPtr(AceType::DynamicCast<MockRenderContext>(frameNode_->renderContext_))),
        GetPaintRectWithTransform())
        .WillRepeatedly(Return(gridRect));

    /**
     * @tc.steps: step2. Run GetInsertPosition func.
     * @tc.expected: Verify return value.
     */
    EXPECT_EQ(eventHub_->GetInsertPosition(DEFAULT_ROOT_WIDTH + 1, DEFAULT_ROOT_HEIGHT), -1); // out of grid
    EXPECT_EQ(eventHub_->GetInsertPosition(0.f, 0.f), 0); // 0, 0
    EXPECT_EQ(eventHub_->GetInsertPosition(90.f, 50.f), 0); // first item
    EXPECT_EQ(eventHub_->GetInsertPosition(360.f, 50.f), 1); // between the second and third
    EXPECT_EQ(eventHub_->GetInsertPosition(360.f, 100.f), 1); // between the 2nd, 3rd, 6th, 7th
    EXPECT_EQ(eventHub_->GetInsertPosition(180.f, 300.f), 8); // in grid but not on item
    pattern_->GetGridLayoutInfo().currentRect_ = RectF(0.f, 0.f, 100.f, 100.f);
    EXPECT_EQ(eventHub_->GetInsertPosition(50.f, 50.f), 0); // on currentRect_
}

/**
 * @tc.name: GridTest023
 * @tc.desc: Test GetFrameNodeChildSize func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest023, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    EXPECT_EQ(eventHub_->GetFrameNodeChildSize(), 8);
}

/**
 * @tc.name: GridTest024
 * @tc.desc: Test positionController func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest024, TestSize.Level1)
{
    GridModelNG gridModelNG;
    RefPtr<ScrollControllerBase> positionController = gridModelNG.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModelNG.CreateScrollBarProxy();
    gridModelNG.Create(positionController, scrollBarProxy);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Test positionController_ func.
     * @tc.expected: Verify return value.
     */
    auto controller = pattern_->positionController_;
    controller->JumpTo(1, 0);
    auto layoutInfo = pattern_->GetGridLayoutInfo();
    EXPECT_EQ(layoutInfo.jumpIndex_, 1);
    controller->AnimateTo(Dimension(100.f, DimensionUnit::PX), 200.f, Curves::LINEAR);
    ASSERT_NE(pattern_->animator_, nullptr);
    Offset currentOffset = controller->GetCurrentOffset();
    EXPECT_EQ(currentOffset, Offset(0, 0));
    layoutInfo.axis_ = Axis::HORIZONTAL;
    currentOffset = controller->GetCurrentOffset();
    EXPECT_EQ(currentOffset, Offset(0, 0));
}

/**
 * @tc.name: GridTest025
 * @tc.desc: Test GetInsertPosition func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest025, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Test GetInsertPosition func.
     * @tc.expected: Verify return value.
     */
    pattern_->gridLayoutInfo_.currentRect_ = RectF(0, 0, 100, 100);
    pattern_->gridLayoutInfo_.currentMovingItemPosition_ = 1;
    int32_t insertPosition = pattern_->GetInsertPosition(50.f, 50.f);
    EXPECT_EQ(insertPosition, 1);
    insertPosition = pattern_->GetInsertPosition(200.f, 200.f);
    EXPECT_EQ(insertPosition, -1);
}

/**
 * @tc.name: GridAccessibilityTest001
 * @tc.desc: Test Grid Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridAccessibilityTest001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Run accessibility func.
     * @tc.expected: Verify return value.
     */
    EXPECT_TRUE(accessibility_->IsScrollable());
    EXPECT_FALSE(accessibility_->IsEditable());
    EXPECT_EQ(accessibility_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibility_->GetCurrentIndex(), 0);
    EXPECT_EQ(accessibility_->GetEndIndex(), 7);
    EXPECT_EQ(accessibility_->GetCollectionItemCounts(), 8);

    pattern_->multiSelectable_ = true;
    AceCollectionInfo info = accessibility_->GetCollectionInfo();
    EXPECT_EQ(info.rows, 2);
    EXPECT_EQ(info.columns, 4);
    EXPECT_EQ(info.selectMode, 1);

    pattern_->gridLayoutInfo_.reachStart_ = false;
    pattern_->gridLayoutInfo_.reachEnd_ = false;

    accessibility_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibility_->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: GridAccessibilityTest002
 * @tc.desc: Test Grid Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridAccessibilityTest002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get frameNode, accessibility and RunMeasureAndLayout.
     * @tc.expected: Verify return value.
     */
    AceCollectionInfo info = accessibility_->GetCollectionInfo();
    EXPECT_EQ(info.rows, 0);
    EXPECT_EQ(info.columns, 0);
    EXPECT_EQ(info.selectMode, 0);
}

/**
 * @tc.name: GridAccessibilityTest003
 * @tc.desc: Test GridItem Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridAccessibilityTest003, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get itemFrameNode, itemAccessibility.
     */
    auto itemFrameNode = GetItemFrameNode(1);
    ASSERT_NE(itemFrameNode, nullptr);
    auto itemAccessibility = itemFrameNode->GetAccessibilityProperty<GridItemAccessibilityProperty>();
    ASSERT_NE(itemAccessibility, nullptr);

    /**
     * @tc.steps: step2. Run itemAccessibility func.
     * @tc.expected: Verify return value.
     */
    EXPECT_FALSE(itemAccessibility->IsSelected());
    AceCollectionItemInfo info = itemAccessibility->GetCollectionItemInfo();
    EXPECT_EQ(info.row, 0);
    EXPECT_EQ(info.column, 1);
    EXPECT_EQ(info.rowSpan, 1);
    EXPECT_EQ(info.columnSpan, 1);
    EXPECT_FALSE(info.heading);

    itemAccessibility->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = itemAccessibility->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: GridSelectTest001
 * @tc.desc: Test mouse click to select, only PRESS and RELEASE the mouse
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridSelectTest001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Click the (0, 0) point of firstItem.
     * @tc.expected: item not selected on MouseAction::PRESS.
     */
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0.f, 0.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    RefPtr<GridItemPattern> firstItemPattern = GetItemPattern(0);
    EXPECT_FALSE(firstItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE); // Release the mouse to deselect.
    pattern_->HandleMouseEventWithoutKeyboard(info);
}

/**
 * @tc.name: GridSelectTest002
 * @tc.desc: Test mouse box selection, PRESS, MOVE and RELEASE the mouse
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridSelectTest002, TestSize.Level1)
{
    const Offset LEFT_TOP = Offset(90.f, 50.f);
    const Offset LEFT_BOTTOM = Offset(90.f, 150.f);
    const Offset RIGHT_TOP = Offset(270.f, 50.f);
    const Offset RIGHT_BOTTOM = Offset(270.f, 150.f);

    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Select (0, 0) - (284, 100) zone.
     * @tc.expected: The 1st, 2nd, 5th, 6th items are selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0.f, 0.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(180.f, 100.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    EXPECT_TRUE(GetItemPattern(0)->IsSelected());
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
    EXPECT_TRUE(GetItemPattern(4)->IsSelected());
    EXPECT_TRUE(GetItemPattern(5)->IsSelected());
    info.SetAction(MouseAction::RELEASE); // Release the mouse to deselect.
    pattern_->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step2. Select (90, 50) - (270, 150) zone, from the LEFT_TOP to the RIGHT_BOTTOM.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(LEFT_TOP);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(RIGHT_BOTTOM);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    EXPECT_TRUE(GetItemPattern(0)->IsSelected());
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
    EXPECT_TRUE(GetItemPattern(4)->IsSelected());
    EXPECT_TRUE(GetItemPattern(5)->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step3. Select (90, 50) - (270, 150) zone, from the RIGHT_TOP to the LEFT_BOTTOM.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(RIGHT_TOP);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(LEFT_BOTTOM);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    EXPECT_TRUE(GetItemPattern(0)->IsSelected());
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
    EXPECT_TRUE(GetItemPattern(4)->IsSelected());
    EXPECT_TRUE(GetItemPattern(5)->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step4. Select (90, 50) - (270, 150) zone, from the LEFT_BOTTOM to the RIGHT_TOP.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(LEFT_BOTTOM);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(RIGHT_TOP);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    EXPECT_TRUE(GetItemPattern(0)->IsSelected());
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
    EXPECT_TRUE(GetItemPattern(4)->IsSelected());
    EXPECT_TRUE(GetItemPattern(5)->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step5. Select (90, 50) - (270, 150) zone, from the RIGHT_BOTTOM to the LEFT_TOP.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(RIGHT_BOTTOM);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(LEFT_TOP);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    EXPECT_TRUE(GetItemPattern(0)->IsSelected());
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
    EXPECT_TRUE(GetItemPattern(4)->IsSelected());
    EXPECT_TRUE(GetItemPattern(5)->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
}

/**
 * @tc.name: GridSelectTest003
 * @tc.desc: Test gridItem selectable property and onSelect callback
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridSelectTest003, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMultiSelectable(true);
    /**
     * @tc.steps: step1. Create gridItem.
     */
    bool isSixthItemSelected = false;
    auto selectCallback = [&isSixthItemSelected](bool) { isSixthItemSelected = true; };
    for (int32_t i = 0; i < 8; i++) {
        GridItemModelNG gridItemModel;
        gridItemModel.Create();
        SetHeight(Dimension(DEFAULT_ITEM_MAIN_LENGTH));
        if (i == 1) {
            gridItemModel.SetSelectable(false);
        }
        if (i == 5) {
            gridItemModel.SetOnSelect(std::move(selectCallback));
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Select (225, 50) - (315, 150) zone.
     * @tc.expected: The 2nd item is not selected but 6th item is selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(225.f, 50.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(315.f, 150.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    EXPECT_FALSE(GetItemPattern(1)->IsSelected());
    EXPECT_TRUE(GetItemPattern(5)->IsSelected());
    EXPECT_TRUE(isSixthItemSelected);
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
}

/**
 * @tc.name: GridSelectTest004
 * @tc.desc: Test OnMouseSelectAll func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridSelectTest004, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Run OnMouseSelectAll func.
     * @tc.expected: All items are selected.
     */
    pattern_->OnMouseSelectAll();
    auto children = frameNode_->GetChildren();
    for (const auto& item : children) {
        auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
        if (!itemFrameNode) {
            continue;
        }
        auto itemPattern = itemFrameNode->GetPattern<GridItemPattern>();
        EXPECT_TRUE(itemPattern->IsSelected());
    }
}

/**
 * @tc.name: GridSelectTest005
 * @tc.desc: Test select in other condition
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridSelectTest005, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Select (225, 50) - (315, 150) zone with RIGHT_BUTTON.
     * @tc.expected: The item is not selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::RIGHT_BUTTON); // Use RIGHT_BUTTON to select.
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(225.f, 50.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(315.f, 150.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    EXPECT_FALSE(GetItemPattern(1)->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step2. Select (225, 50) - (315, 150) zone and trigger other MouseAction.
     * @tc.expected: The item is still selected when trigger other MouseAction.
     */
    info.SetButton(MouseButton::LEFT_BUTTON); // Use RIGHT_BUTTON to select.
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(225.f, 50.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(315.f, 150.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
    info.SetAction(MouseAction::HOVER); // Trigger other MouseAction.
    pattern_->HandleMouseEventWithoutKeyboard(info);
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
}

/**
 * @tc.name: GridSelectTest006
 * @tc.desc: Test mouse right button click on selected item
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridSelectTest006, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Select (0, 0) - (284, 100) zone.
     * @tc.expected: The 1st, 2nd, 5th, 6th items are selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0.f, 0.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(180.f, 100.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    EXPECT_TRUE(GetItemPattern(0)->IsSelected());
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
    EXPECT_TRUE(GetItemPattern(4)->IsSelected());
    EXPECT_TRUE(GetItemPattern(5)->IsSelected());

    /**
     * @tc.steps: step2. Right click on (150.f, 50.f), in selected zone.
     * @tc.expected: The 1st item is still selected.
     */
    info.SetButton(MouseButton::RIGHT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(150.f, 50.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    EXPECT_TRUE(GetItemPattern(0)->IsSelected());

    /**
     * @tc.steps: step3. Left click on (280.f, 100.f), out of selected zone.
     * @tc.expected: The 1st item is not selected.
     */
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetLocalLocation(Offset(280.f, 100.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    EXPECT_FALSE(GetItemPattern(0)->IsSelected());
}

/**
 * @tc.name: GridDragTest001
 * @tc.desc: Verify drag func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridDragTest001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetEditable(true);

    /**
     * @tc.steps: step1. SetOnItemDragStart to get customNode.
     */
    auto onItemDragStart = [](const ItemDragInfo&, int32_t) {
        auto dragItem = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
        return AceType::DynamicCast<UINode>(dragItem);
    };
    gridModelNG.SetOnItemDragStart(onItemDragStart);
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Get frameNode and eventHub and RunMeasureAndLayout.
     */
    eventHub_->onItemDragStart_ = onItemDragStart;
    auto gestureEventHub = eventHub_->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = gestureEventHub->dragEventActuator_;
    ASSERT_NE(dragEventActuator, nullptr);
    auto userCallback = dragEventActuator->userCallback_;
    ASSERT_NE(userCallback, nullptr);
    auto HandleOnItemDragStart = userCallback->GetActionStartEventFunc();
    auto HandleOnItemDragUpdate = userCallback->GetActionUpdateEventFunc();
    auto HandleOnItemDragEnd = userCallback->GetActionEndEventFunc();
    auto HandleOnItemDragCancel = userCallback->GetActionCancelEventFunc();

    /**
     * @tc.steps: step3. Set info.
     */
    GestureEvent info;
    Point globalPoint = Point(270.f, 50.f); // Point at the second item.
    info.SetGlobalPoint(globalPoint);

    /**
     * @tc.steps: step4. Trigger HandleOnItemDragStart.
     * @tc.expected: Verify some values of the drag.
     */
    HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 1);
    ASSERT_NE(eventHub_->dragDropProxy_, nullptr);
    auto itemFrameNode = GetItemFrameNode(1);
    EXPECT_EQ(eventHub_->draggingItem_, itemFrameNode);

    /**
     * @tc.steps: step5. Trigger HandleOnItemDragUpdate, HandleOnItemDragEnd.
     * @tc.expected: Verify some values of the drag.
     */
    HandleOnItemDragUpdate(info);
    HandleOnItemDragEnd(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
    EXPECT_EQ(eventHub_->draggingItem_, nullptr);

    /**
     * @tc.steps: step6. Trigger HandleOnItemDragStart, HandleOnItemDragUpdate, HandleOnItemDragEnd.
     * @tc.expected: Verify some values of the drag.
     */
    HandleOnItemDragStart(info);
    HandleOnItemDragUpdate(info);
    HandleOnItemDragCancel();
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
    EXPECT_EQ(eventHub_->draggingItem_, nullptr);
}

/**
 * @tc.name: GridDragTest002
 * @tc.desc: Verify drag func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridDragTest002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetEditable(true);
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Run FireOnItemDragEnter, FireOnItemDragLeave.
     * @tc.expected: Verify GetOriginalIndex.
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(0.f);
    dragInfo.SetY(0.f);
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, -1);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 8);

    /**
     * @tc.steps: step2. MoveItemsForward.
     * @tc.expected: Verify GetOriginalIndex.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 1, 5);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 5);
    eventHub_->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);

    /**
     * @tc.steps: step3. MoveItemsBack.
     * @tc.expected: Verify GetOriginalIndex.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 5, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    eventHub_->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);

    /**
     * @tc.steps: step4. Move something to Grid.
     * @tc.expected: Verify GetOriginalIndex.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, -1, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    eventHub_->FireOnItemDrop(dragInfo, -1, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);
}

/**
 * @tc.name: GridDragTest003
 * @tc.desc: Verify drag func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridDragTest003, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetEditable(true);
    gridModelNG.SetOnItemDragEnter([](const ItemDragInfo) {});
    gridModelNG.SetOnItemDragMove([](const ItemDragInfo&, int32_t, int32_t) {});
    gridModelNG.SetOnItemDragLeave([](const ItemDragInfo&, int32_t) {});
    gridModelNG.SetOnItemDrop([](const ItemDragInfo&, int32_t, int32_t, bool) {});
    CreateGridItem(8);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Run FireOnItemDragEnter, FireOnItemDragLeave.
     * @tc.expected: Verify GetOriginalIndex.
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(0.f);
    dragInfo.SetY(0.f);
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, -1);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 8);
    pattern_->ClearDragState();

    /**
     * @tc.steps: step2. MoveItemsForward.
     * @tc.expected: Verify GetOriginalIndex.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 1, 5);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 5);
    eventHub_->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);

    /**
     * @tc.steps: step3. MoveItemsBack.
     * @tc.expected: Verify GetOriginalIndex.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 5, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    eventHub_->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);
}

/**
 * @tc.name: GridFocusStepTest001
 * @tc.desc: Test GetNextFocusNode func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridFocusStepTest001, TestSize.Level1)
{
    /**
     *  ___180__360__540__720
     * |____|____|____|____|100
     * |____|____|____|____|200
     * |____|____|          300
     */
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItemWithButton(10);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    RefPtr<FocusHub> currentFocusNode = GetItemFocusHub(0);
    currentFocusNode->RequestFocusImmediately();
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::NONE, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::LEFT, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::UP, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::RIGHT, currentFocusNode).Upgrade(), GetItemFocusHub(1));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::DOWN, currentFocusNode).Upgrade(), GetItemFocusHub(4));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::LEFT_END, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::UP_END, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::RIGHT_END, currentFocusNode).Upgrade(), GetItemFocusHub(3));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::DOWN_END, currentFocusNode).Upgrade(), nullptr);

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentFocusNode = GetItemFocusHub(3);
    currentFocusNode->RequestFocusImmediately();
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::NONE, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::LEFT, currentFocusNode).Upgrade(), GetItemFocusHub(2));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::UP, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::RIGHT, currentFocusNode).Upgrade(), GetItemFocusHub(4));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::DOWN, currentFocusNode).Upgrade(), GetItemFocusHub(7));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::LEFT_END, currentFocusNode).Upgrade(), GetItemFocusHub(0));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::UP_END, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::RIGHT_END, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::DOWN_END, currentFocusNode).Upgrade(), nullptr);

    /**
     * @tc.steps: step3. GetNextFocusNode from left_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentFocusNode = GetItemFocusHub(8);
    currentFocusNode->RequestFocusImmediately();
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::NONE, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::LEFT, currentFocusNode).Upgrade(), GetItemFocusHub(7));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::UP, currentFocusNode).Upgrade(), GetItemFocusHub(4));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::RIGHT, currentFocusNode).Upgrade(), GetItemFocusHub(9));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::DOWN, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::LEFT_END, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::UP_END, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::RIGHT_END, currentFocusNode).Upgrade(), GetItemFocusHub(9));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::DOWN_END, currentFocusNode).Upgrade(), nullptr);

    /**
     * @tc.steps: step4. GetNextFocusNode from right_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentFocusNode = GetItemFocusHub(9);
    currentFocusNode->RequestFocusImmediately();
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::NONE, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::LEFT, currentFocusNode).Upgrade(), GetItemFocusHub(8));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::UP, currentFocusNode).Upgrade(), GetItemFocusHub(5));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::RIGHT, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::DOWN, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::LEFT_END, currentFocusNode).Upgrade(), GetItemFocusHub(8));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::UP_END, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::RIGHT_END, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::DOWN_END, currentFocusNode).Upgrade(), nullptr);

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentFocusNode = GetItemFocusHub(5);
    currentFocusNode->RequestFocusImmediately();
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::NONE, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::LEFT, currentFocusNode).Upgrade(), GetItemFocusHub(4));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::UP, currentFocusNode).Upgrade(), GetItemFocusHub(1));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::RIGHT, currentFocusNode).Upgrade(), GetItemFocusHub(6));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::DOWN, currentFocusNode).Upgrade(), GetItemFocusHub(9));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::LEFT_END, currentFocusNode).Upgrade(), GetItemFocusHub(4));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::UP_END, currentFocusNode).Upgrade(), nullptr);
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::RIGHT_END, currentFocusNode).Upgrade(), GetItemFocusHub(7));
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::DOWN_END, currentFocusNode).Upgrade(), nullptr);
}

/**
 * @tc.name: GridFocusStepTest002
 * @tc.desc: Test GetNextFocusNode func with scrolled Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridFocusStepTest002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItemWithButton(10);
    GetGridInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Set Grid height to 200.
     */
    RefPtr<LayoutWrapper> gridLayoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, 200.f };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, 200.f };
    LayoutConstraint.selfIdealSize = { DEFAULT_ROOT_WIDTH, 200.f };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, 200.f };
    gridLayoutWrapper->Measure(LayoutConstraint);
    gridLayoutWrapper->Layout();

    /**
     * @tc.steps: step2. GetNextFocusNode from 8th item.
     * @tc.expected: Grid jump up.
     */
    RefPtr<FocusHub> currentFocusNode = GetItemFocusHub(7);
    currentFocusNode->RequestFocusImmediately();
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::RIGHT, currentFocusNode).Upgrade(), GetItemFocusHub(8));
    EXPECT_EQ(pattern_->gridLayoutInfo_.jumpIndex_, 8);

    /**
     * @tc.steps: step3. GetNextFocusNode from 5th item.
     * @tc.expected: Grid jump Down.
     */
    currentFocusNode = GetItemFocusHub(4);
    currentFocusNode->RequestFocusImmediately();
    EXPECT_EQ(pattern_->GetNextFocusNode(FocusStep::LEFT, currentFocusNode).Upgrade(), GetItemFocusHub(3));
    EXPECT_EQ(pattern_->gridLayoutInfo_.jumpIndex_, 3);
}

/**
 * @tc.name: GridPatternTest001
 * @tc.desc: Test grid pattern UpdateCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();

    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    bool result;
    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case1: no scrollEffect, !isScrollContent
     * @tc.expected: step2. equal.
     */
    result = pattern_->UpdateCurrentOffset(0, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->scrollState_, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case2: no scrollEffect, isScrollContent
     * @tc.expected: step2. equal.
     */
    result = pattern_->UpdateCurrentOffset(0, SCROLL_FROM_BAR);
    EXPECT_EQ(pattern_->scrollState_, SCROLL_FROM_BAR);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case3: scrollEffect not Spring, !isScrollContent
     * @tc.expected: step2. equal.
     */
    pattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::FADE);
    result = pattern_->UpdateCurrentOffset(0, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->scrollState_, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case4: scrollEffect Spring, !isScrollContent
     * @tc.expected: step2. equal.
     */
    pattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    result = pattern_->UpdateCurrentOffset(0, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->scrollState_, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case4: scrollEffect Spring, isScrollContent
     * @tc.expected: step2. equal.
     */
    pattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    result = pattern_->UpdateCurrentOffset(0, SCROLL_FROM_BAR);
    EXPECT_EQ(pattern_->scrollState_, SCROLL_FROM_BAR);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GridPatternTest002
 * @tc.desc: Test grid pattern IsOutOfBoundary function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    bool result;
    result = pattern_->IsOutOfBoundary();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GridPatternTest003
 * @tc.desc: Test grid pattern IsOutOfBoundary function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest003, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    bool result;
    pattern_->gridLayoutInfo_.reachStart_ = true;
    result = pattern_->IsOutOfBoundary();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GridPatternTest004
 * @tc.desc: Test grid pattern IsOutOfBoundary function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest004, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    bool result;
    pattern_->gridLayoutInfo_.reachStart_ = false;
    pattern_->gridLayoutInfo_.offsetEnd_ = true;
    result = pattern_->IsOutOfBoundary();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GridPatternTest005
 * @tc.desc: Test grid pattern IsOutOfBoundary function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest005, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    bool result;
    pattern_->gridLayoutInfo_.reachStart_ = true;
    pattern_->gridLayoutInfo_.offsetEnd_ = true;
    result = pattern_->IsOutOfBoundary();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GridPatternTest006
 * @tc.desc: Test grid pattern OutBoundaryCallback function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest006, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    bool outBoundary;
    outBoundary = pattern_->OutBoundaryCallback();
    EXPECT_FALSE(outBoundary);
}

/**
 * @tc.name: GridPatternTest007
 * @tc.desc: Test grid pattern OutBoundaryCallback function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest007, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    bool outBoundary;
    pattern_->gridLayoutInfo_.reachStart_ = true;
    pattern_->gridLayoutInfo_.offsetEnd_ = true;
    outBoundary = pattern_->OutBoundaryCallback();
    EXPECT_TRUE(outBoundary);
}

/**
 * @tc.name: GridPatternTest008
 * @tc.desc: Test grid pattern OutBoundaryCallback function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest008, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    bool outBoundary;
    pattern_->gridLayoutInfo_.reachStart_ = false;
    pattern_->gridLayoutInfo_.offsetEnd_ = true;
    outBoundary = pattern_->OutBoundaryCallback();
    EXPECT_TRUE(outBoundary);
}

/**
 * @tc.name: GridPatternTest009
 * @tc.desc: Test grid pattern OutBoundaryCallback function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest009, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    bool outBoundary;
    pattern_->gridLayoutInfo_.reachStart_ = true;
    pattern_->gridLayoutInfo_.offsetEnd_ = false;
    outBoundary = pattern_->OutBoundaryCallback();
    EXPECT_TRUE(outBoundary);
}

/**
 * @tc.name: GridPatternTest010
 * @tc.desc: Test grid pattern CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest010, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    EXPECT_NE(pattern_->CreateNodePaintMethod(), nullptr);
}

/**
 * @tc.name: GridPatternTest011
 * @tc.desc: Test grid pattern OnModifyDone function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest011, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    pattern_->SetMultiSelectable(true);
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    auto gridScrollLayoutAlgorithm = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(
        pattern_->gridLayoutInfo_, ALGORITHM_RELATE_LALUE_FIRST, ALGORITHM_RELATE_LALUE_SECOND);
    ASSERT_NE(gridScrollLayoutAlgorithm, nullptr);
    gridScrollLayoutAlgorithm->SetCanOverScroll(true);
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    pattern_->gridLayoutInfo_.reachEnd_ = true;
    pattern_->gridLayoutInfo_.prevOffset_ = PREV_OFFSET_FIRST;
    pattern_->gridLayoutInfo_.currentOffset_ = CURRENT_OFFSET_FIRST;
    EXPECT_FALSE(gridScrollLayoutAlgorithm->gridLayoutInfo_.reachEnd_);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->multiSelectable_);
    EXPECT_TRUE(pattern_->isMouseEventInit_);
    EXPECT_TRUE(pattern_->isConfigScrollable_);
    pattern_->SetMultiSelectable(false);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->multiSelectable_);
    EXPECT_FALSE(pattern_->isMouseEventInit_);
}

/**
 * @tc.name: GridPatternTest012
 * @tc.desc: Test grid pattern OnModifyDone function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest012, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    pattern_->SetMultiSelectable(true);
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    auto gridScrollLayoutAlgorithm = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(
        pattern_->gridLayoutInfo_, ALGORITHM_RELATE_LALUE_FIRST, ALGORITHM_RELATE_LALUE_SECOND);
    ASSERT_NE(gridScrollLayoutAlgorithm, nullptr);
    gridScrollLayoutAlgorithm->SetCanOverScroll(false);
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    pattern_->gridLayoutInfo_.reachEnd_ = true;
    pattern_->gridLayoutInfo_.prevOffset_ = PREV_OFFSET_FIRST;
    pattern_->gridLayoutInfo_.currentOffset_ = CURRENT_OFFSET_FIRST;
    EXPECT_FALSE(gridScrollLayoutAlgorithm->gridLayoutInfo_.reachEnd_);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->multiSelectable_);
    EXPECT_TRUE(pattern_->isMouseEventInit_);
    EXPECT_TRUE(pattern_->isConfigScrollable_);
    pattern_->SetMultiSelectable(false);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->multiSelectable_);
    EXPECT_FALSE(pattern_->isMouseEventInit_);
}

/**
 * @tc.name: GridPatternTest013
 * @tc.desc: Test grid pattern CreateLayoutAlgorithm function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest013, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto result = pattern_->CreateLayoutAlgorithm();
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: GridPatternTest014
 * @tc.desc: Test grid pattern GetContentSize function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest014, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);

    auto size = pattern_->GetContentSize();
    EXPECT_EQ(size.Width(), 0);
    EXPECT_EQ(size.Height(), 0);
}

/**
 * @tc.name: GridPatternTest015
 * @tc.desc: Test grid pattern CheckScrollable function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest015, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    EXPECT_TRUE(pattern_->scrollable_);
    pattern_->CheckScrollable();
    EXPECT_FALSE(pattern_->scrollable_);
}

/**
 * @tc.name: GridPatternTest016
 * @tc.desc: Test grid pattern CheckScrollable function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest016, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    EXPECT_TRUE(pattern_->scrollable_);
    pattern_->gridLayoutInfo_.endIndex_ = END_INDEX;
    pattern_->gridLayoutInfo_.startIndex_ = START_INDEX_END;
    pattern_->gridLayoutInfo_.childrenCount_ = CHILDREN_COUNT;
    pattern_->CheckScrollable();
    EXPECT_TRUE(pattern_->scrollable_);
}
/**
 * @tc.name: GridPatternTest017
 * @tc.desc: Test grid pattern UpdateScrollBarOffset function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest017, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    pattern_->scrollBar_ = nullptr;
    pattern_->scrollBarProxy_ = nullptr;
    pattern_->UpdateScrollBarOffset();
    EXPECT_EQ(pattern_->estimatedHeight_, 0.0f);
}

/**
 * @tc.name: GridPaintMethodTest001
 * @tc.desc: Test grid paint method GetForegroundDrawFunction function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPaintMethodTest001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();

    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto paintMethod = AceType::DynamicCast<GridPaintMethod>(pattern_->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    auto paintProperty = pattern_->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper paintWrapper(frameNode_->GetRenderContext(), frameNode_->GetGeometryNode(), paintProperty);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
    ASSERT_NE(drawFunction, nullptr);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).WillRepeatedly(Return());
    drawFunction(rsCanvas);
}

/**
 * @tc.name: GridPatternTest018
 * @tc.desc: Test grid pattern ModifyCurrentOffsetWhenReachEnd function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest018, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;
    constexpr float itemHeight = 100.0f;
    /**
     * @tc.steps: step1. Get frameNode, pattern, eventHub and RunMeasureAndLayout.
     */
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    RunMeasureAndLayout();
    pattern_->gridLayoutInfo_.reachEnd_ = true;
    pattern_->gridLayoutInfo_.prevOffset_ = PREV_OFFSET_FIRST;
    pattern_->gridLayoutInfo_.currentOffset_ = CURRENT_OFFSET_FIRST;
    // only set one of rowTemplate and columnsTemplate, use scrollable layout algorithm
    auto gridScrollLayoutAlgorithm = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(
        pattern_->gridLayoutInfo_, ALGORITHM_RELATE_LALUE_FIRST, ALGORITHM_RELATE_LALUE_SECOND);
    ASSERT_NE(gridScrollLayoutAlgorithm, nullptr);
    gridScrollLayoutAlgorithm->SetCanOverScroll(true);
    gridScrollLayoutAlgorithm->ModifyCurrentOffsetWhenReachEnd(DEVICE_HEIGHT);
    EXPECT_TRUE(gridScrollLayoutAlgorithm->gridLayoutInfo_.reachEnd_);

    for (uint32_t i = 0; i < itemCount; i++) {
        gridScrollLayoutAlgorithm->gridLayoutInfo_.lineHeightMap_[i] = itemHeight;
    }
    gridScrollLayoutAlgorithm->gridLayoutInfo_.prevOffset_ = PREV_OFFSET_SECOND;
    gridScrollLayoutAlgorithm->gridLayoutInfo_.currentOffset_ = CURRENT_OFFSET_SECOND;
    gridScrollLayoutAlgorithm->gridLayoutInfo_.startIndex_ = START_INDEX;
    gridScrollLayoutAlgorithm->gridLayoutInfo_.startMainLineIndex_ = START_MAIN_LINE_INDEX;
    gridScrollLayoutAlgorithm->gridLayoutInfo_.endMainLineIndex_ = itemCount;
    gridScrollLayoutAlgorithm->ModifyCurrentOffsetWhenReachEnd(DEVICE_HEIGHT);
    EXPECT_EQ(gridScrollLayoutAlgorithm->gridLayoutInfo_.currentOffset_, CURRENT_OFFSET_SECOND);
    EXPECT_EQ(gridScrollLayoutAlgorithm->gridLayoutInfo_.prevOffset_, PREV_OFFSET_SECOND);
    EXPECT_TRUE(gridScrollLayoutAlgorithm->gridLayoutInfo_.offsetEnd_);
}

/**
 * @tc.name: GridPatternTest019
 * @tc.desc: Test grid pattern GetMainGap function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest019, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(GRID_ROWS_GAP);
    CreateGridItem(10);
    GetGridInstance();
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    auto mainGap = pattern_->GetMainGap();
    EXPECT_EQ(mainGap, 0);
}

/**
 * @tc.name: GridPatternTest020
 * @tc.desc: Test grid pattern SetEdgeEffect function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest020, TestSize.Level1)
{
    GridModelNG gridModelNG;
    auto positionController = AceType::MakeRefPtr<ScrollControllerBase>();
    ASSERT_NE(positionController, nullptr);
    auto scrollProxy = AceType::MakeRefPtr<ScrollProxy>();
    ASSERT_NE(scrollProxy, nullptr);
    gridModelNG.Create(positionController, scrollProxy);
    gridModelNG.SetEdgeEffect(EdgeEffect::NONE);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetEdgeEffectValue(), EdgeEffect::NONE);
}

/**
 * @tc.name: GridPatternTest021
 * @tc.desc: Test grid pattern SetEdgeEffect function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest021, TestSize.Level1)
{
    GridModelNG gridModelNG;
    auto positionController = AceType::MakeRefPtr<ScrollControllerBase>();
    ASSERT_NE(positionController, nullptr);
    auto scrollProxy = AceType::MakeRefPtr<ScrollProxy>();
    ASSERT_NE(scrollProxy, nullptr);
    gridModelNG.Create(positionController, scrollProxy);
    gridModelNG.SetEdgeEffect(EdgeEffect::FADE);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetEdgeEffectValue(), EdgeEffect::FADE);
}

/**
 * @tc.name: GridPatternTest022
 * @tc.desc: Test grid pattern SetEdgeEffect function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPatternTest022, TestSize.Level1)
{
    GridModelNG gridModelNG;
    auto positionController = AceType::MakeRefPtr<ScrollControllerBase>();
    ASSERT_NE(positionController, nullptr);
    auto scrollProxy = AceType::MakeRefPtr<ScrollProxy>();
    ASSERT_NE(scrollProxy, nullptr);
    gridModelNG.Create(positionController, scrollProxy);
    gridModelNG.SetEdgeEffect(EdgeEffect::SPRING);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetEdgeEffectValue(), EdgeEffect::SPRING);
}
} // namespace OHOS::Ace::NG
