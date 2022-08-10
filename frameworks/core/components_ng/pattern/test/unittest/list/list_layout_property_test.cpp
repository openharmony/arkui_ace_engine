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
#include "core/components_ng/pattern/test/unittest/list/list_layout_algorithm_test.h"

#include "core/components_v2/inspector/inspector_constants.h"
#include "frameworks/base/memory/referenced.h"
#include "frameworks/base/geometry/ng/size_t.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/list/list_view.h"

#include "gtest/gtest.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ListLayoutPropertyTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: ListLayoutPropertyTest001
 * @tc.desc: set space width into listLayoutProperty and get it
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutPropertyTest, ListLayoutPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateFrameNode function to create frameNode
     * @tc.steps: step2. call GetLayoutProperty function to get layoutProperty and set space
     * @tc.steps: step3. call GetSpace function to get space and compare
     * @tc.expected: if Dimension is PX, value should not be changed
     */
    for (size_t i = 0; i < NG::TEST_SPACE_PX_COUNT; i++) {
        auto frameNode = NG::FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<NG::ListPattern>());
        NG::ViewStackProcessor::GetInstance()->Push(frameNode);
        auto castListLayoutProperty = frameNode->GetLayoutProperty<NG::ListLayoutProperty>();
        if (castListLayoutProperty) {
            castListLayoutProperty->UpdateSpace(NG::LIST_LAYOUT_ALGORITHM_SPACE_PXS[i]);
        }
        auto layoutProperty = frameNode->GetLayoutProperty();
        auto listLayoutProperty = AceType::DynamicCast<OHOS::Ace::NG::ListLayoutProperty>(layoutProperty);
        ASSERT_NE(listLayoutProperty, nullptr);
        auto space = listLayoutProperty->GetSpace().value_or(Dimension(0));
        ASSERT_EQ(NG::LIST_LAYOUT_ALGORITHM_SPACE_PXS[i].Value(), space.Value());
    }
}

/**
 * @tc.name: ListLayoutPropertyTest002
 * @tc.desc: set initialIndex into listLayoutProperty and get it
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutPropertyTest, ListLayoutPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateFrameNode function to create frameNode
     * @tc.steps: step2. call GetLayoutProperty function to get layoutProperty and set initialIndex
     * @tc.steps: step3. call GetInitialIndex function to get initialIndex and compare
     * @tc.expected: if initialIndex is number, value should not be changed
     */
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto frameNode = NG::FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<NG::ListPattern>());
        NG::ViewStackProcessor::GetInstance()->Push(frameNode);
        auto castListLayoutProperty = frameNode->GetLayoutProperty<NG::ListLayoutProperty>();
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
} // namespace OHOS::Ace