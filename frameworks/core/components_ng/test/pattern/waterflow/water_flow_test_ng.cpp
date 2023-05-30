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
const SizeF CONTAINER_SIZE(DEVICE_WIDTH, DEVICE_HEIGHT);
constexpr float DEFAULT_ROOT_WIDTH = 720.f;
constexpr float DEFAULT_ROOT_HEIGHT = 1136.f;
constexpr float DEFAULT_ITEM_HEIGHT = 100.f;
constexpr float DEFAULT_ITEM_WIDTH = 100.f;
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
    void CreateWaterFlowItemWithButton(int32_t number);
    void CreateHorizontalWaterFlowItem(int32_t number);
    void CreateHorizontalWaterFlowItemWithButton(int32_t number);
    RefPtr<LayoutWrapper> RunMeasureAndLayout(float width = DEVICE_WIDTH, float height = DEFAULT_WATER_FLOW_HEIGHT);
    void UpdateLayoutWrapper(RefPtr<LayoutWrapper> layoutWrapper, float width, float height);
    RefPtr<FrameNode> GetItemFrameNode(int32_t index);
    RefPtr<WaterFlowItemPattern> GetItemPattern(int32_t index);
    RefPtr<FocusHub> GetItemFocusHub(int32_t index);
    void UpdateCurrentOffset(float offset);
    void MouseSelect(Offset start, Offset end);
    void MouseSelectRelease();

    testing::AssertionResult IsEqualNextFocusNode(int32_t currentIndex, std::map<FocusStep, int32_t> next);

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

void WaterFlowTestNg::CreateHorizontalWaterFlowItem(int32_t number)
{
    for (int32_t i = 0; i < number; i++) {
        WaterFlowItemModelNG waterFlowItemModel;
        waterFlowItemModel.Create();
        SetWidth(Dimension(DEFAULT_ITEM_WIDTH));
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void WaterFlowTestNg::CreateWaterFlowItemWithButton(int32_t number)
{
    for (int32_t i = 0; i < number; i++) {
        WaterFlowItemModelNG waterFlowItemModel;
        waterFlowItemModel.Create();
        SetHeight(Dimension(DEFAULT_ITEM_HEIGHT));
        {
            ButtonModelNG buttonModelNG;
            buttonModelNG.CreateWithLabel("label");
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void WaterFlowTestNg::CreateHorizontalWaterFlowItemWithButton(int32_t number)
{
    for (int32_t i = 0; i < number; i++) {
        WaterFlowItemModelNG waterFlowItemModel;
        waterFlowItemModel.Create();
        SetWidth(Dimension(DEFAULT_ITEM_WIDTH));
        {
            ButtonModelNG buttonModelNG;
            buttonModelNG.CreateWithLabel("label");
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
}

RefPtr<LayoutWrapper> WaterFlowTestNg::RunMeasureAndLayout(float width, float height)
{
    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
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
    layoutProperty_->UpdateWaterflowDirection(FlexDirection::ROW);
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionStr(), "FlexDirection.Row");
    layoutProperty_->UpdateWaterflowDirection(FlexDirection::COLUMN_REVERSE);
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionStr(), "FlexDirection.ColumnReverse");
    layoutProperty_->UpdateWaterflowDirection(FlexDirection::ROW_REVERSE);
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionStr(), "FlexDirection.RowReverse");
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

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 200.f);
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

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 250.f);
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

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 200.f);
    pattern_->UpdateCurrentOffset(-50.f, SCROLL_FROM_UPDATE);
    layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 200.f);
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

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 200.f);
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 200.f);
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

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 200.f);
    pattern_->UpdateStartIndex(8);
    layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 200.f);
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

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 200.f);
    pattern_->UpdateStartIndex(1);
    layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 200.f);
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

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 200.f);
    pattern_->UpdateStartIndex(3);
    layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 200.f);
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

    RefPtr<LayoutWrapper> layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 200.f);
    pattern_->UpdateStartIndex(9);
    layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 200.f);
    EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(9, false)->IsActive());
    EXPECT_FALSE(layoutWrapper->GetOrCreateChildByIndex(0, false)->IsActive());

    pattern_->UpdateStartIndex(0);
    layoutWrapper = RunMeasureAndLayout(DEFAULT_ROOT_WIDTH, 200.f);
    EXPECT_FALSE(layoutWrapper->GetOrCreateChildByIndex(9, false)->IsActive());
    EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(0, false)->IsActive());
}
} // namespace OHOS::Ace::NG