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

#define private public
#include <cstdint>
#include <memory>

#include "gtest/gtest.h"

#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/pipeline/base/constants.h"

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
} // namespace

class GridTestNg : public testing::Test {};

/**
 * @tc.name: GridTest001
 * @tc.desc: Fill all items to grid with fixed row and column
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create grid node and initialize width, height, properties.
     */
    RefPtr<V2::GridPositionController> positionController;
    RefPtr<ScrollBarProxy> scrollBarProxy;
    GridModelNG grid;
    grid.Create(positionController, scrollBarProxy);
    std::unique_ptr<ViewAbstractModel> instance = std::make_unique<ViewAbstractModelNG>();
    auto height = StringUtils::StringToDimensionWithUnit("70%");
    instance->SetHeight(height);
    auto width = StringUtils::StringToDimensionWithUnit("90%");
    instance->SetWidth(width);
    grid.SetColumnsTemplate("1fr 1fr 1fr");
    grid.SetRowsTemplate("1fr 1fr 1fr");

    /**
     * @tc.steps: step2. Create the child nodes gridItem and text of the grid, and set the width and height of text.
     */
    GridItemModelNG gridItem;
    TextModelNG text;
    const int32_t ITEM_COUNT = 9;
    for (int32_t i = 0; i < ITEM_COUNT; ++i) {
        gridItem.Create();
        text.Create("test");
        auto textHeight = StringUtils::StringToDimensionWithUnit("50%");
        instance->SetHeight(textHeight);
        auto textWidth = StringUtils::StringToDimensionWithUnit("100%");
        instance->SetWidth(textWidth);
        ViewStackProcessor::GetInstance()->Pop();
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
    OptionalSizeF size;
    constexpr float DEFAULT_WIDTH = 800.0f;
    size.SetWidth(DEFAULT_WIDTH);
    constraint.UpdateIllegalSelfIdealSizeWithCheck(size);

    /**
     * @tc.steps: step4. Call the measure and layout function of grid to calculate the size and layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();

    /**
     * @tc.steps: step5. When setting fixed rows and columns, check the status of child nodes in the grid.
     * @tc.expected: step3. All child nodes are active.
     */
    for (int32_t i = 0; i < ITEM_COUNT; ++i) {
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
    /**
     * @tc.steps: step1. Create grid node and initialize width, height, properties.
     */
    GridModelNG grid;
    RefPtr<V2::GridPositionController> positionController;
    RefPtr<ScrollBarProxy> scrollBarProxy;
    grid.Create(positionController, scrollBarProxy);
    std::unique_ptr<ViewAbstractModel> instance = std::make_unique<ViewAbstractModelNG>();
    auto height = StringUtils::StringToDimensionWithUnit("70%");
    instance->SetHeight(height);
    auto width = StringUtils::StringToDimensionWithUnit("90%");
    instance->SetWidth(width);

    /**
     * @tc.steps: step2. initialize ColumnsTemplate, ColumnsGap and MultiSelectable properties.
     */
    grid.SetColumnsTemplate("1fr 1fr");
    grid.SetColumnsGap(GRID_COLUMNS_GAP);
    grid.SetMultiSelectable(true);

    /**
     * @tc.steps: step2. Create the child nodes gridItem and text of the grid, and set the width and height of text.
     */
    TextModelNG text;
    GridItemModelNG gridItem;
    const int32_t ITEM_COUNT = 10;
    for (int32_t i = 0; i < ITEM_COUNT; ++i) {
        gridItem.Create();
        text.Create("test");
        auto textHeight = StringUtils::StringToDimensionWithUnit("50%");
        instance->SetHeight(textHeight);
        auto textWidth = StringUtils::StringToDimensionWithUnit("100%");
        instance->SetWidth(textWidth);
        ViewStackProcessor::GetInstance()->Pop();
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
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);

    /**
     * @tc.steps: step4. Call the measure and layout function of grid to calculate the size and layout.
     * @tc.expected: step4. Check size after layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    /**
     * @tc.steps: step6. Set different KeyEvent to verify the OnKeyEvent function.
     * @tc.expected: step6. Check whether the return value is correct.
     */
    auto pattern = frameNode->GetPattern<GridPattern>();
    KeyEvent event;
    auto ret = pattern->OnKeyEvent(event);
    EXPECT_EQ(ret, false);
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_PAGE_DOWN;
    ret = pattern->OnKeyEvent(event);
    EXPECT_EQ(ret, false);
    event.code = KeyCode::KEY_PAGE_UP;
    ret = pattern->OnKeyEvent(event);
    EXPECT_EQ(ret, false);
    ret = pattern->HandleDirectionKey(event.code);
    EXPECT_EQ(ret, false);

    event.code = KeyCode::KEY_DPAD_UP;
    ret = pattern->OnKeyEvent(event);
    EXPECT_EQ(ret, false);
    event.code = KeyCode::KEY_DPAD_DOWN;
    ret = pattern->OnKeyEvent(event);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: GridTest003
 * @tc.desc: Set fixed rows only Fill all items in the grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create grid node and initialize width, height, properties.
     */
    GridModelNG grid;
    RefPtr<ScrollBarProxy> scrollBarProxy;
    RefPtr<V2::GridPositionController> positionController;
    grid.Create(positionController, scrollBarProxy);
    std::unique_ptr<ViewAbstractModel> instance = std::make_unique<ViewAbstractModelNG>();
    auto height = StringUtils::StringToDimensionWithUnit("70%");
    instance->SetHeight(height);
    auto width = StringUtils::StringToDimensionWithUnit("90%");
    instance->SetWidth(width);

    /**
     * @tc.steps: step2. initialize RowsTemplate, RowsGap and MultiSelectable properties.
     */
    grid.SetRowsTemplate("1fr 1fr");
    grid.SetRowsGap(GRID_ROWS_GAP);
    grid.SetMultiSelectable(true);

    /**
     * @tc.steps: step3. Create the child nodes gridItem and text of the grid, and set the width and height of text.
     */
    TextModelNG text;
    GridItemModelNG gridItem;
    const int32_t ITEM_COUNT = 10;
    for (int32_t i = 0; i < ITEM_COUNT; ++i) {
        gridItem.Create();
        text.Create("test");
        auto textHeight = StringUtils::StringToDimensionWithUnit("50%");
        instance->SetHeight(textHeight);
        auto textWidth = StringUtils::StringToDimensionWithUnit("100%");
        instance->SetWidth(textWidth);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->Pop();
    }

    /**
     * @tc.steps: step4. Get grid frameNode and set layoutConstraint.
     * @tc.expected: step4. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);

    /**
     * @tc.steps: step5. Call the measure and layout function of grid to calculate the size and layout.
     * @tc.expected: step5. Check size after layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    /**
     * @tc.steps: step6. get grid pattern to call OnModifyDone function.
     * @tc.expected: step6. Check whether the updated properties and parameters are correct.
     */
    auto pattern = frameNode->GetPattern<GridPattern>();
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->multiSelectable_, true);
    EXPECT_EQ(pattern->isMouseEventInit_, true);
    EXPECT_EQ(pattern->isConfigScrollable_, true);

    /**
     * @tc.steps: step7. Call the AddScrollEvent function to add a scroll position callback event.
     * @tc.expected: step7. Call and check the return value of the callback function.
     */
    pattern->AddScrollEvent();
    EXPECT_NE(pattern->scrollableEvent_, nullptr);
    auto callback = pattern->scrollableEvent_->GetScrollPositionCallback();
    EXPECT_NE(callback, nullptr);
    auto ret = callback(GRID_SCROLL_OFFSET, SCROLL_FROM_START);
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step8. When isConfigScrollable_ is false, call related functions.
     * @tc.expected: step8. Check the return value of the related function.
     */
    pattern->isConfigScrollable_ = false;
    ret = pattern->AnimateTo(GRID_POSITION, GRID_DURATION, Curves::LINEAR);
    EXPECT_EQ(ret, false);
    ret = pattern->UpdateCurrentOffset(GRID_SCROLL_OFFSET, SCROLL_FROM_UPDATE);
    EXPECT_EQ(ret, false);
    ret = pattern->UpdateStartIndex(1.0);
    EXPECT_EQ(ret, false);

    /**
     * @tc.steps: step9. When isConfigScrollable_ is true, call AnimateTo functions.
     * @tc.expected: step9. Check the return value and related parameters.
     */
    pattern->ScrollPage(false);
    pattern->isConfigScrollable_ = true;
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
HWTEST_F(GridTestNg, GridTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create grid node and initialize width, height, properties.
     */
    GridModelNG grid;
    RefPtr<ScrollBarProxy> scrollBarProxy;
    auto positionController = grid.CreatePositionController();
    grid.Create(positionController, scrollBarProxy);
    std::unique_ptr<ViewAbstractModel> instance = std::make_unique<ViewAbstractModelNG>();
    auto height = StringUtils::StringToDimensionWithUnit("70%");
    instance->SetHeight(height);
    auto width = StringUtils::StringToDimensionWithUnit("90%");
    instance->SetWidth(width);

    /**
     * @tc.steps: step2. initialize properties such as ColumnsGap, RowsGap, LayoutDirection, MaxCount, MinCount,
     * CellLength and MultiSelectable.
     */
    grid.SetColumnsGap(GRID_COLUMNS_GAP);
    grid.SetRowsGap(GRID_ROWS_GAP);
    grid.SetMultiSelectable(true);
    grid.SetLayoutDirection(FlexDirection::ROW);
    grid.SetMaxCount(GRID_MAX_COUNT);
    grid.SetMinCount(GRID_MIN_COUNT);
    grid.SetCellLength(GRID_CELL_LENGTH);

    /**
     * @tc.steps: step3. Create the child nodes gridItem and text of the grid, and set the width and height of text.
     */
    TextModelNG text;
    GridItemModelNG gridItem;
    const int32_t ITEM_COUNT = 10;
    for (int32_t i = 0; i < ITEM_COUNT; ++i) {
        gridItem.Create();
        text.Create("test");
        auto textHeight = StringUtils::StringToDimensionWithUnit("50%");
        instance->SetHeight(textHeight);
        auto textWidth = StringUtils::StringToDimensionWithUnit("100%");
        instance->SetWidth(textWidth);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->Pop();
    }

    /**
     * @tc.steps: step4. Get grid frameNode and set layoutConstraint.
     * @tc.expected: step4. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);

    /**
     * @tc.steps: step5. Call the measure and layout function of grid to calculate the size and layout.
     * @tc.expected: step5. Check size after layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    /**
     * @tc.steps: step6. Get grid layout properties.
     * @tc.expected: step6. Check whether the updated properties is correct.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<GridLayoutProperty>();
    auto layoutDirectionStr = layoutProperty->GetLayoutDirectionStr();
    EXPECT_EQ(layoutDirectionStr, GRID_DIRECTION_ROW);

    /**
     * @tc.steps: step7. Get the pattern to call the related functions in the positionController.
     */
    auto pattern = frameNode->GetPattern<GridPattern>();
    EXPECT_NE(pattern->positionController_, nullptr);

    /**
     * @tc.steps: step8. When Axis is VERTICAL and ScrollEdgeType is SCROLL_TOP, call the related functions in
     * positionController.
     * @tc.expected: step8. Check whether the return value is correct.
     */
    pattern->gridLayoutInfo_.axis_ = Axis::VERTICAL;
    ScrollEdgeType scrollEdgeType = ScrollEdgeType::SCROLL_TOP;
    pattern->positionController_->ScrollToEdge(scrollEdgeType, true);
    pattern->positionController_->ScrollPage(true, true);
    auto axis = pattern->positionController_->GetScrollDirection();
    EXPECT_EQ(axis, Axis::VERTICAL);

    /**
     * @tc.steps: step9. When Axis is HORIZONTAL and ScrollEdgeType is SCROLL_RIGHT, call the related functions in
     * positionController.
     * @tc.expected: step9. Check whether the return value is correct.
     */
    pattern->gridLayoutInfo_.axis_ = Axis::HORIZONTAL;
    scrollEdgeType = ScrollEdgeType::SCROLL_RIGHT;
    pattern->positionController_->ScrollToEdge(scrollEdgeType, true);
    pattern->positionController_->ScrollPage(true, true);
    axis = pattern->positionController_->GetScrollDirection();
    EXPECT_EQ(axis, Axis::HORIZONTAL);

    /**
     * @tc.steps: step10. When Axis is NONE, call the related functions in positionController.
     * @tc.expected: step10. Check whether the return value is correct.
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
HWTEST_F(GridTestNg, GridTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create grid node and initialize width, height, properties.
     */
    GridModelNG grid;
    RefPtr<ScrollBarProxy> scrollBarProxy;
    auto positionController = grid.CreatePositionController();
    grid.Create(positionController, scrollBarProxy);
    std::unique_ptr<ViewAbstractModel> instance = std::make_unique<ViewAbstractModelNG>();
    auto height = StringUtils::StringToDimensionWithUnit("70%");
    instance->SetHeight(height);
    auto width = StringUtils::StringToDimensionWithUnit("90%");
    instance->SetWidth(width);

    /**
     * @tc.steps: step2. initialize properties such as ColumnsGap, RowsGap, LayoutDirection, MaxCount, MinCount,
     * ScrollBarMode, CellLength and MultiSelectable.
     */
    grid.SetColumnsGap(GRID_COLUMNS_GAP);
    grid.SetRowsGap(GRID_ROWS_GAP);
    grid.SetMultiSelectable(true);
    grid.SetLayoutDirection(FlexDirection::ROW_REVERSE);
    grid.SetMaxCount(GRID_MAX_COUNT);
    grid.SetMinCount(GRID_MIN_COUNT);
    grid.SetCellLength(GRID_CELL_LENGTH);
    grid.SetScrollBarMode(static_cast<int32_t>(NG::DisplayMode::AUTO));

    /**
     * @tc.steps: step3. Create the child nodes gridItem and text of the grid, and set the width and height of text.
     */
    TextModelNG text;
    GridItemModelNG gridItem;
    const int32_t ITEM_COUNT = 10;
    for (int32_t i = 0; i < ITEM_COUNT; ++i) {
        gridItem.Create();
        text.Create("test");
        auto textHeight = StringUtils::StringToDimensionWithUnit("50%");
        instance->SetHeight(textHeight);
        auto textWidth = StringUtils::StringToDimensionWithUnit("100%");
        instance->SetWidth(textWidth);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->Pop();
    }

    /**
     * @tc.steps: step4. Get grid frameNode and set layoutConstraint.
     * @tc.expected: step4. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);

    /**
     * @tc.steps: step5. Call the measure and layout function of grid to calculate the size and layout.
     * @tc.expected: step5. Check size after layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    /**
     * @tc.steps: step6. Get grid layout properties.
     * @tc.expected: step6. Check whether the updated properties is correct.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<GridLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto layoutDirectionStr = layoutProperty->GetLayoutDirectionStr();
    EXPECT_EQ(layoutDirectionStr, GRID_DIRECTION_ROW_REVERSE);
}

/**
 * @tc.name: GridTest006
 * @tc.desc: When fixed rows and columns are not set and direction is Column, all items in the grid are filled.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create grid node and initialize width, height, properties.
     */
    GridModelNG grid;
    RefPtr<ScrollBarProxy> scrollBarProxy;
    auto positionController = grid.CreatePositionController();
    grid.Create(positionController, scrollBarProxy);
    std::unique_ptr<ViewAbstractModel> instance = std::make_unique<ViewAbstractModelNG>();
    auto height = StringUtils::StringToDimensionWithUnit("70%");
    instance->SetHeight(height);
    auto width = StringUtils::StringToDimensionWithUnit("90%");
    instance->SetWidth(width);

    /**
     * @tc.steps: step2. initialize properties such as ColumnsGap, RowsGap, LayoutDirection, MaxCount, MinCount,
     * ScrollBarMode, CellLength and MultiSelectable.
     */
    grid.SetColumnsGap(GRID_COLUMNS_GAP);
    grid.SetRowsGap(GRID_ROWS_GAP);
    grid.SetMultiSelectable(true);
    grid.SetLayoutDirection(FlexDirection::COLUMN);
    grid.SetMaxCount(GRID_MAX_COUNT);
    grid.SetMinCount(GRID_MIN_COUNT);
    grid.SetCellLength(GRID_CELL_LENGTH);
    grid.SetScrollBarMode(static_cast<int32_t>(NG::DisplayMode::ON));

    /**
     * @tc.steps: step3. Create the child nodes gridItem and text of the grid, and set the width and height of text.
     */
    TextModelNG text;
    GridItemModelNG gridItem;
    const int32_t ITEM_COUNT = 10;
    for (int32_t i = 0; i < ITEM_COUNT; ++i) {
        gridItem.Create();
        text.Create("test");
        auto textHeight = StringUtils::StringToDimensionWithUnit("50%");
        instance->SetHeight(textHeight);
        auto textWidth = StringUtils::StringToDimensionWithUnit("100%");
        instance->SetWidth(textWidth);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->Pop();
    }

    /**
     * @tc.steps: step4. Get grid frameNode and set layoutConstraint.
     * @tc.expected: step4. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);

    /**
     * @tc.steps: step5. Call the measure and layout function of grid to calculate the size and layout.
     * @tc.expected: step5. Check size after layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    /**
     * @tc.steps: step6. Get grid layout properties.
     * @tc.expected: step6. Check whether the updated properties is correct.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<GridLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto layoutDirectionStr = layoutProperty->GetLayoutDirectionStr();
    EXPECT_EQ(layoutDirectionStr, GRID_DIRECTION_COLUMN);
}

/**
 * @tc.name: GridTest007
 * @tc.desc: When fixed rows and columns are not set and direction is ColumnReverse, all items in the grid are filled.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create grid node and initialize width, height, properties.
     */
    GridModelNG grid;
    RefPtr<ScrollBarProxy> scrollBarProxy;
    auto positionController = grid.CreatePositionController();
    grid.Create(positionController, scrollBarProxy);
    std::unique_ptr<ViewAbstractModel> instance = std::make_unique<ViewAbstractModelNG>();
    auto height = StringUtils::StringToDimensionWithUnit("70%");
    instance->SetHeight(height);
    auto width = StringUtils::StringToDimensionWithUnit("90%");
    instance->SetWidth(width);

    /**
     * @tc.steps: step2. initialize properties such as ColumnsGap, RowsGap, LayoutDirection, MaxCount, MinCount,
     * ScrollBarMode, CellLength and MultiSelectable.
     */
    grid.SetColumnsGap(GRID_COLUMNS_GAP);
    grid.SetRowsGap(GRID_ROWS_GAP);
    grid.SetMultiSelectable(true);
    grid.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
    grid.SetMaxCount(GRID_MAX_COUNT);
    grid.SetMinCount(GRID_MIN_COUNT);
    grid.SetCellLength(GRID_CELL_LENGTH);
    grid.SetScrollBarMode(static_cast<int32_t>(NG::DisplayMode::OFF));

    /**
     * @tc.steps: step3. Create the child nodes gridItem and text of the grid, and set the width and height of text.
     */
    TextModelNG text;
    GridItemModelNG gridItem;
    const int32_t ITEM_COUNT = 10;
    for (int32_t i = 0; i < ITEM_COUNT; ++i) {
        gridItem.Create();
        text.Create("test");
        auto textHeight = StringUtils::StringToDimensionWithUnit("50%");
        instance->SetHeight(textHeight);
        auto textWidth = StringUtils::StringToDimensionWithUnit("100%");
        instance->SetWidth(textWidth);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->Pop();
    }

    /**
     * @tc.steps: step4. Get grid frameNode and set layoutConstraint.
     * @tc.expected: step4. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);

    /**
     * @tc.steps: step5. Call the measure and layout function of grid to calculate the size and layout.
     * @tc.expected: step5. Check size after layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    /**
     * @tc.steps: step6. Get grid layout properties.
     * @tc.expected: step6. Check whether the updated properties is correct.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<GridLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto layoutDirectionStr = layoutProperty->GetLayoutDirectionStr();
    EXPECT_EQ(layoutDirectionStr, GRID_DIRECTION_COLUMN_REVERSE);

    /**
     * @tc.steps: step7. Get grid EventHub to call related function.
     * @tc.expected: step7. Check whether the related parameters is correct.
     */
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    EXPECT_NE(eventHub, nullptr);
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

/**
 * @tc.name: GridTest008
 * @tc.desc: Set fixed rows only Fill all items in the grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create grid node and initialize width, height, properties.
     */
    GridModelNG grid;
    RefPtr<ScrollBarProxy> scrollBarProxy;
    auto positionController = grid.CreatePositionController();
    grid.Create(positionController, scrollBarProxy);
    std::unique_ptr<ViewAbstractModel> instance = std::make_unique<ViewAbstractModelNG>();
    auto height = StringUtils::StringToDimensionWithUnit("100%");
    instance->SetHeight(height);
    auto width = StringUtils::StringToDimensionWithUnit("90%");
    instance->SetWidth(width);

    /**
     * @tc.steps: step2. initialize properties such as RowsTemplate, RowsGap, Editable and MultiSelectable.
     */
    grid.SetRowsTemplate("1fr 2fr");
    grid.SetRowsGap(GRID_ROWS_GAP);
    grid.SetMultiSelectable(true);
    grid.SetEditable(true);

    /**
     * @tc.steps: step3. Create the child nodes gridItem and text of the grid, and set the width and height of text.
     */
    TextModelNG text;
    GridItemModelNG gridItem;
    const int32_t ITEM_COUNT = 10;
    for (int32_t i = 0; i < ITEM_COUNT; ++i) {
        gridItem.Create();
        text.Create("test");
        auto textHeight = StringUtils::StringToDimensionWithUnit("80%");
        instance->SetHeight(textHeight);
        auto textWidth = StringUtils::StringToDimensionWithUnit("100%");
        instance->SetWidth(textWidth);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->Pop();
    }

    /**
     * @tc.steps: step4. Get grid frameNode and set layoutConstraint.
     * @tc.expected: step4. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(CONTAINER_SIZE);

    /**
     * @tc.steps: step5. Call the measure and layout function of grid to calculate the size and layout.
     * @tc.expected: step5. Check size after layout.
     */
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    /**
     * @tc.steps: step6. Get grid pattern to call ComputeSelectedZone function.
     */
    auto pattern = frameNode->GetPattern<GridPattern>();
    EXPECT_NE(pattern, nullptr);

    /**
     * @tc.steps: step7. When setting different startOffset and endOffset, call the ComputeSelectedZone function.
     * @tc.expected: step7. Check whether the return value is correct.
     */
    OffsetF startOffset1(1.0f, 0.0f);
    OffsetF endOffset1(1.0f, 0.0f);
    auto selectedZone1 = pattern->ComputeSelectedZone(startOffset1, endOffset1);
    EXPECT_EQ(selectedZone1, RectF(startOffset1.GetX(), startOffset1.GetY(), endOffset1.GetX() - startOffset1.GetX(),
                                 endOffset1.GetY() - startOffset1.GetY()));

    OffsetF startOffset2(1.0f, 1.0f);
    OffsetF endOffset2(1.0f, 0.0f);
    auto selectedZone2 = pattern->ComputeSelectedZone(startOffset2, endOffset2);
    EXPECT_EQ(selectedZone2, RectF(startOffset2.GetX(), endOffset2.GetY(), endOffset2.GetX() - startOffset2.GetX(),
                                 startOffset2.GetY() - endOffset2.GetY()));

    OffsetF startOffset3(1.0f, 0.0f);
    OffsetF endOffset3(0.0f, 1.0f);
    auto selectedZone3 = pattern->ComputeSelectedZone(startOffset3, endOffset3);
    EXPECT_EQ(selectedZone3, RectF(endOffset3.GetX(), startOffset3.GetY(), startOffset3.GetX() - endOffset3.GetX(),
                                 endOffset3.GetY() - startOffset3.GetY()));

    OffsetF startOffset4(1.0f, 1.0f);
    OffsetF endOffset4(0.0f, 0.0f);
    auto selectedZone4 = pattern->ComputeSelectedZone(startOffset4, endOffset4);
    EXPECT_EQ(selectedZone4, RectF(endOffset4.GetX(), endOffset4.GetY(), startOffset4.GetX() - endOffset4.GetX(),
                                 startOffset4.GetY() - endOffset4.GetY()));
}

RefPtr<FrameNode> TestScrollGrid(OptionalSizeF gridSize, double gridItemHeight, int32_t gridItemFrom,
    int32_t gridItemTo, float scrollOffset = 0.0f, int32_t totalItemCount = 9)
{
    /**
     * @tc.steps: step1. Create grid node and initialize width, height, properties.
     */
    RefPtr<V2::GridPositionController> positionController;
    RefPtr<ScrollBarProxy> scrollBarProxy;
    GridModelNG grid;
    grid.Create(positionController, scrollBarProxy);
    std::unique_ptr<ViewAbstractModel> instance = std::make_unique<ViewAbstractModelNG>();
    auto height = StringUtils::StringToDimensionWithUnit("70%");
    instance->SetHeight(height);
    auto width = StringUtils::StringToDimensionWithUnit("90%");
    instance->SetWidth(width);
    grid.SetColumnsTemplate("1fr 1fr 1fr");

    /**
     * @tc.steps: step2. Create the child nodes gridItem and text of the grid, and set the width and height of text.
     */
    GridItemModelNG gridItem;
    TextModelNG text;
    for (int32_t i = 0; i < totalItemCount; ++i) {
        gridItem.Create();
        text.Create("test");
        auto textHeight = StringUtils::StringToDimensionWithUnit("50%");
        instance->SetHeight(textHeight);
        auto textWidth = StringUtils::StringToDimensionWithUnit("100%");
        instance->SetWidth(textWidth);
        ViewStackProcessor::GetInstance()->Pop();
        instance->SetHeight(Dimension(gridItemHeight));
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
        auto layoutAlgorithmWrapper = layoutWrapper->GetLayoutAlgorithm();
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
 * @tc.name: GridTest009
 * @tc.desc: grid with fixed column
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest009, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 900.0f);
    const int32_t ITEM_COUNT = 9;
    constexpr double GRID_ITEM_HEIGHT = 300.0f;
    TestScrollGrid(gridSize, GRID_ITEM_HEIGHT, 0, ITEM_COUNT);
}

/**
 * @tc.name: GridTest010
 * @tc.desc: grid with fixed column, some griditem not show
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest010, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t ITEM_COUNT = 6;
    constexpr double GRID_ITEM_HEIGHT = 300.0f;
    TestScrollGrid(gridSize, GRID_ITEM_HEIGHT, 0, ITEM_COUNT);
}

/**
 * @tc.name: GridTest011
 * @tc.desc: grid with fixed column, some griditem not fully show
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest011, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 800.0f);
    const int32_t ITEM_COUNT = 9;
    constexpr double GRID_ITEM_HEIGHT = 300.0f;
    TestScrollGrid(gridSize, GRID_ITEM_HEIGHT, 0, ITEM_COUNT);
}

/**
 * @tc.name: GridTest012
 * @tc.desc: grid with fixed column, scroll to show one more line
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest012, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t ITEM_COUNT = 9;
    constexpr double GRID_ITEM_HEIGHT = 300.0f;
    TestScrollGrid(gridSize, GRID_ITEM_HEIGHT, 0, ITEM_COUNT, -100.0f);
}

/**
 * @tc.name: GridTest013
 * @tc.desc: grid with fixed column, scroll to end
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest013, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t ITEM_COUNT = 9;
    constexpr double GRID_ITEM_HEIGHT = 300.0f;
    TestScrollGrid(gridSize, GRID_ITEM_HEIGHT, 3, ITEM_COUNT, -300.0f);
}

/**
 * @tc.name: GridTest014
 * @tc.desc: grid with fixed column, scroll to index not fully showed at last line
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest014, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t ITEM_COUNT = 9;
    constexpr double GRID_ITEM_HEIGHT = 300.0f;
    auto frameNode = TestScrollGrid(gridSize, GRID_ITEM_HEIGHT, 0, ITEM_COUNT, -100.0f);
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
 * @tc.name: GridTest015
 * @tc.desc: grid with fixed column, scroll to index not fully showed at first line
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest015, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t ITEM_COUNT = 9;
    constexpr double GRID_ITEM_HEIGHT = 300.0f;
    auto frameNode = TestScrollGrid(gridSize, GRID_ITEM_HEIGHT, 0, ITEM_COUNT, -100.0f);
    EXPECT_FALSE(frameNode == nullptr);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    EXPECT_FALSE(gridPattern == nullptr);
    gridPattern->UpdateStartIndex(1);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.UpdateIllegalSelfIdealSizeWithCheck(gridSize);
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    for (int32_t i = 6; i < ITEM_COUNT; ++i) {
        EXPECT_FALSE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: GridTest016
 * @tc.desc: grid with fixed column, scroll to index fully showed
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest016, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t ITEM_COUNT = 9;
    constexpr double GRID_ITEM_HEIGHT = 300.0f;
    auto frameNode = TestScrollGrid(gridSize, GRID_ITEM_HEIGHT, 0, ITEM_COUNT, -100.0f);
    EXPECT_FALSE(frameNode == nullptr);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    EXPECT_FALSE(gridPattern == nullptr);
    gridPattern->UpdateStartIndex(3);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    constraint.UpdateIllegalSelfIdealSizeWithCheck(gridSize);
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    for (int32_t i = 0; i < ITEM_COUNT; ++i) {
        EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: GridTest017
 * @tc.desc: grid with fixed column, scroll to index not fully showed at last line
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest017, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t ITEM_COUNT = 9;
    constexpr double GRID_ITEM_HEIGHT = 300.0f;
    auto frameNode = TestScrollGrid(gridSize, GRID_ITEM_HEIGHT, 0, ITEM_COUNT, -100.0f, 10);
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
 * @tc.name: GridTest018
 * @tc.desc: grid with fixed column, scroll to index out of view
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest018, TestSize.Level1)
{
    OptionalSizeF gridSize(900.0f, 600.0f);
    const int32_t ITEM_COUNT = 9;
    constexpr double GRID_ITEM_HEIGHT = 300.0f;
    // scroll to show index 0-8
    auto frameNode = TestScrollGrid(gridSize, GRID_ITEM_HEIGHT, 0, ITEM_COUNT, -100.0f, 10);

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
} // namespace OHOS::Ace::NG