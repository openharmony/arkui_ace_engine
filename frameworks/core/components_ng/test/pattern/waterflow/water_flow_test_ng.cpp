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
#include "base/memory/ace_type.h"
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
#include "core/components_ng/test/pattern/test_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float ITEM_HEIGHT = 100.f;
constexpr float WATER_FLOW_HEIGHT = 300.f;
} // namespace

class WaterFlowTestNg : public testing::Test, public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void Create(const std::function<void(WaterFlowModelNG)>& callback = nullptr);
    void CreateWithItem(const std::function<void(WaterFlowModelNG)>& callback = nullptr);
    static void CreateWaterFlowItem(int32_t number = 10);
    void UpdateCurrentOffset(float offset);
    void MouseSelect(Offset start, Offset end);
    void MouseSelectRelease();
    static std::function<void()> GetDefaultHeaderBuilder();

    AssertionResult IsEqualTotalOffset(float expectOffset);

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

void WaterFlowTestNg::Create(const std::function<void(WaterFlowModelNG)>& callback)
{
    WaterFlowModelNG model;
    RefPtr<ScrollControllerBase> positionController = model.CreateScrollController();
    RefPtr<ScrollProxy> scrollBarProxy = model.CreateScrollBarProxy();
    model.Create();
    model.SetScroller(positionController, scrollBarProxy);
    if (callback) {
        callback(model);
    }
    GetInstance();
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, WATER_FLOW_HEIGHT);
}

void WaterFlowTestNg::CreateWithItem(const std::function<void(WaterFlowModelNG)>& callback)
{
    Create([callback](WaterFlowModelNG model) {
        if (callback) {
            callback(model);
        }
        int32_t itemNumber = 10;
        CreateWaterFlowItem(itemNumber);
    });
}

void WaterFlowTestNg::CreateWaterFlowItem(int32_t number)
{
    for (int32_t i = 0; i < number; i++) {
        WaterFlowItemModelNG waterFlowItemModel;
        waterFlowItemModel.Create();
        SetHeight(Dimension(ITEM_HEIGHT));
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void WaterFlowTestNg::UpdateCurrentOffset(float offset)
{
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, WATER_FLOW_HEIGHT);
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

AssertionResult WaterFlowTestNg::IsEqualTotalOffset(float expectOffset)
{
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, WATER_FLOW_HEIGHT);
    float currentOffset = pattern_->GetTotalOffset();
    if (NearEqual(currentOffset, expectOffset)) {
        return testing::AssertionSuccess();
    }
    return AssertionFailure() <<
        "currentOffset: " << currentOffset <<
        " != " <<
        "expectOffset: " << expectOffset;
}

/**
 * @tc.name: Property001
 * @tc.desc: Test all the properties of WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property001, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr");
        model.SetRowsGap(Dimension(5));
        model.SetColumnsGap(Dimension(10));
        model.SetLayoutDirection(FlexDirection::ROW);
        model.SetItemMinWidth(Dimension(10));
        model.SetItemMinHeight(Dimension(20));
        model.SetItemMaxWidth(Dimension(200));
        model.SetItemMaxHeight(Dimension(500));
    });

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
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetRowsTemplate("");
        model.SetColumnsTemplate("");
    });

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
    CreateWithItem();
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
 * @tc.desc: Test auto row/col template.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property004, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetRowsTemplate("auto");
        model.SetColumnsTemplate("auto");
    });
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
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("repeat(3, 2fr)");
    });
    EXPECT_EQ(pattern_->GetRows(), 3);
}

/**
 * @tc.name: Property007
 * @tc.desc: Test auto-fill row/col template.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property007, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetRowsTemplate("repeat(auto-fill, 72px)");
        model.SetColumnsTemplate("repeat(auto-fill, 113px)");
    });
    EXPECT_TRUE(true);
}

/**
 * @tc.name: Property008
 * @tc.desc: Test some invaild properties of WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property008, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr");
        model.SetRowsGap(Dimension(-5));
        model.SetColumnsGap(Dimension(-10));
    });
    EXPECT_FALSE(false);
}

/**
 * @tc.name: Property009
 * @tc.desc: Test enableScrollInteraction of WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property009, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetScrollEnabled(true);
    });
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), true);
    layoutProperty_->UpdateScrollEnabled(false);
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), false);
}

/**
 * @tc.name: WaterFlowTest001
 * @tc.desc: Fill all items to waterFlow with fixed row and column
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest001, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });

    /**
     * @tc.steps: step1. When setting fixed rows and columns, check the status of child nodes in the waterFlow.
     * @tc.expected: All child nodes are active.
     */
    for (int32_t i = 0; i < 9; ++i) {
        EXPECT_TRUE(frameNode_->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest002
 * @tc.desc: waterFlow with fixed column
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest002, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });

    /**
     * @tc.steps: step1. When setting fixed rows and columns, check the status of child nodes in the waterFlow.
     * @tc.expected: All child nodes are active.
     */
    for (int32_t i = 0; i < 9; ++i) {
        EXPECT_TRUE(frameNode_->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest003
 * @tc.desc: waterFlow with fixed column, some waterFlowitem not show
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest003, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 200.f);
    for (int32_t i = 0; i < 6; ++i) {
        EXPECT_TRUE(frameNode_->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest004
 * @tc.desc: waterFlow with fixed column, some waterFlowitem not fully show
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest004, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 250.f);
    for (int32_t i = 0; i < 9; ++i) {
        EXPECT_TRUE(frameNode_->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest005
 * @tc.desc: waterFlow with fixed column, scroll to show one more line
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest005, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 200.f);
    pattern_->UpdateCurrentOffset(-50.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 200.f);
    for (int32_t i = 0; i < 9; ++i) {
        EXPECT_TRUE(frameNode_->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest006
 * @tc.desc: waterFlow with fixed column, scroll to end
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest006, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 200.f);
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 200.f);
    for (int32_t i = 3; i < 9; ++i) {
        EXPECT_TRUE(frameNode_->GetOrCreateChildByIndex(i, false)->IsActive());
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
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 200.f);
    pattern_->UpdateStartIndex(8);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 200.f);
    for (int32_t i = 0; i < 3; ++i) {
        EXPECT_FALSE(frameNode_->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest008
 * @tc.desc: waterFlow with fixed column, scroll to index not fully showed at first line
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest008, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 200.f);
    pattern_->UpdateStartIndex(1);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 200.f);
    for (int32_t i = 6; i < 9; ++i) {
        EXPECT_FALSE(frameNode_->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest009
 * @tc.desc: waterFlow with fixed column, scroll to index fully showed
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest009, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 200.f);
    pattern_->UpdateStartIndex(3);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 200.f);
    for (int32_t i = 0; i < 6; ++i) {
        EXPECT_TRUE(frameNode_->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest010
 * @tc.desc: waterFlow with fixed column, scroll to index out of view
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest010, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 200.f);
    pattern_->UpdateStartIndex(9);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 200.f);
    EXPECT_TRUE(frameNode_->GetOrCreateChildByIndex(9, false)->IsActive());
    EXPECT_FALSE(frameNode_->GetOrCreateChildByIndex(0, false)->IsActive());

    pattern_->UpdateStartIndex(0);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, 200.f);
    EXPECT_FALSE(frameNode_->GetOrCreateChildByIndex(9, false)->IsActive());
    EXPECT_TRUE(frameNode_->GetOrCreateChildByIndex(0, false)->IsActive());
}

/**
 * @tc.name: WaterFlowTest011
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest011, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr");
        CreateWaterFlowItem(5);
    });

    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(ITEM_HEIGHT), { ITEM_HEIGHT, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-ITEM_HEIGHT), { 0, 0 }));

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2), { 0, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2), { 0, 0 }));

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(ITEM_HEIGHT), { 0, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-ITEM_HEIGHT), { 0, -ITEM_HEIGHT }));

    pattern_->layoutInfo_.startIndex_ = 0;
    pattern_->layoutInfo_.currentOffset_ = ITEM_HEIGHT;
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(ITEM_HEIGHT), { ITEM_HEIGHT, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2), { -ITEM_HEIGHT, 0 }));

    pattern_->layoutInfo_.currentOffset_ = -ITEM_HEIGHT * 3;
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2), { 0, ITEM_HEIGHT }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-ITEM_HEIGHT), { 0, -ITEM_HEIGHT }));
}

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) { model.SetColumnsTemplate("1fr 1fr"); });

    /**
     * @tc.steps: step1. When itemStart_ and scroll up
     * @tc.expected: can not scroll.
     */
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step2. Scroll down
     * @tc.expected: can scroll.
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));

    /**
     * @tc.steps: step3. Continue scroll down
     * @tc.expected: can scroll and IsAtEnd.
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));
    EXPECT_TRUE(pattern_->controller_->IsAtEnd());

    /**
     * @tc.steps: step4. Continue scroll down
     * @tc.expected: can not scroll.
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));

    /**
     * @tc.steps: step5. When offsetEnd_ and scroll up
     * @tc.expected: can scroll.
     */
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
}

/**
 * @tc.name: PositionController001
 * @tc.desc: Test PositionController
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionController001, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) { model.SetColumnsTemplate("1fr 1fr"); });
    auto controller = pattern_->controller_;

    /**
     * @tc.steps: step1. Test ScrollPage and IsAtEnd
     */
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), ITEM_HEIGHT * 2);
    EXPECT_TRUE(controller->IsAtEnd());
    controller->ScrollPage(true, false);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), 0);
    EXPECT_FALSE(controller->IsAtEnd());

    /**
     * @tc.steps: step2. Test JumpTo func.
     */
    controller->JumpTo(2, false, ScrollAlign::START, 0);
    EXPECT_EQ(pattern_->layoutInfo_.jumpIndex_, 2);
    controller->JumpTo(0, false, ScrollAlign::START, 0);
    EXPECT_EQ(pattern_->layoutInfo_.jumpIndex_, 0);
}

/**
 * @tc.name: WaterFlowPatternTest001
 * @tc.desc: Test water flow pattern func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPatternTest001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateWaterFlowItem(14);
    });

    /**
     * @tc.steps: step1. Run pattern func.
     * @tc.expected: The return_value is correct.
     */
    EXPECT_TRUE(pattern_->IsScrollable());
    EXPECT_TRUE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
}

/**
 * @tc.name: WaterFlowPatternTest002
 * @tc.desc: Test water flow pattern func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPatternTest002, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
        CreateWaterFlowItem(14);
    });

    /**
     * @tc.steps: step1. Run pattern func.
     * @tc.expected: The return_value is correct.
     */
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, WATER_FLOW_HEIGHT);
    pattern_->UpdateScrollBarOffset();
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, 0.f);

    pattern_->UpdateCurrentOffset(200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_, DEVICE_WIDTH, WATER_FLOW_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, -100.f);
}

/**
 * @tc.name: WaterFlowAccessibilityTest001
 * @tc.desc: Test Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowAccessibilityTest001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateWaterFlowItem(18);
    });

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
     * @tc.steps: step2. Scroll to Top.
     * @tc.expected: Verify return value.
     */
    UpdateCurrentOffset(ITEM_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_1 = 0;
    exptectActions_1 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_1);

    /**
     * @tc.steps: step3. Scroll to middle.
     * @tc.expected: Verify return value.
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_2 = 0;
    exptectActions_2 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions_2 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_2);

    /**
     * @tc.steps: step4. Scroll to bottom.
     * @tc.expected: Verify return value.
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_3 = 0;
    exptectActions_3 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_3);

    /**
     * @tc.steps: step5. UnScrollable.
     * @tc.expected: Verify return value.
     */
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateWaterFlowItem(1);
    });
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_4 = 0;
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_4);
}

/**
 * @tc.name: WaterFlowAccessibilityTest002
 * @tc.desc: Test Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowAccessibilityTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Run Accessibility func.
     * @tc.expected: Will trigger ScrollPage func
     */
    CreateWithItem([](WaterFlowModelNG model) { model.SetColumnsTemplate("1fr 1fr"); });
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(IsEqualTotalOffset(0));
}

/**
 * @tc.name: WaterFlowFooterTest001
 * @tc.desc: Test Footer func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowFooterTest001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        auto footer = GetDefaultHeaderBuilder();
        model.SetFooter(std::move(footer));
        CreateWaterFlowItem(5);
        ViewStackProcessor::GetInstance()->Pop();
    });

    /**
     * @tc.steps: step1. Run footer func.
     * @tc.expected: The return_value is correct.
     */
    auto footerRect = GetChildRect(frameNode_, 0);
    EXPECT_FLOAT_EQ(footerRect.GetY(), 200.f);
}

/**
 * @tc.name: WaterFlowFooterTest002
 * @tc.desc: Test Footer func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowFooterTest002, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        auto footer = nullptr;
        model.SetFooter(std::move(footer));
        CreateWaterFlowItem(5);
        ViewStackProcessor::GetInstance()->Pop();
    });
    EXPECT_TRUE(true);
}

/**
 * @tc.name: Callback001
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Callback001, TestSize.Level1)
{
    bool isReachStartCalled = false;
    bool isReachEndCalled = false;
    auto reachStart = [&isReachStartCalled]() { isReachStartCalled = true; };
    auto reachEnd = [&isReachEndCalled]() { isReachEndCalled = true; };
    Create([reachStart, reachEnd](WaterFlowModelNG model) {
        model.SetOnReachStart(reachStart);
        model.SetOnReachEnd(reachEnd);
        CreateWaterFlowItem(8);
    });

    /**
     * @tc.steps: step1. init will trigger once
     */
    EXPECT_TRUE(isReachStartCalled);

    /**
     * @tc.steps: step2. Scroll down to end
     * @tc.expected: Trigger reachend
     */
    UpdateCurrentOffset(-ITEM_HEIGHT * 5);
    EXPECT_TRUE(isReachEndCalled);

    /**
     * @tc.steps: step3. Scroll up to start
     * @tc.expected: Trigger reachstart
     */
    isReachStartCalled = false;
    UpdateCurrentOffset(ITEM_HEIGHT * 5);
    EXPECT_TRUE(isReachStartCalled);
}

/**
 * @tc.name: WaterFlowLayoutInfoTest001
 * @tc.desc: Test functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowLayoutInfoTest001, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetRowsTemplate("1fr 1fr");
        model.SetRowsGap(Dimension(5));
    });

    /**
     * @tc.steps: Test IsAllCrossReachend function
     * @tc.expected: step1. Check whether the return value is correct.
     */
    auto reached = pattern_->layoutInfo_.IsAllCrossReachend(ITEM_HEIGHT);
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

/**
 * @tc.name: WaterFlowPattern_SetFriction001
 * @tc.desc: Test SetFriction. friction shouled be more than 0.0,if out of range,should be default value.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowSetFriction001, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) { model.SetFriction(0); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
    CreateWithItem([](WaterFlowModelNG model) { model.SetFriction(-1); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
    CreateWithItem([](WaterFlowModelNG model) { model.SetFriction(1); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 1);
}

/**
 * @tc.name: WaterFlowPattern_distributed001
 * @tc.desc: Test the distributed capability of WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPattern_distributed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Waterflow node
     */
    WaterFlowModelNG waterFlowModelNG;
    waterFlowModelNG.Create();
    GetInstance();

    // need dpi to be 1
    /**
     * @tc.steps: step2. get pattern .
     * @tc.expected: function ProvideRestoreInfo is called.
     */
    pattern_->layoutInfo_.startIndex_ = 1;
    pattern_->layoutInfo_.storedOffset_ = 1.0f;
    std::string ret = pattern_->ProvideRestoreInfo();

    /**
     * @tc.steps: step3. function OnRestoreInfo is called.
     * @tc.expected: Passing JSON format.
     */
    // std::string restoreInfo = R"({"beginIndex":1,"offset":1.1})";
    pattern_->OnRestoreInfo(ret);
    EXPECT_EQ(pattern_->layoutInfo_.jumpIndex_, 1);
    EXPECT_DOUBLE_EQ(pattern_->layoutInfo_.restoreOffset_, 1.0f);
}

/**
 * @tc.name: WaterFlowPattern_CreateNodePaintMethod001
 * @tc.desc: Test CreateNodePaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPattern_CreateNodePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Waterflow node
     */
    CreateWithItem([](WaterFlowModelNG model) {});

    /**
     * @tc.steps: step1. not set contentModifier_
     */
    RefPtr<NodePaintMethod> ret = pattern_->CreateNodePaintMethod();
    EXPECT_NE(ret, nullptr);

    /**
     * @tc.steps: step1. set contentModifier_
     */
    std::string res = "";
    pattern_->OnRestoreInfo(res);
    ret = pattern_->CreateNodePaintMethod();
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: WaterFlowPositionController_ScrollPage001
 * @tc.desc: Test ScrollPage.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPositionController_ScrollPage001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Waterflow node
     */
    CreateWithItem([](WaterFlowModelNG model) { model.SetColumnsTemplate("1fr 1fr");});
    auto controller = pattern_->controller_;
    
    /**
     * @tc.steps: step2. test function.
     * @tc.expected: function ScrollPage is called.
     */
    pattern_->SetAxis(Axis::VERTICAL);
    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), ITEM_HEIGHT * 2);
    EXPECT_TRUE(controller->IsAtEnd());

    pattern_->SetAxis(Axis::NONE);
    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), 0);
    EXPECT_TRUE(controller->IsAtEnd());
}

/**
 * @tc.name: WaterFlowContentModifier_onDraw001
 * @tc.desc: Test onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowContentModifier_onDraw001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Waterflow node
     */
    CreateWithItem([](WaterFlowModelNG model) {});
    pattern_->CreateNodePaintMethod();
    auto contentModifier = pattern_->contentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    RSCanvas canvas;
    DrawingContext context = { canvas, 1, 1 };
    /**
     * @tc.steps: step2. test function.
     * @tc.expected: function onDraw is called.
     */
    contentModifier->SetClip(true);
    contentModifier->onDraw(context);
    EXPECT_EQ(contentModifier->clip_->Get(), true);

    contentModifier->SetClip(false);
    contentModifier->onDraw(context);
    EXPECT_EQ(contentModifier->clip_->Get(), false);
}

/**
 * @tc.name: WaterFlowPattern_OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPattern_OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Waterflow node
     */
    CreateWithItem([](WaterFlowModelNG model) {});
    pattern_->SetPositionController(nullptr);
    pattern_->InitScrollableEvent();
    EXPECT_NE(pattern_->scrollableEvent_, nullptr);
    pattern_->OnModifyDone();
   
    /**
     * @tc.steps: step2. test function.
     * @tc.expected: function OnDirtyLayoutWrapperSwap is called.
     */
    auto geometryNode = frameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.skipLayout = true;
    config.skipMeasure = false;
    EXPECT_EQ(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config), false);

    config.skipLayout = false;
    config.skipMeasure = true;
    EXPECT_EQ(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config), false);
}

/**
 * @tc.name: Property010
 * @tc.desc: Test ToJsonValue of WaterFlowLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Waterflow node
     */
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr");
        model.SetRowsGap(Dimension(5));
        model.SetColumnsGap(Dimension(10));
        model.SetLayoutDirection(FlexDirection::ROW);
        model.SetItemMinWidth(Dimension(10));
        model.SetItemMinHeight(Dimension(20));
        model.SetItemMaxWidth(Dimension(200));
        model.SetItemMaxHeight(Dimension(500));
        });

     /**
     * @tc.steps: step2. test function.
     * @tc.expected: function ToJsonValue is called.
     */
    EXPECT_NE(layoutProperty_->Clone(), nullptr);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_NE(json, nullptr);

    layoutProperty_->Reset();
    EXPECT_NE(layoutProperty_->Clone(), nullptr);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: WaterFlowLayoutInfoTest002
 * @tc.desc: Test functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowLayoutInfoTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Waterflow node
     */
    CreateWithItem([](WaterFlowModelNG model) {});

    /**
     * @tc.steps: Test GetStartMainPos and GetMainHeight
     * @tc.expected: step2. Check whether the return value is correct.
     */
    int32_t crossIndex = pattern_->layoutInfo_.waterFlowItems_.rbegin()->first;
    int32_t itemIndex = pattern_->layoutInfo_.waterFlowItems_.rbegin()->second.rbegin()->first;
    EXPECT_EQ(pattern_->layoutInfo_.GetStartMainPos(crossIndex + 1, itemIndex), 0.0f);
    EXPECT_EQ(pattern_->layoutInfo_.GetMainHeight(crossIndex + 1, itemIndex), 0.0f);

    EXPECT_EQ(pattern_->layoutInfo_.GetStartMainPos(crossIndex, itemIndex + 1), 0.0f);
    EXPECT_EQ(pattern_->layoutInfo_.GetMainHeight(crossIndex, itemIndex + 1), 0.0f);
}

/**
 * @tc.name: WaterFlowLayoutInfoTest003
 * @tc.desc: Test functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowLayoutInfoTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Waterflow node
     */
    CreateWithItem([](WaterFlowModelNG model) {});

    /**
     * @tc.steps: Test GetMainCount function
     * @tc.expected: step2. Check whether the size is correct.
     */
    std::size_t waterFlowItemsSize = pattern_->layoutInfo_.waterFlowItems_.size();
    int32_t mainCount = pattern_->layoutInfo_.GetMainCount();

    int32_t index = pattern_->layoutInfo_.waterFlowItems_.rbegin()->first;
    pattern_->layoutInfo_.waterFlowItems_[index + 1] = std::map<int32_t, std::pair<float, float>>();
    EXPECT_EQ(pattern_->layoutInfo_.waterFlowItems_.size(), waterFlowItemsSize + 1);
    EXPECT_EQ(pattern_->layoutInfo_.GetMainCount(), mainCount);

    auto lastItem = pattern_->layoutInfo_.waterFlowItems_.begin()->second.rbegin();
    float mainSize = lastItem->second.first + lastItem->second.second - 1.0f;
    EXPECT_FALSE(pattern_->layoutInfo_.IsAllCrossReachend(mainSize));

    pattern_->layoutInfo_.ClearCacheAfterIndex(index + 1);
    EXPECT_EQ(pattern_->layoutInfo_.waterFlowItems_.size(), waterFlowItemsSize + 1);
}

/**
 * @tc.name: WaterFlowLayoutInfoTest004
 * @tc.desc: Test Reset functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowLayoutInfoTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Waterflow node
     */
    CreateWithItem([](WaterFlowModelNG model) {});

    /**
     * @tc.steps: Test Reset function
     * @tc.expected: step2. Check whether the endIndex_ is correct.
     */
    int32_t resetFrom = pattern_->layoutInfo_.endIndex_;
    pattern_->layoutInfo_.Reset(resetFrom);
    EXPECT_EQ(pattern_->layoutInfo_.endIndex_, resetFrom);

    pattern_->layoutInfo_.Reset(resetFrom - 1);
    EXPECT_EQ(pattern_->layoutInfo_.endIndex_, 0);
}

/**
 * @tc.name: WaterFlowLayoutInfoTest005
 * @tc.desc: Test functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowLayoutInfoTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Waterflow node
     */
    CreateWithItem([](WaterFlowModelNG model) {});

    /**
     * @tc.steps: Test GetMaxMainHeight function
     * @tc.expected: step2. Check whether the return value is correct.
     */
    float maxMainHeight = pattern_->layoutInfo_.GetMaxMainHeight();
    int32_t crossIndex = pattern_->layoutInfo_.waterFlowItems_.rbegin()->first;
    pattern_->layoutInfo_.waterFlowItems_[crossIndex + 1][0] = std::pair<float, float>(1.0f, maxMainHeight);
    EXPECT_EQ(pattern_->layoutInfo_.GetMaxMainHeight(), maxMainHeight + 1.0f);

     /**
     * @tc.steps: Test GetCrossIndexForNextItem function
     * @tc.expected: step3. Check whether the return value is correct.
     */
    pattern_->layoutInfo_.waterFlowItems_[crossIndex + 1][1] = std::pair<float, float>(0.0f, 0.0f);
    FlowItemIndex position = pattern_->layoutInfo_.GetCrossIndexForNextItem();
    EXPECT_EQ(position.crossIndex, crossIndex + 1);
    EXPECT_EQ(position.lastItemIndex, 1);
}
} // namespace OHOS::Ace::NG
