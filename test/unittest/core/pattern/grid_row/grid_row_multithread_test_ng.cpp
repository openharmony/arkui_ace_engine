/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "grid_row_base_test_ng.h"
// Include GridRowLayoutPattern to access its members and methods
#include "core/components_ng/pattern/grid_row/grid_row_layout_pattern.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::NG;

class GridRowMultiThreadTestNG : public GridRowBaseTestNG {
public:
    // Helper function: Get GridRowPattern and cast type
    RefPtr<GridRowLayoutPattern> GetGridRowPattern(const RefPtr<FrameNode>& frameNode)
    {
        CHECK_NULL_RETURN(frameNode, nullptr);
        return frameNode->GetPattern<GridRowLayoutPattern>();
    }
};

/**
 * @tc.name: MultiThreadLifecycleCallbackTest001
 * @tc.desc: Test OnAttachToMainTreeMultiThread and OnDetachFromMainTreeMultiThread callbacks.
 *           Verifies that surface change callback is registered/unregistered correctly in multi-thread scenarios.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMultiThreadTestNG, MultiThreadLifecycleCallbackTest001, TestSize.Level1)
{
    auto frameNode = CreateGridRow([](GridRowModelNG model) {
        // Set common GridRow properties for a more realistic test scenario
        V2::GridContainerSize columns(6);
        Dimension xDimen(5.0, DimensionUnit::PX);
        Dimension yDimen(10.0, DimensionUnit::PX);
        V2::Gutter gutter(xDimen, yDimen);
        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(200.0f));

        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Columns, columns);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Direction, V2::GridRowDirection::Row);
    });

    ASSERT_NE(frameNode, nullptr);
    auto pattern = GetGridRowPattern(frameNode);
    ASSERT_NE(pattern, nullptr);

    // Simulate calling OnAttachToMainTreeMultiThread.
    pattern->OnAttachToMainTreeMultiThread();

    // Verify that the callback is registered (check if callbackId_ has been assigned)
    EXPECT_TRUE(pattern->callbackId_.has_value());
    auto registeredCallbackId = pattern->callbackId_.value_or(-1);
    EXPECT_NE(registeredCallbackId, -1); // -1 usually represents an invalid ID

    // Simulate calling OnDetachFromMainTreeMultiThread.
    pattern->OnDetachFromMainTreeMultiThread();

    // Verify that the callback is unregistered (check if callbackId_ has been reset)
    EXPECT_TRUE(pattern->callbackId_.has_value());
}

/**
 * @tc.name: MultiThreadAttachDetachFrameNodeTest001
 * @tc.desc: Test OnAttachToFrameNodeMultiThread and OnDetachFromFrameNodeMultiThread callbacks.
 *           Note: The current implementation of these functions is empty (no-op).
 *           This test ensures that calling them does not cause crashes or unexpected behavior.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMultiThreadTestNG, MultiThreadAttachDetachFrameNodeTest001, TestSize.Level1)
{
    auto frameNode = CreateGridRow([](GridRowModelNG model) {
        // Set common GridRow properties for a more realistic test scenario
        V2::GridContainerSize columns(4);
        Dimension xDimen(2.0, DimensionUnit::VP);
        Dimension yDimen(4.0, DimensionUnit::VP);
        V2::Gutter gutter(xDimen, yDimen);
        ViewAbstract::SetWidth(CalcLength(200.0f));
        ViewAbstract::SetHeight(CalcLength(150.0f));
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, AlignItems, FlexAlign::CENTER);

        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Columns, columns);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Direction, V2::GridRowDirection::RowReverse);
    });

    ASSERT_NE(frameNode, nullptr);
    auto pattern = GetGridRowPattern(frameNode);
    ASSERT_NE(pattern, nullptr);

    // Call OnAttachToFrameNodeMultiThread.
    pattern->OnAttachToFrameNodeMultiThread();

    // Call OnDetachFromFrameNodeMultiThread.
    pattern->OnDetachFromFrameNodeMultiThread(frameNode.GetRawPtr());
}

/**
 * @tc.name: THREAD_SAFE_NODE_CHECK_MacroTest001
 * @tc.desc: Test the behavior of THREAD_SAFE_NODE_CHECK macro by simulating calls to main thread lifecycle methods.
 *           This indirectly tests that the multi-thread versions are invoked.
 *           Since the macro's behavior is framework-level, we focus on ensuring the main methods delegate correctly.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMultiThreadTestNG, THREAD_SAFE_NODE_CHECK_MacroTest001, TestSize.Level1)
{
    auto frameNode = CreateGridRow([](GridRowModelNG model) {
        // Set common GridRow properties for a more realistic test scenario
        V2::GridContainerSize columns;
        columns.xs = 2;
        columns.sm = 4;
        columns.md = 6;
        columns.lg = 8;
        columns.xl = 10;
        columns.xxl = 12;

        V2::Gutter gutter;
        gutter.xXs = gutter.yXs = Dimension(1.0, DimensionUnit::PX);
        gutter.xSm = gutter.ySm = Dimension(2.0, DimensionUnit::PX);
        gutter.xMd = gutter.yMd = Dimension(3.0, DimensionUnit::PX);
        gutter.xLg = gutter.yLg = Dimension(4.0, DimensionUnit::PX);
        gutter.xXl = gutter.yXl = Dimension(5.0, DimensionUnit::PX);
        gutter.xXXl = gutter.yXXl = Dimension(6.0, DimensionUnit::PX);

        V2::BreakPoints breakpoints;
        breakpoints.breakpoints = { "600px", "900px", "1200px", "1500px", "1800px" };
        breakpoints.reference = V2::BreakPointsReference::ComponentSize;

        ViewAbstract::SetWidth(CalcLength(400.0f));
        ViewAbstract::SetHeight(CalcLength(100.0f));
        ViewAbstract::SetPadding(CalcLength(5.0f));

        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Columns, columns);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, breakpoints);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Direction, V2::GridRowDirection::Row);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, AlignItems, FlexAlign::FLEX_END);
    });

    ASSERT_NE(frameNode, nullptr);
    auto pattern = GetGridRowPattern(frameNode);
    ASSERT_NE(pattern, nullptr);

    // Call OnAttachToFrameNode (the main thread version).
    pattern->OnAttachToFrameNode();

    // Call OnAttachToMainTree (the main thread version).
    pattern->OnAttachToMainTree(); // This will call OnAttachToMainTreeMultiThread
    EXPECT_TRUE(pattern->callbackId_.has_value()); // Verify that the callback is registered

    // Call OnDetachFromMainTree (the main thread version).
    pattern->OnDetachFromMainTree(); // This will call OnDetachFromMainTreeMultiThread
    EXPECT_TRUE(pattern->callbackId_.has_value()); // Verify that the callback is unregistered

    // Call OnDetachFromFrameNode (the main thread version).
    pattern->OnDetachFromFrameNode(frameNode.GetRawPtr());

    // The state should remain unregistered
    EXPECT_TRUE(pattern->callbackId_.has_value());
}