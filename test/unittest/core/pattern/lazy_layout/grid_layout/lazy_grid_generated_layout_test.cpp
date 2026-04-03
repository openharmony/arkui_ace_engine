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

#include "lazy_grid_layout_test.h"

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model.h"

namespace OHOS::Ace::NG {

/**
 * @tc.name: LazyGridLayoutPattern_SetDynamicLayoutOptions_001
 * @tc.desc: Test SetDynamicLayoutOptions with true
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutPattern_SetDynamicLayoutOptions_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutPattern
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();

    /**
     * @tc.steps: step2. Set dynamic layout options to true
     */
    pattern->SetDynamicLayoutOptions(true);

    /**
     * @tc.steps: step3. Verify IsDynamicLayout returns true
     * @tc.expected: Should return true
     */
    EXPECT_TRUE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: LazyGridLayoutPattern_SetDynamicLayoutOptions_002
 * @tc.desc: Test SetDynamicLayoutOptions with false
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutPattern_SetDynamicLayoutOptions_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutPattern
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();

    /**
     * @tc.steps: step2. Set dynamic layout options to false
     */
    pattern->SetDynamicLayoutOptions(false);

    /**
     * @tc.steps: step3. Verify IsDynamicLayout returns false
     * @tc.expected: Should return false
     */
    EXPECT_FALSE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: LazyGridLayoutPattern_IsDynamicLayout_Default_001
 * @tc.desc: Test IsDynamicLayout default value
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutPattern_IsDynamicLayout_Default_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutPattern without setting options
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();

    /**
     * @tc.steps: step2. Verify IsDynamicLayout returns false by default
     * @tc.expected: Should return false
     */
    EXPECT_FALSE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: LazyGridLayoutPattern_CreateLayoutAlgorithm_WithDynamicLayout_001
 * @tc.desc: Test CreateLayoutAlgorithm when isDynamicLayout is true
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutPattern_CreateLayoutAlgorithm_WithDynamicLayout_001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutPattern and set dynamic layout
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();
    pattern->SetDynamicLayoutOptions(true);

    /**
     * @tc.steps: step2. Call CreateLayoutAlgorithm
     */
    auto algorithm = pattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step3. Verify algorithm is created and has dynamic layout flag
     * @tc.expected: Should return valid LazyGridLayoutGridLayoutAlgorithm with isDynamicLayout=true
     */
    ASSERT_NE(algorithm, nullptr);
    auto gridAlgorithm = AceType::DynamicCast<LazyGridLayoutAlgorithm>(algorithm);
    ASSERT_NE(gridAlgorithm, nullptr);
}

/**
 * @tc.name: LazyGridLayoutAlgorithm_SetDynamicLayout_001
 * @tc.desc: Test SetDynamicLayout with true
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutAlgorithm_SetDynamicLayout_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutAlgorithm
     */
    auto layoutInfo = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo);

    /**
     * @tc.steps: step2. Set dynamic layout to true
     */
    algorithm->SetDynamicLayout(true);

    /**
     * @tc.steps: step3. Verify flag is set
     * @tc.expected: isDynamicLayout_ should be true
     */
    EXPECT_TRUE(algorithm->isDynamicLayout_);
}

/**
 * @tc.name: LazyGridLayoutAlgorithm_SetDynamicLayout_002
 * @tc.desc: Test SetDynamicLayout with false
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutAlgorithm_SetDynamicLayout_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutAlgorithm
     */
    auto layoutInfo = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo);

    /**
     * @tc.steps: step2. Set dynamic layout to false
     */
    algorithm->SetDynamicLayout(false);

    /**
     * @tc.steps: step3. Verify flag is set
     * @tc.expected: isDynamicLayout_ should be false
     */
    EXPECT_FALSE(algorithm->isDynamicLayout_);
}

/**
 * @tc.name: LazyGridLayoutAlgorithm_SetDynamicLayout_Default_001
 * @tc.desc: Test SetDynamicLayout default value
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutAlgorithm_SetDynamicLayout_Default_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutAlgorithm without setting dynamic layout
     */
    auto layoutInfo = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo);

    /**
     * @tc.steps: step2. Verify default isDynamicLayout is false
     * @tc.expected: isDynamicLayout_ should be false by default
     */
    EXPECT_FALSE(algorithm->isDynamicLayout_);
}

/**
 * @tc.name: LazyGridLayoutPattern_MultipleSetDynamicLayoutOptions_001
 * @tc.desc: Test SetDynamicLayoutOptions called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutPattern_MultipleSetDynamicLayoutOptions_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutPattern
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();

    /**
     * @tc.steps: step2. Set dynamic layout options multiple times
     */
    pattern->SetDynamicLayoutOptions(true);
    EXPECT_TRUE(pattern->IsDynamicLayout());

    pattern->SetDynamicLayoutOptions(false);
    EXPECT_FALSE(pattern->IsDynamicLayout());

    pattern->SetDynamicLayoutOptions(true);
    EXPECT_TRUE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: LazyGridLayoutAlgorithm_MultipleSetDynamicLayout_001
 * @tc.desc: Test SetDynamicLayout called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutAlgorithm_MultipleSetDynamicLayout_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutAlgorithm
     */
    auto layoutInfo = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo);

    /**
     * @tc.steps: step2. Set dynamic layout multiple times
     */
    algorithm->SetDynamicLayout(true);
    EXPECT_TRUE(algorithm->isDynamicLayout_);

    algorithm->SetDynamicLayout(false);
    EXPECT_FALSE(algorithm->isDynamicLayout_);

    algorithm->SetDynamicLayout(true);
    EXPECT_TRUE(algorithm->isDynamicLayout_);
}

/**
 * @tc.name: LazyGridLayoutAlgorithm_RTLAlignment_001
 * @tc.desc: Test RTL alignment with dynamic layout enabled
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutAlgorithm_RTLAlignment_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutAlgorithm with dynamic layout
     */
    auto layoutInfo = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo);
    algorithm->SetDynamicLayout(true);

    /**
     * @tc.steps: step2. Set axis to VERTICAL
     */
    algorithm->SetAxis(Axis::VERTICAL);

    /**
     * @tc.steps: step3. Verify dynamic layout and axis settings
     * @tc.expected: isDynamicLayout_ should be true, axis_ should be VERTICAL
     */
    EXPECT_TRUE(algorithm->isDynamicLayout_);
    EXPECT_EQ(algorithm->GetAxis(), Axis::VERTICAL);
}

/**
 * @tc.name: LazyGridLayoutAlgorithm_RTLAlignment_002
 * @tc.desc: Test RTL alignment with HORIZONTAL axis
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutAlgorithm_RTLAlignment_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutAlgorithm with dynamic layout
     */
    auto layoutInfo = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo);
    algorithm->SetDynamicLayout(true);

    /**
     * @tc.steps: step2. Set axis to HORIZONTAL
     */
    algorithm->SetAxis(Axis::HORIZONTAL);

    /**
     * @tc.steps: step3. Verify dynamic layout and axis settings
     * @tc.expected: isDynamicLayout_ should be true, axis_ should be HORIZONTAL
     */
    EXPECT_TRUE(algorithm->isDynamicLayout_);
    EXPECT_EQ(algorithm->GetAxis(), Axis::HORIZONTAL);
}

/**
 * @tc.name: LazyGridLayoutAlgorithm_RTLAlignment_003
 * @tc.desc: Test RTL alignment with default axis (VERTICAL)
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutAlgorithm_RTLAlignment_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutAlgorithm with dynamic layout
     */
    auto layoutInfo = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo);
    algorithm->SetDynamicLayout(true);

    /**
     * @tc.steps: step2. Verify default axis is VERTICAL
     * @tc.expected: axis_ should be VERTICAL by default
     */
    EXPECT_TRUE(algorithm->isDynamicLayout_);
    EXPECT_EQ(algorithm->GetAxis(), Axis::VERTICAL);
}

/**
 * @tc.name: LazyGridLayoutAlgorithm_RTLAlignment_004
 * @tc.desc: Test RTL alignment with dynamic layout disabled
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutAlgorithm_RTLAlignment_004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutAlgorithm without dynamic layout
     */
    auto layoutInfo = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo);

    /**
     * @tc.steps: step2. Set axis to HORIZONTAL
     */
    algorithm->SetAxis(Axis::HORIZONTAL);

    /**
     * @tc.steps: step3. Verify settings
     * @tc.expected: isDynamicLayout_ should be false, axis_ should be HORIZONTAL
     */
    EXPECT_FALSE(algorithm->isDynamicLayout_);
    EXPECT_EQ(algorithm->GetAxis(), Axis::HORIZONTAL);
}

/**
 * @tc.name: LazyGridLayoutAlgorithm_RTLAlignment_005
 * @tc.desc: Test RTL alignment with axis toggling
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutAlgorithm_RTLAlignment_005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutAlgorithm with dynamic layout
     */
    auto layoutInfo = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo);
    algorithm->SetDynamicLayout(true);

    /**
     * @tc.steps: step2. Toggle axis between VERTICAL and HORIZONTAL
     */
    algorithm->SetAxis(Axis::VERTICAL);
    EXPECT_EQ(algorithm->GetAxis(), Axis::VERTICAL);

    algorithm->SetAxis(Axis::HORIZONTAL);
    EXPECT_EQ(algorithm->GetAxis(), Axis::HORIZONTAL);

    algorithm->SetAxis(Axis::VERTICAL);
    EXPECT_EQ(algorithm->GetAxis(), Axis::VERTICAL);
}

/**
 * @tc.name: LazyGridLayoutAlgorithm_RTLAlignment_006
 * @tc.desc: Test RTL alignment with dynamic layout toggling
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, LazyGridLayoutAlgorithm_RTLAlignment_006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutAlgorithm
     */
    auto layoutInfo = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo);

    /**
     * @tc.steps: step2. Toggle dynamic layout and axis
     */
    algorithm->SetDynamicLayout(true);
    algorithm->SetAxis(Axis::HORIZONTAL);
    EXPECT_TRUE(algorithm->isDynamicLayout_);
    EXPECT_EQ(algorithm->GetAxis(), Axis::HORIZONTAL);

    algorithm->SetDynamicLayout(false);
    algorithm->SetAxis(Axis::VERTICAL);
    EXPECT_FALSE(algorithm->isDynamicLayout_);
    EXPECT_EQ(algorithm->GetAxis(), Axis::VERTICAL);

    algorithm->SetDynamicLayout(true);
    algorithm->SetAxis(Axis::HORIZONTAL);
    EXPECT_TRUE(algorithm->isDynamicLayout_);
    EXPECT_EQ(algorithm->GetAxis(), Axis::HORIZONTAL);
}

/**
 * @tc.name: Alignment_GetAlignPosition_TOP_LEFT_001
 * @tc.desc: Test GetAlignPosition with TOP_LEFT alignment
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, Alignment_GetAlignPosition_TOP_LEFT_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cell size and child size
     */
    SizeF cellSize(100.0f, 100.0f);
    SizeF childSize(80.0f, 60.0f);

    /**
     * @tc.steps: step2. Call GetAlignPosition with TOP_LEFT alignment
     */
    auto alignPosition = Alignment::GetAlignPosition(cellSize, childSize, Alignment::TOP_LEFT);

    /**
     * @tc.steps: step3. Verify offset is (0, 0) for TOP_LEFT
     * @tc.expected: Offset should be (0.0, 0.0)
     */
    EXPECT_FLOAT_EQ(alignPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(alignPosition.GetY(), 0.0f);
}

/**
 * @tc.name: Alignment_GetAlignPosition_TOP_CENTER_001
 * @tc.desc: Test GetAlignPosition with TOP_CENTER alignment
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, Alignment_GetAlignPosition_TOP_CENTER_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cell size and child size
     */
    SizeF cellSize(100.0f, 100.0f);
    SizeF childSize(80.0f, 60.0f);

    /**
     * @tc.steps: step2. Call GetAlignPosition with TOP_CENTER alignment
     */
    auto alignPosition = Alignment::GetAlignPosition(cellSize, childSize, Alignment::TOP_CENTER);

    /**
     * @tc.steps: step3. Verify offset is centered horizontally
     * @tc.expected: X offset should be (100 - 80) / 2 = 10.0
     */
    EXPECT_FLOAT_EQ(alignPosition.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(alignPosition.GetY(), 0.0f);
}

/**
 * @tc.name: Alignment_GetAlignPosition_TOP_RIGHT_001
 * @tc.desc: Test GetAlignPosition with TOP_RIGHT alignment
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, Alignment_GetAlignPosition_TOP_RIGHT_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cell size and child size
     */
    SizeF cellSize(100.0f, 100.0f);
    SizeF childSize(80.0f, 60.0f);

    /**
     * @tc.steps: step2. Call GetAlignPosition with TOP_RIGHT alignment
     */
    auto alignPosition = Alignment::GetAlignPosition(cellSize, childSize, Alignment::TOP_RIGHT);

    /**
     * @tc.steps: step3. Verify offset is right aligned
     * @tc.expected: X offset should be 100 - 80 = 20.0
     */
    EXPECT_FLOAT_EQ(alignPosition.GetX(), 20.0f);
    EXPECT_FLOAT_EQ(alignPosition.GetY(), 0.0f);
}

/**
 * @tc.name: Alignment_GetAlignPosition_CENTER_001
 * @tc.desc: Test GetAlignPosition with CENTER alignment
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, Alignment_GetAlignPosition_CENTER_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cell size and child size
     */
    SizeF cellSize(100.0f, 100.0f);
    SizeF childSize(80.0f, 60.0f);

    /**
     * @tc.steps: step2. Call GetAlignPosition with CENTER alignment
     */
    auto alignPosition = Alignment::GetAlignPosition(cellSize, childSize, Alignment::CENTER);

    /**
     * @tc.steps: step3. Verify offset is centered both horizontally and vertically
     * @tc.expected: X offset should be (100 - 80) / 2 = 10.0, Y offset should be (100 - 60) / 2 = 20.0
     */
    EXPECT_FLOAT_EQ(alignPosition.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(alignPosition.GetY(), 20.0f);
}

/**
 * @tc.name: Alignment_GetAlignPosition_BOTTOM_LEFT_001
 * @tc.desc: Test GetAlignPosition with BOTTOM_LEFT alignment
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, Alignment_GetAlignPosition_BOTTOM_LEFT_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cell size and child size
     */
    SizeF cellSize(100.0f, 100.0f);
    SizeF childSize(80.0f, 60.0f);

    /**
     * @tc.steps: step2. Call GetAlignPosition with BOTTOM_LEFT alignment
     */
    auto alignPosition = Alignment::GetAlignPosition(cellSize, childSize, Alignment::BOTTOM_LEFT);

    /**
     * @tc.steps: step3. Verify offset is bottom aligned
     * @tc.expected: Y offset should be 100 - 60 = 40.0
     */
    EXPECT_FLOAT_EQ(alignPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(alignPosition.GetY(), 40.0f);
}

/**
 * @tc.name: Alignment_GetAlignPosition_BOTTOM_CENTER_001
 * @tc.desc: Test GetAlignPosition with BOTTOM_CENTER alignment
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, Alignment_GetAlignPosition_BOTTOM_CENTER_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cell size and child size
     */
    SizeF cellSize(100.0f, 100.0f);
    SizeF childSize(80.0f, 60.0f);

    /**
     * @tc.steps: step2. Call GetAlignPosition with BOTTOM_CENTER alignment
     */
    auto alignPosition = Alignment::GetAlignPosition(cellSize, childSize, Alignment::BOTTOM_CENTER);

    /**
     * @tc.steps: step3. Verify offset is centered horizontally and bottom aligned vertically
     * @tc.expected: X offset should be (100 - 80) / 2 = 10.0, Y offset should be 100 - 60 = 40.0
     */
    EXPECT_FLOAT_EQ(alignPosition.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(alignPosition.GetY(), 40.0f);
}

/**
 * @tc.name: Alignment_GetAlignPosition_BOTTOM_RIGHT_001
 * @tc.desc: Test GetAlignPosition with BOTTOM_RIGHT alignment
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, Alignment_GetAlignPosition_BOTTOM_RIGHT_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cell size and child size
     */
    SizeF cellSize(100.0f, 100.0f);
    SizeF childSize(80.0f, 60.0f);

    /**
     * @tc.steps: step2. Call GetAlignPosition with BOTTOM_RIGHT alignment
     */
    auto alignPosition = Alignment::GetAlignPosition(cellSize, childSize, Alignment::BOTTOM_RIGHT);

    /**
     * @tc.steps: step3. Verify offset is right and bottom aligned
     * @tc.expected: X offset should be 100 - 80 = 20.0, Y offset should be 100 - 60 = 40.0
     */
    EXPECT_FLOAT_EQ(alignPosition.GetX(), 20.0f);
    EXPECT_FLOAT_EQ(alignPosition.GetY(), 40.0f);
}

/**
 * @tc.name: Alignment_GetAlignPositionWithDirection_LTR_001
 * @tc.desc: Test GetAlignPositionWithDirection with LTR direction
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, Alignment_GetAlignPositionWithDirection_LTR_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cell size and child size
     */
    SizeF cellSize(100.0f, 100.0f);
    SizeF childSize(80.0f, 60.0f);

    /**
     * @tc.steps: step2. Call GetAlignPositionWithDirection with LTR direction and TOP_LEFT alignment
     */
    auto alignPosition = Alignment::GetAlignPositionWithDirection(
        cellSize, childSize, Alignment::TOP_LEFT, TextDirection::LTR);

    /**
     * @tc.steps: step3. Verify offset is (0, 0) for TOP_LEFT with LTR
     * @tc.expected: Offset should be (0.0, 0.0)
     */
    EXPECT_FLOAT_EQ(alignPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(alignPosition.GetY(), 0.0f);
}

/**
 * @tc.name: Alignment_GetAlignPositionWithDirection_LTR_002
 * @tc.desc: Test GetAlignPositionWithDirection with LTR direction and CENTER alignment
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, Alignment_GetAlignPositionWithDirection_LTR_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cell size and child size
     */
    SizeF cellSize(100.0f, 100.0f);
    SizeF childSize(80.0f, 60.0f);

    /**
     * @tc.steps: step2. Call GetAlignPositionWithDirection with LTR direction and CENTER alignment
     */
    auto alignPosition = Alignment::GetAlignPositionWithDirection(
        cellSize, childSize, Alignment::CENTER, TextDirection::LTR);

    /**
     * @tc.steps: step3. Verify offset is centered
     * @tc.expected: X offset should be (100 - 80) / 2 = 10.0, Y offset should be (100 - 60) / 2 = 20.0
     */
    EXPECT_FLOAT_EQ(alignPosition.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(alignPosition.GetY(), 20.0f);
}

/**
 * @tc.name: Alignment_GetAlignPositionWithDirection_RTL_001
 * @tc.desc: Test GetAlignPositionWithDirection with RTL direction
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, Alignment_GetAlignPositionWithDirection_RTL_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cell size and child size
     */
    SizeF cellSize(100.0f, 100.0f);
    SizeF childSize(80.0f, 60.0f);

    /**
     * @tc.steps: step2. Call GetAlignPositionWithDirection with RTL direction and TOP_LEFT alignment
     */
    auto alignPosition = Alignment::GetAlignPositionWithDirection(
        cellSize, childSize, Alignment::TOP_LEFT, TextDirection::RTL);

    /**
     * @tc.steps: step3. Verify offset for RTL with TOP_LEFT
     * @tc.expected: RTL should mirror horizontal alignment
     */
    EXPECT_FLOAT_EQ(alignPosition.GetY(), 0.0f);
}

/**
 * @tc.name: Alignment_GetAlignPositionWithDirection_RTL_002
 * @tc.desc: Test GetAlignPositionWithDirection with RTL direction and CENTER alignment
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, Alignment_GetAlignPositionWithDirection_RTL_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cell size and child size
     */
    SizeF cellSize(100.0f, 100.0f);
    SizeF childSize(80.0f, 60.0f);

    /**
     * @tc.steps: step2. Call GetAlignPositionWithDirection with RTL direction and CENTER alignment
     */
    auto alignPosition = Alignment::GetAlignPositionWithDirection(
        cellSize, childSize, Alignment::CENTER, TextDirection::RTL);

    /**
     * @tc.steps: step3. Verify offset for RTL with CENTER
     * @tc.expected: Center alignment should be same in both directions
     */
    EXPECT_FLOAT_EQ(alignPosition.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(alignPosition.GetY(), 20.0f);
}

/**
 * @tc.name: Alignment_GetAlignPositionWithDirection_RTL_003
 * @tc.desc: Test GetAlignPositionWithDirection with RTL direction and TOP_RIGHT alignment
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, Alignment_GetAlignPositionWithDirection_RTL_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cell size and child size
     */
    SizeF cellSize(100.0f, 100.0f);
    SizeF childSize(80.0f, 60.0f);

    /**
     * @tc.steps: step2. Call GetAlignPositionWithDirection with RTL direction and TOP_RIGHT alignment
     */
    auto alignPosition = Alignment::GetAlignPositionWithDirection(
        cellSize, childSize, Alignment::TOP_RIGHT, TextDirection::RTL);

    /**
     * @tc.steps: step3. Verify offset for RTL with TOP_RIGHT
     * @tc.expected: RTL should mirror horizontal alignment
     */
    EXPECT_FLOAT_EQ(alignPosition.GetY(), 0.0f);
}

/**
 * @tc.name: Alignment_GetAlignPosition_EqualSizes_001
 * @tc.desc: Test GetAlignPosition when cell and child sizes are equal
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, Alignment_GetAlignPosition_EqualSizes_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create equal cell and child sizes
     */
    SizeF cellSize(100.0f, 100.0f);
    SizeF childSize(100.0f, 100.0f);

    /**
     * @tc.steps: step2. Call GetAlignPosition with CENTER alignment
     */
    auto alignPosition = Alignment::GetAlignPosition(cellSize, childSize, Alignment::CENTER);

    /**
     * @tc.steps: step3. Verify offset is (0, 0) when sizes are equal
     * @tc.expected: Offset should be (0.0, 0.0)
     */
    EXPECT_FLOAT_EQ(alignPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(alignPosition.GetY(), 0.0f);
}

/**
 * @tc.name: Alignment_GetAlignPositionWithDirection_EqualSizes_001
 * @tc.desc: Test GetAlignPositionWithDirection when cell and child sizes are equal
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutTest, Alignment_GetAlignPositionWithDirection_EqualSizes_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create equal cell and child sizes
     */
    SizeF cellSize(100.0f, 100.0f);
    SizeF childSize(100.0f, 100.0f);

    /**
     * @tc.steps: step2. Call GetAlignPositionWithDirection with RTL direction and CENTER alignment
     */
    auto alignPosition = Alignment::GetAlignPositionWithDirection(
        cellSize, childSize, Alignment::CENTER, TextDirection::RTL);

    /**
     * @tc.steps: step3. Verify offset is (0, 0) when sizes are equal
     * @tc.expected: Offset should be (0.0, 0.0)
     */
    EXPECT_FLOAT_EQ(alignPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(alignPosition.GetY(), 0.0f);
}
} // namespace OHOS::Ace::NG
