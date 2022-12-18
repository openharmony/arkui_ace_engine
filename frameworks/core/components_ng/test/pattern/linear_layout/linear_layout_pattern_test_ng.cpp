/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include <optional>

#include "gtest/gtest.h"

#define private public
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/linear_layout/column_model.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_styles.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_utils.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string EMPTY_TAG;
constexpr Dimension SPACE_NEGATIVE(-1);
constexpr Dimension SPACE_ONE(1);
} // namespace

class LinearLayoutPatternTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void LinearLayoutPatternTestNg::SetUp() {}

void LinearLayoutPatternTestNg::TearDown() {}

/**
 * @tc.name: LinearRowCreatorTest001
 * @tc.desc: Test create row without space
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutPatternTestNg, LinearRowCreatorTest001, TestSize.Level1)
{
    RowModelNG instance;
    instance.Create(SPACE_NEGATIVE, nullptr, EMPTY_TAG);
    instance.SetAlignItems(FlexAlign::FLEX_START);
    instance.SetJustifyContent(FlexAlign::FLEX_END);
    auto rowFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(rowFrameNode, nullptr);
    EXPECT_EQ(rowFrameNode->GetTag(), V2::ROW_ETS_TAG);
    auto layoutProperty = rowFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto direction = layoutProperty->GetFlexDirection();
    EXPECT_EQ(direction.has_value(), true);
    EXPECT_EQ(direction.value(), FlexDirection::ROW);
    auto space = layoutProperty->GetSpace();
    EXPECT_EQ(space.has_value(), false);
    EXPECT_EQ(space->ConvertToPx(), 0);
    EXPECT_EQ(layoutProperty->GetCrossAxisAlign(), FlexAlign::FLEX_START);
    EXPECT_EQ(layoutProperty->GetMainAxisAlign(), FlexAlign::FLEX_END);
}

/**
 * @tc.name: LinearRowCreatorTest002
 * @tc.desc: Test create row with space
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutPatternTestNg, LinearRowCreatorTest002, TestSize.Level1)
{
    RowModelNG instance;
    instance.Create(SPACE_ONE, nullptr, EMPTY_TAG);
    auto rowFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(rowFrameNode, nullptr);
    EXPECT_EQ(rowFrameNode->GetTag(), V2::ROW_ETS_TAG);
    auto layoutProperty = rowFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto direction = layoutProperty->GetFlexDirection();
    EXPECT_EQ(direction.has_value(), true);
    EXPECT_EQ(direction.value(), FlexDirection::ROW);
    auto space = layoutProperty->GetSpace();
    EXPECT_EQ(space.has_value(), true);
    EXPECT_EQ(space.value(), SPACE_ONE);
}

/**
 * @tc.name: LinearColumnCreatorTest001
 * @tc.desc: Test create column without space
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutPatternTestNg, LinearColumnCreatorTest001, TestSize.Level1)
{
    ColumnModelNG instance;
    instance.Create(SPACE_NEGATIVE, nullptr, EMPTY_TAG);
    instance.SetAlignItems(FlexAlign::FLEX_END);
    instance.SetJustifyContent(FlexAlign::FLEX_START);
    auto columnFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(columnFrameNode, nullptr);
    EXPECT_EQ(columnFrameNode->GetTag(), V2::COLUMN_ETS_TAG);
    auto layoutProperty = columnFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto direction = layoutProperty->GetFlexDirection();
    EXPECT_EQ(direction.has_value(), true);
    EXPECT_EQ(direction.value(), FlexDirection::COLUMN);
    auto space = layoutProperty->GetSpace();
    EXPECT_EQ(space.has_value(), false);
    EXPECT_EQ(space->ConvertToPx(), 0);
    EXPECT_EQ(layoutProperty->GetCrossAxisAlign(), FlexAlign::FLEX_END);
    EXPECT_EQ(layoutProperty->GetMainAxisAlign(), FlexAlign::FLEX_START);
}

/**
 * @tc.name: LinearColumnCreatorTest002
 * @tc.desc: Test create column with space
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutPatternTestNg, LinearColumnCreatorTest002, TestSize.Level1)
{
    ColumnModelNG instance;
    instance.Create(SPACE_ONE, nullptr, EMPTY_TAG);
    auto columnFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(columnFrameNode, nullptr);
    EXPECT_EQ(columnFrameNode->GetTag(), V2::COLUMN_ETS_TAG);
    auto layoutProperty = columnFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto direction = layoutProperty->GetFlexDirection();
    EXPECT_EQ(direction.has_value(), true);
    EXPECT_EQ(direction.value(), FlexDirection::COLUMN);
    auto space = layoutProperty->GetSpace();
    EXPECT_EQ(space.has_value(), true);
    EXPECT_EQ(space.value(), SPACE_ONE);
}

/**
 * @tc.name: LinearLayoutPatternTest001
 * @tc.desc: Verify whether the layout property, layoutAlgorithm are created.
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutPatternTestNg, LinearLayoutPatternTest001, TestSize.Level1)
{
    RowModelNG instance;
    instance.Create(SPACE_ONE, nullptr, EMPTY_TAG);
    auto rowFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(rowFrameNode, nullptr);

    auto rowPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_NE(rowPattern, nullptr);
    auto rowLayoutProperty = rowPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(rowLayoutProperty, nullptr);
    EXPECT_EQ(rowPattern->isVertical_, false);
}
} // namespace OHOS::Ace::NG