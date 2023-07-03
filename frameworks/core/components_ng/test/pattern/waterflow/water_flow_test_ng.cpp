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

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/pattern.h"
#define protected public
#define private public
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_accessibility_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_event_hub.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_algorithm.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_position_controller.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float DEVICE_WIDTH = 720.0f;
constexpr float DEVICE_HEIGHT = 1136.0f;
constexpr float DEFAULT_ITEM_HEIGHT = 100.f;
constexpr float DEFAULT_WATER_FLOW_HEIGHT = 300.f;
} // namespace

class WaterFlowTestNg : public testing::Test {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    static void SetWidth(const Dimension& width);
    static void SetHeight(const Dimension& height);
    void CreateWaterFlowItem(int32_t number = 10);
    RefPtr<LayoutWrapper> RunMeasureAndLayout(float width = DEVICE_WIDTH, float height = DEFAULT_WATER_FLOW_HEIGHT);
    RefPtr<FrameNode> GetItemFrameNode(int32_t index);
    RefPtr<WaterFlowItemPattern> GetItemPattern(int32_t index);
    RefPtr<FocusHub> GetItemFocusHub(int32_t index);
    void UpdateCurrentOffset(float offset);
    void MouseSelect(Offset start, Offset end);
    void MouseSelectRelease();
    std::function<void()> GetDefaultHeaderBuilder();
    RefPtr<GeometryNode> GetChildGeometryNode(int32_t index);
    uint64_t GetActions();
    testing::AssertionResult IsEqualOverScrollOffset(OverScrollOffset offset, OverScrollOffset expectOffset);

    RefPtr<FrameNode> frameNode_;
    RefPtr<WaterFlowPattern> pattern_;
    RefPtr<WaterFlowEventHub> eventHub_;
    RefPtr<WaterFlowLayoutProperty> layoutProperty_;
    RefPtr<WaterFlowAccessibilityProperty> accessibilityProperty_;
};

void WaterFlowTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
}

void WaterFlowTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

void WaterFlowTestNg::SetUp() {}

void WaterFlowTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void WaterFlowTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<WaterFlowPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<WaterFlowLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<WaterFlowAccessibilityProperty>();
}

void WaterFlowTestNg::SetWidth(const Dimension& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), std::nullopt));
}

void WaterFlowTestNg::SetHeight(const Dimension& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(height)));
}

void WaterFlowTestNg::CreateWaterFlowItem(int32_t number)
{
    for (int32_t i = 0; i < number; i++) {
        WaterFlowItemModelNG waterFlowItemModel;
        waterFlowItemModel.Create();
        SetHeight(Dimension(DEFAULT_ITEM_HEIGHT));
        ViewStackProcessor::GetInstance()->Pop();
    }
}

RefPtr<LayoutWrapper> WaterFlowTestNg::RunMeasureAndLayout(float width, float height)
{
    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
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

RefPtr<FrameNode> WaterFlowTestNg::GetItemFrameNode(int32_t index)
{
    auto item = frameNode_->GetChildAtIndex(index);
    return AceType::DynamicCast<FrameNode>(item);
}

RefPtr<WaterFlowItemPattern> WaterFlowTestNg::GetItemPattern(int32_t index)
{
    auto item = frameNode_->GetChildAtIndex(index);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    return itemFrameNode->GetPattern<WaterFlowItemPattern>();
}

RefPtr<FocusHub> WaterFlowTestNg::GetItemFocusHub(int32_t index)
{
    auto item = frameNode_->GetChildAtIndex(index);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    return itemFrameNode->GetOrCreateFocusHub();
}

void WaterFlowTestNg::UpdateCurrentOffset(float offset)
{
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
}

std::function<void()> WaterFlowTestNg::GetDefaultHeaderBuilder()
{
    return []() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetWidth(Dimension(1.0, DimensionUnit::PERCENT));
        SetHeight(Dimension(50.f));
    };
}

RefPtr<GeometryNode> WaterFlowTestNg::GetChildGeometryNode(int32_t index)
{
    auto item = frameNode_->GetChildAtIndex(index);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    return itemFrameNode->GetGeometryNode();
}

uint64_t WaterFlowTestNg::GetActions()
{
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty_->GetSupportAction();
    uint64_t actions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    return actions;
}

testing::AssertionResult WaterFlowTestNg::IsEqualOverScrollOffset(
    OverScrollOffset offset, OverScrollOffset expectOffset)
{
    if (NearEqual(offset.start, expectOffset.start) && NearEqual(offset.end, expectOffset.end)) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "offset: "
                                       << "{ " << offset.start << " , " << offset.end << " }"
                                       << " != "
                                       << "expectOffset: "
                                       << "{ " << expectOffset.start << " , " << expectOffset.end << " }";
}

/**
 * @tc.name: Property001
 * @tc.desc: Test all the properties of WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property001, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    RefPtr<ScrollControllerBase> positionController = waterFlowModelNG.CreateScrollController();
    RefPtr<ScrollProxy> scrollBarProxy = waterFlowModelNG.CreateScrollBarProxy();
    waterFlowModelNG.Create();
    waterFlowModelNG.SetScroller(positionController, scrollBarProxy);
    waterFlowModelNG.SetRowsTemplate("1fr 1fr 1fr");
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr");
    waterFlowModelNG.SetRowsGap(Dimension(5));
    waterFlowModelNG.SetColumnsGap(Dimension(10));
    waterFlowModelNG.SetLayoutDirection(FlexDirection::ROW);
    waterFlowModelNG.SetItemMinWidth(Dimension(10));
    waterFlowModelNG.SetItemMinHeight(Dimension(20));
    waterFlowModelNG.SetItemMaxWidth(Dimension(200));
    waterFlowModelNG.SetItemMaxHeight(Dimension(500));
    CreateWaterFlowItem(10);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. compare waterFlow properties and expected value.
     * @tc.expected: waterFlow properties equals expected value.
     */
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue(), "1fr 1fr 1fr");
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(), "1fr 1fr");
    EXPECT_EQ(layoutProperty_->GetRowsGapValue(), Dimension(5));
    EXPECT_EQ(layoutProperty_->GetColumnsGapValue(), Dimension(10));
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionStr(), "FlexDirection.Row");

    auto minSize = layoutProperty_->GetItemMinSize();
    EXPECT_EQ(minSize->Width().value_or(CalcLength(Infinity<double>(), DimensionUnit::VP)).ToString(), "10.00px");
    EXPECT_EQ(minSize->Height().value_or(CalcLength(Infinity<double>(), DimensionUnit::VP)).ToString(), "20.00px");

    auto maxSize = layoutProperty_->GetItemMaxSize();
    EXPECT_EQ(maxSize->Width().value_or(CalcLength(Infinity<double>(), DimensionUnit::VP)).ToString(), "200.00px");
    EXPECT_EQ(maxSize->Height().value_or(CalcLength(Infinity<double>(), DimensionUnit::VP)).ToString(), "500.00px");

    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: Property002
 * @tc.desc: Test empty row/col template.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property002, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetRowsTemplate("");
    waterFlowModelNG.SetColumnsTemplate("");
    CreateWaterFlowItem(10);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. compare waterFlow properties and expected value after change.
     * @tc.expected: waterFlow properties equals expected value after change.
     */
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue(), "1fr");
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(), "1fr");
}

/**
 * @tc.name: Property003
 * @tc.desc: Test GetWaterFlowDirectionStr func.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property003, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    CreateWaterFlowItem(10);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionStr(), "FlexDirection.Column");
    EXPECT_FALSE(layoutProperty_->IsReverse());
    EXPECT_EQ(layoutProperty_->GetAxis(), Axis::VERTICAL);
    layoutProperty_->UpdateWaterflowDirection(FlexDirection::ROW);
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionStr(), "FlexDirection.Row");
    layoutProperty_->UpdateWaterflowDirection(FlexDirection::COLUMN_REVERSE);
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionStr(), "FlexDirection.ColumnReverse");
    layoutProperty_->UpdateWaterflowDirection(FlexDirection::ROW_REVERSE);
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionStr(), "FlexDirection.RowReverse");
    EXPECT_TRUE(layoutProperty_->IsReverse());
    EXPECT_EQ(layoutProperty_->GetAxis(), Axis::HORIZONTAL);
}

/**
 * @tc.name: Property004
 * @tc.desc: Test property about scroller.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property004, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = waterFlowModelNG.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    waterFlowModelNG.SetScroller(scrollController, proxy);
    CreateWaterFlowItem(DEFAULT_ITEM_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_NE(pattern_->controller_, nullptr);
}

/**
 * @tc.name: Property005
 * @tc.desc: Test auto row/col template.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property005, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetRowsTemplate("auto");
    waterFlowModelNG.SetColumnsTemplate("auto");
    CreateWaterFlowItem(10);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_EQ(pattern_->GetColumns(), 1);
    EXPECT_EQ(pattern_->GetRows(), 3);
}

/**
 * @tc.name: Property006
 * @tc.desc: Test repeat col template.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property006, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("repeat(3, 2fr)");
    CreateWaterFlowItem(10);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_EQ(pattern_->GetRows(), 3);
}

/**
 * @tc.name: Property007
 * @tc.desc: Test auto-fill row/col template.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property007, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetRowsTemplate("repeat(auto-fill, 72px)");
    waterFlowModelNG.SetColumnsTemplate("repeat(auto-fill, 113px)");
    CreateWaterFlowItem(10);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(true);
}

/**
 * @tc.name: Property008
 * @tc.desc: Test some invaild properties of WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property008, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    RefPtr<ScrollControllerBase> positionController = waterFlowModelNG.CreateScrollController();
    RefPtr<ScrollProxy> scrollBarProxy = waterFlowModelNG.CreateScrollBarProxy();
    waterFlowModelNG.Create();
    waterFlowModelNG.SetRowsTemplate("1fr 1fr 1fr");
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr");
    waterFlowModelNG.SetRowsGap(Dimension(-5));
    waterFlowModelNG.SetColumnsGap(Dimension(-10));
    CreateWaterFlowItem(10);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_FALSE(false);
}

/**
 * @tc.name: WaterFlowTest001
 * @tc.desc: Fill all items to waterFlow with fixed row and column
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest001, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetRowsTemplate("1fr 1fr 1fr");
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItem(9);
    GetInstance();

    /**
     * @tc.steps: step1. When setting fixed rows and columns, check the status of child nodes in the waterFlow.
     * @tc.expected: All child nodes are active.
     */
    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout();
    for (int32_t i = 0; i < 9; ++i) {
        EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest002
 * @tc.desc: waterFlow with fixed column
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest002, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItem(9);
    GetInstance();

    /**
     * @tc.steps: step1. When setting fixed rows and columns, check the status of child nodes in the waterFlow.
     * @tc.expected: All child nodes are active.
     */
    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout();
    for (int32_t i = 0; i < 9; ++i) {
        EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest003
 * @tc.desc: waterFlow with fixed column, some waterFlowitem not show
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest003, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItem(9);
    GetInstance();

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 200.f);
    for (int32_t i = 0; i < 6; ++i) {
        EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest004
 * @tc.desc: waterFlow with fixed column, some waterFlowitem not fully show
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest004, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItem(9);
    GetInstance();

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 250.f);
    for (int32_t i = 0; i < 9; ++i) {
        EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest005
 * @tc.desc: waterFlow with fixed column, scroll to show one more line
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest005, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItem(9);
    GetInstance();

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 200.f);
    pattern_->UpdateCurrentOffset(-50.f, SCROLL_FROM_UPDATE);
    layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 200.f);
    for (int32_t i = 0; i < 9; ++i) {
        EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest006
 * @tc.desc: waterFlow with fixed column, scroll to end
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest006, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItem(9);
    GetInstance();

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 200.f);
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 200.f);
    for (int32_t i = 3; i < 9; ++i) {
        EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest007
 * @tc.desc: waterFlow with fixed column, scroll to index not fully showed at last line
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest007, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItem(9);
    GetInstance();

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 200.f);
    pattern_->UpdateStartIndex(8);
    layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 200.f);
    for (int32_t i = 0; i < 3; ++i) {
        EXPECT_FALSE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest008
 * @tc.desc: waterFlow with fixed column, scroll to index not fully showed at first line
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest008, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItem(9);
    GetInstance();

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 200.f);
    pattern_->UpdateStartIndex(1);
    layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 200.f);
    for (int32_t i = 6; i < 9; ++i) {
        EXPECT_FALSE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest009
 * @tc.desc: waterFlow with fixed column, scroll to index fully showed
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest009, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItem(9);
    GetInstance();

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 200.f);
    pattern_->UpdateStartIndex(3);
    layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 200.f);
    for (int32_t i = 0; i < 6; ++i) {
        EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest010
 * @tc.desc: waterFlow with fixed column, scroll to index out of view
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest010, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItem(10);
    GetInstance();

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 200.f);
    pattern_->UpdateStartIndex(9);
    layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 200.f);
    EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(9, false)->IsActive());
    EXPECT_FALSE(layoutWrapper->GetOrCreateChildByIndex(0, false)->IsActive());

    pattern_->UpdateStartIndex(0);
    layoutWrapper = RunMeasureAndLayout(DEVICE_WIDTH, 200.f);
    EXPECT_FALSE(layoutWrapper->GetOrCreateChildByIndex(9, false)->IsActive());
    EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(0, false)->IsActive());
}

/**
 * @tc.name: WaterFlowTest011
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest011, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr");
    CreateWaterFlowItem(5);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(DEFAULT_ITEM_HEIGHT), { DEFAULT_ITEM_HEIGHT, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-DEFAULT_ITEM_HEIGHT), { 0, 0 }));

    UpdateCurrentOffset(-DEFAULT_ITEM_HEIGHT);
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(DEFAULT_ITEM_HEIGHT * 2), { 0, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-DEFAULT_ITEM_HEIGHT * 2), { 0, 0 }));

    UpdateCurrentOffset(-DEFAULT_ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(DEFAULT_ITEM_HEIGHT), { 0, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-DEFAULT_ITEM_HEIGHT), { 0, -DEFAULT_ITEM_HEIGHT }));

    pattern_->layoutInfo_.startIndex_ = 0;
    pattern_->layoutInfo_.currentOffset_ = DEFAULT_ITEM_HEIGHT;
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(DEFAULT_ITEM_HEIGHT), { DEFAULT_ITEM_HEIGHT, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-DEFAULT_ITEM_HEIGHT * 2), { -DEFAULT_ITEM_HEIGHT, 0 }));

    pattern_->layoutInfo_.currentOffset_ = -DEFAULT_ITEM_HEIGHT * 3;
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(DEFAULT_ITEM_HEIGHT * 2), { 0, DEFAULT_ITEM_HEIGHT }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-DEFAULT_ITEM_HEIGHT), { 0, -DEFAULT_ITEM_HEIGHT }));
}

/**
 * @tc.name: PositionControllerCoverage001
 * @tc.desc: For Coverage Rate, branches that are not normally covered.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionControllerCoverage001, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    RefPtr<ScrollControllerBase> positionController = waterFlowModelNG.CreateScrollController();
    waterFlowModelNG.Create();
    waterFlowModelNG.SetScroller(positionController, nullptr);
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateWaterFlowItem(8);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Supplement ScrollPage, GetCurrentOffset branch
     */
    auto controller = pattern_->controller_;
    controller->ScrollPage(true, true);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: PositionControllerCoverage002
 * @tc.desc: Test positionController func in VERTICAL WaterFlow
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionControllerCoverage002, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    RefPtr<ScrollControllerBase> positionController = waterFlowModelNG.CreateScrollController();
    RefPtr<ScrollProxy> scrollBarProxy = waterFlowModelNG.CreateScrollBarProxy();
    waterFlowModelNG.Create();
    waterFlowModelNG.SetScroller(positionController, scrollBarProxy);
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItem(14);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Test JumpTo func.
     * @tc.expected: Verify return value.
     */
    auto controller = pattern_->controller_;
    controller->JumpTo(1, false, ScrollAlign::START, 3);
    EXPECT_EQ(pattern_->layoutInfo_.jumpIndex_, 1);

    /**
     * @tc.steps: step2. Test ScrollPage func.
     * @tc.expected: Verify currentOffset.
     */
    RunMeasureAndLayout();
    controller->ScrollPage(true, true);
    RunMeasureAndLayout();
    EXPECT_EQ(controller->GetCurrentOffset(), Offset(0, 0));

    controller->ScrollPage(false, true);
    RunMeasureAndLayout();
    EXPECT_EQ(controller->GetCurrentOffset(), Offset(0, 200));
}

/**
 * @tc.name: PositionControllerCoverage003
 * @tc.desc: Test positionController func in VERTICAL WaterFlow
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionControllerCoverage003, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    RefPtr<ScrollControllerBase> positionController = waterFlowModelNG.CreateScrollController();
    RefPtr<ScrollProxy> scrollBarProxy = waterFlowModelNG.CreateScrollBarProxy();
    waterFlowModelNG.Create();
    waterFlowModelNG.SetScroller(positionController, scrollBarProxy);
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItem(14);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Test JumpTo func.
     * @tc.expected: Verify return value.
     */
    auto controller = pattern_->controller_;
    pattern_->SetAxis(Axis::VERTICAL);
    controller->JumpTo(1, false, ScrollAlign::START, 3);
    EXPECT_EQ(pattern_->layoutInfo_.jumpIndex_, 1);

    /**
     * @tc.steps: step2. Test ScrollPage func.
     * @tc.expected: Verify currentOffset.
     */
    RunMeasureAndLayout();
    controller->ScrollPage(true, true);
    RunMeasureAndLayout();
    EXPECT_EQ(controller->GetCurrentOffset(), Offset(0, 0));
}

/**
 * @tc.name: WaterFlowPatternTest001
 * @tc.desc: Test water flow pattern func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPatternTest001, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateWaterFlowItem(14);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Run pattern func.
     * @tc.expected: The return_value is correct.
     */
    EXPECT_TRUE(pattern_->IsScrollable());
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
}

/**
 * @tc.name: WaterFlowPatternTest002
 * @tc.desc: Test water flow pattern func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPatternTest002, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    waterFlowModelNG.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
    CreateWaterFlowItem(14);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Run pattern func.
     * @tc.expected: The return_value is correct.
     */
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    pattern_->UpdateScrollBarOffset();
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, 0.f);

    pattern_->UpdateCurrentOffset(200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, -100.f);
}

/**
 * @tc.name: WaterFlowAccessibilityTest001
 * @tc.desc: Test Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowAccessibilityTest001, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateWaterFlowItem(18);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Run Accessibility func.
     * @tc.expected: The return_value is correct.
     */
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 11);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), 18);
    AceCollectionInfo info = accessibilityProperty_->GetCollectionInfo();
    EXPECT_EQ(info.rows, 3);
    EXPECT_EQ(info.columns, 4);

    /**
     * @tc.steps: step1. Scroll to Top.
     * @tc.expected: Verify return value.
     */
    UpdateCurrentOffset(DEFAULT_ITEM_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_1 = 0;
    exptectActions_1 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(), exptectActions_1);

    /**
     * @tc.steps: step2. Scroll to middle.
     * @tc.expected: Verify return value.
     */
    UpdateCurrentOffset(-DEFAULT_ITEM_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_2 = 0;
    exptectActions_2 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions_2 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(), exptectActions_2);

    /**
     * @tc.steps: step3. Scroll to bottom.
     * @tc.expected: Verify return value.
     */
    UpdateCurrentOffset(-DEFAULT_ITEM_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_3 = 0;
    exptectActions_3 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(), exptectActions_3);

    /**
     * @tc.steps: step4. UnScrollable.
     * @tc.expected: Verify return value.
     */
    WaterFlowModelNG waterFlowModelNG_2;
    waterFlowModelNG_2.Create();
    waterFlowModelNG_2.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateWaterFlowItem(1);
    GetInstance();
    RunMeasureAndLayout();
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_4 = 0;
    EXPECT_EQ(GetActions(), exptectActions_4);
}

/**
 * @tc.name: WaterFlowAccessibilityTest002
 * @tc.desc: Test Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowAccessibilityTest002, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateWaterFlowItem(14);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Run Accessibility func.
     * @tc.expected: The return_value is correct.
     */
    pattern_->SetAccessibilityAction();
    accessibilityProperty_->ActActionScrollForward();
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_FALSE(false);
}

/**
 * @tc.name: WaterFlowFooterTest001
 * @tc.desc: Test Footer func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowFooterTest001, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    auto footer = GetDefaultHeaderBuilder();
    waterFlowModelNG.SetFooter(std::move(footer));
    CreateWaterFlowItem(5);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Run footer func.
     * @tc.expected: The return_value is correct.
     */
    auto footerNode = GetChildGeometryNode(0);
    EXPECT_FLOAT_EQ(footerNode->GetFrameOffset().GetY(), 200.f);
}

/**
 * @tc.name: WaterFlowFooterTest002
 * @tc.desc: Test Footer func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowFooterTest002, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    auto footer = nullptr;
    waterFlowModelNG.SetFooter(std::move(footer));
    CreateWaterFlowItem(5);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(true);
}

/**
 * @tc.name: Callback001
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Callback001, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    bool isReachStartCalled = false;
    bool isReachEndCalled = false;
    auto reachStart = [&isReachStartCalled]() { isReachStartCalled = true; };
    auto reachEnd = [&isReachEndCalled]() { isReachEndCalled = true; };
    waterFlowModelNG.SetOnReachStart(reachStart);
    waterFlowModelNG.SetOnReachEnd(reachEnd);
    CreateWaterFlowItem(8);
    GetInstance();
    RunMeasureAndLayout();

    constexpr float scrollUpOffset = DEFAULT_ITEM_HEIGHT;
    constexpr float scrollDownOffset = -DEFAULT_ITEM_HEIGHT;

    /**
     * @tc.steps: step1. Scroll up 100px.
     * @tc.expected: Callback is called.
     */
    pattern_->UpdateCurrentOffset(scrollUpOffset, SCROLL_FROM_ANIMATION);
    RunMeasureAndLayout();
    EXPECT_TRUE(isReachStartCalled);

    /**
     * @tc.steps: step2. Scroll down 500px.
     * @tc.expected: Callback is not called.
     */
    UpdateCurrentOffset(scrollDownOffset * 5);
    EXPECT_TRUE(isReachEndCalled);
}

/**
 * @tc.name: WaterFlowLayoutInfoTest001
 * @tc.desc: Test functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowLayoutInfoTest001, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetRowsTemplate("1fr 1fr");
    waterFlowModelNG.SetRowsGap(Dimension(5));
    CreateWaterFlowItem(10);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: Test IsAllCrossReachend function
     * @tc.expected: step1. Check whether the return value is correct.
     */
    auto reached = pattern_->layoutInfo_.IsAllCrossReachend(DEFAULT_ITEM_HEIGHT);
    EXPECT_TRUE(reached);
    reached = pattern_->layoutInfo_.IsAllCrossReachend(DEVICE_HEIGHT);
    EXPECT_FALSE(reached);

    /**
     * @tc.steps: Test GetEndIndexByOffset function
     * @tc.expected: step2. Check whether the return value is correct.
     */
    auto offset = pattern_->layoutInfo_.GetEndIndexByOffset(0);
    EXPECT_EQ(0, offset);
    offset = pattern_->layoutInfo_.GetEndIndexByOffset(-100.f);
    EXPECT_EQ(1, offset);
}

/*
 * @tc.name: PositionController001
 * @tc.desc: Test property about scroller.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionController001, TestSize.Level1)
{
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = waterFlowModelNG.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    waterFlowModelNG.SetScroller(scrollController, proxy);
    waterFlowModelNG.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItem(10);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_FALSE(scrollController->IsAtEnd());

    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_TRUE(scrollController->IsAtEnd());
}

/**
 * @tc.name: WaterFlowPattern_SetFriction001
 * @tc.desc: Test SetFriction.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowSetFriction001, TestSize.Level1)
{
    constexpr double friction = -1;
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetFriction(friction);
    GetInstance();
    /**
     * @tc.expected: friction shouled be more than 0.0,if out of range,should be default value.
     */
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 0.6);
}

/**
 * @tc.name: WaterFlowPattern_SetFriction002
 * @tc.desc: Test SetFriction.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowSetFriction002, TestSize.Level1)
{
    constexpr double friction = 10;
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    waterFlowModelNG.SetFriction(friction);
    GetInstance();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 10);
}
} // namespace OHOS::Ace::NG
