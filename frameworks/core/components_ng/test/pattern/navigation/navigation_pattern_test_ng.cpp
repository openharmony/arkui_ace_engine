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

#include "gtest/gtest.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_view.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class NavigationPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
protected:
};

/**
 * @tc.name: NavigationPatternTest_001
 * @tc.desc: Test REPLACE navigator.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_001, TestSize.Level1)
{
    NavigationView navigationView;
    navigationView.Create();
    navigationView.SetTitle("navigationView", false);

    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    EXPECT_FALSE(navigationLayoutProperty == nullptr);
}
}