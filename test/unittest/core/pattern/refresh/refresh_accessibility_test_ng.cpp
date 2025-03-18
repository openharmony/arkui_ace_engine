/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "refresh_test_ng.h"

namespace OHOS::Ace::NG {
class RefreshAccessibilityTestNg : public RefreshTestNg {
public:
};

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test IsScrollable and SetSpecificSupportAction.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshAccessibilityTestNg, AccessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When IsScrollable
     * @tc.expected: Trigger AddSupportAction()
     */
    CreateRefresh();
    CreateDone();
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());

    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = { AceAction::ACTION_SCROLL_FORWARD };
    EXPECT_EQ(accessibilityProperty_->GetSupportAction(), expectedActions);

    /**
     * @tc.steps: step2. When IsScrollable() == false
     * @tc.expected: Nothing happened
     */
    pattern_->isRefreshing_ = true;
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());

    accessibilityProperty_->ResetSupportAction();
    expectedActions = {};
    EXPECT_EQ(accessibilityProperty_->GetSupportAction(), expectedActions);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: RefreshAccessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshAccessibilityTestNg, PerformActionTest001, TestSize.Level1)
{
    CreateRefresh();
    CreateDone();

    /**
     * @tc.steps: step1. Not refreshing
     * @tc.expected: Refresh
     */
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());

    /**
     * @tc.steps: step2. Is refreshing
     * @tc.expected: Still refresh
     */
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}
} // namespace OHOS::Ace::NG
