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
#include "list_layout_test.h"

#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/list/list_view.h"
#include "frameworks/base/memory/referenced.h"
#include "frameworks/base/geometry/ng/size_t.h"

#include "gtest/gtest.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ListLayoutTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: ListLayoutTest001
 * @tc.desc: set space width into frameNode and test layout
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTest, ListLayoutTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateFrameNode function to create frameNode
     * @tc.steps: step2. call GeometryNode function to create geometryNode and set frameSize
     * @tc.steps: step3. call LayoutWrapper function to create layoutWrapper
     * @tc.steps: step4. call ListLayoutAlgorithm function to create listLayoutAlgorithm and set space
     * @tc.steps: step5. call Measure function to measure and compare result
     * @tc.expected: layout should be correct
     */
    for (size_t i = 0; i < NG::TEST_SPACE_PX_COUNT; i++) {
        auto frameNode = NG::FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<NG::ListPattern>());

        RefPtr<NG::GeometryNode> geometryNode;
        geometryNode->SetFrameSize(OHOS::Ace::NG::SizeF(NG::GEOMETRYNODE_FRAMESIZE, NG::GEOMETRYNODE_FRAMESIZE));

        NG::LayoutWrapper layoutWrapper = NG::LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());

        auto listLayoutAlgorithm = OHOS::Ace::NG::ListLayoutAlgorithm(NG::START_INDEX, NG::END_INDEX);
        float space = NG::LIST_LAYOUT_ALGORITHM_SPACE_PXS[i].Value();
        listLayoutAlgorithm.SetSpaceWidth(space);

        listLayoutAlgorithm.Measure(&layoutWrapper);
        NG::ListLayoutAlgorithm::PositionMap positionMap = listLayoutAlgorithm.GetItemPosition();
        for (size_t j = NG::START_INDEX; j < NG::END_INDEX; j++) {
            ASSERT_EQ(positionMap[j].first, NG::GEOMETRYNODE_FRAMESIZE * j + space * j);
        }
    }
}

/**
 * @tc.name: ListLayoutTest002
 * @tc.desc: set initialIndex into frameNode and test layout
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTest, ListLayoutTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateFrameNode function to create frameNode
     * @tc.steps: step2. call GeometryNode function to create geometryNode and set frameSize
     * @tc.steps: step3. call LayoutWrapper function to create layoutWrapper
     * @tc.steps: step4. call ListLayoutAlgorithm function to create listLayoutAlgorithm and set initialIndex
     * @tc.steps: step5. call Measure function to measure and compare result
     * @tc.expected: layout should be correct
     */
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto frameNode = NG::FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<NG::ListPattern>());
        NG::ViewStackProcessor::GetInstance()->Push(frameNode);

        RefPtr<NG::GeometryNode> geometryNode;
        geometryNode->SetFrameSize(OHOS::Ace::NG::SizeF(NG::GEOMETRYNODE_FRAMESIZE, NG::GEOMETRYNODE_FRAMESIZE));
        auto castListLayoutProperty = frameNode->GetLayoutProperty<NG::ListLayoutProperty>();
        if (castListLayoutProperty) {
            castListLayoutProperty->UpdateInitialIndex(index);
        }

        NG::LayoutWrapper layoutWrapper = NG::LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());

        auto listLayoutAlgorithm = OHOS::Ace::NG::ListLayoutAlgorithm(NG::START_INDEX, NG::END_INDEX);

        listLayoutAlgorithm.Measure(&layoutWrapper);
        NG::ListLayoutAlgorithm::PositionMap positionMap = listLayoutAlgorithm.GetItemPosition();
        for (size_t j = NG::START_INDEX; j < NG::END_INDEX; j++) {
            ASSERT_EQ(positionMap[j].first, NG::GEOMETRYNODE_FRAMESIZE * (j - index));
        }
    }
}
} // namespace OHOS::Ace
