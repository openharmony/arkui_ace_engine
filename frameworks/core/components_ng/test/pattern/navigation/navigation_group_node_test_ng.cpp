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

#define private public
#define protected public
#include "frameworks/base/json/json_util.h"
#include "frameworks/core/components/button/button_theme.h"
#include "frameworks/core/components_ng/base/ui_node.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"
#include "frameworks/core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_group_node.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_pattern.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_view.h"
#include "frameworks/core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "frameworks/core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "frameworks/core/components_ng/pattern/navigation/nav_bar_node.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

namespace {
const int32_t testdata = 10;
} // namespace

class NavigationGroupNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {} ;
    static void TearDownTestSuite() {} ;
};

/**
 * @tc.name: NavigationGroupNodeTestNg_001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, NavigationGroupNodeTestNg_001, TestSize.Level1)
{
    NavigationView navigationView;
    navigationView.Create();
    navigationView.SetTitle("NavigationPatternTestNg", false);
    const std::string tag = "test";
    int32_t nodeId = testdata;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::Pattern>();
    OHOS::Ace::NG::NavigationGroupNode navigationGroupNode(tag, nodeId, patternCreator);
    auto res = navigationGroupNode.GetFrameNode(tag, nodeId);
    EXPECT_EQ(res,nullptr);
    navigationGroupNode.GetOrCreateGroupNode(tag,nodeId,nullptr);
}

/**
 * @tc.name: NavigationGroupNodeTestNg_002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, NavigationGroupNodeTestNg_002, TestSize.Level1)
{
    NavigationView navigationView;
    navigationView.Create();
    navigationView.SetTitle("NavigationPatternTestNg", false);
    const std::string tag = "test";
    int32_t nodeId = testdata;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::Pattern>();
    OHOS::Ace::NG::NavigationGroupNode navigationGroupNode(tag, nodeId, patternCreator);
    navigationGroupNode.isFirstNavDestination_ = false;
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    json->isRoot_ = true;
    EXPECT_NE(json,nullptr);
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(tag, nodeId, patternCreator);
    navigationGroupNode.SetNavBarNode(navBarNode);
    EXPECT_NE(AceType::DynamicCast<OHOS::Ace::NG::NavBarNode>(navigationGroupNode.GetNavBarNode()),nullptr);
    navigationGroupNode.ToJsonValue(json);
}

} // namespace OHOS::Ace::NG