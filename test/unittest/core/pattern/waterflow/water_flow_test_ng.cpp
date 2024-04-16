/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "water_flow_item_maps.h"

#include "base/utils/system_properties.h"
#include "core/components/scroll/scroll_controller_base.h"

#define protected public
#define private public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "test/unittest/core/pattern/waterflow/water_flow_test_ng.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/pattern/waterflow/water_flow_accessibility_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_event_hub.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_node.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_algorithm.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float WATERFLOW_WIDTH = 480.f;
constexpr float WATERFLOW_HEIGHT = 800.f;
constexpr int32_t TOTAL_LINE_NUMBER = 10;
constexpr int32_t VIEW_LINE_NUMBER = 8;
constexpr float ITEM_HEIGHT = WATERFLOW_HEIGHT / VIEW_LINE_NUMBER;
constexpr float BIG_ITEM_HEIGHT = ITEM_HEIGHT * 2;
} // namespace

void WaterFlowTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

#ifndef TEST_SEGMENTED_WATER_FLOW
    g_segmentedWaterflow = false;
#endif
}

void WaterFlowTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void WaterFlowTestNg::SetUp() {}

void WaterFlowTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void WaterFlowTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<WaterFlowPattern>();
    eventHub_ = frameNode_->GetEventHub<WaterFlowEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<WaterFlowLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<WaterFlowAccessibilityProperty>();
}

void WaterFlowTestNg::Create(const std::function<void(WaterFlowModelNG)>& callback, bool flushLayout)
{
    WaterFlowModelNG model;
    RefPtr<ScrollControllerBase> positionController = model.CreateScrollController();
    RefPtr<ScrollProxy> scrollBarProxy = model.CreateScrollBarProxy();
    model.Create();
    ViewAbstract::SetWidth(CalcLength(WATERFLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(WATERFLOW_HEIGHT));
    model.SetScroller(positionController, scrollBarProxy);
    if (callback) {
        callback(model);
    }
    GetInstance();
    if (flushLayout) {
        FlushLayoutTask(frameNode_);
    }
}

void WaterFlowTestNg::CreateWithItem(const std::function<void(WaterFlowModelNG)>& callback)
{
    Create([callback](WaterFlowModelNG model) {
        if (callback) {
            callback(model);
        }
        CreateItem(TOTAL_LINE_NUMBER);
    });
}

void WaterFlowTestNg::CreateItem(int32_t number)
{
    for (int32_t i = 0; i < number; i++) {
        WaterFlowItemModelNG waterFlowItemModel;
        waterFlowItemModel.Create();
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        // set irregular height
        int32_t two = 2;
        if (i % two == 0) {
            ViewAbstract::SetHeight(CalcLength(Dimension(ITEM_HEIGHT)));
        } else {
            ViewAbstract::SetHeight(CalcLength(Dimension(BIG_ITEM_HEIGHT)));
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void WaterFlowTestNg::AddItems(int32_t number)
{
    for (int i = 0; i < number; ++i) {
        auto child = WaterFlowItemNode::GetOrCreateFlowItem(
            V2::FLOW_ITEM_ETS_TAG, -1, []() { return AceType::MakeRefPtr<WaterFlowItemPattern>(); });
        if (i & 1) {
            child->GetLayoutProperty()->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(FILL_LENGTH), CalcLength(Dimension(BIG_ITEM_HEIGHT))));
        } else {
            child->GetLayoutProperty()->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(FILL_LENGTH), CalcLength(Dimension(ITEM_HEIGHT))));
        }
        frameNode_->AddChild(child);
    }
}

void WaterFlowTestNg::CreateItemWithHeight(float height)
{
    WaterFlowItemModelNG waterFlowItemModel;
    waterFlowItemModel.Create();
    ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    ViewAbstract::SetHeight(CalcLength(Dimension(height)));
    ViewStackProcessor::GetInstance()->Pop();
}

void WaterFlowTestNg::UpdateCurrentOffset(float offset, int32_t source)
{
    pattern_->UpdateCurrentOffset(offset, source);
    FlushLayoutTask(frameNode_);
}

std::function<void()> WaterFlowTestNg::GetDefaultHeaderBuilder()
{
    return []() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        ViewAbstract::SetWidth(CalcLength(Dimension(1.0, DimensionUnit::PERCENT)));
        ViewAbstract::SetHeight(CalcLength(Dimension(50.f)));
    };
}

AssertionResult WaterFlowTestNg::IsEqualTotalOffset(float expectOffset)
{
    FlushLayoutTask(frameNode_);
    float currentOffset = pattern_->GetTotalOffset();
    if (NearEqual(currentOffset, expectOffset)) {
        return testing::AssertionSuccess();
    }
    return AssertionFailure() << "currentOffset: " << currentOffset << " != "
                              << "expectOffset: " << expectOffset;
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
    EXPECT_EQ(pattern_->GetRows(), 6);
}

/**
 * @tc.name: Property006
 * @tc.desc: Test repeat col template.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property006, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) { model.SetColumnsTemplate("repeat(3, 2fr)"); });
    EXPECT_EQ(pattern_->GetRows(), VIEW_LINE_NUMBER / 2);
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
    CreateWithItem([](WaterFlowModelNG model) { model.SetScrollEnabled(true); });
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), true);
    layoutProperty_->UpdateScrollEnabled(false);
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), false);
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
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_NE(json, nullptr);

    layoutProperty_->Reset();
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: Property011
 * @tc.desc: Test ToJsonValue of WaterFlowLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create WaterFlow
     */
    WaterFlowModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(WATERFLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(WATERFLOW_HEIGHT));
    GetInstance();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. set valid value.
     * @tc.expected: the value of layoutProperty_ is right.
     */
    const std::string value = "1fr 1fr";
    const Dimension gaps = Dimension(10.f);
    model.SetColumnsTemplate(AceType::RawPtr(frameNode_), value);
    model.SetRowsTemplate(AceType::RawPtr(frameNode_), value);
    model.SetColumnsGap(AceType::RawPtr(frameNode_), gaps);
    model.SetRowsGap(AceType::RawPtr(frameNode_), gaps);

    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue("1fr"), value);
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue("1fr"), value);
    EXPECT_EQ(layoutProperty_->GetColumnsGapValue(Dimension(0.f)), gaps);
    EXPECT_EQ(layoutProperty_->GetRowsGapValue(Dimension(0.f)), gaps);

    /**
     * @tc.steps: step3. set invalid value.
     * @tc.expected: the value of layoutProperty_ is right.
     */
    model.SetColumnsTemplate(AceType::RawPtr(frameNode_), "");
    model.SetRowsTemplate(AceType::RawPtr(frameNode_), "");
    model.SetColumnsGap(AceType::RawPtr(frameNode_), -gaps);
    model.SetRowsGap(AceType::RawPtr(frameNode_), -gaps);

    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue("1fr"), "1fr");
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue("1fr"), "1fr");
    EXPECT_EQ(layoutProperty_->GetColumnsGapValue(Dimension(0.f)), gaps);
    EXPECT_EQ(layoutProperty_->GetRowsGapValue(Dimension(0.f)), gaps);
}

/**
 * @tc.name: Property012
 * @tc.desc: all the properties of WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create WaterFlow
     */
    ViewStackProcessor::GetInstance()->SetVisualState(VisualState::FOCUSED);
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetItemMinWidth(Dimension(10));
        model.SetItemMinHeight(Dimension(10));
        model.SetItemMaxWidth(Dimension(300));
        model.SetItemMaxHeight(Dimension(300));
    });

    /**
     * @tc.steps: step2. set value when IsCurrentVisualStateProcess is false.
     * @tc.expected: the value not set.
     */
    EXPECT_EQ(layoutProperty_->itemLayoutConstraint_, nullptr);
    ViewStackProcessor::GetInstance()->ClearVisualState();
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
        EXPECT_TRUE(GetChildFrameNode(frameNode_, i)->IsActive());
    }
}

/**
 * @tc.name: WaterFlowTest002
 * @tc.desc: waterFlow with fixed column
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest002, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) { model.SetColumnsTemplate("1fr 1fr 1fr"); });

    /**
     * @tc.steps: step1. When setting fixed rows and columns, check the status of child nodes in the waterFlow.
     * @tc.expected: All child nodes are active.
     */
    for (int32_t i = 0; i < 9; ++i) {
        EXPECT_TRUE(GetChildFrameNode(frameNode_, i)->IsActive());
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
        ViewAbstract::SetWidth(CalcLength(WATERFLOW_WIDTH));
        ViewAbstract::SetHeight(CalcLength(200.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 3)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 4)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 5)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 6)->IsActive());
}

/**
 * @tc.name: WaterFlowTest004
 * @tc.desc: waterFlow with fixed column, some waterFlowitem not fully show
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest004, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(WATERFLOW_WIDTH));
        ViewAbstract::SetHeight(CalcLength(250.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 5)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 6)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 7)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 8)->IsActive());
}

/**
 * @tc.name: WaterFlowTest005
 * @tc.desc: waterFlow with fixed column, scroll to show one more line
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest005, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(WATERFLOW_WIDTH));
        ViewAbstract::SetHeight(CalcLength(200.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    pattern_->UpdateCurrentOffset(-50.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 5)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 6)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 7)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 8)->IsActive());
}

/**
 * @tc.name: WaterFlowTest006
 * @tc.desc: waterFlow with fixed column, scroll to end
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest006, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(WATERFLOW_WIDTH));
        ViewAbstract::SetHeight(CalcLength(200.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 6)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 7)->IsActive());
}

/**
 * @tc.name: WaterFlowTest007
 * @tc.desc: waterFlow with fixed column, scroll to index not fully showed at last line
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest007, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(WATERFLOW_WIDTH));
        ViewAbstract::SetHeight(CalcLength(200.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    pattern_->UpdateStartIndex(8);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 3)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 4)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 5)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 6)->IsActive());
}

/**
 * @tc.name: WaterFlowTest008
 * @tc.desc: waterFlow with fixed column, scroll to index not fully showed at first line
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest008, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(WATERFLOW_WIDTH));
        ViewAbstract::SetHeight(CalcLength(200.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    pattern_->UpdateStartIndex(1);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 3)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 4)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 5)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 6)->IsActive());
}

/**
 * @tc.name: WaterFlowTest009
 * @tc.desc: waterFlow with fixed column, scroll to index fully showed
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest009, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(WATERFLOW_WIDTH));
        ViewAbstract::SetHeight(CalcLength(200.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    pattern_->UpdateStartIndex(3);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 6)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 7)->IsActive());
}

/**
 * @tc.name: WaterFlowTest010
 * @tc.desc: waterFlow with fixed column, scroll to index out of view
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest010, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(WATERFLOW_WIDTH));
        ViewAbstract::SetHeight(CalcLength(200.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    pattern_->UpdateStartIndex(9);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 9)->IsActive());

    pattern_->UpdateStartIndex(0);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 9)->IsActive());
}

/**
 * @tc.name: WaterFlowTest011
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest011, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) { model.SetColumnsTemplate("1fr"); });

    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(ITEM_HEIGHT), { ITEM_HEIGHT, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(-ITEM_HEIGHT), { 0, 0 }));

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2), { 0, 0 }));

    UpdateCurrentOffset(-WATERFLOW_HEIGHT);
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(ITEM_HEIGHT), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(-ITEM_HEIGHT), { 0, -ITEM_HEIGHT }));

    pattern_->layoutInfo_.startIndex_ = 0;
    pattern_->layoutInfo_.currentOffset_ = ITEM_HEIGHT;
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(ITEM_HEIGHT), { ITEM_HEIGHT, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2), { -ITEM_HEIGHT, 0 }));

    pattern_->layoutInfo_.currentOffset_ = -ITEM_HEIGHT * 3;
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(-ITEM_HEIGHT), { 0, 0 }));
}

/**
 * @tc.name: WaterFlowTest012
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow that is less than one screen
     * @tc.expected: itemStart_ = true  itemEnd_ = true.
     */
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateItem(TOTAL_LINE_NUMBER);
    });
    EXPECT_TRUE(pattern_->layoutInfo_.itemStart_);
    EXPECT_TRUE(pattern_->layoutInfo_.itemEnd_);
    EXPECT_TRUE(pattern_->layoutInfo_.offsetEnd_);
    EXPECT_EQ(pattern_->layoutInfo_.maxHeight_, 500);
    EXPECT_EQ(pattern_->layoutInfo_.lastMainSize_, 800);

    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(ITEM_HEIGHT), { 100, 100 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(3 * ITEM_HEIGHT), { 300, 300 }));
}

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });

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
    UpdateCurrentOffset(-WATERFLOW_HEIGHT);
    EXPECT_TRUE(IsEqualTotalOffset(WATERFLOW_HEIGHT));
    EXPECT_TRUE(pattern_->positionController_->IsAtEnd());

    /**
     * @tc.steps: step4. Continue scroll down
     * @tc.expected: can not scroll.
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualTotalOffset(WATERFLOW_HEIGHT));

    /**
     * @tc.steps: step5. When offsetEnd_ and scroll up
     * @tc.expected: can scroll.
     */
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualTotalOffset(WATERFLOW_HEIGHT - ITEM_HEIGHT));
}

/**
 * @tc.name: UpdateCurrentOffset002
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, UpdateCurrentOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow
     * @tc.expected: startIndex_ = 0 endIndex_ = 10.
     */
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.endIndex_, 10);
    EXPECT_TRUE(pattern_->layoutInfo_.itemStart_);
    EXPECT_FALSE(pattern_->layoutInfo_.itemEnd_);
    EXPECT_FALSE(pattern_->layoutInfo_.offsetEnd_);

    /**
     * @tc.steps: step2. Scroll down
     * @tc.expected: startIndex_ = 1 endIndex_ = 13.
     */
    UpdateCurrentOffset(-2 * ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_.endIndex_, 13);
    EXPECT_FALSE(pattern_->layoutInfo_.itemStart_);
    EXPECT_FALSE(pattern_->layoutInfo_.itemEnd_);
    EXPECT_FALSE(pattern_->layoutInfo_.offsetEnd_);

    /**
     * @tc.steps: step3. scroll down
     * @tc.expected: startIndex_ = 11 endIndex_ = 19.
     */
    UpdateCurrentOffset(-10000.f);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 11);
    EXPECT_EQ(pattern_->layoutInfo_.endIndex_, 19);
    EXPECT_FALSE(pattern_->layoutInfo_.itemStart_);
    EXPECT_TRUE(pattern_->layoutInfo_.itemEnd_);
    EXPECT_TRUE(pattern_->layoutInfo_.offsetEnd_);

    /**
     * @tc.steps: step4. scroll up
     * @tc.expected: startIndex_ = 7 endIndex_ = 19.
     */
    UpdateCurrentOffset(2 * ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 7);
    EXPECT_EQ(pattern_->layoutInfo_.endIndex_, 19);
    EXPECT_FALSE(pattern_->layoutInfo_.itemStart_);
    EXPECT_TRUE(pattern_->layoutInfo_.itemEnd_);
    EXPECT_FALSE(pattern_->layoutInfo_.offsetEnd_);
}

/**
 * @tc.name: UpdateCurrentOffset003
 * @tc.desc: Test the firstIndex and endIndex after UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, UpdateCurrentOffset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow
     * @tc.steps: step2. scroll up to a remote position
     * @tc.expected: startIndex_ = 0 endIndex_ = 0.
     */
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });
    pattern_->SetAnimateCanOverScroll(true);
    pattern_->UpdateCurrentOffset(10000, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.firstIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.endIndex_, 0);

    /**
     * @tc.steps: step1. create waterFlow
     * @tc.steps: step2. scroll down to a remote position
     * @tc.expected: startIndex_ = TOTAL_LINE_NUMBER * 2 - 1, endIndex_ = TOTAL_LINE_NUMBER * 2 - 1.
     */
    pattern_->SetAnimateCanOverScroll(true);
    pattern_->UpdateCurrentOffset(-99999, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.firstIndex_, 19);
    EXPECT_EQ(pattern_->layoutInfo_.endIndex_, 19);
}

/**
 * @tc.name: PositionController001
 * @tc.desc: Test PositionController
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionController001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });

    /**
     * @tc.steps: step1. Test ScrollPage and IsAtEnd
     */
    auto controller = pattern_->positionController_;
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqualTotalOffset(WATERFLOW_HEIGHT));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), WATERFLOW_HEIGHT);
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
 * @tc.name: PositionController002
 * @tc.desc: Test PositionController ScrollBy
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionController002, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step1. Test ScrollBy
     */
    controller->ScrollBy(0, ITEM_HEIGHT, true);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), ITEM_HEIGHT);
}

/**
 * @tc.name: PositionController003
 * @tc.desc: Test PositionController ScrollEdge
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionController003, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step1. Test ScrollToEdge
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_TRUE(IsEqualTotalOffset(WATERFLOW_HEIGHT));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY = 200.f;
constexpr float OFFSET_TIME = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS = 20 * 20;
} // namespace
/**
 * @tc.name: PositionController004
 * @tc.desc: Test PositionController ScrollEdge
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionController004, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });
    auto controller = pattern_->positionController_;
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY);
    int32_t offsetTime = OFFSET_TIME;
    for (int i = 0; i < TIME_CHANGED_COUNTS; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY);
    offsetTime = OFFSET_TIME;
    for (int i = 0; i < TIME_CHANGED_COUNTS; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());
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
        CreateItem(TOTAL_LINE_NUMBER * 4);
    });

    /**
     * @tc.steps: step1. Run pattern func.
     * @tc.expected: The return_value is correct.
     */
    EXPECT_TRUE(pattern_->IsScrollable());
    EXPECT_TRUE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step2. Scroll to bottom
     */
    UpdateCurrentOffset(-WATERFLOW_HEIGHT);
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_TRUE(pattern_->IsAtBottom());
}

/**
 * @tc.name: WaterFlowPatternTest002
 * @tc.desc: Test water flow pattern func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow
     * @tc.expected: startIndex_ = 0  endIndex_ = 21
     */
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
        CreateItem(TOTAL_LINE_NUMBER * 4);
    });
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.endIndex_, 21);

    /**
     * @tc.steps: step2. UpdateCurrentOffset -100.f.
     * @tc.expected: startIndex_ = 0  endIndex_ = 21.
     */
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    pattern_->UpdateScrollBarOffset();
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.endIndex_, 21);

    /**
     * @tc.steps: step3. UpdateCurrentOffset 200.f.
     * @tc.expected: startIndex_ = 5  endIndex_ = 27.
     */
    pattern_->UpdateCurrentOffset(200.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, -ITEM_HEIGHT * 2);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 5);
    EXPECT_EQ(pattern_->layoutInfo_.endIndex_, 27);

    /**
     * @tc.steps: step3. UpdateCurrentOffset 100.f.
     * @tc.expected: startIndex_ = 1  endIndex_ = 24.
     */
    pattern_->UpdateCurrentOffset(100.f, SCROLL_FROM_ANIMATION_SPRING);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, -ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_.endIndex_, 24);
}

/**
 * @tc.name: WaterFlowAccessibilityTest001
 * @tc.desc: Test Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowAccessibilityTest001, TestSize.Level1)
{
    float colNumber = 4;
    Create([colNumber](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateItem(TOTAL_LINE_NUMBER * colNumber);
    });

    /**
     * @tc.steps: step1. Run Accessibility func.
     * @tc.expected: The return_value is correct.
     */
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 21);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), TOTAL_LINE_NUMBER * colNumber);
    AceCollectionInfo info = accessibilityProperty_->GetCollectionInfo();
    EXPECT_EQ(info.rows, 6);
    EXPECT_EQ(info.columns, colNumber);

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
    UpdateCurrentOffset(-WATERFLOW_HEIGHT);
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
        CreateItem(1);
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
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(IsEqualTotalOffset(WATERFLOW_HEIGHT));
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
        CreateItem(5);
        ViewStackProcessor::GetInstance()->Pop();
    });

    /**
     * @tc.steps: step1. Run footer func.
     * @tc.expected: The return_value is correct.
     */
    auto footerRect = GetChildRect(frameNode_, pattern_->layoutInfo_.footerIndex_);
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
        CreateItem(5);
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
    CreateWithItem([reachStart, reachEnd](WaterFlowModelNG model) {
        model.SetOnReachStart(reachStart);
        model.SetOnReachEnd(reachEnd);
    });

    /**
     * @tc.steps: step1. init will trigger once
     */
    EXPECT_TRUE(isReachStartCalled);
    isReachStartCalled = false;

    /**
     * @tc.steps: step2. Scroll down to end
     * @tc.expected: Trigger reachend
     */
    UpdateCurrentOffset(-WATERFLOW_HEIGHT);
    EXPECT_TRUE(isReachEndCalled);

    /**
     * @tc.steps: step3. Scroll up to start
     * @tc.expected: Trigger reachstart
     */
    UpdateCurrentOffset(WATERFLOW_HEIGHT);
    EXPECT_TRUE(isReachStartCalled);
}

/**
 * @tc.name: Callback002
 * @tc.desc: Test EdgeEffectCallback
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Callback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow
     */
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });

    auto gestureHub = pattern_->GetGestureHub();
    auto axis = pattern_->GetAxis();
    ASSERT_NE(gestureHub->scrollableActuator_, nullptr);
    EXPECT_EQ(axis, Axis::VERTICAL);
    auto effect = gestureHub->scrollableActuator_->scrollEffects_[axis];

    EXPECT_EQ(effect->leadingCallback_(), 0);
    EXPECT_EQ(effect->initLeadingCallback_(), 0);
    EXPECT_EQ(effect->currentPositionCallback_(), 0);

    pattern_->SetAlwaysEnabled(true);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(effect->leadingCallback_(), 0);
    EXPECT_EQ(effect->initLeadingCallback_(), 0);
    EXPECT_EQ(effect->currentPositionCallback_(), 0);

    pattern_->layoutInfo_.Reset();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(effect->leadingCallback_(), 0);
    EXPECT_EQ(effect->initLeadingCallback_(), 0);
    EXPECT_EQ(effect->currentPositionCallback_(), 0);
}

/**
 * @tc.name: onScroll001
 * @tc.desc: Test onScroll event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, OnScroll001, TestSize.Level1)
{
    CalcDimension scrollOffset;
    ScrollState scrollState = ScrollState::IDLE;
    auto onScroll = [&scrollOffset, &scrollState](CalcDimension offset, ScrollState state) {
        scrollOffset = offset;
        scrollState = state;
    };
    CreateWithItem([onScroll](WaterFlowModelNG model) { model.SetOnScroll(onScroll); });

    /**
     * @tc.steps: step1. finger moves up
     * @tc.expected: Trigger onScroll with SCROLL state
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_EQ(scrollOffset.Value(), ITEM_HEIGHT);
    EXPECT_EQ(scrollState, ScrollState::SCROLL);

    /**
     * @tc.steps: step2. fling
     * @tc.expected: Trigger onScroll with FLING state
     */
    UpdateCurrentOffset(-1, SCROLL_FROM_ANIMATION);
    EXPECT_EQ(scrollOffset.Value(), 1);
    EXPECT_EQ(scrollState, ScrollState::FLING);

    /**
     * @tc.steps: step3. stop
     * @tc.expected: Trigger onScroll with IDLE state
     */
    pattern_->OnAnimateStop();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(scrollOffset.Value(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);
}

/**
 * @tc.name: onScroll002
 * @tc.desc: Test onScroll event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, OnScroll002, TestSize.Level1)
{
    CalcDimension scrollOffset;
    ScrollState scrollState = ScrollState::IDLE;
    auto onScroll = [&scrollOffset, &scrollState](CalcDimension offset, ScrollState state) {
        scrollOffset = offset;
        scrollState = state;
    };
    CreateWithItem([onScroll](WaterFlowModelNG model) { model.SetOnScroll(onScroll); });

    /**
     * @tc.steps: step1. finger moves down at top
     * @tc.expected: Trigger onScroll with SCROLL state
     */
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_EQ(scrollOffset.Value(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);
}

/**
 * @tc.name: onScrollIndex001
 * @tc.desc: Test onScrollIndex event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, onScrollIndex001, TestSize.Level1)
{
    int32_t firstIndex = -1;
    int32_t lastIndex = -1;
    auto onScrollIndex = [&firstIndex, &lastIndex](int32_t first, int32_t last) {
        firstIndex = first;
        lastIndex = last;
    };
    // 10 items total, 8 items showed
    CreateWithItem([onScrollIndex](WaterFlowModelNG model) { model.SetOnScrollIndex(onScrollIndex); });

    /**
     * @tc.steps: step0. event on first layout
     * @tc.expected: Trigger onScrollIndex
     */
    EXPECT_EQ(firstIndex, 0);
    EXPECT_EQ(lastIndex, 5);

    /**
     * @tc.steps: step1. finger move up, offset less than one item height
     * @tc.expected: last item changed, trigger onScrollIndex
     */
    UpdateCurrentOffset(-ITEM_HEIGHT / 2);
    EXPECT_EQ(firstIndex, 0);
    EXPECT_EQ(lastIndex, 5);

    /**
     * @tc.steps: step2. finger move up, offset more than one item height
     * @tc.expected: first and last item changed, trigger onScrollIndex
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_EQ(firstIndex, 1);
    EXPECT_EQ(lastIndex, 6);
}

/**
 * @tc.name: OnScrollStart001
 * @tc.desc: Verify onScrollStart and onScrollStop event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, OnScrollStart001, TestSize.Level1)
{
    bool isScrollStartCalled = false;
    bool isScrollStopCalled = false;
    auto scrollStart = [&isScrollStartCalled]() { isScrollStartCalled = true; };
    auto scrollStop = [&isScrollStopCalled]() { isScrollStopCalled = true; };
    Create([scrollStart, scrollStop](WaterFlowModelNG model) {
        model.SetOnScrollStart(scrollStart);
        model.SetOnScrollStop(scrollStop);
    });

    /**
     * @tc.steps: step1. pan start
     * @tc.expected: trigger onScrollStart
     */
    pattern_->OnScrollCallback(0, SCROLL_FROM_START);
    EXPECT_TRUE(isScrollStartCalled);

    /**
     * @tc.steps: step2. OnScrollEnd
     * @tc.expected: trigger onScrollStop
     */
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isScrollStopCalled);
}

/**
 * @tc.name: WaterFlowLayoutInfoTest001
 * @tc.desc: Test functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowLayoutInfoTest001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetRowsTemplate("1fr 1fr");
        model.SetRowsGap(Dimension(5));
        for (int32_t i = 0; i < TOTAL_LINE_NUMBER; i++) {
            WaterFlowItemModelNG waterFlowItemModel;
            waterFlowItemModel.Create();
            ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
            ViewAbstract::SetHeight(CalcLength(Dimension(ITEM_HEIGHT)));
            ViewStackProcessor::GetInstance()->Pop();
        }
    });

    /**
     * @tc.steps: Test IsAllCrossReachEnd function
     * @tc.expected: step1. Check whether the return value is correct.
     */
    auto reached = pattern_->layoutInfo_.IsAllCrossReachEnd(ITEM_HEIGHT);
    EXPECT_TRUE(reached);
    reached = pattern_->layoutInfo_.IsAllCrossReachEnd(WATERFLOW_HEIGHT);
    EXPECT_TRUE(reached);

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
 * @tc.name: WaterFlowSetFriction001
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
    ViewAbstract::SetWidth(CalcLength(WATERFLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(WATERFLOW_HEIGHT));
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
 * @tc.name: WaterFlowPaintMethod001
 * @tc.desc: Test UpdateOverlayModifier.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFloW
     */
    CreateWithItem([](WaterFlowModelNG model) {
        CreateItem(TOTAL_LINE_NUMBER * 2);
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
    });

    /**
     * @tc.steps: step2. not set positionMode.
     * @tc.expected: the positionMode_ of scrollBarOverlayModifier_ is default value.
     */
    pattern_->SetScrollBar(DisplayMode::AUTO);
    auto scrollBar = pattern_->GetScrollBar();
    scrollBar->SetScrollable(true);

    auto paintMethod = pattern_->CreateNodePaintMethod();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(frameNode_->GetRenderContext(), frameNode_->GetGeometryNode(),
        frameNode_->GetPaintProperty<ScrollablePaintProperty>());
    paintMethod->UpdateOverlayModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(pattern_->GetScrollBarOverlayModifier()->positionMode_, PositionMode::RIGHT);

    /**
     * @tc.steps: step3. scrollBar setting positionMode set to bottom.
     * @tc.expected: the positionMode_ of scrollBarOverlayModifier_ is bottom.
     */
    pattern_->SetEdgeEffect(EdgeEffect::FADE);
    scrollBar->SetPositionMode(PositionMode::BOTTOM);

    paintMethod = pattern_->CreateNodePaintMethod();
    paintWrapper = AceType::MakeRefPtr<PaintWrapper>(frameNode_->GetRenderContext(), frameNode_->GetGeometryNode(),
        frameNode_->GetPaintProperty<ScrollablePaintProperty>());
    paintMethod->UpdateOverlayModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(pattern_->GetScrollBarOverlayModifier()->positionMode_, PositionMode::BOTTOM);
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
    Create([](WaterFlowModelNG model) {
        CreateItem(TOTAL_LINE_NUMBER * 2);
        model.SetColumnsTemplate("1fr 1fr");
    });
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step2. test function.
     * @tc.expected: function ScrollPage is called.
     */
    pattern_->SetAxis(Axis::VERTICAL);
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqualTotalOffset(WATERFLOW_HEIGHT));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), WATERFLOW_HEIGHT);
    EXPECT_EQ(accessibilityProperty_->GetScrollOffSet(), pattern_->GetTotalOffset());
    EXPECT_TRUE(controller->IsAtEnd());

    pattern_->SetAxis(Axis::NONE);
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqualTotalOffset(WATERFLOW_HEIGHT));
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

    /**
     * @tc.steps: step2. Init contentModifier
     */
    pattern_->CreateNodePaintMethod();
    auto contentModifier = pattern_->contentModifier_;
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).Times(AtLeast(1));
    DrawingContext context = { canvas, 1.f, 1.f };

    /**
     * @tc.steps: step3. test function.
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
    pattern_->AddScrollEvent();
    EXPECT_NE(pattern_->scrollableEvent_, nullptr);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->CanOverScroll(SCROLL_FROM_UPDATE));

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
    int32_t crossIndex = pattern_->layoutInfo_.items_[0].rbegin()->first;
    int32_t itemIndex = pattern_->layoutInfo_.items_[0].rbegin()->second.rbegin()->first;
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
    std::size_t waterFlowItemsSize = pattern_->layoutInfo_.items_[0].size();
    int32_t mainCount = pattern_->layoutInfo_.GetMainCount();

    int32_t index = pattern_->layoutInfo_.items_[0].rbegin()->first;
    pattern_->layoutInfo_.items_[0][index + 1] = std::map<int32_t, std::pair<float, float>>();
    EXPECT_EQ(pattern_->layoutInfo_.items_[0].size(), waterFlowItemsSize + 1);
    EXPECT_EQ(pattern_->layoutInfo_.GetMainCount(), mainCount);

    auto lastItem = pattern_->layoutInfo_.items_[0].begin()->second.rbegin();
    float mainSize = lastItem->second.first + lastItem->second.second - 1.0f;
    EXPECT_FALSE(pattern_->layoutInfo_.IsAllCrossReachEnd(mainSize));

    pattern_->layoutInfo_.ClearCacheAfterIndex(index + 1);
    EXPECT_EQ(pattern_->layoutInfo_.items_[0].size(), waterFlowItemsSize + 1);
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
    pattern_->layoutInfo_.Reset(resetFrom + 1);
    EXPECT_EQ(pattern_->layoutInfo_.endIndex_, resetFrom);

    pattern_->layoutInfo_.Reset(resetFrom - 1);
    EXPECT_EQ(pattern_->layoutInfo_.endIndex_, resetFrom);
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
    int32_t crossIndex = pattern_->layoutInfo_.items_[0].rbegin()->first;
    pattern_->layoutInfo_.items_[0][crossIndex + 1][0] = std::pair<float, float>(1.0f, maxMainHeight);
    pattern_->layoutInfo_.itemInfos_.clear();
    pattern_->layoutInfo_.endPosArray_.clear();
    EXPECT_EQ(pattern_->layoutInfo_.GetMaxMainHeight(), maxMainHeight + 1.0f);

    /**
     * @tc.steps: Test GetCrossIndexForNextItem function
     * @tc.expected: step3. Check whether the return value is correct.
     */
    pattern_->layoutInfo_.items_[0][crossIndex + 1][1] = std::pair<float, float>(0.0f, 0.0f);
    FlowItemIndex position = pattern_->layoutInfo_.GetCrossIndexForNextItem(0);
    EXPECT_EQ(position.crossIndex, crossIndex + 1);
    EXPECT_EQ(position.lastItemIndex, 1);
}

/**
 * @tc.name: WaterFlowGetItemRectTest001
 * @tc.desc: Test WaterFlow GetItemRect function.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowGetItemRectTest001, TestSize.Level1)
{
    float colNumber = 4;
    CreateWithItem([colNumber](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateItem(TOTAL_LINE_NUMBER * colNumber);
    });

    /**
     * @tc.steps: step2. Get invalid WaterFlowItem Rect.
     * @tc.expected: Return 0 when input invalid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(-1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(32), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(33), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(39), Rect()));

    /**
     * @tc.steps: step3. Get valid WaterFlowItem Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    float itemWidth = WATERFLOW_WIDTH / colNumber;
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, 0, itemWidth, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(5), Rect(itemWidth * 2, ITEM_HEIGHT, itemWidth, BIG_ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(10), Rect(itemWidth * 2, ITEM_HEIGHT * 3, itemWidth, ITEM_HEIGHT)));
}

/**
 * @tc.name: MeasureForAnimation001
 * @tc.desc: Test WaterFlow MeasureForAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, MeasureForAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WithItem to test MeaseForAnimation for node creation .
     * @tc.expected: pattern_->layoutInfo_ There is corresponding index information in it.
     */
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });
    pattern_->ScrollToIndex(15, true);

    /**
     * @tc.steps: step2. Get value from  pattern_ -> LayoutInfo_ .
     * @tc.expected: return value(crossIndex) is not -1.
     */
    auto crossIndex = pattern_->layoutInfo_.GetCrossIndex(10);
    EXPECT_FALSE(IsEqual(crossIndex, -1));
}

/**
 * @tc.name: ScrollToIndex001
 * @tc.desc: Test WaterFlow ScrollToIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ScrollToIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Calling the ScrollToIndex interface to set values to 20 and true.
     * @tc.expected: pattern_->targetIndex_ is 20
     */
    CreateWithItem([](WaterFlowModelNG model) {});
    pattern_->ScrollToIndex(20, true);
    EXPECT_EQ(pattern_->targetIndex_, 20);
}

/**
 * @tc.name: ScrollToIndex002
 * @tc.desc: Test ScrollToIndex func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ScrollToIndex002, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(30);
    });

    pattern_->ScrollToIndex(3, false, ScrollAlign::AUTO);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, 0);

    pattern_->ScrollToIndex(15, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 15);
    EXPECT_EQ(pattern_->layoutInfo_.storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, -1100);

    pattern_->ScrollToIndex(LAST_ITEM);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 19);
    EXPECT_EQ(pattern_->layoutInfo_.storedOffset_, -100);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, -1500);

    pattern_->ScrollToIndex(0, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, 0);

    pattern_->ScrollToIndex(15, false, ScrollAlign::AUTO);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 7);
    EXPECT_EQ(pattern_->layoutInfo_.storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, -500);

    pattern_->ScrollToIndex(7, false, ScrollAlign::CENTER);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_.storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, -200);

    pattern_->ScrollToIndex(14, false, ScrollAlign::END);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_.storedOffset_, -100);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, -300);

    pattern_->ScrollToIndex(2, false, ScrollAlign::AUTO);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_.storedOffset_, -100);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, -100);
}

/**
 * @tc.name: ScrollToIndex003
 * @tc.desc: Test ScrollToIndex func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ScrollToIndex003, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(30);
    });

    pattern_->ScrollToIndex(3, true, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 200.f);

    pattern_->ScrollToIndex(3, true, ScrollAlign::END);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, -400.f);

    pattern_->ScrollToIndex(15, true, ScrollAlign::AUTO);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 500.f);

    pattern_->ScrollToIndex(15, true, ScrollAlign::CENTER);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 800.f);

    pattern_->ScrollToIndex(3, true, ScrollAlign::AUTO);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 800.f);

    pattern_->ScrollPage(false);
    FlushLayoutTask(frameNode_);
    EXPECT_LT(pattern_->layoutInfo_.currentOffset_, 0.f);

    pattern_->ScrollToIndex(3, true, ScrollAlign::AUTO);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 200.f);

    pattern_->ScrollToIndex(3, true, ScrollAlign::NONE);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 200.f);

    pattern_->ScrollToIndex(29, true);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 2100.f);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll001
 * @tc.desc: Test onScroll event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, OnWillScrollAndOnDidScroll001, TestSize.Level1)
{
    bool isOnScrollCallBack = false;
    bool isOnWillScrollCallBack = false;
    bool isOnDidScrollCallBack = false;

    CalcDimension offsetY;
    ScrollState scrollState = ScrollState::IDLE;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](CalcDimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    Dimension willScrollOffset;
    ScrollState willScrollState;
    auto onWillScroll = [&willScrollOffset, &willScrollState, &isOnWillScrollCallBack](
                            Dimension offset, ScrollState state) {
        willScrollOffset = offset;
        willScrollState = state;
        isOnWillScrollCallBack = true;
    };
    Dimension didScrollOffset;
    ScrollState didScrollState = ScrollState::IDLE;
    auto onDidScroll = [&didScrollOffset, &didScrollState, &isOnDidScrollCallBack](
                           Dimension offset, ScrollState state) {
        didScrollOffset = offset;
        didScrollState = state;
        isOnDidScrollCallBack = true;
    };

    CreateWithItem([onScroll](WaterFlowModelNG model) { model.SetOnScroll(onScroll); });
    eventHub_->SetOnWillScroll(std::move(onWillScroll));
    eventHub_->SetOnDidScroll(std::move(onDidScroll));

    /**
     * @tc.steps: step1. finger moves down at top
     * @tc.expected: Trigger onWillScroll and onDidScroll with SCROLL state
     */
    pattern_->ScrollTo(ITEM_HEIGHT * 5);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_TRUE(isOnWillScrollCallBack);
    EXPECT_TRUE(isOnDidScrollCallBack);
    EXPECT_EQ(offsetY.Value(), ITEM_HEIGHT * 5);
    EXPECT_EQ(willScrollOffset.Value(), ITEM_HEIGHT * 5);
    EXPECT_EQ(didScrollOffset.Value(), ITEM_HEIGHT * 5);
    EXPECT_EQ(scrollState, willScrollState);
    EXPECT_EQ(scrollState, didScrollState);
}

/**
 * @tc.name: onScroll
 * @tc.desc: Test onScroll event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, OnWillScrollAndOnDidScroll002, TestSize.Level1)
{
    bool isOnScrollCallBack = false;
    bool isOnWillScrollCallBack = false;
    bool isOnDidScrollCallBack = false;

    CalcDimension offsetY;
    ScrollState scrollState = ScrollState::IDLE;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](CalcDimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    Dimension willScrollOffset;
    ScrollState willScrollState;
    auto onWillScroll = [&willScrollOffset, &willScrollState, &isOnWillScrollCallBack](
                            Dimension offset, ScrollState state) {
        willScrollOffset = offset;
        willScrollState = state;
        isOnWillScrollCallBack = true;
    };
    Dimension didScrollOffset;
    ScrollState didScrollState = ScrollState::IDLE;
    auto onDidScroll = [&didScrollOffset, &didScrollState, &isOnDidScrollCallBack](
                           Dimension offset, ScrollState state) {
        didScrollOffset = offset;
        didScrollState = state;
        isOnDidScrollCallBack = true;
    };

    CreateWithItem([onScroll](WaterFlowModelNG model) {
        model.SetOnScroll(onScroll);
        model.SetLayoutDirection(FlexDirection::ROW);
    });
    eventHub_->SetOnWillScroll(std::move(onWillScroll));
    eventHub_->SetOnDidScroll(std::move(onDidScroll));

    /**
     * @tc.steps: step1. finger moves down at top
     * @tc.expected: Trigger onScroll with SCROLL state
     */
    pattern_->ScrollTo(ITEM_HEIGHT * 5);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_TRUE(isOnWillScrollCallBack);
    EXPECT_TRUE(isOnDidScrollCallBack);
    EXPECT_EQ(offsetY.Value(), ITEM_HEIGHT * 5);
    EXPECT_EQ(willScrollOffset.Value(), ITEM_HEIGHT * 5);
    EXPECT_EQ(didScrollOffset.Value(), ITEM_HEIGHT * 5);
    EXPECT_EQ(scrollState, willScrollState);
    EXPECT_EQ(scrollState, didScrollState);
}

/**
 * @tc.name: ResetSections001
 * @tc.desc: Layout WaterFlow and then reset to old layout
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ResetSections001, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(60);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_5);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    auto& info = pattern_->layoutInfo_;

    UpdateCurrentOffset(-205.0f);
    EXPECT_EQ(info.currentOffset_, -205.0f);
    EXPECT_EQ(info.startIndex_, 3);
    EXPECT_EQ(info.endIndex_, 11);

    // fallback to layout without sections
    pattern_->ResetSections();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info.currentOffset_, -205.0f);
    EXPECT_EQ(info.startIndex_, 1);
    EXPECT_EQ(info.endIndex_, 5);
    EXPECT_EQ(info.GetCrossCount(), 1);
    if (SystemProperties::WaterFlowUseSegmentedLayout()) {
        EXPECT_EQ(info.segmentTails_.size(), 1);
        EXPECT_EQ(info.margins_.size(), 1);
    } else {
        EXPECT_TRUE(info.segmentTails_.empty());
        EXPECT_TRUE(info.margins_.empty());
    }

    UpdateCurrentOffset(250.0f);
    EXPECT_EQ(info.currentOffset_, 0.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 3);
}
} // namespace OHOS::Ace::NG
