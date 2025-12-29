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
#include "frameworks/core/components/common/layout/constants.h" // For WrapDirection
#include "frameworks/core/components_ng/layout/layout_algorithm.h" // For OverflowCollector
#include "frameworks/core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "frameworks/core/components_ng/pattern/flex/wrap_layout_algorithm.h"

#define protected public
#define private public

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class WrapOverflowTestNG : public FlexNewTestNG {};

/**
 * @tc.name: WrapLayoutAlgorithmVerticalOverflowTest
 * @tc.desc: Test Wrap layout with vertical overflow collection and content detection
 * @tc.type: FUNC
 */
HWTEST_F(WrapOverflowTestNG, WrapLayoutAlgorithmVerticalOverflowTest, TestSize.Level0)
{
    auto frameNode = CreateFlexWrapRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);
        ViewAbstract::SetWidth(CalcLength(100.0f));  // Small container to force wrapping
        ViewAbstract::SetHeight(CalcLength(100.0f));

        // Add multiple items that will wrap
        for (int i = 0; i < 6; i++) {
            std::string str = "text" + std::to_string(i);
            std::u16string input(str.begin(), str.end());
            CreateText(input, [this](TextModelNG model) {
                ViewAbstract::SetWidth(CalcLength(80.0f));
                ViewAbstract::SetHeight(CalcLength(60.0f));
            });
        }
    });

    CreateLayoutTask(frameNode);
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);

    const auto& vOverflowHandler = pattern->GetOrCreateVerticalOverflowHandler(
        AceType::WeakClaim(AceType::RawPtr(frameNode)));
    EXPECT_NE(vOverflowHandler, nullptr);
    EXPECT_TRUE(vOverflowHandler->IsVerticalOverflow());
}

/**
 * @tc.name: WrapLayoutAlgorithmHorizontalOverflowTest
 * @tc.desc: Test Wrap layout with horizontal overflow collection
 * @tc.type: FUNC
 */
HWTEST_F(WrapOverflowTestNG, WrapLayoutAlgorithmHorizontalOverflowTest, TestSize.Level0)
{
    auto frameNode = CreateFlexWrapRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
        model.SetWrapDirection(WrapDirection::VERTICAL);
        ViewAbstract::SetWidth(CalcLength(200.0f));
        ViewAbstract::SetHeight(CalcLength(150.0f));  // Small height to force wrapping

        // Add multiple items that will wrap vertically
        for (int i = 0; i < 6; i++) {
            std::string str = "text" + std::to_string(i);
            std::u16string input(str.begin(), str.end());
            CreateText(input, [this](TextModelNG model) {
                ViewAbstract::SetWidth(CalcLength(50.0f));
                ViewAbstract::SetHeight(CalcLength(100.0f));
            });
        }
    });

    CreateLayoutTask(frameNode);
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    
    const auto& vOverflowHandler = pattern->GetOrCreateVerticalOverflowHandler(
        AceType::WeakClaim(AceType::RawPtr(frameNode)));
    EXPECT_NE(vOverflowHandler, nullptr);
    EXPECT_TRUE(vOverflowHandler->IsOverflow());
}
} // namespace OHOS::Ace::NG