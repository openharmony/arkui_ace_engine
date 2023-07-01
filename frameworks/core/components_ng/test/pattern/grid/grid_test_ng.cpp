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
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float DEVICE_WIDTH = 720.0f;
constexpr float DEVICE_HEIGHT = 1136.0f;
constexpr float ITEM_HEIGHT = 100.f;
constexpr float ITEM_WIDTH = 100.f;
constexpr float GRID_HEIGHT = 300.f;
} // namespace

class GridTestNg : public testing::Test {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    static void SetWidth(const Dimension& width);
    static void SetHeight(const Dimension& height);
    void CreateGrid(int32_t itemNumber = 20, Axis axis = Axis::VERTICAL);
    void CreateGridItem(int32_t count = 10, float width = -1, float height = -1, bool focusable = false);
    void CreateSingleGridItem(int32_t rowStart = -1, int32_t rowEnd = -1, int32_t colStart = -1,
        int32_t colEnd = -1, float width = -1, float height = -1);
    RefPtr<LayoutWrapper> RunMeasureAndLayout(
        float width = DEVICE_WIDTH, float height = GRID_HEIGHT);
    void UpdateLayoutWrapper(
        RefPtr<LayoutWrapper>& layoutWrapper, float width = DEVICE_WIDTH, float height = GRID_HEIGHT);
    RefPtr<FrameNode> GetItemFrameNode(int32_t index);
    RectF GetItemRect(int32_t index);
    RefPtr<GridItemPattern> GetItemPattern(int32_t index);
    RefPtr<FocusHub> GetItemFocusHub(int32_t index);
    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
    void MouseSelect(Offset start, Offset end);
    void MouseSelectRelease();
    int32_t CalculateGridColumnsOrRows(float contentWidth, float gridWidth, float gutter = 0.0f, float margin = 0.0f);
    testing::AssertionResult IsEqualNextFocusNode(
        int32_t currentIndex, std::map<FocusStep, int32_t> next);
    testing::AssertionResult IsEqualRect(RectF rect, RectF expectRect);
    testing::AssertionResult IsEqualCurrentOffset(float expectOffset);
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
    RunMeasureAndLayout();
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
    RunMeasureAndLayout();
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

RefPtr<LayoutWrapper> GridTestNg::RunMeasureAndLayout(float width, float height)
{
    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
    LayoutConstraint.percentReference = { DEVICE_WIDTH, DEVICE_HEIGHT };
    LayoutConstraint.selfIdealSize = { width, height };
    LayoutConstraint.maxSize = { width, height };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
    return layoutWrapper;
}

void GridTestNg::UpdateLayoutWrapper(RefPtr<LayoutWrapper>& layoutWrapper, float width, float height)
{
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
    LayoutConstraint.percentReference = { DEVICE_WIDTH, DEVICE_HEIGHT };
    LayoutConstraint.selfIdealSize = { width, height };
    LayoutConstraint.maxSize = { width, height };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
}

RefPtr<FrameNode> GridTestNg::GetItemFrameNode(int32_t index)
{
    return AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(index));
}

RectF GridTestNg::GetItemRect(int32_t index)
{
    return GetItemFrameNode(index)->GetGeometryNode()->GetFrameRect();
}

RefPtr<GridItemPattern> GridTestNg::GetItemPattern(int32_t index)
{
    return GetItemFrameNode(index)->GetPattern<GridItemPattern>();
}

RefPtr<FocusHub> GridTestNg::GetItemFocusHub(int32_t index)
{
    return GetItemFrameNode(index)->GetOrCreateFocusHub();
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
    RunMeasureAndLayout();
}

testing::AssertionResult GridTestNg::IsEqualNextFocusNode(
    int32_t currentIndex, std::map<FocusStep, int32_t> next)
{
    RefPtr<FocusHub> currentFocusNode = GetItemFocusHub(currentIndex);
    currentFocusNode->RequestFocusImmediately();
    for (auto iter = next.begin(); iter != next.end(); iter++) {
        FocusStep step = iter->first;
        int32_t nextIndex = iter->second;
        RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
        if (nextIndex == -1 && nextFocusNode != nullptr) {
            return testing::AssertionFailure() <<
                "Next FocusNode is not null." <<
                " FocusStep: " << static_cast<int32_t>(step) <<
                " nextIndex: " << nextIndex;
        }
        if (nextIndex != -1 && nextFocusNode != GetItemFocusHub(nextIndex)) {
            return testing::AssertionFailure() <<
                "Get wrong next FocusNode." <<
                " FocusStep: " << static_cast<int32_t>(step) <<
                " nextIndex: " << nextIndex;
        }
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult GridTestNg::IsEqualRect(RectF rect, RectF expectRect)
{
    if (rect == expectRect) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() <<
        "rect: " << rect.ToString() <<
        " != " <<
        "expectRect: " << expectRect.ToString();
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
    RunMeasureAndLayout();

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
    RunMeasureAndLayout();

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
    RunMeasureAndLayout();

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
        RectF childRect = GetItemRect(index);
        float offsetX = index % colsNumber * (averageWidth + columnsGap.ConvertToPx());
        float offsetY = floor(index / colsNumber) * (ITEM_HEIGHT + rowsGap.ConvertToPx());
        RectF expectRect = RectF(offsetX, offsetY, averageWidth, ITEM_HEIGHT);
        EXPECT_TRUE(IsEqualRect(childRect, expectRect));
        EXPECT_TRUE(GetItemFrameNode(index)->IsActive());
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     * @tc.expected: The rect is equal to expectRect
     */
    const float averageWidth = DEVICE_WIDTH / 7;
    RectF rect_1 = GetItemRect(1);
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
    RectF rect_6 = GetItemRect(6);
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     * @tc.expected: The item width is zero
     */
    const float averageWidth = DEVICE_WIDTH / 2;
    RectF rect_1 = GetItemRect(1);
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
    RunMeasureAndLayout();

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
        RectF childRect = GetItemRect(index);
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
    RunMeasureAndLayout();

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
        RectF childRect = GetItemRect(index);
        float offsetX = floor(index / rowsNumber) * (ITEM_WIDTH + columnsGap.ConvertToPx());
        float offsetY = index % rowsNumber * (averageHeight + rowsGap.ConvertToPx());
        RectF expectRect = RectF(offsetX, offsetY, ITEM_WIDTH, averageHeight);
        EXPECT_TRUE(IsEqualRect(childRect, expectRect));
        EXPECT_TRUE(GetItemFrameNode(index)->IsActive());
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     * @tc.expected: The rect is equal to expectRect
     */
    const float averageHeight = GRID_HEIGHT / 7;
    RectF rect_1 = GetItemRect(1);
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
    RectF rect_6 = GetItemRect(6);
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     * @tc.expected: The item height is zero
     */
    const float averageHeight = GRID_HEIGHT / 2;
    RectF rect_1 = GetItemRect(1);
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
    RunMeasureAndLayout();

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
        RectF childRect = GetItemRect(index);
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
    RunMeasureAndLayout();

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
    /**
     *    0__180_360_540_720
     * 75 |___|___|___|___|
     * 150|___|___|___|___|
     * 225|___|___|___|___|
     * 300|___|___|___|___|
     */
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Set both columns/rows Template
     * @tc.expected: The gridItem width/height will slef-adaption
     */
    constexpr int32_t colsNumber = 4;
    constexpr int32_t rowsNumber = 4;
    const float averageWidth = DEVICE_WIDTH / colsNumber;
    const float averageHeight = GRID_HEIGHT / rowsNumber;
    for (int32_t index = 0; index < gridItemNumber; index++) {
        RectF childRect = GetItemRect(index);
        float offsetX = index % colsNumber * averageWidth;
        float offsetY = floor(index / colsNumber) * averageHeight;
        RectF expectRect = RectF(offsetX, offsetY, averageWidth, averageHeight);
        EXPECT_TRUE(IsEqualRect(childRect, expectRect));
        EXPECT_TRUE(GetItemFrameNode(index)->IsActive());
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
    /**
     *    0__110_220_330_430_________720
     * 105|_0_|_1_|___|___|          |
     * 210|___|___|___|___|          |
     * 300|__________________________|
     */
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    constexpr int32_t colsNumber = 4;
    constexpr int32_t activeCount = 8;
    for (int32_t index = 0; index < gridItemNumber; index++) {
        if (index < activeCount) {
            RectF childRect = GetItemRect(index);
            float offsetX = index % colsNumber * (ITEM_WIDTH + columnsGap.ConvertToPx());
            float offsetY = floor(index / colsNumber) * (ITEM_HEIGHT + rowsGap.ConvertToPx());
            RectF expectRect = RectF(offsetX, offsetY, ITEM_WIDTH, ITEM_HEIGHT);
            EXPECT_TRUE(IsEqualRect(childRect, expectRect)) << "index: " << index;
            EXPECT_TRUE(GetItemFrameNode(index)->IsActive());
        } else {
            // beyond grid size, would not load
            EXPECT_FALSE(GetItemFrameNode(index)->IsActive());
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
    /**
     *    0__110_220_330_430_________720
     * 105|___|___|_1_|_0_|          |
     * 210|___|___|___|___|          |
     * 300|__________________________|
     */
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    constexpr int32_t colsNumber = 4;
    constexpr int32_t activeCount = 8;
    const float colsWidthTotal = colsNumber * ITEM_WIDTH + (colsNumber - 1) * columnsGap.ConvertToPx();
    for (int32_t index = 0; index < gridItemNumber; index++) {
        if (index < activeCount) {
            RectF childRect = GetItemRect(index);
            float offsetX = colsWidthTotal - (index % colsNumber + 1) * ITEM_WIDTH -
                index % colsNumber * columnsGap.ConvertToPx();
            float offsetY = floor(index / colsNumber) * (ITEM_HEIGHT + rowsGap.ConvertToPx());
            RectF expectRect = RectF(offsetX, offsetY, ITEM_WIDTH, ITEM_HEIGHT);
            EXPECT_TRUE(IsEqualRect(childRect, expectRect)) << "index: " << index;
            EXPECT_TRUE(GetItemFrameNode(index)->IsActive());
        } else {
            // beyond grid size, would not load
            EXPECT_FALSE(GetItemFrameNode(index)->IsActive());
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
    /**
     *    0__110_220_330_440_540_____720
     * 105|_0_|___|___|___|___|      |
     * 210|_1_|___|___|___|___|      |
     * 300|__________________________|
     */
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    constexpr int32_t rowsNumber = 2;
    for (int32_t index = 0; index < gridItemNumber; index++) {
        RectF childRect = GetItemRect(index);
        float offsetX = floor(index / rowsNumber) * (ITEM_WIDTH + columnsGap.ConvertToPx());
        float offsetY = index % rowsNumber * (ITEM_HEIGHT + rowsGap.ConvertToPx());
        RectF expectRect = RectF(offsetX, offsetY, ITEM_WIDTH, ITEM_HEIGHT);
        EXPECT_TRUE(IsEqualRect(childRect, expectRect)) << "index: " << index;
        EXPECT_TRUE(GetItemFrameNode(index)->IsActive());
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
    /**
     *    0__110_220_330_440_540_____720
     * 105|_1_|___|___|___|___|      |
     * 210|_0_|___|___|___|___|      |
     * 300|__________________________|
     */
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    constexpr int32_t rowsNumber = 2;
    const float rowsHeightTotal = rowsNumber * ITEM_HEIGHT + (rowsNumber - 1) * rowsGap.ConvertToPx();
    for (int32_t index = 0; index < gridItemNumber; index++) {
        RectF childRect = GetItemRect(index);
        float offsetX = floor(index / rowsNumber) * (ITEM_WIDTH + columnsGap.ConvertToPx());
        float offsetY = rowsHeightTotal - (index % rowsNumber + 1) * ITEM_HEIGHT -
            index % rowsNumber * rowsGap.ConvertToPx();
        RectF expectRect = RectF(offsetX, offsetY, ITEM_WIDTH, ITEM_HEIGHT);
        EXPECT_TRUE(IsEqualRect(childRect, expectRect)) << "index: " << index;
        EXPECT_TRUE(GetItemFrameNode(index)->IsActive());
    }
}

/**
 * @tc.name: AttrGridItem001
 * @tc.desc: Test property rowStart/rowEnd/colStart/colEnd with colTemplate/rowTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrGridItem001, TestSize.Level1)
{
    /**
     *    0__180_360_540_720
     *  75|_____1_____|   |
     * 150|___|   0   | 2 |
     * 225|___|_______|   |
     * 300|___|___|___|___|
     */
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
    RunMeasureAndLayout();

    RectF rect_0 = GetItemRect(0);
    const float averageWidth = DEVICE_WIDTH / 4;
    const float averageHeight = GRID_HEIGHT / 4;
    const float offsetX_0 = averageWidth;
    const float offsetY_0 = averageHeight;
    const float width_0 = averageWidth * 2;
    const float height_0 = averageHeight * 2;
    const RectF expectRect_0 = RectF(offsetX_0, offsetY_0, width_0, height_0);
    EXPECT_TRUE(IsEqualRect(rect_0, expectRect_0));

    RectF rect_1 = GetItemRect(1);
    const float offsetX_1 = 0.f;
    const float offsetY_1 = 0.f;
    const float width_1 = averageWidth * 3;
    const float height_1 = averageHeight;
    const RectF expectRect_1 = RectF(offsetX_1, offsetY_1, width_1, height_1);
    EXPECT_TRUE(IsEqualRect(rect_1, expectRect_1));

    RectF rect_2 = GetItemRect(2);
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
    /**
     *    0__100_200_300
     *  75| 0 |   | 2 |
     * 150|___| 1 |___|
     * 225|___|___|___|
     * 300|___|___|___|
     */
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
    RunMeasureAndLayout(300.f);

    const float averageHeight = GRID_HEIGHT / 4;
    EXPECT_TRUE(IsEqualRect(GetItemRect(0), RectF(
        0.f,
        0.f,
        ITEM_WIDTH,
        averageHeight * 2
    )));
    EXPECT_TRUE(IsEqualRect(GetItemRect(1), RectF(
        ITEM_WIDTH,
        0.f,
        ITEM_WIDTH,
        averageHeight * 3
    )));
    EXPECT_TRUE(IsEqualRect(GetItemRect(2), RectF(
        ITEM_WIDTH * 2,
        0.f,
        ITEM_WIDTH,
        averageHeight * 2
    )));

    UpdateCurrentOffset(-ITEM_WIDTH);
    EXPECT_TRUE(IsEqualRect(GetItemRect(1), RectF(
        ITEM_WIDTH,
        0.f,
        ITEM_WIDTH,
        averageHeight * 3
    )));
    EXPECT_TRUE(IsEqualRect(GetItemRect(2), RectF(
        ITEM_WIDTH * 2,
        0.f,
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
    /**
     *    0__180_360_540_720
     * 100|___0___|___|___|
     * 200|_____1_____|___|
     * 300|_2_|___|___|___|
     */
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
    RunMeasureAndLayout();

    const float averageWidth = DEVICE_WIDTH / 4;
    EXPECT_TRUE(IsEqualRect(GetItemRect(0), RectF(
        0.f,
        0.f,
        averageWidth * 2,
        ITEM_HEIGHT
    )));
    EXPECT_TRUE(IsEqualRect(GetItemRect(1), RectF(
        0.f,
        ITEM_HEIGHT,
        averageWidth * 3,
        ITEM_HEIGHT
    )));
    EXPECT_TRUE(IsEqualRect(GetItemRect(2), RectF(
        0.f,
        ITEM_HEIGHT * 2,
        averageWidth,
        ITEM_HEIGHT
    )));

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualRect(GetItemRect(1), RectF(
        0.f,
        0.f,
        averageWidth * 3,
        ITEM_HEIGHT
    )));
    EXPECT_TRUE(IsEqualRect(GetItemRect(2), RectF(
        0.f,
        ITEM_HEIGHT,
        averageWidth,
        ITEM_HEIGHT
    )));
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
    RunMeasureAndLayout();

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
    RunMeasureAndLayout();
    EXPECT_FALSE(pattern_->AnimateTo(100.f, 200.f, Curves::LINEAR));

    /**
     * @tc.steps: step2. isConfigScrollable_
     */
    CreateGrid();
    EXPECT_TRUE(pattern_->AnimateTo(100.f, 200.f, Curves::LINEAR));
    ASSERT_NE(pattern_->animator_, nullptr);

    /**
     * @tc.steps: step3. animator_->Stop()
     */
    pattern_->animator_->Stop();
    EXPECT_TRUE(pattern_->AnimateTo(100.f, 200.f, Curves::LINEAR));
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
    auto callback_1 = pattern_->scrollableEvent_->GetScrollPositionCallback();
    auto callback_2 = pattern_->scrollableEvent_->GetScrollEndCallback();
    EXPECT_TRUE(callback_1(ITEM_HEIGHT, SCROLL_FROM_UPDATE));
    EXPECT_TRUE(callback_1(ITEM_HEIGHT, SCROLL_FROM_UPDATE));
    EXPECT_TRUE(callback_1(ITEM_HEIGHT, SCROLL_FROM_START));
    callback_2();
    auto coordinationEvent = AceType::MakeRefPtr<ScrollableCoordinationEvent>();
    auto event1 = [](double) {};
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
 * @tc.name: EventHub001
 * @tc.desc: Test GetInsertPosition func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, EventHub001, TestSize.Level1)
{
    CreateGrid();
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
    EXPECT_EQ(eventHub_->GetInsertPosition(90.f, 50.f), 0); // first item
    EXPECT_EQ(eventHub_->GetInsertPosition(360.f, 50.f), 1); // between the second and third
    EXPECT_EQ(eventHub_->GetInsertPosition(360.f, 100.f), 1); // between the 2nd, 3rd, 6th, 7th
    EXPECT_EQ(eventHub_->GetInsertPosition(180.f, 300.f), 8); // in grid but not on item
    pattern_->GetGridLayoutInfo().currentRect_ = RectF(0.f, 0.f, 180.f, 300.f);
    EXPECT_EQ(eventHub_->GetInsertPosition(180.f, 300.f), 8); // on currentRect_

    /**
     * @tc.steps: step2. call GetFrameNodeChildSize func.
     */
    EXPECT_EQ(eventHub_->GetFrameNodeChildSize(), 20);
}

/**
 * @tc.name: PositionController001
 * @tc.desc: Test positionController func in VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, PositionController001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test JumpTo func.
     * @tc.expected: Verify return value.
     */
    CreateGrid();
    auto controller = pattern_->positionController_;
    controller->JumpTo(1, false, ScrollAlign::START, 3);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 1);

    /**
     * @tc.steps: step2. Test AnimateTo func.
     * @tc.expected: Verify return value.
     */
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
    EXPECT_EQ(currentOffset, Offset(0, 20.f));

    /**
     * @tc.steps: step5. Test ScrollToEdge func.
     * @tc.expected: Verify return value.
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 1);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 1);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 19);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 0);

    /**
     * @tc.steps: step6. Test ScrollPage func.
     * @tc.expected: Verify currentOffset.
     */
    RunMeasureAndLayout();
    controller->ScrollPage(true, true);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset(0, 300.f));
    controller->ScrollPage(false, true);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset(0, 0));

    /**
     * @tc.steps: step7. Test IsAtEnd func.
     */
    EXPECT_FALSE(controller->IsAtEnd());
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    RunMeasureAndLayout();
    EXPECT_TRUE(controller->IsAtEnd());
}

/**
 * @tc.name: PositionController002
 * @tc.desc: Test positionController func in HORIZONTAL Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, PositionController002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Change Grid width to 300.
     */
    CreateGrid(20, Axis::HORIZONTAL);
    RunMeasureAndLayout(300.f);

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
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, -1);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, -1);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 19);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 0);

    /**
     * @tc.steps: step5. Test ScrollPage func.
     * @tc.expected: Verify currentOffset.
     */
    pattern_->UpdateCurrentOffset(-20.f, SCROLL_FROM_UPDATE);
    controller->ScrollPage(true, true);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset(0, 0));
    EXPECT_EQ(pattern_->GetMainContentSize(), 720.f);
    controller->ScrollPage(false, true);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset(0, 0));
}

/**
 * @tc.name: PositionController003
 * @tc.desc: Test positionController func in Axis::NONE Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, PositionController003, TestSize.Level1)
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
 * @tc.name: LayoutInfo001
 * @tc.desc: Test UpdateEndLine func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, LayoutInfo001, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(8, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Change Grid size.
     * @tc.expected: Verify endMainLineIndex_.
     */
    RunMeasureAndLayout(DEVICE_WIDTH, 100.f);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().endMainLineIndex_, 1);
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
    RunMeasureAndLayout();

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
    RunMeasureAndLayout();

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
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(14, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Run SetSpecificSupportAction func.
     * @tc.expected: The return_value is correct.
     */
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: GridAccessibilityTest004
 * @tc.desc: Test Accessibility SetSpecificSupportAction func with non-scrollable Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridAccessibilityTest004, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    CreateGridItem(14, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Run SetSpecificSupportAction func.
     * @tc.expected: The return_value is correct.
     */
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: GridAccessibilityTest005
 * @tc.desc: Test Accessibility SetSpecificSupportAction func with
 * scrollable Grid and scroll the Grid to the top
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridAccessibilityTest005, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(14, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Run SetSpecificSupportAction func.
     * @tc.expected: The return_value is correct.
     */
    pattern_->UpdateCurrentOffset(100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: GridAccessibilityTest006
 * @tc.desc: Test Accessibility SetSpecificSupportAction func with
 * scrollable Grid and scroll the Grid to the bottom
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridAccessibilityTest006, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(14, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Run SetSpecificSupportAction func.
     * @tc.expected: The return_value is correct.
     */
    pattern_->UpdateCurrentOffset(-200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
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
    CreateGridItem(10, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get 2nd GridItem.
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

    /**
     * @tc.steps: step3. Run SetSpecificSupportAction func.
     * @tc.expected: Verify return value.
     */
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Get 1st GridItem.
     */
    auto itemFrameNode = GetItemFrameNode(0);
    ASSERT_NE(itemFrameNode, nullptr);
    auto itemAccessibility = itemFrameNode->GetAccessibilityProperty<GridItemAccessibilityProperty>();
    ASSERT_NE(itemAccessibility, nullptr);

    /**
     * @tc.steps: step2. Run GetCollectionItemInfo func.
     * @tc.expected: Verify return value.
     */
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Click the (0, 0) point of firstItem.
     * @tc.expected: item not selected on MouseAction::PRESS.
     */
    MouseSelect(Offset(0.f, 0.f), Offset(0.f, 0.f));
    EXPECT_FALSE(GetItemPattern(0)->IsSelected());
}

/**
 * @tc.name: MouseSelect002
 * @tc.desc: Test mouse box selection, PRESS, MOVE and RELEASE the mouse
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Select (0, 0) - (180, 100) zone.
     * @tc.expected: The 1st, 2nd, 5th, 6th items are selected.
     */
    MouseSelect(Offset(0.f, 0.f), Offset(180.f, 100.f));
    EXPECT_TRUE(GetItemPattern(0)->IsSelected());
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
    EXPECT_TRUE(GetItemPattern(4)->IsSelected());
    EXPECT_TRUE(GetItemPattern(5)->IsSelected());
    MouseSelectRelease();

    /**
     * @tc.steps: step2. Select (90, 50) - (270, 150) zone, from the LEFT_TOP to the RIGHT_BOTTOM.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    MouseSelect(LEFT_TOP, RIGHT_BOTTOM);
    EXPECT_TRUE(GetItemPattern(0)->IsSelected());
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
    EXPECT_TRUE(GetItemPattern(4)->IsSelected());
    EXPECT_TRUE(GetItemPattern(5)->IsSelected());
    MouseSelectRelease();

    /**
     * @tc.steps: step3. Select (90, 50) - (270, 150) zone, from the RIGHT_TOP to the LEFT_BOTTOM.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    MouseSelect(RIGHT_TOP, LEFT_BOTTOM);
    EXPECT_TRUE(GetItemPattern(0)->IsSelected());
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
    EXPECT_TRUE(GetItemPattern(4)->IsSelected());
    EXPECT_TRUE(GetItemPattern(5)->IsSelected());
    MouseSelectRelease();

    /**
     * @tc.steps: step4. Select (90, 50) - (270, 150) zone, from the LEFT_BOTTOM to the RIGHT_TOP.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    MouseSelect(LEFT_BOTTOM, RIGHT_TOP);
    EXPECT_TRUE(GetItemPattern(0)->IsSelected());
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
    EXPECT_TRUE(GetItemPattern(4)->IsSelected());
    EXPECT_TRUE(GetItemPattern(5)->IsSelected());
    MouseSelectRelease();

    /**
     * @tc.steps: step5. Select (90, 50) - (270, 150) zone, from the RIGHT_BOTTOM to the LEFT_TOP.
     * @tc.expected: The 1st, 2nd, 5th, 6th are selected.
     */
    MouseSelect(RIGHT_BOTTOM, LEFT_TOP);
    EXPECT_TRUE(GetItemPattern(0)->IsSelected());
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
    EXPECT_TRUE(GetItemPattern(4)->IsSelected());
    EXPECT_TRUE(GetItemPattern(5)->IsSelected());
    MouseSelectRelease();
}

/**
 * @tc.name: MouseSelect003
 * @tc.desc: Test gridItem selectable property and onSelect callback
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, MouseSelect003, TestSize.Level1)
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
        /**
         *  ___180__360___540___720
         * |____|__1__|__2__|____|100
         * |____|__5__|_____|____|200
         * |____|_____|          300
         */
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Select (225, 50) - (315, 150) zone, include 2nd, 3rd, 6th, 7th item.
     * @tc.expected: The 2nd and 3rd item is not selected but 6th item is selected.
     */
    MouseSelect(Offset(225.f, 50.f), Offset(315.f, 150.f));
    EXPECT_FALSE(GetItemPattern(1)->IsSelected());
    EXPECT_FALSE(GetItemPattern(2)->IsSelected());
    EXPECT_TRUE(GetItemPattern(5)->IsSelected());
    EXPECT_TRUE(isSixthItemSelected);
}

/**
 * @tc.name: MouseSelect004
 * @tc.desc: Test OnMouseSelectAll func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, MouseSelect004, TestSize.Level1)
{
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    gridModelNG.SetMultiSelectable(true);
    CreateGridItem(8, -1, ITEM_HEIGHT);
    GetInstance();
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
    RunMeasureAndLayout();

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
    EXPECT_FALSE(GetItemPattern(1)->IsSelected());

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
    EXPECT_FALSE(GetItemPattern(1)->IsSelected());

    /**
     * @tc.steps: step3. Move distance < FRAME_SELECTION_DISTANCE
     * @tc.expected: The item is not Selected
     */
    MouseSelect(Offset(0.f, 0.f), Offset(1.f, 1.f));
    EXPECT_FALSE(GetItemPattern(0)->IsSelected());
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
    RunMeasureAndLayout();
    eventHub_->onItemDragStart_ = onItemDragStart;

    GestureEvent info;
    Point globalPoint = Point(270.f, 50.f); // Point at the second item.
    info.SetGlobalPoint(globalPoint);

    /**
     * @tc.steps: step1. Trigger HandleOnItemDragStart, HandleOnItemDragUpdate, HandleOnItemDragEnd.
     * @tc.expected: Verify some values of the drag.
     */
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 1);
    ASSERT_NE(eventHub_->dragDropProxy_, nullptr);
    auto itemFrameNode = GetItemFrameNode(1);
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
    RunMeasureAndLayout();
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
    RunMeasureAndLayout();

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
    RunMeasureAndLayout();

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
    RunMeasureAndLayout();

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
    RunMeasureAndLayout();
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
    RunMeasureAndLayout();
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
    RunMeasureAndLayout();

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
    RunMeasureAndLayout();

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
    RunMeasureAndLayout();

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
    RunMeasureAndLayout();
}

/**
 * @tc.name:FocusStep001
 * @tc.desc: Test GetNextFocusNode func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep001, TestSize.Level1)
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
    CreateGridItem(10, -1, ITEM_HEIGHT, true);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    constexpr int32_t currentIndex1 = 0;
    std::map<FocusStep, int32_t> next1 = {
        {FocusStep::NONE, -1},
        {FocusStep::LEFT, -1},
        {FocusStep::UP, -1},
        {FocusStep::RIGHT, 1},
        {FocusStep::DOWN, 4},
        {FocusStep::LEFT_END, -1},
        {FocusStep::UP_END, -1},
        {FocusStep::RIGHT_END, 3},
        {FocusStep::DOWN_END, -1}
    };
    EXPECT_TRUE(IsEqualNextFocusNode(currentIndex1, next1));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    constexpr int32_t currentIndex2 = 3;
    std::map<FocusStep, int32_t> next2 = {
        {FocusStep::NONE, -1},
        {FocusStep::LEFT, 2},
        {FocusStep::UP, -1},
        {FocusStep::RIGHT, 4},
        {FocusStep::DOWN, 7},
        {FocusStep::LEFT_END, 0},
        {FocusStep::UP_END, -1},
        {FocusStep::RIGHT_END, -1},
        {FocusStep::DOWN_END, -1}
    };
    EXPECT_TRUE(IsEqualNextFocusNode(currentIndex2, next2));

    /**
     * @tc.steps: step3. GetNextFocusNode from left_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    constexpr int32_t currentIndex3 = 8;
    std::map<FocusStep, int32_t> next3 = {
        {FocusStep::NONE, -1},
        {FocusStep::LEFT, 7},
        {FocusStep::UP, 4},
        {FocusStep::RIGHT, 9},
        {FocusStep::DOWN, -1},
        {FocusStep::LEFT_END, -1},
        {FocusStep::UP_END, -1},
        {FocusStep::RIGHT_END, 9},
        {FocusStep::DOWN_END, -1}
    };
    EXPECT_TRUE(IsEqualNextFocusNode(currentIndex3, next3));

    /**
     * @tc.steps: step4. GetNextFocusNode from right_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    constexpr int32_t currentIndex4 = 9;
    std::map<FocusStep, int32_t> next4 = {
        {FocusStep::NONE, -1},
        {FocusStep::LEFT, 8},
        {FocusStep::UP, 5},
        {FocusStep::RIGHT, -1},
        {FocusStep::DOWN, -1},
        {FocusStep::LEFT_END, 8},
        {FocusStep::UP_END, -1},
        {FocusStep::RIGHT_END, -1},
        {FocusStep::DOWN_END, -1}
    };
    EXPECT_TRUE(IsEqualNextFocusNode(currentIndex4, next4));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     * @tc.expected: Verify all condition of FocusStep.
     */
    constexpr int32_t currentIndex5 = 5;
    std::map<FocusStep, int32_t> next5 = {
        {FocusStep::NONE, -1},
        {FocusStep::LEFT, 4},
        {FocusStep::UP, 1},
        {FocusStep::RIGHT, 6},
        {FocusStep::DOWN, 9},
        {FocusStep::LEFT_END, 4},
        {FocusStep::UP_END, -1},
        {FocusStep::RIGHT_END, 7},
        {FocusStep::DOWN_END, -1}
    };
    EXPECT_TRUE(IsEqualNextFocusNode(currentIndex5, next5));
}

/**
 * @tc.name:FocusStep002
 * @tc.desc: Test GetNextFocusNode() with FlexDirection::COLUMN
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep002, TestSize.Level1)
{
    /**
     *  ___180__360__540__720
     * |____|____|____|     100
     * |____|____|____|     200
     * |____|____|          300
     * |____|____|          400
     */
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);
    gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItem(10, ITEM_WIDTH, -1, true);
    GetInstance();
    RunMeasureAndLayout(DEVICE_WIDTH, 400.f);

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    constexpr int32_t currentIndex1 = 0;
    std::map<FocusStep, int32_t> next1 = {
        {FocusStep::NONE, -1},
        {FocusStep::LEFT, -1},
        {FocusStep::UP, -1},
        {FocusStep::RIGHT, 4},
        {FocusStep::DOWN, 1},
        {FocusStep::LEFT_END, -1},
        {FocusStep::UP_END, -1},
        {FocusStep::RIGHT_END, -1},
        {FocusStep::DOWN_END, 3}
    };
    EXPECT_TRUE(IsEqualNextFocusNode(currentIndex1, next1));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    constexpr int32_t currentIndex2 = 8;
    std::map<FocusStep, int32_t> next2 = {
        {FocusStep::NONE, -1},
        {FocusStep::LEFT, 4},
        {FocusStep::UP, 7},
        {FocusStep::RIGHT, -1},
        {FocusStep::DOWN, 9},
        {FocusStep::LEFT_END, -1},
        {FocusStep::UP_END, -1},
        {FocusStep::RIGHT_END, -1},
        {FocusStep::DOWN_END, 9}
    };
    EXPECT_TRUE(IsEqualNextFocusNode(currentIndex2, next2));

    /**
     * @tc.steps: step3. GetNextFocusNode from left_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    constexpr int32_t currentIndex3 = 3;
    std::map<FocusStep, int32_t> next3 = {
        {FocusStep::NONE, -1},
        {FocusStep::LEFT, -1},
        {FocusStep::UP, 2},
        {FocusStep::RIGHT, 7},
        {FocusStep::DOWN, 4},
        {FocusStep::LEFT_END, -1},
        {FocusStep::UP_END, 0},
        {FocusStep::RIGHT_END, -1},
        {FocusStep::DOWN_END, -1}
    };
    EXPECT_TRUE(IsEqualNextFocusNode(currentIndex3, next3));

    /**
     * @tc.steps: step4. GetNextFocusNode from right_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    constexpr int32_t currentIndex4 = 9;
    std::map<FocusStep, int32_t> next4 = {
        {FocusStep::NONE, -1},
        {FocusStep::LEFT, 5},
        {FocusStep::UP, 8},
        {FocusStep::RIGHT, -1},
        {FocusStep::DOWN, -1},
        {FocusStep::LEFT_END, -1},
        {FocusStep::UP_END, 8},
        {FocusStep::RIGHT_END, -1},
        {FocusStep::DOWN_END, -1}
    };
    EXPECT_TRUE(IsEqualNextFocusNode(currentIndex4, next4));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     * @tc.expected: Verify all condition of FocusStep.
     */
    constexpr int32_t currentIndex5 = 5;
    std::map<FocusStep, int32_t> next5 = {
        {FocusStep::NONE, -1},
        {FocusStep::LEFT, 1},
        {FocusStep::UP, 4},
        {FocusStep::RIGHT, 9},
        {FocusStep::DOWN, 6},
        {FocusStep::LEFT_END, -1},
        {FocusStep::UP_END, 4},
        {FocusStep::RIGHT_END, -1},
        {FocusStep::DOWN_END, 7}
    };
    EXPECT_TRUE(IsEqualNextFocusNode(currentIndex5, next5));
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. GetNextFocusNode from 1st item and FocusStep::RIGHT.
     * @tc.expected: The 3rd item is focused.
     */
    GetItemFocusHub(1)->SetFocusable(false); // The 2nd item can not focus.
    constexpr int32_t currentIndex = 0;
    std::map<FocusStep, int32_t> next = {
        {FocusStep::RIGHT, 2},
    };
    EXPECT_TRUE(IsEqualNextFocusNode(currentIndex, next));
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Scroll to second row
     */
    constexpr float scrollOffset = -ITEM_HEIGHT - 1.f;
    UpdateCurrentOffset(scrollOffset);

    /**
     * @tc.steps: step2. UP
     */
    constexpr int32_t currentIndex = 4;
    std::map<FocusStep, int32_t> next = {
        {FocusStep::UP, -1},
    };
    EXPECT_TRUE(IsEqualNextFocusNode(currentIndex, next));
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Scroll to first row
     */
    constexpr float scrollOffset = -ITEM_HEIGHT + 1.f;
    UpdateCurrentOffset(scrollOffset);

    /**
     * @tc.steps: step2. DOWN
     */
    constexpr int32_t currentIndex = 15;
    std::map<FocusStep, int32_t> next = {
        {FocusStep::DOWN, -1},
    };
    EXPECT_TRUE(IsEqualNextFocusNode(currentIndex, next));
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. When focus grid from the outside
     * @tc.expected: Will focus first child
     */
    auto gridFocus = frameNode_->GetOrCreateFocusHub();
    gridFocus->RequestFocusImmediately();
    RunMeasureAndLayout();
    EXPECT_TRUE(GetItemFocusHub(0)->IsCurrentFocus());

    /**
     * @tc.steps: step2. When grid IsCurrentFocus and has lastFocus child
     * @tc.expected: Will focus last child
     */
    GetItemFocusHub(1)->RequestFocusImmediately();
    gridFocus->RequestFocusImmediately();
    RunMeasureAndLayout();
    EXPECT_TRUE(GetItemFocusHub(1)->IsCurrentFocus());

    /**
     * @tc.steps: step3. Scroll to second row
     * @tc.expected: Would change startMainLineIndex_, focus last child.
     */
    gridFocus->RequestFocusImmediately();
    UpdateCurrentOffset(-ITEM_HEIGHT - 1.f);
    EXPECT_TRUE(GetItemFocusHub(1)->IsCurrentFocus());
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
    auto layoutWrapper = RunMeasureAndLayout();

    /**
     * @tc.steps: step1. UpdateCurrentOffset to end, over start, over end
     * @tc.expected: veridy currentOffset_.
     */
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_TRUE(IsEqualCurrentOffset(-100.f));
    pattern_->UpdateCurrentOffset(200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    pattern_->UpdateCurrentOffset(-200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_BAR);
    RunMeasureAndLayout();
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    pattern_->UpdateCurrentOffset(200.f, SCROLL_FROM_BAR);
    RunMeasureAndLayout();
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    pattern_->UpdateCurrentOffset(-200.f, SCROLL_FROM_BAR);
    RunMeasureAndLayout();
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    pattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::FADE);
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    pattern_->UpdateCurrentOffset(200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    pattern_->UpdateCurrentOffset(-200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    pattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    pattern_->UpdateCurrentOffset(200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    pattern_->UpdateCurrentOffset(-200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    pattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_BAR);
    RunMeasureAndLayout();
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    pattern_->UpdateCurrentOffset(200.f, SCROLL_FROM_BAR);
    RunMeasureAndLayout();
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    pattern_->UpdateCurrentOffset(-200.f, SCROLL_FROM_BAR);
    RunMeasureAndLayout();
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
    auto layoutWrapper = RunMeasureAndLayout();

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
    UpdateLayoutWrapper(layoutWrapper, DEVICE_WIDTH, smallerHeight);
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
    auto layoutWrapper = RunMeasureAndLayout();

    /**
     * @tc.steps: step1. While axis_ == Axis::HORIZONTAL
     * @tc.expected: currentOffset_ would not change
     */
    pattern_->gridLayoutInfo_.axis_ = Axis::HORIZONTAL;
    const float smallerHeight = GRID_HEIGHT - ITEM_HEIGHT;
    // change grid height and trigger Measure
    UpdateLayoutWrapper(layoutWrapper, DEVICE_WIDTH, smallerHeight);
    float currentOffset = pattern_->gridLayoutInfo_.currentOffset_;
    EXPECT_FLOAT_EQ(currentOffset, 0.f);

    /**
     * @tc.steps: step2. While Grid !IsCurrentFocus()
     * @tc.expected: currentOffset_ would not change
     */
    UpdateLayoutWrapper(layoutWrapper, DEVICE_WIDTH, GRID_HEIGHT); // reset Grid height
    pattern_->gridLayoutInfo_.axis_ = Axis::VERTICAL;
    // change grid height and trigger Measure
    UpdateLayoutWrapper(layoutWrapper, DEVICE_WIDTH, smallerHeight);
    currentOffset = pattern_->gridLayoutInfo_.currentOffset_;
    EXPECT_FLOAT_EQ(currentOffset, 0.f);

    /**
     * @tc.steps: step3. While clickPosition is in Grid
     * @tc.expected: currentOffset_ would not change
     */
    UpdateLayoutWrapper(layoutWrapper, DEVICE_WIDTH, GRID_HEIGHT); // reset Grid height
    pattern_->gridLayoutInfo_.axis_ = Axis::VERTICAL;
    // change grid height and trigger Measure
    UpdateLayoutWrapper(layoutWrapper, DEVICE_WIDTH, smallerHeight);
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. While the before set minCount > maxCount
     * @tc.expected: would let minCount = 1, maxCount = Infinity;
     */
    constexpr int32_t colsNumber = 7; // 7 * 100(itemWidth) < 720(gridWidth)
    for (int32_t index = 0; index < gridItemNumber; index++) {
        RectF childRect = GetItemRect(index);
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
    RunMeasureAndLayout();

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
    RunMeasureAndLayout();

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
    RunMeasureAndLayout();

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
 * @tc.name: ModelCoverage001
 * @tc.desc: For Coverage Rate, branches that are not need test.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, ModelCoverage001, TestSize.Level1)
{
    GridItemModelNG gridItemModelNG;
    gridItemModelNG.Create([](int32_t) {}, true);
    gridItemModelNG.Create([](int32_t) {}, false);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: GirdItem Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create girdItem and initialize related properties.
     */
    GridItemModelNG gridItemModelNG;
    gridItemModelNG.Create();

    /**
     * @tc.steps: step2. Get girdItem frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto gridItemPattern = frameNode->GetPattern<GridItemPattern>();
    ASSERT_NE(gridItemPattern, nullptr);
    gridItemPattern->selectable_ = false;
    gridItemPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get girdItem accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto gridItemAccessibilityProperty = frameNode->GetAccessibilityProperty<GridItemAccessibilityProperty>();
    ASSERT_NE(gridItemAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When girdItem is not Selectable, call the callback function in gridItemAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(gridItemAccessibilityProperty->ActActionSelect());
    EXPECT_TRUE(gridItemAccessibilityProperty->ActActionClearSelection());

    /**
     * @tc.steps: step5. When girdItem is Selectable, call the callback function in gridItemAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    gridItemPattern->selectable_ = true;
    EXPECT_TRUE(gridItemAccessibilityProperty->ActActionSelect());
    EXPECT_TRUE(gridItemAccessibilityProperty->ActActionClearSelection());
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: Gird Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, PerformActionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gird and initialize related properties.
     */
    GridModelNG gridModelNG;
    gridModelNG.Create(nullptr, nullptr);

    /**
     * @tc.steps: step2. Get gird frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(gridPattern, nullptr);
    gridPattern->isConfigScrollable_ = false;
    gridPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get gird accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto gridAccessibilityProperty = frameNode->GetAccessibilityProperty<GridAccessibilityProperty>();
    ASSERT_NE(gridAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When gird is not Scrollable, call the callback function in gridAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(gridAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(gridAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When gird is Scrollable, call the callback function in gridAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    gridPattern->isConfigScrollable_ = true;
    EXPECT_TRUE(gridAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(gridAccessibilityProperty->ActActionScrollBackward());
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
        std::optional<float> horizontalOffset = 10.0f;
        std::optional<float> verticalOffset = 10.0f;
        return std::make_pair(horizontalOffset, verticalOffset);
    };
    gridModelNG.SetOnScrollBarUpdate(std::move(scrollFunc));
    CreateSingleGridItem(1, 1, 1, 2);
    CreateGridItem(2, -1, ITEM_HEIGHT);
    GetInstance();
    RunMeasureAndLayout();
    Dimension offset(1.0);
    auto fireOnScroll = eventHub_->FireOnScrollBarUpdate(1.0, offset);
    EXPECT_FLOAT_EQ(fireOnScroll.first.value(), 10.0f);
    EXPECT_FLOAT_EQ(fireOnScroll.second.value(), 10.0f);
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
    auto layoutWrapper = RunMeasureAndLayout();
    ASSERT_NE(layoutWrapper, nullptr);
    auto item = GetItemFrameNode(0);
    auto gridScrollLayoutAlgorithm = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(pattern_->gridLayoutInfo_, 2, 0);
    ASSERT_NE(gridScrollLayoutAlgorithm, nullptr);
    auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    gridScrollLayoutAlgorithm->AdjustRowColSpan(itemWrapper);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto layoutProperty = item->GetLayoutProperty<GridItemLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetRowStart(), -1);
    EXPECT_EQ(layoutProperty->GetRowEnd(), -1);
    EXPECT_EQ(layoutProperty->GetColumnStart(), -1);
    EXPECT_EQ(layoutProperty->GetColumnEnd(), -1);
}
} // namespace OHOS::Ace::NG
