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
#include "core/components_ng/pattern/grid/grid_layout_info.h"
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
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_with_options_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_ng/test/pattern/test_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t VIEWPORT_LINE_NUMBER = 4;
constexpr float ITEM_WIDTH = DEVICE_WIDTH / VIEWPORT_LINE_NUMBER;
constexpr float ITEM_HEIGHT = DEVICE_HEIGHT / VIEWPORT_LINE_NUMBER;
constexpr Dimension GRIDITEM_FOCUS_INTERVAL = 3.0_vp;
constexpr Dimension BORDER_RADIUS = 8.0_vp;
constexpr int32_t NULL_VALUE = -1;
constexpr float COL_GAP = 10.f;
constexpr float ROW_GAP = 5.f;
} // namespace

class GridTestNg : public testing::Test, public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void CreateGrid(const std::function<void(GridModelNG)>& callback = nullptr);
    void CreateGridNoProxy(const std::function<void(GridModelNG)>& callback = nullptr);
    static void CreateItem(int32_t count = 10, float width = NULL_VALUE, float height = NULL_VALUE,
        bool focusable = false, GridItemStyle gridItemStyle = GridItemStyle::NONE);
    static void CreateVerticalItem(
        int32_t count, bool focusable = false, GridItemStyle gridItemStyle = GridItemStyle::NONE);
    static void CreateHorizontalItem(
        int32_t count, bool focusable = false, GridItemStyle gridItemStyle = GridItemStyle::NONE);
    static void CreateBigItem(int32_t rowStart = NULL_VALUE, int32_t rowEnd = NULL_VALUE,
        int32_t colStart = NULL_VALUE, int32_t colEnd = NULL_VALUE, float width = NULL_VALUE,
        float height = NULL_VALUE);
    void UpdateLayoutWrapper(
        RefPtr<FrameNode>& frameNode, float width = DEVICE_WIDTH, float height = DEVICE_HEIGHT);
    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
    void MouseSelect(Offset start, Offset end);
    void MouseSelectRelease();
    int32_t CalculateGridColumnsOrRows(float contentWidth, float gridWidth, float gutter = 0.0f, float margin = 0.0f);
    AssertionResult IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t expectNextIndex);
    AssertionResult IsEqualCurrentOffset(float expectOffset);
    AssertionResult VerifyItemRect(
        int32_t viewItemNumber, int32_t lanes, float width, float height, int32_t startIndex, FlexDirection direction);
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
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
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
    auto gridItemTheme = AceType::MakeRefPtr<GridItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    EXPECT_CALL(*themeManager, GetTheme(GridItemTheme::TypeId())).WillRepeatedly(Return(gridItemTheme));
}

void GridTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

void GridTestNg::SetUp() {}

void GridTestNg::TearDown()
{
    if (frameNode_ && frameNode_->renderContext_) {
        // the destructor is not virtual, the MockRenderContext destructor will not be called
        frameNode_->renderContext_ = nullptr;
    }
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

void GridTestNg::CreateGrid(const std::function<void(GridModelNG)>& callback)
{
    GridModelNG gridModelNG;
    RefPtr<ScrollControllerBase> positionController = gridModelNG.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = gridModelNG.CreateScrollBarProxy();
    gridModelNG.Create(positionController, scrollBarProxy);
    if (callback) {
        callback(gridModelNG);
    }
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
}

void GridTestNg::CreateGridNoProxy(const std::function<void(GridModelNG)>& callback)
{
    GridModelNG gridModelNG;
    RefPtr<ScrollControllerBase> positionController = gridModelNG.CreatePositionController();
    gridModelNG.Create(positionController, nullptr);
    if (callback) {
        callback(gridModelNG);
    }
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
}

void GridTestNg::CreateItem(
    int32_t count, float width, float height, bool focusable, GridItemStyle gridItemStyle)
{
    for (int32_t i = 0; i < count; i++) {
        GridItemModelNG gridItemModel;
        gridItemModel.Create(gridItemStyle);
        if (width != NULL_VALUE) {
            SetWidth(Dimension(width));
        }
        if (height != NULL_VALUE) {
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

void GridTestNg::CreateVerticalItem(
    int32_t count, bool focusable, GridItemStyle gridItemStyle)
{
    CreateItem(count, NULL_VALUE, ITEM_HEIGHT, focusable, gridItemStyle);
}

void GridTestNg::CreateHorizontalItem(
    int32_t count, bool focusable, GridItemStyle gridItemStyle)
{
    CreateItem(count, ITEM_WIDTH, NULL_VALUE, focusable, gridItemStyle);
}

void GridTestNg::CreateBigItem(
    int32_t rowStart, int32_t rowEnd, int32_t colStart, int32_t colEnd, float width, float height)
{
        GridItemModelNG gridItemModel;
        gridItemModel.Create(GridItemStyle::NONE);
        if (rowStart != NULL_VALUE) {
            gridItemModel.SetRowStart(rowStart);
        }
        if (rowEnd != NULL_VALUE) {
            gridItemModel.SetRowEnd(rowEnd);
        }
        if (colStart != NULL_VALUE) {
            gridItemModel.SetColumnStart(colStart);
        }
        if (colEnd != NULL_VALUE) {
            gridItemModel.SetColumnEnd(colEnd);
        }
        if (width != NULL_VALUE) {
            SetWidth(Dimension(width));
        }
        if (height != NULL_VALUE) {
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
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
}

AssertionResult GridTestNg::IsEqualNextFocusNode(
    FocusStep step, int32_t currentIndex, int32_t expectNextIndex)
{
    RefPtr<FocusHub> currentFocusNode = GetChildFocusHub(frameNode_, currentIndex);
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
    if (expectNextIndex != NULL_INDEX && nextFocusNode == nullptr) {
        return AssertionFailure() << "Next FocusNode is null";
    }
    int32_t nextIndex = findFocusNodeIndex(nextFocusNode);
    return IsEqual(nextIndex, expectNextIndex);
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

AssertionResult GridTestNg::IsEqualCurrentOffset(float expectOffset)
{
    float currentOffset = pattern_->GetGridLayoutInfo().currentOffset_;
    return IsEqual(currentOffset, expectOffset);
}

AssertionResult GridTestNg::VerifyItemRect(
    int32_t viewItemNumber, int32_t lanes, float width, float height, int32_t startIndex, FlexDirection direction)
{
    if (lanes < 1) {
        return AssertionFailure() << "lanes < 1";
    }
    float unitX = width + COL_GAP;
    float unitY = height + ROW_GAP;
    float itemWidthTotal = lanes * unitX - COL_GAP;
    float itemHeightTotal = lanes * unitY - ROW_GAP;
    for (int32_t index = 0; index < viewItemNumber; index++) {
        float offsetX;
        float offsetY;
        switch (direction) {
            case FlexDirection::ROW:
                offsetX = index % lanes * unitX;
                offsetY = floor(index / lanes) * unitY;
                break;
            case FlexDirection::ROW_REVERSE:
                offsetX = itemWidthTotal - (index % lanes + 1) * unitX + COL_GAP;
                offsetY = floor(index / lanes) * unitY;
                break;
            case FlexDirection::COLUMN:
                offsetX = floor(index / lanes) * unitX;
                offsetY = index % lanes * unitY;
                break;
            case FlexDirection::COLUMN_REVERSE:
                offsetX = floor(index / lanes) * unitX;
                offsetY = itemHeightTotal - (index % lanes + 1) * unitY + ROW_GAP;
                break;
            default:
                break;
        }
        int32_t itemIndex = index + startIndex;
        RectF rect = GetChildRect(frameNode_, itemIndex);
        RectF expectRect = RectF(offsetX, offsetY, width, height);
        if (rect != expectRect) {
            return AssertionFailure() << "At Item Index: " << itemIndex << " rect: " << rect.ToString() <<
                " != " << "expectRect: " << expectRect.ToString();
        }
        if (!GetChildFrameNode(frameNode_, itemIndex)->IsActive()) {
            return AssertionFailure() << "At Item Index: " << itemIndex << " IsActive() is false";
        }
    }
    return AssertionSuccess();
}

/**
 * @tc.name: Property001
 * @tc.desc: Test Grid properties
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Property001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr");
        gridModelNG.SetColumnsGap(Dimension(COL_GAP));
        gridModelNG.SetRowsGap(Dimension(ROW_GAP));
        gridModelNG.SetCachedCount(2);
        gridModelNG.SetEditable(true);
        gridModelNG.SetLayoutDirection(FlexDirection::ROW);
        gridModelNG.SetMaxCount(5);
        gridModelNG.SetMinCount(2);
        gridModelNG.SetCellLength(100);
        gridModelNG.SetEdgeEffect(EdgeEffect::SPRING);
        gridModelNG.SetScrollEnabled(false);
        CreateVerticalItem(10);
    });

    /**
     * @tc.steps: step1. Test ToJsonValue
     */
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("columnsTemplate"), "1fr 1fr");
    EXPECT_EQ(json->GetString("rowsTemplate"), "1fr 1fr 1fr");
    EXPECT_EQ(Dimension::FromString(json->GetString("columnsGap")), Dimension(COL_GAP));
    EXPECT_EQ(Dimension::FromString(json->GetString("rowsGap")), Dimension(ROW_GAP));
    EXPECT_EQ(json->GetInt("cachedCount"), 2);
    EXPECT_EQ(json->GetString("editMode"), "true");
    EXPECT_EQ(json->GetString("layoutDirection"), "GridDirection.Row");
    EXPECT_EQ(json->GetInt("maxCount"), 5);
    EXPECT_EQ(json->GetInt("minCount"), 2);
    EXPECT_EQ(json->GetInt("cellLength"), 100);
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect.Spring");
    EXPECT_FALSE(json->GetBool("enableScrollInteraction"));

    /**
     * @tc.steps: step2. Test ToJsonValue, change some property
     */
    layoutProperty_->UpdateGridDirection(FlexDirection::ROW_REVERSE);
    layoutProperty_->UpdateEdgeEffect(EdgeEffect::FADE);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("layoutDirection"), "GridDirection.RowReverse");
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect.Fade");

    /**
     * @tc.steps: step3. Test ToJsonValue, change some property
     */
    layoutProperty_->UpdateGridDirection(FlexDirection::COLUMN);
    layoutProperty_->UpdateEdgeEffect(EdgeEffect::NONE);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("layoutDirection"), "GridDirection.Column");
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect.None");

    /**
     * @tc.steps: step4. Test ToJsonValue, change some property
     */
    layoutProperty_->UpdateGridDirection(FlexDirection::COLUMN_REVERSE);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("layoutDirection"), "GridDirection.ColumnReverse");
}

/**
 * @tc.name: Property002
 * @tc.desc: Test Negative Gap
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Property002, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsGap(Dimension(-5));
        gridModelNG.SetColumnsGap(Dimension(-10));
        CreateVerticalItem(10);
    });

    /**
     * @tc.steps: step1. Verify GapValue
     * @tc.expected: Gap not be set
     */
    EXPECT_EQ(layoutProperty_->GetRowsGap(), std::nullopt);
    EXPECT_EQ(layoutProperty_->GetColumnsGap(), std::nullopt);
}

/**
 * @tc.name: Property003
 * @tc.desc: Test all the properties of GridItem.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Property003, TestSize.Level1)
{
    GridItemModelNG gridItemModelNG;
    gridItemModelNG.Create(GridItemStyle::NONE);
    gridItemModelNG.SetRowStart(1);
    gridItemModelNG.SetRowEnd(2);
    gridItemModelNG.SetColumnStart(1);
    gridItemModelNG.SetColumnEnd(2);
    gridItemModelNG.SetForceRebuild(true);
    gridItemModelNG.SetSelectable(false);
    gridItemModelNG.SetOnSelect([](bool) {});

    /**
     * @tc.steps: step1. Get frameNode and properties.
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
    EXPECT_EQ(layoutProperty->GetMainEnd(Axis::VERTICAL), 2);
    EXPECT_EQ(layoutProperty->GetMainEnd(Axis::HORIZONTAL), 2);
    EXPECT_EQ(layoutProperty->GetCrossEnd(Axis::VERTICAL), 2);
    EXPECT_EQ(layoutProperty->GetCrossEnd(Axis::HORIZONTAL), 2);
    auto pattern = frameNode->GetPattern<GridItemPattern>();
    EXPECT_TRUE(pattern->forceRebuild_);
    auto eventHub = frameNode->GetEventHub<GridItemEventHub>();
    ASSERT_NE(eventHub->onSelect_, nullptr);

    /**
     * @tc.steps: step2. Test ToJsonValue
     */
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(json->GetString("rowStart"), "1");
    EXPECT_EQ(json->GetString("rowEnd"), "2");
    EXPECT_EQ(json->GetString("columnStart"), "1");
    EXPECT_EQ(json->GetString("columnEnd"), "2");
}

/**
 * @tc.name: AttrColumnsTemplate001
 * @tc.desc: Test property about columnsTemplate and Gap,
 * test normal condition that template is "1fr 1fr 1fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrColumnsTemplate001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetColumnsGap(Dimension(COL_GAP));
        gridModelNG.SetRowsGap(Dimension(ROW_GAP));
        CreateVerticalItem(20);
    });

    /**
     * @tc.steps: step1. While only set ColumnsTemplate
     * @tc.expected: The axis is VERTICAL
     */
    EXPECT_EQ(pattern_->GetAxis(), Axis::VERTICAL);

    /**
     * @tc.steps: step2. Verify all of gridItems rect
     */
    float averageWidth = (DEVICE_WIDTH + COL_GAP) / 4 - COL_GAP;
    EXPECT_TRUE(VerifyItemRect(12, 4, averageWidth, ITEM_HEIGHT, 0, FlexDirection::ROW));

    /**
     * @tc.steps: step3. Scroll and Verify
     */
    UpdateCurrentOffset(-(ITEM_HEIGHT + ROW_GAP));
    EXPECT_TRUE(VerifyItemRect(12, 4, averageWidth, ITEM_HEIGHT, 4, FlexDirection::ROW));
}

/**
 * @tc.name: AttrColumnsTemplate002
 * @tc.desc: Test property about columnsTemplate,
 * test condition that template is "1fr 2fr 3fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrColumnsTemplate002, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 2fr 3fr 1fr");
        CreateVerticalItem(10);
    });

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     */
    float averageWidth = DEVICE_WIDTH / 7;
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1),
        RectF(averageWidth, 0.f, averageWidth * 2, ITEM_HEIGHT)));

    /**
     * @tc.steps: step2. Verify index 6 gridItem rect
     */
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 6),
        RectF(averageWidth * 3, ITEM_HEIGHT, averageWidth * 3, ITEM_HEIGHT)));
}

/**
 * @tc.name: AttrColumnsTemplate003
 * @tc.desc: Test property about columnsTemplate,
 * test condition that template is "1fr 0fr 0fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrColumnsTemplate003, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 0fr 0fr 1fr");
        CreateVerticalItem(10);
    });

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     * @tc.expected: The item width is zero
     */
    float averageWidth = DEVICE_WIDTH / 2;
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1),
        RectF(averageWidth, 0.f, 0.f, ITEM_HEIGHT)));
}

/**
 * @tc.name: AttrColumnsTemplate004
 * @tc.desc: Test property about columnsTemplate and Gap,
 * test normal condition that template is "repeat(auto-fit, 90px)"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrColumnsTemplate004, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("repeat(auto-fit, 90px)");
        gridModelNG.SetColumnsGap(Dimension(COL_GAP));
        gridModelNG.SetRowsGap(Dimension(ROW_GAP));
        CreateVerticalItem(20);
    });

    /**
     * @tc.steps: step1. While only set ColumnsTemplate
     * @tc.expected: The axis is VERTICAL
     */
    EXPECT_EQ(pattern_->GetAxis(), Axis::VERTICAL);

    /**
     * @tc.steps: step2. Verify all of gridItems rect
     */
    float gridWidth = 90.0f;
    int32_t lanes = CalculateGridColumnsOrRows(DEVICE_WIDTH, gridWidth, COL_GAP);
    float averageWidth = (DEVICE_WIDTH + COL_GAP) / 4 - COL_GAP;
    EXPECT_TRUE(VerifyItemRect(12, lanes, averageWidth, ITEM_HEIGHT, 0, FlexDirection::ROW));

    /**
     * @tc.steps: step3. Scroll and Verify
     */
    UpdateCurrentOffset(-(ITEM_HEIGHT + ROW_GAP));
    EXPECT_TRUE(VerifyItemRect(12, lanes, averageWidth, ITEM_HEIGHT, 4, FlexDirection::ROW));
}

/**
 * @tc.name: AttrRowsTemplate001
 * @tc.desc: Test property about rowsTemplate and Gap,
 * test normal condition that template is "1fr 1fr 1fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrRowsTemplate001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetColumnsGap(Dimension(COL_GAP));
        gridModelNG.SetRowsGap(Dimension(ROW_GAP));
        CreateHorizontalItem(20);
    });

    /**
     * @tc.steps: step1. While only set rowsTemplate
     * @tc.expected: The axis is HORIZONTAL
     */
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);

    /**
     * @tc.steps: step2. Verify all of gridItems rect
     */
    float averageHeight = (DEVICE_HEIGHT + ROW_GAP) / 4 - ROW_GAP;
    EXPECT_TRUE(VerifyItemRect(12, 4, ITEM_WIDTH, averageHeight, 0, FlexDirection::COLUMN));

    /**
     * @tc.steps: step3. Scroll and Verify
     */
    UpdateCurrentOffset(-(ITEM_WIDTH + COL_GAP));
    EXPECT_TRUE(VerifyItemRect(12, 4, ITEM_WIDTH, averageHeight, 4, FlexDirection::COLUMN));
}

/**
 * @tc.name: AttrRowsTemplate002
 * @tc.desc: Test property about rowsTemplate,
 * test condition that template is "1fr 2fr 3fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrRowsTemplate002, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 2fr 3fr 1fr");
        CreateHorizontalItem(10);
    });

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     */
    float averageHeight = DEVICE_HEIGHT / 7;
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1),
        RectF(0.f, averageHeight, ITEM_WIDTH, averageHeight * 2)));

    /**
     * @tc.steps: step2. Verify index 6 gridItem rect
     */
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 6),
        RectF(ITEM_WIDTH, averageHeight * 3, ITEM_WIDTH, averageHeight * 3)));
}

/**
 * @tc.name: AttrRowsTemplate003
 * @tc.desc: Test property about rowsTemplate,
 * test condition that template is "1fr 0fr 0fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrRowsTemplate003, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 0fr 0fr 1fr");
        CreateHorizontalItem(10);
    });

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     * @tc.expected: The item height is zero
     */
    float averageHeight = DEVICE_HEIGHT / 2;
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1),
        RectF(0.f, averageHeight, ITEM_WIDTH, 0.f)));
}

/**
 * @tc.name: AttrRowsTemplate004
 * @tc.desc: Test property about rowsTemplate and Gap,
 * test normal condition that template is "repeat(auto-fit, 90px)"
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrRowsTemplate004, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("repeat(auto-fit, 90px)");
        gridModelNG.SetColumnsGap(Dimension(COL_GAP));
        gridModelNG.SetRowsGap(Dimension(ROW_GAP));
        CreateHorizontalItem(24);
    });

    /**
     * @tc.steps: step1. While only set rowsTemplate
     * @tc.expected: The axis is HORIZONTAL
     */
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);

    /**
     * @tc.steps: step2. Verify all of gridItems rect
     * @tc.expected: The rect is equal to expectRect
     */
    float gridHeight = 90.0f;
    int32_t lanes = CalculateGridColumnsOrRows(DEVICE_HEIGHT, gridHeight, ROW_GAP);
    float averageHeight = (DEVICE_HEIGHT + ROW_GAP) / lanes - ROW_GAP;
    EXPECT_TRUE(VerifyItemRect(15, lanes, ITEM_WIDTH, averageHeight, 0, FlexDirection::COLUMN));
}

/**
 * @tc.name: AttrColumnsRows001
 * @tc.desc: Test property about columns/rows Template,
 * test condition that template is empty: ""
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrColumnsRows001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("");
        gridModelNG.SetColumnsTemplate("");
        CreateVerticalItem(10);
    });

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
    // not set gridItem width/height, gridItem will fill the mesh size by default
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetColumnsGap(Dimension(COL_GAP));
        gridModelNG.SetRowsGap(Dimension(ROW_GAP));
        CreateItem(20);
    });

    /**
     * @tc.steps: step1. Set both columns/rows Template
     * @tc.expected: The gridItem width/height will slef-adaption
     */
    int32_t lanes = 4;
    float averageWidth = (DEVICE_WIDTH + COL_GAP) / lanes - COL_GAP;
    float averageHeight = (DEVICE_HEIGHT + ROW_GAP) / lanes - ROW_GAP;
    EXPECT_TRUE(VerifyItemRect(12, lanes, averageWidth, averageHeight, 0, FlexDirection::ROW));

    /**
     * @tc.steps: step2. Scroll and Verify
     * @tc.expected: Can not scroll
     */
    UpdateCurrentOffset(-(ITEM_HEIGHT + ROW_GAP));
    EXPECT_TRUE(VerifyItemRect(12, lanes, averageWidth, averageHeight, 0, FlexDirection::ROW));
}

/**
 * @tc.name: AttrLayoutDirection001
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::ROW
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrLayoutDirection001, TestSize.Level1)
{
    float itemWidth = 100.f;
    CreateGrid([itemWidth](GridModelNG gridModelNG) {
        gridModelNG.SetLayoutDirection(FlexDirection::ROW);
        gridModelNG.SetCellLength(ITEM_HEIGHT);
        gridModelNG.SetMinCount(2);
        gridModelNG.SetMaxCount(4);
        gridModelNG.SetColumnsGap(Dimension(COL_GAP));
        gridModelNG.SetRowsGap(Dimension(ROW_GAP));
        CreateItem(20, itemWidth, ITEM_HEIGHT);
    });

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    EXPECT_TRUE(VerifyItemRect(8, 4, itemWidth, ITEM_HEIGHT, 0, FlexDirection::ROW));

    /**
     * @tc.steps: step2. Scroll and Verify
     * @tc.expected: Can not scroll
     */
    UpdateCurrentOffset(-(ITEM_HEIGHT + ROW_GAP));
    EXPECT_TRUE(VerifyItemRect(8, 4, itemWidth, ITEM_HEIGHT, 0, FlexDirection::ROW));
}

/**
 * @tc.name: AttrLayoutDirection002
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::ROW_REVERSE
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrLayoutDirection002, TestSize.Level1)
{
    float itemWidth = 100.f;
    CreateGrid([itemWidth](GridModelNG gridModelNG) {
        gridModelNG.SetLayoutDirection(FlexDirection::ROW_REVERSE);
        gridModelNG.SetCellLength(ITEM_HEIGHT);
        gridModelNG.SetMinCount(2);
        gridModelNG.SetMaxCount(4);
        gridModelNG.SetColumnsGap(Dimension(COL_GAP));
        gridModelNG.SetRowsGap(Dimension(ROW_GAP));
        CreateItem(20, itemWidth, ITEM_HEIGHT);
    });

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    EXPECT_TRUE(VerifyItemRect(8, 4, itemWidth, ITEM_HEIGHT, 0, FlexDirection::ROW_REVERSE));

    /**
     * @tc.steps: step3. Scroll and Verify
     * @tc.expected: Can not scroll
     */
    UpdateCurrentOffset(-(ITEM_HEIGHT + ROW_GAP));
    EXPECT_TRUE(VerifyItemRect(8, 4, itemWidth, ITEM_HEIGHT, 0, FlexDirection::ROW_REVERSE));
}

/**
 * @tc.name: AttrLayoutDirection003
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::COLUMN
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrLayoutDirection003, TestSize.Level1)
{
    float itemHeight = 100.f;
    CreateGrid([itemHeight](GridModelNG gridModelNG) {
        gridModelNG.SetLayoutDirection(FlexDirection::COLUMN);
        gridModelNG.SetCellLength(ITEM_WIDTH);
        gridModelNG.SetMinCount(2);
        gridModelNG.SetMaxCount(4);
        gridModelNG.SetColumnsGap(Dimension(COL_GAP));
        gridModelNG.SetRowsGap(Dimension(ROW_GAP));
        CreateItem(20, ITEM_WIDTH, itemHeight);
    });

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    EXPECT_TRUE(VerifyItemRect(8, 4, ITEM_WIDTH, itemHeight, 0, FlexDirection::COLUMN));

    /**
     * @tc.steps: step3. Scroll and Verify
     * @tc.expected: Can not scroll
     */
    UpdateCurrentOffset(-(ITEM_WIDTH + COL_GAP));
    EXPECT_TRUE(VerifyItemRect(8, 4, ITEM_WIDTH, itemHeight, 0, FlexDirection::COLUMN));
}

/**
 * @tc.name: AttrLayoutDirection004
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::COLUMN_REVERSE
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrLayoutDirection004, TestSize.Level1)
{
    float itemHeight = 100.f;
    CreateGrid([itemHeight](GridModelNG gridModelNG) {
        gridModelNG.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
        gridModelNG.SetCellLength(ITEM_WIDTH);
        gridModelNG.SetMinCount(2);
        gridModelNG.SetMaxCount(4);
        gridModelNG.SetColumnsGap(Dimension(COL_GAP));
        gridModelNG.SetRowsGap(Dimension(ROW_GAP));
        CreateItem(20, ITEM_WIDTH, itemHeight);
    });

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    EXPECT_TRUE(VerifyItemRect(8, 4, ITEM_WIDTH, itemHeight, 0, FlexDirection::COLUMN_REVERSE));

    /**
     * @tc.steps: step3. Scroll and Verify
     * @tc.expected: Can not scroll
     */
    UpdateCurrentOffset(-(ITEM_WIDTH + COL_GAP));
    EXPECT_TRUE(VerifyItemRect(8, 4, ITEM_WIDTH, itemHeight, 0, FlexDirection::COLUMN_REVERSE));
}

/**
 * @tc.name: AttrGridItem001
 * @tc.desc: Test property rowStart/rowEnd/colStart/colEnd with colTemplate/rowTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrGridItem001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        // not set width/height
        CreateBigItem(1, 2, 1, 2);
        CreateBigItem(NULL_VALUE, NULL_VALUE, 1, 3);
        CreateBigItem(1, 3, NULL_VALUE, NULL_VALUE);
        CreateItem(7);
    });

    float averageWidth = DEVICE_WIDTH / 4;
    float averageHeight = DEVICE_HEIGHT / 4;
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 0),
        RectF(averageWidth, averageHeight, averageWidth * 2, averageHeight * 2)));

    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1),
        RectF(0.f, 0.f, averageWidth * 3, averageHeight)));

    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 2),
        RectF(averageWidth * 3, 0.f, averageWidth, averageHeight * 3)));
}

/**
 * @tc.name: AttrGridItem002
 * @tc.desc: Test property rowStart/rowEnd with rowTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrGridItem002, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        // need set width
        CreateBigItem(1, 2, NULL_VALUE, NULL_VALUE, ITEM_WIDTH, NULL_VALUE);
        CreateBigItem(0, 2, NULL_VALUE, NULL_VALUE, ITEM_WIDTH, NULL_VALUE);
        CreateBigItem(2, 3, NULL_VALUE, NULL_VALUE, ITEM_WIDTH, NULL_VALUE);
        CreateHorizontalItem(7);
    });

    float averageHeight = DEVICE_HEIGHT / 4;
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 0),
        RectF(0.f, averageHeight, ITEM_WIDTH, averageHeight * 2)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1),
        RectF(ITEM_WIDTH, 0.f, ITEM_WIDTH, averageHeight * 3)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 2),
        RectF(ITEM_WIDTH * 2, averageHeight * 2, ITEM_WIDTH, averageHeight * 2)));

    UpdateCurrentOffset(-ITEM_WIDTH);
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1),
        RectF(0.f, 0.f, ITEM_WIDTH, averageHeight * 3)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 2),
        RectF(ITEM_WIDTH, averageHeight * 2, ITEM_WIDTH, averageHeight * 2)));
}

/**
 * @tc.name: AttrGridItem003
 * @tc.desc: Test property colStart/colEnd with colTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrGridItem003, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        // need set height
        CreateBigItem(NULL_VALUE, NULL_VALUE, 2, 3, NULL_VALUE, ITEM_HEIGHT);
        CreateBigItem(NULL_VALUE, NULL_VALUE, 0, 2, NULL_VALUE, ITEM_HEIGHT);
        CreateBigItem(NULL_VALUE, NULL_VALUE, 2, 1, NULL_VALUE, ITEM_HEIGHT);
        CreateVerticalItem(7);
    });

    float averageWidth = DEVICE_WIDTH / 4;
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 0),
        RectF(averageWidth * 2, 0.f, averageWidth * 2, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1),
        RectF(0.f, ITEM_HEIGHT, averageWidth * 3, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 2),
        RectF(averageWidth * 2, ITEM_HEIGHT * 2, averageWidth, ITEM_HEIGHT)));

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1),
        RectF(0.f, 0.f, averageWidth * 3, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 2),
        RectF(averageWidth * 2, ITEM_HEIGHT, averageWidth, ITEM_HEIGHT)));
}

/**
 * @tc.name: AttrEnableScrollInteraction001
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, AttrEnableScrollInteraction001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetScrollEnabled(true);
        CreateVerticalItem(10);
    });
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), true);

    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetScrollEnabled(false);
        CreateVerticalItem(10);
    });
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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
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
    EXPECT_TRUE(IsEqualCurrentOffset(-DEVICE_HEIGHT));

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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetMultiSelectable(true);
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });

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

    UpdateCurrentOffset(DEVICE_HEIGHT);
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
    CreateGrid([](GridModelNG gridModelNG) {
        CreateVerticalItem(10);
    });
    pattern_->AnimateTo(100.f, 200.f, Curves::LINEAR, false);
    ASSERT_EQ(pattern_->animator_, nullptr);

    /**
     * @tc.steps: step2. isConfigScrollable_
     */
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
    EXPECT_TRUE(pattern_->OnScrollPosition(ITEM_HEIGHT, SCROLL_FROM_UPDATE));
    EXPECT_TRUE(pattern_->OnScrollPosition(ITEM_HEIGHT, SCROLL_FROM_UPDATE));
    EXPECT_TRUE(pattern_->OnScrollPosition(ITEM_HEIGHT, SCROLL_FROM_START));
    pattern_->OnScrollEnd();
    auto coordinationEvent = AceType::MakeRefPtr<ScrollableCoordinationEvent>();
    auto event1 = [](double) { return true; };
    auto event2 = [](bool) {};
    auto event3 = [](double) {};
    coordinationEvent->SetOnScrollEvent(event1);
    coordinationEvent->SetOnScrollStartEvent(event2);
    coordinationEvent->SetOnScrollEndEvent(event3);
    EXPECT_TRUE(pattern_->OnScrollPosition(ITEM_HEIGHT, SCROLL_FROM_UPDATE));
    EXPECT_TRUE(pattern_->OnScrollPosition(ITEM_HEIGHT, SCROLL_FROM_UPDATE));
    EXPECT_TRUE(pattern_->OnScrollPosition(ITEM_HEIGHT, SCROLL_FROM_START));
    pattern_->OnScrollEnd();
    EXPECT_TRUE(pattern_->OnScrollPosition(ITEM_HEIGHT, SCROLL_FROM_UPDATE));
    pattern_->OnScrollEnd();

    /**
     * @tc.steps: step2. Test OnScrollCallback.
     */
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
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
    CreateGrid([event](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(event);
        CreateVerticalItem(10);
    });

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
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);

    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_EQ(offsetY.ConvertToPx(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);

    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_EQ(offsetY.ConvertToPx(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);

    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_EQ(offsetY.ConvertToPx(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);

    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_EQ(offsetY.ConvertToPx(), -ITEM_HEIGHT);
    EXPECT_EQ(scrollState, ScrollState::IDLE);

    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    pattern_->SetScrollAbort(true);
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_NONE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
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
    CreateGrid([event](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetOnScrollIndex(event);
        CreateVerticalItem(12);
    });

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 9);

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(endIndex, 11);
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
    CreateGrid([event](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetOnReachStart(event);
        CreateVerticalItem(12);
    });
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_AXIS);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_JUMP);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_JUMP);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_BAR);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_FALSE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);
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
    CreateGrid([event](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetOnReachEnd(event);
        CreateVerticalItem(10);
    });

    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT * 3);
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_AXIS);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_JUMP);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_JUMP);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_BAR);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_NONE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
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
    CreateGrid([scrollStart, scrollStop](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetOnScrollStart(scrollStart);
        gridModelNG.SetOnScrollStop(scrollStop);
        CreateVerticalItem(10);
    });

    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(isScrollStartCalled);

    pattern_->SetScrollAbort(true);
    pattern_->OnScrollEndCallback();
    EXPECT_FALSE(isScrollStopCalled);
    pattern_->SetScrollAbort(false);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isScrollStopCalled);
}

/**
 * @tc.name: Event006
 * @tc.desc: Test other condition
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Event006, TestSize.Level1)
{
    auto event = [](Dimension, ScrollState) {
        ScrollFrameResult result;
        return result;
    };
    CreateGrid([event](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetOnScrollFrameBegin(event);
        CreateVerticalItem(10);
    });

    auto scrollableEvent = pattern_->GetScrollableEvent();
    ASSERT_NE(scrollableEvent, nullptr);
    EXPECT_NE(scrollableEvent->GetScrollable()->callback_, nullptr);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
}

/**
 * @tc.name: VerticalGridWithoutScrollBar001
 * @tc.desc: Test Grid(Axis::VERTICAL) Scroll Without Scroll Bar Without Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, VerticalGridWithoutScrollBarWithoutAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGridNoProxy([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd, this](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        CreateVerticalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's center position without animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: Only onScroll call back function should be triggered
     */
    pattern_->ScrollTo(ITEM_HEIGHT * 1);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_FALSE(isOnScrollStartCallBack);
    EXPECT_FALSE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack);
    EXPECT_FALSE(isOnReachEndCallBack);
}

/**
 * @tc.name: VerticalGridWithoutScrollBar002
 * @tc.desc: Test Grid(Axis::VERTICAL) Scroll Without Scroll Bar Without Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, VerticalGridWithoutScrollBarWithoutAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGridNoProxy([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd, this](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        CreateVerticalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's end position without animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: Only onScroll and onReachEnd should be triggered
     */
    pattern_->ScrollTo(ITEM_HEIGHT * 9);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_FALSE(isOnScrollStartCallBack);
    EXPECT_FALSE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack);
    EXPECT_TRUE(isOnReachEndCallBack);
}

/**
 * @tc.name: VerticalGridWithoutScrollBarWithAnimation001
 * @tc.desc: Test Grid(Axis::VERTICAL) Scroll Without Scroll Bar With Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, VerticalGridWithoutScrollBarWithAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset; scrollState = state; isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGridNoProxy([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        gridModelNG.SetSupportAnimation(true);
        CreateVerticalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;
    /**
     * @tc.steps: step2. Scroll to grid's center with animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: OnScroll OnScrollStart and onScrollStop call back functions should be triggered
     */
    pattern_->AnimateTo(-5*ITEM_HEIGHT, 1.f, Curves::LINEAR, false);
    pattern_->animator_->Stop(); pattern_->SetScrollAbort(false); pattern_->OnScrollEndCallback();
    pattern_->UpdateCurrentOffset(-5*ITEM_HEIGHT, SCROLL_FROM_ANIMATION);

    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack); EXPECT_TRUE(isOnScrollStartCallBack); EXPECT_TRUE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack); EXPECT_FALSE(isOnReachEndCallBack);
}

/**
 * @tc.name: VerticalGridWithoutScrollBarWithAnimation002
 * @tc.desc: Test Grid(Axis::VERTICAL) Scroll Without Scroll Bar With Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, VerticalGridWithoutScrollBarWithAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset; scrollState = state; isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGridNoProxy([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        gridModelNG.SetSupportAnimation(true);
        CreateVerticalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's end without animation, and check the
     *                   five kinds of call back functions is triggered or not.
     * @tc.expected:All call back functions except onReachStart should be triggered
     */
    pattern_->AnimateTo(-20*ITEM_HEIGHT, 1.f, Curves::LINEAR, false);
    pattern_->animator_->Stop();
    pattern_->SetScrollAbort(false);
    pattern_->OnScrollEndCallback();
    pattern_->UpdateCurrentOffset(-20*ITEM_HEIGHT, SCROLL_FROM_ANIMATION);

    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 20);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack); EXPECT_TRUE(isOnScrollStartCallBack); EXPECT_TRUE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack); EXPECT_TRUE(isOnReachEndCallBack);
}

/**
 * @tc.name: HorizontalGridWithoutScrollBarWithoutAnimation001
 * @tc.desc: Test Grid(Axis::HORIZONTAL) Scroll Without Scroll Bar Without Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, HorizontalGridWithoutScrollBarWithoutAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGridNoProxy([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        CreateHorizontalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's center position without animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: Only onScroll call back function should be triggered
     */
    pattern_->ScrollTo(ITEM_WIDTH * 1);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_FALSE(isOnScrollStartCallBack);
    EXPECT_FALSE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack);
    EXPECT_FALSE(isOnReachEndCallBack);
}

/**
 * @tc.name: HorizontalGridWithoutScrollBarWithoutAnimation002
 * @tc.desc: Test Grid(Axis::HORIZONTAL) Scroll Without Scroll Bar Without Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, HorizontalGridWithoutScrollBarWithoutAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGridNoProxy([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        CreateHorizontalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

   /**
     * @tc.steps: step2. Scroll to grid's end position without animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: Only onScroll and onReachEnd should be triggered
     */
    pattern_->ScrollTo(ITEM_WIDTH * 10);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_FALSE(isOnScrollStartCallBack);
    EXPECT_FALSE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack);
    EXPECT_TRUE(isOnReachEndCallBack);
}

/**
 * @tc.name: HorizontalGridWithoutScrollBarWithAnimation001
 * @tc.desc: Test Grid(Axis::HORIZONTAL) Scroll Without Scroll Bar With Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, HorizontalGridWithoutScrollBarWithAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;
    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset; scrollState = state; isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGridNoProxy([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        gridModelNG.SetSupportAnimation(true);
        CreateHorizontalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's center with animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: OnScroll OnScrollStart and onScrollStop call back functions should be triggered
     */
    pattern_->AnimateTo(-5*ITEM_WIDTH, 1.f, Curves::LINEAR, false);
    pattern_->animator_->Stop();
    pattern_->SetScrollAbort(false);
    pattern_->OnScrollEndCallback();
    pattern_->UpdateCurrentOffset(-5*ITEM_WIDTH, SCROLL_FROM_ANIMATION);

    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack); EXPECT_TRUE(isOnScrollStartCallBack); EXPECT_TRUE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack); EXPECT_FALSE(isOnReachEndCallBack);
}

/**
 * @tc.name: HorizontalGridWithoutScrollBarWithAnimation002
 * @tc.desc: Test Grid(Axis::HORIZONTAL) Scroll Without Scroll Bar With Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, HorizontalGridWithoutScrollBarWithAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;
    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset; scrollState = state; isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGridNoProxy([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        gridModelNG.SetSupportAnimation(true);
        CreateHorizontalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's end without animation, and check the
     *                   five kinds of call back functions is triggered or not.
     * @tc.expected:All call back functions except onReachStart should be triggered
     */
    pattern_->AnimateTo(-10*ITEM_WIDTH, 1.f, Curves::LINEAR, false);
    pattern_->animator_->Stop();
    pattern_->SetScrollAbort(false);
    pattern_->OnScrollEndCallback();
    pattern_->UpdateCurrentOffset(-10*ITEM_WIDTH, SCROLL_FROM_ANIMATION);

    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack); EXPECT_TRUE(isOnScrollStartCallBack); EXPECT_TRUE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack); EXPECT_TRUE(isOnReachEndCallBack);
}

/**
 * @tc.name: VerticalGridWithScrollBarWithoutAnimation001
 * @tc.desc: Test Grid(Axis::VERTICAL) Scroll With Scroll Bar Without Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, VerticalGridWithScrollBarWithoutAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGrid([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd, this](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        CreateVerticalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's center position without animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: Only onScroll call back function should be triggered
     */
    auto controller = pattern_->positionController_;
    controller->JumpTo(5, false, ScrollAlign::CENTER, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_FALSE(isOnScrollStartCallBack);
    EXPECT_FALSE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack);
    EXPECT_FALSE(isOnReachEndCallBack);
}

/**
 * @tc.name: VerticalGridWithScrollBarWithoutAnimation002
 * @tc.desc: Test Grid(Axis::VERTICAL) Scroll With Scroll Bar Without Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, VerticalGridWithScrollBarWithoutAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset; scrollState = state; isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGrid([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd, this](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        CreateVerticalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's end position without animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: Only onScroll and onReachEnd should be triggered
     */
    auto controller = pattern_->positionController_;
    controller->JumpTo(19, false, ScrollAlign::END, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack); EXPECT_FALSE(isOnScrollStartCallBack); EXPECT_FALSE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack); EXPECT_TRUE(isOnReachEndCallBack);
}

/**
 * @tc.name: VerticalGridWithScrollBarWithAnimation001
 * @tc.desc: Test Grid(Axis::VERTICAL) Scroll With Scroll Bar With Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, VerticalGridWithScrollBarWithAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset; scrollState = state; isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGrid([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        gridModelNG.SetSupportAnimation(true);
        CreateVerticalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's center with animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: OnScroll OnScrollStart and onScrollStop call back functions should be triggered
     */
    auto controller = pattern_->positionController_;
    controller->AnimateTo(Dimension(-5*ITEM_HEIGHT, DimensionUnit::PX), 1.f, Curves::LINEAR, false);
    pattern_->animator_->Stop();
    pattern_->SetScrollAbort(false);
    pattern_->OnScrollEndCallback();
    pattern_->UpdateCurrentOffset(-5*ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);

    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack); EXPECT_TRUE(isOnScrollStartCallBack); EXPECT_TRUE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack); EXPECT_FALSE(isOnReachEndCallBack);
}


/**
 * @tc.name: VerticalGridWithScrollBarWithAnimation002
 * @tc.desc: Test Grid(Axis::VERTICAL) Scroll With Scroll Bar With Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, VerticalGridWithScrollBarWithAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset; scrollState = state; isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGrid([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        gridModelNG.SetSupportAnimation(true);
        CreateVerticalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's end without animation, and check the
     *                   five kinds of call back functions is triggered or not.
     * @tc.expected:All call back functions except onReachStart should be triggered
     */
    auto controller = pattern_->positionController_;
    controller->AnimateTo(Dimension(-10*ITEM_HEIGHT, DimensionUnit::PX), 1.f, Curves::LINEAR, false);
    pattern_->animator_->Stop();
    pattern_->SetScrollAbort(false);
    pattern_->OnScrollEndCallback();
    pattern_->UpdateCurrentOffset(-10*ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);

    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack); EXPECT_TRUE(isOnScrollStartCallBack); EXPECT_TRUE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack); EXPECT_TRUE(isOnReachEndCallBack);
}

/**
 * @tc.name: HorizontalGridWithScrollBarWithoutAnimation001
 * @tc.desc: Test Grid(Axis::HORIZONTAL) Scroll With Scroll Bar Without Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, HorizontalGridWithScrollBarWithoutAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset; scrollState = state; isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGrid([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        CreateHorizontalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's center position without animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: Only onScroll call back function should be triggered
     */
    auto controller = pattern_->positionController_;
    controller->JumpTo(5, false, ScrollAlign::CENTER, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_FALSE(isOnScrollStartCallBack);
    EXPECT_FALSE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack);
    EXPECT_FALSE(isOnReachEndCallBack);
}

/**
 * @tc.name: HorizontalGridWithScrollBarWithoutAnimation002
 * @tc.desc: Test Grid(Axis::HORIZONTAL) Scroll With Scroll Bar Without Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, HorizontalGridWithScrollBarWithoutAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGrid([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        CreateHorizontalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step3. Scroll to grid's end position without animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: Only onScroll and onReachEnd should be triggered
     */
    auto controller = pattern_->positionController_;
    controller->JumpTo(19, false, ScrollAlign::END, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_FALSE(isOnScrollStartCallBack);
    EXPECT_FALSE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack);
    EXPECT_TRUE(isOnReachEndCallBack);
}

/**
 * @tc.name: HorizontalGridWithScrollBarWithAnimation001
 * @tc.desc: Test Grid(Axis::HORIZONTAL) Scroll With Scroll Bar With Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, HorizontalGridWithScrollBarWithAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset; scrollState = state; isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGrid([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        gridModelNG.SetSupportAnimation(true);
        CreateHorizontalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's center with animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: OnScroll OnScrollStart and onScrollStop call back functions should be triggered
     */
    auto controller = pattern_->positionController_;
    controller->AnimateTo(Dimension(-5*ITEM_WIDTH, DimensionUnit::PX), 1.f, Curves::LINEAR, false);
    pattern_->animator_->Stop();
    pattern_->SetScrollAbort(false);
    pattern_->OnScrollEndCallback();
    pattern_->UpdateCurrentOffset(-5*ITEM_WIDTH, SCROLL_FROM_ANIMATION_CONTROLLER);

    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack); EXPECT_TRUE(isOnScrollStartCallBack); EXPECT_TRUE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack); EXPECT_FALSE(isOnReachEndCallBack);
}

/**
 * @tc.name: HorizontalGridWithScrollBarWithAnimation002
 * @tc.desc: Test Grid(Axis::HORIZONTAL) Scroll With Scroll Bar With Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, HorizontalGridWithScrollBarWithAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset; scrollState = state; isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    CreateGrid([onScroll, onScrollStart, onScrollStop, onReachStart, onReachEnd](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr");
        gridModelNG.SetOnScroll(onScroll);
        gridModelNG.SetOnScrollStart(onScrollStart);
        gridModelNG.SetOnScrollStop(onScrollStop);
        gridModelNG.SetOnReachStart(onReachStart);
        gridModelNG.SetOnReachEnd(onReachEnd);
        gridModelNG.SetSupportAnimation(true);
        CreateHorizontalItem(20);
    });
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's end without animation, and check the
     *                   five kinds of call back functions is triggered or not.
     * @tc.expected:All call back functions except onReachStart should be triggered
     */
    auto controller = pattern_->positionController_;
    controller->AnimateTo(Dimension(-10*ITEM_WIDTH, DimensionUnit::PX), 1.f, Curves::LINEAR, false);
    pattern_->animator_->Stop();
    pattern_->SetScrollAbort(false);
    pattern_->OnScrollEndCallback();
    pattern_->UpdateCurrentOffset(-10*ITEM_WIDTH, SCROLL_FROM_ANIMATION_CONTROLLER);

    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(isOnScrollCallBack); EXPECT_TRUE(isOnScrollStartCallBack); EXPECT_TRUE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack); EXPECT_TRUE(isOnReachEndCallBack);
}

/**
 * @tc.name: GetOverScrollOffset001
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GetOverScrollOffset001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        CreateVerticalItem(10);
    });

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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        CreateVerticalItem(8);
    });

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    OverScrollOffset expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    pattern_->gridLayoutInfo_.currentOffset_ = -ITEM_HEIGHT;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2);
    expectOffset = { ITEM_HEIGHT, ITEM_HEIGHT };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2);
    expectOffset = { 0, -ITEM_HEIGHT * 2 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    pattern_->gridLayoutInfo_.currentOffset_ = -ITEM_HEIGHT * 2;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { 0, ITEM_HEIGHT };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
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
    expectOffset = { 0, ITEM_HEIGHT  * 2 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
}

/**
 * @tc.name: ScrollToFocusNodeIndex001
 * @tc.desc: Test ScrollToFocusNodeIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, ScrollToFocusNodeIndex001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        CreateVerticalItem(10, true);
    });

    /**
     * @tc.steps: step1. Focus node outside the viewport
     * @tc.expected: scroll to the node
     */
    int32_t focusNodeIndex = 6;
    pattern_->ScrollToFocusNodeIndex(focusNodeIndex);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    RefPtr<FocusHub> focusNode = GetChildFocusHub(frameNode_, focusNodeIndex);
    EXPECT_TRUE(focusNode->IsCurrentFocus());
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    /**
     * @tc.steps: step2. Focus node index not exist
     * @tc.expected: do nothing
     */
    focusNodeIndex = 10;
    pattern_->ScrollToFocusNodeIndex(focusNodeIndex);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
}

/**
 * @tc.name: ScrollToNode001
 * @tc.desc: Test ScrollToNode
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, ScrollToNode001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr");
        CreateVerticalItem(10, true);
    });

    /**
     * @tc.steps: step1. Focus node outside the viewport
     * @tc.expected: scroll to the node
     */
    int32_t focusNodeIndex = 6;
    RefPtr<FrameNode> focusNode = GetChildFrameNode(frameNode_, focusNodeIndex);
    pattern_->ScrollToNode(focusNode);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
}

/**
 * @tc.name: EventHub001
 * @tc.desc: Test GetInsertPosition func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, EventHub001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(8);
    });
    RectF gridRect(0.f, 0.f, DEVICE_WIDTH, DEVICE_HEIGHT);
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode_->renderContext_);
    mockRenderContext->rect_ = gridRect;

    /**
     * @tc.steps: step1. call GetInsertPosition func.
     */
    EXPECT_EQ(eventHub_->GetInsertPosition(DEVICE_WIDTH + 1, DEVICE_HEIGHT), NULL_VALUE); // out of grid
    EXPECT_EQ(eventHub_->GetInsertPosition(0.f, 0.f), 0); // 0, 0
    EXPECT_EQ(eventHub_->GetInsertPosition(ITEM_WIDTH / 2, ITEM_HEIGHT / 2), 0); // first item
    EXPECT_EQ(eventHub_->GetInsertPosition(ITEM_WIDTH * 2, ITEM_HEIGHT / 2), 1); // between the second and third
    EXPECT_EQ(eventHub_->GetInsertPosition(ITEM_WIDTH * 2, ITEM_HEIGHT), 1); // between the 2nd, 3rd, 6th, 7th
    EXPECT_EQ(eventHub_->GetInsertPosition(ITEM_WIDTH, DEVICE_HEIGHT), 8); // in grid but not on item
    pattern_->GetGridLayoutInfo().currentRect_ = RectF(0.f, 0.f, 180.f, 300.f);
    EXPECT_EQ(eventHub_->GetInsertPosition(180.f, 300.f), 5); // on currentRect_

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
    CreateGrid([](GridModelNG gridModelNG) {
        CreateVerticalItem(14);
    });
    auto controller = pattern_->positionController_;
    controller->JumpTo(1, false, ScrollAlign::START, 3);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, NULL_VALUE);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    /**
     * @tc.steps: step2. Test JumpTo func.
     * @tc.expected: Verify return value.
     */
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
    controller = pattern_->positionController_;
    controller->JumpTo(1, false, ScrollAlign::START, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(19, false, ScrollAlign::START, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(11, false, ScrollAlign::START, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
    controller = pattern_->positionController_;
    controller->JumpTo(1, false, ScrollAlign::CENTER, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(12, false, ScrollAlign::CENTER, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(11, false, ScrollAlign::CENTER, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(-100.f));

    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
    controller = pattern_->positionController_;
    controller->JumpTo(1, false, ScrollAlign::END, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(12, false, ScrollAlign::END, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(11, false, ScrollAlign::END, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
    controller = pattern_->positionController_;
    controller->JumpTo(1, false, ScrollAlign::AUTO, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(12, false, ScrollAlign::AUTO, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(11, false, ScrollAlign::AUTO, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
    controller = pattern_->positionController_;
    controller->JumpTo(1, false, ScrollAlign::NONE, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(12, false, ScrollAlign::NONE, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    controller->JumpTo(11, false, ScrollAlign::NONE, 3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
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
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, NULL_VALUE);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, NULL_VALUE);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 19);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 0);

    /**
     * @tc.steps: step6. Test ScrollPage func.
     * @tc.expected: Verify currentOffset.
     */
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    controller->ScrollPage(true, true);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset(0, -DEVICE_HEIGHT));

    controller->ScrollPage(false, true);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset(0, 0));

    /**
     * @tc.steps: step7. Test IsAtEnd func.
     */
    EXPECT_FALSE(controller->IsAtEnd());
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        CreateHorizontalItem(20);
    });
    RunMeasureAndLayout(frameNode_, 300.f, DEVICE_HEIGHT);

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
    EXPECT_TRUE(IsEqual(controller->GetCurrentOffset(), Offset(-280.f, 0)));
    EXPECT_EQ(pattern_->GetMainContentSize(), 300.f);
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqual(controller->GetCurrentOffset(), Offset(20.f, 0)));
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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetMultiSelectable(true);
        gridModelNG.SetEditable(true);
        CreateVerticalItem(14);
    });

    /**
     * @tc.steps: step1. Run accessibility func.
     * @tc.expected: The return_value is correct.
     */
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_TRUE(accessibilityProperty_->IsEditable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 13);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), 14);
    AceCollectionInfo info = accessibilityProperty_->GetCollectionInfo();
    EXPECT_EQ(info.rows, 4);
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
    CreateGrid([](GridModelNG gridModelNG) {
        CreateVerticalItem(8);
    });

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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
    UpdateCurrentOffset(ITEM_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_1 = 0;
    exptectActions_1 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_1);

    /**
     * @tc.steps: step2. Scroll to middle.
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_2 = 0;
    exptectActions_2 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions_2 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_2);

    /**
     * @tc.steps: step3. Scroll to bottom.
     */
    UpdateCurrentOffset(-ITEM_HEIGHT * 2);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_3 = 0;
    exptectActions_3 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_3);

    /**
     * @tc.steps: step4. UnScrollable.
     */
    CreateGrid([](GridModelNG gridModelNG) {
        CreateVerticalItem(14);
    });
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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        GridItemModelNG gridItemModel;
        gridItemModel.Create(GridItemStyle::NONE);
        gridItemModel.SetColumnStart(0);
        gridItemModel.SetColumnEnd(3);
        SetHeight(Dimension(ITEM_HEIGHT));
        ViewStackProcessor::GetInstance()->Pop();
        CreateVerticalItem(10);
    });

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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetMultiSelectable(true);
        CreateVerticalItem(8);
    });

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
    float itemWidth = DEVICE_WIDTH / 4;
    const Offset LEFT_TOP = Offset(itemWidth * 0.5, ITEM_HEIGHT * 0.5);
    const Offset LEFT_BOTTOM = Offset(itemWidth * 0.5, ITEM_HEIGHT * 1.5);
    const Offset RIGHT_TOP = Offset(itemWidth * 1.5, ITEM_HEIGHT * 0.5);
    const Offset RIGHT_BOTTOM = Offset(itemWidth * 1.5, ITEM_HEIGHT * 1.5);
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetMultiSelectable(true);
        CreateVerticalItem(8);
    });

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
    float itemHeight = DEVICE_HEIGHT / 4;
    const Offset LEFT_TOP = Offset(ITEM_WIDTH * 0.5, itemHeight * 0.5);
    const Offset LEFT_BOTTOM = Offset(ITEM_WIDTH * 0.5, itemHeight * 1.5);
    const Offset RIGHT_TOP = Offset(ITEM_WIDTH * 1.5, itemHeight * 0.5);
    const Offset RIGHT_BOTTOM = Offset(ITEM_WIDTH * 1.5, itemHeight * 1.5);
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetMultiSelectable(true);
        CreateHorizontalItem(8);
    });

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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetMultiSelectable(true);
        CreateVerticalItem(10);
    });
    bool isSixthItemSelected = false;
    auto selectCallback = [&isSixthItemSelected](bool) { isSixthItemSelected = true; };
    GetChildPattern<GridItemPattern>(frameNode_, 1)->SetSelectable(false);
    GetChildEventHub<GridItemEventHub>(frameNode_, 2)->SetEnabled(false);
    GetChildEventHub<GridItemEventHub>(frameNode_, 5)->SetOnSelect(std::move(selectCallback));
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);

    /**
     * @tc.steps: step2. Select zone, include 2nd, 3rd, 6th, 7th item.
     * @tc.expected: The 2nd and 3rd item is not selected but 6th item is selected.
     */
    float itemWidth = DEVICE_WIDTH / 4;
    MouseSelect(Offset(itemWidth * 1.5, ITEM_HEIGHT * 1.5), Offset(itemWidth * 2.5, ITEM_HEIGHT * 1.5));
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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetMultiSelectable(true);
        CreateVerticalItem(8);
    });
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
    auto onItemDragStart = [](const ItemDragInfo&, int32_t) {
        auto dragItem = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
        return AceType::DynamicCast<UINode>(dragItem);
    };
    CreateGrid([onItemDragStart](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetEditable(true);
        gridModelNG.SetOnItemDragStart(onItemDragStart);
        CreateVerticalItem(8);
    });
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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetEditable(true);
        gridModelNG.SetSupportAnimation(true);
        CreateBigItem(NULL_VALUE, NULL_VALUE, 2, 3, NULL_VALUE, ITEM_HEIGHT);
        CreateBigItem(NULL_VALUE, NULL_VALUE, 0, 2, NULL_VALUE, ITEM_HEIGHT);
        CreateBigItem(NULL_VALUE, NULL_VALUE, 2, 1, NULL_VALUE, ITEM_HEIGHT);
        CreateVerticalItem(8);
    });
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
    eventHub_->FireOnItemDragLeave(dragInfo, NULL_VALUE);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 11);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);

    /**
     * @tc.steps: step2. Drag 2nd item to 3rd item, Drag 3 item to 2 item.
     * @tc.expected: GetOriginalIndex changed.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 1, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    eventHub_->FireOnItemDragLeave(dragInfo, NULL_VALUE);
    eventHub_->FireOnItemDragEnter(dragInfo);
    // 3 to 2
    eventHub_->FireOnItemDragMove(dragInfo, 2, 1);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 1);
    // SupportAnimation, ClearDragState
    eventHub_->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);

    /**
     * @tc.steps: step3. Move something to 3rd item.
     * @tc.expected: GetOriginalIndex changed.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, NULL_VALUE);
    eventHub_->FireOnItemDragMove(dragInfo, NULL_VALUE, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    // SupportAnimation, ClearDragState
    eventHub_->FireOnItemDrop(dragInfo, NULL_VALUE, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);

    /**
     * @tc.steps: step4. Move one item to wrong insertIndex.
     * @tc.expected: GetOriginalIndex unchanged.
     */
    // insertIndex < 0
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 1, NULL_VALUE);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    // insertIndex >= itemCount
    eventHub_->FireOnItemDragMove(dragInfo, 1, 11);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
}

/**
 * @tc.name: Drag003
 * @tc.desc: Verify drag func with SetLayoutDirection
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Drag003, TestSize.Level1)
{
    const int32_t itemCount = 8;
    CreateGrid([itemCount](GridModelNG gridModelNG) {
        gridModelNG.SetLayoutDirection(FlexDirection::ROW);
        gridModelNG.SetEditable(true);
        gridModelNG.SetCellLength(ITEM_HEIGHT);
        gridModelNG.SetMinCount(2);
        gridModelNG.SetMaxCount(4);
        gridModelNG.SetSupportAnimation(true);
        CreateVerticalItem(itemCount);
    });
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
    eventHub_->FireOnItemDragLeave(dragInfo, NULL_VALUE);
    EXPECT_EQ(pattern_->GetOriginalIndex(), itemCount);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);

    /**
     * @tc.steps: step2. Drag 2nd item to 3rd item, Drag 3 item to 2 item.
     * @tc.expected: GetOriginalIndex changed.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 1, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    eventHub_->FireOnItemDragLeave(dragInfo, NULL_VALUE);
    eventHub_->FireOnItemDragEnter(dragInfo);
    // 3 to 2
    eventHub_->FireOnItemDragMove(dragInfo, 2, 1);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 1);
    // SupportAnimation, ClearDragState
    eventHub_->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);

    /**
     * @tc.steps: step3. Move something to 3rd item.
     * @tc.expected: GetOriginalIndex changed.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, NULL_VALUE);
    eventHub_->FireOnItemDragMove(dragInfo, NULL_VALUE, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    // SupportAnimation, ClearDragState
    eventHub_->FireOnItemDrop(dragInfo, NULL_VALUE, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);

    /**
     * @tc.steps: step4. Move one item to wrong insertIndex.
     * @tc.expected: GetOriginalIndex unchanged.
     */
    // insertIndex < 0
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 1, NULL_VALUE);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    // insertIndex >= itemCount
    eventHub_->FireOnItemDragMove(dragInfo, 1, itemCount);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
}

/**
 * @tc.name:FocusStep001
 * @tc.desc: Test GetNextFocusNode func
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(10, true);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step3. GetNextFocusNode from left_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 8;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 7));

    /**
     * @tc.steps: step4. GetNextFocusNode from right_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 9;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 8));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        CreateHorizontalItem(10, true);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 8;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 7));

    /**
     * @tc.steps: step3. GetNextFocusNode from left_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step4. GetNextFocusNode from right_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 9;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 8));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 4));
}

/**
 * @tc.name:FocusStep003
 * @tc.desc: Test GetNextFocusNode() with colTemplate/rowTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep003, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateItem(10, NULL_VALUE, NULL_VALUE, true);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step3. GetNextFocusNode from left_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 8;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 7));

    /**
     * @tc.steps: step4. GetNextFocusNode from right_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 9;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 8));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 4));
}

/**
 * @tc.name: FocusStep004
 * @tc.desc: Test GetNextFocusNode func when exist big item
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep004, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateBigItem(NULL_VALUE, NULL_VALUE, 2, 3, NULL_VALUE, ITEM_HEIGHT);
        CreateBigItem(NULL_VALUE, NULL_VALUE, 0, 2, NULL_VALUE, ITEM_HEIGHT);
        CreateBigItem(NULL_VALUE, NULL_VALUE, 2, 1, NULL_VALUE, ITEM_HEIGHT);
        CreateVerticalItem(7, true);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from BigItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from BigItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 1;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step3. GetNextFocusNode from BigItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step4. GetNextFocusNode from NormalItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step5. GetNextFocusNode from NormalItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 4));
}

/**
 * @tc.name: FocusStep005
 * @tc.desc: Test GetNextFocusNode func when exist big item with RowsTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep005, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        CreateBigItem(1, 2, NULL_VALUE, NULL_VALUE, ITEM_WIDTH, NULL_VALUE);
        CreateBigItem(0, 2, NULL_VALUE, NULL_VALUE, ITEM_WIDTH, NULL_VALUE);
        CreateBigItem(2, 3, NULL_VALUE, NULL_VALUE, ITEM_WIDTH, NULL_VALUE);
        CreateHorizontalItem(7, true);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from BigItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from BigItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 1;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step3. GetNextFocusNode from BigItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step4. GetNextFocusNode from NormalItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step5. GetNextFocusNode from NormalItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 4));
}

/**
 * @tc.name: FocusStep006
 * @tc.desc: Test GetNextFocusNode func when exist big item with colTemplate/rowTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep006, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateBigItem(1, 2, 1, 2);
        CreateBigItem(NULL_VALUE, NULL_VALUE, 1, 3);
        CreateBigItem(1, 3, NULL_VALUE, NULL_VALUE);
        CreateItem(7, NULL_VALUE, NULL_VALUE, true);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from BigItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    /**
     * @tc.steps: step2. GetNextFocusNode from BigItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 1;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step3. GetNextFocusNode from BigItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 7));

    /**
     * @tc.steps: step4. GetNextFocusNode from NormalItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step5. GetNextFocusNode from NormalItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 4));
}

/**
 * @tc.name: FocusStep007
 * @tc.desc: Test GetNextFocusNode func when has unfocuseable item
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep007, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(10, true);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from 1st item and FocusStep::RIGHT.
     * @tc.expected: The 3rd item is focused.
     */
    GetChildFocusHub(frameNode_, 1)->SetFocusable(false); // The 2nd item can not focus.
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 2));
}

/**
 * @tc.name: FocusStep008
 * @tc.desc: Test GetNextFocusNode func from top boundary item in Scrollable Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep008, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(24, true);
    });

    /**
     * @tc.steps: step1. Scroll to second row
     */
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT - 1.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);

    /**
     * @tc.steps: step2. UP
     */
    int32_t currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_EQ(pattern_->gridLayoutInfo_.jumpIndex_, 3);
}

/**
 * @tc.name: FocusStep009
 * @tc.desc: Test GetNextFocusNode func from bottom boundary item in Scrollable Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, FocusStep009, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(24, true);
    });

    /**
     * @tc.steps: step1. Scroll to first row
     */
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT + 1.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);

    /**
     * @tc.steps: step2. DOWN
     */
    int32_t currentIndex = 19;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_EQ(pattern_->gridLayoutInfo_.jumpIndex_, 20);
}

/**
 * @tc.name: Focus001
 * @tc.desc: Test Foucus
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, Focus001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(18, true);
    });

    /**
     * @tc.steps: step1. When focus grid from the outside
     * @tc.expected: Will focus first child
     */
    auto gridFocusNode = frameNode_->GetOrCreateFocusHub();
    gridFocusNode->RequestFocusImmediately();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());

    /**
     * @tc.steps: step2. When grid IsCurrentFocus and has lastFocus child
     * @tc.expected: Will focus last child
     */
    GetChildFocusHub(frameNode_, 1)->RequestFocusImmediately();
    gridFocusNode->RequestFocusImmediately();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 1)->IsCurrentFocus());

    /**
     * @tc.steps: step3. Scroll to second row
     * @tc.expected: Would change startMainLineIndex_, focus last child.
     */
    gridFocusNode->RequestFocusImmediately();
    UpdateCurrentOffset(-ITEM_HEIGHT - 1.f);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 1)->IsCurrentFocus());
}

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: Test grid pattern UpdateCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
    UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentOffset(-100.f));
    UpdateCurrentOffset(100.f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    UpdateCurrentOffset(-200.f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentOffset(-200.f));

    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
    UpdateCurrentOffset(-100.f, SCROLL_FROM_BAR);
    EXPECT_TRUE(IsEqualCurrentOffset(-100.f));
    UpdateCurrentOffset(100.f, SCROLL_FROM_BAR);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    UpdateCurrentOffset(-200.f, SCROLL_FROM_BAR);
    EXPECT_TRUE(IsEqualCurrentOffset(-200.f));

    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
    pattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::FADE);
    UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentOffset(-100.f));
    UpdateCurrentOffset(100.f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentOffset(0));
    UpdateCurrentOffset(-200.f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentOffset(-200.f));
}

/**
 * @tc.name: GridPaintMethodTest001
 * @tc.desc: Test grid paint method GetForegroundDrawFunction function
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridPaintMethodTest001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr");
        CreateVerticalItem(10);
    });
    auto paintMethod = AceType::DynamicCast<GridPaintMethod>(pattern_->CreateNodePaintMethod());
    auto paintProperty = pattern_->CreatePaintProperty();
    PaintWrapper paintWrapper(frameNode_->GetRenderContext(), frameNode_->GetGeometryNode(), paintProperty);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
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
    const Offset clickPosition = Offset(100.f, DEVICE_HEIGHT + ITEM_HEIGHT);
    textFieldManager->SetClickPosition(clickPosition);

    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetMaxCount(2);
        CreateVerticalItem(18, true);
    });
    const float smallerHeight = DEVICE_HEIGHT - ITEM_HEIGHT;
    RectF gridRect(0.f, 0.f, DEVICE_WIDTH, smallerHeight);
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode_->renderContext_);
    mockRenderContext->rect_ = gridRect;

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
    EXPECT_FLOAT_EQ(currentOffset, -ITEM_HEIGHT);
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

    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetMaxCount(2);
        CreateVerticalItem(18, true);
    });

    /**
     * @tc.steps: step1. While axis_ == Axis::HORIZONTAL
     * @tc.expected: currentOffset_ would not change
     */
    pattern_->gridLayoutInfo_.axis_ = Axis::HORIZONTAL;
    const float smallerHeight = DEVICE_HEIGHT - ITEM_HEIGHT;
    // change grid height and trigger Measure
    UpdateLayoutWrapper(frameNode_, DEVICE_WIDTH, smallerHeight);
    float currentOffset = pattern_->gridLayoutInfo_.currentOffset_;
    EXPECT_FLOAT_EQ(currentOffset, 0.f);

    /**
     * @tc.steps: step2. While Grid !IsCurrentFocus()
     * @tc.expected: currentOffset_ would not change
     */
    UpdateLayoutWrapper(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT); // reset Grid height
    pattern_->gridLayoutInfo_.axis_ = Axis::VERTICAL;
    // change grid height and trigger Measure
    UpdateLayoutWrapper(frameNode_, DEVICE_WIDTH, smallerHeight);
    currentOffset = pattern_->gridLayoutInfo_.currentOffset_;
    EXPECT_FLOAT_EQ(currentOffset, 0.f);

    /**
     * @tc.steps: step3. While clickPosition is in Grid
     * @tc.expected: currentOffset_ would not change
     */
    UpdateLayoutWrapper(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT); // reset Grid height
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
    float itemWidth = 100.f;
    CreateGrid([itemWidth](GridModelNG gridModelNG) {
        gridModelNG.SetLayoutDirection(FlexDirection::ROW);
        gridModelNG.SetEditable(true);
        gridModelNG.SetCellLength(ITEM_HEIGHT);
        gridModelNG.SetMinCount(4);
        gridModelNG.SetMaxCount(2);
        CreateItem(10, itemWidth, ITEM_HEIGHT);
    });

    /**
     * @tc.steps: step1. While the before set minCount > maxCount
     * @tc.expected: would let minCount = 1, maxCount = Infinity;
     */
    int32_t colsNumber = 4; // 4 * 100(itemWidth) < 480(gridWidth)
    for (int32_t index = 0; index < 10; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = index % colsNumber * itemWidth;
        float offsetY = floor(index / colsNumber) * ITEM_HEIGHT;
        RectF expectRect = RectF(offsetX, offsetY, itemWidth, ITEM_HEIGHT);
        EXPECT_TRUE(IsEqual(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: GirdItem Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, PerformActionTest001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(10);
    });
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(IsEqualCurrentOffset(0.f));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(IsEqualCurrentOffset(0.f));

    /**
     * @tc.steps: step2. When grid is Scrollable
     * @tc.expected: can scrollpage
     */
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(IsEqualCurrentOffset(-DEVICE_HEIGHT));
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
    CreateGrid([](GridModelNG gridModelNG) {
        ScrollBarUpdateFunc scrollFunc = [](int32_t index, Dimension offset) {
            std::optional<float> horizontalOffset = offset.ConvertToPx();
            std::optional<float> verticalOffset = offset.ConvertToPx();
            return std::make_pair(horizontalOffset, verticalOffset);
        };
        gridModelNG.SetRowsTemplate("1fr 1fr");
        gridModelNG.SetRowsGap(Dimension(5));
        gridModelNG.SetOnScrollBarUpdate(std::move(scrollFunc));
        CreateBigItem(1, 1, 1, 2);
        CreateVerticalItem(2);
    });
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
    EXPECT_EQ(ret.GetY(), 100.f - ITEM_HEIGHT);
    EXPECT_EQ(ret.GetX(), 100.f);
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
    CreateVerticalItem(10);
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
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr");
        GridItemModelNG gridItemModelNG;
        gridItemModelNG.Create(GridItemStyle::NONE);
        gridItemModelNG.SetRowStart(NULL_VALUE);
        gridItemModelNG.SetRowEnd(NULL_VALUE);
        gridItemModelNG.SetColumnStart(NULL_VALUE);
        gridItemModelNG.SetColumnEnd(NULL_VALUE);
        ViewStackProcessor::GetInstance()->Pop();
    });
    auto layoutProperty = GetChildLayoutProperty<GridItemLayoutProperty>(frameNode_, 0);
    EXPECT_EQ(layoutProperty->GetRowStart(), NULL_VALUE);
    EXPECT_EQ(layoutProperty->GetRowEnd(), NULL_VALUE);
    EXPECT_EQ(layoutProperty->GetColumnStart(), NULL_VALUE);
    EXPECT_EQ(layoutProperty->GetColumnEnd(), NULL_VALUE);
}

/**
 * @tc.name: GridSetFrictionTest001
 * @tc.desc: Test SetFriction Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridSetFriction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. friction <= 0
     * @tc.expected: friction would be default
     */
    CreateGrid([](GridModelNG gridModelNG) { gridModelNG.SetFriction(NULL_VALUE); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
    CreateGrid([](GridModelNG gridModelNG) { gridModelNG.SetFriction(0); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);

    /**
     * @tc.steps: step2. friction > 0
     * @tc.expected: friction would be itself
     */
    CreateGrid([](GridModelNG gridModelNG) { gridModelNG.SetFriction(1); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 1);
}

/**
 * @tc.name: ScrollTo001
 * @tc.desc: Test ScrollTo Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, ScrollTo001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(10);
    });
    pattern_->ScrollTo(ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(0));

    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
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
    /**
     * @tc.steps: step1. Create 10 gridItem
     */
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(10);
    });
    EXPECT_EQ(pattern_->GetTotalHeight(), ITEM_HEIGHT * 3);

    /**
     * @tc.steps: step2. Create 20 gridItem
     */
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
    EXPECT_EQ(pattern_->GetTotalHeight(), ITEM_HEIGHT * 5);
}

/**
 * @tc.name: GetAverageHeight001
 * @tc.desc: Test GetAverageHeight Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GetAverageHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create 10 gridItem
     */
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(10);
    });
    EXPECT_EQ(pattern_->GetAverageHeight(), 60);

    /**
     * @tc.steps: step2. Create 20 gridItem
     */
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateVerticalItem(20);
    });
    EXPECT_EQ(pattern_->GetAverageHeight(), 50);
}

/**
 * @tc.name: GridItemHoverEventTest001
 * @tc.desc: GirdItem hover event test.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridItemHoverEventTest001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        CreateVerticalItem(10, false, GridItemStyle::PLAIN);
    });

    /**
     * @tc.steps: step2. Get girdItem frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    gridItemPattern->isPressed_ = false;
    gridItemPattern->HandleHoverEvent(true);
    EXPECT_TRUE(gridItemPattern->isHover_);
    gridItemPattern->HandleHoverEvent(false);
    EXPECT_FALSE(gridItemPattern->isHover_);

    /**
     * @tc.steps: step3. Test gridItem hover event when hoverEvent_ has value.
     * @tc.expected: InitHoverEvent func will return.
     */
    gridItemPattern->hoverEvent_ = AceType::MakeRefPtr<InputEvent>([](MouseInfo&) {});
    gridItemPattern->InitHoverEvent();
}

/**
 * @tc.name: GridItemPressEventTest001
 * @tc.desc: GirdItem press event test.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridItemPressEventTest001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        CreateVerticalItem(10, false, GridItemStyle::PLAIN);
    });

    /**
     * @tc.steps: step2. Get girdItem frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    gridItemPattern->isHover_ = false;
    gridItemPattern->HandlePressEvent(true);
    EXPECT_TRUE(gridItemPattern->isPressed_);
    gridItemPattern->HandlePressEvent(false);
    EXPECT_FALSE(gridItemPattern->isPressed_);

    /**
     * @tc.steps: step3. Test gridItem press event when touchListener_ has value.
     * @tc.expected: InitPressEvent func will return.
     */
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gridItemPattern->touchListener_ = touchEvent;
    gridItemPattern->InitPressEvent();
}

/**
 * @tc.name: GridItemDisableEventTest001
 * @tc.desc: GirdItem disable event test.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridItemDisableEventTest001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) {
        CreateVerticalItem(10, false, GridItemStyle::PLAIN);
    });

    /**
     * @tc.steps: step2. Get girdItem frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    auto gridItemEventHub = GetChildEventHub<GridItemEventHub>(frameNode_, 0);
    gridItemEventHub->SetEnabled(false);
    gridItemPattern->InitDisableStyle();
    gridItemEventHub->SetEnabled(true);
    gridItemPattern->InitDisableStyle();
}

/**
 * @tc.name: GridItemGetInnerFocusPaintRectTest001
 * @tc.desc: GirdItem GetInnerFocusPaintRect test.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridItemGetInnerFocusPaintRectTest001, TestSize.Level1)
{
    CreateGrid([](GridModelNG gridModelNG) { CreateVerticalItem(10); });
    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);

    /**
     * @tc.steps: step1. Set paintRect when grid item does not have border radius.
     * @tc.expected: Focus border radius is equal to 4.0_vp.
     */
    RoundRect paintRect;
    gridItemPattern->GetInnerFocusPaintRect(paintRect);
    EdgeF radius = paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS);
    float expectRadius = GRIDITEM_FOCUS_INTERVAL.ConvertToPx();
    EXPECT_EQ(radius.x, expectRadius);
    EXPECT_EQ(radius.y, expectRadius);

    /**
     * @tc.steps: step2. Set paintRect when grid item has border radius.
     * @tc.expected: Focus border radius is equal to 11.0_vp.
     */
    auto renderContext = gridItemNode->GetRenderContext();
    renderContext->UpdateBorderRadius({ BORDER_RADIUS, BORDER_RADIUS, BORDER_RADIUS, BORDER_RADIUS });
    gridItemPattern->GetInnerFocusPaintRect(paintRect);
    radius = paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS);
    expectRadius = (GRIDITEM_FOCUS_INTERVAL + BORDER_RADIUS).ConvertToPx();
    EXPECT_EQ(radius.x, expectRadius);
    EXPECT_EQ(radius.y, expectRadius);
}

/**
 * @tc.name: GridScrollWithOptions001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridScrollWithOptions001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5, 0 };
    auto onGetIrregularSizeByIndex = [](int32_t index) {
        GridItemSize gridItemSize;
        return gridItemSize;
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    CreateGrid([option](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetLayoutOptions(option);
        CreateVerticalItem(10);
    });

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm = AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(
        layoutAlgorithmWrapper->GetLayoutAlgorithm());
    layoutAlgorithm->GetTargetIndexInfoWithBenchMark(AccessibilityManager::RawPtr(frameNode_), false, 5);
    EXPECT_EQ(layoutAlgorithm->gridLayoutInfo_.startMainLineIndex_, 1);
}

/**
 * @tc.name: GridScrollWithOptions002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridScrollWithOptions002, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5, 0 };
    CreateGrid([option](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetLayoutOptions(option);
        CreateHorizontalItem(10);
    });

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm = AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(
        layoutAlgorithmWrapper->GetLayoutAlgorithm());
    layoutAlgorithm->GetTargetIndexInfoWithBenchMark(AccessibilityManager::RawPtr(frameNode_), false, 5);
    EXPECT_EQ(layoutAlgorithm->gridLayoutInfo_.startMainLineIndex_, 5);
}

/**
 * @tc.name: GridScrollWithOptions003
 * @tc.desc: change grid columns after scroll
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridScrollWithOptions003, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5 };
    auto onGetIrregularSizeByIndex = [](int32_t index) {
        GridItemSize gridItemSize { 1, 2 };
        return gridItemSize;
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    CreateGrid([option](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr");
        gridModelNG.SetLayoutOptions(option);
        CreateHorizontalItem(10);
    });
    pattern_->UpdateStartIndex(3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(3, option, 1), std::make_pair(0, 2));
}

/**
 * @tc.name: GridScrollWithOptions004
 * @tc.desc: change grid columns after scroll, first line has empty position
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridScrollWithOptions004, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5 };
    auto onGetIrregularSizeByIndex = [](int32_t index) {
        GridItemSize gridItemSize { 1, 2 };
        return gridItemSize;
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    CreateGrid([option](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr");
        gridModelNG.SetLayoutOptions(option);
        CreateHorizontalItem(10);
    });
    pattern_->UpdateStartIndex(3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr 1fr 1fr");
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, DEVICE_HEIGHT);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(3, option, 1), std::make_pair(0, 2));
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(2, option, 1), std::make_pair(3, 2));
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(1, option, 1), std::make_pair(1, 2));
}

/**
 * @tc.name: GridScrollWithOptions005
 * @tc.desc: second line full
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridScrollWithOptions005, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5 };
    auto onGetIrregularSizeByIndex = [](int32_t index) {
        GridItemSize gridItemSize { 1, 2 };
        return gridItemSize;
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    CreateGrid([option](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetLayoutOptions(option);
        CreateHorizontalItem(10);
    });
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(3, option, 1), std::make_pair(2, 2));
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(2, option, 1), std::make_pair(0, 2));
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(1, option, 1), std::make_pair(1, 2));
}

/**
 * @tc.name: GridScrollWithOptions006
 * @tc.desc: first irregular item in new line
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridScrollWithOptions006, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 3, 4, 5 };
    auto onGetIrregularSizeByIndex = [](int32_t index) {
        GridItemSize gridItemSize { 1, 2 };
        return gridItemSize;
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    CreateGrid([option](GridModelNG gridModelNG) {
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetLayoutOptions(option);
        CreateHorizontalItem(10);
    });
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(4, option, 1), std::make_pair(2, 2));
}

/**
 * @tc.name: GridDistributed001
 * @tc.desc: Test the distributed capability of Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridDistributed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Grid node
     */
    CreateGrid();

    /**
     * @tc.steps: step2. get pattern .
     * @tc.expected: function ProvideRestoreInfo is called.
     */
    pattern_->gridLayoutInfo_.startIndex_ = 1;
    std::string ret = pattern_->ProvideRestoreInfo();

    /**
     * @tc.steps: step3. function OnRestoreInfo is called.
     * @tc.expected: Passing JSON format.
     */
    pattern_->OnRestoreInfo(ret);
    EXPECT_EQ(pattern_->gridLayoutInfo_.jumpIndex_, 1);
}

/**
 * @tc.name: SearchIrregularFocusableChildInScroll001
 * @tc.desc: Test the function when the gridItem cannot be focused
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, SearchIrregularFocusableChildInScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gridItems with irregular shape in scroll grid.
     */
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5, 0 };
    CreateGrid([option](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetLayoutOptions(option);
        CreateHorizontalItem(10);
    });

    /**
     * @tc.steps: step2. Find target child with specified index parameters.
     * @tc.expected: Can not find the target focus child.
     */
    int32_t tarMainIndex = 1;
    int32_t tarCrossIndex = 1;
    auto IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    RefPtr<FocusHub> result = IrregularFocusableChild.Upgrade();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: SearchIrregularFocusableChildInScroll002
 * @tc.desc: Test the function when the gridItem can be focused
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, SearchIrregularFocusableChildInScroll002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gridItems with irregular shape in scroll grid.
     */
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5, 0 };
    CreateGrid([option](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetLayoutOptions(option);
        CreateHorizontalItem(10, true);
    });

    /**
     * @tc.steps: step2. Find target child with specified index parameters.
     * @tc.expected: Can not find the target focus child.
     */
    int32_t tarMainIndex = 1;
    int32_t tarCrossIndex = 1;
    auto IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    RefPtr<FocusHub> result = IrregularFocusableChild.Upgrade();
    EXPECT_EQ(result, nullptr);

    /**
     * @tc.steps: step3. Call the function when isLeftStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    tarCrossIndex = 0;
    pattern_->isLeftStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step4. Call the function when isRightStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isLeftStep_ = false;
    pattern_->isRightStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step5. Call the function when isUpStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isRightStep_ = false;
    pattern_->isUpStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step6. Call the function when isDownStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isUpStep_ = false;
    pattern_->isDownStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step7. Call the function when isLeftEndStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isDownStep_ = false;
    pattern_->isLeftEndStep_  = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step8. Call the function when isRightEndStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isLeftEndStep_ = false;
    pattern_->isRightEndStep_  = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: SearchIrregularFocusableChildInNormalGrid001
 * @tc.desc: Test ability of a fixed shape grid to obtain irregular shape focal item.
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, SearchIrregularFocusableChildInNormalGrid001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gridItems with irregular shape in fixed shape grid.
     */
    CreateGrid([](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateBigItem(1, 2, 1, 2);
        CreateHorizontalItem(10, true);
    });

    /**
     * @tc.steps: step2. Find target child with specified index parameters.
     * @tc.expected: Can find the target focus child.
     */
    int32_t tarMainIndex = 1;
    int32_t tarCrossIndex = 1;
    pattern_->isLeftStep_ = true;
    auto IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    RefPtr<FocusHub> result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step3. Call the function when isRightStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isLeftStep_ = false;
    pattern_->isRightStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step4. Call the function when isUpStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isRightStep_ = false;
    pattern_->isUpStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step5. Call the function when isDownStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isUpStep_ = false;
    pattern_->isDownStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);
}
} // namespace OHOS::Ace::NG
