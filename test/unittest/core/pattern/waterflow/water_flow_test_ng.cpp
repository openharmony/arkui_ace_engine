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

#define protected public
#define private public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_accessibility_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_event_hub.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"
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

class WaterFlowTestNg : public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void Create(const std::function<void(WaterFlowModelNG)>& callback = nullptr);
    void CreateWithItem(const std::function<void(WaterFlowModelNG)>& callback = nullptr);
    static void CreateItem(int32_t number = 10);
    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
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
    TestNG::SetUpTestSuite();
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
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
    ViewAbstract::SetWidth(CalcLength(WATERFLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(WATERFLOW_HEIGHT));
    model.SetScroller(positionController, scrollBarProxy);
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
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
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 0)->IsActive());
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
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
        CreateItem(TOTAL_LINE_NUMBER * 4);
    });

    /**
     * @tc.steps: step1. Run pattern func.
     * @tc.expected: The return_value is correct.
     */
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    pattern_->UpdateScrollBarOffset();
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, 0.f);

    pattern_->UpdateCurrentOffset(200.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, -ITEM_HEIGHT * 2);
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
 * @tc.name: onScroll
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
 * @tc.name: onScroll
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
 * @tc.name: onScrollIndex
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
 * @tc.name: onScrollStart and onScrollStop
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
     * @tc.steps: Test IsAllCrossReachend function
     * @tc.expected: step1. Check whether the return value is correct.
     */
    auto reached = pattern_->layoutInfo_.IsAllCrossReachend(ITEM_HEIGHT);
    EXPECT_TRUE(reached);
    reached = pattern_->layoutInfo_.IsAllCrossReachend(WATERFLOW_HEIGHT);
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
    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualTotalOffset(WATERFLOW_HEIGHT));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), WATERFLOW_HEIGHT);
    EXPECT_TRUE(controller->IsAtEnd());

    pattern_->SetAxis(Axis::NONE);
    controller->ScrollPage(false, true);
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
 * @tc.name: WaterFlowPattern_EdgeEffect001
 * @tc.desc: Test EdgeEffect.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPattern_EdgeEffect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Waterflow node
     */
    CreateWithItem([](WaterFlowModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING, true); });

    /**
     * @tc.steps: step2. test function.
     * @tc.expected: function CanOverScroll return true with spring edge effect.
     */
    EXPECT_TRUE(pattern_->CanOverScroll(SCROLL_FROM_UPDATE));
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

    pattern_->ScrollToIndex(3);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, 0);

    pattern_->ScrollToIndex(15);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 15);
    EXPECT_EQ(pattern_->layoutInfo_.storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, -1100);

    pattern_->ScrollToIndex(LAST_ITEM);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 19);
    EXPECT_EQ(pattern_->layoutInfo_.storedOffset_, -100);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, -1500);

    pattern_->ScrollToIndex(0);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_.startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_.currentOffset_, 0);
}
} // namespace OHOS::Ace::NG
