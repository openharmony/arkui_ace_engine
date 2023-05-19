/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <memory>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "base/geometry/ng/rect_t.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/option/option_layout_algorithm.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/property/geometry_property.h"
#include "core/components_ng/property/measure_property.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class PanelOptionTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void PanelOptionTestNg::SetUpTestCase() {}

void PanelOptionTestNg::TearDownTestCase() {}

void PanelOptionTestNg::SetUp() {}

void PanelOptionTestNg::TearDown() {}

/**
 * @tc.name: PanelOptionTestNg001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanelOptionTestNg, PanelOptionTestNg001, TestSize.Level1)
{
    OHOS::Ace::NG::OptionLayoutAlgorithm rosenOptionLayoutAlgorithm;
    rosenOptionLayoutAlgorithm.horInterval_ = 2.0;
    EXPECT_FLOAT_EQ(rosenOptionLayoutAlgorithm.horInterval_, 2.0);
    auto rosenMakeRefPtr = AceType::MakeRefPtr<OHOS::Ace::NG::LayoutProperty>();
    auto rosenRefPtr = AceType::MakeRefPtr<OHOS::Ace::NG::GeometryNode>();
    rosenRefPtr->margin_ = nullptr;
    OHOS::Ace::NG::LayoutWrapper* rosenLayoutWrapper = new LayoutWrapper(nullptr, rosenRefPtr, rosenMakeRefPtr);
    rosenOptionLayoutAlgorithm.Layout(rosenLayoutWrapper);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Option Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(PanelOptionTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create option frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<OptionPattern>(0); });
    ASSERT_NE(frameNode, nullptr);
    auto optionPattern = frameNode->GetPattern<OptionPattern>();
    ASSERT_NE(optionPattern, nullptr);
    optionPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step2. Get option accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto optionAccessibilityProperty = frameNode->GetAccessibilityProperty<OptionAccessibilityProperty>();
    ASSERT_NE(optionAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step3. Call the callback function in optionAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(optionAccessibilityProperty->ActActionSelect());
}
} // namespace OHOS::Ace::NG
