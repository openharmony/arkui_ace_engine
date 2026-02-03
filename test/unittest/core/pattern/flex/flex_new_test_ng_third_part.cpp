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
#include "flex_new_test_common.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

/**
 * @tc.name: FlexLayoutAlgorithmDirection001
 * @tc.desc: Test FlexLayoutAlgorithm with different flex directions
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmDirection001, TestSize.Level0)
{
    /**
     * @tc.steps1: Create layout property with ROW direction
     */
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();
    layoutProperty->UpdateFlexDirection(FlexDirection::ROW);

    /**
     * @tc.expected: Direction should be set to ROW
     */
    EXPECT_EQ(layoutProperty->GetFlexDirection().value(), FlexDirection::ROW);

    /**
     * @tc.steps2: Change to COLUMN direction
     */
    layoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    EXPECT_EQ(layoutProperty->GetFlexDirection().value(), FlexDirection::COLUMN);

    /**
     * @tc.steps3: Test ROW_REVERSE
     */
    layoutProperty->UpdateFlexDirection(FlexDirection::ROW_REVERSE);
    EXPECT_EQ(layoutProperty->GetFlexDirection().value(), FlexDirection::ROW_REVERSE);

    /**
     * @tc.steps4: Test COLUMN_REVERSE
     */
    layoutProperty->UpdateFlexDirection(FlexDirection::COLUMN_REVERSE);
    EXPECT_EQ(layoutProperty->GetFlexDirection().value(), FlexDirection::COLUMN_REVERSE);
}

/**
 * @tc.name: FlexLayoutAlgorithmAlign001
 * @tc.desc: Test FlexLayoutAlgorithm with different main axis alignments
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmAlign001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();

    /**
     * @tc.steps1: Test FLEX_START alignment
     */
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    EXPECT_EQ(layoutProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::FLEX_START);

    /**
     * @tc.steps2: Test CENTER alignment
     */
    layoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    EXPECT_EQ(layoutProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::CENTER);

    /**
     * @tc.steps3: Test FLEX_END alignment
     */
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_END);
    EXPECT_EQ(layoutProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::FLEX_END);

    /**
     * @tc.steps4: Test SPACE_BETWEEN alignment
     */
    layoutProperty->UpdateMainAxisAlign(FlexAlign::SPACE_BETWEEN);
    EXPECT_EQ(layoutProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::SPACE_BETWEEN);

    /**
     * @tc.steps5: Test SPACE_AROUND alignment
     */
    layoutProperty->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
    EXPECT_EQ(layoutProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::SPACE_AROUND);
}

/**
 * @tc.name: FlexLayoutAlgorithmCrossAlign001
 * @tc.desc: Test FlexLayoutAlgorithm with different cross axis alignments
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmCrossAlign001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();

    /**
     * @tc.steps1: Test FLEX_START cross axis alignment
     */
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    EXPECT_EQ(layoutProperty->GetCrossAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::FLEX_START);

    /**
     * @tc.steps2: Test CENTER cross axis alignment
     */
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    EXPECT_EQ(layoutProperty->GetCrossAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::CENTER);

    /**
     * @tc.steps3: Test FLEX_END cross axis alignment
     */
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_END);
    EXPECT_EQ(layoutProperty->GetCrossAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::FLEX_END);

    /**
     * @tc.steps4: Test STRETCH cross axis alignment
     */
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::STRETCH);
    EXPECT_EQ(layoutProperty->GetCrossAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::STRETCH);
}

/**
 * @tc.name: FlexLayoutAlgorithmSpace001
 * @tc.desc: Test FlexLayoutAlgorithm with space property
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmSpace001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();

    /**
     * @tc.steps1: Update space with different values
     */
    layoutProperty->UpdateSpace(Dimension(10.0, DimensionUnit::PX));
    auto space = layoutProperty->GetSpaceValue({});
    EXPECT_EQ(space.ConvertToPx(), 10.0f);

    layoutProperty->UpdateSpace(Dimension(20.0, DimensionUnit::PX));
    space = layoutProperty->GetSpaceValue({});
    EXPECT_EQ(space.ConvertToPx(), 20.0f);
}

/**
 * @tc.name: FlexLayoutAlgorithmRTL001
 * @tc.desc: Test FlexLayoutAlgorithm with RTL layout direction
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmRTL001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();

    /**
     * @tc.steps1: Test LTR direction
     */
    layoutProperty->UpdateLayoutDirection(TextDirection::LTR);
    EXPECT_EQ(layoutProperty->GetLayoutDirection(), TextDirection::LTR);

    /**
     * @tc.steps2: Test RTL direction
     */
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_EQ(layoutProperty->GetLayoutDirection(), TextDirection::RTL);

    /**
     * @tc.steps3: Test AUTO direction
     */
    layoutProperty->UpdateLayoutDirection(TextDirection::AUTO);
    EXPECT_EQ(layoutProperty->GetLayoutDirection(), TextDirection::AUTO);
}

/**
 * @tc.name: FlexLayoutAlgorithmClone001
 * @tc.desc: Test FlexLayoutProperty clone functionality
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmClone001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();
    layoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    layoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::STRETCH);

    /**
     * @tc.steps: Clone the property
     */
    auto clonedProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutProperty->Clone());

    /**
     * @tc.expected: Cloned property should have same values
     */
    ASSERT_NE(clonedProperty, nullptr);
    EXPECT_EQ(clonedProperty->GetFlexDirection().value(), FlexDirection::COLUMN);
    EXPECT_EQ(clonedProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::CENTER);
    EXPECT_EQ(clonedProperty->GetCrossAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::STRETCH);
}

/**
 * @tc.name: FlexLayoutAlgorithmReset001
 * @tc.desc: Test FlexLayoutProperty reset functionality
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmReset001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();
    layoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    layoutProperty->UpdateMainAxisAlign(FlexAlign::SPACE_BETWEEN);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::BASELINE);

    /**
     * @tc.steps: Reset the property
     */
    layoutProperty->Reset();

    /**
     * @tc.expected: Property should be reset to default
     */
    EXPECT_FALSE(layoutProperty->GetFlexDirection().has_value());
}

/**
 * @tc.name: FlexLayoutAlgorithmToJson001
 * @tc.desc: Test FlexLayoutProperty ToJsonValue functionality
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmToJson001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();
    layoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    layoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);

    /**
     * @tc.steps: Create JSON from property
     */
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, InspectorFilter());

    /**
     * @tc.expected: Assert FlexDirection and FlexAlign with EXPECT_EQ
     */
    ASSERT_NE(json, nullptr);
    auto flexDirection = json->GetString("direction");
    EXPECT_EQ(flexDirection, "FlexDirection::ROW");
    auto mainAxisAlign = json->GetString("justifyContent");
    EXPECT_EQ(mainAxisAlign.value(), "FlexAlign.Center");
}
} // namespace OHOS::Ace::NG