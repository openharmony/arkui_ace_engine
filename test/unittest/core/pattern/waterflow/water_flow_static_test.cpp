/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#include "water_flow_test_ng.h"

#include "core/components_ng/pattern/waterflow/water_flow_model_static.h"

namespace OHOS::Ace::NG {

class WaterFlowStaticTest : public WaterFlowTestNg {};

/**
 * @tc.name: CreateFrameNode001
 * @tc.desc: Test CreateFrameNode with different nodeIds
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, CreateFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create node with positive id.
     * @tc.expected: Node created with correct id and tag.
     */
    int32_t nodeId = 100;
    auto frameNode = WaterFlowModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetId(), nodeId);
    EXPECT_EQ(frameNode->GetTag(), "WaterFlow");
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    EXPECT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create node with zero id.
     * @tc.expected: Node created with id 0.
     */
    auto frameNode2 = WaterFlowModelStatic::CreateFrameNode(0);
    ASSERT_NE(frameNode2, nullptr);
    EXPECT_EQ(frameNode2->GetId(), 0);

    /**
     * @tc.steps: step3. Create node with negative id.
     * @tc.expected: Node created with negative id.
     */
    auto frameNode3 = WaterFlowModelStatic::CreateFrameNode(-1);
    ASSERT_NE(frameNode3, nullptr);
    EXPECT_EQ(frameNode3->GetId(), -1);
}

/**
 * @tc.name: GetOrCreateController001
 * @tc.desc: Test GetOrCreateController create and reuse
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, GetOrCreateController001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Clear existing controller and call GetOrCreateController.
     * @tc.expected: A new controller is created and attached to pattern.
     */
    pattern_->positionController_ = nullptr;
    auto controller = WaterFlowModelStatic::GetOrCreateController(AceType::RawPtr(frameNode_));
    ASSERT_NE(controller, nullptr);
    EXPECT_EQ(pattern_->GetPositionController(), controller);

    /**
     * @tc.steps: step2. Call GetOrCreateController again.
     * @tc.expected: Returns the same controller instance.
     */
    auto controller2 = WaterFlowModelStatic::GetOrCreateController(AceType::RawPtr(frameNode_));
    EXPECT_EQ(controller, controller2);

    /**
     * @tc.steps: step3. Call with null frameNode.
     * @tc.expected: Returns nullptr.
     */
    auto controller3 = WaterFlowModelStatic::GetOrCreateController(nullptr);
    EXPECT_EQ(controller3, nullptr);
}

/**
 * @tc.name: GetOrCreateScrollBarProxy001
 * @tc.desc: Test GetOrCreateScrollBarProxy create and reuse
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, GetOrCreateScrollBarProxy001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Clear existing proxy and call GetOrCreateScrollBarProxy.
     * @tc.expected: A new proxy is created and attached to pattern.
     */
    pattern_->scrollBarProxy_ = nullptr;
    auto proxy = WaterFlowModelStatic::GetOrCreateScrollBarProxy(AceType::RawPtr(frameNode_));
    ASSERT_NE(proxy, nullptr);
    EXPECT_EQ(pattern_->GetScrollBarProxy(), proxy);

    /**
     * @tc.steps: step2. Call GetOrCreateScrollBarProxy again.
     * @tc.expected: Returns the same proxy instance.
     */
    auto proxy2 = WaterFlowModelStatic::GetOrCreateScrollBarProxy(AceType::RawPtr(frameNode_));
    EXPECT_EQ(proxy, proxy2);

    /**
     * @tc.steps: step3. Call with null frameNode.
     * @tc.expected: Returns nullptr.
     */
    auto proxy3 = WaterFlowModelStatic::GetOrCreateScrollBarProxy(nullptr);
    EXPECT_EQ(proxy3, nullptr);
}

/**
 * @tc.name: SetColumnsTemplate001
 * @tc.desc: Test SetColumnsTemplate with various templates
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetColumnsTemplate001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set columnsTemplate to "1fr 1fr".
     * @tc.expected: Property value equals "1fr 1fr".
     */
    std::optional<std::string> columnsTemplate = "1fr 1fr";
    WaterFlowModelStatic::SetColumnsTemplate(AceType::RawPtr(frameNode_), columnsTemplate);
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(""), "1fr 1fr");

    /**
     * @tc.steps: step2. Set columnsTemplate to "1fr 2fr 1fr".
     * @tc.expected: Property value equals "1fr 2fr 1fr".
     */
    columnsTemplate = "1fr 2fr 1fr";
    WaterFlowModelStatic::SetColumnsTemplate(AceType::RawPtr(frameNode_), columnsTemplate);
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(""), "1fr 2fr 1fr");

    /**
     * @tc.steps: step3. Reset columnsTemplate with nullopt.
     * @tc.expected: Property has no value.
     */
    columnsTemplate.reset();
    WaterFlowModelStatic::SetColumnsTemplate(AceType::RawPtr(frameNode_), columnsTemplate);
    EXPECT_FALSE(layoutProperty_->GetColumnsTemplate().has_value());
}

/**
 * @tc.name: SetColumnsTemplate002
 * @tc.desc: Test SetColumnsTemplate with empty and special templates
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetColumnsTemplate002, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set columnsTemplate to empty string.
     * @tc.expected: Property value is empty string.
     */
    std::optional<std::string> columnsTemplate = "";
    WaterFlowModelStatic::SetColumnsTemplate(AceType::RawPtr(frameNode_), columnsTemplate);
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue("default"), "");

    /**
     * @tc.steps: step2. Set columnsTemplate with pixel values.
     * @tc.expected: Property value set correctly.
     */
    columnsTemplate = "100px 200px";
    WaterFlowModelStatic::SetColumnsTemplate(AceType::RawPtr(frameNode_), columnsTemplate);
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(""), "100px 200px");
}

/**
 * @tc.name: SetRowsTemplate001
 * @tc.desc: Test SetRowsTemplate with various templates
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetRowsTemplate001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set rowsTemplate to "1fr 1fr".
     * @tc.expected: Property value equals "1fr 1fr".
     */
    std::optional<std::string> rowsTemplate = "1fr 1fr";
    WaterFlowModelStatic::SetRowsTemplate(AceType::RawPtr(frameNode_), rowsTemplate);
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue(""), "1fr 1fr");

    /**
     * @tc.steps: step2. Set rowsTemplate to "auto".
     * @tc.expected: Property value equals "auto".
     */
    rowsTemplate = "auto";
    WaterFlowModelStatic::SetRowsTemplate(AceType::RawPtr(frameNode_), rowsTemplate);
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue(""), "auto");

    /**
     * @tc.steps: step3. Reset rowsTemplate with nullopt.
     * @tc.expected: Property has no value.
     */
    rowsTemplate.reset();
    WaterFlowModelStatic::SetRowsTemplate(AceType::RawPtr(frameNode_), rowsTemplate);
    EXPECT_FALSE(layoutProperty_->GetRowsTemplate().has_value());
}

/**
 * @tc.name: SetScrollEnabled001
 * @tc.desc: Test SetScrollEnabled toggle states
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetScrollEnabled001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set scrollEnabled to false.
     * @tc.expected: ScrollEnabled is false.
     */
    WaterFlowModelStatic::SetScrollEnabled(AceType::RawPtr(frameNode_), false);
    EXPECT_FALSE(layoutProperty_->GetScrollEnabledValue(true));

    /**
     * @tc.steps: step2. Set scrollEnabled to true.
     * @tc.expected: ScrollEnabled is true.
     */
    WaterFlowModelStatic::SetScrollEnabled(AceType::RawPtr(frameNode_), true);
    EXPECT_TRUE(layoutProperty_->GetScrollEnabledValue(false));

    /**
     * @tc.steps: step3. Toggle back to false.
     * @tc.expected: ScrollEnabled is false again.
     */
    WaterFlowModelStatic::SetScrollEnabled(AceType::RawPtr(frameNode_), false);
    EXPECT_FALSE(layoutProperty_->GetScrollEnabledValue(true));
}

/**
 * @tc.name: SetColumnsGap001
 * @tc.desc: Test SetColumnsGap with different units
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetColumnsGap001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set columnsGap to 16vp.
     * @tc.expected: Property value equals Dimension(16vp).
     */
    std::optional<Dimension> columnsGap = Dimension(16.f, DimensionUnit::VP);
    WaterFlowModelStatic::SetColumnsGap(AceType::RawPtr(frameNode_), columnsGap);
    EXPECT_EQ(layoutProperty_->GetColumnsGapValue(Dimension(0.0)), Dimension(16.f, DimensionUnit::VP));

    /**
     * @tc.steps: step2. Set columnsGap to 10px.
     * @tc.expected: Property value equals Dimension(10px).
     */
    columnsGap = Dimension(10.f, DimensionUnit::PX);
    WaterFlowModelStatic::SetColumnsGap(AceType::RawPtr(frameNode_), columnsGap);
    EXPECT_EQ(layoutProperty_->GetColumnsGapValue(Dimension(0.0)), Dimension(10.f, DimensionUnit::PX));

    /**
     * @tc.steps: step3. Reset columnsGap with nullopt.
     * @tc.expected: Property has no value.
     */
    columnsGap.reset();
    WaterFlowModelStatic::SetColumnsGap(AceType::RawPtr(frameNode_), columnsGap);
    EXPECT_FALSE(layoutProperty_->GetColumnsGap().has_value());
}

/**
 * @tc.name: SetColumnsGap002
 * @tc.desc: Test SetColumnsGap with zero and percent values
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetColumnsGap002, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set columnsGap to 0.
     * @tc.expected: Property value equals Dimension(0).
     */
    std::optional<Dimension> columnsGap = Dimension(0.f);
    WaterFlowModelStatic::SetColumnsGap(AceType::RawPtr(frameNode_), columnsGap);
    EXPECT_EQ(layoutProperty_->GetColumnsGapValue(Dimension(1.0)).Value(), 0.f);

    /**
     * @tc.steps: step2. Set columnsGap to 5%.
     * @tc.expected: Property value equals Dimension(5%).
     */
    columnsGap = Dimension(5.f, DimensionUnit::PERCENT);
    WaterFlowModelStatic::SetColumnsGap(AceType::RawPtr(frameNode_), columnsGap);
    auto result = layoutProperty_->GetColumnsGapValue(Dimension(0.0));
    EXPECT_EQ(result.Unit(), DimensionUnit::PERCENT);
    EXPECT_FLOAT_EQ(result.Value(), 5.f);
}

/**
 * @tc.name: SetRowsGap001
 * @tc.desc: Test SetRowsGap with different units
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetRowsGap001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set rowsGap to 8vp.
     * @tc.expected: Property value equals Dimension(8vp).
     */
    std::optional<Dimension> rowsGap = Dimension(8.f, DimensionUnit::VP);
    WaterFlowModelStatic::SetRowsGap(AceType::RawPtr(frameNode_), rowsGap);
    EXPECT_EQ(layoutProperty_->GetRowsGapValue(Dimension(0.0)), Dimension(8.f, DimensionUnit::VP));

    /**
     * @tc.steps: step2. Set rowsGap to 20fp.
     * @tc.expected: Property value equals Dimension(20fp).
     */
    rowsGap = Dimension(20.f, DimensionUnit::FP);
    WaterFlowModelStatic::SetRowsGap(AceType::RawPtr(frameNode_), rowsGap);
    EXPECT_EQ(layoutProperty_->GetRowsGapValue(Dimension(0.0)), Dimension(20.f, DimensionUnit::FP));

    /**
     * @tc.steps: step3. Reset rowsGap with nullopt.
     * @tc.expected: Property has no value.
     */
    rowsGap.reset();
    WaterFlowModelStatic::SetRowsGap(AceType::RawPtr(frameNode_), rowsGap);
    EXPECT_FALSE(layoutProperty_->GetRowsGap().has_value());
}

/**
 * @tc.name: SetItemMinWidth001
 * @tc.desc: Test SetItemMinWidth with various values
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetItemMinWidth001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set minWidth to 100vp.
     * @tc.expected: ItemMinSize width equals CalcLength(100vp).
     */
    std::optional<CalcLength> minWidth = CalcLength(100.0_vp);
    WaterFlowModelStatic::SetItemMinWidth(AceType::RawPtr(frameNode_), minWidth);
    EXPECT_TRUE(layoutProperty_->HasItemLayoutConstraint());
    auto minSize = layoutProperty_->GetItemMinSize();
    ASSERT_TRUE(minSize.has_value());
    EXPECT_EQ(minSize->Width(), CalcLength(100.0_vp));

    /**
     * @tc.steps: step2. Set minWidth to 50%.
     * @tc.expected: Width set to percentage value.
     */
    minWidth = CalcLength(Dimension(50.f, DimensionUnit::PERCENT));
    WaterFlowModelStatic::SetItemMinWidth(AceType::RawPtr(frameNode_), minWidth);
    minSize = layoutProperty_->GetItemMinSize();
    ASSERT_TRUE(minSize.has_value());

    /**
     * @tc.steps: step3. Set minWidth with nullopt.
     * @tc.expected: Width falls back to default CalcLength(0vp).
     */
    minWidth.reset();
    WaterFlowModelStatic::SetItemMinWidth(AceType::RawPtr(frameNode_), minWidth);
    minSize = layoutProperty_->GetItemMinSize();
    ASSERT_TRUE(minSize.has_value());
    EXPECT_EQ(minSize->Width(), CalcLength(0.0_vp));
}

/**
 * @tc.name: SetItemMaxWidth001
 * @tc.desc: Test SetItemMaxWidth with various values
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetItemMaxWidth001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set maxWidth to 200vp.
     * @tc.expected: ItemMaxSize width equals CalcLength(200vp).
     */
    std::optional<CalcLength> maxWidth = CalcLength(200.0_vp);
    WaterFlowModelStatic::SetItemMaxWidth(AceType::RawPtr(frameNode_), maxWidth);
    EXPECT_TRUE(layoutProperty_->HasItemLayoutConstraint());
    auto maxSize = layoutProperty_->GetItemMaxSize();
    ASSERT_TRUE(maxSize.has_value());
    EXPECT_EQ(maxSize->Width(), CalcLength(200.0_vp));

    /**
     * @tc.steps: step2. Set maxWidth to 300px.
     * @tc.expected: Width set to pixel value.
     */
    maxWidth = CalcLength(Dimension(300.f, DimensionUnit::PX));
    WaterFlowModelStatic::SetItemMaxWidth(AceType::RawPtr(frameNode_), maxWidth);
    maxSize = layoutProperty_->GetItemMaxSize();
    ASSERT_TRUE(maxSize.has_value());

    /**
     * @tc.steps: step3. Set maxWidth with nullopt.
     * @tc.expected: Width falls back to default CalcLength(0vp).
     */
    maxWidth.reset();
    WaterFlowModelStatic::SetItemMaxWidth(AceType::RawPtr(frameNode_), maxWidth);
    maxSize = layoutProperty_->GetItemMaxSize();
    ASSERT_TRUE(maxSize.has_value());
    EXPECT_EQ(maxSize->Width(), CalcLength(0.0_vp));
}

/**
 * @tc.name: SetItemMinHeight001
 * @tc.desc: Test SetItemMinHeight with various values
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetItemMinHeight001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set minHeight to 50vp.
     * @tc.expected: ItemMinSize height equals CalcLength(50vp).
     */
    std::optional<CalcLength> minHeight = CalcLength(50.0_vp);
    WaterFlowModelStatic::SetItemMinHeight(AceType::RawPtr(frameNode_), minHeight);
    EXPECT_TRUE(layoutProperty_->HasItemLayoutConstraint());
    auto minSize = layoutProperty_->GetItemMinSize();
    ASSERT_TRUE(minSize.has_value());
    EXPECT_EQ(minSize->Height(), CalcLength(50.0_vp));

    /**
     * @tc.steps: step2. Set minHeight to 80fp.
     * @tc.expected: Height set to fp value.
     */
    minHeight = CalcLength(Dimension(80.f, DimensionUnit::FP));
    WaterFlowModelStatic::SetItemMinHeight(AceType::RawPtr(frameNode_), minHeight);
    minSize = layoutProperty_->GetItemMinSize();
    ASSERT_TRUE(minSize.has_value());

    /**
     * @tc.steps: step3. Set minHeight with nullopt.
     * @tc.expected: Height falls back to default CalcLength(0vp).
     */
    minHeight.reset();
    WaterFlowModelStatic::SetItemMinHeight(AceType::RawPtr(frameNode_), minHeight);
    minSize = layoutProperty_->GetItemMinSize();
    ASSERT_TRUE(minSize.has_value());
    EXPECT_EQ(minSize->Height(), CalcLength(0.0_vp));
}

/**
 * @tc.name: SetItemMaxHeight001
 * @tc.desc: Test SetItemMaxHeight with various values
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetItemMaxHeight001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set maxHeight to 150vp.
     * @tc.expected: ItemMaxSize height equals CalcLength(150vp).
     */
    std::optional<CalcLength> maxHeight = CalcLength(150.0_vp);
    WaterFlowModelStatic::SetItemMaxHeight(AceType::RawPtr(frameNode_), maxHeight);
    EXPECT_TRUE(layoutProperty_->HasItemLayoutConstraint());
    auto maxSize = layoutProperty_->GetItemMaxSize();
    ASSERT_TRUE(maxSize.has_value());
    EXPECT_EQ(maxSize->Height(), CalcLength(150.0_vp));

    /**
     * @tc.steps: step2. Set maxHeight to 100%.
     * @tc.expected: Height set to percentage value.
     */
    maxHeight = CalcLength(Dimension(100.f, DimensionUnit::PERCENT));
    WaterFlowModelStatic::SetItemMaxHeight(AceType::RawPtr(frameNode_), maxHeight);
    maxSize = layoutProperty_->GetItemMaxSize();
    ASSERT_TRUE(maxSize.has_value());

    /**
     * @tc.steps: step3. Set maxHeight with nullopt.
     * @tc.expected: Height falls back to default CalcLength(0vp).
     */
    maxHeight.reset();
    WaterFlowModelStatic::SetItemMaxHeight(AceType::RawPtr(frameNode_), maxHeight);
    maxSize = layoutProperty_->GetItemMaxSize();
    ASSERT_TRUE(maxSize.has_value());
    EXPECT_EQ(maxSize->Height(), CalcLength(0.0_vp));
}

/**
 * @tc.name: SetLayoutDirection001
 * @tc.desc: Test SetLayoutDirection with all FlexDirection values
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetLayoutDirection001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set direction to ROW.
     * @tc.expected: WaterflowDirection equals FlexDirection::ROW.
     */
    std::optional<FlexDirection> direction = FlexDirection::ROW;
    WaterFlowModelStatic::SetLayoutDirection(AceType::RawPtr(frameNode_), direction);
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionValue(FlexDirection::COLUMN), FlexDirection::ROW);

    /**
     * @tc.steps: step2. Set direction to COLUMN.
     * @tc.expected: WaterflowDirection equals FlexDirection::COLUMN.
     */
    direction = FlexDirection::COLUMN;
    WaterFlowModelStatic::SetLayoutDirection(AceType::RawPtr(frameNode_), direction);
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionValue(FlexDirection::ROW), FlexDirection::COLUMN);

    /**
     * @tc.steps: step3. Set direction to ROW_REVERSE.
     * @tc.expected: WaterflowDirection equals FlexDirection::ROW_REVERSE.
     */
    direction = FlexDirection::ROW_REVERSE;
    WaterFlowModelStatic::SetLayoutDirection(AceType::RawPtr(frameNode_), direction);
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionValue(FlexDirection::COLUMN), FlexDirection::ROW_REVERSE);
}

/**
 * @tc.name: SetLayoutDirection002
 * @tc.desc: Test SetLayoutDirection with COLUMN_REVERSE and reset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetLayoutDirection002, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set direction to COLUMN_REVERSE.
     * @tc.expected: WaterflowDirection equals FlexDirection::COLUMN_REVERSE.
     */
    std::optional<FlexDirection> direction = FlexDirection::COLUMN_REVERSE;
    WaterFlowModelStatic::SetLayoutDirection(AceType::RawPtr(frameNode_), direction);
    EXPECT_EQ(layoutProperty_->GetWaterflowDirectionValue(FlexDirection::COLUMN), FlexDirection::COLUMN_REVERSE);

    /**
     * @tc.steps: step2. Reset direction with nullopt.
     * @tc.expected: WaterflowDirection property has no value.
     */
    direction.reset();
    WaterFlowModelStatic::SetLayoutDirection(AceType::RawPtr(frameNode_), direction);
    EXPECT_FALSE(layoutProperty_->GetWaterflowDirection().has_value());
}

/**
 * @tc.name: SetNestedScroll001
 * @tc.desc: Test SetNestedScroll with various mode combinations
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetNestedScroll001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set forward=SELF_FIRST, backward=PARENT_FIRST.
     * @tc.expected: NestedScroll modes set correctly.
     */
    NestedScrollOptions nestedOpt;
    nestedOpt.forward = NestedScrollMode::SELF_FIRST;
    nestedOpt.backward = NestedScrollMode::PARENT_FIRST;
    WaterFlowModelStatic::SetNestedScroll(AceType::RawPtr(frameNode_), nestedOpt);
    auto result = pattern_->GetNestedScroll();
    EXPECT_EQ(result.forward, NestedScrollMode::SELF_FIRST);
    EXPECT_EQ(result.backward, NestedScrollMode::PARENT_FIRST);

    /**
     * @tc.steps: step2. Set forward=PARALLEL, backward=SELF_ONLY.
     * @tc.expected: NestedScroll modes updated correctly.
     */
    nestedOpt.forward = NestedScrollMode::PARALLEL;
    nestedOpt.backward = NestedScrollMode::SELF_ONLY;
    WaterFlowModelStatic::SetNestedScroll(AceType::RawPtr(frameNode_), nestedOpt);
    result = pattern_->GetNestedScroll();
    EXPECT_EQ(result.forward, NestedScrollMode::PARALLEL);
    EXPECT_EQ(result.backward, NestedScrollMode::SELF_ONLY);
}

/**
 * @tc.name: SetFriction001
 * @tc.desc: Test SetFriction with valid values and reset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetFriction001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set friction to 0.8.
     * @tc.expected: Pattern friction equals 0.8.
     */
    std::optional<double> friction = 0.8;
    WaterFlowModelStatic::SetFriction(AceType::RawPtr(frameNode_), friction);
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 0.8);

    /**
     * @tc.steps: step2. Set friction to 1.0.
     * @tc.expected: Pattern friction equals 1.0.
     */
    friction = 1.0;
    WaterFlowModelStatic::SetFriction(AceType::RawPtr(frameNode_), friction);
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 1.0);

    /**
     * @tc.steps: step3. Reset friction with nullopt.
     * @tc.expected: Friction is set to default value.
     */
    friction.reset();
    WaterFlowModelStatic::SetFriction(AceType::RawPtr(frameNode_), friction);
    EXPECT_NEAR(pattern_->GetFriction(), 0.6, 0.0000001);
}

/**
 * @tc.name: SetFriction002
 * @tc.desc: Test SetFriction with boundary values
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetFriction002, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set friction to 0.0.
     * @tc.expected: Pattern friction set to 0.0 or clamped.
     */
    std::optional<double> friction = 0.0;
    WaterFlowModelStatic::SetFriction(AceType::RawPtr(frameNode_), friction);
    auto result = pattern_->GetFriction();
    EXPECT_GE(result, 0.0);

    /**
     * @tc.steps: step2. Set friction to 0.5.
     * @tc.expected: Pattern friction equals 0.5.
     */
    friction = 0.5;
    WaterFlowModelStatic::SetFriction(AceType::RawPtr(frameNode_), friction);
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 0.5);
}

/**
 * @tc.name: SetCachedCount001
 * @tc.desc: Test SetCachedCount with valid values
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetCachedCount001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set cachedCount to 5.
     * @tc.expected: CachedCount equals 5.
     */
    std::optional<int32_t> cachedCount = 5;
    WaterFlowModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), cachedCount);
    EXPECT_EQ(layoutProperty_->GetCachedCountValue(0), 5);

    /**
     * @tc.steps: step2. Set cachedCount to 10.
     * @tc.expected: CachedCount equals 10.
     */
    cachedCount = 10;
    WaterFlowModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), cachedCount);
    EXPECT_EQ(layoutProperty_->GetCachedCountValue(0), 10);

    /**
     * @tc.steps: step3. Set cachedCount to 0.
     * @tc.expected: CachedCount equals 0.
     */
    cachedCount = 0;
    WaterFlowModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), cachedCount);
    EXPECT_EQ(layoutProperty_->GetCachedCountValue(1), 0);
}

/**
 * @tc.name: SetCachedCount002
 * @tc.desc: Test SetCachedCount with negative and reset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetCachedCount002, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set cachedCount to -10.
     * @tc.expected: Negative value clamped to 1.
     */
    std::optional<int32_t> cachedCount = -10;
    WaterFlowModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), cachedCount);
    EXPECT_EQ(layoutProperty_->GetCachedCountValue(0), 1);

    /**
     * @tc.steps: step2. Set cachedCount to -1.
     * @tc.expected: Negative value clamped to 1.
     */
    cachedCount = -1;
    WaterFlowModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), cachedCount);
    EXPECT_EQ(layoutProperty_->GetCachedCountValue(0), 1);

    /**
     * @tc.steps: step3. Reset cachedCount with nullopt.
     * @tc.expected: CachedCount property cleared.
     */
    cachedCount.reset();
    WaterFlowModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), cachedCount);
    EXPECT_FALSE(layoutProperty_->GetCachedCount().has_value());
}

/**
 * @tc.name: SetCachedCountWithShow001
 * @tc.desc: Test SetCachedCount(count, show) with valid values
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetCachedCountWithShow001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set count=4, show=true.
     * @tc.expected: CachedCount=4, ShowCachedItems=true.
     */
    std::optional<int32_t> count = 4;
    std::optional<bool> show = true;
    WaterFlowModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), count, show);
    EXPECT_EQ(layoutProperty_->GetCachedCountValue(0), 4);
    EXPECT_TRUE(layoutProperty_->GetShowCachedItemsValue(false));

    /**
     * @tc.steps: step2. Set count=8, show=false.
     * @tc.expected: CachedCount=8, ShowCachedItems=false.
     */
    count = 8;
    show = false;
    WaterFlowModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), count, show);
    EXPECT_EQ(layoutProperty_->GetCachedCountValue(0), 8);
    EXPECT_FALSE(layoutProperty_->GetShowCachedItemsValue(true));
}

/**
 * @tc.name: SetCachedCountWithShow002
 * @tc.desc: Test SetCachedCount(count, show) with negative and reset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetCachedCountWithShow002, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set count=-5, show=false.
     * @tc.expected: Negative count clamped to 1, ShowCachedItems=false.
     */
    std::optional<int32_t> count = -5;
    std::optional<bool> show = false;
    WaterFlowModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), count, show);
    EXPECT_EQ(layoutProperty_->GetCachedCountValue(0), 1);
    EXPECT_FALSE(layoutProperty_->GetShowCachedItemsValue(true));

    /**
     * @tc.steps: step2. Reset both count and show with nullopt.
     * @tc.expected: Both properties cleared.
     */
    count.reset();
    show.reset();
    WaterFlowModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), count, show);
    EXPECT_FALSE(layoutProperty_->GetCachedCount().has_value());
    EXPECT_FALSE(layoutProperty_->GetShowCachedItems().has_value());
}

/**
 * @tc.name: GetOrCreateWaterFlowSections001
 * @tc.desc: Test GetOrCreateWaterFlowSections create and reuse
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, GetOrCreateWaterFlowSections001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Call GetOrCreateWaterFlowSections.
     * @tc.expected: A valid sections object is returned.
     */
    auto sections = WaterFlowModelStatic::GetOrCreateWaterFlowSections(AceType::RawPtr(frameNode_));
    ASSERT_NE(sections, nullptr);

    /**
     * @tc.steps: step2. Call again.
     * @tc.expected: Returns same sections instance.
     */
    auto sections2 = WaterFlowModelStatic::GetOrCreateWaterFlowSections(AceType::RawPtr(frameNode_));
    EXPECT_EQ(sections, sections2);

    /**
     * @tc.steps: step3. Call with null frameNode.
     * @tc.expected: Returns nullptr.
     */
    auto sections3 = WaterFlowModelStatic::GetOrCreateWaterFlowSections(nullptr);
    EXPECT_EQ(sections3, nullptr);
}

/**
 * @tc.name: SetOnReachStart001
 * @tc.desc: Test SetOnReachStart registers and clears callback
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetOnReachStart001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set onReachStart callback.
     * @tc.expected: Callback is registered on eventHub.
     */
    bool called = false;
    OnReachEvent onReachStart = [&called]() { called = true; };
    WaterFlowModelStatic::SetOnReachStart(AceType::RawPtr(frameNode_), std::move(onReachStart));
    auto eventHub = frameNode_->GetEventHub<ScrollableEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->GetOnReachStart(), nullptr);

    /**
     * @tc.steps: step2. Set nullptr callback to clear.
     * @tc.expected: Callback is cleared.
     */
    WaterFlowModelStatic::SetOnReachStart(AceType::RawPtr(frameNode_), nullptr);
    EXPECT_EQ(eventHub->GetOnReachStart(), nullptr);
}

/**
 * @tc.name: SetOnReachEnd001
 * @tc.desc: Test SetOnReachEnd registers and clears callback
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetOnReachEnd001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set onReachEnd callback.
     * @tc.expected: Callback is registered on eventHub.
     */
    bool called = false;
    OnReachEvent onReachEnd = [&called]() { called = true; };
    WaterFlowModelStatic::SetOnReachEnd(AceType::RawPtr(frameNode_), std::move(onReachEnd));
    auto eventHub = frameNode_->GetEventHub<ScrollableEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->GetOnReachEnd(), nullptr);

    /**
     * @tc.steps: step2. Set nullptr callback to clear.
     * @tc.expected: Callback is cleared.
     */
    WaterFlowModelStatic::SetOnReachEnd(AceType::RawPtr(frameNode_), nullptr);
    EXPECT_EQ(eventHub->GetOnReachEnd(), nullptr);
}

/**
 * @tc.name: SetOnScrollFrameBegin001
 * @tc.desc: Test SetOnScrollFrameBegin registers and clears callback
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetOnScrollFrameBegin001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set onScrollFrameBegin callback.
     * @tc.expected: Callback is registered.
     */
    OnScrollFrameBeginEvent onScrollFrameBegin = [](Dimension offset, ScrollState state) {
        return ScrollFrameResult { .offset = offset };
    };
    WaterFlowModelStatic::SetOnScrollFrameBegin(AceType::RawPtr(frameNode_), std::move(onScrollFrameBegin));
    auto eventHub = frameNode_->GetEventHub<ScrollableEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Set nullptr callback to clear.
     * @tc.expected: No crash, callback cleared.
     */
    WaterFlowModelStatic::SetOnScrollFrameBegin(AceType::RawPtr(frameNode_), nullptr);
    EXPECT_EQ(eventHub->GetOnScrollFrameBegin(), nullptr);
}

/**
 * @tc.name: SetOnScrollIndex001
 * @tc.desc: Test SetOnScrollIndex registers and clears callback
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetOnScrollIndex001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set onScrollIndex callback.
     * @tc.expected: Callback is registered on WaterFlowEventHub.
     */
    int32_t firstCalled = -1;
    int32_t lastCalled = -1;
    ScrollIndexFunc onScrollIndex = [&firstCalled, &lastCalled](int32_t first, int32_t last) {
        firstCalled = first;
        lastCalled = last;
    };
    WaterFlowModelStatic::SetOnScrollIndex(AceType::RawPtr(frameNode_), std::move(onScrollIndex));
    ASSERT_NE(eventHub_, nullptr);
    EXPECT_NE(eventHub_->GetOnScrollIndex(), nullptr);

    /**
     * @tc.steps: step2. Set nullptr callback to clear.
     * @tc.expected: Callback is cleared.
     */
    WaterFlowModelStatic::SetOnScrollIndex(AceType::RawPtr(frameNode_), nullptr);
    EXPECT_EQ(eventHub_->GetOnScrollIndex(), nullptr);
}

/**
 * @tc.name: SetLayoutMode001
 * @tc.desc: Test SetLayoutMode with all layout modes
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetLayoutMode001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set mode to TOP_DOWN.
     * @tc.expected: LayoutMode equals TOP_DOWN.
     */
    WaterFlowModelStatic::SetLayoutMode(AceType::RawPtr(frameNode_), WaterFlowLayoutMode::TOP_DOWN);
    EXPECT_EQ(pattern_->GetLayoutMode(), WaterFlowLayoutMode::TOP_DOWN);

    /**
     * @tc.steps: step2. Set mode to SLIDING_WINDOW.
     * @tc.expected: LayoutMode equals SLIDING_WINDOW.
     */
    WaterFlowModelStatic::SetLayoutMode(AceType::RawPtr(frameNode_), WaterFlowLayoutMode::SLIDING_WINDOW);
    EXPECT_EQ(pattern_->GetLayoutMode(), WaterFlowLayoutMode::SLIDING_WINDOW);

    /**
     * @tc.steps: step3. Set mode back to TOP_DOWN.
     * @tc.expected: LayoutMode equals TOP_DOWN.
     */
    WaterFlowModelStatic::SetLayoutMode(AceType::RawPtr(frameNode_), WaterFlowLayoutMode::TOP_DOWN);
    EXPECT_EQ(pattern_->GetLayoutMode(), WaterFlowLayoutMode::TOP_DOWN);
}

/**
 * @tc.name: SetFooter001
 * @tc.desc: Test SetFooter with valid and null footer
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetFooter001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set a valid footer node.
     * @tc.expected: Pattern hasFooter() returns true.
     */
    auto footerNode = FrameNode::CreateFrameNode("Footer", 101, AceType::MakeRefPtr<Pattern>());
    WaterFlowModelStatic::SetFooter(AceType::RawPtr(frameNode_), footerNode);
    EXPECT_TRUE(pattern_->hasFooter());

    /**
     * @tc.steps: step2. Set footer to null.
     * @tc.expected: CHECK_NULL_VOID early return, hasFooter() unchanged.
     */
    WaterFlowModelStatic::SetFooter(AceType::RawPtr(frameNode_), nullptr);
    EXPECT_TRUE(pattern_->hasFooter());
}

/**
 * @tc.name: SetFooter002
 * @tc.desc: Test SetFooter replaces existing footer
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, SetFooter002, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set first footer node.
     * @tc.expected: hasFooter() returns true.
     */
    auto footerNode1 = FrameNode::CreateFrameNode("Footer1", 201, AceType::MakeRefPtr<Pattern>());
    WaterFlowModelStatic::SetFooter(AceType::RawPtr(frameNode_), footerNode1);
    EXPECT_TRUE(pattern_->hasFooter());

    /**
     * @tc.steps: step2. Set second footer node to replace.
     * @tc.expected: hasFooter() still true with new footer.
     */
    auto footerNode2 = FrameNode::CreateFrameNode("Footer2", 202, AceType::MakeRefPtr<Pattern>());
    WaterFlowModelStatic::SetFooter(AceType::RawPtr(frameNode_), footerNode2);
    EXPECT_TRUE(pattern_->hasFooter());
}

/**
 * @tc.name: ResetFooter001
 * @tc.desc: Test ResetFooter clears existing footer
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, ResetFooter001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set a footer and verify.
     * @tc.expected: hasFooter() returns true.
     */
    auto footerNode = FrameNode::CreateFrameNode("Footer", 102, AceType::MakeRefPtr<Pattern>());
    WaterFlowModelStatic::SetFooter(AceType::RawPtr(frameNode_), footerNode);
    EXPECT_TRUE(pattern_->hasFooter());

    /**
     * @tc.steps: step2. Call ResetFooter.
     * @tc.expected: hasFooter() returns false.
     */
    WaterFlowModelStatic::ResetFooter(AceType::RawPtr(frameNode_));
    EXPECT_FALSE(pattern_->hasFooter());

    /**
     * @tc.steps: step3. Call ResetFooter again when no footer.
     * @tc.expected: No crash, hasFooter() still false.
     */
    WaterFlowModelStatic::ResetFooter(AceType::RawPtr(frameNode_));
    EXPECT_FALSE(pattern_->hasFooter());
}

/**
 * @tc.name: ResetItemLayoutConstraint001
 * @tc.desc: Test ResetItemLayoutConstraint clears all constraints
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, ResetItemLayoutConstraint001, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Set all min/max width/height constraints.
     * @tc.expected: HasItemLayoutConstraint() is true.
     */
    WaterFlowModelStatic::SetItemMinWidth(AceType::RawPtr(frameNode_), CalcLength(100.0_vp));
    WaterFlowModelStatic::SetItemMaxWidth(AceType::RawPtr(frameNode_), CalcLength(200.0_vp));
    WaterFlowModelStatic::SetItemMinHeight(AceType::RawPtr(frameNode_), CalcLength(50.0_vp));
    WaterFlowModelStatic::SetItemMaxHeight(AceType::RawPtr(frameNode_), CalcLength(150.0_vp));
    EXPECT_TRUE(layoutProperty_->HasItemLayoutConstraint());

    /**
     * @tc.steps: step2. Call ResetItemLayoutConstraint.
     * @tc.expected: HasItemLayoutConstraint() is false.
     */
    WaterFlowModelStatic::ResetItemLayoutConstraint(AceType::RawPtr(frameNode_));
    EXPECT_FALSE(layoutProperty_->HasItemLayoutConstraint());
}

/**
 * @tc.name: ResetItemLayoutConstraint002
 * @tc.desc: Test ResetItemLayoutConstraint when no constraints set
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTest, ResetItemLayoutConstraint002, TestSize.Level1)
{
    CreateWaterFlow();
    /**
     * @tc.steps: step1. Verify no constraints initially.
     * @tc.expected: HasItemLayoutConstraint() is false.
     */
    EXPECT_FALSE(layoutProperty_->HasItemLayoutConstraint());

    /**
     * @tc.steps: step2. Call ResetItemLayoutConstraint without setting constraints.
     * @tc.expected: No crash, HasItemLayoutConstraint() still false.
     */
    WaterFlowModelStatic::ResetItemLayoutConstraint(AceType::RawPtr(frameNode_));
    EXPECT_FALSE(layoutProperty_->HasItemLayoutConstraint());
}
} // namespace OHOS::Ace::NG