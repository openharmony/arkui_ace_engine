/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#define protected public
#define private public
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_ng/test/pattern/test_ng.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float ITEM_WIDTH = 100.f;
constexpr float ITEM_HEIGHT = 100.f;
constexpr float GRID_HEIGHT = 300.f;
} // namespace

class GridTestNg : public testing::Test, public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    void CreateGrid(int32_t itemNumber = 20, Axis axis = Axis::VERTICAL);
    void CreateGridItem(int32_t count = 10, float width = -1, float height = -1, bool focusable = false);
    void CreateSingleGridItem(int32_t rowStart = -1, int32_t rowEnd = -1, int32_t colStart = -1,
        int32_t colEnd = -1, float width = -1, float height = -1);
    void UpdateLayoutWrapper(
        RefPtr<FrameNode>& frameNode, float width = DEVICE_WIDTH, float height = GRID_HEIGHT);
    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
    void MouseSelect(Offset start, Offset end);
    void MouseSelectRelease();
    int32_t CalculateGridColumnsOrRows(float contentWidth, float gridWidth, float gutter = 0.0f, float margin = 0.0f);
    testing::AssertionResult IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t expectNextIndex);
    testing::AssertionResult IsEqualCurrentOffset(float expectOffset);
    int32_t findFocusNodeIndex(RefPtr<FocusHub>& focusNode);
    void UpdateLayoutInfo();

    RefPtr<FrameNode> frameNode_;
    RefPtr<GridPattern> pattern_;
    RefPtr<GridEventHub> eventHub_;
    RefPtr<GridLayoutProperty> layoutProperty_;
    RefPtr<GridAccessibilityProperty> accessibilityProperty_;
};

void GridTestNg::UpdateLayoutInfo()
{
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    pattern_->gridLayoutInfo_.lineHeightMap_[0] = ITEM_HEIGHT;
    pattern_->gridLayoutInfo_.gridMatrix_[0][0] = 0;
    pattern_->gridLayoutInfo_.gridMatrix_[0][1] = 1;
    pattern_->gridLayoutInfo_.gridMatrix_[1][0] = 0;
    pattern_->gridLayoutInfo_.gridMatrix_[1][1] = 1;
}

void GridTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
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
    accessibilityProperty_ = nullptr;
}

void GridTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<GridPattern>();
    eventHub_ = frameNode_->GetEventHub<GridEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<GridLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<GridAccessibilityProperty>();
    EXPECT_CALL(
        *(AceType::RawPtr(AceType::DynamicCast<MockRenderContext>(frameNode_->renderContext_))),
        GetPaintRectWithTransform())
        .WillRepeatedly(Return(RectF()));
}

void GridTestNg::CreateGrid(int32_t itemNumber, Axis axis)
{
    GridModelNG gridModelNG;
    RefPtr<ScrollControllerBase> positionController = gridModelNG.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModelNG.CreateScrollBarProxy();
    gridModelNG.Create(positionController, scrollBarProxy);
    if (axis == Axis::HORIZONTAL) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        CreateGridItem(itemNumber, ITEM_WIDTH, -1);
    } else {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateGridItem(itemNumber, -1, ITEM_HEIGHT);
    }
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
}

void GridTestNg::CreateGridItem(
    int32_t count, float width, float height, bool focusable)
{
    for (int32_t i = 0; i < count; i++) {
        GridItemModelNG gridItemModel;
        gridItemModel.Create();
        if (width != -1) {
            SetWidth(Dimension(width));
        }
        if (height != -1) {
            SetHeight(Dimension(height));
        }
        if (focusable) {
            ButtonModelNG buttonModelNG;
            buttonModelNG.CreateWithLabel("label");
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void GridTestNg::CreateSingleGridItem(
    int32_t rowStart, int32_t rowEnd, int32_t colStart, int32_t colEnd, float width, float height)
{
        GridItemModelNG gridItemModel;
        gridItemModel.Create();
        if (rowStart != -1) {
            gridItemModel.SetRowStart(rowStart);
        }
        if (rowEnd != -1) {
            gridItemModel.SetRowEnd(rowEnd);
        }
        if (colStart != -1) {
            gridItemModel.SetColumnStart(colStart);
        }
        if (colEnd != -1) {
            gridItemModel.SetColumnEnd(colEnd);
        }
        if (width != -1) {
            SetWidth(Dimension(width));
        }
        if (height != -1) {
            SetHeight(Dimension(height));
        }
        ViewStackProcessor::GetInstance()->Pop();
}

void GridTestNg::UpdateLayoutWrapper(RefPtr<FrameNode>& frameNode, float width, float height)
{
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
    LayoutConstraint.percentReference = { DEVICE_WIDTH, DEVICE_HEIGHT };
    LayoutConstraint.selfIdealSize = { width, height };
    LayoutConstraint.maxSize = { width, DEVICE_HEIGHT };
    frameNode->Measure(LayoutConstraint);
    frameNode->Layout();
}

void GridTestNg::MouseSelect(Offset start, Offset end)
{
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(start);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    if (start != end) {
        info.SetAction(MouseAction::MOVE);
        info.SetLocalLocation(end);
        pattern_->HandleMouseEventWithoutKeyboard(info);
    }
}

void GridTestNg::MouseSelectRelease()
{
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
}

int32_t GridTestNg::CalculateGridColumnsOrRows(float contentWidth, float gridWidth, float gutter, float margin)
{
    int32_t count = static_cast<int32_t>(floor((contentWidth - 2 * margin + gutter) / (gridWidth + gutter)));
    return count < 1 ? 1 : count;
}

void GridTestNg::UpdateCurrentOffset(float offset, int32_t source)
{
    pattern_->UpdateCurrentOffset(offset, source);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
}

testing::AssertionResult GridTestNg::IsEqualNextFocusNode(
    FocusStep step, int32_t currentIndex, int32_t expectNextIndex)
{
    RefPtr<FocusHub> currentFocusNode = GetChildFocusHub(frameNode_, currentIndex);
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
    if (expectNextIndex != NULL_INDEX && nextFocusNode == nullptr) {
        return testing::AssertionFailure() << "Next FocusNode is null.";
    }
    int32_t nextIndex = findFocusNodeIndex(nextFocusNode);
    if (expectNextIndex != nextIndex) {
        return testing::AssertionFailure() <<
            "Get wrong Next FocusNode or Next FocusNode is not null. The nextIndex is " <<
            nextIndex;
    }
    return testing::AssertionSuccess();
}

int32_t GridTestNg::findFocusNodeIndex(RefPtr<FocusHub>& focusNode)
{
    auto children = frameNode_->GetChildren();
    int32_t size = static_cast<int32_t>(children.size());
    for (int32_t index = 0; index < size; index++) {
        if (focusNode == GetChildFocusHub(frameNode_, index)) {
            return index;
        }
    }
    return NULL_INDEX;
}

testing::AssertionResult GridTestNg::IsEqualCurrentOffset(float expectOffset)
{
    float currentOffset = pattern_->GetGridLayoutInfo().currentOffset_;
    if (currentOffset == expectOffset) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() <<
        "currentOffset: " << currentOffset <<
        " != " <<
        "expectOffset: " << expectOffset;
}

/**
 * @tc.name: Property001
 * @tc.desc: Test all the properties of Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Property001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    RefPtr<ScrollControllerBase> positionController = gridModelNG.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModelNG.CreateScrollBarProxy();
    gridModelNG.Create(positionController, scrollBarProxy);
    gridModelNG.SetRowsTemplate("1fr 1fr 1fr");
    gridModelNG.SetColumnsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(Dimension(5));
    gridModelNG.SetColumnsGap(Dimension(10));
    gridModelNG.SetEdgeEffect(EdgeEffect::SPRING);
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue(), "1fr 1fr 1fr");
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(), "1fr 1fr");
    EXPECT_EQ(layoutProperty_->GetRowsGapValue(), Dimension(5));
    EXPECT_EQ(layoutProperty_->GetColumnsGapValue(), Dimension(10));
    EXPECT_EQ(layoutProperty_->GetEdgeEffectValue(), EdgeEffect::SPRING);

    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_NE(json, nullptr);

    layoutProperty_->UpdateEdgeEffect(EdgeEffect::FADE);
    auto json2 = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json2);
    EXPECT_EQ(json2->GetString("edgeEffect"), "EdgeEffect.Fade");
}

/**
 * @tc.name: Property002
 * @tc.desc: Test Negative Gap
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Property002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsGap(Dimension(-5));
    gridModelNG.SetColumnsGap(Dimension(-10));
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Verify GapValue
     * @tc.expected: Gap not be set
     */
    EXPECT_EQ(layoutProperty_->GetRowsGap(), std::nullopt);
    EXPECT_EQ(layoutProperty_->GetColumnsGap(), std::nullopt);

    /**
     * @tc.steps: step1. Call GetGridDirectionStr()
     * @tc.expected: The return string value is correct
     */
    EXPECT_EQ(layoutProperty_->GetGridDirectionStr(), "GridDirection.Row");
    layoutProperty_->UpdateGridDirection(FlexDirection::ROW_REVERSE);
    EXPECT_EQ(layoutProperty_->GetGridDirectionStr(), "GridDirection.RowReverse");
    layoutProperty_->UpdateGridDirection(FlexDirection::COLUMN);
    EXPECT_EQ(layoutProperty_->GetGridDirectionStr(), "GridDirection.Column");
    layoutProperty_->UpdateGridDirection(FlexDirection::COLUMN_REVERSE);
    EXPECT_EQ(layoutProperty_->GetGridDirectionStr(), "GridDirection.ColumnReverse");
}

/**
 * @tc.name: Property003
 * @tc.desc: Test all the properties of GridItem.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Property003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gridItem and Set properties.
     */
    GridItemModelNG gridItemModelNG;
    gridItemModelNG.Create();
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
    auto layoutProperty = frameNode->GetLayoutProperty<GridItemLayoutProperty>();
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
    EXPECT_TRUE(pattern->forceRebuild_);
    auto eventHub = frameNode->GetEventHub<GridItemEventHub>();
    ASSERT_NE(eventHub->onSelect_, nullptr);
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: AttrColumnsTemplate001
 * @tc.desc: Test property about columnsTemplate and Gap,
 * test normal condition that template is "1fr 1fr 1fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrColumnsTemplate001, TestSize.Level1)
{
    const std::string columnsTemplate = "1fr 1fr 1fr 1fr";
    const Dimension columnsGap = Dimension(10);
    const Dimension rowsGap = Dimension(5);
    constexpr int32_t gridItemNumber = 10;
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate(columnsTemplate);
    gridModelNG.SetColumnsGap(columnsGap);
    gridModelNG.SetRowsGap(rowsGap);
    CreateGridItem(gridItemNumber, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. While only set ColumnsTemplate
     * @tc.expected: The axis is VERTICAL
     */
    EXPECT_EQ(pattern_->GetAxis(), Axis::VERTICAL);

    /**
     * @tc.steps: step2. Verify all of gridItems rect
     * @tc.expected: The rect is equal to expectRect
     */
    constexpr int32_t colsNumber = 4;
    const float colsGapTotal = columnsGap.ConvertToPx() * (colsNumber - 1);
    const float averageWidth = (DEVICE_WIDTH - colsGapTotal) / colsNumber;
    for (int32_t index = 0; index < gridItemNumber; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = index % colsNumber * (averageWidth + columnsGap.ConvertToPx());
        float offsetY = floor(index / colsNumber) * (ITEM_HEIGHT + rowsGap.ConvertToPx());
        RectF expectRect = RectF(offsetX, offsetY, averageWidth, ITEM_HEIGHT);
        EXPECT_TRUE(IsEqualRect(childRect, expectRect));
        EXPECT_TRUE(GetChildFrameNode(frameNode_, index)->IsActive());
    }
}

/**
 * @tc.name: AttrColumnsTemplate002
 * @tc.desc: Test property about columnsTemplate,
 * test condition that template is "1fr 2fr 3fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrColumnsTemplate002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    const std::string columnsTemplate = "1fr 2fr 3fr 1fr";
    gridModelNG.SetColumnsTemplate(columnsTemplate);
    constexpr int32_t gridItemNumber = 10;
    CreateGridItem(gridItemNumber, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     * @tc.expected: The rect is equal to expectRect
     */
    const float averageWidth = DEVICE_WIDTH / 7;
    RectF rect_1 = GetChildRect(frameNode_, 1);
    const float offsetX_1 = averageWidth;
    const float offsetY_1 = 0.f;
    const float width_1 = averageWidth * 2;
    const float height_1 = ITEM_HEIGHT;
    const RectF expectRect_1 = RectF(offsetX_1, offsetY_1, width_1, height_1);
    EXPECT_TRUE(IsEqualRect(rect_1, expectRect_1));

    /**
     * @tc.steps: step2. Verify index 6 gridItem rect
     * @tc.expected: The rect is equal to expectRect
     */
    RectF rect_6 = GetChildRect(frameNode_, 6);
    const float offsetX_6 = averageWidth * 3;
    const float offsetY_6 = ITEM_HEIGHT;
    const float width_6 = averageWidth * 3;
    const float height_6 = ITEM_HEIGHT;
    const RectF expectRect_6 = RectF(offsetX_6, offsetY_6, width_6, height_6);
    EXPECT_TRUE(IsEqualRect(rect_6, expectRect_6));
}

/**
 * @tc.name: AttrColumnsTemplate003
 * @tc.desc: Test property about columnsTemplate,
 * test condition that template is "1fr 0fr 0fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrColumnsTemplate003, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    const std::string columnsTemplate = "1fr 0fr 0fr 1fr";
    gridModelNG.SetColumnsTemplate(columnsTemplate);
    constexpr int32_t gridItemNumber = 10;
    CreateGridItem(gridItemNumber, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     * @tc.expected: The item width is zero
     */
    const float averageWidth = DEVICE_WIDTH / 2;
    RectF rect_1 = GetChildRect(frameNode_, 1);
    const float offsetX_1 = averageWidth;
    const float offsetY_1 = 0.f;
    const float width_1 = 0.f;
    const float height_1 = ITEM_HEIGHT;
    const RectF expectRect_1 = RectF(offsetX_1, offsetY_1, width_1, height_1);
    EXPECT_TRUE(IsEqualRect(rect_1, expectRect_1));
}

/**
 * @tc.name: AttrColumnsTemplate004
 * @tc.desc: Test property about columnsTemplate and Gap,
 * test normal condition that template is "repeat(auto-fit, 90px)"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrColumnsTemplate004, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    const std::string columnsTemplate = "repeat(auto-fit, 90px)";
    gridModelNG.SetColumnsTemplate(columnsTemplate);
    const Dimension columnsGap = Dimension(10);
    gridModelNG.SetColumnsGap(columnsGap);
    const Dimension rowsGap = Dimension(5);
    gridModelNG.SetRowsGap(rowsGap);
    constexpr int32_t gridItemNumber = 10;
    CreateGridItem(gridItemNumber, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. While only set ColumnsTemplate
     * @tc.expected: The axis is VERTICAL
     */
    EXPECT_EQ(pattern_->GetAxis(), Axis::VERTICAL);

    /**
     * @tc.steps: step2. Verify all of gridItems rect
     * @tc.expected: The rect is equal to expectRect
     */
    constexpr float gridWidth = 90.0f;
    int32_t colsNumber = CalculateGridColumnsOrRows(DEVICE_WIDTH, gridWidth, columnsGap.ConvertToPx());
    const float colsGapTotal = columnsGap.ConvertToPx() * (colsNumber - 1);
    const float averageWidth = (DEVICE_WIDTH - colsGapTotal) / colsNumber;
    for (int32_t index = 0; index < gridItemNumber; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = index % colsNumber * (averageWidth + columnsGap.ConvertToPx());
        float offsetY = floor(index / colsNumber) * (ITEM_HEIGHT + rowsGap.ConvertToPx());
        RectF expectRect = RectF(offsetX, offsetY, averageWidth, ITEM_HEIGHT);
        EXPECT_TRUE(IsEqualRect(childRect, expectRect));
    }
}

/**
 * @tc.name: AttrRowsTemplate001
 * @tc.desc: Test property about rowsTemplate and Gap,
 * test normal condition that template is "1fr 1fr 1fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrRowsTemplate001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    const std::string rowsTemplate = "1fr 1fr 1fr 1fr";
    gridModelNG.SetRowsTemplate(rowsTemplate);
    const Dimension columnsGap = Dimension(10);
    gridModelNG.SetColumnsGap(columnsGap);
    const Dimension rowsGap = Dimension(5);
    gridModelNG.SetRowsGap(rowsGap);
    constexpr int32_t gridItemNumber = 10;
    CreateGridItem(gridItemNumber, ITEM_WIDTH, -1);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. While only set rowsTemplate
     * @tc.expected: The axis is HORIZONTAL
     */
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);

    /**
     * @tc.steps: step2. Verify all of gridItems rect
     * @tc.expected: The rect is equal to expectRect
     */
    constexpr int32_t rowsNumber = 4;
    const float rowsGapTotal = rowsGap.ConvertToPx() * (rowsNumber - 1);
    const float averageHeight = (GRID_HEIGHT - rowsGapTotal) / rowsNumber;
    for (int32_t index = 0; index < gridItemNumber; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = floor(index / rowsNumber) * (ITEM_WIDTH + columnsGap.ConvertToPx());
        float offsetY = index % rowsNumber * (averageHeight + rowsGap.ConvertToPx());
        RectF expectRect = RectF(offsetX, offsetY, ITEM_WIDTH, averageHeight);
        EXPECT_TRUE(IsEqualRect(childRect, expectRect));
        EXPECT_TRUE(GetChildFrameNode(frameNode_, index)->IsActive());
    }
}

/**
 * @tc.name: AttrRowsTemplate002
 * @tc.desc: Test property about rowsTemplate,
 * test condition that template is "1fr 2fr 3fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrRowsTemplate002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    const std::string rowsTemplate = "1fr 2fr 3fr 1fr";
    gridModelNG.SetRowsTemplate(rowsTemplate);
    constexpr int32_t gridItemNumber = 10;
    CreateGridItem(gridItemNumber, ITEM_WIDTH, -1);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     * @tc.expected: The rect is equal to expectRect
     */
    const float averageHeight = GRID_HEIGHT / 7;
    RectF rect_1 = GetChildRect(frameNode_, 1);
    const float offsetX_1 = 0.f;
    const float offsetY_1 = averageHeight;
    const float width_1 = ITEM_WIDTH;
    const float height_1 = averageHeight * 2;
    const RectF expectRect_1 = RectF(offsetX_1, offsetY_1, width_1, height_1);
    EXPECT_TRUE(IsEqualRect(rect_1, expectRect_1));

    /**
     * @tc.steps: step2. Verify index 6 gridItem rect
     * @tc.expected: The rect is equal to expectRect
     */
    RectF rect_6 = GetChildRect(frameNode_, 6);
    const float offsetX_6 = ITEM_WIDTH;
    const float offsetY_6 = averageHeight * 3;
    const float width_6 = ITEM_WIDTH;
    const float height_6 = averageHeight * 3;
    const RectF expectRect_6 = RectF(offsetX_6, offsetY_6, width_6, height_6);
    EXPECT_TRUE(IsEqualRect(rect_6, expectRect_6));
}

/**
 * @tc.name: AttrRowsTemplate003
 * @tc.desc: Test property about rowsTemplate,
 * test condition that template is "1fr 0fr 0fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrRowsTemplate003, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    const std::string rowsTemplate = "1fr 0fr 0fr 1fr";
    gridModelNG.SetRowsTemplate(rowsTemplate);
    constexpr int32_t gridItemNumber = 10;
    CreateGridItem(gridItemNumber, ITEM_WIDTH, -1);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     * @tc.expected: The item height is zero
     */
    const float averageHeight = GRID_HEIGHT / 2;
    RectF rect_1 = GetChildRect(frameNode_, 1);
    const float offsetX_1 = 0.f;
    const float offsetY_1 = averageHeight;
    const float width_1 = ITEM_WIDTH;
    const float height_1 = 0.f;
    const RectF expectRect_1 = RectF(offsetX_1, offsetY_1, width_1, height_1);
    EXPECT_TRUE(IsEqualRect(rect_1, expectRect_1));
}

/**
 * @tc.name: AttrRowsTemplate004
 * @tc.desc: Test property about rowsTemplate and Gap,
 * test normal condition that template is "repeat(auto-fit, 90px)"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrRowsTemplate004, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    const std::string rowsTemplate = "repeat(auto-fit, 90px)";
    gridModelNG.SetRowsTemplate(rowsTemplate);
    const Dimension columnsGap = Dimension(10);
    gridModelNG.SetColumnsGap(columnsGap);
    const Dimension rowsGap = Dimension(5);
    gridModelNG.SetRowsGap(rowsGap);
    constexpr int32_t gridItemNumber = 10;
    CreateGridItem(gridItemNumber, ITEM_WIDTH, -1);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. While only set rowsTemplate
     * @tc.expected: The axis is HORIZONTAL
     */
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);

    /**
     * @tc.steps: step2. Verify all of gridItems rect
     * @tc.expected: The rect is equal to expectRect
     */
    constexpr float gridWidth = 90.0f;
    int32_t rowsNumber = CalculateGridColumnsOrRows(GRID_HEIGHT, gridWidth, rowsGap.ConvertToPx());
    const float rowsGapTotal = rowsGap.ConvertToPx() * (rowsNumber - 1);
    const float averageHeight = (GRID_HEIGHT - rowsGapTotal) / rowsNumber;
    for (int32_t index = 0; index < gridItemNumber; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = floor(index / rowsNumber) * (ITEM_WIDTH + columnsGap.ConvertToPx());
        float offsetY = index % rowsNumber * (averageHeight + rowsGap.ConvertToPx());
        RectF expectRect = RectF(offsetX, offsetY, ITEM_WIDTH, averageHeight);
        EXPECT_TRUE(IsEqualRect(childRect, expectRect));
    }
}

/**
 * @tc.name: AttrColumnsRows001
 * @tc.desc: Test property about columns/rows Template,
 * test condition that template is empty: ""
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrColumnsRows001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("");
    gridModelNG.SetColumnsTemplate("");
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. compare grid properties and expected value after change.
     * @tc.expected: grid properties equals expected value after change.
     */
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue(), "1fr");
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(), "1fr");
}

/**
 * @tc.name: AttrColumnsRows002
 * @tc.desc: Test property about columns/rows Template,
 * set both columns/rows Template with "1fr 1fr 1fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrColumnsRows002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    const std::string colstemplate = "1fr 1fr 1fr 1fr";
    const std::string rowstemplate = "1fr 1fr 1fr 1fr";
    gridModelNG.SetColumnsTemplate(colstemplate);
    gridModelNG.SetRowsTemplate(rowstemplate);
    constexpr int32_t gridItemNumber = 10;
    // not set gridItem width/height, gridItem will fill the mesh size by default
    CreateGridItem(gridItemNumber);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Set both columns/rows Template
     * @tc.expected: The gridItem width/height will slef-adaption
     */
    constexpr int32_t colsNumber = 4;
    constexpr int32_t rowsNumber = 4;
    const float averageWidth = DEVICE_WIDTH / colsNumber;
    const float averageHeight = GRID_HEIGHT / rowsNumber;
    for (int32_t index = 0; index < gridItemNumber; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = index % colsNumber * averageWidth;
        float offsetY = floor(index / colsNumber) * averageHeight;
        RectF expectRect = RectF(offsetX, offsetY, averageWidth, averageHeight);
        EXPECT_TRUE(IsEqualRect(childRect, expectRect));
        EXPECT_TRUE(GetChildFrameNode(frameNode_, index)->IsActive());
    }
}

/**
 * @tc.name: AttrLayoutDirection001
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::ROW
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrLayoutDirection001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetLayoutDirection(FlexDirection::ROW);
    gridModelNG.SetCellLength(ITEM_HEIGHT);
    constexpr int32_t minCount = 2;
    gridModelNG.SetMinCount(minCount);
    constexpr int32_t maxCount = 4;
    gridModelNG.SetMaxCount(maxCount);
    const Dimension columnsGap = Dimension(10);
    gridModelNG.SetColumnsGap(columnsGap);
    const Dimension rowsGap = Dimension(5);
    gridModelNG.SetRowsGap(rowsGap);
    constexpr int32_t gridItemNumber = 10;
    CreateGridItem(gridItemNumber, ITEM_WIDTH, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    constexpr int32_t colsNumber = 4;
    constexpr int32_t activeCount = 8;
    for (int32_t index = 0; index < gridItemNumber; index++) {
        if (index < activeCount) {
            RectF childRect = GetChildRect(frameNode_, index);
            float offsetX = index % colsNumber * (ITEM_WIDTH + columnsGap.ConvertToPx());
            float offsetY = floor(index / colsNumber) * (ITEM_HEIGHT + rowsGap.ConvertToPx());
            RectF expectRect = RectF(offsetX, offsetY, ITEM_WIDTH, ITEM_HEIGHT);
            EXPECT_TRUE(IsEqualRect(childRect, expectRect)) << "index: " << index;
            EXPECT_TRUE(GetChildFrameNode(frameNode_, index)->IsActive());
        } else {
            // beyond grid size, would not load
            EXPECT_FALSE(GetChildFrameNode(frameNode_, index)->IsActive());
        }
    }
}

/**
 * @tc.name: AttrLayoutDirection002
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::ROW_REVERSE
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrLayoutDirection002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetLayoutDirection(FlexDirection::ROW_REVERSE);
    gridModelNG.SetCellLength(ITEM_HEIGHT);
    constexpr int32_t minCount = 2;
    gridModelNG.SetMinCount(minCount);
    constexpr int32_t maxCount = 4;
    gridModelNG.SetMaxCount(maxCount);
    const Dimension columnsGap = Dimension(10);
    gridModelNG.SetColumnsGap(columnsGap);
    const Dimension rowsGap = Dimension(5);
    gridModelNG.SetRowsGap(rowsGap);
    constexpr int32_t gridItemNumber = 10;
    CreateGridItem(gridItemNumber, ITEM_WIDTH, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    constexpr int32_t colsNumber = 4;
    constexpr int32_t activeCount = 8;
    const float colsWidthTotal = colsNumber * ITEM_WIDTH + (colsNumber - 1) * columnsGap.ConvertToPx();
    for (int32_t index = 0; index < gridItemNumber; index++) {
        if (index < activeCount) {
            RectF childRect = GetChildRect(frameNode_, index);
            float offsetX = colsWidthTotal - (index % colsNumber + 1) * ITEM_WIDTH -
                index % colsNumber * columnsGap.ConvertToPx();
            float offsetY = floor(index / colsNumber) * (ITEM_HEIGHT + rowsGap.ConvertToPx());
            RectF expectRect = RectF(offsetX, offsetY, ITEM_WIDTH, ITEM_HEIGHT);
            EXPECT_TRUE(IsEqualRect(childRect, expectRect)) << "index: " << index;
            EXPECT_TRUE(GetChildFrameNode(frameNode_, index)->IsActive());
        } else {
            // beyond grid size, would not load
            EXPECT_FALSE(GetChildFrameNode(frameNode_, index)->IsActive());
        }
    }
}

/**
 * @tc.name: AttrLayoutDirection003
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::COLUMN
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrLayoutDirection003, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetLayoutDirection(FlexDirection::COLUMN);
    gridModelNG.SetCellLength(ITEM_WIDTH);
    constexpr int32_t minCount = 2;
    gridModelNG.SetMinCount(minCount);
    constexpr int32_t maxCount = 4;
    gridModelNG.SetMaxCount(maxCount);
    const Dimension columnsGap = Dimension(10);
    gridModelNG.SetColumnsGap(columnsGap);
    const Dimension rowsGap = Dimension(5);
    gridModelNG.SetRowsGap(rowsGap);
    constexpr int32_t gridItemNumber = 10;
    CreateGridItem(gridItemNumber, ITEM_WIDTH, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    constexpr int32_t rowsNumber = 2;
    constexpr int32_t showItemNumber = 8;
    for (int32_t index = 0; index < gridItemNumber; index++) {
        if (index < showItemNumber) {
            RectF childRect = GetChildRect(frameNode_, index);
            float offsetX = floor(index / rowsNumber) * (ITEM_WIDTH + columnsGap.ConvertToPx());
            float offsetY = index % rowsNumber * (ITEM_HEIGHT + rowsGap.ConvertToPx());
            RectF expectRect = RectF(offsetX, offsetY, ITEM_WIDTH, ITEM_HEIGHT);
            EXPECT_TRUE(IsEqualRect(childRect, expectRect)) << "index: " << index;
            EXPECT_TRUE(GetChildFrameNode(frameNode_, index)->IsActive());
        } else {
            EXPECT_FALSE(GetChildFrameNode(frameNode_, index)->IsActive());
        }
    }
}

/**
 * @tc.name: AttrLayoutDirection004
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::COLUMN_REVERSE
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrLayoutDirection004, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
    gridModelNG.SetCellLength(ITEM_WIDTH);
    constexpr int32_t minCount = 2;
    gridModelNG.SetMinCount(minCount);
    constexpr int32_t maxCount = 4;
    gridModelNG.SetMaxCount(maxCount);
    const Dimension columnsGap = Dimension(10);
    gridModelNG.SetColumnsGap(columnsGap);
    const Dimension rowsGap = Dimension(5);
    gridModelNG.SetRowsGap(rowsGap);
    constexpr int32_t gridItemNumber = 10;
    CreateGridItem(gridItemNumber, ITEM_WIDTH, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    constexpr int32_t rowsNumber = 2;
    constexpr int32_t showItemNumber = 8;
    const float rowsHeightTotal = rowsNumber * ITEM_HEIGHT + (rowsNumber - 1) * rowsGap.ConvertToPx();
    for (int32_t index = 0; index < gridItemNumber; index++) {
        if (index < showItemNumber) {
            RectF childRect = GetChildRect(frameNode_, index);
            float offsetX = floor(index / rowsNumber) * (ITEM_WIDTH + columnsGap.ConvertToPx());
            float offsetY = rowsHeightTotal - (index % rowsNumber + 1) * ITEM_HEIGHT -
                index % rowsNumber * rowsGap.ConvertToPx();
            RectF expectRect = RectF(offsetX, offsetY, ITEM_WIDTH, ITEM_HEIGHT);
            EXPECT_TRUE(IsEqualRect(childRect, expectRect)) << "index: " << index;
            EXPECT_TRUE(GetChildFrameNode(frameNode_, index)->IsActive());
        } else {
            EXPECT_FALSE(GetChildFrameNode(frameNode_, index)->IsActive());
        }
    }
}

/**
 * @tc.name: AttrGridItem001
 * @tc.desc: Test property rowStart/rowEnd/colStart/colEnd with colTemplate/rowTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrGridItem001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    const std::string rowsTemplate = "1fr 1fr 1fr 1fr";
    gridModelNG.SetRowsTemplate(rowsTemplate);
    const std::string columnsTemplate = "1fr 1fr 1fr 1fr";
    gridModelNG.SetColumnsTemplate(columnsTemplate);
     // not set width/height
    CreateSingleGridItem(1, 2, 1, 2);
    CreateSingleGridItem(-1, -1, 1, 3);
    CreateSingleGridItem(1, 3, -1, -1);
    CreateGridItem(7);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    RectF rect_0 = GetChildRect(frameNode_, 0);
    const float averageWidth = DEVICE_WIDTH / 4;
    const float averageHeight = GRID_HEIGHT / 4;
    const float offsetX_0 = averageWidth;
    const float offsetY_0 = averageHeight;
    const float width_0 = averageWidth * 2;
    const float height_0 = averageHeight * 2;
    const RectF expectRect_0 = RectF(offsetX_0, offsetY_0, width_0, height_0);
    EXPECT_TRUE(IsEqualRect(rect_0, expectRect_0));

    RectF rect_1 = GetChildRect(frameNode_, 1);
    const float offsetX_1 = 0.f;
    const float offsetY_1 = 0.f;
    const float width_1 = averageWidth * 3;
    const float height_1 = averageHeight;
    const RectF expectRect_1 = RectF(offsetX_1, offsetY_1, width_1, height_1);
    EXPECT_TRUE(IsEqualRect(rect_1, expectRect_1));

    RectF rect_2 = GetChildRect(frameNode_, 2);
    const float offsetX_2 = averageWidth * 3;
    const float offsetY_2 = 0.f;
    const float width_2 = averageWidth;
    const float height_2 = averageHeight * 3;
    const RectF expectRect_2 = RectF(offsetX_2, offsetY_2, width_2, height_2);
    EXPECT_TRUE(IsEqualRect(rect_2, expectRect_2));
}

/**
 * @tc.name: AttrGridItem002
 * @tc.desc: Test property rowStart/rowEnd with rowTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrGridItem002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    const std::string rowsTemplate = "1fr 1fr 1fr 1fr";
    gridModelNG.SetRowsTemplate(rowsTemplate);
    // need set width
    CreateSingleGridItem(1, 2, -1, -1, ITEM_WIDTH, -1);
    CreateSingleGridItem(0, 2, -1, -1, ITEM_WIDTH, -1);
    CreateSingleGridItem(2, 3, -1, -1, ITEM_WIDTH, -1);
    CreateGridItem(7, ITEM_WIDTH, -1);
    GetInstance();
    RunMeasureAndLayout(frameNode_, 300.f, GRID_HEIGHT);

    const float averageHeight = GRID_HEIGHT / 4;
    EXPECT_TRUE(IsEqualRect(GetChildRect(frameNode_, 0), RectF(
        0.f,
        averageHeight,
        ITEM_WIDTH,
        averageHeight * 2
    )));
    EXPECT_TRUE(IsEqualRect(GetChildRect(frameNode_, 1), RectF(
        ITEM_WIDTH,
        0.f,
        ITEM_WIDTH,
        averageHeight * 3
    )));
    EXPECT_TRUE(IsEqualRect(GetChildRect(frameNode_, 2), RectF(
        ITEM_WIDTH * 2,
        averageHeight * 2,
        ITEM_WIDTH,
        averageHeight * 2
    )));

    UpdateCurrentOffset(-ITEM_WIDTH);
    EXPECT_TRUE(IsEqualRect(GetChildRect(frameNode_, 1), RectF(
        80.f,
        0.f,
        ITEM_WIDTH,
        averageHeight * 3
    )));
    EXPECT_TRUE(IsEqualRect(GetChildRect(frameNode_, 2), RectF(
        180.f,
        averageHeight * 2,
        ITEM_WIDTH,
        averageHeight * 2
    )));
}

/**
 * @tc.name: AttrGridItem003
 * @tc.desc: Test property colStart/colEnd with colTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrGridItem003, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    const std::string columnsTemplate = "1fr 1fr 1fr 1fr";
    gridModelNG.SetColumnsTemplate(columnsTemplate);
    // need set height
    CreateSingleGridItem(-1, -1, 2, 3, -1, ITEM_HEIGHT);
    CreateSingleGridItem(-1, -1, 0, 2, -1, ITEM_HEIGHT);
    CreateSingleGridItem(-1, -1, 2, 1, -1, ITEM_HEIGHT);
    CreateGridItem(7, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    const float averageWidth = DEVICE_WIDTH / 4;
    EXPECT_TRUE(IsEqualRect(GetChildRect(frameNode_, 0), RectF(
        averageWidth * 2,
        0.f,
        averageWidth * 2,
        ITEM_HEIGHT
    )));
    EXPECT_TRUE(IsEqualRect(GetChildRect(frameNode_, 1), RectF(
        0.f,
        ITEM_HEIGHT,
        averageWidth * 3,
        ITEM_HEIGHT
    )));
    EXPECT_TRUE(IsEqualRect(GetChildRect(frameNode_, 2), RectF(
        averageWidth * 2,
        ITEM_HEIGHT * 2,
        averageWidth,
        ITEM_HEIGHT
    )));

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualRect(GetChildRect(frameNode_, 1), RectF(
        0.f,
        0.f,
        averageWidth * 3,
        ITEM_HEIGHT
    )));
    EXPECT_TRUE(IsEqualRect(GetChildRect(frameNode_, 2), RectF(
        averageWidth * 2,
        ITEM_HEIGHT,
        averageWidth,
        ITEM_HEIGHT
    )));
}

/**
 * @tc.name: AttrEnableScrollInteraction001
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrEnableScrollInteraction001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);

    /**
     * @tc.steps: step1. Test set value: true
     */
    gridModelNG.SetScrollEnabled(true);
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), true);

    /**
     * @tc.steps: step2. Test set value: false
     */
    layoutProperty_->UpdateScrollEnabled(false);
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), false);
}

/**
 * @tc.name: KeyEvent001
 * @tc.desc: Test OnKeyEvent func.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, KeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. KeyAction::UNKNOWN.
     * @tc.expected: Nothing changed.
     */
    CreateGrid();
    KeyEvent event;
    pattern_->OnKeyEvent(event);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    /**
     * @tc.steps: step2. KeyCode::KEY_PAGE_DOWN.
     * @tc.expected: Page jump down width Grid height.
     */
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_PAGE_DOWN;
    pattern_->OnKeyEvent(event);
    EXPECT_TRUE(IsEqualCurrentOffset(-GRID_HEIGHT));

    /**
     * @tc.steps: step3. KeyCode::KEY_PAGE_UP.
     * @tc.expected: Page jump up width Grid height.
     */
    event.code = KeyCode::KEY_PAGE_UP;
    pattern_->OnKeyEvent(event);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    /**
     * @tc.steps: step4. Test HandleDirectionKey().
     */
    EXPECT_FALSE(pattern_->HandleDirectionKey(KeyCode::KEY_UNKNOWN));
    EXPECT_TRUE(pattern_->HandleDirectionKey(KeyCode::KEY_DPAD_UP));
    EXPECT_TRUE(pattern_->HandleDirectionKey(KeyCode::KEY_DPAD_DOWN));
}

/**
 * @tc.name: GridTest001
 * @tc.desc: Test OnModifyDone()
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetMultiSelectable(true);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(20, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. test OnModifyDone().
     */
    EXPECT_TRUE(pattern_->multiSelectable_);
    EXPECT_TRUE(pattern_->isMouseEventInit_);
    EXPECT_TRUE(pattern_->isConfigScrollable_);
    pattern_->SetMultiSelectable(false);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->multiSelectable_);
    EXPECT_FALSE(pattern_->isMouseEventInit_);

    UpdateCurrentOffset(GRID_HEIGHT);
}

/**
 * @tc.name: GridTest002
 * @tc.desc: Test AnimateTo()
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. !isConfigScrollable_
     */
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    pattern_->AnimateTo(100.f, 200.f, Curves::LINEAR, false);
    ASSERT_EQ(pattern_->animator_, nullptr);

    /**
     * @tc.steps: step2. isConfigScrollable_
     */
    CreateGrid();
    pattern_->AnimateTo(100.f, 200.f, Curves::LINEAR, false);
    ASSERT_NE(pattern_->animator_, nullptr);

    /**
     * @tc.steps: step3. animator_->Stop()
     */
    pattern_->animator_->Stop();
    pattern_->AnimateTo(100.f, 200.f, Curves::LINEAR, false);
    ASSERT_NE(pattern_->animator_, nullptr);
}

/**
 * @tc.name: ScrollablePattern001
 * @tc.desc: Test scrollable_pattern
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, ScrollablePattern001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test OnScrollPosition/OnScrollEnd.
     */
    CreateGrid();
    auto scrollable = pattern_->scrollableEvent_->GetScrollable();
    auto callback_1 = scrollable->callback_;
    auto callback_2 = scrollable->scrollEndCallback_;
    EXPECT_TRUE(callback_1(ITEM_HEIGHT, SCROLL_FROM_UPDATE));
    EXPECT_TRUE(callback_1(ITEM_HEIGHT, SCROLL_FROM_UPDATE));
    EXPECT_TRUE(callback_1(ITEM_HEIGHT, SCROLL_FROM_START));
    callback_2();
    auto coordinationEvent = AceType::MakeRefPtr<ScrollableCoordinationEvent>();
    auto event1 = [](double) { return true; };
    auto event2 = []() {};
    coordinationEvent->SetOnScrollEvent(event1);
    coordinationEvent->SetOnScrollStartEvent(event2);
    coordinationEvent->SetOnScrollEndEvent(event2);
    pattern_->SetCoordinationEvent(coordinationEvent);
    EXPECT_TRUE(callback_1(ITEM_HEIGHT, SCROLL_FROM_UPDATE));
    EXPECT_TRUE(callback_1(ITEM_HEIGHT, SCROLL_FROM_UPDATE));
    EXPECT_TRUE(callback_1(ITEM_HEIGHT, SCROLL_FROM_START));
    callback_2();
    EXPECT_TRUE(callback_1(ITEM_HEIGHT, SCROLL_FROM_UPDATE));
    callback_2();

    /**
     * @tc.steps: step2. Test OnScrollCallback.
     */
    CreateGrid();
    EXPECT_TRUE(pattern_->OnScrollCallback(-ITEM_HEIGHT, SCROLL_FROM_START));
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    EXPECT_TRUE(pattern_->OnScrollCallback(-ITEM_HEIGHT, SCROLL_FROM_UPDATE));
    EXPECT_TRUE(IsEqualCurrentOffset(-ITEM_HEIGHT));
    EXPECT_TRUE(pattern_->OnScrollCallback(-ITEM_HEIGHT, SCROLL_FROM_UPDATE));
    EXPECT_TRUE(IsEqualCurrentOffset(-ITEM_HEIGHT * 2));
}

/**
 * @tc.name: Event001
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Event001, TestSize.Level1)
{
    Dimension offsetY;
    ScrollState scrollState;
    auto event = [&offsetY, &scrollState](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
    };
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr");
    gridModelNG.SetOnScroll(event);
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_EQ(offsetY.ConvertToPx(), ITEM_HEIGHT);
    EXPECT_EQ(scrollState, ScrollState::SCROLL);

    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    EXPECT_EQ(offsetY.ConvertToPx(), -ITEM_HEIGHT);
    EXPECT_EQ(scrollState, ScrollState::FLING);

    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_EQ(offsetY.ConvertToPx(), ITEM_HEIGHT);
    EXPECT_EQ(scrollState, ScrollState::FLING);

    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    EXPECT_EQ(offsetY.ConvertToPx(), -ITEM_HEIGHT);
    EXPECT_EQ(scrollState, ScrollState::IDLE);

    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_EQ(offsetY.ConvertToPx(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);

    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_EQ(offsetY.ConvertToPx(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);

    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_EQ(offsetY.ConvertToPx(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);

    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_EQ(offsetY.ConvertToPx(), -ITEM_HEIGHT);
    EXPECT_EQ(scrollState, ScrollState::IDLE);

    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    pattern_->SetScrollAbort(true);
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_NONE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
}

/**
 * @tc.name: Event002
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Event002, TestSize.Level1)
{
    int32_t startIndex;
    int32_t endIndex;
    auto event = [&startIndex, &endIndex](int32_t start, int32_t end) {
        startIndex = start;
        endIndex = end;
    };
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr");
    gridModelNG.SetOnScrollIndex(event);
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 7);

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(endIndex, 9);
}

/**
 * @tc.name: Event003
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Event003, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger]() { isTrigger = true; };
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr");
    gridModelNG.SetOnReachStart(event);
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_AXIS);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_JUMP);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_JUMP);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_BAR);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: Event004
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Event004, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger]() { isTrigger = true; };
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr");
    gridModelNG.SetOnReachEnd(event);
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT * 3);
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_AXIS);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_JUMP);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_JUMP);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_BAR);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_NONE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: Event005
 * @tc.desc: Verify onScrollStart, onScrollStop callback
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Event005, TestSize.Level1)
{
    bool isScrollStartCalled = false;
    bool isScrollStopCalled = false;
    auto scrollStart = [&isScrollStartCalled]() { isScrollStartCalled = true; };
    auto scrollStop = [&isScrollStopCalled]() { isScrollStopCalled = true; };
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr");
    gridModelNG.SetOnScrollStart(scrollStart);
    gridModelNG.SetOnScrollStop(scrollStop);
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(isScrollStartCalled);

    pattern_->SetScrollAbort(true);
    pattern_->OnScrollEndCallback();
    EXPECT_FALSE(isScrollStopCalled);
    pattern_->SetScrollAbort(false);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(isScrollStopCalled);
}

/**
 * @tc.name: Event006
 * @tc.desc: Test other condition
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Event006, TestSize.Level1)
{
    auto onScrollFrameBegin = [](Dimension, ScrollState) {
        ScrollFrameResult result;
        return result;
    };
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr");
    gridModelNG.SetOnScrollFrameBegin(onScrollFrameBegin);
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    auto scrollableEvent = pattern_->GetScrollableEvent();
    ASSERT_NE(scrollableEvent, nullptr);
    EXPECT_NE(scrollableEvent->GetScrollable()->scrollFrameBeginCallback_, nullptr);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
}

/**
 * @tc.name: GetOverScrollOffset001
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GetOverScrollOffset001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr");
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    OverScrollOffset expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    pattern_->gridLayoutInfo_.currentOffset_ = -ITEM_HEIGHT;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    pattern_->gridLayoutInfo_.currentOffset_ = -ITEM_HEIGHT * 2;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    pattern_->gridLayoutInfo_.currentOffset_ = ITEM_HEIGHT;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2);
    expectOffset = { -ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    pattern_->gridLayoutInfo_.currentOffset_ = -ITEM_HEIGHT * 3;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
}

/**
 * @tc.name: GetOverScrollOffset002
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GetOverScrollOffset002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr");
    CreateGridItem(5, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    OverScrollOffset expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -100.f };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    pattern_->gridLayoutInfo_.currentOffset_ = -ITEM_HEIGHT;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2);
    expectOffset = { 100.f, 100.f };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2);
    expectOffset = { 0, -200.f };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    pattern_->gridLayoutInfo_.currentOffset_ = -ITEM_HEIGHT * 2;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { 0, 100.f };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -100.f };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    pattern_->gridLayoutInfo_.currentOffset_ = ITEM_HEIGHT;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2);
    expectOffset = { -ITEM_HEIGHT, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    pattern_->gridLayoutInfo_.currentOffset_ = -ITEM_HEIGHT * 3;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2);
    expectOffset = { 0, 200.f };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -100.f };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
}

/**
 * @tc.name: ScrollToFocusNodeIndex001
 * @tc.desc: Test ScrollToFocusNodeIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, ScrollToFocusNodeIndex001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr");
    CreateGridItem(10, -1, ITEM_HEIGHT, true);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Focus node outside the viewport
     * @tc.expected: scroll to the node
     */
    int32_t focusNodeIndex = 6;
    pattern_->ScrollToFocusNodeIndex(focusNodeIndex);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    RefPtr<FocusHub> focusNode = GetChildFocusHub(frameNode_, focusNodeIndex);
    EXPECT_FALSE(focusNode->IsCurrentFocus());
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    /**
     * @tc.steps: step2. Focus node index not exist
     * @tc.expected: do nothing
     */
    focusNodeIndex = 10;
    pattern_->ScrollToFocusNodeIndex(focusNodeIndex);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
}

/**
 * @tc.name: ScrollToNode001
 * @tc.desc: Test ScrollToNode
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, ScrollToNode001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr");
    CreateGridItem(10, -1, ITEM_HEIGHT, true);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Focus node outside the viewport
     * @tc.expected: scroll to the node
     */
    int32_t focusNodeIndex = 6;
    RefPtr<FrameNode> focusNode = GetChildFrameNode(frameNode_, focusNodeIndex);
    pattern_->ScrollToNode(focusNode);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
}

/**
 * @tc.name: EventHub001
 * @tc.desc: Test GetInsertPosition func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, EventHub001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(8, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    RectF gridRect(0.f, 0.f, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_CALL(
        *(AceType::RawPtr(AceType::DynamicCast<MockRenderContext>(frameNode_->renderContext_))),
        GetPaintRectWithTransform())
        .WillRepeatedly(Return(gridRect));

    /**
     * @tc.steps: step1. call GetInsertPosition func.
     */
    EXPECT_EQ(eventHub_->GetInsertPosition(DEVICE_WIDTH + 1, DEVICE_HEIGHT), -1); // out of grid
    EXPECT_EQ(eventHub_->GetInsertPosition(0.f, 0.f), 0); // 0, 0
    EXPECT_EQ(eventHub_->GetInsertPosition(ITEM_WIDTH / 2, ITEM_HEIGHT / 2), 0); // first item
    EXPECT_EQ(eventHub_->GetInsertPosition(ITEM_WIDTH * 2, ITEM_HEIGHT / 2), 1); // between the second and third
    EXPECT_EQ(eventHub_->GetInsertPosition(ITEM_WIDTH * 2, ITEM_HEIGHT), 1); // between the 2nd, 3rd, 6th, 7th
    EXPECT_EQ(eventHub_->GetInsertPosition(ITEM_WIDTH, GRID_HEIGHT), 8); // in grid but not on item
    pattern_->GetGridLayoutInfo().currentRect_ = RectF(0.f, 0.f, 180.f, 300.f);
    EXPECT_EQ(eventHub_->GetInsertPosition(180.f, 300.f), 8); // on currentRect_

    /**
     * @tc.steps: step2. call GetFrameNodeChildSize func.
     */
    EXPECT_EQ(eventHub_->GetFrameNodeChildSize(), 8);
}

/**
 * @tc.name: PositionController001
 * @tc.desc: Test positionController func in VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, PositionController001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Unscrollable
     * @tc.expected: jumpIndex_ not change
     */
    GridModelNG gridModelNG;
    RefPtr<ScrollControllerBase> positionController = gridModelNG.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModelNG.CreateScrollBarProxy();
    gridModelNG.Create(positionController, scrollBarProxy);
    CreateGridItem(14, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    auto controller = pattern_->positionController_;
    controller->JumpTo(1, false, ScrollAlign::START, 3);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, -1);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    /**
     * @tc.steps: step2. Test JumpTo func.
     * @tc.expected: Verify return value.
     */
    CreateGrid();
    controller = pattern_->positionController_;
    controller->JumpTo(1, false, ScrollAlign::START, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(19, false, ScrollAlign::START, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(11, false, ScrollAlign::START, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    CreateGrid();
    controller = pattern_->positionController_;
    controller->JumpTo(1, false, ScrollAlign::CENTER, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(12, false, ScrollAlign::CENTER, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(11, false, ScrollAlign::CENTER, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    CreateGrid();
    controller = pattern_->positionController_;
    controller->JumpTo(1, false, ScrollAlign::END, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(12, false, ScrollAlign::END, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(11, false, ScrollAlign::END, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    CreateGrid();
    controller = pattern_->positionController_;
    controller->JumpTo(1, false, ScrollAlign::AUTO, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(12, false, ScrollAlign::AUTO, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(11, false, ScrollAlign::AUTO, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    CreateGrid();
    controller = pattern_->positionController_;
    controller->JumpTo(1, false, ScrollAlign::NONE, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(12, false, ScrollAlign::NONE, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(11, false, ScrollAlign::NONE, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
}

/**
 * @tc.name: PositionController002
 * @tc.desc: Test positionController func in VERTICAL Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, PositionController002, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test AnimateTo func.
     * @tc.expected: Verify return value.
     */
    CreateGrid();
    auto controller = pattern_->positionController_;
    controller->AnimateTo(Dimension(100.f, DimensionUnit::PX), 200.f, Curves::LINEAR, false);
    ASSERT_NE(pattern_->animator_, nullptr);

    /**
     * @tc.steps: step3. Test GetScrollDirection func.
     * @tc.expected: Verify return value.
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);

    /**
     * @tc.steps: step4. Test GetCurrentOffset func.
     * @tc.expected: Verify return value.
     */
    pattern_->UpdateCurrentOffset(20.f, SCROLL_FROM_UPDATE);
    Offset currentOffset = controller->GetCurrentOffset();
    EXPECT_EQ(currentOffset, Offset(0, -20.f));

    /**
     * @tc.steps: step5. Test ScrollToEdge func.
     * @tc.expected: Verify return value.
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, -1);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, -1);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 19);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 0);

    /**
     * @tc.steps: step6. Test ScrollPage func.
     * @tc.expected: Verify currentOffset.
     */
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    controller->ScrollPage(true, true);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset(0, -300.f));

    controller->ScrollPage(false, true);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset(0, 0));

    /**
     * @tc.steps: step7. Test IsAtEnd func.
     */
    EXPECT_FALSE(controller->IsAtEnd());
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(controller->IsAtEnd());
}

/**
 * @tc.name: PositionController003
 * @tc.desc: Test positionController func in HORIZONTAL Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, PositionController003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Change Grid width to 300.
     */
    CreateGrid(20, Axis::HORIZONTAL);
    RunMeasureAndLayout(frameNode_, 300.f, GRID_HEIGHT);

    /**
     * @tc.steps: step2. Test GetScrollDirection func.
     * @tc.expected: Verify return value.
     */
    auto controller = pattern_->positionController_;
    EXPECT_EQ(controller->GetScrollDirection(), Axis::HORIZONTAL);

    /**
     * @tc.steps: step4. Test ScrollToEdge func.
     * @tc.expected: Verify return value.
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 0);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 19);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, false);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 19);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, false);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 19);

    /**
     * @tc.steps: step5. Test ScrollPage func.
     * @tc.expected: Verify currentOffset.
     */
    pattern_->UpdateCurrentOffset(-20.f, SCROLL_FROM_UPDATE);
    controller->ScrollPage(true, false);
    EXPECT_TRUE(IsEqualOffset(controller->GetCurrentOffset(), Offset(-280.f, 0)));
    EXPECT_EQ(pattern_->GetMainContentSize(), 300.f);
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqualOffset(controller->GetCurrentOffset(), Offset(20.f, 0)));
}

/**
 * @tc.name: PositionController004
 * @tc.desc: Test positionController func in Axis::NONE Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, PositionController004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Supplement ScrollPage, GetCurrentOffset branch,
     * has no condition that axis_ is Axis::NONE.
     */
    CreateGrid();
    pattern_->gridLayoutInfo_.axis_ = Axis::NONE;
    auto controller = pattern_->positionController_;
    controller->ScrollPage(true, true);
    controller->GetCurrentOffset();
    EXPECT_TRUE(IsEqualCurrentOffset(0));
}

/**
 * @tc.name: GridAccessibilityTest001
 * @tc.desc: Test Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridAccessibilityTest001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMultiSelectable(true);
    gridModelNG.SetEditable(true);
    CreateGridItem(14, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Run accessibility func.
     * @tc.expected: The return_value is correct.
     */
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_TRUE(accessibilityProperty_->IsEditable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 11);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), 14);
    AceCollectionInfo info = accessibilityProperty_->GetCollectionInfo();
    EXPECT_EQ(info.rows, 3);
    EXPECT_EQ(info.columns, 4);
    EXPECT_EQ(info.selectMode, 1);
}

/**
 * @tc.name: GridAccessibilityTest002
 * @tc.desc: Test Accessibility GetCollectionInfo func with non-scrollable Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridAccessibilityTest002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    CreateGridItem(8, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Run GetCollectionInfo Func.
     * @tc.expected: Verify return value.
     */
    AceCollectionInfo info = accessibilityProperty_->GetCollectionInfo();
    EXPECT_EQ(info.rows, 0);
    EXPECT_EQ(info.columns, 0);
    EXPECT_EQ(info.selectMode, 0);
}

/**
 * @tc.name: GridAccessibilityTest003
 * @tc.desc: Test Accessibility SetSpecificSupportAction func with
 * scrollable Grid and scroll the Grid to the middle
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridAccessibilityTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Scroll to Top.
     */
    CreateGrid(20);
    UpdateCurrentOffset(100.f);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_1 = 0;
    exptectActions_1 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_1);

    /**
     * @tc.steps: step2. Scroll to middle.
     */
    UpdateCurrentOffset(-100.f);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_2 = 0;
    exptectActions_2 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions_2 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_2);

    /**
     * @tc.steps: step3. Scroll to bottom.
     */
    UpdateCurrentOffset(-200.f);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_3 = 0;
    exptectActions_3 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_3);

    /**
     * @tc.steps: step4. UnScrollable.
     */
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    CreateGridItem(14, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_4 = 0;
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_4);
}

/**
 * @tc.name: GridAccessibilityTest007
 * @tc.desc: Test GridItem_Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridAccessibilityTest007, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(20, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    auto itemAccessibility = GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 1);

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

    /**
     * @tc.steps: step3. Run SetSpecificSupportAction func.
     * @tc.expected: Verify return value.
     */
    itemAccessibility->ResetSupportAction();
    uint64_t exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(GetActions(itemAccessibility), exptectActions);
}

/**
 * @tc.name: GridAccessibilityTest008
 * @tc.desc: Test GridItem_Accessibility GetCollectionItemInfo func with has heading GridItem
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridAccessibilityTest008, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");

    /**
     * @tc.steps: step1. Create heading GridItem.
     */
    GridItemModelNG gridItemModel;
    gridItemModel.Create();
    gridItemModel.SetColumnStart(0);
    gridItemModel.SetColumnEnd(3);
    SetHeight(Dimension(ITEM_HEIGHT));
    ViewStackProcessor::GetInstance()->Pop();
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step2. Run GetCollectionItemInfo func.
     * @tc.expected: Verify return value.
     */
    auto itemAccessibility = GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 0);
    AceCollectionItemInfo info = itemAccessibility->GetCollectionItemInfo();
    EXPECT_EQ(info.row, 0);
    EXPECT_EQ(info.column, 0);
    EXPECT_EQ(info.rowSpan, 1);
    EXPECT_EQ(info.columnSpan, 4);
    EXPECT_TRUE(info.heading);
}

/**
 * @tc.name: MouseSelect001
 * @tc.desc: Test mouse click to select, only PRESS and RELEASE the mouse
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, MouseSelect001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(8, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Click the (0, 0) point of firstItem.
     * @tc.expected: item not selected on MouseAction::PRESS.
     */
    MouseSelect(Offset(0.f, 0.f), Offset(0.f, 0.f));
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
}

/**
 * @tc.name: MouseSelect002
 * @tc.desc: Test mouse box selection with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, MouseSelect002, TestSize.Level1)
{
    const Offset LEFT_TOP = Offset(90.f, 50.f);
    const Offset LEFT_BOTTOM = Offset(90.f, 150.f);
    const Offset RIGHT_TOP = Offset(270.f, 50.f);
    const Offset RIGHT_BOTTOM = Offset(270.f, 150.f);

    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(8, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step2. Select (90, 50) - (270, 150) zone, from the LEFT_TOP to the RIGHT_BOTTOM.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    MouseSelect(LEFT_TOP, RIGHT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 4)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 5)->IsSelected());
    MouseSelectRelease();

    /**
     * @tc.steps: step3. Select (90, 50) - (270, 150) zone, from the RIGHT_TOP to the LEFT_BOTTOM.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    MouseSelect(RIGHT_TOP, LEFT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 4)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 5)->IsSelected());
    MouseSelectRelease();

    /**
     * @tc.steps: step4. Select (90, 50) - (270, 150) zone, from the LEFT_BOTTOM to the RIGHT_TOP.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    MouseSelect(LEFT_BOTTOM, RIGHT_TOP);
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 4)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 5)->IsSelected());
    MouseSelectRelease();

    /**
     * @tc.steps: step5. Select (90, 50) - (270, 150) zone, from the RIGHT_BOTTOM to the LEFT_TOP.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    MouseSelect(RIGHT_BOTTOM, LEFT_TOP);
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 4)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 5)->IsSelected());
    MouseSelectRelease();
}

/**
 * @tc.name: MouseSelect003
 * @tc.desc: Test mouse box selection with HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, MouseSelect003, TestSize.Level1)
{
    const Offset LEFT_TOP = Offset(50.f, 50.f);
    const Offset LEFT_BOTTOM = Offset(50.f, 100.f);
    const Offset RIGHT_TOP = Offset(150.f, 50.f);
    const Offset RIGHT_BOTTOM = Offset(150.f, 100.f);

    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(8, ITEM_WIDTH, -1);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step2. Select from the LEFT_TOP to the RIGHT_BOTTOM.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    MouseSelect(LEFT_TOP, RIGHT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 4)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 5)->IsSelected());
    MouseSelectRelease();

    /**
     * @tc.steps: step3. Select from the RIGHT_TOP to the LEFT_BOTTOM.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    MouseSelect(RIGHT_TOP, LEFT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 4)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 5)->IsSelected());
    MouseSelectRelease();

    /**
     * @tc.steps: step4. Select from the LEFT_BOTTOM to the RIGHT_TOP.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    MouseSelect(LEFT_BOTTOM, RIGHT_TOP);
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 4)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 5)->IsSelected());
    MouseSelectRelease();

    /**
     * @tc.steps: step5. Select from the RIGHT_BOTTOM to the LEFT_TOP.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    MouseSelect(RIGHT_BOTTOM, LEFT_TOP);
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 4)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 5)->IsSelected());
    MouseSelectRelease();
}

/**
 * @tc.name: MouseSelect004
 * @tc.desc: Test gridItem selectable property and onSelect callback
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, MouseSelect004, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMultiSelectable(true);
    bool isSixthItemSelected = false;
    auto selectCallback = [&isSixthItemSelected](bool) { isSixthItemSelected = true; };
    for (int32_t i = 0; i < 10; i++) {
        GridItemModelNG gridItemModel;
        gridItemModel.Create();
        SetHeight(Dimension(ITEM_HEIGHT));
        if (i == 1) {
            gridItemModel.SetSelectable(false);
        }
        if (i == 2) {
            auto itemFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
            auto itemEvent = itemFrameNode->GetEventHub<EventHub>();
            itemEvent->SetEnabled(false);
        }
        if (i == 5) {
            gridItemModel.SetOnSelect(std::move(selectCallback));
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step2. Select (225, 50) - (315, 150) zone, include 2nd, 3rd, 6th, 7th item.
     * @tc.expected: The 2nd and 3rd item is not selected but 6th item is selected.
     */
    MouseSelect(Offset(225.f, 50.f), Offset(315.f, 150.f));
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 5)->IsSelected());
    EXPECT_TRUE(isSixthItemSelected);
}

/**
 * @tc.name: MouseSelect005
 * @tc.desc: Test select in other condition
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, MouseSelect005, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(8, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    const Offset startOffset = Offset(225.f, 50.f);
    const Offset endOffset = Offset(315.f, 150.f);

    /**
     * @tc.steps: step1. Select (225, 50) - (315, 150) zone with RIGHT_BUTTON.
     * @tc.expected: The item is not selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::RIGHT_BUTTON); // Use RIGHT_BUTTON to select.
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(startOffset);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(endOffset);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step2. Select (225, 50) - (315, 150) zone with HOVER
     * @tc.expected: The item is not Selected
     */
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::HOVER); // HOVER
    info.SetLocalLocation(startOffset);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(endOffset);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step3. Move distance < FRAME_SELECTION_DISTANCE
     * @tc.expected: The item is not Selected
     */
    MouseSelect(Offset(0.f, 0.f), Offset(1.f, 1.f));
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
}

/**
 * @tc.name: Drag001
 * @tc.desc: Verify drag func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Drag001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetEditable(true);
    auto onItemDragStart = [](const ItemDragInfo&, int32_t) {
        auto dragItem = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
        return AceType::DynamicCast<UINode>(dragItem);
    };
    gridModelNG.SetOnItemDragStart(onItemDragStart);
    CreateGridItem(8, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    eventHub_->onItemDragStart_ = onItemDragStart;

    GestureEvent info;
    Point globalPoint = Point(ITEM_WIDTH * 1.5, ITEM_HEIGHT / 2); // Point at the second item.
    info.SetGlobalPoint(globalPoint);

    /**
     * @tc.steps: step1. Trigger HandleOnItemDragStart, HandleOnItemDragUpdate, HandleOnItemDragEnd.
     * @tc.expected: Verify some values of the drag.
     */
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 1);
    ASSERT_NE(eventHub_->dragDropProxy_, nullptr);
    auto itemFrameNode = GetChildFrameNode(frameNode_, 1);
    EXPECT_EQ(eventHub_->draggingItem_, itemFrameNode);
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragEnd(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
    EXPECT_EQ(eventHub_->draggingItem_, nullptr);

    /**
     * @tc.steps: step2. Trigger HandleOnItemDragStart, HandleOnItemDragUpdate, HandleOnItemDragCancel.
     * @tc.expected: Verify some values of the drag.
     */
    eventHub_->HandleOnItemDragStart(info);
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragCancel();
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
    EXPECT_EQ(eventHub_->draggingItem_, nullptr);
}

/**
 * @tc.name: Drag002
 * @tc.desc: Verify drag func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Drag002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetEditable(true);
    gridModelNG.SetSupportAnimation(true);
    CreateSingleGridItem(-1, -1, 2, 3, -1, ITEM_HEIGHT);
    CreateSingleGridItem(-1, -1, 0, 2, -1, ITEM_HEIGHT);
    CreateSingleGridItem(-1, -1, 2, 1, -1, ITEM_HEIGHT);
    CreateGridItem(8, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    auto onItemDragStart = [](const ItemDragInfo&, int32_t) {
        auto dragItem = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
        return AceType::DynamicCast<UINode>(dragItem);
    };
    eventHub_->onItemDragStart_ = onItemDragStart;

    GestureEvent info;
    Point globalPoint = Point(270.f, 50.f);
    info.SetGlobalPoint(globalPoint);
    eventHub_->HandleOnItemDragStart(info);

    /**
     * @tc.steps: step1. Drag 1st item to out of Grid.
     * @tc.expected: GetOriginalIndex return number of GridItem.
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(0.f);
    dragInfo.SetY(0.f);
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, -1);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 11);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step2. Drag 2nd item to 3rd item, Drag 3 item to 2 item.
     * @tc.expected: GetOriginalIndex changed.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 1, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    eventHub_->FireOnItemDragLeave(dragInfo, -1);
    eventHub_->FireOnItemDragEnter(dragInfo);
    // 3 to 2
    eventHub_->FireOnItemDragMove(dragInfo, 2, 1);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 1);
    // SupportAnimation, ClearDragState
    eventHub_->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step3. Move something to 3rd item.
     * @tc.expected: GetOriginalIndex changed.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, -1);
    eventHub_->FireOnItemDragMove(dragInfo, -1, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    // SupportAnimation, ClearDragState
    eventHub_->FireOnItemDrop(dragInfo, -1, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step4. Move one item to wrong insertIndex.
     * @tc.expected: GetOriginalIndex unchanged.
     */
    // insertIndex < 0
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 1, -1);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);
    // insertIndex >= itemCount
    eventHub_->FireOnItemDragMove(dragInfo, 1, 11);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
}

/**
 * @tc.name: Drag003
 * @tc.desc: Verify drag func with SetLayoutDirection
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Drag003, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetLayoutDirection(FlexDirection::ROW);
    gridModelNG.SetEditable(true);
    gridModelNG.SetCellLength(ITEM_HEIGHT);
    constexpr int32_t minCount = 2;
    gridModelNG.SetMinCount(minCount);
    constexpr int32_t maxCount = 4;
    gridModelNG.SetMaxCount(maxCount);
    gridModelNG.SetSupportAnimation(true);
    const int32_t itemCount = 8;
    CreateGridItem(itemCount, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    auto onItemDragStart = [](const ItemDragInfo&, int32_t) {
        auto dragItem = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
        return AceType::DynamicCast<UINode>(dragItem);
    };
    eventHub_->onItemDragStart_ = onItemDragStart;

    GestureEvent info;
    Point globalPoint = Point(270.f, 50.f);
    info.SetGlobalPoint(globalPoint);
    eventHub_->HandleOnItemDragStart(info);

    /**
     * @tc.steps: step1. Drag 1st item to out of Grid.
     * @tc.expected: GetOriginalIndex return number of GridItem.
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(0.f);
    dragInfo.SetY(0.f);
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, -1);
    EXPECT_EQ(pattern_->GetOriginalIndex(), itemCount);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step2. Drag 2nd item to 3rd item, Drag 3 item to 2 item.
     * @tc.expected: GetOriginalIndex changed.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 1, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    eventHub_->FireOnItemDragLeave(dragInfo, -1);
    eventHub_->FireOnItemDragEnter(dragInfo);
    // 3 to 2
    eventHub_->FireOnItemDragMove(dragInfo, 2, 1);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 1);
    // SupportAnimation, ClearDragState
    eventHub_->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step3. Move something to 3rd item.
     * @tc.expected: GetOriginalIndex changed.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, -1);
    eventHub_->FireOnItemDragMove(dragInfo, -1, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    // SupportAnimation, ClearDragState
    eventHub_->FireOnItemDrop(dragInfo, -1, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step4. Move one item to wrong insertIndex.
     * @tc.expected: GetOriginalIndex unchanged.
     */
    // insertIndex < 0
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 1, -1);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);
    // insertIndex >= itemCount
    eventHub_->FireOnItemDragMove(dragInfo, 1, itemCount);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
}

/**
 * @tc.name:FocusStep001
 * @tc.desc: Test GetNextFocusNode func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(10, -1, ITEM_HEIGHT, true);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, -1));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step3. GetNextFocusNode from left_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 8;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 7));

    /**
     * @tc.steps: step4. GetNextFocusNode from right_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 9;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 8));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 4));
}

/**
 * @tc.name:FocusStep002
 * @tc.desc: Test GetNextFocusNode() with FlexDirection::COLUMN
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(10, ITEM_WIDTH, -1, true);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 400.f);

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, -1));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 8;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 7));

    /**
     * @tc.steps: step3. GetNextFocusNode from left_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step4. GetNextFocusNode from right_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 9;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 8));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 4));
}

/**
 * @tc.name: FocusStep003
 * @tc.desc: Test GetNextFocusNode func when has unfocuseable item
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep003, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(10, -1, ITEM_HEIGHT, true);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. GetNextFocusNode from 1st item and FocusStep::RIGHT.
     * @tc.expected: The 3rd item is focused.
     */
    GetChildFocusHub(frameNode_, 1)->SetFocusable(false); // The 2nd item can not focus.
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 2));
}

/**
 * @tc.name: FocusStep004
 * @tc.desc: Test GetNextFocusNode func from top boundary item in Scrollable Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep004, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(18, -1, ITEM_HEIGHT, true);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Scroll to second row
     */
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT - 1.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step2. UP
     */
    int32_t currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, -1));
    EXPECT_EQ(pattern_->gridLayoutInfo_.jumpIndex_, 3);
}

/**
 * @tc.name: FocusStep005
 * @tc.desc: Test GetNextFocusNode func from bottom boundary item in Scrollable Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep005, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(18, -1, ITEM_HEIGHT, true);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Scroll to first row
     */
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT + 1.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step2. DOWN
     */
    int32_t currentIndex = 15;
    std::map<FocusStep, int32_t> next = {
        {FocusStep::DOWN, -1},
    };
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, -1));
    EXPECT_EQ(pattern_->gridLayoutInfo_.jumpIndex_, 16);
}

/**
 * @tc.name: Focus001
 * @tc.desc: Test Foucus
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Focus001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(18, -1, ITEM_HEIGHT, true);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. When focus grid from the outside
     * @tc.expected: Will focus first child
     */
    auto gridFocus = frameNode_->GetOrCreateFocusHub();
    gridFocus->RequestFocusImmediately();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());

    /**
     * @tc.steps: step2. When grid IsCurrentFocus and has lastFocus child
     * @tc.expected: Will focus last child
     */
    GetChildFocusHub(frameNode_, 1)->RequestFocusImmediately();
    gridFocus->RequestFocusImmediately();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 1)->IsCurrentFocus());

    /**
     * @tc.steps: step3. Scroll to second row
     * @tc.expected: Would change startMainLineIndex_, focus last child.
     */
    gridFocus->RequestFocusImmediately();
    UpdateCurrentOffset(-ITEM_HEIGHT - 1.f);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 1)->IsCurrentFocus());
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
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(14, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. UpdateCurrentOffset to end, over start, over end
     * @tc.expected: veridy currentOffset_.
     */
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(-100.f));
    pattern_->UpdateCurrentOffset(200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    pattern_->UpdateCurrentOffset(-200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_BAR);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    pattern_->UpdateCurrentOffset(200.f, SCROLL_FROM_BAR);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    pattern_->UpdateCurrentOffset(-200.f, SCROLL_FROM_BAR);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    pattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::FADE);
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    pattern_->UpdateCurrentOffset(200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    pattern_->UpdateCurrentOffset(-200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
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
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();

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

    /**
     * @tc.steps: step1. When EdgeEffect::SPRING
     * @tc.expected: CreateNodePaintMethod would not trigger SetEdgeEffect
     */
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    paintMethod = AceType::DynamicCast<GridPaintMethod>(pattern_->CreateNodePaintMethod());
    EXPECT_EQ(paintMethod->edgeEffect_.Upgrade(), nullptr);

    /**
     * @tc.steps: step2. When EdgeEffect::FADE
     * @tc.expected: CreateNodePaintMethod would trigger SetEdgeEffect
     */
    pattern_->SetEdgeEffect(EdgeEffect::FADE);
    paintMethod = AceType::DynamicCast<GridPaintMethod>(pattern_->CreateNodePaintMethod());
    EXPECT_NE(paintMethod->edgeEffect_.Upgrade(), nullptr);
}

/**
 * @tc.name: ScrollLayout001
 * @tc.desc: Test UpdateOffsetOnVirtualKeyboardHeightChange
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, ScrollLayout001, TestSize.Level1)
{
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    MockPipelineBase::GetCurrent()->SetTextFieldManager(textFieldManager);
    auto textFieldPattern = AceType::MakeRefPtr<Pattern>();
    textFieldManager->SetOnFocusTextField(textFieldPattern);
    const Offset clickPosition = Offset(100.f, GRID_HEIGHT + ITEM_HEIGHT);
    textFieldManager->SetClickPosition(clickPosition);

    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMaxCount(2);
    CreateGridItem(18, -1, ITEM_HEIGHT, true);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    // MOCK GetPaintRectWithTransform()
    const float smallerHeight = GRID_HEIGHT - ITEM_HEIGHT;
    RectF gridRect(0.f, 0.f, DEVICE_WIDTH, smallerHeight);
    EXPECT_CALL(
        *(AceType::RawPtr(AceType::DynamicCast<MockRenderContext>(frameNode_->renderContext_))),
        GetPaintRectWithTransform())
        .WillRepeatedly(Return(gridRect));

    /**
     * @tc.steps: step1. Change to smaller mainSize
     * @tc.expected: The mainSize is correct
     */
    auto gridFocus = frameNode_->GetOrCreateFocusHub();
    gridFocus->RequestFocusImmediately();
    // change grid height and trigger Measure
    UpdateLayoutWrapper(frameNode_, DEVICE_WIDTH, smallerHeight);
    float gridHeight = frameNode_->GetGeometryNode()->GetFrameSize().Height();
    EXPECT_FLOAT_EQ(gridHeight, smallerHeight);
    float currentOffset = pattern_->gridLayoutInfo_.currentOffset_;
    EXPECT_FLOAT_EQ(currentOffset, -100.f);
}

/**
 * @tc.name: ScrollLayout002
 * @tc.desc: Test UpdateOffsetOnVirtualKeyboardHeightChange that currentOffset wuold not change
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, ScrollLayout002, TestSize.Level1)
{
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    MockPipelineBase::GetCurrent()->SetTextFieldManager(textFieldManager);
    auto textFieldPattern = AceType::MakeRefPtr<Pattern>();
    textFieldManager->SetOnFocusTextField(textFieldPattern);
    const Offset clickPosition = Offset(100.f, 100.f);
    textFieldManager->SetClickPosition(clickPosition);

    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMaxCount(2);
    CreateGridItem(18, -1, ITEM_HEIGHT, true);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. While axis_ == Axis::HORIZONTAL
     * @tc.expected: currentOffset_ would not change
     */
    pattern_->gridLayoutInfo_.axis_ = Axis::HORIZONTAL;
    const float smallerHeight = GRID_HEIGHT - ITEM_HEIGHT;
    // change grid height and trigger Measure
    UpdateLayoutWrapper(frameNode_, DEVICE_WIDTH, smallerHeight);
    float currentOffset = pattern_->gridLayoutInfo_.currentOffset_;
    EXPECT_FLOAT_EQ(currentOffset, 0.f);

    /**
     * @tc.steps: step2. While Grid !IsCurrentFocus()
     * @tc.expected: currentOffset_ would not change
     */
    UpdateLayoutWrapper(frameNode_, DEVICE_WIDTH, GRID_HEIGHT); // reset Grid height
    pattern_->gridLayoutInfo_.axis_ = Axis::VERTICAL;
    // change grid height and trigger Measure
    UpdateLayoutWrapper(frameNode_, DEVICE_WIDTH, smallerHeight);
    currentOffset = pattern_->gridLayoutInfo_.currentOffset_;
    EXPECT_FLOAT_EQ(currentOffset, 0.f);

    /**
     * @tc.steps: step3. While clickPosition is in Grid
     * @tc.expected: currentOffset_ would not change
     */
    UpdateLayoutWrapper(frameNode_, DEVICE_WIDTH, GRID_HEIGHT); // reset Grid height
    pattern_->gridLayoutInfo_.axis_ = Axis::VERTICAL;
    // change grid height and trigger Measure
    UpdateLayoutWrapper(frameNode_, DEVICE_WIDTH, smallerHeight);
    currentOffset = pattern_->gridLayoutInfo_.currentOffset_;
    EXPECT_FLOAT_EQ(currentOffset, 0.f);
}

/**
 * @tc.name: AdaptiveLayout001
 * @tc.desc: Test property AdaptiveLayout
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AdaptiveLayout001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetLayoutDirection(FlexDirection::ROW);
    gridModelNG.SetEditable(true);
    gridModelNG.SetCellLength(ITEM_HEIGHT);
    constexpr int32_t minCount = 4;
    gridModelNG.SetMinCount(minCount);
    constexpr int32_t maxCount = 2;
    gridModelNG.SetMaxCount(maxCount);
    constexpr int32_t gridItemNumber = 10;
    CreateGridItem(gridItemNumber, ITEM_WIDTH, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. While the before set minCount > maxCount
     * @tc.expected: would let minCount = 1, maxCount = Infinity;
     */
    constexpr int32_t colsNumber = 4; // 4 * 100(itemWidth) < 480(gridWidth)
    for (int32_t index = 0; index < gridItemNumber; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = index % colsNumber * ITEM_WIDTH;
        float offsetY = floor(index / colsNumber) * ITEM_HEIGHT;
        RectF expectRect = RectF(offsetX, offsetY, ITEM_WIDTH, ITEM_HEIGHT);
        EXPECT_TRUE(IsEqualRect(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: EventHubCoverage001
 * @tc.desc: For Coverage Rate, branches that are not need test.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, EventHubCoverage001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(8, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Supplement InitItemDragEvent branch.
     */
    auto gestureEventHub = eventHub_->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    eventHub_->InitItemDragEvent(gestureEventHub);
    auto dragEventActuator = gestureEventHub->dragEventActuator_;
    ASSERT_NE(dragEventActuator, nullptr);
    auto userCallback = dragEventActuator->userCallback_;
    ASSERT_NE(userCallback, nullptr);
    auto HandleOnItemDragStart = userCallback->GetActionStartEventFunc();
    auto HandleOnItemDragUpdate = userCallback->GetActionUpdateEventFunc();
    auto HandleOnItemDragEnd = userCallback->GetActionEndEventFunc();
    auto HandleOnItemDragCancel = userCallback->GetActionCancelEventFunc();
    GestureEvent info;
    HandleOnItemDragStart(info);
    HandleOnItemDragUpdate(info);
    HandleOnItemDragEnd(info);
    HandleOnItemDragCancel();

    EXPECT_TRUE(true);
}

/**
 * @tc.name: EventHubCoverage002
 * @tc.desc: For Coverage Rate, branches that are not normally covered.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, EventHubCoverage002, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetEditable(true);
    CreateGridItem(8, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Supplement HandleOnItemDragEnd branch,
     * has no condition that draggingItem_ is null when dragDropProxy_ was not null.
     */
    auto onItemDragStart = [](const ItemDragInfo&, int32_t) {
        auto dragItem = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
        return AceType::DynamicCast<UINode>(dragItem);
    };
    eventHub_->onItemDragStart_ = onItemDragStart;
    GestureEvent info;
    Point globalPoint = Point(270.f, 50.f);
    info.SetGlobalPoint(globalPoint);
    eventHub_->HandleOnItemDragStart(info);
    eventHub_->draggingItem_ = nullptr;
    eventHub_->HandleOnItemDragEnd(info);

    eventHub_->HandleOnItemDragStart(info);
    eventHub_->draggingItem_ = nullptr;
    eventHub_->HandleOnItemDragCancel();
    // has no condition that draggingItem_ is null when FireOnItemDrop was called.
    ItemDragInfo dragInfo;
    eventHub_->FireOnItemDrop(dragInfo, 0, 0, false);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: EventHubCoverage003
 * @tc.desc: For Coverage Rate, branches that are not need test.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, EventHubCoverage003, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetEditable(true);
    gridModelNG.SetOnItemDragEnter([](const ItemDragInfo) {});
    gridModelNG.SetOnItemDragMove([](const ItemDragInfo&, int32_t, int32_t) {});
    gridModelNG.SetOnItemDragLeave([](const ItemDragInfo&, int32_t) {});
    gridModelNG.SetOnItemDrop([](const ItemDragInfo&, int32_t, int32_t, bool) {});
    CreateGridItem(8, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);

    /**
     * @tc.steps: step1. Supplement drag callback branch.
     */
    ItemDragInfo dragInfo;
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, 1);
    eventHub_->FireOnItemDragMove(dragInfo, 1, 2);
    eventHub_->FireOnItemDrop(dragInfo, 0, 2, true);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: GirdItem Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, PerformActionTest001, TestSize.Level1)
{
    CreateGrid();
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    auto gridItemAccessibilityProperty = GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 0);

    /**
     * @tc.steps: step1. When gridItem is unSelectable
     * @tc.expected: can not be selected
     */
    gridItemPattern->SetSelectable(false);
    gridItemAccessibilityProperty->ActActionSelect();
    EXPECT_FALSE(gridItemPattern->IsSelected());
    gridItemAccessibilityProperty->ActActionClearSelection();
    EXPECT_FALSE(gridItemPattern->IsSelected());

    /**
     * @tc.steps: step2. When gridItem is Selectable
     * @tc.expected: can be selected
     */
    gridItemPattern->SetSelectable(true);
    gridItemAccessibilityProperty->ActActionSelect();
    EXPECT_TRUE(gridItemPattern->IsSelected());
    gridItemAccessibilityProperty->ActActionClearSelection();
    EXPECT_FALSE(gridItemPattern->IsSelected());
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: Gird Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, PerformActionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When grid is not Scrollable
     * @tc.expected: can not scrollpage
     */
    CreateGrid(10);
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(IsEqualCurrentOffset(0.f));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(IsEqualCurrentOffset(0.f));

    /**
     * @tc.steps: step2. When grid is Scrollable
     * @tc.expected: can scrollpage
     */
    CreateGrid();
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(IsEqualCurrentOffset(-300.f));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(IsEqualCurrentOffset(0.f));
}


/**
 * @tc.name: GridScrollTest001
 * @tc.desc: Test FireOnScrollBarUpdate Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridScrollTest001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(Dimension(5));
    ScrollBarUpdateFunc scrollFunc = [](int32_t index, Dimension offset) {
        std::optional<float> horizontalOffset = offset.ConvertToPx();
        std::optional<float> verticalOffset = offset.ConvertToPx();
        return std::make_pair(horizontalOffset, verticalOffset);
    };
    gridModelNG.SetOnScrollBarUpdate(std::move(scrollFunc));
    CreateSingleGridItem(1, 1, 1, 2);
    CreateGridItem(2, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    Dimension offset(1.0);
    auto fireOnScroll = eventHub_->FireOnScrollBarUpdate(1.0, offset);
    EXPECT_FLOAT_EQ(fireOnScroll.first.value(), 1.0f);
    EXPECT_FLOAT_EQ(fireOnScroll.second.value(), 1.0f);
}

/**
 * @tc.name: GridScrollTest002
 * @tc.desc: Test CalculateLargeItemOffset Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridScrollTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create girdItem and initialize related properties.
     */

    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(Dimension(5));
    UpdateLayoutInfo();
    auto gridScrollLayoutAlgorithm = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(pattern_->gridLayoutInfo_, 2, 0);
    ASSERT_NE(gridScrollLayoutAlgorithm, nullptr);
    auto ret = gridScrollLayoutAlgorithm->CalculateLargeItemOffset(OffsetF(100, 100), 0, 1, 0);
    EXPECT_EQ(ret.GetY(), 0.0f);
    EXPECT_EQ(ret.GetX(), 100.0f);
}

/**
 * @tc.name: GridScrollTest003
 * @tc.desc: Test CalculateLargeItemOffset Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridScrollTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create girdItem and initialize related properties.
     */

    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(Dimension(5));
    CreateGridItem(10, -1, ITEM_HEIGHT);
    UpdateLayoutInfo();
    auto gridScrollLayoutAlgorithm = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(pattern_->gridLayoutInfo_, 2, 0);
    ASSERT_NE(gridScrollLayoutAlgorithm, nullptr);
    auto ret = gridScrollLayoutAlgorithm->CalculateLargeItemOffset(OffsetF(0, 100), 1, 1, 0);
    EXPECT_EQ(ret.GetY(), 100.0f);
    EXPECT_EQ(ret.GetX(), 0.0f);
}

/**
 * @tc.name: GridScrollTest004
 * @tc.desc: Test CalculateLargeItemOffset Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridScrollTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create girdItem and initialize related properties.
     */
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");
    gridModelNG.SetRowsGap(Dimension(5));
    UpdateLayoutInfo();
    auto gridScrollLayoutAlgorithm = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(pattern_->gridLayoutInfo_, 2, 0);
    auto ret1 = gridScrollLayoutAlgorithm->CalculateLargeItemOffset(OffsetF(0, 100), 1, 1, 0);
    EXPECT_EQ(ret1.GetY(), 100.0f);
    EXPECT_EQ(ret1.GetX(), 0.0f);
}

/**
 * @tc.name: GridScrollTest005
 * @tc.desc: Test AdjustRowColSpan Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridScrollTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gridItem and Set properties.
     */
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr");

    /**
     * @tc.steps: step2. Create heading GridItem.
     */
    GridItemModelNG gridItemModelNG;
    gridItemModelNG.Create();
    gridItemModelNG.SetRowStart(-1);
    gridItemModelNG.SetRowEnd(-1);
    gridItemModelNG.SetColumnStart(-1);
    gridItemModelNG.SetColumnEnd(-1);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    auto item = GetChildFrameNode(frameNode_, 0);
    auto gridScrollLayoutAlgorithm = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(pattern_->gridLayoutInfo_, 2, 0);
    ASSERT_NE(gridScrollLayoutAlgorithm, nullptr);
    auto itemWrapper = frameNode_->GetOrCreateChildByIndex(0);
    gridScrollLayoutAlgorithm->AdjustRowColSpan(itemWrapper, nullptr, 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto layoutProperty = item->GetLayoutProperty<GridItemLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetRowStart(), -1);
    EXPECT_EQ(layoutProperty->GetRowEnd(), -1);
    EXPECT_EQ(layoutProperty->GetColumnStart(), -1);
    EXPECT_EQ(layoutProperty->GetColumnEnd(), -1);
}

/**
 * @tc.name: GridSetFrictionTest001
 * @tc.desc: Test SetFriction Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridSetFriction001, TestSize.Level1)
{
    GridModelNG gridModelNG;

    /**
     * @tc.steps: step1. friction <= 0
     * @tc.expected: friction would be default
     */
    double friction = -1;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetFriction(friction);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);

    /**
     * @tc.steps: step2. friction > 0
     * @tc.expected: friction would be itself
     */
    friction = 1;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetFriction(friction);
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, GRID_HEIGHT);
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), friction);
}

/**
 * @tc.name: ScrollTo001
 * @tc.desc: Test ScrollTo Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, ScrollTo001, TestSize.Level1)
{
    CreateGrid(10);
    pattern_->ScrollTo(ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    CreateGrid();
    pattern_->ScrollTo(ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(-ITEM_HEIGHT));
}

/**
 * @tc.name: GetTotalHeight001
 * @tc.desc: Test GetTotalHeight Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GetTotalHeight001, TestSize.Level1)
{
    CreateGrid(10);
    float height = pattern_->GetTotalHeight();
    EXPECT_EQ(height, 300.f);

    CreateGrid(20);
    height = pattern_->GetTotalHeight();
    EXPECT_EQ(height, 500.f);
}

/**
 * @tc.name: GetAverageHeight001
 * @tc.desc: Test GetAverageHeight Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GetAverageHeight001, TestSize.Level1)
{
    CreateGrid(10);
    float height = pattern_->GetAverageHeight();
    EXPECT_EQ(height, 30.f);

    CreateGrid();
    height = pattern_->GetAverageHeight();
    EXPECT_EQ(height, 25.f);
}
} // namespace OHOS::Ace::NG
