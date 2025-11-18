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

#include <optional>

#include "gtest/gtest.h"
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"

#define protected public
#define private public
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/navigation/navigation_layout_util.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class NavigationLayoutUtilTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void NavigationLayoutUtilTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavigationLayoutUtilTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/*
 * @tc.name: CheckVerticalExtend
 * @tc.desc: branch if (hideToolbar) true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutUtilTest, CheckVerticalExtend, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto layoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIgnoreLayoutSafeAreaOpts({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_ALL });
    auto& opts = *(layoutProperty->GetIgnoreLayoutSafeAreaOpts());
    layoutProperty->propHideToolBar_ = true;

    auto ret = NavigationLayoutUtil::CheckVerticalExtend(layoutProperty, navDestinationNode, opts);
    EXPECT_EQ(ret.second, true);
}
} // namespace OHOS::Ace::NG