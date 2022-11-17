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

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
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
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string EMPTY_TAG;
const Dimension SPACE_ZERO;
const Dimension SPACE_ONE(1);
} // namespace

class LinearLayoutCreatorTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void LinearLayoutCreatorTestNg::SetUp() {}

void LinearLayoutCreatorTestNg::TearDown() {}

/**
 * @tc.name: LinearRowCreatorTest001
 * @tc.desc: Test create row without space
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutCreatorTestNg, LinearRowCreatorTest001, TestSize.Level1)
{
    RowModelNG instance;
    instance.Create(SPACE_ZERO, nullptr, EMPTY_TAG);
    auto rowFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(rowFrameNode == nullptr);
    EXPECT_EQ(rowFrameNode->GetTag(), V2::ROW_ETS_TAG);
    auto layoutProperty = rowFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);
    auto direction = layoutProperty->GetFlexDirection();
    EXPECT_TRUE(direction.has_value());
    EXPECT_EQ(direction.value(), FlexDirection::ROW);
    auto space = layoutProperty->GetSpace();
    EXPECT_TRUE(space.has_value());
    EXPECT_EQ(space.value(), SPACE_ZERO);
}

/**
 * @tc.name: LinearRowCreatorTest002
 * @tc.desc: Test create row with space
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutCreatorTestNg, LinearRowCreatorTest002, TestSize.Level1)
{
    RowModelNG instance;
    instance.Create(SPACE_ONE, nullptr, EMPTY_TAG);
    auto rowFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(rowFrameNode == nullptr);
    EXPECT_EQ(rowFrameNode->GetTag(), V2::ROW_ETS_TAG);
    auto layoutProperty = rowFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);
    auto direction = layoutProperty->GetFlexDirection();
    EXPECT_TRUE(direction.has_value());
    EXPECT_EQ(direction.value(), FlexDirection::ROW);
    auto space = layoutProperty->GetSpace();
    EXPECT_TRUE(space.has_value());
    EXPECT_EQ(space.value(), SPACE_ONE);
}

/**
 * @tc.name: LinearColumnCreatorTest001
 * @tc.desc: Test create column without space
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutCreatorTestNg, LinearColumnCreatorTest001, TestSize.Level1)
{
    ColumnModelNG instance;
    instance.Create(SPACE_ZERO, nullptr, EMPTY_TAG);
    auto columnFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(columnFrameNode == nullptr);
    EXPECT_EQ(columnFrameNode->GetTag(), V2::COLUMN_ETS_TAG);
    auto layoutProperty = columnFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);
    auto direction = layoutProperty->GetFlexDirection();
    EXPECT_TRUE(direction.has_value());
    EXPECT_EQ(direction.value(), FlexDirection::COLUMN);
    auto space = layoutProperty->GetSpace();
    EXPECT_TRUE(space.has_value());
    EXPECT_EQ(space.value(), SPACE_ZERO);
}

/**
 * @tc.name: LinearColumnCreatorTest002
 * @tc.desc: Test create column with space
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutCreatorTestNg, LinearColumnCreatorTest002, TestSize.Level1)
{
    ColumnModelNG instance;
    instance.Create(SPACE_ONE, nullptr, EMPTY_TAG);
    auto columnFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(columnFrameNode == nullptr);
    EXPECT_EQ(columnFrameNode->GetTag(), V2::COLUMN_ETS_TAG);
    auto layoutProperty = columnFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);
    auto direction = layoutProperty->GetFlexDirection();
    EXPECT_TRUE(direction.has_value());
    EXPECT_EQ(direction.value(), FlexDirection::COLUMN);
    auto space = layoutProperty->GetSpace();
    EXPECT_TRUE(space.has_value());
    EXPECT_EQ(space.value(), SPACE_ONE);
}
} // namespace OHOS::Ace::NG