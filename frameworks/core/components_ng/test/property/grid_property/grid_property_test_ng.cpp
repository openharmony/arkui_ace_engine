/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include <optional>
#include <string>
#include <vector>
#include <cstddef>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "core/components_ng/property/grid_property.h"
#include "core/components/common/layout/grid_container_info.h"
#include "core/components_ng/pattern/grid_container/grid_container_layout_property.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components/common/layout/grid_column_info.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid_container/grid_container_model_ng.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SPANONE = 10;
constexpr int32_t SPANTWO = -10;
constexpr int32_t OFFSETONE = 5;
constexpr int32_t OFFSETTWO = -5;
Dimension TESTWIDTH {1.0, DimensionUnit::VP};
Dimension TESTLEFT {2.0, DimensionUnit::VP};
Dimension TESTRIGHT {3.0, DimensionUnit::VP};
} // namespace

class GridPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: GridPropertyTest001
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback UpdateSpan.push span is -10.
     * @tc.expected: step2. Return result is false.
     */
    GridProperty testGridProperty;
    int32_t index = 1;
    auto type = static_cast<GridSizeType>(index);

    bool result = testGridProperty.UpdateSpan(SPANTWO, type);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GridPropertyTest002
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback UpdateSpan.push span is 10.
     * @tc.expected: step2. Return result is true.
     */
    GridProperty testGridProperty;
    int32_t index = 1;
    auto type = static_cast<GridSizeType>(index);

    bool result = testGridProperty.UpdateSpan(SPANONE, type);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GridPropertyTest003
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback UpdateOffset.push offset is 5.
     * @tc.expected: step2. Return result is true.
     */
    GridProperty testGridProperty;
    int32_t index = 1;
    auto type = static_cast<GridSizeType>(index);

    bool result = testGridProperty.UpdateOffset(OFFSETONE, type);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GridPropertyTest004
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback UpdateOffset.push offset is -5.
     * @tc.expected: step2. Return result is true.
     */
    GridProperty testGridProperty;
    int32_t index = 1;
    auto type = static_cast<GridSizeType>(index);

    bool result = testGridProperty.UpdateOffset(OFFSETTWO, type);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GridPropertyTest005
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback UpdateOffset.push typedPropertySet_ is not null.
     * @tc.expected: step2. Return result is true.
     */
    GridProperty testGridProperty;
    GridTypedProperty testGridTypedProperty0 {GridSizeType::XS, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty1 {GridSizeType::SM, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty2 {GridSizeType::MD, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty3 {GridSizeType::LG, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty4 {GridSizeType::XL, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty5 {GridSizeType::UNDEFINED, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty0);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty1);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty2);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty3);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty4);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty5);
    int32_t index = 1;
    auto type = static_cast<GridSizeType>(index);

    bool result = testGridProperty.UpdateOffset(OFFSETTWO, type);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GridPropertyTest006
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback UpdateSpan.push typedPropertySet_ is not null.
     * @tc.expected: step2. Return result is true.
     */
    GridProperty testGridProperty;
    GridTypedProperty testGridTypedProperty0 {GridSizeType::XS, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty1 {GridSizeType::SM, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty2 {GridSizeType::MD, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty3 {GridSizeType::LG, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty4 {GridSizeType::XL, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty5 {GridSizeType::UNDEFINED, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty0);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty1);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty2);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty3);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty4);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty5);
    int32_t index = 1;
    auto type = static_cast<GridSizeType>(index);

    bool result = testGridProperty.UpdateSpan(SPANONE, type);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GridPropertyTest007
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback UpdateOffset.push offset is -5.
     * @tc.expected: step2. Return result is true.
     */
    GridProperty testGridProperty;
    GridTypedProperty testGridTypedProperty0 {GridSizeType::XS, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty1 {GridSizeType::SM, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty2 {GridSizeType::MD, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty3 {GridSizeType::LG, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty4 {GridSizeType::XL, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty5 {GridSizeType::UNDEFINED, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty0);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty1);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty2);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty3);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty4);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty5);
    int32_t index = 1;
    auto type = static_cast<GridSizeType>(index);

    testGridProperty.UpdateOffset(OFFSETTWO, type);
    bool result = testGridProperty.SetOffset(type, OFFSETTWO);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GridPropertyTest008
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback SetSpan.push offset is DEFAULT_GRID_SPAN.
     * @tc.expected: step2. Return result is false.
     */
    GridProperty testGridProperty;
    GridTypedProperty testGridTypedProperty0 {GridSizeType::XS, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty1 {GridSizeType::SM, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty2 {GridSizeType::MD, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty3 {GridSizeType::LG, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty4 {GridSizeType::XL, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty5 {GridSizeType::UNDEFINED, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty0);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty1);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty2);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty3);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty4);
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty5);
    int32_t index = 1;
    auto type = static_cast<GridSizeType>(index);

    testGridProperty.UpdateSpan(DEFAULT_GRID_SPAN, type);
    bool result = testGridProperty.SetSpan(type, DEFAULT_GRID_SPAN);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GridPropertyTest009
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback ToJsonValue.push gridInfo_ is null.
     * @tc.expected: step2. Return expected results.
     */
    GridProperty testGridProperty;
    int32_t index = 1;
    auto type = static_cast<GridSizeType>(index);
    bool result = testGridProperty.UpdateSpan(DEFAULT_GRID_SPAN, type);
    EXPECT_TRUE(result);

    auto json = JsonUtil::Create(true);
    testGridProperty.ToJsonValue(json);
    EXPECT_EQ(json->GetString("gridSpan"), "");
}

/**
 * @tc.name: GridPropertyTest010
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback ToJsonValue.push gridInfo_ is not null.
     * @tc.expected: step2. Return expected results.
     */
    GridProperty testGridProperty;
    const RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(ONE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    testGridProperty.gridInfo_ = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto json = JsonUtil::Create(true);
    testGridProperty.ToJsonValue(json);
    EXPECT_EQ(json->GetString("gridOffset"), "");
}

/**
 * @tc.name: GridPropertyTest011
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback ToJsonValue.push json is true.
     * @tc.expected: step2. Return expected results.
     */
    GridProperty testGridProperty;
    std::vector<GridTypedProperty> typedPropertySet;
    GridTypedProperty testGridTypedProperty0 {GridSizeType::XS, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty1 {GridSizeType::SM, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty2 {GridSizeType::MD, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty3 {GridSizeType::LG, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    GridTypedProperty testGridTypedProperty4 {GridSizeType::XL, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    typedPropertySet.clear();
    typedPropertySet.emplace_back(testGridTypedProperty0);
    typedPropertySet.emplace_back(testGridTypedProperty1);
    typedPropertySet.emplace_back(testGridTypedProperty2);
    typedPropertySet.emplace_back(testGridTypedProperty3);
    typedPropertySet.emplace_back(testGridTypedProperty4);
    testGridProperty.typedPropertySet_ = typedPropertySet;

    auto json = JsonUtil::Create(true);
    testGridProperty.ToJsonValue(json);
    EXPECT_EQ(json->GetString("span"), "");
}

/**
 * @tc.name: GridPropertyTest012
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback ToJsonValue.push gridInfo_ is not null.
     * @tc.expected: step2. Return expected results.
     */
    GridProperty testGridProperty;
    GridTypedProperty testGridTypedProperty {GridSizeType::UNDEFINED, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    testGridProperty.typedPropertySet_.emplace_back(testGridTypedProperty);

    auto json = JsonUtil::Create(true);
    testGridProperty.ToJsonValue(json);
    EXPECT_EQ(json->GetString("offset"), "");
}

/**
 * @tc.name: GridPropertyTest013
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback ToJsonValue.push json is true.
     * @tc.expected: step2. Return expected results.
     */
    GridProperty testGridProperty;
    GridTypedProperty testGridTypedProperty {GridSizeType::UNDEFINED, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty);
    testGridProperty.gridInfo_ = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);

    auto result = testGridProperty.GetWidth();
    EXPECT_EQ(result, Dimension(0.0));
}

/**
 * @tc.name: GridPropertyTest014
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback GetOffset.push hasColumnOffset_ is false.
     * @tc.expected: step2. Return expected results.
     */
    GridProperty testGridProperty;
    GridTypedProperty testGridTypedProperty {GridSizeType::UNDEFINED, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty);

    GridColumnInfo::Builder columnBuilder;
    testGridProperty.gridInfo_ = columnBuilder.Build();

    GridContainerInfo::Builder builder;
    builder.SetColumns(1);
    builder.SetGutterWidth(TESTWIDTH);
    builder.SetMarginLeft(TESTLEFT);
    builder.SetMarginRight(TESTRIGHT);

    builder.SetSizeType(GridSizeType::XL);
    builder.SetColumnType(GridColumnType::NONE);
    builder.SetGridTemplateType(GridTemplateType::NORMAL);

    testGridProperty.gridInfo_->parent_ = builder.Build();
    testGridProperty.gridInfo_->dimOffsets_ = {TESTWIDTH};
    auto result = testGridProperty.GetOffset();
    EXPECT_EQ(result.value_, 1.0);
    EXPECT_EQ(result.unit_, DimensionUnit::VP);
}

/**
 * @tc.name: GridPropertyTest015
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback GetOffset.push hasColumnOffset_ is true.
     * @tc.expected: step2. Return expected results.
     */
    GridProperty testGridProperty;
    GridTypedProperty testGridTypedProperty {GridSizeType::XS, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET};
    testGridProperty.typedPropertySet_.push_back(testGridTypedProperty);
    testGridProperty.gridInfo_ = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    GridContainerInfo::Builder builder;
    builder.SetColumns(SPANONE);
    builder.SetGutterWidth(TESTWIDTH);
    builder.SetMarginLeft(TESTLEFT);
    builder.SetMarginRight(TESTRIGHT);

    builder.SetSizeType(GridSizeType::XL);
    builder.SetColumnType(GridColumnType::NONE);
    builder.SetGridTemplateType(GridTemplateType::NORMAL);

    testGridProperty.gridInfo_->parent_ = builder.Build();
    testGridProperty.gridInfo_->hasColumnOffset_ = true;
    auto result = testGridProperty.GetOffset();
    EXPECT_EQ(result.value_, -1.0);
    EXPECT_EQ(result.unit_, DimensionUnit::VP);
}

/**
 * @tc.name: GridPropertyTest016
 * @tc.desc: Test the operation of Grid_Property
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GridPropertyTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object GridProperty.
     * @tc.steps: step2. callback GetContainerPosition.push container_ is null.
     * @tc.expected: step2. Return expected results.
     */
    GridProperty testGridProperty;
    testGridProperty.gridInfo_ = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    GridContainerInfo::Builder builder;
    builder.SetColumns(SPANONE);
    builder.SetGutterWidth(TESTWIDTH);
    builder.SetMarginLeft(TESTLEFT);
    builder.SetMarginRight(TESTRIGHT);

    builder.SetSizeType(GridSizeType::UNDEFINED);
    builder.SetColumnType(GridColumnType::BUBBLE_TYPE);
    builder.SetGridTemplateType(GridTemplateType::GRID);

    testGridProperty.gridInfo_->parent_ = builder.Build();
    testGridProperty.gridInfo_->hasColumnOffset_ = true;
    auto result = testGridProperty.GetContainerPosition();
    EXPECT_EQ(result, OffsetF());
}
} // namespace OHOS::Ace::Ng
