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

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/pattern/grid_container/grid_container_layout_property.h"
#include "core/components_ng/property/grid_property.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;

constexpr int32_t SPANONE = 10;
constexpr int32_t SPANTWO = -10;
constexpr int32_t OFFSETONE = 5;
constexpr int32_t INDEX = 1;

const Dimension TESTWIDTH { 1.0, DimensionUnit::VP };
const Dimension TESTLEFT { 2.0, DimensionUnit::VP };
const Dimension TESTRIGHT { 3.0, DimensionUnit::VP };
const Dimension TEST_VALUE = Dimension(0.0);

const GridTypedProperty TEST_TYPED0 { GridSizeType::XS, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET };
const GridTypedProperty TEST_TYPED1 { GridSizeType::SM, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET };
const GridTypedProperty TEST_TYPED2 { GridSizeType::MD, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET };
const GridTypedProperty TEST_TYPED3 { GridSizeType::LG, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET };
const GridTypedProperty TEST_TYPED4 { GridSizeType::XL, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET };
const GridTypedProperty TEST_TYPED5 { GridSizeType::UNDEFINED, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET };

void MakeProperty(RefPtr<GridProperty> gridProperty)
{
    gridProperty->typedPropertySet_.push_back(TEST_TYPED0);
    gridProperty->typedPropertySet_.push_back(TEST_TYPED1);
    gridProperty->typedPropertySet_.push_back(TEST_TYPED2);
    gridProperty->typedPropertySet_.push_back(TEST_TYPED3);
    gridProperty->typedPropertySet_.push_back(TEST_TYPED4);
    gridProperty->typedPropertySet_.push_back(TEST_TYPED5);
};
} // namespace

class GridPropertyTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void GridPropertyTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void GridPropertyTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: UpdateSpan_Test
 * @tc.desc: Test cast to GridProperty
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, UpdateSpan_Test, TestSize.Level1)
{
    /**
     * @tc.steps1: create a object gridProperty.
     */
    RefPtr<GridProperty> gridProperty = AceType::MakeRefPtr<NG::GridProperty>();
    auto type = static_cast<GridSizeType>(INDEX);

    /**
     * @tc.steps2: call UpdateSpan.push span is < 0.
     * @tc.expected: Return result is false.
     */
    bool result = gridProperty->UpdateSpan(SPANTWO, type);
    EXPECT_FALSE(result);

    /**
     * @tc.steps3: call UpdateSpan.push span >= 0, container_ is null.
     * @tc.expected: Return result is true.
     */
    bool result_Span = gridProperty->UpdateSpan(SPANONE, type);
    EXPECT_TRUE(result_Span);

    /**
     * @tc.steps4: call UpdateOffset.push Offset >= 0, container_ is null.
     * @tc.expected: Return result is true.
     */
    bool result_Off = gridProperty->UpdateOffset(OFFSETONE, type);
    EXPECT_TRUE(result_Off);
}

/**
 * @tc.name: UpdateSpan_Test002
 * @tc.desc: Test cast to GridProperty
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, UpdateSpan_Test002, TestSize.Level1)
{
    /**
     * @tc.steps1: create a object gridProperty.
     */
    RefPtr<GridProperty> gridProperty = AceType::MakeRefPtr<NG::GridProperty>();
    auto type = static_cast<GridSizeType>(INDEX);

    /**
     * @tc.steps2: create a container_.
     */
    gridProperty->container_ = AceType::MakeRefPtr<GridContainerLayoutProperty>();

    /**
     * @tc.steps2: call UpdateSpan.push span is < 0.
     * @tc.expected: Return result is false.
     */
    bool result = gridProperty->UpdateSpan(SPANONE, type);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: UpdateOffset_Test
 * @tc.desc: Test cast to GridProperty
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, UpdateOffset_Test, TestSize.Level1)
{
    /**
     * @tc.steps1: create a object gridProperty.
     */
    RefPtr<GridProperty> gridProperty = AceType::MakeRefPtr<NG::GridProperty>();
    auto type = static_cast<GridSizeType>(INDEX);

    /**
     * @tc.steps2: create a container_.
     */
    gridProperty->container_ = AceType::MakeRefPtr<GridContainerLayoutProperty>();

    /**
     * @tc.steps2: call UpdateSpan.push span is < 0.
     * @tc.expected: Return result is false.
     */
    bool result = gridProperty->UpdateOffset(OFFSETONE, type);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetSpan_Test
 * @tc.desc: Test cast to GridProperty
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, SetSpan_Test, TestSize.Level1)
{
    /**
     * @tc.steps1: create a object gridProperty.
     */
    RefPtr<GridProperty> gridProperty = AceType::MakeRefPtr<NG::GridProperty>();

    /**
     * @tc.steps2: call MakeProperty.set typedPropertySet_ is not empty
     * @tc.steps2: call SetSpan, push span_ == span.
     * @tc.expected: Return result is false.
     */
    MakeProperty(gridProperty);
    auto type = static_cast<GridSizeType>(INDEX);
    gridProperty->UpdateSpan(SPANONE, type);
    bool result = gridProperty->SetSpan(type, SPANONE);
    EXPECT_FALSE(result);

    /**
     * @tc.steps3: call SetSpan, push span_ != span.
     * @tc.expected: Return result_Span is true.
     */
    bool result_Span = gridProperty->SetSpan(type, DEFAULT_GRID_SPAN);
    EXPECT_TRUE(result_Span);
}

/**
 * @tc.name: SetOffset_Test
 * @tc.desc: Test cast to GridProperty
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, SetOffset_Test, TestSize.Level1)
{
    /**
     * @tc.steps1: create a object gridProperty.
     */
    RefPtr<GridProperty> gridProperty = AceType::MakeRefPtr<NG::GridProperty>();

    /**
     * @tc.steps2: call SetOffset, push offset_ != offset.
     * @tc.expected: Return result is true.
     */
    auto type = static_cast<GridSizeType>(INDEX);
    bool result = gridProperty->SetOffset(type, OFFSETONE);
    EXPECT_TRUE(result);

    /**
     * @tc.steps3: call MakeProperty.
     * @tc.steps3: call SetOffset, push offset_ == offset.
     * @tc.expected: Return result_Off is false.
     */
    MakeProperty(gridProperty);
    gridProperty->UpdateOffset(OFFSETONE, type);
    bool result_Off = gridProperty->SetOffset(type, OFFSETONE);
    EXPECT_FALSE(result_Off);
}

/**
 * @tc.name: ToJsonValue_Test01
 * @tc.desc: Test cast to GridProperty
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, ToJsonValue_Test01, TestSize.Level1)
{
    /**
     * @tc.steps1: create a object gridProperty.
     */
    RefPtr<GridProperty> gridProperty = AceType::MakeRefPtr<NG::GridProperty>();

    /**
     * @tc.steps2: callback ToJsonValue.push gridInfo_ is null.
     * @tc.expected: Return expected results.
     */
    auto json = JsonUtil::Create(true);
    gridProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("gridSpan"), "");
    EXPECT_EQ(json->GetString("gridOffset"), "");

    /**
     * @tc.steps3: callback GetWidth.
     * @tc.expected: expected Return result is default value.
     */
    auto result_Width = gridProperty->GetWidth();
    EXPECT_EQ(result_Width, TEST_VALUE);

    /**
     * @tc.steps4: callback GetOffset.
     * @tc.expected: expected Return result is default value.
     */
    auto result_Offset = gridProperty->GetOffset();
    EXPECT_EQ(result_Offset, TEST_VALUE);
}

/**
 * @tc.name: GetOffset_Test
 * @tc.desc: Test cast to GridProperty
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GetOffset_Test, TestSize.Level1)
{
    /**
     * @tc.steps1: create a object gridProperty.
     * @tc.steps1: create a columnBuilder and builder.
     */
    RefPtr<GridProperty> gridProperty = AceType::MakeRefPtr<NG::GridProperty>();
    GridColumnInfo::Builder columnBuilder;
    GridContainerInfo::Builder builder;
    builder.SetColumns(INDEX);
    builder.SetGutterWidth(TESTWIDTH);
    builder.SetMarginLeft(TESTLEFT);
    builder.SetMarginRight(TESTRIGHT);
    builder.SetSizeType(GridSizeType::XL);
    builder.SetColumnType(GridColumnType::NONE);
    builder.SetGridTemplateType(GridTemplateType::NORMAL);

    /**
     * @tc.steps2: callback GetOffset.push hasColumnOffset_ is false.
     * @tc.expected: Return expected results.
     */
    gridProperty->gridInfo_ = columnBuilder.Build();
    gridProperty->gridInfo_->parent_ = builder.Build();
    gridProperty->gridInfo_->dimOffsets_ = { TESTWIDTH };
    auto result_One = gridProperty->GetOffset();
    EXPECT_EQ(result_One, TESTRIGHT);

    /**
     * @tc.steps3: callback GetOffset.push hasColumnOffset_ is true.
     * @tc.expected: Return expected results.
     */
    gridProperty->gridInfo_->hasColumnOffset_ = true;
    auto result_Two = gridProperty->GetOffset();
    EXPECT_EQ(result_Two, UNDEFINED_DIMENSION);
}

/**
 * @tc.name: GetContainerPositionTest01
 * @tc.desc: Test cast to GridProperty
 * @tc.type: FUNC
 */
HWTEST_F(GridPropertyTestNg, GetContainerPositionTest01, TestSize.Level1)
{
    /**
     * @tc.steps1: create a object gridProperty.
     */
    RefPtr<GridProperty> gridProperty = AceType::MakeRefPtr<NG::GridProperty>();

    gridProperty->container_ = AceType::MakeRefPtr<GridContainerLayoutProperty>();
    auto columnFrameNode1 = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    auto temp = AceType::MakeRefPtr<GridContainerLayoutProperty>();
    temp->host_ = columnFrameNode1;
    gridProperty->container_ = temp;

    /**
     * @tc.steps2: callback GetContainerPosition.push container_ is not null.
     * @tc.expected: Return expected results.
     */
    auto result = gridProperty->GetContainerPosition();
    EXPECT_EQ(result, OffsetF());
}
} // namespace OHOS::Ace::NG
