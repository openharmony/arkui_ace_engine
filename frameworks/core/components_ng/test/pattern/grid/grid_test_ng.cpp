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
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float DEVICE_WIDTH = 720.0f;
constexpr float DEVICE_HEIGHT = 1136.0f;
constexpr float GRID_POSITION = 100.0f;
constexpr float GRID_DURATION = 200.0f;
constexpr int32_t GRID_MAX_COUNT = 10;
constexpr int32_t GRID_MIN_COUNT = 1;
constexpr int32_t GRID_CELL_LENGTH = 200;
constexpr float GRID_SCROLL_OFFSET = 1.0f;
const SizeF CONTAINER_SIZE(DEVICE_WIDTH, DEVICE_HEIGHT);
const Dimension GRID_COLUMNS_GAP = Dimension(10, DimensionUnit::PX);
const Dimension GRID_ROWS_GAP = Dimension(5, DimensionUnit::PX);
const std::string GRID_DIRECTION_ROW = "GridDirection.Row";
const std::string GRID_DIRECTION_ROW_REVERSE = "GridDirection.RowReverse";
const std::string GRID_DIRECTION_COLUMN = "GridDirection.Column";
const std::string GRID_DIRECTION_COLUMN_REVERSE = "GridDirection.ColumnReverse";
const std::string GRID_SCROLL_BAR_AUTO = "BarState.Auto";
const std::string GRID_SCROLL_BAR_OFF = "BarState.Off";
const std::string GRID_SCROLL_BAR_ON = "BarState.On";
const std::string GRID_TEMPLATE_ILLEGAL = "abcd1234 *&^%$";
const int32_t GRID_CACHED_COUNT = 5;
const std::string SCROLL_BAR_WIDTH = "10px";
const std::string SCROLL_BAR_COLOR = "#909090";
constexpr float DEFAULT_ITEM_MAIN_SIZE = 100.f;
} // namespace

struct GridTestProperty {
    std::optional<std::string> rowsTemplate;
    std::optional<std::string> columnsTemplate;
    std::optional<Dimension> rowsGap;
    std::optional<Dimension> columnsGap;
    std::optional<int32_t> cachedCount;
    std::optional<FlexDirection> gridDirection;
    std::optional<int32_t> maxCount;
    std::optional<int32_t> minCount;
    std::optional<int32_t> cellLength;
    std::optional<bool> editable;
    std::optional<int32_t> scrollBarMode;
    std::optional<std::string> scrollBarWidth;
    std::optional<std::string> scrollBarColor;
};

class GridPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineBase::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineBase::TearDown();
    }

    static void SetWidth(const Dimension& width)
    {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto layoutProperty = frameNode->GetLayoutProperty();
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), std::nullopt));
    }

    static void SetHeight(const Dimension& height)
    {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto layoutProperty = frameNode->GetLayoutProperty();
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(height)));
    }

    static void CreateGridItem(int32_t number)
    {
        for (int32_t i = 0; i < number; i++) {
            GridItemModelNG gridItemModel;
            gridItemModel.Create();
            SetHeight(Dimension(DEFAULT_ITEM_MAIN_SIZE));
            ViewStackProcessor::GetInstance()->Pop();
        }
    }

    static void CreateGridItemWithButton(int32_t number)
    {
        for (int32_t i = 0; i < number; i++) {
            GridItemModelNG gridItemModel;
            gridItemModel.Create();
            SetHeight(Dimension(DEFAULT_ITEM_MAIN_SIZE));
            {
                ButtonView::Create("Button");
                ViewStackProcessor::GetInstance()->Pop();
            }
            ViewStackProcessor::GetInstance()->Pop();
        }
    }

    static void RunMeasureAndLayout(const RefPtr<FrameNode>& frameNode)
    {
        RefPtr<LayoutWrapper> gridLayoutWrapper = frameNode->CreateLayoutWrapper(false, false);
        gridLayoutWrapper->SetActive();
        gridLayoutWrapper->SetRootMeasureNode();
        LayoutConstraintF LayoutConstraint;
        LayoutConstraint.parentIdealSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
        LayoutConstraint.percentReference = { DEVICE_WIDTH, DEVICE_HEIGHT };
        LayoutConstraint.selfIdealSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
        LayoutConstraint.maxSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
        gridLayoutWrapper->Measure(LayoutConstraint);
        gridLayoutWrapper->Layout();
        gridLayoutWrapper->MountToHostOnMainThread();
    }

    static RefPtr<GridItemPattern> GetItemPattern(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        auto item = frameNode->GetChildAtIndex(index);
        auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
        if (!itemFrameNode) {
            return nullptr;
        }
        return itemFrameNode->GetPattern<GridItemPattern>();
    }

    static RefPtr<FocusHub> GetItemFocusHub(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        auto item = frameNode->GetChildAtIndex(index);
        auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
        if (!itemFrameNode) {
            return nullptr;
        }
        return itemFrameNode->GetOrCreateFocusHub();
    }

    static RefPtr<FrameNode> CreateGrid(const GridTestProperty& gridTestProperty, const int32_t girdItemCount = 0)
    {
        GridModelNG grid;
        RefPtr<ScrollControllerBase> positionController = grid.CreatePositionController();
        RefPtr<ScrollProxy> scrollBarProxy = grid.CreateScrollBarProxy();
        grid.Create(positionController, scrollBarProxy);

        if (gridTestProperty.rowsTemplate.has_value()) {
            grid.SetRowsTemplate(gridTestProperty.rowsTemplate.value());
        }
        if (gridTestProperty.columnsTemplate.has_value()) {
            grid.SetColumnsTemplate(gridTestProperty.columnsTemplate.value());
        }
        if (gridTestProperty.rowsGap.has_value()) {
            grid.SetRowsGap(gridTestProperty.rowsGap.value());
        }
        if (gridTestProperty.columnsGap.has_value()) {
            grid.SetColumnsGap(gridTestProperty.columnsGap.value());
        }
        if (gridTestProperty.cachedCount.has_value()) {
            grid.SetCachedCount(gridTestProperty.cachedCount.value());
        }
        if (gridTestProperty.gridDirection.has_value()) {
            grid.SetLayoutDirection(gridTestProperty.gridDirection.value());
        }
        if (gridTestProperty.maxCount.has_value()) {
            grid.SetMaxCount(gridTestProperty.maxCount.value());
        }
        if (gridTestProperty.minCount.has_value()) {
            grid.SetMinCount(gridTestProperty.minCount.value());
        }
        if (gridTestProperty.cellLength.has_value()) {
            grid.SetCellLength(gridTestProperty.cellLength.value());
        }
        if (gridTestProperty.editable.has_value()) {
            grid.SetEditable(gridTestProperty.editable.value());
        }
        if (gridTestProperty.scrollBarMode.has_value()) {
            grid.SetScrollBarMode(gridTestProperty.scrollBarMode.value());
        }
        if (gridTestProperty.scrollBarWidth.has_value()) {
            grid.SetScrollBarWidth(gridTestProperty.scrollBarWidth.value());
        }
        if (gridTestProperty.scrollBarColor.has_value()) {
            grid.SetScrollBarColor(gridTestProperty.scrollBarColor.value());
        }

        for (int32_t i = 0; i < girdItemCount; ++i) {
            GridItemModelNG gridItem;
            gridItem.Create();
            ViewStackProcessor::GetInstance()->Pop();
        }

        RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
        return AceType::DynamicCast<FrameNode>(element);
    }
};

/**
 * @tc.name: GridTest001
 * @tc.desc: Fill all items to grid with fixed row and column
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set grid properties.
     */
    GridTestProperty gridTestProperty;
    gridTestProperty.rowsTemplate = std::make_optional("1fr 1fr 1fr");
    gridTestProperty.columnsTemplate = std::make_optional("1fr 1fr 1fr");

    /**
     * @tc.steps: step2. Create grid and gridItem.
     */
    const int32_t gridItemCount = 9;
    RefPtr<FrameNode> frameNode = CreateGrid(gridTestProperty, gridItemCount);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. Set layoutConstraint.
     * @tc.expected: step3. related function is called.
     */
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(frameNode, nullptr);
    OptionalSizeF size(800.0f, 800.0f);
    LayoutConstraintF constraint;
    constraint.UpdateIllegalSelfIdealSizeWithCheck(size);
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();

    /**
     * @tc.steps: step4. When setting fixed rows and columns, check the status of child nodes in the grid.
     * @tc.expected: step4. All child nodes are active.
     */
    for (int32_t i = 0; i < gridItemCount; ++i) {
        EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: GridTest002
 * @tc.desc: Set fixed columns only Fill all items in the grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set grid properties.
     */
    GridTestProperty gridTestProperty;
    gridTestProperty.columnsTemplate = std::make_optional("1fr 1fr");
    gridTestProperty.columnsGap = std::make_optional(GRID_COLUMNS_GAP);

    /**
     * @tc.steps: step2. Create grid and gridItem.
     */
    RefPtr<FrameNode> frameNode = CreateGrid(gridTestProperty, 10);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetMultiSelectable(true);

    /**
     * @tc.steps: step3. Set layoutConstraint.
     * @tc.expected: step3. related function is called.
     */
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);

    /**
     * @tc.steps: step4. Call the measure and layout function of grid to calculate the size and layout.
     * @tc.expected: step4. Check size after layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    /**
     * @tc.steps: step5. Set different KeyEvent to verify the OnKeyEvent function.
     * @tc.expected: step5. Check whether the return value is correct.
     */
    KeyEvent event;
    auto ret = pattern->OnKeyEvent(event);
    EXPECT_FALSE(ret);
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_PAGE_DOWN;
    ret = pattern->OnKeyEvent(event);
    EXPECT_FALSE(ret);
    event.code = KeyCode::KEY_PAGE_UP;
    ret = pattern->OnKeyEvent(event);
    EXPECT_FALSE(ret);
    ret = pattern->HandleDirectionKey(event.code);
    EXPECT_FALSE(ret);
    ret = pattern->HandleDirectionKey(KeyCode::KEY_DPAD_UP);
    EXPECT_TRUE(ret);
    ret = false;
    ret = pattern->HandleDirectionKey(KeyCode::KEY_DPAD_DOWN);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: GridTest003
 * @tc.desc: Set fixed rows only Fill all items in the grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set grid properties.
     */
    GridTestProperty gridTestProperty;
    gridTestProperty.rowsTemplate = std::make_optional("1fr 1fr");
    gridTestProperty.rowsGap = std::make_optional(GRID_ROWS_GAP);
    gridTestProperty.scrollBarColor = std::make_optional(SCROLL_BAR_COLOR);

    /**
     * @tc.steps: step2. Create grid and gridItem.
     */
    RefPtr<FrameNode> frameNode = CreateGrid(gridTestProperty, 10);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetMultiSelectable(true);

    /**
     * @tc.steps: step3. Set layoutConstraint.
     * @tc.expected: step3. related function is called.
     */
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);

    /**
     * @tc.steps: step4. Call the measure and layout function of grid to calculate the size and layout.
     * @tc.expected: step4. Check size after layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    /**
     * @tc.steps: step5. Call OnModifyDone function.
     * @tc.expected: step5. Check whether the updated properties and parameters are correct.
     */
    pattern->OnModifyDone();
    EXPECT_TRUE(pattern->multiSelectable_);
    EXPECT_TRUE(pattern->isMouseEventInit_);
    EXPECT_TRUE(pattern->isConfigScrollable_);

    /**
     * @tc.steps: step5. Change MultiSelectable and Call OnModifyDone  function.
     * @tc.expected: step5. Check whether the updated properties and parameters are correct.
     */
    pattern->SetMultiSelectable(false);
    pattern->OnModifyDone();
    EXPECT_FALSE(pattern->multiSelectable_);
    EXPECT_FALSE(pattern->isMouseEventInit_);

    /**
     * @tc.steps: step6. Call the AddScrollEvent function to add a scroll position callback event.
     * @tc.expected: step6. Call and check the return value of the callback function.
     */
    pattern->AddScrollEvent();
    EXPECT_NE(pattern->scrollableEvent_, nullptr);
    auto callback = pattern->scrollableEvent_->GetScrollPositionCallback();
    EXPECT_NE(callback, nullptr);
    auto ret = callback(GRID_SCROLL_OFFSET, SCROLL_FROM_START);
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step7. When isConfigScrollable_ is false, call related functions.
     * @tc.expected: step7. Check the return value of the related function.
     */
    pattern->isConfigScrollable_ = false;
    ret = pattern->AnimateTo(GRID_POSITION, GRID_DURATION, Curves::LINEAR);
    EXPECT_EQ(ret, false);
    ret = pattern->UpdateCurrentOffset(GRID_SCROLL_OFFSET, SCROLL_FROM_UPDATE);
    EXPECT_EQ(ret, false);
    ret = pattern->UpdateStartIndex(1.0);
    EXPECT_EQ(ret, false);

    /**
     * @tc.steps: step8. When isConfigScrollable_ is true, call AnimateTo functions.
     * @tc.expected: step8. Check the return value and related parameters.
     */
    pattern->ScrollPage(false);
    pattern->isConfigScrollable_ = true;
    ret = pattern->AnimateTo(GRID_POSITION, GRID_DURATION, Curves::LINEAR);
    EXPECT_NE(pattern->animator_, nullptr);
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step9. Call AnimateTo functions again.
     * @tc.expected: step9. Check the return value and related parameters.
     */
    ret = false;
    pattern->animator_->status_ = Animator::Status::STOPPED;
    ret = pattern->AnimateTo(GRID_POSITION, GRID_DURATION, Curves::LINEAR);
    EXPECT_NE(pattern->animator_, nullptr);
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step10. When offsetEnd_ and reachStart_ are true, call OnScrollCallback functions.
     * @tc.expected: step10. Check whether the return value is correct.
     */
    pattern->gridLayoutInfo_.offsetEnd_ = true;
    pattern->gridLayoutInfo_.reachStart_ = true;
    ret = pattern->OnScrollCallback(0.0f, SCROLL_FROM_ANIMATION);
    EXPECT_EQ(ret, false);
    ret = pattern->OnScrollCallback(GRID_SCROLL_OFFSET, SCROLL_FROM_ANIMATION);
    EXPECT_EQ(pattern->gridLayoutInfo_.offsetEnd_, false);
    EXPECT_EQ(ret, false);
    ret = pattern->OnScrollCallback(-1.0f, SCROLL_FROM_ANIMATION);
    EXPECT_EQ(pattern->gridLayoutInfo_.reachStart_, false);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: GridTest004
 * @tc.desc: When fixed rows and columns are not set and direction is row, all items in the grid are filled.
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set grid properties.
     */
    GridTestProperty gridTestProperty;
    gridTestProperty.columnsGap = std::make_optional(GRID_COLUMNS_GAP);
    gridTestProperty.rowsGap = std::make_optional(GRID_ROWS_GAP);
    gridTestProperty.gridDirection = std::make_optional(FlexDirection::ROW);
    gridTestProperty.maxCount = std::make_optional(GRID_MAX_COUNT);
    gridTestProperty.minCount = std::make_optional(GRID_MIN_COUNT);
    gridTestProperty.cellLength = std::make_optional(GRID_CELL_LENGTH);

    /**
     * @tc.steps: step2. Create grid and gridItem.
     */
    RefPtr<FrameNode> frameNode = CreateGrid(gridTestProperty, 10);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetMultiSelectable(true);

    /**
     * @tc.steps: step3. Set layoutConstraint.
     * @tc.expected: step3. related function is called.
     */
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);

    /**
     * @tc.steps: step4. Call the measure and layout function of grid to calculate the size and layout.
     * @tc.expected: step4. Check size after layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    /**
     * @tc.steps: step5. Get grid layout properties.
     * @tc.expected: step5. Check whether the updated properties is correct.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<GridLayoutProperty>();
    auto layoutDirectionStr = layoutProperty->GetGridDirectionStr();
    EXPECT_EQ(layoutDirectionStr, GRID_DIRECTION_ROW);

    /**
     * @tc.steps: step6. Get the pattern to call the related functions in the positionController.
     */
    EXPECT_NE(pattern->positionController_, nullptr);

    /**
     * @tc.steps: step7. When Axis is VERTICAL and ScrollEdgeType is SCROLL_TOP, call the related functions in
     * positionController.
     * @tc.expected: step7. Check whether the return value is correct.
     */
    pattern->gridLayoutInfo_.axis_ = Axis::VERTICAL;
    ScrollEdgeType scrollEdgeType = ScrollEdgeType::SCROLL_TOP;
    pattern->positionController_->ScrollToEdge(scrollEdgeType, true);
    pattern->positionController_->ScrollPage(true, true);
    auto axis = pattern->positionController_->GetScrollDirection();
    EXPECT_EQ(axis, Axis::VERTICAL);

    /**
     * @tc.steps: step8. When Axis is HORIZONTAL and ScrollEdgeType is SCROLL_RIGHT, call the related functions in
     * positionController.
     * @tc.expected: step8. Check whether the return value is correct.
     */
    pattern->gridLayoutInfo_.axis_ = Axis::HORIZONTAL;
    scrollEdgeType = ScrollEdgeType::SCROLL_RIGHT;
    pattern->positionController_->ScrollToEdge(scrollEdgeType, true);
    pattern->positionController_->ScrollPage(true, true);
    axis = pattern->positionController_->GetScrollDirection();
    EXPECT_EQ(axis, Axis::HORIZONTAL);

    /**
     * @tc.steps: step9. When Axis is NONE, call the related functions in positionController.
     * @tc.expected: step9. Check whether the return value is correct.
     */
    pattern->gridLayoutInfo_.axis_ = Axis::NONE;
    auto offset = pattern->positionController_->GetCurrentOffset();
    EXPECT_EQ(offset, Offset::Zero());
}

/**
 * @tc.name: GridTest005
 * @tc.desc: When fixed rows and columns are not set and direction is RowReverse, all items in the grid are filled.
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set grid properties.
     */
    GridTestProperty gridTestProperty;
    gridTestProperty.columnsGap = std::make_optional(GRID_COLUMNS_GAP);
    gridTestProperty.rowsGap = std::make_optional(GRID_ROWS_GAP);
    gridTestProperty.gridDirection = std::make_optional(FlexDirection::ROW_REVERSE);
    gridTestProperty.maxCount = std::make_optional(GRID_MAX_COUNT);
    gridTestProperty.minCount = std::make_optional(GRID_MIN_COUNT);
    gridTestProperty.cellLength = std::make_optional(GRID_CELL_LENGTH);
    gridTestProperty.scrollBarMode = std::make_optional(static_cast<int32_t>(NG::DisplayMode::AUTO));

    /**
     * @tc.steps: step2. Create grid and gridItem.
     */
    RefPtr<FrameNode> frameNode = CreateGrid(gridTestProperty, 10);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetMultiSelectable(true);

    /**
     * @tc.steps: step3. Set layoutConstraint.
     * @tc.expected: step3. related function is called.
     */
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);

    /**
     * @tc.steps: step4. Call the measure and layout function of grid to calculate the size and layout.
     * @tc.expected: step4. Check size after layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    /**
     * @tc.steps: step5. Get grid layout properties.
     * @tc.expected: step5. Check whether the updated properties is correct.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<GridLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto layoutDirectionStr = layoutProperty->GetGridDirectionStr();
    EXPECT_EQ(layoutDirectionStr, GRID_DIRECTION_ROW_REVERSE);
}

/**
 * @tc.name: GridTest006
 * @tc.desc: When fixed rows and columns are not set and direction is Column, all items in the grid are filled.
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set grid properties.
     */
    GridTestProperty gridTestProperty;
    gridTestProperty.columnsGap = std::make_optional(GRID_COLUMNS_GAP);
    gridTestProperty.rowsGap = std::make_optional(GRID_ROWS_GAP);
    gridTestProperty.gridDirection = std::make_optional(FlexDirection::COLUMN);
    gridTestProperty.maxCount = std::make_optional(GRID_MAX_COUNT);
    gridTestProperty.minCount = std::make_optional(GRID_MIN_COUNT);
    gridTestProperty.cellLength = std::make_optional(GRID_CELL_LENGTH);
    gridTestProperty.scrollBarMode = std::make_optional(static_cast<int32_t>(NG::DisplayMode::ON));

    /**
     * @tc.steps: step2. Create grid and gridItem.
     */
    RefPtr<FrameNode> frameNode = CreateGrid(gridTestProperty, 10);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetMultiSelectable(true);

    /**
     * @tc.steps: step3. Set layoutConstraint.
     * @tc.expected: step3. related function is called.
     */
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);

    /**
     * @tc.steps: step4. Call the measure and layout function of grid to calculate the size and layout.
     * @tc.expected: step4. Check size after layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    /**
     * @tc.steps: step5. Get grid layout properties.
     * @tc.expected: step5. Check whether the updated properties is correct.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<GridLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto layoutDirectionStr = layoutProperty->GetGridDirectionStr();
    EXPECT_EQ(layoutDirectionStr, GRID_DIRECTION_COLUMN);
}

/**
 * @tc.name: GridTest007
 * @tc.desc: When fixed rows and columns are not set and direction is ColumnReverse, all items in the grid are filled.
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set grid properties.
     */
    GridTestProperty gridTestProperty;
    gridTestProperty.columnsGap = std::make_optional(GRID_COLUMNS_GAP);
    gridTestProperty.rowsGap = std::make_optional(GRID_ROWS_GAP);
    gridTestProperty.gridDirection = std::make_optional(FlexDirection::COLUMN_REVERSE);
    gridTestProperty.maxCount = std::make_optional(GRID_MAX_COUNT);
    gridTestProperty.minCount = std::make_optional(GRID_MIN_COUNT);
    gridTestProperty.cellLength = std::make_optional(GRID_CELL_LENGTH);
    gridTestProperty.scrollBarMode = std::make_optional(static_cast<int32_t>(NG::DisplayMode::OFF));

    /**
     * @tc.steps: step2. Create grid and gridItem.
     */
    RefPtr<FrameNode> frameNode = CreateGrid(gridTestProperty, 10);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetMultiSelectable(true);

    /**
     * @tc.steps: step3. Set layoutConstraint.
     * @tc.expected: step3. related function is called.
     */
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);

    /**
     * @tc.steps: step4. Call the measure and layout function of grid to calculate the size and layout.
     * @tc.expected: step4. Check size after layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    /**
     * @tc.steps: step5. Get grid layout properties.
     * @tc.expected: step5. Check whether the updated properties is correct.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<GridLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto layoutDirectionStr = layoutProperty->GetGridDirectionStr();
    EXPECT_EQ(layoutDirectionStr, GRID_DIRECTION_COLUMN_REVERSE);

    /**
     * @tc.steps: step6. Get grid EventHub to call related function.
     * @tc.expected: step6. Check whether the related parameters is correct.
     */
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    ASSERT_NE(eventHub, nullptr);
    GestureEvent info;
    info.globalPoint_.SetX(1.0f);
    info.globalPoint_.SetY(1.0f);
    eventHub->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub->draggedIndex_, 0);
    EXPECT_EQ(eventHub->dragDropProxy_, nullptr);
    eventHub->HandleOnItemDragUpdate(info);
    EXPECT_EQ(eventHub->draggedIndex_, 0);
    EXPECT_EQ(eventHub->dragDropProxy_, nullptr);
    eventHub->HandleOnItemDragEnd(info);
    EXPECT_EQ(eventHub->draggedIndex_, 0);
    EXPECT_EQ(eventHub->dragDropProxy_, nullptr);
    eventHub->HandleOnItemDragCancel();
    EXPECT_EQ(eventHub->draggedIndex_, 0);
    EXPECT_EQ(eventHub->dragDropProxy_, nullptr);
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
HWTEST_F(GridPatternTestNg, GridTest008, TestSize.Level1)
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
HWTEST_F(GridPatternTestNg, GridTest009, TestSize.Level1)
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
HWTEST_F(GridPatternTestNg, GridTest010, TestSize.Level1)
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
HWTEST_F(GridPatternTestNg, GridTest011, TestSize.Level1)
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
HWTEST_F(GridPatternTestNg, GridTest012, TestSize.Level1)
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
HWTEST_F(GridPatternTestNg, GridTest013, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t itemCount = 9;
    constexpr double gridItemHeight = 300.0f;
    auto frameNode = TestScrollGrid(gridSize, gridItemHeight, 0, itemCount, -100.0f);
    EXPECT_FALSE(frameNode == nullptr);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    EXPECT_FALSE(gridPattern == nullptr);
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
HWTEST_F(GridPatternTestNg, GridTest014, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t itemCount = 9;
    constexpr double gridItemHeight = 300.0f;
    auto frameNode = TestScrollGrid(gridSize, gridItemHeight, 0, itemCount, -100.0f);
    EXPECT_FALSE(frameNode == nullptr);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    EXPECT_FALSE(gridPattern == nullptr);
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
HWTEST_F(GridPatternTestNg, GridTest015, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t itemCount = 9;
    constexpr double gridItemHeight = 300.0f;
    auto frameNode = TestScrollGrid(gridSize, gridItemHeight, 0, itemCount, -100.0f);
    EXPECT_FALSE(frameNode == nullptr);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    EXPECT_FALSE(gridPattern == nullptr);
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
HWTEST_F(GridPatternTestNg, GridTest016, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t itemCount = 9;
    constexpr double gridItemHeight = 300.0f;
    auto frameNode = TestScrollGrid(gridSize, gridItemHeight, 0, itemCount, -100.0f, 10);
    EXPECT_FALSE(frameNode == nullptr);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    EXPECT_FALSE(gridPattern == nullptr);
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
HWTEST_F(GridPatternTestNg, GridTest017, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t itemCount = 9;
    constexpr double gridItemHeight = 300.0f;
    // scroll to show index 0-8
    auto frameNode = TestScrollGrid(gridSize, gridItemHeight, 0, itemCount, -100.0f, 10);

    // scroll to index 9
    EXPECT_FALSE(frameNode == nullptr);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    EXPECT_FALSE(gridPattern == nullptr);
    gridPattern->UpdateStartIndex(9);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.UpdateIllegalSelfIdealSizeWithCheck(gridSize);
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(9, false)->IsActive());
    EXPECT_FALSE(layoutWrapper->GetOrCreateChildByIndex(0, false)->IsActive());

    // save current grid info to grid pattern for next operation
    DirtySwapConfig config { false, false, false, false };
    auto layoutAlgorithmWrapper = layoutWrapper->GetLayoutAlgorithm();
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
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
HWTEST_F(GridPatternTestNg, GridTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GridTestProperty and set properties of grid.
     */
    GridTestProperty gridTestProperty;
    gridTestProperty.rowsTemplate = std::make_optional("1fr 1fr 1fr");
    gridTestProperty.columnsTemplate = std::make_optional("1fr 1fr");
    gridTestProperty.rowsGap = std::make_optional(GRID_ROWS_GAP);
    gridTestProperty.columnsGap = std::make_optional(GRID_COLUMNS_GAP);
    gridTestProperty.cachedCount = std::make_optional(GRID_CACHED_COUNT);
    gridTestProperty.gridDirection = std::make_optional(FlexDirection::ROW);
    gridTestProperty.maxCount = std::make_optional(GRID_MAX_COUNT);
    gridTestProperty.minCount = std::make_optional(GRID_MIN_COUNT);
    gridTestProperty.cellLength = std::make_optional(GRID_CELL_LENGTH);
    gridTestProperty.editable = std::make_optional(true);
    gridTestProperty.scrollBarMode = std::make_optional(static_cast<int32_t>(NG::DisplayMode::ON));
    gridTestProperty.scrollBarWidth = std::make_optional(SCROLL_BAR_WIDTH);
    gridTestProperty.scrollBarColor = std::make_optional(SCROLL_BAR_COLOR);

    /**
     * @tc.steps: step2. create grid frameNode and get GridLayoutProperty.
     * @tc.expected: step2. get GridLayoutProperty success.
     */
    RefPtr<FrameNode> frameNode = CreateGrid(gridTestProperty);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. compare grid properties and expected value.
     * @tc.expected: step3. grid properties equals expected value.
     */
    EXPECT_EQ(layoutProperty->GetRowsTemplate(), "1fr 1fr 1fr");
    EXPECT_EQ(layoutProperty->GetColumnsTemplate(), "1fr 1fr");
    EXPECT_EQ(layoutProperty->GetRowsGap(), GRID_ROWS_GAP);
    EXPECT_EQ(layoutProperty->GetColumnsGap(), GRID_COLUMNS_GAP);
    EXPECT_EQ(layoutProperty->GetCachedCount(), GRID_CACHED_COUNT);
    EXPECT_EQ(layoutProperty->GetGridDirection(), FlexDirection::ROW);
    EXPECT_EQ(layoutProperty->GetMaxCount(), GRID_MAX_COUNT);
    EXPECT_EQ(layoutProperty->GetMinCount(), GRID_MIN_COUNT);
    EXPECT_EQ(layoutProperty->GetCellLength(), GRID_CELL_LENGTH);
    EXPECT_EQ(layoutProperty->GetEditable(), true);

    auto paintProperty = frameNode->GetPaintProperty<ScrollablePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetScrollBarMode(), NG::DisplayMode::ON);
    EXPECT_EQ(paintProperty->GetScrollBarWidth(), StringUtils::StringToDimensionWithUnit(SCROLL_BAR_WIDTH));
    EXPECT_EQ(paintProperty->GetScrollBarColor(), Color::FromString(SCROLL_BAR_COLOR));

    /**
     * @tc.steps: step4. change grid row/column template properties to test illegal template.
     */
    gridTestProperty.rowsTemplate = std::make_optional(GRID_TEMPLATE_ILLEGAL);
    gridTestProperty.columnsTemplate = std::make_optional(GRID_TEMPLATE_ILLEGAL);

    /**
     * @tc.steps: step5. create grid frameNode and get GridLayoutProperty again.
     * @tc.expected: step5. get GridLayoutProperty success again.
     */
    frameNode = CreateGrid(gridTestProperty);
    ASSERT_NE(frameNode, nullptr);
    layoutProperty = frameNode->GetLayoutProperty<GridLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step6. compare grid properties and expected value after change.
     * @tc.expected: step6. grid properties equals expected value after change.
     */
    EXPECT_EQ(layoutProperty->GetRowsTemplate(), "");
    EXPECT_EQ(layoutProperty->GetColumnsTemplate(), "");
}

/**
 * @tc.name: GridTest019
 * @tc.desc: Test function of grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create grid.
     */
    GridModelNG grid;
    RefPtr<ScrollControllerBase> positionController = grid.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = grid.CreateScrollBarProxy();
    grid.Create(positionController, scrollBarProxy);
    /**
     * @tc.steps: step2. Set grid properties.
     */
    grid.SetMultiSelectable(true);
    grid.SetSupportAnimation(true);
    grid.SetOnScrollToIndex([](const BaseEventInfo*) {});

    /**
     * @tc.steps: step3. Get frameNode.
     * @tc.expected: step3. Check whether the updated properties and parameters are correct.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->multiSelectable_);
    EXPECT_TRUE(pattern->supportAnimation_);
}

/**
 * @tc.name: GridTest020
 * @tc.desc: Test all the properties of gridItem.
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gridItem and Set properties.
     */
    GridItemModelNG gridItem;
    gridItem.Create([](int32_t) {}, true);
    gridItem.SetRowStart(1);
    gridItem.SetRowEnd(2);
    gridItem.SetColumnStart(1);
    gridItem.SetColumnEnd(2);
    gridItem.SetForceRebuild(true);
    gridItem.SetSelectable(false);
    gridItem.SetOnSelect([](bool) {});

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
    EXPECT_NE(eventHub->onSelect_, nullptr);
}

/**
 * @tc.name: GridTest021
 * @tc.desc: Test GetInsertPosition func
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridTest021, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(itemCount);

    /**
     * @tc.steps: step2. Get frameNode, pattern, eventHub and RunMeasureAndLayout.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.steps: step3. Mock GetPaintRectWithTransform.
     */
    RectF gridRect(0.f, 0.f, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_CALL(*(AceType::RawPtr(AceType::DynamicCast<MockRenderContext>(frameNode->renderContext_))),
        GetPaintRectWithTransform())
        .WillRepeatedly(Return(gridRect));

    /**
     * @tc.steps: step4. Run GetInsertPosition func.
     * @tc.expected: Verify return value.
     */
    int32_t insertPosition = -1;
    insertPosition = eventHub->GetInsertPosition(DEVICE_WIDTH + 1, DEVICE_HEIGHT); // out of grid
    EXPECT_EQ(insertPosition, -1);
    insertPosition = -1;
    insertPosition = eventHub->GetInsertPosition(0.f, 0.f); // 0, 0
    EXPECT_EQ(insertPosition, 0);
    insertPosition = -1;
    insertPosition = eventHub->GetInsertPosition(90.f, 50.f); // first item
    EXPECT_EQ(insertPosition, 0);
    insertPosition = -1;
    insertPosition = eventHub->GetInsertPosition(360.f, 50.f); // between the second and third
    EXPECT_EQ(insertPosition, 1);
    insertPosition = -1;
    insertPosition = eventHub->GetInsertPosition(360.f, 100.f); // between the 2nd, 3rd, 6th, 7th
    EXPECT_EQ(insertPosition, 1);
    insertPosition = -1;
    insertPosition = eventHub->GetInsertPosition(180.f, 300.f); // in grid but not on item
    EXPECT_EQ(insertPosition, itemCount);
    insertPosition = -1;
    pattern->GetGridLayoutInfo().currentRect_ = RectF(0.f, 0.f, 100.f, 100.f); // on currentRect_
    insertPosition = eventHub->GetInsertPosition(50.f, 50.f);
    EXPECT_EQ(insertPosition, 0);
}

/**
 * @tc.name: GridTest022
 * @tc.desc: Test GetFrameNodeChildSize func
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridTest022, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(itemCount);

    /**
     * @tc.steps: step2. Get frameNode, accessibility and RunMeasureAndLayout.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RunMeasureAndLayout(frameNode);
    EXPECT_EQ(eventHub->GetFrameNodeChildSize(), itemCount);
}

/**
 * @tc.name: GridTest023
 * @tc.desc: Test positionController func
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridTest023, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(itemCount);

    /**
     * @tc.steps: step2. Get frameNode, accessibility and RunMeasureAndLayout.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.steps: step2. Test positionController_ func.
     * @tc.expected: Verify return value.
     */
    auto controller = pattern->positionController_;
    controller->JumpTo(1, 0);
    auto layoutInfo = pattern->GetGridLayoutInfo();
    EXPECT_EQ(layoutInfo.jumpIndex_, 1);
    controller->AnimateTo(Dimension(GRID_POSITION, DimensionUnit::PX), GRID_DURATION, Curves::LINEAR);
    EXPECT_NE(pattern->animator_, nullptr);
    Offset currentOffset = controller->GetCurrentOffset();
    EXPECT_EQ(currentOffset, Offset(0, 0));
    layoutInfo.axis_ = Axis::HORIZONTAL;
    currentOffset = controller->GetCurrentOffset();
    EXPECT_EQ(currentOffset, Offset(0, 0));
}

/**
 * @tc.name: GridTest024
 * @tc.desc: Test GetInsertPosition func
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridTest024, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(itemCount);

    /**
     * @tc.steps: step2. Get something and RunMeasureAndLayout.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.steps: step2. Test GetInsertPosition func.
     * @tc.expected: Verify return value.
     */
    pattern->gridLayoutInfo_.currentRect_ = RectF(0, 0, 100, 100);
    pattern->gridLayoutInfo_.currentMovingItemPosition_ = 1;
    int32_t insertPosition = pattern->GetInsertPosition(50.f, 50.f);
    EXPECT_EQ(insertPosition, 1);
    insertPosition = pattern->GetInsertPosition(200.f, 200.f);
    EXPECT_EQ(insertPosition, -1);
}

/**
 * @tc.name: GridAccessibilityTest001
 * @tc.desc: Test Grid Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridAccessibilityTest001, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(itemCount);

    /**
     * @tc.steps: step2. Get frameNode, accessibility and RunMeasureAndLayout.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto accessibility = frameNode->GetAccessibilityProperty<GridAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.steps: step3. Run accessibility func.
     * @tc.expected: Verify return value.
     */
    EXPECT_TRUE(accessibility->IsScrollable());
    EXPECT_FALSE(accessibility->IsEditable());
    EXPECT_EQ(accessibility->GetBeginIndex(), 0);
    EXPECT_EQ(accessibility->GetCurrentIndex(), 0);
    EXPECT_EQ(accessibility->GetEndIndex(), itemCount - 1);
    EXPECT_EQ(accessibility->GetCollectionItemCounts(), itemCount);

    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->multiSelectable_ = true;
    AceCollectionInfo info = accessibility->GetCollectionInfo();
    EXPECT_EQ(info.rows, 2);
    EXPECT_EQ(info.columns, 4);
    EXPECT_EQ(info.selectMode, 1);

    pattern->gridLayoutInfo_.reachStart_ = false;
    pattern->gridLayoutInfo_.reachEnd_ = false;

    accessibility->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibility->GetSupportAction();
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
HWTEST_F(GridPatternTestNg, GridAccessibilityTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create grid without gridItem.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);

    /**
     * @tc.steps: step2. Get frameNode, accessibility and RunMeasureAndLayout.
     * @tc.expected: Verify return value.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto accessibility = frameNode->GetAccessibilityProperty<GridAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    RunMeasureAndLayout(frameNode);
    AceCollectionInfo info = accessibility->GetCollectionInfo();
    EXPECT_EQ(info.rows, 0);
    EXPECT_EQ(info.columns, 0);
    EXPECT_EQ(info.selectMode, 0);
}

/**
 * @tc.name: GridAccessibilityTest003
 * @tc.desc: Test GridItem Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridAccessibilityTest003, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(itemCount);

    /**
     * @tc.steps: step2. Get frameNode, accessibility and RunMeasureAndLayout.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.steps: step3. Get itemFrameNode, itemAccessibility.
     */
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(1));
    ASSERT_NE(itemFrameNode, nullptr);
    auto itemAccessibility = itemFrameNode->GetAccessibilityProperty<GridItemAccessibilityProperty>();
    ASSERT_NE(itemAccessibility, nullptr);

    /**
     * @tc.steps: step3. Run itemAccessibility func.
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
HWTEST_F(GridPatternTestNg, GridSelectTest001, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModel.SetMultiSelectable(true);
    CreateGridItem(itemCount);

    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. RunMeasureAndLayout and set MouseButton::LEFT_BUTTON.
     */
    RunMeasureAndLayout(frameNode);
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);

    /**
     * @tc.steps: step4. Click the (0, 0) point of firstItem.
     * @tc.expected: item not selected on MouseAction::PRESS.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0.f, 0.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    RefPtr<GridItemPattern> firstItemPattern = GetItemPattern(frameNode, 0);
    EXPECT_FALSE(firstItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE); // Release the mouse to deselect.
    pattern->HandleMouseEventWithoutKeyboard(info);
}

/**
 * @tc.name: GridSelectTest002
 * @tc.desc: Test mouse box selection, PRESS, MOVE and RELEASE the mouse
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridSelectTest002, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;
    const Offset LEFT_TOP = Offset(90.f, 50.f);
    const Offset LEFT_BOTTOM = Offset(90.f, 150.f);
    const Offset RIGHT_TOP = Offset(270.f, 50.f);
    const Offset RIGHT_BOTTOM = Offset(270.f, 150.f);

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModel.SetMultiSelectable(true);
    CreateGridItem(itemCount);

    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. RunMeasureAndLayout and set MouseButton::LEFT_BUTTON.
     */
    RunMeasureAndLayout(frameNode);
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);

    /**
     * @tc.steps: step4. Select (0, 0) - (284, 100) zone.
     * @tc.expected: The 1st, 2nd, 5th, 6th items are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0.f, 0.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(180.f, 100.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    RefPtr<GridItemPattern> firstItemPattern = GetItemPattern(frameNode, 0);
    EXPECT_TRUE(firstItemPattern->IsSelected());
    RefPtr<GridItemPattern> secondItemPattern = GetItemPattern(frameNode, 1);
    EXPECT_TRUE(secondItemPattern->IsSelected());
    RefPtr<GridItemPattern> fifthItemPattern = GetItemPattern(frameNode, 4);
    EXPECT_TRUE(fifthItemPattern->IsSelected());
    RefPtr<GridItemPattern> sixthItemPattern = GetItemPattern(frameNode, 5);
    EXPECT_TRUE(sixthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE); // Release the mouse to deselect.
    pattern->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step5. Select (90, 50) - (270, 150) zone, from the LEFT_TOP to the RIGHT_BOTTOM.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(LEFT_TOP);
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(RIGHT_BOTTOM);
    pattern->HandleMouseEventWithoutKeyboard(info);
    firstItemPattern = GetItemPattern(frameNode, 0);
    EXPECT_TRUE(firstItemPattern->IsSelected());
    secondItemPattern = GetItemPattern(frameNode, 1);
    EXPECT_TRUE(secondItemPattern->IsSelected());
    fifthItemPattern = GetItemPattern(frameNode, 4);
    EXPECT_TRUE(fifthItemPattern->IsSelected());
    sixthItemPattern = GetItemPattern(frameNode, 5);
    EXPECT_TRUE(sixthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step6. Select (90, 50) - (270, 150) zone, from the RIGHT_TOP to the LEFT_BOTTOM.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(RIGHT_TOP);
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(LEFT_BOTTOM);
    pattern->HandleMouseEventWithoutKeyboard(info);
    firstItemPattern = GetItemPattern(frameNode, 0);
    EXPECT_TRUE(firstItemPattern->IsSelected());
    secondItemPattern = GetItemPattern(frameNode, 1);
    EXPECT_TRUE(secondItemPattern->IsSelected());
    fifthItemPattern = GetItemPattern(frameNode, 4);
    EXPECT_TRUE(fifthItemPattern->IsSelected());
    sixthItemPattern = GetItemPattern(frameNode, 5);
    EXPECT_TRUE(sixthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step7. Select (90, 50) - (270, 150) zone, from the LEFT_BOTTOM to the RIGHT_TOP.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(LEFT_BOTTOM);
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(RIGHT_TOP);
    pattern->HandleMouseEventWithoutKeyboard(info);
    firstItemPattern = GetItemPattern(frameNode, 0);
    EXPECT_TRUE(firstItemPattern->IsSelected());
    secondItemPattern = GetItemPattern(frameNode, 1);
    EXPECT_TRUE(secondItemPattern->IsSelected());
    fifthItemPattern = GetItemPattern(frameNode, 4);
    EXPECT_TRUE(fifthItemPattern->IsSelected());
    sixthItemPattern = GetItemPattern(frameNode, 5);
    EXPECT_TRUE(sixthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step8. Select (90, 50) - (270, 150) zone, from the RIGHT_BOTTOM to the LEFT_TOP.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(RIGHT_BOTTOM);
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(LEFT_TOP);
    pattern->HandleMouseEventWithoutKeyboard(info);
    firstItemPattern = GetItemPattern(frameNode, 0);
    EXPECT_TRUE(firstItemPattern->IsSelected());
    secondItemPattern = GetItemPattern(frameNode, 1);
    EXPECT_TRUE(secondItemPattern->IsSelected());
    fifthItemPattern = GetItemPattern(frameNode, 4);
    EXPECT_TRUE(fifthItemPattern->IsSelected());
    sixthItemPattern = GetItemPattern(frameNode, 5);
    EXPECT_TRUE(sixthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEventWithoutKeyboard(info);
}

/**
 * @tc.name: GridSelectTest003
 * @tc.desc: Test gridItem selectable property and onSelect callback
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridSelectTest003, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModel.SetMultiSelectable(true);

    /**
     * @tc.steps: step2. Create gridItem.
     */
    bool isSixthItemSelected = false;
    auto selectCallback = [&isSixthItemSelected](bool) { isSixthItemSelected = true; };
    for (int32_t i = 0; i < itemCount; i++) {
        GridItemModelNG gridItemModel;
        gridItemModel.Create();
        SetHeight(Dimension(DEFAULT_ITEM_MAIN_SIZE));
        if (i == 1) {
            gridItemModel.SetSelectable(false);
        }
        if (i == 5) {
            gridItemModel.SetOnSelect(std::move(selectCallback));
        }
        ViewStackProcessor::GetInstance()->Pop();
    }

    /**
     * @tc.steps: step3. Get frameNode and pattern.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. RunMeasureAndLayout and set MouseButton::LEFT_BUTTON.
     */
    RunMeasureAndLayout(frameNode);
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);

    /**
     * @tc.steps: step5. Select (225, 50) - (315, 150) zone.
     * @tc.expected: The 2nd item is not selected but 6th item is selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(225.f, 50.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(315.f, 150.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    RefPtr<GridItemPattern> secondItemPattern = GetItemPattern(frameNode, 1);
    EXPECT_FALSE(secondItemPattern->IsSelected());
    RefPtr<GridItemPattern> sixthItemPattern = GetItemPattern(frameNode, 5);
    EXPECT_TRUE(sixthItemPattern->IsSelected());
    EXPECT_TRUE(isSixthItemSelected);
    info.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEventWithoutKeyboard(info);
}

/**
 * @tc.name: GridSelectTest004
 * @tc.desc: Test OnMouseSelectAll func
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridSelectTest004, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModel.SetMultiSelectable(true);
    CreateGridItem(itemCount);

    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. RunMeasureAndLayout and run OnMouseSelectAll func.
     * @tc.expected: All items are selected.
     */
    RunMeasureAndLayout(frameNode);
    pattern->OnMouseSelectAll();
    auto children = frameNode->GetChildren();
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
HWTEST_F(GridPatternTestNg, GridSelectTest005, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModel.SetMultiSelectable(true);
    CreateGridItem(itemCount);

    /**
     * @tc.steps: step2. Get something and RunMeasureAndLayout.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.steps: step5. Select (225, 50) - (315, 150) zone with RIGHT_BUTTON.
     * @tc.expected: The item is not selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::RIGHT_BUTTON); // Use RIGHT_BUTTON to select.
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(225.f, 50.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(315.f, 150.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    RefPtr<GridItemPattern> secondItemPattern = GetItemPattern(frameNode, 1);
    EXPECT_FALSE(secondItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step6. Select (225, 50) - (315, 150) zone and trigger other MouseAction.
     * @tc.expected: The item is still selected when trigger other MouseAction.
     */
    info.SetButton(MouseButton::LEFT_BUTTON); // Use RIGHT_BUTTON to select.
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(225.f, 50.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(315.f, 150.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    secondItemPattern = GetItemPattern(frameNode, 1);
    EXPECT_TRUE(secondItemPattern->IsSelected());
    info.SetAction(MouseAction::HOVER); // Trigger other MouseAction.
    pattern->HandleMouseEventWithoutKeyboard(info);
    EXPECT_TRUE(secondItemPattern->IsSelected());
}

/**
 * @tc.name: GridSelectTest006
 * @tc.desc: Test mouse right button click on selected item
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridSelectTest006, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;
    const Offset LEFT_TOP = Offset(90.f, 50.f);
    const Offset LEFT_BOTTOM = Offset(90.f, 150.f);
    const Offset RIGHT_TOP = Offset(270.f, 50.f);
    const Offset RIGHT_BOTTOM = Offset(270.f, 150.f);

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModel.SetMultiSelectable(true);
    CreateGridItem(itemCount);

    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. RunMeasureAndLayout and set MouseButton::LEFT_BUTTON.
     */
    RunMeasureAndLayout(frameNode);
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);

    /**
     * @tc.steps: step4. Select (0, 0) - (284, 100) zone.
     * @tc.expected: The 1st, 2nd, 5th, 6th items are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0.f, 0.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(180.f, 100.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    RefPtr<GridItemPattern> firstItemPattern = GetItemPattern(frameNode, 0);
    EXPECT_TRUE(firstItemPattern->IsSelected());
    RefPtr<GridItemPattern> secondItemPattern = GetItemPattern(frameNode, 1);
    EXPECT_TRUE(secondItemPattern->IsSelected());
    RefPtr<GridItemPattern> fifthItemPattern = GetItemPattern(frameNode, 4);
    EXPECT_TRUE(fifthItemPattern->IsSelected());
    RefPtr<GridItemPattern> sixthItemPattern = GetItemPattern(frameNode, 5);
    EXPECT_TRUE(sixthItemPattern->IsSelected());

    /**
     * @tc.steps: step5. Right click on (150.f, 50.f), in selected zone.
     * @tc.expected: The 1st item is still selected.
     */
    info.SetButton(MouseButton::RIGHT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(150.f, 50.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    EXPECT_TRUE(firstItemPattern->IsSelected());

    /**
     * @tc.steps: step6. Left click on (280.f, 100.f), out of selected zone.
     * @tc.expected: The 1st item is not selected.
     */
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetLocalLocation(Offset(280.f, 100.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    EXPECT_FALSE(firstItemPattern->IsSelected());
}

/**
 * @tc.name: GridDragTest001
 * @tc.desc: Verify drag func
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridDragTest001, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModel.SetEditable(true);
    CreateGridItem(itemCount);

    /**
     * @tc.steps: step2. SetOnItemDragStart to get customNode.
     */
    auto onItemDragStart = [](const ItemDragInfo&, int32_t) {
        auto dragItem = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
        return AceType::DynamicCast<UINode>(dragItem);
    };
    gridModel.SetOnItemDragStart(onItemDragStart);

    /**
     * @tc.steps: step3. Get frameNode and eventHub and RunMeasureAndLayout.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RunMeasureAndLayout(frameNode);
    eventHub->onItemDragStart_ = onItemDragStart;

    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
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
     * @tc.steps: step4. RunMeasureAndLayout and set info.
     */
    GestureEvent info;
    Point globalPoint = Point(270.f, 50.f); // Point at the second item.
    info.SetGlobalPoint(globalPoint);

    /**
     * @tc.steps: step5. Trigger HandleOnItemDragStart.
     * @tc.expected: Verify some values of the drag.
     */
    HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub->draggedIndex_, 1);
    EXPECT_NE(eventHub->dragDropProxy_, nullptr);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(1));
    EXPECT_EQ(eventHub->draggingItem_, itemFrameNode);

    /**
     * @tc.steps: step6. Trigger HandleOnItemDragUpdate, HandleOnItemDragEnd.
     * @tc.expected: Verify some values of the drag.
     */
    HandleOnItemDragUpdate(info);
    HandleOnItemDragEnd(info);
    EXPECT_EQ(eventHub->draggedIndex_, 0);
    EXPECT_EQ(eventHub->dragDropProxy_, nullptr);
    EXPECT_EQ(eventHub->draggingItem_, nullptr);

    /**
     * @tc.steps: step7. Trigger HandleOnItemDragStart, HandleOnItemDragUpdate, HandleOnItemDragEnd.
     * @tc.expected: Verify some values of the drag.
     */
    HandleOnItemDragStart(info);
    HandleOnItemDragUpdate(info);
    HandleOnItemDragCancel();
    EXPECT_EQ(eventHub->draggedIndex_, 0);
    EXPECT_EQ(eventHub->dragDropProxy_, nullptr);
    EXPECT_EQ(eventHub->draggingItem_, nullptr);
}

/**
 * @tc.name: GridDragTest002
 * @tc.desc: Verify drag func
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridDragTest002, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModel.SetEditable(true);
    CreateGridItem(itemCount);

    /**
     * @tc.steps: step2. Get frameNode, pattern and eventHub and RunMeasureAndLayout.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.steps: step3. Run FireOnItemDragEnter, FireOnItemDragLeave.
     * @tc.expected: Verify GetOriginalIndex.
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(0.f);
    dragInfo.SetY(0.f);
    eventHub->FireOnItemDragEnter(dragInfo);
    eventHub->FireOnItemDragLeave(dragInfo, -1);
    EXPECT_EQ(pattern->GetOriginalIndex(), itemCount);

    /**
     * @tc.steps: step4. MoveItemsForward.
     * @tc.expected: Verify GetOriginalIndex.
     */
    eventHub->FireOnItemDragEnter(dragInfo);
    eventHub->FireOnItemDragMove(dragInfo, 1, 5);
    EXPECT_EQ(pattern->GetOriginalIndex(), 5);
    eventHub->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_EQ(pattern->GetOriginalIndex(), -1);

    /**
     * @tc.steps: step5. MoveItemsBack.
     * @tc.expected: Verify GetOriginalIndex.
     */
    eventHub->FireOnItemDragEnter(dragInfo);
    eventHub->FireOnItemDragMove(dragInfo, 5, 2);
    EXPECT_EQ(pattern->GetOriginalIndex(), 2);
    eventHub->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_EQ(pattern->GetOriginalIndex(), -1);

    /**
     * @tc.steps: step6. Move something to Grid.
     * @tc.expected: Verify GetOriginalIndex.
     */
    eventHub->FireOnItemDragEnter(dragInfo);
    eventHub->FireOnItemDragMove(dragInfo, -1, 2);
    EXPECT_EQ(pattern->GetOriginalIndex(), 2);
    eventHub->FireOnItemDrop(dragInfo, -1, 1, true);
    EXPECT_EQ(pattern->GetOriginalIndex(), -1);
}

/**
 * @tc.name: GridDragTest003
 * @tc.desc: Verify drag func
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridDragTest003, TestSize.Level1)
{
    constexpr int32_t itemCount = 8;

    /**
     * @tc.steps: step1. Create grid, Set 4 columns and SetMultiSelectable.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController = gridModel.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModel.CreateScrollBarProxy();
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModel.SetEditable(true);
    gridModel.SetOnItemDragEnter([](const ItemDragInfo) {});
    gridModel.SetOnItemDragMove([](const ItemDragInfo&, int32_t, int32_t) {});
    gridModel.SetOnItemDragLeave([](const ItemDragInfo&, int32_t) {});
    gridModel.SetOnItemDrop([](const ItemDragInfo&, int32_t, int32_t, bool) {});
    CreateGridItem(itemCount);

    /**
     * @tc.steps: step2. Get frameNode, pattern and eventHub and RunMeasureAndLayout.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.steps: step3. Run FireOnItemDragEnter, FireOnItemDragLeave.
     * @tc.expected: Verify GetOriginalIndex.
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(0.f);
    dragInfo.SetY(0.f);
    eventHub->FireOnItemDragEnter(dragInfo);
    eventHub->FireOnItemDragLeave(dragInfo, -1);
    EXPECT_EQ(pattern->GetOriginalIndex(), itemCount);
    pattern->ClearDragState();

    /**
     * @tc.steps: step4. MoveItemsForward.
     * @tc.expected: Verify GetOriginalIndex.
     */
    eventHub->FireOnItemDragEnter(dragInfo);
    eventHub->FireOnItemDragMove(dragInfo, 1, 5);
    EXPECT_EQ(pattern->GetOriginalIndex(), 5);
    eventHub->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_EQ(pattern->GetOriginalIndex(), -1);

    /**
     * @tc.steps: step5. MoveItemsBack.
     * @tc.expected: Verify GetOriginalIndex.
     */
    eventHub->FireOnItemDragEnter(dragInfo);
    eventHub->FireOnItemDragMove(dragInfo, 5, 2);
    EXPECT_EQ(pattern->GetOriginalIndex(), 2);
    eventHub->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_EQ(pattern->GetOriginalIndex(), -1);
}

/**
 * @tc.name: GridFocusStepTest001
 * @tc.desc: Test GetNextFocusNode func
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridFocusStepTest001, TestSize.Level1)
{
    /**
     *  ___180__360__540__720
     * |____|____|____|____|100
     * |____|____|____|____|200
     * |____|____|          300
     */
    constexpr int32_t itemCount = 10;

    /**
     * @tc.steps: step1. Create Grid, Set 4 columns.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController;
    RefPtr<ScrollProxy> scrollBarProxy;
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");

    /**
     * @tc.steps: step2. Create focusable GridItem.
     */
    CreateGridItemWithButton(itemCount);

    /**
     * @tc.steps: step3. Get frameNode and RunMeasureAndLayout.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.steps: step4. GetNextFocusNode from left_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    RefPtr<FocusHub> currentFocusNode = GetItemFocusHub(frameNode, 0);
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern->GetNextFocusNode(FocusStep::NONE, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::LEFT, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::UP, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::RIGHT, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 1));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::DOWN, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 4));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::LEFT_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::UP_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::RIGHT_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 3));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::DOWN_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);

    /**
     * @tc.steps: step5. GetNextFocusNode from right_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentFocusNode = GetItemFocusHub(frameNode, 3);
    currentFocusNode->RequestFocusImmediately();
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::NONE, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::LEFT, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 2));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::UP, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::RIGHT, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 4));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::DOWN, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 7));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::LEFT_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 0));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::UP_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::RIGHT_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::DOWN_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);

    /**
     * @tc.steps: step6. GetNextFocusNode from left_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentFocusNode = GetItemFocusHub(frameNode, 8);
    currentFocusNode->RequestFocusImmediately();
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::NONE, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::LEFT, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 7));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::UP, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 4));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::RIGHT, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 9));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::DOWN, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::LEFT_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::UP_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::RIGHT_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 9));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::DOWN_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);

    /**
     * @tc.steps: step7. GetNextFocusNode from right_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentFocusNode = GetItemFocusHub(frameNode, 9);
    currentFocusNode->RequestFocusImmediately();
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::NONE, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::LEFT, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 8));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::UP, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 5));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::RIGHT, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::DOWN, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::LEFT_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 8));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::UP_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::RIGHT_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::DOWN_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);

    /**
     * @tc.steps: step8. GetNextFocusNode from middle.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentFocusNode = GetItemFocusHub(frameNode, 5);
    currentFocusNode->RequestFocusImmediately();
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::NONE, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::LEFT, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 4));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::UP, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 1));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::RIGHT, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 6));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::DOWN, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 9));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::LEFT_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 4));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::UP_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::RIGHT_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 7));
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::DOWN_END, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, nullptr);
}

/**
 * @tc.name: GridFocusStepTest002
 * @tc.desc: Test GetNextFocusNode func with scrolled Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, GridFocusStepTest002, TestSize.Level1)
{
    constexpr int32_t itemCount = 10;

    /**
     * @tc.steps: step1. Create Grid, Set 4 columns.
     */
    GridModelNG gridModel;
    RefPtr<ScrollControllerBase> positionController;
    RefPtr<ScrollProxy> scrollBarProxy;
    gridModel.Create(positionController, scrollBarProxy);
    gridModel.SetColumnsTemplate("1fr 1fr 1fr 1fr");

    /**
     * @tc.steps: step2. Create focusable GridItem.
     */
    CreateGridItemWithButton(itemCount);

    /**
     * @tc.steps: step3. Get frameNode and RunMeasureAndLayout.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.steps: step4. Set Grid height to 200.
     */
    RefPtr<LayoutWrapper> gridLayoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEVICE_WIDTH, 200.f };
    LayoutConstraint.percentReference = { DEVICE_WIDTH, 200.f };
    LayoutConstraint.selfIdealSize = { DEVICE_WIDTH, 200.f };
    LayoutConstraint.maxSize = { DEVICE_WIDTH, 200.f };
    gridLayoutWrapper->Measure(LayoutConstraint);
    gridLayoutWrapper->Layout();

    /**
     * @tc.steps: step5. GetNextFocusNode from 8th item.
     * @tc.expected: Grid jump up.
     */
    RefPtr<FocusHub> currentFocusNode = GetItemFocusHub(frameNode, 7);
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern->GetNextFocusNode(FocusStep::RIGHT, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 8));
    EXPECT_EQ(pattern->gridLayoutInfo_.jumpIndex_, 8);

    /**
     * @tc.steps: step6. GetNextFocusNode from 5th item.
     * @tc.expected: Grid jump Down.
     */
    currentFocusNode = GetItemFocusHub(frameNode, 4);
    currentFocusNode->RequestFocusImmediately();
    nextFocusNode = pattern->GetNextFocusNode(FocusStep::LEFT, currentFocusNode).Upgrade();
    EXPECT_EQ(nextFocusNode, GetItemFocusHub(frameNode, 3));
    EXPECT_EQ(pattern->gridLayoutInfo_.jumpIndex_, 3);
}
} // namespace OHOS::Ace::NG
