/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"

namespace OHOS::Ace::NG {

class WaterFlowModelNGTest : public WaterFlowTestNg {};

/**
 * @tc.name: LayoutDirection001
 * @tc.desc: Test GetLayoutDirection / SetLayoutDirection with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, LayoutDirection001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Check default layout direction.
     * @tc.expected: Default is COLUMN.
     */
    EXPECT_EQ(WaterFlowModelNG::GetLayoutDirection(node), FlexDirection::COLUMN);

    /**
     * @tc.steps: step2. Set direction to ROW and read back.
     * @tc.expected: Direction equals ROW.
     */
    WaterFlowModelNG::SetLayoutDirection(node, FlexDirection::ROW);
    EXPECT_EQ(WaterFlowModelNG::GetLayoutDirection(node), FlexDirection::ROW);

    /**
     * @tc.steps: step3. Reset direction with nullopt.
     * @tc.expected: Direction returns default COLUMN.
     */
    WaterFlowModelNG::SetLayoutDirection(node, std::nullopt);
    EXPECT_EQ(WaterFlowModelNG::GetLayoutDirection(node), FlexDirection::COLUMN);
}

/**
 * @tc.name: ColumnsTemplate001
 * @tc.desc: Test GetColumnsTemplate / SetColumnsTemplate with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, ColumnsTemplate001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Check default columns template.
     * @tc.expected: Default is "1fr".
     */
    EXPECT_EQ(WaterFlowModelNG::GetColumnsTemplate(node), "1fr");

    /**
     * @tc.steps: step2. Set columns template to "1fr 1fr" and read back.
     * @tc.expected: Template equals "1fr 1fr".
     */
    WaterFlowModelNG::SetColumnsTemplate(node, "1fr 1fr");
    EXPECT_EQ(WaterFlowModelNG::GetColumnsTemplate(node), "1fr 1fr");

    /**
     * @tc.steps: step3. Set empty string.
     * @tc.expected: Falls back to "1fr".
     */
    WaterFlowModelNG::SetColumnsTemplate(node, "");
    EXPECT_EQ(WaterFlowModelNG::GetColumnsTemplate(node), "1fr");
}

/**
 * @tc.name: RowsTemplate001
 * @tc.desc: Test GetRowsTemplate / SetRowsTemplate with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, RowsTemplate001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Check default rows template.
     * @tc.expected: Default is "1fr".
     */
    EXPECT_EQ(WaterFlowModelNG::GetRowsTemplate(node), "1fr");

    /**
     * @tc.steps: step2. Set rows template to "1fr 2fr" and read back.
     * @tc.expected: Template equals "1fr 2fr".
     */
    WaterFlowModelNG::SetRowsTemplate(node, "1fr 2fr");
    EXPECT_EQ(WaterFlowModelNG::GetRowsTemplate(node), "1fr 2fr");

    /**
     * @tc.steps: step3. Set empty string.
     * @tc.expected: Falls back to "1fr".
     */
    WaterFlowModelNG::SetRowsTemplate(node, "");
    EXPECT_EQ(WaterFlowModelNG::GetRowsTemplate(node), "1fr");
}

/**
 * @tc.name: ColumnsGap001
 * @tc.desc: Test GetColumnsGap / SetColumnsGap with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, ColumnsGap001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Check default columns gap.
     * @tc.expected: Default is 0.
     */
    EXPECT_FLOAT_EQ(WaterFlowModelNG::GetColumnsGap(node), 0.0f);

    /**
     * @tc.steps: step2. Set columns gap to 16 and read back.
     * @tc.expected: Gap value is 16.
     */
    WaterFlowModelNG::SetColumnsGap(node, Dimension(16.0f));
    EXPECT_FLOAT_EQ(WaterFlowModelNG::GetColumnsGap(node), 16.0f);
}

/**
 * @tc.name: RowsGap001
 * @tc.desc: Test GetRowsGap / SetRowsGap with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, RowsGap001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Check default rows gap.
     * @tc.expected: Default is 0.
     */
    EXPECT_FLOAT_EQ(WaterFlowModelNG::GetRowsGap(node), 0.0f);

    /**
     * @tc.steps: step2. Set rows gap to 8 and read back.
     * @tc.expected: Gap value is 8.
     */
    WaterFlowModelNG::SetRowsGap(node, Dimension(8.0f));
    EXPECT_FLOAT_EQ(WaterFlowModelNG::GetRowsGap(node), 8.0f);
}

/**
 * @tc.name: ScrollEnabled001
 * @tc.desc: Test GetScrollEnabled / SetScrollEnabled with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, ScrollEnabled001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Check default scroll enabled.
     * @tc.expected: Default is true.
     */
    EXPECT_TRUE(WaterFlowModelNG::GetScrollEnabled(node));

    /**
     * @tc.steps: step2. Set scroll enabled to false and read back.
     * @tc.expected: ScrollEnabled is false.
     */
    WaterFlowModelNG::SetScrollEnabled(node, false);
    EXPECT_FALSE(WaterFlowModelNG::GetScrollEnabled(node));

    /**
     * @tc.steps: step3. Set scroll enabled back to true.
     * @tc.expected: ScrollEnabled is true.
     */
    WaterFlowModelNG::SetScrollEnabled(node, true);
    EXPECT_TRUE(WaterFlowModelNG::GetScrollEnabled(node));
}

/**
 * @tc.name: NestedScroll001
 * @tc.desc: Test GetNestedScroll / SetNestedScroll with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, NestedScroll001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Set nested scroll options.
     * @tc.expected: Options set correctly.
     */
    NestedScrollOptions nestedOpt;
    nestedOpt.forward = NestedScrollMode::SELF_FIRST;
    nestedOpt.backward = NestedScrollMode::PARENT_FIRST;
    WaterFlowModelNG::SetNestedScroll(node, nestedOpt);
    auto result = WaterFlowModelNG::GetNestedScroll(node);
    EXPECT_EQ(result.forward, NestedScrollMode::SELF_FIRST);
    EXPECT_EQ(result.backward, NestedScrollMode::PARENT_FIRST);
}

/**
 * @tc.name: Friction001
 * @tc.desc: Test GetFriction / SetFriction with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, Friction001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Set friction to 0.8.
     * @tc.expected: Friction equals 0.8.
     */
    WaterFlowModelNG::SetFriction(node, 0.8);
    EXPECT_NEAR(WaterFlowModelNG::GetFriction(node), 0.8, 0.001);

    /**
     * @tc.steps: step2. Reset friction with nullopt (-1.0 triggers default).
     * @tc.expected: Friction returns default value.
     */
    WaterFlowModelNG::SetFriction(node, std::nullopt);
    EXPECT_NEAR(WaterFlowModelNG::GetFriction(node), 0.6, 0.0000001);
}

/**
 * @tc.name: CachedCount001
 * @tc.desc: Test GetCachedCount / SetCachedCount with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, CachedCount001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Set cached count to 5.
     * @tc.expected: CachedCount equals 5.
     */
    WaterFlowModelNG::SetCachedCount(node, 5);
    EXPECT_EQ(WaterFlowModelNG::GetCachedCount(node), 5);

    /**
     * @tc.steps: step2. Reset cached count with nullopt.
     * @tc.expected: CachedCount returns default.
     */
    WaterFlowModelNG::SetCachedCount(node, std::nullopt);
    EXPECT_EQ(WaterFlowModelNG::GetCachedCount(node), 1);
}

/**
 * @tc.name: ShowCached001
 * @tc.desc: Test GetShowCached / SetShowCached with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, ShowCached001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Check default show cached.
     * @tc.expected: Default is false.
     */
    EXPECT_EQ(WaterFlowModelNG::GetShowCached(node), 0);

    /**
     * @tc.steps: step2. Set show cached to true.
     * @tc.expected: ShowCached is true (1).
     */
    WaterFlowModelNG::SetShowCached(node, true);
    EXPECT_EQ(WaterFlowModelNG::GetShowCached(node), 1);
}

/**
 * @tc.name: ScrollBarMode001
 * @tc.desc: Test GetScrollBarMode / SetScrollBarMode with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, ScrollBarMode001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Set scroll bar mode to ON.
     * @tc.expected: Mode equals ON.
     */
    WaterFlowModelNG::SetScrollBarMode(node, DisplayMode::ON);
    EXPECT_EQ(WaterFlowModelNG::GetScrollBarMode(node), static_cast<int32_t>(DisplayMode::ON));

    /**
     * @tc.steps: step2. Set scroll bar mode to OFF.
     * @tc.expected: Mode equals OFF.
     */
    WaterFlowModelNG::SetScrollBarMode(node, DisplayMode::OFF);
    EXPECT_EQ(WaterFlowModelNG::GetScrollBarMode(node), static_cast<int32_t>(DisplayMode::OFF));
}

/**
 * @tc.name: EdgeEffect001
 * @tc.desc: Test GetEdgeEffect / SetEdgeEffect with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, EdgeEffect001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Set edge effect to SPRING.
     * @tc.expected: EdgeEffect equals SPRING.
     */
    WaterFlowModelNG::SetEdgeEffect(node, EdgeEffect::SPRING, true);
    EXPECT_EQ(WaterFlowModelNG::GetEdgeEffect(node), static_cast<int32_t>(EdgeEffect::SPRING));
    EXPECT_EQ(WaterFlowModelNG::GetEdgeEffectAlways(node), 1);

    /**
     * @tc.steps: step2. Set edge effect to FADE.
     * @tc.expected: EdgeEffect equals FADE.
     */
    WaterFlowModelNG::SetEdgeEffect(node, EdgeEffect::FADE, false);
    EXPECT_EQ(WaterFlowModelNG::GetEdgeEffect(node), static_cast<int32_t>(EdgeEffect::FADE));
    EXPECT_EQ(WaterFlowModelNG::GetEdgeEffectAlways(node), 0);
}

/**
 * @tc.name: EffectEdge001
 * @tc.desc: Test GetEffectEdge with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, EffectEdge001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Set edge effect with EffectEdge::START.
     * @tc.expected: EffectEdge equals START.
     */
    WaterFlowModelNG::SetEdgeEffect(node, EdgeEffect::SPRING, true, EffectEdge::START);
    EXPECT_EQ(WaterFlowModelNG::GetEffectEdge(node), EffectEdge::START);

    /**
     * @tc.steps: step2. Set edge effect with EffectEdge::ALL.
     * @tc.expected: EffectEdge equals ALL.
     */
    WaterFlowModelNG::SetEdgeEffect(node, EdgeEffect::SPRING, true, EffectEdge::ALL);
    EXPECT_EQ(WaterFlowModelNG::GetEffectEdge(node), EffectEdge::ALL);
}

/**
 * @tc.name: ItemMinWidth001
 * @tc.desc: Test GetItemMinWidth / SetItemMinWidth with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, ItemMinWidth001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Check default min width.
     * @tc.expected: Default is 0.
     */
    EXPECT_EQ(WaterFlowModelNG::GetItemMinWidth(node), Dimension(0.0f));

    /**
     * @tc.steps: step2. Set min width to 100vp with value.
     * @tc.expected: MinWidth dimension matches.
     */
    WaterFlowModelNG::SetItemMinWidth(node, Dimension(100.0f, DimensionUnit::VP));
    auto result = WaterFlowModelNG::GetItemMinWidth(node);
    EXPECT_FLOAT_EQ(result.Value(), 100.0f);

    /**
     * @tc.steps: step3. Update min width to a different value.
     * @tc.expected: New value applies.
     */
    WaterFlowModelNG::SetItemMinWidth(node, Dimension(200.0f, DimensionUnit::VP));
    EXPECT_FLOAT_EQ(WaterFlowModelNG::GetItemMinWidth(node).Value(), 200.0f);
}

/**
 * @tc.name: ItemMaxWidth001
 * @tc.desc: Test GetItemMaxWidth / SetItemMaxWidth with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, ItemMaxWidth001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Check default max width.
     * @tc.expected: Default is 0.
     */
    EXPECT_EQ(WaterFlowModelNG::GetItemMaxWidth(node), Dimension(0.0f));

    /**
     * @tc.steps: step2. Set max width to 200vp.
     * @tc.expected: MaxWidth dimension matches.
     */
    WaterFlowModelNG::SetItemMaxWidth(node, Dimension(200.0f, DimensionUnit::VP));
    auto result = WaterFlowModelNG::GetItemMaxWidth(node);
    EXPECT_FLOAT_EQ(result.Value(), 200.0f);

    /**
     * @tc.steps: step3. Update max width to a different value.
     * @tc.expected: New value applies.
     */
    WaterFlowModelNG::SetItemMaxWidth(node, Dimension(300.0f, DimensionUnit::VP));
    EXPECT_FLOAT_EQ(WaterFlowModelNG::GetItemMaxWidth(node).Value(), 300.0f);
}

/**
 * @tc.name: ItemMinHeight001
 * @tc.desc: Test GetItemMinHeight / SetItemMinHeight with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, ItemMinHeight001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Check default min height.
     * @tc.expected: Default is 0.
     */
    EXPECT_EQ(WaterFlowModelNG::GetItemMinHeight(node), Dimension(0.0f));

    /**
     * @tc.steps: step2. Set min height to 50vp.
     * @tc.expected: MinHeight dimension matches.
     */
    WaterFlowModelNG::SetItemMinHeight(node, Dimension(50.0f, DimensionUnit::VP));
    auto result = WaterFlowModelNG::GetItemMinHeight(node);
    EXPECT_FLOAT_EQ(result.Value(), 50.0f);

    /**
     * @tc.steps: step3. Update min height to a different value.
     * @tc.expected: New value applies.
     */
    WaterFlowModelNG::SetItemMinHeight(node, Dimension(80.0f, DimensionUnit::VP));
    EXPECT_FLOAT_EQ(WaterFlowModelNG::GetItemMinHeight(node).Value(), 80.0f);
}

/**
 * @tc.name: ItemMaxHeight001
 * @tc.desc: Test GetItemMaxHeight / SetItemMaxHeight with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, ItemMaxHeight001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Check default max height.
     * @tc.expected: Default is 0.
     */
    EXPECT_EQ(WaterFlowModelNG::GetItemMaxHeight(node), Dimension(0.0f));

    /**
     * @tc.steps: step2. Set max height to 150vp.
     * @tc.expected: MaxHeight dimension matches.
     */
    WaterFlowModelNG::SetItemMaxHeight(node, Dimension(150.0f, DimensionUnit::VP));
    auto result = WaterFlowModelNG::GetItemMaxHeight(node);
    EXPECT_FLOAT_EQ(result.Value(), 150.0f);

    /**
     * @tc.steps: step3. Update max height to a different value.
     * @tc.expected: New value applies.
     */
    WaterFlowModelNG::SetItemMaxHeight(node, Dimension(250.0f, DimensionUnit::VP));
    EXPECT_FLOAT_EQ(WaterFlowModelNG::GetItemMaxHeight(node).Value(), 250.0f);
}

/**
 * @tc.name: ItemFillPolicy001
 * @tc.desc: Test GetItemFillPolicy / SetItemFillPolicy / ResetItemFillPolicy with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, ItemFillPolicy001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Check default fill policy.
     * @tc.expected: Default is -1 (no value).
     */
    EXPECT_EQ(WaterFlowModelNG::GetItemFillPolicy(node), -1);

    /**
     * @tc.steps: step2. Set fill policy to STRETCH.
     * @tc.expected: Fill policy matches.
     */
    WaterFlowModelNG::SetItemFillPolicy(node, PresetFillType::BREAKPOINT_DEFAULT);
    EXPECT_EQ(WaterFlowModelNG::GetItemFillPolicy(node), static_cast<int32_t>(PresetFillType::BREAKPOINT_DEFAULT));

    /**
     * @tc.steps: step3. Reset fill policy.
     * @tc.expected: Fill policy returns -1.
     */
    WaterFlowModelNG::ResetItemFillPolicy(node);
    EXPECT_EQ(WaterFlowModelNG::GetItemFillPolicy(node), -1);
}

/**
 * @tc.name: LayoutMode001
 * @tc.desc: Test GetLayoutMode / SetLayoutMode with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, LayoutMode001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Check default layout mode.
     * @tc.expected: Default is TOP_DOWN.
     */
    EXPECT_EQ(WaterFlowModelNG::GetLayoutMode(node), WaterFlowLayoutMode::TOP_DOWN);

    /**
     * @tc.steps: step2. Set layout mode to SLIDING_WINDOW.
     * @tc.expected: Mode equals SLIDING_WINDOW.
     */
    WaterFlowModelNG::SetLayoutMode(node, WaterFlowLayoutMode::SLIDING_WINDOW);
    EXPECT_EQ(WaterFlowModelNG::GetLayoutMode(node), WaterFlowLayoutMode::SLIDING_WINDOW);

    /**
     * @tc.steps: step3. Set layout mode back to TOP_DOWN.
     * @tc.expected: Mode equals TOP_DOWN.
     */
    WaterFlowModelNG::SetLayoutMode(node, WaterFlowLayoutMode::TOP_DOWN);
    EXPECT_EQ(WaterFlowModelNG::GetLayoutMode(node), WaterFlowLayoutMode::TOP_DOWN);
}

/**
 * @tc.name: Footer001
 * @tc.desc: Test hasFooter / SetWaterflowFooter with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, Footer001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Check default no footer.
     * @tc.expected: hasFooter returns false.
     */
    EXPECT_FALSE(WaterFlowModelNG::hasFooter(node));

    /**
     * @tc.steps: step2. Set footer node.
     * @tc.expected: hasFooter returns true.
     */
    auto footerNode = FrameNode::CreateFrameNode("Footer", 201, AceType::MakeRefPtr<Pattern>());
    WaterFlowModelNG::SetWaterflowFooter(node, AceType::RawPtr(footerNode));
    EXPECT_TRUE(WaterFlowModelNG::hasFooter(node));
}

/**
 * @tc.name: FlingSpeedLimit001
 * @tc.desc: Test SetFlingSpeedLimit with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, FlingSpeedLimit001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Set fling speed limit.
     * @tc.expected: Speed limit value matches.
     */
    WaterFlowModelNG::SetFlingSpeedLimit(node, 5000.0);
    auto speed = ScrollableModelNG::GetMaxFlingSpeed(node);
    EXPECT_FLOAT_EQ(speed, 5000.0f);
}

/**
 * @tc.name: ScrollBarColor001
 * @tc.desc: Test GetScrollBarColor / SetScrollBarColor with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, ScrollBarColor001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Set scroll bar color to red.
     * @tc.expected: Color value matches.
     */
    WaterFlowModelNG::SetScrollBarColor(node, "#FF0000");
    auto color = WaterFlowModelNG::GetScrollBarColor(node);
    EXPECT_NE(color, 0u);
}

/**
 * @tc.name: ScrollBarWidth001
 * @tc.desc: Test GetScrollBarWidth / SetScrollBarWidth with FrameNode*
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, ScrollBarWidth001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Set scroll bar width.
     * @tc.expected: Width value is non-zero.
     */
    WaterFlowModelNG::SetScrollBarWidth(node, "10vp");
    auto width = WaterFlowModelNG::GetScrollBarWidth(node);
    EXPECT_GT(width, 0.0f);
}

/**
 * @tc.name: ColumnsGapOptional001
 * @tc.desc: Test SetColumnsGap with optional<Dimension> overload
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, ColumnsGapOptional001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Set columns gap with optional value.
     * @tc.expected: Gap set correctly.
     */
    std::optional<Dimension> gap = Dimension(12.0f);
    WaterFlowModelNG::SetColumnsGap(node, gap);
    EXPECT_FLOAT_EQ(WaterFlowModelNG::GetColumnsGap(node), 12.0f);

    /**
     * @tc.steps: step2. Reset columns gap with nullopt.
     * @tc.expected: Gap reset.
     */
    gap.reset();
    WaterFlowModelNG::SetColumnsGap(node, gap);
    EXPECT_FLOAT_EQ(WaterFlowModelNG::GetColumnsGap(node), 0.0f);
}

/**
 * @tc.name: RowsGapOptional001
 * @tc.desc: Test SetRowsGap with optional<Dimension> overload
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModelNGTest, RowsGapOptional001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    auto* node = AceType::RawPtr(frameNode_);

    /**
     * @tc.steps: step1. Set rows gap with optional value.
     * @tc.expected: Gap set correctly.
     */
    std::optional<Dimension> gap = Dimension(10.0f);
    WaterFlowModelNG::SetRowsGap(node, gap);
    EXPECT_FLOAT_EQ(WaterFlowModelNG::GetRowsGap(node), 10.0f);

    /**
     * @tc.steps: step2. Reset rows gap with nullopt.
     * @tc.expected: Gap reset.
     */
    gap.reset();
    WaterFlowModelNG::SetRowsGap(node, gap);
    EXPECT_FLOAT_EQ(WaterFlowModelNG::GetRowsGap(node), 0.0f);
}
} // namespace OHOS::Ace::NG
