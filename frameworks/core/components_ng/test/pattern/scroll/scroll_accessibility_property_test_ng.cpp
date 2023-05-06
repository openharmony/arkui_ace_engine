/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License" << std::endl;
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

#include "core/components_v2/inspector/inspector_constants.h"

#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr float SCROLLABLE_DISTANCE = 10.0f;
constexpr float CURRENT_DISTANCE = -5.0f;
constexpr float CURRENT_DISTANCE_TOP = 0.0f;
constexpr float CURRENT_DISTANCE_BOTTOM = -SCROLLABLE_DISTANCE;
} // namespace
class ScrollAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: ScrollAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of scrollAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollAccessibilityPropertyTestNg, ScrollAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SCROLL_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto scrollPattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto scrollAccessibilityProperty = frameNode->GetAccessibilityProperty<ScrollAccessibilityProperty>();
    ASSERT_NE(scrollAccessibilityProperty, nullptr);
    EXPECT_FALSE(scrollAccessibilityProperty->IsScrollable());

    scrollPattern->SetAxis(Axis::VERTICAL);
    scrollPattern->scrollableDistance_ = SCROLLABLE_DISTANCE;
    EXPECT_TRUE(scrollAccessibilityProperty->IsScrollable());

    scrollPattern->SetAxis(Axis::NONE);
    EXPECT_FALSE(scrollAccessibilityProperty->IsScrollable());
}

/**
 * @tc.name: ScrollAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of scrollAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollAccessibilityPropertyTestNg, ScrollAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode, scrollPattern, scrollAccessibilityProperty.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SCROLL_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto scrollPattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto scrollAccessibilityProperty = frameNode->GetAccessibilityProperty<ScrollAccessibilityProperty>();
    ASSERT_NE(scrollAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step2. set scrollPattern property for test.
     */
    scrollPattern->axis_ = Axis::VERTICAL;
    scrollPattern->scrollableDistance_ = SCROLLABLE_DISTANCE;
    scrollPattern->currentOffset_ = CURRENT_DISTANCE;

    /**
     * @tc.steps: step3. callback ResetSupportAction then GetSupportAction, copy to actions. Contrast actions and expectActions.
     * @tc.expected: expect actions equals to expectActions.
     */
    scrollAccessibilityProperty->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = scrollAccessibilityProperty->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);

    /**
     * @tc.steps: step4. change scrollPattern property and retrieve actions from updated SupportAction. Contrast actions and expectActions.
     * @tc.expected: expect actions equals to expectActions.
     */
    scrollPattern->currentOffset_ = CURRENT_DISTANCE_TOP;
    scrollAccessibilityProperty->ResetSupportAction();
    supportAceActions = scrollAccessibilityProperty->GetSupportAction();
    actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);

    /**
     * @tc.steps: step5. change scrollPattern property and retrieve actions from updated SupportAction. Contrast actions and expectActions.
     * @tc.expected: expect actions equals to expectActions.
     */
    scrollPattern->currentOffset_ = CURRENT_DISTANCE_BOTTOM;
    scrollAccessibilityProperty->ResetSupportAction();
    supportAceActions = scrollAccessibilityProperty->GetSupportAction();
    actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);

    /**
     * @tc.steps: step6. change scrollPattern property and retrieve actions from updated SupportAction. Contrast actions and expectActions.
     * @tc.expected: expect actions equals to expectActions.
     */
    scrollPattern->axis_ = Axis::NONE;
    scrollAccessibilityProperty->ResetSupportAction();
    supportAceActions = scrollAccessibilityProperty->GetSupportAction();
    actions = 0, expectActions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}
} // namespace OHOS::Ace::NG
