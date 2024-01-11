/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "tabs_test_ng.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TabsCommonTestNg : public TabsTestNg {
public:
    AssertionResult IsEqualNextFocusNode(FocusStep step,
        const RefPtr<FrameNode>& currentNode, const RefPtr<FrameNode>& expectNextNode);
};

AssertionResult TabsCommonTestNg::IsEqualNextFocusNode(FocusStep step,
    const RefPtr<FrameNode>& currentNode, const RefPtr<FrameNode>& expectNextNode)
{
    RefPtr<FocusHub> currentFocusNode = currentNode->GetOrCreateFocusHub();
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
    if (nextFocusNode == expectNextNode->GetOrCreateFocusHub()) {
        return AssertionSuccess();
    }
    return AssertionFailure() << "Next focusNode is not as expected";
}

/**
 * @tc.name: FocusStep001
 * @tc.desc: Test Tabs FocusStep
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, FocusStep001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, tabBarNode_, swiperNode_));
    // to do...
}
} // namespace OHOS::Ace::NG
