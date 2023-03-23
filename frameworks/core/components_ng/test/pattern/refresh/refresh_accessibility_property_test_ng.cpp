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
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
class RefreshAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: RefreshAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshAccessibilityPropertyTestNg, RefreshAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::REFRESH_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<RefreshPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto refreshPattern = frameNode->GetPattern<RefreshPattern>();
    ASSERT_NE(refreshPattern, nullptr);
    auto refreshAccessibilityProperty = frameNode->GetAccessibilityProperty<RefreshAccessibilityProperty>();
    ASSERT_NE(refreshAccessibilityProperty, nullptr);

    EXPECT_TRUE(refreshAccessibilityProperty->IsScrollable());

    refreshPattern->isRefreshing_ = true;
    EXPECT_FALSE(refreshAccessibilityProperty->IsScrollable());
}
} // namespace OHOS::Ace::NG
