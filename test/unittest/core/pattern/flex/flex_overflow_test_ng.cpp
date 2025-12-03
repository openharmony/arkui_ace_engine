/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "base/memory/ace_type.h"
#include "frameworks/core/components_ng/layout/layout_algorithm.h" // For OverflowCollector
#include "frameworks/core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "frameworks/core/components_ng/pattern/flex/flex_layout_algorithm.h"

#define protected public
#define private public

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class FlexOverflowTestNG : public FlexNewTestNG {};

/**
 * @tc.name: FlexLayoutAlgorithmLayoutWithOverflowTest
 * @tc.desc: Test Layout method with overflow collection
 * @tc.type: FUNC
 */
HWTEST_F(FlexOverflowTestNG, FlexLayoutAlgorithmLayoutWithOverflowTest, TestSize.Level0)
{
    auto frameNode = CreateFlexWrapRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);
        ViewAbstract::SetWidth(CalcLength(200.0f));
        ViewAbstract::SetHeight(CalcLength(100.0f));

        // Add children that might cause overflow
        CreateText(u"text1", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(150.0f));
            ViewAbstract::SetHeight(CalcLength(60.0f));
        });
        CreateText(u"text2", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(150.0f));
            ViewAbstract::SetHeight(CalcLength(60.0f));
        });
    });
    CreateLayoutTask(frameNode);
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    // The algorithm should have collected overflow data during layout
    // Verify that no crash occurs and the overflow collection logic is executed
    
    const auto& vOverflowHandler = pattern->GetOrCreateVerticalOverflowHandler(
        AceType::WeakClaim(AceType::RawPtr(frameNode)));
    EXPECT_NE(vOverflowHandler, nullptr);
    EXPECT_TRUE(vOverflowHandler->IsVerticalOverflow());
}
/**
 * @tc.name: FlexLayoutAlgorithmLayoutWithOverflowContentTest
 * @tc.desc: Test overflow content detection in Flex layout
 * @tc.type: FUNC
 */
HWTEST_F(FlexOverflowTestNG, FlexLayoutAlgorithmLayoutWithOverflowContentTest, TestSize.Level0)
{
    auto frameNode = CreateFlexWrapRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
        model.SetWrapDirection(WrapDirection::VERTICAL);
        ViewAbstract::SetWidth(CalcLength(100.0f));  // Small container
        ViewAbstract::SetHeight(CalcLength(100.0f));

        // Add children that exceed container size to potentially trigger overflow
        CreateText(u"longtext1", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(80.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        CreateText(u"longtext2", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(80.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        CreateText(u"longtext3", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(80.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
    });

    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    
    CreateLayoutTask(frameNode);

    const auto& vOverflowHandler = pattern->GetOrCreateVerticalOverflowHandler(
        AceType::WeakClaim(AceType::RawPtr(frameNode)));
    EXPECT_NE(vOverflowHandler, nullptr);
    EXPECT_TRUE(vOverflowHandler->IsOverflow());
}

/**
 * @tc.name: FlexLayoutAlgorithmIsRowDirectionTest
 * @tc.desc: Test the new IsRowDirection helper method
 * @tc.type: FUNC
 */
HWTEST_F(FlexOverflowTestNG, FlexLayoutAlgorithmIsRowDirectionTest, TestSize.Level0)
{
    auto frameNode = CreateFlexRow([](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);
    });
    CreateLayoutTask(frameNode);
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    auto flexLayoutAlgorithm = AceType::DynamicCast<FlexLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());

    // Test ROW direction
    flexLayoutAlgorithm->direction_ = FlexDirection::ROW;
    EXPECT_TRUE(flexLayoutAlgorithm->IsRowDirection());

    // Test ROW_REVERSE direction
    flexLayoutAlgorithm->direction_ = FlexDirection::ROW_REVERSE;
    EXPECT_TRUE(flexLayoutAlgorithm->IsRowDirection());

    // Test COLUMN direction
    flexLayoutAlgorithm->direction_ = FlexDirection::COLUMN;
    EXPECT_FALSE(flexLayoutAlgorithm->IsRowDirection());

    // Test COLUMN_REVERSE direction
    flexLayoutAlgorithm->direction_ = FlexDirection::COLUMN_REVERSE;
    EXPECT_FALSE(flexLayoutAlgorithm->IsRowDirection());
}
}