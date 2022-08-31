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

#include "core/components_v2/inspector/inspector_constants.h"
#include "frameworks/base/memory/referenced.h"
#include "frameworks/base/geometry/ng/size_t.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_view.h"

#include "gtest/gtest.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t START_INDEX = 0;
constexpr int32_t END_INDEX = 10;

constexpr Dimension LIST_LAYOUT_ALGORITHM_SPACE_PX_1 = Dimension(0);
constexpr Dimension LIST_LAYOUT_ALGORITHM_SPACE_PX_2 = Dimension(10);
constexpr Dimension LIST_LAYOUT_ALGORITHM_SPACE_PX_3 = Dimension(100);
constexpr Dimension LIST_LAYOUT_ALGORITHM_SPACE_PX_4 = Dimension(1000);
constexpr Dimension LIST_LAYOUT_ALGORITHM_SPACE_PX_5 = Dimension(10000);
const std::vector<Dimension> LIST_LAYOUT_ALGORITHM_SPACE_PXS = {LIST_LAYOUT_ALGORITHM_SPACE_PX_1,
                                                                LIST_LAYOUT_ALGORITHM_SPACE_PX_2,
                                                                LIST_LAYOUT_ALGORITHM_SPACE_PX_3,
                                                                LIST_LAYOUT_ALGORITHM_SPACE_PX_4,
                                                                LIST_LAYOUT_ALGORITHM_SPACE_PX_5};
constexpr size_t TEST_SPACE_PX_COUNT = 5;

constexpr int32_t LANES_1 = 1;
constexpr int32_t LANES_2 = 2;
constexpr int32_t LANES_3 = 3;
constexpr int32_t LANES_4 = 4;
constexpr int32_t LANES_5 = 5;
const std::vector<int32_t> LANES = {LANES_1,
                                    LANES_2,
                                    LANES_3,
                                    LANES_4,
                                    LANES_5};
constexpr int32_t LANES_COUNT = 5;
} // namespace

class ListPropertyTest  : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: ListLayoutPropertyTest001
 * @tc.desc: set space width into listLayoutProperty and get it
 * @tc.type: FUNC
 */
HWTEST_F(ListPropertyTest, ListLayoutPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateFrameNode function to create frameNode
     * @tc.steps: step2. call GetLayoutProperty function to get layoutProperty and set space
     * @tc.steps: step3. call GetSpace function to get space and compare
     * @tc.expected: if Dimension is PX, value should not be changed
     */
    for (size_t i = 0; i < TEST_SPACE_PX_COUNT; i++) {
        auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<Pattern>());
        ViewStackProcessor::GetInstance()->Push(frameNode);
        auto castListLayoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
        if (castListLayoutProperty) {
            castListLayoutProperty->UpdateSpace(LIST_LAYOUT_ALGORITHM_SPACE_PXS[i]);
        }
        auto layoutProperty = frameNode->GetLayoutProperty();
        auto listLayoutProperty = AceType::DynamicCast<OHOS::Ace::NG::ListLayoutProperty>(layoutProperty);
        ASSERT_NE(listLayoutProperty, nullptr);
        auto space = listLayoutProperty->GetSpace().value_or(Dimension(0));
        ASSERT_EQ(LIST_LAYOUT_ALGORITHM_SPACE_PXS[i].Value(), space.Value());
    }
}

/**
 * @tc.name: ListLayoutPropertyTest002
 * @tc.desc: set initialIndex into listLayoutProperty and get it
 * @tc.type: FUNC
 */
HWTEST_F(ListPropertyTest, ListLayoutPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateFrameNode function to create frameNode
     * @tc.steps: step2. call GetLayoutProperty function to get layoutProperty and set initialIndex
     * @tc.steps: step3. call GetInitialIndex function to get initialIndex and compare
     * @tc.expected: if initialIndex is number, value should not be changed
     */
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<Pattern>());
        ViewStackProcessor::GetInstance()->Push(frameNode);
        auto castListLayoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
        if (castListLayoutProperty) {
            castListLayoutProperty->UpdateInitialIndex(index);
        }
        auto layoutProperty = frameNode->GetLayoutProperty();
        auto listLayoutProperty = AceType::DynamicCast<OHOS::Ace::NG::ListLayoutProperty>(layoutProperty);
        ASSERT_NE(listLayoutProperty, nullptr);
        auto initialIndex = listLayoutProperty->GetInitialIndex().value_or(0);
        ASSERT_EQ(index, initialIndex);
    }
}

/**
 * @tc.name: ListLayoutPropertyTest003
 * @tc.desc: set lanes into listLayoutProperty and get it
 * @tc.type: FUNC
 */
HWTEST_F(ListPropertyTest, ListLayoutPropertyTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateFrameNode function to create frameNode
     * @tc.steps: step2. call GetLayoutProperty function to get layoutProperty and set lanes
     * @tc.steps: step3. call GetLanes function to get lanes and compare
     * @tc.expected: if lanes is number, value should not be changed
     */
    for (int32_t index = 0; index < LANES_COUNT; index++) {
        auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<Pattern>());
        ViewStackProcessor::GetInstance()->Push(frameNode);
        auto castListLayoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
        if (castListLayoutProperty) {
            castListLayoutProperty->UpdateLanes(LANES[index]);
        }
        auto layoutProperty = frameNode->GetLayoutProperty();
        auto listLayoutProperty = AceType::DynamicCast<OHOS::Ace::NG::ListLayoutProperty>(layoutProperty);
        ASSERT_NE(listLayoutProperty, nullptr);
        auto lanes = listLayoutProperty->GetLanes().value_or(0);
        ASSERT_EQ(lanes, LANES[index]);
    }
}
} // namespace OHOS::Ace
