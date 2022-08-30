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

#define private public

#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_view.h"
#include "frameworks/base/memory/referenced.h"
#include "frameworks/base/geometry/ng/size_t.h"

#include "gtest/gtest.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t START_INDEX = 0;
constexpr int32_t END_INDEX = 10;
constexpr int32_t INDEX_NUMBER = 10;

constexpr int32_t SCALE_SIZE = 20;

constexpr float GEOMETRYNODE_FRAMESIZE = 200.0;

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
constexpr int32_t TEST_SPACE_PX_COUNT = 5;

constexpr int32_t LANES_3 = 3;
} // namespace

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
    for (int32_t i = 0; i < TEST_SPACE_PX_COUNT; i++) {
        auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<Pattern>());
        ViewStackProcessor::GetInstance()->Push(frameNode);

        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        float mainSize = GEOMETRYNODE_FRAMESIZE * INDEX_NUMBER +
            LIST_LAYOUT_ALGORITHM_SPACE_PXS[i].Value() * INDEX_NUMBER;
        geometryNode->SetFrameSize(OHOS::Ace::NG::SizeF(mainSize, mainSize));

        LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
        for (int32_t j = START_INDEX; j < END_INDEX; j++) {
            auto childFrameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0,
                AceType::MakeRefPtr<Pattern>());
            ViewStackProcessor::GetInstance()->Push(childFrameNode);
            RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
            childGeometryNode->SetFrameSize(
                OHOS::Ace::NG::SizeF(GEOMETRYNODE_FRAMESIZE, GEOMETRYNODE_FRAMESIZE));
            RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(childFrameNode,
                childGeometryNode, childFrameNode->GetLayoutProperty());
            childLayoutWrapper->GetGeometryNode()->SetFrameSize(
                OHOS::Ace::NG::SizeF(GEOMETRYNODE_FRAMESIZE, GEOMETRYNODE_FRAMESIZE));
            layoutWrapper.AppendChild(std::move(childLayoutWrapper));
        }

        auto listLayoutAlgorithm = OHOS::Ace::NG::ListLayoutAlgorithm(START_INDEX, END_INDEX);
        float space = LIST_LAYOUT_ALGORITHM_SPACE_PXS[i].Value();
        listLayoutAlgorithm.SetSpaceWidth(space);

        auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper.GetLayoutProperty());

        LayoutConstraintF setLayoutConstraint;
        setLayoutConstraint.Reset();
        listLayoutProperty->UpdateLayoutConstraint(setLayoutConstraint);

        listLayoutAlgorithm.SetSpaceWidth(space);

        for (int32_t j = START_INDEX; j < END_INDEX; j++) {
            listLayoutAlgorithm.itemPosition_[j] = {0.0, 0.0};
        }
        listLayoutAlgorithm.LayoutForward(&layoutWrapper, setLayoutConstraint,
            Axis::VERTICAL, mainSize * SCALE_SIZE);

        for (int32_t j = START_INDEX; j < END_INDEX; j++) {
            auto wrapper = layoutWrapper.GetOrCreateChildByIndex(j);
            auto size = wrapper->GetGeometryNode()->GetFrameSize();
            ASSERT_EQ(size.Height(), GEOMETRYNODE_FRAMESIZE);
            ASSERT_EQ(size.Width(), GEOMETRYNODE_FRAMESIZE);
            ASSERT_EQ(listLayoutAlgorithm.itemPosition_[j].first, GEOMETRYNODE_FRAMESIZE * j + space * j);
        }
        ASSERT_EQ(space, listLayoutAlgorithm.GetSpaceWidth());
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
    for (int32_t i = 0; i < TEST_SPACE_PX_COUNT; i++) {
        auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<Pattern>());
        ViewStackProcessor::GetInstance()->Push(frameNode);

        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        float mainSize = GEOMETRYNODE_FRAMESIZE * INDEX_NUMBER +
            LIST_LAYOUT_ALGORITHM_SPACE_PXS[i].Value() * INDEX_NUMBER;
        geometryNode->SetFrameSize(OHOS::Ace::NG::SizeF(mainSize, mainSize));

        LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
        for (int32_t j = START_INDEX; j < END_INDEX; j++) {
            auto childFrameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0,
                AceType::MakeRefPtr<Pattern>());
            ViewStackProcessor::GetInstance()->Push(childFrameNode);
            RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
            childGeometryNode->SetFrameSize(
                OHOS::Ace::NG::SizeF(GEOMETRYNODE_FRAMESIZE, GEOMETRYNODE_FRAMESIZE));
            RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(childFrameNode,
                childGeometryNode, childFrameNode->GetLayoutProperty());
            childLayoutWrapper->GetGeometryNode()->SetFrameSize(
                OHOS::Ace::NG::SizeF(GEOMETRYNODE_FRAMESIZE, GEOMETRYNODE_FRAMESIZE));
            layoutWrapper.AppendChild(std::move(childLayoutWrapper));
        }

        auto listLayoutAlgorithm = OHOS::Ace::NG::ListLayoutAlgorithm(i, END_INDEX);

        auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper.GetLayoutProperty());

        LayoutConstraintF setLayoutConstraint;
        setLayoutConstraint.Reset();
        listLayoutProperty->UpdateLayoutConstraint(setLayoutConstraint);

        for (int32_t j = START_INDEX; j < END_INDEX; j++) {
            listLayoutAlgorithm.itemPosition_[j] = {0.0, 0.0};
        }
        listLayoutAlgorithm.LayoutForward(&layoutWrapper, setLayoutConstraint,
            Axis::VERTICAL, mainSize * SCALE_SIZE);

        for (int32_t j = i; j < END_INDEX; j++) {
            auto wrapper = layoutWrapper.GetOrCreateChildByIndex(j);
            auto size = wrapper->GetGeometryNode()->GetFrameSize();
            ASSERT_EQ(size.Height(), GEOMETRYNODE_FRAMESIZE);
            ASSERT_EQ(size.Width(), GEOMETRYNODE_FRAMESIZE);
            ASSERT_EQ(listLayoutAlgorithm.itemPosition_[j].first, GEOMETRYNODE_FRAMESIZE * (j - i));
        }
    }
}

/**
 * @tc.name: ListLayoutTest003
 * @tc.desc: set lanes into frameNode and test layout
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTest, ListLayoutTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateFrameNode function to create frameNode
     * @tc.steps: step2. call GeometryNode function to create geometryNode and set frameSize
     * @tc.steps: step3. call LayoutWrapper function to create layoutWrapper
     * @tc.steps: step4. call ListLayoutAlgorithm function to create listLayoutAlgorithm and set lanes
     * @tc.steps: step5. call Measure function to measure and compare result
     * @tc.expected: layout should be correct
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<Pattern>());
    ViewStackProcessor::GetInstance()->Push(frameNode);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    float mainSize = GEOMETRYNODE_FRAMESIZE * INDEX_NUMBER;
    geometryNode->SetFrameSize(OHOS::Ace::NG::SizeF(mainSize, mainSize));

    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    for (int32_t j = START_INDEX; j < END_INDEX; j++) {
        auto childFrameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0,
            AceType::MakeRefPtr<Pattern>());
        ViewStackProcessor::GetInstance()->Push(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        childGeometryNode->SetFrameSize(
            OHOS::Ace::NG::SizeF(GEOMETRYNODE_FRAMESIZE, GEOMETRYNODE_FRAMESIZE));
        RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(childFrameNode,
            childGeometryNode, childFrameNode->GetLayoutProperty());
        childLayoutWrapper->GetGeometryNode()->SetFrameSize(
            OHOS::Ace::NG::SizeF(GEOMETRYNODE_FRAMESIZE, GEOMETRYNODE_FRAMESIZE));
        layoutWrapper.AppendChild(std::move(childLayoutWrapper));
    }

    auto listLayoutAlgorithm = OHOS::Ace::NG::ListLayoutAlgorithm(START_INDEX, END_INDEX);

    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper.GetLayoutProperty());
    int32_t lanes = LANES_3;
    listLayoutAlgorithm.SetLanes(lanes);

    LayoutConstraintF setLayoutConstraint;
    setLayoutConstraint.Reset();
    listLayoutProperty->UpdateLayoutConstraint(setLayoutConstraint);

    for (int32_t j = START_INDEX; j < END_INDEX; j++) {
        listLayoutAlgorithm.itemPosition_[j] = {0.0, 0.0};
    }
    listLayoutAlgorithm.LayoutForwardForLaneList(&layoutWrapper, setLayoutConstraint,
        Axis::VERTICAL, mainSize * SCALE_SIZE);

    for (int32_t j = START_INDEX; j < END_INDEX; j++) {
        ASSERT_EQ(listLayoutAlgorithm.itemPosition_[j].first, GEOMETRYNODE_FRAMESIZE * (j / lanes));
    }
}
} // namespace OHOS::Ace
